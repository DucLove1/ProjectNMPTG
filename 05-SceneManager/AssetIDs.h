#pragma once

//
// This file contains all IDs of game assets 
//

#define ID_TEX_MARIO 0
#define ID_TEX_ENEMY 10
#define ID_TEX_MISC 20
#define ID_TEX_STUFFS 30


#define OBJECT_TYPE_MARIO	0
#define OBJECT_TYPE_BRICK	1
#define OBJECT_TYPE_GOOMBA	2
#define OBJECT_TYPE_KOOPAS	3
#define OBJECT_TYPE_COIN 4
#define OBJECT_TYPE_PLATFORM 5
#define OBJECT_TYPE_GREEN_KOOPAS 6
#define OBJECT_TYPE_BLOCK 7
#define OBJECT_TYPE_PIPE 9

#define OBJECT_TYPE_QUESTION_BRICK 20
#define OBJECT_TYPE_LEAF 21

#define OBJECT_TYPE_PORTAL	50


#pragma region MARIO 

#define ID_SPRITE_MARIO 10000
#define ID_SPRITE_MARIO_BIG (ID_SPRITE_MARIO + 1000)
#define ID_SPRITE_MARIO_BIG_IDLE (ID_SPRITE_MARIO_BIG + 100)
#define ID_SPRITE_MARIO_BIG_IDLE_LEFT (ID_SPRITE_MARIO_BIG_IDLE + 10)
#define ID_SPRITE_MARIO_BIG_IDLE_RIGHT (ID_SPRITE_MARIO_BIG_IDLE + 20)

#define ID_SPRITE_MARIO_BIG_WALKING (ID_SPRITE_MARIO_BIG + 200)
#define ID_SPRITE_MARIO_BIG_WALKING_LEFT (ID_SPRITE_MARIO_BIG_WALKING + 10)
#define ID_SPRITE_MARIO_BIG_WALKING_RIGHT (ID_SPRITE_MARIO_BIG_WALKING + 20)
#define ID_SPRITE_MARIO_BIG_RUNNING (ID_SPRITE_MARIO_BIG + 300)
#define ID_SPRITE_MARIO_BIG_RUNNING_LEFT (ID_SPRITE_MARIO_BIG_RUNNING + 10)
#define ID_SPRITE_MARIO_BIG_RUNNING_RIGHT (ID_SPRITE_MARIO_BIG_RUNNING + 20)
#define ID_SPRITE_MARIO_BIG_JUMP (ID_SPRITE_MARIO_BIG + 400)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK (ID_SPRITE_MARIO_BIG_JUMP + 10)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK_LEFT (ID_SPRITE_MARIO_BIG_JUMP_WALK + 2)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK_RIGHT (ID_SPRITE_MARIO_BIG_JUMP_WALK + 6)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN (ID_SPRITE_MARIO_BIG_JUMP + 20)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN_LEFT (ID_SPRITE_MARIO_BIG_JUMP_RUN + 2)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN_RIGHT (ID_SPRITE_MARIO_BIG_JUMP_RUN + 6)
#define ID_SPRITE_MARIO_BIG_SIT (ID_SPRITE_MARIO_BIG + 500)
#define ID_SPRITE_MARIO_BIG_SIT_LEFT (ID_SPRITE_MARIO_BIG_SIT + 10)
#define ID_SPRITE_MARIO_BIG_SIT_RIGHT (ID_SPRITE_MARIO_BIG_SIT + 20)
#define ID_SPRITE_MARIO_BIG_BRACE (ID_SPRITE_MARIO_BIG + 600)
#define ID_SPRITE_MARIO_BIG_BRACE_LEFT (ID_SPRITE_MARIO_BIG_BRACE + 10)
#define ID_SPRITE_MARIO_BIG_BRACE_RIGHT (ID_SPRITE_MARIO_BIG_BRACE + 20)

