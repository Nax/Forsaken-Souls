#include "IEntity.hpp"
#include "Screen.hpp"
#include <vector>

extern std::vector<lm::VertexArrayc<4>> debugPhysics;

IEntity::IEntity()
: _mult(1.f)
{

}

void
IEntity::setAnimation(int start, int end, int frames, bool loop)
{
	_sprite.setAnimation(start, end, frames, loop);
}

void
IEntity::render(lm::SpriteBatch& sb) const
{
	for (auto& v : debugPhysics)
	{
		v.draw(GL_LINE_LOOP);
	}
	glBegin(GL_LINE_LOOP);
	glColor3ub(0, 255, 0);
	glVertex3i(position.x * 32, SCREEN_HEIGHT - position.y * 32, 0);
	glVertex3i((position.x + gEntityData[_dataId].boundingBox[static_cast<int>(_stance)][0]) * 32, SCREEN_HEIGHT - position.y * 32, 0);
	glVertex3i((position.x + gEntityData[_dataId].boundingBox[static_cast<int>(_stance)][0])* 32, SCREEN_HEIGHT - (position.y + gEntityData[_dataId].boundingBox[static_cast<int>(_stance)][1]) * 32, 0);
	glVertex3i(position.x * 32, SCREEN_HEIGHT - (position.y + gEntityData[_dataId].boundingBox[static_cast<int>(_stance)][1]) * 32, 0);
	glEnd();
	glColor3ub(255, 255, 255);

	sb.begin();
	sb.draw(_sprite);
	sb.end();
}

void
IEntity::update()
{
	_sprite.update();
	_sprite.pos.x = position.x * 32;
	_sprite.pos.y = SCREEN_HEIGHT - (position.y + 1) * 32 - _sprite.height();
}
