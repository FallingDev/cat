#pragma once
#include "Entity.h"

class Bait
{
public:
	Entity& Get();
	void Throw(float const angle);
	void Update(float const t);

private:
	const float SPEED = 200;
	Entity m_bait = Entity("bait.png");
	float m_speedX = 0;
	float m_speedY = 0;
};

