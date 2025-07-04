﻿#include <iostream>
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
#include "HUDLevel.h"
#include "HUDScoreText.h"
#include "HUDCoin.h"
#include "HUDMarioPower.h"

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
#include "PausePanel.h"
#include "HUDRandomCardSystem.h"
#include "Mario.h"
#define TIMES_TO_DEVIDE_WIDTH 10
#define TIMES_TO_DEVIDE_HEIGHT 5

#define WAITING_TIME_BEFORE_SCROLLING 1000 * 3
#define VX_SCROLLING 0.035f 
#define TIME_FOR_DELAY 2000
using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath, int worldIndex, int directionWhenReenterScene) :
	CScene(id, filePath, worldIndex)
{
	isStartGame = false;
	timeStart = GameClock::GetInstance()->GetTime();

	curObject = NULL;
	player = NULL;
	key_handler = new CSampleKeyHandler(this);
	this->timerWhenPlayerDie = -1; // -1 means player is not dead yet
	this->directionWhenReenterScene = directionWhenReenterScene;
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
	bool isUIElement = false;
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
	{
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		if (tokens.size() >= 4)
		{
			int direction = atoi(tokens[3].c_str());

			obj = new CMario(x, y, direction);

		}
		else
			obj = new CMario(x, y);
		player = (CMario*)obj;
		//set level to mario 
		player->SetState(GameManager::GetInstance()->GetCurLevel());
		DebugOut(L"[INFO] Player object has been created!\n");
		break;
	}
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
		int marioOut = 0;
		int canEntry = 0;
		if (tokens.size() > 9)
			marioOut = atoi(tokens[9].c_str());
		if (tokens.size() > 10)
			canEntry = atoi(tokens[10].c_str());

		obj = new CPipe(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end, marioOut, canEntry);
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
		isUIElement = true;
		obj = new CHUDBorder(x, y);
		DebugOut(L"%f , %f HUDpos", x, y);
		DebugOut(L"HUDCreated");
		break;
	}
	// this is base class, almost is not render this class, just to Inherit
	case OBJECT_TYPE_HUD_TEXTMESHPRO:
	{
		isUIElement = true;
		string str = "";
		obj = new CTextMeshPro(x, y, str);
		break;
	}
	case OBJECT_TYPE_HUD_LIFE_TEXT:
	{
		isUIElement = true;
		string str = "COUTER OF REMAINING LIVES";
		obj = new CHUDLifeText(x, y, str);
		break;
	}
	case OBEJECT_TYPE_HUD_LEVEL_TEXT:
	{
		isUIElement = true;
		string str = "LEVEL";
		obj = new CHUDLevel(x, y, str);
		break;
	}
	case OBJECT_TYPE_HUD_SCORE_TEXT:
	{
		isUIElement = true;
		string str = "SCORE";
		obj = new CHUDScoreText(x, y, str);
		break;
	}
	case OBJECT_TYPE_HUD_TIME_TEXT:
	{
		isUIElement = true;
		string str = "TIME";
		obj = new CHUDTimeText(x, y, str);
		break;
	}
	case OBJECT_TYPE_HUD_COIN:
	{
		isUIElement = true;
		string str = "COIN";
		obj = new CHUDCoin(x, y, str);
		break;
	}
	case OBJECT_TYPE_HUD_POWER: //45
	{
		isUIElement = true;
		obj = new CHUDMarioPower(x, y);
		break;
	}

	case OBJECT_TYPE_HUD_PAUSE_PANEL:
	{
		isUIElement = true;
		obj = new CPausePanel(x, y);
		break;
	}

	case OBJECT_TYPE_HUD_RANDOM_CARD_SYSTEM:
	{
		isUIElement = true;
		obj = new HUDRandomCardSystem(x, y);
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
		float posOutX = NON_POS, posOutY = NON_POS;
		posOutX = (float)atof(tokens[7].c_str());
		posOutY = (float)atof(tokens[8].c_str());
		obj = new CPortal(x, y, r, b, isPortalIn, scene_id, posOutX, posOutY);
		break;
	}
	case OBJECT_TYPE_RANDOM_CARD_SYSTEM:
	{
		obj = new RandomCardSystem(x, y);
		break;
	}
	case OBJECT_TYPE_FADE_TRANSITION:
	{
		bool isFadeIn = atoi(tokens[3].c_str()) == 1 ? true : false; // 1 for fade in, 0 for fade out
		obj = new FadeTransition(x, y, isFadeIn);
		break;
	}

	default:
	{
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}
	}
	// General object setup
	obj->SetPosition(x, y);

	if (isUIElement)
		UserInterfaces.push_back(obj);
	else
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
	// scene da duoc load roi
	if (!this->objects.empty())
	{
		// vi da xoa asset khi chuyen scene nen phai add vao lai
		// khong can them object vi da co san object
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
			if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

			//
			// data section
			//
			switch (section)
			{
			case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
			}
		}

		// neu quay lai map da duoc load thi gan lai trang thai cua mario
		if (player != NULL)
		{
			CMario* mario = dynamic_cast<CMario*>(player);
			mario->SetLevel(GameManager::GetInstance()->GetCurLevel());
			mario->SetPosition(this->posOutX, this->posOutY);
			mario->SetDirection(GameManager::GetInstance()->GetMarioDirection());
			mario->SetState(MARIO_STATE_EXIT_PIPE);
			mario->SetDirectionToExit(this->directionWhenReenterScene);
			mario->SetStartPoint(this->posOutX, this->posOutY);
		}
		// tao mario moi
		//CMario* mario = new CMario(this->posOutX, this->posOutY, this->directionWhenReenterScene); // create new mario object
		//mario->SetLevel(GameManager::GetInstance()->GetCurLevel());
		//player->Delete();
		//player = mario; // set player to new mario object
		//objects[0] = mario;
		f.close();
		// ADD FADE TRANSITION
		this->objects.push_back(new FadeTransition(0, 0, true));
		return;
	}
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
	// ADD FADE TRANSITION
	this->objects.push_back(new FadeTransition(0, 0, true));
	// set state mario 
	((CMario*)player)->SetLevel(GameManager::GetInstance()->GetCurLevel());
	// set direction for mario
	((CMario*)player)->SetDirection(GameManager::GetInstance()->GetMarioDirection());
	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
	/*float x, y;
	player->GetPosition(x, y);
	CGame::GetInstance()->SetCamPos(x - CGame::GetInstance()->GetBackBufferWidth() / 2, y - CGame::GetInstance()->GetBackBufferHeight() * 3 / 5);*/
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

	limitRight = cameraCenterX + width * 5 / TIMES_TO_DEVIDE_WIDTH;
	limitLeft = limitRight - 2 * width / TIMES_TO_DEVIDE_WIDTH;
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


