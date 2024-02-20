#include "Asteroid.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "CircleComponent.h"
#include "Random.h"
#include "Game.h"

Asteroid::Asteroid(Game* game)
	:Actor(game)
	,mCircle(nullptr)
{
	Vector2 randPos = Random::GetVector(Vector2(31.0f, 0.0f), Vector2(993.0f, 0.0f));
	SetPosition(randPos);
	SetRotation(Random::GetFloatRange(-Math::Pi / 12, Math::Pi / 12));
	SetVelocity(GetRotation());

	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Asteroid.png"));

	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(150.0f);
	mc->SetReflect(true);
	
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(40.0f);

	game->AddAsteroid(this);
}

Asteroid::~Asteroid() {
	GetGame()->RemoveAsteroid(this);
}