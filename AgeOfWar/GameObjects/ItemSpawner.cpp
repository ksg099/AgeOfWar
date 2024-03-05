#include "pch.h"
#include "ItemSpawner.h"
#include "GameObject.h"
#include "SceneGame.h"

ItemSpawner::ItemSpawner(const std::string& name)
    : Spawner(name) 
{
}

GameObject* ItemSpawner::Create()
{
    if (itemTypes.empty())
        return nullptr;

    Item::Types itemType = itemTypes[Utils::RandomRange(0, itemTypes.size())];
    if (Utils::RandomValue() < 0.2f)
    {
        itemType = Item::Types::Ammo;
        value = Ammovalue;
       
    }
    else if (Utils::RandomValue() < 0.21f)
    {
        itemType = Item::Types::Health;
        value = Healthvalue;
        
    }
    else
    {
        itemType = Item::Types::None;
    }
    return Item::Create(itemType, value);
}

void ItemSpawner::Reset()
{
    Spawner::Reset();
    itemTypes.clear();

    itemTypes.push_back(Item::Types::Ammo);
    itemTypes.push_back(Item::Types::Health);

    interval = 5.f;
    spawnCount = 0;
    radius = 500.f;
}

void ItemSpawner::OnDrop(const sf::Vector2f& position)
{
    GameObject* newItem = Create();

    newItem->Init();
    newItem->Reset();
    newItem->SetPosition(position);
    newItem->SetOrigin(Origins::MC);

    SCENE_MGR.GetCurrentScene()->AddGo(newItem);

}




