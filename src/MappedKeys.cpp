#include "MappedKeys.hpp"


MappedKeys::MappedKeys()
: left(lm::Key::Left)
, right(lm::Key::Right)
, jump(lm::Key::Space)
, crouch(lm::Key::Down)
, attack(lm::Key::A)
, _actionKeyA(*new ActionKeyA)
{
	ActionKeyA& mutActionKeyAr = const_cast<ActionKeyA&>(_actionKeyA);

	mutActionKeyAr[static_cast<short>(MappedActions::Left)] = &this->left;
	mutActionKeyAr[static_cast<short>(MappedActions::Right)] = &this->right;
	mutActionKeyAr[static_cast<short>(MappedActions::Jump)] = &this->jump;
	mutActionKeyAr[static_cast<short>(MappedActions::Crouch)] = &this->crouch;
	mutActionKeyAr[static_cast<short>(MappedActions::Attack)] = &this->attack;
}

MappedKeys::~MappedKeys()
{
	delete &_actionKeyA;
}
