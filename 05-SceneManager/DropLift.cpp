#include "DropLift.h"
#include "Sprites.h"
#include "Mario.h"
#include "GoldBrick.h"
#include "Game.h"
#define DROP_LIFT_BBOX_WIDTH 48
#define DROP_LIFT_BBOX_HEIGHT 16
#define ID_SPRITE_DROP_LIFT 560000
#define SCREEN_HEIGHT 268
#define SCREEN_WIDTH 274
int DropLift::IsCollidable()
{
    return 1;
}

void DropLift::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
    left = x - DROP_LIFT_BBOX_WIDTH / 2;
    top = y - DROP_LIFT_BBOX_HEIGHT / 2;
    right = left + DROP_LIFT_BBOX_WIDTH;
    bottom = top + DROP_LIFT_BBOX_HEIGHT;
}

void DropLift::Render()
{
    CSprites::GetInstance()->Get(ID_SPRITE_DROP_LIFT)->Draw(x, y);
}

void DropLift::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    if (!isActive && IsOnCamera())
        isActive = true;
    if (!isActive)
        return;
    if(!isTouched)
        x += vx * dt;
    else
    {
        vy += GRAVITY * dt;
        y += vy * dt;
    }
}

bool DropLift::IsOnCamera()
{
    float camX, camY;
    CGame::GetInstance()->GetCamPos(camX, camY);
    if (this->x - DROP_LIFT_BBOX_WIDTH <= camX + SCREEN_WIDTH && this->x >= camX
        && this->y <= camY + SCREEN_HEIGHT && this->y >= camY)
        return true;
    return false;
}