void CPlayScene::ScrollingCamera(DWORD dt)
{
	ULONGLONG curentTime = GameClock::GetInstance()->GetTime();

	CGame* game = CGame::GetInstance();
	float cx = 0, cy = 0;
	if (!isStartGame)
	{
		if (curentTime - timeStart >= WAITING_TIME_BEFORE_SCROLLING)
		{
			isStartGame = true;
		}
	}
	else
	{
		game->GetCamPos(cx, cy);
		cx += VX_SCROLLING * dt;
	}

	game->SetCamPos(cx, cy);
}

void CPlayScene::Update(DWORD dt)
{
	if (!player)
		return;
	if (player->GetState() == MARIO_STATE_DIE)
	{
		if (this->timerWhenPlayerDie == -1) // if player is not dead yet
		{
			this->timerWhenPlayerDie = GetTickCount64();
			GameManager::GetInstance()->PauseToTransform();
			// reset level mario to small
			GameManager::GetInstance()->SetCurLevel(MARIO_LEVEL_SMALL);
		}
		else if (GetTickCount64() - timerWhenPlayerDie >= TIME_FOR_DELAY)
		{
			Reload();
			this->timerWhenPlayerDie = -1; // reset timer
			GameManager::GetInstance()->ResumeWhenDoneTransform();
		}
		else
		{
			player->Update(dt);
			return;
		}
	}
	CMario* mario = dynamic_cast<CMario*>(player);
	if (mario && (mario->IsEntryPipe() || mario->IsPrepareEntry()))
	{
		GameManager::GetInstance()->PauseToTransform();
	}
	else if (mario && this->timerWhenPlayerDie == -1 && !mario->IsPowerUp()) // if player is dead, we don't update the scene
		GameManager::GetInstance()->ResumeWhenDoneTransform();
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
		if (!GameManager::GetInstance()->IsPausedToTransform() || objects[i]->IsUpdateWhenMarioTransform())
			objects[i]->Update(dt, &coObjects);

	}
	for (size_t i = 0; i < UserInterfaces.size(); i++)
	{
		//if (i != 0 && GameClock::GetInstance()->IsTempPaused())
		//	break;

		if (GameManager::GetInstance()->IsPausedGame())
			return;
		if (!GameManager::GetInstance()->IsPausedToTransform() || objects[i]->IsUpdateWhenMarioTransform())
			UserInterfaces[i]->Update(dt, &coObjects);

	}

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;

	int currentMap = CGame::GetInstance()->GetCurrentScene()->GetID();
	if (currentMap != 8)
	{
		// Update camera to follow mario
		CinemachineCamera();
	}
	else
	{
		// Update camera to scrolling
		ScrollingCamera(dt);
	}

	KeepCameraAlwaysRight(currentMap);
	float camX, camY;
	CGame::GetInstance()->GetCamPos(camX, camY);
	//DebugOut(L"cam pos x = %f, y =%f\n", camX, camY);
	//CGame::GetInstance()->SetCamPos(cx, cy);

	PurgeDeletedObjects();

}
void CPlayScene::KeepCameraAlwaysRight(int curentMap)
{
	CGame* game = CGame::GetInstance();
	float cx, cy;
	game->GetCamPos(cx, cy);

	switch (curentMap)
	{
	case 6:
		if (cx < 0) cx = 0;
		if (cx > 2600) cx = 2580;
		if (cy > -17) cy = -17;
		if (cy < -250) cy = -250;
		break;
	case 7:
		if (cx < 2) cx = 2;
		if (cx > 200) cx = 200;
		if (cy < 0) cy = 0;
		if (cy > 4) cy = 4;
		break;
	case 8:

		if (cx > 1800) cx = 1800;
		break;
	case 9:
		if (cx < 10) cx = 10;
		if (cx > 230) cx = 230;
		if (cy > 7) cy = 7;
		if (cy < -50) cy = -50;
		break;
	}

	game->SetCamPos(cx, cy);
}

