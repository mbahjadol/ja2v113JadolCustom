#ifndef __ANIMATION_CONTROL_H
#define __ANIMATION_CONTROL_H

// Header file for merc animation control
#include "Soldier Control.h"
#include "Animation Data.h"

// Defines
// #######################################################
#define MAX_ANIMATIONS									400 //!!!!!ddd added 30 new animations // SANDRO - added 50 more
#define MAX_FRAMES_PER_ANIM								100
#define	MAX_RANDOM_ANIMS_PER_BODYTYPE					10

#define	RANDOM_ANIM_NOTHINGINHAND						0
#define	RANDOM_ANIM_RIFLEINHAND							1
#define	RANDOM_ANIM_IRRELEVENTINHAND					2


#define	RANDOM_ANIM_SOUND								250

#define	RANDOM_ANIM_CASUAL								0x01
#define	RANDOM_ANIM_SECONDBIGMERC						0x02
#define	RANDOM_ANIM_FIRSTBIGMERC						0x04
#define	RANDOM_ANIM_INJURED								0x08
#define	RANDOM_ANIM_DRUNK								0x10
#define	RANDOM_ANIM_LOOKAROUND							0x20
#define	RANDOM_ANIM_SHOWOFF								0x40


#define	INJURED_CHANGE_THREASHOLD						30


#define USESTATS										0
#define	FAST_TURN_ANIM_SPEED							30

#define	INVALID_ANIMATION_SURFACE						32000

// FLAG DEFINES
#define	ANIM_IGNORE_AUTOSTANCE							0x00000001
#define	ANIM_OK_CHARGE_AP_FOR_TURN						0x00000002
#define ANIM_STATIONARY									0x00000004
#define ANIM_MOVING										0x00000008
#define ANIM_TURNING									0x00000010
#define ANIM_FASTTURN									0x00000020
#define	ANIM_FIREREADY									0x00000040
#define	ANIM_NONINTERRUPT								0x00000080
#define ANIM_HITFINISH									0x00000100
#define ANIM_HITSTART									0x00000200
#define ANIM_HITWHENDOWN								0x00000400
#define ANIM_NOSHOW_MARKER								0x00000800
#define ANIM_NOMOVE_MARKER								0x00001000
#define ANIM_NORESTART									0x00002000
#define ANIM_HITSTOP									0x00004000
#define ANIM_SPECIALMOVE								0x00008000
#define ANIM_MERCIDLE									0x00010000
#define ANIM_STANCECHANGEANIM							0x00020000
#define	ANIM_LOWER_WEAPON								0x00040000
#define	ANIM_RAISE_WEAPON								0x00080000
#define	ANIM_NOCHANGE_WEAPON							0x00100000
#define	ANIM_NOCHANGE_PENDINGCOUNT						0x00200000
// I'm commandeering the effort flags.	I do not expect to see multiple efforts for the same tasks, so I'm turning them into a 2-bit
// level instead.	So there :P
#define	ANIM_NO_EFFORT									0x00000000
#define	ANIM_MIN_EFFORT									0x00400000
#define	ANIM_LIGHT_EFFORT								0x00800000
#define	ANIM_MODERATE_EFFORT							0x00C00000

// Return a number between 0 and 4 to indicate effort.	4 means variable
#define EFFORT(flags) (((flags) & ANIM_VARIABLE_EFFORT) ? 4 : ((flags) & 0x00C00000) >> 22)

// Now I have room for a new flag.	And there's still room for one more!
#define ANIM_ATTACK										0x01000000
#define ANIM_FREEFORUSE									0x02000000

#define	ANIM_RT_NONINTERRUPT							0x04000000
#define	ANIM_VARIABLE_EFFORT							0x08000000
#define	ANIM_UPDATEMOVEMENTMODE							0x10000000
#define	ANIM_FIRE										0x20000000
#define ANIM_BREATH										0x40000000
// SANDRO - this flag is not assigned to any animation, so I am taking it for the hip fire feature
//#define ANIM_IGNOREHITFINISH							0x80000000
#define ANIM_ALT_WEAPON_HOLDING							0x80000000

//ANIMATION HEIGHT VALUES
#define ANIM_STAND										6
#define ANIM_CROUCH										3
#define ANIM_PRONE										1

#define INVALID_ANIMATION								0xFFF0
#define FOUND_INVALID_ANIMATION							0xFFF1

#define MAX_ANIM_STR_SIZE								35 //30 1 byte overflow! (jonathanl)



// Enumerations
// #######################################################

// STRUCTURES
// ###################################################################

