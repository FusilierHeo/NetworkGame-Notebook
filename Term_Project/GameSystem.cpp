#include "stdafx.h"
#include "GameSystem.h"

GameSystem::~GameSystem()
{
}


void GameSystem::Initialization()
{
	position->x = 0;
	position->y = 60.0;
	position->z = 0;
	*height_buffer = 0.0;
	SetMap();
}

void GameSystem::SetMap()
{
		BuildBoard(-20, -20, 0, 20, 20, false, 0, 0);
		BuildBoard(-20, -70, 10, 20, -30, false, 0, 1);
		BuildBoard(-20, -120, 20, 20, -80, true, 20, 0);
		BuildBoard(-20, -170, 10, 20, -130, false, 0, 0);
		BuildBoard(-35, -215, 0, -5, -185, false, 0, 0);	
}

void GameSystem::BallUpdate()
{

	static double ballspeed_timer = 30.0;
	static double ballpower_timer = 30.0;
	static double balldisappear_timer = 30.0;
	static double timeup_timer = 10.0;
	static double fog_timer = 30.0;
	static double x = 0.0;
	BOARD *NOW = GetBOARD(position->x, position->z);
	Move();
	if (FallBall() == 0 && *ballstate)
	{
	BACK:
		x += ballspeed;
		position->y = *height_buffer - 60.0*x*x + 60.0;

		if (position->y >= *height_buffer + 59.0)
		{
			balltop = true;
		}
		else
		{
			balltop = false;
		}

		if (position->y <= *height_buffer + 0.06)
		{
			*ballbottom = true;
		}
		else
		{
			*ballbottom = false;
		}
		if (!(*ballpower)) {
			if ((FallBall() == 2 && *ballstate) || position->y <= *height_buffer - 200) // 떨어졌는지
			{
				sound.Play_GameSound(5);
				*ballstate = false;
			}
		}
		if (GetItem() && *ballstate)// 이벤트 박스 충돌
		{
			sound.Play_GameSound(2);
			if (NOW->item == 1) {
				ItemEffect(rand() % 4 + 1);
				NOW->item = 0;
			}
			else if (NOW->item == 2)
			{
				ItemEffect(rand() % 3 + 4);
				NOW->item = 0;
			}
		}
		if (FallBall() == 1 && *startstate == 1)
		{
			sound.Play_GameSound(1);
		}
	}
	else if (*ballstate &&  FallBall() == 1)
	{
		x = -1.0;
		if (NOW != NULL) {
			*height_buffer = NOW->y;
		}
		goto BACK;
	}
	else
	{
		position->y -= 2.0;
	}

	if (*ballspeed_switch || ballspeed == 0.01)
	{
		ballspeed_timer -= 0.1;
		if (ballspeed_timer <= 0.0)
		{
			ballspeed = 0.02;
			ballspeed_timer = 30.0;
			*ballspeed_switch = false;
		}
	}
	Move();
	if (*ballpower)
	{
		ballpower_timer -= 0.1;
		if (ballpower_timer <= 0.0)
		{
			ballpower_timer = 30.0;
			*ballpower = false;
		}
	}

	if (*balldisappear)
	{
		balldisappear_timer -= 0.1;
		if (balldisappear_timer <= 0.0)
		{
			ballpower_timer = 30.0;
			*balldisappear = false;
		}
	}

	if (*fog_switch)
	{
		fog_timer -= 0.1;
		if (fog_timer <= 0.0)
		{
			fog_timer = 30.0;
			*fog_switch = false;
		}
	}
	if (*timeup)
	{
		timeup_timer -= 0.1;
		if (timeup_timer <= 0.0)
		{
			timeup_timer = 10.0;
			*timeup = false;
		}
	}
	if (CheckPosition())
		MakeBoard();


	if (!(*fog_switch) && fog_timer < 30.0)
	{
		fog_timer = 30.0;
	}
	if (!(*balldisappear) && balldisappear_timer < 30.0)
	{
		balldisappear_timer = 30.0;
	}
	if (!(*ballpower) && ballpower_timer < 30.0)
	{
		ballpower_timer = 30.0;
	}
	if (!(*ballspeed_switch) && ballspeed_timer < 30.0)
	{
		ballspeed_timer = 30.0;
	}
}

void GameSystem::BuildBoard(double x1, double z1, double y, double x2, double z2, bool move, double range, int item)
{
	BOARD A;

	A.x[0] = x1, A.x[1] = x2;
	A.y = y;		  
	A.z[0] = z1, A.z[1] = z2;
	A.clicked = false;
	A.move = move;
	A.m_range = 0;
	A.range = range;
	A.item = item;
	if (rand() % 2 == 0)
		A.mark = false;
	else
		A.mark = true;

	b.push_back(A);
}

bool  GameSystem::IsGoall()
{
	if ((b[b.size() - 1].x[0] <= position->x && b[b.size() - 1].x[1] >= position->x) && (b[b.size() - 1].z[0] <= position->z && b[b.size() - 1].z[1] >= position->z) && (b[b.size() - 1].y + 4.0 >= position->y)) {
		{
			return true;
		}
	}
	else
		return false;
}


