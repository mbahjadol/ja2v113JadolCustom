#pragma once

/**
* "Turn Based Input GKI Handler.cpp" This source is additional modular external for source "Turn Based Input.cpp"
* on function "void GetKeyboardInput()" inside loop while (DequeueEvent(&InputEvent) == TRUE)
*
**/

#include "Types.h"

// class GKIWhenDQEOnKD (GetKeyboardInput When DequeueEvent On Keyboard Down)
class GKIWhenDQEOnKD
{
public:
	static void On_SPACE(UINT32 * puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift);
	static void On_LEFTARROW(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift);
	static void On_RIGHTARROW(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift);
	static void On_INSERT(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift);
	static void On_DELETE(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift);
	static void On_HOME(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift);
	static void On_END(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift);
	static void On_PGUP(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift);
	static void On_PGDN(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift);
	static void On_BACKSPACE(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift);
	static void On_TAB(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift);
	static void On_F1(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift);
	static void On_F2(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift);
	static void On_F3(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift);
	static void On_F4(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift);
	static void On_F5(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift);
	static void On_F6(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift);
	static void On_F7(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift);
	static void On_F8(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift);
	static void On_F9(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift);
	static void On_F10(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift);
	static void On_F11(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift);
	static void On_F12(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift);
	static void On_MinusOrUnderscore(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift);
	static void On_Plus(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift);
	static void On_Equal(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift);
	static void On_Comma(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_Dot(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_Slash(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_BackSlash(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_BackQuote(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_One(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_Two(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_Three(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_Four(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_Five(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_Six(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_Seven(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_Eight(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_Nine(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_Zero(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_Exclamation(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_AtSign(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_Hash(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_DollarSign(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_Percent(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_Caret(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_Ampersand(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_Asterix(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_OpenParenthesis(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_CloseParenthesis(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_a(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos, INT16* gCurrentFortificationStructure, UINT8* gCurrentFortificationTileLibraryIndex);
	static void On_A(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_b(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos, INT16* gCurrentFortificationStructure, UINT8* gCurrentFortificationTileLibraryIndex);
	static void On_B(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_c(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_C(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_d(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_D(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_e(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_E(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_f(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_F(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_G(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_g(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos, INT32 * mappos);
	static void On_H(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_h(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_I(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_i(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static bool On_j(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos, BOOLEAN	*gfNextFireJam);
	static void On_J(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_k(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos, UINT16 *gusItemExplosion);
	static void On_K(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_l(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_L(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_m(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_M(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_N(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_n(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_o(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_O(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_p(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_P(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_q(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_Q(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_R(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_r(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_S(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static bool On_s(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_t(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_T(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_u(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_U(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_v(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_V(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_w(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_W(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_x(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_X(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_y(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_Y(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_z(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
	static void On_Z(UINT32* puiNewEvent, BOOLEAN fAlt, BOOLEAN fCtrl, BOOLEAN fShift, INT32 usMapPos);
};

