// Eric Lowe and Rodolfo Hernandez
// list.cpp
//

#include <iostream>
#include "list.h"

template <class T>
ListNode<T>::ListNode(const T &d, ListNode<T> *n) : data(d), next(n)
{
}  // ListNode()

template <class T>
List<T>::List(const T &nF) : head(NULL), size(0), notFound(nF)
{
} // List()


template <class T>
List<T>::List(const List<T> &rhs) : head(NULL), notFound(rhs.notFound)
{
  ListNode <T> *ptr = NULL, *ptr2;
  
  for(ptr2 = rhs.head; ptr2; ptr2 = ptr2->next)
    if(!ptr)
      ptr = head = new ListNode<T>(ptr2->data, NULL);
    else
      ptr = ptr->next = new ListNode<T>(ptr2->data, NULL);
  
  size = rhs.size;
} // List()



template <class T>
List<T>::~List()
{
    for(ListNode <T> *ptr = head; ptr != NULL; ptr = head)
  {
    head = ptr->next;
    delete ptr;
  }
} // ~List()

template <class T>
const T& List<T>::find(const T &key) const
{
  ListNode<T> *ptr;
  
  for(ptr = head; ptr && (ptr->data < key  || key < ptr->data); ptr = ptr->next);
  
  if(ptr)
    return ptr->data;
  
  return notFound;
} // find()

template <class T>
int List<T>::getSize() const
{
  return size;
} // getSize();


template <class T>
const T& List<T>::operator[] (int index) const
{
  ListNode<T> *ptr = head;
  
  for(int i = 0; i < index; i++)
    ptr = ptr->next;
    
  return ptr->data;
} // operator[]


template <class T>
T& List<T>::operator[] (int index)
{
  ListNode<T> *ptr = head;
  
  for(int i = 0; i < index; i++)
    ptr = ptr->next;
    
  return ptr->data;
} // operator[]


template <class T>
List<T>& List<T>::operator+= (const T &d)
{
  ListNode<T> *ptr, *prev = NULL;
  
  for(ptr = head; ptr && ptr->data < d; ptr = ptr->next)
    prev = ptr;
  
  if(prev)
    prev->next = new ListNode<T>(d, ptr);
  else 
    head = new ListNode<T>(d, ptr);
  
  size++;
  
  return *this;
} // operator+=


template <class T>
List<T>& List<T>::operator-= (const T &d)
{
  ListNode<T> *ptr, *prev = NULL;
  
  for(ptr = head; ptr && ptr->data < d; ptr = ptr->next)
    prev = ptr;
  
  if(ptr && !(d < ptr->data))
  {
    if(prev)
      prev->next = ptr->next;
    else // deleting head of list
      head = ptr->next;
    
    delete ptr;
    size--;
  } // if d found
  
  return *this;
} // operator-=


template <class T>
const List<T>& List<T>::operator= (const List<T> &rhs)
{
  ListNode <T> *ptr, *ptr2;
  
  if(this == &rhs)
    return *this;
  
  for(ptr = head; ptr; ptr = head)
  {
    head = ptr->next;
    delete ptr;
  }  // for ptr
  
  
  for(ptr2 = rhs.head; ptr2; ptr2 = ptr2->next)
    if(!ptr)
      ptr = head = new ListNode<T>(ptr2->data, NULL);
    else
      ptr = ptr->next = new ListNode<T>(ptr2->data, NULL);
  
  size = rhs.size;
  return *this;
} // operator=
