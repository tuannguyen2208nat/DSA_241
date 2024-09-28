

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class IntDLinkedList
{
private:
    class Node;

private:
    Node *head;
    Node *tail;
    int count;

public:
    IntDLinkedList();
    // ~IntDLinkedList();

    void add(int e);
    void add(int index, int e);
    int &get(int index);
    int removeAt(int index);
    int size();
    bool empty();

    string toString();
    // void dump();

private:
    Node *getAddressAt(int index);

private:
    class Node
    {
    public:
        int data;
        Node *next;
        Node *prev;

        Node(int data, Node *next = NULL, Node *prev = NULL) : data(data), next(next), prev(prev) {}
        Node(Node *next = NULL, Node *prev = NULL) : next(next), prev(prev) {}
    };
};

IntDLinkedList::IntDLinkedList() : head(new Node()), tail(new Node()), count(0)
{
    head->next = tail;
    tail->prev = head;
}

void IntDLinkedList::add(int e)
{
    Node *newNode = new Node(e);
    if (count == 0)
    {
        newNode->prev = head;
        head->next = newNode;
        newNode->next = tail;
        tail->prev = newNode;
    }
    else
    {
        newNode->prev = tail->prev;
        tail->prev->next = newNode;
        newNode->next = tail;
        tail->prev = newNode;
    }
    count++;
}

void IntDLinkedList::add(int index, int e)
{
    if (index < 0 || index > count)
    {
        throw std::out_of_range("Index is out of range!");
    }
    Node *newNode = new Node(e);
    if (count == 0)
    {
        newNode->prev = head;
        head->next = newNode;
        newNode->next = tail;
        tail->prev = newNode;
    }
    else if (index == 0)
    {
        newNode->next = head->next;
        head->next->prev = newNode;
        head->next = newNode;
        newNode->prev = head;
    }
    else if (index == count)
    {
        newNode->prev = tail->prev;
        tail->prev->next = newNode;
        newNode->next = tail;
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
    count++;
}

int IntDLinkedList::size()
{
    return count;
}

bool IntDLinkedList::empty()
{
    return count == 0;
}

string IntDLinkedList::toString()
{
    string result = "[";
    Node *temp = head->next;
    while (temp != tail)
    {
        result += (temp->data);
        temp = temp->next;
        if (temp != tail)
        {
            result += " ,";
        }
    }
    result += "]";
    return result;
}

IntDLinkedList::Node *IntDLinkedList::getAddressAt(int index)
{
    if (index < 0 || index >= count)
    {
        throw std::out_of_range("Index is out of range!");
    }
    Node *temp = head->next;
    for (int i = 0; i < index; i++)
    {
        temp = temp->next;
    }
    return temp;
}

int &IntDLinkedList::get(int index)
{
    if (index < 0 || index >= count)
    {
        throw std::out_of_range("Index is out of range!");
    }
    Node *temp = head->next;
    for (int i = 0; i < index; i++)
    {
        temp = temp->next;
    }
    return temp->data;
}

int IntDLinkedList::removeAt(int index)
{
    if (index < 0 || index >= count)
    {
        throw std::out_of_range("Index is out of range!");
    }
    Node *deleteNode;
    if (index == 0)
    {
        deleteNode = head->next;
        if (count == 1)
        {
            head->next = tail;
            tail->prev = head;
        }
        else
        {
            head->next = deleteNode->next;
            deleteNode->next->prev = head;
        }
    }
    else if (index == count - 1)
    {
        deleteNode = tail->prev;
        tail->prev = deleteNode->prev;
        deleteNode->prev->next = tail->prev;
    }
    else
    {
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
            temp = head->prev;
            for (int i = 0; i < count - index - 1; i++)
            {
                temp = temp->prev;
            }
        }
        deleteNode = temp;
        temp->prev->next = deleteNode->next;
        temp->next->prev = temp->prev;
    }
    int result = deleteNode->data;
    delete deleteNode;
    deleteNode = nullptr;
    count--;
    return result;
}

int main()
{
    IntDLinkedList list;
    list.add(10);
    list.removeAt(0);
    cout << list.toString();
    return 0;
}