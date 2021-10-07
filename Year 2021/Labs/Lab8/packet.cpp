#include "packet.hpp"

packet::packet(int id, int size,int start_node, int end_node)
{
    this->id = id;
    this->size = size;
    this->error = false;
    this->start_node = start_node;
    this->end_node = end_node;
}