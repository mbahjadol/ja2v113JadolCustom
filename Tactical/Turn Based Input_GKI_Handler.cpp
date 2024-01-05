/**
* "Turn Based Input GKI Handler.cpp" This source is additional modular external for source "Turn Based Input.cpp"
* on function "void GetKeyboardInput()" inside loop while (DequeueEvent(&InputEvent) == TRUE)
*
**/

#include "builddefines.h"
#include <stdio.h>
#include <string.h>
#include "stdlib.h"
#include "debug.h"
#include "math.h"
#include "jascreens.h"
#include "pathai.h"
#include "Animation Control.h"
#include "Animation Data.h"
#include "Event Pump.h"
#include "Timer Control.h"
#include "Handle UI.h"
#include "Isometric Utils.h"
#include "input.h"
#include "overhead.h"
#include "Sys Globals.h"
#include "screenids.h"
#include "interface.h"
#include "cursor control.h"
#include "points.h"
#include "Interactive Tiles.h"
#include "interface cursors.h"
#include "weapons.h"
#include "lighting.h"
#include "sound control.h"
#include "environment.h"
#include "Music Control.h"
#include "ai.h"
#include "renderworld.h"
#include "font control.h"
#include "worldman.h"
#include "Handle UI Plan.h"
#include "message.h"
#ifdef NETWORKED
#include "Networking.h"
#include "Communication.h"
#endif
#include "overhead map.h"
#include "world items.h"
#include "Game Clock.h"
#include "interface items.h"
#include "physics.h"
#include "ui cursors.h"
#include "worldman.h"
#include "strategicmap.h"
#include "soldier profile.h"
#include "soldier create.h"
#include "soldier add.h"
#include "dialogue control.h"
#include "interface dialogue.h"
#include "opplist.h"
#include "interactive tiles.h"
#include "messageboxscreen.h"
#include "gameloop.h"

#include "spread burst.h"
#include "explosion control.h"
#include "QuestDebug.h"
#include "assignments.h"
#include "EditScreen.h"
#include "SaveLoadGame.h"
#include "los.h"
#include "Exit Grids.h"
#include "Strategic Exit GUI.h"
#include "auto bandage.h"
#include	"Options Screen.h"
#include "squads.h"
#include "interface panels.h"
#include "soldier tile.h"
#include "Soldier functions.h"
#include "Game Events.h"
#include "english.h"
#include "Random.h"
#include "Assignments.h"
#include "Map Screen Interface.h"
#include "renderworld.h"
#include	"Quest Debug System.h"
//#include "medical.h"
#include "Arms Dealer Init.h"
#include "ShopKeeper Interface.h"
#include "GameSettings.h"
#include "vehicles.h"
#include "SaveLoadScreen.h"
#include "Air raid.h"
#include "meanwhile.h"
#include "text.h"
#include "Inventory Choosing.h"
#include "soldier macros.h"
#include "HelpScreen.h"
#include "cheats.h"
#include "displaycover.h"
#include "Tactical Save.h"
#include "history.h"
#include "Queen Command.h"
#include "PreBattle Interface.h"
#include "_Ja25EnglishText.h"
#include "Militia Control.h"
#include "Ambient Control.h"
#include "Strategic AI.h"
#include "VehicleMenu.h"

#include "Quest Debug System.h"
#include "connect.h"
#include "fresh_header.h"

#include "IMP Skill Trait.h"			// added by Flugente
#include "SkillMenu.h"					// added by Flugente
#include "Map Screen Interface Map Inventory.h"//dnl ch75 021113

#include "DisplayCover.h"				// added by Sevenfm
#include "InterfaceItemImages.h"		// added by Sevenfm
#include "DynamicDialogueWidget.h"		// added by Flugente for DelayBoxDestructionBy(...)
#include "Utilities.h"					// added by Flugente
#include "AIInternals.h"				// sevenfm
#include "Interface Cursors.h"			// sevenfm
#include "strategic.h"					// shadooow for CreateNewMerc
#include "Structure Wrap.h"

#include "Turn Based Input.h"
#include "Turn Based Input_GKI_Handler.h"

extern INT32		iSMPanelButtons[NUM_SM_BUTTONS];
extern INT32		iTEAMPanelButtons[NUM_TEAM_BUTTONS];

extern OBJECTTYPE* gpItemDescObject;

extern SOLDIERTYPE* gpSMCurrentMerc;

extern SOLDIERTYPE* FindNextActiveSquad(SOLDIERTYPE* pSoldier);

extern UINT32 guiMessageBoxImage;
extern UINT16 guiMessageBoxImageIndex;

extern BOOLEAN gfReportHitChances;
extern void ToggleItemGlow(BOOLEAN fOn);
extern BOOLEAN gfNextShotKills;
extern void BeginKeyPanelFromKeyShortcut();
extern INT32	giStartingMemValue;

extern	BOOLEAN		gfDisableRegionActive;
extern	BOOLEAN		gfUserTurnRegionActive;

extern INT16 ITEMDESC_START_X;
extern INT16 ITEMDESC_START_Y;

extern INT8 gBadMercBodyType;
extern INT8 gCivilianBodyType;
extern INT8 gCreatedMonsterType;
extern INT32 gusMapPos;


/*
*
* IMPLEMENTATIONS OF class
* GKIWhenDQEOnKD (GetKeyboardInput When DequeueEvent On Keyboard Down)
*
*
*/

void GKIWhenDQEOnKD::On_SPACE(UINT32 * puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift)
{
	// nothing in hand and either not in SM panel, or the matching button is enabled if we are in SM panel
	if (!(gTacticalStatus.uiFlags & ENGAGED_IN_CONV) &&
		((gsCurInterfacePanel != SM_PANEL) || (ButtonList[iSMPanelButtons[NEXTMERC_BUTTON]]->uiFlags & BUTTON_ENABLED)))
	{
		if (!InKeyRingPopup())
		{

			if (_KeyDown(CTRL))
			{
				checkLBEArrayIntegrity();
			}
			else if (_KeyDown(ALT))
			{
				checkLBEArrayIntegrity(true);
			}
			else if (_KeyDown(SHIFT))
			{
				SOLDIERTYPE* pNewSoldier;
				INT32		iCurrentSquad;

				if (gusSelectedSoldier != NOBODY)
				{
					// only allow if nothing in hand and if in SM panel, the Change Squad button must be enabled
					if (((gsCurInterfacePanel != TEAM_PANEL) || (ButtonList[iTEAMPanelButtons[CHANGE_SQUAD_BUTTON]]->uiFlags & BUTTON_ENABLED)))
					{
						//Select next squad
						iCurrentSquad = CurrentSquad();

						pNewSoldier = FindNextActiveSquad(MercPtrs[gusSelectedSoldier]);

						if (pNewSoldier->bAssignment != iCurrentSquad)
						{
							HandleLocateSelectMerc(pNewSoldier->ubID, LOCATEANDSELECT_MERC);

							if (gGameExternalOptions.fUseXMLSquadNames && pNewSoldier->bAssignment < min(ON_DUTY, gSquadNameVector.size()))
								ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, pMessageStrings[MSG_SQUAD_ACTIVE_STRING], gSquadNameVector[pNewSoldier->bAssignment].c_str());
							else
								//ScreenMsg( FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, pMessageStrings[ MSG_SQUAD_ACTIVE ], ( CurrentSquad( ) + 1 ) );
								ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, pMessageStrings[MSG_SQUAD_ACTIVE], (pNewSoldier->bAssignment + 1));

							// Center to guy....
							//LocateSoldier( gusSelectedSoldier, SETLOCATOR );
						}
					}
				}
			}
			else
			{
				if (gusSelectedSoldier != NOBODY)
				{ //Select next merc
					UINT8 bID;

					bID = FindNextMercInTeamPanel(MercPtrs[gusSelectedSoldier], FALSE, FALSE);

					HandleLocateSelectMerc(bID, LOCATEANDSELECT_MERC);

					ErasePath(TRUE);
					gfPlotNewMovement = TRUE;

					// Center to guy....
					LocateSoldier(gusSelectedSoldier, SETLOCATOR);
				}
			}

			*puiNewEvent = M_ON_TERRAIN;
		}
	}

}

void GKIWhenDQEOnKD::On_LEFTARROW(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift)
{
	// used for map scrolling
	if (fCtrl)
	{
		if (gusSelectedSoldier != NOBODY)
			SwapMercPortraits(MercPtrs[gusSelectedSoldier], -1);
	}
}

void GKIWhenDQEOnKD::On_RIGHTARROW(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift)
{
	// used for map scrolling
	if (fCtrl)
	{
		if (gusSelectedSoldier != NOBODY)
			SwapMercPortraits(MercPtrs[gusSelectedSoldier], 1);
	}
}

void GKIWhenDQEOnKD::On_INSERT(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift)
{
	GoIntoOverheadMap();
}

void GKIWhenDQEOnKD::On_DELETE(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift)
{
	// used for LOS display
}

void GKIWhenDQEOnKD::On_HOME(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift)
{
	if (gGameSettings.fOptions[TOPTION_3D_CURSOR])
	{
		gGameSettings.fOptions[TOPTION_3D_CURSOR] = FALSE;

		ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, pMessageStrings[MSG_3DCURSOR_OFF]);
	}
	else
	{
		gGameSettings.fOptions[TOPTION_3D_CURSOR] = TRUE;

		ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, pMessageStrings[MSG_3DCURSOR_ON]);
	}
}

void GKIWhenDQEOnKD::On_END(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift)
{
	// Lalien: commented out, to fix "end move & LOS bug" (same button has two different actions)
	//		if ( gusSelectedSoldier != NOBODY )
	//		{
	//			if ( CheckForMercContMove( MercPtrs[ gusSelectedSoldier ] ) )
	//			{
	//				// Continue
	//				ContinueMercMovement( MercPtrs[ gusSelectedSoldier ] );
	//				ErasePath( TRUE );
	//			}
	//		}
}

void GKIWhenDQEOnKD::On_PGUP(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift)
{
	if (CHEATER_CHEAT_LEVEL())
	{
		if (fCtrl)
			AttemptToChangeFloorLevel(-1); //try to go up towards ground level
	}

	if (guiCurrentScreen != DEBUG_SCREEN)
	{
		if (gusSelectedSoldier != NOBODY)
		{
			// nothing in hand and either not in SM panel, or the matching button is enabled if we are in SM panel
			if ((gpItemPointer == NULL))
			{
				GotoHeigherStance(MercPtrs[gusSelectedSoldier]);
			}
		}
	}
}

