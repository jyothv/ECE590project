#include <iostream>
#include <chrono>
#include "elma.h"
#include "CheckStateMachine.h"

using namespace elma;

//! Add a state machine whose safety of operation has to be tested.
//! \param State machine to be tested
//! \event For the given event test if the current state is correct.
//! \return True if safe, False if unsafe
bool CheckStateMachine::property(StateMachine& sm, const Event et){
         
        std::vector<Transition> trans = sm.get_transitions();
        for (auto transition : trans ) {
            if(transition.event_name()==et.name()){
                if(is_initial == true){
                    current_state =  &(transition.to() ) ; 
                    is_initial = false;
                    return true;
                    }
                else if(transition.from().id() ==current_state->id()){
                    current_state =  &(transition.to() ) ; 
                    return true;
                    }
                    
                else {
                    return false;
                    }
                }
            }
    }

//! Add a state machine whose safety of operation has to be tested.
//! \param Sequence of events that the state machine responds to.
//! \param State machine under test
//! \return True or false based on complete operation. It loops through all the event and at each step
//! calls property function to check if it is safe or not.
bool CheckStateMachine::check_condition(std::vector<std::string> event_sequence,StateMachine& sm){
        bool result = true;
        std::string temp;
        for(int i=0; i<event_sequence.size(); i++) {
            temp = event_sequence[i];
            result &= property(sm, Event(temp));
        }
        return result;
    }

//! Initialization method. Sets default value to flag.
void CheckStateMachine::init(){
   is_initial = true;
}