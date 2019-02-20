#include <iostream>
#include "elma.h"

namespace elma {

    int State::_id_counter = 0;

    StateMachine& StateMachine::set_initial(State& s) {
        _initial = &s;
        return *this;
    }

    StateMachine& StateMachine::add_transition(string event_name, State& from, State& to) {
        _transitions.push_back(Transition(event_name, from, to));
        return *this;
    }

    void StateMachine::init() {
        for (auto transition : _transitions ) {
            watch(transition.event_name(), [this, transition](Event& e) {
                if ( _current->id() == transition.from().id() ) {
                    _current->exit();
                    _current = &transition.to();
                    _current->entry();
                    if ( !_propagate ) {
                      e.stop_propagation();
                    }
                }
            });
        }
    }

    void StateMachine::start() {
        _current = _initial;
        _current->entry();
    }

    void StateMachine::update() {
        _current->during();
    }

    void StateMachine::stop() {}

};