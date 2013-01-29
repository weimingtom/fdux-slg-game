#pragma once

#include "GUIScene.h"
#include "GUISLWindow.h"

#include "Squad.h"

#include "WeaponItemBox.h"
#include "SquadItemBox.h"
#include "SkillItemBox.h"

#include <vector>

#define SQUAD_SKILL_NUM 5
#define SQUAD_PASSIVE_SKILL_NUM 5
#define SQUAD_USE_EQUIP_NUM 5
#define SQUAD_EFFECT_NUM 5

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
	void setItemInfo(WeaponItemData* item);
	void setSkillInfo(SkillItemData* item);
	void showArmyInfo();
	void showSkill(int type);
	void showSkillItem(int type,std::string skillListPath);
	void trainSkill(SkillItemData* skill);

	void eventMouseItemActivate(MyGUI::ItemBox* _sender, size_t _index);
	void eventSelectItemAccept(MyGUI::ItemBox* _sender, size_t _index);
	void eventSquadMouseItemActivate(MyGUI::ItemBox* _sender, size_t _index);
	void eventTabChangeSelect(MyGUI::TabControl* _sender, size_t _index);

	void eventMouseSkillActivate(MyGUI::ItemBox* _sender, size_t _index);
	void eventSelectSkillAccept(MyGUI::ItemBox* _sender, size_t _index);
	void eventSkillTabChangeSelect(MyGUI::TabControl* _sender, size_t _index);

	std::string itemCompare(Squad* newSquad,Squad* oldSquad,AttrType type);

	std::string getItemNameFormLanguage(std::string type,std::string name);

	void onSave(MyGUI::Widget* _sender);
	void onLoad(MyGUI::Widget* _sender);
	void onExit(MyGUI::Widget* _sender);
	void onOtherSceneNotify(std::string arg);
	void onEquipment(MyGUI::Widget* _sender);
	void onSkill(MyGUI::Widget* _sender);
	void onSoilder(MyGUI::Widget* _sender);

	MyGUI::Button* mSaveButton;
	MyGUI::Button* mLoadButton;
	MyGUI::Button* mExitButton;
	MyGUI::Button* mEquipmentButton;
	MyGUI::Button* mSkillButton;
	MyGUI::Button* mSoilderButton;
	MyGUI::TextBox* mSoilderButtonText;

	MyGUI::ImageBox* mSupplyBG;

	WeaponItemBox* mPWeaponItemBox;
	WeaponItemBox* mSWeaponItemBox;
	WeaponItemBox* mShieldItemBox;
	WeaponItemBox* mHorseItemBox;
	WeaponItemBox* mArmorItemBox;
	WeaponItemBox* mSoilderItemBox;
	WeaponItemBox* mRetainerItemBox;

	SkillItemBox* mActiveItemBox;
	SkillItemBox* mPassiveItemBox;
	SkillItemBox* mEquipItemBox;

	SquadItemBox* mSquadItemBox;

	MyGUI::Window* mArmyWindow;
	MyGUI::Window* mControlWindow;
	MyGUI::Window* mAttributeWindow;
	MyGUI::Window* mItemWindow;
	MyGUI::Window* mTemaWindow;
	MyGUI::Window* mItemAttributeWindow;

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
	MyGUI::TextBox* mTextRetainer;
	MyGUI::ImageBox* mRetainerSkill1;
	MyGUI::ImageBox* mRetainerSkill2;
	MyGUI::ImageBox* mRetainerImage;

	MyGUI::ImageBox* mItemIcon;
	MyGUI::TextBox* mTextItemName;
	MyGUI::TextBox* mTextItemPrice;
	MyGUI::EditBox* mTextItemInfo;

	MyGUI::TextBox* mTextArmyInfo;

	MyGUI::TabControl* mSkillTabControl;
	MyGUI::TabControl* mWeaponTabControl;
	MyGUI::TextBox* mSquadPassivePoint;
	MyGUI::TextBox* mSquadActivePoint;
	MyGUI::TextBox* mSquadEquipPoint;

	std::vector<Squad*> mBattleSquad;

	int m_SquadSkillNum;
	int m_SquadPassiveSkillNum;
	int m_SquadUseEquipNum;
	int m_SquadEffectNum;
	SkillType m_CurrSkillType;

	int m_Money;
	int m_CurrSquadIndex;
	EquipmentType m_CurrSelectType;
	WeaponItemData* m_CurrSquadEquipItem;

	std::string mNextScript;

	GUISLWindow* SLWindow;

	bool mIsHideScene;

	std::map<int,std::string> mSquadTypeMap;
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