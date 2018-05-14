/*
 * GameMgr.cpp
 *
 *  Created on: Mar 4, 2018
 *      Author: sushil
 */
#include <Engine.h>

#include <EntityMgr.h>
#include <GameMgr.h>
#include <GfxMgr.h>
#include <string>


#include <iostream>
#include <Types381.h>

#include <OgreOverlay.h>
#include <OgreSceneNode.h>
#include <OgreMeshManager.h>
#include <OgreManualObject.h>
#include <OgreStaticGeometry.h>

GameMgr::GameMgr(Engine *engine): Mgr(engine) {
	cameraNode = 0;
	levelTwo = false;
	todo = true;
}

GameMgr::~GameMgr() {
	// TODO Auto-generated destructor stub
}

void GameMgr::Init(){

}

void GameMgr::Tick(float dt){
	if(engine->uiMgr->score >= engine->uiMgr->highScore && todo){
		levelTwo = true;
		LoadLevel();
		todo = false;
	}
}

void GameMgr::LoadLevel(){
	  //CEGUI::OgreRenderer* mRenderer;
	  std::string lightString;
	  Ogre::Light* light;
	  Ogre::Light* light2;

	  if(levelTwo){
		  mapSize = 12000.0;
		  lightString = "TestLight2";
	  }
	  else{
		  mapSize = 40000.0;
		  lightString = "TestLight";
	  }

	  engine->gfxMgr->mSceneMgr->setAmbientLight(Ogre::ColourValue(0.3, 0.3, 0.4));
	  engine->gfxMgr->mCamera->lookAt(Ogre::Vector3(0, 0, 0));

	  Ogre::Vector3 lightDir(.55, -.3, .75);
	  lightDir.normalise();

	  if(levelTwo == false){
		  light = engine->gfxMgr->mSceneMgr->createLight(lightString);
		  light->setType(Ogre::Light::LT_DIRECTIONAL);
		  light->setDirection(lightDir);
		  light->setDiffuseColour(Ogre::ColourValue::White);
		  light->setSpecularColour(Ogre::ColourValue(.4, .4, .4));
	  }
	  else{
		  light2 = engine->gfxMgr->mSceneMgr->createLight(lightString);
		  light2->setType(Ogre::Light::LT_DIRECTIONAL);
		  light2->setDirection(lightDir);
		  light2->setDiffuseColour(Ogre::ColourValue::White);
		  light2->setSpecularColour(Ogre::ColourValue(.4, .4, .4));
	  }

	  // A node to attach the camera to so we can move the camera node instead of the camera.
	  if(levelTwo == false){
		  cameraNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode();
		  cameraNode->setPosition(500, 600, 1500);
		  cameraNode->attachObject(engine->gfxMgr->mCamera);
	  }

	  // Terrain
	  mTerrainGlobals = OGRE_NEW Ogre::TerrainGlobalOptions();

	  if(levelTwo == false){
		  mTerrainGroup = OGRE_NEW Ogre::TerrainGroup(
		    engine->gfxMgr->mSceneMgr,
		    Ogre::Terrain::ALIGN_X_Z,
		    513, mapSize);
		  mTerrainGroup->setFilenameConvention(Ogre::String("terrain"), Ogre::String("dat"));
		  mTerrainGroup->setOrigin(Ogre::Vector3::ZERO);
		  configureTerrainDefaults(light);
		  for (long x = 0; x <= 0; ++x)
		    for (long y = 0; y <= 0; ++y)
		      defineTerrain(x, y);
	  }
	  else{
		  mTerrainGroup->unloadTerrain(0,0);
		  mTerrainGroup = OGRE_NEW Ogre::TerrainGroup(
			 engine->gfxMgr->mSceneMgr,
	         Ogre::Terrain::ALIGN_X_Z,
		     513, mapSize);
		  mTerrainGroup->setFilenameConvention(Ogre::String("terrain"), Ogre::String("dat"));
		  mTerrainGroup->setOrigin(Ogre::Vector3::ZERO);
		  configureTerrainDefaults(light2);
		  for (long x = 0; x <= 0; ++x)
			  for (long y = 0; y <= 0; ++y)
				  defineTerrain(x, y);
		  }

	  mTerrainGroup->loadAllTerrains(true);

	  if (mTerrainsImported)
	  {
	    Ogre::TerrainGroup::TerrainIterator ti = mTerrainGroup->getTerrainIterator();
        while (ti.hasMoreElements())
	    {
	      Ogre::Terrain* t = ti.getNext()->instance;
	      initBlendMaps(t);
	    }
	  }

	  mTerrainGroup->freeTemporaryResources();

	  if(levelTwo == false){
		  MakeEntities();
		  MakeProjectiles();
		  cameraNode->setPosition(500, engine->gameMgr->mTerrainGroup->getHeightAtWorldPosition(engine->gameMgr->cameraNode->getPosition()) + 100, 1500);
	  }


	  if (levelTwo == false){
		  engine->gfxMgr->mSceneMgr->setSkyDome(true, "Examples/CloudySky");
	  }
	  else{
		  engine->gfxMgr->mSceneMgr->setSkyDome(false, "");
		  engine->gfxMgr->mSceneMgr->setSkyBox(true, "Examples/MorningSkyBox");
	  }

}

