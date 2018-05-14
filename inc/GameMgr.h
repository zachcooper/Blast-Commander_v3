/*
 * GameMgr.h
 *
 *  Created on: Mar 4, 2018
 *      Author: sushil
 */

#ifndef GAMEMGR_H_
#define GAMEMGR_H_

#include <Mgr.h>
#include <Terrain/OgreTerrain.h>
#include <Terrain/OgreTerrainGroup.h>

class GameMgr: public Mgr {
public:
	GameMgr(Engine *engine);
	virtual ~GameMgr();

	void Init();
	void LoadLevel();
	void Tick(float dt);

	void MakeGround();
	void MakeSky();
	void MakeEntities();
	void createGrassMesh();
	void MakeProjectiles();

	Ogre::SceneNode *cameraNode;
	Ogre::Plane myPlane;

	//terrain
    void defineTerrain(long x, long y);
    void initBlendMaps(Ogre::Terrain* terrain);
    void configureTerrainDefaults(Ogre::Light* light);

    bool mTerrainsImported;
    Ogre::TerrainGroup* mTerrainGroup;
    Ogre::TerrainGlobalOptions* mTerrainGlobals;
    Ogre::TerrainGroup* mTerrainGroup2;
    Ogre::TerrainGlobalOptions* mTerrainGlobals2;

    bool levelTwo;
    float mapSize;
    bool todo;

    //OgreBites::Label* mInfoLabel;

};

#endif /* GAMEMGR_H_ */
