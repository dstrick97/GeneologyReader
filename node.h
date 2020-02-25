/***********************************************************************
 * Header:
 *    NODE.H
 * Summary:
 *    creates the Node data class
 * Author
 *    Daniel Strickland
 ************************************************************************/
#ifndef NODE_H
#define NODE_H

/************************************************
 * Node
 * class declaration
 ***********************************************/
template <class T>
class Node
{
	public:
		T data;								//data in each node
		Node <T> * pNext;					//pointer to next node
		Node <T> * pPrev;
		Node() : data(T()), pNext(NULL), pPrev(NULL) {}	//creates empty node
		Node(T data);
};

/************************************************
 * Node()
 * default constructor for Node()
 ***********************************************/
template <class T>
Node <T> :: Node(T data) 
{
	this-> data = data;
	this-> pNext = NULL;
	this-> pPrev = NULL;
}

/************************************************
 * <<
 * overloads the << operator to display the
 * contents of a linked list
 ***********************************************/
template <class T>
std::ostream & operator << (std::ostream & out, Node <T>* rhs)
{
	
	while(rhs != NULL)
	{
		out << rhs->data;
		if(rhs->pNext != NULL)
		{
			out << ", ";
		}
		
		rhs = rhs->pNext;	
	}
	
	return out;
}

/************************************************
 * copy()
 * copies one linked list to another with the 
 * same data but different addresses
 ***********************************************/
template <class T>
Node <T>* copy(Node <T>* node)
{
	Node<T>* head;
	Node<T>* temp;
	Node <T>* newNode;	

	if(node != NULL)
	{
		head = new Node<T>(node->data);
		temp = head; 
		while (node->pNext != NULL)
		{
			node = node->pNext;
			newNode = new Node<T>(node->data);
			temp->pNext = newNode;
			newNode->pPrev = temp;
			temp = newNode;
		}

		return head;
	}

	else
	{
		return NULL;
	}
}

/************************************************
 * freeData()
 * deletes the contents of a linked list
 ***********************************************/
template <class T>
void freeData(Node <T> * & node)
{
	while (node != NULL)
	{
		Node <T> *temp = node->pNext;
		delete node;
		node = temp;
	}
}

/************************************************
 * find()
 * finds a value within the list
 ***********************************************/
template <class T>
Node <T>* find(Node<T>*n, const T & data)
{
	if(n == NULL)
		return NULL;

	if(n->data == data)
		return n;
	else
		return find(n->pNext, data);
}

/************************************************
 * insert()
 * inserts new node within list
 ***********************************************/
template <class T>
void insert(T data, Node <T>* &nextNode, bool front = false)
{
	Node<T>* newNode = new Node<T>;
	newNode->data = data;
	if(front || nextNode == NULL)
	{
		newNode->pNext = nextNode;
		nextNode = newNode;
	}

	else
	{
		newNode->pNext = nextNode->pNext;
		nextNode->pNext = newNode;
	}
}

/*
non-recursive find:
{
	while(n != NULL)
	{
		if(n->data == data)
			return n;
		n = n->pNext;

	}
	return NULL;
}
*/
#endif // NODE_H