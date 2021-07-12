#include "Object.h"
#include "videoDriver.h"
#include <cmath>
#include <iostream>
#include <ctime>
using namespace std;
void Object::Update(float frameTime)
{

}
void Object::throwObject(float ax, float ay)
{
	t =clock() - t;
	position[0] += 0.5*ax*((((float)t) / CLOCKS_PER_SEC)*(((float)t) / CLOCKS_PER_SEC));
	position[1] += 0.5*ay*((((float)t) / CLOCKS_PER_SEC)*(((float)t) / CLOCKS_PER_SEC));
}
float Object::pointCenter()
{
	if (type == "RECT") return position[1] + position[3]/2;
	if (type == "CIRCLE") return position[1];
}
void Object::Drop()
{
	if (type == "CIRCLE")
	{
		if (position[0] + position[2] >= SCREEN_W)
		{
			cout << "edge collision detected" << endl;
			ax = -ax;
			position[0] = SCREEN_W - position[2] - 1;
		}
		if (position[0] - position[2] <= 0)
		{
			cout << "edge collision detected" << endl;
			ax = -ax;
			position[0] = position[2] + 1;
		}
		if (position[1] <= position[2])
		{
			position[1] = position[2] + 1;
			ay = -ay;
			cout << "edge collision detected" << endl;
		}
		if (position[1] + position[2] >= SCREEN_H)
		{
			candrop = false;
			ay = -ay;
			position[1] = SCREEN_H - position[2] - 1;
			cout << "edge collision detected" << endl;
		}
	}
	if (type == "RECT")
	{
		if (position[0] <= 0)
		{
			cout << "edge collision detected" << endl;
			position[0] = 1;
			ax = -ax;
		}
		if (position[0] + position[2] >= SCREEN_W)
		{
			cout << "edge collision detected" << endl;
			position[0] = SCREEN_W - position[2] - 1;
			ax = -ax;
		}
		if (position[1] <= 0)
		{
			position[1] = 1;
			ay = -ay;
			cout << "edge collision detected" << endl;
		}
		if (position[1] + position[3] >= SCREEN_H)
		{
			candrop = false;
			ay = -ay;
			position[1] = SCREEN_H - position[3] - 1;
			cout << "edge collision detected" << endl;
		}
	}
	if(candrop) position[1] += 0.3;
}
Object::Object()
{

}
Object::Object(string type)
{
	this->type = type;
}
void Object::Render()
{
	if (type == "RECT")
	{
		VideoDriver::GetInstance()->DrawRect(position[0], position[1], position[2], position[3]);
	}
	if (type == "CIRCLE")
	{
		VideoDriver::GetInstance()->DrawCircle(position[0], position[1],position[2]);
	}
	if (type == "PLANE")
	{
		VideoDriver::GetInstance()->DrawLine(position[0], position[1], position[2], position[3]);
	}
}
bool Object::insideObject(int x, int y)
{
	if (type == "CIRCLE")
	{
		float t = sqrt(pow((x - position[0]), 2.0) + pow(y - position[1], 2));
		if (t <= position[2]) return true;
		return false;
	}
	if (type == "RECT")
	{
		if (x<position[0] || x>(position[0] + position[2])) return false;
		if (y<position[1] || y>(position[1] + position[3])) return false;
		return true;
	}
	if (type == "PLANE")
	{
		if (x < position[0] && x < position[2]) return false;
		if (y < position[1] && y < position[3]) return false;
		if ((x - position[0]) / (x - position[2]) == (y - position[1]) / (y - position[3])) return true;
	}
	return false;
}
void Circle::Render()
{
	VideoDriver::GetInstance()->DrawCircle(position[0], position[1], position[2]);
}
Circle::Circle(string type, float position[4], int mass, int velocity)
{
	this->type = type;
	for (int i = 0; i < 3; i++)
	{
		this->position[i] = position[i];
	}
	this->mass = mass;
	this->velocity = velocity;
}
void Rect::Render()
{
	VideoDriver::GetInstance()->DrawRect(position[0], position[1], position[2], position[3]);
}
Rect::Rect(string type,float position[4], int mass, int velocity)
{
	this->type = type;
	for (int i = 0; i < 4; i++)
	{
		this->position[i] = position[i];
	}
	this->mass = mass;
	this->velocity = velocity;
}
void Plane::Render()
{
	VideoDriver::GetInstance()->DrawLine(position[0], position[1], position[2], position[3]);
}
Plane::Plane(string type, float position[4], int mass, int velocity)
{
	this->type = type;
	for (int i = 0; i < 4; i++)
	{
		this->position[i] = position[i];
	}
	this->mass = mass;
	this->velocity = velocity;
}