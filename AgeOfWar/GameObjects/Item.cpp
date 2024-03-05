#include "pch.h"
#include "Item.h"
#include "Player.h"

Item* Item::Create(Types t, int v)
{
    Item* newItem = new Item();
    newItem->type = t;
    newItem->value = v;

    switch (newItem->type)
    {
    case Types::Ammo:
        newItem->textureId = "graphics/ammo_pickup.png";
        break;
    case Types::Health:
        newItem->textureId = "graphics/health_pickup.png";
        break;
    case Types::None:
        newItem->textureId = "";
        break;
    }

    return newItem;
}

Item::Item(const std::string& name) : SpriteGo(name)
{
}

void Item::Reset()
{
    SpriteGo::Reset();
    time = 0.f;

    player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));
    SetOrigin(Origins::MC);
}

void Item::FixedUpdate(float dt)
{
    SpriteGo::FixedUpdate(dt);

    if (player == nullptr)
        return;

    time += dt;
    if (time > duration)
    {
        SetActive(false);
        SCENE_MGR.GetCurrentScene()->RemoveGo(this);
        return;
    }



    if (GetGlobalBounds().intersects(player->GetGlobalBounds()))
    {
        player->OnItem(this);
        SetActive(false);
        SCENE_MGR.GetCurrentScene()->RemoveGo(this);
    }
}