typedef struct
{
	CHAR8			zAnimStr[ MAX_ANIM_STR_SIZE ];
	INT16			sAP;
	INT16			sSpeed;
	FLOAT			dMovementChange;	
	UINT32			uiFlags;
	UINT8			ubHeight;
	UINT8			ubEndHeight;
	INT8			bProfile;

} ANIMCONTROLTYPE;


typedef struct
{
	INT16			sSpeed;
	FLOAT			dMovementChange;

} ANI_SPEED_DEF;


typedef struct
{
	UINT8			ubHandRestriction;
	INT16			sAnimID;
	UINT8			ubStartRoll;
	UINT8			ubEndRoll;
	UINT8			ubFlags;
	UINT8			ubAnimHeight;
	CHAR8			zSoundFile[ 64 ];

} RANDOM_ANI_DEF;



// Enumeration of animation states
enum AnimationStates
{
	WALKING = 0,
	STANDING,
	KNEEL_DOWN,
	CROUCHING,
	KNEEL_UP,
	SWATTING,
	RUNNING,
	PRONE_DOWN,
	CRAWLING,
	PRONE_UP,
	PRONE,
	READY_RIFLE_STAND,
	AIM_RIFLE_STAND,
	SHOOT_RIFLE_STAND,
	END_RIFLE_STAND,
	START_SWAT,
	END_SWAT,
	FLYBACK_HIT,
	READY_RIFLE_PRONE,
	AIM_RIFLE_PRONE,
	SHOOT_RIFLE_PRONE,
	END_RIFLE_PRONE,
	FALLBACK_DEATHTWICH,
	GENERIC_HIT_STAND,
	FLYBACK_HIT_BLOOD_STAND,
	FLYBACK_HIT_DEATH,
	READY_RIFLE_CROUCH,
	AIM_RIFLE_CROUCH,
	SHOOT_RIFLE_CROUCH,
	END_RIFLE_CROUCH,
	FALLBACK_HIT_STAND,
	ROLLOVER,
	CLIMBUPROOF,
	FALLOFF,
	GETUP_FROM_ROLLOVER,
	CLIMBDOWNROOF,
	FALLFORWARD_ROOF,
	GENERIC_HIT_DEATHTWITCHNB,
	GENERIC_HIT_DEATHTWITCHB,
	FALLBACK_HIT_DEATHTWITCHNB,
	FALLBACK_HIT_DEATHTWITCHB,
	GENERIC_HIT_DEATH,
	FALLBACK_HIT_DEATH,
	GENERIC_HIT_CROUCH,
	STANDING_BURST,
	STANDING_BURST_HIT,
	FALLFORWARD_FROMHIT_STAND,
	FALLFORWARD_FROMHIT_CROUCH,
	ENDFALLFORWARD_FROMHIT_CROUCH,
	GENERIC_HIT_PRONE,
	PRONE_HIT_DEATH,
	PRONE_LAY_FROMHIT,
	PRONE_HIT_DEATHTWITCHNB,
	PRONE_HIT_DEATHTWITCHB,

	ADULTMONSTER_BREATHING,
	ADULTMONSTER_WALKING,
	ADULTMONSTER_ATTACKING,

	FLYBACK_HITDEATH_STOP,
	FALLFORWARD_HITDEATH_STOP,
	FALLBACK_HITDEATH_STOP,
	PRONE_HITDEATH_STOP,

	FLYBACKHIT_STOP,
	FALLBACKHIT_STOP,
	FALLOFF_STOP,
	FALLOFF_FORWARD_STOP,
	STAND_FALLFORWARD_STOP,
	PRONE_LAYFROMHIT_STOP,

	HOPFENCE,

	ADULTMONSTER_HIT,
	ADULTMONSTER_DYING,
	ADULTMONSTER_DYING_STOP,

	PUNCH_BREATH,
	PUNCH,
	NOTHING_STAND,

	JFK_HITDEATH,
	JFK_HITDEATH_STOP,
	JFK_HITDEATH_TWITCHB,

	FIRE_STAND_BURST_SPREAD,

	FALLOFF_DEATH,
	FALLOFF_DEATH_STOP,
	FALLOFF_TWITCHB,
	FALLOFF_TWITCHNB,

	FALLOFF_FORWARD_DEATH,
	FALLOFF_FORWARD_DEATH_STOP,
	FALLOFF_FORWARD_TWITCHB,
	FALLOFF_FORWARD_TWITCHNB,

	OPEN_DOOR,
	OPEN_STRUCT,

	PICKUP_ITEM,
	DROP_ITEM,

