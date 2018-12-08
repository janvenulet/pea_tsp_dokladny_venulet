#include <iostream>
#include "myGraph.h"
#include <Windows.h>
using namespace std;

const char * welcome = "Welcome \nto program solving traveling salesman problem(TSP).\nDeveloped by: Jan Maksymilian Venulet 235542\nOctober 2018\n\n\n";
const char * menu = "1. Read data from constant file\n2. Read data from given file(not supported yet)\n3. Display graph\n4. Use brute force to find shortest path\n5. Use simulated annealing algorithm to find shortest path\n6. Run tests for BF\n7. Run tests for SA\n0. Exit program\nEnter your choice : ";
const char * filePath = "C:\\Users\\Jan\\source\\repos\\pea_tsp_dokladny_venulet\\data120.txt";




void runMenu(void)
{
	myGraph * graph = new myGraph((char*)filePath);
	bool exit = true;
	system("cls");
	do
	{
		system("cls");
		cout << welcome << menu;
		int chosen;
		cin >> chosen;
		switch (chosen)
		{
			case 1:
				delete graph;
				graph = new myGraph((char*)filePath);
				break;
			case 2:
				cout << "Enter file name you want to open file from in project file: ";
				//cin >> tmpFileName;
				//tmpFileName = new char(chosen);
				//graph = new myGraph("C:\\Users\\Jan\\source\\repos\\pea_tsp_dokladny_venulet\\" + *tmpFileName);
				break;
			case 3:
				system("cls");
				if (graph != nullptr) graph->display();
				else cout << "\nGraph hasn't been loaded to program yet.\n";
				system("pause");
				break;
			case 4:
				system("cls");
				cout << "What vertex you want to start from: ";
				int startVertex; 
				cin >> startVertex;
				if (startVertex >= graph->getSize() || startVertex < 0)
				{
					cout << "You entered wrong number!!!Try again!!!" << endl;
					system("pause");
					break;
				}
				graph->TSP_bruteForce(startVertex);
				//if (graph != nullptr) cout << "FTP: " << graph->getShortestPathWeight() << endl;
				system("pause");
				break;
			case 5:
				if (graph != nullptr)
				{
					cout << "Use default settings (10000, 0.00001, 0.99999)? [1-yes] : " << endl;
					char g= fgetc(stdin);
					g= getchar();
					if (g == '1')
					{
						graph->TSP_SimulatedAnnealing((double)10000, (double)0.00001, (double) 0.9999);
						cout << "\nResult: " << graph->getShortestPathWeight() << endl;
						system("pause");
						break;
					}
					else 
					{
						double temperatureMax, temperatureMin, coolingRate;
						cout << "Start temperature: ";
						cin >> temperatureMax;
						cout << "Minimal temperature: ";
						cin >> temperatureMin;
						cout << "Cooling rate [0,1) (use dot '.') : ";
						cin >> coolingRate;
						graph->TSP_SimulatedAnnealing(temperatureMax, temperatureMin, coolingRate);
						system("pause");
						break;
					}
				}
			case 6: 
				system("cls");
				if (graph != nullptr) 
				{
					int rep; 
					cout << "Enter number of times brute force algorithm is supposed to be run: ";
					cin >> rep; 
					graph->BFTest(rep, 0);
					system("pause");// 0 jest wierzcholkiem dla ktorego test rozpoczyna sie
					break;
				}
				else cout << "\nGraph hasn't been loaded to program yet.\n";
				system("pause");
				break;
			case 7:
				system("cls");
				if (graph != nullptr)
				{
					int rep;
					cout << "Enter number of times brute force algorithm is supposed to be run: "; 
					cin >> rep;
					graph->SA_Test(rep);
				}
				else cout << "\nGraph hasn't been loaded to program yet.\n";
				system("pause");
				break;
			case 0: 
			{	
				exit = false;
				break;
			}
			default:
				cout << "You've entered wrong numer\nTRY AGAIN!!!\n\n\n";
				system("pause");
				break;
		}
	} while (exit);
	delete graph;
	cout << "Goodbye :)\n";
	system("pause");
	return;
}


int main(void)
{
	runMenu();
	return 0; 
}
