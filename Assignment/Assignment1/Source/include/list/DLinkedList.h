/*
 * File:   DLinkedList.h
 */

#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H

#include <iostream>
#include <sstream>
#include <type_traits>

#include "list/IList.h"
using namespace std;

template <class T>
class DLinkedList : public IList<T>
{
public:
  class Node;        // Forward declaration
  class Iterator;    // Forward declaration
  class BWDIterator; // Forward declaration

protected:
  Node *head;
  Node *tail;
  int count;
  bool (*itemEqual)(T &lhs, T &rhs);
  void (*deleteUserData)(DLinkedList<T> *);

public:
  DLinkedList(void (*deleteUserData)(DLinkedList<T> *) = 0,
              bool (*itemEqual)(T &, T &) = 0);
  DLinkedList(const DLinkedList<T> &list);
  DLinkedList<T> &operator=(const DLinkedList<T> &list);
  ~DLinkedList();

  // Inherit from IList: BEGIN
  void add(T e);
  void add(int index, T e);
  T removeAt(int index);
  bool removeItem(T item, void (*removeItemData)(T) = 0);
  bool empty();
  int size();
  void clear();
  T &get(int index);
  int indexOf(T item);
  bool contains(T item);
  string toString(string (*item2str)(T &) = 0);
  // Inherit from IList: END

  void println(string (*item2str)(T &) = 0)
  {
    cout << toString(item2str) << endl;
  }
  void setDeleteUserDataPtr(void (*deleteUserData)(DLinkedList<T> *) = 0)
  {
    this->deleteUserData = deleteUserData;
  }

  bool contains(T array[], int size)
  {
    int idx = 0;
    for (DLinkedList<T>::Iterator it = begin(); it != end(); it++)
    {
      if (!equals(*it, array[idx++], this->itemEqual))
        return false;
    }
    return true;
  }

  Iterator begin() { return Iterator(this, true); }
  Iterator end() { return Iterator(this, false); }

  BWDIterator bbegin() { return BWDIterator(this, true); }
  BWDIterator bend() { return BWDIterator(this, false); }

protected:
  void copyFrom(const DLinkedList<T> &list);
  void removeInternalData();
  Node *getPreviousNodeOf(int index);

  //! FUNTION STATIC
public:
  static void free(DLinkedList<T> *list)
  {
    typename DLinkedList<T>::Iterator it = list->begin();
    while (it != list->end())
    {
      delete *it;
      it++;
    }
  }

protected:
  static bool equals(T &lhs, T &rhs, bool (*itemEqual)(T &, T &))
  {
    if (itemEqual == 0)
      return lhs == rhs;
    else
      return itemEqual(lhs, rhs);
  }

public:
  class Node
  {
  public:
    T data;
    Node *next;
    Node *prev;
    friend class DLinkedList<T>;

  public:
    Node(Node *next = 0, Node *prev = 0)
    {
      this->next = next;
      this->prev = prev;
    }
    Node(T data, Node *next = 0, Node *prev = 0)
    {
      this->data = data;
      this->next = next;
      this->prev = prev;
    }
  };

public:
  class Iterator
  {
  private:
    DLinkedList<T> *pList;
    Node *pNode;

  public:
    Iterator(DLinkedList<T> *pList = 0, bool begin = true)
    {
      if (begin)
      {
        if (pList != 0)
          this->pNode = pList->head->next;
        else
          pNode = 0;
      }
      else
      {
        if (pList != 0)
          this->pNode = pList->tail;
        else
          pNode = 0;
      }
      this->pList = pList;
    }

    Iterator &operator=(const Iterator &iterator)
    {
      this->pNode = iterator.pNode;
      this->pList = iterator.pList;
      return *this;
    }
    void remove(void (*removeItemData)(T) = 0)
    {
      pNode->prev->next = pNode->next;
      pNode->next->prev = pNode->prev;
      Node *pNext = pNode->prev; // MUST prev, so iterator++ will go to end
      if (removeItemData != 0)
        removeItemData(pNode->data);
      delete pNode;
      pNode = pNext;
      pList->count -= 1;
    }

    T &operator*() { return pNode->data; }
    bool operator!=(const Iterator &iterator)
    {
      return pNode != iterator.pNode;
    }
    // Prefix ++ overload
    Iterator &operator++()
    {
      pNode = pNode->next;
      return *this;
    }
    // Postfix ++ overload
    Iterator operator++(int)
    {
      Iterator iterator = *this;
      ++*this;
      return iterator;
    }
  };

  class BWDIterator
  {
  private:
    Node *pNode;
    DLinkedList<T> *pList;

