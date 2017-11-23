#include "stdafx.h"
#include "GameSound.h"


GameSound::GameSound()
{
	System_Create(&pSystem);
	pSystem->init(6, FMOD_INIT_NORMAL, NULL);
	pSystem->createSound("SOUND\\BGM.mp3",
		FMOD_LOOP_NORMAL | FMOD_HARDWARE, NULL, &pSound[0]);
	pSystem->createSound("SOUND\\drip.wav",
		FMOD_LOOP_OFF | FMOD_HARDWARE, NULL, &pSound[1]);
	pSystem->createSound("SOUND\\tring.wav",
		FMOD_LOOP_OFF | FMOD_HARDWARE, NULL, &pSound[2]);
	pSystem->createSound("SOUND\\TADA.wav",
		FMOD_LOOP_OFF | FMOD_HARDWARE, NULL, &pSound[3]);
	pSystem->createSound("SOUND\\Click.wav",
		FMOD_LOOP_OFF | FMOD_HARDWARE, NULL, &pSound[4]);
	pSystem->createSound("SOUND\\explosion6.wav",
		FMOD_LOOP_OFF | FMOD_HARDWARE, NULL, &pSound[5]);
}


GameSound::~GameSound()
{
}


void GameSound::Play_GameSound(int i)
{
	pSystem->playSound(FMOD_CHANNEL_REUSE, pSound[i], false, &pChannel[i]);
}
