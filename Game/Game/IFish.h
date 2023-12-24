#pragma once

class IFish
{
public:
	virtual int Sell() = 0;
	virtual void Uncaught() = 0;
	virtual bool IsTired() const = 0;
};