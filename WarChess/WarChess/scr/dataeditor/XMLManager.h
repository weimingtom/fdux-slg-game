#pragma once

#include "ticpp.h"
#include <string>

class XMLManager
{
public:
	bool LoadMod(std::wstring _modName, std::wstring _langName, bool _editorMode);
	bool LoadLang(std::wstring _modName, std::wstring _langName, bool _editorMode);
	bool LoadStringTable(std::wstring _modName, std::wstring _langName, bool _editorMode);
	bool SaveData();
	bool SaveLang();
	bool SaveStringTable();

	bool AddData(std::string _parent, ticpp::Element *_element);
	bool AddLang(std::string _parent, ticpp::Element *_element);
	bool AddStringTable(ticpp::Element *_element);

	bool RemoveData(std::string _parent, std::string _child);
	bool RemoveLang(std::string _parent, std::string _child);
	bool RemoveStringTable(std::string _key);

	ticpp::Element* GetData(std::string _parent, std::string _child);
	ticpp::Element* GetLang(std::string _parent, std::string _child);
	ticpp::Element* GetStringTable(std::string _key);

	std::wstring GetDataID(std::string _parent, int _index);
	std::wstring GetLangID(std::string _parent, int _index);
	std::wstring GetStringTableID(int _index);	

	bool SetDataStr(std::string _parent, std::string _child, std::string _tag, std::string _value);
	bool SetDataInt(std::string _parent, std::string _child, std::string _tag, int _value);
	bool SetDataFloat(std::string _parent, std::string _child, std::string _tag, float _value);
	bool SetDataAttr(std::string _parent, std::string _child, std::string _tag, std::string _attr, float _value);

	bool SetLang(std::string _parent, std::string _child, std::string _tag, std::string _value);
	bool SetStringTable(std::string _key, std::string _value);

	bool SetDataID(std::string _parent, std::string _child, std::string _id);
	bool SetLangID(std::string _parent, std::string _child, std::string _id);
	bool SetStringTableID(std::string _key, std::string _id);

	int CountData(std::string _parent);
	int CountLang(std::string _parent);
	int CountStringTable();
private:
	bool CreateDataFile();
	bool CreateLangFile();
	bool CreateStringTableFile();

	std::string dataPath_;
	std::string langPath_;
	std::string stringTablePath_;

	ticpp::Document dataFile_;
	ticpp::Document langFile_;
	ticpp::Document stringTableFile_;
};