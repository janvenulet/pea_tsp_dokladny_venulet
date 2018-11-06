#pragma once


struct myVertex
{
	int index;
	myVertex *next;
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