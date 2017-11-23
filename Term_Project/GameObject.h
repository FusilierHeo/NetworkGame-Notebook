#pragma once
#include "Texture.h"
#include "GameSystem.h"
#define particle_num 60

class Etc;
class Ball;
class Board;
class Particle;

class GameObject
{
private:
	int startstate;
	std::template  vector<BOARD> b;
	OBJECT  position;

	double height_buffer;

	bool ballbottom = true;// 공이 바닥에 닿을때
	bool stopmotion = true;//이벤트로 잠시 판이 멈출때
	bool ballspeed_switch = false;// 공의 속도 늦추는 스위치
	bool ballpower = false; // 공 무적 이벤트
	bool fog_switch = false;
	bool balldisappear = false;
	bool timeup = false;
	bool nextstage = false;
	bool ballstate = true; //공의 상태
	bool finish = false;

public:
	Etc *e;
	Texture* t;
	Ball *ball;
	Board *board;
	GameSystem* system;
	Particle* p;

	GameObject();
	~GameObject();

	BOARD* GetBOARD(double x, double z);
	void Draw_Menu();
	OBJECT GetBallPosition()
	{
		return position;
	}
	bool GetFinish()
	{
		return finish;
	}
	void SetStartState(int i)
	{
		startstate = i;
	}
	int GetStartState()
	{
		return startstate;
	}
	bool GetBallState()
	{
		return ballstate;
	}
	bool GetFogSwitch()
	{
		return fog_switch;
	}
	bool GetNextStage()
	{
		return nextstage;
	}
};


class Ball
{
private:
	bool* ballbottom;// 공이 바닥에 닿을때
	bool* balldisappear;
	OBJECT*  position;

public:
	Ball(bool* d, bool* bottom, OBJECT* p):balldisappear(d), ballbottom(bottom), position(p)
	{}
	~Ball();

	void Draw();
	void Update();
};

class Board
{
private:
	bool* stopmotion;
	int board_speed;
	Texture* t;
	std::template vector<BOARD>& b;

public:
	Board(bool* speed, std::template vector<BOARD>& board, Texture* texture) : stopmotion(speed), b(board), board_speed(1),t(texture)
	{}
	~Board();

	void Draw();
	void Update();

	void  Draw_ItemBox(int effect);
};

class Box 
{
public:
	Box();
	~Box();

	void Draw();
	void Update();
};

class Particle 
{
private:
	OBJECT p[particle_num];
public :
	Particle();
	~Particle();

	void Init();
	void Draw();
	void Update();
};

class Etc // 에너지바, 아이템효과, 레벨등을 그린다.
{
private :
	
	int* startstate;
	OBJECT*  position;
	Texture* t;
	std::template vector<BOARD>& b;

	bool* stopmotion;//이벤트로 잠시 판이 멈출때
	bool* ballspeed_switch;// 공의 속도 늦추는 스위치
	bool* ballpower; // 공 무적 이벤트
	bool* fog_switch;
	bool* balldisappear;
	bool* timeup;
	bool* nextstage;
	bool* ballstate; //공의 상태

public:
	Etc(bool* stop, bool* ballspeed, bool* power, bool* fog, bool* disappear, bool* time, bool* next, bool* state,
OBJECT* p, Texture* texture, std::template vector<BOARD>& board, int* s)
:stopmotion(stop), ballspeed_switch(ballspeed), ballpower(power), fog_switch(fog), balldisappear(disappear), timeup(time), 
nextstage(next), ballstate(state), position(p), t(texture), b(board), startstate(s)
	{}
	~Etc();

	void Draw();
	void Draw_Inform();
	void  Draw_Fog();
	void Draw_RestartInform();
	void Draw_Finish();
	BOARD* GetBOARD(double x, double z);
};

