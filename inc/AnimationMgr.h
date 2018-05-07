/*
 * AnimationMgr.h
 *
 *  Created on: Apr 24, 2018
 *      Author: zachcooper
 */

#ifndef INC_ANIMATIONMGR_H_
#define INC_ANIMATIONMGR_H_

#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreVector3.h>
#include <Aspect.h>
#include <Engine.h>
#include <EntityMgr.h>
#include <UiMgr.h>
#include <GfxMgr.h>
#include <GameMgr.h>
#include <InputMgr.h>
#include <deque>

class AnimationMgr :	public Mgr,
		public Ogre::WindowEventListener,
		public Ogre::FrameListener{
public:

	AnimationMgr(Engine *engine);
	virtual ~AnimationMgr();

	void Init();
	void LoadLevel();
	void Tick(float dt);
	void Stop();

    virtual void createFrameListener(void);
    virtual bool frameRenderingQueued(const Ogre::FrameEvent &evt);
    virtual bool keyPressed(const OIS::KeyEvent& ke);
    virtual bool keyReleased(const OIS::KeyEvent& ke);

    virtual bool nextLocation(Entity381* node);
    virtual bool frameStarted(const Ogre::FrameEvent& evt);
    virtual bool frameEnded(const Ogre::FrameEvent& evt);

    void fixOrientation(Entity381* robot, Ogre::Vector3 source);
    bool startFix;
    std::deque<Ogre::Vector3> mWalkList;
    Ogre::Real mWalkSpeed;
};




#endif /* INC_ANIMATIONMGR_H_ */