void GKIWhenDQEOnKD::On_PGDN(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift)
{
	if (CHEATER_CHEAT_LEVEL())
	{
		if (fCtrl)
			AttemptToChangeFloorLevel(+1); //try to enter a lower underground level
	}

	if (guiCurrentScreen != DEBUG_SCREEN)
	{
		if (gusSelectedSoldier != NOBODY)
		{
			// nothing in hand and either not in SM panel, or the matching button is enabled if we are in SM panel
			if ((gpItemPointer == NULL))
			{
				GotoLowerStance(MercPtrs[gusSelectedSoldier]);
			}
		}
	}
}

void GKIWhenDQEOnKD::On_BACKSPACE(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift)
{
	// used for stopping speech
}

void GKIWhenDQEOnKD::On_TAB(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift)
{
	// go to next tab in enhanced description box
	if ((fCtrl) && InItemDescriptionBox() && gGameSettings.fOptions[TOPTION_ENHANCED_DESC_BOX] == TRUE)
	{
		if ((Item[gpItemDescObject->usItem].usItemClass & IC_WEAPON || Item[gpItemDescObject->usItem].usItemClass & IC_PUNCH)
			&& gubDescGenPage == 0 && gubDescBoxPage == 1)
		{
			gubDescGenPage = 1;
		}
		else if (gubDescBoxPage < 2)
		{
			gubDescGenPage = 0;
			gubDescBoxPage++;
		}
		else
		{
			gubDescBoxPage = 0;
		}
		HandleItemDescTabButton();
	}
	// nothing in hand and either not in SM panel, or the matching button is enabled if we are in SM panel
	else if ((gpItemPointer == NULL) &&
		((gsCurInterfacePanel != SM_PANEL) || (ButtonList[iSMPanelButtons[UPDOWN_BUTTON]]->uiFlags & BUTTON_ENABLED)))
	{
		UIHandleChangeLevel(NULL);

		if (gsCurInterfacePanel == SM_PANEL)
		{
			// Remember soldier's new value
			gpSMCurrentMerc->bUIInterfaceLevel = (INT8)gsInterfaceLevel;
		}
	}
}

void GKIWhenDQEOnKD::On_F1(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift)
{
	if (fShift)
	{
		HandleSelectMercSlot(0, LOCATE_MERC_ONCE);
	}
#ifdef JA2TESTVERSION
	else if (fAlt)
	{
		TestMeanWhile(15);
	}
	else if (fCtrl)
	{
		TestMeanWhile(10);
	}
#endif
	else
		HandleSelectMercSlot(0, LOCATEANDSELECT_MERC);
}

void GKIWhenDQEOnKD::On_F2(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift)
{
	if (fShift)
		HandleSelectMercSlot(1, LOCATE_MERC_ONCE);
#ifdef JA2TESTVERSION
	else if (fAlt)
	{
		TestMeanWhile(1);
	}
	else if (fCtrl)
	{
		TestMeanWhile(11);
	}
#endif
	else
		HandleSelectMercSlot(1, LOCATEANDSELECT_MERC);
}

void GKIWhenDQEOnKD::On_F3(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift)
{
	if (fShift)
		HandleSelectMercSlot(2, LOCATE_MERC_ONCE);
#ifdef JA2TESTVERSION
	else if (fAlt)
	{
		TestMeanWhile(2);
	}
	else if (fCtrl)
	{
		TestMeanWhile(12);
	}
#endif
	else
		HandleSelectMercSlot(2, LOCATEANDSELECT_MERC);
}

void GKIWhenDQEOnKD::On_F4(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift)
{
	if (fShift)
		HandleSelectMercSlot(3, LOCATE_MERC_ONCE);
#ifdef JA2TESTVERSION
	else if (fAlt)
	{
		TestMeanWhile(3);
	}
	else if (fCtrl)
	{
		TestMeanWhile(13);
	}
#endif
	else
		HandleSelectMercSlot(3, LOCATEANDSELECT_MERC);
}

void GKIWhenDQEOnKD::On_F5(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift)
{
	if (fShift)
		HandleSelectMercSlot(4, LOCATE_MERC_ONCE);
#ifdef JA2TESTVERSION
	else if (fAlt)
	{
		TestMeanWhile(4);
	}
	else if (fCtrl)
	{
		TestMeanWhile(14);
	}
#endif
	else
		HandleSelectMercSlot(4, LOCATEANDSELECT_MERC);
}

void GKIWhenDQEOnKD::On_F6(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift)
{
	if (fShift)
		HandleSelectMercSlot(5, LOCATE_MERC_ONCE);
#ifdef JA2TESTVERSION
	else if (fAlt)
		TestMeanWhile(5);
	else if (fCtrl)
		TestMeanWhile(15);
#endif
	else
		HandleSelectMercSlot(5, LOCATEANDSELECT_MERC);
}

void GKIWhenDQEOnKD::On_F7(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift)
{
	if (fShift)
		HandleSelectMercSlot(6, LOCATE_MERC_ONCE);
#ifdef JA2TESTVERSION
	else if (fAlt)
		TestMeanWhile(16);
#endif
	else
		HandleSelectMercSlot(6, LOCATEANDSELECT_MERC);
}

void GKIWhenDQEOnKD::On_F8(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift)
{
	if (fShift)
		HandleSelectMercSlot(7, LOCATE_MERC_ONCE);
#ifdef JA2TESTVERSION
	else if (fAlt)
		TestMeanWhile(7);
#endif
	else
		HandleSelectMercSlot(7, LOCATEANDSELECT_MERC);
}

void GKIWhenDQEOnKD::On_F9(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift)
{
	if (fShift)
		HandleSelectMercSlot(8, LOCATE_MERC_ONCE);
#ifdef JA2TESTVERSION
	else if (fCtrl)
		TestMeanWhile(8);
#endif
	else
	{
#ifdef JA2EDITOR
		* puiNewEvent = I_ENTER_EDIT_MODE;
		gfMercResetUponEditorEntry = !fAlt;
		return;
#endif
		HandleSelectMercSlot(8, LOCATEANDSELECT_MERC);
	}
}

void GKIWhenDQEOnKD::On_F10(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift)
{
	if (fShift)
		HandleSelectMercSlot(9, LOCATE_MERC_ONCE);
#ifdef JA2TESTVERSION
	else if (fAlt)
		TestMeanWhile(9);
#endif
	else
		HandleSelectMercSlot(9, LOCATEANDSELECT_MERC);
}

void GKIWhenDQEOnKD::On_F11(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift)
{
	if (fAlt)
	{
#ifdef JA2TESTVERSION
		SOLDIERTYPE* pSoldier;

		// Get selected soldier
		if (GetSoldier(&pSoldier, gusSelectedSoldier))
		{
			if (pSoldier->ubID == 46)
			{
				// Change guy to drunk larry
				ForceSoldierProfileID(pSoldier, 47);
			}
			else
			{
				// Change guy to normal larry
				ForceSoldierProfileID(pSoldier, 46);
			}

			// Dirty interface
			DirtyMercPanelInterface(pSoldier, DIRTYLEVEL2);
		}
#endif
	}
	else
	{
		if (DEBUG_CHEAT_LEVEL())
		{
			GetMouseMapPos(&gsQdsEnteringGridNo);
			LeaveTacticalScreen(QUEST_DEBUG_SCREEN);
		}
	}
}

void GKIWhenDQEOnKD::On_F12(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift)
{
#ifdef JA2TESTVERSION
	if (fAlt)
	{
		UINT8 ubProfile = TONY;

		GetMouseMapPos(&gsQdsEnteringGridNo);
		AddShopkeeperToGridNo(ubProfile, gsQdsEnteringGridNo);
		EnterShopKeeperInterfaceScreen(ubProfile);
	}
#endif
	//clear tactical of messages
	if (fCtrl)
	{
		ClearTacticalMessageQueue();
	}
	else if (!fAlt)
	{
		ClearDisplayedListOfTacticalStrings();
	}
}

void GKIWhenDQEOnKD::On_MinusOrUnderscore(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift)
{
	//if the display cover or line of sight is being displayed
	if (_KeyDown(END) || _KeyDown(DEL))
	{
		//if( _KeyDown( DEL ) )
			//ChangeSizeOfDisplayCover( gGameSettings.ubSizeOfDisplayCover - 1 );

		//if( _KeyDown( END ) )
			//ChangeSizeOfLOS( gGameSettings.ubSizeOfLOS - 1 );
	}
	else
	{
		if (fAlt)
		{
			if (MusicGetVolume() >= 20)
				MusicSetVolume(MusicGetVolume() - 20);
			else
				MusicSetVolume(0);
		}
		else if (fCtrl)
		{
#ifdef JA2TESTVERSION
			gTacticalStatus.bRealtimeSpeed = max(1, gTacticalStatus.bRealtimeSpeed - 1);
			ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, L"Decreasing Realtime speed to %d", gTacticalStatus.bRealtimeSpeed);
#endif
		}
		else
		{
#ifdef JA2TESTVERSION
			ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, L"Using Normal Scroll Speed");
			gubCurScrollSpeedID = 1;
#endif
		}
	}
}

void GKIWhenDQEOnKD::On_Plus(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift)
{
#ifdef JA2TESTVERSION
	if (fAlt)
	{
		if (MusicGetVolume() <= 107)
			MusicSetVolume(MusicGetVolume() + 20);
		else
			MusicSetVolume(127);
	}
	else if (fCtrl)
	{
		gTacticalStatus.bRealtimeSpeed = min(MAX_REALTIME_SPEED_VAL, gTacticalStatus.bRealtimeSpeed + 1);
		ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, L"Increasing Realtime speed to %d", gTacticalStatus.bRealtimeSpeed);
	}
	else
	{
		ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, L"Using Higher Scroll Speed");
		gubCurScrollSpeedID = 2;
	}
#endif
}

void GKIWhenDQEOnKD::On_Equal(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift)
{
	//if the display cover or line of sight is being displayed
	if (_KeyDown(END) || _KeyDown(DEL))
	{
		//f( _KeyDown( DEL ) )
			//ChangeSizeOfDisplayCover( gGameSettings.ubSizeOfDisplayCover + 1 );

		//if( _KeyDown( END ) )
			//ChangeSizeOfLOS( gGameSettings.ubSizeOfLOS + 1 );
	}
	else
	{

#ifdef JA2TESTVERSION
		if (fAlt)
		{
			WarpGameTime(60, TRUE);
			return;
		}
#endif

		// ATE: This key will select everybody in the sector
		// Buggler: Disabled check for all merc display cover in turnbased mode
		//if ( !(gTacticalStatus.uiFlags & INCOMBAT) )
		//{
		HandleTBSelectAllMercs();
		//}
	}
}

