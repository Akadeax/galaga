#include "pch.h"
#include "Game.h"

#include <iostream>
#include "utils.h"
#include "BezierGenerator.h"
#include "EnemyPaths.h"

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
	m_EnemyFlightPaths = GetEnemyPaths();
}

void Game::Cleanup()
{
}

void Game::Update(float deltaTime)
{
	// Make movement independent of distance between the points in the curve
	const Vector2f current = m_EnemyFlightPaths[m_CurrentPath].combinedBezierPoints[static_cast<int>(m_CurrentPoint)];
	const Vector2f next = m_EnemyFlightPaths[m_CurrentPath].combinedBezierPoints[static_cast<int>(m_CurrentPoint + 1)];
	const float distanceCurrentNext = (current - next).Length();

	const float movementAmount = static_cast<float>(m_SpeedMultiplier) / distanceCurrentNext * deltaTime;

	// If this frames movement amount doesn't put the square beyond the last point
	if (m_CurrentPoint + movementAmount < m_EnemyFlightPaths[m_CurrentPath].combinedBezierPoints.size() - 1)
	{
		m_CurrentPoint += movementAmount;
	}
	else
	{
		m_CurrentPoint = 0;
		m_CurrentPath = (m_CurrentPath + 1) % m_EnemyFlightPaths.size();
	}
}

void Game::Draw() const
{
	ClearBackground();

	constexpr float SQUARE_SIZE{ 25 };
	utils::SetColor(Color4f{ 1, 0, 0, 1 });
	for (int i{}; i <= 3; ++i)
	{
		bezierUtils::DrawFlightPath(m_EnemyFlightPaths[i]);
	}
	//bezierUtils::DrawFlightPath(m_EnemyFlightPaths[1]);
	

	Vector2f smootheTransition = bezierUtils::Lerp(m_EnemyFlightPaths[m_CurrentPath].combinedBezierPoints[int(m_CurrentPoint)], m_EnemyFlightPaths[m_CurrentPath].combinedBezierPoints[int(m_CurrentPoint) + 1],
	                                              m_CurrentPoint - int(m_CurrentPoint));
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