#include "pch.h"
#include "Level.h"
#include "Texture.h"
#include "utils.h"

Level::Level()
	:m_pBackgroundTexture{new Texture{"Images/background.png"}},
	m_pFenceTexture{new Texture{"Images/fence.png"}},
	m_FenceBottomLeft{Point2f{200,190}},
	m_IsOnGround{false}
{
	InitializeCollisionVertices();
}

Level::~Level()
{
	delete m_pBackgroundTexture;
	delete m_pFenceTexture;
	m_pBackgroundTexture = nullptr;
	m_pFenceTexture = nullptr;
}

void Level::DrawBackground() const
{
	m_pBackgroundTexture->Draw();
}

void Level::DrawForeground() const
{
	m_pFenceTexture->Draw(m_FenceBottomLeft);
}

void Level::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity)
{
	utils::HitInfo hitInfo{};
	const Point2f centerOfActor
	{
		actorShape.left + actorShape.width * 0.5f,
		actorShape.bottom + actorShape.height * 0.5f
	};
	const Point2f bottomOfActor
	{
		actorShape.left + actorShape.width * 0.5f,
		actorShape.bottom - 1
	};


	if(utils::Raycast(m_Vertices,centerOfActor,bottomOfActor,hitInfo))
	{
		actorVelocity.y = 0;
		actorShape.bottom = hitInfo.intersectPoint.y;
		m_IsOnGround = true;
		return;
	}
	m_IsOnGround = false;
}

void Level::InitializeCollisionVertices()
{
	m_Vertices.push_back(Point2f{ 0, 0 });
	m_Vertices.push_back(Point2f{ 0, 190 });
	m_Vertices.push_back(Point2f{ 340, 190 });
	m_Vertices.push_back(Point2f{ 408, 124 });
	m_Vertices.push_back(Point2f{ 560, 124 });
	m_Vertices.push_back(Point2f{ 660, 224 });
	m_Vertices.push_back(Point2f{ 846, 224 });
	m_Vertices.push_back(Point2f{ 846, 0 });
	m_Vertices.push_back(Point2f{ 0, 0 });
}

bool Level::IsOnGround(const Rectf& actorShape) const
{
	return m_IsOnGround;
}


