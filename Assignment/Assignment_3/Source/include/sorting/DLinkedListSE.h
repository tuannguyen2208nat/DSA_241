/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   DLinkedListSE.h
 * Author: LTSACH
 *
 * Created on 31 August 2020, 14:13
 */

#ifndef DLINKEDLISTSE_H
#define DLINKEDLISTSE_H
#include "list/DLinkedList.h"
#include "sorting/ISort.h"

template <class T>
class DLinkedListSE : public DLinkedList<T>
{
public:
    DLinkedListSE(
        void (*removeData)(DLinkedList<T> *) = 0,
        bool (*itemEQ)(T &, T &) = 0) : DLinkedList<T>(removeData, itemEQ) {

                                        };

    DLinkedListSE(const DLinkedList<T> &list) : DLinkedList<T>(list)
    {
        this->copyFrom(list);
    }

    void sort(int (*comparator)(T &, T &) = 0)
    {
        // TODO: implement this function
        //     - You should implement the merge sort algorithm
        if (this->head->next == this->tail || this->head->next->next == this->tail)
        {
            return;
        }
        typename DLinkedList<T>::Node *current = mergeSort(this->head->next, comparator);
        current->prev = this->head;
        this->head->next = current;
        while (current->next != this->tail)
        {
            current = current->next;
        }
        this->tail->prev = current;
    };

private:
    typename DLinkedList<T>::Node *split(typename DLinkedList<T>::Node *head)
    {
        typename DLinkedList<T>::Node *slow = head;
        typename DLinkedList<T>::Node *fast = head;
        while (fast->next != this->tail && fast->next->next != this->tail)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        typename DLinkedList<T>::Node *second = slow->next;
        slow->next = this->tail;
        return second;
    }

    typename DLinkedList<T>::Node *merge(typename DLinkedList<T>::Node *left,
                                         typename DLinkedList<T>::Node *right,
                                         int (*comparator)(T &, T &) = 0)
    {
        if (left == this->tail)
            return right;
        if (right == this->tail)
            return left;

        if (compare(left->data, right->data, comparator) <= 0)
        {
            left->next = merge(left->next, right, comparator);
            if (left->next != this->tail)
            {
                left->next->prev = left;
            }
            return left;
        }
        else
        {

            right->next = merge(left, right->next, comparator);
            if (right->next != this->tail)
            {
                right->next->prev = right;
            }
            return right;
        }
    }

    typename DLinkedList<T>::Node *mergeSort(typename DLinkedList<T>::Node *head,
                                             int (*comparator)(T &, T &) = 0)
    {
        if (head->next == this->tail || head->next->next == this->tail)
        {
            return head;
        }
        typename DLinkedList<T>::Node *mid = split(head);
        typename DLinkedList<T>::Node *rightHead = mid;

        typename DLinkedList<T>::Node *newLeft = mergeSort(head, comparator);
        typename DLinkedList<T>::Node *newRight = mergeSort(rightHead, comparator);
        return merge(newLeft, newRight, comparator);
    }

protected:
    static int compare(T &lhs, T &rhs, int (*comparator)(T &, T &) = 0)
    {
        if (comparator != 0)
            return comparator(lhs, rhs);
        else
        {
            if (lhs < rhs)
                return -1;
            else if (lhs > rhs)
                return +1;
            else
                return 0;
        }
    }
};

#endif /* DLINKEDLISTSE_H */
