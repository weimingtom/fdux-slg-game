#pragma once

#include "GUIScene.h"

#include "BattleSquad.h"

#include "WeaponItemBox.h"
#include "SquadItemBox.h"

#include <vector>

#define SQUAD_SKILL_NUM 3
#define SQUAD_PASSIVE_SKILL_NUM 5
#define SQUAD_USE_EQUIP_NUM 3
#define SQUAD_EFFECT_NUM 4

class ItemBox;

class GUISupply
	:public GUIScene
{
public:
	GUISupply(int width,int height);
	~GUISupply(void);

	void showScene(std::string arg);
	void hideScene();

	void FrameEvent();

	GUISceneType getType()
	{
		return SupplyScene;
	}

private:
	void createBattleSquad();
	void clearBattleSquad();
	void refreshArmyList();
	void showArmy(int index);
	void showItem(int type);
	void showAttribute(int index,int itemType,std::string itemID);
	void buyItem(int index,WeaponItemData* item);

	void eventMouseItemActivate(MyGUI::ItemBox* _sender, size_t _index);
	void eventSelectItemAccept(MyGUI::ItemBox* _sender, size_t _index);
	void eventSquadMouseItemActivate(MyGUI::ItemBox* _sender, size_t _index);

	std::string itemCompare(BattleSquad* newSquad,BattleSquad* oldSquad,AttrType type);

	std::string getItemNameFormLanguage(std::string type,std::string name);

	MyGUI::ImageBox* mSupplyBG;

	WeaponItemBox* mPWeaponItemBox;
	SquadItemBox* mSquadItemBox;

	MyGUI::ImageBox* mSquadImage;
	MyGUI::TextBox* mTextSquadLeadName;
	MyGUI::TextBox* mTextSquadType;
	MyGUI::TextBox* mTextSquadLv;
	MyGUI::TextBox* mTextSquadExp;
	MyGUI::TextBox* mTextSquadPWeapon;
	MyGUI::TextBox* mTextSquadSWeapon;
	MyGUI::TextBox* mTextSquadShield;
	MyGUI::TextBox* mTextSquadArmor;
	MyGUI::TextBox* mTextSqureHorse;
	MyGUI::TextBox* mTextSquadAttack;
	MyGUI::TextBox* mTextSquadRangeAttack;
	MyGUI::TextBox* mTextSquadDefense;
	MyGUI::TextBox* mTextSquadArray;
	MyGUI::TextBox* mTextSquadAgility;
	MyGUI::TextBox* mTextSquadDetect;
	MyGUI::TextBox* mTextSquadConcealment;
	MyGUI::TextBox* mTextSquadTenacity;
	MyGUI::TextBox* mTextSquadAP;
	MyGUI::TextBox* mTextSquadCounterattack;
	MyGUI::TextBox* mTextSquadPeople;
	MyGUI::ImageBox* mSquadSkillIcon[SQUAD_SKILL_NUM];
	MyGUI::ImageBox* mSquadPassiveSkillIcon[SQUAD_PASSIVE_SKILL_NUM];
	MyGUI::ImageBox* mSquadUseEquipIcon[SQUAD_USE_EQUIP_NUM];
	MyGUI::ImageBox* mSquadEffectIcon[SQUAD_EFFECT_NUM];

	std::vector<BattleSquad*> mBattleSquad;

	int m_SquadSkillNum;
	int m_SquadPassiveSkillNum;
	int m_SquadUseEquipNum;
	int m_SquadEffectNum;

	int m_Money;
	int m_CurrSquadIndex;
	EquipmentType m_CurrSelectType;
};

class GUISupplywFactory:
	public GUISceneFactory
{
public:
	GUISupplywFactory(){}

	~GUISupplywFactory(){}

	GUIScene* CreateScene(int Width,int Height)
	{
		return new GUISupply(Width, Height);
	}
};