#include"myStack.h"
#include <vector>
#include <time.h>
#include<fstream>
#include <random>
#include<iostream>

class myGraph
{
	private:
		int size;
		int **matrix;
		int szczyt; 
		int tmpSzczyt;
		int Stos[100];
		int tmpStos[100];
		int *shortestPath;
		myStack testFinal;
		int shortestPathWeight;
		int tmpShortestPathWeight;
		std::vector <int> bestPath;
		std::vector <int> tmpPath;
		double Temperature;
		double minTemperature;
		double coolingRate;
		void swapVertex();
public:
		myGraph(char *);
		~myGraph();
		void TSP_bruteForce(int);
		void TSP_bruteForceRecurence(int, int, bool *, int *);
		void TSP_SimulatedAnnealing(double, double, double);
		int getShortestPathWeight();
		int getSize();
		void display();
		void BFTest(int,int);
		int pathLength(std::vector<int> vector);
		void SA_Test(int);
};