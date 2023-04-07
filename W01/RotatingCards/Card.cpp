#include "pch.h"
#include "Card.h"
#include "Texture.h"

const int Card::m_MinRank{ 1 };
const int Card::m_MaxRank{ 13 };

Card::Card(Suit suit, int rank, float angle, const Circlef& circle) :
	m_Suit{ suit },
	m_Rank{rank},
	m_Angle{angle},
	m_Circle{circle},
	m_RotationalSpeed{50.f}
{
	m_pTexture = new Texture{"Cards/" + std::to_string( int(suit) * 100 + rank) + ".png"};
	m_Height = m_pTexture->GetHeight();
	m_Width = m_pTexture->GetWidth();
}

Card::~Card()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}

void Card::Update(float elapsedSec)
{
	m_Angle += m_RotationalSpeed * elapsedSec;
}

void Card::Draw() const
{
	glPushMatrix();

	glTranslatef(m_Circle.center.x,m_Circle.center.y, 0);
	glScalef(.5f, .5f, 1.f);
	glRotatef(m_Angle, 0, 0, 1);

	m_pTexture->Draw(Point2f{m_Circle.radius,0});
	glPopMatrix();
}

float Card::GetWidth() const
{
	return m_Width;
}

float Card::GetHeight() const
{
	return m_Height;
}

std::string Card::GetImagePath(Suit suit, int rank) const
{
	return "Cards/" + std::to_string(int(suit) * 100 + rank) + ".png";
}