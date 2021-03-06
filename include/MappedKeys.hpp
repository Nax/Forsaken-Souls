#ifndef MAPPED_KEYS_HPP
#define MAPPED_KEYS_HPP

#include <array>
#include <Lums>


enum struct MappedActions : short
{
	Left
	, Right
	, Jump
	, Crouch
	, Attack
	, Count
};

// As of 279e0653d196b
//
// MappedKeys instance is constructed, initialized and 
// managed by the Settings class. The Settings instance
// automatically initializes and updates the MappedKeys
// instance.

class MappedKeys
{
public:
	MappedKeys(const MappedKeys&) = delete;
	MappedKeys&	operator=(const MappedKeys&) = delete;
	~MappedKeys();

	lm::Key		left;
	lm::Key		right;
	lm::Key		jump;
	lm::Key		crouch;
	lm::Key		attack;

	lm::Key&	actionKey(MappedActions e)			{ return *_actionKeyA[static_cast<short>(e)]; }

private:
	friend class Settings;
	MappedKeys();

	using ActionKeyA = std::array<lm::Key*, static_cast<short>(MappedActions::Count)>;
	const ActionKeyA&	_actionKeyA;
};

#endif