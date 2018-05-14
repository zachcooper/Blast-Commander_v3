/*
 * UiMgr.h
 *
 *  Created on: Apr 12, 2017
 *      Author: chad
 */

#ifndef INC_UIMGR_H_
#define INC_UIMGR_H_

#include <OgreWindowEventUtilities.h>
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include <Mgr.h>

#include <SdkTrays.h>
#include <string>
#include <Command.h>
#include <UnitAI.h>

class UiMgr : public Mgr, public Ogre::FrameListener, public OIS::KeyListener, public OIS::MouseListener, public Ogre::WindowEventListener, public OgreBites::SdkTrayListener
{
private:


	OgreBites::ProgressBar * pbar;
	OgreBites::ProgressBar * ebar;
	OgreBites::Label* scoreLabel;
	OgreBites::Label* livesLabel;

	Ogre::Timer* timer;

protected:
	virtual void windowResized(Ogre::RenderWindow *rw);
	virtual void windowClosed(Ogre::RenderWindow *rw);

    virtual bool keyPressed(const OIS::KeyEvent &arg);
    virtual bool keyReleased(const OIS::KeyEvent &arg);
    virtual bool mouseMoved(const OIS::MouseEvent &arg);
    virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
    virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

    void buttonHit(OgreBites::Button *b);
    void Splash();
    void Hide();

public:

	UiMgr(Engine *engine);
	~UiMgr();
	virtual void Init();
	virtual void Tick(float dt);
	virtual void LoadLevel();
	virtual void stop();

	OgreBites::InputContext mInputContext;
	OgreBites::SdkTrayManager* mTrayMgr;
	Ogre::OverlaySystem* mOverlaySystem;
	OgreBites::Label *mLabel;
	int score;
	int highScore;
	int lives;
	std::string scoreString;
	Ogre::Real health;
	Ogre::Real enemyHealth;

};

#endif /* INC_UIMGR_H_ */
