#include <iostream>
#include <chrono>
#include "elma.h"

using namespace elma;

/*!
 * This is an internally used by Robot. We won't be testing this class.
 */
class RobotState : public State {
public:
    RobotState(std::string name) : State(name) {}
    RobotState() : State() {}
    void entry(const Event& e) {
       //std::cout<<"entering: "<<e.name()<<"\n";
        
    }
    void during() {} 
    void exit(const Event& e) {
       //std::cout<<"exit: "<<e.name()<<"\n";
        
    }
    /*
     * Question 2: define a 'RobotState' that inherits from 'State'
     * Hint 1: you'll need to implement the 'virtual' methods and inherit both of
     * the 'State' constructors.
     */
};

class Robot : public StateMachine {
public:
    Robot(std::string name) : StateMachine(name) {
        set_all_transition();
        set_events();
    }
    Robot() : StateMachine() {
        set_all_transition();
        set_events();
    }
    std::vector<std::string> get_events_list(){
        return events_list;
    } 

    std::vector<Transition> get_robot_transitions(){
     _robot_transitions  = this->get_transitions();

        return _robot_transitions;
    } 

    /*
     * Implement contructors. Constructors should instantiate states
     * and transitions AND should set initial_state so that Event('start')
     * sets the Robot to state 'Wander'
     *
     * Look at code for StateMachine.h and in examples and elma/example if you need help.
     *
     * States should have the EXACT names:
     * "Recharge"
     * "Wander"
     * "Find Recharge Station"
     * "Evade"
     *  "Make Noise"
     *
     * Robot should respond to events with the EXACT names:
     * "found recharge station"
     * "battery full"
     * "battery low"
     * "start"
     * "reset"
     * "intruder detected"
     * "proximity warning"
     */

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
        add_transition("reset", makeNoise, wander);
        add_transition("reset", evade, makeNoise);
    }
    std::vector<std::string> events_list;
    std::vector<Transition> _robot_transitions;
};