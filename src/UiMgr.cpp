/*
 * UiMgr.cpp
 *
 *  Created on: Apr 12, 2017
 *      Author: chad
 */

#include <UiMgr.h>
#include <Engine.h>
#include <GfxMgr.h>
#include <InputMgr.h>
#include <EntityMgr.h>
#include <Types381.h>
#include <GameMgr.h>
#include <Entity381.h>
#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


UiMgr::UiMgr(Engine* eng): Mgr(eng){
	// Initialize the OverlaySystem (changed for Ogre 1.9)
	    mOverlaySystem = new Ogre::OverlaySystem();
	    engine->gfxMgr->mSceneMgr->addRenderQueueListener(mOverlaySystem);

	    //Ogre::WindowEventUtilities::addWindowEventListener(engine->gfxMgr->ogreRenderWindow, this);
	    health = 1.00;
	    enemyHealth = 1.00;
	    score = 0;
	    highScore = 100;
	    lives = 2;
}

UiMgr::~UiMgr(){ // before gfxMgr destructor

}

void UiMgr::Init(){
	//init sdktrays

    mInputContext.mKeyboard = engine->inputMgr->mKeyboard;
    //mInputContext.mMouse = engine->inputMgr->mMouse;
    mTrayMgr = new OgreBites::SdkTrayManager("InterfaceName", engine->gfxMgr->mWindow, mInputContext, this);
    //mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    //mTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);
    mTrayMgr->hideCursor();
}

void UiMgr::stop(){

}

void UiMgr::Splash()
{
	mTrayMgr->showBackdrop("Splash");
}

void UiMgr::Hide()
{
	mTrayMgr->hideLoadingBar();
}

void UiMgr::LoadLevel(){

	//Splash();
	//Hide();
	//mTrayMgr->showBackdrop("myUI");
	//enemyHealthButton = mTrayMgr->createButton(OgreBites::TL_RIGHT, "EnemyHealthButton", "Enemy Drain");

	//OgreBites::ProgressBar * pbar;
	pbar = mTrayMgr->createProgressBar(OgreBites::TL_BOTTOMLEFT,"HealthBar", "Health", 300, 200);
	pbar->setProgress(health);

	//OgreBites::ProgressBar * ebar;
	ebar = mTrayMgr->createProgressBar(OgreBites::TL_BOTTOMRIGHT,"EnemyHealthBar", "Enemy Health", 350, 200);
	ebar->setProgress(enemyHealth);

	std::stringstream ss2;
	ss2 << score;
	std::string str2 = ss2.str();
	scoreLabel = mTrayMgr->createLabel(OgreBites::TL_TOPRIGHT, "Score", str2, 150.0);

	std::stringstream ss3;
	ss3 << lives;
	std::string str3 = ss3.str();
	livesLabel = mTrayMgr->createLabel(OgreBites::TL_TOPLEFT, "Lives", str3, 150.0);

	mTrayMgr->hideAll();
	Splash();

	srand (time(NULL));



	Follow* follow;

	for(unsigned int i = 0; i < engine->entityMgr->entities.size(); i++)
	{
		if(engine->entityMgr->entities[i]->meshfilename == "banshee.mesh")
		{
			follow = new Follow(engine->entityMgr->entities[i], engine->gameMgr->cameraNode);
			engine->entityMgr->entities[i]->unitAI->followCommand = follow;
		}
	}


}

