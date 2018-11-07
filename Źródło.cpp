#include <iostream>
#include "myGraph.h"
#include <Windows.h>
using namespace std;

const char * welcome = "Welcome \nto program solving traveling salesman problem(TSP).\nDeveloped by: Jan Maksymilian Venulet 235542\nOctober 2018\n\n\n";
const char * menu = "1. Read data from constant file\n2. Read data from given file(not supported yet)\n3. Use brute force to find shortest path\n4. Display graph\n5. Run tests\n0. Exit program\nEnter your choice : ";
const char * filePath = "C:\\Users\\Jan\\source\\repos\\pea_tsp_dokladny_venulet\\dane13.txt";




void runMenu(void)
{
	myGraph * graph = new myGraph((char*)filePath);
	//char tmpFileName[51] = "231";
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
				//cout << "Enter file name you want to open file from in project file: ";
				//cin >> tmpFileName;
				//tmpFileName = new char(chosen);
				//graph = new myGraph("C:\\Users\\Jan\\source\\repos\\pea_tsp_dokladny_venulet\\" + *tmpFileName);
				break;
			case 3:
				system("cls");
				graph->TSP_bruteForce(0);
				//if (graph != nullptr) cout << "FTP: " << graph->getShortestPathWeight() << endl;
				system("pause");
				break;
			case 4:
				system("cls");
				if (graph != nullptr) graph->display();
				else cout << "\nGraph hasn't been loaded to program yet.\n"; 
				system("pause");
				break;
			case 5: 
				system("cls");
				if (graph != nullptr) 
				{
					int rep; 
					cout << "Enter number of times brute force algorithm is supposed to be run: ";
					cin >> rep; 
					graph->BFTest(rep, 0); // 0 jest wierzcholkiem dla ktorego test rozpoczyna sie
						
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
		//system("cls");
	} while (exit);
	delete graph;
	cout << "Goodbye :)\n";
	system("pause");
	return;
}


int main(void)
{
	runMenu();
	return 1; 
}
