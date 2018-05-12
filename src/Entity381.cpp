/*
 * Entity381.cpp
 *
 *  Created on: Feb 7, 2018
 *      Author: sushil
 */

#include <GfxMgr.h>

#include<Entity381.h>
#include<Physics2D.h>

std::string IntToString(int x){
	char tmp[10000];
	sprintf(tmp, "%i", x);
	return std::string(tmp);
}



Entity381::Entity381(Engine *engine, std::string meshfname, Ogre::Vector3 pos, int ident){

	this->engine = engine;


	meshfilename = meshfname;
	position = pos;
	velocity = Ogre::Vector3(0, 0, 0);
	identity = ident;
	isSelected = false;

	name = meshfname + IntToString(identity);

	ogreEntity = engine->gfxMgr->mSceneMgr->createEntity(meshfilename);
	sceneNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(pos);
	sceneNode->attachObject(ogreEntity);

	Physics2D* phx = new Physics2D(this);
	aspects.push_back((Aspect*) phx);

	if(meshfname != "banshee.mesh" )
	{
		Renderable * renderable = new Renderable(this);
		aspects.push_back((Aspect*)renderable);
	}
	else
	{
		ShipRenderable * shipRenderable = new ShipRenderable(this);
		aspects.push_back((Aspect*)shipRenderable);
	}


	unitAI = new UnitAI(this);
	aspects.push_back((Aspect*) unitAI);

	this->acceleration = 0;
	this->desiredHeading = this->heading = 0;
	this->turnRate = 0;
	this->desiredSpeed = this->speed = 0;
	this->minSpeed = this->maxSpeed = 0;
	this->altitude = 0;
	this->desiredAltitude = 0;
	this->climbRate = 0;

	this->playSound = false;
	this->didSelectSoundPlay = false;
	this->soundFile = "BoatSound.wav";
	this->audioId = 0;

    this->mDirection == Ogre::Vector3::ZERO;
    this->mDestination== Ogre::Vector3::ZERO;
    this->mDistance = 0;
    this->mAnimation = 0;

	this->mWalkSpeed = 5;
}

Entity381::~Entity381(){

}

void Entity381::Tick(float dt){
	for(unsigned int i = 0; i < aspects.size(); i++){
		aspects[i]->Tick(dt);
	}
}

//-------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------
Carrier::Carrier(Engine *engine, std::string meshfname, Ogre::Vector3 pos, int ident):
		Entity381(engine, meshfname, pos, ident){
	this->minSpeed = 0;
	this->maxSpeed = 20.0f;//meters per second...
	this->acceleration = 10.0f; // slow
	this->turnRate = 20.0f; //2 degrees per second
	this->altitude = 700;
	this->desiredAltitude = 0;
	this->climbRate = 0;

	this->playSound = true;
	this->didSelectSoundPlay = false;
	this->soundFile = "BoatSound.wav";
	this->audioId = 1;

	ShipPhysics2D* shipPhx = new ShipPhysics2D(this);
	aspects.push_back((Aspect*) shipPhx);

}

Carrier::~Carrier(){

}
//-------------------------------------------------------------------------------------------------------------------------------
Robot::Robot(Engine *engine, std::string meshfname, Ogre::Vector3 pos, int ident):
		Entity381(engine, meshfname, pos, ident){

}

Robot::~Robot(){

}

Projectile::Projectile(Engine *engine, std::string meshfname, Ogre::Vector3 pos, int ident):
		Entity381(engine, meshfname, pos, ident){
	sceneNode->setScale(Ogre::Real(0.05), Ogre::Real(0.05), Ogre::Real(0.05));

	ogreEntity->setMaterialName("Projectile");

}

Projectile::~Projectile()
{

}



//-------------------------------------------------------------------------------------------------------------------------------


