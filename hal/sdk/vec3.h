#pragma once
#include "DxINC/SimpleMath.h"

using namespace DirectX::SimpleMath;

/*
#include <vector>

class Vector3
{
public:
	float x, y, z;

	Vector3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector3()
	{
		x = y = z = 0;
	}
	float length()
	{
		return (float)sqrt(x * x + y * y + z * z);
	}
	float dotproduct(Vector3 dot)
	{
		return (x * dot.x + y * dot.y + z * dot.z);
	}

	float Distance(Vector3& from, Vector3& to)
	{
		return Vector3(from.x - to.x, from.y - to.y, from.z - to.z).length();
	}
}; */