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

#include "Turn Based Input.h"				// JADOL -- Tidying up the source code
#include "Turn Based Input_GKI_Handler.h"	// JADOL -- Modularizing GetKeyboardInput DequeueEvent Handler

//forward declarations of common classes to eliminate includes
class OBJECTTYPE;
class SOLDIERTYPE;

BOOLEAN gfMouseLockedOnBorder = FALSE;
INT32 gusMapPos;
UINT16 gusItemExplosion = NULL;
INT8 gCreatedMonsterType = NULL;

UINT16 usitem = 1623;
INT32 mappos = 0;

BOOLEAN gfFirstCycleMovementStarted = FALSE;

UINT32 guiSoldierFlags;
UINT32 guiUITargetSoldierId = NOBODY;

SOLDIERTYPE* gpExchangeSoldier1;
SOLDIERTYPE* gpExchangeSoldier2;

// Flugente: fortification
INT16	gCurrentFortificationStructure = -1;
UINT8	gCurrentFortificationTileLibraryIndex = 0;

BOOLEAN	gfNextFireJam = FALSE;
INT16 brstmode = 0; //dddd

extern UIKEYBOARD_HOOK					gUIKeyboardHook;
extern BOOLEAN	fRightButtonDown;
extern BOOLEAN	fLeftButtonDown;
extern BOOLEAN fIgnoreLeftUp;
extern UINT32	guiCurrentEvent;
extern UINT8	gubIntTileCheckFlags;
extern UINT32	guiCurrentUICursor;
extern SOLDIERTYPE* gpSMCurrentMerc;
extern INT32 gsOverItemsGridNo;
extern INT16 gsOverItemsLevel;
extern BOOLEAN	gfUIShowExitSouth;
extern BOOLEAN	fMiddleButtonDown;
extern BOOLEAN	fX1ButtonDown;
extern BOOLEAN	fX2ButtonDown;

extern INT32	giStartingMemValue;

extern BOOLEAN gfBeginBurstSpreadTracking;
extern BOOLEAN gfRTClickLeftHoldIntercepted;

extern BOOLEAN gfReportHitChances;

extern UINT32 guiVObjectSize;
extern UINT32 guiVSurfaceSize;

extern BOOLEAN gfNextShotKills;
// sevenfm: for cover dialog
extern COVER_DRAW_MODE gubDrawMode;

extern TraitSelection	gTraitSelection;
extern SkillSelection	gSkillSelection;
extern ArtillerySector	gArtillerySector;
extern ArtilleryTeam	gArtilleryTeam;
extern ReinforcementSector	gReinforcementSector;
extern ReinforcementNumber	gReinforcementNumber;
extern SoldierSelection	gSoldierSelection;
extern DragSelection	gDragSelection;

extern  MOUSE_REGION    gMPanelRegion;

extern UINT32 guiNewUICursor;
extern SOLDIERTYPE* pTMilitiaSoldier;

extern BOOLEAN ValidQuickExchangePosition();

extern SOLDIERTYPE* FindNextActiveSquad(SOLDIERTYPE* pSoldier);
extern void ToggleItemGlow(BOOLEAN fOn);
extern void HandleTalkingMenuBackspace(void);
extern void BeginKeyPanelFromKeyShortcut();

extern INT32		iSMPanelButtons[NUM_SM_BUTTONS];
extern INT32		iTEAMPanelButtons[NUM_TEAM_BUTTONS];
extern INT32		giSMStealthButton;

extern UINT32 guiMessageBoxImage;
extern UINT16 guiMessageBoxImageIndex;

extern INT16 ITEMDESC_START_X;
extern INT16 ITEMDESC_START_Y;

extern int iWindowedMode;

extern OBJECTTYPE* gpItemDescObject;
extern BOOLEAN gfInItemStackPopup;
extern BOOLEAN gfInKeyRingPopup;

extern BOOLEAN CompatibleAmmoForGun(OBJECTTYPE* pTryObject, OBJECTTYPE* pTestObject);
extern void DetermineWhichAssignmentMenusCanBeShown(void);
extern void DetermineWhichMilitiaControlMenusCanBeShown(void); //lalien
// The_Bob - real time sneaking, 01-06-09
extern BOOLEAN WeSeeNoOne(void); // Needed to control entering turn-based with ctrl-x

extern	INT8 GetTeamSlotFromPlayerID(UINT8 ubID);
extern FACETYPE* gpCurrentTalkingFace;

// Flugente:  toggle display of enemy role indicators
extern BOOLEAN gDisplayEnemyRoles;

extern BOOLEAN AnyItemsVisibleOnLevel(ITEM_POOL* pItemPool, INT8 bZLevel);

extern OBJECTTYPE* gpItemDescOrigAttachmentObject;

extern BOOLEAN	gUIActionModeChangeDueToMouseOver;

extern	BOOLEAN		gfDisableRegionActive;
extern	BOOLEAN		gfUserTurnRegionActive;

extern INT8 gBadMercBodyType;
extern INT8 gCivilianBodyType;


void	GetTBMouseButtonInput(UINT32* puiNewEvent)
{
	QueryTBLeftButton(puiNewEvent);
	QueryTBRightButton(puiNewEvent);
	QueryTBWheel(puiNewEvent);
	QueryTBMButton(puiNewEvent);
	QueryTBX1Button(puiNewEvent);
	QueryTBX2Button(puiNewEvent);
}

void	QueryTBLeftButton(UINT32* puiNewEvent)
{
	SOLDIERTYPE* pSoldier;
	INT32 usMapPos;
	static BOOLEAN	fClickHoldIntercepted = FALSE;
	static BOOLEAN	fCanCheckForSpeechAdvance = FALSE;
	static INT32		sMoveClickGridNo = 0;


	// LEFT MOUSE BUTTON
	if (gViewportRegion.uiFlags & MSYS_MOUSE_IN_AREA)
	{
		if (!GetMouseMapPos(&usMapPos) && !gfUIShowExitSouth)
		{
			return;
		}

		if (gViewportRegion.ButtonState & MSYS_LEFT_BUTTON)
		{
			if (!fLeftButtonDown)
			{
				fLeftButtonDown = TRUE;
				RESETCOUNTER(LMOUSECLICK_DELAY_COUNTER);

				{
					switch (gCurrentUIMode)
					{
					case CONFIRM_ACTION_MODE:

						if (GetSoldier(&pSoldier, gusSelectedSoldier))
						{
							pSoldier->sStartGridNo = usMapPos;
						}
						break;

					case MOVE_MODE:

						if (giUIMessageOverlay != -1)
						{
							EndUIMessage();
						}
						else
						{
							if (!HandleCheckForExitArrowsInput(FALSE) && gpItemPointer == NULL)
							{
								// First check if we clicked on a guy, if so, make selected if it's ours
								if (gfUIFullTargetFound && (guiUIFullTargetFlags & OWNED_MERC))
								{
									if (!(guiUIFullTargetFlags & UNCONSCIOUS_MERC))
									{
										fClickHoldIntercepted = TRUE;

										// Select guy
										if (GetSoldier(&pSoldier, gusUIFullTargetID) && gpItemPointer == NULL)
										{
											if (pSoldier->bAssignment >= ON_DUTY)
											{
												// do nothing
												fClickHoldIntercepted = FALSE;
											}
											else
											{
												*puiNewEvent = I_SELECT_MERC;
											}
										}
										else
										{
											*puiNewEvent = I_SELECT_MERC;
										}
									}
								}
								else
								{
									if (InUIPlanMode())
									{
										AddUIPlan(usMapPos, UIPLAN_ACTION_MOVETO);
									}
									else
									{
										// We're on terrain in which we can walk, walk
										// If we're on terrain,
										if (gusSelectedSoldier != NOBODY)
										{
											GetSoldier(&pSoldier, gusSelectedSoldier);

											INT8 bReturnVal = HandleMoveModeInteractiveClick(usMapPos, puiNewEvent);

											// All's OK for interactive tile?
											if (bReturnVal == -2)
											{
												// Confirm!
												if (SelectedMercCanAffordMove())
												{
													*puiNewEvent = C_WAIT_FOR_CONFIRM;
												}
											}
											else if (bReturnVal == 0)
											{
												if (gfUIAllMoveOn)
												{
													*puiNewEvent = C_WAIT_FOR_CONFIRM;
												}
												else
												{
													if (gsCurrentActionPoints == 0)
													{
														ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_UI_FEEDBACK, TacticalStr[NO_PATH]);
													}
													else if (SelectedMercCanAffordMove())
													{
														BOOLEAN fResult;

														if ((fResult = UIOKMoveDestination(MercPtrs[gusSelectedSoldier], usMapPos)) == 1)
														{
															// ATE: CHECK IF WE CAN GET TO POSITION
															// Check if we are not in combat
															GetSoldier(&pSoldier, gusSelectedSoldier);

															if (gsCurrentActionPoints == 0)
															{
																ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_UI_FEEDBACK, TacticalStr[NO_PATH]);
															}
															else
															{
																*puiNewEvent = C_WAIT_FOR_CONFIRM;
															}
														}
														else
														{
															if (fResult == 2)
															{
																ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_UI_FEEDBACK, TacticalStr[NOBODY_USING_REMOTE_STR]);
															}
															else
															{
																//if ( sMapPos != sMoveClickGridNo || pSoldier->flags.uiStatusFlags & SOLDIER_ROBOT )
																//{
																//	sMoveClickGridNo					= sMapPos;

																//ScreenMsg( FONT_MCOLOR_LTYELLOW, MSG_UI_FEEDBACK, TacticalStr[ CANT_MOVE_THERE_STR ] );
																// Goto hand cursor mode....
																//	*puiNewEvent					= M_CHANGE_TO_HANDMODE;
																//	gsOverItemsGridNo				= sMapPos;
																//	gsOverItemsLevel				= gsInterfaceLevel;
																//}
																//else
																//{
																//	sMoveClickGridNo = 0;
																//	*puiNewEvent = M_CHANGE_TO_HANDMODE;
																//}

															}
															//ScreenMsg( FONT_MCOLOR_LTYELLOW, MSG_UI_FEEDBACK, L"Invalid move destination." );
														}
													}
												}
											}
											// OK, our first right-click is an all-cycle
											gfUICanBeginAllMoveCycle = FALSE;
										}
										fClickHoldIntercepted = TRUE;

									}
								}
							}
							else
							{
								fClickHoldIntercepted = TRUE;
								fIgnoreLeftUp = TRUE;
							}

						}
						break;
					}
				}
				if (gfUIWaitingForUserSpeechAdvance)
				{
					fCanCheckForSpeechAdvance = TRUE;
				}

			}

			// HERE FOR CLICK-DRAG CLICK
			switch (gCurrentUIMode)
			{

			case MOVE_MODE:

				// First check if we clicked on a guy, if so, make selected if it's ours
				if (gfUIFullTargetFound)
				{
					// Select guy
					if ((guiUIFullTargetFlags & SELECTED_MERC) && !(guiUIFullTargetFlags & UNCONSCIOUS_MERC) && !(MercPtrs[gusUIFullTargetID]->flags.uiStatusFlags & SOLDIER_VEHICLE))
					{
						*puiNewEvent = M_CHANGE_TO_ADJPOS_MODE;
						fIgnoreLeftUp = FALSE;
					}
				}
				break;
			}

			// IF HERE, DO A CLICK-HOLD IF IN INTERVAL
			if (COUNTERDONE(LMOUSECLICK_DELAY_COUNTER) && !fClickHoldIntercepted)
			{
				/* removed warning C4060 (jonathanl)
				// Switch on UI mode
				switch( gCurrentUIMode )
				{

				}
				*/
			}


		}
		else
		{
			if (fLeftButtonDown)
			{
				if (!fIgnoreLeftUp)
				{

					// FIRST CHECK FOR ANYTIME ( NON-INTERVAL ) CLICKS
					switch (gCurrentUIMode)
					{
					case ADJUST_STANCE_MODE:

						// If button has come up, change to mocve mode
						*puiNewEvent = PADJ_ADJUST_STANCE;
						break;
					}

					// CHECK IF WE CLICKED-HELD
					if (COUNTERDONE(LMOUSECLICK_DELAY_COUNTER))
					{
						// LEFT CLICK-HOLD EVENT
						// Switch on UI mode
						switch (gCurrentUIMode)
						{
						case CONFIRM_ACTION_MODE:

							if (GetSoldier(&pSoldier, gusSelectedSoldier))
							{
								if (pSoldier->bDoBurst)
								{
									pSoldier->sEndGridNo = usMapPos;

									gfBeginBurstSpreadTracking = FALSE;

									if (pSoldier->sEndGridNo != pSoldier->sStartGridNo)
									{
										pSoldier->flags.fDoSpread = TRUE;

										PickBurstLocations(pSoldier);

										*puiNewEvent = CA_MERC_SHOOT;
									}
									else
									{
										pSoldier->flags.fDoSpread = FALSE;
									}

									fClickHoldIntercepted = TRUE;

								}
							}
							break;

						}

					}

					{
						//LEFT CLICK NORMAL EVENT
						// Switch on UI mode
						if (!fClickHoldIntercepted)
						{
							if (giUIMessageOverlay != -1)
							{
								EndUIMessage();
							}
							else
							{
								if (!HandleCheckForExitArrowsInput(TRUE))
								{
									if (gpItemPointer != NULL)
									{
										if (HandleItemPointerClick(usMapPos))
										{
											// getout of mode
											EndItemPointer();

											*puiNewEvent = A_CHANGE_TO_MOVE;
										}
									}
									else
									{
										// Check for wiating for keyboard advance
										if (gfUIWaitingForUserSpeechAdvance && fCanCheckForSpeechAdvance)
										{
											// We have a key, advance!
											DialogueAdvanceSpeech();
										}
										else
										{
											switch (gCurrentUIMode)
											{
											case MENU_MODE:

												// If we get a hit here and we're in menu mode, quit the menu mode
												EndMenuEvent(guiCurrentEvent);
												break;

											case IDLE_MODE:

												// First check if we clicked on a guy, if so, make selected if it's ours
												if (gfUIFullTargetFound)
												{
													// Select guy
													if (guiUIFullTargetFlags & OWNED_MERC && !(guiUIFullTargetFlags & UNCONSCIOUS_MERC))
													{
														*puiNewEvent = I_SELECT_MERC;
													}

												}
												break;

											case MOVE_MODE:

												// Check if we should activate an interactive tile!
												// Select guy
												if ((guiUIFullTargetFlags & OWNED_MERC) && !(guiUIFullTargetFlags & UNCONSCIOUS_MERC))
												{
													// Select guy
													if (GetSoldier(&pSoldier, gusUIFullTargetID) && (gpItemPointer == NULL) && !(pSoldier->flags.uiStatusFlags & SOLDIER_VEHICLE))
													{
														if (pSoldier->bAssignment >= ON_DUTY)
														{
															PopupAssignmentMenuInTactical(pSoldier);
														}
													}
												}
												break;

											case CONFIRM_MOVE_MODE:

												*puiNewEvent = C_MOVE_MERC;
												break;

											case HANDCURSOR_MODE:

												HandleHandCursorClick(usMapPos, puiNewEvent);
												break;

											case RADIOCURSOR_MODE:

												HandleRadioCursorClick(usMapPos, puiNewEvent);
												break;

											case JUMPOVER_MODE:

												if (GetSoldier(&pSoldier, gusSelectedSoldier))
												{
													if (EnoughPoints(pSoldier, gsCurrentActionPoints, 0, TRUE))
													{
														*puiNewEvent = JP_JUMP;
													}
												}
												break;

											case ACTION_MODE:

												if (InUIPlanMode())
												{
													AddUIPlan(usMapPos, UIPLAN_ACTION_FIRE);
												}
												else
												{
													if (GetSoldier(&pSoldier, gusSelectedSoldier))
													{
														if (!HandleUIReloading(pSoldier))
														{
															// ATE: Reset refine aim..
															pSoldier->aiData.bShownAimTime = 0;

															if (gsCurrentActionPoints == 0)
															{
																ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_UI_FEEDBACK, TacticalStr[NO_PATH]);
															}
															// Determine if we have enough action points!
															else if (UIMouseOnValidAttackLocation(pSoldier) && SelectedMercCanAffordAttack())
															{
																*puiNewEvent = A_CHANGE_TO_CONFIM_ACTION;
																pSoldier->sStartGridNo = usMapPos;
															}
														}

													}
												}
												break;

											case CONFIRM_ACTION_MODE:
												if (GetSoldier(&pSoldier, gusSelectedSoldier))
												{
													//shadooow: this fixes merc randomly shooting in different direction than assigned
													pSoldier->flags.fDoSpread = 0;
												}
												*puiNewEvent = CA_MERC_SHOOT;
												break;

											case LOOKCURSOR_MODE:
												// If we cannot actually do anything, return to movement mode
												*puiNewEvent = LC_LOOK;
												break;

											case TALKCURSOR_MODE:

												if (HandleTalkInit())
												{
													*puiNewEvent = TA_TALKINGMENU;
												}
												break;

											case GETTINGITEM_MODE:

												// Remove menu!
												// RemoveItemPickupMenu( );
												break;

											case TALKINGMENU_MODE:

												//HandleTalkingMenuEscape( TRUE );
												break;

											case EXITSECTORMENU_MODE:

												RemoveSectorExitMenu(FALSE);
												break;

											case OPENDOOR_MENU_MODE:

												CancelOpenDoorMenu();
												HandleOpenDoorMenu();
												*puiNewEvent = A_CHANGE_TO_MOVE;
												break;

											}
										}
									}
								}
							}
						}
					}
				}

				// Reset flag
				fLeftButtonDown = FALSE;
				fIgnoreLeftUp = FALSE;
				fClickHoldIntercepted = FALSE;
				fCanCheckForSpeechAdvance = FALSE;
				gfFirstCycleMovementStarted = FALSE;

				// Reset counter
				RESETCOUNTER(LMOUSECLICK_DELAY_COUNTER);

			}

		}

	}
	else
	{
		// Set mouse down to false
		//fLeftButtonDown = FALSE;

		// OK, handle special cases like if we are dragging and holding for a burst spread and
		// release mouse over another mouse region
		if (gfBeginBurstSpreadTracking)
		{
			if (GetSoldier(&pSoldier, gusSelectedSoldier))
			{
				pSoldier->flags.fDoSpread = FALSE;
			}
			gfBeginBurstSpreadTracking = FALSE;
		}
	}

}

void	QueryTBRightButton(UINT32* puiNewEvent)
{
	static BOOLEAN	fClickHoldIntercepted = FALSE;
	static BOOLEAN	fClickIntercepted = FALSE;
	SOLDIERTYPE* pSoldier;
	INT32 usMapPos;
	BOOLEAN				fDone = FALSE;
	if (!GetMouseMapPos(&usMapPos))
	{
		return;
	}

	if (gViewportRegion.uiFlags & MSYS_MOUSE_IN_AREA)
	{

		// RIGHT MOUSE BUTTON
		if (gViewportRegion.ButtonState & MSYS_RIGHT_BUTTON)
		{
			if (!fRightButtonDown)
			{
				fRightButtonDown = TRUE;
				RESETCOUNTER(RMOUSECLICK_DELAY_COUNTER);
			}

			// CHECK COMBINATIONS
			if (fLeftButtonDown)
			{
			}
			else
			{
				if (gpItemPointer == NULL)
				{
					// IF HERE, DO A CLICK-HOLD IF IN INTERVAL
					if (COUNTERDONE(RMOUSECLICK_DELAY_COUNTER) && !fClickHoldIntercepted)
					{
						// Switch on UI mode
						switch (gCurrentUIMode)
						{
						case IDLE_MODE:
						case ACTION_MODE:
						case HANDCURSOR_MODE:
						case RADIOCURSOR_MODE:
						case LOOKCURSOR_MODE:
						case TALKCURSOR_MODE:
						case MOVE_MODE:

							// Check if we're on terrain
							//if ( !gfUIFullTargetFound )
							//{
							// ATE:
							fDone = FALSE;

							if ((guiUIFullTargetFlags & OWNED_MERC) && !(guiUIFullTargetFlags & UNCONSCIOUS_MERC))
							{
								// Select guy
								if (GetSoldier(&pSoldier, gusUIFullTargetID) && (gpItemPointer == NULL) && !(pSoldier->flags.uiStatusFlags & SOLDIER_VEHICLE))
								{
									//if( pSoldier->bAssignment >= ON_DUTY )
									{
										PopupAssignmentMenuInTactical(pSoldier);
										fClickHoldIntercepted = TRUE;
									}
								}
							}

							if (fDone == TRUE)
							{
								break;
							}

							if (gusSelectedSoldier != NOBODY && !fClickHoldIntercepted)
							{
								*puiNewEvent = U_MOVEMENT_MENU;
								fClickHoldIntercepted = TRUE;
							}
							//}
							//else
							//{
							// If we are on a selected guy
							//	if ( guiUIFullTargetFlags & SELECTED_MERC && !( guiUIFullTargetFlags & UNCONSCIOUS_MERC ) )
							//	{
							//*puiNewEvent = U_POSITION_MENU;
							//fClickHoldIntercepted = TRUE;
							//	}
							//		else if ( guiUIFullTargetFlags & OWNED_MERC )
							//		{
							// If we are on a non-selected guy selected guy
							//		}

							//}
							break;
						}
					}
				}

			}

		}
		else
		{
			if (fRightButtonDown)
			{

				if (fLeftButtonDown)
				{
					fIgnoreLeftUp = TRUE;

					if (gpItemPointer == NULL)
					{
						// ATE:
						if (gusSelectedSoldier != NOBODY)
						{
							switch (gCurrentUIMode)
							{
							case CONFIRM_MOVE_MODE:
							case MOVE_MODE:

								if (gfUICanBeginAllMoveCycle)
								{
									*puiNewEvent = M_CYCLE_MOVE_ALL;
								}
								else
								{
									if (!gfFirstCycleMovementStarted)
									{
										gfFirstCycleMovementStarted = TRUE;

										// OK, set this guy's movement mode to crawling fo rthat we will start cycling in run.....
										if (MercPtrs[gusSelectedSoldier]->usUIMovementMode != RUNNING)
										{
											// ATE: UNLESS WE ARE IN RUNNING MODE ALREADY
											MercPtrs[gusSelectedSoldier]->usUIMovementMode = CRAWLING;
										}
									}

									// Give event to cycle movement
									*puiNewEvent = M_CYCLE_MOVEMENT;
									break;
								}
							}

							// ATE: Added cancel of burst mode....
							if (gfBeginBurstSpreadTracking)
							{
								gfBeginBurstSpreadTracking = FALSE;
								gfRTClickLeftHoldIntercepted = TRUE;
								MercPtrs[gusSelectedSoldier]->flags.fDoSpread = FALSE;
								fClickHoldIntercepted = TRUE;
								*puiNewEvent = A_END_ACTION;
								gCurrentUIMode = MOVE_MODE;
							}
						}
					}
				}
				else
				{
					if (!fClickHoldIntercepted && !fClickIntercepted)
					{
						if (gpItemPointer == NULL)
						{
							// ATE:
							if (gusSelectedSoldier != NOBODY)
							{
								// sevenfm: ALT+RMB - TraitsMenu
								if (_KeyDown(ALT))
								{
									switch (gCurrentUIMode)
									{
									case MOVE_MODE:
									case TALKCURSOR_MODE:
									case ACTION_MODE:
									case CONFIRM_ACTION_MODE:
									case LOOKCURSOR_MODE:
										TraitsMenu(usMapPos);
										fClickIntercepted = TRUE;
										break;
									}
								}
								// anv: CTRL+RMB - VehicleMenu
								else if (_KeyDown(CTRL))
								{
									switch (gCurrentUIMode)
									{
									case HANDCURSOR_MODE:
										HandleHandCursorRightClick(usMapPos, puiNewEvent);
										break;
									}
								}
								else
								{
									gfPlotNewMovement = TRUE;//shadooow: this fixes AP cost sometimes not recalculating when changing modes via right click
									// Switch on UI mode
									switch (gCurrentUIMode)
									{
									case IDLE_MODE:

										break;

									case MOVE_MODE:
										// anv: don't switch if passengers are blocked from attacking
										pSoldier = MercPtrs[gusSelectedSoldier];
										if (pSoldier->flags.uiStatusFlags & (SOLDIER_DRIVER | SOLDIER_PASSENGER))
										{
											SOLDIERTYPE* pVehicle = GetSoldierStructureForVehicle(pSoldier->iVehicleId);
											INT8 bSeatIndex = GetSeatIndexFromSoldier(pSoldier);
											if (gNewVehicle[pVehicleList[pSoldier->iVehicleId].ubVehicleType].VehicleSeats[bSeatIndex].fBlockedShots == TRUE)
											{
												ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, pVehicleSeatsStrings[0]);
												break;
											}
										}
										// We have here a change to action mode
										*puiNewEvent = M_CHANGE_TO_ACTION;
										fClickIntercepted = TRUE;
										break;

									case ACTION_MODE:

										// We have here a change to action mode
										*puiNewEvent = A_CHANGE_TO_MOVE;
										fClickIntercepted = TRUE;
										break;

									case CONFIRM_MOVE_MODE:

										*puiNewEvent = A_CHANGE_TO_MOVE;
										fClickIntercepted = TRUE;
										break;

									case HANDCURSOR_MODE:
										// If we cannot actually do anything, return to movement mode
										*puiNewEvent = A_CHANGE_TO_MOVE;
										break;

									case RADIOCURSOR_MODE:
										// If we cannot actually do anything, return to movement mode
										*puiNewEvent = A_CHANGE_TO_MOVE;
										break;

									case LOOKCURSOR_MODE:
									case TALKCURSOR_MODE:

										// If we cannot actually do anything, return to movement mode
										*puiNewEvent = A_CHANGE_TO_MOVE;
										break;

									case CONFIRM_ACTION_MODE:

										if (GetSoldier(&pSoldier, gusSelectedSoldier))
										{
											HandleRightClickAdjustCursor(pSoldier, usMapPos);
										}
										fClickIntercepted = TRUE;
										break;

									case MENU_MODE:

										// If we get a hit here and we're in menu mode, quit the menu mode
										EndMenuEvent(guiCurrentEvent);
										fClickIntercepted = TRUE;
										break;

									}
								}
							}
						}
						else
						{
							if (gfUIFullTargetFound)
							{
								gfItemPointerDifferentThanDefault = !gfItemPointerDifferentThanDefault;
							}
						}
					}
				}
			}
			// Reset flag
			fRightButtonDown = FALSE;
			fClickHoldIntercepted = FALSE;
			fClickIntercepted = FALSE;

			// Reset counter
			RESETCOUNTER(RMOUSECLICK_DELAY_COUNTER);

		}
	}

}

void GetTBMousePositionInput(UINT32* puiNewEvent)
{
	INT32 usMapPos;
	static INT32			usOldMapPos = 0;
	SOLDIERTYPE* pSoldier;
	BOOLEAN						bHandleCode;
	static BOOLEAN		fOnValidGuy = FALSE;
	static UINT32			uiMoveTargetSoldierId = NOBODY;


	if (!GetMouseMapPos(&usMapPos))
	{
		return;
	}

	if (gViewportRegion.uiFlags & MSYS_MOUSE_IN_AREA)
	{
		// Handle highlighting stuff
		HandleObjectHighlighting();

		// Check if we have an item in our hands...
		if (gpItemPointer != NULL)
		{
			*puiNewEvent = A_ON_TERRAIN;
			return;
		}

		// Switch on modes
		switch (gCurrentUIMode)
		{
		case LOCKUI_MODE:
			*puiNewEvent = LU_ON_TERRAIN;
			break;

		case LOCKOURTURN_UI_MODE:
			*puiNewEvent = LA_ON_TERRAIN;
			break;

		case IDLE_MODE:
			*puiNewEvent = I_ON_TERRAIN;
			break;

		case ENEMYS_TURN_MODE:
			*puiNewEvent = ET_ON_TERRAIN;
			break;

		case LOOKCURSOR_MODE:
			*puiNewEvent = LC_ON_TERRAIN;
			break;

		case TALKCURSOR_MODE:
			if (uiMoveTargetSoldierId != NOBODY)
			{
				if (gfUIFullTargetFound)
				{
					if (gusUIFullTargetID != uiMoveTargetSoldierId)
					{
						*puiNewEvent = A_CHANGE_TO_MOVE;
						return;
					}
				}
				else
				{
					*puiNewEvent = A_CHANGE_TO_MOVE;
					return;
				}
			}
			*puiNewEvent = T_ON_TERRAIN;
			break;

		case MOVE_MODE:

			uiMoveTargetSoldierId = NOBODY;

			// Check for being on terrain
			if (GetSoldier(&pSoldier, gusSelectedSoldier))
			{
				if (IsValidJumpLocation(pSoldier, usMapPos, TRUE))
				{
					gsJumpOverGridNo = usMapPos;
					*puiNewEvent = JP_ON_TERRAIN;
					return;
				}
				else
				{
					if (gfUIFullTargetFound)
					{
						// ATE: Don't do this automatically for enemies......
						if (MercPtrs[gusUIFullTargetID]->bTeam != ENEMY_TEAM)
						{
							uiMoveTargetSoldierId = gusUIFullTargetID;
							if (IsValidTalkableNPC((UINT8)gusUIFullTargetID, FALSE, FALSE, FALSE) && !_KeyDown(SHIFT) && !AM_AN_EPC(pSoldier) && !ValidQuickExchangePosition())
							{
								*puiNewEvent = T_CHANGE_TO_TALKING;
								return;
							}
						}
					}
				}
			}
			*puiNewEvent = M_ON_TERRAIN;
			break;

		case ACTION_MODE:

			// First check if we are on a guy, if so, make selected if it's ours
			// Check if the guy is visible
			guiUITargetSoldierId = NOBODY;

			fOnValidGuy = FALSE;

			if (gfUIFullTargetFound)
				//if ( gfUIFullTargetFound )
			{
				if (IsValidTargetMerc((UINT8)gusUIFullTargetID))
				{
					guiUITargetSoldierId = gusUIFullTargetID;

					if (MercPtrs[gusUIFullTargetID]->bTeam != gbPlayerNum)
					{
						fOnValidGuy = TRUE;
						//ddd turn off flag that indicates aim/autofire mode adjustment (aimed burst/auto)
						brstmode = 0;
					}
					else
					{
						if (gUIActionModeChangeDueToMouseOver)
						{
							*puiNewEvent = A_CHANGE_TO_MOVE;
							return;
						}
					}
				}
			}
			else
			{
				if (gUIActionModeChangeDueToMouseOver)
				{
					*puiNewEvent = A_CHANGE_TO_MOVE;
					return;
				}
			}
			*puiNewEvent = A_ON_TERRAIN;
			break;

		case GETTINGITEM_MODE:

			break;

		case TALKINGMENU_MODE:

			if (HandleTalkingMenu())
			{
				*puiNewEvent = A_CHANGE_TO_MOVE;
			}
			break;

		case EXITSECTORMENU_MODE:

			if (HandleSectorExitMenu())
			{
				*puiNewEvent = A_CHANGE_TO_MOVE;
			}
			break;

		case OPENDOOR_MENU_MODE:
			bHandleCode = HandleOpenDoorMenu(); // I think its nicer to avoid assignments in conditionals (jonathanl)
			if (bHandleCode)
			{
				// OK, IF we are not canceling, set ui back!
				if (bHandleCode == 2)
				{
					*puiNewEvent = A_CHANGE_TO_MOVE;
				}
				else
				{
				}
			}
			break;

		case JUMPOVER_MODE:

			// ATE: Make sure!
			if (gsJumpOverGridNo != usMapPos)
			{
				*puiNewEvent = A_CHANGE_TO_MOVE;
			}
			else
			{
				*puiNewEvent = JP_ON_TERRAIN;
			}
			break;

		case CONFIRM_MOVE_MODE:

			if (usMapPos != usOldMapPos)
			{
				// Switch event out of confirm mode
				*puiNewEvent = A_CHANGE_TO_MOVE;

				// Set off ALL move....
				gfUIAllMoveOn = FALSE;

				// ERASE PATH
				ErasePath(TRUE);
			}
			break;

		case CONFIRM_ACTION_MODE:

			// DONOT CANCEL IF BURST
			if (GetSoldier(&pSoldier, gusSelectedSoldier))
			{
				if (pSoldier->bDoBurst)
				{
					pSoldier->sEndGridNo = usMapPos;

					if (pSoldier->sEndGridNo != pSoldier->sStartGridNo && fLeftButtonDown)
					{
						pSoldier->flags.fDoSpread = TRUE;
						gfBeginBurstSpreadTracking = TRUE;
					}

					if (pSoldier->flags.fDoSpread)
					{
						// Accumulate gridno
						AccumulateBurstLocation(usMapPos);

						*puiNewEvent = CA_ON_TERRAIN;
						break;
					}
				}
			}

			// First check if we are on a guy, if so, make selected if it's ours
			if (gfUIFullTargetFound)
			{
				if (guiUITargetSoldierId != gusUIFullTargetID)
				{
					// Switch event out of confirm mode
					*puiNewEvent = CA_END_CONFIRM_ACTION;
				}
				else
				{
					*puiNewEvent = CA_ON_TERRAIN;
				}
			}
			else
			{
				// OK, if we were on a guy, and now we are off, go back!
				if (fOnValidGuy)
				{
					// Switch event out of confirm mode
					*puiNewEvent = CA_END_CONFIRM_ACTION;
				}
				else
				{
					if (ConfirmActionCancel(usMapPos, usOldMapPos))
					{
						// Switch event out of confirm mode
						*puiNewEvent = CA_END_CONFIRM_ACTION;
					}
					else
					{
						*puiNewEvent = CA_ON_TERRAIN;
					}
				}
			}
			break;

		case HANDCURSOR_MODE:

			*puiNewEvent = HC_ON_TERRAIN;
			break;

		case RADIOCURSOR_MODE:
			break;

		}

		usOldMapPos = usMapPos;

	}
}