	SLICE,
	STAB, 
	CROUCH_STAB,

	START_AID,
	GIVING_AID,
	END_AID,

	DODGE_ONE,

	FATCIV_ASS_SCRATCH,

	READY_DUAL_STAND,
	AIM_DUAL_STAND,
	SHOOT_DUAL_STAND,
	END_DUAL_STAND,

	RAISE_RIFLE,
	LOWER_RIFLE,

	BODYEXPLODING,

	THROW_ITEM,
	LOB_ITEM,

	QUEEN_MONSTER_BREATHING,

	CROUCHED_BURST,
	PRONE_BURST,

	NOTUSEDANIM1,

	BIGBUY_FLEX,
	BIGBUY_STRECH,
	BIGBUY_SHOEDUST,
	BIGBUY_HEADTURN,

	MINIGIRL_STOCKING,

	GIVE_ITEM, // 116

	CLIMB_CLIFF, 

	COW_EATING,
	COW_HIT,
	COW_DYING,
	COW_DYING_STOP,

	WATER_HIT,
	WATER_DIE,
	WATER_DIE_STOP,

	CROW_WALK,
	CROW_TAKEOFF,
	CROW_LAND,
	CROW_FLY,
	CROW_EAT,

	HELIDROP,

	FEM_CLEAN,
	FEM_KICKSN,
	FEM_LOOK,
	FEM_WIPE,

	REG_SQUISH,
	REG_PULL,
	REG_SPIT,

	HATKID_YOYO,
	KID_ARMPIT,

	MONSTER_CLOSE_ATTACK,
	MONSTER_SPIT_ATTACK,
	MONSTER_BEGIN_EATTING_FLESH,
	MONSTER_EATTING_FLESH,
	MONSTER_END_EATTING_FLESH,

	BLOODCAT_RUN,
	BLOODCAT_STARTREADY,
	BLOODCAT_READY,
	BLOODCAT_ENDREADY,
	BLOODCAT_HIT,
	BLOODCAT_DYING,
	BLOODCAT_DYING_STOP,
	BLOODCAT_SWIPE,
	
	NINJA_GOTOBREATH,
	NINJA_BREATH,
	NINJA_LOWKICK,
	NINJA_PUNCH,
	NINJA_SPINKICK,

	END_OPEN_DOOR,
	END_OPEN_LOCKED_DOOR,

	KICK_DOOR,

	CLOSE_DOOR,

	RIFLE_STAND_HIT,

	DEEP_WATER_TRED,
	DEEP_WATER_SWIM,
	DEEP_WATER_HIT,
	DEEP_WATER_DIE,
	DEEP_WATER_DIE_STOPPING,
	DEEP_WATER_DIE_STOP,

	LOW_TO_DEEP_WATER,
	DEEP_TO_LOW_WATER,

	GOTO_SLEEP,
	SLEEPING,
	WKAEUP_FROM_SLEEP,

	FIRE_LOW_STAND,
	FIRE_BURST_LOW_STAND,

	LARVAE_BREATH,
	LARVAE_HIT,
	LARVAE_DIE,
	LARVAE_DIE_STOP,
	LARVAE_WALK,

	INFANT_HIT,
	INFANT_DIE,
	INFANT_DIE_STOP,
	INFANT_ATTACK,
	INFANT_BEGIN_EATTING_FLESH,
	INFANT_EATTING_FLESH,
	INFANT_END_EATTING_FLESH,

	MONSTER_UP,
	MONSTER_JUMP,

	STANDING_SHOOT_UNJAM,
	CROUCH_SHOOT_UNJAM,
	PRONE_SHOOT_UNJAM,
	STANDING_SHOOT_DWEL_UNJAM,
	STANDING_SHOOT_LOW_UNJAM,

	READY_DUAL_CROUCH,
	AIM_DUAL_CROUCH,
	SHOOT_DUAL_CROUCH,
	END_DUAL_CROUCH,
	CROUCH_SHOOT_DWEL_UNJAM,
	
	ADJACENT_GET_ITEM,

	CUTTING_FENCE,

	CRIPPLE_BEG,
	CRIPPLE_HIT,
	CRIPPLE_DIE,
	CRIPPLE_DIE_STOP,
	CRIPPLE_DIE_FLYBACK,
	CRIPPLE_DIE_FLYBACK_STOP,
	CRIPPLE_KICKOUT,

	FROM_INJURED_TRANSITION,

	THROW_KNIFE,
	KNIFE_BREATH,
	KNIFE_GOTOBREATH,
	KNIFE_ENDBREATH,

