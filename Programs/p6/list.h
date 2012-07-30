// Eric Lowe and Rodolfo Hernandez
// list.h
// Header file for the List and ListNode classes
// which implement a Linked List data structure
// for course information

#ifndef LIST_H
#define	LIST_H

template <class T> 
class List;
template <class T> 
class ListPtr;

template <class T>
class ListNode
{
  T data;
  ListNode <T> *next;
  ListNode(const T &d, ListNode<T> *n);
  friend class List<T>;
  friend class ListPtr<T>;
}; // class ListNode

template <class T>
class List
{
protected:
  ListNode <T> *head;
  int size;
  const T notFound;
public:
  List(const T &nF);
  List(const List<T> &rhs);
  ~List();
  const T& find(const T &key) const;
  int getSize() const;
  const T& operator[] (int index) const;
  T& operator[] (int index);
  List<T>& operator+= (const T &d);
  List<T>& operator-= (const T &d);
  const List<T>& operator= (const List<T> &rhs);
};

#include "list.cpp"
#endif	/* LIST_H */