void GetPolledKeyboardInput(UINT32* puiNewEvent)
{
	static BOOLEAN	fShifted = FALSE;
	static BOOLEAN	fShifted2 = FALSE;
	static BOOLEAN	fCtrlDown = FALSE;
	static BOOLEAN	fAltDown = FALSE;
	static BOOLEAN	fDeleteDown = FALSE;
	static BOOLEAN	fEndDown = FALSE;

	// CHECK FOR POLLED KEYS!!
	// CHECK FOR CTRL
	switch (gCurrentUIMode)
	{
	case DONT_CHANGEMODE:
	case CONFIRM_MOVE_MODE:
	case CONFIRM_ACTION_MODE:
	case LOOKCURSOR_MODE:
	case TALKCURSOR_MODE:
	case IDLE_MODE:
	case MOVE_MODE:
	case ACTION_MODE:
	case HANDCURSOR_MODE:
	case RADIOCURSOR_MODE:

		if (_KeyDown(CTRL))
		{
			if (fCtrlDown == FALSE)
			{
				ErasePath(TRUE);
				gfPlotNewMovement = TRUE;
			}
			fCtrlDown = TRUE;
			*puiNewEvent = HC_ON_TERRAIN;

		}
		if (!(_KeyDown(CTRL)) && fCtrlDown)
		{
			fCtrlDown = FALSE;
			*puiNewEvent = M_ON_TERRAIN;
			gfPlotNewMovement = TRUE;
		}
		break;
	}

	// CHECK FOR ALT
	switch (gCurrentUIMode)
	{
	case MOVE_MODE:

		if (_KeyDown(ALT))
		{
			if (fAltDown == FALSE)
			{
				// Get currently selected guy and change reverse....
				if (gusSelectedSoldier != NOBODY)
				{
					gUIUseReverse = TRUE;
					ErasePath(TRUE);
					gfPlotNewMovement = TRUE;
				}
			}
			fAltDown = TRUE;

		}
		if (!(_KeyDown(ALT)) && fAltDown)
		{
			if (gusSelectedSoldier != NOBODY)
			{
				gUIUseReverse = FALSE;
				ErasePath(TRUE);
				gfPlotNewMovement = TRUE;
			}

			fAltDown = FALSE;
		}
		break;
	}

	// Check realtime input!
	if (((gTacticalStatus.uiFlags & REALTIME) || !(gTacticalStatus.uiFlags & INCOMBAT)))
	{
		//if ( _KeyDown( CAPS )	) //&& !fShifted )
		//{
		//	fShifted = TRUE;
		//	if ( gCurrentUIMode != ACTION_MODE && gCurrentUIMode != CONFIRM_ACTION_MODE )
		//	{
		//		*puiNewEvent = CA_ON_TERRAIN;
		//	}
		//}
		//if ( !(_KeyDown( CAPS ) ) && fShifted )
		//{
		//	fShifted = FALSE;
		//	{
		//		*puiNewEvent = M_ON_TERRAIN;
		//	}
		//}


		if (_KeyDown(SHIFT)) //&& !fShifted )
		{
			fShifted2 = TRUE;
			if (gCurrentUIMode != MOVE_MODE && gCurrentUIMode != CONFIRM_MOVE_MODE)
			{
				//puiNewEvent = M_ON_TERRAIN;
			}
		}
		if (!(_KeyDown(SHIFT)) && fShifted2)
		{
			fShifted2 = FALSE;
			if (gCurrentUIMode != ACTION_MODE && gCurrentUIMode != CONFIRM_ACTION_MODE)
			{
				//	*puiNewEvent = A_ON_TERRAIN;
			}
		}

	}

	if (_KeyDown(DEL) && !fDeleteDown)
	{

		if (_KeyDown(ALT))
			SwitchToHostileTrapsView();	// added by Flugente
		else
			SwitchToEnemyView();

		fDeleteDown = TRUE;
	}

	if (!_KeyDown(DEL) && fDeleteDown)
	{

		if (_KeyDown(ALT))
			SwitchMineViewOff();	// added by Flugente
		else
			SwitchViewOff();

		fDeleteDown = FALSE;
	}

	if (_KeyDown(END) && !fEndDown)
	{

		if (_KeyDown(ALT))
			SwitchToTrapNetworkView();	// added by Flugente
		else
			SwitchToMercView();

		fEndDown = TRUE;
	}

	if (!_KeyDown(END) && fEndDown)
	{
		if (_KeyDown(ALT))
			SwitchMineViewOff();	// added by Flugente
		else
			SwitchViewOff();


		fEndDown = FALSE;
	}
}

void CheatCreateItem()
{
	if (gusSelectedSoldier != NOBODY)
	{
		INT16 status = 100;
		FLOAT temperature = 0.0;

		if (Item[usitem].foodtype)
			temperature = OVERHEATING_MAX_TEMPERATURE;

		// Flugente: spawn items while debugging
		OBJECTTYPE newobj;
		CreateItem(usitem, status, &newobj);
		(newobj)[0]->data.bTemperature = temperature;

		if (!AutoPlaceObject(MercPtrs[gusSelectedSoldier], &newobj, FALSE))
			AddItemToPool(MercPtrs[gusSelectedSoldier]->sGridNo, &newobj, 1, 0, 0, -1);
	}
}

void CheatNewMerc(int nProfileID)
{
	if (nProfileID >= NUM_PROFILES || nProfileID < 0)
	{
		ScreenMsg(FONT_ORANGE, MSG_BETAVERSION, L"Invalid Profile ID.");
		return;
	}

	MERC_HIRE_STRUCT HireMercStruct;
	memset(&HireMercStruct, 0, sizeof(MERC_HIRE_STRUCT));
	HireMercStruct.ubProfileID = nProfileID;

	//DEF: temp
	HireMercStruct.sSectorX = gWorldSectorX;
	HireMercStruct.sSectorY = gWorldSectorY;
	HireMercStruct.bSectorZ = gbWorldSectorZ;
	HireMercStruct.ubInsertionCode = INSERTION_CODE_GRIDNO;
	HireMercStruct.usInsertionData = mappos;
	HireMercStruct.fCopyProfileItemsOver = TRUE;
	HireMercStruct.iTotalContractLength = 7;

	//specify when the merc should arrive
	HireMercStruct.uiTimeTillMercArrives = 0;

	//if we succesfully hired the merc
	INT8 bReturnCode = HireMerc(&HireMercStruct);

	if (bReturnCode == MERC_HIRE_FAILED)
	{
		ScreenMsg(FONT_ORANGE, MSG_BETAVERSION, L"Merc hire failed:	Either already hired or dislikes you.");
	}
	// WDS - make number of mercenaries, etc. be configurable
	else if (bReturnCode == MERC_HIRE_OVER_PLAYER_LIMIT)
	{
		ScreenMsg(FONT_ORANGE, MSG_BETAVERSION, L"Can't hire that many mercs.");
	}
	else
	{
		// Get soldier from profile
		SOLDIERTYPE* pSoldier = FindSoldierByProfileID(nProfileID, FALSE);

		MercArrivesCallback(pSoldier->ubID);
		SelectSoldier(pSoldier->ubID, FALSE, TRUE);
	}
}

void CheatSelectExplosionCallBack(UINT8 ubResult)
{
	//STR16 info = L"STUN(131), TEARGAS(132), MUSTARD(133), MINI_G(134), HAND_G(135), RDX(136), TNT(137), HMX(138), C1(139), MORTAR_SHELL(140),\n"
	//	"MINE(141), C4(142), TRIP_FLARE(143), TRIP_KLAXON(144), SHPD_CHRGE(145), BRK_LGT(146), GL_HE_G(147), GL_TEARGAS_G(148),\n"
	//	"GL_STUN_G(149), GL_SMOKE_G(150), SMOKE_G(151), TANK_SHELL(152), STRUCTURE_IGNITE(153), CREATURE_COCKTAIL(154),\n"
	//	"STRUCTURE_EXPLOSION(155), GREAT_BIG_EXPLOSION(156), BIG_TEAR_GAS(157), SMALL_CREATURE_GAS(158), \n"
	//	"LARGE_CREATURE_GAS(159), VERY_SMALL_CREATURE_GAS(270), SMALL_SMOKE(1702), MOLOTOV_EXPLOSION(979), GAS_EXPLOSION(1703), \n"
	//	"FRAG_EXPLOSION(1704)";

	if (ubResult == MSG_BOX_RETURN_OK && wcscmp(gszMsgBoxInputString, L"") > 0)
	{
		usitem = _wtoi(gszMsgBoxInputString);
		if (((usitem >= 131) && (usitem <= 159)) || usitem == 270 || usitem == 979 || usitem == 1702 || usitem == 1703 || usitem == 1704)
			CreateExplosion(usitem, gusMapPos);
	}
	memset(gszMsgBoxInputString, 0, sizeof(gszMsgBoxInputString));
}

void MercCreationCallBack(UINT8 ubResult)
{
	if (ubResult == MSG_BOX_RETURN_OK && wcscmp(gszMsgBoxInputString, L"") > 0)
	{
		CheatNewMerc(_wtoi(gszMsgBoxInputString));
	}
	memset(gszMsgBoxInputString, 0, sizeof(gszMsgBoxInputString));
}

void ItemCreationCallBack(UINT8 ubResult)
{
	if (ubResult == MSG_BOX_RETURN_OK && wcscmp(gszMsgBoxInputString, L"") > 0)
	{
		usitem = _wtoi(gszMsgBoxInputString);
		CheatCreateItem();

	}
	memset(gszMsgBoxInputString, 0, sizeof(gszMsgBoxInputString));
}

void GetKeyboardInput(UINT32* puiNewEvent)
{
	InputAtom					InputEvent;
	BOOLEAN						fKeyTaken = FALSE;
	POINT	MousePos;
	//SOLDIERTYPE				*pSoldier;
	static BOOLEAN	fShifted = FALSE;
	static BOOLEAN	fShifted2 = FALSE;
	static BOOLEAN	fAltDown = FALSE;
	INT32 usMapPos;

	GetCursorPos(&MousePos);
	ScreenToClient(ghWindow, &MousePos); // In window coords!

	GetMouseMapPos(&usMapPos);

	while (DequeueEvent(&InputEvent) == TRUE)
	{
		// HOOK INTO MOUSE HOOKS
		switch (InputEvent.usEvent)
		{
		case LEFT_BUTTON_DOWN:
			MouseSystemHook(LEFT_BUTTON_DOWN, (INT16)MousePos.x, (INT16)MousePos.y, _LeftButtonDown, _RightButtonDown);
			break;
		case LEFT_BUTTON_UP:
			MouseSystemHook(LEFT_BUTTON_UP, (INT16)MousePos.x, (INT16)MousePos.y, _LeftButtonDown, _RightButtonDown);
			break;
		case RIGHT_BUTTON_DOWN:
			MouseSystemHook(RIGHT_BUTTON_DOWN, (INT16)MousePos.x, (INT16)MousePos.y, _LeftButtonDown, _RightButtonDown);
			break;
		case RIGHT_BUTTON_UP:
			MouseSystemHook(RIGHT_BUTTON_UP, (INT16)MousePos.x, (INT16)MousePos.y, _LeftButtonDown, _RightButtonDown);
			break;

		}

		// handle for fast help text for interface stuff
		if (IsTheInterfaceFastHelpTextActive())
		{
			if (InputEvent.usEvent == KEY_UP)
			{
				ShutDownUserDefineHelpTextRegions();
			}

			continue;
		}

		// Check for waiting for keyboard advance
		if (gfUIWaitingForUserSpeechAdvance && InputEvent.usEvent == KEY_UP)
		{
			// We have a key, advance!
			DialogueAdvanceSpeech();

			// Ignore anything else
			continue;
		}

		// ATE: if game paused because fo player, unpasue with any key
		if (gfPauseDueToPlayerGamePause && InputEvent.usEvent == KEY_UP)
		{
			HandlePlayerPauseUnPauseOfGame();

			continue;
		}

		if ((InputEvent.usEvent == KEY_DOWN))
		{
			if (giUIMessageOverlay != -1)
			{
				EndUIMessage();
				continue;
			}

			// End auto bandage if we want....
			if (gTacticalStatus.fAutoBandageMode)
			{
				AutoBandage(FALSE);
				*puiNewEvent = LU_ENDUILOCK;
			}
		}

		if (gUIKeyboardHook != NULL)
		{
			fKeyTaken = gUIKeyboardHook(&InputEvent);
		}
		if (fKeyTaken)
		{
			continue;
		}

		/*
		if( (InputEvent.usEvent == KEY_DOWN )&& ( InputEvent.usParam == ) )
		{
		HandlePlayerPauseUnPauseOfGame( );
		}
		*/

		if ((InputEvent.usEvent == KEY_UP) && (InputEvent.usParam == PAUSE) && !(gTacticalStatus.uiFlags & ENGAGED_IN_CONV))
		{
			// Pause game!
			HandlePlayerPauseUnPauseOfGame();
		}

		// FIRST DO KEYS THAT ARE USED EVERYWHERE!
		if ((InputEvent.usEvent == KEY_DOWN) && (InputEvent.usParam == 'x') && (InputEvent.usKeyState & ALT_DOWN))
		{
			HandleShortCutExitState();
			//*puiNewEvent = I_EXIT;
		}
#ifdef JA2UB
		//Ja25 No meanwhiles
#else
		if ((InputEvent.usEvent == KEY_UP) && (InputEvent.usParam == ESC))
		{
			if (AreInMeanwhile() && gCurrentMeanwhileDef.ubMeanwhileID != INTERROGATION)
			{
				DeleteTalkingMenu();
				EndMeanwhile();
			}

			// Flugente: speed up dynamic dialogue boxes
			// Note that this will behave oddly on the morning of January 1st 1970 :-)
			DelayBoxDestructionBy(-gGameExternalOptions.sDynamicDialogueTimeOffset);
		}
#endif

		// BEGIN: by Lejardo for mouse-locking in game screen
		// WANNE: If the game runs in windowed mode, the user can "lock" / "unlock" the mouse cursor
		if (iWindowedMode && !gfInKeyRingPopup && !gfInItemStackPopup)
		{
			if ((InputEvent.usEvent == KEY_DOWN) && InputEvent.usParam == 'z')
			{
				if ((InputEvent.usKeyState & CTRL_DOWN) && !(InputEvent.usKeyState & ALT_DOWN))
				{
					// Unlock the mouse cursor
					if (gfMouseLockedOnBorder)
					{
						FreeMouseCursor(FALSE);

						ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, pMessageStrings[MSG_WINDOWED_MODE_RELEASE_MOUSE]);
					}
					// Lock the mouse cursor
					else
					{
						SGPRect			LJDRect;

						LJDRect.iLeft = 0;
						LJDRect.iTop = 0;
						LJDRect.iRight = SCREEN_WIDTH;
						LJDRect.iBottom = SCREEN_HEIGHT;
						RestrictMouseCursor(&LJDRect);

						ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, pMessageStrings[MSG_WINDOWED_MODE_LOCK_MOUSE]);
					}

					gfMouseLockedOnBorder = !gfMouseLockedOnBorder;
				}
			}
		}
		// END: by Lejardo for mouse-locking in game screen

		// WANNE: Just disabled for now, because we don't need it yet.
		/*
		// WANNE: If the game hangs on enemy turn, just press ALT + CTRL + E and the game will continue with enemy turn!!
		if ( (InputEvent.usEvent == KEY_DOWN )&& (InputEvent.usKeyState & CTRL_DOWN) && ( InputEvent.usParam == 'e') )
		{
			if( InputEvent.usKeyState & ALT_DOWN )
			{
				if (gTacticalStatus.ubCurrentTeam != 0)
				{
					if( (gTacticalStatus.uiFlags & TURNBASED) && (gTacticalStatus.uiFlags & INCOMBAT) )
					{
						EndTurn( 1 );
					}
				}
			}
		}
		*/

		if (!is_networked)
		{
			// Allow to load everywhere
			if ((InputEvent.usEvent == KEY_DOWN) && (InputEvent.usParam == 'l'))
			{
				if (InputEvent.usKeyState & ALT_DOWN)
				{
					if (!(gTacticalStatus.uiFlags & ENGAGED_IN_CONV))
					{
						gTacticalStatus.ubDisablePlayerInterrupts = FALSE;

						gfSaveGame = FALSE;
						gfCameDirectlyFromGame = TRUE;

						SetOptionsPreviousScreen(GAME_SCREEN);

						EscapeUILock();
						// cancel, the player can move when it is not its turn!
						//Heinz: 28.02.09 BUGFIX: player doesn't need to see save/load screen
						//LeaveTacticalScreen( SAVE_LOAD_SCREEN );
						DoQuickLoad();
					}
				}
				else if (InputEvent.usKeyState & CTRL_DOWN)
				{
					// WANNE: Do not allow saving via the save screen when it is not our turn,
					// because there is an exploit when you close the save window without saving, you can move your merc even it is not your turn
					// IF UI HAS LOCKED, ONLY ALLOW EXIT!
					if (gfDisableRegionActive || gfUserTurnRegionActive)
					{
						continue;
					}

					if (!(gTacticalStatus.uiFlags & ENGAGED_IN_CONV))
					{
						gfSaveGame = FALSE;
						gfCameDirectlyFromGame = TRUE;

						SetOptionsPreviousScreen(GAME_SCREEN);
						LeaveTacticalScreen(SAVE_LOAD_SCREEN);
					}
				}
			}
		}

		if (is_networked)
		{
			// WANNE: Disabled the quick saving in a multiplayer game, because if you quit out of the save dialog,
			// you can move your merc even if it is not your turn.
			/*
			if ((InputEvent.usEvent == KEY_DOWN )&& ( InputEvent.usParam == 's') )//allow saving 'always'//hayden
			{
				if( InputEvent.usKeyState & ALT_DOWN )
				{
					if( !fDisableMapInterfaceDueToBattle && !( gTacticalStatus.uiFlags & ENGAGED_IN_CONV ) )
					{
						//if the game CAN be saved
						if( CanGameBeSaved() )
						{
							guiPreviousOptionScreen = GAME_SCREEN;
							//guiPreviousOptionScreen = guiCurrentScreen;
							DoQuickSave();
						}
						else
						{
							//Display a message saying the player cant save now
							DoMessageBox( MSG_BOX_BASIC_STYLE, zNewTacticalMessages[ TCTL_MSG__IRON_MAN_CANT_SAVE_NOW ], GAME_SCREEN, ( UINT8 )MSG_BOX_FLAG_OK, NULL, NULL );
						}
					}
				}
				else if( InputEvent.usKeyState & CTRL_DOWN )
				{
					if( !fDisableMapInterfaceDueToBattle && !( gTacticalStatus.uiFlags & ENGAGED_IN_CONV ) )
					{
						//if the game CAN be saved
						if( CanGameBeSaved() )
						{
							gfSaveGame = TRUE;
							gfCameDirectlyFromGame = TRUE;

							guiPreviousOptionScreen = GAME_SCREEN;
							LeaveTacticalScreen( SAVE_LOAD_SCREEN );
						}
						else
						{
							//Display a message saying the player cant save now
							DoMessageBox( MSG_BOX_BASIC_STYLE, zNewTacticalMessages[ TCTL_MSG__IRON_MAN_CANT_SAVE_NOW ], GAME_SCREEN, ( UINT8 )MSG_BOX_FLAG_OK, NULL, NULL);
						}
					}
				}
			}
			*/

			//#ifdef DISABLE_MP_INTERRUPTS_IN_COOP

						// WANNE: Not needed to show the override turn dialog
			//#else

			if ((InputEvent.usEvent == KEY_DOWN) && (InputEvent.usParam == 'e'))
			{
				if (InputEvent.usKeyState & ALT_DOWN)
				{
					if (!(gTacticalStatus.uiFlags & ENGAGED_IN_CONV))
					{
						overide_turn();
					}
				}
			}

			//#endif

			if ((InputEvent.usEvent == KEY_DOWN) && (InputEvent.usParam == 'k'))
			{
				if (InputEvent.usKeyState & ALT_DOWN)
				{
					if (!(gTacticalStatus.uiFlags & ENGAGED_IN_CONV))
					{
						kick_player();
					}
				}
			}

			// OJW - 090209 - ingame chat
			if (InputEvent.usEvent == KEY_UP && InputEvent.usParam == 'y')
			{
				if (!(InputEvent.usKeyState & ALT_DOWN) && !(InputEvent.usKeyState & CTRL_DOWN))
				{
					OpenChatMsgBox();
					continue;
				}
			}
		} // end is_networked


		// Break of out IN CONV...
		if (CHEATER_CHEAT_LEVEL())
		{
			if ((InputEvent.usEvent == KEY_DOWN) && (InputEvent.usParam == ENTER) && (InputEvent.usKeyState & ALT_DOWN))
			{
				if (gTacticalStatus.uiFlags & ENGAGED_IN_CONV)
				{
					gTacticalStatus.uiFlags &= (~ENGAGED_IN_CONV);
					giNPCReferenceCount = 0;
				}
			}
		}

		if (gTacticalStatus.uiFlags & TURNBASED && (gTacticalStatus.uiFlags & INCOMBAT))
		{
			{
				if (gTacticalStatus.ubCurrentTeam != gbPlayerNum)
				{
					if (CHEATER_CHEAT_LEVEL())
					{
						if ((InputEvent.usEvent == KEY_DOWN) && (InputEvent.usParam == ENTER) && (InputEvent.usKeyState & ALT_DOWN))
						{
							// ESCAPE ENEMY'S TURN
							EndAIDeadlock();

							// Decrease global busy	counter...
							gTacticalStatus.ubAttackBusyCount = 0;
#ifdef DEBUG_ATTACKBUSY
							OutputDebugString("Resetting attack busy due to keyboard interrupt.\n");
#endif
							guiPendingOverrideEvent = LU_ENDUILOCK;
							UIHandleLUIEndLock(NULL);

						}
					}
					//Madd: removed from cheat mode
					if ((InputEvent.usEvent == KEY_DOWN) && (InputEvent.usParam == ENTER) && (InputEvent.usKeyState & CTRL_DOWN))
					{
						EscapeUILock();
					}
				}
				else
				{
					if (CHEATER_CHEAT_LEVEL() && (InputEvent.usEvent == KEY_DOWN) && (InputEvent.usParam == ENTER) && (InputEvent.usKeyState & CTRL_DOWN))
					{
						//UNLOCK UI
						EscapeUILock();
					}
					else if ((InputEvent.usEvent == KEY_DOWN) && InputEvent.usParam == ENTER)
					{
						// Cycle through enemys
						CycleThroughKnownEnemies();
					}
				}
			}
		}

		if (gfInTalkPanel)
		{
			HandleTalkingMenuKeys(&InputEvent, puiNewEvent);
		}

		// Do some checks based on what mode we are in
		switch (gCurrentUIMode)
		{
		case EXITSECTORMENU_MODE:

			HandleSectorExitMenuKeys(&InputEvent, puiNewEvent);
			continue;

		case GETTINGITEM_MODE:

			HandleItemMenuKeys(&InputEvent, puiNewEvent);
			continue;

		case MENU_MODE:

			HandleMenuKeys(&InputEvent, puiNewEvent);
			continue;

		case OPENDOOR_MENU_MODE:

			HandleOpenDoorMenuKeys(&InputEvent, puiNewEvent);
			continue;
		}


		// CHECK ESC KEYS HERE....
		if ((InputEvent.usEvent == KEY_DOWN) && (InputEvent.usParam == ESC))
		{
			//EscapeUILock( );
#ifdef JA2TESTVERSION
			if (InAirRaid())
			{
				EndAirRaid();
			}
#endif

			// Cancel out of spread burst...
			gfBeginBurstSpreadTracking = FALSE;
			gfRTClickLeftHoldIntercepted = TRUE;
			if (gusSelectedSoldier != NOBODY)
			{
				MercPtrs[gusSelectedSoldier]->flags.fDoSpread = FALSE;
			}

			// Before anything, delete popup box!
			EndUIMessage();

			// CANCEL FROM PLANNING MODE!
			if (InUIPlanMode())
			{
				EndUIPlan();
				continue;
			}

			if (InItemDescriptionBox())
			{
				DeleteItemDescriptionBox();
				continue;
			}
			else if (InKeyRingPopup())
			{
				DeleteKeyRingPopup();
				continue;
			}

			if (gDragSelection.Active())
			{
				gDragSelection.Cancel();
				continue;
			}
			else if (gReinforcementNumber.Active())
			{
				gReinforcementNumber.Cancel();
				continue;
			}
			else if (gSoldierSelection.Active())
			{
				gSoldierSelection.Cancel();
				continue;
			}
			else if (gArtilleryTeam.Active())
			{
				gArtilleryTeam.Cancel();
				continue;
			}
			else if (gArtillerySector.Active())
			{
				gArtillerySector.Cancel();
				continue;
			}
			else if (gReinforcementSector.Active())
			{
				gReinforcementSector.Cancel();
				continue;
			}
			else if (gSkillSelection.Active())
			{
				gSkillSelection.Cancel();
				continue;
			}
			else if (gTraitSelection.Active())
			{
				gTraitSelection.Cancel();
				continue;
			}

			if (gCurrentUIMode == MENU_MODE)
			{
				// If we get a hit here and we're in menu mode, quit the menu mode
				EndMenuEvent(guiCurrentEvent);
				continue;
			}

			if (gCurrentUIMode == HANDCURSOR_MODE || gCurrentUIMode == RADIOCURSOR_MODE)
			{
				*puiNewEvent = A_CHANGE_TO_MOVE;
				continue;
			}

			if (!(gTacticalStatus.uiFlags & ENGAGED_IN_CONV))
			{
				if (gTacticalStatus.fAtLeastOneGuyOnMultiSelect)
				{
					// ATE: OK, stop any mercs who are moving by selection method....
					BOOLEAN fFound = StopRubberBandedMercFromMoving();

					// sevenfm: unready weapon for all selected
					if (!fFound)
					{
						UINT8 cnt = gTacticalStatus.Team[gbPlayerNum].bFirstID;
						for (SOLDIERTYPE* pSoldier = MercPtrs[cnt]; cnt <= gTacticalStatus.Team[gbPlayerNum].bLastID; cnt++, pSoldier++)
						{
							if (pSoldier->bActive && pSoldier->bInSector && pSoldier->flags.uiStatusFlags & SOLDIER_MULTI_SELECTED && WeaponReady(pSoldier))
							{
								pSoldier->InternalSoldierReadyWeapon(pSoldier->ubDirection, TRUE, FALSE);
								HandleSight(pSoldier, SIGHT_LOOK);
							}
						}
					}

					continue;
				}
				else if (gusSelectedSoldier != NOBODY &&
					MercPtrs[gusSelectedSoldier] &&
					!(gAnimControl[MercPtrs[gusSelectedSoldier]->usAnimState].uiFlags & ANIM_STATIONARY))
				{
					// If soldier is not stationary, stop
					MercPtrs[gusSelectedSoldier]->StopSoldier();
					*puiNewEvent = A_CHANGE_TO_MOVE;
					continue;
				}
			}

			// sevenfm: also stop dragging
			if (gusSelectedSoldier != NOBODY &&
				MercPtrs[gusSelectedSoldier] &&
				MercPtrs[gusSelectedSoldier]->IsDragging(false))
			{
				MercPtrs[gusSelectedSoldier]->CancelDrag();
				DirtyMercPanelInterface(MercPtrs[gusSelectedSoldier], DIRTYLEVEL2);
				continue;
			}

			// sevenfm: unready weapon
			if (gusSelectedSoldier != NOBODY &&
				MercPtrs[gusSelectedSoldier] &&
				WeaponReady(MercPtrs[gusSelectedSoldier]))
			{
				MercPtrs[gusSelectedSoldier]->InternalSoldierReadyWeapon(MercPtrs[gusSelectedSoldier]->ubDirection, TRUE, FALSE);
				HandleSight(MercPtrs[gusSelectedSoldier], SIGHT_LOOK);
				continue;
			}
		}

		// CHECK ESC KEYS HERE....
		if ((InputEvent.usEvent == KEY_DOWN) && (InputEvent.usParam == BACKSPACE))
		{
			StopAnyCurrentlyTalkingSpeech();
		}

		// IF UI HAS LOCKED, ONLY ALLOW EXIT!
		if (gfDisableRegionActive || gfUserTurnRegionActive)
		{
			continue;
		}

		// Check all those we want if enemy's turn
		if ((InputEvent.usEvent == KEY_UP) && (InputEvent.usParam == 'q'))
		{
			if (InputEvent.usKeyState & ALT_DOWN)
			{
				if (CHEATER_CHEAT_LEVEL())
				{
					static BOOLEAN fShowRoofs = TRUE;
					INT32 x;
					UINT16 usType;

					// Toggle removal of roofs...
					fShowRoofs = !fShowRoofs;

					for (x = 0; x < WORLD_MAX; x++)
					{
						for (usType = FIRSTROOF; usType <= LASTSLANTROOF; usType++)
						{
							HideStructOfGivenType(x, usType, (BOOLEAN)(!fShowRoofs));
						}
					}
					InvalidateWorldRedundency();
					SetRenderFlags(RENDER_FLAG_FULL);
				}

			}
			else if (InputEvent.usKeyState & CTRL_DOWN)
			{
#ifdef JA2BETAVERSION
				if (CHEATER_CHEAT_LEVEL())
				{
					LeaveTacticalScreen(ANIEDIT_SCREEN);
				}
#endif
			}
			else
			{
				if (INFORMATION_CHEAT_LEVEL())
				{
					*puiNewEvent = I_SOLDIERDEBUG;
				}
				else
				{
					//if ( !( gTacticalStatus.uiFlags & ENGAGED_IN_CONV ) )
					//	{
					//		if ( gusSelectedSoldier != NOBODY )
					//		{
					//			if ( gTacticalStatus.uiFlags & TURNBASED && !MercPtrs[ gusSelectedSoldier ]->fDontChargeReadyAPs )
					//			{
					//				INT16 apCost = GetAPsToReadyWeapon( MercPtrs[ gusSelectedSoldier ], 0 );
					//				if (MercPtrs[ gusSelectedSoldier ]->bActionPoints >= apCost )
					//				{
					//					DeductPoints( MercPtrs[ gusSelectedSoldier ],apCost , 0 );
					//					DirtyMercPanelInterface( MercPtrs[ gusSelectedSoldier ], DIRTYLEVEL2 );
					//					SoldierReadyWeapon( MercPtrs[ gusSelectedSoldier ] );
					//				}
					//			}
					//			else
					//			{
					//				SoldierReadyWeapon( MercPtrs[ gusSelectedSoldier ] );
					//			}

					//		}
					//	}
				}
			}
		}

#ifdef JA2TESTVERSION
		if ((InputEvent.usEvent == KEY_DOWN) && (InputEvent.usParam == '0') && (InputEvent.usKeyState & ALT_DOWN))
		{
			INT32 i = 0;
			INT32 sGridNo;
			INT32 iTime = GetJA2Clock();
			UINT8	ubLevel;

			for (i = 0; i < 1000; i++)
			{
				CalculateLaunchItemChanceToGetThrough(MercPtrs[gusSelectedSoldier], &(MercPtrs[gusSelectedSoldier]->inv[HANDPOS]), usMapPos, 0, 0, &sGridNo, TRUE, (INT8*)&ubLevel, TRUE);
			}

			ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_TESTVERSION, L"Physics 100 times: %d", (GetJA2Clock() - iTime));

		}
#endif


#ifdef NETWORKED
		// DEF: Test Networking
		if ((InputEvent.usEvent == KEY_DOWN) && (InputEvent.usParam == '0') && (InputEvent.usKeyState & ALT_DOWN))
		{
			DisplayMultiPlayerInfo();
		}
		if ((InputEvent.usEvent == KEY_DOWN) && (InputEvent.usParam == '9') && (InputEvent.usKeyState & ALT_DOWN))
		{
			DisplayDirectPlayInfo();
		}
		if ((InputEvent.usEvent == KEY_DOWN) && (InputEvent.usParam == '8') && (InputEvent.usKeyState & ALT_DOWN))
		{
			DisplayDirectPlayPlayerInfo();
		}

		if ((InputEvent.usEvent == KEY_DOWN) && (InputEvent.usParam == '7') && (InputEvent.usKeyState & ALT_DOWN))
		{
			SetDisplayFlag();
		}
