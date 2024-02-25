#include "MoveComponent.h"
#include "Actor.h"
#include "SDL/SDL.h"

MoveComponent::MoveComponent(class Actor* owner, int updateOrder)
	:Component(owner)
	,mMoveSpeedH(0.0f)
	,mMoveSpeedV(0.0f)
	,mIsReflect(false)
	,mIsPlayable(false)
{

}

void MoveComponent::Update(float deltaTime) {
	if (!Math::NearZero(mForwardSpeed)) {
		Vector2 pos = mOwner->GetPosition();
		Vector2 vel = mOwner->GetVelocity();
		Vector2 dir = mOwner->GetForward();
		vel += Vector2(0.1f, 5.0f) * deltaTime;
		bool isRef = GetReflect();

		if (isRef) {
			pos += vel * mForwardSpeed * deltaTime;
			if (pos.x <= 20.0f && vel.x < 0.0f) {
				vel.x *= -1;
			}
			else if (pos.x >= 1004.0f && vel.x > 0.0f) {
				vel.x *= -1;
			}

			if (pos.y <= 0.0f && vel.y < 0.0f) {
				vel.y *= -1;
			}
			else if (pos.y >= 743.0f && vel.y > 0.0f) {
				vel.y *= -0.95f;
			}
		}
		else {
			pos += dir * mForwardSpeed * deltaTime;
		}
		mOwner->SetVelocity(vel);
		mOwner->SetPosition(pos);
	}
	if (!Math::NearZero(mMoveSpeedH) || !Math::NearZero(mMoveSpeedV)) {
		Vector2 pos = mOwner->GetPosition();
		Vector2 dir = mOwner->GetForward();
		float tmp = dir.x;
		dir.x = -dir.y;
		dir.y = tmp;

		if (pos.x <= 30.0f) {
			pos.x = 30.0f;
		}
		else if (pos.x >= 1024.0f-30.0f) {
			pos.x = 1024.0f-30.0f;
		}
		if (pos.y >= 768.0f - 30.0f) {
			pos.y = 768.0f - 30.0f;
		}

		pos += dir * Vector2(mMoveSpeedH, mMoveSpeedV) * deltaTime;
		mOwner->SetPosition(pos);
	}
}