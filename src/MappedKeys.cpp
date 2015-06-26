#include "MappedKeys.hpp"


namespace
{
	void
	initActionKeyArray (MappedKeys& that, ActionKeyA& mutActionKeyAr)
	{
		mutActionKeyAr[static_cast<short>(MappedActions::Left)] = &that.left;
		mutActionKeyAr[static_cast<short>(MappedActions::Right)] = &that.right;
		mutActionKeyAr[static_cast<short>(MappedActions::Jump)] = &that.jump;
		mutActionKeyAr[static_cast<short>(MappedActions::Crouch] = &that.crouch;
		mutActionKeyAr[static_cast<short>(MappedActions::Attack)] = &that.attack;
	}
}

MappedKeys::MappedKeys()
: left(lm::Key::Left)
, right(lm::Key::Right)
, jump(lm::Key::Space)
, crouch(lm::Key::Down)
, attack(lm::Key::A)
, _actionKeyA(*new ActionKeyA)
{
	initActionKeyArray(*this, const_cast<ActionKeyA&>(_actionKeyA));	
}

MappedKeys::~MappedKeys()
{
	delete &_actionKeyA;
}
