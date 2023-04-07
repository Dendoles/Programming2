#include "pch.h"
#include "Game.h"
#include "TrafficLight.h"
#include <iostream>

Game::Game( const Window& window ) 
	:BaseGame{ window },
	m_NumberOfTrafficLights{10},
	m_MousePos{}
{
	Initialize();
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	InitializeTrafficLights();
}

void Game::Cleanup( )
{
	DestroyTrafficLights();
}

void Game::Update( float elapsedSec )
{
	UpdateTrafficLights(elapsedSec);
	// Check keyboard state
	//const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	//if ( pStates[SDL_SCANCODE_RIGHT] )
	//{
	//	std::cout << "Right arrow key is down\n";
	//}
	//if ( pStates[SDL_SCANCODE_LEFT] && pStates[SDL_SCANCODE_UP])
	//{
	//	std::cout << "Left and up arrow keys are down\n";
	//}
}

void Game::Draw( ) const
{
	ClearBackground();
	DrawTrafficLights();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
	m_MousePos.x = e.x;
	m_MousePos.y = e.y;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	switch ( e.button )
	{
	case SDL_BUTTON_LEFT:
		for (int i{}; i < m_NumberOfTrafficLights; i++)
		{
			m_pTrafficLights[i]->DoHitTest(m_MousePos);
		}
		break;
	}
	
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
	glClearColor( 0.3f, 0.3f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Game::DrawTrafficLights() const
{
	for (int i{}; i < m_NumberOfTrafficLights; i++)
	{
		m_pTrafficLights[i]->Draw();
	}
}
void Game::UpdateTrafficLights(float elapsedSec)
{
	for (int i{}; i < m_NumberOfTrafficLights; i++)
	{
		m_pTrafficLights[i]->Update(elapsedSec);
	}
}
void Game::DestroyTrafficLights()
{
	for (int i{}; i < m_NumberOfTrafficLights; i++)
	{
		delete m_pTrafficLights[i];
		m_pTrafficLights[i] = nullptr;
	}
}
void Game::InitializeTrafficLights()
{
	Point2f pos{};
	bool isHalf{false};
	const float margin{10.f};
	const int halfOfTrafficLights{ m_NumberOfTrafficLights / 2};
	float posY{ GetViewPort().height - 295 };
	float posX{};

	for (int i{}; i < m_NumberOfTrafficLights; i++)
	{
		if (i == halfOfTrafficLights)
		{
			posY = margin;
			isHalf = true;
		}
		pos.x = (i - halfOfTrafficLights * isHalf) * 118.f;
		pos.x = margin + pos.x;
		pos.y = posY;
		m_pTrafficLights.push_back(new TrafficLight{pos});
	}
}