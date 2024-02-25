#include "Player_Asteroid.h"
#include "SpriteComponent.h"
#include "InputComponent.h"
#include "MoveComponent.h"
#include "CircleComponent.h"
#include "Random.h"
#include "Game.h"

Player_Asteroid::Player_Asteroid(Game* game)
	:Actor(game)
	,mCircle(nullptr)
{
	Vector2 randPos = Random::GetVector(Vector2(31.0f, 30.0f), Vector2(993.0f, 30.0f));
	SetPosition(randPos);
	SetRotation(Math::PiOver2);
	SetVelocity(Math::PiOver2);

	SpriteComponent* sc = new SpriteComponent(this, 150);
	sc->SetTexture(game->GetTexture("Assets/Asteroid_P.png"));

	InputComponent* ic = new InputComponent(this);
	ic->SetMoveRightKey(SDL_SCANCODE_L);
	ic->SetMoveLeftKey(SDL_SCANCODE_J);
	ic->SetJumpKey(SDL_SCANCODE_I);
	ic->SetJumpSpeed(150.0f);
	ic->SetMaxMoveSpeed(120.0f);
	ic->SetForwardSpeed(150.0f);
	ic->SetReflect(true);

	mCircle = new CircleComponent(this);
	mCircle->SetRadius(40.0f);

	game->SetPlayerAsteroid(this);
}
