#ifndef _END_EVENT_H_
#define _END_EVENT_H_

#include "event.hpp"

class endEvent : public event
{
    public:
    endEvent(double start_time, packet *event_packet);
    virtual void trigger(std::unordered_set<packet*> &air, std::priority_queue<event *, std::vector<event *>, std::function<bool(event *, event *)>> &event_queue) ;
};

#endif