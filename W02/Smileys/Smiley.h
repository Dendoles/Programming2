#pragma once
#include  "Vector2f.h"
class  Texture; // class forward declaration
class Smiley
{
public:
	Smiley(const Point2f& position);
	~Smiley();

	void Draw() const;
	void Update(float elapsedSec, const Rectf& boundingRect, const Rectf& safeRect);
	void HitTest(const Point2f& pos);
	bool IsSleeping() const;
	Point2f GetPosition() const;
	void SetHighest(bool isHighest);
	void IncreaseSpeed();
	void DecreaseSpeed();
	void CheckIfSleeping();
	Vector2f GetRandomVelocity() const;

private:
	// DATA MEMBERS
	static Texture* m_pSmileyTexture;
	static int m_InstanceCounter;

	void SetTexture() const;
	Point2f m_Position;
	Vector2f m_Velocity;
	bool m_IsHighest;
	bool m_IsSleeping;
	bool m_IsInSafeArea;
	float m_SmileyWidth;
	const int m_AmountOfSmileys;

	// FUNCTIONS
	bool IsInSafeArea(const Rectf& safeRect);
	Rectf DecideSourceRect() const;
};


