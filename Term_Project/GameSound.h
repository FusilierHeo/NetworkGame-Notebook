#pragma once
class GameSound
{
private:
	System* pSystem;
	Sound *pSound[6];
	Channel *pChannel[6];
public:
	GameSound();
	~GameSound();
	void Play_GameSound(int i);
};

