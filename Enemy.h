#pragma once
#include "Vector2f.h"
#include "constants.h"

class Texture;
class BulletPool;

enum class EnemyState
{
	Entering,
	Idling,
	Attacking,
	Exiting
};
  

class Enemy
{
public:
	explicit Enemy(BulletPool* bulletPool, float speed, float health);
	~Enemy();

	void Draw() const;
	void Update(float deltaTime);

private:
	BulletPool* m_pBulletPool{ nullptr };

	float m_Speed{};
	float m_health{};
	Vector2f m_Position{};

	float m_CurrentShootCooldown{ 0.f };
	const float m_ShootCooldown{ 0.15f };
	const float m_BulletSpeed{ 750.f };

	const Texture* m_pTexture{ nullptr };
};

