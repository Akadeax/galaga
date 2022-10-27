#include "pch.h"
#include "Game.h"

#include <iostream>
#include "utils.h"
#include "BezierGenerator.h"
#include "constants.h"

Game::Game(const Window & window)
	:m_Window{ window }
{
	Initialize();
}

Game::~Game()
{
	Cleanup();
}

void Game::Initialize()
{
	m_FlightPath = bezierUtils::CalculateFlightPath(bezierUtils::FlightPathData{
		{
			bezierUtils::BezierData{ Vector2f{0, 1}, Vector2f{2.66f, 1.5f}, Vector2f{8, 3}, Vector2f{8, 5} },
			bezierUtils::BezierData{ Vector2f{8, 5}, Vector2f{8, 8}, Vector2f{8, 8}, Vector2f{7, 8} },
			bezierUtils::BezierData{ Vector2f{7, 8}, Vector2f{6, 8}, Vector2f{6, 8}, Vector2f{6, 6.5f} },
			bezierUtils::BezierData{ Vector2f{6, 6.5f}, Vector2f{6, 5}, Vector2f{6, 5}, Vector2f{7, 5} },
			bezierUtils::BezierData{ Vector2f{7, 5}, Vector2f{8, 5}, Vector2f{9.33f, 6}, Vector2f{10, 8} },
		}
	});
}

void Game::Cleanup()
{
}

void Game::Update(float deltaTime)
{
	m_Offset += static_cast<float>(m_Speed) * deltaTime;
}

void Game::Draw() const
{
	ClearBackground();

	constexpr float SQUARE_SIZE{ 50 };
	utils::SetColor(Color4f{ 1, 0, 0, 1 });
	bezierUtils::DrawFlightPath(m_FlightPath);

	Vector2f smootheTransition = bezierUtils::Lerp(m_FlightPath.combinedBezierPoints[int(m_Offset)], m_FlightPath.combinedBezierPoints[int(m_Offset) + 1],
	                                              m_Offset - int(m_Offset));
	smootheTransition.x -= SQUARE_SIZE / 2;
	smootheTransition.y -= SQUARE_SIZE / 2;

	utils::FillRect(smootheTransition.ToPoint2f(), SQUARE_SIZE, SQUARE_SIZE);
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
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

void Game::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
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

void Game::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
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

void Game::ClearBackground() const
{
	glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}