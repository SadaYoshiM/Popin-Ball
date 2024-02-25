#pragma once
#include "Actor.h"

class Player_Asteroid :public Actor {
public:
	Player_Asteroid(class Game* game);

	class CircleComponent* GetCircle() { return mCircle; }

private:
	class CircleComponent* mCircle;
};