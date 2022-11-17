#include "pch.h"
#include "BulletPool.h"

#include "Texture.h"
#include <iostream>

BulletPool::BulletPool()
{
	m_pBulletTexture = new Texture("./sprites/bullets.png");
}

BulletPool::~BulletPool()
{
	for (int i{ 0 }; i < m_BulletPool.size(); ++i)
	{
		delete m_BulletPool[i];
	}

	delete m_pBulletTexture;
}

void BulletPool::ShootBullet(Bullet::ShootData data)
{
	for (int i{ 0 }; i < m_BulletPool.size(); ++i)
	{
		if (!m_BulletPool[i]->IsEnabled())
		{
			m_BulletPool[i]->Enable(data);
			return;
		}
	}

	// No available bullet found
	Bullet* next{ new Bullet(m_pBulletTexture) };
	m_BulletPool.push_back(next);
	next->Enable(data);
}

void BulletPool::Update(float deltaTime)
{
	for (int i{ 0 }; i < m_BulletPool.size(); ++i)
	{
		m_BulletPool[i]->Update(deltaTime);
	}
}

void BulletPool::Draw() const
{
	for (int i{ 0 }; i < m_BulletPool.size(); ++i)
	{
		m_BulletPool[i]->Draw();
	}
}
