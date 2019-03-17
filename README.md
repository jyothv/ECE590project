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

We will take the examples of Robot, Microwave and vending machine to test and confirm the safety. Random sequence of events will be produced to test the safe operation of the system.

*Steps for testing*: In a given sequence of events for each event 
1. Identify the current state.
2. Has event triggered change in state?
3. Determine the new state of the system?
4. Is the new state as expected after the test?
Did the system change its states as expected by the given sequence of events?

**Steps involved in the project and Milestone**: 
1. First step is to create a Unittest with random sequence of events for Robot, Microwave and vending machine.
Target completion date: 03/15/2019

**Progress as on 03/17/2019**:

Below is the states machine operation of a vending machine. The below state machine will be tested for safe operation.



2. Create a class and methods required to receive sequence as arguments and  returns true or false after each step along the sequence.
Target completion date: 03/17/2019
3. Add necessary comments and details required to generate API documentation for the project.
Target completion date: 03/19/2019
4. Integrate unittest with rest of the code. Run verification tests.
Target completion date: 03/21/2019
5. Submit a report with test results and observations.
Target completion date: 03/22/2019

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
