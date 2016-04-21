#include <iostream>
#include "BQUEUE.h"

using namespace std;

//*************************************************************************************
//Precondition: The default constructor has not been called.
//Postcondition: The default constructor has been called, and the values set to their initials.
//Description:  This constructor will initialize the state of the class. 
//*************************************************************************************
BQUEUE::BQUEUE()
{
	cout << "The default constructor has been called." << endl;
	front = 0; 
}

//*************************************************************************************
//Precondition: The copy constructor has not been called.
//Postcondition: The copy constructor has been called, and the values of the current object
//				 to another, newly created object. 
//Description:  This constructor will pass in values to the new queue via a while loop.
//*************************************************************************************
BQUEUE::BQUEUE(const BQUEUE & ORG)
{
	//int counter = 0;
	//bqnode *temp = ORG.front;
	//bqnode *temp2 = ORG.front;
	///*while(temp != NULL)
	//{
	//	counter++;
	//	temp=temp->next;
	//}*/

	//for(int i = 0; i < counter; i++)
	//{
	//	Enqueue(temp2->time);
	//	temp2 = temp2->next;
	//}

	if (!ORG.front) return;

    front = new bqnode;
	front->time = ORG.front->time;
    front->next = front->prev = front;

	const bqnode *ptr1 = ORG.front->next;

	while (ptr1 != ORG.front)
    {
        bqnode *pnew = new bqnode;
		pnew->time = ptr1->time;
        pnew->next = front;
        pnew->prev = front->prev;
        front->prev->next = pnew;
        front->prev = pnew;
        ptr1 = ptr1->next;
    }
}
//*************************************************************************************
//Precondition: The destructor has not been called.
//Postcondition: The destructor has been called, and the allocated memory has been deleted,
//				 and the queue has been emptied. 
//Description:  This destructor actually does very little, it merely calls a function named
//				"Dequeue" to handle the deletion for it. This is because a circular queue
//				can only be accessed in one spot, and deleting the front will not delete
//				the whole list, merely access to it.
//*************************************************************************************
BQUEUE::~BQUEUE()
{
	cout<<"Destructor invoked"<<endl;
	if (front != 0)
	{
		Dequeue();
	}
}

//*************************************************************************************
//Precondition: The function has not been called to assist in deletion.
//Postcondition: The function has been called, and the requested item has been deleted
//				 from the front. 
//Description:  This function does the destructor's job by traversing the queue and deleting
//				each node from the front every time it's called, while setting front to a new
//				value each time the function is called.
//*************************************************************************************
void BQUEUE::Dequeue()
{
	if(front == 0) //When debugging, this case was never utilized by the program when I tried to do a stepover. Thus the error.
	{
		cout<<"There is nothing in your queue."<<endl;
	}
	if (front->next == front) 
	{ 
		 delete front; front = 0; 
	}
	if (front->next == front->prev) //This case is stepped into twice by the program, thus the error. 
	{
		bqnode *p = new bqnode;
		p = front->prev;
		delete front;
		front = p;
	}
	else
	{
		/*bqnode *p = front;
		p->next =  front->next;
		p->prev = front->prev;
		front = front->next;
		delete p;*/
		bqnode *p = front;
		front = front->next;
		front->prev = p->prev;
		p->prev->next = front;
		delete p;
	}
}

//*************************************************************************************
//Precondition: The function has not been called to assist with insertion.
//Postcondition: The function has been called, and the item passed in was added to the 
//				 the back of the queue. 
//Description:  This function inserts a number to the back of the queue each time it's called.
//*************************************************************************************
void BQUEUE::Enqueue(int num)
{

	if(front == 0)
	{
		front = new bqnode;
		front->time = num;
		front->next = front;
		front->prev = front;
	}
	else
	{
		/*bqnode *p = new bqnode;
		p->time = num;
		p->prev = front->prev;
		p->next = front->prev->next;
		front->prev->next = p;
		front->prev = p;
		front = p;*/
		bqnode *p = new bqnode;
		p->time = num;
        p->next = front;
        p->prev = front->prev;
        front->prev->next = p;
        front->prev = p;
	}
}

//*************************************************************************************
//Precondition: The function has not been called to print the queue.
//Postcondition: The function has been called, and the queue has been output to the console.
//Description:  This function merely prints the queue, and has a couple of redundancies to 
//				make sure everything prints properly (temp->next->next)
//*************************************************************************************
void BQUEUE::Print()
{
	bqnode *temp = front;
	int i = 0;

	if(front == 0)
	{
		cout<<"The queue is empty."<<endl;
	}
	else
	{
		if(front == front->next)
		{
			cout<<"One item is in the list, and it is: " << temp->time << endl;

		}
		else
		{
			while(temp != front->prev)
			{
				
				cout<<"Item number "<< i+1 <<" is " << temp->time << endl;
				i++;
				if(temp == front->prev->prev) //This is where the program breaks. 
				{
					cout<<"Item number "<< i+1 <<" is " << temp->next->time << endl;
				}//The above line makes sure the last line gets output before reaching the terminating condition.
				temp = temp->next;
				
			}
		}
	}
}
