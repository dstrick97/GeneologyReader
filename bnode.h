#ifndef BNODE_H
#define BNODE_H

#include <iostream> 
#include <cassert>
using namespace std;

/*****************************************************************
 * BINARY NODE
 * A single node in a binary tree.  Note that the node does not know
 * anything about the properties of the tree so no validation can be done.
 *****************************************************************/
template <class T>
class BinaryNode
{
public:
   BinaryNode() : data(T()), pParent(NULL), pRight(NULL), pLeft(NULL) {}
   BinaryNode(const T & t): data(t), pParent(NULL), pRight(NULL), pLeft(NULL) {}


   // return size (i.e. number of nodes in tree)
   int size() const
   {
            return 1 +
               (pLeft== NULL? 0 : pLeft->size()) +
               (pRight == NULL ? 0 : pRight->size());
   }
   
   // add a node to the left/right
   void addLeft (BinaryNode <T> * pNode);
   void addRight(BinaryNode <T> * pNode);

   // create a node and add it to the left/right
   void addLeft (const T & t) throw (const char *);
   void addRight(const T & t) throw (const char *);

   void level();

   
   // since no validation is done, everything is public
   BinaryNode <T> * pLeft;
   BinaryNode <T> * pRight;
   BinaryNode <T> * pParent;
   T data;
};


//LEVEL()
template<class T>
void BinaryNode <T>::level()
{

	const int MAX = 100;
	BinaryNode* queue[MAX];
	BinaryNode* temp;
	int front = 0;
	int back = 0;
	int level = 1;
	int check = 1;

	queue[back++] = this;
	int savedBack = 1;

	while (front != back)
	{
		temp = queue[front];
		if (front == savedBack)
		{
			if (level == 1)
				cout << "Parents:\n ";
			else if (level == 2)
				cout << "Grandparents:\n ";
			else if (level == 3)
				cout << "Great Grandparents:\n ";
			else if (level == 4)
				cout << "2nd Great Grandparents:\n ";
			else if (level == 5)
				cout << "3rd Great Grandparents:\n ";
			else if (level == 6)
				cout << "4th Great Grandparents:\n ";
			else if (level == 7)
				cout << "5th Great Grandparents:\n ";
			
			savedBack = back;
			level++;
		}
		front = (front + 1) % MAX;
		if (temp != NULL)
		{
			// visit
			if (check == 1)
			{
				cout << temp->data;
				check++;
			}
			else
			{
				cout << "       ";
				cout << temp->data;
			}
			// end Visit        
			queue[back] = temp->pLeft;
			back = (back + 1) % MAX;
			queue[back] = temp->pRight;
			back = (back + 1) % MAX;

		}
	}
}





/*****************************************************************
 * Delete Binary Node
 * deletes the appropriate node
 *****************************************************************/
template <class T>
void deleteBinaryTree(BinaryNode <T> * & pNode)
{
	if(pNode == NULL)
		return;
	deleteBinaryTree(pNode->pLeft);
	deleteBinaryTree(pNode->pRight);
	delete pNode;
}

/*****************************************************************
* << 
* overloads the << operator
 *****************************************************************/
template <class T>
std::ostream & operator << (std::ostream & out, BinaryNode <T>* rhs)
{
	if(rhs != 0)
	{
		out << rhs->pLeft;
		out << rhs->data << " ";
		out << rhs->pRight;
	}
	return out;
}

/*****************************************************************
 * addLeft
 * adds a given node to the left pointer
 *****************************************************************/
template <class T>
void BinaryNode <T> :: addLeft(BinaryNode <T> * pNode)
{
	this->pLeft = pNode;
	if(pNode != NULL)
		pNode->pParent = this;
}

/*****************************************************************
 * addRight
 * adds a given node to the right pointer
 *****************************************************************/
template <class T>
void BinaryNode <T> :: addRight(BinaryNode <T> * pNode)
{
	this->pRight = pNode;
	if(pNode != NULL)
		pNode->pParent = this;
}

/*****************************************************************
 * addLeft
 * creates a node with a given value on the left pointer
 *****************************************************************/
template <class T>
void BinaryNode <T> :: addLeft(const T & t) throw (const char*)
{
	try
	{
		BinaryNode <T> *newNode = new BinaryNode <T>(t);
		this->pLeft = newNode;
		newNode->pParent = this;
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: unable to allocate a node";
	}
}

/*****************************************************************
 * addRight
 * creates a node with a given value on the right pointer
 *****************************************************************/
template <class T>
void BinaryNode <T> :: addRight(const T & t) throw (const char*)
{
	try
	{
		BinaryNode <T> *newNode = new BinaryNode <T>(t);
		this->pRight = newNode;
		newNode->pParent = this;
	}

		catch (std::bad_alloc)
	{
		throw "ERROR: unable to allocate a node";
	}

}


#endif // BNODE_H
