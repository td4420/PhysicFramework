#pragma once
#include "Object.h"
class CollisionManager
{
public:
	bool CheckCollision(Object , Object );
	bool CheckTwoRect(Rect, Rect);
	bool CheckTwoCircle(Circle, Circle);
	bool CheckCircleAndRect(Circle, Rect);
};