#include "pch.h"
#include "Game.h"
#include "Ball.h"

Game::Game( const Window& window ) 
	:BaseGame{ window }
	//m_pBall{ new Ball(Point2f{140.f,200.f}, Vector2f{120.f,-80.f}, Color4f{1.f,0.f,0.f,1.f}, 20.f)}
{
	Initialize();
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize()
{
	InitBalls();
}

void Game::Cleanup( )
{
	DeleteBalls();
	/*delete m_pBall;
	m_pBall = nullptr;*/
}

void Game::Update( float elapsedSec )
{
	UpdateBalls(elapsedSec);
	//m_pBall->Update(elapsedSec, GetViewPort());
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
	DrawBalls();
	//m_pBall->Draw();
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

void Game::InitBalls()
{
	m_pArrayBalls[0] = new Ball(
		Point2f{ GetViewPort().width / 2, GetViewPort().height / 2 },
		Vector2f{ 120.f, -80.f },
		Color4f{ 1.f,0.f,0.f,1.f },
		20.f
	);
	const float radius{ 40.f };
	m_pArrayBalls[1] = new Ball(
		Point2f{ rand() % int(GetViewPort().width - radius * 2) + radius,
						rand() % int(GetViewPort().width - radius * 2) + radius },
		Vector2f{ 200.f, 180.f },
		Color4f{ 0.f,1.f,0.f,1.f },
		radius
	);
}
void Game::DrawBalls() const
{
	for (int i{0}; i < m_NumberBalls; ++i)
	{
		m_pArrayBalls[i]->Draw();
	}
}
void Game::UpdateBalls(float elapsedSec)
{
	for (Ball* pBall : m_pArrayBalls)
	{
		pBall->Update(elapsedSec, GetViewPort());
	}
}
void Game::DeleteBalls()
{
	for (int i{}; i < m_NumberBalls; ++i)
	{
		delete m_pArrayBalls[i];
		m_pArrayBalls[i] = nullptr;
	}
}