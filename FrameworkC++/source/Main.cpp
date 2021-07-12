#include <stdio.h>
#include "esUtil.h"
#include "log.h"
#include "define.h"
#include "VideoDriver.h"
#include <crtdbg.h>
#include "SceneManager.h"
#include <string>
#include <functional>
#include <ctime>
using namespace std;
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

clock_t t;
int mouse_x, mouse_y;

void PaintObject()
{
	// Limit FPS
	DWORD start, end;
	start = GetTickCount();

	// Render something here
	VideoDriver::GetInstance()->CleanScreen();
	VideoDriver::GetInstance()->DrawCircle(100.0f, 100.0f, 100.0f);
	VideoDriver::GetInstance()->FillRect(0, 0, 100, 100);

	// Limit FPS
	end = GetTickCount();
	DWORD frameTime = end - start;
	if (frameTime < 1000.0/LIMIT_FPS)
		Sleep(1000/LIMIT_FPS - frameTime);
}

bool InitGraphics(int w, int h)
{
	// Init scene
	LOGI("Initializing...");
	glViewport(0, 0, w, h);
	LOGI("Done!");
	return true;
}

void TouchActionDown(ESContext *esContext,int x, int y)
{
	// Mouse down
	mouse_x = x;
	mouse_y = y;
	t = clock();
	int count = SceneManager::GetInstance()->numberOfObject;
	for (int i = 0; i < count; i++) {
		
		if (SceneManager::GetInstance()->listObject.at(i).insideObject(x, y))
		{
			SceneManager::GetInstance()->listObject.at(i).ax = 0;
			SceneManager::GetInstance()->listObject.at(i).ay = 0;
			SceneManager::GetInstance()->listObject.at(i).candrop = false;
			SceneManager::GetInstance()->listObject.at(i).isClick = true;
			break;
		}
	}
}

void TouchActionUp(ESContext *esContext,int x, int y)
{
	// Mouse up
	t = clock() - t;
	float Dx = x - mouse_x;
	float Dy = y - mouse_y;
	int count = SceneManager::GetInstance()->numberOfObject;
	for (int i = 0; i < count; i++)
	{
		if (SceneManager::GetInstance()->listObject.at(i).isClick)
		{
			SceneManager::GetInstance()->listObject.at(i).ax = (2 * Dx) / ((((float)t) / CLOCKS_PER_SEC)*(((float)t) / CLOCKS_PER_SEC)) / 10000;
			SceneManager::GetInstance()->listObject.at(i).ay = (2 * Dy) / ((((float)t) / CLOCKS_PER_SEC)*(((float)t) / CLOCKS_PER_SEC)) / 10000;
			SceneManager::GetInstance()->listObject.at(i).t = clock();
			SceneManager::GetInstance()->listObject.at(i).isClick = false;
			SceneManager::GetInstance()->listObject.at(i).candrop = true;

		}
	}
}

void TouchActionMove(ESContext *esContext,int x, int y)
{
	// Mouse move
	
	int count = SceneManager::GetInstance()->numberOfObject;
	for (int i = 0; i < count; i++)
	{
		if (SceneManager::GetInstance()->listObject.at(i).isClick)
		{
			if (SceneManager::GetInstance()->listObject.at(i).type == "CIRCLE")
			{
				SceneManager::GetInstance()->listObject.at(i).position[0] = x;
				SceneManager::GetInstance()->listObject.at(i).position[1] = y;
			}
			if (SceneManager::GetInstance()->listObject.at(i).type == "RECT")
			{
				SceneManager::GetInstance()->listObject.at(i).position[0] = x - SceneManager::GetInstance()->listObject.at(i).position[2] / 2;
				SceneManager::GetInstance()->listObject.at(i).position[1] = y - SceneManager::GetInstance()->listObject.at(i).position[3] / 2;
			}
			SceneManager::GetInstance()->Update(50);
		}
	}
	
}

void KeyDown(ESContext *ESContext, unsigned char keyCode, int x, int y)
{
	switch (keyCode)
	{
	case 'W':
	case 'w':
		break;
	case 'S':
	case 's':
		break;
	case 'A':
	case 'a':
		break;
	case 'D':
	case 'd':
		break;
	}
}

void KeyUp(ESContext *ESContext, unsigned char keyCode, int x, int y)
{
	switch (keyCode)
	{
	case 'W':
	case 'w':
		break;
	case 'S':
	case 's':
		break;
	case 'A':
	case 'a':
		break;
	case 'D':
	case 'd':
		break;
	}
}

void GameUpdate(ESContext *esContext, float deltaTime)
{
	// Update scene
	SceneManager::GetInstance()->Update(5);
}

void GameDraw(ESContext *esContext)
{
	// Draw scene then swap buffer to display to screen
	SceneManager::GetInstance()->Init();
	SceneManager::GetInstance()->Render();
	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

void GameExit()
{
	// Cleanup memory here
}

int main(int argc, char *argv[])
{
	ESContext esContext;
	esInitContext(&esContext );
	esCreateWindow(&esContext, "Framework", (int)SCREEN_W, (int)SCREEN_H, ES_WINDOW_RGB);
	if (!InitGraphics((int)SCREEN_W, (int)SCREEN_H))
		return 0;
	
	esRegisterDrawFunc(&esContext, GameDraw);
	esRegisterKeyDownFunc(&esContext, KeyDown);
	esRegisterKeyUpFunc(&esContext, KeyUp);
	esRegisterUpdateFunc(&esContext, GameUpdate);
	esRegisterMouseDownFunc(&esContext, TouchActionDown);
	esRegisterMouseUpFunc(&esContext, TouchActionUp);
	esRegisterMouseMoveFunc(&esContext, TouchActionMove);
	esMainLoop(&esContext);
	GameExit();
}