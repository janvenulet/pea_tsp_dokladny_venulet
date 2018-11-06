#include"myStack.h"
#include<iostream>


myStack::myStack()
{
	head = nullptr;
	size = 0;
}

myStack::~myStack()
{
	//while (head != nullptr)
	
		delete this->head;
	
}

int myStack::pop(void)
{
	if (this->head == nullptr)
	{
		std::cout << "Stack is empty";
		return 0; 
	}
	else
	{
		int result = head->index;  //a moze zrobic **
		head = head->next;
		size--;
		return result;
	}
}

void myStack:: push(int a)
{
	if (head == nullptr)
	{
		myVertex *tmp = new myVertex;
		tmp->index = a;
		tmp->next = nullptr; 
		head = tmp;
		size++;
	}
	else
	{
		myVertex * tmp = new myVertex;
		tmp->index = a; 
		tmp->next=head; 
		head = tmp;
		size++;
	}
}

int myStack::showStackIndex(int a)
{
	myVertex * indexedVertex = this->head; 
	for (int i = 0; i < a; i++)
	{
		indexedVertex = indexedVertex->next;
	}
	if (indexedVertex != nullptr)
	return indexedVertex->index;
}

int myStack::getSize()
{
	return this->size;
}