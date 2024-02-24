#pragma once
#include "MoveComponent.h"
#include <cstdint>

class InputComponent : public MoveComponent {
public:
	InputComponent(class Actor* owner);

	void ProcessInput(const uint8_t* keyState) override;

	float GetMaxMove() const { return mMaxMoveSpeed; }
	float GetMaxJump() const { return mMaxJumpSpeed; }
	int GetMoveRightKey() const { return mMoveRightKey; }
	int GetMoveLeftKey() const { return mMoveLeftKey; }
	int GetJumpKey() const { return mJumpKey; }

	void SetMaxMoveSpeed(float speed) { mMaxMoveSpeed = speed; }
	void SetMaxJumpSpeed(float speed) { mMaxJumpSpeed = speed; }
	void SetMoveRightKey(int key) { mMoveRightKey = key; }
	void SetMoveLeftKey(int key) { mMoveLeftKey = key; }
	void SetJumpKey(int key) { mJumpKey = key; }

private:
	float mMaxMoveSpeed;
	float mMaxJumpSpeed;

	int mMoveRightKey;
	int mMoveLeftKey;
	int mJumpKey;
};