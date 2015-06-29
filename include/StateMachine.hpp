#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

#include <cstdlib>
#include <unordered_map>
#include <Lums>

class StateMachine
{
public:
    StateMachine();
    void    loadBinary(const lm::BObject& object);
    size_t  switchMove(size_t move, size_t action, size_t message);
    size_t  switchAction(size_t action, size_t message);
    ~StateMachine();

private:
    std::unordered_map<size_t, std::unordered_map<size_t, std::unordered_map<size_t, size_t>>>   _moves;
    std::unordered_map<size_t, std::unordered_map<size_t, size_t>>                               _actions;
};

using   StateMachineProvider = lm::Provider<StateMachine>;

#endif