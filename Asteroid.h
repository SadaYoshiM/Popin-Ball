#pragma once
#include "Actor.h"

class Asteroid :public Actor {
public:
	Asteroid(class Game* game, bool playable);
	~Asteroid();

	class CircleComponent* GetCircle() { return mCircle; }

private:
	class CircleComponent* mCircle;
};