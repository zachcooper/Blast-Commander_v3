/*
 * AnimationMgr.cpp
 *
 *  Created on: Apr 24, 2018
 *      Author: zachcooper
 */

#include <AnimationMgr.h>
#include <cstdlib>
#include <ctime>

AnimationMgr::AnimationMgr(Engine *engine): Mgr(engine) {
    mWalkSpeed = 70.0;
    startFix = false;
}

AnimationMgr::~AnimationMgr(){

}

void AnimationMgr::Init(){
	srand(time(NULL));
    createFrameListener();
}

void AnimationMgr::LoadLevel(){

}

bool AnimationMgr::nextLocation(Entity381* entity){
/*
	float rand1 = rand()%3000 - 400;
	float rand2 =  entity->sceneNode->getPosition().y;
	float rand3 = rand()%3000 - 400;
	entity->mDestination = Ogre::Vector3(rand1, rand2, rand3);

	entity->mDirection = entity->mDestination - entity->sceneNode->getPosition();
	entity->mDistance = entity->mDirection.normalise();
	//startFix = true;
*/

	for (unsigned int i = 0; i < engine->entityMgr->entities.size(); i ++){
		if (engine->entityMgr->entities[i]->meshfilename == "robot.mesh"){
			float rand1 = rand()%10000 - 800;
			float rand2 =  engine->entityMgr->entities[i]->sceneNode->getPosition().y;
			float rand3 = rand()%10000 - 800;
			engine->entityMgr->entities[i]->mDestination = Ogre::Vector3(rand1, rand2, rand3);
		}
	}

	for (unsigned int i = 0; i < engine->entityMgr->entities.size(); i ++){
		if (engine->entityMgr->entities[i]->meshfilename == "robot.mesh"){
			engine->entityMgr->entities[i]->mDirection = engine->entityMgr->entities[i]->mDestination - engine->entityMgr->entities[i]->sceneNode->getPosition();
			engine->entityMgr->entities[i]->mDistance = engine->entityMgr->entities[i]->mDirection.normalise();
		}
	}
    return true;
}

void AnimationMgr::createFrameListener(void){
    engine->gfxMgr->mRoot->addFrameListener(this);
	for (unsigned int i = 0; i < engine->entityMgr->entities.size(); i ++){
		if (engine->entityMgr->entities[i]->meshfilename == "robot.mesh"){
			engine->entityMgr->entities[i]->mAnimation = engine->entityMgr->entities[i]->ogreEntity->getAnimationState("Idle");
			engine->entityMgr->entities[i]->mAnimation->setLoop(true);
			engine->entityMgr->entities[i]->mAnimation->setEnabled(true);
			engine->entityMgr->entities[i]->mDirection = Ogre::Vector3::ZERO;
		}
	}
}

void AnimationMgr::Tick(float dt){
	for (unsigned int i = 0; i < engine->entityMgr->entities.size(); i ++){
		if (engine->entityMgr->entities[i]->meshfilename == "robot.mesh"){
			engine->entityMgr->entities[i]->sceneNode->setPosition(engine->entityMgr->entities[i]->sceneNode->getPosition().x,
					engine->gameMgr->mTerrainGroup->getHeightAtWorldPosition(engine->entityMgr->entities[i]->sceneNode->getPosition()),
					engine->entityMgr->entities[i]->sceneNode->getPosition().z);
		}
	}
}

void AnimationMgr::fixOrientation(Entity381* robot, Ogre::Vector3 source){
	if ((1.0f + source.dotProduct(robot->mDirection)) < 0.0001f) {
		robot->sceneNode->yaw(Ogre::Degree(180));

	}
	else{
		Ogre::Quaternion quat = source.getRotationTo(robot->mDirection);
		robot->sceneNode->rotate(quat);
	}
}

void AnimationMgr::Stop(){

}

bool AnimationMgr::frameRenderingQueued(const Ogre::FrameEvent &evt){

	for (unsigned int i = 0; i < engine->entityMgr->entities.size(); i ++){
		if (engine->entityMgr->entities[i]->meshfilename == "robot.mesh"){

			engine->entityMgr->entities[i]->mAnimation = engine->entityMgr->entities[i]->ogreEntity->getAnimationState("Walk");
			engine->entityMgr->entities[i]->mAnimation->setLoop(true);
			engine->entityMgr->entities[i]->mAnimation->setEnabled(true);
			engine->entityMgr->entities[i]->mAnimation->addTime(evt.timeSinceLastFrame);

			Ogre::Real move = mWalkSpeed * evt.timeSinceLastFrame;
			engine->entityMgr->entities[i]->mDistance -= move;
			if (engine->entityMgr->entities[i]->mDistance <= 0.0f){
				engine->entityMgr->entities[i]->sceneNode->setPosition(engine->entityMgr->entities[i]->mDestination);
				engine->entityMgr->entities[i]->mDirection = Ogre::Vector3::ZERO;
				if (!nextLocation(engine->entityMgr->entities[i])){
					engine->entityMgr->entities[i]->mAnimation = engine->entityMgr->entities[i]->ogreEntity->getAnimationState("Idle");
					engine->entityMgr->entities[i]->mAnimation->setLoop(true);
					engine->entityMgr->entities[i]->mAnimation->setEnabled(true);
					engine->entityMgr->entities[i]->mAnimation->addTime(evt.timeSinceLastFrame);

				}
				else{
					Ogre::Vector3 source = engine->entityMgr->entities[i]->sceneNode->getOrientation() * Ogre::Vector3::UNIT_X;
					if ((1.0f + source.dotProduct(engine->entityMgr->entities[i]->mDirection)) < 0.0001f){
						engine->entityMgr->entities[i]->sceneNode->yaw(Ogre::Degree(180));
					}
					else{
						Ogre::Quaternion quat = source.getRotationTo(engine->entityMgr->entities[i]->mDirection);
						engine->entityMgr->entities[i]->sceneNode->rotate(quat);
					}
				}
			}
			else{
				engine->entityMgr->entities[i]->sceneNode->translate(engine->entityMgr->entities[i]->mDirection * move);
			}
			Ogre::Vector3 source = engine->entityMgr->entities[i]->sceneNode->getOrientation() * Ogre::Vector3::UNIT_X;
			//engine->entityMgr->entities[i]->sceneNode->setPosition(engine->entityMgr->entities[i]->sceneNode->getPosition().x ,engine->gameMgr->mTerrainGroup->getHeightAtWorldPosition(engine->entityMgr->entities[i]->sceneNode->getPosition()),engine->entityMgr->entities[i]->sceneNode->getPosition().z );
			fixOrientation(engine->entityMgr->entities[i], source);
		}
	}

	return true;
}

bool AnimationMgr::keyPressed(const OIS::KeyEvent& ke){

	return true;
}

bool AnimationMgr::keyReleased(const OIS::KeyEvent& ke){
	  switch (ke.key)
	  {
	  case OIS::KC_1:

	    break;

	  default:
		  break;
	  }
	return true;
}

bool AnimationMgr::frameStarted(const Ogre::FrameEvent& evt){

	return true;
}

bool AnimationMgr::frameEnded(const Ogre::FrameEvent& evt){

	return true;
}