void UiMgr::Tick(float dt){
	//mTrayMgr->refreshCursor();

	Ogre::Vector3 diff;
	Ogre::Vector3 distance;
	Ogre::Vector3 projDiff;
	Ogre::Vector3 loc;
	Ogre::Vector3 groundPos;
	int random;


	for (unsigned int i = 0; i < engine->entityMgr->entities.size(); i++)
	{
		diff = engine->gameMgr->cameraNode->getPosition() - engine->entityMgr->entities[i]->sceneNode->getPosition();
		if(engine->entityMgr->entities[i] != engine->entityMgr->shipEntity)
		{
			if (diff.length() < 150.0)
			{
				health -= 0.001;
			}

			if(diff.length() < 2000.00)
			{

				random = rand() % 10000;
				if(random % 5077  == 0)
				{

				      if(!engine->entityMgr->enemyProjectiles.empty())
				      {
				    	  engine->entityMgr->enemyProjectile = engine->entityMgr->enemyProjectiles.back();
				          engine->entityMgr->enemyProjectiles.pop_back();
				          engine->entityMgr->enemyProjectile->position = engine->entityMgr->entities[i]->sceneNode->getPosition();
				          engine->entityMgr->enemyProjectile->position.y += 40;

				          diff.y -= 40;
				          engine->entityMgr->enemyProjectile->velocity = diff; //* 2;

				          //engine->soundMgr->playLaserSound(engine->entityMgr->projectileEntity);
				      }
				}
			}
		}

		if(engine->entityMgr->projectileEntity != NULL)
		{
			projDiff = engine->entityMgr->projectileEntity->sceneNode->getPosition() - engine->entityMgr->entities[i]->sceneNode->getPosition();
			if (projDiff.length() < 60.0)
			{
				engine->gfxMgr->mSceneMgr->destroySceneNode(engine->entityMgr->entities[i]->sceneNode);
				engine->entityMgr->entities.erase(engine->entityMgr->entities.begin() + i);
				score += 20;
				enemyHealth -= 0.01;
			}
		}
	}

	if(engine->inputMgr->mKeyboard->isKeyDown(OIS::KC_INSERT))
	{
		mTrayMgr->hideBackdrop();
		mTrayMgr->showBackdrop("Instructions");
	}

	if(engine->inputMgr->mKeyboard->isKeyDown(OIS::KC_RETURN))
	{
		mTrayMgr->hideBackdrop();
		mTrayMgr->showBackdrop("myUI");
		mTrayMgr->showAll();
	}

	ebar->setProgress(enemyHealth);
	pbar->setProgress(health);

	std::stringstream ss2;
	ss2 << score;
	std::string str2 = ss2.str();
	scoreLabel->setCaption(str2);

	std::stringstream ss3;
	ss3 << lives;
	std::string str3 = ss3.str();
	livesLabel->setCaption(str3);

	if(score > highScore)
	{
		mTrayMgr->hideAll();
		mTrayMgr->hideBackdrop();
		mTrayMgr->showBackdrop("End");
		highScore = 2000;
	}

	if(health < 0)
	{
		health = 1.0;
		lives--;
		if(lives < 0)
		{
			mTrayMgr->hideAll();
			mTrayMgr->hideBackdrop();
			mTrayMgr->showBackdrop("Died");
			health = 1.0;
			lives = 2;
		}

	}
}


void UiMgr::windowResized(Ogre::RenderWindow* rw){
	unsigned int width, height, depth;
	int left, top;
	rw->getMetrics(width, height, depth, left, top);

	const OIS::MouseState &ms = engine->inputMgr->mMouse->getMouseState();
	ms.width = width;
	ms.height = height;
}

void UiMgr::windowClosed(Ogre::RenderWindow* rw){

}

bool UiMgr::keyPressed(const OIS::KeyEvent &arg) {
	//std::cout << "Key Pressed: " << arg.key << std::endl;
	return true;
}
bool UiMgr::keyReleased(const OIS::KeyEvent &arg){
	return true;
}
bool UiMgr::mouseMoved(const OIS::MouseEvent &arg){
    //if (mTrayMgr->injectMouseMove(arg)) return true;
	return false;
}
bool UiMgr::mousePressed(const OIS::MouseEvent &me, OIS::MouseButtonID mid) {
	//std::cout << "mouse clicked" << std::endl;
	//if (mTrayMgr->injectMouseDown(me, mid)) return true;
	return false;
}
bool UiMgr::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id){
   //if (mTrayMgr->injectMouseUp(arg, id)) return true;
    /* normal mouse processing here... */
	return false;
}

void UiMgr::buttonHit(OgreBites::Button *b){

/*
    if(b->getName()=="StartButton")
    {
    	mTrayMgr->removeWidgetFromTray("StartButton");
		mTrayMgr->hideBackdrop();
		mTrayMgr->showBackdrop("myUI");
		mTrayMgr->showAll();

    }
    */
}


