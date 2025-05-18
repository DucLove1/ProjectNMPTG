#include "DropLift.h"
#include "Sprites.h"
#include "Mario.h"
#include "GoldBrick.h"
#define DROP_LIFT_BBOX_WIDTH 48
#define DROP_LIFT_BBOX_HEIGHT 16
#define ID_SPRITE_DROP_LIFT 560000
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
    RenderBoundingBox();
}

void DropLift::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    /*if (!isActive)
        return;*/
    if(!isTouched)
        x += vx * dt;
    else
    {
        vy += GRAVITY * dt;
        y += vy * dt;
    }
}

