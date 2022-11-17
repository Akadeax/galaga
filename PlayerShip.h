#pragma once
#include "Vector2f.h"
#include "constants.h"

class Texture;
class BulletPool;

class PlayerShip
{
public:
	explicit PlayerShip(BulletPool* bulletPool);
	~PlayerShip();

	void Draw() const;
	void Update(float deltaTime);

private:
	BulletPool* m_pBulletBool{ nullptr };

	float m_PlayerSize{ 25 };
	float m_HorizontalSpeed{ 200 };
	float m_XPosition{ g_WindowWidth / 2 };
	const float m_HorizontalBound{ m_PlayerSize };

	const float m_YPosition{ 25 };
	const Vector2f m_DrawSize{ Vector2f{m_PlayerSize, m_PlayerSize} };

	float m_CurrentShootCooldown{ 0.f };
	const float m_ShootCooldown{ 0.15f };
	const float m_BulletSpeed{ 750.f };

	const Texture* m_pTexture{ nullptr };
};