int  GameSystem::FallBall()
{
	BOARD *A = GetBOARD(position->x, position->z);

	if (A == NULL)
	{
		if (*height_buffer <  (position->y))//공이 공중에 있음
		{
			return 0;
		}
		else
		{
			return 2;
		}
	}
	else {
		if (A->y <  position->y)//공이 공중에 있음
		{
			return 0;
		}
		else
		{
			if ((A->x[0] <= position->x && A->x[1] >= position->x) && (A->z[0] - 5 <= position->z && A->z[1] + 5 >= position->z))
			{//공이 판에 맞음
				if (A->y + 8.0 >= position->y) {
					return 1;
				}
			}
		}
		return 2;//공이 바닥으로 떨어짐
	}
}

void  GameSystem::ItemEffect(int num)
{
	if (num == 2)// 발판 잠시 정지
	{
		*stopmotion = false;
	}
	else if (num == 3)//공 무적
	{
		*ballpower = true;
	}
	else if (num == 4)//공의 속도를 줄인다.
	{
		ballspeed = 0.01;
		*ballspeed_switch = true;
	}
	else if (num == 5)// 공 블라인드
	{
		*balldisappear = true;
	}
	else if (num == 6)//안개 효과
	{
		*fog_switch = true;
	}
}

void GameSystem::Move()
{
	if (!(*finish)) {
		if (*ballstate) {
			if (GetAsyncKeyState(VK_LEFT) & 0x80000000)
			{
				position->x -= 0.12;
			}
			if (GetAsyncKeyState(VK_RIGHT) & 0x80000000)
			{
				position->x += 0.12;
			}
			if (GetAsyncKeyState(VK_UP) & 0x80000000)
			{
				position->z -= 0.12;
			}
			if (GetAsyncKeyState(VK_DOWN) & 0x80000000)
			{
				position->z += 0.12;
			}
		}
	}
}

bool  GameSystem::GetItem()
{
	for (int i = 0; i < b.size(); i++)
	{
		if (b[i].item == 1)
		{
			if (((b[i].x[0] + b[i].x[1]) / 2 - 5 <= position->x && (b[i].x[0] + b[i].x[1]) / 2 + 5 >= position->x)
				&& ((b[i].z[0] + b[i].z[1]) / 2 - 5 <= position->z && (b[i].z[0] + b[i].z[1]) / 2 + 5 >= position->z)
				&& (position->y >= 4 + b[i].y &&  position->y <= +b[i].y + 14))
			{
				return true;
			}
		}
		else if (b[i].item == 2)
		{
			if (((b[i].x[0] + b[i].x[1]) / 2 - 8.5 <= position->x && (b[i].x[0] + b[i].x[1]) / 2 + 8.5 >= position->x)
				&& ((b[i].z[0] + b[i].z[1]) / 2 - 8.5 <= position->z && (b[i].z[0] + b[i].z[1]) / 2 + 8.5 >= position->z)
				&& (position->y >= 4 + b[i].y &&  position->y <= + b[i].y + 21))
			{
				return true;
			}
		}
	}
	return false;
}

BOARD* GameSystem::GetBOARD(double x, double z)
{
	for (int i = 0; i < b.size(); i++)
	{
		if ((b[i].x[0] <= x && b[i].x[1] >= x) && (b[i].z[0] <= z && b[i].z[1] >= z))
		{
			return &b[i];
		}
	}
	return NULL;
}
void GameSystem::DeleteBOARD()
{
	b.clear();
}

void GameSystem::ResetState(bool type)
{
	*ballstate = true;
	*stopmotion = true;
	*ballspeed_switch = false;
	*ballpower = false;
	*balldisappear = false;
	*fog_switch = false;
	*nextstage = false;
	ballspeed = 0.02;
}
bool GameSystem::CheckPosition()
{
	if (position->z < b[b.size() - 3].z[0])
		return true;
	else
		return false;
}
void GameSystem::MakeBoard()
{
	BOARD newBoard;

	newBoard.x[0] = b[b.size() - 1].x[0] + rand() % 160 - 80;
	newBoard.x[1] = newBoard.x[0] + rand()% 10 + 30;
	newBoard.z[0] = b[b.size() - 1].z[0] - (rand() % 10 + 50);
	newBoard.z[1] = newBoard.z[0] + rand() % 10 + 30;
	newBoard.y = b[b.size() - 1].y + rand() % 20 - 10;
	newBoard.m_range = 0;

	if (rand() % 5 == 0)
		newBoard.move = true;
	else
		newBoard.move = false;

	newBoard.range = rand() % 20 + 20;

	if (rand() % 2 == 0)
		newBoard.mark = false;
	else
		newBoard.mark = true;

	int itemRate = rand() % 10;

	if (itemRate == 0)
		newBoard.item = 1;
	else if (itemRate == 1)
		newBoard.item = 2;
	else
		newBoard.item = 0;


	b.push_back(newBoard);
}