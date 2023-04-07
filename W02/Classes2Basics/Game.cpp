#include "pch.h"
#include "Game.h"
#include "Square.h"
#include "Time.h"
#include "Container.h"
#include <iostream>
#include <iomanip>

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
	TestingFunctions();
}

void Game::Cleanup( )
{
}

void Game::Update( float elapsedSec )
{
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

void Game::TestSquares()
{
	Square square1 = Square(10);
	Square square2 = Square(10, 20, 30);

	std::cout << "--> Squares with constructor delegation\n";
	square1.Print();
	square2.Print();

}
void Game::CompareTimes(const Time* t1, const Time* t2)
{
	if (t1->GetSeconds()  == t2->GetSeconds())
	{
		std::cout << std::setw(2) << "They are equal\n";
		return;
	}
	std::cout << std::setw(2) << "They are not equal\n";
}
void Game::PrintInstancesCounter(const std::string& message)
{
	std::cout << message << " -> Nr of Time objects: " << Time::GetNrInstances() << std::endl << std::endl;
}
void Game::TestContainer()
{
	Container* c{ new Container(5)};
	std::cout << "-- Container tests --\n";
	std::cout << "Create container with capacity of 5 elements\n";
	PrintContainer(c);

	std::cout << "Push back of 4 elements\n";
	c->PushBack(18);
	c->PushBack(18);
	c->PushBack(9);
	c->PushBack(9);
	PrintContainer(c);

	std::cout << "Change the value of the elements (using Set)\n";
	c->Set(0, 17);
	c->Set(1, 6);
	c->Set(2, 19);
	c->Set(3, 13);
	PrintContainer(c);

	std::cout << "Push back another 4 elements\n";
	c->PushBack(18);
	c->PushBack(18);
	c->PushBack(9);
	c->PushBack(9);
	PrintContainer(c);

	delete c;
}
void Game::PrintContainer(const Container* c)
{
	std::string numbersString{};
	std::cout << "-- Print container --\n";
	std::cout << std::setw(2) << "Capacity: " << c->Capacity() << std::endl;
	std::cout << std::setw(2) << "Size: " << c->Size() << std::endl;
	std::cout << std::setw(2) << "Get the elements" << std::endl;
	for (int i{}; i < c->Size(); ++i)
	{
		numbersString.append(std::to_string(c->Get(i)) + ' ');
	}
	std::cout << std::setw(2) << numbersString << std::endl << std::endl;
}
void Game::PrintTimes(const Time* t1, const Time* t2)
{
	std::cout << "--> Comparing 2 time objects\n";
	t1->Print();
	t2->Print();
	std::cout << std::endl;
}

void Game::TestingFunctions()
{

	//TestSquares();

	//Time* t1 = new Time{1000000};
	//Time* t2 = new Time{30000};
	//PrintTimes(t1,t2);
	//CompareTimes(t1, t2);
	//delete t1;
	//delete t2;

	//PrintInstancesCounter("Before creating the Time objects no instances (objects)");

	//Time* t3 = new Time{ 1000000 };
	//Time* t4 = new Time{ 30000 };
	//PrintInstancesCounter("After creating 2 Time objects there are 2 instances");

	//Time* t5 = new Time{ 100 };
	//PrintInstancesCounter("After creating all Time objects there should be 3 instances");

	//delete t3;
	//PrintInstancesCounter("After deleting 1 Time objects there should be 2 instances");
	//delete t4;
	//delete t5;
	//PrintInstancesCounter("After deleting all Time objects there should be 0 instances");

	TestContainer();
}
