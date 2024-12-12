/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   UGraphModel.h
 * Author: LTSACH
 *
 * Created on 24 August 2020, 15:16
 */

#ifndef UGRAPHMODEL_H
#define UGRAPHMODEL_H

#include "graph/AbstractGraph.h"

//////////////////////////////////////////////////////////////////////
///////////// UGraphModel: Undirected Graph Model ////////////////////
//////////////////////////////////////////////////////////////////////

template <class T>
class UGraphModel : public AbstractGraph<T>
{
private:
public:
    // class UGraphAlgorithm;
    // friend class UGraphAlgorithm;

    UGraphModel(
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
        if (!fromNode->equals(toNode))
        {
            toNode->connect(fromNode, weight);
        }
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
            if (!fromNode->equals(toNode))
            {
                toNode->removeTo(fromNode);
            }
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
            if (fromNode->equals(toNode))
            {
                fromNode->removeTo(toNode);
            }
            else
            {
                fromNode->removeTo(toNode);
                toNode->removeTo(fromNode);
            }
        }
        if (!this->nodeList.removeItem(fromNode))
        {
            throw std::runtime_error("Failed to remove vertex from nodeList");
        }
        delete fromNode;
    }
    static UGraphModel<T> *create(
        T *vertices, int nvertices, Edge<T> *edges, int nedges,
        bool (*vertexEQ)(T &, T &),
        string (*vertex2str)(T &))
    {
        // TODO
        UGraphModel<T> *a = new UGraphModel(vertexEQ, vertex2str);
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

#endif /* UGRAPHMODEL_H */
