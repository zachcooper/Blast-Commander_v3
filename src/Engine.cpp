/*
 * Engine.cpp
 *
 *  Created on: Mar 4, 2018
 *      Author: sushil
 */

#include <Engine.h>

Engine::Engine() {
	gfxMgr    = 0;
	entityMgr = 0; //null
	gameMgr   = 0;
	inputMgr  = 0;
	uiMgr = 0;
	animationMgr = 0;
	soundMgr = 0;

	keepRunning = true;

}

Engine::~Engine() {

}

void Engine::Init(){
	gfxMgr    = new GfxMgr(this);
	entityMgr = new EntityMgr(this);
	gameMgr   = new GameMgr(this);
	inputMgr  = new InputMgr(this);
	uiMgr 	  = new UiMgr(this);
	animationMgr = new AnimationMgr(this);
	soundMgr = new OgreSND::SoundMgr(this);

	//--------------------------------------------------------------
	gfxMgr->Init();
	entityMgr->Init();
	inputMgr->Init(); // must initialize AFTER gfx manager
	gameMgr->Init();
	uiMgr->Init();
	animationMgr->Init();
	soundMgr->init();

	//--------------------------------------------------------------
	gfxMgr->LoadLevel();
	entityMgr->LoadLevel();
	inputMgr->LoadLevel();
	gameMgr->LoadLevel();
	uiMgr->LoadLevel();
	animationMgr->LoadLevel();
	soundMgr->loadLevel();
}


void Engine::TickAll(float dt){
	gfxMgr->Tick(dt);
	inputMgr->Tick(dt);
	entityMgr->Tick(dt);
	gameMgr->Tick(dt);
	uiMgr->Tick(dt);
	animationMgr->Tick(dt);
	soundMgr->tick(dt);
}


void Engine::Run(){
	const float MICROSECONDS_PER_SECOND = 1000000.0f;
	Ogre::Timer* timer = new Ogre::Timer();

	float oldTime = timer->getMicroseconds()/MICROSECONDS_PER_SECOND;
	float newTime = timer->getMicroseconds()/MICROSECONDS_PER_SECOND;
	float dt = newTime - oldTime;

	while(keepRunning){

		TickAll(dt);

		newTime = timer->getMicroseconds()/MICROSECONDS_PER_SECOND;
		dt = newTime - oldTime;
		oldTime = newTime;

	}
	// main must call cleanup or bad stuff happens->Cleanup()
}

void Engine::Cleanup(){
	inputMgr->Stop();
	gfxMgr->Stop();
	entityMgr->Stop();
	gameMgr->Stop();
	uiMgr->Stop();
	animationMgr->Stop();
	soundMgr->Stop();
}

