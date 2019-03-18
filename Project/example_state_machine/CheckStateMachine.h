#include <iostream>
#include <chrono>
#include "elma.h"

using namespace elma;

bool property(StateMachine& sm, const Event& et){
        
        std::vector<Transition> trans = sm.get_transitions();
        bool valid = false;
        State* curr = sm.current();
        for (auto transition : _transitions ) {
            if(transition.event_name() == et && transition.from().id() == curr->id){
                valid |= True;

            }
        }
        
        return valid;
    }
    
bool check_condition(std::vector<std::string> event_sequence, StateMachine& sm,bool (*f)(StateMachine&, const Event&)){
        bool result;
        std::string temp;
        for(int i=0; i<event_sequence.size(); i++) {
            temp = event_sequence[i];
            result &= f(sm, Event(temp));
        //std::cout<<"In CSM: "<<event_sequence[i]<<std::endl;
        }
        return result;
    }