void GKIWhenDQEOnKD::On_Comma(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	// Flugente: alternate for people without mousewheel to aim auto-only weapons
	if (gGameExternalOptions.bAimedBurstEnabled && gCurrentUIMode == CONFIRM_ACTION_MODE)
	{
		SOLDIERTYPE* pSoldier;

		if (GetSoldier(&pSoldier, gusSelectedSoldier))
		{
			HandleRightClickAdjustCursor(pSoldier, usMapPos);
		}
	}
}

void GKIWhenDQEOnKD::On_Dot(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	// added by Flugente
	if (fCtrl && fAlt) //jikuja: Create item by reusing old entered number
	{
		if (CHEATER_CHEAT_LEVEL())
		{
			CheatCreateItem();
		}
	}
	else if (fCtrl)
	{
		if (gusSelectedSoldier != NOBODY)
		{
			HandleTacticalFunctionSelection(MercPtrs[gusSelectedSoldier], usMapPos);
		}
	}
	else if (fAlt)
	{
		if (CHEATER_CHEAT_LEVEL())
		{
			if (gusSelectedSoldier != NOBODY)
			{
				DoMessageBox(MSG_BOX_BASIC_SMALL_BUTTONS, L"Enter ItemID", GAME_SCREEN, MSG_BOX_FLAG_INPUTBOX, ItemCreationCallBack, NULL);
			}
		}
	}
	else
	{
		SetScopeMode(usMapPos);
	}

}

void GKIWhenDQEOnKD::On_Slash(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	// Center to guy....
	if (gusSelectedSoldier != NOBODY)
	{
		LocateSoldier(gusSelectedSoldier, 10);
	}
}

void GKIWhenDQEOnKD::On_BackSlash(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	if (gusSelectedSoldier != NOBODY)
	{
		SOLDIERTYPE* pSoldier;
		if (GetSoldier(&pSoldier, gusSelectedSoldier))
		{
			if (pSoldier->CanBreakWindow())
			{
				if (EnoughPoints(pSoldier, GetAPsToBreakWindow(pSoldier, TRUE), BP_USE_CROWBAR, TRUE))
					pSoldier->BreakWindow();
			}
			else if (pSoldier->CanStartDrag())
			{
				INT32 sNewGridNo = NewGridNo(pSoldier->sGridNo, DirectionInc(pSoldier->ubDirection));

				if (!TileIsOutOfBounds(sNewGridNo) && sNewGridNo != pSoldier->sGridNo)
				{
					if (EnoughPoints(pSoldier, GetAPsToStartDrag(pSoldier, sNewGridNo), 0, TRUE))
						pSoldier->StartDrag();
				}
			}
		}
	}
}

void GKIWhenDQEOnKD::On_BackQuote(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	if (fAlt)
	{
		HandleTacticalStoreInvItem();
	}
	else if (!AreInMeanwhile())
		// Switch panels...
	{
		ToggleTacticalPanels();
	}
}

void GKIWhenDQEOnKD::On_One(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	if (fCtrl && fAlt)
	{
		if (CHEATER_CHEAT_LEVEL())
		{
			//ChangeSoldiersBodyType( TANK_NW, TRUE );
			// MercPtrs[ gusSelectedSoldier ]->flags.uiStatusFlags |= SOLDIER_CREATURE;
			//EVENT_InitNewSoldierAnim( MercPtrs[ gusSelectedSoldier ], CRIPPLE_BEG, 0 , TRUE );
		}
	}
	else if (fAlt)
	{
		HandleTacticalTakeInvItem(gGameExternalOptions.iQuickItem1);
	}
	else
		ChangeCurrentSquad(0);
}