//new anim 
#define ID_SPRITE_MARIO_BIG_PICKING (ID_SPRITE_MARIO_BIG + 700)
#define ID_SPRITE_MARIO_BIG_PICKING_LEFT (ID_SPRITE_MARIO_BIG_PICKING +10)
#define ID_SPRITE_MARIO_BIG_PICKING_RIGHT (ID_SPRITE_MARIO_BIG_PICKING +20)

#define ID_SPRITE_MARIO_DIE (ID_SPRITE_MARIO + 3000)

#define ID_SPRITE_MARIO_SMALL (ID_SPRITE_MARIO + 2000)
#define ID_SPRITE_MARIO_SMALL_IDLE (ID_SPRITE_MARIO_SMALL + 100)
#define ID_SPRITE_MARIO_SMALL_IDLE_LEFT (ID_SPRITE_MARIO_SMALL_IDLE + 10)
#define ID_SPRITE_MARIO_SMALL_IDLE_RIGHT (ID_SPRITE_MARIO_SMALL_IDLE + 20)

#define ID_SPRITE_MARIO_SMALL_WALKING (ID_SPRITE_MARIO_SMALL + 200)
#define ID_SPRITE_MARIO_SMALL_WALKING_LEFT (ID_SPRITE_MARIO_SMALL_WALKING + 10)
#define ID_SPRITE_MARIO_SMALL_WALKING_RIGHT (ID_SPRITE_MARIO_SMALL_WALKING + 20)
#define ID_SPRITE_MARIO_SMALL_RUNNING (ID_SPRITE_MARIO_SMALL + 300)
#define ID_SPRITE_MARIO_SMALL_RUNNING_LEFT (ID_SPRITE_MARIO_SMALL_RUNNING + 10)
#define ID_SPRITE_MARIO_SMALL_RUNNING_RIGHT (ID_SPRITE_MARIO_SMALL_RUNNING + 20)
#define ID_SPRITE_MARIO_SMALL_JUMP (ID_SPRITE_MARIO_SMALL + 400)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK (ID_SPRITE_MARIO_SMALL_JUMP + 10)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK_LEFT (ID_SPRITE_MARIO_SMALL_JUMP_WALK + 2)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK_RIGHT (ID_SPRITE_MARIO_SMALL_JUMP_WALK + 6)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN (ID_SPRITE_MARIO_SMALL_JUMP + 20)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN_LEFT (ID_SPRITE_MARIO_SMALL_JUMP_RUN + 2)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN_RIGHT (ID_SPRITE_MARIO_SMALL_JUMP_RUN + 6)

#define ID_SPRITE_MARIO_SMALL_SIT (ID_SPRITE_MARIO_SMALL + 500)
#define ID_SPRITE_MARIO_SMALL_SIT_LEFT (ID_SPRITE_MARIO_SMALL_SIT + 10)
#define ID_SPRITE_MARIO_SMALL_SIT_RIGHT (ID_SPRITE_MARIO_SMALL_SIT + 20)

#define ID_SPRITE_MARIO_SMALL_BRACE (ID_SPRITE_MARIO_SMALL + 500)
#define ID_SPRITE_MARIO_SMALL_BRACE_LEFT (ID_SPRITE_MARIO_SMALL_BRACE + 10)
#define ID_SPRITE_MARIO_SMALL_BRACE_RIGHT (ID_SPRITE_MARIO_SMALL_BRACE + 20)

//new anim 
#define ID_SPRITE_MARIO_SMALL_PICKING (ID_SPRITE_MARIO_SMALL + 600)
#define ID_SPRITE_MARIO_SMALL_PICKING_LEFT (ID_SPRITE_MARIO_SMALL_PICKING +10)
#define ID_SPRITE_MARIO_SMALL_PICKING_RIGHT (ID_SPRITE_MARIO_SMALL_PICKING +20)

#pragma endregion 

#define ID_SPRITE_BRICK 20000

