#ifndef __Entity381_h_
#define __Entity381_h_

#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreVector3.h>
#include <Aspect.h>

#include <Engine.h>


class Entity381
{
public:
  Entity381(Engine *engine, std::string meshfilename, Ogre::Vector3 pos, int identity);
  virtual ~Entity381();

  Engine *engine;

  //static data
  int identity;
  std::string name;
  std::string meshfilename;
  Ogre::SceneNode* sceneNode;
  Ogre::Entity*    ogreEntity;
  float acceleration, turnRate;
  float minSpeed, maxSpeed;
  Ogre::Real mWalkSpeed;

  // flying
  float altitude, desiredAltitude, climbRate;

  //dynamic data
  Ogre::Vector3 position;
  Ogre::Vector3 velocity;
  bool isSelected;
  float desiredHeading, desiredSpeed;
  float heading, speed;

  // robots
  Ogre::Vector3 mDirection;
  Ogre::Vector3 mDestination;
  Ogre::Real mDistance;
  Ogre::AnimationState* mAnimation;

  //sound
	std::string soundFile;
	bool playSound;
	unsigned int audioId;
	bool didSelectSoundPlay;

  std::vector<Aspect* > aspects;

  void Tick(float dt);

protected:


};

class Carrier: Entity381 {
public:
	Carrier(Engine *engine, std::string meshfilename, Ogre::Vector3 pos, int identity);
	virtual ~Carrier();

};

class Robot: Entity381 {
public:
	Robot(Engine *engine, std::string meshfilename, Ogre::Vector3 pos, int identity);
	virtual ~Robot();

};

class Projectile: public Entity381
{
public:
	Projectile(Engine *engine, std::string meshfilename, Ogre::Vector3 pos, int identity);
	virtual ~Projectile();

};

#endif // #ifndef __Entity381_h_
