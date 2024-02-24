#pragma once
#include "Component.h"
#include "Math.h"

class MoveComponent : public Component {
public:
	MoveComponent(class Actor* owner, int updateOrder = 10);
	void Update(float deltaTime) override;

	float GetAngularSpeed() const { return mAngularSpeed; }
	float GetForwardSpeed() const { return mForwardSpeed; }
	float GetMoveSpeed() const { return mMoveSpeed; }
	float GetJumpSpeed() const { return mJumpSpeed; }
	bool GetReflect() const { return mIsReflect; }
	void SetAngularSpeed(float speed) { mAngularSpeed = speed; }
	void SetForwardSpeed(float speed) { mForwardSpeed = speed; }
	void SetMoveSpeed(float speed) { mMoveSpeed = speed; }
	void SetJumpSpeed(float speed) { mJumpSpeed = speed; }
	void SetReflect(bool reflect) { mIsReflect = reflect; }

private:
	float mAngularSpeed;
	float mForwardSpeed;
	float mMoveSpeed;
	float mJumpSpeed;
	bool mIsReflect;
};