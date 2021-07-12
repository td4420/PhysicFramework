#include "SceneManager.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "videoDriver.h"
#include "CollisionManager.h"
using namespace std;
SceneManager *SceneManager::s_Instance = NULL;
SceneManager* SceneManager::GetInstance()
{
	if (!s_Instance)
		s_Instance = new SceneManager();
	return s_Instance;
}
void SceneManager::Update(float frameTime)
{
	VideoDriver::GetInstance()->CleanScreen();
	CollisionManager cm;
	for (int i = 0; i < numberOfObject - 1; i++)
	{
		for (int j = i + 1; j < numberOfObject; j++)
		{
			if (cm.CheckCollision(listObject.at(i), listObject.at(j)))
			{
				if (listObject.at(i).pointCenter() <= listObject.at(j).pointCenter()) // compare y
				{
					listObject.at(i).candrop = false; 
				}
				else listObject.at(j).candrop = false;
			}
			else
			{
				if(listObject.at(i).isClick==false) listObject.at(i).candrop = true;
				if(listObject.at(j).isClick==false) listObject.at(j).candrop = true;
			}
		}
	}
	for (int i = 0; i < numberOfObject; i++) 
	{
		listObject.at(i).throwObject(listObject.at(i).ax,listObject.at(i).ay);
		listObject.at(i).Drop();
	}
	Render();
}
SceneManager::SceneManager()
{

}
void SceneManager::Render()
{
	VideoDriver::GetInstance()->DrawLine(1, 1, SCREEN_W-1, 1);
	VideoDriver::GetInstance()->DrawLine(1, 1, 1,SCREEN_H-1);
	VideoDriver::GetInstance()->DrawLine(SCREEN_W-1, 1, SCREEN_W-1, SCREEN_H-1);
	VideoDriver::GetInstance()->DrawLine(0, SCREEN_H-1, SCREEN_W-1, SCREEN_H-1);
	for (int i = 0; i < numberOfObject; i++)
	{
		listObject.at(i).Render();
	}
}
void SceneManager::Init()
{
	fstream file;
	file.open("SceneManager.txt", ios::in);
	if (file.is_open())
	{
		string s;
		int tmp;
		file >> s >> this->numberOfObject;	//get number of object
		getline(file, s);	//go to next line
		for (int i = 0; i<this->numberOfObject; i++)
		{
			getline(file, s);	// skip ID line
			file >> s >> s;		//get type object at second word
			Object o = Object(s);
			getline(file, s);	//go to position line
			for (int i = 0; i < 4; i++)
			{
				if (i == 3 && o.type == "CIRCLE") break;
				file >> s;
				file >> tmp;
				o.position[i] = tmp;
			}
			getline(file, s);	//go to velocity line
			file >> s >> tmp;
			o.velocity = tmp;
			if (o.type == "CIRCLE")
			{
				Circle c = Circle(o.type, o.position, o.mass, o.velocity);
				listObject.push_back(c);
			}
			if (o.type == "RECT")
			{
				Rect r = Rect(o.type, o.position, o.mass, o.velocity);
				listObject.push_back(r);
			}
			if (o.type == "PLANE")
			{
				Plane p = Plane(o.type, o.position, o.mass, o.velocity);
				listObject.push_back(p);
			}
			getline(file, s); // go to next object infor
		}
	}
}
void SceneManager::AddObject(Object *object)
{
	listObject.push_back(*object);
}