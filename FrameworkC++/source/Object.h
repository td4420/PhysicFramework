#pragma once
#include <iostream>
#include <ctime>
using namespace std;
class Object
{
public:
	string type;
	bool isClick = false;
	bool candrop = true;
	float position[4];
	int mass;
	clock_t t;
	float ax = 0;
	float ay = 0;
	int velocity;
	Object(string type);
	Object();
	void Render();
	void Drop();
	void Update(float frameTime);
	bool insideObject(int x, int y);
	void throwObject(float ax, float ay);
	float pointCenter();
};
class Rect : public Object
{
public:
	Rect(string type, float position[4], int mass, int velocity);
	void Render();
};
class Circle : public Object
{
public:
	Circle(string type, float position[4], int mass, int velocity);
	void Render();
};
class Plane : public Object
{
public:
	Plane(string type, float position[4], int mass, int velocity);
	void Render();
};