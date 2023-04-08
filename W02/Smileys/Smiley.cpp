// -- Smiley.cpp file --
// Decide yourself about the necessary include directives
// #include .....
// ....
#include "pch.h"
#include "Smiley.h"
#include "Texture.h"
#include "utils.h"
#include <iostream>

// Static Texture data
Texture* Smiley::m_pSmileyTexture{ nullptr };
int Smiley::m_InstanceCounter{ 0 };

// Constructor
// Initializes the object, among others:
//	- Initializes the data members, the velocity gets a random value within the inclusive range[60, 180] and [-180, -60]
//	- Creates a texture object to load the image, only if it hasn’t been created before(!)
//  - Adapts the instance counter
Smiley::Smiley(const Point2f& position)
	:m_Position{ position },
	m_IsHighest{ false },
	m_IsSleeping{ false },
	m_IsInSafeArea{ true },
	m_AmountOfSmileys{ 4 }
{
	m_Velocity = GetRandomVelocity();
	SetTexture();
	m_InstanceCounter++;
	m_SmileyWidth = m_pSmileyTexture->GetWidth() / m_AmountOfSmileys;
}

// Destructor
// Deletes the Texture object when this is the last Smiley that is being destroyed.
Smiley::~Smiley()
{
	std::cout << "Smiley got destroyed\n";
	m_InstanceCounter--;
	if (!m_InstanceCounter)
	{
		delete m_pSmileyTexture;
		m_pSmileyTexture = nullptr;
		//std::cout << "meow";
	}
}

// Draw
// Draws a part of the image on the window, which part depends on the state of the smiley:
// - If the smiley is sleeping then the sleeping smiley is drawn.
// - If the smiley is at the highest position, then the happy smiley is drawn.
// - If the smiley is not in the safe area, the scary smiley is drawn.
// - If none of the above conditions is met, the neutral smiley should be drawn.
void Smiley::Draw() const
{
	m_pSmileyTexture->Draw(m_Position, DecideSourceRect());
}

// Update
// - When the smiley is not sleeping, the new position - using the velocity and elapsed seconds - is calculated.
// - The velocity changes sign when at this new position the smiley is outside the bounding rectangle (boundingRect)
// - Checks whether at this new position, it is located in the safe area and updates m_IsInSafeArea accordingly.
void Smiley::Update(float elapsedSec, const Rectf& boundingRect, const Rectf& safeRect)
{
	m_Position.x += m_Velocity.x * elapsedSec;
	m_Position.y += m_Velocity.y * elapsedSec;
	if (boundingRect.left >= m_Position.x ||
		boundingRect.width <= m_Position.x + m_SmileyWidth)
	{
		m_Velocity.x = -m_Velocity.x;
	}
	if (boundingRect.bottom >= m_Position.y ||
		boundingRect.height <= m_Position.y + m_pSmileyTexture->GetHeight())
	{
		m_Velocity.y = -m_Velocity.y;
	}
	IsInSafeArea(safeRect);
}

// HitTest
// If the value of the parameter pos is within the boundaries of the smiley’s circle,
// then the sleeping state of the smiley changes.
void Smiley::HitTest(const Point2f& pos)
{
	const Circlef smiley
	{ m_Position.x + m_SmileyWidth / 2,
		m_Position.y + m_pSmileyTexture->GetHeight() / 2,
		m_SmileyWidth / 2
	};

	if (utils::IsPointInCircle(pos, smiley))
	{
		m_IsSleeping = !m_IsSleeping;
		CheckIfSleeping();
	}
}

// IsSleeping
// Getter of the m_IsSleeping data member
bool Smiley::IsSleeping() const
{
	return m_IsSleeping;
}

// GetPosition
// Getter of the m_Position data member
Point2f Smiley::GetPosition() const
{
	return m_Position;
}

// SetHighest
// Setter of the m_IsHighest data member
void Smiley::SetHighest(bool isHighest)
{
	if (!m_IsSleeping)
	{
		if (isHighest) m_IsHighest = true;
		else m_IsHighest = false;
	}
}

// IncreaseSpeed
// Changes the speed 5% up
void Smiley::IncreaseSpeed()
{
	const float percentage{ 0.05f };
	m_Velocity.x += m_Velocity.x * percentage;
	m_Velocity.y += m_Velocity.y * percentage;
}

// DecreaseSpeed
// Changes the speed 5% down
void Smiley::DecreaseSpeed()
{
	const float percentage{ 0.05f };
	m_Velocity.x -= m_Velocity.x * percentage;
	m_Velocity.y -= m_Velocity.y * percentage;
}

// IsInSafeArea
// Returns true when the smiley is completely inside the safe area as indicated by safeRect
bool Smiley::IsInSafeArea(const Rectf& safeRect)
{
	if ((safeRect.left >= m_Position.x ||
		safeRect.width <= m_Position.x + m_SmileyWidth) ||
		(safeRect.bottom >= m_Position.y ||
			safeRect.height <= m_Position.y + m_pSmileyTexture->GetHeight()))
	{
		m_IsInSafeArea = false;
		return false;
	}
	m_IsInSafeArea = true;
	return true;
}

void Smiley::SetTexture() const
{
	if (!m_InstanceCounter)
	{
		m_pSmileyTexture = new Texture("Smileys.png");
		if (!m_pSmileyTexture->IsCreationOk())
		{
			std::cout << "Texture loaded incorrectly\n";
		}
	}
}

Rectf Smiley::DecideSourceRect() const
{
	// 1 happy, 2 normal, 3 about to hit, 4 sleepy
	int whichSmiley{ 1 };
	Rectf sourceRect
	{
		m_SmileyWidth,
		m_pSmileyTexture->GetHeight(),
		m_SmileyWidth,
		m_pSmileyTexture->GetHeight()
	};

	if (!m_IsInSafeArea) whichSmiley = 2;
	if (m_IsSleeping) whichSmiley = 3;
	if (m_IsHighest && !m_IsSleeping) whichSmiley = 0;

	sourceRect.left = m_SmileyWidth * whichSmiley;
	return sourceRect;
}

void Smiley::CheckIfSleeping()
{
	if (m_IsSleeping)
	{
		m_Velocity = Vector2f{ 0,0 };
	}
	else
	{
		m_Velocity = GetRandomVelocity();
	}
}

Vector2f Smiley::GetRandomVelocity() const
{
	const int minVelocity{ -200 };
	const int maxVelocity{ 200 };
	Vector2f velocity{};
	velocity.x = float(std::rand() % (maxVelocity + (-minVelocity) + 1) + minVelocity);
	velocity.y = float(std::rand() % (maxVelocity + (-minVelocity) + 1) + minVelocity);

	return velocity;
}