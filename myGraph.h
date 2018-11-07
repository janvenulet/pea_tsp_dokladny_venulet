#include"myStack.h"

class myGraph
{
	private:
		int size;
		int **matrix;
		 //myStack shortestPath; 
		int szczyt; 
		int tmpSzczyt;
		int Stos[100];
		int tmpStos[100];
		int *shortestPath;
		myStack testFinal;
		int shortestPathWeight;
	
public:
		myGraph(char *);

		~myGraph();

		void TSP_bruteForce(int);
		void TSP_bruteForceRecurence(int, int, bool *, int *);
		int getShortestPathWeight();
		int getSize();
		void display();
		void BFTest(int,int);
};