#pragma once
class Player:public IGameObject
{
public:
	Player();
	~Player();

	void Update();
	void Render(RenderContext& rc);
	void Move();
	void Rotation();
	void ManageState();
	void PlayAnimation();

	ModelRender m_modelRender;
	Vector3 m_position = Vector3::Zero;
	bool isDashing = false;
	int playerState = 0;
	int itemCount = 0;
	int jumpcount = 0;
private:
	enum PlayAnimationClip {
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Run,
		enAnimationClip_Jump,
		enAnimationClip_Num,
	};

	AnimationClip animationClips[enAnimationClip_Num];
	Vector3 moveSpeed;
	Quaternion rotation;
	CharacterController characterController;
	
};

