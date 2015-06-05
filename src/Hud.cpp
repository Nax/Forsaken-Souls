#include <Lums>
#include "Hud.hpp"
#include "Player.hpp"

void
hud::draw(const Player& player)
{
	// lm::VertexArrayc<12> va;
	// const float hp = static_cast<float>(player.hp()) / player.hpMax();

	// va.push(25, 25, 1.0f, 1.0f, 1.0f);
	// va.push(25 + 210, 25, 1.0f, 1.0f, 1.0f);
	// va.push(25 + 210, 25 + 20, 1.0f, 1.0f, 1.0f);
	// va.push(25, 25 + 20, 1.0f, 1.0f, 1.0f);

	// va.push(27, 27, 0.0f, 0.0f, 0.0f);
	// va.push(27 + 206, 27, 0.0f, 0.0f, 0.0f);
	// va.push(27 + 206, 27 + 16, 0.0f, 0.0f, 0.0f);
	// va.push(27, 27 + 16, 0.0f, 0.0f, 0.0f);

	// va.push(27, 27, 0.0f, 0.8f, 0.0f);
	// va.push(27 + 206 * hp, 27, 0.0f, 0.8f, 0.0f);
	// va.push(27 + 206 * hp, 27 + 16, 0.0f, 0.8f, 0.0f);
	// va.push(27, 27 + 16, 0.0f, 0.8f, 0.0f);
	// va.draw(GL_QUADS);
}
