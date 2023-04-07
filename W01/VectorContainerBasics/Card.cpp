#include "pch.h"
#include "Card.h"
#include "Texture.h"

const int Card::m_MinRank{ 1 };
const int Card::m_MaxRank{ 13 };

Card::Card(Suit suit, int rank) :
	m_Suit{ suit },
	m_Rank{rank}
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

void Card::Draw(const Rectf& destRect) const
{
	Rectf sourceRect{
		0,
		0,
		0,
		0
	};
	m_pTexture->Draw(destRect,sourceRect);
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