#define ID_SPRITE_GOOMBA 30000
#define ID_SPRITE_GOOMBA_WALK (ID_SPRITE_GOOMBA + 1000)
#define ID_SPRITE_GOOMBA_DIE (ID_SPRITE_GOOMBA + 2000)
#define ID_SPRITE_GOOMBA_KNOCK_OUT (ID_SPRITE_GOOMBA + 3000)

#define ID_SPRITE_COIN 40000

#define ID_SPRITE_CLOUD 50000
#define ID_SPRITE_CLOUD_BEGIN (ID_SPRITE_CLOUD+1000)
#define ID_SPRITE_CLOUD_MIDDLE (ID_SPRITE_CLOUD+2000)
#define ID_SPRITE_CLOUD_END (ID_SPRITE_CLOUD+3000)

#define ID_SPRITE_RED_GOOMBA 60000
#define ID_SPRITE_RED_GOOMBA_WALK (ID_SPRITE_RED_GOOMBA + 1000)
#define ID_SPRITE_RED_GOOMBA_DIE (ID_SPRITE_RED_GOOMBA + 2000)
#define ID_SPRITE_RED_GOOMBA_WING (ID_SPRITE_RED_GOOMBA + 3000)
#define ID_SPRITE_RED_GOOMBA_KNOCK_OUT (ID_SPRITE_RED_GOOMBA + 4000)

#define ID_SPRITE_PIPE 80000
#define ID_SPRITE_PIPE_BEGIN (ID_SPRITE_PIPE + 1000)
#define ID_SPRITE_PIPE_MIDDLE (ID_SPRITE_PIPE + 2000)
#define ID_SPRITE_PIPE_END (ID_SPRITE_PIPE + 3000)

#define ID_SPRITE_QUESTION_EMPTY 200000
#define ID_SPRITE_QUESTION_SPIN	(ID_SPRITE_QUESTION_EMPTY + 1000)
#define ID_SPRITE_QUESTION_COIN (ID_SPRITE_QUESTION_EMPTY + 2000)
#define ID_SPRITE_QUESTION_MUSHROOM (ID_SPRITE_QUESTION_EMPTY + 3000)
#define ID_SPRITE_QUESTION_LEAF (ID_SPRITE_QUESTION_EMPTY + 4000)

#define ID_SPRITE_LEAF 210000
#define ID_SPRITE_LEAF_LEFT (ID_SPRITE_LEAF + 1000)
#define ID_SPRITE_LEAF_RIGHT (ID_SPRITE_LEAF + 2000)

