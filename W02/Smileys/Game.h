#pragma once
#include "BaseGame.h"

class Smiley;
class Game : public BaseGame
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();

	void Update( float elapsedSec ) override;
	void Draw( ) const override;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;

private:

	// FUNCTIONS
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;

	//Smiley data members
	static const int m_ArraySmileySize{ 10 };
	Smiley* m_pSmileys[m_ArraySmileySize];
	Rectf m_SafeRect;


	//Smiley Functions
	void CreateSmileys();
	void DrawSmileys() const;
	void UpdateSmileys(float elapsedSec);
	void HitTestSmileys(const Point2f& mousePos);
	void DetermineHighestSmiley();
	void DestroySmileys();
	void IncreaseSmileysSpeed();
	void DecreaseSmileysSpeed();
	void DeleteSleepers();
};