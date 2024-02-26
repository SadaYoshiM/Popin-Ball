#include "InputComponent.h"
#include "Actor.h"

InputComponent::InputComponent(class Actor* owner)
	:MoveComponent(owner)
	,mMoveRightKey(0)
	,mMoveLeftKey(0)
	,mJumpKey(0)
{

}

void InputComponent::ProcessInput(const uint8_t* keyState) {
	float moveSpeedH = 0.0f;
	if (keyState[mMoveRightKey]) {
		moveSpeedH += mMaxMoveSpeed;
	}
	if (keyState[mMoveLeftKey]) {
		moveSpeedH -= mMaxMoveSpeed;
	}
	SetHorizontalMoveSpeed(moveSpeedH);

	float moveSpeedV = 0.0f;
	if (keyState[mMoveUpperKey]) {
		moveSpeedV -= mMaxMoveSpeed;
	}
	if (keyState[mMoveDownKey]) {
		moveSpeedV += mMaxMoveSpeed;
	}
	SetVerticalMoveSpeed(moveSpeedV);
}
