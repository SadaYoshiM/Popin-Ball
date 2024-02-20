#include "Laser.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Game.h"
#include "CircleComponent.h"
#include "Asteroid.h"

Laser::Laser(Game* game)
	:Actor(game)
	,mDeathTimer(1.0f)
{
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Laser.png"));

	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(800.0f);
	mc->SetReflect(false);
	this->SetVelocity(800.0f, Math::PiOver2);

	mCircle = new CircleComponent(this);
	mCircle->SetRadius(11.0f);
}

void Laser::UpdateActor(float deltaTime) {
	mDeathTimer -= deltaTime;
	if (mDeathTimer <= 0.0f) {
		SetState(EDead);
	}
	else {
		for (auto ast : GetGame()->GetAsteroids()) {
			if (Intersect(*mCircle, *(ast->GetCircle()))) {
				SetState(EDead);
				ast->SetState(EDead);
				break;
			}
		}
	}
	Vector2 pos = this->GetPosition();
	if (pos.x <= 0.0f || pos.x >= 1024.0f || pos.y <= 0.0f || pos.y >= 768.0f) {
		SetState(EDead);
	}
}