#pragma region GREEN_KOOPA
#define ID_SPRITE_GREEN_KOOPA 90000
#define ID_SPRITE_GREEN_KOOPA_WALK_NO_WING_LEFT (ID_SPRITE_GREEN_KOOPA + 1000)
#define ID_SPRITE_GREEN_KOOPA_WALK_NO_WING_RIGHT (ID_SPRITE_GREEN_KOOPA + 2000)
#define ID_SPRITE_GREEN_KOOPA_IN_SHELL_UP (ID_SPRITE_GREEN_KOOPA + 3000)
#define ID_SPRITE_GREEN_KOOPA_IN_SHELL_UP_MOVE (ID_SPRITE_GREEN_KOOPA_IN_SHELL_UP + 100)
#define ID_SPRITE_GREEN_KOOPA_IN_SHELL_DOWN (ID_SPRITE_GREEN_KOOPA + 4000)
#define ID_SPRITE_GREEN_KOOPA_IN_SHELL_DOWN_MOVE (ID_SPRITE_GREEN_KOOPA_IN_SHELL_DOWN + 100)
#define ID_SPRITE_GREEN_KOOPA_OUT_OF_SHELL (ID_SPRITE_GREEN_KOOPA + 5000)
#define ID_SPRITE_GREEN_KOOPA_WING (ID_SPRITE_GREEN_KOOPA + 6000)
#define ID_SPRITE_GREEN_KOOPA_WING_WALK_LEFT (ID_SPRITE_GREEN_KOOPA_WING + 100)
#define ID_SPRITE_GREEN_KOOPA_WING_WALK_RIGHT (ID_SPRITE_GREEN_KOOPA_WING + 200)
#pragma endregion
#pragma region RED_KOOPA
#define ID_SPRITE_RED_KOOPA 100000
#define ID_SPRITE_RED_KOOPA_WALK_NO_WING_LEFT (ID_SPRITE_RED_KOOPA + 1000)
#define ID_SPRITE_RED_KOOPA_WALK_NO_WING_RIGHT (ID_SPRITE_RED_KOOPA + 2000)
#define ID_SPRITE_RED_KOOPA_IN_SHELL_UP (ID_SPRITE_RED_KOOPA + 3000)
#define ID_SPRITE_RED_KOOPA_IN_SHELL_UP_MOVE (ID_SPRITE_RED_KOOPA_IN_SHELL_UP + 100)
#define ID_SPRITE_RED_KOOPA_IN_SHELL_DOWN (ID_SPRITE_RED_KOOPA + 4000)
#define ID_SPRITE_RED_KOOPA_IN_SHELL_DOWN_MOVE (ID_SPRITE_RED_KOOPA_IN_SHELL_DOWN + 100)
#define ID_SPRITE_RED_KOOPA_OUT_OF_SHELL (ID_SPRITE_RED_KOOPA + 5000)
#define ID_SPRITE_RED_KOOPA_WING (ID_SPRITE_RED_KOOPA + 6000)
#define ID_SPRITE_RED_KOOPA_WING_WALK_LEFT (ID_SPRITE_RED_KOOPA_WING + 100)
#define ID_SPRITE_RED_KOOPA_WING_WALK_RIGHT (ID_SPRITE_RED_KOOPA_WING + 200)
#pragma endregion
#pragma region Block
#define ID_SPRITE_BEIGE_BLOCK 110000
#define ID_SPRITE_BLUE_BLOCK 111000
#define ID_SPRITE_GREEN_BLOCK 112000
#define ID_SPRITE_WHITE_BLOCK 113000
#define ID_SPRITE_SHADOW_CORNER 114000
#define ID_SPRITE_SHADOW_EDGE 115000
#pragma endregion
  
//Animations
#pragma region ANIMATION
#pragma region MARIO

#define ID_ANI_MARIO_PICKING_RIGHT 300
#define ID_ANI_MARIO_PICKING_LEFT 301

#define ID_ANI_MARIO_IDLE_RIGHT 400
#define ID_ANI_MARIO_IDLE_LEFT 401

#define ID_ANI_MARIO_WALKING_RIGHT 500
#define ID_ANI_MARIO_WALKING_LEFT 501

#define ID_ANI_MARIO_RUNNING_RIGHT 600
#define ID_ANI_MARIO_RUNNING_LEFT 601

#define ID_ANI_MARIO_JUMP_WALK_RIGHT 700
#define ID_ANI_MARIO_JUMP_WALK_LEFT 701

#define ID_ANI_MARIO_JUMP_RUN_RIGHT 800
#define ID_ANI_MARIO_JUMP_RUN_LEFT 801

#define ID_ANI_MARIO_SIT_RIGHT 900
#define ID_ANI_MARIO_SIT_LEFT 901

#define ID_ANI_MARIO_BRACE_RIGHT 1000
#define ID_ANI_MARIO_BRACE_LEFT 1001

#define ID_ANI_MARIO_DIE 999

// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 1100
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 1102

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT 1200
#define ID_ANI_MARIO_SMALL_WALKING_LEFT 1201

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT 1300
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT 1301

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT 1400
#define ID_ANI_MARIO_SMALL_BRACE_LEFT 1401

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT 1500
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT 1501

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT 1600
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT 1601

#pragma endregion

