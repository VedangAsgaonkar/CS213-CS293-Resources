#include "endEvent.hpp"
#include <iostream>

endEvent::endEvent(double start_time, packet *event_packet) : event(start_time, event_packet)
{
    this->start_time = start_time;
    this->is_start_event = false;
    this->event_packet = event_packet;
}

void endEvent::trigger(std::unordered_set<packet*> &air, std::priority_queue<event *, std::vector<event *>, std::function<bool(event *, event *)>> &event_queue)
{
    air.erase(event_packet);
    std::cout << "Packet id " << event_packet->id << " of size " << event_packet->size << " reached at node "<< event_packet->end_node << " from node " << event_packet->start_node << " at time " << start_time << " with error status " << event_packet->error << std::endl;
}
