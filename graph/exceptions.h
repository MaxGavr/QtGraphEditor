#pragma once

#include <exception>

class bad_graph_node: public std::exception
{
    virtual const char* what() const throw()
    {
        return "Cannot add new node!";
    }
};

class bad_graph_edge: public std::exception
{
    virtual const char* what() const throw()
    {
        return "Cannot add new edge!";
    }
};
