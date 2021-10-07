#include "event.hpp"

event::event(double start_time, packet *event_packet){

}

bool Compare(event* first, event *second){
    return first->start_time >= second->start_time;
}