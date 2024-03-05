#include "pch.h"
#include "AniTest2.h"

void AniTest2::Init()
{
	SpriteGo::Init();
	//std::string textureId = "graphics/RubySheet.png";
	//int width = 256;
	//int height = 256;




	//{
	//	AnimationClip clip;
	//	clip.id = "IdleSide";
	//	clip.fps = 10;
	//	clip.loopType = AnimationLoopTypes::Loop;
	//	clip.frames.push_back({ textureId, {0, 3 * height, width, height } });
	//	clip.frames.push_back({ textureId, { 1 * width, 5 * height, width, height } });
	//	//animator.AddClip(clip);
	//}

	//{
	//	AnimationClip clip;
	//	clip.id = "IdleDown";
	//	clip.fps = 2;
	//	clip.loopType = AnimationLoopTypes::Loop;
	//	clip.frames.push_back({ textureId, {1 * width, 3 * height, width, height } });
	//	clip.frames.push_back({ textureId, { 1 * width, 5 * height, width, height } });
	//	//animator.AddClip(clip);

	//}

	//{
	//	AnimationClip clip;
	//	clip.id = "IdleUp";
	//	clip.fps = 2;
	//	clip.loopType = AnimationLoopTypes::Loop;
	//	clip.frames.push_back({ textureId, {2, 3 * height, width, height } });
	//	clip.frames.push_back({ textureId, { 3 * width, 5 * height, width, height } });
	//	//animator.AddClip(clip);
	//}

	//{
	//	AnimationClip clip;
	//	clip.id = "MoveSide";
	//	clip.fps =2;
	//	clip.loopType = AnimationLoopTypes::Loop;
	//	for (int i = 0; i < 4; i++)
	//	{
	//		clip.frames.push_back({ textureId, {i * width, 0, width, height } });
	//	}
	//	//animator.AddClip(clip);
	//}

	//{
	//	AnimationClip clip;
	//	clip.id = "MoveUp";
	//	clip.fps = 2;
	//	clip.loopType = AnimationLoopTypes::Loop;
	//	for (int i = 0; i < 4; i++)
	//	{
	//		clip.frames.push_back({ textureId, {i * width, height, width, height } });
	//	}
	//	//animator.AddClip(clip);
	//}

	//{
	//	AnimationClip clip;
	//	clip.id = "MoveDown";
	//	clip.fps = 2;
	//	clip.loopType = AnimationLoopTypes::Loop;
	//	for (int i = 0; i < 4; i++)
	//	{
	//		clip.frames.push_back({ textureId, {i * width, 2 * height, width, height } });
	//	}
	//	//animator.AddClip(clip);
	//}
	animator.SetTarget(&sprite);  //이거 좌표 넣는 부분 좌표 다시 수정해서 넣어야함

	clipInfos.push_back({ "animations/Idle2Side.csv", "animations/Idle2MoveSide.csv", false, Utils::GetNormal({-1, -1}) });
	clipInfos.push_back({ "animations/Idle2Up.csv", "animations/Idle2MoveUp.csv", false, {0, -1} });
	clipInfos.push_back({ "animations/Idle2Side.csv", "animations/Idle2MoveSide.csv", true, Utils::GetNormal({1, -1}) });
	
	clipInfos.push_back({ "animations/Idle2Side.csv", "animations/Idle2MoveSide.csv", false, {-1, 0} }); //왼
	clipInfos.push_back({ "animations/Idle2Side.csv", "animations/Idle2MoveSide.csv", true, {1, 0} }); //오
	
	clipInfos.push_back({ "animations/Idle2Side.csv", "animations/Idle2MoveSide.csv", false, Utils::GetNormal({-1, 1}) });
	clipInfos.push_back({ "animations/Idle2Down.csv", "animations/Idle2MoveDown.csv", false, Utils::GetNormal({-1, -1}) }); //아래
	clipInfos.push_back({ "animations/Idle2Side.csv", "animations/Idle2MoveSide.csv", true, Utils::GetNormal({1, 1}) }); //아래 오른쪽

}

void AniTest2::Reset()
{
	animator.Play("animations/Idle2Down.csv");
	SetOrigin(Origins::MC);
	SetPosition({ 0.f, 0.f });
	SetFlipX(false); //초기화

	currnetClipInfo = clipInfos[6];
}

void AniTest2::Update(float dt)
{
	//SpriteGo::Update(dt);
	animator.Update(dt);

	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	direction.y = InputMgr::GetAxis(Axis::Vertical);
	//이렇게 하면 대각선 이동할때 좀 더 빨리 이동하게 됨 아래에서 처리해줌

	float mag = Utils::Magnitude(direction);
	if (mag > 1.f) //키입력에 맞춰 direction 뽑기
	{
		direction /= mag;
	}
	//여까지

	Translate(direction * speed * dt);

	if (direction.x != 0.f || direction.y != 0.f)
	{
		auto min = std::min_element(clipInfos.begin(), clipInfos.end(),//최솟값 찾을 범위
			//람다식으로 해보자이
			[this](const ClipInfo& lhs, ClipInfo& rhs)
			{
				return Utils::Distance(direction, lhs.point)
					< Utils::Distance(direction, rhs.point);
			});
		currnetClipInfo = *min;
	}

	SetFlipX(currnetClipInfo.filpX);

	const std::string& clipId = (direction.x != 0.f || direction.y != 0.f) ?
		currnetClipInfo.move : currnetClipInfo.idle;

	if (animator.GetCurrentClipId() != clipId)
	{
		animator.Play(clipId);
	}
	
}
