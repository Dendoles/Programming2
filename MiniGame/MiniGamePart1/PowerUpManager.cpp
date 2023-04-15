#include "pch.h"
#include "PowerUpManager.h"

PowerUpManager::PowerUpManager()
{
}

PowerUpManager::~PowerUpManager()
{
	for (size_t index{}; index < m_pItems.size(); ++index)
	{
		delete m_pItems[index];
		m_pItems[index] = nullptr;
	}
}

PowerUp* PowerUpManager::AddItem(const Point2f& center, PowerUp::Type type)
{
	m_pItems.push_back(new PowerUp(center, type));
	return m_pItems[m_pItems.size() - 1];
}

void PowerUpManager::Update(float elapsedSec)
{
	for(size_t index{}; index < m_pItems.size(); ++index)
	{
		m_pItems[index]->Update(elapsedSec);
	}
}

void PowerUpManager::Draw() const
{
	for (size_t index{}; index < m_pItems.size(); ++index)
	{
		m_pItems[index]->Draw();
	}
}

size_t PowerUpManager::Size() const
{
	return m_pItems.size();
}

bool PowerUpManager::HitItem(const Rectf& rect)
{
	for (size_t index{}; index < m_pItems.size(); ++index)
	{
		if(m_pItems[index]->IsOverlapping(rect))
		{
			ExchangePositionWithLastPowerUp(index);
			DeleteLastPowerUp();
			return true;
		}
	}
	return false;
}

void PowerUpManager::ExchangePositionWithLastPowerUp(size_t index)
{
	const size_t lastPowerUpIndex{ m_pItems.size() - 1 };
	PowerUp* temporaryVariable{ m_pItems[index] };
	m_pItems[index] = m_pItems[lastPowerUpIndex];
	m_pItems[lastPowerUpIndex] = temporaryVariable;
}

void PowerUpManager::DeleteLastPowerUp()
{
	const size_t lastPowerUpIndex{ m_pItems.size() - 1 };
	delete m_pItems[lastPowerUpIndex];
	m_pItems[lastPowerUpIndex] = nullptr;
	m_pItems.pop_back();
}