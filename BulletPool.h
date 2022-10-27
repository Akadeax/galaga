#pragma once
#include <vector>
#include "Bullet.h"

class Bullet;
class Texture;

class BulletPool
{
public:
	explicit BulletPool();
	~BulletPool();

	void ShootBullet(Bullet::ShootData data);

	void Update(float deltaTime);
	void Draw() const;

private:
	std::vector<Bullet*> m_BulletPool{};
	Texture* m_pBulletTexture{ nullptr };
};