void GKIWhenDQEOnKD::On_Two(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{

	if (fCtrl && fAlt)
	{
		if (CHEATER_CHEAT_LEVEL())
		{
			ChangeSoldiersBodyType(INFANT_MONSTER, TRUE);
		}
	}
	else if (fAlt)
	{
		HandleTacticalTakeInvItem(gGameExternalOptions.iQuickItem2);
	}
	else if (fCtrl) //toggle between the different npc debug modes
	{
		if (CHEATER_CHEAT_LEVEL())
		{
			ToggleQuestDebugModes(QD_NPC_MSG);
		}
	}
	else
		ChangeCurrentSquad(1);
}

void GKIWhenDQEOnKD::On_Three(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	if (fCtrl && fAlt)
	{
		if (CHEATER_CHEAT_LEVEL())
		{
			MercPtrs[gusSelectedSoldier]->EVENT_InitNewSoldierAnim(KID_SKIPPING, 0, TRUE);

			//ChangeSoldiersBodyType( LARVAE_MONSTER, TRUE );
			//MercPtrs[ gusSelectedSoldier ]->usAttackingWeapon = TANK_CANNON;
			//LocateSoldier( gusSelectedSoldier, FALSE );
			//EVENT_FireSoldierWeapon( MercPtrs[ gusSelectedSoldier ], sMapPos );
		}
	}
	else if (fAlt)
	{
		HandleTacticalTakeInvItem(gGameExternalOptions.iQuickItem3);
	}
	else if (fCtrl) //toggle between the different npc debug modes
	{
		if (CHEATER_CHEAT_LEVEL())
		{
			CreateBloodCat();
		}
	}
	else
		ChangeCurrentSquad(2);

}

void GKIWhenDQEOnKD::On_Four(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	if (fCtrl && fAlt)
	{
		if (CHEATER_CHEAT_LEVEL())
		{
			ChangeSoldiersBodyType(CRIPPLECIV, TRUE);
		}
	}
	else if (fAlt)
	{
		HandleTacticalTakeInvItem(gGameExternalOptions.iQuickItem4);
	}
	else
		ChangeCurrentSquad(3);

	//ChangeSoldiersBodyType( BLOODCAT, FALSE );
}

void GKIWhenDQEOnKD::On_Five(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	if (fCtrl && fAlt)
	{
		if (CHEATER_CHEAT_LEVEL())
		{
			ChangeSoldiersBodyType(YAM_MONSTER, TRUE);
		}
	}
	else if (fAlt)
	{
		HandleTacticalTakeInvItem(gGameExternalOptions.iQuickItem5);
	}
	else
	{
		ChangeCurrentSquad(4);

		if (is_networked)
			grid_display();//hayden
	}
}

void GKIWhenDQEOnKD::On_Six(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	if (fCtrl && fAlt)
	{
		if (CHEATER_CHEAT_LEVEL())
		{
			ChangeSoldiersBodyType(BLOODCAT, TRUE);
		}
	}
	else if (fAlt)
	{
		HandleTacticalTakeInvItem(gGameExternalOptions.iQuickItem6);
	}
	else
	{
		ChangeCurrentSquad(5);
	}
}

void GKIWhenDQEOnKD::On_Seven(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	if (fAlt)
	{
		HandleTacticalTakeInvItem(gGameExternalOptions.iQuickItem7);
	}
	else
	{
		ChangeCurrentSquad(6);
	}
}

void GKIWhenDQEOnKD::On_Eight(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	if (fAlt)
		HandleTacticalTakeInvItem(gGameExternalOptions.iQuickItem8);
	else
		ChangeCurrentSquad(7);
}

void GKIWhenDQEOnKD::On_Nine(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	if (fAlt)
		HandleTacticalTakeInvItem(gGameExternalOptions.iQuickItem9);
	else
		ChangeCurrentSquad(8);
}

void GKIWhenDQEOnKD::On_Zero(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	if (fAlt)
		// used for calculating item chance to get through in cheat mode
		HandleTacticalTakeInvItem(gGameExternalOptions.iQuickItem0);
	else
		ChangeCurrentSquad(9);
}

void GKIWhenDQEOnKD::On_Exclamation(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
}

void GKIWhenDQEOnKD::On_AtSign(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
}

void GKIWhenDQEOnKD::On_Hash(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
}

void GKIWhenDQEOnKD::On_DollarSign(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	if (fCtrl && gGameExternalOptions.fEnableInventoryPoolQ)//dnl ch75 021113
		DisplaySectorItemsInfo();
	else
		HandleTBSkillsMenu();
}

void GKIWhenDQEOnKD::On_Percent(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
}

void GKIWhenDQEOnKD::On_Caret(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
}

void GKIWhenDQEOnKD::On_Ampersand(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
}

void GKIWhenDQEOnKD::On_Asterix(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	if (fCtrl)
	{
		if (gTacticalStatus.uiFlags & RED_ITEM_GLOW_ON)
		{
			gTacticalStatus.uiFlags &= (~RED_ITEM_GLOW_ON);
		}
		else
		{
			gTacticalStatus.uiFlags |= RED_ITEM_GLOW_ON;
		}
	}
}

void GKIWhenDQEOnKD::On_OpenParenthesis(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
}

void GKIWhenDQEOnKD::On_CloseParenthesis(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
}

void GKIWhenDQEOnKD::On_a(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos, INT16* gCurrentFortificationStructure, UINT8* gCurrentFortificationTileLibraryIndex)
{

	if (fCtrl && fAlt)
	{
		// Flugente: fortification
		// set details on how to place fortification nodes
		// loop over all structure constructs, and select those entries that are possible in this map
		std::vector<std::pair<INT16, STR16> > dropdownvector_1 = GetCurrentSectorAllowedFortificationTileSetVector(giCurrentTilesetID);

		DropDownTemplate<DROPDOWNNR_MSGBOX_1>::getInstance().SetEntries(dropdownvector_1);

		if (!dropdownvector_1.empty())
		{
			BOOLEAN found = FALSE;
			for (std::vector<std::pair<INT16, STR16> >::iterator it = dropdownvector_1.begin(); it != dropdownvector_1.end(); ++it)
			{
				if ((*it).first == *gCurrentFortificationStructure)
				{
					found = TRUE;
					break;
				}
			}

			if (!found)
				*gCurrentFortificationStructure = dropdownvector_1[0].first;
		}

		DropDownTemplate<DROPDOWNNR_MSGBOX_1>::getInstance().SetSelectedEntryKey(*gCurrentFortificationStructure);

		std::vector<std::pair<INT16, STR16> > dropdownvector_2 = GetTileSetIndexVector(*gCurrentFortificationStructure);

		DropDownTemplate<DROPDOWNNR_MSGBOX_2>::getInstance().SetEntries(dropdownvector_2);

		if (!dropdownvector_2.empty())
		{
			BOOLEAN found = FALSE;
			for (std::vector<std::pair<INT16, STR16> >::iterator it = dropdownvector_2.begin(); it != dropdownvector_2.end(); ++it)
			{
				if ((*it).first == guiMessageBoxImageIndex)
				{
					found = TRUE;
					break;
				}
			}

			if (!found)
				guiMessageBoxImageIndex = dropdownvector_2[0].first;
		}

		DropDownTemplate<DROPDOWNNR_MSGBOX_2>::getInstance().SetSelectedEntryKey(guiMessageBoxImageIndex);

		if (dropdownvector_1.empty() || dropdownvector_2.empty())
		{
			CHAR16 text[100];
			swprintf(text, szFortificationText[4], giCurrentTilesetID, gTilesets[giCurrentTilesetID].zName);

			DoMessageBox(MSG_BOX_BASIC_STYLE, text, GAME_SCREEN, MSG_BOX_FLAG_OK, NULL, NULL);
		}
		else
		{
			CHAR16 text[100];
			swprintf(text, szFortificationText[5], giCurrentTilesetID, gTilesets[giCurrentTilesetID].zName);

			VOBJECT_DESC VObjectDesc;
			VObjectDesc.fCreateFlags = VOBJECT_CREATE_FROMFILE;

			sprintf(VObjectDesc.ImageFile, "TILESETS\\%d\\%s", giCurrentTilesetID, gStructureConstruct[*gCurrentFortificationStructure].szTileSetName);

			// even if AddVideoObject fails, we still set MSG_BOX_FLAG_IMAGE, as we might 'repair' it while the box is open
			if (!AddVideoObject(&VObjectDesc, &guiMessageBoxImage))
			{
				sprintf(VObjectDesc.ImageFile, "TILESETS\\0\\%s", gStructureConstruct[*gCurrentFortificationStructure].szTileSetName);

				AddVideoObject(&VObjectDesc, &guiMessageBoxImage);
			}

			DoMessageBox(MSG_BOX_BASIC_STYLE, text, GAME_SCREEN, (MSG_BOX_FLAG_OK | MSG_BOX_FLAG_DROPDOWN_1 | MSG_BOX_FLAG_DROPDOWN_2 | MSG_BOX_FLAG_IMAGE), FortificationSettingCallBack, NULL);
		}
	}
	else if (fCtrl)
	{
		// Flugente: fortification
		INT32 sGridNo;

		//Get the gridno the cursor is at
		GetMouseMapPos(&sGridNo);

		// a node to add a structure
		AddFortificationPlanNode(sGridNo, (INT8)gsInterfaceLevel, *gCurrentFortificationStructure, *gCurrentFortificationTileLibraryIndex, TRUE);
	}
	else if (fAlt)
	{
#ifdef JA2TESTVERSION
		//	ToggleMercsNeverQuit();
		static UINT8 ubAmbientSound = 0;

		ubAmbientSound++;

		if (ubAmbientSound >= NUM_STEADY_STATE_AMBIENCES)
		{
			ubAmbientSound = 1;
		}

		SetSteadyStateAmbience(ubAmbientSound);

#else
		//shadooow: trying to use autobandage during conversation will mess up game
		// sevenfm: don't try to activate autobandage in hostile sector
		if (CheckAutoBandage())
		{
			BeginAutoBandage();
		}
#endif
	}
	else
	{
		HandleTBSkillsMenu();
	}
}

void GKIWhenDQEOnKD::On_A(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	//CHRISL: Ammo Crate
	//MM: Ammo Box
	if (fCtrl)
		HandleTacticalAmmoCrates(AMMO_CRATE);
	else
		HandleTacticalAmmoCrates(AMMO_BOX);
}

void GKIWhenDQEOnKD::On_b(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos, INT16* gCurrentFortificationStructure, UINT8* gCurrentFortificationTileLibraryIndex)
{
	if (fAlt)
	{
		if (CHEATER_CHEAT_LEVEL())
		{
			CreateBadMerc(puiNewEvent);
			//*puiNewEvent = I_NEW_BADMERC;
		}
	}
	else if (fCtrl)
	{
		// Flugente: fortification
		INT32 sGridNo;

		//Get the gridno the cursor is at
		GetMouseMapPos(&sGridNo);

		// a node to delete a structure
		AddFortificationPlanNode(sGridNo, (INT8)gsInterfaceLevel, *gCurrentFortificationStructure, *gCurrentFortificationTileLibraryIndex, FALSE);
	}
	else
	{
		// nothing in hand and either not in SM panel, or the matching button is enabled if we are in SM panel
		if ((gpItemPointer == NULL) &&
			((gsCurInterfacePanel != SM_PANEL) || (ButtonList[iSMPanelButtons[BURSTMODE_BUTTON]]->uiFlags & BUTTON_ENABLED)))
		{
			SetBurstMode();
		}
	}
}

void GKIWhenDQEOnKD::On_B(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	if (fCtrl)
	{
		HandleSelectBadMercType();
	}
	else
		//Drop/Pick up backpack for all mercs on current map
		HandleTBBackpacks();
}

void GKIWhenDQEOnKD::On_c(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	if (fAlt && fCtrl)
	{
		if (CHEATER_CHEAT_LEVEL())
		{
			ToggleCliffDebug();
		}
	}
	else if (fAlt)
	{
		if (CHEATER_CHEAT_LEVEL())
		{
			// JADOL -- Add to support selection civilian body type with CTRL+C
			GetMouseMapPos(&gusMapPos); // set mouse position to create civilian
			CreateCivillian(gCivilianBodyType);
			// -- 
		}
	}
	else if (fCtrl)
	{
		HandleTacticalCoverMenu();
	}
	else
	{
		HandleStanceChangeFromUIKeys(ANIM_CROUCH);
	}
}

void GKIWhenDQEOnKD::On_C(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	if (fAlt)
		ToggleHostileTrapsView();	// added by Flugente
	else if (fCtrl)
	{
		if (CHEATER_CHEAT_LEVEL())
		{
			// JADOL -- Add to support selection civilian body type with CTRL+C
			GetMouseMapPos(&gusMapPos); // set mouse position to create civilian
			HandleSelectCreateCivilian();
			// --
		}
	}
	else
		ToggleEnemyView();
}

void GKIWhenDQEOnKD::On_d(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	if (gTacticalStatus.uiFlags & TURNBASED && gTacticalStatus.uiFlags & INCOMBAT)
	{
		if (gTacticalStatus.ubCurrentTeam == gbPlayerNum)
		{
			// nothing in hand and the Done button for whichever panel we're in must be enabled
			if ((gpItemPointer == NULL) && !gfDisableTacticalPanelButtons &&
				(((gsCurInterfacePanel == SM_PANEL) && (ButtonList[iSMPanelButtons[SM_DONE_BUTTON]]->uiFlags & BUTTON_ENABLED)) ||
					((gsCurInterfacePanel == TEAM_PANEL) && (ButtonList[iTEAMPanelButtons[TEAM_DONE_BUTTON]]->uiFlags & BUTTON_ENABLED))))
			{
				if (fAlt)
				{
					INT32 cnt;
					SOLDIERTYPE* pSoldier;

					if (CHEATER_CHEAT_LEVEL())
					{
						for (pSoldier = MercPtrs[gbPlayerNum], cnt = 0; cnt <= gTacticalStatus.Team[gbPlayerNum].bLastID; cnt++, pSoldier++)
						{
							if (pSoldier->bActive && pSoldier->stats.bLife > 0)
							{
								// Get APs back...
								pSoldier->CalcNewActionPoints();

								fInterfacePanelDirty = DIRTYLEVEL2;
							}
						}
					}
				}
				else
				{
					//End turn only if in combat and it is the player's turn
					if (fCtrl)
						gTacticalStatus.ubDisablePlayerInterrupts = TRUE;

					*puiNewEvent = I_ENDTURN;
				}
			}
		}
	}

#ifdef JA2TESTVERSION
	else if (fCtrl)
	{
		AdvanceToNextDay();
	}
#endif
	// sevenfm: press 'd' in realtime to start turnbased
	else
	{
		if ((gTacticalStatus.uiFlags & INCOMBAT) || (NumEnemyInSector() != 0))
		{
			EnterCombatMode(OUR_TEAM);
		}
	}
}

void GKIWhenDQEOnKD::On_D(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	// SANDRO - changed from drop all to enable soldier tooltips
	if (gGameSettings.fOptions[TOPTION_ALLOW_SOLDIER_TOOLTIPS])
	{
		gGameSettings.fOptions[TOPTION_ALLOW_SOLDIER_TOOLTIPS] = FALSE;
		ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, pMessageStrings[MSG_SOLDIER_TOOLTIPS_OFF]);
	}
	else
	{
		gGameSettings.fOptions[TOPTION_ALLOW_SOLDIER_TOOLTIPS] = TRUE;
		ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, pMessageStrings[MSG_SOLDIER_TOOLTIPS_ON]);
	}
	//	if ( gGameSettings.fOptions[TOPTION_DROP_ALL] )
	//	{
	//		gGameSettings.fOptions[TOPTION_DROP_ALL] = FALSE;
	//		ScreenMsg( FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, pMessageStrings[ MSG_DROP_ALL_OFF ] );
	//	}
	//	else
	//	{
	//		gGameSettings.fOptions[TOPTION_DROP_ALL] = TRUE;
	//		ScreenMsg( FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, pMessageStrings[ MSG_DROP_ALL_ON ] );
	//	}
}

void GKIWhenDQEOnKD::On_e(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	if (fAlt)
	{
		// used for override player's turn in network game
		if (CHEATER_CHEAT_LEVEL())
		{
			ToggleViewAllMercs();
			ToggleViewAllItems();
		}
	}
#ifdef JA2BETAVERSION
	else if (fCtrl)
	{
		ToggleMapEdgepoints();
	}
#endif
	else
	{
		SOLDIERTYPE* pSoldier;

		if (gusSelectedSoldier != NOBODY)
		{
			pSoldier = MercPtrs[gusSelectedSoldier];

			if (pSoldier->aiData.bOppCnt > 0)
			{
				// Cycle....
				CycleVisibleEnemies(pSoldier);
			}
			else
			{
				ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_UI_FEEDBACK, TacticalStr[NO_ENEMIES_IN_SIGHT_STR]);
			}
		}
	}
}

