#include <iostream>
#include <chrono>
#include "elma.h"

using namespace elma;
using namespace std::chrono;
typedef std::chrono::duration<double,std::ratio<1,1>> seconds_type;

class Stopwatch : public Process {
public:
    Stopwatch() : Process("Stopwatch") {
        watch_running=false;
        _tot_time_elapsed = high_resolution_clock::duration::zero();
        _time_elapsed =high_resolution_clock::duration::zero();
        _sw_start_time = {};
    }
    void init() {}
    void start();              // starts the timer
    void stop();               // stops the timer
    void reset();              // sets stopwatch to zero
    void update() {}
    double seconds(); 
  private:
    bool watch_running;
    high_resolution_clock::time_point _sw_start_time;
    high_resolution_clock::duration _tot_time_elapsed;
    high_resolution_clock::duration _time_elapsed; 
};

class StopWatchUser: public Process {
    public: 
    StopWatchUser() : Process() {}
    void init() {}
    void start() {}
    /*void update() { 
        std::cout << "switch at " << milli_time() << "\n";
        emit(Event("switch"));
    }*/
    void stop() {}
};