void getTerrainImage(bool flipX, bool flipY, Ogre::Image& img)
{
  img.load("terrain.png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

  if (flipX)
    img.flipAroundY();
  if (flipY)
    img.flipAroundX();
}

void GameMgr::defineTerrain(long x, long y)
{
  Ogre::String filename = mTerrainGroup->generateFilename(x, y);

  bool exists =
    Ogre::ResourceGroupManager::getSingleton().resourceExists(
      mTerrainGroup->getResourceGroup(),
      filename);

  if (exists)
    mTerrainGroup->defineTerrain(x, y);
  else
  {
    Ogre::Image img;
    getTerrainImage(x % 2 != 0, y % 2 != 0, img);
    mTerrainGroup->defineTerrain(x, y, &img);

    mTerrainsImported = true;
  }
}

void GameMgr::initBlendMaps(Ogre::Terrain* terrain)
{
  Ogre::Real minHeight0 = 70;
  Ogre::Real fadeDist0 = 40;
  Ogre::Real minHeight1 = 70;
  Ogre::Real fadeDist1 = 15;

  Ogre::TerrainLayerBlendMap* blendMap0 = terrain->getLayerBlendMap(1);
  Ogre::TerrainLayerBlendMap* blendMap1 = terrain->getLayerBlendMap(2);

  float* pBlend0 = blendMap0->getBlendPointer();
  float* pBlend1 = blendMap1->getBlendPointer();

  for (Ogre::uint16 y = 0; y < terrain->getLayerBlendMapSize(); ++y)
  {
    for (Ogre::uint16 x = 0; x < terrain->getLayerBlendMapSize(); ++x)
    {
      Ogre::Real tx, ty;

      blendMap0->convertImageToTerrainSpace(x, y, &tx, &ty);
      Ogre::Real height = terrain->getHeightAtTerrainPosition(tx, ty);
      Ogre::Real val = (height - minHeight0) / fadeDist0;
      val = Ogre::Math::Clamp(val, (Ogre::Real)0, (Ogre::Real)1);
      *pBlend0++ = val;

      val = (height - minHeight1) / fadeDist1;
      val = Ogre::Math::Clamp(val, (Ogre::Real)0, (Ogre::Real)1);
      *pBlend1++ = val;
    }
  }

  blendMap0->dirty();
  blendMap1->dirty();
  blendMap0->update();
  blendMap1->update();

}

void GameMgr::configureTerrainDefaults(Ogre::Light* light)
{
	std::string diffuse1;
	std::string diffuse2;
	std::string diffuse3;

	std::string normal1;
	std::string normal2;
	std::string normal3;
	float worldSize = 0.0;

  if(levelTwo == false){
	diffuse1 = "grass_green-01_diffusespecular.dds";
	diffuse2 = "grass_green-01_diffusespecular.dds";
	diffuse3 = "grass_green-01_diffusespecular.dds";
	normal1 = "grass_green-01_normalheight.dds";
	normal2 = "grass_green-01_normalheight.dds";
	normal3 = "grass_green-01_normalheight.dds";
	worldSize = 40000.0;
  }
  else{
	diffuse1 = "dirt_grayrocky_diffusespecular.dds";
	diffuse2 = "grass_green-01_diffusespecular.dds";
	diffuse3 = "growth_weirdfungus-03_diffusespecular.dds";
	normal1 = "dirt_grayrocky_normalheight.dds";
	normal2 = "grass_green-01_normalheight.dds";
	normal3 = "growth_weirdfungus-03_normalheight.dds";
	worldSize = 12000.0;
  }
	mTerrainGlobals->setMaxPixelError(8);
	mTerrainGlobals->setCompositeMapDistance(3000);

	mTerrainGlobals->setLightMapDirection(light->getDerivedDirection());
	mTerrainGlobals->setCompositeMapAmbient(engine->gfxMgr->mSceneMgr->getAmbientLight());
	mTerrainGlobals->setCompositeMapDiffuse(light->getDiffuseColour());

	Ogre::Terrain::ImportData& importData = mTerrainGroup->getDefaultImportSettings();
	importData.terrainSize = 513;
	importData.worldSize = worldSize;
	importData.inputScale = 600;
	importData.minBatchSize = 33;
	importData.maxBatchSize = 65;

	importData.layerList.resize(3);
	importData.layerList[0].worldSize = 100;
	importData.layerList[0].textureNames.push_back(diffuse1);
	importData.layerList[0].textureNames.push_back(normal1);
	importData.layerList[1].worldSize = 30;
	importData.layerList[1].textureNames.push_back(diffuse2);
	importData.layerList[1].textureNames.push_back(normal2);
	importData.layerList[2].worldSize = 200;
	importData.layerList[2].textureNames.push_back(diffuse3);
	importData.layerList[2].textureNames.push_back(normal3);

}

void GameMgr::MakeEntities(){
	Ogre::Vector3 pos = Ogre::Vector3(-1000, 0, 0);
	Ogre::Vector3 position = Ogre::Vector3(-1000, 0, 0);
	Ogre::Vector3 enemyShipPos = Ogre::Vector3(0, 700, 0);

	for (int i = 0; i < 100; i++){
		engine->entityMgr->CreateEntityOfTypeAtPosition(RobotType, position);
		position.x += 500;
		if (i == 10){
			position = Ogre::Vector3(0, 0, 0);
		}
		else if(i == 20){
			position = Ogre::Vector3(0, 0, -1000);
		}
		else if(i == 30){
			position = Ogre::Vector3(0, 0, -2000);
		}
		else if(i == 40){
			position = Ogre::Vector3(0, 0, -3000);
		}
		else if(i == 50){
			position = Ogre::Vector3(0, 0, -4000);
		}
		else if(i == 60){
			position = Ogre::Vector3(0, 0, -5000);
		}
		else if(i == 70){
			position = Ogre::Vector3(0, 0, -6000);
		}
		else if(i == 80){
			position = Ogre::Vector3(0, 0, -7000);
		}
		else if(i == 90){
			position = Ogre::Vector3(0, 0, -8000);
		}
		else if(i == 100){
			position = Ogre::Vector3(0, 0, -9000);
		}
	}

	if(levelTwo == false){
	engine->entityMgr->CreateEntityOfTypeAtPosition(CarrierType, enemyShipPos);

	}
}

void GameMgr::MakeProjectiles()
{
	Ogre::Vector3 proj = engine->gameMgr->cameraNode->getPosition();
	Ogre::Vector3 enemyProj = Ogre::Vector3(0,-300,0);
	proj.y -= 10;
	//proj.z -= 500;
	size_t i;
	for(i = 0; i < 200; i++)
	{
		engine->entityMgr->CreateEntityOfTypeAtPosition(ProjectileType, proj);
	}


	for(i = 0; i < 1000; i++)
	{
		engine->entityMgr->CreateEntityOfTypeAtPosition(EnemyProjectileType, enemyProj);
	}


}

void GameMgr::MakeGround(){

	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);

	  Ogre::MeshManager::getSingleton().createPlane(
	    "ground",
	    Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	    plane,
	    15000, 15000, 20, 20,
	    true,
	    1, 5, 5,
	    Ogre::Vector3::UNIT_Z);

	  Ogre::Entity* groundEntity = engine->gfxMgr->mSceneMgr->createEntity("ground");
	  engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
	  groundEntity->setCastShadows(false);
	  //groundEntity->setMaterialName("Ocean2_HLSL_GLSL");
	  //groundEntity->setMaterialName("OceanHLSL_GLSL");
	  groundEntity->setMaterialName("Examples/GrassFloor");
	  //groundEntity->setMaterialName("NavyCg");

	  myPlane = plane;
}

