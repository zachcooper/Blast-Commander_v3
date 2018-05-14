/*
 * SoundMgr.h
 *
 *  Created on: Oct 30, 2013
 *      Author: sushil
 */

#ifndef SOUNDMANAGER_H_
#define SOUNDMANAGER_H_


#include <iostream>
#include <cstring>
#include <vector>

#include <OgreVector3.h>
#include <OgreQuaternion.h>
#include <OgreFrameListener.h>

#include <wave.h>
#include <al.h>
#include <alc.h>
#include <Mgr.h>

class Entity381;

namespace OgreSND {
    const int soundPerEnt = 3;      // max different sounds to randomly choose per entity
	const int maxAudioBuffers = 63; // + 1 for background music
	const int maxAudioSources = 15; // + 1 for background music
	const std::string backgroundMusicFilename = "assets/sounds/Background1.wav";
	const std::string laserSoundFilename = "assets/sounds/LaserSound1.wav";
	const std::string laserSound2Filename = "assets/sounds/LaserSound2.wav";
	const std::string explosionSoundFilename = "assets/sounds/explosion.wav";
	const std::string explosionRobotSoundFilename = "assets/sounds/ExplosionRobot.wav";
	const std::string vehicleHitSoundFilename = "assets/sounds/VehicleHit.wav";

	typedef struct {
		ALuint source;
		bool   inUse;
	} SourceInfo;

	typedef struct {
		ALuint buffer;
		std::string bufferFilename;
		WaveInfo *wave;
	} BufferInfo;

	class SoundMgr : public Mgr , public Ogre::FrameListener {
	private:
		//OgreGFX::GraphicsInteractionManager *gim;
		ALCdevice  *device;
		ALCcontext *context;
		ALfloat position[3];
		ALfloat velocity[3];
		ALfloat orientation[6];

		//Buffers and Sources indices

		SourceInfo sourceInfo[maxAudioSources];
		BufferInfo  bufferInfo[maxAudioBuffers];

		//Special treatment for background source and buffer
		ALuint backgroundMusicBuffer, backgroundMusicSource;
		WaveInfo *backgroundWaveInfo;

		// Custom sound sources
        ALuint laserSoundSource, laserSound2Source;
        ALuint explosionSoundSource, explosionRobotSoundSource;
        ALuint vehicleHitSoundSource;
		//unsigned int scvId;
		//unsigned int soundDictionary[FastEcslent::NENTITYTYPES];
		std::vector <std::string> sourceDictionary;

		//other formats with time
		std::string getFQFNFromFilename(std::string filename);
		int getBufferId(std::string filename);
		//int firstIndexNotInUse(bool inUse[], int size);
		int getEmptySourceIndex();
		bool resetSource(ALuint sid);
        bool isEnabled;

	public:
		SoundMgr(Engine* eng);
		~SoundMgr();
		//default methods
		void initialize();
		void crosslink();
		void init();
		void loadLevel();
		void tick(double dtime);
		void releaseLevel();
		void cleanup ();

		// Play sounds at entity locations
		bool playLaserSound(Entity381* et);
		bool playEnemyLaserSound(Entity381* et);
		bool playPlayerExplosionSound(Entity381* et);
		bool playRobotExplosionSound(Entity381* et);
		bool playVehicleHitSound(Entity381* et);

		// Enable/disable sound
		void enable();
		void disable();

		// Background music
		bool loadBackground();
		bool playBackground();
		bool stopBackground();
		bool pauseBackground();
		bool resumeBackground();

		// misc
		bool playAudio(ALuint audioId, bool forceRestart );
		bool playAudio(ALuint audioId);
		bool setSoundPosition(ALuint audioID, Ogre::Vector3 position );

	    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	    virtual bool frameStarted(const Ogre::FrameEvent& evt);
	    virtual bool frameEnded(const Ogre::FrameEvent& evt);


		void printAudioDevices(const ALCchar *devices);
		int printError(const char *ermsg);
		inline ALenum toALFormat(short channels, short samples);
		void syncListenerToCamera();

		void attachSelectedNodeToSoundIndex(Entity381* ent, unsigned int index);
                
		//specific for sound managers everywhere
		bool loadAudio(std::string filename, int sid);
		//bool loadAndBindAudio(std::string filename, bool loop, ALuint &audioId); //return +ive audioId or -ive error code
                
		bool reserveAudio(std::string filename, bool loop, unsigned int &alSourceInfoIndex);
		bool releaseSource(ALuint audioId);
		bool releaseSourceIndex(int sid);

        // Returns true if the audio is started from the beginning
        // false if error or if already playing and forceRestart is false
        bool playAudioSourceIndex(int sid, bool forceRestart );
        bool playAudioSourceIndex(int sid);
        
        void copySoundState();
        
        bool isAudioPlaying(ALuint audioId);
        bool stopAudio(ALuint audioID );
        bool stopAllAudio( void );
        bool stopAudioSourceIndex(int sid);

        bool pauseAudio(ALuint audioID );
        bool pauseAllAudio( void );
        bool pauseAudioSourceIndex(int sid );

        bool resumeAudio(ALuint audioID );
        bool resumeAllAudio( void );
        bool resumeAudioSourceIndex(int sid);

        bool setSoundDisposition(ALuint audioID, Ogre::Vector3 position, Ogre::Vector3 velocity, Ogre::Vector3 direction );

        bool setSound(ALuint audioID, Ogre::Vector3 position,
            Ogre::Vector3 velocity, Ogre::Vector3 direction, float maxDistance,
            bool playNow, bool forceRestart, float minGain );

        bool setListenerDisposition( Ogre::Vector3 position, Ogre::Vector3 velocity, Ogre::Quaternion orientation );

        // Addon Sounds


	};
        
        //double volume;
        


}


#endif /* SOUNDMANAGER_H_ */
