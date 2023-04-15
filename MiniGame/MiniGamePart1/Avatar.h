#pragma once
#include "Vector2f.h"

class Level;

class Avatar
{
	enum class ActionState
	{
		waiting,
		moving,
		transforming
	};
public:
	Avatar();
	void Update(float elapsedSec, const Level& level);
	void Draw();
	void PowerUpHit();
	Rectf GetShape();

private:
	Rectf m_Shape;
	float m_HorSpeed;
	float m_JumpSpeed;
	Vector2f m_Velocity;
	Vector2f m_Acceleration;
	ActionState m_ActionState;
	float m_AccuTransformSec;
	float m_MaxTransformSec;
	int m_Power;

};

