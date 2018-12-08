#pragma once


class myVertex
{
public:
	int index;
	myVertex *next;

	myVertex()
	{
		//next = new myVertex;
	}
	~myVertex()
	{
		//delete next; 
	}
};


class myStack
{
	myVertex * head;
	int size;

public:
	myStack();
	~myStack();
	void push(int);
	int showStackIndex(int);
	int pop(void);
	int getSize();
};