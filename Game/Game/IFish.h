#pragma once
#include "Common.h"

class IFish
{
public:
	virtual int Sell() = 0;
	virtual void Uncaught() = 0;
	virtual bool IsTired() const = 0;
	virtual Size GetSize() const = 0;
	virtual void HideFish() = 0;
	virtual bool IsEaten() const = 0;
	virtual void Eat() = 0;
};