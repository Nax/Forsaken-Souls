#ifndef BODY_HPP
#define BODY_HPP

#include <unordered_map>
#include <Lums>

class Body
{
public:
    struct Data
    {
        lm::Vector2f    speed;
        lm::Vector2f    impulse;
    };

    void            loadBinary(const lm::BObject& object);
    Data&           body(size_t move, size_t action);

private:
    std::unordered_map<size_t, std::unordered_map<size_t, Data>>    _bodies;
};

using BodyProvider = lm::Provider<Body>;

#endif
