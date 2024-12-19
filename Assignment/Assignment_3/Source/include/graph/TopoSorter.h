/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   TopoSorter.h
 * Author: ltsach
 *
 * Created on July 11, 2021, 10:21 PM
 */

#ifndef TOPOSORTER_H
#define TOPOSORTER_H
#include "graph/DGraphModel.h"
#include "list/DLinkedList.h"
#include "sorting/DLinkedListSE.h"
#include "hash/xMap.h"
#include "stacknqueue/Stack.h"
#include "stacknqueue/Queue.h"

template <class T>
class TopoSorter
{
public:
    static int DFS;
    static int BFS;

protected:
    DGraphModel<T> *graph;
    int (*hash_code)(T &, int);

public:
    TopoSorter(DGraphModel<T> *graph, int (*hash_code)(T &, int) = 0)
    {
        // TODO
        this->graph = graph;
        this->hash_code = hash_code;
    }
    DLinkedList<T> sort(int mode = 0, bool sorted = true)
    {
        // TODO
        return (mode == BFS) ? bfsSort(sorted) : dfsSort(sorted);
    }
    DLinkedList<T> bfsSort(bool sorted = true)
    {
        // TODO
        xMap<T, int> inDegree = vertex2inDegree(hash_code);
        Queue<T> bfsQueue;
        DLinkedListSE<T> list = listOfZeroInDegrees();
        if (sorted)
        {
            list.sort();
        }

        DLinkedList<T> research;

        for (auto it = list.begin(); it != list.end(); ++it)
        {
            bfsQueue.push(*it);
        }
        while (!bfsQueue.empty())
        {
            T current = bfsQueue.peek();
            bfsQueue.pop();
            research.add(current);
            DLinkedListSE<T> neighbors = graph->getOutwardEdges(current);
            for (auto c = neighbors.begin(); c != neighbors.end(); ++c)
            {
                T neighbor = *c;
                int degree = inDegree.get(neighbor) - 1;
                inDegree.put(neighbor, degree);
                if (degree == 0)
                {
                    bfsQueue.push(neighbor);
                }
            }
        }
        return research;
    }

    DLinkedList<T> dfsSort(bool sorted = true)
    {
        // TODO
        DLinkedListSE<T> List_sort(listOfZeroInDegrees());
        if (sorted)
        {
            List_sort.sort();
        }
        xMap<T, bool> visited(hash_code);
        DLinkedList<T> research;
        Stack<T> dfsStack;
        for (const auto &vertex : graph->vertices())
        {
            visited.put(vertex, false);
        }
        for (auto it = List_sort.begin(); it != List_sort.end(); ++it)
        {
            T vertex = *it;
            if (!visited.get(vertex))
            {
                dfsStack.push(vertex);
                visited.put(vertex, true);
            }

            while (!dfsStack.empty())
            {
                T current = dfsStack.peek();
                DLinkedListSE<T> neighbors = graph->getOutwardEdges(current);
                bool checked = false;
                for (auto c = neighbors.begin(); c != neighbors.end(); ++c)
                {
                    T neighbor = *c;
                    if (visited.get(neighbor) == false)
                    {
                        dfsStack.push(neighbor);
                        visited.put(neighbor, true);
                        checked = true;
                        break;
                    }
                }
                if (!checked)
                {
                    research.add(0, dfsStack.pop());
                }
            }
        }
        return research;
    }

protected:
    // Helper functions
    xMap<T, int> vertex2inDegree(int (*hash)(T &, int))
    {
        xMap<T, int> result(hash);
        for (const auto &vertex : graph->vertices())
        {
            result.put(vertex, graph->inDegree(vertex));
        }
        return result;
    }
    xMap<T, int> vertex2outDegree(int (*hash)(T &, int))
    {
        xMap<T, int> result(hash);
        for (const auto &vertex : graph->vertices())
        {
            result.put(vertex, graph->outDegree(vertex));
        }
        return result;
    }
    DLinkedList<T> listOfZeroInDegrees()
    {
        DLinkedList<T> result;
        for (const auto &vertex : graph->vertices())
        {
            if (graph->inDegree(vertex) == 0)
            {
                result.add(vertex);
            }
        }
        return result;
    }

}; // TopoSorter
template <class T>
int TopoSorter<T>::DFS = 0;
template <class T>
int TopoSorter<T>::BFS = 1;

/////////////////////////////End of TopoSorter//////////////////////////////////

#endif /* TOPOSORTER_H */
