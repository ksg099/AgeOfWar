#pragma once

enum class AnimationLoopTypes
{
	Single,
	Loop,
	PingPong,
};


struct AnimationFrame
{
	std::string textureId;
	sf::IntRect texCoord;

	AnimationFrame(const std::string& id, const sf::IntRect& coord)
		: textureId(id), texCoord(coord)
	{

	}

	sf::Texture& GetTexture() const
	{
		return RES_MGR_TEXTURE.Get(textureId);
	}
};

struct AnimationClip
{
	//이부분 엑셀로
	std::string id;
	int fps= 30;
	AnimationLoopTypes loopType = AnimationLoopTypes::Single;

	std::vector< AnimationFrame> frames;

	int GetTotalFrame() const
	{
		return frames.size();
	}

	bool loadFromFile(const std::string& filePath);
};


struct AnimationEvent
{
	std::string clipId;
	int frame;
	std::function<void()> action; // <반환형(매개변수)> 옆에 꺼는 반환도 안하고 매개변수도 안받음
};

class Animator
{
protected:
	//std::unordered_map<std::string, AnimationClip> clips;
	std::queue<std::string> queue; //재생할 플레이어의 아이디 넣어둠
	std::list <AnimationEvent> eventList;
 	float  speed = 1.f;

	bool isPlaying = false;
	AnimationClip* currentClip = nullptr;
	int totalFrame = 0;
	int currentFrame = -1;
	int addFrame = 1;
	float clipDuration = 0.f;

	float accumTime = 0.f;

	sf::Sprite* target = nullptr;


public:

	Animator();
	~Animator();

	void AddEvent(const std::string& clipId, int frame, std::function<void()> action);
	void ClearEvent();

	sf::Sprite* GetTarget() const 	{return target;	}
	void SetTarget(sf::Sprite* t) { target = t; }
	
	const std::string& GetCurrentClipId() { return currentClip->id; }
	void SetSpeed(float s) { speed = s; }
	float GetSpeed() const { return speed; }

	bool IsPlaying() const { return isPlaying; }

	//void AddClip(const AnimationClip& clip);
	void SetFrame(const AnimationFrame& frame);
	void Update(float dt);
	void Play(const std::string& clipId, bool clearQueue = true); // 내가 원하는 플레이하기
	void PlayQueue(const std::string& clipId);
	void Stop();
};

