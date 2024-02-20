#include "Component.h"
#include "Actor.h"

Component::Component(Actor* owner, int updateOrder)
	:mOwner(owner)
	,mUpdateOrder(updateOrder)
{
	mOwner->AddComponent(this);
}

Component::~Component() {
	mOwner->RemoveComponent(this);
}

//Œp³æ‚Å•ÏX‚·‚éŠÖ”
void Component::Update(float deltaTime) {
	;
}