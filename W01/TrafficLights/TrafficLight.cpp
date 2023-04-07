#include "pch.h"
#include "TrafficLight.h"
#include "utils.h"

TrafficLight::TrafficLight(const Point2f& pos):
	m_State{State::off},
	m_Position{pos},
	m_AccumulatedSec{},
	m_RedColor{ Color4f{ 1.f,0.f,0.f,1} },
	m_GreenColor{ Color4f{ 0.f,1.f,0.f,1 } },
	m_OrangeColor{ Color4f{ 1.f,0.647f,0.f,1 } },
	m_GreyColor{ Color4f{0.1f,0.1f,0.1f,1.f} }
{
	InitializeArmatureAndCircles();
}

void TrafficLight::DoHitTest(const Point2f& point)
{
	if (!utils::IsPointInRect(point, m_Armature))
	{
		return;
	}
	if (utils::IsPointInCircle(point, m_Red))
	{
		m_State = State::red;
		return;
	}
	if (utils::IsPointInCircle(point, m_Green))
	{
		m_State = State::green;
		return;
	}
	if (utils::IsPointInCircle(point, m_Orange))
	{
		m_State = State::orange;
		return;
	}
	m_State = State::off;
}

void TrafficLight::Update(float elapsedSec) 
{
	switch (m_State)
	{
	case State::off:
		m_AccumulatedSec = 0.f;
		return;
		break;
	case State::green:
		m_AccumulatedSec += elapsedSec;
		if (m_AccumulatedSec >= 4.f)
		{
			m_State = State::orange;
			m_AccumulatedSec = 0.f;
		}
		break;
	case State::red:
		m_AccumulatedSec += elapsedSec;
		if (m_AccumulatedSec >= 4.f)
		{
			m_State = State::green;
			m_AccumulatedSec = 0.f;
		}
		break;
	case State::orange:
		m_AccumulatedSec += elapsedSec;
		if (m_AccumulatedSec >= 1.f)
		{
			m_State = State::red;
			m_AccumulatedSec = 0.f;
		}
		break;
	}
	m_AccumulatedSec += elapsedSec;
}
void TrafficLight::Draw() const
{
	utils::SetColor(Color4f{0.f,0.f,0.f,1});
	utils::FillRect(m_Armature);
	utils::SetColor(SetColor(m_RedColor));
	utils::FillEllipse(m_Red.center, m_Red.radius, m_Red.radius);
	utils::SetColor(SetColor(m_GreenColor));
	utils::FillEllipse(m_Green.center, m_Green.radius, m_Green.radius);
	utils::SetColor(SetColor(m_OrangeColor));
	utils::FillEllipse(m_Orange.center, m_Orange.radius, m_Orange.radius);
}
float TrafficLight::GetWidth() const
{
	return m_Armature.width;
}
float TrafficLight::GetHeight() const
{
	return m_Armature.height;
}

void TrafficLight::InitializeArmatureAndCircles()
{
	m_Armature.bottom = m_Position.y;
	m_Armature.left = m_Position.x;
	m_Armature.height = 285.f;
	m_Armature.width = 108.f;

	const float halfOfArmatureWidth{ m_Armature.width * 0.5f };
	const float halfOfArmatureHeight{ m_Armature.height * 0.5f };
	const float fifthOfArmatureWidth{ m_Armature.width * 0.2f};
	const float fifthOfArmatureHeight{ m_Armature.height * 0.2f };

	m_Orange.center = Point2f{ m_Position.x + halfOfArmatureWidth,m_Position.y + halfOfArmatureHeight };
	m_Orange.radius = halfOfArmatureWidth - fifthOfArmatureWidth;

	m_Red.center = Point2f{ m_Position.x + halfOfArmatureWidth,m_Position.y + m_Armature.height - fifthOfArmatureHeight };
	m_Red.radius = halfOfArmatureWidth - fifthOfArmatureWidth;

	m_Green.center = Point2f{ m_Position.x + halfOfArmatureWidth, m_Position.y + fifthOfArmatureHeight + m_Green.radius };
	m_Green.radius = halfOfArmatureWidth - fifthOfArmatureWidth;
}

Color4f TrafficLight::SetColor(Color4f defaultOnColor) const
{
	if (defaultOnColor.r == m_RedColor.r &&
		defaultOnColor.g == m_RedColor.g &&
		defaultOnColor.b == m_RedColor.b)
	{
		switch (m_State)
		{
			case State::red:
				return m_RedColor;
				break;
			default:
				return m_GreyColor;
				break;
		}
	}
	if (defaultOnColor.r == m_GreenColor.r &&
		defaultOnColor.g == m_GreenColor.g &&
		defaultOnColor.b == m_GreenColor.b)
	{
		switch (m_State)
		{
		case State::green:
			return m_GreenColor;
			break;
		default:
			return m_GreyColor;
			break;
		}
	}
	if (defaultOnColor.r == m_OrangeColor.r &&
		defaultOnColor.g == m_OrangeColor.g &&
		defaultOnColor.b == m_OrangeColor.b)
	{
		switch (m_State)
		{
		case State::orange:
			return m_OrangeColor;
			break;
		default:
			return m_GreyColor;
			break;
		}
	}
}