

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

template <class T>
class ArrayList
{
protected:
    T *data;      // dynamic array to store the list's items
    int capacity; // size of the dynamic array
    int count;    // number of items stored in the array
public:
    ArrayList()
    {
        capacity = 5;
        count = 0;
        data = new T[5];
    }
    ~ArrayList() { delete[] data; }
    void ensureCapacity(int index);
    string toString();
    void add(T e);
    void add(int index, T e);
    int size();
    bool empty();
    void clear();             // remove data and set the list to the initial condition
    T get(int index);         // get the element at the index, if the index is out of range, "throw std::out_of_range("index is out of range");"
    void set(int index, T e); // set the index position in the list with the value e
    int indexOf(T item);      // get the first index of item in the list, else return -1
    bool contains(T item);    // check if the item is in the list
    T removeAt(int index);
    bool removeItem(T item);
};

template <class T>
void ArrayList<T>::ensureCapacity(int cap)
{
    try
    {
        T *newData = new T[cap];
        for (int i = 0; i < count; ++i)
        {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = cap;
    }
    catch (const std::bad_alloc &)
    {
        throw std::bad_alloc();
    }
}

template <class T>
void ArrayList<T>::add(T e)
{
    if (count == capacity)
    {
        ensureCapacity(count * 1.5);
    }
    data[count++] = e;
}

template <class T>
void ArrayList<T>::add(int index, T e)
{
    if (index < 0 || index > count)
    {
        throw std::out_of_range("Index is out of range");
    }
    if (count == capacity)
    {
        ensureCapacity(count * 1.5);
    }
    for (int i = count; i > index; --i)
    {
        data[i] = data[i - 1];
    }
    data[index] = e;
    ++count;
}

template <class T>
int ArrayList<T>::size()
{
    /* Return the length (size) of the array */
    return count;
}

template <class T>
std::string converToString(T &item)
{
    std::stringstream ss;
    ss << item;
    return ss.str();
}

template <class T>
string ArrayList<T>::toString()
{
    string result;
    for (int i = 0; i < count; i++)
    {
        result += converToString(data[i]);
        if (i != count - 1)
        {
            result += " ,";
        }
    }
    /* Return the length (size) of the array */
    return result;
}

template <class T>
T ArrayList<T>::removeAt(int index)
{
    /*
    Remove element at index and return removed value
    if index is invalid:
        throw std::out_of_range("index is out of range");
    */

    if (index < 0 || index >= count)
    {
        throw std::out_of_range("Index is out of range");
    }
    T result = data[index];
    for (int i = index; i < count - 1; i++)
    {
        data[i] = data[i + 1];
    }
    count--;
    return result;
}

template <class T>
bool ArrayList<T>::removeItem(T item)
{
    for (int i = 0; i < count; i++)
    {
        if (data[i] == item)
        {
            if (removeAt(i))
            {
                return true;
            }
        }
    }
    return false;
    /* Remove the first apperance of item in array and return true, otherwise return false */
}

template <class T>
void ArrayList<T>::clear()
{
    if (count != 0)
    {
        delete[] data;
        data = nullptr;
        count = 0;
    }
    capacity = 10;
    data = new T[capacity];
}

template <class T>
bool ArrayList<T>::empty()
{
    return count == 0;
}

template <class T>
int ArrayList<T>::indexOf(T item)
{
    for (int i = 0; i < count; i++)
    {
        if (data[i] == item)
        {
            return i;
        }
    }
    return -1;
}

template <class T>
bool ArrayList<T>::contains(T item)
{
    if (indexOf(item) != -1)
    {
        return true;
    }
    return false;
}

template <class T>
void ArrayList<T>::set(int index, T e)
{
    if (index < 0 || index >= count)
    {
        throw std::out_of_range("Index is out of range");
    }
    data[index] = e;
}

template <class T>
T ArrayList<T>::get(int index)
{
    if (index < 0 || index >= count)
    {
        throw std::out_of_range("Index is out of range");
    }
    return data[index];
}

int main()
{
    ArrayList<int> arr;
    int size = 10;
    for (int index = 0; index < size; index++)
    {
        arr.add(index);
    }
    try
    {
        arr.set(10, 100);
        cout << arr.get(10) << '\n';
    }
    catch (const std::exception &e)
    {
        cout << e.what() << endl;
    }
}