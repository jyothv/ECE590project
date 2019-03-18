#include <iostream>
#include <chrono>
#include "elma.h"

using namespace elma;

std::vector<std::string> generate_random_sequence(std::vector<std::string> events_list ){
    int length = events_list.size();
    std::vector<std::string> rand_seq;
    int seq_index;
    for (int i=0; i<length; i++)
    {
        seq_index = rand() %(length -1);
        rand_seq.push_back(events_list[seq_index]);
    }
    return rand_seq;
}
std::vector<std::string> generate_wrong_sequence(std::vector<std::string> events_list ){
    int length = events_list.size();
    std::vector<std::string> rand_seq;
    int seq_index;
    for (int i=0; i<length; i++)
    {
        seq_index = rand() %(length -1);
        rand_seq.push_back(events_list[seq_index]);
    }
    rand_seq.push_back("NOTVALID1");
    rand_seq.push_back("NOTVALID2");
    return rand_seq;
}