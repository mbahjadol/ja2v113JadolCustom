/*
* this header is created because "Turn Based GKI_Handler" is need some of function
* inside of "Turn Based Input.cpp" so they can call it
*/

void HandleTalkingMenuKeys(InputAtom* pInputEvent, UINT32* puiNewEvent);
void HandleMenuKeys(InputAtom* pInputEvent, UINT32* puiNewEvent);
void HandleItemMenuKeys(InputAtom* pInputEvent, UINT32* puiNewEvent);
void HandleOpenDoorMenuKeys(InputAtom* pInputEvent, UINT32* puiNewEvent);
void HandleSectorExitMenuKeys(InputAtom* pInputEvent, UINT32* puiNewEvent);
void HandleStanceChangeFromUIKeys(UINT8 ubAnimHeight);

BOOLEAN ConfirmActionCancel(INT32 usMapPos, INT32 usOldMapPos);

//Little functions called by keyboard input
void SwapGoggles(SOLDIERTYPE* pTeamSoldier);
// HEADROCK HAM B2.8: Function to switch team's goggles uniformly
void SwapGogglesUniformly(SOLDIERTYPE* pTeamSoldier, BOOLEAN fToNightVision);
void SeperateItems();
void StackAndSort(BOOLEAN fRestrictToAmmo);
void MakeSelectedSoldierTired();
void ToggleRealTime(UINT32* puiNewEvent);
void ToggleViewAllMercs();
void ToggleViewAllItems();
void TestExplosion();
void CycleSelectedMercsItem();
void ToggleWireFrame();
void RefreshSoldier();
void ChangeSoldiersBodyType(UINT8 ubBodyType, BOOLEAN fCreateNewPalette);
void TeleportSelectedSoldier();
void ToggleTurnMode();// ary-05/05/2009 : add forced turn mode
void ToggleTreeTops();
void ToggleZBuffer();
void TogglePlanningMode();
void SetBurstMode();
void SetScopeMode(INT32 usMapPos);
void ObliterateSector();
void RandomizeMercProfile();
void ToggleCliffDebug();
void ToggleRealTimeConfirm();
void TestMeanWhile(INT32 iID);
void ChangeCurrentSquad(INT32 iSquad);
void HandleSelectMercSlot(UINT8 ubPanelSlot, INT8 bCode);
void EscapeUILock();

#ifdef JA2BETAVERSION
void ToggleMapEdgepoints();
#endif
#ifdef JA2TESTVERSION
void ToggleMercsNeverQuit();
#endif
#ifdef JA2TESTVERSION
void DumpSectorDifficultyInfo(void);
#endif

void	QueryTBMButton(UINT32* puiNewEvent);
void	QueryTBWheel(UINT32* puiNewEvent);
void	QueryTBX1Button(UINT32* puiNewEvent);
void	QueryTBX2Button(UINT32* puiNewEvent);

//// silversurfer: added for merc portrait swapping in tactical
void	SwapMercPortraits(SOLDIERTYPE* pSoldier, INT8 bDirection);

// sevenfm: new mouse commands
void HandleAltMouseTBWheel(void);
void HandleAltMouseTBMButton(UINT32* puiNewEvent);
void HandleAltMouseTBX1Button(UINT32* puiNewEvent);
void HandleAltMouseTBX2Button(UINT32* puiNewEvent);

// sevenfm: original mouse commands functionality
void HandleMouseTBWheel(void);
void HandleMouseTBMButton(UINT32* puiNewEvent);
void HandleMouseTBX1Button(UINT32* puiNewEvent);
void HandleMouseTBX2Button(UINT32* puiNewEvent);

// sevenfm: check availability for actions
BOOLEAN CheckAutoBandage(void);

