#include "pch.h"
#include "PlayerShip.h"

#include "Texture.h"
#include "utils.h"
#include "BulletPool.h"

PlayerShip::PlayerShip(BulletPool* bulletPool)
	: m_pBulletBool{ bulletPool }
{
	m_pTexture = new Texture("./sprites/player.png");
}

PlayerShip::~PlayerShip()
{
	delete m_pTexture;
}

void PlayerShip::Draw() const
{
	m_pTexture->Draw(
		Rectf{ m_XPosition - m_DrawSize.x / 2, m_YPosition - m_DrawSize.y / 2, m_DrawSize.x, m_DrawSize.y },
		Rectf{ 0, 0, 16, 16 }
	);
}

void PlayerShip::Update(float deltaTime)
{
	const Uint8* state = SDL_GetKeyboardState(nullptr);

	if (state[SDL_SCANCODE_RIGHT])
	{
		m_XPosition += m_HorizontalSpeed * deltaTime;
	}
	else if (state[SDL_SCANCODE_LEFT])
	{
		m_XPosition -= m_HorizontalSpeed * deltaTime;
	}

	if (m_XPosition < m_HorizontalBound)
	{
		m_XPosition = m_HorizontalBound;
	}
	if (m_XPosition > g_WindowWidth - m_HorizontalBound)
	{
		m_XPosition = g_WindowWidth - m_HorizontalBound;
	}

	if (m_CurrentShootCooldown > 0)
	{
		m_CurrentShootCooldown -= deltaTime;
	}
	if (state[SDL_SCANCODE_SPACE] && m_CurrentShootCooldown <= 0.f)
	{
		m_CurrentShootCooldown = m_ShootCooldown;

		m_pBulletBool->ShootBullet(Bullet::ShootData(
			Vector2f{ m_XPosition, m_YPosition },
			Vector2f{ 0, m_BulletSpeed },
			true
		));
	}
}
