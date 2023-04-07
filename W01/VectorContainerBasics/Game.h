#pragma once
#include "BaseGame.h"
#include <vector>
class Card;
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

	std::vector<int> m_Numbers;
	std::vector<Card*> m_pCards;
	const int m_NumberOfCards;
	const int m_NumberOfCardsPerSuit;

	// FUNCTIONS
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;
	void AddNumberToVector();
	void RemoveNumberFromVector();
	void PrintVectorElements() const;
	void IncrementVectorElements();
	void DecrementVectorElements();
	void InitializeCards();
	void DeleteCards();
	void ShuffleCards();
	void DrawCards() const;
};