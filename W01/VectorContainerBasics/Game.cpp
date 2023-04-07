#include "pch.h"
#include "Game.h"
#include <iostream>
#include "Card.h"

Game::Game( const Window& window ) 
	:BaseGame{ window },
	m_NumberOfCards{52},
	m_NumberOfCardsPerSuit{13}
{
	Initialize();
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	InitializeCards();
}

void Game::Cleanup( )
{
	DeleteCards();
}

void Game::Update( float elapsedSec )
{
	/*const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	if ( pStates[SDL_SCANCODE_KP_MINUS]  || pStates[SDL_SCANCODE_A])
	{
	}
	if ( pStates[SDL_SCANCODE_KP_PLUS] || pStates[SDL_SCANCODE_S])
	{
	}*/
}

void Game::Draw( ) const
{
	ClearBackground( );
	DrawCards();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	switch ( e.keysym.sym )
	{
	case SDLK_KP_MINUS:
	case SDLK_d:
		if (m_Numbers.size() < 1)
		{
			std::cout << "The size of vector is 0 you can't decrease it\n";
			return;
		}
		RemoveNumberFromVector();
		PrintVectorElements();
		break;
	case SDLK_KP_PLUS:
	case SDLK_a:
		AddNumberToVector();
		PrintVectorElements();
		break;
	case SDLK_UP:
		IncrementVectorElements();
		PrintVectorElements();
		break;
	case SDLK_DOWN:
		DecrementVectorElements();
		PrintVectorElements();
		break;
	case SDLK_s:
		ShuffleCards();
		break;
	}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
	
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Game::AddNumberToVector()
{
	m_Numbers.push_back(std::rand() % 30);
}
void Game::RemoveNumberFromVector()
{
	m_Numbers.pop_back();
}
void Game::PrintVectorElements() const
{
	//for (int i{}; i < m_Numbers.size(); i++)
	//{
	//	std::cout << m_Numbers[i] << ' ';
	//}

	for (const int& number : m_Numbers)
	{
		std::cout << number << ' ';
	}
	std::cout << '\n';
}

void Game::IncrementVectorElements()
{
	for (int& number : m_Numbers)
	{
		++number;
	}
}

void Game::DecrementVectorElements()
{
	for (int& number : m_Numbers)
	{
		--number;
	}
}

void Game::InitializeCards()
{
	int suit{ 0 };

	for (int i{}; i < m_NumberOfCards; i++)
	{
		if ((i % m_NumberOfCardsPerSuit) == 0)
		{
			 ++suit;
		}
		m_pCards.push_back(new Card{ Card::Suit(suit),(i % m_NumberOfCardsPerSuit + 1)});
		
		//std::cout << suit * 100 + i % m_NumberOfCardsPerSuit + 1 << '\n';
	}
}
void Game::DeleteCards()
{
	for (int i{}; i < m_pCards.size(); i++)
	{
		delete m_pCards[i];
		m_pCards[i] = nullptr;
	}
}
void Game::ShuffleCards()
{
	int firstCard{};
	Card* copyOfCard{};
	for (int i{}; i < m_NumberOfCards; i++)
	{
		do {
			firstCard = std::rand() % m_NumberOfCards;
		} while (firstCard == i);
		copyOfCard = m_pCards[i];
		m_pCards[i] = m_pCards[firstCard];
		m_pCards[firstCard] = copyOfCard;
	}
}
void Game::DrawCards() const
{
	float halfOfRectWidth{ m_pCards[0]->GetWidth() * 0.5f };
	float halfOfRectHeight{ m_pCards[0]->GetHeight() * 0.5f };
	int suit{};
	int triggerForNewCollumn{}; //starts at 0 when i gets to 13 it becomes 13 and is substracted from the i to create new column
	Rectf destRect{
		0,
		GetViewPort().height - halfOfRectHeight,
		halfOfRectWidth,
		halfOfRectHeight
	};

	for (int i{}; i < m_NumberOfCards; i++)
	{
		if ((i % m_NumberOfCardsPerSuit) == 0)
		{
			++suit;
			//std::cout << suit * m_NumberOfCardsPerSuit << '\n';
		}
		triggerForNewCollumn = (suit - 1) * m_NumberOfCardsPerSuit;
		destRect.left = (i - triggerForNewCollumn) * (halfOfRectWidth * 0.5f);

		//we take the highest point and than we subtract the height of a card + 1 for the initial row
		destRect.bottom = GetViewPort().height - (halfOfRectHeight * suit + 1);

		m_pCards[i]->Draw(destRect);
	}
}