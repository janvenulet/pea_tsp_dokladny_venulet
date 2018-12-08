#include"myGraph.h"



using namespace std;

#include <windows.h>

double PCFreq = 0.0;
__int64 CounterStart = 0;

void StartCounter()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		cout << "QueryPerformanceFrequency failed!\n";

	PCFreq = double(li.QuadPart) / 1000.0;

	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}
double GetCounter()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double(li.QuadPart - CounterStart) / PCFreq;
}


myGraph::myGraph(char * filePath)
{
	szczyt = 0;
	tmpSzczyt = 0;
	std::fstream file;
	file.open(filePath, std::fstream::in);
	if (!file.is_open())
	{
		std::cout << "Error occured while opening file.\nCheck given file path.\n";
	}
	file >> this->size;
	matrix = new int *[this->size];
	for (int i = 0; i < size; i++)
	{
		matrix[i] = new int[this->size]; //utworzenie macierzy dynamicznie
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			char * tmp = new char;
			file >> tmp;
			//cout << "Matrix[" << i << "][" << j << "] =" << atoi(tmp) << " " << *tmp << endl;
			matrix[i][j] = (int) atoi(tmp); // wczytane dane z pliku konwertowane do macierzy
			//cout << "MatrixTRUE[" << i << "][" << j << "] =" << matrix[i][j]<< endl;
		}
	}

	file.close();
}


myGraph::~myGraph()
{
	for (int i=0; i < this->size; i++)
	{
		delete[] this->matrix[i];
	}
	delete[] matrix;
}

void myGraph::TSP_bruteForceRecurence(int startVertexIndex, int currentVertexIndex, bool * visited, int *tmpPathWeight)
{
	tmpStos[tmpSzczyt++] = currentVertexIndex;
	if (tmpSzczyt < this->size)
	{
		visited[currentVertexIndex] = true; 
		for (int j = 0; j < size; j++)
		{
			if (visited[j]) continue;
			*tmpPathWeight += matrix[currentVertexIndex][j];
			TSP_bruteForceRecurence(startVertexIndex, j , visited,tmpPathWeight);
			*tmpPathWeight -= matrix[currentVertexIndex][j];
		}
		visited[currentVertexIndex]=false;
		tmpSzczyt--;		
		return;

	}
	else
	{
		*tmpPathWeight += matrix[currentVertexIndex][startVertexIndex];
		if (*tmpPathWeight < this->shortestPathWeight)
		{
			this->shortestPathWeight = *tmpPathWeight;
			for (int i=0; i<tmpSzczyt; i++)
			{
				Stos[i] = tmpStos[i];
			}
			szczyt = tmpSzczyt;
		}
		*tmpPathWeight -= matrix[currentVertexIndex][startVertexIndex];
	}
	tmpSzczyt--;
	return;
}

void myGraph::BFTest(int reps, int startVertexIndex)
{
	double aggregateTime=0.0;
	for (int i = 0; i < reps; i++)
	{
		myStack *tmpStack = new myStack;
		int * tmpPathWeight = new int;
		*tmpPathWeight = 0;
		this->shortestPathWeight = INT_MAX;
		bool *visited = new bool[this->size];
		for (int i = 0; i < this->size; i++)
		{
			visited[i] = false;
		}
		double time;
		StartCounter();
		TSP_bruteForceRecurence(startVertexIndex, startVertexIndex, visited, tmpPathWeight);
		time = GetCounter();
		aggregateTime += time; 
		cout << i << " : " << time << " ms \tAggregated time: " << aggregateTime << "ms"<< endl;
	}
	cout << "\n\nFinal time for " << reps << " repetitions for this graph was : " << aggregateTime << "ms"<< endl;
	cout << "Average time for " << reps << " repetitions for this graph was : " << aggregateTime/reps << "ms" << endl;
}
void myGraph::TSP_bruteForce(int startVertexIndex)
{
	int * tmpPathWeight = new int;
	*tmpPathWeight = 0; 
	this->shortestPathWeight = INT_MAX;
	bool *visited = new bool[this->size];
	for (int i = 0; i < this->size; i++)
	{
		visited[i] = false; 
	}
	double time;
	StartCounter();
	TSP_bruteForceRecurence(startVertexIndex, startVertexIndex, visited, tmpPathWeight);
	time = GetCounter();
	if (this->shortestPathWeight == INT_MAX)
	{
		cout << "Shortes Hamilton path hasn't been found" << endl;
		getchar();
		delete[]visited;
		return; 
	}
	cout << "Shortes Hamilton path's weight is: " << this->shortestPathWeight << endl;
	cout << "Found in: " << time << " ms" << endl;
	cout << "Founded path's order is as following: " << endl;
	for (int i = size -1 ; i > 0  ; i--)
	{
		cout << "Vertex[" << i << "] : ";
		cout << Stos[i] << endl;
	}
	cout << "Vertex[0] : " << startVertexIndex <<  endl;
	getchar();
	delete []visited;
	return; 
}

