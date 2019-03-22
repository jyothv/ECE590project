#include "gtest/gtest.h"
#include "robot.h"
#include "VendingMachine.h"
#include "stopwatch.h"
#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <json/json.h>
#include "RandomSequence.h"
#include "CheckStateMachine.h"

using namespace std::chrono;
using namespace elma;

/*!!
 * Here we use Vending Machine class to give the machine
 * a little trial and see if the machine responds with correct transition
 * and states for a give event.
 */
TEST(TestVend, VendingMachineOP) {
    std::cout<<"Test if the state machine works fine by emitting events"<<std::endl;
    VendingMachine vm = VendingMachine("What a very nice robot");
    Manager m;
    m.schedule(vm, 10_ms)
    .init()
    .start()
    .emit(Event("coin"));

    string idle = "Idle";
    string ready = "Ready";
    string vending = "Vending goodies";
    string fault = "Machine at Fault";

    /*
     * Send signals to vm and test
     */
    EXPECT_EQ(vm.current().name(), ready.c_str());
    m.emit(Event("reset"));
    m.emit(Event("generic_fault"));
    EXPECT_EQ(vm.current().name(), fault.c_str());
    m.emit(Event("reset"));
    EXPECT_EQ(vm.current().name(), idle.c_str());
    m.emit(Event("coin"));
    EXPECT_EQ(vm.current().name(), ready.c_str());
    m.emit(Event("button"));
    EXPECT_EQ(vm.current().name(), vending.c_str());
    m.emit(Event("vend_complete"));
    EXPECT_EQ(vm.current().name(), idle.c_str());
    m.emit(Event("coin_return"));
    EXPECT_EQ(vm.current().name(), idle.c_str());
    std::cout<<std::endl;
}

/*!!
 * Here we use Robot class to check the safety of the state machine.
 * First we get the list of all the events that the state machine responds to.
 * Next we call generate_random_sequence() to generate a random sequence of events.
 * Next the sequence of operation is tested safe operation using check_condition()
 */

TEST(rand, RandomSeqGenRobot) {
    Robot robot = Robot("Robot");
    std::vector<std::string> seq_ar= robot.get_events_list();
    std::vector<std::string> rand_seq= generate_random_sequence(seq_ar);
    
    std::cout<<"Normal sequence of events for robot:"<<std::endl;
    for(int i =0; i< seq_ar.size();i++){
        std::cout<<seq_ar[i]<<"-->";
    }
    std::cout<<std::endl;
    CheckStateMachine csm;
    csm.init();
    bool result1 = csm.check_condition(seq_ar , robot );
    if(result1) {
        std::cout<<"The sequence of events is SAFE for robot operation. "<<std::endl;
    } 
    else{
        std::cout<<"The sequence of events is UNSAFE for robot operation. "<<std::endl;
    }
    std::cout<<std::endl;
    EXPECT_EQ (result1, 1);
    std::cout<<"Random sequence of events for robot:"<<std::endl;
    for(int i =0; i< rand_seq.size();i++){
        std::cout<<rand_seq[i]<<"-->";
    }
    std::cout<<std::endl;
    CheckStateMachine csm2;
    csm2.init();
    bool result2 = csm2.check_condition(rand_seq, robot );
    if(result2) {
        std::cout<<"The sequence of events is SAFE for robot operation. "<<std::endl;
    } 
    else{
        std::cout<<"The sequence of events is UNSAFE for robot operation. "<<std::endl;
    }
    std::cout<<std::endl;
    EXPECT_EQ (result2, 0);
   
}

/*!!
 * Here we use VendingMachine class to check the safety of the state machine.
 * First we get the list of all the events that the state machine responds to.
 * Next we call generate_random_sequence() to generate a random sequence of events.
 * Next the sequence of operation is tested safe operation using check_condition()
 */

TEST(rand, RandomSeqGenVM) {
    VendingMachine vm = VendingMachine("My cool vm");
    std::vector<std::string> seq_ar= vm.get_events_list();
    std::vector<std::string> rand_seq= generate_random_sequence(seq_ar);

    std::cout<<"Normal sequence of events for Vending Machine:"<<std::endl;
    for(int i =0; i< seq_ar.size();i++){
        std::cout<<seq_ar[i]<<"-->";
    }
    std::cout<<std::endl;

    CheckStateMachine csm;
    csm.init();
    bool result1 = csm.check_condition(seq_ar, vm );
    if(result1) {
        std::cout<<"The sequence of events is SAFE for Vending Machine operation. "<<std::endl;
    } 
    else{
        std::cout<<"The sequence of events is UNSAFE for Vending Machine operation. "<<std::endl;
    }
    std::cout<<std::endl;
    EXPECT_EQ (result1, 1);

    std::cout<<"Random sequence of events for Vending Machine:"<<std::endl;
    for(int i =0; i< rand_seq.size();i++){
         std::cout<<rand_seq[i]<<"-->";
    }
    std::cout<<std::endl;
    
    CheckStateMachine csm2;
    csm2.init();
    bool result2 = csm2.check_condition(rand_seq, vm );
    if(result2) {
        std::cout<<"The sequence of events is SAFE for Vending Machine operation. "<<std::endl;
    } 
    else{
        std::cout<<"The sequence of events is UNSAFE for Vending Machine operation. "<<std::endl;
    }
    std::cout<<std::endl;
    EXPECT_EQ (result2, 0);
}