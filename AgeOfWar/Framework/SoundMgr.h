#pragma once
#include "Singleton.h"

class SoundMgr : public Singleton<SoundMgr>
{
	friend Singleton<SoundMgr>;
private:
	SoundMgr();
	virtual ~SoundMgr();

	sf::Sound bgm[2];
	int frontBgmIndex = 0;

	bool isFading = false;
	float fadeSpeed = 1.f;
	float fadeLimit = 0.05f;

	std::list<sf::Sound*> playing;
	std::list<sf::Sound*> waiting;

	float sfxVolume = 100.f;
	float bgmVolume = 100.f;

public:
	void SetSfxVolume(float v) { sfxVolume = v; }
	void SetBgmVolume(float v) { bgmVolume = v; }

	void Init(int totalChannels = 64);
	void Release();
	void Update(float dt);

	void PlayBgm(std::string id, bool crossFade = true);
	void StopBgm();

	void PlaySfx(std::string id, bool loop = false);
	void PlaySfx(sf::SoundBuffer& buffer, bool loop = false);

	void StopAllSfx();

};

#define SOUND_MGR (Singleton<SoundMgr>::Instance())