	ROBOTNW_HIT,
	ROBOTNW_DIE,
	ROBOTNW_DIE_STOP,

	CATCH_STANDING,
	CATCH_CROUCHED,

	PLANT_BOMB,
	USE_REMOTE,

	START_COWER,
	COWERING,
	END_COWER,

	STEAL_ITEM,

	SHOOT_ROCKET,

	CIV_DIE2,

	SHOOT_MORTAR,

	CROW_DIE,

	SIDE_STEP,
	WALK_BACKWARDS,
	BEGIN_OPENSTRUCT,
	END_OPENSTRUCT,
	END_OPENSTRUCT_LOCKED,

	PUNCH_LOW,
	PISTOL_SHOOT_LOW,

	DECAPITATE,

	BLOODCAT_BITE_ANIM,

	BIGMERC_IDLE_NECK,
	BIGMERC_CROUCH_TRANS_INTO,
	BIGMERC_CROUCH_TRANS_OUTOF,

	GOTO_PATIENT,
	BEING_PATIENT,
	GOTO_DOCTOR,
	BEING_DOCTOR,
	END_DOCTOR,
	GOTO_REPAIRMAN,
	BEING_REPAIRMAN,
	END_REPAIRMAN,

	FALL_INTO_PIT,

	ROBOT_WALK,
	ROBOT_SHOOT,

	QUEEN_HIT,
	QUEEN_DIE,
	QUEEN_DIE_STOP,
	QUEEN_INTO_READY,
	QUEEN_READY,
	QUEEN_END_READY,
	QUEEN_CALL,
	QUEEN_SPIT,
	QUEEN_SWIPE,

	RELOAD_ROBOT,

	END_CATCH,
	END_CROUCH_CATCH,

	AI_RADIO,
	AI_CR_RADIO,

	TANK_SHOOT,
	TANK_BURST,

	QUEEN_SLAP,
	SLAP_HIT,

	TAKE_BLOOD_FROM_CORPSE,

	VEHICLE_DIE,

	QUEEN_FRUSTRATED_SLAP,

	CHARIOTS_OF_FIRE,
	
	AI_PULL_SWITCH,

	MONSTER_MELT,

	MERC_HURT_IDLE_ANIM,
	END_HURT_WALKING,

	PASS_OBJECT,
	DROP_ADJACENT_OBJECT,

	READY_DUAL_PRONE,
	AIM_DUAL_PRONE,
	SHOOT_DUAL_PRONE,
	END_DUAL_PRONE,
	PRONE_SHOOT_DWEL_UNJAM,

	PICK_LOCK,

	OPEN_DOOR_CROUCHED,
	BEGIN_OPENSTRUCT_CROUCHED,
	CLOSE_DOOR_CROUCHED,
	OPEN_STRUCT_CROUCHED,
	END_OPEN_DOOR_CROUCHED,
	END_OPENSTRUCT_CROUCHED,
	END_OPEN_LOCKED_DOOR_CROUCHED,
	END_OPENSTRUCT_LOCKED_CROUCHED,

	DRUNK_IDLE,
	CROWBAR_ATTACK,

	CIV_COWER_HIT,
	BLOODCAT_WALK_BACKWARDS,
	MONSTER_WALK_BACKWARDS,
	KID_SKIPPING,
	ROBOT_BURST_SHOOT,
	ATTACH_CAN_TO_STRING,
	SWAT_BACKWARDS,
	JUMP_OVER_BLOCKING_PERSON,
	REFUEL_VEHICLE,
	ROBOT_CAMERA_NOT_MOVING,
	CRIPPLE_OPEN_DOOR,
	CRIPPLE_CLOSE_DOOR,
	CRIPPLE_END_OPEN_DOOR,
	CRIPPLE_END_OPEN_LOCKED_DOOR,
	LOCKPICK_CROUCHED,

	//<SB> crouch throwing
	THROW_ITEM_CROUCHED,
	//</SB>
	///ddd
	BIGGUY_STONE,
	SHOOT_ROCKET_CROUCHED,
	SWATTING_WK,
	SWAT_BACKWARDS_WK,
	SWAT_BACKWARDS_NOTHING,
	THROW_GRENADE_STANCE, //ddd Currently no animation for women. Using the standard.
	LOB_GRENADE_STANCE,
	//Prone rolls
	ROLL_PRONE_R,
	ROLL_PRONE_L, 
	
	//jump wall
	JUMPUPWALL,
	JUMPDOWNWALL,
	
	JUMPWINDOWS,
	
