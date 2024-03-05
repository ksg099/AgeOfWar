#include "pch.h"
#include "StringTable.h"
#include "rapidcsv.h"

StringTable::StringTable(Types t)
	:DataTable(t)
{
}

StringTable::~StringTable()
{
}

const std::string& StringTable::Get(const std::string& id)
{
	auto find = table.find(id);
	if (find == table.end())
		return "Undefined ID";
	return find->second;
}

bool StringTable::Load()
{
	return Load(currLang);
}

bool StringTable::Load(Languages lanuage)
{
	static std::vector<std::string > filePathArray = { "tables/StringTable_KR.csv" , "tables/StringTable_EN.csv" };

	currLang = lanuage;

	table.clear();

	rapidcsv::Document doc(filePathArray[(int)currLang], rapidcsv::LabelParams(0, -1)); //기본값 ㄴ 파일 같은경우 첫째줄이 이름(ID)을 제외 시작점지정

	//std::vector<std::string> keys = doc.GetColumn<std::string>(0);//0번줄 column이 통째로 로딩
	for (int i = 0; i < doc.GetRowCount(); ++i)
	{
		std::vector<std::string> pair = doc.GetRow<std::string>(i);
		table.insert({ pair[0],pair[1] });
	}

	return true;
}

void StringTable::Release()
{
}