void GKIWhenDQEOnKD::On_E(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	//CHRISL: drop all items
	if (gusSelectedSoldier != NOBODY && !(gTacticalStatus.fEnemyInSector))
	{
		SOLDIERTYPE* pSoldier = MercPtrs[gusSelectedSoldier];
		for (int i = BODYPOSFINAL; i < NUM_INV_SLOTS; i++)
		{
			if (pSoldier->inv[i].exists() == true)
			{
				AddItemToPool(pSoldier->sGridNo, &pSoldier->inv[i], 1, pSoldier->pathing.bLevel, 0, -1);
				//pSoldier->inv[i].initialize();
				DeleteObj(&pSoldier->inv[i]);
			}
		}
		fCharacterInfoPanelDirty = TRUE;
		fInterfacePanelDirty = DIRTYLEVEL2;
	}
}

void GKIWhenDQEOnKD::On_f(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	if (fCtrl)
	{
		if (INFORMATION_CHEAT_LEVEL())
		{
			//Toggle Frame Rate Display
			gbFPSDisplay = !gbFPSDisplay;
			DisableFPSOverlay((BOOLEAN)!gbFPSDisplay);
			if (!gbFPSDisplay)
				SetRenderFlags(RENDER_FLAG_FULL);
		}
	}
	else if (fAlt)
	{
		if (gGameSettings.fOptions[TOPTION_TRACKING_MODE])
		{
			gGameSettings.fOptions[TOPTION_TRACKING_MODE] = FALSE;

			ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, pMessageStrings[MSG_TRACKING_MODE_OFF]);
		}
		else
		{
			gGameSettings.fOptions[TOPTION_TRACKING_MODE] = TRUE;

			ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, pMessageStrings[MSG_TRACKING_MODE_ON]);
		}
	}
	else
	{
		INT32 usGridNo;

		//Get the gridno the cursor is at
		GetMouseMapPos(&usGridNo);

		// if the cursor location is valid					
		if (!TileIsOutOfBounds(usGridNo))
		{
			// sevenfm: code to check ubAdjacentSoldierCnt
			/*MAP_ELEMENT *pMapElement;
			pMapElement = &(gpWorldLevelData[usGridNo]);
			ScreenMsg(FONT_ORANGE, MSG_INTERFACE, L"adjacent soldiers %d", pMapElement->ubAdjacentSoldierCnt);*/

			// if there is a selected soldier
			if (gusSelectedSoldier != NOBODY)
			{
				//if the cursor is over someone
				if (gfUIFullTargetFound)
				{
					//Display the range to the target
					DisplayRangeToTarget(MercPtrs[gusSelectedSoldier], MercPtrs[gusUIFullTargetID]->sGridNo);
				}
				else
				{
					//Display the range to the target
					DisplayRangeToTarget(MercPtrs[gusSelectedSoldier], usGridNo);
				}
			}

			CHAR16	zOutputString[512];
			swprintf(zOutputString, L"%s: %d", pUpdateMapInfoText[19], usGridNo);
			ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, zOutputString);

			// Flugente: print out structure tileset
			if (gGameExternalOptions.fPrintStructureTileset)
			{
				STRUCTURE* pStruct = FindStructure(usGridNo, (STRUCTURE_TYPE_DEFINED));
				if (pStruct)
				{
					// if this is a multi-tile structure, be sure to use the base gridno
					if (!(pStruct->fFlags & STRUCTURE_BASE_TILE))
					{
						pStruct = FindBaseStructure(pStruct);
					}

					if (pStruct)
					{
						LEVELNODE* pNode = FindLevelNodeBasedOnStructure(pStruct->sGridNo, pStruct);

						if (pNode)
						{
							UINT32 uiTileType = 0;
							if (GetTileType(pNode->usIndex, &uiTileType))
							{
								std::string tilesestr = GetNameToTileSet(uiTileType);

								CHAR16 whcarthing[100];

								int nChars = MultiByteToWideChar(CP_ACP, 0, tilesestr.c_str(), -1, NULL, 0);
								MultiByteToWideChar(CP_UTF8, 0, tilesestr.c_str(), -1, whcarthing, nChars);

								swprintf(zOutputString, L"Tileset %d: Tilesetname: %s tileindex: %d", giCurrentTilesetID, whcarthing, pStruct->pDBStructureRef->pDBStructure->usStructureNumber);
								ScreenMsg(FONT_MCOLOR_LTGREEN, MSG_INTERFACE, zOutputString);
							}
						}
					}
				}
			}

			extern BOOLEAN InARoom(INT32 sGridNo, UINT16 * pusRoomNo);

			UINT16 usRoom;
			if (InARoom(usGridNo, &usRoom))
			{
				swprintf(zOutputString, L"Room number: %d", usRoom);
				ScreenMsg(FONT_MCOLOR_LTGREEN, MSG_INTERFACE, zOutputString);
			}

			// display height
			swprintf(zOutputString, L"Floor height: %d", gpWorldLevelData[usGridNo].sHeight);
			ScreenMsg(FONT_MCOLOR_LTGREEN, MSG_INTERFACE, zOutputString);
		}
	}
}

void GKIWhenDQEOnKD::On_F(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	if (fCtrl && UsingNewInventorySystem() == true)
	{
		HandleTBPickUpBackpacks();
	}
	SeperateItems();
	if (fCtrl)
		StackAndSort(TRUE);
	ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, pImpButtonText[11]);
}

void GKIWhenDQEOnKD::On_G(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	if (fCtrl)
	{
		if (CHEATER_CHEAT_LEVEL())
		{
			if (gTacticalStatus.uiFlags & GODMODE)
			{
				//ScreenMsg(FONT_MCOLOR_RED, MSG_INTERFACE, L"God mode deactivated.");
				gTacticalStatus.uiFlags &= (~GODMODE);
			}
			else
			{
				//ScreenMsg(FONT_MCOLOR_RED, MSG_INTERFACE, L"God mode activated.");
				gTacticalStatus.uiFlags |= GODMODE;
			}
		}
	}
	else if (gGameSettings.fOptions[TOPTION_GL_BURST_CURSOR])
	{
		gGameSettings.fOptions[TOPTION_GL_BURST_CURSOR] = FALSE;
		ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, pMessageStrings[MSG_GL_BURST_CURSOR_OFF]);
	}
	else
	{
		gGameSettings.fOptions[TOPTION_GL_BURST_CURSOR] = TRUE;
		ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, pMessageStrings[MSG_GL_BURST_CURSOR_ON]);
	}
}

void GKIWhenDQEOnKD::On_g(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos, INT32* mappos)
{
	if (fCtrl && fAlt)
	{
		HandleTBToggleFormation();
	}
	else if (fCtrl)
	{
		// Flugente: ask player whether he wants to activate cheats or not, but not in multiplayer
		if (!is_networked)
		{
			if (CHEATER_CHEAT_LEVEL())
			{
				DoScreenIndependantMessageBox(pMessageStrings[MSG_PROMPT_CHEATS_DEACTIVATE], MSG_BOX_FLAG_YESNO, ActivateCheatsMessageBoxCallBack);
			}
			else
			{
				DoScreenIndependantMessageBox(pMessageStrings[MSG_PROMPT_CHEATS_ACTIVATE], MSG_BOX_FLAG_YESNO, ActivateCheatsMessageBoxCallBack);
			}
		}
	}
	else if (fAlt)
	{
		if (CHEATER_CHEAT_LEVEL())
		{
			//*puiNewEvent = I_NEW_MERC;
			if (GetMouseMapPos(mappos))
			{
				DoMessageBox(MSG_BOX_BASIC_SMALL_BUTTONS, L"Enter ProfileID", GAME_SCREEN, MSG_BOX_FLAG_INPUTBOX, MercCreationCallBack, NULL);
			}
		}
	}
	else
	{
		HandlePlayerTogglingLightEffects(TRUE);
	}
}

void GKIWhenDQEOnKD::On_H(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	HandleTBSwapHands();
}

void GKIWhenDQEOnKD::On_h(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	if (fAlt)
	{
		if (CHEATER_CHEAT_LEVEL())
		{
			if (gfReportHitChances)
			{
				gfReportHitChances = FALSE;
			}
			else
			{
				gfReportHitChances = TRUE;
			}
		}
	}
	else if (fCtrl)
	{
		if (CHEATER_CHEAT_LEVEL())
		{
			*puiNewEvent = I_TESTHIT;
		}
	}
	else
	{
		ShouldTheHelpScreenComeUp(HELP_SCREEN_TACTICAL, TRUE);
	}
}

void GKIWhenDQEOnKD::On_I(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	//CHRISL: This will create a large number of objects for checking overloading //dnl ch75 251013
	if (fAlt && fCtrl)
	{
		if (CHEATER_CHEAT_LEVEL())
		{
			for (UINT16 i = FIRST_WEAPON; i < gMAXITEMS_READ; ++i)
			{
				if (i == 1580 || Item[i].ubWeight == 0 && !(i == 257 || i == 1006 || i == 1026 || i == 1183))//dnl!!! items 257, 1006, 1026, 1183 had weight 0 which need to be changed in xml
					continue;

				CreateItem(i, 100, &gTempObject);
				AddItemToPool(usMapPos, &gTempObject, VISIBLE, 0, WORLD_ITEM_REACHABLE, 0);
			}
		}
	}
}

void GKIWhenDQEOnKD::On_i(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	if (fCtrl && fAlt)
	{
		if (gGameSettings.fOptions[TOPTION_GLOW_ITEMS])
		{
			gGameSettings.fOptions[TOPTION_GLOW_ITEMS] = FALSE;
			ToggleItemGlow(FALSE);
		}
		else
		{
			gGameSettings.fOptions[TOPTION_GLOW_ITEMS] = TRUE;
			ToggleItemGlow(TRUE);
		}
	}
	else if (fAlt)
	{
		if (CHEATER_CHEAT_LEVEL())
		{
			CreateRandomItem();
		}
	}
	else if (fCtrl)
	{
		// free to use
	}
	else
	{
		// freed, use this only for a frequently-used new function
	}
}

