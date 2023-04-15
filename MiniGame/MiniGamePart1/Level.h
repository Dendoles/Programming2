#pragma once
#include "Vector2f.h"
#include <vector>
class Texture;

class Level
{
public:
	Level();
	~Level();
	void DrawBackground() const;
	void DrawForeground() const;
	void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity);
	bool IsOnGround(const Rectf& actorShape) const;

private:
	Texture* m_pBackgroundTexture;
	Texture* m_pFenceTexture;
	std::vector<Point2f> m_Vertices;
	Point2f m_FenceBottomLeft;
	bool m_IsOnGround;

	void InitializeCollisionVertices();
};

