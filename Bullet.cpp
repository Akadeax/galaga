#include "pch.h"
#include "Bullet.h"
#include "Texture.h"
#include "constants.h"



Bullet::Bullet(const Texture* bulletTexture)
	: m_pBulletTexture{ bulletTexture }
{
}

void Bullet::Enable(Bullet::ShootData data)
{
	m_Enabled = true;
	m_Position = data.position;
	m_Velocity = data.velocity;
	m_IsPlayerBullet = data.isPlayerBullet;
}

void Bullet::Update(float deltaTime)
{
	if (!m_Enabled) return;

	m_Position += m_Velocity * deltaTime;

	if (m_Position.y >= g_WindowHeight)
	{
		m_Enabled = false;
	}
}

void Bullet::Draw() const
{
	if (!m_Enabled) return;

	Rectf srcRect{ 0, 0, 16, 16 };
	if (!m_IsPlayerBullet) srcRect.bottom += 16;

	m_pBulletTexture->Draw(
		Rectf(m_Position.x - m_DrawSize.x / 2, m_Position.y - m_DrawSize.y / 2, m_DrawSize.x, m_DrawSize.y),
		srcRect
	);
}

bool Bullet::IsEnabled() const
{
	return m_Enabled;
}
