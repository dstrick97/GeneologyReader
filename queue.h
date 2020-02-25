/***********************************************************************
* Header:
*    Container
* Summary:
*    This class contains the notion of a container: a bucket to hold
*    data for the user. This is just a starting-point for more advanced
*    constainers such as the vector, set, stack, queue, deque, and map
*    which we will build later this semester.
*
*    This will contain the class definition of:
*        Container         : A class that holds stuff
*        ContainerIterator : An interator through Container
* Author
*    Br. Helfrich
************************************************************************/

#ifndef QUEUE_H
#define QUEUE_H

#include <cassert>
#include <iostream>


/************************************************
 * Queue
 * A class that holds stuff
 ***********************************************/
template <class T>
class Queue
{
public:
   // default constructor : empty and kinda useless
   Queue() : numItems(0), cap(0), data(NULL), frontP(0), backP(0) {}

   // copy constructor : copy it
   Queue(const Queue & rhs) throw (const char *);
   
   // non-default constructor : pre-allocate
   Queue(int capacity) throw (const char *);
   
   // destructor : free everything
   ~Queue()        { if (cap) delete [] data; }
   
   // is the container currently empty
   bool empty() const  { return numItems == 0;         }

   // remove all the items from the container
   void clear()        { numItems = 0;                 }

   // how many items are currently in the container?
   int size() const    { return numItems;              }

   // return size of Queue
   int capacity()       { return cap;                   }

   // overloads = operator
   Queue <T> & operator = (const Queue <T> & rhs);

   // returns const value at front of Queue
   T & front();

   // returns value at back of Queue
    T & back();

   //pushes new value onto top of Queue
   void push(T t);
   
   // removes top item on Queue
   void pop();

   // re-allocates queue to a larger size if neccessary
   void realloc();

   

   

private:
   T * data;          // dynamically allocated array of T
   int numItems;      // how many items are currently in the Container?
   int cap;           // how many items can I put on the Container before full?
   int frontP;         // tracks position of front pointer
   int backP;          // tracks position of back pointer
};

/**************************************************
 * realloc
 * transferes data from one Queue to another of
 * greater capactiy
 *************************************************/
template <class T>
void Queue <T> :: realloc()
{
   if(cap == 0)
   {
      cap = 1;
      data = new T[cap];
   }

   else
   {
      T* newData = new T[cap * 2];
      int j = frontP;
      for (int i = 0; i < numItems; i++, j = (j + 1) % cap)
      {
         newData[i] = data[j];
      }

      delete [] data;
      data = newData;
      frontP = 0;
      backP = numItems;
      cap *= 2;
   }
}

/**************************************************
 * pop
 * removes front value and decrements Queue
 *************************************************/
template <class T>
void Queue <T> :: pop()
{
	if (numItems == 0)
		throw "ERROR: attempting to pop from an empty queue";
	else
	{
      frontP = (frontP + 1) % cap;
	  numItems--;

	}
}


/**************************************************
 * Push
 * adds new value and increases Queue
 *************************************************/
template <class T>
void Queue <T> :: push(T t)
{
   if(numItems == cap)
   {
          realloc();      
   }

   data[backP] = t;
   backP = (backP + 1) % cap;
   numItems++;
   
}


/**************************************************
 * front
 * const returns the value at front of Queue
 *************************************************/
template <class T>
T & Queue <T> :: front()
{	
	if(numItems != 0)
	  return data[frontP % cap];
	
	else
	{
		throw "ERROR: attempting to access an item in an empty queue";
	}

}

/**************************************************
 * back
 * returns value at back of Queue
 *************************************************/
template <class T>
T & Queue <T> :: back()
{
   if(numItems != 0)
   return data[((backP - 1) + cap) % cap];
   
   else
      throw "ERROR: attempting to access an item in an empty queue";}


/**************************************************
 * Queue Operator =
 * overload "="
 *************************************************/
template <class T>
Queue <T> & Queue <T> :: operator = (const Queue <T> & rhs)
{
   // attempt to allocate
   try
   {
      data = new T[rhs.numItems];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a new buffer for Queue";
   }

assert(rhs.numItems >= 0 && rhs.numItems <= rhs.cap);
   cap = rhs.numItems;
   numItems = rhs.numItems;

   // copy the items over one at a time using the assignment operator
   int j = rhs.frontP;
      for (int i = 0; i < numItems; i++, j = (j + 1) % cap)
      {
         data[i] = rhs.data[j];
      }
      frontP = 0;
      backP = numItems;
}


/*******************************************
 * Queue :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Queue <T> :: Queue(const Queue <T> & rhs) throw (const char *)
{
   assert(rhs.cap >= 0);
      
   // do nothing if there is nothing to do
   if (rhs.cap == 0)
   {
      cap = 0;
      numItems = 0;
      data = NULL;
      frontP = 0;
      backP = 0;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[rhs.numItems];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
   
   // copy over the capacity and size
   assert(rhs.numItems >= 0 && rhs.numItems <= rhs.cap);
   cap = rhs.numItems;
   numItems = rhs.numItems;

   // copy the items over one at a time using the assignment operator
   int j = rhs.frontP;
      for (int i = 0; i < numItems; i++, j = (j + 1) % rhs.cap)
      {
         data[i] = rhs.data[j];
      }
      frontP = 0;
      backP = numItems;
}

/**********************************************
 * Queue : NON-DEFAULT CONSTRUCTOR
 * Preallocate the Queue to "capacity"
 **********************************************/
template <class T>
Queue <T> :: Queue(int capacity) throw (const char *)
{
   assert(capacity >= 0);
   
   // do nothing if there is nothing to do
   if (capacity == 0)
   {
      this->cap = this->numItems = 0;
      this->data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[capacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }

      
   // copy over the stuff
   this->cap = capacity;
   this->numItems = 0;

   // initialize the container by calling the default constructor
   for (int i = 0; i < capacity; i++)
      data[i] = T();
}

#endif // QUEUE_H

