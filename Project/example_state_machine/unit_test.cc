#include "gtest/gtest.h"
#include "robot.h"
#include "VendingMachine.h"
#include "stopwatch.h"
#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <json/json.h>

using namespace std::chrono;
using namespace elma;

double tolerance = 0.01;
/*!!
 * Here we use your StopWatch class to time something.
 */
TEST(Question1, StopWatch) {
    Manager m;

    Stopwatch watch = Stopwatch();

    m.schedule(watch, 10_ms)
    .init()
    .start();

    //std::cout << watch.seconds() << std::endl;
    m.emit(Event("start"));
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    //std::cout <<"expected: 0.5, got: "<< watch.seconds() << std::endl;
    EXPECT_NEAR(watch.seconds(), 0.5, tolerance);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    //std::cout <<"expected: 1.0, got: "<< watch.seconds() << std::endl;
    EXPECT_NEAR(watch.seconds(), 1.0, tolerance);
    m.stop();
    m.emit(Event("stop"));
    EXPECT_NEAR(watch.seconds(), 1.0, tolerance);
    watch.reset();
    //std::cout<<"propagate: "<<Event("reset").propagate()<<"\n";
    EXPECT_EQ(watch.seconds(), 0);

}


/*!!
 * Here we use your Robot class to give the robot
 * a little trial and see what state its in.
 *
 * Variants of tests will include more than one robot,
 * non-sense events, and varying event sequences.
 */
TEST(Question2, RobotEnvironment1) {

    // create a new robot
    Robot robot = Robot("What a very nice robot");
    // Robot robot = Robot(); // << this should also work

    // init manager
    Manager m;
    m.schedule(robot, 10_ms)
    .init()
    .start()
    .emit(Event("start"));

 
    string wander = "Wander";
    string noise = "Make Noise";
    string evade = "Evade";
    string station = "Find Recharge Station";
    string recharge = "Recharge";

    /*
     * Send signals to robot and test
     */
    //std::cout << robot.current().name() << std::endl;
    EXPECT_EQ(robot.current().name(), wander.c_str());

    //std::cout <<"before reset 1: "<< robot.current().name() << std::endl;
    m.emit(Event("reset"));
    //std::cout <<"after reset 1: "<< robot.current().name() << std::endl;

    m.emit(Event("intruder detected"));
    //std::cout << robot.current().name() << std::endl;
    EXPECT_EQ(robot.current().name(), noise.c_str());

    m.emit(Event("proximity warning"));
    //std::cout << robot.current().name() << std::endl;
    EXPECT_EQ(robot.current().name(), evade.c_str());

    m.emit(Event("battery full"));
    //std::cout << robot.current().name() << std::endl;
    EXPECT_EQ(robot.current().name(), evade.c_str());
    //std::cout << robot.to_json().dump(4) << std::endl;
   //json j = robot.to_json();
   //std::cout <<"before reset 2: "<< robot.current().name() << std::endl;
    m.emit(Event("reset"));
    //std::cout <<"after reset 2: "<< robot.current().name() << std::endl;
    
    //std::cout <<"before reset 3: "<< robot.current().name() << std::endl;
    m.emit(Event("reset"));
    //std::cout <<"after reset 3: "<< robot.current().name() << std::endl;
   
    m.emit(Event("battery low"));
    //std::cout << robot.current().name() << std::endl;
    EXPECT_EQ(robot.current().name(), station.c_str());
   
    m.emit(Event("found recharge station"));
    //std::cout << robot.current().name() << std::endl;
    m.emit(Event("battery full"));
    //std::cout << robot.current().name() << std::endl;
    EXPECT_EQ(robot.current().name(), wander.c_str());

    m.emit(Event("intruder detected"));
    //std::cout << robot.current().name() << std::endl;
    EXPECT_EQ(robot.current().name(), noise.c_str());

}


TEST(TestVend, VendingMachineOP) {

    // create a new robot
    VendingMachine vm = VendingMachine("What a very nice robot");
    // Robot robot = Robot(); // << this should also work

    // init manager
    Manager m;
    m.schedule(vm, 10_ms)
    .init()
    .start()
    .emit(Event("coin"));

 
    string idle = "Idle";
    string ready = "Ready";
    string vending = "Vending goodies";
    string fault = "Machine at Fault";
    //string reset = "Machine Reset";

    /*
     * Send signals to vm and test
     */
    //std::cout << vm.current().name() << std::endl;
    EXPECT_EQ(vm.current().name(), ready.c_str());

    //std::cout <<"before reset 1: "<< vm.current().name() << std::endl;
    m.emit(Event("reset"));
    //std::cout <<"after reset 1: "<< vm.current().name() << std::endl;

    m.emit(Event("generic_fault"));
    //std::cout << vm.current().name() << std::endl;
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
    

}


TEST(Question4, WatchPriority) {
class Print : public Process {
public:
    Print() : Process() {}
    void init() {
        watch("clicked", [this](Event& e) {
        std::cout<<"I'm handler A."<<"\n";
        },2);
        watch("clicked", [this](Event& e) {
        std::cout<<"I'm handler B."<<"\n";
        },1);
        watch("clicked", [this](Event& e) {
        std::cout<<"I'm handler C."<<"\n";
        },1);
    }
    void start(){}          
    void stop(){}          
    void update() {}
   
    };
Print print= Print();
Manager m;
    m.schedule(print, 10_ms)
    .init()
    .start()
    .emit(Event("clicked"));
     
}
