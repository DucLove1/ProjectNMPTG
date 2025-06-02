#include <iostream>
#include <limits>
#include <fstream>
#include "AssetIDs.h"

#include "PlayScene.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Coin.h"
#include "Platform.h"
#include "Pipe.h"
#include "CQuestionBrick.h"
#include "Leaf.h"
#include "Mushroom.h"
#include "HUDBorder.h"
#include "TextMeshPro.h"
#include "HUDLifeText.h"
#include "HUDTimeText.h"

#include "HUDScoreText.h"

#include "GreenKoopa.h"

#include "SampleKeyEventHandler.h"
#include "Block.h"
#include "RedKoopa.h"
#include "Sensor.h"
#include "Venus.h"
#include "Ground.h"
#include "SpawnEnemy.h"
#include "Goomba.h"
#include "BigTree.h"
#include "Bushes.h"
#include "Cloud.h"
#include "LionBricks.h"
#include "PiranhaPlant.h"
#include "GoldBrick.h"
#include "BreakableGoldBrick.h"
#include "GoldBrickMulti.h"
#include "ItemGoldBrick.h"
#include "GoldBrickWithButton.h"
#include "BuiderGoldBrick.h"
#include "GameClock.h"
#include "Leaf.h"
#include "Mushroom.h"
#include "BouncingCoin.h"
#include "Wall.h"
#include "BlueWallBuilder.h"
#include "BackGroundBuilder.h"
#include "RectanglePlatform.h"
#include "Icon.h"
#include "WoddenBlock.h"
#include "DropLift.h"
#include "Boomerang.h"
#include "BoomerangBro.h"
#include "TeethLine.h"
#include "RandomCardSystem.h"
#define TIMES_TO_DEVIDE_WIDTH 10
#define TIMES_TO_DEVIDE_HEIGHT 5

using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	curObject = NULL;
	player = NULL;
	key_handler = new CSampleKeyHandler(this);
}


#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPTEXTURE tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ASSETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);

	LoadAssets(path.c_str());
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

