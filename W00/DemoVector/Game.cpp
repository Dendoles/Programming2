#include "pch.h"
#include "Game.h"
#include <iostream>

Game::Game( const Window& window ) 
	:BaseGame{ window },
	m_pLogo{ new Texture("DAE.png")},
	m_Angle{}
{
	Initialize();
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	const int numValues{ 10 };
	for (int i{}; i < numValues; ++i)
	{
		m_Numbers.push_back(rand() % 100);
	}

	for (const int& number : m_Numbers)
	{
		std::cout << number << '\n';
	}
}

void Game::Cleanup( )
{
	delete m_pLogo;
	m_pLogo = nullptr;
}

void Game::Update( float elapsedSec )
{
	++m_Angle;
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
	ClearBackground( );

	Point2f pos{
		GetViewPort().width / 2 - m_pLogo->GetWidth() / 2,
		GetViewPort().height / 2 - m_pLogo->GetHeight() / 2,
	};

	glPushMatrix();


	glTranslatef(GetViewPort().width / 2, GetViewPort().height / 2, 0);
	//glScalef(.7f,.7f,1.f);
	glRotatef(m_Angle, 0, 0, 1);
	glTranslatef(-m_pLogo->GetWidth() / 2, -m_pLogo->GetHeight() / 2,0);

	m_pLogo->Draw(Point2f(0,0));

	glPopMatrix();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	switch ( e.keysym.sym )
	{
	case SDLK_LEFT:
		//std::cout << "Left arrow key released\n";
		break;
	case SDLK_RIGHT:
		//std::cout << "`Right arrow key released\n";
		break;
	case SDLK_1:
	case SDLK_KP_1:
		m_Numbers.pop_back();

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
