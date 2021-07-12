#pragma once
#include "Object.h"
#include <vector>
class SceneManager
{
public:
	static SceneManager* s_Instance;
	SceneManager();
	vector<Object> listObject;
	int numberOfObject;
	void Update(float frameTime);
	void Render();
	void AddObject(Object *object);
	void Init();
	static SceneManager* GetInstance();
};