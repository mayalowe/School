// Eric Lowe
// list.h


#ifndef LIST_H_
#define LIST_H_

template <class T> class List;

template <class T> 
class ListNode {
  T data;
  ListNode<T> next;
  ListNode(int d, ListNode *n): data(d), next(n){};
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
  List<T>& operator[]();
  const List<T>& operator[]() const;
  void getSize();
  void insert(const T &n);
  int& find(int k);
  void remove(int n);
};


#endif /* LIST_H_ */
#include "list.cpp"