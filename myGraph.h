#include"myStack.h"

class myGraph
{
	private:
		int size;
		int **matrix;
		 myStack shortestPath; 
		 myStack testFinal;
		int shortestPathWeight;
	
public:
		myGraph(char *);

		~myGraph();

		void TSP_bruteForce(int);
		void TSP_bruteForceRecurence(int, int, myStack *, bool *, int *);
		int getShortestPathWeight();
		int getSize();
		void display();
		void BFTest(int,int);
};