  public:
    BWDIterator(DLinkedList<T> *pList = 0, bool begin = true)
    {
      if (begin)
      {
        if (pList != 0)
          this->pNode = pList->tail->prev;
        else
          pNode = 0;
      }
      else
      {
        if (pList != 0)
          this->pNode = pList->head;
        else
          pNode = 0;
      }
      this->pList = pList;
    }

    BWDIterator &operator=(const BWDIterator &iterator)
    {
      this->pNode = iterator.pNode;
      this->pList = iterator.pList;
      return *this;
    }

    void remove(void (*removeItemData)(T) = 0)
    {
      pNode->next->prev = pNode->prev;
      pNode->prev->next = pNode->next;
      Node *pPrev = pNode->next; // MUST prev, so iterator-- will go to end
      if (removeItemData != 0)
        removeItemData(pNode->data);
      delete pNode;
      pNode = pPrev;
      pList->count -= 1;
    }

    T &operator*()
    {
      return pNode->data;
    }

    bool operator!=(const BWDIterator &iterator)
    {
      return pNode != iterator.pNode;
    }

    // Prefix -- overload
    BWDIterator &operator--()
    {
      pNode = pNode->prev;
      return *this;
    }

    // Postfix -- overload
    BWDIterator operator--(int)
    {
      BWDIterator iterator = *this;
      --*this;
      return iterator;
    }
  };
};

template <class T>
using List = DLinkedList<T>;

//! ////////////////////////////////////////////////////////////////////
//! //////////////////////     METHOD DEFNITION      ///////////////////
//! ////////////////////////////////////////////////////////////////////

template <class T>
DLinkedList<T>::DLinkedList(void (*deleteUserData)(DLinkedList<T> *),
                            bool (*itemEqual)(T &, T &))
{
  // TODO implement
  this->deleteUserData = deleteUserData;
  this->itemEqual = itemEqual;
  head = new Node(T(0));
  tail = new Node(T(0));

  head->next = tail;
  tail->prev = head;

  count = 0;
}

template <class T>
DLinkedList<T>::DLinkedList(const DLinkedList<T> &list) : head(nullptr), tail(nullptr), count(0)
{
  // TODO implement
  Node *temp = list.head;
  for (int i = 0; i < list.count; i++)
  {
    this->add(temp->data, i);
    temp = temp->next;
  }
}

template <class T>
DLinkedList<T> &DLinkedList<T>::operator=(const DLinkedList<T> &list)
{
  // TODO implement
  Node *current;
  while (count != 0)
  {
    current = head;
    head = head->next;
    delete current;
    count--;
  }
  head = tail = nullptr;
  count = 0;
  Node *temp = list.head;
  for (int i = 0; i < list.count; i++)
  {
    this->add(temp->data, i);
    temp = temp->next;
  }
}

template <class T>
DLinkedList<T>::~DLinkedList()
{
  // TODO implement
  Node *temp;
  while (count != 0)
  {
    temp = head;
    head = head->next;
    delete temp;
    count--;
  }
  head = tail = nullptr;
  count = 0;
}

template <class T>
void DLinkedList<T>::add(T e)
{
  // TODO implement
  Node *newNode = new Node(e);
  if (count == 0)
  {
    newNode->prev = head;
    newNode->next = tail;
    head->next = newNode;
    tail->prev = newNode;
  }
  else
  {
    newNode->prev = tail->prev;
    newNode->next = tail;
    tail->prev->next = newNode;
    tail->prev = newNode;
  }
  this->count++;
}
template <class T>
void DLinkedList<T>::add(int index, T e)
{
  if (index < 0 || index > count)
  {
    throw std::out_of_range("Index is out of range!");
  }

  Node *newNode = new Node(e);

  if (this->count == 0)
  {
    newNode->prev = head;
    newNode->next = tail;
    head->next = newNode;
    tail->prev = newNode;
  }
  else if (index == 0)
  {
    newNode->next = head->next;
    head->next->prev = newNode;
    head->next = newNode;
    newNode->prev = head;
  }
  else if (index == this->count)
  {
    newNode->prev = tail->prev;
    newNode->next = tail;
    tail->prev->next = newNode;
    tail->prev = newNode;
  }
  else
  {
    Node *temp = head->next;
    for (int i = 0; i < index - 1; i++)
    {
      temp = temp->next;
    }

    newNode->next = temp->next;
    newNode->prev = temp;
    temp->next->prev = newNode;
    temp->next = newNode;
  }
  this->count++;
}

