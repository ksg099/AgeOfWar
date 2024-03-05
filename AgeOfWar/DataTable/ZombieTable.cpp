#include "pch.h"
#include "ZombieTable.h"
#include "rapidcsv.h"

DataZombie ZombieTable::Undefined = {};

ZombieTable::ZombieTable(DataTable::Types t)
	:DataTable(t)
{
}

ZombieTable::~ZombieTable()
{
	Release();
}

const DataZombie& ZombieTable::Get(Zombie::Types id)
{
	auto find = table.find(id);
	if (find == table.end())
	{
		std::cout << "좀비 테이블 없는 아이디..." << std::endl;
		return Undefined;
	}
	return find->second;
}

bool ZombieTable::Load()
{
	Release();

	rapidcsv::Document doc("tables/ZombieTable.csv");
	for (int i = 0; i < doc.GetRowCount(); ++i)
	{
		auto row = doc.GetRow<std::string>(i);
		Zombie::Types id = (Zombie::Types)std::stoi(row[0]);
		if (table.find(id) != table.end())
		{
			std::cout << "좀비 테이블 중복 아이디..." << std::endl;
			return false;
		}
		table[id] = DataZombie();

		table[id].id = id;
		table[id].nameId = row[1];
		table[id].descriptionId = row[2];
		table[id].textureId = row[3];
		table[id].maxHp = std::stoi(row[4]);
		table[id].speed = std::stoi(row[5]);
		table[id].damage = std::stoi(row[6]);
		table[id].attackInterval = std::stoi(row[7]);
	}
	return true;
}

void ZombieTable::Release()
{
	table.clear();

}
