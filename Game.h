#pragma once
#include "BezierGenerator.h"

class PlayerShip;
class BulletPool;

class Game final
{
public:
	explicit Game(const Window& window);
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game(Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	~Game();

	void Update(float deltaTime);
	void Draw() const;

	// Event handling
	void ProcessKeyDownEvent(const SDL_KeyboardEvent& e);
	void ProcessKeyUpEvent(const SDL_KeyboardEvent& e);
	void ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e);
	void ProcessMouseDownEvent(const SDL_MouseButtonEvent& e);
	void ProcessMouseUpEvent(const SDL_MouseButtonEvent& e);

private:
	// DATA MEMBERS
	const Window m_Window{};

	BulletPool* m_pBulletBool{ nullptr };
	PlayerShip* m_pPlayer{ nullptr };

	std::vector<bezierUtils::FlightPath> m_EnemyFlightPaths{};
	int m_CurrentPath{ 2 };
	const int m_SpeedMultiplier{ 500 };
	float m_CurrentPoint{};

	// FUNCTIONS
	void Initialize();
	void Cleanup();
	void ClearBackground() const;
};
