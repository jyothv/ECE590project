#include "stopwatch.h"


void Stopwatch::start(){
    watch("start", [this](Event& e) {
        watch_running = true;
        });
    _sw_start_time = high_resolution_clock::now();
   //std::cout << "starting watch "<<"\n";
}

void Stopwatch::stop(){
    watch("stop", [this](Event& e) {
        watch_running = false;
        //std::cout << "stoping watch "<<"\n";
        });
   _tot_time_elapsed += high_resolution_clock::now() - _sw_start_time;
}

void Stopwatch::reset(){
    //std::cout << "reseting watch "<<"\n";
    watch_running = false;
    _sw_start_time  = {};
    _tot_time_elapsed = _time_elapsed = high_resolution_clock::duration::zero();
}

double Stopwatch::seconds(){
    if(watch_running){
        _time_elapsed = _tot_time_elapsed+high_resolution_clock::now() - _sw_start_time;
        auto x  = seconds_type(_time_elapsed);
      //  std::cout<<"time counted w/o stop: "<<x.count()<<"\n";
        return x.count();
    }
    else {
        auto x  = seconds_type(_tot_time_elapsed);
        //std::cout<<"time counted with stop: "<<x.count()<<"\n";
        return x.count();
    }
    
    //std::cout<<"time counted: "<<x.count()<<"\n";
    
}