/*
	Parse a line in section [OBJECTS]
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

	CGameObject* obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new CMario(x, y);
		player = (CMario*)obj;
		//set level to mario 
		player->SetState(GameManager::GetInstance()->GetCurLevel());
		DebugOut(L"[INFO] Player object has been created!\n");
		break;
	case OBJECT_TYPE_BROWN_GOOMBA:
	{
		int state = atoi(tokens[3].c_str());
		obj = new CGoomba(x, y, GOOMBA, state); break;
	}
	case OBJECT_TYPE_RED_GOOMBA:
	{
		int state = atoi(tokens[3].c_str());
		obj = new CGoomba(x, y, RED_GOOMBA, state); break;
	}
	case OBJECT_TYPE_BRICK: obj = new CBrick(x, y); break;
	case OBJECT_TYPE_COIN: obj = new CCoin(x, y); break;
	case OBJECT_TYPE_GREEN_KOOPAS:
	{
		int state = atoi(tokens[3].c_str());
		obj = new GreenKoopa(x, y, state);
		break;
	}
	case OBJECT_TYPE_RED_KOOPAS:
	{
		int state = atoi(tokens[3].c_str());
		obj = new RedKoopa(x, y, state);
		Sensor* sensor = new Sensor(dynamic_cast<CEnemy*>(obj));
		objects.push_back(sensor);
		break;
	}
	case OBJECT_TYPE_RED_VENUS:
	{
		obj = new Venus(x, y, RED);
		// pipe
		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());
		CPipe* pipe = new CPipe(
			x, y - 8,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end);
		objects.push_back(obj);
		objects.push_back(pipe);
		return;
		break;

	}
	case OBJECT_TYPE_GREEN_VENUS:
	{
		obj = new Venus(x, y, GREEN);
		// pipe
		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());
		CPipe* pipe = new CPipe(
			x, y - 8,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end);
		objects.push_back(obj);
		objects.push_back(pipe);
		return;
	}
	case OBJECT_TYPE_PIRANHA_PLANT:
	{
		obj = new PiranhaPlant(x, y);
		// pipe
		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());
		CPipe* pipe = new CPipe(
			x, y - 8,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end);
		objects.push_back(obj);
		objects.push_back(pipe);
		return;
	}
	case OBJECT_TYPE_SPAWNER:
	{
		float posSpawnX = (float)atof(tokens[3].c_str());
		float posSpawnY = (float)atof(tokens[4].c_str());
		int sizeTokens = tokens.size();
		vector<pair<int, int>> enemies;
		for (int i = 5; i < sizeTokens; i += 2)
		{
			pair<int, int> enemy;
			enemy.first = atoi(tokens[i].c_str());
			enemy.second = atoi(tokens[i + 1].c_str());
			enemies.emplace_back(enemy);
		}
		obj = new SpawnEnemy(x, y, posSpawnX, posSpawnY, enemies);
		break;
	}
	case OBJECT_TYPE_BLOCK:
	{
		int width = atoi(tokens[3].c_str());
		int height = atoi(tokens[4].c_str());
		int color = atoi(tokens[5].c_str());
		bool isShadowBottom = false;
		if (tokens.size() > 6)
		{
			isShadowBottom = atoi(tokens[6].c_str()) == 1 ? true : false;
		}
		obj = new Block(x, y, width, height, color, isShadowBottom);
		break;
	}
	case OBJECT_TYPE_BULDER_GOLD_BRICK:
	{
		int type = atoi(tokens[3].c_str());
		vector<vector<int>> grid;
		int width = atoi(tokens[4].c_str());
		int height = atoi(tokens[5].c_str());
		int curToken = 6;
		for (int i = 0; i < height; i++)
		{
			vector<int> row;
			for (int j = 0; j < width; j++)
			{
				row.push_back(atoi(tokens[curToken++].c_str()));
			}
			grid.push_back(row);
		}
		obj = new BuiderGoldBrick(x, y, type, grid);
		break;
	}

	case OBJECT_TYPE_PIPE:
	{
		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());

		obj = new CPipe(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end);
		break;

	}
	case OBJECT_TYPE_GROUND:
	{
		int width = atoi(tokens[3].c_str());
		int height = atoi(tokens[4].c_str());
		obj = new Ground(x, y, width, height);
		break;
	}
	case OBJECT_TYPE_QUESTION_BRICK:
	{
		int item = atoi(tokens[3].c_str());
		int timeCanHit = atoi(tokens[4].c_str());
		obj = new CQuestionBrick(x, y, item, timeCanHit);
		break;
	}
	case OBJECT_TYPE_LEAF:
	{
		obj = new CLeaf(x, y);
		break;
	}
	//case OBJECT_TYPE_MUSHROOM:
	//{
	//	int nx = atoi(tokens[3].c_str());
	//	obj = new CMushroom(x, y, nx);
	//	break;
	//}
	case OBJECT_TYPE_BOUNCING_COIN:
	{
		obj = new CBouncingCoin(x, y);
		break;
	}
	//for UI
	case OBJECT_TYPE_HUD_BORDER:
	{
		obj = new CHUDBorder(x, y);
		DebugOut(L"HUDCreated");
		break;
	}
	// this is base class, almost is not render this class, just to Inherit
	case OBJECT_TYPE_HUD_TEXTMESHPRO:
	{
		string str = "";
		obj = new CTextMeshPro(x, y, str);
		break;
	}
	case OBJECT_TYPE_HUD_LIFE_TEXT:
	{
		string str = "COUTER OF REMAINING LIVES";
		obj = new CHUDLifeText(x, y, str);
		break;
	}
	case OBEJECT_TYPE_HUD_LEVEL_TEXT:
	{
		string str = "LEVEL";
		//	obj = new CTextMeshPro(x, y, str);
		break;
	}
	case OBJECT_TYPE_HUD_SCORE_TEXT:
	{
		string str = "SCORE";
		obj = new CHUDScoreText(x, y, str);
		break;
	}
	case OBJECT_TYPE_HUD_TIME_TEXT:
	{
		string str = "TIME";
		obj = new CHUDTimeText(x, y, str);
		break;
	}
	case OBJECT_TYPE_HUD_COIN:
	{
		string str = "COIN";
		//	obj = new CTextMeshPro(x, y, str);
		break;
	}

	//end UI

	case OBJECT_TYPE_BIG_TREE:
	{
		int height = atoi(tokens[3].c_str());
		int position = atoi(tokens[4].c_str());
		obj = new BigTree(x, y, height, position);
		break;
	}
	case OBJECT_TYPE_BUSHES:
	{
		int width = atoi(tokens[3].c_str());
		obj = new Bushes(x, y, width);
		break;
	}
	case OBJECT_TYPE_CLOUD:
	{
		int width = atoi(tokens[3].c_str());
		obj = new Cloud(x, y, width);
		break;
	}
	case OBJECT_TYPE_LION_BRICKS:
	{
		int width = atoi(tokens[3].c_str());
		int height = atoi(tokens[4].c_str());
		obj = new LionBricks(x, y, width, height);
		break;
	}
	case OBJECT_TYPE_WALL:
	{
		obj = new Wall(x, y);
		break;
	}
	case OBJECT_TYPE_WALL_BUILDER:
	{
		int width = atoi(tokens[3].c_str());
		int height = atoi(tokens[4].c_str());
		obj = new BlueWallBuilder(x, y, width, height);
		break;
	}
	case OBJECT_TYPE_PLATFORM:
	{

		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());

		obj = new CPlatform(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end
		);

		break;
	}
	case OBJECT_TYPE_BACKGROUND_BUILDER:
	{
		int width = atoi(tokens[3].c_str());
		int height = atoi(tokens[4].c_str());
		int IdSpriteStart = atoi(tokens[5].c_str());
		int IdSpriteMiddle = atoi(tokens[6].c_str());
		int IdSpriteEnd = atoi(tokens[7].c_str());
		obj = new BackGroundBuilder(x, y, width, height, IdSpriteStart, IdSpriteMiddle, IdSpriteEnd);
		break;
	}
	case OBJECT_TYPE_RECTANGLE_PLATFORM:
	{
		int width = atoi(tokens[3].c_str());
		int height = atoi(tokens[4].c_str());
		vector<vector<int>> gridId;
		int curToken = 5;
		for (int i = 0; i < 2; i++)
		{
			vector<int> row;
			for (int j = 0; j < 3; j++)
			{
				row.push_back(atoi(tokens[curToken++].c_str()));
			}
			gridId.push_back(row);
		}
		obj = new RectanglePlatform(x, y, width, height, gridId);
		break;
	}
	case OBJECT_TYPE_ICON:
	{
		int id = atoi(tokens[3].c_str());
		obj = new Icon(x, y, id);
		break;
	}
	case OBJECT_TYPE_WOODEN_BLOCK:
	{
		int width = atoi(tokens[3].c_str());
		int height = atoi(tokens[4].c_str());
		vector<vector<int>> gridId;
		int curToken = 5;
		for (int i = 0; i < 2; i++)
		{
			vector<int> row;
			for (int j = 0; j < 3; j++)
			{
				row.push_back(atoi(tokens[curToken++].c_str()));
			}
			gridId.push_back(row);
		}
		obj = new WoddenBlock(x, y, width, height, gridId);
		break;
	}
	case OBJECT_TYPE_DROP_LIFT:
	{
		obj = new DropLift(x, y);
		break;
	}
	case OBJECT_TYPE_BOOMERANG:
	{
		obj = new Boomerang(x, y);
		break;
	}
	case OBJECT_TYPE_BOOMERANG_BRO:
	{
		obj = new BoomerangBro(x, y);
		break;
	}
	case OBJECT_TYPE_TEETH_LINE:
	{
		int unitWidth = atoi(tokens[3].c_str());
		int unitHeight = atoi(tokens[4].c_str());
		obj = new TeethLine(x, y, unitWidth, unitHeight);
		break;
	}
	case OBJECT_TYPE_PORTAL:
	{
		float r = (float)atof(tokens[3].c_str());
		float b = (float)atof(tokens[4].c_str());
		bool isPortalIn = atoi(tokens[5].c_str()) == 1 ? true : false; // 1 for in, 0 for out
		int scene_id = atoi(tokens[6].c_str());
		obj = new CPortal(x, y, r, b, isPortalIn,scene_id);
		break;
	}
	case OBJECT_TYPE_RANDOM_CARD_SYSTEM:
	{
		obj = new RandomCardSystem(x, y);
		break;
	}


	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);


	objects.push_back(obj);
}

void CPlayScene::AddObject(LPGAMEOBJECT obj) {
	objects.push_back(obj);
}

void CPlayScene::LoadAssets(LPCWSTR assetFile)
{
	DebugOut(L"[INFO] Start loading assets from : %s \n", assetFile);

	ifstream f;
	f.open(assetFile);

	int section = ASSETS_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SPRITES]") { section = ASSETS_SECTION_SPRITES; continue; };
		if (line == "[ANIMATIONS]") { section = ASSETS_SECTION_ANIMATIONS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case ASSETS_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case ASSETS_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading assets from %s\n", assetFile);
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
}

void CPlayScene::CinemachineCamera()
{
	CGame* game = CGame::GetInstance();

	// Update camera to follow mario
	float cx = std::numeric_limits<float>::lowest(),
		cy = std::numeric_limits<float>::lowest();

	float playerX, playerY;
	player->GetPosition(playerX, playerY);

	//Get Height and Width of screen
	float width = game->GetBackBufferWidth() / 2;
	float height = game->GetBackBufferHeight() * 3 / 5;

	//previrous camera position
	float preCamLeft, preCamTop, preCamRight, preCamBottom;
	//previouse camera limit range (if player move out of this range, camera will repositon to follow) 
	//I comment carefully bcuz i can read it again and if you read this line, bạn đã bị con mèo -BNguyen- =))))
	float limitLeft, limitTop, limitRight, limitBottom;

	float cameraCenterX, cameraCenterY;

	bool isChangeX = false;
	bool isChangeY = false;

	CGame::GetInstance()->GetCamPos(preCamLeft, preCamTop);
	preCamRight = preCamLeft + width;
	preCamBottom = preCamTop + height;

	cameraCenterX = (preCamLeft + preCamRight) / 2;
	cameraCenterY = (preCamTop + preCamBottom) / 2;

	limitRight = cameraCenterX +  width * 5 / TIMES_TO_DEVIDE_WIDTH;
	limitLeft =  limitRight - 2 * width / TIMES_TO_DEVIDE_WIDTH;
	limitTop = cameraCenterY - height / TIMES_TO_DEVIDE_HEIGHT;
	limitBottom = cameraCenterY + height / TIMES_TO_DEVIDE_HEIGHT;

	if (playerX < limitLeft)
	{
		cx = preCamLeft - (limitLeft - playerX);
		isChangeX = true;
	}
	else if (playerX > limitRight)
	{
		cx = preCamLeft + (playerX - limitRight);
		isChangeX = true;
	}
	if (playerY < limitTop)
	{
		cy = preCamTop - (limitTop - playerY);
		isChangeY = true;
	}
	else if (playerY > limitBottom)
	{
		cy = preCamTop + (playerY - limitBottom);
		isChangeY = true;
	}


	if (cx < 0) cx = 0;
	if (cy > -17) cy = -17;

	if (!isChangeX && !isChangeY)
	{
		CGame::GetInstance()->SetCamPos(preCamLeft, preCamTop);
	}
	else if (!isChangeX)
	{
		CGame::GetInstance()->SetCamPos(preCamLeft, cy);
	}
	else if (!isChangeY)
	{
		CGame::GetInstance()->SetCamPos(cx, preCamTop);
	}
	else
	{
		CGame::GetInstance()->SetCamPos(cx, cy);
	}

	//player->GetPosition(cx, cy);

	//cx -= game->GetBackBufferWidth() / 2;
	//cy -= game->GetBackBufferHeight() * 3/ 5;

	//CGame::GetInstance()->SetCamPos(cx, cy);
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 
	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	//if (GameManager::GetInstance()->IsPausedToTransform())
	//{
	//	player->Update(dt, &coObjects);
	//	return;
	//}
	for (size_t i = 0; i < objects.size(); i++)
	{
		//if (i != 0 && GameClock::GetInstance()->IsTempPaused())
		//	break;
		if (GameManager::GetInstance()->IsPausedGame())
			return;
		if(!GameManager::GetInstance()->IsPausedToTransform() || objects[i]->IsUpdateWhenMarioTransform())
		objects[i]->Update(dt, &coObjects);
	}

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;


	// Update camera to follow mario

	CinemachineCamera();

	//CGame::GetInstance()->SetCamPos(cx, cy);

	PurgeDeletedObjects();
}
bool CPlayScene::CheckObjectPause(CGameObject* object)
{
	if (dynamic_cast<CEnemy*>(object) || dynamic_cast<VenusBullet*>(object)
		|| dynamic_cast<CLeaf*>(object) || dynamic_cast<CMushroom*>(object))
	{
		return true;
	}
	return false;
}
void CPlayScene::Render()
{
	for (int i = 1; i < objects.size(); i++)
	{
		curObject = objects[i];
		if(GameManager::GetInstance()->IsPausedGame() && !curObject->IsRenderWhenPaused())
			continue;
		objects[i]->Render();
	}
	//if(!GameClock::GetInstance()->IsPaused())
	curObject = objects[0];
	if (GameManager::GetInstance()->IsPausedGame() && !curObject->IsRenderWhenPaused())
		return;
	objects[0]->Render();
}

/*
*	Clear all objects from this scene
*/
void CPlayScene::Clear()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		delete (*it);
	}
	objects.clear();
}

/*
	Unload scene

	TODO: Beside objects, we need to clean up sprites, animations and textures as well

*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

bool CPlayScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

void CPlayScene::PurgeDeletedObjects()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}

	// NOTE: remove_if will swap all deleted items to the end of the vector
	// then simply trim the vector, this is much more efficient than deleting individual items
	objects.erase(
		std::remove_if(objects.begin(), objects.end(), CPlayScene::IsGameObjectDeleted),
		objects.end());
}