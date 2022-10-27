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
	m_FlightPath.windowWidth = g_WindowWidth;
	m_FlightPath.windowHeight = g_WindowHeight;
	m_FlightPath.pathWidth = 7.5f;
	m_FlightPath.pathHeight = 10;
	m_FlightPath.xScaling = m_FlightPath.windowWidth / m_FlightPath.pathWidth;
	m_FlightPath.yScaling = m_FlightPath.windowHeight / m_FlightPath.pathHeight;

	m_FlightPath.paths.push_back(bezierUtils::CalculateBezier(Vector2f{ 0 * m_FlightPath.xScaling,1 * m_FlightPath.yScaling }, Vector2f{ 2 * m_FlightPath.xScaling,1.5f * m_FlightPath.yScaling }, Vector2f{ 6 * m_FlightPath.xScaling,3 * m_FlightPath.yScaling }, Vector2f{ 6 * m_FlightPath.xScaling,5 * m_FlightPath.yScaling }));

	m_FlightPath.paths.push_back(bezierUtils::CalculateBezier(Vector2f{ 6 * m_FlightPath.xScaling,5 * m_FlightPath.yScaling }, Vector2f{ 6 * m_FlightPath.xScaling,8 * m_FlightPath.yScaling }, Vector2f{ 6 * m_FlightPath.xScaling,8 * m_FlightPath.yScaling }, Vector2f{ 5.25f * m_FlightPath.xScaling,8 * m_FlightPath.yScaling }));

	m_FlightPath.paths.push_back(bezierUtils::CalculateBezier(Vector2f{ 5.25f * m_FlightPath.xScaling,8 * m_FlightPath.yScaling }, Vector2f{ 4.5f * m_FlightPath.xScaling,8 * m_FlightPath.yScaling }, Vector2f{ 4.5f * m_FlightPath.xScaling,8 * m_FlightPath.yScaling }, Vector2f{ 4.5f * m_FlightPath.xScaling,6.5f * m_FlightPath.yScaling }));

	m_FlightPath.paths.push_back(bezierUtils::CalculateBezier(Vector2f{ 4.5f * m_FlightPath.xScaling,6.5f * m_FlightPath.yScaling }, Vector2f{ 4.5f * m_FlightPath.xScaling,5 * m_FlightPath.yScaling }, Vector2f{ 4.5f * m_FlightPath.xScaling,5 * m_FlightPath.yScaling }, Vector2f{ 5.25f * m_FlightPath.xScaling,5 * m_FlightPath.yScaling }));

	m_FlightPath.paths.push_back(bezierUtils::CalculateBezier(Vector2f{ 5.25f * m_FlightPath.xScaling,5 * m_FlightPath.yScaling }, Vector2f{ 6 * m_FlightPath.xScaling,5 * m_FlightPath.yScaling }, Vector2f{ 7 * m_FlightPath.xScaling,6 * m_FlightPath.yScaling }, Vector2f{ 7.5f * m_FlightPath.xScaling,8 * m_FlightPath.yScaling }));
}

void Game::Cleanup()
{
}

void Game::Update(float deltaTime)
{
	m_Offset += static_cast<float>(m_Speed) * deltaTime;
	if(m_Offset >= bezierUtils::BEZIER_STEPS_AMOUNT * m_FlightPath.paths.size() - 1)
	{
		m_Offset = 0;
	}
}

void Game::Draw() const
{
	ClearBackground();

	constexpr float SQUARE_SIZE{ 50 };
	utils::SetColor(Color4f{ 1, 0, 0, 1 });

	for (int i{ 0 }; i < m_FlightPath.paths.size(); ++i)
	{
		DrawBezier(m_FlightPath.paths[i], 1);
	}

	std::vector<Vector2f> combinedPaths = std::vector<Vector2f>();
	for (int i{ 0 }; i < m_FlightPath.paths.size(); ++i)
	{
		const std::vector<Vector2f>& current = m_FlightPath.paths[i].curvePoints;
		combinedPaths.insert(combinedPaths.end(), current.begin(), current.end());
	}

	Vector2f smootheTransition = bezierUtils::Lerp(combinedPaths[int(m_Offset)], combinedPaths[int(m_Offset) + 1],
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