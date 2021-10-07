#include "startEvent.hpp"
#include <iostream>

startEvent::startEvent(double start_time, packet *event_packet) : event(start_time, event_packet)
{
    this->start_time = start_time;
    this->is_start_event = true;
    this->event_packet = event_packet;
}

void startEvent::trigger(std::unordered_set<packet *> &air, std::priority_queue<event *, std::vector<event *>, std::function<bool(event *, event *)>> &event_queue)
{
    air.insert(event_packet);
    std::cout << "Packet id " << event_packet->id << " of size " << event_packet->size << " started at node " << event_packet->start_node << " heading to node " << event_packet->end_node << " at time " << start_time << std::endl;
    if ((int)air.size() > 1)
    {
        for (auto pt : air)
        {
            pt->error = true;
        }
    }
    event *nextEndEvent = new endEvent(start_time + (event_packet->size / 1000), event_packet);
    event_queue.push(nextEndEvent);
}
