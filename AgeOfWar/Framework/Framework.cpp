#include "pch.h"
#include "Framework.h"
#include "DataTableMgr.h"

void Framework::Init(int width, int height, const std::string& name)
{
    srand(std::time(NULL));

    windowSize.x = width;
    windowSize.y = height;

    window.create(sf::VideoMode(windowSize.x, windowSize.y), name);

    InputMgr::Init();
    SOUND_MGR.Init();
    DT_MGR.Init();
    SCENE_MGR.Init();

}

void Framework::Do()
{
    while (window.isOpen())
    {
        deltaTime = realDeltaTime = clock.restart();
        deltaTime *= timeScale;

        time += deltaTime;
        realTime += realDeltaTime;

        fixedDeltaTime += deltaTime;

        InputMgr::Clear();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            InputMgr::UpdateEvent(event);
        }
        InputMgr::Update(GetDT());
        SOUND_MGR.Update(GetDT());

        SCENE_MGR.Update(GetDT());
        SCENE_MGR.LateUpdate(GetDT());

        float fdt = fixedDeltaTime.asSeconds();
        if (fdt > fixedUpdateTime)
        {
            SCENE_MGR.FixedUpdate(fdt);
            fixedDeltaTime = sf::Time::Zero;
        }

        window.clear();
        SCENE_MGR.Draw(window);
        window.display();
    }
}

void Framework::Release()
{
    SCENE_MGR.Release();
    SOUND_MGR.Release();

    RES_MGR_TEXTURE.UnloadAll();
    RES_MGR_FONT.UnloadAll();
    RES_MGR_SOUND_BUFFER.UnloadAll();

    DT_MGR.Release();
}
