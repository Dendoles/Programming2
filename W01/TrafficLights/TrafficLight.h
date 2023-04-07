#pragma once
class TrafficLight
{
public:
	enum class State
	{
		red,
		green,
		orange,
		off
	};

	explicit TrafficLight(const Point2f& pos);
	void DoHitTest(const Point2f& point);
	void Update(float elapsedSec);
	void Draw() const;
	float GetWidth() const;
	float GetHeight() const;

private:
	State m_State;
	Point2f m_Position;
	float m_AccumulatedSec;
	Rectf m_Armature;
	Circlef m_Red;
	Circlef m_Green;
	Circlef m_Orange;
	Color4f m_RedColor;
	Color4f m_GreenColor;
	Color4f m_OrangeColor;
	Color4f m_GreyColor;


	void InitializeArmatureAndCircles();
	Color4f SetColor(Color4f defaultOnColor) const;
};

