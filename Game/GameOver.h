#pragma once
class GameOver : public IGameObject
{
	public:
	GameOver();
	~GameOver();
	void Update();
	void Render(RenderContext& rc);
	SpriteRender spriteRender;
	SoundSource* gameOverBGM;
};

