#pragma once

#include <exception>

class bad_graph_node: public std::exception
{
    virtual const char* what() const throw()
    {
        return "Graph node error!";
    }
};

class bad_graph_edge: public std::exception
{
    virtual const char* what() const throw()
    {
        return "Graph edge error!";
    }
};
