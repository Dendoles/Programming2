#include "pch.h"
#include "PowerUp.h"
#include "Texture.h"

PowerUp::PowerUp(const Point2f& center, PowerUp::Type type):
	m_Type{type},
	m_pTexture{ new Texture{"Images/PowerUp.png"}},
	m_RotSpeed{360}, //360 degrees per second
	m_TextClip{},
	m_Shape{center, 0},
	m_Angle{}
{
	m_Shape.radius = m_pTexture->GetWidth() * 0.5f;
	InitiateTextClip();
}

PowerUp::~PowerUp()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}

void PowerUp::Update(float elapsedSec)
{
	m_Angle += m_RotSpeed * elapsedSec;
	//m_Angle = m_Angle % 360;
}

void PowerUp::Draw() const
{
	glPushMatrix();

	glTranslatef(m_Shape.center.x,m_Shape.center.y, 0);
	glRotatef(m_Angle, 0, 0, 1);
	glTranslatef(-m_TextClip.width * 0.5f, -m_TextClip.height * 0.5f, 0);

	m_pTexture->Draw(Point2f{0,0}, m_TextClip);

	glPopMatrix();
}

bool PowerUp::IsOverlapping(const Rectf& rect) const
{
	if (utils::IsOverlapping(rect,m_Shape))
	{
		return true;
	}
	return false;
}

void PowerUp::InitiateTextClip()
{
	float textureBottom{};
	switch (m_Type)
	{
	case Type::brown:
		textureBottom = m_pTexture->GetHeight();
		break;
	case Type::green:
		textureBottom = 0.f;
		break;
	}
	m_TextClip = Rectf
	{
		0.0f,
		textureBottom,
		m_pTexture->GetWidth(),
		m_pTexture->GetHeight() * 0.5f
	};
}