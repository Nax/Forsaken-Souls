#include "IEntity.hpp"
#include "Screen.hpp"
#include <vector>

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
IEntity::render(lm::SpriteBatch& sb, const Camera& camera) const
{
	const lm::Vector2f& off = camera.offset();
	const lm::Vector2f p = position - off;

	_sprite.pos.x = p.x * 32.0f;
	_sprite.pos.y = SCREEN_HEIGHT - (position.y - off.y) * 32.0f - _sprite.height();

	sb.draw(_sprite);

	glDisable(GL_TEXTURE_2D);
	glBegin(GL_LINE_LOOP);
	glColor3ub(0, 255, 0);
	glVertex3i(p.x * 32, SCREEN_HEIGHT - p.y * 32, 0);
	glVertex3i((p.x + gEntityData[_dataId].boundingBox[static_cast<int>(_stance)][0]) * 32, SCREEN_HEIGHT - p.y * 32, 0);
	glVertex3i((p.x + gEntityData[_dataId].boundingBox[static_cast<int>(_stance)][0])* 32, SCREEN_HEIGHT - (p.y + gEntityData[_dataId].boundingBox[static_cast<int>(_stance)][1]) * 32, 0);
	glVertex3i(p.x * 32, SCREEN_HEIGHT - (p.y + gEntityData[_dataId].boundingBox[static_cast<int>(_stance)][1]) * 32, 0);
	glEnd();
	glColor3ub(255, 255, 255);
}

void
IEntity::update()
{
	_sprite.update();
	_sprite.pos.x = position.x * 32;
	_sprite.pos.y = SCREEN_HEIGHT - (position.y + 1) * 32 - _sprite.height();
}
