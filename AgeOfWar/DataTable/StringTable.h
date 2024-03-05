#pragma once
#include "DataTable.h"

class StringTable : public DataTable
{
protected:
	std::unordered_map<std::string, std::string> table;
	Languages currLang = Languages::Korean;

public:
	StringTable(Types t);
	~StringTable() override;

	;
	const std::string& Get(const std::string& id);

	bool Load() override;
	bool Load(Languages lanuage);

	void Release() override;

};

