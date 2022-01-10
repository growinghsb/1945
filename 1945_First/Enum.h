#pragma once

enum class KEY_LIST
{
	A,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P,
	Q,
	R,
	S,
	T,
	U,
	V,
	W,
	X,
	Y,
	Z,

	_0,
	_1,
	_2,
	_3,
	_4,
	_5,
	_6,
	_7,
	_8,
	_9,

	ESCAPE,
	SPACE,
	ENTER,

	LEFT,
	TOP,
	RIGHT,
	BOTTOM,

	LSHIFT,
	LCTRL,
	LALT,

	LBUTTON,
	RBUTTON,

	END
};

enum class KEY_STATE 
{
	TIC, 
	PRESS, 
	BACK, 
	NONE
};

enum class EVENT_TYPE
{
	STAGE_CHANGE,
	CREATE_OBJ,
	DELETE_OBJ,
	END
};

enum class CHANGE_STAGE_TYPE 
{
	INTRO, 
	NEXT, 
	PREV, 
	END
};

enum class OBJ_TYPE 
{
	PLAYER, 
	SECOND_PLAYER,
	ENEMY, 
	OBSTACLE, 
	ITEM,
	P_DEFAULT_BULLET, 
	SP_DEFAULT_BULLET,
	E_DEFAULT_BULLET,
	END
};

enum class LAYER_TYPE
{
	//BACKGRAOUND,
	OBJ,
	UI,
	END
};

enum class COMPONENT_TYPE 
{
	COLLIDER,
	ANIMATOR,
	FSM,
	END
};