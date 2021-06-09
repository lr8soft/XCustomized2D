#pragma once
#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

class GameObject {
private:
	int priority = 0;
public:

	void OnRenderInit();
	void OnLogicInit();

	void OnUpdate();
	void OnRender();


};

#endif