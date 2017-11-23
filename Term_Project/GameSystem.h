#pragma once
#include "GameSound.h"

class GameSystem
{
private:
	bool* nextstage;
	bool* ballstate;
	bool balltop;
	bool* ballbottom;
	bool* ballpower;
	bool* ballspeed_switch;
	bool* balldisappear;
	bool* fog_switch;
	bool* timeup;
	bool* stopmotion;
	bool* finish;

	int* startstate;
	double ballspeed;
	double* height_buffer;
	OBJECT*  position;

	std::vector<BOARD>& b;
public:
	GameSound sound;

	GameSystem(double* h_buffer, OBJECT*  p, std::vector<BOARD>& board, bool* bottom, bool* power, int* start, bool* speed_switch,
		bool* disappear, bool* fog, bool* time, bool* stop, bool* f, bool* state, bool* next)
:  height_buffer(h_buffer), position(p), b(board),  ballbottom(bottom), ballpower(power), startstate(start), ballspeed_switch(speed_switch),
balldisappear(disappear), fog_switch(fog), timeup(time), stopmotion(stop), finish(f), ballstate(state), nextstage(next)
	{
		ballspeed = 0.02;
	}
	~GameSystem();
	void Initialization();
	void SetMap();
	void BallUpdate();
	void BuildBoard(double x1, double z1, double y, double x2, double z2, bool move, double range, int item);
	bool IsGoall();
	int FallBall();
	void ItemEffect(int num);
	void Move();
	bool GetItem();
	bool CheckPosition();
	void MakeBoard();
	BOARD* GetBOARD(double x, double z);
	void DeleteBOARD();
	void ResetState(bool type);
};
