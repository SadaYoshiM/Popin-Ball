#pragma once
#include "Component.h"
#include "Math.h"

class MoveComponent : public Component {
public:
	MoveComponent(class Actor* owner, int updateOrder = 10);
	void Update(float deltaTime) override;

	float GetForwardSpeed() const { return mForwardSpeed; }
	float GetHorizontalMoveSpeed() const { return mMoveSpeedH; }
	float GetVerticalMoveSpeed() const { return mMoveSpeedV; }
	bool GetReflect() const { return mIsReflect; }
	bool GetPlayable() const { return mIsPlayable; }
	void SetForwardSpeed(float speed) { mForwardSpeed = speed; }
	void SetHorizontalMoveSpeed(float speed) { mMoveSpeedH = speed; }
	void SetVerticalMoveSpeed(float speed) { mMoveSpeedV = speed; }
	void SetReflect(bool reflect) { mIsReflect = reflect; }
	void SetPlayable(bool playable) { mIsPlayable = playable; }

private:
	float mForwardSpeed;
	float mMoveSpeedH;
	float mMoveSpeedV;
	bool mIsReflect;
	bool mIsPlayable;
};