#include "Ship.h"
#include "SpriteComponent.h"
#include "InputComponent.h"
#include "CircleComponent.h"
#include "Asteroid.h"
#include "Game.h"
#include "Laser.h"

Ship::Ship(Game* game)
	:Actor(game)
	,mLaserCooldown(0.1f)
{
	SpriteComponent* sc = new SpriteComponent(this, 150);
	sc->SetTexture(game->GetTexture("Assets/Ship.png"));

	InputComponent* ic = new InputComponent(this);
	ic->SetMoveRightKey(SDL_SCANCODE_D);
	ic->SetMoveLeftKey(SDL_SCANCODE_A);
	ic->SetMaxMoveSpeed(200.0f);
	ic->SetReflect(false);

	mCircle = new CircleComponent(this);
	mCircle->SetRadius(20.0f);
}

void Ship::UpdateActor(float deltaTime) {
	mLaserCooldown -= deltaTime;
	for (auto ast : GetGame()->GetAsteroids()) {
		if (Intersect(*mCircle, *(ast->GetCircle()))) {
			SetState(EDead);
			break;
		}
	}
}

void Ship::ActorInput(const uint8_t* keyState) {
	if (keyState[SDL_SCANCODE_SPACE] && mLaserCooldown <= 0.0f) {
		Laser* laser = new Laser(GetGame());
		laser->SetPosition(GetPosition());
		laser->SetRotation(GetRotation());

		mLaserCooldown = 0.25f;
	}
}