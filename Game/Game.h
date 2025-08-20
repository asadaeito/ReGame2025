#pragma once

#include "Level3DRender/LevelRender.h"

class Player;
class Background;
class GameCamera;

class Game : public IGameObject
{
public:
	Game();
	~Game();
	void InitSky();
	void Update();
	void Render(RenderContext& rc);
	//bool Start();
	
	Vector3 m_pos;
	Player* player;
	Background* backGround;
	GameCamera* gameCamera;
	SoundSource* gameBGM;
	

	SkyCube* m_skyCube; 
	int m_skyCubeType = enSkyCubeType_Day;
};
