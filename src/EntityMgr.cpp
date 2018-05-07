/*
 * EntityMgr.cpp
 *
 *  Created on: Feb 7, 2018
 *      Author: sushil
 */

#include <EntityMgr.h>
#include <Engine.h>

EntityMgr::EntityMgr(Engine *eng): Mgr(eng){
	selectedEntity = 0;
	count = 0;
	selectedEntityIndex = -1;
	projectileCount = 0;
	projectileEntity = NULL;
}

EntityMgr::~EntityMgr(){}

void EntityMgr::CreateEntity(std::string meshfilename, Ogre::Vector3 pos){
	Entity381 *ent = new Entity381(this->engine, meshfilename, pos, count);
	count++;
	entities.push_back(ent);
}

void EntityMgr::CreateCarrier(Ogre::Vector3 pos){
	Carrier *ent = new Carrier(this->engine, "cvn68.mesh", pos, count);
	count++;
	entities.push_back((Entity381 *) ent);
	shipEntity = entities.back();
}

void EntityMgr::CreateRobot(Ogre::Vector3 pos){
	Robot *ent = new Robot(this->engine, "robot.mesh", pos, count);
	count++;
	entities.push_back((Entity381 *) ent);
}

void EntityMgr::SelectNextEntity(bool plus){
	if(selectedEntityIndex >= count - 1) {
		selectedEntityIndex = 0;
	} else {
		selectedEntityIndex++;
	}
	if(selectedEntity != 0 && plus == true && selectedEntity->isSelected == true)
		selectedEntity->isSelected = false;
	selectedEntity = entities[selectedEntityIndex];
	selectedEntity->isSelected = true;
}

void EntityMgr::CreateProjectile(Ogre::Vector3 pos){
	Projectile *ent = new Projectile(this->engine, "sphere.mesh", pos, count);
	projectileCount++;
	projectiles.push_back((Entity381 *) ent);

}

void EntityMgr::CreateEntityOfTypeAtPosition(EntityTypes entType, Ogre::Vector3 pos){

	switch(entType){

	case CarrierType:
		CreateCarrier(pos);
		break;

	case RobotType:
		CreateRobot(pos);
		break;

	case ProjectileType:
		CreateProjectile(pos);
		break;

	default:
		CreateEntity("robot.mesh", pos);
		break;
	}
}

void EntityMgr::Tick(float dt){
	for(int i = 0; i < count; i++){
		entities[i]->Tick(dt);
	}
	for(int i = 0; i < projectileCount; i++){
		projectiles[i]->Tick(dt);
	}

}
