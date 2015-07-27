#ifndef BOX_SET_HPP
#define BOX_SET_HPP

#include <unordered_map>
#include <Lums>

class BoxSet
{
public:
    void    loadBinary(const lm::BObject& object);
    const lm::Rect2f& boxes(size_t move, size_t action);

private:
    std::unordered_map<size_t, std::unordered_map<size_t, lm::Rect2f>>    _boxes;
};

using BoxProvider = lm::Provider<BoxSet>;

#endif