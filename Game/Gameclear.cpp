#include "stdafx.h"
#include "Gameclear.h"
#include "Title.h"
#include "Sound/SoundEngine.h"

Gameclear::Gameclear()
{
	g_soundEngine->ResistWaveFileBank(3, "Assets/Sound/GameclearBGM.wav");
	gameclearBGM = NewGO<SoundSource>(3);
	gameclearBGM->Init(3);
	gameclearBGM->Play(false);
}

Gameclear::~Gameclear()
{
	
}

void Gameclear::Update()
{
	if (g_pad[0]->IsTrigger(enButtonX))
	{
		NewGO<Title>(0, "title");
		DeleteGO(this);
	}
}

void Gameclear::Render(RenderContext& rc)
{
	spriteRender.Draw(rc);
}