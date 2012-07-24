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
List<T>& List<T>::operator+=()
{
  
  return(*this);
}
  
template <class T> 
List<T>& List<T>::operator-=()
{
  
  return(*this);
}
  
template <class T> 
List<T>& List<T>::operator[](int index)
{
  
  return(*this);
}
  
template <class T> 
const List<T>& List<T>::operator[](int index) const
{
  
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
  ListNode *ptr, *prev = NULL;
  for(ptr = head; ptr && ptr->data < d; ptr = ptr->next)
    prev = ptr;
  
  if(prev)
    prev->next = new ListNode(d, ptr);
  else
    head = new ListNode(d, ptr);
  
  return;
}
  
template <class T> 
string& List<T>::find(const T k)
{
  ListNode *ptr;
  
  for(ptr = head; ptr && ptr->data < k; ptr = ptr->next);
  
  if(!ptr || key < ptr->data)
    return(notFound);
  else
    return(ptr->data);
}
  
template <class T> 
void List<T>::remove(const T k)
{
  ListNode *ptr, *prev = NULL;
  
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
