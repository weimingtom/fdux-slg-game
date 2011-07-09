#ifndef SCRIPTEDITOR_H
#define SCRIPTEDITOR_H

#include <QtGui/QMainWindow>
#include "ui_scripteditor.h"

#include "GUICommon.h"

#include "LuaSystem.h"

#include "OgreCore.h"

#include "ScriptParse.h"

class ScriptEditor : public QMainWindow,public Ogre::WindowEventListener,public LuaSystemListener
{
	Q_OBJECT

public:
	ScriptEditor(QWidget *parent = 0, Qt::WFlags flags = 0);
	~ScriptEditor();

	void timerEvent(QTimerEvent * event);
	bool windowClosing(Ogre::RenderWindow *rw);

	void onError(std::string error);
	void onComplete();

public slots:
	void showImageButton();
	void SetTextColorButton();
	void SetDialogButton();
	void ShowTextButton();
	void ShowRoleNameButton();
	void SetRoleNameColorButton();
	void ClearTextButton();
	void RunLuaScript();
	void ParseScript();
	void ClearScript();
private:
	Ui::ScriptEditorClass ui;
	GUIDialogAttribute mDialogAttribute;
	ScriptParse mScriptParse;
};

#endif // SCRIPTEDITOR_H
