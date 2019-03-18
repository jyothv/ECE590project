#include <iostream>
#include <chrono>
#include "elma.h"

using namespace elma;

class VendingMachineState : public State {
public:
    VendingMachineState(std::string name) : State(name) {}
    VendingMachineState() : State() {}
    void entry(const Event& e) {
       //std::cout<<"entering: "<<e.name()<<"\n";
    }
    void during() {} 
    void exit(const Event& e) {
       //std::cout<<"exit: "<<e.name()<<"\n";
    }
};

class VendingMachine : public StateMachine {
public:
    VendingMachine(std::string name) : StateMachine(name) {
        set_all_transition();
        set_events();
    }
    VendingMachine() : StateMachine() {
        set_all_transition();
        set_events();
    }
    std::vector<std::string> get_events_list(){
        return events_list;
    } 
   
//     * The initial state of the state machine should be IDLE
//     * The function should output the current state of the state machine
//     * Unexpected input should not cause a state transition
//     * GENERIC_FAULT may be received in any state and should put the machine
//       into the FAULT state
//
//
//          COIN      +---------+
//   +--------------->|         |   BUTTON
//   |                |  READY  | ---------+       
//   |    COIN_RETURN |         |          |
//   |   +----------- +---------+          |
//   |   |                                 |
//   |   V                                 V
// +---------+                        +---------+
// |         |     VEND_COMPLETE      |         |
// |  IDLE   |<-----------------------| VENDING |
// |         |                        |         |
// +---------+                        +---------+
//      ^
//      |         RESET            +---------+
//      +--------------------------|         |
//                                 |         |
//                GENERIC_FAULT    |  FAULT  |
//             +------------------>|         |
//                                 +---------+
//

private:
    VendingMachineState idle = VendingMachineState("Idle");
    VendingMachineState ready= VendingMachineState("Ready");
    VendingMachineState vending= VendingMachineState("Vending goodies");
    VendingMachineState fault= VendingMachineState("Machine at Fault");

    void set_events(){

        events_list.push_back("coin"); 
        events_list.push_back("coin_return");
        events_list.push_back("button");
        events_list.push_back("vend_complete");
        events_list.push_back("generic_fault");
        events_list.push_back("reset");
    }

    void set_all_transition(){
        set_initial(idle);
        add_transition("coin", idle, ready);
        add_transition("coin_return", ready,idle);
        add_transition("button", ready,vending);
        add_transition("vend_complete", vending, idle);
        add_transition("generic_fault", ready,fault);
        add_transition("generic_fault", idle,fault);
        add_transition("generic_fault", vending,fault);
        add_transition("generic_fault", fault,fault);
        add_transition("reset", fault,idle);
        
    }
    std::vector<std::string> events_list;
};