// sevenfm: common functionality
void HandleStealthChangeFromUIKeys();
void HandleTBSelectAllMercs(void);
void HandleTBToggleStealthAll(void);
void HandleTBToggleFireMode(void);
void HandleTBJumpThroughWindow(void);
void HandleTBJump(void);
void HandleTBLook(UINT32* puiNewEvent);
void HandleTBSelectAllMercs(void);
void HandleTBCycleThroughKnownEnemies(void);
void HandleTBCycleThroughKnownEnemiesBackward(void);
void HandleTBCycleThroughVisibleEnemies(void);
void HandleTBCycleThroughVisibleEnemiesBackward(void);
void HandleTBLocateSoldier(void);
void HandleTBChangeLevel(void);
void HandleTBSwapHands(void);
void HandleTBSwapGunsling(void);
void HandleTBSwapKnife(void);
void HandleTBSwapSidearm(void);
void HandleTBSwapGoogles(void);
void HandleTBToggleFormation(void);
void HandleTBEnterTurnbased(void);
void HandleTBToggleSneak(void);
void HandleTBToggleStealth(void);
void HandleTBReload(void);
void HandleTBReloadAll(void);
void HandleTBShowCover(void);
void HandleTBShowMines(void);
void HandleTBShowLOS(void);
void HandleTBToggleTrapNetworkView(void);
void HandleTBGotoHigherStance(void);
void HandleTBGotoLowerStance(void);
void HandleTBLocateNextMerc(void);
void HandleTBLocatePrevMerc(void);
void HandleTBLevelDown(void);
void HandleTBLevelUp(void);
void HandleTBBackpacks(void);
void HandleTBDropBackpacks(void);
void HandleTBPickUpBackpacks(void);
void HandleTBSoldierRun(void);
void HandleTacticalReload(void);
void HandleTacticalTakeItem(void);
void HandleTacticalDropItem(UINT8 ubSlot);
void HandleTacticalTakeInvItem(INT32 iType);
void HandleTacticalStoreInvItem(void);
INT32 InvItemType(UINT16 usItem);
void HandleTacticalMoveItems(void);
void HandleTacticalAmmoCrates(UINT8 magType);
void HandleTacticalTransformItem(void);
void HandleTacticalTransformFlashlight(void);
void HandleTacticalTransformLaser(void);
void HandleTacticalTransformStock(void);
void HandleTacticalTransformScope(void);
BOOLEAN FindTransformation(UINT16 usItem, TransformInfoStruct** pTransformation, BOOLEAN fTactical = FALSE);
BOOLEAN FindLaserTransformation(UINT16 usItem, TransformInfoStruct** pTransformation);
BOOLEAN FindStockTransformation(UINT16 usItem, TransformInfoStruct** pTransformation);
BOOLEAN FindFlashlightTransformation(UINT16 usItem, TransformInfoStruct** pTransformation);
BOOLEAN FindScopeTransformation(UINT16 usItem, TransformInfoStruct** pTransformation);

// silversurfer: added for merc portrait swapping in tactical
void HandleTBSelectAllMercs(void);

BOOLEAN HandleUIReloading(SOLDIERTYPE* pSoldier);



// Create Handler -- 
void CreateRandomItem();
void CreateCow();
void CreateBloodCat();
void CreatePlayerControlledCow();
void CreatePlayerControlledMonster();
void CreateExplosion(UINT16 usItemExplosion, INT32 gridNo = NULL);
void CheatCreateItem();
void CreateBadMerc(UINT32* puiNewEvent, bool hasSelected = false);
void CreateCivillian(INT8 civBodyType = NULL);

// Selection Menu Handler --
void CheatSelectExplosion();
void CheatSelectCreateMonster();
void HandleSelectBadMercType();
void HandleSelectCreateCivilian();
void HandleTacticalInventoryMenu(void);
void HandleTacticalCoverMenu(void);
void HandleTBSkillsMenu(void);

// Callbacks --
void SelectCreateMonsterCallback(UINT8 ubExitValue);
void CheatSelectExplosionCallBack(UINT8 ubResult);
void MercCreationCallBack(UINT8 ubResult);
void ItemCreationCallBack(UINT8 ubResult);
void TacticalInventoryMessageBoxCallBack(UINT8 ubExitValue);
void FortificationSettingCallBack(UINT8 ubExitValue);
void TacticalCoverMessageBoxCallBack(UINT8 ubExitValue);
void ActivateCheatsMessageBoxCallBack(UINT8 ubExitValue);
void SelectBadMercTypeCallback(UINT8 ubExitValue);
void SelectCreateCivilianCallback(UINT8 ubExitValue);

