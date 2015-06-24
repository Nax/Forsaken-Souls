#ifndef MAPPED_KEYS_HPP
#define MAPPED_KEYS_HPP

#include <Lums>

class MappedKeys : public lm::Singleton<MappedKeys>
{
public:
	MappedKeys();
	~MappedKeys();

	lm::Key		left;
	lm::Key		right;
	lm::Key		jump;
	lm::Key		crouch;
	lm::Key		attack;
};

#endif