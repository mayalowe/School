// Eric Lowe
// list.cpp

using namespace std;


template <class T> 
List<T>::List(const T nf) : head(NULL), size(0), notFound(nf)
{
  
}
  
template <class T> 
List<T>::~List()
{
  delete[] head;
}

template <class T>  
List<T>& List<T>::operator=(const T &rhs)
{
  
  return(*this);
}
  
template <class T> 
List<T>& List<T>::operator+=(const T d)
{
  
  return(*this);
}
  
template <class T> 
List<T>& List<T>::operator-=(const T d)
{
  
  return(*this);
}
  
template <class T> 
List<T>& List<T>::operator[](int index)
{
  if(index > size)
    cout << "Node does not exist!\n" << endl;
  return(*this);
}
  
template <class T> 
const List<T>& List<T>::operator[](int index) const
{
  if(index > size)
    cout << "Node does not exist!\n" << endl;
  return(*this);
}
  
template <class T> 
void List<T>::getSize()
{
  
  return;
}
 
template <class T> 
void List<T>::insert(const T &n)
{
  ListNode<T> *ptr, *prev = NULL;
  for(ptr = head; ptr && ptr->data < n; ptr = ptr->next)
    prev = ptr;
  
  if(prev)
    prev->next = new ListNode<T>(n, ptr);
  else
    head = new ListNode<T>(n, ptr);
  
  return;
}
  
template <class T> 
T& List<T>::find(const T k)
{
  ListNode<T> *ptr;
  
  for(ptr = head; ptr && ptr->data < k; ptr = ptr->next);
  
  if(!ptr || k < ptr->data)
    return(notFound);
  else
    return(ptr->data);
}
  
template <class T> 
void List<T>::remove(const T k)
{
  ListNode<T> *ptr, *prev = NULL;
  
  for(ptr = head; ptr && ptr->data != k; ptr = ptr->next)
    prev = ptr;
  
  if(!ptr)
    return;
  
  if(!prev)
    head = ptr->next;
  else
    prev->next = ptr->next;
  
  delete ptr;
  return;
}