bool GKIWhenDQEOnKD::On_j(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos, BOOLEAN* gfNextFireJam)
{
	if (fAlt)
	{
		if (CHEATER_CHEAT_LEVEL())
		{
			*gfNextFireJam = TRUE;
		}
	}
	else if (fCtrl)
	{
#ifdef JA2BETAVERSION
		if (CHEATER_CHEAT_LEVEL())
		{
			ToggleNPCRecordDisplay();
		}
#endif
	}
	else
	{
		SOLDIERTYPE* pjSoldier;
		if (GetSoldier(&pjSoldier, gusSelectedSoldier))
		{
			// Flugente: robots do not climb
			if (AM_A_ROBOT(pjSoldier))
				return(false);

			INT16							sAPCost;
			INT16							sBPCost;
			BOOLEAN	fNearHeigherLevel;
			BOOLEAN	fNearLowerLevel;
			INT8	bDirection;

			// Make sure the merc is not collapsed!
			if (!IsValidStance(pjSoldier, ANIM_CROUCH))
			{
				if (pjSoldier->bCollapsed && pjSoldier->bBreath < OKBREATH)
				{
					ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_UI_FEEDBACK, gzLateLocalizedString[4], pjSoldier->GetName());
				}

				return(false);
			}

			// Climb on roof
			GetMercClimbDirection(pjSoldier->ubID, &fNearLowerLevel, &fNearHeigherLevel);

			if (fNearLowerLevel)
			{
				// No climbing when wearing a backpack!
				if (!pjSoldier->CanClimbWithCurrentBackpack())
				{
					ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, NewInvMessage[NIV_NO_CLIMB]);
					return(true);
				}

				if (EnoughPoints(pjSoldier, GetAPsToClimbRoof(pjSoldier, TRUE), GetBPsToClimbRoof(pjSoldier, TRUE), FALSE))
				{
					pjSoldier->BeginSoldierClimbDownRoof();
					return(true);
				}
			}

			if (fNearHeigherLevel)
			{
				// No climbing when wearing a backpack!
				if (!pjSoldier->CanClimbWithCurrentBackpack())
				{
					ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, NewInvMessage[NIV_NO_CLIMB]);
					return(true);
				}

				if (EnoughPoints(pjSoldier, GetAPsToClimbRoof(pjSoldier, FALSE), GetBPsToClimbRoof(pjSoldier, FALSE), FALSE))
				{
					pjSoldier->BeginSoldierClimbUpRoof();
					return(true);
				}
			}

			// Jump over fence
			if (FindFenceJumpDirection(pjSoldier, pjSoldier->sGridNo, pjSoldier->ubDirection, &bDirection))
			{
				if (!pjSoldier->CanClimbWithCurrentBackpack())
				{
					//Moa: no jumping whith backpack
					//sAPCost = GetAPsToJumpFence( pjSoldier, TRUE );
					//sBPCost = GetBPsToJumpFence( pjSoldier, TRUE );
					ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, NewInvMessage[NIV_NO_CLIMB]);
					return(false);
				}
				else
				{
					sAPCost = GetAPsToJumpFence(pjSoldier, FALSE);
					sBPCost = GetBPsToJumpFence(pjSoldier, FALSE);
				}

				if (EnoughPoints(pjSoldier, sAPCost, sBPCost, FALSE))
				{
					pjSoldier->BeginSoldierClimbFence();
					return(true);
				}
			}

			// Climb on walls
			if (gGameExternalOptions.fCanClimbOnWalls == TRUE)
			{
				// No climbing when wearing a backpack!
				if (!pjSoldier->CanClimbWithCurrentBackpack())
				{
					ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, NewInvMessage[NIV_NO_CLIMB]);
					return(true);
				}

				if (FindWallJumpDirection(pjSoldier, pjSoldier->sGridNo, pjSoldier->ubDirection, &bDirection))
				{
					if (EnoughPoints(pjSoldier, GetAPsToJumpWall(pjSoldier, FALSE), GetBPsToJumpWall(pjSoldier, FALSE), FALSE))
					{
						pjSoldier->BeginSoldierClimbWall();
						return(true);
					}
				}
			}
		}
	}
	return(false);
}

void GKIWhenDQEOnKD::On_J(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	// WANNE: Jump through window?
	if (gGameExternalOptions.fCanJumpThroughWindows == TRUE)
	{
		INT16		sAPCost;
		INT16		sBPCost;
		INT8	bDirection;
		SOLDIERTYPE* lSoldier;

		if (GetSoldier(&lSoldier, gusSelectedSoldier))
		{
			// Flugente: robots do not climb
			if (AM_A_ROBOT(lSoldier))
				return;

			if (FindWindowJumpDirection(lSoldier, lSoldier->sGridNo, lSoldier->ubDirection, &bDirection))
			{
				if (!lSoldier->CanClimbWithCurrentBackpack())
				{
					//Moa: no jumping with backpack
					//sAPCost = GetAPsToJumpThroughWindows( lSoldier, TRUE );
					//sBPCost = GetBPsToJumpThroughWindows( lSoldier, TRUE );
					ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, NewInvMessage[NIV_NO_CLIMB]);
					return;
				}
				else
				{
					sAPCost = GetAPsToJumpFence(lSoldier, FALSE);
					sBPCost = GetBPsToJumpFence(lSoldier, FALSE);
				}

				if (EnoughPoints(lSoldier, sAPCost, sBPCost, FALSE))
				{
					lSoldier->BeginSoldierClimbWindow();
				}
			}
		}
	}
}

void GKIWhenDQEOnKD::On_k(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos, UINT16 * gusItemExplosion)
{
	if (fAlt)
	{
		if (fCtrl)
		{
			if (CHEATER_CHEAT_LEVEL())
			{
				// next shot by anybody is auto kill
				if (gfNextShotKills)
				{
					gfNextShotKills = FALSE;
				}
				else
				{
					gfNextShotKills = TRUE;
				}
			}
		}
		else
		{
			if (CHEATER_CHEAT_LEVEL())
			{
				if (*gusItemExplosion != NULL)
					CreateExplosion(*gusItemExplosion);
			}
		}
	}
	else if (fCtrl)
	{
		if (CHEATER_CHEAT_LEVEL())
		{
			CheatSelectExplosion();
		}
	}
	else
	{
		BeginKeyPanelFromKeyShortcut();
	}
}

void GKIWhenDQEOnKD::On_K(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	// Flugente: reworked this
	//CHRISL: Swap gunsling
	if (gusSelectedSoldier != NOBODY)
	{
		SOLDIERTYPE* pSoldier = MercPtrs[gusSelectedSoldier];

		if (fAlt)
			// switch to knife, or from knife to gun
			pSoldier->SwitchWeapons(TRUE);
		else if (fCtrl)
			// switch to sidearm, or from sidearm to non-sidearm gun
			pSoldier->SwitchWeapons(FALSE, TRUE);
		else
			// switch to and from gunsling
			pSoldier->SwitchWeapons();
	}
}

void GKIWhenDQEOnKD::On_l(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	if (fCtrl && fAlt)
	{
#ifdef JA2BETAVERSION
		gfDisplayStrategicAILogs ^= TRUE;
		if (gfDisplayStrategicAILogs)
		{
			ScreenMsg(FONT_LTKHAKI, MSG_INTERFACE, L"Strategic AI Log visually enabled.");
		}
		else
		{
			ScreenMsg(FONT_LTKHAKI, MSG_INTERFACE, L"Strategic AI Log visually disabled.");
		}
		return;
#endif
	}
	else if (fAlt)
	{
		// used for quickloading
	}
	else if (fCtrl)
	{
		// used for loading game
	}
	else
	{
		// nothing in hand and either not in SM panel, or the matching button is enabled if we are in SM panel
		if ((gpItemPointer == NULL) &&
			((gsCurInterfacePanel != SM_PANEL) || (ButtonList[iSMPanelButtons[LOOK_BUTTON]]->uiFlags & BUTTON_ENABLED)))
		{
			*puiNewEvent = LC_CHANGE_TO_LOOK;
		}
	}
}

void GKIWhenDQEOnKD::On_L(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	HandleTacticalTransformFlashlight();
}

void GKIWhenDQEOnKD::On_m(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	if (fAlt)
	{
		if (INFORMATION_CHEAT_LEVEL())
		{
			*puiNewEvent = I_LEVELNODEDEBUG;
			CountLevelNodes();
		}
	}
	else if (fCtrl)
	{
		if (INFORMATION_CHEAT_LEVEL())
		{
			ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, L"Memory Used: %d + %d = %d vs: %d", guiMemTotal, giMemUsedInSurfaces, (guiMemTotal + giMemUsedInSurfaces), (giStartingMemValue - MemGetFree()));
		}
	}
	else
	{
		// nothing in hand and the Map Screen button for whichever panel we're in must be enabled
		if ((gpItemPointer == NULL) && !gfDisableTacticalPanelButtons &&
			(((gsCurInterfacePanel == SM_PANEL) && (ButtonList[iSMPanelButtons[SM_MAP_SCREEN_BUTTON]]->uiFlags & BUTTON_ENABLED)) ||
				((gsCurInterfacePanel == TEAM_PANEL) && (ButtonList[iTEAMPanelButtons[TEAM_MAP_SCREEN_BUTTON]]->uiFlags & BUTTON_ENABLED))))
		{
			// go to Map screen
			if (!(gTacticalStatus.uiFlags & ENGAGED_IN_CONV))
			{
				GoToMapScreenFromTactical();
			}
		}
	}
}

void GKIWhenDQEOnKD::On_M(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	if (fAlt)
	{

	}
	else if (fCtrl)
	{
		// Merge all items
		StackAndSort(FALSE);
	}
	else
	{
		HandleTacticalMoveItems();
	}
}

