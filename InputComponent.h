#pragma once
#include "MoveComponent.h"
#include <cstdint>

class InputComponent : public MoveComponent {
public:
	InputComponent(class Actor* owner);

	void ProcessInput(const uint8_t* keyState) override;

	float GetMaxMove() const { return mMaxMoveSpeed; }
	int GetMoveRightKey() const { return mMoveRightKey; }
	int GetMoveLeftKey() const { return mMoveLeftKey; }
	int GetMoveUpperKey() const { return mMoveUpperKey; }
	int GetMoveDownKey() const { return mMoveDownKey; }
	int GetJumpKey() const { return mJumpKey; }

	void SetMaxMoveSpeed(float speed) { mMaxMoveSpeed = speed; }
	void SetMoveRightKey(int key) { mMoveRightKey = key; }
	void SetMoveLeftKey(int key) { mMoveLeftKey = key; }
	void SetMoveUpperKey(int key) { mMoveUpperKey = key; }
	void SetMoveDownKey(int key) { mMoveDownKey = key; }

private:
	float mMaxMoveSpeed;

	int mMoveRightKey;
	int mMoveLeftKey;
	int mMoveUpperKey;
	int mMoveDownKey;
	int mJumpKey;
};