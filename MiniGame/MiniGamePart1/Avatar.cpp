#include "pch.h"
#include "Avatar.h"

Avatar::Avatar()
	:m_Shape{Rectf{50,280,36,97}},
	m_HorSpeed{200.0f},
	m_JumpSpeed{600.0f},
	m_Velocity{ Vector2f{0.0f,0.0f} },
	m_Acceleration{Vector2f{0.0f,-981.0f}},
	m_ActionState{ActionState::moving},
	m_AccuTransformSec{0.0f},
	m_MaxTransformSec{1.0f},
	m_Power{0}
{
}
void Avatar::Update(float elapsedSec, const Level& level)
{
	
}

void Avatar::Draw()
{
	
}

void Avatar::PowerUpHit()
{
	
}

Rectf Avatar::GetShape()
{
	return m_Shape;
}

