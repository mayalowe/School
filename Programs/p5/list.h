// Eric Lowe
// list.h


#ifndef LIST_H_
#define LIST_H_

template <class T> class List;

template <class T> 
class ListNode {
  T data;
  ListNode<T> *next;
  ListNode(T d, ListNode *n): data(d), next(n){};
  friend class List<T>;
};


template <class T> 
class List {
  ListNode<T> *head;
  int size;
  const T notFound;
    
public:
  List<T>(const T nf);
  ~List<T>();
  List<T>& operator=(const T &rhs);
  List<T>& operator+=();
  List<T>& operator-=();
  List<T>& operator[](int index);
  const List<T>& operator[](int index) const;
  void getSize();
  void insert(const T &n);
  string& find(const T k);
  void remove(const T k);
};


#endif /* LIST_H_ */

#include "list.cpp"
