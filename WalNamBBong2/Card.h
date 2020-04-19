#pragma once
#include "pch.h"

class Card
{
private:
	string shape;
	int num;

public:
	inline void SetShape(string _shape) { shape = _shape; }
	inline void SetNum(int _num) { num = _num; }
	inline int GetNum() { return num; }
	inline string GetShape() { return shape; }

};