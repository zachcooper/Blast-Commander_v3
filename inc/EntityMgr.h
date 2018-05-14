#ifndef __EntityMgr_h_
#define __EntityMgr_h_

#include <vector>
#include <Mgr.h>
#include <Entity381.h>
#include <Types381.h>
#include <OgreVector3.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>

class EntityMgr: public Mgr {
public:
  EntityMgr(Engine *engine);
  virtual ~EntityMgr();

  //Engine *engine;

  std::vector<Entity381*> entities;
  std::vector<Entity381*> projectiles;
  std::vector<Entity381*> enemyProjectiles;
  Entity381* selectedEntity;
  int selectedEntityIndex;
  Entity381* shipEntity;
  Entity381* projectileEntity;
  Entity381* enemyProjectile;


  //Ogre::SceneManager *sceneMgr;

  void CreateEntityOfTypeAtPosition(EntityTypes type, Ogre::Vector3 pos);
  void SelectNextEntity(bool plus);

  void Tick(float dt);

protected:

private:
  void CreateEntity(std::string meshfilename, Ogre::Vector3 pos);
  void CreateCarrier(Ogre::Vector3 pos);
  void CreateRobot(Ogre::Vector3 pos);
  void CreateProjectile(Ogre::Vector3 pos);
  void CreateEnemyProjectile(Ogre::Vector3 pos);
  int count;
  int projectileCount;
  int enemyProjectileCount;

};

#endif // #ifndef __EntityMgr_h_
