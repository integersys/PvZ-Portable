#include "ChallengePagesDialog.h"
#include "../../LawnApp.h"
#include "ChallengeScreen.h"
#include "GameButton.h"
#include "../System/PlayerInfo.h"
#include "widget/WidgetManager.h"

ChallengePagesDialog::ChallengePagesDialog(LawnApp* theApp)
	: LawnDialog(theApp, Dialogs::DIALOG_CHALLENGE_PAGES, true, "Page Selection", "", "Close Page Selection", Dialog::BUTTONS_FOOTER)
{
	mApp = theApp;
	CalcSize(150, 350);

	for (int aPage = 0; aPage < MAX_CHALLANGE_PAGES; aPage++)
	{
		LawnStoneButton* aPageButton = MakeButton(aPage, this, GetPageLabel((ChallengePage)aPage));
		mPageButtons[aPage] = aPageButton;
	}

	LayoutButtons();
}

ChallengePagesDialog::~ChallengePagesDialog()
{
	for (LawnStoneButton* aPageButton : mPageButtons)
		delete aPageButton;
}

std::string ChallengePagesDialog::GetPageLabel(ChallengePage thePage)
{
	switch (thePage)
	{
	case ChallengePage::CHALLENGE_PAGE_SURVIVAL:
		return "Survival";
	case ChallengePage::CHALLENGE_PAGE_CHALLENGE:
		return "Mini-Games";
	case ChallengePage::CHALLENGE_PAGE_LIMBO:
		return "Limbo Page";
	case ChallengePage::CHALLENGE_PAGE_PUZZLE:
		return "Puzzle";
	default:
		return "Unknown Page";
	}
}

bool ChallengePagesDialog::IsPageUnlocked(ChallengePage thePage)
{
	switch (thePage)
	{
	case ChallengePage::CHALLENGE_PAGE_SURVIVAL:
		return mApp->HasFinishedAdventure() || mApp->mPlayerInfo->mHasUnlockedSurvivalMode;
	case ChallengePage::CHALLENGE_PAGE_CHALLENGE:
		return mApp->HasFinishedAdventure() || mApp->mPlayerInfo->mHasUnlockedMinigames;
	case ChallengePage::CHALLENGE_PAGE_LIMBO:
		return mApp->HasFinishedAdventure();
	case ChallengePage::CHALLENGE_PAGE_PUZZLE:
		return mApp->HasFinishedAdventure() || mApp->mPlayerInfo->mHasUnlockedPuzzleMode;
	default:
		return false;
	}
}

void ChallengePagesDialog::LayoutButtons()
{
	int aVisibleIndex = 0;
	for (int aPage = 0; aPage < MAX_CHALLANGE_PAGES; aPage++)
	{
		LawnStoneButton* aPageButton = mPageButtons[aPage];
		aPageButton->mVisible = IsPageUnlocked((ChallengePage)aPage);
		aPageButton->mDisabled = aPage == (int)mApp->mChallengeScreen->mPageIndex;
		if (aPageButton->mVisible)
		{
			aPageButton->Resize(45, 120 + aVisibleIndex * 49, mWidth - 90, 46);
			aVisibleIndex++;
		}
	}
}

void ChallengePagesDialog::AddedToManager(WidgetManager* theWidgetManager)
{
	LawnDialog::AddedToManager(theWidgetManager);
	for (LawnStoneButton* aPageButton : mPageButtons)
		AddWidget(aPageButton);
}

void ChallengePagesDialog::RemovedFromManager(WidgetManager* theWidgetManager)
{
	LawnDialog::RemovedFromManager(theWidgetManager);
	for (LawnStoneButton* aPageButton : mPageButtons)
		RemoveWidget(aPageButton);
}

void ChallengePagesDialog::Update()
{
	LawnDialog::Update();
	LayoutButtons();
}

void ChallengePagesDialog::ButtonDepress(int theId)
{
	if (theId == Dialog::ID_OK)
	{
		mApp->KillDialog(Dialogs::DIALOG_CHALLENGE_PAGES);
		mApp->PlaySample(Sexy::SOUND_BUTTONCLICK);
		return;
	}

	if (theId >= 0 && theId < MAX_CHALLANGE_PAGES && IsPageUnlocked((ChallengePage)theId))
	{
		mApp->mChallengeScreen->mPageIndex = (ChallengePage)theId;
		mApp->mChallengeScreen->UpdateButtons();
		LayoutButtons();
		mApp->PlaySample(Sexy::SOUND_BUTTONCLICK);
	}
}

void ChallengePagesDialog::KeyDown(KeyCode theKey)
{
	if (theKey == KeyCode::KEYCODE_ESCAPE)
	{
		mApp->KillDialog(Dialogs::DIALOG_CHALLENGE_PAGES);
		mApp->PlaySample(Sexy::SOUND_BUTTONCLICK);
		return;
	}

	LawnDialog::KeyDown(theKey);
}
