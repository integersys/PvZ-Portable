#ifndef __CHALLENGEPAGESDIALOG_H__
#define __CHALLENGEPAGESDIALOG_H__

#include "../../ConstEnums.h"
#include "LawnDialog.h"

class ChallengePagesDialog : public LawnDialog
{
public:
	LawnApp* mApp;
	LawnStoneButton* mPageButtons[MAX_CHALLANGE_PAGES];

public:
	ChallengePagesDialog(LawnApp* theApp);
	~ChallengePagesDialog() override;
	void AddedToManager(WidgetManager* theWidgetManager) override;
	void RemovedFromManager(WidgetManager* theWidgetManager) override;
	void Update() override;
	void ButtonDepress(int theId) override;
	void KeyDown(KeyCode theKey) override;

private:
	std::string GetPageLabel(ChallengePage thePage);
	bool IsPageUnlocked(ChallengePage thePage);
	void LayoutButtons();
};

#endif
