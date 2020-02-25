/***********************************************************************
 * Header:
 *    LIST.H
 * Summary:
 *    creates the list data class
 * Author
 *    Daniel Strickland
 ************************************************************************/
#include "node.h"
#ifndef LIST_H
#define LIST_H


// forward declaration for ListIterator
template <class T>
class List;

template <class T>
class ListIterator;

/************************************************
 * List
 * class declaration
 ***********************************************/
template <class T>
class List
{
public:
	Node <T> *head;
	Node <T> *tail;
	int numitems;

	List() : head(NULL), tail(NULL), numitems(0){}
	List(const List <T> &copy);
	~List();
	List<T> & operator = (List<T> rhs);
	bool empty();
	void clear();
	int size() {return numitems;}
	void push_back(T t);
	void push_front(T t);
	T & front();
	T & back();

	ListIterator <T> begin();
	ListIterator <T> rbegin();
	ListIterator <T> end();
	ListIterator <T> rend();

	ListIterator <T> insert(ListIterator<T> &it, const T & item) throw(const char*);
	void remove(ListIterator <T> &it);

};

/************************************************
 * List()
 * copy constructor for List()
 ***********************************************/
template <class T>
List <T> :: List(const List<T> & rhs)
{
	numitems = rhs.numitems;
	head = copy(rhs.head);
	if(rhs.tail != NULL)
	{
		tail = find(head, rhs.tail->data);
	}
} 

/************************************************
 * ~List()
 * destructor for List()
 ***********************************************/
template <class T>
List<T> :: ~List()
{
	while (this->head != NULL)
	{
		Node<T> *temp = this->head->pNext;
		delete this->head;
		this->head = temp;
	}
	this->head = NULL;
	this->tail = NULL;
	this->numitems = 0;
}

/************************************************
 * = operator
 * overloads = operator
 ***********************************************/
template <class T>
List<T> & List<T> :: operator = (List<T> rhs)
{
	Node <T>* newNode;	
	this->numitems = rhs.numitems;
	if(rhs.head != NULL)
	{
		this->head = new Node<T>(rhs.head->data);
		this->tail = this->head; 
		while (rhs.head->pNext != NULL)
		{
			rhs.head = rhs.head->pNext;
			newNode = new Node<T>(rhs.head->data);
			this->tail->pNext = newNode;
			newNode->pPrev = this->tail;
			this->tail = newNode;
		}
	return *this;
		
	}

	else 
		return *this;
}

/************************************************
 * empty()
 * checks if list is empty
 ***********************************************/
template <class T>
bool List <T> :: empty()
{
	if(numitems != 0 && head != NULL)
		return false;
	else
		return true;
}

/************************************************
 * clear()
 * empties the list
 ***********************************************/
template <class T>
void List <T> :: clear()
{
	while (head != NULL)
	{
		Node <T> *temp = head->pNext;
		delete head;
		head = temp;
	}
	head = NULL;
	tail = NULL;
	numitems = 0;
}

/************************************************
 * size()
 * return number of nodes
 ***********************************************/
// template <class T>
// int size()
// {
// 	return numitems;
// }

/************************************************
 * push_back()
 * adds an item to the end of the list
 ***********************************************/
template <class T>
void List<T> :: push_back(T t)
{
	if (tail != NULL)
	{
		Node<T> *newNode = new Node<T>(t);
		this->tail->pNext = newNode;
		newNode ->pPrev = this->tail;
		this->tail = newNode;
		this->numitems += 1;
	}
	else
	{
		this->head = new Node<T>(t);
		this->tail = this->head;
		this->numitems = 1;
	}
}

/************************************************
 * push_front()
 * adds an item to the front of the list
 ***********************************************/
template <class T>
void List<T> :: push_front(T t)
{
	if (head != NULL)
	{
		Node<T> *newNode = new Node<T>(t);
		this->head->pPrev = newNode;
		newNode ->pNext = this->head;
		this->head = newNode;
		this->numitems += 1;
	}
	else
	{
		this->head = new Node<T>(t);
		this->tail = this->head;
		this->numitems = 1;
	}
}

