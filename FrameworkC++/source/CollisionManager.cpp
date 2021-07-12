#include "CollisionManager.h"
#include <cmath>
#include <algorithm>
using namespace std;
bool CollisionManager::CheckTwoCircle(Circle a, Circle b)
{
	float d = sqrt(pow(a.position[1] - b.position[1], 2) + pow(a.position[0] - b.position[0],2));
	if (d > a.position[2] + b.position[2]) return false;
	cout << "object collision detected" << endl;
	return true;
}
bool CollisionManager::CheckTwoRect(Rect a, Rect b)
{
	//If one object is on the left of another object
	if (a.position[0] + a.position[2] < b.position[0] || a.position[0] > b.position[0] + b.position[2]) return false;
	//If one object is above another object
	if (a.position[1] + a.position[3] < b.position[1] || a.position[1] > b.position[1] + b.position[3]) return false;
	cout << "object collision detected" << endl;
	return true;
}
bool CollisionManager::CheckCircleAndRect(Circle a, Rect b)
{
	int X = max(b.position[0], min(a.position[0], b.position[0] + b.position[2]));
	int Y = max(b.position[1], min(a.position[1], b.position[1] + b.position[3]));
	int Dx = X - a.position[0];
	int Dy = Y - a.position[1];
	if ((Dx*Dx + Dy*Dy) > a.position[2] * a.position[2]) return false;
	cout << "object collision detected" << endl;
	return true;
}
bool CollisionManager::CheckCollision(Object a, Object b)
{
	if (a.type == "CIRCLE" && b.type == "CIRCLE")
	{	
		Circle c1 = Circle(a.type, a.position, a.mass, a.velocity);
		Circle c2 = Circle(b.type, b.position, b.mass, b.velocity);
		return CheckTwoCircle(c1, c2);
	}
	if (a.type == "RECT"&&b.type == "RECT")
	{
		Rect r1 = Rect(a.type, a.position, a.mass, a.velocity);
		Rect r2 = Rect(b.type, b.position, b.mass, b.velocity);
		return CheckTwoRect(r1, r2);
	}
	if (a.type == "RECT" && b.type == "CIRCLE")
	{
		Rect r = Rect(a.type, a.position, a.mass, a.velocity);
		Circle c = Circle(b.type, b.position, b.mass, b.velocity);
		return CheckCircleAndRect(c,r);
	}
	if (a.type == "CIRCLE" && b.type == "RECT")
	{
		Circle c = Circle(a.type, a.position, a.mass, a.velocity);
		Rect r = Rect(b.type, b.position, b.mass, b.velocity);
		return CheckCircleAndRect(c, r);
	}
	return false;
}