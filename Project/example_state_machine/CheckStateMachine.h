#include <iostream>
#include <chrono>
#include "elma.h"

using namespace elma;

//!The class tests the safety of finite state machines.
class CheckStateMachine{

public:
//!Default constructor. 
CheckStateMachine() {}

//!Initialization method. It is called once to initialize flags to default value.
void init();

//!Check condition method. Loops through random sequence of events that the machine responds to.
bool check_condition(std::vector<std::string> event_sequence, StateMachine& sm);

//! returns if the transition is safe or not
bool property(StateMachine& sm, const Event et);

private:
bool is_initial;
State* current_state;
};

