#include <iostream>
#include "elma.h"
//using nlohmann::json; 
#include <set>

namespace elma {

    int State::_id_counter = 0;

    StateMachine& StateMachine::set_initial(State& s) {
        _initial = &s;
        return *this;
    }

    StateMachine& StateMachine::add_transition(string event_name, State& from, State& to) {
        _transitions.push_back(Transition(event_name, from, to));
        to._state_machine_ptr = this;
        from._state_machine_ptr = this;
        return *this;
    }

    void StateMachine::init() {
        for (auto transition : _transitions ) {
            watch(transition.event_name(), [this, transition](Event& e) {
                if ( _current->id() == transition.from().id() ) {
                    _current->exit(e);
                    _current = &transition.to();
                    _current->entry(e);
                    if ( !_propagate ) {
                      e.stop_propagation();
                    }
                }
            });
        }
    }

    void StateMachine::start() {
        if ( _initial == NULL ) { 
            throw(Exception("State machine started without an initial state (call set_initial(...) first)"));
        }
        _current = _initial;
        _current->entry(Event("start"));
    }

    void StateMachine::update() {
        _current->during();
    }

    void StateMachine::stop() {}
    json StateMachine::to_json(){
        string this_name = name();
        json j ;
        j["name"] = this_name;   
        json transition_array, state_arr;
        std::set<string> myset;
        std::set<string>::iterator it;
        for (auto transition : _transitions ) {
            string from_ = transition.from().name()  ;
            string to_ = transition.to().name() ;
            string eve_ =transition.event_name() ;
            json t = {{"from", from_},{"to", to_} ,{"when", eve_}};
            transition_array.push_back(t);
            myset.insert(from_);
            myset.insert(to_);
        }
        for (it=myset.begin(); it!=myset.end(); ++it){
            state_arr.push_back(*it);
        }
        j["states"]=state_arr;
        j["transitions"]= transition_array;
        return j;
}

vector<Transition> StateMachine::get_transitions(){
    return _transitions;
}
};