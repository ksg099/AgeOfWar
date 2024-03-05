#include "pch.h"
#include "Animator.h"
#include "rapidcsv.h"

Animator::Animator()
{
}

Animator::~Animator()
{
}
void Animator::AddEvent(const std::string& clipId, int frame, std::function<void()> action)
{
	eventList.push_back({ clipId, frame, action });
}
void Animator::ClearEvent()
{
	eventList.clear();
}
//
//void Animator::AddClip(const AnimationClip& clip)
//{
//	//중복을 허용하면 안되기 때문에 키 검사를 한다.
//	if (clips.find(clip.id) == clips.end()) //안들어있으면 end
//	{
//		//clips.insert({ clip.id , clip }); 아래 코드와 동일하다.
//		clips[clip.id] = clip; 
//	}
//}


void Animator::Update(float dt)
{
	if (!isPlaying)
		return;

	accumTime += dt * speed;
	if (accumTime < clipDuration)
		return;

	accumTime = 0.f;
	//currentFrame++;
	currentFrame += addFrame;

	if (currentFrame == totalFrame) //다 재생했을경우
	{

		if (!queue.empty()) //q가 차있을 경우
		{
			std::string id = queue.front();
			queue.pop();
			Play(id, false);
			return;
		}
		switch (currentClip->loopType)
		{
		case AnimationLoopTypes::Single:
			currentFrame = totalFrame - 1;
			break;
		case AnimationLoopTypes::Loop:
			currentFrame = 0;
			break;
		case AnimationLoopTypes::PingPong:
			if (addFrame > 0)
			{
				currentFrame = totalFrame - 2;
				addFrame = -1;
				totalFrame = -1;
			}
			else
			{
				currentFrame = 1;
				addFrame = -1;
				totalFrame = currentClip->frames.size();
			}
			break;
		}
	}

	for (auto& event : eventList)
	{
		if (currentClip->id == event.clipId && currentFrame == event.frame)
		{
			if(event.action != nullptr) //null체크후
			{
				event.action();
			}
		}
	}


	SetFrame(currentClip->frames[currentFrame]); //
}


void Animator::Play(const std::string& clipId, bool clearQueue) //이 함수 호출시 첫번째 프레임이 세팅 된다.
{

	if (clearQueue)
	{
		while (!queue.empty()) //안비워져 있으면
		{
			queue.pop(); //비워질때까지 뻄
		}
	}
	addFrame = 1;
	isPlaying = true;
	accumTime = 0.f;

	currentClip = &RES_MGR_ANI_CLIP.Get(clipId);
	//currentClip = &clips[clipId];
	currentFrame = 0;
	totalFrame = currentClip->GetTotalFrame();
	clipDuration = 1.f / currentClip->fps;
	SetFrame(currentClip->frames[currentFrame]);
	//SetFrame(currentClip->frames[0]);

}

void Animator::PlayQueue(const std::string& clipId)
{
	queue.push(clipId);
}

void Animator::Stop()
{
	isPlaying = false;
}

void Animator::SetFrame(const AnimationFrame& frame) //할때마다 프레임 바뀜
{
	target->setTexture(frame.GetTexture());
	target->setTextureRect(frame.texCoord);
}

//일단 다 해놓고 바꿔보는 걸로 합시다
//진화 할때 텍스처만 갈아끼는 형식으로 일일히 만드는것이 아닌 고민해보자
bool AnimationClip::loadFromFile(const std::string& filePath) //데이터테이블형식과 같음
{
	rapidcsv::Document doc(filePath);

	//id = doc.GetCell<std::string>(0, 0);
	id = filePath;
	fps = doc.GetCell<int>(1, 0);
	loopType = (AnimationLoopTypes)doc.GetCell<int>(2, 0);

	for (int i = 3; i < doc.GetRowCount(); i++)
	{
		auto row = doc.GetRow<std::string>(i);
		frames.push_back({ row[0],
			{std::stoi(row[1]), std::stoi(row[2]), std::stoi(row[3]),std::stoi(row[4])} });
	}
	return true;
}
