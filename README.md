# Testing safety of Finite State Machines

**Introduction**:

*Finite State Machine*: A finite state machine (FSM) is a method to model a system's dynamic behavior. The model is composed of a finite number of states, of which one of the state is designated as the start or initial state. The initial state is the state that the FSM begins when it is instantiated. The transition from the initial state and between the set of states is determined by occurence of a set of events. From one state to the next, an event may be processed to cause a transition or ignored.

A finite state machine (FSM) M is a quintuple
                               M = (I, O, S, δ, λ)
where I, O, and S are finite and nonempty sets of input symbols, output symbols, and states,
respectively.
δ: S×I → S is the state transition function;
λ: S×I → O is the output function.

When the machine is in a current state s in S and receives an input a from I it moves to the next state specified by δ(s, a) and produces an output given by λ(s, a).

**Objective**:

*Testing safety of Finite State Machine*: To ensure reliability and to verify functionality of the system we will test finite state machines. It is crucial to ensure the system goes into a predefined state on occurrence of a particular event. This guarantees safe operation of the system under all circumstances. We will do a *conformance testing* of the system. Given a specification of a  finite state machine, for which we have its transition diagram, and an implementation, we will test whether the implementation conforms to the specification. We will also generate a *checking sequence* which will help in fault detection in the system. 

We will take the examples of Robot and vending machine to test and confirm the safety. Random sequence of events will be produced to test the safe operation of the system.

*Steps for testing*: In a given sequence of events for each event 
1. Identify the current state.
2. Has event triggered change in state?
3. Determine the new state of the system?
4. Is the new state as expected after the test?
Did the system change its states as expected by the given sequence of events?

**Steps involved in the project and Milestone**: 
1. First step is to create a Unittest with random sequence of events for Robot, Microwave and vending machine.

Below is the state machine of a vending machine. The below state machine will be tested for safe operation.
![Image of state machine](https://github.com/jyothv/ECE590project/blob/master/VendingMachine.PNG)

*New State Machine: Project/example_state_machine/VendingMachine.h*

- I have defined various State for the VendingMachine.Like IDLE, READY, VENDING and FAULT.
- I have created responses to various events. Like COIN, BUTTON, VEND_COMPLETE, GENERIC_FAULT, RESET.
- I have added transition from one state to other state.

*New header file with function to generate random sequence of events: Project/example_state_machine/RandomSequence.h*
*New unit_test.cc: Tests the safety of state machines. Test case to check robot and Vending machine*

2. Create a class and methods required to receive sequence as arguments and  returns true or false after each step along the sequence.
Target 

*New Class CheckStateMachine: Project/example_state_machine/CheckStateMachine.h, CheckStateMachine.cc*

- Class has two functions check_condition and property.
- bool check_condition(std::vector<std::string> event_sequence, StateMachine& sm): Loops through random sequence of events that the machine responds to and calls bool property(StateMachine& sm, const Event et) for every event. Returns true if all the events in the sequence are safe, false if not.
- bool property(StateMachine& sm, const Event et): Takes state machine under test and one event at a time. Checks the current state and sees if its safe to transition next state. If its safe return true, else return false.

3. Add necessary comments and details required to generate API documentation for the project.
- Added comments with description for class, methods, details of arguments and return type.

4. Integrate unittest with rest of the code. Run verification tests.
- Tested both robot and vending machine state machine. 

5. Created A Dockerized instance of your code on Dockerhub. Submit a report with test results and observations.

*To run the tests*

docker run -v "$PWD:/source" -it jyothv/jyothv_finalproject:createimage bash <br/>
cd example_state_machine/ <br/>
make <br/>
 ./bin/test <br/>

*Results*

**Robot**

Normal sequence of events for robot:
start-->intruder detected-->proximity warning-->battery low-->found recharge station-->battery full-->reset--> <br/>
The sequence of events is **SAFE** for robot operation. <br/>

Random sequence of events for robot:
intruder detected-->found recharge station-->battery low-->intruder detected-->battery full-->intruder detected-->found recharge station--> <br/>
The sequence of events is **UNSAFE** for robot operation.<br/>

**Vending Machine**

Normal sequence of events for Vending Machine: <br/>
coin-->button-->vend_complete-->generic_fault-->reset--> <br/>
The sequence of events is **SAFE** for Vending Machine operation. <br/>

Random sequence of events for Vending Machine: <br/>
coin-->button-->button-->vend_complete-->generic_fault--> <br/>
The sequence of events is **UNSAFE** for Vending Machine operation. <br/>


**Resources**:
* [Elma](https://klavins.github.io/ECEP520/index.html) will be used a base to develop a library for checking the safety of finite state machines.
* Unittest will be used to generate random sequence for each system.
* The documentation for the project will be automatically generated using Doxygen. For all the classes and methods description will be generated. This will help user to understand purpose of the function, give information on arguments required and return types.

**References**:

* The [Elma](https://klavins.github.io/ECEP520/index.html) process manager
* Prof. Klavins' [Dockerhub](https://cloud.docker.com/u/klavins/repository/docker/klavins/ecep520) account
* [Github](https://github.com/) for version controlling all of our code. 
* Visual Studio [Code](https://code.visualstudio.com/) .
* [Google Test](https://github.com/google/googletest) unit testing environment
* [Docker](https://www.docker.com/) container creation and management system
* [C++](http://www.cplusplus.com/) language documentation
* [Doxygen](http://www.doxygen.org/) API documentation generator
* Principles and methods of testing finite state machines - By David Lee, Mihalis Yannakakis
* How to Unittest finite state machines - By Urs Enzler 
