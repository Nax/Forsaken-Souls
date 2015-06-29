#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <unordered_map>
#include <Lums>

class Animation
{
public:
    struct Data
    {
        size_t  start;
        size_t  length;
        size_t  speed;
        bool    repeat;
    };

    Animation();
    void       loadBinary(const lm::BObject& object);
    Data&      animation(size_t move, size_t action);
    ~Animation();

private:
    std::unordered_map<size_t, std::unordered_map<size_t, Data>>    _animations;
};

using AnimationProvider = lm::Provider<Animation>;

#endif
