/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   DGraphModel.h
 * Author: LTSACH
 *
 * Created on 23 August 2020, 19:36
 */

#ifndef DGRAPHMODEL_H
#define DGRAPHMODEL_H
#include "graph/AbstractGraph.h"
#include "stacknqueue/Queue.h"
#include "stacknqueue/Stack.h"
#include "hash/xMap.h"
#include "sorting/DLinkedListSE.h"

//////////////////////////////////////////////////////////////////////
///////////// GraphModel: Directed Graph Model    ////////////////////
//////////////////////////////////////////////////////////////////////

template <class T>
class DGraphModel : public AbstractGraph<T>
{
private:
public:
    DGraphModel(
        bool (*vertexEQ)(T &, T &),
        string (*vertex2str)(T &)) : AbstractGraph<T>(vertexEQ, vertex2str)
    {
    }

    void connect(T from, T to, float weight = 0)
    {
        // TODO
        typename AbstractGraph<T>::VertexNode *fromNode = this->getVertexNode(from);
        if (!fromNode)
            throw VertexNotFoundException(this->vertex2str(from));
        typename AbstractGraph<T>::VertexNode *toNode = this->getVertexNode(to);
        if (!toNode)
            throw VertexNotFoundException(this->vertex2str(to));
        fromNode->connect(toNode, weight);
    }
    void disconnect(T from, T to)
    {
        // TODO
        typename AbstractGraph<T>::VertexNode *fromNode = this->getVertexNode(from);
        if (!fromNode)
            throw VertexNotFoundException(this->vertex2str(from));
        typename AbstractGraph<T>::VertexNode *toNode = this->getVertexNode(to);
        if (!toNode)
            throw VertexNotFoundException(this->vertex2str(to));

        if (fromNode->getEdge(toNode))
        {
            fromNode->removeTo(toNode);
        }
        else
        {
            typename AbstractGraph<T>::Edge result(fromNode, toNode);
            throw EdgeNotFoundException(this->edge2Str(result));
        }
    }
    void remove(T vertex)
    {
        // TODO
        typename AbstractGraph<T>::VertexNode *fromNode = this->getVertexNode(vertex);
        if (!fromNode)
            throw VertexNotFoundException(this->vertex2str(vertex));
        DLinkedList<T> outEdge = this->getOutwardEdges(vertex);
        for (auto it = outEdge.begin(); it != outEdge.end(); ++it)
        {
            typename AbstractGraph<T>::VertexNode *toNode = this->getVertexNode(*it);
            if (toNode)
            {
                fromNode->removeTo(toNode);
            }
        }
        DLinkedList<T> inEdge = this->getInwardEdges(vertex);
        for (auto it = inEdge.begin(); it != inEdge.end(); ++it)
        {
            typename AbstractGraph<T>::VertexNode *toNode = this->getVertexNode(*it);
            if (toNode)
            {
                toNode->removeTo(fromNode);
            }
        }
        this->nodeList.removeItem(fromNode);
        delete fromNode;
    }

    static DGraphModel<T> *create(
        T *vertices, int nvertices, Edge<T> *edges, int nedges,
        bool (*vertexEQ)(T &, T &),
        string (*vertex2str)(T &))
    {
        // TODO
        DGraphModel<T> *a = new DGraphModel<T>(vertexEQ, vertex2str);
        for (int i = 0; i < nvertices; i++)
        {
            a->add(vertices[i]);
        }
        for (int i = 0; i < nedges; i++)
        {
            a->connect(edges[i].from, edges[i].to, edges[i].weight);
        }
        return a;
    }
};

#endif /* DGRAPHMODEL_H */
