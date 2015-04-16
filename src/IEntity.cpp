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
	const lm::Vector2f bpp = { boundingBox().x + position.x - off.x, boundingBox().y + position.y - off.y };

	_sprite.pos.x = p.x * 32.0f;
	_sprite.pos.y = SCREEN_HEIGHT - (position.y - off.y) * 32.0f - _sprite.height();

	sb.draw(_sprite);

	glDisable(GL_TEXTURE_2D);
	lm::VertexArray<4>	bb;
	glColor3ub(0, 255, 0);
	bb.push(bpp.x * 32, SCREEN_HEIGHT - bpp.y * 32);
	bb.push((bpp.x + boundingBox().w) * 32, SCREEN_HEIGHT - bpp.y * 32);
	bb.push((bpp.x + boundingBox().w) * 32, SCREEN_HEIGHT - (bpp.y + boundingBox().h) * 32);
	bb.push(bpp.x * 32, SCREEN_HEIGHT - (bpp.y + boundingBox().h) * 32);
	bb.draw(GL_LINE_LOOP);

	lm::VertexArray<4>	va;
	glColor3ub(255, 0, 0);
	va.push(_sprite.pos.x, _sprite.pos.y);
	va.push(_sprite.pos.x + _sprite.width(), _sprite.pos.y);
	va.push(_sprite.pos.x + _sprite.width(), _sprite.pos.y + _sprite.height());
	va.push(_sprite.pos.x, _sprite.pos.y + _sprite.height());
	va.draw(GL_LINE_LOOP);
	glColor3ub(255, 255, 255);
}

void
IEntity::update()
{
	_sprite.update();
	_sprite.pos.x = position.x * 32;
	_sprite.pos.y = SCREEN_HEIGHT - (position.y + 1) * 32 - _sprite.height();
}
