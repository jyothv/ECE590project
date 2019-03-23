#include <iostream>
#include <chrono>
#include "elma.h"

using namespace elma;

//! Function that generates random sequence of events for the given state machine.
//! \param List of events that state machine responds to.
//! \return Random sequence of events.
std::vector<std::string> generate_random_sequence(std::vector<std::string> events_list ){
    int length = events_list.size();
    std::vector<std::string> rand_seq;
    int seq_index;
    for (int i=0; i<(length*2); i++)
    {
        seq_index = rand() %length;
        rand_seq.push_back(events_list[seq_index]);
    }
    return rand_seq;
}
