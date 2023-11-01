#pragma once
#include "Entity.h"

class Bait final : public Entity
{
public:
	explicit Bait();
	void Throw(float const angle);
	void Update(float const t);
	bool IsThrown() const;

private:
	float m_speedX = 0;
	float m_speedY = 0;
	bool m_isThrown = false;
};

