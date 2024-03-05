#pragma once
#include "DataTable.h"
#include "Zombie.h"

struct DataZombie
{
	Zombie::Types id;

	std::string nameId;
	std::string descriptionId;

	std::string textureId;
	int maxHp;
	float speed;
	int damage;
	float attackInterval;
};

class ZombieTable : public DataTable
{
public:
	static DataZombie Undefined;

protected:
	std::unordered_map<Zombie::Types, DataZombie> table;
public:
	ZombieTable(DataTable::Types t);
	~ZombieTable()override;

	const DataZombie& Get(Zombie::Types id);

	bool Load()override;
	void Release()override;

};

