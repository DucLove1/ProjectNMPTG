#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Leaf.h"
#include "Mushroom.h"
#include "BouncingCoin.h"
//#include "Koopas.h"


class CPlayScene: public CScene
{
private:
	CGameObject* curObject; // current object being edited
	ULONGLONG timerWhenPlayerDie;
protected: 
	// A play scene has to have player, right? 
	LPGAMEOBJECT player;					

	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> UserInterfaces;

	ULONGLONG timeStart;
	BOOLEAN isStartGame; //for scrollingCamera

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);

	void LoadAssets(LPCWSTR assetFile);
	
public: 
	CPlayScene(int id, LPCWSTR filePath, int worldIndex);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	LPGAMEOBJECT GetPlayer() { return player; }

	void CinemachineCamera();
	void ScrollingCamera(DWORD dt);
	void KeepCameraAlwaysRight(int curentMap);

	void Clear();
	void PurgeDeletedObjects();
	void AddObject(LPGAMEOBJECT obj);
	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
	CGameObject* GetCurObject() { return curObject; }
	void DeleteFadeTransition();
	void Reload();
};

typedef CPlayScene* LPPLAYSCENE;

