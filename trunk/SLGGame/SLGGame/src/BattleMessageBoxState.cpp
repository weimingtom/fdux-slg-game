#include "BattleMessageBoxState.h"

#include "BattlePlayerState.h"
#include "BattleState.h"

#include "GUISystem.h"
#include "GUIMessageBox.h"
#include "StringTable.h"

BattleMessageBoxState::BattleMessageBoxState(BattlePlayerState* playerstate, std::string message)
:mPlayerState(playerstate)
{
	mMessageBox=static_cast<GUIMessageBox*>(GUISystem::getSingletonPtr()->createScene(MessageBoxScene));
	mMessageBox->showScene(StringTable::getSingletonPtr()->getString("IsContinueMove"));
}
BattleMessageBoxState::~BattleMessageBoxState()
{

}

void BattleMessageBoxState::update(unsigned int deltaTime)
{
	if (mMessageBox->mIsReturn)
	{
		mPlayerState->setMessageBoxReturn(mMessageBox->mYesNo);
		mMainState->PopState();
		GUISystem::getSingletonPtr()->destoryScene(MessageBoxScene);
	}
}