#pragma region BRICK
#define ID_ANI_BRICK 10000
#pragma endregion

#pragma region GOOMBA
#define ID_ANI_GOOMBA_WALKING 5000
#define ID_ANI_GOOMBA_DIE 5001
#define ID_ANI_GOOMBA_WALKING_WING 5002
#define ID_ANI_GOOMBA_WALKING_WING_READY_FLY 5003
#define ID_ANI_GOOMBA_WING_FLY 5004
#define ID_ANI_GOOMBA_KNOCK_OUT 5005
#pragma endregion

#pragma region RED_GOOMBA
#define ID_ANI_RED_GOOMBA_WALKING 6000
#define ID_ANI_RED_GOOMBA_DIE 6001
#define ID_ANI_RED_GOOMBA_WALKING_WING 6002
#define ID_ANI_RED_GOOMBA_WALKING_WING_READY_FLY 6003
#define ID_ANI_RED_GOOMBA_WING_FLY 6004
#define ID_ANI_RED_GOOMBA_KNOCK_OUT 6005
#pragma endregion

#pragma region KOOPA
#define ID_ANI_KOOPA_WALKING 7000
#define ID_ANI_KOOPA_IN_SHELL 7001
#define ID_ANI_KOOPA_SHAKING 7002
#define ID_ANI_KOOPA_WING 7003
#define ID_ANI_KOOPA_IN_SHELL_THROWED_OR_KICKED 7004
#pragma endregion

#pragma region GREEN_KOOPA
#define ID_ANI_GREEN_KOOPA_WALKING_LEFT 8000
#define ID_ANI_GREEN_KOOPA_IN_SHELL_UP 8001
#define ID_ANI_GREEN_KOOPA_SHAKING_UP 8002
#define ID_ANI_GREEN_KOOPA_WING_LEFT 8003
#define ID_ANI_GREEN_KOOPA_IN_SHELL_UP_MOVE 8004
#define ID_ANI_GREEN_KOOPA_WALKING_RIGHT 8005
#define ID_ANI_GREEN_KOOPA_WING_RIGHT 8006
#define ID_ANI_GREEN_KOOPA_IN_SHELL_DOWN 8007
#define ID_ANI_GREEN_KOOPA_IN_SHELL_DOWN_MOVE 8008
#define ID_ANI_GREEN_KOOPA_SHAKING_DOWN 8009
#pragma endregion
#pragma region RED_KOOPA
#define ID_ANI_RED_KOOPA_WALKING_LEFT 7000
#define ID_ANI_RED_KOOPA_IN_SHELL_UP 7001
#define ID_ANI_RED_KOOPA_SHAKING_UP 7002
#define ID_ANI_RED_KOOPA_WING_LEFT 7003
#define ID_ANI_RED_KOOPA_IN_SHELL_UP_MOVE 7004
#define ID_ANI_RED_KOOPA_WALKING_RIGHT 7005
#define ID_ANI_RED_KOOPA_WING_RIGHT 7006
#define ID_ANI_RED_KOOPA_IN_SHELL_DOWN 7007
#define ID_ANI_RED_KOOPA_IN_SHELL_DOWN_MOVE 7008
#define ID_ANI_RED_KOOPA_SHAKING_DOWN 7009
#pragma endregion

#pragma region COIN
#define ID_ANI_COIN 11000
#pragma endregion

#pragma region QUESTION_BRICK
#define ID_ANI_QUESTION_BRICK_EMPTY 20000
#define ID_ANI_QUESTION_BRICK_SPIN 20001
#define ID_ANI_QUESTION_BRICK_COIN 20002
#define ID_ANI_QUESTION_BRICK_MUSHROOM 20003
#define ID_ANI_QUESTION_BRICK_LEAF 20004
#pragma endregion

#pragma region LEAF
#define ID_ANI_LEAF_LEFT 21000
#define ID_ANI_LEAF_RIGHT 21001
