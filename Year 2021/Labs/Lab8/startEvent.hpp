#ifndef _START_EVENT_H_
#define _START_EVENT_H_

#include "event.hpp"
#include "endEvent.hpp"

class startEvent : public event
{
    public:
    startEvent(double start_time, packet *event_packet);
    virtual void trigger(std::unordered_set<packet*> &air,std::priority_queue<event *, std::vector<event *>, std::function<bool(event *, event *)>> &event_queue) ;
};

#endif