void GKIWhenDQEOnKD::On_N(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	// swap sungoggles and nightgoggles / put on gas masks
	SOLDIERTYPE* pTeamSoldier;
	INT8		bLoop;

	// emergency command: everybody in this sector puts on gasmasks
	if (fAlt)
	{
		for (bLoop = gTacticalStatus.Team[gbPlayerNum].bFirstID, pTeamSoldier = MercPtrs[bLoop]; bLoop <= gTacticalStatus.Team[gbPlayerNum].bLastID; bLoop++, pTeamSoldier++)
		{
			if (!AM_A_ROBOT(pTeamSoldier) && pTeamSoldier->stats.bLife >= OKLIFE && (pTeamSoldier->sSectorX == gWorldSectorX) && (pTeamSoldier->sSectorY == gWorldSectorY) && (pTeamSoldier->bSectorZ == gbWorldSectorZ))
			{
				WearGasMaskIfAvailable(pTeamSoldier);
			}
		}

		// redraw panels
		fCharacterInfoPanelDirty = TRUE;
		fTeamPanelDirty = TRUE;
		fInterfacePanelDirty = DIRTYLEVEL2;
	}
	// HEADROCK HAM B2.8: Added call for CTRL-SHIFT-N to switch all soldiers to day/night.
	else if (fCtrl)
	{
		BOOLEAN fToNightVision = FALSE; // JADOL -- Add initialization

		for (bLoop = gTacticalStatus.Team[gbPlayerNum].bFirstID, pTeamSoldier = MercPtrs[bLoop]; bLoop <= gTacticalStatus.Team[gbPlayerNum].bLastID; bLoop++, pTeamSoldier++)
		{
			if (OK_CONTROLLABLE_MERC(pTeamSoldier) && pTeamSoldier->bAssignment == CurrentSquad() && !AM_A_ROBOT(pTeamSoldier))
			{
				if (pTeamSoldier->inv[HEAD1POS].exists() || pTeamSoldier->inv[HEAD2POS].exists())
				{
					fToNightVision = (Item[pTeamSoldier->inv[HEAD1POS].usItem].brightlightvisionrangebonus > 0 || Item[pTeamSoldier->inv[HEAD2POS].usItem].brightlightvisionrangebonus > 0);
					break;
				}
				if (bLoop == gTacticalStatus.Team[gbPlayerNum].bLastID)
				{
					// Default to night or day based on game hour
					fToNightVision = NightTime();
				}
			}
		}
		for (bLoop = gTacticalStatus.Team[gbPlayerNum].bFirstID, pTeamSoldier = MercPtrs[bLoop]; bLoop <= gTacticalStatus.Team[gbPlayerNum].bLastID; bLoop++, pTeamSoldier++)
		{
			// HEADROCK HAM 3.5: When this INI setting is enabled, ALL mercs in the current sector will do a goggle swap.
			if (gGameExternalOptions.fGoggleSwapAffectsAllMercsInSector)
			{
				if (OK_CONTROLLABLE_MERC(pTeamSoldier) && pTeamSoldier->sSectorX == gWorldSectorX && pTeamSoldier->sSectorY == gWorldSectorY && pTeamSoldier->bSectorZ == gbWorldSectorZ && !AM_A_ROBOT(pTeamSoldier))
				{
					SwapGogglesUniformly(pTeamSoldier, fToNightVision);
				}
			}
			else
			{
				if (OK_CONTROLLABLE_MERC(pTeamSoldier) && pTeamSoldier->bAssignment == CurrentSquad() && !AM_A_ROBOT(pTeamSoldier))
				{
					SwapGogglesUniformly(pTeamSoldier, fToNightVision);
				}
			}
		}
	}
	else // Shift-N
	{
		HandleTBSwapGoogles();
	}
}

void GKIWhenDQEOnKD::On_n(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	if (!AreInMeanwhile())
	{
		static UINT16 gQuoteNum = 0;
		if (fAlt)
		{
			// if (INFORMATION_CHEAT_LEVEL()) // JADOL -- Disabled by me , because it's harmless
			{
				// if (gfUIFullTargetFound) // JADOL -- Disabled by me , because it's harmless
				{
					//ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, L"Quote Enum No: %d", gQuoteNum);
					////MapScreenMessage(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, L"Quote Enum No: %d", gQuoteNum);
					//TacticalCharacterDialogue(MercPtrs[gusUIFullTargetID], gQuoteNum);
					//gQuoteNum++;
					MercPtrs[gusUIFullTargetID]->DoMercBattleSound(BATTLE_SOUND_LOWMORALE_OK);
				}
			}
		}
		else if (fCtrl)
		{
			ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, L"Quote Enum increment reset to 0");
			//MapScreenMessage(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, L"Quote Enum increment reset to 0");
			gQuoteNum = 0;
		}
		else
		{
			if (!CycleSoldierFindStack(usMapPos))// Are we over a merc stack?
				CycleIntTileFindStack(usMapPos); // If not, now check if we are over a struct stack
		}
	}
}

void GKIWhenDQEOnKD::On_o(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	if (!AreInMeanwhile())
	{
		if (fAlt)
		{
			if (CHEATER_CHEAT_LEVEL())
			{
				gStrategicStatus.usPlayerKills += NumEnemiesInAnySector(gWorldSectorX, gWorldSectorY, gbWorldSectorZ);
				ObliterateSector();
			}
		}
		else if (fCtrl)
		{
			if (CHEATER_CHEAT_LEVEL())
			{
				if (gCreatedMonsterType == NULL)
					gCreatedMonsterType = ADULTFEMALEMONSTER;
				if (GetMouseMapPos(&gusMapPos))
					CreatePlayerControlledMonster();
			}
		}
		else
		{
			// nothing in hand and the Options Screen button for whichever panel we're in must be enabled
			if ((gpItemPointer == NULL) && !gfDisableTacticalPanelButtons &&
				((gsCurInterfacePanel != SM_PANEL) || (ButtonList[iSMPanelButtons[OPTIONS_BUTTON]]->uiFlags & BUTTON_ENABLED)))
			{
				if (!fDisableMapInterfaceDueToBattle)
				{
					// go to Options screen
					SetOptionsPreviousScreen(GAME_SCREEN);
					LeaveTacticalScreen(OPTIONS_SCREEN);
				}
			}
		}
	}
}

void GKIWhenDQEOnKD::On_O(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	if (fCtrl)
	{
		if (CHEATER_CHEAT_LEVEL())
		{
			CheatSelectCreateMonster();
		}
	}
	else
	{
		HandleTacticalTransformScope();
	}
}

void GKIWhenDQEOnKD::On_p(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{

#ifdef JA2BETAVERSION
	if (fAlt)
		ToggleRealTimeConfirm();
	else
#endif

#ifdef JA2TESTVERSION
		if (fCtrl)
		{
			// CTRL-P: Display player's highest progress percentage
			DumpSectorDifficultyInfo();
		}
		else
#endif
			HandleStanceChangeFromUIKeys(ANIM_PRONE);
}

void GKIWhenDQEOnKD::On_P(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	HandleTacticalTransformStock();
}

void GKIWhenDQEOnKD::On_q(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	if (fCtrl)
	{
		if (gGameSettings.fOptions[TOPTION_GL_HIGH_ANGLE])
		{
			gGameSettings.fOptions[TOPTION_GL_HIGH_ANGLE] = FALSE;
			ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, pMessageStrings[MSG_GL_LOW_ANGLE]);
		}
		else
		{
			gGameSettings.fOptions[TOPTION_GL_HIGH_ANGLE] = TRUE;
			ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, pMessageStrings[MSG_GL_HIGH_ANGLE]);
		}

		//HandleTBSwapHands( );
	}
	else if (fAlt)
	{
		HandleTBSwapGunsling();
	}
	else
	{
		SetScopeMode(usMapPos);
	}
}

void GKIWhenDQEOnKD::On_Q(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	HandleTacticalDropItem(HANDPOS);
}

void GKIWhenDQEOnKD::On_R(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	// Make auto reload with magazines from sector inventory
	HandleTBReloadAll();
}

void GKIWhenDQEOnKD::On_r(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	if (gusSelectedSoldier != NOBODY)
	{
		if (fAlt) //reload selected merc's weapon
		{
			if (CHEATER_CHEAT_LEVEL())
			{
				ReloadWeapon(MercPtrs[gusSelectedSoldier], MercPtrs[gusSelectedSoldier]->ubAttackingHand);
			}
			else
				HandleTBReload();
		}
		else if (fCtrl)
		{
			if (INFORMATION_CHEAT_LEVEL())
			{
			}
		}
		else
		{
			HandleTBSoldierRun();
		}
	}
}

void GKIWhenDQEOnKD::On_S(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	StackAndSort(TRUE);
	ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, pImpButtonText[11]);
}

bool GKIWhenDQEOnKD::On_s(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	if (!AreInMeanwhile())
	{
		if (fCtrl)
		{
			if (fAlt)
			{
				RemoveCharacterFromSquads(MercPtrs[gusSelectedSoldier]);
			}
			else if (!fDisableMapInterfaceDueToBattle && !(gTacticalStatus.uiFlags & ENGAGED_IN_CONV) && !is_networked)
			{
				// WANNE: Do not allow saving via the save screen when it is not our turn,
				// because there is an explit when you close the save window without saving, you can move your merc even it is not your turn
				// IF UI HAS LOCKED, ONLY ALLOW EXIT!
				if (gfDisableRegionActive || gfUserTurnRegionActive)
				{
					return(true);
				}

				//if the game CAN be saved
				if (CanGameBeSaved())
				{
					gfSaveGame = TRUE;
					gfCameDirectlyFromGame = TRUE;

					SetOptionsPreviousScreen(GAME_SCREEN);
					LeaveTacticalScreen(SAVE_LOAD_SCREEN);
				}
				else
				{
					//Display a message saying the player cant save now
					switch (gGameOptions.ubIronManMode)
					{
					case 2:
						DoMapMessageBox(MSG_BOX_BASIC_STYLE, zNewTacticalMessages[TCTL_MSG__SOFT_IRON_MAN_CANT_SAVE_NOW], GAME_SCREEN, (UINT8)MSG_BOX_FLAG_OK, NULL);
						break;
					case 3:
						CHAR16 zTemp[320];
						swprintf(zTemp, zNewTacticalMessages[TCTL_MSG__EXTREME_IRON_MAN_CANT_SAVE_NOW], gGameExternalOptions.ubExtremeIronManSavingHour);
						DoMapMessageBox(MSG_BOX_BASIC_STYLE, zTemp, GAME_SCREEN, (UINT8)MSG_BOX_FLAG_OK, NULL);
						break;
					default:
						DoMessageBox(MSG_BOX_BASIC_STYLE, zNewTacticalMessages[TCTL_MSG__IRON_MAN_CANT_SAVE_NOW], GAME_SCREEN, (UINT8)MSG_BOX_FLAG_OK, NULL, NULL);
						break;
					}
				}
			}
		}
		else
		{
			if (fAlt)
			{
				if (!fDisableMapInterfaceDueToBattle && !(gTacticalStatus.uiFlags & ENGAGED_IN_CONV) && !is_networked)
				{
					//if the game CAN be saved
					if (CanGameBeSaved())
					{
						SetOptionsPreviousScreen(GAME_SCREEN);
						//guiPreviousOptionScreen = guiCurrentScreen;
						DoQuickSave();
					}
					else
					{
						//Display a message saying the player cant save now
						switch (gGameOptions.ubIronManMode)
						{
						case 2:
							DoMapMessageBox(MSG_BOX_BASIC_STYLE, zNewTacticalMessages[TCTL_MSG__SOFT_IRON_MAN_CANT_SAVE_NOW], GAME_SCREEN, MSG_BOX_FLAG_OK, NULL);
							break;
						case 3:
							CHAR16 zTemp[320];
							swprintf(zTemp, zNewTacticalMessages[TCTL_MSG__EXTREME_IRON_MAN_CANT_SAVE_NOW], gGameExternalOptions.ubExtremeIronManSavingHour);
							DoMapMessageBox(MSG_BOX_BASIC_STYLE, zTemp, GAME_SCREEN, MSG_BOX_FLAG_OK, NULL);
							break;
						default:
							DoMessageBox(MSG_BOX_BASIC_STYLE, zNewTacticalMessages[TCTL_MSG__IRON_MAN_CANT_SAVE_NOW], GAME_SCREEN, MSG_BOX_FLAG_OK, NULL, NULL);
							break;
						}
					}
				}
			}
			else if (gusSelectedSoldier != NOBODY)
			{
				gfPlotNewMovement = TRUE;
				HandleStanceChangeFromUIKeys(ANIM_STAND);
			}
		}
	}
	return(false);
}

