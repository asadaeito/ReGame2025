#include "stdafx.h"
#include "Background.h"

Background::Background()
{
	modelRender.Init("Assets/modelData/stage.tkm");
	physicsStaticObject.CreateFromModel(modelRender.GetModel(), modelRender.GetModel().GetWorldMatrix());
	
}

Background::~Background()
{

}

void Background::Render(RenderContext& rc)
{
	modelRender.Draw(rc);
}