void myGraph::display()
{
	cout << "Graph has: " << this->size << " vertices.\nCosts of travelling from vertex A to B are as following: \n  " ;
	for (int i = 0; i < this->size; i++)
	{
		cout << "  " << i;
	}
	cout << endl;
	for (int i = 0; i < this->size; i++)
	{
		cout << "---";
	}
	cout << endl; 
	for (int i = 0; i < this->size; i++)
	{
		for (int j = 0; j < this->size; j++)
		{
			if (j == 0) cout << i << "| ";
			cout << this->matrix[i][j] << " ";
		}
		cout << endl;
	}
}

int myGraph::getSize()
{
	return this->size;
}

int myGraph::getShortestPathWeight()
{
	return this->shortestPathWeight;
}

int myGraph::pathLength(vector<int> vector)
{
	int result = 0;
	int tmp = 0; 
	for (int i = 1; i < this->size; i++) //-1 bo dla ostatniego dadawane jest recznie
	{
		result += matrix[tmp][vector[i]];
		tmp = vector[i];
	}
	result += matrix[tmp][0];
	return result;
}

void myGraph::swapVertex() 
{
	int vertex1 = rand() % (this->size - 1)+1;
	int vertex2 = rand() % (this->size - 1)+1;
	while (vertex1 == vertex2)
	{
		vertex2 = rand() % (this->size - 1)+1;
	}
	int tmp = bestPath[vertex1];
	tmpPath = bestPath;
	tmpPath[vertex1] = tmpPath[vertex2];
	tmpPath[vertex2] = tmp;
}

void myGraph::TSP_SimulatedAnnealing(double a, double b, double c) 
{
	this->Temperature = a; 
	this->minTemperature = b;
	this->coolingRate = c;
	uniform_real_distribution<double> distribution(0.0, 1.0);
	default_random_engine generator;
	double stalaEulera = 2.718281828459;
	srand((unsigned int)time(NULL));
	for (int i = 0; i < this->size; i++) //inicjowanie poczatkowej sciezki
	{
		bestPath.push_back(i);
	}
	tmpPath = bestPath;
	shortestPathWeight = pathLength(tmpPath);
	tmpShortestPathWeight = shortestPathWeight;
	while (Temperature > minTemperature) 
	{
		swapVertex();
		tmpShortestPathWeight = pathLength(tmpPath);
		if (tmpShortestPathWeight < shortestPathWeight) 
		{
			shortestPathWeight = tmpShortestPathWeight;
			bestPath = tmpPath;
		}
		else if (pow(stalaEulera,(shortestPathWeight - tmpShortestPathWeight)/Temperature) > distribution(generator))
		{
			shortestPathWeight = tmpShortestPathWeight;
			bestPath = tmpPath;
		}
		Temperature *= coolingRate;
	}
}

void myGraph::SA_Test(int reps)
{
	double aggregateTime = 0.0;
	int shortest=2000000000, aggregatePath=0;
	for (int i = 0; i < reps; i++)
	{
		double time;
		StartCounter();
		this->TSP_SimulatedAnnealing((double)1000000, (double)0.000001, (double) 0.999999);
		time = GetCounter();
		aggregateTime += time;
		cout << i << " : " << time << " ms Result: "<< this->shortestPathWeight<<"\t\tAggregated time: " << aggregateTime << "ms" << endl;
		if (this->shortestPathWeight < shortest) shortest = this->shortestPathWeight;
		aggregatePath += this->shortestPathWeight;
	}
	cout << "\n\nFinal time for " << reps << " repetitions for this graph was : " << aggregateTime << "ms" << endl;
	cout << "Average time for " << reps << " repetitions for this graph was : " << aggregateTime / reps << "ms" << endl;
	cout << "Shortest founded path: " << shortest << "\nAverage % error from shortest founded path: " << (double)((double)((double)(aggregatePath / reps) / shortest))*100<< "%" << endl;
}