void GameMgr::MakeSky(){
	if (levelTwo == false){
	engine->gfxMgr->mSceneMgr->setSkyDome(true, "Examples/CloudySky");
	}
	if(levelTwo){
		engine->gfxMgr->mSceneMgr->setSkyBox(true, "Examples/MorningSkyBox");

	}
}

void GameMgr::createGrassMesh()
{
	const float width = 25;
	const float height = 30;
	Ogre::Vector3 vec(width / 2, 0, 0);
	Ogre::ManualObject obj("GrassObject");

	Ogre::Quaternion quat;
	quat.FromAngleAxis(Ogre::Degree(60), Ogre::Vector3::UNIT_Y);

	obj.begin("Examples/GrassBlades", Ogre::RenderOperation::OT_TRIANGLE_LIST);

	for (int i = 0; i < 3; ++i)
	{
		obj.position(-vec.x, height, -vec.z);
		obj.textureCoord(0, 0);
		obj.position(vec.x, height, vec.z);
		obj.textureCoord(1, 0);
		obj.position(-vec.x, 0, -vec.z);
		obj.textureCoord(0, 1);
		obj.position(vec.x, 0, vec.z);
		obj.textureCoord(1, 1);

		int offset = 4 * i;
		obj.triangle(offset, offset + 3, offset + 1);
		obj.triangle(offset, offset + 2, offset + 3);

		vec = quat * vec;
	}

	obj.end();
	obj.convertToMesh("GrassBladesMesh");

	Ogre::Entity* grass = engine->gfxMgr->mSceneMgr->createEntity("GrassBladesMesh");
	Ogre::StaticGeometry* sg = engine->gfxMgr->mSceneMgr->createStaticGeometry("GrassArea");

	const int size = 15000;
	const int amount = 200;

	sg->setRegionDimensions(Ogre::Vector3(size, size, size));
	sg->setOrigin(Ogre::Vector3(-size/2, 0, -size/2));

	for (int x = -size/2; x < size/2; x += (size / amount))
	{
	  for (int z = -size/2; z < size/2; z += (size / amount))
	  {
		Ogre::Real r = size / (float)amount / 2;
		Ogre::Vector3 pos(
	x + Ogre::Math::RangeRandom(-r, r),
	0,
	z + Ogre::Math::RangeRandom(-r, r));

		Ogre::Vector3 scale(1, Ogre::Math::RangeRandom(0.9, 1.1), 1);

		Ogre::Quaternion orientation;
		orientation.FromAngleAxis(
	Ogre::Degree(Ogre::Math::RangeRandom(0, 359)),
	Ogre::Vector3::UNIT_Y);

		sg->addEntity(grass, pos, orientation, scale);
	  }
	}
	sg->build();
}