template <class T>
T DLinkedList<T>::removeAt(int index)
{

  if (index < 0 || index >= count)
  {
    throw std::out_of_range("Index is out of range!");
  }

  T result;
  Node *deleteNode;

  if (count == 1)
  {
    deleteNode = head->next;
    head->next = tail;
    tail->prev = head;
  }

  else if (index == 0)
  {
    deleteNode = head->next;
    head->next = deleteNode->next;
    head->next->prev = head;
  }

  else if (index == count - 1)
  {
    deleteNode = tail->prev;
    tail->prev = deleteNode->prev;
    deleteNode->prev->next = tail;
  }

  else
  {
    Node *temp = head->next;
    for (int i = 0; i < index; i++)
    {
      temp = temp->next;
    }
    deleteNode = temp;
    deleteNode->prev->next = deleteNode->next;
    deleteNode->next->prev = deleteNode->prev;
  }

  result = deleteNode->data;
  delete deleteNode;
  count--;

  return result;
}

template <class T>
bool DLinkedList<T>::empty()
{
  // TODO implement
  return count == 0;
}

template <class T>
int DLinkedList<T>::size()
{
  // TODO implement
  return count;
}

template <class T>
void DLinkedList<T>::clear()
{
  // TODO implement
  Node *current = head->next;
  Node *nextNode;

  while (current != tail)
  {
    nextNode = current->next;
    delete current;
    current = nextNode;
  }
  head->next = tail;
  tail->prev = head;
  count = 0;
}

template <class T>
T &DLinkedList<T>::get(int index)
{
  // TODO implement
  if (index < 0 || index >= count)
  {
    throw std::out_of_range("Index is out of range!");
  }
  Node *temp;
  if (index < count / 2)
  {
    temp = head->next;
    for (int i = 0; i < index; i++)
    {
      temp = temp->next;
    }
  }
  else
  {
    temp = tail->prev;
    for (int i = count - 1; i > index; i--)
    {
      temp = temp->prev;
    }
  }
  return temp->data;
}

template <class T>
int DLinkedList<T>::indexOf(T item)
{
  // TODO implement
  Node *temp = head->next;
  for (int i = 0; i < count; i++)
  {
    if (temp->data == item)
    {
      return i;
    }
    temp = temp->next;
  }
  return -1;
}

template <class T>
bool DLinkedList<T>::removeItem(T item, void (*removeItemData)(T))
{
  // TODO implement
  int index = -1;
  Node *temp = head->next;
  if constexpr (std::is_pointer_v<T>)
  {
    for (int i = 0; i < count; i++)
    {
      if (*temp->data == *item)
      {
        index = i;
        break;
      }
      temp = temp->next;
    }
  }
  else
  {
    index = indexOf(item);
  }

  if (index == -1)
  {
    return false;
  }

  temp = head->next;
  for (int i = 0; i <= index; i++)
  {
    temp = temp->next;
  }

  if (removeItemData != 0)
  {
    removeItemData(temp->data);
  }
  removeAt(index);
  return true;
}

template <class T>
bool DLinkedList<T>::contains(T item)
{
  // TODO implement
  Node *temp = head->next;
  for (int i = 0; i < count; i++)
  {
    if (this->equals(temp->data, item, itemEqual))
    {
      return true;
    }
    temp = temp->next;
  }
  return false;
}

template <class T>
std::string convertToString(T &item)
{
  std::stringstream ss;
  ss << item;
  return ss.str();
}

template <class T>
string DLinkedList<T>::toString(string (*item2str)(T &))
{
  // TODO implement
  string result = "[";
  if (count > 0)
  {
    Node *temp = head->next;
    while (temp != tail)
    {
      result += item2str ? item2str(temp->data) : convertToString(temp->data);
      temp = temp->next;
      if (temp != tail)
      {
        result += ", ";
      }
    }
  }
  result += "]";
  return result;
}

//! ////////////////////////////////////////////////////////////////////
//! ////////////////////// (private) METHOD DEFNITION //////////////////
//! ////////////////////////////////////////////////////////////////////
template <class T>
void DLinkedList<T>::copyFrom(const DLinkedList<T> &list)
{
  /**
   * Copies the contents of another doubly linked list into this list.
   * Initializes the current list to an empty state and then duplicates all data
   * and pointers from the source list. Iterates through the source list and
   * adds each element, preserving the order of the nodes.
   */
  // TODO implement
}

template <class T>
void DLinkedList<T>::removeInternalData()
{
  /**
   * Clears the internal data of the list by deleting all nodes and user-defined
   * data. If a custom deletion function is provided, it is used to free the
   * user's data stored in the nodes. Traverses and deletes each node between
   * the head and tail to release memory.
   */
  // TODO implement
}

template <class T>
typename DLinkedList<T>::Node *DLinkedList<T>::getPreviousNodeOf(int index)
{
  /**
   * Returns the node preceding the specified index in the doubly linked list.
   * If the index is in the first half of the list, it traverses from the head;
   * otherwise, it traverses from the tail. Efficiently navigates to the node by
   * choosing the shorter path based on the index's position.
   */
  // TODO implement
}

#endif /* DLINKEDLIST_H */
