#pragma once
#include "Singleton.h"

class Scene;

enum class SceneIds
{
	None = -1,TitleScene, SceneGame, SceneDev1, SceneDev2, Count,
};

class SceneMgr : public Singleton<SceneMgr>
{
	friend class Singleton<SceneMgr>;

protected:
	std::vector<Scene*> scenes;

	SceneIds startScene = SceneIds::SceneDev1;
	SceneIds currentScene = startScene;

	SceneMgr() = default;
	virtual ~SceneMgr();

public:
	void Init();
	void Release();

	void ChangeScene(SceneIds id);
	Pause playMode = Pause::Exit;

	Scene* GetCurrentScene() { return scenes[(int)currentScene]; }

	void Update(float dt);
	void LateUpdate(float dt);
	void FixedUpdate(float dt);

	void Draw(sf::RenderWindow& window);

	SceneMgr(const SceneMgr&) = delete;
	SceneMgr(SceneMgr&&) = delete;
	SceneMgr& operator=(const SceneMgr&) = delete;
	SceneMgr& operator=(SceneMgr&&) = delete;
};

#define SCENE_MGR (SceneMgr::Instance())