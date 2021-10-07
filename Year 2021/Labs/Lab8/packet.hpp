#ifndef _PACKET_H_
#define _PACKET_H_

class packet
{
public:
    int id;
    int size;
    bool error;
    int start_node;
    int end_node;
    packet(int id, int size, int start_node, int end_node);
};

#endif