void CPlayScene::Render()
{
	for (int i = 1; i < objects.size(); i++)
	{
		curObject = objects[i];
		if (GameManager::GetInstance()->IsPausedGame() && !curObject->IsRenderWhenPaused())
			continue;
		objects[i]->Render();
	}
	//if(!GameClock::GetInstance()->IsPaused())
	if (!this->objects.empty())
		curObject = objects[0];
	else
		return;
	if (!(GameManager::GetInstance()->IsPausedGame() && !curObject->IsRenderWhenPaused()))
		objects[0]->Render();

	for (int i = 0; i < UserInterfaces.size(); i++)
	{
		curObject = UserInterfaces[i];
		UserInterfaces[i]->Render();
	}
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
	for (it = UserInterfaces.begin(); it != UserInterfaces.end(); it++)
	{
		delete(*it);
	}
	UserInterfaces.clear();
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
	for (int i = 0; i < UserInterfaces.size(); i++)
		delete UserInterfaces[i];

	UserInterfaces.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

bool CPlayScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

void CPlayScene::DeleteFadeTransition()
{
	int sizeOfObjects = objects.size();
	if (sizeOfObjects == 0) return; // no objects to delete
	CGameObject* fadeTransition = nullptr;
	fadeTransition = dynamic_cast<CGameObject*>(objects[sizeOfObjects - 1]);
	if (fadeTransition)
		fadeTransition->Delete();
}

void CPlayScene::Reload()
{
	Unload();
	GameManager::GetInstance()->AddLives(-1); // decrease lives by 1
	int remainLives = GameManager::GetInstance()->GetLives();
	if (remainLives < 0)
	{
		// reset game
		GameManager::GetInstance()->Reset();
		CGame::GetInstance()->InitiateSwitchScene(6);
	}
	else
	{
		// reload current scene
		GameManager::GetInstance()->ResetTime();
		//Load();
		CGame::GetInstance()->InitiateSwitchScene(this->id);
	}
}


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