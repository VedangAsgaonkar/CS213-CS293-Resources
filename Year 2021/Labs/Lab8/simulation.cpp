#include <iostream>
#include <cstdlib>
#include <random>
#include <queue>
#include <unordered_set>
#include <functional>
#include "packet.hpp"
#include "event.hpp"
#include "startEvent.hpp"
#include "endEvent.hpp"
using namespace std;

int main(int argc, char *argv[])
{
    srand(1);
    int T = atoi(argv[1]);
    int N = atoi(argv[2]);

    priority_queue<event *, std::vector<event *>, std::function<bool(event *, event *)>> event_queue(Compare);
    unordered_set<packet *> air;

    for (int i = 0; i < N; i++)
    {
        double startTime = drand48() + rand() % ((int)(T / 100));
        packet *p = new packet(rand(), 51 + (rand() % 3950), i, (i + 1 + rand() % (N - 1)) % N);
        event *event1 = new startEvent(startTime, p);
        event_queue.push(event1);
    }

    // for(int i=0 ; i<N ; i++){
    //     std::cout << event_queue.top()->start_time << std::endl;
    //     event_queue.pop();
    // }

    for (int t = 1; t < T; t++)
    {
        std::cout << "=========================" << std::endl;
        std::cout << "TIME " << t-1 << std::endl;
        std::cout << "=========================" << std::endl;

        while (!event_queue.empty() && event_queue.top()->start_time <= t)
        {
            event *event1 = event_queue.top();
            event_queue.pop();
            event1->trigger(std::ref(air), std::ref(event_queue));
            if (event1->is_start_event)
            {
                packet *p = new packet(rand(), 51 + (rand() % 3950), event1->event_packet->start_node, (event1->event_packet->start_node + 1 + rand() % (N - 1)) % N);
                double startTime = drand48() + rand() % ((int)(T / 100));
                event *event2 = new startEvent(t + startTime, p);
                event_queue.push(event2);
            }
        }
    }
    std::cout << "END OF SIMULATION" << std::endl;
}