void GKIWhenDQEOnKD::On_t(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	if (fAlt)
	{
		if (CHEATER_CHEAT_LEVEL())
		{
			TeleportSelectedSoldier();
		}
	}
	else if (fCtrl && !is_networked)// ary-05/05/2009 : add forced turn mode
	{
		ToggleTurnMode();
	}
	else
		ToggleTreeTops();
}

void GKIWhenDQEOnKD::On_T(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	if (fCtrl && fShift && fAlt)
	{
		if (CHEATER_CHEAT_LEVEL())
		{
			// Test Capturing Mercs as POW
			AttemptToCapturePlayerSoldiers();
		}
	}
	else if (fCtrl && fShift)
	{
		if (CHEATER_CHEAT_LEVEL())
		{
			CHAR16	zString[128];
			swprintf(zString, L"%s cheat", pMessageStrings[MSG_SAVE_AUTOSAVE_TEXT]);
			DoAutoSave(SAVE__TIMED_AUTOSAVE_SLOT1, zString);
		}
	}
	else if (fAlt && fShift)
	{
		//resort Team by ubID
		SortSquadByID(MercPtrs[gusSelectedSoldier]->bTeam);
	}
	else
	{
		HandleTacticalTransformItem();
	}
}

void GKIWhenDQEOnKD::On_u(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	if (fAlt)
	{
		if (CHEATER_CHEAT_LEVEL())
		{
			RefreshSoldier();
		}
	}
	else if (fCtrl)
	{
		if (CHEATER_CHEAT_LEVEL() && gusSelectedSoldier != NOBODY)
		{
			INT32 cnt;
			SOLDIERTYPE* pSoldier;

			for (pSoldier = MercPtrs[gbPlayerNum], cnt = 0; cnt <= gTacticalStatus.Team[gbPlayerNum].bLastID; cnt++, pSoldier++)
			{
				if (pSoldier->bActive && pSoldier->stats.bLife > 0)
				{
					if (pSoldier->flags.uiStatusFlags & SOLDIER_VEHICLE)
					{
						// Get breath back
						pSoldier->bBreath = 100;
						pSoldier->sBreathRed = 10000;
					}
					else
					{
						// Get breath back
						pSoldier->bBreath = pSoldier->bBreathMax;
						pSoldier->sBreathRed = 0;
					}
					// Get life back
					pSoldier->stats.bLife = pSoldier->stats.bLifeMax;
					pSoldier->bBleeding = 0;

					// SANDRO - erase insta-healable injury 
					pSoldier->iHealableInjury = 0;

					fInterfacePanelDirty = DIRTYLEVEL2;
				}
			}
		}
	}

	else if (gusSelectedSoldier != NOBODY)
		*puiNewEvent = M_CHANGE_TO_ACTION;
}

void GKIWhenDQEOnKD::On_U(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
}

void GKIWhenDQEOnKD::On_v(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	if (fAlt)
	{
#ifdef JA2TESTVERSION
		if (gfDoVideoScroll ^= TRUE)
			ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, L"Video Scroll ON");
		else
			ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, L"Video Scroll OFF");
#endif
	}
	else if (fCtrl)
	{
#ifdef SGP_VIDEO_DEBUGGING
		ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, L"VObjects:	%d", guiVObjectSize);
		ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, L"VSurfaces:	%d", guiVSurfaceSize);
		ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, L"SGPVideoDump.txt updated...");
		PerformVideoInfoDumpIntoFile("SGPVideoDump.txt", TRUE);
#else
		HandleTacticalInventoryMenu();
#endif
	}
	else
		DisplayGameSettings();

}

void GKIWhenDQEOnKD::On_V(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	if (fAlt)
		ToggleTrapNetworkView();	// added by Flugente
	else
		ToggleMercView();
}

void GKIWhenDQEOnKD::On_w(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	if (fCtrl && fAlt)
	{
		ToggleWireFrame();
	}
	else if (fAlt)
	{
		if (CHEATER_CHEAT_LEVEL())
		{
			// cycle item forward in primary hand
			if (InItemDescriptionBox())
			{
				// Swap item in description panel...
				CycleItemDescriptionItem(ITEMDESC_START_X, ITEMDESC_START_Y);

			}
			else
			{
				CycleSelectedMercsItem();
			}
		}
	}
	else if (fCtrl)
	{
		if (CHEATER_CHEAT_LEVEL())
		{
			if (gusSelectedSoldier != NOBODY)
			{
				CreateItem(FLAMETHROWER, 100, &(MercPtrs[gusSelectedSoldier]->inv[HANDPOS]));
			}
		}
	}
	else
	{
		// nothing in hand and either not in SM panel, or the matching button is enabled if we are in SM panel
		if ((gpItemPointer == NULL) &&
			((gsCurInterfacePanel != SM_PANEL) || (ButtonList[iSMPanelButtons[LOOK_BUTTON]]->uiFlags & BUTTON_ENABLED)))
		{
			*puiNewEvent = LC_CHANGE_TO_LOOK;
		}
	}
}

void GKIWhenDQEOnKD::On_W(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	if (fAlt)
	{
		if (CHEATER_CHEAT_LEVEL())
		{
			// cycle item backward in primary hand
			if (InItemDescriptionBox())
			{
				// Swap item in description panel...
				CycleItemDescriptionItem(ITEMDESC_START_X, ITEMDESC_START_Y);
			}
			else
			{
				CycleSelectedMercsItem();
			}
		}
	}
}

void GKIWhenDQEOnKD::On_x(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	if (!fCtrl && !fAlt)
	{
		// Exchange places...
		SOLDIERTYPE* pSoldier1, * pSoldier2;

		//Check if we have a good selected guy
		if (gusSelectedSoldier != NOBODY)
		{
			pSoldier1 = MercPtrs[gusSelectedSoldier];

			BOOLEAN fFoundGoodTarget = FALSE;
			if (gfUIFullTargetFound)
			{
				// Get soldier...
				pSoldier2 = MercPtrs[gusUIFullTargetID];

				// Check if both OK....
				if (pSoldier1->stats.bLife >= OKLIFE && pSoldier2->ubID != gusSelectedSoldier)
				{
					if (pSoldier2->stats.bLife >= OKLIFE)
					{
						if (CanSoldierReachGridNoInGivenTileLimit(pSoldier1, pSoldier2->sGridNo, 1, (INT8)gsInterfaceLevel))
						{
							// Exclude enemies....
							if (!pSoldier2->aiData.bNeutral && (pSoldier2->bSide != gbPlayerNum))
							{

							}
							else
							{
								if (CanExchangePlaces(pSoldier1, pSoldier2, TRUE))
								{
									// All's good!
									SwapMercPositions(pSoldier1, pSoldier2);

									DeductPoints(pSoldier1, APBPConstants[AP_EXCHANGE_PLACES], 0);
									DeductPoints(pSoldier2, APBPConstants[AP_EXCHANGE_PLACES], 0);
								}
							}
							fFoundGoodTarget = TRUE;
						}
					}
				}
			}
			if (!fFoundGoodTarget)
			{
				HandleStanceChangeFromUIKeys(ANIM_PRONE);
			}
		}
	}
	else if (fCtrl)	// The_Bob - real time sneaking, 01-06-09
	{
		HandleTBEnterTurnbased();
	}
	else if (fAlt)
	{
		// used for exit game
	}
}

void GKIWhenDQEOnKD::On_X(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	// The_Bob - real time sneaking, 01-06-09
	// shift-ctrl-x: toggle real time sneaking
	if (fCtrl)
	{
		HandleTBToggleSneak();
	}
}

void GKIWhenDQEOnKD::On_y(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	if (!AreInMeanwhile())
	{
		if (fAlt)
		{
			OBJECTTYPE		Object;
			SOLDIERTYPE* pSoldier;

			if (CHEATER_CHEAT_LEVEL())
			{
				QuickCreateProfileMerc(CIV_TEAM, MARIA); //Ira

				// Recruit!
				RecruitEPC(MARIA);

				//Heinz: 28.02.09 BUGFIX: giving G41 to Maria only in cheat mode
				// Create object and set
				CreateItem(G41, 100, &Object);

				pSoldier = FindSoldierByProfileID(MARIA, FALSE);

				AutoPlaceObject(pSoldier, &Object, FALSE);
			}
		}
		else
		{
			// used for opening chatbox in networked game
			if (INFORMATION_CHEAT_LEVEL())
			{
				*puiNewEvent = I_LOSDEBUG;
			}
		}
	}
}

void GKIWhenDQEOnKD::On_Y(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	HandleTacticalTransformLaser();
}

void GKIWhenDQEOnKD::On_z(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
	if (fCtrl && fAlt)
	{
		if (INFORMATION_CHEAT_LEVEL())
		{
			ToggleZBuffer();
		}
	}
	else if (fAlt)
	{
		HandleTBToggleStealthAll();
	}
	else if (fCtrl)
	{
		// used for "lock" / "unlock" the mouse cursor in windowed mode
	}
	else
	{
		HandleTBToggleStealth();
	}
}

void GKIWhenDQEOnKD::On_Z(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos)
{
}

