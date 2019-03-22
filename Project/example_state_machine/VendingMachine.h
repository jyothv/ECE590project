#include <iostream>
#include <chrono>
#include "elma.h"

using namespace elma;
//! 'VendingMachineState' that inherits from 'State'
class VendingMachineState : public State {
public:
    //! Constructor that takes a name for the VendingMachineState
    /*!
        \param name The name of the VendingMachineState
    */
    VendingMachineState(std::string name) : State(name) {}
    
    //! Default constructor.
    VendingMachineState() : State() {}
    void entry(const Event& e) {
    }
    void during() {} 
    void exit(const Event& e) {
    }
};

class VendingMachine : public StateMachine {
public:
    //! Constructor that takes a name for the VendingMachine
    //! \param name The name of the VendingMachine
    //! Constructors instantiate states and
    //! transitions and sets initial_state so that Event('start')
    //! sets the VendingMachine to state 'Idle'
    VendingMachine(std::string name) : StateMachine(name) {
        set_all_transition();
        set_events();
    }

    //! Default constructor.
    VendingMachine() : StateMachine() {
        set_all_transition();
        set_events();
    }

    //! Function that returns list of all the events that state machine responds to.
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
//   |                |         |          |
//   |                +---------+          |
//   |                                     |
//   |                                     V
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
        events_list.push_back("button");
        events_list.push_back("vend_complete");
        events_list.push_back("generic_fault");
        events_list.push_back("reset");
    }

    void set_all_transition(){
        set_initial(idle);
        add_transition("coin", idle, ready);
        add_transition("button", ready,vending);
       add_transition("vend_complete", vending, idle);
        add_transition("generic_fault", idle,fault);
        add_transition("generic_fault", ready,fault);
        add_transition("generic_fault", vending,fault);
        add_transition("generic_fault", fault,fault);
        add_transition("reset", fault,idle);
        
    }
    std::vector<std::string> events_list;
};