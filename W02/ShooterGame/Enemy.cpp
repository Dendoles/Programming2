#include "pch.h"
#include "Enemy.h"
#include "utils.h"

Enemy::Enemy(const Point2f& center, float width, float height)
	:m_Center{center},
	m_Width{width},
	m_Height{height},
	m_IsDead{false}
{
}

void Enemy::Draw() const
{
	if(m_IsDead)
	{
		return;
	}
	utils::SetColor(Color4f{1.f,0.f,0.f,1.f});
	utils::DrawRect(GetBounds());
}

bool Enemy::DoHitTest(const Rectf& other)
{
	if(utils::IsOverlapping(GetBounds(), other))
	{
		m_IsDead = true;
		return true;
	}
	return false;
}

void Enemy::SetCenter(const Point2f center)
{
	m_Center = center;
}

void Enemy::SetDimensions(float width, float height)
{
	m_Width = width;
	m_Height = height;
}

bool Enemy::IsDead() const
{
	return m_IsDead;
}

Rectf Enemy::GetBounds() const
{
	const Rectf bounds
	{
		m_Center.x - (0.5f * m_Width),
		m_Center.y - (0.5f * m_Height),
		m_Width,
		m_Height
	};
	return bounds;
}
