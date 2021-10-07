#ifndef _EVENT_H_
#define _EVENT_H_

#include <unordered_set>
#include <queue>
#include <vector>
#include <functional>
#include "packet.hpp"

class event
{
public:
    double start_time;
    bool is_start_event;
    packet *event_packet;
    event(double start_time, packet *event_packet);
    virtual void trigger(std::unordered_set<packet *> &air, std::priority_queue<event *, std::vector<event *>, std::function<bool(event *, event *)>> &event_queue) = 0;
};

bool Compare(event *first, event *second);

#endif