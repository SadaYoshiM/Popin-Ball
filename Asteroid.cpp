#include "Asteroid.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "InputComponent.h"
#include "CircleComponent.h"
#include "Random.h"
#include "Game.h"

Asteroid::Asteroid(Game* game, bool playable)
	:Actor(game)
	,mCircle(nullptr)
{
	Vector2 randPos = Random::GetVector(Vector2(31.0f, 0.0f), Vector2(993.0f, 0.0f));
	SetPosition(randPos);
	SetRotation(Random::GetFloatRange(-Math::Pi / 12, Math::Pi / 12));
	SetVelocity(GetRotation());
	SetPlayable(playable);

	SpriteComponent* sc = new SpriteComponent(this);
	if (playable) {
		sc->SetTexture(game->GetTexture("Assets/Asteroid_P.png"));
	}
	else {
		sc->SetTexture(game->GetTexture("Assets/Asteroid.png"));
	}

	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(120.0f);
	mc->SetHorizontalMoveSpeed(0.0f);
	mc->SetVerticalMoveSpeed(0.0f);
	mc->SetReflect(true);
	mc->SetPlayable(playable);
	if (playable) {
		InputComponent* ic = new InputComponent(this);
		ic->SetMoveRightKey(SDL_SCANCODE_L);
		ic->SetMoveLeftKey(SDL_SCANCODE_J);
		ic->SetMoveUpperKey(SDL_SCANCODE_I);
		ic->SetMoveDownKey(SDL_SCANCODE_K);
		ic->SetHorizontalMoveSpeed(1.5f);
		ic->SetVerticalMoveSpeed(1.2f);
		ic->SetMaxMoveSpeed(200.0f);
	}
	
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(40.0f);

	game->AddAsteroid(this);
}

Asteroid::~Asteroid() {
	GetGame()->RemoveAsteroid(this);
}