#endif
		// INPUT KEY HERE EVENT HERE ...
		if (InputEvent.usEvent == KEY_DOWN)
		{
			BOOLEAN fAlt, fCtrl, fShift;
			fAlt = InputEvent.usKeyState & ALT_DOWN ? TRUE : FALSE;
			fCtrl = InputEvent.usKeyState & CTRL_DOWN ? TRUE : FALSE;
			fShift = InputEvent.usKeyState & SHIFT_DOWN ? TRUE : FALSE;
			switch (InputEvent.usParam)
			{
			case SPACE:
				GKIWhenDQEOnKD::On_SPACE(puiNewEvent, fAlt, fCtrl, fShift);
				break;
			case LEFTARROW:
				GKIWhenDQEOnKD::On_LEFTARROW(puiNewEvent, fAlt, fCtrl, fShift);
				break;
			case RIGHTARROW:
				GKIWhenDQEOnKD::On_RIGHTARROW(puiNewEvent, fAlt, fCtrl, fShift);
				break;
			case INSERT:
				GKIWhenDQEOnKD::On_INSERT(puiNewEvent, fAlt, fCtrl, fShift);
				break;
			case DEL:
				GKIWhenDQEOnKD::On_DELETE(puiNewEvent, fAlt, fCtrl, fShift);
				break;
			case HOME:
				GKIWhenDQEOnKD::On_HOME(puiNewEvent, fAlt, fCtrl, fShift);
				break;
			case END:
				GKIWhenDQEOnKD::On_END(puiNewEvent, fAlt, fCtrl, fShift);
				break;
			case PGUP:
				GKIWhenDQEOnKD::On_PGUP(puiNewEvent, fAlt, fCtrl, fShift);
				break;
			case PGDN:
				GKIWhenDQEOnKD::On_PGDN(puiNewEvent, fAlt, fCtrl, fShift);
				break;
			case BACKSPACE:
				// used for stopping speech
				GKIWhenDQEOnKD::On_BACKSPACE(puiNewEvent, fAlt, fCtrl, fShift);
				break;
			case TAB:
				GKIWhenDQEOnKD::On_TAB(puiNewEvent, fAlt, fCtrl, fShift);
				break;
			case F1:
				GKIWhenDQEOnKD::On_F1(puiNewEvent, fAlt, fCtrl, fShift);
				break;
			case F2:
				GKIWhenDQEOnKD::On_F2(puiNewEvent, fAlt, fCtrl, fShift);
				break;
			case F3:
				GKIWhenDQEOnKD::On_F3(puiNewEvent, fAlt, fCtrl, fShift);
				break;
			case F4:
				GKIWhenDQEOnKD::On_F4(puiNewEvent, fAlt, fCtrl, fShift);
				break;
			case F5:
				GKIWhenDQEOnKD::On_F5(puiNewEvent, fAlt, fCtrl, fShift);
				break;
			case F6:
				GKIWhenDQEOnKD::On_F6(puiNewEvent, fAlt, fCtrl, fShift);
				break;
			case F7:
				GKIWhenDQEOnKD::On_F7(puiNewEvent, fAlt, fCtrl, fShift);
				break;
			case F8:
				GKIWhenDQEOnKD::On_F8(puiNewEvent, fAlt, fCtrl, fShift);
				break;
			case F9:
				GKIWhenDQEOnKD::On_F9(puiNewEvent, fAlt, fCtrl, fShift);
				break;
			case F10:
				GKIWhenDQEOnKD::On_F10(puiNewEvent, fAlt, fCtrl, fShift);
				break;
			case F11:
				GKIWhenDQEOnKD::On_F11(puiNewEvent, fAlt, fCtrl, fShift);
				break;
			case F12:
				GKIWhenDQEOnKD::On_F12(puiNewEvent, fAlt, fCtrl, fShift);
				break;
			case '-':
			case '_':
				GKIWhenDQEOnKD::On_MinusOrUnderscore(puiNewEvent, fAlt, fCtrl, fShift);
				break;
			case '+':
				GKIWhenDQEOnKD::On_Plus(puiNewEvent, fAlt, fCtrl, fShift);
				break;
			case '=':
				GKIWhenDQEOnKD::On_Equal(puiNewEvent, fAlt, fCtrl, fShift);
				break;
			case ',':
				GKIWhenDQEOnKD::On_Comma(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case '.':
				GKIWhenDQEOnKD::On_Dot(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case '/':
				GKIWhenDQEOnKD::On_Slash(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case '\\':
				GKIWhenDQEOnKD::On_BackSlash(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case '`':
				GKIWhenDQEOnKD::On_BackQuote(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case '1':
				GKIWhenDQEOnKD::On_One(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case '2':
				GKIWhenDQEOnKD::On_Two(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case '3':
				GKIWhenDQEOnKD::On_Three(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case '4':
				GKIWhenDQEOnKD::On_Four(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case '5':
				GKIWhenDQEOnKD::On_Five(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case '6':
				GKIWhenDQEOnKD::On_Six(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case '7':
				GKIWhenDQEOnKD::On_Seven(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case '8':
				GKIWhenDQEOnKD::On_Eight(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case '9':
				GKIWhenDQEOnKD::On_Nine(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case '0':
				GKIWhenDQEOnKD::On_Zero(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case '!':
				GKIWhenDQEOnKD::On_Exclamation(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case '@':
				GKIWhenDQEOnKD::On_AtSign(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case '#':
				GKIWhenDQEOnKD::On_Hash(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case '$':
				GKIWhenDQEOnKD::On_DollarSign(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case '%':
				GKIWhenDQEOnKD::On_Percent(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case '^':
				GKIWhenDQEOnKD::On_Caret(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case '&':
				GKIWhenDQEOnKD::On_Ampersand(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case '*':
				GKIWhenDQEOnKD::On_Asterix(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case '(':
				GKIWhenDQEOnKD::On_OpenParenthesis(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case ')':
				GKIWhenDQEOnKD::On_CloseParenthesis(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case 'a':
				GKIWhenDQEOnKD::On_a(puiNewEvent, fAlt, fCtrl, fShift, usMapPos, &gCurrentFortificationStructure, &gCurrentFortificationTileLibraryIndex);
				break;
			case 'A':
				GKIWhenDQEOnKD::On_A(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case 'b':
				GKIWhenDQEOnKD::On_b(puiNewEvent, fAlt, fCtrl, fShift, usMapPos, &gCurrentFortificationStructure, &gCurrentFortificationTileLibraryIndex);
				break;
			case 'B':
				GKIWhenDQEOnKD::On_B(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case 'c':
				GKIWhenDQEOnKD::On_c(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case 'C':
				GKIWhenDQEOnKD::On_C(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case 'd':
				GKIWhenDQEOnKD::On_d(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case 'D':
				GKIWhenDQEOnKD::On_D(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case 'e':
				GKIWhenDQEOnKD::On_e(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case 'E':
				GKIWhenDQEOnKD::On_E(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case 'f':
				GKIWhenDQEOnKD::On_f(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case 'F':
				GKIWhenDQEOnKD::On_F(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case 'G':
				GKIWhenDQEOnKD::On_G(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case 'g':
				GKIWhenDQEOnKD::On_g(puiNewEvent, fAlt, fCtrl, fShift, usMapPos, &mappos);
				break;
			case 'H':
				GKIWhenDQEOnKD::On_H(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case 'h':
				GKIWhenDQEOnKD::On_h(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case 'I':
				GKIWhenDQEOnKD::On_I(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case 'i':
				GKIWhenDQEOnKD::On_i(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case 'j':
				if (GKIWhenDQEOnKD::On_j(puiNewEvent, fAlt, fCtrl, fShift, usMapPos, &gfNextFireJam))
					return;
				break;
			case 'J':
				GKIWhenDQEOnKD::On_J(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case 'k':
				GKIWhenDQEOnKD::On_k(puiNewEvent, fAlt, fCtrl, fShift, usMapPos, &gusItemExplosion);
				break;
			case 'K':
				GKIWhenDQEOnKD::On_K(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case 'l':
				GKIWhenDQEOnKD::On_l(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case 'L':
				GKIWhenDQEOnKD::On_L(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case 'm':
				GKIWhenDQEOnKD::On_m(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case 'M':
				GKIWhenDQEOnKD::On_M(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case 'N':
				GKIWhenDQEOnKD::On_N(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case 'n':
				GKIWhenDQEOnKD::On_n(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case 'o':
				GKIWhenDQEOnKD::On_o(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case 'O':
				GKIWhenDQEOnKD::On_O(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case 'p':
				GKIWhenDQEOnKD::On_p(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case 'P':
				GKIWhenDQEOnKD::On_P(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case 'q':
				GKIWhenDQEOnKD::On_q(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case 'Q':
				GKIWhenDQEOnKD::On_Q(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case 'R':
				GKIWhenDQEOnKD::On_R(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case 'r':
				GKIWhenDQEOnKD::On_r(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case 'S':
				GKIWhenDQEOnKD::On_S(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case 's':
				if (GKIWhenDQEOnKD::On_s(puiNewEvent, fAlt, fCtrl, fShift, usMapPos))
					continue; // see the content of the function GKIWhenDQEOnKD::On_s(...), why they put continue in it? we just adopt it anyway
				break;
			case 't':
				GKIWhenDQEOnKD::On_t(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case 'T':
				GKIWhenDQEOnKD::On_T(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case 'u':
				GKIWhenDQEOnKD::On_u(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case 'U':
				GKIWhenDQEOnKD::On_U(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case 'v':
				GKIWhenDQEOnKD::On_v(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case 'V':
				GKIWhenDQEOnKD::On_V(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case 'w':
				GKIWhenDQEOnKD::On_w(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case 'W':
				GKIWhenDQEOnKD::On_W(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case 'x':
				GKIWhenDQEOnKD::On_x(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case 'X':
				// The_Bob - real time sneaking, 01-06-09
				// shift-ctrl-x: toggle real time sneaking
				GKIWhenDQEOnKD::On_X(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case 'y':
				GKIWhenDQEOnKD::On_y(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case 'Y':
				GKIWhenDQEOnKD::On_Y(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case 'z':
				GKIWhenDQEOnKD::On_z(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;
			case 'Z':
				GKIWhenDQEOnKD::On_Z(puiNewEvent, fAlt, fCtrl, fShift, usMapPos);
				break;

			}
		}
	}
}


void HandleTalkingMenuKeys(InputAtom* pInputEvent, UINT32* puiNewEvent)
{
	// CHECK ESC KEYS HERE....
	if (pInputEvent->usEvent == KEY_UP)
	{
		if (pInputEvent->usParam == ESC)
		{
			//Handle esc in talking menu
			if (HandleTalkingMenuEscape(TRUE, TRUE))
			{
				*puiNewEvent = A_CHANGE_TO_MOVE;
			}
		}
		else if (pInputEvent->usParam == BACKSPACE)
		{
			HandleTalkingMenuBackspace();
		}

	}
}

void HandleSectorExitMenuKeys(InputAtom* pInputEvent, UINT32* puiNewEvent)
{
	// CHECK ESC KEYS HERE....
	if ((pInputEvent->usEvent == KEY_UP) && (pInputEvent->usParam == ESC))
	{
		//Handle esc in talking menu
		RemoveSectorExitMenu(FALSE);

		*puiNewEvent = A_CHANGE_TO_MOVE;
	}
}

void HandleOpenDoorMenuKeys(InputAtom* pInputEvent, UINT32* puiNewEvent)
{
	// CHECK ESC KEYS HERE....
	if ((pInputEvent->usEvent == KEY_UP) && (pInputEvent->usParam == ESC))
	{
		//Handle esc in talking menu
		CancelOpenDoorMenu();
		HandleOpenDoorMenu();
		*puiNewEvent = A_CHANGE_TO_MOVE;
	}
}

void HandleMenuKeys(InputAtom* pInputEvent, UINT32* puiNewEvent)
{
	// CHECK ESC KEYS HERE....
	if ((pInputEvent->usEvent == KEY_UP) && (pInputEvent->usParam == ESC))
	{
		//Handle esc in talking menu
		CancelMovementMenu();

		*puiNewEvent = A_CHANGE_TO_MOVE;
	}
}

void HandleItemMenuKeys(InputAtom* pInputEvent, UINT32* puiNewEvent)
{
	// CHECK ESC KEYS HERE....
	if ((pInputEvent->usEvent == KEY_UP) && (pInputEvent->usParam == ESC))
	{
		//Handle esc in talking menu
		RemoveItemPickupMenu();
		*puiNewEvent = A_CHANGE_TO_MOVE;
	}
}

BOOLEAN HandleCheckForExitArrowsInput(BOOLEAN fAdjustConfirm)
{
	INT32 usMapPos;

	// If not in move mode, return!
	if (gCurrentUIMode != MOVE_MODE)
	{
		return(FALSE);
	}

	if (gusSelectedSoldier == NOBODY)
	{
		return(FALSE);
	}

	// ATE: Remove confirm for exit arrows...
	fAdjustConfirm = TRUE;
	gfUIConfirmExitArrows = TRUE;


	//Return right away, saying that we are in this mode, don't do any normal stuff!
	if (guiCurrentUICursor == NOEXIT_EAST_UICURSOR || guiCurrentUICursor == NOEXIT_WEST_UICURSOR
		|| guiCurrentUICursor == NOEXIT_NORTH_UICURSOR || guiCurrentUICursor == NOEXIT_SOUTH_UICURSOR ||
		guiCurrentUICursor == NOEXIT_GRID_UICURSOR)
	{
		// Yeah, but add a message....
		if (gfInvalidTraversal)
		{
			ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_UI_FEEDBACK, TacticalStr[CANNOT_LEAVE_SECTOR_FROM_SIDE_STR]);
			gfInvalidTraversal = FALSE;
		}
		else if (gfRobotWithoutControllerAttemptingTraversal)
		{
			ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_UI_FEEDBACK, gzLateLocalizedString[1]);
			gfRobotWithoutControllerAttemptingTraversal = FALSE;
		}
		else if (gfLoneEPCAttemptingTraversal)
		{
			ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_UI_FEEDBACK, pExitingSectorHelpText[EXIT_GUI_ESCORTED_CHARACTERS_CANT_LEAVE_SECTOR_ALONE_STR], MercPtrs[gusSelectedSoldier]->GetName());
			gfLoneEPCAttemptingTraversal = FALSE;
		}
		else if (gubLoneMercAttemptingToAbandonEPCs)
		{
			CHAR16 str[256];
			if (gubLoneMercAttemptingToAbandonEPCs == 1)
			{ //Use the singular version of the string
				if (gMercProfiles[MercPtrs[gusSelectedSoldier]->ubProfile].bSex == MALE)
				{ //male singular
					swprintf(str, pExitingSectorHelpText[EXIT_GUI_MERC_CANT_ISOLATE_EPC_HELPTEXT_MALE_SINGULAR], MercPtrs[gusSelectedSoldier]->GetName(),
						MercPtrs[gbPotentiallyAbandonedEPCSlotID]->GetName());
				}
				else
				{ //female singular
					swprintf(str, pExitingSectorHelpText[EXIT_GUI_MERC_CANT_ISOLATE_EPC_HELPTEXT_FEMALE_SINGULAR], MercPtrs[gusSelectedSoldier]->GetName(),
						MercPtrs[gbPotentiallyAbandonedEPCSlotID]->GetName());
				}
			}
			else
			{ //Use the plural version of the string
				if (gMercProfiles[MercPtrs[gusSelectedSoldier]->ubProfile].bSex == MALE)
				{ //male plural
					swprintf(str, pExitingSectorHelpText[EXIT_GUI_MERC_CANT_ISOLATE_EPC_HELPTEXT_MALE_PLURAL], MercPtrs[gusSelectedSoldier]->GetName());
				}
				else
				{ //female plural
					swprintf(str, pExitingSectorHelpText[EXIT_GUI_MERC_CANT_ISOLATE_EPC_HELPTEXT_FEMALE_PLURAL], MercPtrs[gusSelectedSoldier]->GetName());
				}
			}
			ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_UI_FEEDBACK, str);
			gubLoneMercAttemptingToAbandonEPCs = FALSE;
		}
		else if (!gGameExternalOptions.fGridExitInTurnBased && (gTacticalStatus.uiFlags & TURNBASED) && (gTacticalStatus.uiFlags & INCOMBAT))
		{
			ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_UI_FEEDBACK, TacticalStr[CANNOT_LEAVE_IN_TURN_MODE_STR]);
		}
		else
		{
			ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_UI_FEEDBACK, TacticalStr[MERC_IS_TOO_FAR_AWAY_STR], MercPtrs[gusSelectedSoldier]->GetName());
		}

		return(TRUE);
	}

	// Check if we want to exit!
	if (guiCurrentUICursor == EXIT_GRID_UICURSOR || guiCurrentUICursor == CONFIRM_EXIT_GRID_UICURSOR)
	{
		if (fAdjustConfirm)
		{
			if (!gfUIConfirmExitArrows)
			{
				gfUIConfirmExitArrows = TRUE;
			}
			else
			{
				if (!GetMouseMapPos(&usMapPos))
				{
					return(FALSE);
				}

				// Goto next sector
				//SimulateMouseMovement( gusMouseXPos - 5, gusMouseYPos );
				InitSectorExitMenu(DIRECTION_EXITGRID, usMapPos);
			}
		}
		return(TRUE);
	}

	// Check if we want to exit!
	if (guiCurrentUICursor == EXIT_EAST_UICURSOR || guiCurrentUICursor == CONFIRM_EXIT_EAST_UICURSOR)
	{
		if (fAdjustConfirm)
		{
			if (!gfUIConfirmExitArrows)
			{
				gfUIConfirmExitArrows = TRUE;
			}
			else
			{
				// Goto next sector
				//SimulateMouseMovement( gusMouseXPos - 5, gusMouseYPos );
				InitSectorExitMenu(EAST, 0);
			}
		}
		return(TRUE);
	}
	if (guiCurrentUICursor == EXIT_WEST_UICURSOR || guiCurrentUICursor == CONFIRM_EXIT_WEST_UICURSOR)
	{
		if (fAdjustConfirm)
		{
			if (!gfUIConfirmExitArrows)
			{
				gfUIConfirmExitArrows = TRUE;
			}
			else
			{
				// Goto next sector
				//SimulateMouseMovement( gusMouseXPos + 5, gusMouseYPos );
				InitSectorExitMenu(WEST, 0);
			}
		}
		return(TRUE);
	}
	if (guiCurrentUICursor == EXIT_NORTH_UICURSOR || guiCurrentUICursor == CONFIRM_EXIT_NORTH_UICURSOR)
	{
		if (fAdjustConfirm)
		{
			if (!gfUIConfirmExitArrows)
			{
				gfUIConfirmExitArrows = TRUE;
			}
			else
			{
				// Goto next sector
				//SimulateMouseMovement( gusMouseXPos, gusMouseYPos + 5 );
				InitSectorExitMenu(NORTH, 0);
			}
		}
		return(TRUE);
	}
	if (guiCurrentUICursor == EXIT_SOUTH_UICURSOR || guiCurrentUICursor == CONFIRM_EXIT_SOUTH_UICURSOR)
	{
		if (fAdjustConfirm)
		{
			if (!gfUIConfirmExitArrows)
			{
				gfUIConfirmExitArrows = TRUE;
			}
			else
			{
				// Goto next sector
				//SimulateMouseMovement( gusMouseXPos, gusMouseYPos - 5);
				InitSectorExitMenu(SOUTH, 0);
			}
		}
		return(TRUE);
	}
	return(FALSE);
}

//Simple function implementations called by keyboard input

void CreateRandomItem()
{
	INT32 usMapPos;
	if (GetMouseMapPos(&usMapPos))
	{
		CreateItem((UINT16)(Random(35) + 1), 100, &gTempObject);
		AddItemToPool(usMapPos, &gTempObject, -1, 0, 0, 0);
	}
}

void MakeSelectedSoldierTired()
{
	// Key to make guy get tired!
	SOLDIERTYPE* pSoldier;
	INT32 usMapPos;
	if (GetMouseMapPos(&usMapPos))
	{
		CreateItem(TNT, 100, &gTempObject);
		AddItemToPool(usMapPos, &gTempObject, -1, 0, 0, 0);
	}

	// CHECK IF WE'RE ON A GUY ( EITHER SELECTED, OURS, OR THEIRS
	if (gfUIFullTargetFound)
	{
		// Get Soldier
		GetSoldier(&pSoldier, gusUIFullTargetID);

		//FatigueCharacter( pSoldier );

		fInterfacePanelDirty = DIRTYLEVEL2;
	}
}

void ToggleRealTime(UINT32* puiNewEvent)
{
	if (gTacticalStatus.uiFlags & TURNBASED)
	{
		// Change to real-time
		gTacticalStatus.uiFlags &= (~TURNBASED);
		gTacticalStatus.uiFlags |= REALTIME;

		ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, L"Switching to Realtime.");
	}
	else if (gTacticalStatus.uiFlags & REALTIME)
	{
		// Change to turn-based
		gTacticalStatus.uiFlags |= TURNBASED;
		gTacticalStatus.uiFlags &= (~REALTIME);

		*puiNewEvent = M_ON_TERRAIN;

		ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, L"Switching to Turnbased.");
	}

	// Plot new path!
	gfPlotNewMovement = TRUE;
}

void ToggleViewAllMercs()
{
	// Set option to show all mercs
	if (gTacticalStatus.uiFlags & SHOW_ALL_MERCS)
	{
		gTacticalStatus.uiFlags &= (~SHOW_ALL_MERCS);
	}
	else
	{
		gTacticalStatus.uiFlags |= SHOW_ALL_MERCS;
	}

	// RE-RENDER
	SetRenderFlags(RENDER_FLAG_FULL);
}

void ToggleViewAllItems()
{
	// Set option to show all mercs
	if (gTacticalStatus.uiFlags & SHOW_ALL_ITEMS)
	{
		gTacticalStatus.uiFlags &= ~SHOW_ALL_ITEMS;
	}
	else
	{
		gTacticalStatus.uiFlags |= SHOW_ALL_ITEMS;
	}

	if (gGameSettings.fOptions[TOPTION_GLOW_ITEMS])
	{
		ToggleItemGlow(TRUE);
	}
	else
	{
		ToggleItemGlow(FALSE);
	}

	// RE-RENDER
	SetRenderFlags(RENDER_FLAG_FULL);
}

// Adding Cheat Select Explosion
void CheatSelectExplosion()
{
	if (GetMouseMapPos(&gusMapPos))
	{
		/*
		STUN_GRENADE		= 131,
		TEARGAS_GRENADE,
		MUSTARD_GRENADE,
		MINI_GRENADE,
		HAND_GRENADE,
		RDX,
		TNT,
		HMX,
		C1,
		MORTAR_SHELL,
		MINE,
		C4,
		TRIP_FLARE,
		TRIP_KLAXON,
		SHAPED_CHARGE,
		BREAK_LIGHT,
		GL_HE_GRENADE,
		GL_TEARGAS_GRENADE,
		GL_STUN_GRENADE,
		GL_SMOKE_GRENADE,
		SMOKE_GRENADE,
		TANK_SHELL,
		STRUCTURE_IGNITE,
		CREATURE_COCKTAIL,
		STRUCTURE_EXPLOSION,
		GREAT_BIG_EXPLOSION,
		BIG_TEAR_GAS,
		SMALL_CREATURE_GAS,
		LARGE_CREATURE_GAS,
		VERY_SMALL_CREATURE_GAS=270, // Renumbered because the original 160 was lost
		SMALL_SMOKE=1702,			//	sevenfm - item for small smoke effect after explosion
		MOLOTOV_EXPLOSION=979,				//	molotov - small fire explosion
		GAS_EXPLOSION=1703,				//	molotov - small fire explosion
		FRAG_EXPLOSION=1704,				//	molotov - small fire explosion
		*/

		STR16 info = L"STUN(131), TEARGAS(132), MUSTARD(133), MINI_G(134), HAND_G(135), RDX(136), TNT(137), HMX(138), C1(139), MORTAR_SHELL(140),\n";
		ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, info);
		info = L"MINE(141), C4(142), TRIP_FLARE(143), TRIP_KLAXON(144), SHPD_CHRGE(145), BRK_LGT(146), GL_HE_G(147), GL_TEARGAS_G(148),\n";
		ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, info);
		info = L"GL_STUN_G(149), GL_SMOKE_G(150), SMOKE_G(151), TANK_SHELL(152), STRUCTURE_IGNITE(153), CREATURE_COCKTAIL(154),\n";
		ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, info);
		info = L"STRUCTURE_EXPLOSION(155), GREAT_BIG_EXPLOSION(156), BIG_TEAR_GAS(157), SMALL_CREATURE_GAS(158), \n";
		ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, info);
		info = L"LARGE_CREATURE_GAS(159), VERY_SMALL_CREATURE_GAS(270), SMALL_SMOKE(1702), MOLOTOV_EXPLOSION(979), GAS_EXPLOSION(1703), \n";
		ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, info);
		info = L"FRAG_EXPLOSION(1704)";
		ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, info);

		//// JADOL -- TESTING append STR16 char
		//wchar_t* zzz = new wchar_t[512]();
		//wcsncat(zzz, info, wcslen(info));
		//wcsncat(zzz, L" tambahan", sizeof(L" tambahan"));
		//ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, zzz);
		//delete[] zzz;

		//std::wstring* test = new std::wstring(L"ini adalah testing aja");
		//test->append(L" ini tambahan aja yaak!");
		//test->append(L" eh ini ditambahin lagi |d|o|n|g|");
		//ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, (STR16) test->c_str());
		//delete test;


		if (GetMouseMapPos(&gusMapPos))
			DoMessageBox(MSG_BOX_BASIC_SMALL_BUTTONS, L"Pick Explosion Type Number from [131 to 159, 270, 979, 1702, 1703, or 1704]", GAME_SCREEN, MSG_BOX_FLAG_INPUTBOX, CheatSelectExplosionCallBack, NULL);

	}
}

void CheatSelectCreateMonster()
{
	if (GetMouseMapPos(&gusMapPos))
	{
		/*
		enum SoldierBodyTypes
		{
			ADULTFEMALEMONSTER,		4
			AM_MONSTER,				5
			YAF_MONSTER,			6
			YAM_MONSTER,			7
			LARVAE_MONSTER,			8
			INFANT_MONSTER,			9
			QUEENMONSTER,			10
		} ;
		*/

		wcscpy(gzUserDefinedButton[0], L"Adult Female");
		wcscpy(gzUserDefinedButton[1], L"Adult Male");
		wcscpy(gzUserDefinedButton[2], L"Kid Female");
		wcscpy(gzUserDefinedButton[3], L"Kid Male");
		wcscpy(gzUserDefinedButton[4], L"Larvae Monster");
		wcscpy(gzUserDefinedButton[5], L"Infant Monster");
		wcscpy(gzUserDefinedButton[6], L"Queen (Not Moving)");
		wcscpy(gzUserDefinedButton[7], L"-Unused-");

		DoMessageBox(MSG_BOX_BASIC_MEDIUM_BUTTONS, L"Select Type of Monster", GAME_SCREEN,
			MSG_BOX_FLAG_GENERIC_EIGHT_BUTTONS, SelectCreateMonsterCallback, NULL);
	}
}

void SelectCreateMonsterCallback(UINT8 ubExitValue)
{
	if (ubExitValue != NULL)
	{
		if (ubExitValue > 0 && ubExitValue < 8) {
			/*
			enum SoldierBodyTypes
			{
				ADULTFEMALEMONSTER,		4
				AM_MONSTER,				5
				YAF_MONSTER,			6
				YAM_MONSTER,			7
				LARVAE_MONSTER,			8
				INFANT_MONSTER,			9
				QUEENMONSTER,			10
			} ;
			*/
			gCreatedMonsterType = ubExitValue + 3;
			CreatePlayerControlledMonster();
		}
	}
}


void CreateExplosion(UINT16 usItemExplosion, INT32 gridNo)
{
	INT32 sBombGridNo = gridNo;
	if (gridNo == NULL) {
		if (GetMouseMapPos(&sBombGridNo))
		{
			INT16		sBombX, sBombY;
			ConvertGridNoToCenterCellXY(sBombGridNo, &sBombX, &sBombY);
			InternalIgniteExplosion(NOBODY, sBombX, sBombY, 0, sBombGridNo, usItemExplosion, FALSE, (UINT8)IsRoofPresentAtGridNo(sBombGridNo));
			gusItemExplosion = usItemExplosion;
		}
	}
	else
	{
		INT16		sBombX, sBombY;
		ConvertGridNoToCenterCellXY(sBombGridNo, &sBombX, &sBombY);
		InternalIgniteExplosion(NOBODY, sBombX, sBombY, 0, sBombGridNo, usItemExplosion, FALSE, (UINT8)IsRoofPresentAtGridNo(sBombGridNo));
		gusItemExplosion = usItemExplosion;
	}
}

void TestExplosion()
{
	INT32 usMapPos;
	if (GetMouseMapPos(&usMapPos))
	{
		EXPLOSION_PARAMS	ExpParams;
		ExpParams.uiFlags = 0;
		ExpParams.ubOwner = NOBODY;
		ExpParams.ubTypeID = STUN_BLAST;
		ExpParams.sGridNo = usMapPos;

		GenerateExplosion(&ExpParams);

		PlayJA2Sample(EXPLOSION_1, RATE_11025, MIDVOLUME, 1, MIDDLEPAN);
	}
}

void CycleSelectedMercsItem()
{
	DebugMsg(TOPIC_JA2, DBG_LEVEL_3, String("CycleSelectedMercsItem"));
	INT16 usOldItem;
	SOLDIERTYPE* pSoldier;
	// Cycle selected guy's item...
	if (gusSelectedSoldier != NOBODY)
	{
		// Get soldier...
		pSoldier = MercPtrs[gusSelectedSoldier];

		UINT16 usOldHandItem = pSoldier->inv[HANDPOS].usItem;

		// Cycle item....
		usOldItem = CycleItems(pSoldier->inv[HANDPOS].usItem);

		CreateItem((UINT16)usOldItem, 100, &(pSoldier->inv[HANDPOS]));

		pSoldier->ReLoadSoldierAnimationDueToHandItemChange(usOldHandItem, pSoldier->inv[HANDPOS].usItem);

		DirtyMercPanelInterface(pSoldier, DIRTYLEVEL2);
	}
}

void ToggleWireFrame()
{
	if (gGameSettings.fOptions[TOPTION_TOGGLE_WIREFRAME])
	{
		gGameSettings.fOptions[TOPTION_TOGGLE_WIREFRAME] = FALSE;

		ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, pMessageStrings[MSG_WIREFRAMES_REMOVED]);
	}
	else
	{
		gGameSettings.fOptions[TOPTION_TOGGLE_WIREFRAME] = TRUE;

		ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, pMessageStrings[MSG_WIREFRAMES_ADDED]);
	}

	SetRenderFlags(RENDER_FLAG_FULL);
}

void RefreshSoldier()
{
	SOLDIERTYPE* pSoldier;
	INT32 usMapPos;
	// CHECK IF WE'RE ON A GUY ( EITHER SELECTED, OURS, OR THEIRS
	if (gfUIFullTargetFound)
	{
		// Get Soldier
		GetSoldier(&pSoldier, gusUIFullTargetID);

		pSoldier->ReviveSoldier();

	}

	if (GetMouseMapPos(&usMapPos))
		sprintf(gDebugStr, "%d %d %d %d %d %d %d %d",
			gubWorldMovementCosts[usMapPos][0][gsInterfaceLevel],
			gubWorldMovementCosts[usMapPos][1][gsInterfaceLevel],
			gubWorldMovementCosts[usMapPos][2][gsInterfaceLevel],
			gubWorldMovementCosts[usMapPos][3][gsInterfaceLevel],
			gubWorldMovementCosts[usMapPos][4][gsInterfaceLevel],
			gubWorldMovementCosts[usMapPos][5][gsInterfaceLevel],
			gubWorldMovementCosts[usMapPos][6][gsInterfaceLevel],
			gubWorldMovementCosts[usMapPos][7][gsInterfaceLevel]);
}

void ChangeSoldiersBodyType(UINT8 ubBodyType, BOOLEAN fCreateNewPalette)
{
	SOLDIERTYPE* pSoldier;
	if (gusSelectedSoldier != NOBODY)
	{
		if (GetSoldier(&pSoldier, gusSelectedSoldier))
		{
			pSoldier->ubBodyType = ubBodyType;
			pSoldier->EVENT_InitNewSoldierAnim(STANDING, 0, TRUE);
			//SetSoldierAnimationSurface( pSoldier, pSoldier->usAnimState );
			if (fCreateNewPalette)
			{
				pSoldier->CreateSoldierPalettes();

				switch (ubBodyType)
				{
				case ADULTFEMALEMONSTER:
				case AM_MONSTER:
				case YAF_MONSTER:
				case YAM_MONSTER:
				case LARVAE_MONSTER:
				case INFANT_MONSTER:
				case QUEENMONSTER:

					pSoldier->flags.uiStatusFlags |= SOLDIER_MONSTER;
					AssignCreatureInventory(pSoldier);
					CreateItem(CREATURE_YOUNG_MALE_SPIT, 100, &(pSoldier->inv[HANDPOS]));

					break;

				case TANK_NW:
				case TANK_NE:
				case COMBAT_JEEP:

					pSoldier->flags.uiStatusFlags |= SOLDIER_VEHICLE;
					//pSoldier->inv[ HANDPOS ].usItem = TANK_CANNON;

					pSoldier->inv[HANDPOS].usItem = MINIMI;
					pSoldier->bVehicleID = (INT8)AddVehicleToList(pSoldier->sSectorX, pSoldier->sSectorY, pSoldier->bSectorZ, HUMMER);

					break;
				}

			}
		}
	}
}

void TeleportSelectedSoldier()
{
	SOLDIERTYPE* pSoldier;
	INT32 usMapPos;
	// CHECK IF WE'RE ON A GUY ( EITHER SELECTED, OURS, OR THEIRS
	if (GetSoldier(&pSoldier, gusSelectedSoldier))
	{
		if (GetMouseMapPos(&usMapPos))
		{
			// Check level first....
			if (gsInterfaceLevel == 0)
			{
				pSoldier->SetSoldierHeight(0);
				TeleportSoldier(pSoldier, usMapPos, FALSE);
				pSoldier->EVENT_StopMerc(pSoldier->sGridNo, pSoldier->ubDirection);
			}
			else
			{
				// Is there a roof?
				if (FindStructure(usMapPos, STRUCTURE_ROOF) != NULL)
				{
					pSoldier->SetSoldierHeight(50.0);

					TeleportSoldier(pSoldier, usMapPos, TRUE);
					pSoldier->EVENT_StopMerc(pSoldier->sGridNo, pSoldier->ubDirection);
				}
			}
		}
	}
}

void ToggleTurnMode()// ary-05/05/2009 : add forced turn mode
{
	if (!gGameSettings.fOptions[TOPTION_TOGGLE_TURN_MODE])
	{
		ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, pMessageStrings[MSG_FORCED_TURN_MODE]);
		gGameSettings.fOptions[TOPTION_TOGGLE_TURN_MODE] = TRUE;
		EnterCombatMode(OUR_TEAM); // ary-05/05/2009 : randomize ? i'm leaving this for now due to "player makes the call, player gets dibs"
	}
	else
	{
		ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, pMessageStrings[MSG_NORMAL_TURN_MODE]);
		gGameSettings.fOptions[TOPTION_TOGGLE_TURN_MODE] = FALSE;
	}
}

void ToggleTreeTops()
{
	if (gGameSettings.fOptions[TOPTION_TOGGLE_TREE_TOPS])
	{
		ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, TacticalStr[REMOVING_TREETOPS_STR]);
		gGameSettings.fOptions[TOPTION_TOGGLE_TREE_TOPS] = FALSE;
		WorldHideTrees();
		gTacticalStatus.uiFlags |= NOHIDE_REDUNDENCY;
	}
	else
	{
		ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, TacticalStr[SHOWING_TREETOPS_STR]);
		WorldShowTrees();
		gGameSettings.fOptions[TOPTION_TOGGLE_TREE_TOPS] = TRUE;
		gTacticalStatus.uiFlags &= (~NOHIDE_REDUNDENCY);
	}

	// FOR THE NEXT RENDER LOOP, RE-EVALUATE REDUNDENT TILES
	InvalidateWorldRedundency();
}

void ToggleZBuffer()
{
	// Set option to show all mercs
	if (gTacticalStatus.uiFlags & SHOW_Z_BUFFER)
	{
		gTacticalStatus.uiFlags &= (~SHOW_Z_BUFFER);
		SetRenderFlags(SHOW_Z_BUFFER);
	}
	else
	{
		gTacticalStatus.uiFlags |= SHOW_Z_BUFFER;
	}
}

void TogglePlanningMode()
{
	SOLDIERTYPE* pSoldier;
	INT32 usMapPos;
	// DO ONLY IN TURNED BASED!
	if (gTacticalStatus.uiFlags & TURNBASED && (gTacticalStatus.uiFlags & INCOMBAT))
	{
		// CANCEL FROM PLANNING MODE!
		if (InUIPlanMode())
		{
			EndUIPlan();
		}
		else if (GetMouseMapPos(&usMapPos))
		{
			switch (gCurrentUIMode)
			{
			case MOVE_MODE:
				if (gusSelectedSoldier != NOBODY)
				{
					GetSoldier(&pSoldier, gusSelectedSoldier);
					BeginUIPlan(pSoldier);
					AddUIPlan(usMapPos, UIPLAN_ACTION_MOVETO);
				}
				break;
			case ACTION_MODE:
				if (gusSelectedSoldier != NOBODY)
				{
					GetSoldier(&pSoldier, gusSelectedSoldier);
					BeginUIPlan(pSoldier);
					AddUIPlan(usMapPos, UIPLAN_ACTION_FIRE);
				}
				break;
			}
		}
	}
}

void SetBurstMode()
{
	if (gusSelectedSoldier != NOBODY)
	{
		ChangeWeaponMode(MercPtrs[gusSelectedSoldier]);
	}
}

void SetScopeMode(INT32 usMapPos)
{
	if (gusSelectedSoldier != NOBODY)
	{
		if (GetMouseMapPos(&usMapPos))
			ChangeScopeMode(MercPtrs[gusSelectedSoldier], usMapPos);
		else
			ChangeScopeMode(MercPtrs[gusSelectedSoldier], NOWHERE);

		// reevaluate sight
		ManLooksForOtherTeams(MercPtrs[gusSelectedSoldier]);
	}
}

void ObliterateSector()
{
	INT32 cnt;
	SOLDIERTYPE* pTSoldier;

	// Kill everybody!
	cnt = gTacticalStatus.Team[gbPlayerNum].bLastID + 1;

#ifdef JA2BETAVERSION
	ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_TESTVERSION, L"Obliterating Sector!");
#endif

	for (pTSoldier = MercPtrs[cnt]; cnt < MAX_NUM_SOLDIERS; pTSoldier++, cnt++)
	{
		if (pTSoldier->bActive && !pTSoldier->aiData.bNeutral && (pTSoldier->bSide != gbPlayerNum))
		{
			//	ANITILE_PARAMS	AniParams;
			//		memset( &AniParams, 0, sizeof( ANITILE_PARAMS ) );
			//		AniParams.sGridNo							= pTSoldier->sGridNo;
			//		AniParams.ubLevelID						= ANI_STRUCT_LEVEL;
			//	AniParams.usTileType				= FIRSTEXPLOSION;
			//	AniParams.usTileIndex					= FIRSTEXPLOSION1;
			//	AniParams.sDelay							= 80;
			//	AniParams.sStartFrame					= 0;
			//	AniParams.uiFlags							= ANITILE_FORWARD;

			//	CreateAnimationTile( &AniParams );
			//PlayJA2Sample( EXPLOSION_1, RATE_11025, MIDVOLUME, 1, MIDDLEPAN );

			pTSoldier->EVENT_SoldierGotHit(1, 400, 0, pTSoldier->ubDirection, 320, NOBODY, FIRE_WEAPON_NO_SPECIAL, pTSoldier->bAimShotLocation, 0, NOWHERE);
		}
	}
}

void RandomizeMercProfile()
{
	SOLDIERTYPE* pSoldier;
	// Get selected soldier
	if (GetSoldier(&pSoldier, gusSelectedSoldier))
	{
		// Change guy!
		ForceSoldierProfileID(pSoldier, (UINT8)Random(30));

		// Dirty interface
		DirtyMercPanelInterface(pSoldier, DIRTYLEVEL2);
	}
}

void ToggleCliffDebug()
{
	// Set option to show all mercs
	if (gTacticalStatus.uiFlags & DEBUGCLIFFS)
	{
		ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_TESTVERSION, L"Cliff debug OFF.");

		gTacticalStatus.uiFlags &= (~DEBUGCLIFFS);
		SetRenderFlags(RENDER_FLAG_FULL);
	}
	else
	{
		ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_TESTVERSION, L"Cliff debug ON.");

		gTacticalStatus.uiFlags |= DEBUGCLIFFS;
	}
}

void CreateCow()
{
	SOLDIERCREATE_STRUCT		MercCreateStruct;
	INT32 usMapPos;

	// Get Grid Corrdinates of mouse
	if (GetMouseMapPos(&usMapPos))
	{
		INT8							iNewIndex;

		MercCreateStruct.ubProfile = NO_PROFILE;
		MercCreateStruct.sSectorX = gWorldSectorX;
		MercCreateStruct.sSectorY = gWorldSectorY;
		MercCreateStruct.bSectorZ = gbWorldSectorZ;
		MercCreateStruct.ubBodyType = COW;
		//MercCreateStruct.bTeam				= SOLDIER_CREATE_AUTO_TEAM;
		MercCreateStruct.bTeam = CIV_TEAM;
		MercCreateStruct.sInsertionGridNo = usMapPos;
		RandomizeNewSoldierStats(&MercCreateStruct);

		if (TacticalCreateSoldier(&MercCreateStruct, (UINT8*)&iNewIndex))
		{
			AddSoldierToSector(iNewIndex);

			// So we can see them!
			AllTeamsLookForAll(NO_INTERRUPTS);
		}
	}
}

void CreateBloodCat()
{
	SOLDIERCREATE_STRUCT		MercCreateStruct;
	INT32 usMapPos;

	// Get Grid Corrdinates of mouse
	if (GetMouseMapPos(&usMapPos))
	{
		INT8							iNewIndex;

		MercCreateStruct.ubProfile = NO_PROFILE;
		MercCreateStruct.sSectorX = gWorldSectorX;
		MercCreateStruct.sSectorY = gWorldSectorY;
		MercCreateStruct.bSectorZ = gbWorldSectorZ;
		MercCreateStruct.ubBodyType = BLOODCAT;
		//MercCreateStruct.bTeam				= SOLDIER_CREATE_AUTO_TEAM;
		MercCreateStruct.bTeam = CREATURE_TEAM;
		MercCreateStruct.sInsertionGridNo = usMapPos;
		RandomizeNewSoldierStats(&MercCreateStruct);

		if (TacticalCreateSoldier(&MercCreateStruct, (UINT8*)&iNewIndex))
		{
			AddSoldierToSector(iNewIndex);

			// So we can see them!
			AllTeamsLookForAll(NO_INTERRUPTS);
		}
	}
}

void CreatePlayerControlledCow()
{
	SOLDIERCREATE_STRUCT		MercCreateStruct;
	INT32 usMapPos;

	// Get Grid Corrdinates of mouse
	if (GetMouseMapPos(&usMapPos))
	{
		INT8							iNewIndex;

		MercCreateStruct.ubProfile = 12;
		MercCreateStruct.sSectorX = gWorldSectorX;
		MercCreateStruct.sSectorY = gWorldSectorY;
		MercCreateStruct.bSectorZ = gbWorldSectorZ;
		MercCreateStruct.ubBodyType = COW;
		MercCreateStruct.sInsertionGridNo = usMapPos;
		MercCreateStruct.bTeam = SOLDIER_CREATE_AUTO_TEAM;
		MercCreateStruct.fPlayerMerc = TRUE;

		RandomizeNewSoldierStats(&MercCreateStruct);

		if (TacticalCreateSoldier(&MercCreateStruct, (UINT8*)&iNewIndex))
		{
			AddSoldierToSector(iNewIndex);

			// So we can see them!
			AllTeamsLookForAll(NO_INTERRUPTS);
		}
	}
}

void ToggleRealTimeConfirm()
{

}

/*
void GrenadeTest1()
{
	// Get mousexy
	INT16 sX, sY;
	if ( GetMouseXY( &sX, &sY ) )
	{
		OBJECTTYPE		Object;
		Object.usItem = MUSTARD_GRENADE;
		Object[0]->data.objectStatus = 100;
		Object.ubNumberOfObjects = 1;
		CreatePhysicalObject( &Object, 60,	(FLOAT)(sX * CELL_X_SIZE), (FLOAT)(sY * CELL_Y_SIZE ), 256, -20, 20, 158, NOBODY, THROW_ARM_ITEM, 0, FALSE );
	}
}

void GrenadeTest2()
{
	// Get mousexy
	INT16 sX, sY;
	if ( GetMouseXY( &sX, &sY ) )
	{
		OBJECTTYPE		Object;
		Object.usItem = HAND_GRENADE;
		Object[0]->data.objectStatus = 100;
		Object.ubNumberOfObjects = 1;
		CreatePhysicalObject( &Object, 60,	(FLOAT)(sX * CELL_X_SIZE), (FLOAT)(sY * CELL_Y_SIZE ), 256, 0, -30, 158, NOBODY, THROW_ARM_ITEM, 0, FALSE );
	}
}

void GrenadeTest3()
{
	// Get mousexy
	INT16 sX, sY;
	if ( GetMouseXY( &sX, &sY ) )
	{
		OBJECTTYPE		Object;
		Object.usItem = HAND_GRENADE;
		Object[0]->data.objectStatus = 100;
		Object.ubNumberOfObjects = 1;
		CreatePhysicalObject( &Object, 60,	(FLOAT)(sX * CELL_X_SIZE), (FLOAT)(sY * CELL_Y_SIZE ), 256, -10, 10, 158, NOBODY, THROW_ARM_ITEM, 0, FALSE );
	}
}
*/
void CreatePlayerControlledMonster()
{
	SOLDIERCREATE_STRUCT		MercCreateStruct;
	INT8							iNewIndex;

	MercCreateStruct.ubProfile = NO_PROFILE;
	MercCreateStruct.sSectorX = gWorldSectorX;
	MercCreateStruct.sSectorY = gWorldSectorY;
	MercCreateStruct.bSectorZ = gbWorldSectorZ;

	////Note:	only gets called if Alt and/or Ctrl isn't pressed!
	//if (_KeyDown(INSERT))
	//	MercCreateStruct.ubBodyType = QUEENMONSTER;
	////MercCreateStruct.ubBodyType		= LARVAE_MONSTER;
	//else
	//	MercCreateStruct.ubBodyType = ADULTFEMALEMONSTER;

	MercCreateStruct.ubBodyType = gCreatedMonsterType;
	MercCreateStruct.bTeam = SOLDIER_CREATE_AUTO_TEAM;
	MercCreateStruct.sInsertionGridNo = gusMapPos;
	RandomizeNewSoldierStats(&MercCreateStruct);

	if (TacticalCreateSoldier(&MercCreateStruct, (UINT8*)&iNewIndex))
	{
		AddSoldierToSector(iNewIndex);
	}
}


INT8 CheckForAndHandleHandleVehicleInteractiveClick(SOLDIERTYPE* pSoldier, UINT16 usMapPos, BOOLEAN fMovementMode, UINT8 ubSeatIndex)
{
	// Look for an item pool
	INT32 sActionGridNo;
	UINT8							ubDirection;
	SOLDIERTYPE* pTSoldier;
	INT16							sAPCost = 0;

	if (gfUIFullTargetFound)
	{
		pTSoldier = MercPtrs[gusUIFullTargetID];

		// anv: added condition - make sure we won't put vehicle in another vehicle
		if (OK_ENTERABLE_VEHICLE(pTSoldier) && pTSoldier->bVisible != -1 && OKUseVehicle(pTSoldier->ubProfile) && !(pSoldier->flags.uiStatusFlags & (SOLDIER_DRIVER | SOLDIER_PASSENGER | SOLDIER_VEHICLE)))
			//if ( OK_ENTERABLE_VEHICLE( pTSoldier ) && pTSoldier->bVisible != -1 && OKUseVehicle( pTSoldier->ubProfile ) )
		{
			if ((GetNumberInVehicle(pTSoldier->bVehicleID) == 0) || !fMovementMode)
			{
				// Find a gridno closest to sweetspot...
				sActionGridNo = FindGridNoFromSweetSpotWithStructDataFromSoldier(pSoldier, pSoldier->usUIMovementMode, 5, &ubDirection, 0, pTSoldier, TRUE);

				if (!TileIsOutOfBounds(sActionGridNo))
				{
					// Calculate AP costs...
					//sAPCost = GetAPsToBeginFirstAid( pSoldier );
					sAPCost += PlotPath(pSoldier, sActionGridNo, NO_COPYROUTE, FALSE, TEMPORARY, (UINT16)pSoldier->usUIMovementMode, NOT_STEALTH, FORWARD, pSoldier->bActionPoints);

					if (EnoughPoints(pSoldier, sAPCost, 0, TRUE))
					{
						pSoldier->DoMercBattleSound(BATTLE_SOUND_OK);

						// CHECK IF WE ARE AT THIS GRIDNO NOW
						if (pSoldier->sGridNo != sActionGridNo)
						{
							// SEND PENDING ACTION
							pSoldier->aiData.ubPendingAction = MERC_ENTER_VEHICLE;
							pSoldier->aiData.sPendingActionData2 = pTSoldier->sGridNo;
							pSoldier->aiData.bPendingActionData3 = ubDirection;
							pSoldier->aiData.uiPendingActionData4 = ubSeatIndex;
							pSoldier->aiData.ubPendingActionAnimCount = 0;

							// WALK UP TO DEST FIRST
							pSoldier->EVENT_InternalGetNewSoldierPath(sActionGridNo, pSoldier->usUIMovementMode, 3, pSoldier->flags.fNoAPToFinishMove);
						}
						else
						{
							pSoldier->EVENT_SoldierEnterVehicle(pTSoldier->sGridNo, ubDirection, ubSeatIndex);
						}

						// OK, set UI
						SetUIBusy(pSoldier->ubID);
						//guiPendingOverrideEvent = A_CHANGE_TO_MOVE;

						return(-1);
					}
				}
			}
		}
	}

	return(0);
}

void HandleRadioCursorClick(INT32 usMapPos, UINT32* puiNewEvent)
{
	SOLDIERTYPE* pSoldier = NULL;
	GetSoldier(&pSoldier, gusSelectedSoldier);

	if (pSoldier &&
		pTMilitiaSoldier &&
		pTMilitiaSoldier->bActive &&
		pTMilitiaSoldier->bInSector &&
		pTMilitiaSoldier->stats.bLife >= OKLIFE)
	{
		INT32 sMoveSpot = usMapPos;
		BOOLEAN fClimbingNecessary;
		INT32 sClimbSpot;
		INT32 iPathCost = EstimatePathCostToLocation(pTMilitiaSoldier, sMoveSpot, (INT8)gsInterfaceLevel, FALSE, &fClimbingNecessary, &sClimbSpot);

		// See if we can get there
		if (iPathCost > 0)
		{
			// sevenfm: change from stationary/patrol etc
			pTMilitiaSoldier->aiData.bOrders = STATIONARY;
			pTMilitiaSoldier->aiData.bAttitude = DEFENSIVE;

			// sevenfm: set this spot as original point
			pTMilitiaSoldier->aiData.sPatrolGrid[0] = sMoveSpot;

			CancelAIAction(pTMilitiaSoldier, TRUE);
			if (fClimbingNecessary)
			{
				pTMilitiaSoldier->aiData.bNextAction = AI_ACTION_MOVE_TO_CLIMB;
				pTMilitiaSoldier->aiData.usNextActionData = sClimbSpot;
				pTMilitiaSoldier->sAbsoluteFinalDestination = sMoveSpot;

				BeginMultiPurposeLocator(sClimbSpot, pTMilitiaSoldier->pathing.bLevel, FALSE);
			}
			else
			{
				pTMilitiaSoldier->aiData.bNextAction = AI_ACTION_SEEK_OPPONENT;
				pTMilitiaSoldier->aiData.usNextActionData = sMoveSpot;

				BeginMultiPurposeLocator(sMoveSpot, pTMilitiaSoldier->pathing.bLevel, FALSE);
			}
			RESETTIMECOUNTER(pTMilitiaSoldier->timeCounters.AICounter, 100);

			//pTMilitiaSoldier->usSoldierFlagMask |= SOLDIER_MILITIA_ORDER;
		}
		else
		{
			pTMilitiaSoldier->DoMercBattleSound(BATTLE_SOUND_CURSE);
		}
	}

	*puiNewEvent = A_CHANGE_TO_MOVE;

	return;
}

void HandleHandCursorClick(INT32 usMapPos, UINT32* puiNewEvent)
{
	SOLDIERTYPE* pSoldier;
	LEVELNODE* pIntTile;
	INT32 sIntTileGridNo;
	INT32 sActionGridNo;
	UINT8							ubDirection;
	INT16							sAPCost;
	INT32 sAdjustedGridNo;
	STRUCTURE* pStructure = NULL;
	ITEM_POOL* pItemPool;
	BOOLEAN						fIgnoreItems = FALSE;

	if (GetSoldier(&pSoldier, gusSelectedSoldier))
	{
		// If we are out of breath, no cursor...
		if (pSoldier->bBreath < OKBREATH && pSoldier->bCollapsed)
		{
			return;
		}

		if (CheckForAndHandleHandleVehicleInteractiveClick(pSoldier, usMapPos, FALSE, 0) == -1)
		{
			return;
		}

		if (pSoldier->flags.uiStatusFlags & (SOLDIER_VEHICLE | SOLDIER_DRIVER | SOLDIER_PASSENGER))
		{
			return;
		}

		// Check if we are on a merc... if so.. steal!
		if (gfUIFullTargetFound)
		{
			// Flugente: allow stealing if the other guy is an enemy, OR if we are on the same team
			//if ( (( guiUIFullTargetFlags & ENEMY_MERC ) && !( guiUIFullTargetFlags & UNCONSCIOUS_MERC )) || (AllowedToStealFromTeamMate(pSoldier->ubID, (UINT8)gusUIFullTargetID) && guiUIFullTargetFlags & OWNED_MERC) )
			{
				sActionGridNo = FindAdjacentGridEx(pSoldier, MercPtrs[gusUIFullTargetID]->sGridNo, &ubDirection, &sAdjustedGridNo, TRUE, FALSE);
				if (sActionGridNo == -1)
				{
					sActionGridNo = sAdjustedGridNo;
				}

				// Steal!
				sAPCost = GetAPsToStealItem(pSoldier, MercPtrs[gusUIFullTargetID], sActionGridNo); // SANDRO - added target variable

				if (EnoughPoints(pSoldier, sAPCost, 0, TRUE))
				{
					MercStealFromMerc(pSoldier, MercPtrs[gusUIFullTargetID]);

					*puiNewEvent = A_CHANGE_TO_MOVE;

					return;
				}
				else
				{
					return;
				}
			}
		}

		// Default action gridno to mouse....
		sActionGridNo = usMapPos;

		// If we are over an interactive struct, adjust gridno to this....
		pIntTile = ConditionalGetCurInteractiveTileGridNoAndStructure(&sIntTileGridNo, &pStructure, FALSE);
		if (pIntTile != NULL)
		{
			sActionGridNo = sIntTileGridNo;

			//if ( pStructure->fFlags & ( STRUCTURE_SWITCH | STRUCTURE_ANYDOOR ) )
			if (pStructure->fFlags & (STRUCTURE_SWITCH))
			{
				fIgnoreItems = TRUE;
			}

			if (pStructure->fFlags & (STRUCTURE_ANYDOOR) && sActionGridNo != usMapPos)
			{
				fIgnoreItems = TRUE;
			}
		}

		// Check if we are over an item pool
		// ATE: Ignore items will be set if over a switch interactive tile...
		if (GetItemPool(sActionGridNo, &pItemPool, pSoldier->pathing.bLevel) && ITEMPOOL_VISIBLE(pItemPool) && !fIgnoreItems)
		{
			if (AM_AN_EPC(pSoldier))
			{
				// Display message
				// ScreenMsg( FONT_MCOLOR_LTYELLOW, MSG_UI_FEEDBACK, TacticalStr[ NO_PATH ] );
				ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_UI_FEEDBACK, TacticalStr[EPC_CANNOT_DO_THAT]);
			}
			else if (UIOkForItemPickup(pSoldier, sActionGridNo))
			{
				INT8 bZLevel = GetLargestZLevelOfItemPool(pItemPool);

				SoldierPickupItem(pSoldier, pItemPool->iItemIndex, sActionGridNo, bZLevel);

				*puiNewEvent = A_CHANGE_TO_MOVE;

			}
		}
		else
		{
			if (pIntTile != NULL && !(pStructure->fFlags & STRUCTURE_HASITEMONTOP))
			{
				sActionGridNo = FindAdjacentGridEx(pSoldier, sIntTileGridNo, &ubDirection, NULL, FALSE, TRUE);
				if (sActionGridNo == -1)
				{
					sActionGridNo = sIntTileGridNo;
				}

				// If this is not the same tile as ours, check if we can get to dest!
				if (sActionGridNo != pSoldier->sGridNo && gsCurrentActionPoints == 0)
				{
					ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_UI_FEEDBACK, TacticalStr[NO_PATH]);
				}
				else
				{
					if (SelectedMercCanAffordMove())
					{
						*puiNewEvent = C_MOVE_MERC;
					}
				}
			}
			else
			{
				// ATE: Here, the poor player wants to search something that does not exist...
				// Why should we not let them make fools of themselves....?
				if (AM_AN_EPC(pSoldier))
				{
					// Display message
					// ScreenMsg( FONT_MCOLOR_LTYELLOW, MSG_UI_FEEDBACK, TacticalStr[ NO_PATH ] );
					ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_UI_FEEDBACK, TacticalStr[EPC_CANNOT_DO_THAT]);
				}
				else
				{
					// Check morale, if < threashold, refuse...
					if (pSoldier->aiData.bMorale < 30)
					{
						TacticalCharacterDialogue(pSoldier, QUOTE_REFUSING_ORDER);
					}
					else
					{
						if (gsCurrentActionPoints == 0)
						{
							ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_UI_FEEDBACK, TacticalStr[NO_PATH]);
						}
						else
						{
							SoldierPickupItem(pSoldier, NOTHING, sActionGridNo, 0);
							*puiNewEvent = A_CHANGE_TO_MOVE;
						}
					}
				}
			}
		}
	}
}

void HandleHandCursorRightClick(INT32 usMapPos, UINT32* puiNewEvent)
{
	SOLDIERTYPE* pSoldier;
	SOLDIERTYPE* pTSoldier;

	if (GetSoldier(&pSoldier, gusSelectedSoldier))
	{
		// If we are out of breath, no cursor...
		if (pSoldier->bBreath < OKBREATH && pSoldier->bCollapsed)
		{
			return;
		}

		if (gfUIFullTargetFound)
		{
			pTSoldier = MercPtrs[gusUIFullTargetID];
			if (OK_ENTERABLE_VEHICLE(pTSoldier) && pTSoldier->bVisible != -1 && OKUseVehicle(pTSoldier->ubProfile))
			{
				// anv: if we are passengers, only show menu when clicking on vehicle we're in
				if (pSoldier->flags.uiStatusFlags & (SOLDIER_DRIVER | SOLDIER_PASSENGER))
				{
					if (pSoldier->iVehicleId == pTSoldier->bVehicleID)
					{
						VehicleMenu(usMapPos, pSoldier, pTSoldier);
					}
				}
				else
				{
					VehicleMenu(usMapPos, pSoldier, pTSoldier);
				}
				return;
			}
		}
	}
}

void ExchangeMessageBoxCallBack(UINT8 bExitValue)
{
	if (bExitValue == MSG_BOX_RETURN_YES)
	{
		SwapMercPositions(gpExchangeSoldier1, gpExchangeSoldier2);
	}
}


INT8 HandleMoveModeInteractiveClick(INT32 usMapPos, UINT32* puiNewEvent)
{
	// Look for an item pool
	ITEM_POOL* pItemPool;
	BOOLEAN						fContinue = TRUE;
	SOLDIERTYPE* pSoldier;
	LEVELNODE* pIntTile;
	INT32 sIntTileGridNo;
	INT32 sActionGridNo;
	UINT8							ubDirection;
	INT8							bReturnCode = 0;
	INT8							bZLevel;
	STRUCTURE* pStructure = NULL;

	if (GetSoldier(&pSoldier, gusSelectedSoldier))
	{
		// If we are out of breath, no cursor...
		// if ( pSoldier->bBreath < OKBREATH )
		//{
		//	return( -1 );
		//}

		// ATE: If we are a vehicle, no moving!
		if (!gGameExternalOptions.fAllowDrivingVehiclesInTactical && pSoldier->flags.uiStatusFlags & SOLDIER_VEHICLE)
		{
			ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_UI_FEEDBACK, TacticalStr[VEHICLE_CANT_MOVE_IN_TACTICAL]);
			return(-3);
		}

		//if ( pSoldier->flags.uiStatusFlags & ( SOLDIER_DRIVER | SOLDIER_PASSENGER ) )
		if (pSoldier->flags.uiStatusFlags & (SOLDIER_PASSENGER))
		{
			// anv: there's some weird bug with moving invisible passengers after loading game, that should solve it
			//ScreenMsg( FONT_MCOLOR_LTYELLOW, MSG_UI_FEEDBACK, TacticalStr[ VEHICLE_CANT_MOVE_IN_TACTICAL ] );
			// actually, you know what, let's switch to vehicle using the occasion
			HandleLocateSelectMerc(GetDriver(MercPtrs[pSoldier->ubID]->iVehicleId)->ubID, 0);
			return(-3);
		}

		if (pSoldier->flags.uiStatusFlags & (SOLDIER_DRIVER))
		{
			pSoldier = GetSoldierStructureForVehicle(MercPtrs[pSoldier->ubID]->iVehicleId);
		}

		// OK, check for height differences.....
		if (gpWorldLevelData[usMapPos].sHeight != gpWorldLevelData[pSoldier->sGridNo].sHeight)
		{
			ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_UI_FEEDBACK, TacticalStr[CANT_GET_THERE]);
			return(-1);
		}

		// See if we are over a vehicle, and walk up to it and enter....
		if (CheckForAndHandleHandleVehicleInteractiveClick(pSoldier, usMapPos, TRUE, 0) == -1)
		{
			return(-1);
		}

		// Check if we are over a civillian....
		if (gfUIFullTargetFound)
		{
			if (ValidQuickExchangePosition())
			{
				// Check if we can...
				if (CanExchangePlaces(pSoldier, MercPtrs[gusUIFullTargetID], TRUE))
				{
					gpExchangeSoldier1 = pSoldier;
					gpExchangeSoldier2 = MercPtrs[gusUIFullTargetID];

					// Do message box...
					//DoMessageBox( MSG_BOX_BASIC_STYLE, TacticalStr[ EXCHANGE_PLACES_REQUESTER ], GAME_SCREEN, ( UINT8 )MSG_BOX_FLAG_YESNO, ExchangeMessageBoxCallBack, NULL );
					SwapMercPositions(gpExchangeSoldier1, gpExchangeSoldier2);
				}
			}
			return(-3);
		}

		pIntTile = GetCurInteractiveTileGridNoAndStructure(&sIntTileGridNo, &pStructure);

		if (pIntTile != NULL)
		{
			bReturnCode = -3;

			// Check if we are over an item pool, take precedence over that.....
			// EXCEPT FOR SWITCHES!
			if ((pStructure->fFlags & STRUCTURE_OPEN || !(pStructure->fFlags & STRUCTURE_OPENABLE)) && !(pStructure->fFlags & (STRUCTURE_SWITCH | STRUCTURE_ANYDOOR)) && GetItemPool(sIntTileGridNo, &pItemPool, pSoldier->pathing.bLevel))
			{
				if (AM_AN_EPC(pSoldier))
				{
					// Display message
					// ScreenMsg( FONT_MCOLOR_LTYELLOW, MSG_UI_FEEDBACK, TacticalStr[ NO_PATH ] );
					ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_UI_FEEDBACK, TacticalStr[EPC_CANNOT_DO_THAT]);
					bReturnCode = -1;
				}
				else if (UIOkForItemPickup(pSoldier, sIntTileGridNo))
				{
					bZLevel = GetLargestZLevelOfItemPool(pItemPool);

					if (AnyItemsVisibleOnLevel(pItemPool, bZLevel))
					{
						fContinue = FALSE;

						SetUIBusy(pSoldier->ubID);

						if ((gTacticalStatus.uiFlags & INCOMBAT) && (gTacticalStatus.uiFlags & TURNBASED))
						{
							//puiNewEvent = C_WAIT_FOR_CONFIRM;
							SoldierPickupItem(pSoldier, pItemPool->iItemIndex, sIntTileGridNo, bZLevel);
						}
						else
						{
							BeginDisplayTimedCursor(OKHANDCURSOR_UICURSOR, 300);

							SoldierPickupItem(pSoldier, pItemPool->iItemIndex, sIntTileGridNo, bZLevel);
						}
					}
				}
			}

			if (fContinue)
			{
				sActionGridNo = FindAdjacentGridEx(MercPtrs[gusSelectedSoldier], sIntTileGridNo, &ubDirection, NULL, FALSE, TRUE);
				if (sActionGridNo == -1)
				{
					sActionGridNo = sIntTileGridNo;
				}

				// If this is not the same tile as ours, check if we can get to dest!
				if (sActionGridNo != MercPtrs[gusSelectedSoldier]->sGridNo && gsCurrentActionPoints == 0)
				{
					ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_UI_FEEDBACK, TacticalStr[NO_PATH]);
					bReturnCode = -1;
				}
				else
				{
					bReturnCode = -2;
				}
			}
		}
	}

	return(bReturnCode);
}


BOOLEAN HandleUIReloading(SOLDIERTYPE* pSoldier)
{
	INT16 bAPs = 0;

	// CHECK OUR CURRENT CURSOR...

	// Do we have the ammo to reload?
	if (guiCurrentUICursor == GOOD_RELOAD_UICURSOR)
	{
		// Check APs to reload...
		bAPs = GetAPsToAutoReload(pSoldier, false);

		if (EnoughPoints(pSoldier, bAPs, 0, TRUE))
		{
			// OK, we have some ammo we can reload.... reload now!
			if (!AutoReload(pSoldier, false))
			{
				// Do we say we could not reload gun...?
			}

			// ATE: Re-examine cursor info!
			gfUIForceReExamineCursorData = TRUE;
		}
		return(TRUE);
	}

	if (guiCurrentUICursor == BAD_RELOAD_UICURSOR)
	{
		// OK, we have been told to reload but have no ammo...
		//ScreenMsg( FONT_MCOLOR_LTYELLOW, MSG_UI_FEEDBACK, L"No ammo to reload." );
		if (Random(3) == 0)
		{
			TacticalCharacterDialogue(pSoldier, QUOTE_OUT_OF_AMMO);
		}
		return(TRUE);
	}

	return(FALSE);
}


BOOLEAN ConfirmActionCancel(INT32 usMapPos, INT32 usOldMapPos)
{
	// OK, most times we want to leave confirm mode if our
	// gridno is different... but if we are in the grenade throw
	// confirm UI, we want a bigger radius...
	//if ( InAimCubeUI( ) )
	//{
	// Calculate distence between both gridnos.....
	//	if ( GetRangeFromGridNoDiff( GetInAimCubeUIGridNo( ), usOldMapPos ) > 1 )
	//if ( sMapPos != usOldMapPos )
	//	{
	//		return( TRUE );
	//	}
	//
	//else
	{
		if (usMapPos != usOldMapPos)
		{
			return(TRUE);
		}
	}

	return(FALSE);
}

void ChangeCurrentSquad(INT32 iSquad)
{
	// only allow if nothing in hand and the Change Squad button for whichever panel we're in must be enabled
	if ((gpItemPointer == NULL) && !gfDisableTacticalPanelButtons &&
		((gsCurInterfacePanel != TEAM_PANEL) || (ButtonList[iTEAMPanelButtons[CHANGE_SQUAD_BUTTON]]->uiFlags & BUTTON_ENABLED)))
	{
		INT32 cnt, cnt2, iCurrentSquad;
		INT32 cnt3 = -1;

		// Buggler: dynamic tactical squad hotkey assignments only take into account squads present in sector
		//find the actual squad ID present in tactical map
		for (cnt = 0; cnt < NUMBER_OF_SQUADS; cnt++)
		{
			for (cnt2 = 0; cnt2 < NUMBER_OF_SOLDIERS_PER_SQUAD; cnt2++)
			{
				if (Squad[cnt][cnt2] != NULL && Squad[cnt][cnt2]->bInSector && OK_INTERRUPT_MERC(Squad[cnt][cnt2]) && OK_CONTROLLABLE_MERC(Squad[cnt][cnt2]))
				{
					cnt3++;
					break;
				}
			}

			if (iSquad == cnt3)
				break;
		}

		if (IsSquadOnCurrentTacticalMap(cnt))
		{
			//resort the squad in case the order has, for any reason, changed
			SortSquadByID((INT8)cnt);

			iCurrentSquad = CurrentSquad();

			if (cnt != iCurrentSquad)
			{
				//set active squad
				SetCurrentSquad(cnt, FALSE);

				if (gGameExternalOptions.fUseXMLSquadNames && cnt < min(ON_DUTY, gSquadNameVector.size()))
					ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, pMessageStrings[MSG_SQUAD_ACTIVE_STRING], gSquadNameVector[cnt].c_str());
				else
					ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, pMessageStrings[MSG_SQUAD_ACTIVE], (cnt + 1));

				ErasePath(TRUE);
				gfPlotNewMovement = TRUE;
			}
		}
	}
}

void HandleSelectMercSlot(UINT8 ubPanelSlot, INT8 bCode)
{
	UINT8 ubID;

	if (GetPlayerIDFromInterfaceTeamSlot(ubPanelSlot, &ubID))
	{
		HandleLocateSelectMerc(ubID, bCode);

		ErasePath(TRUE);
		gfPlotNewMovement = TRUE;
	}
}

void TestMeanWhile(INT32 iID)
{
	MEANWHILE_DEFINITION MeanwhileDef;
	INT32	cnt;
	SOLDIERTYPE* pSoldier;

	MeanwhileDef.sSectorX = gModSettings.ubMeanwhilePalaceSectorX; //3
	MeanwhileDef.sSectorY = gModSettings.ubMeanwhilePalaceSectorY; //16
	MeanwhileDef.ubNPCNumber = QUEEN;
	MeanwhileDef.usTriggerEvent = 0;
	MeanwhileDef.ubMeanwhileID = (UINT8)iID;

	if (iID == INTERROGATION)
	{
		UINT8 numPrisoners = 0;
		MeanwhileDef.sSectorX = gModSettings.ubMeanwhileInterrogatePOWSectorX; //7
		MeanwhileDef.sSectorY = gModSettings.ubMeanwhileInterrogatePOWSectorY; //14

		// Loop through our mercs and set gridnos once some found.....
		// look for all mercs on the same team,
		cnt = gTacticalStatus.Team[gbPlayerNum].bFirstID;

		for (pSoldier = MercPtrs[cnt]; cnt <= gTacticalStatus.Team[gbPlayerNum].bLastID; cnt++, pSoldier++)
		{
			// Are we a POW in this sector?
			if (pSoldier->bActive && pSoldier->bInSector)
			{

				ChangeSoldiersAssignment(pSoldier, ASSIGNMENT_POW);

				pSoldier->sSectorX = gModSettings.ubMeanwhileInterrogatePOWSectorX; //7
				pSoldier->sSectorY = gModSettings.ubMeanwhileInterrogatePOWSectorY; //14
				if (++numPrisoners > 2) break;
			}
		}
	}

	ScheduleMeanwhileEvent(&MeanwhileDef, 10);
}

void EscapeUILock()
{
	//UNLOCK UI
	UnSetUIBusy((UINT8)gusSelectedSoldier);

	// Decrease global busy	counter...
	gTacticalStatus.ubAttackBusyCount = 0;
#ifdef DEBUG_ATTACKBUSY
	OutputDebugString("Resetting attack busy due to escape of UI lock.\n");
#endif
	guiPendingOverrideEvent = LU_ENDUILOCK;
	UIHandleLUIEndLock(NULL);
}

#ifdef JA2BETAVERSION
#include "Map Edgepoints.h"
void ToggleMapEdgepoints()
{
#ifdef JA2EDITOR
	static BOOLEAN fToggleEdgepointDisplay = FALSE;
	if (fToggleEdgepointDisplay ^= TRUE)
	{ //Show edgepoints
		ShowMapEdgepoints();
	}
	else
	{ //Hide edgepoints
		HideMapEdgepoints();
	}
	SetRenderFlags(RENDER_FLAG_FULL);
#endif
}
#endif

#ifdef JA2BETAVERSION
BOOLEAN gfMercsNeverQuit = FALSE;
void ToggleMercsNeverQuit()
{
	if (gfMercsNeverQuit)
	{
		gfMercsNeverQuit = FALSE;
		ScreenMsg(FONT_RED, MSG_BETAVERSION, L"Merc contract expiring enabled.");
	}
	else
	{
		gfMercsNeverQuit ^= TRUE;
		ScreenMsg(FONT_RED, MSG_BETAVERSION, L"Merc contract expiring disabled.");
	}
}
#endif

// silversurfer: This function handles switching between prone, crouching and standing stance. Running is handled in function HandleTBSoldierRun().
void HandleStanceChangeFromUIKeys(UINT8 ubAnimHeight)
{
	// If we have multiple guys selected, make all change stance!
	SOLDIERTYPE* pSoldier;
	INT32						cnt;

	if (gTacticalStatus.fAtLeastOneGuyOnMultiSelect && !(gTacticalStatus.uiFlags & INCOMBAT))
	{
		// OK, loop through all guys who are 'multi-selected' and
		// check if our currently selected guy is amoung the
		// lucky few.. if not, change to a guy who is...
		cnt = gTacticalStatus.Team[gbPlayerNum].bFirstID;
		for (pSoldier = MercPtrs[cnt]; cnt <= gTacticalStatus.Team[gbPlayerNum].bLastID; cnt++, pSoldier++)
		{
			if (pSoldier->bActive && pSoldier->bInSector)
			{
				if (pSoldier->flags.uiStatusFlags & SOLDIER_MULTI_SELECTED)
				{
					// silversurfer: If we decide to stand up or press "s" again while we are standing we should reset movement to walk mode.
					// If we want to run we have to press "r" which is handled elsewhere.
					if (ubAnimHeight == ANIM_STAND)
					{
						if (pSoldier->usUIMovementMode != WALKING && pSoldier->usUIMovementMode != RUNNING && pSoldier->usUIMovementMode != WALKING_WEAPON_RDY && pSoldier->usUIMovementMode != WALKING_DUAL_RDY && pSoldier->usUIMovementMode != WALKING_ALTERNATIVE_RDY)
						{
							UIHandleSoldierStanceChange(pSoldier->ubID, ANIM_STAND);
							pSoldier->flags.fUIMovementFast = 0;
						}
						else
						{
							pSoldier->flags.fUIMovementFast = 0;
							pSoldier->usUIMovementMode = WALKING;
							gfPlotNewMovement = TRUE;
						}
					}
					else
						UIHandleSoldierStanceChange(pSoldier->ubID, ubAnimHeight);
				}
			}
		}
	}
	else
	{
		if (gusSelectedSoldier != NOBODY)
		{
			pSoldier = MercPtrs[(UINT8)gusSelectedSoldier];
			// silversurfer: If we decide to stand up or press "s" again while we are standing we should reset movement to walk mode.
			// If we want to run we have to press "r" which is handled elsewhere.
			if (ubAnimHeight == ANIM_STAND)
			{
				if (pSoldier->usUIMovementMode != WALKING && pSoldier->usUIMovementMode != RUNNING && pSoldier->usUIMovementMode != WALKING_WEAPON_RDY && pSoldier->usUIMovementMode != WALKING_DUAL_RDY && pSoldier->usUIMovementMode != WALKING_ALTERNATIVE_RDY)
				{
					UIHandleSoldierStanceChange(pSoldier->ubID, ANIM_STAND);
					pSoldier->flags.fUIMovementFast = 0;
				}
				else
				{
					if (pSoldier->IsCowering())
					{
						pSoldier->StopCoweringAnimation();
						UINT16 usNewState = pSoldier->GetNewSoldierStateFromNewStance(ubAnimHeight);
						pSoldier->usPendingAnimation = usNewState;
					}

					pSoldier->flags.fUIMovementFast = 0;
					pSoldier->usUIMovementMode = WALKING;
					gfPlotNewMovement = TRUE;
				}
			}
			else
			{
				if (pSoldier->IsCowering())
				{
					pSoldier->StopCoweringAnimation();
					UINT16 usNewState = pSoldier->GetNewSoldierStateFromNewStance(ubAnimHeight);
					if (gAnimControl[pSoldier->usAnimState].ubEndHeight != ubAnimHeight)
						pSoldier->usPendingAnimation = usNewState;
				}
				else if (pSoldier->bCollapsed && pSoldier->bBreath >= OKBREATH)
				{
					pSoldier->BeginSoldierGetup();
				}
				else
				{
					UIHandleSoldierStanceChange(pSoldier->ubID, ubAnimHeight);
				}
			}
		}
	}
}

void ToggleStealthMode(SOLDIERTYPE* pSoldier)
{
	// nothing in hand and either not in SM panel, or the matching button is enabled if we are in SM panel
	if ((gsCurInterfacePanel != SM_PANEL) || (ButtonList[giSMStealthButton]->uiFlags & BUTTON_ENABLED))
	{
		if (pSoldier->flags.uiStatusFlags & SOLDIER_VEHICLE)
		{
			return;
		}

		// ATE: Toggle stealth
		if (gpSMCurrentMerc != NULL && pSoldier->ubID == gpSMCurrentMerc->ubID)
		{
			gfUIStanceDifferent = TRUE;
		}

		pSoldier->bStealthMode = !pSoldier->bStealthMode;
		gfPlotNewMovement = TRUE;
		fInterfacePanelDirty = DIRTYLEVEL2;

		if (pSoldier->bStealthMode)
		{
			ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, pMessageStrings[MSG_MERC_ON_STEALTHMODE], pSoldier->GetName());
		}
		else
		{
			ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, pMessageStrings[MSG_MERC_OFF_STEALTHMODE], pSoldier->GetName());
		}
	}
}


void HandleStealthChangeFromUIKeys()
{
	// If we have multiple guys selected, make all change stance!
	SOLDIERTYPE* pSoldier;
	INT32						cnt;

	if (gTacticalStatus.fAtLeastOneGuyOnMultiSelect && !(gTacticalStatus.uiFlags & INCOMBAT))
	{
		// OK, loop through all guys who are 'multi-selected' and
		// check if our currently selected guy is amoung the
		// lucky few.. if not, change to a guy who is...
		cnt = gTacticalStatus.Team[gbPlayerNum].bFirstID;
		for (pSoldier = MercPtrs[cnt]; cnt <= gTacticalStatus.Team[gbPlayerNum].bLastID; cnt++, pSoldier++)
		{
			if (pSoldier->bActive && !AM_A_ROBOT(pSoldier) && pSoldier->bInSector)
			{
				if (pSoldier->flags.uiStatusFlags & SOLDIER_MULTI_SELECTED)
				{
					ToggleStealthMode(pSoldier);
				}
			}
		}
	}
	else
	{
		if (gusSelectedSoldier != NOBODY)
		{
			if (!AM_A_ROBOT(MercPtrs[gusSelectedSoldier]))
			{
				ToggleStealthMode(MercPtrs[gusSelectedSoldier]);
			}
		}
	}
}

void PopupAssignmentMenuInTactical(SOLDIERTYPE* pSoldier)
{
	// do something
	fShowAssignmentMenu = TRUE;
	CreateDestroyAssignmentPopUpBoxes();
	SetTacticalPopUpAssignmentBoxXY();
	DetermineBoxPositions();
	DetermineWhichAssignmentMenusCanBeShown();
	fFirstClickInAssignmentScreenMask = TRUE;
	gfIgnoreScrolling = TRUE;
}

//lal
void PopupMilitiaControlMenu(SOLDIERTYPE* pSoldier)
{
	// do something
	fShowMilitiaControlMenu = TRUE;
	CreateDestroyMilitiaControlPopUpBoxes();
	SetTacticalPopUpMilitiaControlBoxXY(pSoldier);
	DetermineMilitiaControlBoxPositions();
	DetermineWhichMilitiaControlMenusCanBeShown();
	fFirstClickInMilitiaControlScreenMask = TRUE;
	gfIgnoreScrolling = TRUE;
}

INT32 PickPocket(MERCPROFILESTRUCT* pProfile, UINT8 ppStart, UINT8 ppStop, UINT16 usItem, UINT8 iNumber, UINT8* cap);

bool BadGoggles(SOLDIERTYPE* pTeamSoldier)
{
	// WDS - Smart goggle switching
	// NOTE: Investigate using GetItemVisionRangeBonus from Items.cpp???
	if (!gGameExternalOptions.smartGoggleSwitch)
		return false;
	else
	{
		// Look through the head slots and find any sort of goggle.  Check if it is bad for this time of day.
		// silversurfer: also check if we are underground, sun goggles and night vision bonus are useless underground
		for (int headSlot = HEAD1POS; headSlot <= HEAD2POS; ++headSlot)
		{
			// check if we are below ground
			if (pTeamSoldier->bSectorZ > 0)
			{
				// we don't want a cave vision penalty
				if (Item[pTeamSoldier->inv[headSlot].usItem].cavevisionrangebonus < 0)
					return true;
			}

			// if we are above ground
			else
			{
				// at night we don't want a night vision penalty
				if (NightTime())
				{
					if (Item[pTeamSoldier->inv[headSlot].usItem].nightvisionrangebonus < 0)
						return true;
				}
				// at daytime we don't want a day vision penalty
				// also if we have a bright light penalty make sure that is doesn't exceed the day vision bonus
				else if (Item[pTeamSoldier->inv[headSlot].usItem].dayvisionrangebonus < 0 ||
					(Item[pTeamSoldier->inv[headSlot].usItem].dayvisionrangebonus + Item[pTeamSoldier->inv[headSlot].usItem].brightlightvisionrangebonus) < 0)
					return true;
			}
		}
	}
	return false;
}

void SwapGoggles(SOLDIERTYPE* pTeamSoldier)
{
	// WDS - Smart goggle switching
	// NOTE: Investigate using GetItemVisionRangeBonus from Items.cpp???
	// Look through the head slots and find any sort of goggle or an empty spot
	OBJECTTYPE* pGoggles = 0;
	int slotToUse = -1;
	INT8 swapSlot = -1;
	BOOLEAN isAttach = FALSE;

	for (int headSlot = HEAD1POS; headSlot <= HEAD2POS; ++headSlot)
	{
		if ((Item[pTeamSoldier->inv[headSlot].usItem].brightlightvisionrangebonus != 0))
		{
			slotToUse = headSlot;
			break;
		}
		if ((Item[pTeamSoldier->inv[headSlot].usItem].dayvisionrangebonus != 0))
		{
			slotToUse = headSlot;
			break;
		}
		else if ((Item[pTeamSoldier->inv[headSlot].usItem].nightvisionrangebonus != 0))
		{
			slotToUse = headSlot;
			break;
		}
		else if ((Item[pTeamSoldier->inv[headSlot].usItem].cavevisionrangebonus != 0))
		{
			slotToUse = headSlot;
			break;
		}
		else if (pTeamSoldier->inv[headSlot].exists() == false)
		{
			slotToUse = headSlot;
		}
	}

	if (slotToUse == -1)
	{
		// No place to swap in a new goggle, give up
		return;
	}

	// Find the best goggles for the current time of day anywhere in inventory
	// silversurfer: also check if underground
	if (DayTime() && pTeamSoldier->bSectorZ == 0)
	{
		pGoggles = FindSunGogglesInInv(pTeamSoldier, &swapSlot, &isAttach, TRUE);
	}
	else
	{
		pGoggles = FindNightGogglesInInv(pTeamSoldier, &swapSlot, &isAttach, TRUE);
	}

	if (pGoggles)
	{
		// We need to check that pGoggles is compatible with whatever is in the other face slot
		int otherFaceSlot = (slotToUse == HEAD1POS ? HEAD2POS : HEAD1POS);
		if (pTeamSoldier->inv[otherFaceSlot].exists() == true && !CompatibleFaceItem(pGoggles->usItem, pTeamSoldier->inv[otherFaceSlot].usItem))
			pGoggles = NULL;
	}

	if (pGoggles)
	{
		// Now either swap or equip the best one that was found
		if (pTeamSoldier->inv[slotToUse].exists())
		{
			if (CanItemFitInPosition(pTeamSoldier, &pTeamSoldier->inv[slotToUse], swapSlot, TRUE))
				SwapObjs(pTeamSoldier, slotToUse, pGoggles, TRUE);
			else if (swapSlot == HELMETPOS)
				SwapObjs(pTeamSoldier, slotToUse, pGoggles, TRUE);
			else if ((pTeamSoldier->inv[HELMETPOS].exists() == true && pTeamSoldier->inv[HELMETPOS].AttachObject(pTeamSoldier, &pTeamSoldier->inv[slotToUse], FALSE)) ||
				AutoPlaceObject(pTeamSoldier, &pTeamSoldier->inv[slotToUse], FALSE))
				pGoggles->MoveThisObjectTo(pTeamSoldier->inv[slotToUse], 1, pTeamSoldier, slotToUse);
			else
			{
				CHAR16	zTemp[100];
				swprintf(zTemp, Message[STR_CANNOT_ATTACH_ANY_SLOT], ItemNames[pTeamSoldier->inv[slotToUse].usItem]);
				ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_UI_FEEDBACK, zTemp);
			}
		}
		else
		{
			pGoggles->MoveThisObjectTo(pTeamSoldier->inv[slotToUse], 1, pTeamSoldier, slotToUse);
		}
	}
	else
	{
		// No goggles to equip, should the current ones be unequiped?
		if (pTeamSoldier->inv[slotToUse].exists())
		{
			if ((DayTime() && Item[pTeamSoldier->inv[slotToUse].usItem].nightvisionrangebonus > 0 && pTeamSoldier->bSectorZ == 0) ||
				((!DayTime() || pTeamSoldier->bSectorZ > 0) && (Item[pTeamSoldier->inv[slotToUse].usItem].brightlightvisionrangebonus > 0)))
			{
				// It's day and we're wearing night goggles (or vice-versa), find a place to stash them
				if (pTeamSoldier->inv[HELMETPOS].exists())
				{
					if (pTeamSoldier->inv[HELMETPOS].AttachObject(NULL, &pTeamSoldier->inv[slotToUse]))
					{
						// It worked!
					}
					else
					{
						/* //If we're here we already know we can't attach, don't we?
						// Try dumping it anywhere in inventory because it doesn't attach to the helmet
						if (NASValidAttachment( pTeamSoldier->inv[slotToUse].usItem, pTeamSoldier->inv[HELMETPOS].usItem ) &&
							pTeamSoldier->inv[slotToUse][0]->attachments.size() < MAX_ATTACHMENTS)
						{
							pTeamSoldier->inv[HELMETPOS].AttachObject( pTeamSoldier, &pTeamSoldier->inv[slotToUse], FALSE, 0 );
						}
						else
						*/
						//{
							// Remove sungoggles.
						PlaceInAnyPocket(pTeamSoldier, &pTeamSoldier->inv[slotToUse], FALSE);
						//}
					}
				}
				else
				{
					/* //again useless?
					// Try dumping it anywhere in inventory given there's no helemt
					if (NASValidAttachment( pTeamSoldier->inv[slotToUse].usItem, pTeamSoldier->inv[HELMETPOS].usItem ) &&
						pTeamSoldier->inv[slotToUse][0]->attachments.size() < MAX_ATTACHMENTS)
					{
						pTeamSoldier->inv[HELMETPOS].AttachObject( pTeamSoldier, &pTeamSoldier->inv[slotToUse], FALSE, 0 );
					}
					else
					*/
					//{
						// Remove sungoggles.
					PlaceInAnyPocket(pTeamSoldier, &pTeamSoldier->inv[slotToUse], FALSE);
					//}
				}
			}
		}
	}

	fCharacterInfoPanelDirty = TRUE;
	fTeamPanelDirty = TRUE;
	fInterfacePanelDirty = DIRTYLEVEL2;
	pTeamSoldier->DeleteSoldierLight();
	pTeamSoldier->PositionSoldierLight();
}

// HEADROCK HAM B2.8: This function does the same as SwapGoggles, with a twist. It changes all worn goggles in the
// team uniformly, so that everyone is wearing either nightvision or dayvision, regardless of what they were wearing
// before. The check is based on the headgear of the first character in the group (he'll switch, and everyone else
// will switch to match him.

void SwapGogglesUniformly(SOLDIERTYPE* pTeamSoldier, BOOLEAN fToNightVision)
{
	/* CHRISL - Adjusted this option to allow the game to search through Helmet attachments
		as well as inventory positions.
	*/
	OBJECTTYPE* pObj;
	OBJECTTYPE* pGoggles = NULL;
	INT8		bSlot1;
	int			bestBonus;
	bool		itemFound = false;
	INT8 swapSlot = -1;
	BOOLEAN isAttach = FALSE;

	//CHRISL: Before doing anything, we should look at both head slots to see if either slot has some sort of goggles
	for (bSlot1 = HEAD1POS; bSlot1 <= HEAD2POS; bSlot1++)
	{
		if (Item[pTeamSoldier->inv[bSlot1].usItem].brightlightvisionrangebonus > 0)
			itemFound = true;
		if (Item[pTeamSoldier->inv[bSlot1].usItem].nightvisionrangebonus > 0)
			itemFound = true;
	}
	//2 head slots
	for (bSlot1 = HEAD1POS; bSlot1 <= HEAD2POS; bSlot1++)
	{
		// if wearing sungoggles
		if (Item[pTeamSoldier->inv[bSlot1].usItem].brightlightvisionrangebonus > 0)
		{
			if (fToNightVision == TRUE) // Only if we want to switch to nightvision!
			{
				itemFound = true;
				bestBonus = 0;
				pGoggles = FindNightGogglesInInv(pTeamSoldier, &swapSlot, &isAttach);
				//search for better goggles on the helmet
				if (pGoggles)
				{
					bestBonus = Item[pGoggles->usItem].nightvisionrangebonus;
				}
				//search helmet and vest
				for (UINT8 gear = HELMETPOS; gear <= VESTPOS; gear++)
				{
					pObj = &(pTeamSoldier->inv[gear]);
					for (attachmentList::iterator iter = (*pObj)[0]->attachments.begin(); iter != (*pObj)[0]->attachments.end(); ++iter)
					{
						if (Item[iter->usItem].nightvisionrangebonus > bestBonus && Item[iter->usItem].usItemClass == IC_FACE && iter->exists())
						{
							pGoggles = &(*iter);
							bestBonus = Item[iter->usItem].nightvisionrangebonus;
						}
					}
				}
				if (pGoggles)
				{
					SwapObjs(pTeamSoldier, bSlot1, pGoggles, TRUE);
					break;
				}
				else if (Item[pTeamSoldier->inv[bSlot1].usItem].nightvisionrangebonus <= 0)
				{	//WarmSteel - just try and see if it works
					//if (NASValidAttachment( pTeamSoldier->inv[bSlot1].usItem, pTeamSoldier->inv[HELMETPOS].usItem ) &&
					//	pTeamSoldier->inv[bSlot1][0]->attachments.size() < MAX_ATTACHMENTS)
					if (pTeamSoldier->inv[HELMETPOS].AttachObject(pTeamSoldier, &pTeamSoldier->inv[bSlot1], FALSE, 0))
					{
						break;
					}
					else
					{
						// Remove nightgoggles.
						PlaceInAnyPocket(pTeamSoldier, &pTeamSoldier->inv[bSlot1], FALSE);
						break;
					}
				}
			}
		}
		// else if wearing NVGs
		else if (Item[pTeamSoldier->inv[bSlot1].usItem].nightvisionrangebonus > 0)
		{
			if (fToNightVision == FALSE) // Only if we want to switch to dayvision!
			{
				itemFound = true;
				bestBonus = 0;
				pGoggles = FindSunGogglesInInv(pTeamSoldier, &swapSlot, &isAttach);
				//search for better goggles on the helmet
				if (pGoggles)
				{
					bestBonus = Item[pGoggles->usItem].brightlightvisionrangebonus;
				}
				//search helmet and vest
				for (UINT8 gear = HELMETPOS; gear <= VESTPOS; gear++)
				{
					pObj = &(pTeamSoldier->inv[gear]);
					for (attachmentList::iterator iter = (*pObj)[0]->attachments.begin(); iter != (*pObj)[0]->attachments.end(); ++iter)
					{
						if (Item[iter->usItem].brightlightvisionrangebonus > bestBonus && Item[iter->usItem].usItemClass == IC_FACE && iter->exists())
						{
							pGoggles = &(*iter);
							bestBonus = Item[iter->usItem].brightlightvisionrangebonus;
						}
					}
				}
				if (pGoggles)
				{
					SwapObjs(pTeamSoldier, bSlot1, pGoggles, TRUE);
					break;
				}
				else if (Item[pTeamSoldier->inv[bSlot1].usItem].brightlightvisionrangebonus <= 0)
				{	//WarmSteel - try
					//if (NASValidAttachment( pTeamSoldier->inv[bSlot1].usItem, pTeamSoldier->inv[HELMETPOS].usItem ) &&
					//	pTeamSoldier->inv[bSlot1][0]->attachments.size() < MAX_ATTACHMENTS)
					if (pTeamSoldier->inv[HELMETPOS].AttachObject(pTeamSoldier, &pTeamSoldier->inv[bSlot1], FALSE, 0))
					{
						break;
					}
					else
					{
						// Remove nightgoggles.
						PlaceInAnyPocket(pTeamSoldier, &pTeamSoldier->inv[bSlot1], FALSE);
						break;
					}
				}
			}
		}
		// else if not wearing anything and no goggles found
		else if (itemFound == false && pTeamSoldier->inv[bSlot1].exists() == false)
		{
			bestBonus = 0;
			// search helmet and vest for goggles of some kind
			for (UINT8 gear = HELMETPOS; gear <= VESTPOS; gear++)
			{
				pObj = &(pTeamSoldier->inv[gear]);
				for (attachmentList::iterator iter = (*pObj)[0]->attachments.begin(); iter != (*pObj)[0]->attachments.end(); ++iter)
				{
					if (iter->exists()) {
						if (fToNightVision == FALSE && Item[iter->usItem].brightlightvisionrangebonus > bestBonus && Item[iter->usItem].usItemClass == IC_FACE)
						{
							pGoggles = &(*iter);
							bestBonus = Item[iter->usItem].brightlightvisionrangebonus;
						}
						else if (fToNightVision == TRUE && Item[iter->usItem].nightvisionrangebonus > bestBonus && Item[iter->usItem].usItemClass == IC_FACE)
						{
							pGoggles = &(*iter);
							bestBonus = Item[iter->usItem].nightvisionrangebonus;
						}
					}
				}
				if (pGoggles)
				{
					pGoggles->MoveThisObjectTo(pTeamSoldier->inv[bSlot1], 1, pTeamSoldier, bSlot1);
					pObj->RemoveAttachment(pGoggles);
					break;
				}
			}
			if (pTeamSoldier->inv[bSlot1].exists() == false)
			{
				if (fToNightVision == FALSE)
					pGoggles = FindSunGogglesInInv(pTeamSoldier, &swapSlot, &isAttach);
				else
					pGoggles = FindNightGogglesInInv(pTeamSoldier, &swapSlot, &isAttach);
				if (pGoggles)
				{
					SwapObjs(pTeamSoldier, bSlot1, pGoggles, TRUE);
					break;
				}
			}
			else
			{
				break;
			}
		}
	}
	fCharacterInfoPanelDirty = TRUE;
	fTeamPanelDirty = TRUE;
	fInterfacePanelDirty = DIRTYLEVEL2;
	pTeamSoldier->DeleteSoldierLight();
	pTeamSoldier->PositionSoldierLight();
}

void SeperateItems()
{
	if (!(gTacticalStatus.fEnemyInSector))
	{
		HandleAllReachAbleItemsInTheSector(gWorldSectorX, gWorldSectorY, gbWorldSectorZ);
		for (UINT32 uiLoop = 0; uiLoop < guiNumWorldItems; uiLoop++) //for all items in sector
		{
			if ((gWorldItems[uiLoop].bVisible == TRUE) && (gWorldItems[uiLoop].fExists) && (gWorldItems[uiLoop].usFlags & WORLD_ITEM_REACHABLE) && !(gWorldItems[uiLoop].usFlags & WORLD_ITEM_ARMED_BOMB))//item exists, is reachable, is visible and is not trapped
			{
				for (int x = 0; x < gWorldItems[uiLoop].object.ubNumberOfObjects; ++x) {
					if ((Item[gWorldItems[uiLoop].object.usItem].usItemClass == IC_GUN) && (gGameExternalOptions.gfShiftFUnloadWeapons == TRUE))//item is a gun and unloading is allowed
					{
						//Remove magazine
						if ((gWorldItems[uiLoop].object[x]->data.gun.usGunAmmoItem != NONE) && (gWorldItems[uiLoop].object[x]->data.gun.ubGunShotsLeft > 0))
						{
							CreateAmmo(gWorldItems[uiLoop].object[x]->data.gun.usGunAmmoItem, &gTempObject, gWorldItems[uiLoop].object[x]->data.gun.ubGunShotsLeft);
							gWorldItems[uiLoop].object[x]->data.gun.ubGunShotsLeft = 0;
							gWorldItems[uiLoop].object[x]->data.gun.usGunAmmoItem = NONE;
							// HEADROCK HAM 3.5: Clear ammo type
							gWorldItems[uiLoop].object[x]->data.gun.ubGunAmmoType = NONE;

							// put it on the ground
							AddItemToPool(gWorldItems[uiLoop].sGridNo, &gTempObject, 1, gWorldItems[uiLoop].ubLevel, WORLD_ITEM_REACHABLE, -1);
						}
					}

					//remove attachments
					//WarmSteel - This causes a crash when unloading attachments, then sorting, then selling all items in the sector in the map screen.
					//It is likely to be caused here because when i accidentally broke this part the bug didn't occur.
					//TODO : fix this.
					if (gGameExternalOptions.gfShiftFRemoveAttachments == TRUE)
					{
						//CHRISL: We run into a problem here because GetFreeWorldItemIndex, which gets called 
						//	from AddItemToPool, resets gWorldItems when it increases it's size.  This means
						//	iter loses it's relationship which causes a CTD if we use this hotkey and there
						//	aren't enough open WorldItems to accomodate all the attachments we're seperating.
						UINT8 size = 0, cnt = 0, uiLoopCnt = 0;
						// uiLoopCnt is an extra failsafe.  I think I've already managed to eliminate the
						//	infinite loop, but just in case, we'll use uiLoopCnt to force a break after a
						//	certain point.

						// Iterate backwards through attachments in order to detach grenades from underbarrel
						// launchers before detaching the launchers (and their grenade slots) themselves.
						// Since the size of the attachmentList remains constant under NAS but decrements by one
						// under OAS, recheck the list size every iteration in order to calculate an rindex.
						while ((size = gWorldItems[uiLoop].object[x]->attachments.size()) != cnt)
						{
							gTempObject = *gWorldItems[uiLoop].object[x]->GetAttachmentAtIndex(size - 1 - cnt);

							//WarmSteel - This actually still works with NAS, be it by accident
							if (gWorldItems[uiLoop].object.RemoveAttachment(&gTempObject, 0, x))
							{
								AddItemToPool(gWorldItems[uiLoop].sGridNo, &gTempObject, 1, gWorldItems[uiLoop].ubLevel, WORLD_ITEM_REACHABLE, -1);
								ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, TacticalStr[ATTACHMENT_REMOVED]);
							}
							else
							{
								cnt++;
							}

							uiLoopCnt++;
							if (uiLoopCnt > 100)
								break;
						}
					}

					// Bob: also empty out LBE items in sector inventory
					if (gWorldItems[uiLoop].object.IsActiveLBE(x)) {
						LBENODE* lbePtr = gWorldItems[uiLoop].object.GetLBEPointer(x);

						for (auto lbeInvIter = lbePtr->inv.begin(); lbeInvIter != lbePtr->inv.end(); lbeInvIter++) {
							OBJECTTYPE* LBEStack = lbeInvIter._Ptr;

							if (LBEStack->usItem != 0 && LBEStack->exists()) {
								AddItemToPool(gWorldItems[uiLoop].sGridNo, LBEStack, 1, gWorldItems[uiLoop].ubLevel, WORLD_ITEM_REACHABLE, -1);
							}
						}
						DestroyLBE(&(gWorldItems[uiLoop].object), x);
					}

				}
			}
		}
		ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, pImpButtonText[11]);
	}
}

void StackAndSort(BOOLEAN fRestrictToAmmo)
{
	if (!(gTacticalStatus.fEnemyInSector))
	{
		HandleAllReachAbleItemsInTheSector(gWorldSectorX, gWorldSectorY, gbWorldSectorZ);

		for (UINT32 uiLoop = 0; uiLoop < guiNumWorldItems; uiLoop++)
		{
			if ((gWorldItems[uiLoop].bVisible == TRUE) && (gWorldItems[uiLoop].fExists) && (gWorldItems[uiLoop].usFlags & WORLD_ITEM_REACHABLE) && !(gWorldItems[uiLoop].usFlags & WORLD_ITEM_ARMED_BOMB))//item exists, is reachable, is visible and is not trapped
			{
				//start by putting all identical items into one large pile regardless of stacking limits so we can merge them
				WORLDITEM dummyItem = gWorldItems[uiLoop];
				RemoveItemFromPool(gWorldItems[uiLoop].sGridNo, (uiLoop), gWorldItems[uiLoop].ubLevel);
				RemoveItemFromWorld(uiLoop);
				for (UINT32 i = uiLoop + 1; i < guiNumWorldItems; i++)
				{
					if (dummyItem.object.usItem == gWorldItems[i].object.usItem && gWorldItems[i].bVisible == TRUE && gWorldItems[i].fExists && (gWorldItems[i].usFlags & WORLD_ITEM_REACHABLE) && !(gWorldItems[i].usFlags & WORLD_ITEM_ARMED_BOMB))
					{
						dummyItem.object.AddObjectsToStack(gWorldItems[i].object, -1, NULL, NUM_INV_SLOTS, MAX_OBJECTS_PER_SLOT, false);
						if (gWorldItems[i].object.exists() == false && gWorldItems[i].fExists)
						{
							RemoveItemFromPool(gWorldItems[i].sGridNo, i, gWorldItems[i].ubLevel);
							RemoveItemFromWorld(i);
						}
					}
				}

				//merge items in stack
				if (fRestrictToAmmo == FALSE || Item[dummyItem.object.usItem].usItemClass == IC_AMMO)
					CleanUpStack(&dummyItem.object, NULL);

				//return item to world
				AddItemToPool(dummyItem.sGridNo, &dummyItem.object, dummyItem.bVisible, dummyItem.ubLevel, dummyItem.usFlags, dummyItem.bRenderZHeightAboveLevel, dummyItem.soldierID);

				//find out how many items can be put in a big slot
				UINT8 ubSlotLimit = ItemSlotLimit(&gWorldItems[uiLoop].object, STACK_SIZE_LIMIT);

				/*				//if we still have some space
								INT32 i = 0;
								while ( gWorldItems[ uiLoop ].object.ubNumberOfObjects < ubSlotLimit )
								{
									i++;
									//if the next item is the same
									if ( gWorldItems[ uiLoop ].object.usItem == gWorldItems[ uiLoop + i ].object.usItem )
									{
										// Clean up ammo stacks prior to trying to merge them
										if(fRestrictToAmmo == FALSE || Item[gWorldItems[uiLoop].object.usItem].usItemClass == IC_AMMO)
										{
											CleanUpStack(&gWorldItems[uiLoop].object, NULL);
											CleanUpStack(&gWorldItems[uiLoop+i].object, NULL);
										}
										INT8 ubObjCount = ubSlotLimit - gWorldItems[ uiLoop ].object.ubNumberOfObjects;
										INT8 bPointsToMove = __min( ubObjCount, gWorldItems[ uiLoop + i ].object.ubNumberOfObjects );

										gWorldItems[ uiLoop ].object.AddObjectsToStack( (gWorldItems[ uiLoop + i ].object), bPointsToMove);
										if(fRestrictToAmmo == FALSE || Item[gWorldItems[uiLoop].object.usItem].usItemClass == IC_AMMO)
											CleanUpStack(&gWorldItems[uiLoop].object, NULL);
										//CHRISL: After adding the object to the stack, we need to delete the old object from
										//	both gWorldItems and the ItemPool otherwise we cause a CTD.
										if(gWorldItems[uiLoop+i].object.exists() == false && gWorldItems[ uiLoop ].fExists)
										{
											RemoveItemFromPool(gWorldItems[uiLoop+i].sGridNo,(uiLoop+i),gWorldItems[uiLoop+i].ubLevel);
											RemoveItemFromWorld(uiLoop+i);
										}
									}
									//CHRISL: by changing this to a condition, we can use this hotkey immediately after the
									//	SHITFT+F hotkey.  Otherwise, if a stackable item ends up at the end of the inventory
									//	list, we won't be able to add it to the initial stack.
									else if(uiLoop+i == guiNumWorldItems)
									{
										break;
									}
								}*/
			}
		}
		NotifySoldiersToLookforItems();
		//HandleAllReachAbleItemsInTheSector( gWorldSectorX, gWorldSectorY, gbWorldSectorZ );
	}
}


void	QueryTBMButton(UINT32* puiNewEvent)
{
	INT32	sMapPos;

	if (!GetMouseMapPos(&sMapPos))
		return;

	if (gViewportRegion.ButtonState & MSYS_MIDDLE_BUTTON) // MID MOUSE BUTTON
	{
		if (!fMiddleButtonDown)
		{
			fMiddleButtonDown = TRUE;
			//RESETCOUNTER( RMOUSECLICK_DELAY_COUNTER );
		}
	}
	else if (fMiddleButtonDown)
	{
		if (gViewportRegion.uiFlags & MSYS_MOUSE_IN_AREA)
		{
			if (gGameExternalOptions.bAlternateMouseCommands)
				HandleAltMouseTBMButton(puiNewEvent);
			else
				HandleMouseTBMButton(puiNewEvent);
		}
		fMiddleButtonDown = FALSE;
		// Reset counter
		//RESETCOUNTER( RMOUSECLICK_DELAY_COUNTER );
	}
}//void	QueryTBMButton( UINT32 *puiNewEvent )

void	QueryTBWheel(UINT32* puiNewEvent)
{
	SOLDIERTYPE* pSoldier;
	INT32		usMapPos = 0;

	gViewportRegion.WheelState = gViewportRegion.WheelState * (gGameSettings.fOptions[TOPTION_INVERT_WHEEL] ? -1 : 1);
	// stub
	if (gViewportRegion.uiFlags & MSYS_MOUSE_IN_AREA)
	{
		if (gViewportRegion.WheelState != 0)
		{
			//printf("wheel %d\n", gViewportRegion.WheelState);
			//ScreenMsg( FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, L"wheel %d", gViewportRegion.WheelState);
			if (gpItemPointer == NULL)
			{
				// ATE:
				if (gusSelectedSoldier != NOBODY)
				{
					// Switch on UI mode
					switch (gCurrentUIMode)
					{

					case MOVE_MODE:
					case CONFIRM_MOVE_MODE:
					case HANDCURSOR_MODE:
					case RADIOCURSOR_MODE:
						if (gGameExternalOptions.bAlternateMouseCommands)
							HandleAltMouseTBWheel();
						else
							HandleMouseTBWheel();
					case IDLE_MODE:
					case ACTION_MODE:
					case LOCKOURTURN_UI_MODE:
					case LOOKCURSOR_MODE:
					case LOCKUI_MODE:
					case TALKCURSOR_MODE:
					case MENU_MODE:
						break;
					case CONFIRM_ACTION_MODE:
						if (GetSoldier(&pSoldier, gusSelectedSoldier))
						{
							if (gGameExternalOptions.bAimedBurstEnabled)
								HandleWheelAdjustCursor(pSoldier, usMapPos, -gViewportRegion.WheelState, brstmode);
							else
								HandleWheelAdjustCursorWOAB(pSoldier, usMapPos, -gViewportRegion.WheelState);
						}
						break;
					}
				}
			}
			ResetWheelState(&gViewportRegion);
		}
	}
}

void QueryTBX1Button(UINT32* puiNewEvent)
{
	INT32	sMapPos;
	if (gViewportRegion.uiFlags & MSYS_MOUSE_IN_AREA)
	{
		if (!GetMouseMapPos(&sMapPos))
			return;

		if (gViewportRegion.ButtonState & MSYS_X1_BUTTON) // MID MOUSE BUTTON
		{
			if (!fX1ButtonDown)
			{
				fX1ButtonDown = TRUE;
				//RESETCOUNTER( RMOUSECLICK_DELAY_COUNTER );
			}
		}
		else
		{
			if (fX1ButtonDown)
			{
				//*puiNewEvent = LC_LOOK;
				fX1ButtonDown = FALSE;

				if (gGameExternalOptions.bAlternateMouseCommands)
					HandleAltMouseTBX1Button(puiNewEvent);
				else
					HandleMouseTBX1Button(puiNewEvent);
			}
		}
	}
}

void QueryTBX2Button(UINT32* puiNewEvent)
{
	INT32	sMapPos;
	if (gViewportRegion.uiFlags & MSYS_MOUSE_IN_AREA)
	{
		if (!GetMouseMapPos(&sMapPos))
			return;

		if (gViewportRegion.ButtonState & MSYS_X2_BUTTON) // MID MOUSE BUTTON
		{
			if (!fX2ButtonDown)
			{
				fX2ButtonDown = TRUE;
				//RESETCOUNTER( RMOUSECLICK_DELAY_COUNTER );
			}
		}
		else if (fX2ButtonDown)
		{
			fX2ButtonDown = FALSE;
			if (gGameExternalOptions.bAlternateMouseCommands)
				HandleAltMouseTBX2Button(puiNewEvent);
			else
				HandleMouseTBX2Button(puiNewEvent);
		}
	}
}

//silversurfer: this allows swapping of merc portraits in tactical screen using CTRL+LEFTARROW / CTRL+RIGHTARROW
void SwapMercPortraits(SOLDIERTYPE* pSoldier, INT8 bDirection)
{
	// only swap mercs when the Team Panel is active
	if (gsCurInterfacePanel != TEAM_PANEL)
		return;

	// if someone is talking don't swap!
	if (gpCurrentTalkingFace != NULL)
		return;

	UINT8 ubSourceMerc = (UINT8)gusSelectedSoldier;
	UINT8 ubTargetMerc;
	INT32 iSourceFace;
	INT32 iTargetFace;
	UINT8 ubGroupID = pSoldier->ubGroupID;
	INT8 bOldPosition = GetTeamSlotFromPlayerID(MercPtrs[ubSourceMerc]->ubID);
	INT8 bNewPosition = bOldPosition + bDirection;
	SOLDIERTYPE TempMenptr = Menptr[ubSourceMerc];

	// anv: vehicle passengers are swapped differently
	if (pSoldier->flags.uiStatusFlags & (SOLDIER_DRIVER | SOLDIER_PASSENGER))
	{
		SOLDIERTYPE* pVehicle = GetSoldierStructureForVehicle(pSoldier->iVehicleId);
		if (pVehicle != NULL && bNewPosition < gNewVehicle[pVehicleList[pVehicle->bVehicleID].ubVehicleType].iNewSeatingCapacities)
		{
			if (SwapVehicleSeat(pVehicle, pSoldier, bNewPosition))
			{
				RebuildCurrentSquad();
				// refresh interface
				fCharacterInfoPanelDirty = TRUE;
				fTeamPanelDirty = TRUE;
				fInterfacePanelDirty = DIRTYLEVEL2;
			}
		}
		return;
	}

	// check if new position is occupied by another merc? we won't replace an empty slot
	if (gTeamPanel[bNewPosition].fOccupied && gTeamPanel[bNewPosition].ubID != NOBODY)
	{
		ubTargetMerc = gTeamPanel[bNewPosition].ubID;

		// Hey, you're dead. I don't want to swap with you.
		if (MercPtrs[ubTargetMerc]->stats.bLife <= 0)
		{
			RebuildCurrentSquad();
			return;
		}

		// store face indexes
		iSourceFace = MercPtrs[ubSourceMerc]->iFaceIndex;
		iTargetFace = MercPtrs[ubTargetMerc]->iFaceIndex;
		FACETYPE TempFace = gFacesData[iSourceFace];

		// swap the data
		Menptr[ubSourceMerc] = Menptr[ubTargetMerc];
		Menptr[ubTargetMerc] = TempMenptr;
		// also swap face data, otherwise face gear, opp count etc won't update
		gFacesData[iSourceFace] = gFacesData[iTargetFace];
		gFacesData[iTargetFace] = TempFace;

		// update IDs in the data so they match array index again
		Menptr[ubSourceMerc].ubID = ubSourceMerc;
		Menptr[ubTargetMerc].ubID = ubTargetMerc;
		gFacesData[iSourceFace].iID = iSourceFace;
		gFacesData[iTargetFace].iID = iTargetFace;

		// update soldier ID so they match merc index again
		gFacesData[iSourceFace].ubSoldierID = ubSourceMerc;
		gFacesData[iTargetFace].ubSoldierID = ubTargetMerc;

		// update face index in merc data
		Menptr[ubSourceMerc].iFaceIndex = iSourceFace;
		Menptr[ubTargetMerc].iFaceIndex = iTargetFace;

		// update group info
		RemovePlayerFromGroup(ubGroupID, MercPtrs[ubSourceMerc]);
		RemovePlayerFromGroup(ubGroupID, MercPtrs[ubTargetMerc]);
		AddPlayerToGroup(ubGroupID, MercPtrs[ubSourceMerc]);
		AddPlayerToGroup(ubGroupID, MercPtrs[ubTargetMerc]);
		SortSquadByID(MercPtrs[ubSourceMerc]->bAssignment);
		RebuildCurrentSquad();

		// don't forget to renew selection of merc
		gusSelectedSoldier = ubTargetMerc;

		// refresh interface
		fCharacterInfoPanelDirty = TRUE;
		fTeamPanelDirty = TRUE;
		fInterfacePanelDirty = DIRTYLEVEL2;
	}
}

// sevenfm: new mouse commands
void HandleAltMouseTBWheel(void)
{
	if (!(gTacticalStatus.uiFlags & ENGAGED_IN_CONV) &&
		((gsCurInterfacePanel != SM_PANEL) || (ButtonList[iSMPanelButtons[NEXTMERC_BUTTON]]->uiFlags & BUTTON_ENABLED)))
	{
		if (gViewportRegion.WheelState > 0)	// wheel up
		{
			if (_KeyDown(ALT))
				if (_KeyDown(SHIFT))
				{
					if (_KeyDown(CTRL))			// SHIFT+CTRL+ALT
						;
					else							// SHIFT+ALT
						;
				}
				else if (_KeyDown(CTRL))		// CTRL+ALT
					HandleTBPickUpBackpacks();
				else								// ALT
					HandleTBGotoHigherStance();
			else if (_KeyDown(CTRL))
			{
				if (_KeyDown(SHIFT))				// SHIFT+CTRL
					;
				else								// CTRL
					HandleTBLocatePrevMerc();
			}
			else if (_KeyDown(SHIFT))			// SHIFT
				HandleTBCycleThroughVisibleEnemiesBackward();
			else
				HandleTBLevelUp();
		}
		else										// wheel down
		{
			if (_KeyDown(ALT))
				if (_KeyDown(SHIFT))
				{
					if (_KeyDown(CTRL))			// SHIFT+CTRL+ALT
						;
					else							// SHIFT+ALT
						;
				}
				else if (_KeyDown(CTRL))		// CTRL+ALT
					HandleTBDropBackpacks();
				else								// ALT
					HandleTBGotoLowerStance();
			else if (_KeyDown(CTRL))
			{
				if (_KeyDown(SHIFT))				// SHIFT+CTRL
					;
				else								// CTRL
					HandleTBLocateNextMerc();
			}
			else if (_KeyDown(SHIFT))			// SHIFT
				HandleTBCycleThroughVisibleEnemies();
			else
				HandleTBLevelDown();
		}
	}
}

void HandleAltMouseTBMButton(UINT32* puiNewEvent)
{
	INT32 usMapPos;
	GetMouseMapPos(&usMapPos);

	if (_KeyDown(ALT))
	{
		if (_KeyDown(SHIFT))
		{
			if (_KeyDown(CTRL))			// SHIFT+CTRL+ALT
				;
			else							// SHIFT+ALT
				;// reserved
		}
		else if (_KeyDown(CTRL))		// CTRL+ALT
		{
			HandleTacticalReload();
		}
		else								// ALT
		{
			HandleTBToggleFireMode();
		}
	}
	else if (_KeyDown(CTRL))
	{
		if (_KeyDown(SHIFT))				// SHIFT+CTRL
			;
		else								// CTRL
			SetScopeMode(usMapPos);
	}
	else if (_KeyDown(SHIFT))			// SHIFT
	{
		HandleTacticalTransformItem();
	}
	else									// Button
	{
		HandleTBLook(puiNewEvent);
	}
}

void HandleAltMouseTBX1Button(UINT32* puiNewEvent)
{
	if (_KeyDown(ALT))
	{
		if (_KeyDown(SHIFT))
		{
			if (_KeyDown(CTRL))		// SHIFT+CTRL+ALT
				;
			else						// SHIFT+ALT
				;
		}
		else if (_KeyDown(CTRL))	// CTRL+ALT
			ToggleTrapNetworkView();
		else							// ALT
			HandleTBSwapGunsling();
	}
	else if (_KeyDown(CTRL))
	{
		if (_KeyDown(SHIFT))			// SHIFT+CTRL
			;
		else							// CTRL
			HandleTBSwapHands();
	}
	else if (_KeyDown(SHIFT))		// SHIFT
		;
	else								// Button
		HandleTBShowLOS();
}

void HandleAltMouseTBX2Button(UINT32* puiNewEvent)
{
	if (_KeyDown(ALT))
	{
		if (_KeyDown(SHIFT))
		{
			if (_KeyDown(CTRL))		// SHIFT+CTRL+ALT
				;
			else						// SHIFT+ALT
				;
		}
		else if (_KeyDown(CTRL))	// CTRL+ALT
			ToggleHostileTrapsView();
		else							// ALT
			HandleTBToggleFormation();
	}
	else if (_KeyDown(CTRL))
	{
		if (_KeyDown(SHIFT))			// SHIFT+CTRL
			;
		else							// CTRL
			HandleTBJump();
	}
	else if (_KeyDown(SHIFT))		// SHIFT
		HandleTBJumpThroughWindow();
	else								// Button
		HandleTBShowCover();
}

// sevenfm: these functions keep original mouse code functionality
void HandleMouseTBWheel(void)
{
	UINT8		bID;

	if (!(gTacticalStatus.uiFlags & ENGAGED_IN_CONV) &&
		((gsCurInterfacePanel != SM_PANEL) || (ButtonList[iSMPanelButtons[NEXTMERC_BUTTON]]->uiFlags & BUTTON_ENABLED)))
	{
		if (gViewportRegion.WheelState > 0)
		{
			//change stance ->DOWN
			if (_KeyDown(ALT))
			{
				if ((gusSelectedSoldier != NOBODY) && (gpItemPointer == NULL))
					GotoLowerStance(MercPtrs[gusSelectedSoldier]);
				return;
			}
			if (gusSelectedSoldier != NOBODY)
			{
				bID = FindPrevActiveAndAliveMerc(MercPtrs[gusSelectedSoldier], TRUE, TRUE);
				HandleLocateSelectMerc(bID, LOCATEANDSELECT_MERC);
				ErasePath(TRUE);
				gfPlotNewMovement = TRUE;
				// Center to guy....
				LocateSoldier(gusSelectedSoldier, SETLOCATOR);
			}
		}
		else
		{

			//change stance ->UP
			if (_KeyDown(ALT))
			{
				if ((gusSelectedSoldier != NOBODY) && (gpItemPointer == NULL))
					GotoHeigherStance(MercPtrs[gusSelectedSoldier]);
				return;
			}

			//ScreenMsg( FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, L"wheel %d", gViewportRegion.WheelState);
			if (gusSelectedSoldier != NOBODY)
			{ //Select next merc
				bID = FindNextMercInTeamPanel(MercPtrs[gusSelectedSoldier], FALSE, FALSE);
				HandleLocateSelectMerc(bID, LOCATEANDSELECT_MERC);
				ErasePath(TRUE);
				gfPlotNewMovement = TRUE;
				// Center to guy....
				LocateSoldier(gusSelectedSoldier, SETLOCATOR);
			}
		}
		//*puiNewEvent = M_ON_TERRAIN; ????????????????
	}
}

void HandleMouseTBMButton(UINT32* puiNewEvent)
{
	if (_KeyDown(ALT))
	{
		// toggle fire mode
		if ((gpItemPointer == NULL) &&
			((gsCurInterfacePanel != SM_PANEL) || (ButtonList[iSMPanelButtons[BURSTMODE_BUTTON]]->uiFlags & BUTTON_ENABLED)))
			SetBurstMode();
	}
	else
	{
		HandleTBLook(puiNewEvent);
	}
}

void HandleMouseTBX1Button(UINT32* puiNewEvent)
{
	if (!_KeyDown(ALT) && !_KeyDown(SHIFT))
	{
		UIHandleChangeLevel(NULL);
	}
	else if (_KeyDown(SHIFT))
	{
		HandleTBJumpThroughWindow();
	}
	else if (_KeyDown(ALT))
	{
		HandleTBJump();
	}
}
void HandleMouseTBX2Button(UINT32* puiNewEvent)
{
	if (_KeyDown(ALT))
		AutoReload(MercPtrs[gusSelectedSoldier]);
	else
		HandleTBToggleStealthAll();
}

// sevenfm: common TurnBased functionality
void HandleTBLook(UINT32* puiNewEvent)
{
	//*puiNewEvent = LC_LOOK;
	if (gCurrentUIMode == CONFIRM_ACTION_MODE)
		brstmode = (brstmode == 1) ? 0 : 1;
	else
	{
		ErasePath(TRUE);
		*puiNewEvent = LC_ON_TERRAIN;
	}
}
void HandleTBJump(void)
{
	SOLDIERTYPE* pjSoldier;
	if (GetSoldier(&pjSoldier, gusSelectedSoldier))
	{
		INT16							sAPCost;
		INT16							sBPCost;
		BOOLEAN	fNearHeigherLevel;
		BOOLEAN	fNearLowerLevel;
		INT8	bDirection;

		// Make sure the merc is not collapsed!
		if (!IsValidStance(pjSoldier, ANIM_CROUCH))
		{
			if (pjSoldier->bCollapsed && pjSoldier->bBreath < OKBREATH)
				ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_UI_FEEDBACK, gzLateLocalizedString[4], pjSoldier->GetName());
			return;
		}

		// Climb on roofs
		GetMercClimbDirection(pjSoldier->ubID, &fNearLowerLevel, &fNearHeigherLevel);

		if (fNearLowerLevel)
		{
			// CHRISL: Turn off manual jumping while wearing a backpack
			if (!pjSoldier->CanClimbWithCurrentBackpack())
				return;

			if (EnoughPoints(pjSoldier, GetAPsToClimbRoof(pjSoldier, TRUE), GetBPsToClimbRoof(pjSoldier, TRUE), FALSE))
			{
				pjSoldier->BeginSoldierClimbDownRoof();
			}
		}

		if (fNearHeigherLevel)
		{
			// No climbing when wearing a backpack!
			if (!pjSoldier->CanClimbWithCurrentBackpack())
				return;

			if (EnoughPoints(pjSoldier, GetAPsToClimbRoof(pjSoldier, FALSE), GetBPsToClimbRoof(pjSoldier, FALSE), FALSE))
			{
				pjSoldier->BeginSoldierClimbUpRoof();
			}
		}

		// Jump over fence
		if (FindFenceJumpDirection(pjSoldier, pjSoldier->sGridNo, pjSoldier->ubDirection, &bDirection))
		{
			if (!pjSoldier->CanClimbWithCurrentBackpack())
			{
				sAPCost = GetAPsToJumpFence(pjSoldier, TRUE);
				sBPCost = GetBPsToJumpFence(pjSoldier, TRUE);
			}
			else
			{
				sAPCost = GetAPsToJumpFence(pjSoldier, FALSE);
				sBPCost = GetBPsToJumpFence(pjSoldier, FALSE);
			}

			if (EnoughPoints(pjSoldier, sAPCost, sBPCost, FALSE))
			{
				pjSoldier->BeginSoldierClimbFence();
			}
		}

		// Climb on walls
		if (gGameExternalOptions.fCanClimbOnWalls == TRUE)
		{
			if (FindWallJumpDirection(pjSoldier, pjSoldier->sGridNo, pjSoldier->ubDirection, &bDirection))
			{
				// No climbing when wearing a backpack!
				if (!pjSoldier->CanClimbWithCurrentBackpack())
					return;

				if (EnoughPoints(pjSoldier, GetAPsToJumpWall(pjSoldier, FALSE), GetBPsToJumpWall(pjSoldier, FALSE), FALSE))
				{
					pjSoldier->BeginSoldierClimbWall();
				}
			}
		}
	}
}
void HandleTBJumpThroughWindow(void) {
	// WANNE: Jump through window?
	if (gGameExternalOptions.fCanJumpThroughWindows == TRUE)
	{
		INT16		sAPCost;
		INT16		sBPCost;
		SOLDIERTYPE* pjSoldier;
		INT8	bDirection;

		if (GetSoldier(&pjSoldier, gusSelectedSoldier))
		{
			if (FindWindowJumpDirection(pjSoldier, pjSoldier->sGridNo, pjSoldier->ubDirection, &bDirection))
			{
				if (!pjSoldier->CanClimbWithCurrentBackpack())
				{
					sAPCost = GetAPsToJumpThroughWindows(pjSoldier, TRUE);
					sBPCost = GetBPsToJumpThroughWindows(pjSoldier, TRUE);
				}
				else
				{
					sAPCost = GetAPsToJumpFence(pjSoldier, FALSE);
					sBPCost = GetBPsToJumpFence(pjSoldier, FALSE);
				}
				if (EnoughPoints(pjSoldier, sAPCost, sBPCost, FALSE))
				{
					pjSoldier->BeginSoldierClimbWindow();
				}
			}
		}
	}
}
void HandleTBToggleStealthAll(void)
{
	// Toggle squad's stealth mode.....
	// For each guy on squad...
	SOLDIERTYPE* pTeamSoldier;
	INT8					bLoop;
	BOOLEAN					fStealthOn = FALSE;

	// Check if at least one guy is on stealth....
	for (bLoop = gTacticalStatus.Team[gbPlayerNum].bFirstID, pTeamSoldier = MercPtrs[bLoop]; bLoop <= gTacticalStatus.Team[gbPlayerNum].bLastID; bLoop++, pTeamSoldier++)
	{
		if (OK_CONTROLLABLE_MERC(pTeamSoldier) && pTeamSoldier->bAssignment == CurrentSquad())
		{
			if (pTeamSoldier->bStealthMode)
				fStealthOn = TRUE;
		}
	}

	fStealthOn = !fStealthOn;

	for (bLoop = gTacticalStatus.Team[gbPlayerNum].bFirstID, pTeamSoldier = MercPtrs[bLoop]; bLoop <= gTacticalStatus.Team[gbPlayerNum].bLastID; bLoop++, pTeamSoldier++)
	{
		if (OK_CONTROLLABLE_MERC(pTeamSoldier) && pTeamSoldier->bAssignment == CurrentSquad() && !AM_A_ROBOT(pTeamSoldier))
		{
			if (gpSMCurrentMerc != NULL && bLoop == gpSMCurrentMerc->ubID)
				gfUIStanceDifferent = TRUE;
			pTeamSoldier->bStealthMode = fStealthOn;
		}
	}

	fInterfacePanelDirty = DIRTYLEVEL2;

	// OK, display message
	if (fStealthOn)
		ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, pMessageStrings[MSG_SQUAD_ON_STEALTHMODE]);
	else
		ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, pMessageStrings[MSG_SQUAD_OFF_STEALTHMODE]);
}
void HandleTBToggleFireMode(void)
{
	// toggle fire mode
	if ((gpItemPointer == NULL) &&
		((gsCurInterfacePanel != SM_PANEL) || (ButtonList[iSMPanelButtons[BURSTMODE_BUTTON]]->uiFlags & BUTTON_ENABLED)))
		SetBurstMode();
}
void HandleTBSelectAllMercs(void)
{
	SOLDIERTYPE* pSoldier;
	INT32						cnt;

	cnt = gTacticalStatus.Team[gbPlayerNum].bFirstID;
	for (pSoldier = MercPtrs[cnt]; cnt <= gTacticalStatus.Team[gbPlayerNum].bLastID; cnt++, pSoldier++)
	{

		// Check if this guy is OK to control....
		if (OK_CONTROLLABLE_MERC(pSoldier) && !(pSoldier->flags.uiStatusFlags & (SOLDIER_VEHICLE | SOLDIER_PASSENGER | SOLDIER_DRIVER)))
		{
			pSoldier->flags.uiStatusFlags |= SOLDIER_MULTI_SELECTED;
		}
	}
	EndMultiSoldierSelection(TRUE);
}
void HandleTBCycleThroughKnownEnemies(void)
{
	if (gTacticalStatus.uiFlags & TURNBASED && (gTacticalStatus.uiFlags & INCOMBAT))
	{
		//	if ( (InputEvent.usEvent == KEY_DOWN ) && InputEvent.usParam == ENTER	)
		CycleThroughKnownEnemies();
	}
}
void HandleTBCycleThroughKnownEnemiesBackward(void)
{
	if (gTacticalStatus.uiFlags & TURNBASED && (gTacticalStatus.uiFlags & INCOMBAT))
	{
		//	if ( (InputEvent.usEvent == KEY_DOWN ) && InputEvent.usParam == ENTER	)
		CycleThroughKnownEnemies(TRUE);
	}
}
void HandleTBCycleThroughVisibleEnemies(void)
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
void HandleTBCycleThroughVisibleEnemiesBackward(void)
{
	SOLDIERTYPE* pSoldier;

	if (gusSelectedSoldier != NOBODY)
	{
		pSoldier = MercPtrs[gusSelectedSoldier];

		if (pSoldier->aiData.bOppCnt > 0)
		{
			// Cycle....
			CycleVisibleEnemiesBackward(pSoldier);
		}
		else
		{
			ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_UI_FEEDBACK, TacticalStr[NO_ENEMIES_IN_SIGHT_STR]);
		}
	}
}
void HandleTBLocateSoldier(void)
{
	if (gusSelectedSoldier != NOBODY)
	{
		LocateSoldier(gusSelectedSoldier, 10);
	}
}
void HandleTBChangeLevel(void)
{
	if (gpItemPointer == NULL)
		UIHandleChangeLevel(NULL);
}
void HandleTBSwapHands(void)
{
	// swap primary & secondary hand
	if (gusSelectedSoldier != NOBODY && !AM_A_ROBOT(MercPtrs[gusSelectedSoldier]))
	{
		SOLDIERTYPE* pSoldier = MercPtrs[gusSelectedSoldier];
		UINT16 usOldHandItem = pSoldier->inv[HANDPOS].usItem;
		SwapHandItems(pSoldier);
		pSoldier->ReLoadSoldierAnimationDueToHandItemChange(usOldHandItem, pSoldier->inv[HANDPOS].usItem);

		fCharacterInfoPanelDirty = TRUE;
		fInterfacePanelDirty = DIRTYLEVEL2;
	}
}
void HandleTBSwapGunsling(void)
{
	SOLDIERTYPE* pSoldier;

	if (gusSelectedSoldier != NOBODY && UsingNewInventorySystem() == true)
	{
		pSoldier = MercPtrs[gusSelectedSoldier];
		pSoldier->SwitchWeapons();
	}
}
void HandleTBSwapKnife(void)
{
	if (gusSelectedSoldier != NOBODY && UsingNewInventorySystem() == true)
	{
		SOLDIERTYPE* pSoldier = MercPtrs[gusSelectedSoldier];
		pSoldier->SwitchWeapons(TRUE);
	}
}
void HandleTBSwapSidearm(void)
{
	if (gusSelectedSoldier != NOBODY && UsingNewInventorySystem() == true)
	{
		SOLDIERTYPE* pSoldier = MercPtrs[gusSelectedSoldier];
		pSoldier->SwitchWeapons(FALSE, TRUE);
	}
}
void HandleTBSwapGoogles(void)
{
	SOLDIERTYPE* pTeamSoldier;
	INT8		bLoop;

	for (bLoop = gTacticalStatus.Team[gbPlayerNum].bFirstID, pTeamSoldier = MercPtrs[bLoop]; bLoop <= gTacticalStatus.Team[gbPlayerNum].bLastID; bLoop++, pTeamSoldier++)
	{
		// HEADROCK HAM 3.5: When this INI setting is enabled, ALL mercs in the current sector will do a goggle swap.
		if (gGameExternalOptions.fGoggleSwapAffectsAllMercsInSector)
		{
			if (OK_CONTROLLABLE_MERC(pTeamSoldier) && pTeamSoldier->sSectorX == gWorldSectorX && pTeamSoldier->sSectorY == gWorldSectorY && pTeamSoldier->bSectorZ == gbWorldSectorZ && !AM_A_ROBOT(pTeamSoldier))
			{
				SwapGoggles(pTeamSoldier);
			}
		}
		else
		{
			if (OK_CONTROLLABLE_MERC(pTeamSoldier) && pTeamSoldier->bAssignment == CurrentSquad() && !AM_A_ROBOT(pTeamSoldier))
			{
				SwapGoggles(pTeamSoldier);
			}
		}
	}
}
void HandleTBToggleFormation(void)
{
	// Flugente: toggle formation
	if (gGameSettings.fOptions[TOPTION_MERCENARY_FORMATIONS])
	{
		gGameSettings.fOptions[TOPTION_MERCENARY_FORMATIONS] = FALSE;
		ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, pMessageStrings[MSG_FORMATIONS_OFF]);
	}
	else
	{
		gGameSettings.fOptions[TOPTION_MERCENARY_FORMATIONS] = TRUE;
		ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, pMessageStrings[MSG_FORMATIONS_ON]);
	}
}
void HandleTBEnterTurnbased(void)
{
	if (!is_networked)
	{
		// ctrl-x: enter turn based while sneaking - check if RT sneak is on, iw we're not already in combat and if we actually see any enemies
		if (gGameSettings.fOptions[TOPTION_ALLOW_REAL_TIME_SNEAK]) // changed by SANDRO
		{
			BOOLEAN fSneakingInRealTime = true;

			if (gTacticalStatus.uiFlags & INCOMBAT)
			{	// Don't allow this in combat
				if (!gGameExternalOptions.fQuietRealTimeSneak)
					ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, New113Message[MSG113_RTM_IN_COMBAT_ALREADY]);
				fSneakingInRealTime = false;
			}

			if (WeSeeNoOne())
			{	// Don't allow this if no enemies are seen - we have the forced turn mode for that
				if (!gGameExternalOptions.fQuietRealTimeSneak)
					ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, New113Message[MSG113_RTM_NO_ENEMIES]);
				fSneakingInRealTime = false;
			}

			if (fSneakingInRealTime)
				EnterCombatMode(OUR_TEAM);
		}
	}
}
void HandleTBToggleSneak(void)
{
	if (!is_networked)
	{
		// SANDRO - changed the real time sneak switch to be in the preferences
		if (gGameSettings.fOptions[TOPTION_ALLOW_REAL_TIME_SNEAK])
		{
			gGameSettings.fOptions[TOPTION_ALLOW_REAL_TIME_SNEAK] = false;
			ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, New113Message[MSG113_RTM_SNEAKING_OFF]);

			if (!WeSeeNoOne())	// if we're sneaking up on someone, enter turn-based
				EnterCombatMode(OUR_TEAM);
		}
		else
		{
			gGameSettings.fOptions[TOPTION_ALLOW_REAL_TIME_SNEAK] = true;
			ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, New113Message[MSG113_RTM_SNEAKING_ON]);
		}
	}
}
void HandleTBToggleStealth(void)
{
	// nothing in hand and either not in SM panel, or the matching button is enabled if we are in SM panel
	if ((gpItemPointer == NULL))
	{
		HandleStealthChangeFromUIKeys();
	}
}
void HandleTBReload(void)
{
	AutoReload(MercPtrs[gusSelectedSoldier]);
}
void HandleTBReloadAll(void)
{
	if (!(gTacticalStatus.fEnemyInSector))
	{
		SOLDIERTYPE* pTeamSoldier;
		UINT8		bLoop;
		UINT16		bullets;
		OBJECTTYPE* pGun, * pAmmo, * pAmmoMags;

		// Search for soldier
		for (bLoop = gTacticalStatus.Team[gbPlayerNum].bFirstID, pTeamSoldier = MercPtrs[bLoop]; bLoop <= gTacticalStatus.Team[gbPlayerNum].bLastID; bLoop++, pTeamSoldier++)
		{
			if (OK_CONTROLLABLE_MERC(pTeamSoldier) && pTeamSoldier->bAssignment == CurrentSquad() && !AM_A_ROBOT(pTeamSoldier))
			{
				// Search for gun in soldier inventory
				UINT32 invsize = pTeamSoldier->inv.size();
				for (UINT32 bLoop2 = 0; bLoop2 < invsize; ++bLoop2)
				{
					if ((Item[pTeamSoldier->inv[bLoop2].usItem].usItemClass & (IC_GUN | IC_LAUNCHER)))
					{
						pGun = &(pTeamSoldier->inv[bLoop2]);

						UINT16 gunmagsize = GetMagSize(pGun);

						//if magazine is not full
						if ((*pGun)[0]->data.gun.ubGunShotsLeft < gunmagsize)
						{
							// Search for ammo in sector
							for (UINT32 uiLoop = 0; uiLoop < guiNumWorldItems; ++uiLoop)
							{
								if ((gWorldItems[uiLoop].bVisible == TRUE) && (gWorldItems[uiLoop].fExists) && (gWorldItems[uiLoop].usFlags & WORLD_ITEM_REACHABLE) && !(gWorldItems[uiLoop].usFlags & WORLD_ITEM_ARMED_BOMB))//item exists, is reachable, is visible and is not trapped
								{
									if ((Item[gWorldItems[uiLoop].object.usItem].usItemClass & IC_AMMO)) // the item is ammo
									{
										pAmmo = &(gWorldItems[uiLoop].object);

										if (CompatibleAmmoForGun(pAmmo, pGun)) // can use the ammo with this gun
										{
											// same ammo type in gun and magazine
											if (Magazine[Item[(*pGun)[0]->data.gun.usGunAmmoItem].ubClassIndex].ubAmmoType == Magazine[Item[pAmmo->usItem].ubClassIndex].ubAmmoType)
											{
												ReloadGun(pTeamSoldier, pGun, pAmmo);
											}

											if ((*pAmmo)[0]->data.ubShotsLeft == 0)
											{
												RemoveItemFromPool(gWorldItems[uiLoop].sGridNo, uiLoop, gWorldItems[uiLoop].ubLevel);
											}

											// if gun is full, we can stop this
											if ((*pGun)[0]->data.gun.ubGunShotsLeft >= gunmagsize)
												break;
										}
									}
								}
							}
						}
						//CHRISL: if not enough ammo in sector, reload using ammo carried in inventory
						if ((*pGun)[0]->data.gun.ubGunShotsLeft < gunmagsize)
						{
							AutoReload(pTeamSoldier);
						}
					}
				}
			}
		}

		//MM: loop thru the soldiers again (lazy copy/paste :p).  could do it all at once, but then there may not be enough ammo from the world items to fill everyone's guns first
		for (bLoop = gTacticalStatus.Team[gbPlayerNum].bFirstID, pTeamSoldier = MercPtrs[bLoop]; bLoop <= gTacticalStatus.Team[gbPlayerNum].bLastID; bLoop++, pTeamSoldier++)
		{
			if (OK_CONTROLLABLE_MERC(pTeamSoldier) && pTeamSoldier->bAssignment == CurrentSquad() && !AM_A_ROBOT(pTeamSoldier))
			{
				// Search for ammo in soldier inventory
				UINT32 invsize = pTeamSoldier->inv.size();
				for (UINT32 bLoop2 = 0; bLoop2 < invsize; ++bLoop2)
				{
					if (Item[pTeamSoldier->inv[bLoop2].usItem].usItemClass & IC_AMMO)
					{
						pAmmoMags = &(pTeamSoldier->inv[bLoop2]);

						for (UINT16 stackMag = 0; stackMag < (*pAmmoMags).ubNumberOfObjects; stackMag++)
						{
							if ((*pAmmoMags)[stackMag]->data.ubShotsLeft < Magazine[Item[pAmmoMags->usItem].ubClassIndex].ubMagSize)
							{
								// Search for ammo in sector
								for (UINT32 uiLoop = 0; uiLoop < guiNumWorldItems; ++uiLoop)
								{
									if ((gWorldItems[uiLoop].bVisible == TRUE) && (gWorldItems[uiLoop].fExists) && (gWorldItems[uiLoop].usFlags & WORLD_ITEM_REACHABLE) && !(gWorldItems[uiLoop].usFlags & WORLD_ITEM_ARMED_BOMB))//item exists, is reachable, is visible and is not trapped
									{
										if ((Item[gWorldItems[uiLoop].object.usItem].usItemClass & IC_AMMO)) // the item is ammo
										{
											pAmmo = &(gWorldItems[uiLoop].object);

											if (Magazine[Item[pAmmoMags->usItem].ubClassIndex].ubCalibre == Magazine[Item[pAmmo->usItem].ubClassIndex].ubCalibre) // same calibre
											{
												// same ammo type
												if (Magazine[Item[pAmmoMags->usItem].ubClassIndex].ubAmmoType == Magazine[Item[pAmmo->usItem].ubClassIndex].ubAmmoType)
												{
													bullets = Magazine[Item[pAmmoMags->usItem].ubClassIndex].ubMagSize - (*pAmmoMags)[stackMag]->data.ubShotsLeft;

													if ((*pAmmo)[0]->data.ubShotsLeft < bullets)
														bullets = (*pAmmo)[0]->data.ubShotsLeft;

													(*pAmmoMags)[stackMag]->data.ubShotsLeft += bullets;
													(*pAmmo)[0]->data.ubShotsLeft -= bullets;

													fCharacterInfoPanelDirty = TRUE;
													fInterfacePanelDirty = DIRTYLEVEL2;
												}

												if ((*pAmmo)[0]->data.ubShotsLeft == 0)
												{
													RemoveItemFromPool(gWorldItems[uiLoop].sGridNo, uiLoop, gWorldItems[uiLoop].ubLevel);
												}
											}
										}
									}
								}

								//MM: if magazines still are partly empty, look through inventory for boxes and crates
								if ((*pAmmoMags)[stackMag]->data.ubShotsLeft < Magazine[Item[pAmmoMags->usItem].ubClassIndex].ubMagSize)
								{
									UINT32 invsize = pTeamSoldier->inv.size();
									for (UINT32 uiLoop = 0; uiLoop < invsize; ++uiLoop)
									{
										if ((Item[pTeamSoldier->inv[uiLoop].usItem].usItemClass & IC_AMMO) && Magazine[Item[pTeamSoldier->inv[uiLoop].usItem].ubClassIndex].ubMagType >= AMMO_BOX)
										{
											pAmmo = &(pTeamSoldier->inv[uiLoop]);

											if (Magazine[Item[pAmmoMags->usItem].ubClassIndex].ubCalibre == Magazine[Item[pAmmo->usItem].ubClassIndex].ubCalibre) // same calibre
											{
												// same ammo type
												if (Magazine[Item[pAmmoMags->usItem].ubClassIndex].ubAmmoType == Magazine[Item[pAmmo->usItem].ubClassIndex].ubAmmoType)
												{
													bullets = Magazine[Item[pAmmoMags->usItem].ubClassIndex].ubMagSize - (*pAmmoMags)[stackMag]->data.ubShotsLeft;

													if ((*pAmmo)[0]->data.ubShotsLeft < bullets)
														bullets = (*pAmmo)[0]->data.ubShotsLeft;

													(*pAmmoMags)[stackMag]->data.ubShotsLeft += bullets;
													(*pAmmo)[0]->data.ubShotsLeft -= bullets;

													fCharacterInfoPanelDirty = TRUE;
													fInterfacePanelDirty = DIRTYLEVEL2;
												}

												if ((*pAmmo)[0]->data.ubShotsLeft == 0)
													DeleteObj(pAmmo);
											}
										}
									}
								}
							}
						}

						if (IsWeaponAttached(pGun, IC_GUN))
						{
							OBJECTTYPE* pGun2 = FindAttachedWeapon(pGun, IC_GUN);

							UINT16 gunmagsize2 = GetMagSize(pGun2);

							if ((*pGun2)[0]->data.gun.ubGunShotsLeft < gunmagsize2)
							{
								// Search for ammo in sector
								for (UINT32 uiLoop = 0; uiLoop < guiNumWorldItems; ++uiLoop)
								{
									if ((gWorldItems[uiLoop].bVisible == TRUE) && (gWorldItems[uiLoop].fExists) && (gWorldItems[uiLoop].usFlags & WORLD_ITEM_REACHABLE) && !(gWorldItems[uiLoop].usFlags & WORLD_ITEM_ARMED_BOMB))//item exists, is reachable, is visible and is not trapped
									{
										if ((Item[gWorldItems[uiLoop].object.usItem].usItemClass & IC_AMMO)) // the item is ammo
										{
											pAmmo = &(gWorldItems[uiLoop].object);

											if (CompatibleAmmoForGun(pAmmo, pGun2)) // can use the ammo with this gun
											{
												// same ammo type in gun and magazine
												if (Magazine[Item[(*pGun2)[0]->data.gun.usGunAmmoItem].ubClassIndex].ubAmmoType == Magazine[Item[pAmmo->usItem].ubClassIndex].ubAmmoType)
												{
													ReloadGun(pTeamSoldier, pGun2, pAmmo);
												}

												if ((*pAmmo)[0]->data.ubShotsLeft == 0)
												{
													RemoveItemFromPool(gWorldItems[uiLoop].sGridNo, uiLoop, gWorldItems[uiLoop].ubLevel);
												}

												// if gun is full, we can stop this
												if ((*pGun2)[0]->data.gun.ubGunShotsLeft >= gunmagsize2)
													break;
											}
										}
									}
								}
							}

							//CHRISL: if not enough ammo in sector, reload using ammo carried in inventory
							if ((*pGun2)[0]->data.gun.ubGunShotsLeft < gunmagsize2)
							{
								AutoReload(pTeamSoldier);
							}
						}
					}
				}
			}
		}
	}
	else
	{
		SOLDIERTYPE* pTeamSoldier;
		UINT8		bLoop;
		OBJECTTYPE* pGun, * pAmmo;

		for (bLoop = gTacticalStatus.Team[gbPlayerNum].bFirstID, pTeamSoldier = MercPtrs[bLoop]; bLoop <= gTacticalStatus.Team[gbPlayerNum].bLastID; ++bLoop, pTeamSoldier++)
		{
			if (OK_CONTROLLABLE_MERC(pTeamSoldier) && pTeamSoldier->bAssignment == CurrentSquad() && !AM_A_ROBOT(pTeamSoldier))
			{
				if ((Item[pTeamSoldier->inv[HANDPOS].usItem].usItemClass & (IC_GUN | IC_LAUNCHER)))
				{
					if ((gTacticalStatus.uiFlags & INCOMBAT))
					{
						// Flugente: check for underbarrel weapons and use that object if necessary
						pGun = pTeamSoldier->GetUsedWeapon(&(pTeamSoldier->inv[HANDPOS]));

						//magazine is not full
						if ((*pGun)[0]->data.gun.ubGunShotsLeft < GetMagSize(pGun))
						{
							AutoReload(pTeamSoldier);
						}
					}
					else
					{
						// Search for gun in soldier inventory
						UINT32 invsize = pTeamSoldier->inv.size();
						for (UINT32 bLoop2 = 0; bLoop2 < invsize; ++bLoop2)
						{
							if ((Item[pTeamSoldier->inv[bLoop2].usItem].usItemClass & (IC_GUN | IC_LAUNCHER)))
							{
								pGun = &(pTeamSoldier->inv[bLoop2]);

								UINT16 gunmagsize = GetMagSize(pGun);

								//if magazine is not full
								if ((*pGun)[0]->data.gun.ubGunShotsLeft < gunmagsize)
								{
									// Search for ammo in soldier inventory
									for (UINT32 uiLoop = 0; uiLoop < invsize; ++uiLoop)
									{
										if ((Item[pTeamSoldier->inv[uiLoop].usItem].usItemClass & IC_AMMO)) // the item is ammo
										{
											pAmmo = &(pTeamSoldier->inv[uiLoop]);

											if (CompatibleAmmoForGun(pAmmo, pGun)) // can use the ammo with this gun
											{
												// same ammo type in gun and magazine
												if (Magazine[Item[(*pGun)[0]->data.gun.usGunAmmoItem].ubClassIndex].ubAmmoType == Magazine[Item[pAmmo->usItem].ubClassIndex].ubAmmoType)
												{
													ReloadGun(pTeamSoldier, pGun, pAmmo);

													fCharacterInfoPanelDirty = TRUE;
													fInterfacePanelDirty = DIRTYLEVEL2;

													// if gun is full, we can stop this
													if ((*pGun)[0]->data.gun.ubGunShotsLeft >= gunmagsize)
														break;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

void HandleTBShowCover(void)
{
	ToggleEnemyView();
}
void HandleTBShowMines(void)
{
	ToggleHostileTrapsView();
}
void HandleTBShowLOS(void)
{
	ToggleMercView();
}

void HandleTBToggleTrapNetworkView(void)
{
	ToggleTrapNetworkView();
}


void HandleTBGotoHigherStance(void)
{
	if ((gusSelectedSoldier != NOBODY) && (gpItemPointer == NULL))
		GotoHeigherStance(MercPtrs[gusSelectedSoldier]);
}
void HandleTBGotoLowerStance(void)
{
	if ((gusSelectedSoldier != NOBODY) && (gpItemPointer == NULL))
		GotoLowerStance(MercPtrs[gusSelectedSoldier]);
}
void HandleTBLocateNextMerc(void)
{
	UINT8	bID;
	if (gusSelectedSoldier != NOBODY)
	{ //Select next merc
		bID = FindNextMercInTeamPanel(MercPtrs[gusSelectedSoldier], FALSE, FALSE);
		HandleLocateSelectMerc(bID, LOCATEANDSELECT_MERC);
		// Center to guy....
		LocateSoldier(gusSelectedSoldier, SETLOCATOR);
	}
}
void HandleTBLocatePrevMerc(void)
{
	UINT8	bID;
	if (gusSelectedSoldier != NOBODY)
	{
		bID = FindPrevActiveAndAliveMerc(MercPtrs[gusSelectedSoldier], TRUE, TRUE);
		HandleLocateSelectMerc(bID, LOCATEANDSELECT_MERC);
		// Center to guy....
		LocateSoldier(gusSelectedSoldier, SETLOCATOR);
	}
}

void HandleTBLevelDown(void)
{
	if (gsInterfaceLevel > 0 &&
		gpItemPointer == NULL &&
		(gsCurInterfacePanel != SM_PANEL || ButtonList[iSMPanelButtons[UPDOWN_BUTTON]]->uiFlags & BUTTON_ENABLED))
	{
		UIHandleChangeLevel(NULL);

		if (gsCurInterfacePanel == SM_PANEL)
		{
			// Remember soldier's new value
			gpSMCurrentMerc->bUIInterfaceLevel = (INT8)gsInterfaceLevel;
		}
	}
}

void HandleTBLevelUp(void)
{
	if (gsInterfaceLevel == 0 &&
		gpItemPointer == NULL &&
		(gsCurInterfacePanel != SM_PANEL || ButtonList[iSMPanelButtons[UPDOWN_BUTTON]]->uiFlags & BUTTON_ENABLED))
	{
		UIHandleChangeLevel(NULL);

		if (gsCurInterfacePanel == SM_PANEL)
		{
			// Remember soldier's new value
			gpSMCurrentMerc->bUIInterfaceLevel = (INT8)gsInterfaceLevel;
		}
	}
}

void HandleTBBackpacks(void)
{
	if (UsingNewInventorySystem())
	{
		bool backpackDropped = false;
		SOLDIERTYPE* pTeamSoldier;

		for (UINT8 ubLoop = gTacticalStatus.Team[gbPlayerNum].bFirstID; ubLoop <= gTacticalStatus.Team[gbPlayerNum].bLastID; ubLoop++)
		{
			pTeamSoldier = MercPtrs[ubLoop];

			if (pTeamSoldier->flags.DropPackFlag)
			{
				backpackDropped = true;
				break;
			}
		}

		if (backpackDropped)
		{
			HandleTBPickUpBackpacks();
		}
		else
		{
			HandleTBDropBackpacks();
		}
	}
}

void HandleTBDropBackpacks(void)
{
	//if( UsingNewInventorySystem() && gusSelectedSoldier != NOBODY )
	if (UsingNewInventorySystem())
	{
		//SOLDIERTYPE *pSoldier = MercPtrs[ gusSelectedSoldier ];
		SOLDIERTYPE* pTeamSoldier;
		UINT8		ubLoop;

		INT16	sAPCost = APBPConstants[AP_BACK_PACK];
		INT32	iBPCost = APBPConstants[BP_BACK_PACK];

		for (ubLoop = gTacticalStatus.Team[gbPlayerNum].bFirstID; ubLoop <= gTacticalStatus.Team[gbPlayerNum].bLastID; ubLoop++)
		{
			pTeamSoldier = MercPtrs[ubLoop];

			if (OK_CONTROLLABLE_MERC(pTeamSoldier) &&
				OK_INTERRUPT_MERC(pTeamSoldier) &&
				!AM_A_ROBOT(pTeamSoldier) &&
				EnoughPoints(pTeamSoldier, sAPCost, iBPCost, FALSE) &&
				//pTeamSoldier->bAssignment == pSoldier->bAssignment &&
				pTeamSoldier->bAssignment < ON_DUTY &&
				pTeamSoldier->inv[BPACKPOCKPOS].exists() &&
				!pTeamSoldier->flags.DropPackFlag)
			{
				if (ChangeDropPackStatus(pTeamSoldier, TRUE))
				{
					ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, NewInvMessage[NIV_SOLDIER_DROP], pTeamSoldier->GetName());
				}
			}
		}

		fCharacterInfoPanelDirty = TRUE;
		fInterfacePanelDirty = DIRTYLEVEL2;
		//ScreenMsg( FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, NewInvMessage[NIV_ALL_DROP] );
	}
}

void HandleTBPickUpBackpacks(void)
{
	//if( UsingNewInventorySystem() && gusSelectedSoldier != NOBODY )
	if (UsingNewInventorySystem())
	{
		//SOLDIERTYPE *pSoldier = MercPtrs[ gusSelectedSoldier ];
		SOLDIERTYPE* pTeamSoldier;
		UINT8		ubLoop;

		INT16	sAPCost = APBPConstants[AP_BACK_PACK];
		INT32	iBPCost = APBPConstants[BP_BACK_PACK];

		for (ubLoop = gTacticalStatus.Team[gbPlayerNum].bFirstID; ubLoop <= gTacticalStatus.Team[gbPlayerNum].bLastID; ubLoop++)
		{
			pTeamSoldier = MercPtrs[ubLoop];

			if (OK_CONTROLLABLE_MERC(pTeamSoldier) &&
				OK_INTERRUPT_MERC(pTeamSoldier) &&
				!AM_A_ROBOT(pTeamSoldier) &&
				EnoughPoints(pTeamSoldier, sAPCost, iBPCost, FALSE) &&
				//pTeamSoldier->bAssignment == pSoldier->bAssignment &&
				pTeamSoldier->bAssignment < ON_DUTY &&
				!pTeamSoldier->inv[BPACKPOCKPOS].exists() &&
				pTeamSoldier->flags.DropPackFlag)
			{
				if (ChangeDropPackStatus(pTeamSoldier, FALSE))
				{
					ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, NewInvMessage[NIV_SOLDIER_PICKUP], pTeamSoldier->GetName());
				}
			}
		}

		fCharacterInfoPanelDirty = TRUE;
		fInterfacePanelDirty = DIRTYLEVEL2;
		//ScreenMsg( FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, NewInvMessage[NIV_ALL_PICKUP] );
	}
}

void HandleTBSoldierRun(void)
{
	SOLDIERTYPE* pSoldier = MercPtrs[gusSelectedSoldier];
	if (pSoldier->flags.uiStatusFlags & (SOLDIER_DRIVER))
	{
		pSoldier = GetSoldierStructureForVehicle(pSoldier->iVehicleId);
	}
	if (!pSoldier->MercInWater() && !(pSoldier->flags.uiStatusFlags & SOLDIER_ROBOT))
	{
		//change selected merc to run
		if (pSoldier->usUIMovementMode != WALKING
			&& pSoldier->usUIMovementMode != RUNNING
			&& pSoldier->usUIMovementMode != WALKING_WEAPON_RDY
			&& pSoldier->usUIMovementMode != WALKING_DUAL_RDY
			&& pSoldier->usUIMovementMode != WALKING_ALTERNATIVE_RDY)
		{
			UIHandleSoldierStanceChange((UINT8)pSoldier->ubID, ANIM_STAND);
			pSoldier->flags.fUIMovementFast = 1;
		}
		else
		{
			if (pSoldier->IsCowering())
			{
				pSoldier->StopCoweringAnimation();
				UINT16 usNewState = pSoldier->GetNewSoldierStateFromNewStance(ANIM_STAND);
				pSoldier->usPendingAnimation = usNewState;
			}

			pSoldier->flags.fUIMovementFast = 1;
			pSoldier->usUIMovementMode = RUNNING;
			gfPlotNewMovement = TRUE;
		}
	}
}

void HandleTacticalAmmoCrates(UINT8 magType)
{
	if (gTacticalStatus.fEnemyInSector)
		return;

	INT32		crateItem;
	INT32		worldItem;
	//UINT8		magType;
	bool		mergeSuccessful = false, ammoPresent = false;
	int loopCount = 0;
	OBJECTTYPE	newCrate;
	ammoPresent = true;

	while (ammoPresent && loopCount <= 10)
	{
		//look through all sector items for ammo.
		for (unsigned int wItem = 0; wItem < guiNumWorldItems; wItem++)
		{
			crateItem = 0;
			mergeSuccessful = false;
			if (Item[gWorldItems[wItem].object.usItem].usItemClass == IC_AMMO && gWorldItems[wItem].bVisible == TRUE && gWorldItems[wItem].fExists && (gWorldItems[wItem].usFlags & WORLD_ITEM_REACHABLE) && !(gWorldItems[wItem].usFlags & WORLD_ITEM_ARMED_BOMB))
			{
				worldItem = gWorldItems[wItem].object.usItem;
				//we don't want to do anything if the world item is already an ammo crate/box
				if (Magazine[Item[worldItem].ubClassIndex].ubMagType == magType)
					continue;

				//we have a valid, ammo item.  Look through Items.xml and see if we have an ammo crate for
				//	this ammo type
				for (UINT32 iLoop = 0; iLoop < gMAXITEMS_READ; ++iLoop)
				{
					//if ammo crate && calibers match && Ammo Types match
					if (Item[iLoop].usItemClass == IC_AMMO && Magazine[Item[iLoop].ubClassIndex].ubMagType == magType && Magazine[Item[iLoop].ubClassIndex].ubCalibre == Magazine[Item[worldItem].ubClassIndex].ubCalibre && Magazine[Item[iLoop].ubClassIndex].ubAmmoType == Magazine[Item[worldItem].ubClassIndex].ubAmmoType)
					{
						crateItem = iLoop;
						break;
					}
				}

				//if we found a crateItem in the list, we first want to see if we already have an item created
				if (crateItem != 0)
				{
					//look through world items first
					for (unsigned int loop = 0; loop < guiNumWorldItems; ++loop)
					{
						if (gWorldItems[loop].object.usItem == crateItem)
						{
							DistributeStatus(&gWorldItems[wItem].object, &gWorldItems[loop].object, Magazine[Item[crateItem].ubClassIndex].ubMagSize);
							if (gWorldItems[wItem].object.ubNumberOfObjects < 1)
							{
								mergeSuccessful = true;
								RemoveItemFromPool(gWorldItems[wItem].sGridNo, (wItem), gWorldItems[wItem].ubLevel);
								RemoveItemFromWorld(wItem);
								break;
							}
						}

					}
					//no crates in sector inventory.  search merc inventories
					if (!mergeSuccessful)
					{
						for (int loop = 0; loop < (int)OUR_TEAM_SIZE_NO_VEHICLE; ++loop)
						{
							if (MercPtrs[loop]->bActive && MercPtrs[loop]->bInSector)
							{
								UINT32 invsize = MercPtrs[loop]->inv.size();
								for (UINT32 pocket = 0; pocket < invsize; ++pocket)
								{
									if (MercPtrs[loop]->inv[pocket].usItem == crateItem)
									{
										DistributeStatus(&gWorldItems[wItem].object, &MercPtrs[loop]->inv[pocket], Magazine[Item[crateItem].ubClassIndex].ubMagSize);
										if (gWorldItems[wItem].object.ubNumberOfObjects < 1)
										{
											mergeSuccessful = true;
											RemoveItemFromPool(gWorldItems[wItem].sGridNo, (wItem), gWorldItems[wItem].ubLevel);
											RemoveItemFromWorld(wItem);
											break;
										}
									}
								}
								if (mergeSuccessful == true)
									break;
							}
						}
					}
					//no crates in merc inventory.  create a new sector item
					if (!mergeSuccessful)
					{
						CreateAmmo(crateItem, &newCrate, 0);
						DistributeStatus(&gWorldItems[wItem].object, &newCrate, Magazine[Item[crateItem].ubClassIndex].ubMagSize);
						AddItemToPool(gWorldItems[wItem].sGridNo, &newCrate, 1, gWorldItems[wItem].ubLevel, gWorldItems[wItem].usFlags, gWorldItems[wItem].bRenderZHeightAboveLevel);
						if (gWorldItems[wItem].object.ubNumberOfObjects < 1)
						{
							mergeSuccessful = true;
							RemoveItemFromPool(gWorldItems[wItem].sGridNo, (wItem), gWorldItems[wItem].ubLevel);
							RemoveItemFromWorld(wItem);
						}
					}
				}
			}
		}

		// if we added to / created a box/crate, then we're fine to reset this
		if (mergeSuccessful)
			loopCount = 0;

		//MM: loop through ammo multiple times, as boxes and crates may take a few passes to fill
		ammoPresent = false;
		for (unsigned int wItem = 0; wItem < guiNumWorldItems; ++wItem)
		{
			if (Item[gWorldItems[wItem].object.usItem].usItemClass == IC_AMMO && gWorldItems[wItem].bVisible == TRUE && gWorldItems[wItem].fExists && (gWorldItems[wItem].usFlags & WORLD_ITEM_REACHABLE) && !(gWorldItems[wItem].usFlags & WORLD_ITEM_ARMED_BOMB))
			{
				worldItem = gWorldItems[wItem].object.usItem;
				if (Magazine[Item[worldItem].ubClassIndex].ubMagType == magType)
					continue;

				loopCount++;
				ammoPresent = true;
				break;
			}
		}

		StackAndSort(TRUE);
	}
	ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, pImpButtonText[11]);
}

void HandleTacticalInventoryMenu(void)
{
	for (INT32 cnt = 0; cnt < TACTICAL_INVENTORY_DIALOG_NUM; ++cnt)
	{
		wcscpy(gzUserDefinedButton[cnt], szTacticalInventoryDialogString[cnt + 1]);
		gzUserDefinedButtonColor[cnt] = 0;
	}

	gzUserDefinedButtonColor[0] = FONT_MCOLOR_LTGRAY;
	gzUserDefinedButtonColor[1] = FONT_MCOLOR_LTGRAY;
	gzUserDefinedButtonColor[2] = FONT_MCOLOR_LTGRAY;
	gzUserDefinedButtonColor[3] = FONT_MCOLOR_LTGRAY;
	gzUserDefinedButtonColor[4] = FONT_ORANGE;
	gzUserDefinedButtonColor[5] = FONT_ORANGE;
	gzUserDefinedButtonColor[6] = FONT_ORANGE;
	gzUserDefinedButtonColor[7] = FONT_ORANGE;

	gzUserDefinedButtonColor[8] = FONT_MCOLOR_LTGREEN;
	gzUserDefinedButtonColor[9] = FONT_MCOLOR_LTGREEN;
	gzUserDefinedButtonColor[10] = FONT_MCOLOR_LTYELLOW;
	gzUserDefinedButtonColor[11] = FONT_MCOLOR_LTYELLOW;

	DoMessageBox(MSG_BOX_BASIC_STYLE,
		szTacticalInventoryDialogString[0], GAME_SCREEN, MSG_BOX_FLAG_GENERIC_SIXTEEN_BUTTONS,
		TacticalInventoryMessageBoxCallBack, NULL);
}

void TacticalInventoryMessageBoxCallBack(UINT8 ubExitValue)
{
	switch (ubExitValue)
	{
	case 1:		// switch NVG
		HandleTBSwapGoogles();
		break;
	case 2:		// reload ALL
		HandleTBReloadAll();
		break;
	case 3:		// move items (Shift+m)
		HandleTacticalMoveItems();
		break;
	case 4:
		break;
	case 5:		// sort items
		StackAndSort(TRUE);
		break;
	case 6:		// merge items
		StackAndSort(FALSE);
		break;
	case 7:		// remove att
		SeperateItems();
		break;
	case 8:		// organize items
		SeperateItems();
		StackAndSort(FALSE);
		break;
	case 9:		// ammo crates
		HandleTacticalAmmoCrates(AMMO_CRATE);
		break;
	case 10:	// ammo boxes
		HandleTacticalAmmoCrates(AMMO_BOX);
		break;
	case 11:	// drop backpacks
		HandleTBDropBackpacks();
		break;
	case 12:	// pickup backpacks
		HandleTBPickUpBackpacks();
		break;
	case 13:
		break;
	case 14:
		break;
	case 15:
		break;
	case 16:
		break;
	}
}

void FortificationSettingCallBack(UINT8 ubExitValue)
{
	gCurrentFortificationStructure = (UINT8)(DropDownTemplate<DROPDOWNNR_MSGBOX_1>::getInstance().GetSelectedEntryKey());
	gCurrentFortificationTileLibraryIndex = (UINT8)(DropDownTemplate<DROPDOWNNR_MSGBOX_2>::getInstance().GetSelectedEntryKey());
}

void HandleTacticalCoverMenu(void)
{
	for (INT32 cnt = 0; cnt < TACTICAL_COVER_DIALOG_NUM; ++cnt)
	{
		wcscpy(gzUserDefinedButton[cnt], szTacticalCoverDialogString[cnt + 1]);
		gzUserDefinedButtonColor[cnt] = 0;
	}
	gzUserDefinedButtonColor[0] = 0;
	gzUserDefinedButtonColor[1] = (gubDrawMode != COVER_DRAW_ENEMY_VIEW) ? FONT_LTRED : FONT_MCOLOR_LTGREEN;
	gzUserDefinedButtonColor[2] = (gubDrawMode != COVER_DRAW_MERC_VIEW) ? FONT_LTRED : FONT_MCOLOR_LTGREEN;
	gzUserDefinedButtonColor[3] = 0;
	gzUserDefinedButtonColor[4] = gDisplayEnemyRoles ? FONT_MCOLOR_LTGREEN : FONT_LTRED;
	gzUserDefinedButtonColor[5] = (gubDrawMode != DRAW_MODE_FORTIFY) ? FONT_LTRED : FONT_MCOLOR_LTGREEN;
	gzUserDefinedButtonColor[6] = (gubDrawMode != DRAW_MODE_TRACKER_SMELL) ? FONT_LTRED : FONT_MCOLOR_LTGREEN;
	gzUserDefinedButtonColor[7] = (gubDrawMode != DRAW_MODE_WEAPONDATA) ? FONT_LTRED : FONT_MCOLOR_LTGREEN;
	gzUserDefinedButtonColor[8] = (gubDrawMode != MINES_DRAW_PLAYERTEAM_NETWORKS) ? FONT_LTRED : FONT_MCOLOR_LTGREEN;
	gzUserDefinedButtonColor[9] = (gubDrawMode != MINES_DRAW_NETWORKCOLOURING) ? FONT_LTRED : FONT_MCOLOR_LTGREEN;
	gzUserDefinedButtonColor[10] = (gubDrawMode != MINES_DRAW_DETECT_ENEMY) ? FONT_LTRED : FONT_MCOLOR_LTGREEN;
	gzUserDefinedButtonColor[11] = 0;
	gzUserDefinedButtonColor[12] = (gubDrawMode != MINES_DRAW_NET_A) ? FONT_LTRED : FONT_MCOLOR_LTGREEN;
	gzUserDefinedButtonColor[13] = (gubDrawMode != MINES_DRAW_NET_B) ? FONT_LTRED : FONT_MCOLOR_LTGREEN;
	gzUserDefinedButtonColor[14] = (gubDrawMode != MINES_DRAW_NET_C) ? FONT_LTRED : FONT_MCOLOR_LTGREEN;
	gzUserDefinedButtonColor[15] = (gubDrawMode != MINES_DRAW_NET_D) ? FONT_LTRED : FONT_MCOLOR_LTGREEN;

	DoMessageBox(MSG_BOX_BASIC_STYLE, szTacticalCoverDialogString[0], GAME_SCREEN,
		MSG_BOX_FLAG_GENERIC_SIXTEEN_BUTTONS, TacticalCoverMessageBoxCallBack, NULL);
}

void TacticalCoverMessageBoxCallBack(UINT8 ubExitValue)
{
	switch (ubExitValue)
	{
	case 1:
		gubDrawMode = DRAW_MODE_OFF;
		break;
	case 2:
		gubDrawMode = COVER_DRAW_ENEMY_VIEW;
		break;
	case 3:
		gubDrawMode = COVER_DRAW_MERC_VIEW;
		break;
	case 4:
		break;
	case 5:
		gDisplayEnemyRoles = !gDisplayEnemyRoles;
		break;
	case 6:
		if (gubDrawMode == DRAW_MODE_FORTIFY)
			gubDrawMode = DRAW_MODE_OFF;
		else
			gubDrawMode = DRAW_MODE_FORTIFY;
		break;
	case 7:
		if (gubDrawMode == DRAW_MODE_TRACKER_SMELL)
			gubDrawMode = DRAW_MODE_OFF;
		else
			gubDrawMode = DRAW_MODE_TRACKER_SMELL;
		break;
	case 8:
		if (gubDrawMode == DRAW_MODE_WEAPONDATA)
			gubDrawMode = DRAW_MODE_OFF;
		else
			gubDrawMode = DRAW_MODE_WEAPONDATA;
		break;
	case 9:
		gubDrawMode = MINES_DRAW_PLAYERTEAM_NETWORKS;
		break;
	case 10:
		gubDrawMode = MINES_DRAW_NETWORKCOLOURING;
		break;
	case 11:
		gubDrawMode = MINES_DRAW_DETECT_ENEMY;
		break;
	case 12:
		break;
	case 13:
		gubDrawMode = MINES_DRAW_NET_A;
		break;
	case 14:
		gubDrawMode = MINES_DRAW_NET_B;
		break;
	case 15:
		gubDrawMode = MINES_DRAW_NET_C;
		break;
	case 16:
		gubDrawMode = MINES_DRAW_NET_D;
		break;
	}

	DisplayCover(TRUE);

	if (ubExitValue <= TACTICAL_COVER_DIALOG_NUM)
		ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, szTacticalCoverDialogPrintString[ubExitValue - 1]);
}

void ActivateCheatsMessageBoxCallBack(UINT8 ubExitValue)
{
	if (ubExitValue == MSG_BOX_RETURN_YES)
	{
		if (CHEATER_CHEAT_LEVEL())
		{
			RESET_CHEAT_LEVEL();
		}
		else
		{
			ACTIVATE_CHEAT_LEVEL();

			// ATE; We're done.... start cheat mode....
			ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, pMessageStrings[MSG_CHEAT_LEVEL_TWO]);
			SetHistoryFact(HISTORY_CHEAT_ENABLED, 0, GetWorldTotalMin(), -1, -1);
		}
	}
}


void HandleTacticalTransformItem(void)
{
	UINT16 usItem;
	TransformInfoStruct* pTransformation;

	SOLDIERTYPE* pSoldier;
	if (!GetSoldier(&pSoldier, gusSelectedSoldier))
		return;

	if (!pSoldier->inv[HANDPOS].exists())
		return;

	// ATE: Don't do this if in a fire animation.....
	if (gAnimControl[pSoldier->usAnimState].uiFlags & ANIM_FIRE)
		return;

	// don't do this when EDB is active
	if (gpItemDescObject)
		return;

	usItem = pSoldier->inv[HANDPOS].usItem;

	if (FindTransformation(usItem, &pTransformation, TRUE))
	{
		if (pTransformation->usAPCost > 0 && gTacticalStatus.uiFlags & INCOMBAT && gTacticalStatus.uiFlags & TURNBASED)
			ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, L"%s (%d AP)", pTransformation->szMenuRowText, pTransformation->usAPCost);
		else
			ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, pTransformation->szMenuRowText);

		// let's pretend we are calling this from EDB
		gpItemDescObject = &pSoldier->inv[HANDPOS];

		gpItemDescObject->TransformObject(pSoldier, 0, pTransformation, NULL);

		// cleanup
		gpItemDescObject = NULL;

		DirtyMercPanelInterface(pSoldier, DIRTYLEVEL2);
		gfUIForceReExamineCursorData = TRUE;
	}
}

BOOLEAN FindTransformation(UINT16 usItem, TransformInfoStruct** pTransformation, BOOLEAN fTactical)
{
	// find transformation
	for (UINT32 x = 0; x < MAXITEMS + 1; ++x)
	{
		if (Transform[x].usItem == (UINT16)-1)
		{
			break;
		}
		if (Transform[x].usItem == usItem &&
			(!fTactical ||
				HasItemFlag(usItem, CORPSE) ||
				Transform[x].usResult[0] != usItem && Item[Transform[x].usResult[0]].usItemClass == Item[usItem].usItemClass ||
				Transform[x].usResult[0] != usItem && Item[Transform[x].usResult[0]].ItemSize == Item[usItem].ItemSize))
		{
			*pTransformation = &Transform[x];
			return TRUE;
		}
	}
	return FALSE;
}

void HandleTacticalMoveItems(void)
{
	// Move all sector items to current mercs feet
	if (!(gTacticalStatus.fEnemyInSector))
	{
		HandleAllReachAbleItemsInTheSector(gWorldSectorX, gWorldSectorY, gbWorldSectorZ);

		SOLDIERTYPE* pSoldier;
		if (GetSoldier(&pSoldier, gusSelectedSoldier))
		{

			for (UINT32 uiLoop = 0; uiLoop < guiNumWorldItems; ++uiLoop) //for all items in sector
			{
				if ((gWorldItems[uiLoop].bVisible == TRUE) && (gWorldItems[uiLoop].fExists) && (gWorldItems[uiLoop].usFlags & WORLD_ITEM_REACHABLE) && !(gWorldItems[uiLoop].usFlags & WORLD_ITEM_ARMED_BOMB) && (gWorldItems[uiLoop].sGridNo != pSoldier->sGridNo))//item exists and is reachable and is not already on soldiers tile
				{
					MoveItemPools(gWorldItems[uiLoop].sGridNo, pSoldier->sGridNo, gWorldItems[uiLoop].ubLevel, pSoldier->pathing.bLevel);
				}
			}

			NotifySoldiersToLookforItems();
		}
	}
}

void HandleTacticalStoreInvItem(void)
{
	SOLDIERTYPE* pSoldier;
	UINT8 ubStoreSlot = 0;
	UINT16 APTotalCost = 0;

	if (gusSelectedSoldier != NOBODY)
		pSoldier = MercPtrs[gusSelectedSoldier];
	else
		return;

	if (!UsingNewInventorySystem())
	{
		ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, TacticalStr[QUICK_ITEMS_ONLY_NIV]);
		return;
	}

	if (!pSoldier->inv[HANDPOS].exists())
	{
		ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, TacticalStr[QUICK_ITEMS_NO_ITEM_IN_HAND]);
		return;
	}

	if (pSoldier->usQuickItemId == pSoldier->inv[HANDPOS].usItem &&
		(CanItemFitInPosition(pSoldier, &pSoldier->inv[HANDPOS], pSoldier->ubQuickItemSlot, FALSE) && !pSoldier->inv[pSoldier->ubQuickItemSlot].exists()))
		ubStoreSlot = pSoldier->ubQuickItemSlot;

	// find slot to store HANDPOS in
	for (UINT8 i = GUNSLINGPOCKPOS; i < NUM_INV_SLOTS && ubStoreSlot == 0; ++i)
	{
		// take first slot that hand item would fit
		if ((CanItemFitInPosition(pSoldier, &pSoldier->inv[HANDPOS], i, FALSE) && !pSoldier->inv[i].exists()))
		{
			ubStoreSlot = i;
			break;
		}
	}

	if (ubStoreSlot == 0)
	{
		ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, TacticalStr[QUICK_ITEMS_NOWHERE_TO_PLACE]);
		return;
	}

	// calculate needed APs
	if (UsingInventoryCostsAPSystem())
	{
		APTotalCost += GetInvMovementCost(&pSoldier->inv[HANDPOS], HANDPOS, ubStoreSlot);
		if (!EnoughPoints(pSoldier, APTotalCost, 0, TRUE))
			return;

		// move item from HANDPOS to found ubStoreSlot
		DeductPoints(pSoldier, APTotalCost, 0);
	}

	pSoldier->inv[HANDPOS].MoveThisObjectTo(pSoldier->inv[ubStoreSlot], 1, pSoldier);

	// swap hands
	if (pSoldier->inv[SECONDHANDPOS].exists())
		SwapHandItems(pSoldier);

	// update interface
	fCharacterInfoPanelDirty = TRUE;
	fInterfacePanelDirty = DIRTYLEVEL2;
	pSoldier->HandleFlashLights();
}

void HandleTacticalTakeInvItem(INT32 iType)
{
	SOLDIERTYPE* pSoldier;
	UINT8 ubItemSlot = HANDPOS;
	UINT16 APTotalCost = 0;

	if (iType == 0)
	{
		ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, TacticalStr[QUICK_ITEM_NO_DEFINED_ITEM]);
		return;
	}

	if (gusSelectedSoldier != NOBODY)
		pSoldier = MercPtrs[gusSelectedSoldier];
	else
		return;

	if (!UsingNewInventorySystem())
	{
		ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, TacticalStr[QUICK_ITEMS_ONLY_NIV]);
		return;
	}

	// check if item is already in main hand
	if (pSoldier->inv[HANDPOS].exists() &&
		(iType > 0 ? (pSoldier->inv[HANDPOS].usItem == iType) : (InvItemType(pSoldier->inv[HANDPOS].usItem) == iType)))
		return;

	if (pSoldier->inv[HANDPOS].exists() && pSoldier->inv[SECONDHANDPOS].exists())
	{
		// try to free HANDPOS for new item
		HandleTacticalStoreInvItem();
	}

	// both hands are full
	if (pSoldier->inv[HANDPOS].exists() && pSoldier->inv[SECONDHANDPOS].exists())
	{
		ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, TacticalStr[QUICK_ITEM_NO_FREE_HAND]);
		return;
	}

	// search for type of item
	for (UINT8 i = GUNSLINGPOCKPOS; i < NUM_INV_SLOTS; ++i)
	{
		if (pSoldier->inv[i].exists() &&
			!Item[pSoldier->inv[i].usItem].twohanded &&
			(iType > 0 ? (pSoldier->inv[i].usItem == iType) : (InvItemType(pSoldier->inv[i].usItem) == iType)))
		{
			ubItemSlot = i;
			break;
		}
	}
	// if not found item
	if (ubItemSlot == HANDPOS)
	{
		ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, TacticalStr[QUICK_ITEM_NOT_FOUND]);
		return;
	}

	// remember item slot and id
	pSoldier->usQuickItemId = pSoldier->inv[ubItemSlot].usItem;
	pSoldier->ubQuickItemSlot = ubItemSlot;

	if (UsingInventoryCostsAPSystem())
	{
		APTotalCost += GetInvMovementCost(&pSoldier->inv[ubItemSlot], ubItemSlot, HANDPOS);
		if (!EnoughPoints(pSoldier, APTotalCost, 0, TRUE))
			return;
	}

	if (!CanItemFitInPosition(pSoldier, &pSoldier->inv[ubItemSlot], HANDPOS, FALSE))
	{
		ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, TacticalStr[QUICK_ITEM_CANNOT_TAKE]);
		return;
	}

	// if item in main hand exists -> move it to second hand
	if (pSoldier->inv[HANDPOS].exists())
		HandleTBSwapHands();

	// move item to handpos
	if (UsingInventoryCostsAPSystem())
		DeductPoints(pSoldier, APTotalCost, 0);
	pSoldier->inv[ubItemSlot].MoveThisObjectTo(pSoldier->inv[HANDPOS], 1, pSoldier);

	// update interface
	fCharacterInfoPanelDirty = TRUE;
	fInterfacePanelDirty = DIRTYLEVEL2;
	pSoldier->HandleFlashLights();
}

INT32 InvItemType(UINT16 usItem)
{
	if (usItem == XRAY_DEVICE)
		return INV_ITEM_TYPE_XRAY;
	if (Item[usItem].firstaidkit)
		return INV_ITEM_TYPE_FIRSTAID;
	if (Item[usItem].usItemClass == IC_BLADE)
		return INV_ITEM_TYPE_MELEE;
	if (Item[usItem].usItemClass == IC_PUNCH && !HasItemFlag(usItem, TASER))
		return INV_ITEM_TYPE_HTH;
	if (HasItemFlag(usItem, HANDCUFFS))
		//if( Item[ usItem ].usItemClass == IC_MISC && Item[ usItem ].usItemFlag & HANDCUFFS )
		return INV_ITEM_TYPE_HANDCUFFS;
	//Item[ uiItem ].usSpotting
	if (Item[usItem].usItemClass == IC_MISC && Item[usItem].dayvisionrangebonus)
		return INV_ITEM_TYPE_BINOCULARS;
	if (HasItemFlag(usItem, TASER))
		return INV_ITEM_TYPE_TASER;
	if (Item[usItem].usItemClass == IC_GUN && !Item[usItem].twohanded && Weapon[Item[usItem].ubClassIndex].ubWeaponType <= GUN_SMG)
		return INV_ITEM_TYPE_SIDEARM;
	if (Item[usItem].usItemClass == IC_MISC && Item[usItem].metaldetector)
		return INV_ITEM_TYPE_METALDETECTOR;

	return INV_ITEM_TYPE_UNKNOWN;
}

void HandleTacticalDropItem(UINT8 ubSlot)
{
	SOLDIERTYPE* pSoldier;
	UINT16 APTotalCost = 0;

	if (gusSelectedSoldier != NOBODY)
		pSoldier = MercPtrs[gusSelectedSoldier];
	else
		return;

	if (pSoldier->inv[ubSlot].exists())
	{
		if (UsingInventoryCostsAPSystem())
		{
			APTotalCost += GetInvMovementCost(&pSoldier->inv[ubSlot], ubSlot, HANDPOS);
			APTotalCost += GetBasicAPsToPickupItem(pSoldier);
			if (!EnoughPoints(pSoldier, APTotalCost, 0, TRUE))
				return;
			DeductPoints(pSoldier, APTotalCost, 0);
		}

		SoldierDropItem(pSoldier, &pSoldier->inv[ubSlot]);
		DeleteObj(&(pSoldier->inv[ubSlot]));
	}
}

void HandleTacticalTakeItem(void)
{
	SOLDIERTYPE* pSoldier;

	if (gusSelectedSoldier != NOBODY)
		pSoldier = MercPtrs[gusSelectedSoldier];
	else
		return;

	if (gpItemPointer != NULL)
	{
		//not holding anything
		if (pSoldier->inv[HANDPOS].exists())
		{
			pSoldier->inv[HANDPOS].MoveThisObjectTo(gItemPointer);
			gpItemPointer = &gItemPointer;
		}
	}

	// update interface
	fCharacterInfoPanelDirty = TRUE;
	fInterfacePanelDirty = DIRTYLEVEL2;
	pSoldier->HandleFlashLights();

	// Set mouse
	if (gpItemPointer != NULL)
	{
		if (gpItemPointer->exists())
		{
			guiExternVo = GetInterfaceGraphicForItem(&(Item[gpItemPointer->usItem]));
			gusExternVoSubIndex = g_bUsePngItemImages ? 0 : Item[gpItemPointer->usItem].ubGraphicNum;

			MSYS_ChangeRegionCursor(&gMPanelRegion, EXTERN_CURSOR);
			MSYS_SetCurrentCursor(EXTERN_CURSOR);

			fMapInventoryItem = TRUE;
			fTeamPanelDirty = TRUE;
		}
	}
}

void HandleTacticalReload()
{
	SOLDIERTYPE* pSoldier;
	INT16 bAPs = 0;

	if (gusSelectedSoldier != NOBODY)
		pSoldier = MercPtrs[gusSelectedSoldier];
	else
		return;

	// Do we have the ammo to reload?
	// Check APs to reload...
	bAPs = GetAPsToAutoReload(pSoldier, false);

	if (EnoughPoints(pSoldier, bAPs, 0, TRUE))
	{
		// OK, we have some ammo we can reload.... reload now!
		if (!AutoReload(pSoldier, false))
		{
			// Do we say we could not reload gun...?
			pSoldier->DoMercBattleSound(BATTLE_SOUND_CURSE);
			//TacticalCharacterDialogue( pSoldier, QUOTE_OUT_OF_AMMO );
		}

		// ATE: Re-examine cursor info!
		gfUIForceReExamineCursorData = TRUE;
	}
}

void HandleTacticalTransformScope(void)
{
	UINT16 usItem;
	TransformInfoStruct* pTransformation;
	OBJECTTYPE* pObj;

	SOLDIERTYPE* pSoldier;
	if (!GetSoldier(&pSoldier, gusSelectedSoldier))
		return;

	if (!pSoldier->inv[HANDPOS].exists())
		return;

	// ATE: Don't do this if in a fire animation.....
	if (gAnimControl[pSoldier->usAnimState].uiFlags & ANIM_FIRE)
		return;

	// don't do this when EDB is active
	if (gpItemDescObject)
		return;

	usItem = pSoldier->inv[HANDPOS].usItem;
	//GetMouseMapPos(&usGridNo);

	// check attachments
	attachmentList::iterator iter;
	pObj = &(pSoldier->inv[HANDPOS]);

	// check all attachments, search for available transformations
	for (iter = (*pObj)[0]->attachments.begin(); iter != (*pObj)[0]->attachments.end(); ++iter)
	{
		if (iter->exists() && Item[iter->usItem].usItemClass == IC_MISC && Item[iter->usItem].attachmentclass & AC_SCOPE)
		{
			usItem = Item[iter->usItem].uiIndex;

			// check flashlight transformation
			if (FindScopeTransformation(usItem, &pTransformation) &&
				pTransformation->usResult[0] != 0 &&
				Item[usItem].scopemagfactor != Item[pTransformation->usResult[0]].scopemagfactor)
			{
				if (pTransformation->usAPCost > 0 && gTacticalStatus.uiFlags & INCOMBAT && gTacticalStatus.uiFlags & TURNBASED)
					ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, L"%s (%d AP)", pTransformation->szMenuRowText, pTransformation->usAPCost);
				else
					ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, pTransformation->szMenuRowText);

				// let's pretend we are calling this from EDB
				gpItemDescObject = pObj;
				gpItemDescOrigAttachmentObject = &(*iter);

				gpItemDescOrigAttachmentObject->TransformObject(pSoldier, 0, pTransformation, gpItemDescObject);

				// cleanup
				gpItemDescObject = NULL;
				gpItemDescOrigAttachmentObject = NULL;

				pSoldier->aiData.bShownAimTime = 0;
				DirtyMercPanelInterface(pSoldier, DIRTYLEVEL2);
				gfUIForceReExamineCursorData = TRUE;

				break;
			}
		}
	}
}

void HandleTacticalTransformLaser(void)
{
	UINT16 usItem;
	TransformInfoStruct* pTransformation;
	OBJECTTYPE* pObj;

	SOLDIERTYPE* pSoldier;
	if (!GetSoldier(&pSoldier, gusSelectedSoldier))
		return;

	if (!pSoldier->inv[HANDPOS].exists())
		return;

	// ATE: Don't do this if in a fire animation.....
	if (gAnimControl[pSoldier->usAnimState].uiFlags & ANIM_FIRE)
		return;

	// don't do this when EDB is active
	if (gpItemDescObject)
		return;

	usItem = pSoldier->inv[HANDPOS].usItem;

	// check attachments
	attachmentList::iterator iter;
	pObj = &(pSoldier->inv[HANDPOS]);

	// check all attachments, search for available transformations
	for (iter = (*pObj)[0]->attachments.begin(); iter != (*pObj)[0]->attachments.end(); ++iter)
	{
		if (iter->exists() && Item[iter->usItem].usItemClass == IC_MISC && Item[iter->usItem].attachmentclass & AC_LASER)
		{
			usItem = Item[iter->usItem].uiIndex;

			// check flashlight transformation
			if (FindLaserTransformation(usItem, &pTransformation) &&
				pTransformation->usResult[0] != 0 &&
				Item[usItem].bestlaserrange != Item[pTransformation->usResult[0]].bestlaserrange)
			{
				if (pTransformation->usAPCost > 0 && gTacticalStatus.uiFlags & INCOMBAT && gTacticalStatus.uiFlags & TURNBASED)
					ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, L"%s (%d AP)", pTransformation->szMenuRowText, pTransformation->usAPCost);
				else
					ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, pTransformation->szMenuRowText);

				// let's pretend we are calling this from EDB
				gpItemDescObject = pObj;
				gpItemDescOrigAttachmentObject = &(*iter);

				gpItemDescOrigAttachmentObject->TransformObject(pSoldier, 0, pTransformation, gpItemDescObject);

				// cleanup
				gpItemDescObject = NULL;
				gpItemDescOrigAttachmentObject = NULL;

				DirtyMercPanelInterface(pSoldier, DIRTYLEVEL2);
				gfUIForceReExamineCursorData = TRUE;

				break;
			}
		}
	}
}

void HandleTacticalTransformStock(void)
{
	UINT16 usItem;
	TransformInfoStruct* pTransformation;
	OBJECTTYPE* pObj;

	SOLDIERTYPE* pSoldier;
	if (!GetSoldier(&pSoldier, gusSelectedSoldier))
		return;

	if (!pSoldier->inv[HANDPOS].exists())
		return;

	// ATE: Don't do this if in a fire animation.....
	if (gAnimControl[pSoldier->usAnimState].uiFlags & ANIM_FIRE)
		return;

	// don't do this when EDB is active
	if (gpItemDescObject)
		return;

	usItem = pSoldier->inv[HANDPOS].usItem;

	// check if can transform item
	if (FindStockTransformation(usItem, &pTransformation))
	{
		if (pTransformation->usAPCost > 0 && (gTacticalStatus.uiFlags & INCOMBAT && gTacticalStatus.uiFlags & TURNBASED))
			ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, L"%s (%d AP)", pTransformation->szMenuRowText, pTransformation->usAPCost);
		else
			ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, pTransformation->szMenuRowText);

		// let's pretend we are calling this from EDB
		gpItemDescObject = &pSoldier->inv[HANDPOS];
		gpItemDescObject->TransformObject(pSoldier, 0, pTransformation, NULL);

		// cleanup
		gpItemDescObject = NULL;

		DirtyMercPanelInterface(pSoldier, DIRTYLEVEL2);
		gfUIForceReExamineCursorData = TRUE;

		return;
	}

	// check attachments
	attachmentList::iterator iter;
	pObj = &(pSoldier->inv[HANDPOS]);

	// check all attachments, search for available transformations
	for (iter = (*pObj)[0]->attachments.begin(); iter != (*pObj)[0]->attachments.end(); ++iter)
	{
		if (iter->exists() && Item[iter->usItem].usItemClass == IC_MISC && Item[iter->usItem].attachmentclass & AC_STOCK)
		{
			usItem = Item[iter->usItem].uiIndex;

			// check flashlight transformation
			if (FindStockTransformation(usItem, &pTransformation) &&
				pTransformation->usResult[0] != 0)
			{
				if (pTransformation->usAPCost > 0 && gTacticalStatus.uiFlags & INCOMBAT && gTacticalStatus.uiFlags & TURNBASED)
					ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, L"%s (%d AP)", pTransformation->szMenuRowText, pTransformation->usAPCost);
				else
					ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, pTransformation->szMenuRowText);

				// let's pretend we are calling this from EDB
				gpItemDescObject = pObj;
				gpItemDescOrigAttachmentObject = &(*iter);

				gpItemDescOrigAttachmentObject->TransformObject(pSoldier, 0, pTransformation, gpItemDescObject);

				// cleanup
				gpItemDescObject = NULL;
				gpItemDescOrigAttachmentObject = NULL;

				DirtyMercPanelInterface(pSoldier, DIRTYLEVEL2);
				gfUIForceReExamineCursorData = TRUE;

				return;
			}
		}
	}
}

void HandleTacticalTransformFlashlight(void)
{
	UINT16 usItem;
	TransformInfoStruct* pTransformation;
	OBJECTTYPE* pObj;

	SOLDIERTYPE* pSoldier;
	if (!GetSoldier(&pSoldier, gusSelectedSoldier))
		return;

	if (!pSoldier->inv[HANDPOS].exists())
		return;

	// ATE: Don't do this if in a fire animation.....
	if (gAnimControl[pSoldier->usAnimState].uiFlags & ANIM_FIRE)
		return;

	// don't do this when EDB is active
	if (gpItemDescObject)
		return;

	usItem = pSoldier->inv[HANDPOS].usItem;

	// first try a transformation of item
	if (FindFlashlightTransformation(usItem, &pTransformation))
	{
		if (pTransformation->usAPCost > 0 && gTacticalStatus.uiFlags & INCOMBAT && gTacticalStatus.uiFlags & TURNBASED)
			ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, L"%s (%d AP)", pTransformation->szMenuRowText, pTransformation->usAPCost);
		else
			ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, pTransformation->szMenuRowText);

		// let's pretend we are calling this from EDB
		gpItemDescObject = &pSoldier->inv[HANDPOS];

		gpItemDescObject->TransformObject(pSoldier, 0, pTransformation, NULL);

		// cleanup
		gpItemDescObject = NULL;

		DirtyMercPanelInterface(pSoldier, DIRTYLEVEL2);
		gfUIForceReExamineCursorData = TRUE;

		return;
	}

	// check attachments
	attachmentList::iterator iter;
	pObj = &(pSoldier->inv[HANDPOS]);

	// check all attachments, search for available transformations
	for (iter = (*pObj)[0]->attachments.begin(); iter != (*pObj)[0]->attachments.end(); ++iter)
	{
		if (iter->exists() && Item[iter->usItem].usItemClass == IC_MISC)
		{
			usItem = Item[iter->usItem].uiIndex;

			// check flashlight transformation
			if (FindFlashlightTransformation(usItem, &pTransformation))
			{
				if (pTransformation->usAPCost > 0 && gTacticalStatus.uiFlags & INCOMBAT && gTacticalStatus.uiFlags & TURNBASED)
					ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, L"%s (%d AP)", pTransformation->szMenuRowText, pTransformation->usAPCost);
				else
					ScreenMsg(FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, pTransformation->szMenuRowText);

				// let's pretend we are calling this from EDB
				gpItemDescObject = pObj;
				gpItemDescOrigAttachmentObject = &(*iter);

				gpItemDescOrigAttachmentObject->TransformObject(pSoldier, 0, pTransformation, gpItemDescObject);

				// cleanup
				gpItemDescObject = NULL;
				gpItemDescOrigAttachmentObject = NULL;

				DirtyMercPanelInterface(pSoldier, DIRTYLEVEL2);
				gfUIForceReExamineCursorData = TRUE;

				break;
			}
		}
	}
}

BOOLEAN FindLaserTransformation(UINT16 usItem, TransformInfoStruct** pTransformation)
{
	// find transformation
	for (INT32 x = 0; x < MAXITEMS + 1; x++)
	{
		if (Transform[x].usItem == (UINT16)-1)
		{
			break;
		}
		if (Transform[x].usItem == usItem &&
			Transform[x].usResult[0] != 0 &&
			Transform[x].usResult[0] != usItem &&
			Item[Transform[x].usResult[0]].usItemClass & IC_MISC &&
			Item[Transform[x].usResult[0]].attachmentclass & AC_LASER)
		{
			*pTransformation = &Transform[x];
			return TRUE;
		}
	}
	return FALSE;
}

BOOLEAN FindStockTransformation(UINT16 usItem, TransformInfoStruct** pTransformation)
{
	// find transformation
	for (INT32 x = 0; x < MAXITEMS + 1; x++)
	{
		if (Transform[x].usItem == (UINT16)-1)
		{
			break;
		}
		if (Transform[x].usItem == usItem &&
			Transform[x].usResult[0] != 0 &&
			Transform[x].usResult[0] != usItem &&
			(Item[Transform[x].usResult[0]].usItemClass == Item[usItem].usItemClass && Transform[x].usResult[0] != usItem && Item[Transform[x].usResult[0]].ItemSize != Item[usItem].ItemSize ||
				Item[Transform[x].usResult[0]].usItemClass & IC_MISC && Item[Transform[x].usResult[0]].attachmentclass & AC_STOCK))
		{
			*pTransformation = &Transform[x];
			return TRUE;
		}
	}
	return FALSE;
}

BOOLEAN FindFlashlightTransformation(UINT16 usItem, TransformInfoStruct** pTransformation)
{
	// find transformation
	for (INT32 x = 0; x < MAXITEMS + 1; x++)
	{
		if (Transform[x].usItem == (UINT16)-1)
		{
			break;
		}
		if (Transform[x].usItem == usItem &&
			Transform[x].usResult[0] != 0 &&
			Transform[x].usResult[0] != usItem &&
			Item[Transform[x].usResult[0]].usFlashLightRange != Item[usItem].usFlashLightRange)
		{
			*pTransformation = &Transform[x];
			return TRUE;
		}
	}
	return FALSE;
}

BOOLEAN FindScopeTransformation(UINT16 usItem, TransformInfoStruct** pTransformation)
{
	INT32 iFoundIndex;
	FLOAT scope;

	// search for higher magnification first
	iFoundIndex = MAXITEMS;
	scope = Item[usItem].scopemagfactor;
	for (INT32 x = 0; x < MAXITEMS + 1; x++)
	{
		if (Transform[x].usItem == (UINT16)-1)
		{
			break;
		}

		if (Transform[x].usItem == usItem &&
			Transform[x].usResult[0] != 0 &&
			Item[Transform[x].usResult[0]].usItemClass & IC_MISC &&
			Item[Transform[x].usResult[0]].attachmentclass & AC_SCOPE &&
			Item[Transform[x].usResult[0]].scopemagfactor > Item[usItem].scopemagfactor &&
			(iFoundIndex == MAXITEMS || Item[Transform[x].usResult[0]].scopemagfactor < scope))
		{
			scope = Item[Transform[x].usResult[0]].scopemagfactor;
			iFoundIndex = x;
		}
	}
	if (iFoundIndex != MAXITEMS)
	{
		*pTransformation = &Transform[iFoundIndex];
		return TRUE;
	}

	// search for lowest magnification
	iFoundIndex = MAXITEMS;
	scope = Item[usItem].scopemagfactor;
	for (INT32 x = 0; x < MAXITEMS + 1; x++)
	{
		if (Transform[x].usItem == (UINT16)-1)
		{
			break;
		}

		if (Transform[x].usItem == usItem &&
			Transform[x].usResult[0] != 0 &&
			Item[Transform[x].usResult[0]].usItemClass & IC_MISC &&
			Item[Transform[x].usResult[0]].attachmentclass & AC_SCOPE &&
			Item[Transform[x].usResult[0]].scopemagfactor < scope)
		{
			scope = Item[Transform[x].usResult[0]].scopemagfactor;
			iFoundIndex = x;
		}
	}
	if (iFoundIndex != MAXITEMS)
	{
		*pTransformation = &Transform[iFoundIndex];
		return TRUE;
	}

	// search for any transformation
	for (INT32 x = 0; x < MAXITEMS + 1; x++)
	{
		if (Transform[x].usItem == (UINT16)-1)
		{
			break;
		}

		if (Transform[x].usItem == usItem &&
			Transform[x].usResult[0] != 0 &&
			Item[Transform[x].usResult[0]].usItemClass & IC_MISC &&
			Item[Transform[x].usResult[0]].attachmentclass & AC_SCOPE)
		{
			*pTransformation = &Transform[x];
			return TRUE;
		}
	}

	return FALSE;
}

void HandleTBSkillsMenu(void)
{
	// Flugente: trait skill selection menu.
	INT32 usMapPos;
	if (GetMouseMapPos(&usMapPos))
	{
		TraitsMenu(usMapPos);
	}
	else if (gusSelectedSoldier != NOBODY && MercPtrs[gusSelectedSoldier] && !TileIsOutOfBounds(MercPtrs[gusSelectedSoldier]->sGridNo))
	{
		LocateGridNo(MercPtrs[gusSelectedSoldier]->sGridNo);
		TraitsMenu(MercPtrs[gusSelectedSoldier]->sGridNo);
	}
}

void CreateCivillian(INT8 civBodyType)
{
	SOLDIERCREATE_STRUCT		MercCreateStruct;
	INT32 usMapPos = gusMapPos;
	//static						INT8 ubBodyType = FATCIV;

	// FATCIV = 11 .... CRIPPLECIV = 17 total civ body type : 7

	INT8 ubBodyType = civBodyType;
	if (ubBodyType == NULL)
		ubBodyType = 11 + Random(7);
	else if (ubBodyType == -1) // this option always random
	{
		ubBodyType = 11 + Random(7);
		gCivilianBodyType = -1; // keep random position
	}

	MercCreateStruct.ubProfile = NO_PROFILE;
	MercCreateStruct.sSectorX = gWorldSectorX;
	MercCreateStruct.sSectorY = gWorldSectorY;
	MercCreateStruct.bSectorZ = gbWorldSectorZ;
	MercCreateStruct.ubBodyType = ubBodyType;
	MercCreateStruct.ubDirection = Random(NUM_WORLD_DIRECTIONS);

	++ubBodyType;

	if (ubBodyType > KIDCIV)
	{
		ubBodyType = FATCIV;
	}

	MercCreateStruct.bTeam = CIV_TEAM;
	MercCreateStruct.sInsertionGridNo = usMapPos;
	RandomizeNewSoldierStats(&MercCreateStruct);

	INT8 iubID;
	SOLDIERTYPE* pEntity = TacticalCreateSoldier(&MercCreateStruct, (UINT8*)&iubID);
	if (pEntity)
	{
		AddSoldierToSector(iubID);

		DebugMsg(TOPIC_CREATE_ENTITY, DBG_LEVEL_3,
			String("CreateCivillian type: %d, ubID: %d, gridNo: %d", ubBodyType, pEntity->ubID, gusMapPos)
		);

		// So we can see them!
		AllTeamsLookForAll(NO_INTERRUPTS);
	}
}

void HandleSelectCreateCivilian()
{
	if (GetMouseMapPos(&gusMapPos))
	{
		wcscpy(gzUserDefinedButton[0], L"FATCIV");		// ubExitValue equal with 1
		wcscpy(gzUserDefinedButton[1], L"MANCIV");
		wcscpy(gzUserDefinedButton[2], L"MINICIV");
		wcscpy(gzUserDefinedButton[3], L"DRESSCIV");
		wcscpy(gzUserDefinedButton[4], L"HATKIDCIV");
		wcscpy(gzUserDefinedButton[5], L"KIDCIV");
		wcscpy(gzUserDefinedButton[6], L"CRIPPLECIV");
		wcscpy(gzUserDefinedButton[7], L"-RANDOM-");			// ubExitValue equal with 8

		DoMessageBox(MSG_BOX_BASIC_MEDIUM_BUTTONS, L"Select Type of Civilian", GAME_SCREEN,
			MSG_BOX_FLAG_GENERIC_EIGHT_BUTTONS, SelectCreateCivilianCallback, NULL);
	}
}

void SelectCreateCivilianCallback(UINT8 ubExitValue)
{
	if (ubExitValue != NULL)
	{
		if (ubExitValue >= 1 && ubExitValue <= 7)
			gCivilianBodyType = 10 + ubExitValue;
		else // pick random
			gCivilianBodyType = -1;
		CreateCivillian(gCivilianBodyType);
	}
}


//***************************************************************************
// JADOL -- Cheat Create New Bad Merc with Option
void CreateBadMerc(UINT32* puiNewEvent, bool hasSelected)
{
	//if (!hasSelected)
	//{
	//	if (*puiNewEvent != NULL)
	//		*puiNewEvent = I_NEW_BADMERC;
	//	return;
	//}

	SOLDIERTYPE* pSoldier = NULL;
	INT32 usMapPos = gusMapPos;

	if (!hasSelected)
		GetMouseMapPos(&usMapPos);

	// Are we an OK dest?
	if (!IsLocationSittable(usMapPos, 0))
	{
		return;
	}

	if ((gBadMercBodyType < 1 || gBadMercBodyType > 7))
		gBadMercBodyType = 3; // default is ArmyTroop with red shirt


	switch (gBadMercBodyType)
	{
	case 1: pSoldier = TacticalCreateNewbie(); break;
	case 2: pSoldier = TacticalCreateAdministrator(); break;
	case 3: pSoldier = TacticalCreateArmyTroop(); break;
	case 4: pSoldier = TacticalCreateEliteEnemy(); break;
	case 5: pSoldier = TacticalCreateEnemyTank(); break;
	case 6: pSoldier = TacticalCreateEnemyJeep(); break;
	case 7: pSoldier = TacticalCreateEnemyRobot(); break;
	}

	DebugMsg(TOPIC_CREATE_ENTITY, DBG_LEVEL_3,
		String("CreateBadMerc type: %d, ubID: %d, gridNo: %d", gBadMercBodyType, pSoldier->ubID, gusMapPos)
	);

	//Add soldier strategic info, so it doesn't break the counters!
	if (pSoldier)
	{
		if (!gbWorldSectorZ)
		{
			SECTORINFO* pSector = &SectorInfo[SECTOR(gWorldSectorX, gWorldSectorY)];
			switch (pSoldier->ubSoldierClass)
			{
			case SOLDIER_CLASS_NONE:					pSector->ubNumAdmins++; pSector->ubAdminsInBattle++; break;
			case SOLDIER_CLASS_ADMINISTRATOR:			pSector->ubNumAdmins++; pSector->ubAdminsInBattle++; break;
			case SOLDIER_CLASS_ARMY:					pSector->ubNumTroops++; pSector->ubTroopsInBattle++; break;
			case SOLDIER_CLASS_ELITE:					pSector->ubNumElites++; pSector->ubElitesInBattle++; break;
			case SOLDIER_CLASS_TANK:					pSector->ubNumTanks++;	pSector->ubTanksInBattle++;  break;
			case SOLDIER_CLASS_JEEP:					pSector->ubNumJeeps++;	pSector->ubJeepsInBattle++; break;
			case SOLDIER_CLASS_ROBOT:					pSector->ubNumRobots++; pSector->ubRobotsInBattle++; break;
			}
		}
		else
		{
			UNDERGROUND_SECTORINFO* pSector = FindUnderGroundSector(gWorldSectorX, gWorldSectorY, gbWorldSectorZ);
			if (pSector)
			{
				switch (pSoldier->ubSoldierClass)
				{
				case SOLDIER_CLASS_NONE:					pSector->ubNumAdmins++; pSector->ubAdminsInBattle++; break;
				case SOLDIER_CLASS_ADMINISTRATOR:			pSector->ubNumAdmins++; pSector->ubAdminsInBattle++; break;
				case SOLDIER_CLASS_ARMY:					pSector->ubNumTroops++; pSector->ubTroopsInBattle++; break;
				case SOLDIER_CLASS_ELITE:					pSector->ubNumElites++; pSector->ubElitesInBattle++; break;
				case SOLDIER_CLASS_TANK:					pSector->ubNumTanks++;	pSector->ubTanksInBattle++; break;
				case SOLDIER_CLASS_JEEP:					pSector->ubNumJeeps++;	pSector->ubJeepsInBattle++; break;
				case SOLDIER_CLASS_ROBOT:					pSector->ubNumRobots++; pSector->ubRobotsInBattle++; break;
				}
			}
		}

		// sevenfm
		if (IS_MERC_BODY_TYPE(pSoldier))
		{
			if (gsInterfaceLevel)
				pSoldier->SetSoldierHeight(WALL_HEIGHT);
			else
				pSoldier->SetSoldierHeight(0);
		}

		pSoldier->ubStrategicInsertionCode = INSERTION_CODE_GRIDNO;
		pSoldier->usStrategicInsertionData = usMapPos;
		UpdateMercInSector(pSoldier, gWorldSectorX, gWorldSectorY, gbWorldSectorZ);
		AllTeamsLookForAll(NO_INTERRUPTS);
	}

}

void HandleSelectBadMercType()
{
	if (GetMouseMapPos(&gusMapPos))
	{
		wcscpy(gzUserDefinedButton[0], L"Newbie Troop");		// ubExitValue equal with 1
		wcscpy(gzUserDefinedButton[1], L"Administrator");
		wcscpy(gzUserDefinedButton[2], L"Army Troop");
		wcscpy(gzUserDefinedButton[3], L"Elite Troop");
		wcscpy(gzUserDefinedButton[4], L"Tank");
		wcscpy(gzUserDefinedButton[5], L"Jeep");
		wcscpy(gzUserDefinedButton[6], L"Robot");
		wcscpy(gzUserDefinedButton[7], L"-Unused-");			// ubExitValue equal with 8

		DoMessageBox(MSG_BOX_BASIC_MEDIUM_BUTTONS, L"Select Type of Enemy", GAME_SCREEN,
			MSG_BOX_FLAG_GENERIC_EIGHT_BUTTONS, SelectBadMercTypeCallback, NULL);
	}
}

void SelectBadMercTypeCallback(UINT8 ubExitValue)
{
	if (ubExitValue != NULL)
	{
		if (ubExitValue >= 1 && ubExitValue <= 7) {
			gBadMercBodyType = ubExitValue;
			CreateBadMerc(NULL, true);
		}
	}
}

//--
//***************************************************************************

BOOLEAN CheckAutoBandage(void)
{
	if (!(gTacticalStatus.uiFlags & INCOMBAT) && NumEnemyInSector() == 0 && DialogueQueueIsEmpty())
	{
		return TRUE;
	}

	return FALSE;
}
