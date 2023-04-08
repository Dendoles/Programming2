#include "pch.h"
#include "Game.h"
#include "Smiley.h"
#include "utils.h"

Game::Game( const Window& window ) 
	:BaseGame{ window }
{
	Initialize();
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	const float border{ 30 };
	m_SafeRect = Rectf
	{
		border,
		border,
		GetViewPort().width - 2 * border,
		GetViewPort().height - 2 * border };
	CreateSmileys();
}

void Game::Cleanup( )
{
	DestroySmileys();
}

void Game::Update( float elapsedSec )
{
	DetermineHighestSmiley();
	UpdateSmileys(elapsedSec);
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
	utils::SetColor(Color4f(1.f, 0.1f, 0.1f, 1));
	utils::DrawRect(m_SafeRect);
	DrawSmileys();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	switch (e.keysym.sym)
	{
	case SDLK_DOWN:
		DecreaseSmileysSpeed();
		//std::cout << "Left arrow key released\n";
		break;
	case SDLK_UP:
		IncreaseSmileysSpeed();
		//std::cout << "`Right arrow key released\n";
		break;
	case SDLK_DELETE:
		DeleteSleepers();
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
	switch (e.button)
	{
	case SDL_BUTTON_LEFT:
		HitTestSmileys(Point2f{ float(e.x),float(e.y) });
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
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Game::CreateSmileys()
{
	const float oneSmiley{ 50 };
	Point2f pos{ oneSmiley, GetViewPort().height / 2 };

	for (int i{ 0 }; i < m_ArraySmileySize; i++)
	{
		pos.x = i * oneSmiley + oneSmiley;
		m_pSmileys[i] = new Smiley(pos);
	}
}
void Game::DrawSmileys() const
{
	for (int i{}; i < m_ArraySmileySize; i++)
	{
		if (m_pSmileys[i])
		{
			m_pSmileys[i]->Draw();
		}
	}
}

void Game::UpdateSmileys(float elapsedSec)
{
	const Rectf boundingRect{ 0,0,GetViewPort().width, GetViewPort().height };

	for (int i{}; i < m_ArraySmileySize; i++)
	{
		if (m_pSmileys[i])
		{
			m_pSmileys[i]->Update(elapsedSec, boundingRect, m_SafeRect);
		}
	}
}
void Game::HitTestSmileys(const Point2f& mousePos)
{
	for (int i{ 0 }; i < m_ArraySmileySize; i++)
	{
		if (m_pSmileys[i])
		{
			m_pSmileys[i]->HitTest(mousePos);
		}
	}
}
void Game::DetermineHighestSmiley()
{
	float highestY{ 0 };
	int indexOfHighest{};
	for (int i{}; i < m_ArraySmileySize; i++)
	{
		if (m_pSmileys[i])
		{
			m_pSmileys[i]->SetHighest(false);
			if (highestY < m_pSmileys[i]->GetPosition().y &&
				!m_pSmileys[i]->IsSleeping())
			{
				highestY = m_pSmileys[i]->GetPosition().y;
				indexOfHighest = i;
			}
		}
	}
	if (m_pSmileys[indexOfHighest]) m_pSmileys[indexOfHighest]->SetHighest(true);
}

void Game::DestroySmileys()
{
	for (int i{}; i < Game::m_ArraySmileySize; i++)
	{
		delete m_pSmileys[i];
		m_pSmileys[i] = nullptr;
	}
}

void  Game::IncreaseSmileysSpeed()
{
	for (int i{}; i < m_ArraySmileySize; i++)
	{
		if (m_pSmileys[i])
		{
			m_pSmileys[i]->IncreaseSpeed();
		}
	}
}
void  Game::DecreaseSmileysSpeed()
{
	for (int i{}; i < m_ArraySmileySize; i++)
	{
		if (m_pSmileys[i])
		{
			m_pSmileys[i]->DecreaseSpeed();
		}
	}
}

void Game::DeleteSleepers()
{
	for (int i{}; i < m_ArraySmileySize; i++)
	{
		if (m_pSmileys[i])
		{
			if (m_pSmileys[i]->IsSleeping())
			{
				delete m_pSmileys[i];
				m_pSmileys[i] = nullptr;
			}
		}
	}
}