	THROW_KNIFE_SP_BM,
	RUNNING_W_PISTOL,

	SIDE_STEP_WEAPON_RDY,
	SIDE_STEP_DUAL_RDY,
	SIDE_STEP_CROUCH_RIFLE,
	SIDE_STEP_CROUCH_PISTOL,
	SIDE_STEP_CROUCH_DUAL,

	WALKING_WEAPON_RDY,
	WALKING_DUAL_RDY,
	CROUCHEDMOVE_RIFLE_READY,
	CROUCHEDMOVE_PISTOL_READY,
	CROUCHEDMOVE_DUAL_READY,

	START_AID_PRN,
	GIVING_AID_PRN,
	END_AID_PRN,

	ADJACENT_GET_ITEM_CROUCHED,
	STEAL_ITEM_CROUCHED,
	
	BURST_DUAL_STAND,
	BURST_DUAL_CROUCH,
	BURST_DUAL_PRONE,

	READY_ALTERNATIVE_STAND,
	AIM_ALTERNATIVE_STAND,
	SHOOT_ALTERNATIVE_STAND,
	BURST_ALTERNATIVE_STAND,
	LOW_SHOT_ALTERNATIVE_STAND,
	LOW_BURST_ALTERNATIVE_STAND,
	UNREADY_ALTERNATIVE_STAND,
	UNJAM_ALTERNATIVE_STAND,
	LOW_UNJAM_ALTERNATIVE_STAND,
	WALKING_ALTERNATIVE_RDY,
	SIDE_STEP_ALTERNATIVE_RDY,

	START_COWER_CROUCHED,
	END_COWER_CROUCHED,
	START_COWER_PRONE,
	COWERING_PRONE,
	END_COWER_PRONE,

	BIGMERC_IDLE_NECK2,

	FOCUSED_PUNCH,
	FOCUSED_STAB,	
	HTH_KICK,	
	FOCUSED_HTH_KICK,

	LONG_JUMP,

	CRYO_DEATH,
	CRYO_DEATH_CROUCHED,

	BAYONET_STAB_STANDING_VS_STANDING,
	BAYONET_STAB_STANDING_VS_PRONE,
	
	NUMANIMATIONSTATES

};
 


extern UINT16 gusAnimInst[ MAX_ANIMATIONS ][ MAX_FRAMES_PER_ANIM ];
extern ANIMCONTROLTYPE gAnimControl[ NUMANIMATIONSTATES ];

extern ANI_SPEED_DEF gubAnimWalkSpeeds[ TOTALBODYTYPES ];
extern ANI_SPEED_DEF gubAnimRunSpeeds[ TOTALBODYTYPES ];
extern ANI_SPEED_DEF gubAnimSwatSpeeds[ TOTALBODYTYPES ];
extern ANI_SPEED_DEF gubAnimCrawlSpeeds[ TOTALBODYTYPES ];
extern INT16 gubMaxActionPoints[ TOTALBODYTYPES ];


// OK, this array contains definitions for random animations based on bodytype, total # allowed, and what is in their hand....
extern RANDOM_ANI_DEF gRandomAnimDefs[ TOTALBODYTYPES ][ MAX_RANDOM_ANIMS_PER_BODYTYPE ];

// Corpse Defines
extern UINT16 gubAnimSurfaceCorpseID[ TOTALBODYTYPES ][ NUMANIMATIONSTATES ];


//FUNCTIONS
BOOLEAN LoadAnimationStateInstructions( );
void	InitAnimationSurfacesPerBodytype( );
BOOLEAN IsAnimationValidForBodyType( SOLDIERTYPE *pSoldier, UINT16 usNewState );
BOOLEAN SubstituteBodyTypeAnimation( SOLDIERTYPE *pSoldier, UINT16 usTestState, UINT16 *pusSubState );
INT8	GetBodyTypePaletteSubstitutionCode( SOLDIERTYPE *pSoldier, UINT8 ubBodyType, CHAR8 *zColFilename );

BOOLEAN SetSoldierAnimationSurface( SOLDIERTYPE *pSoldier, UINT16 usAnimState );
UINT16	DetermineSoldierAnimationSurface( SOLDIERTYPE *pSoldier, UINT16 usAnimState );
UINT16 LoadSoldierAnimationSurface( SOLDIERTYPE *pSoldier, UINT16 usAnimState );

// This function could be wrapped in a debug marco, since it only returns pSoldier->ubAnimSurface but
// Also does some debug checking
UINT16 GetSoldierAnimationSurface( SOLDIERTYPE *pSoldier, UINT16 usAnimState );


#endif
