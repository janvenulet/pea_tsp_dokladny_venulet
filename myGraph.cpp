#include"myGraph.h"
#include<fstream>
#include<iostream>

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
	//shortestPath = new myStack();
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

void myGraph::TSP_bruteForceRecurence(int startVertexIndex, int currentVertexIndex, myStack *tmpStack, bool * visited, int *tmpPathWeight)
{
	tmpStack->push(currentVertexIndex);
	if (tmpStack->getSize() != this->size)
	{
		visited[currentVertexIndex] = true; 
		for (int j = 0; j < size; j++)
		{
			if (visited[j]) continue;
			*tmpPathWeight += matrix[currentVertexIndex][j];
			TSP_bruteForceRecurence(startVertexIndex, j , tmpStack, visited,tmpPathWeight);
			*tmpPathWeight -= matrix[currentVertexIndex][j];
		}
		visited[currentVertexIndex]=false;
		tmpStack->pop();		
		return;

	}
	else
	{
		*tmpPathWeight += matrix[currentVertexIndex][startVertexIndex];
		if (*tmpPathWeight < this->shortestPathWeight)
		{
			this->shortestPathWeight = *tmpPathWeight;
			this->shortestPath = *tmpStack;
		}
		*tmpPathWeight -= matrix[currentVertexIndex][startVertexIndex];
	}
	tmpStack->pop();
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
		TSP_bruteForceRecurence(startVertexIndex, startVertexIndex, tmpStack, visited, tmpPathWeight);
		time = GetCounter();
		aggregateTime += time; 
		cout << i << " : " << time << " ms \tAggregated time: " << aggregateTime << "ms"<< endl;
	}
	cout << "\n\nFinal time for " << reps << " repetitions for this graph was : " << aggregateTime << "ms"<< endl;
	cout << "Average time for " << reps << " repetitions for this graph was : " << aggregateTime/reps << "ms" << endl;
}
void myGraph::TSP_bruteForce(int startVertexIndex)
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
	TSP_bruteForceRecurence(startVertexIndex, startVertexIndex, tmpStack, visited, tmpPathWeight);
	time = GetCounter();
	//cout << "\nHej:" << shortestPath.getSize() << endl;
	if (this->shortestPathWeight == INT_MAX)
	{
		cout << "Shortes Hamilton path hasn't been found" << endl;
		getchar();
		delete[]visited;
		delete tmpStack;
		return; 
	}
	cout << "Shortes Hamilton path's weight is: " << this->shortestPathWeight << endl;
	cout << "Found in: " << time << " ms" << endl;
	cout << "Founded path's order is as following: " << endl;
	/*
	myStack *testStack = new myStack();
	testStack->push(4);
	testStack->push(7);
	testStack->push(5);
	testStack->push(6);
	testStack->push(0);
	testStack->push(11);
	testStack->push(3);
	*/
	for (int i = shortestPath.getSize(); i > 0  ; i--)
	{
		cout << "Vertex[" << i << "] : ";
		cout << shortestPath.showStackIndex(i-1) << endl;
	}
	cout << "Vertex[0] : " << startVertexIndex <<  endl;
	getchar();
	delete tmpStack;
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
			//cout << "Matrix[" << i << "][" << j << "] =" << this->matrix[i][j] << endl;
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