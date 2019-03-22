#include <iostream>
#include <chrono>
#include "elma.h"

using namespace elma;

//! 'RobotState' that inherits from 'State'
class RobotState : public State {
public:
    //! Default constructor.
    RobotState() : State() {}
    //! Constructor that takes a name for the RobotState
    /*!
        \param name The name of the RobotState
    */
    RobotState(std::string name) : State(name) {}
    
    void entry(const Event& e) {}
    void during() {} 
    void exit(const Event& e) {
       
    }
    
};

class Robot : public StateMachine {
public:
    //! Constructor that takes a name for the Robot
    //! \param name The name of the Robot
    //! Constructors instantiate states and
    //! transitions and sets initial_state so that Event('start')
    //! sets the Robot to state 'Wander'
    Robot(std::string name) : StateMachine(name) {
        set_all_transition();
        set_events();
    }
    //! Default constructor.
    Robot() : StateMachine() {
        set_all_transition();
        set_events();
    }

    //! Function that returns list of all the events that state machine responds to.
    std::vector<std::string> get_events_list(){
        return events_list;
    } 

private:
    RobotState idle = RobotState("Idle");
    RobotState recharge= RobotState("Recharge");
    RobotState wander= RobotState("Wander");
    RobotState station= RobotState("Find Recharge Station");
    RobotState makeNoise= RobotState("Make Noise");
    RobotState evade= RobotState("Evade");

    void set_events(){
        events_list.push_back("start"); 
        events_list.push_back("intruder detected");
        events_list.push_back("proximity warning");
        events_list.push_back("battery low");
        events_list.push_back("found recharge station");
        events_list.push_back("battery full");
        events_list.push_back("reset");
    }
    
    void set_all_transition(){
        set_initial(idle);
        add_transition("start", idle, wander);
        add_transition("intruder detected",wander, makeNoise);
        add_transition("proximity warning", makeNoise, evade);
        add_transition("battery full", recharge, wander);
        add_transition("battery low", evade, station);
        add_transition("battery low", wander, station);
        add_transition("found recharge station", station, recharge);
        add_transition("reset", wander, idle);
        add_transition("reset", makeNoise, wander);
        add_transition("reset", evade, makeNoise);
    }
    std::vector<std::string> events_list;
};