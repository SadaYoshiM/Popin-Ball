#include "InputComponent.h"
#include "Actor.h"

InputComponent::InputComponent(class Actor* owner)
	:MoveComponent(owner)
	,mMoveRightKey(0)
	,mMoveLeftKey(0)
{

}

void InputComponent::ProcessInput(const uint8_t* keyState) {
	float moveSpeed = 0.0f;
	if (keyState[mMoveRightKey]) {
		moveSpeed += mMaxMoveSpeed;
	}
	if (keyState[mMoveLeftKey]) {
		moveSpeed -= mMaxMoveSpeed;
	}
	SetMoveSpeed(moveSpeed);
}
