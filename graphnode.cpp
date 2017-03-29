#include "graphnode.h"

GraphNode::GraphNode(int i)
    : index(i)
{

}

GraphNode::GraphNode(int i, const QString& str)
    : index(i)
{
    setText(str);
}

GraphNode::~GraphNode()
{
    qDeleteAll(edges);
}

int GraphNode::getIndex() const
{
    return index;
}

void GraphNode::addEdge(GraphEdge *edge)
{
    if (edge && !edges.contains(edge))
    {
        edges.append(edge);
    }
}

void GraphNode::removeEdge(GraphEdge *edge)
{
    if (edge)
        edges.removeOne(edge);
}

void GraphNode::setText(const QString &str)
{
    text = str;
}

QString GraphNode::getText() const
{
    return text;
}