/************************************************
 * front()
 * returns item in front of list
 ***********************************************/
template <class T>
T & List<T> :: front()
{
	if(this->head != NULL)
	{
		return this->head->data;
	}
	else
		throw "ERROR: unable to access data from an empty list";
}

/************************************************
 * back()
 * returns item from back of list
 ***********************************************/
template <class T>
T & List<T> :: back()
{
	if(this->tail != NULL)
	{
		return this->tail->data;
	}
	else
		throw "ERROR: unable to access data from an empty list";
}

/************************************************
 * begin()
 * returns iterator to first item in list
 ***********************************************/
template <class T>
ListIterator<T> List<T> :: begin()
{
	//return head;
	return ListIterator<T>(head);
}

/************************************************
 * rbegin()
 * returns iterator to last element in list
 ***********************************************/
template <class T>
ListIterator <T> List<T> :: rbegin()
{
	//return tail;
	return ListIterator<T>(tail);
}

/************************************************
 * end()
 * returns iterator to past the end element
 ***********************************************/
template <class T>
ListIterator <T> List<T> :: end()
{
	//return tail->pNext;
	return ListIterator<T>(NULL);
}

/************************************************
 * rend()
 * returns item from back of list
 ***********************************************/
template <class T>
ListIterator <T> List<T> :: rend()
{
	//return head->pPrev;
	return ListIterator<T>(NULL);
}

/************************************************
 * insert()
 * adds item to middle of list
 ***********************************************/
template <class T>
ListIterator <T> List<T> :: insert(ListIterator<T> &it, const T & item) throw(const char*)
{
	try
	{
		Node <T> * temp = new Node<T>(item);
		if(head == NULL)
		{
			head = temp;
			tail = temp;
		}

		else if (it.node == NULL)
		{
			tail->pNext = temp;
			temp ->pPrev = tail;
			tail = temp;
		}

		else
		{
			temp->pNext = it.node;
			temp->pPrev = it.node->pPrev;
			it.node->pPrev = temp;
			if(it.node == head)
				head = temp;
			else
				temp->pPrev->pNext = temp;

		}
		numitems++;
		return ListIterator<T>(temp);
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: unable to allocate a new node for a list";
	}
}

/************************************************
 * remove()
 * removes an item from the middle of the list
 ***********************************************/
template <class T>
void List<T> :: remove(ListIterator <T> &it)
{
		if(it.node == NULL)
		{
			std::cout << "ERROR: unable to remove from an invalid location in a list";
		}

		else if (it.node == head)
		{
			if (head == tail)
			{
				head = NULL;
				tail = NULL;
			}
			else
			{
				Node<T>* temp = head->pNext;
				temp->pPrev = NULL;
				head = temp;
			}
		}

		else if(it.node == tail)
		{
			Node <T> *temp = tail->pPrev;
			temp->pNext = NULL;
			tail = temp;
		}

		else
		{
			Node<T> *previous = it.node->pPrev;
			Node<T> *next = it.node->pNext;

			previous->pNext = next;
			next->pPrev = previous;
		}

		delete it.node;
		it.node = NULL;

		numitems--;


}


/**************************************************
 * LIST ITERATOR
 * An iterator through a list
 *************************************************/
template <class T>
class ListIterator
{
friend List<T>;


public:
	Node <T> *node;


	ListIterator() : node(NULL) {}

	ListIterator(Node<T> *input)
	{
		node = input;
	}

	//dereference operator
	T & operator * ()
	{
		return node->data;
	}

	bool operator != (const ListIterator & rhs) const
	{
		return rhs.node != this->node;
	}


	//incrememnt
	ListIterator <T> & operator ++ ()
	{
		node = this->node->pNext;
		return *this;
	}

	//decrement
	ListIterator <T> & operator -- ()
	{
		node = this->node->pPrev;
		return *this;
	}

};

#endif