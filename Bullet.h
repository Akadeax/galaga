#pragma once
#include "Vector2f.h"

class Texture;

class Bullet
{
public:
	explicit Bullet(const Texture* bulletTexture);

	struct ShootData
	{
		Vector2f position;
		Vector2f velocity;
		bool isPlayerBullet;

		ShootData(Vector2f position, Vector2f velocity, bool isPlayerBullet)
			: position{ position }, velocity{ velocity }, isPlayerBullet{ isPlayerBullet} {}
	};

	void Enable(Bullet::ShootData data);
	
	void Update(float deltaTime);
	void Draw() const;

	bool IsEnabled() const;

private:
	Vector2f m_Position{};
	Vector2f m_Velocity{};

	bool m_Enabled{ true };
	bool m_IsPlayerBullet{ true };

	const Texture* m_pBulletTexture{ nullptr };
	const Vector2f m_DrawSize{ Vector2f(50, 50) };
};
