/*#include "bnode.h"
#include <iostream>
using namespace std;

template<class T>
void BinaryNode <T>::level()
{
	ostream out;
	
	const int MAX = 100;
  BinaryNode *queue[MAX];
  BinaryNode *temp;
  int front = 0;
  int back = 0;

  queue[back++] = this;
  int savedBack = 1;

  while (front != back)
  {
    temp = queue[front];
	if (front == savedBack)
	{
		cout << "Parents";
		savedBack = back;
	}
    front = (front + 1) % MAX;
    if (temp != NULL)
    {
      // visit
      cout.width(4);
      out << temp->data << " ";
      // end Visit        
      queue[back] = temp->left;
      back = (back + 1) % MAX;
      queue[back] = temp->right;
      back = (back + 1) % MAX;

    }
  }
}


/*
make new variable saved back initialized to 1
when front gets to saved back, its a new generation.
when front gets saved back, saved back gets set to back

*/

/*
make class for nodes. Should hold first name, last name, birthday
??needs to have pointers to parents, and child??
have a ??string?? that has data index for family relations

take linked list and build into tree??

or have list with pointers to mother and father. search through list, assign pointers to mother and father within list

*/