#pragma once
#include "targetver.h"
#include <stdio.h>
#include <iostream>
#include <tchar.h>
#include <math.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <string.h>
#include <vector>
#include "SOUND\fmod.hpp"

#pragma comment (lib, "SOUND\\fmodex_vc.lib")

#define Pi 3.141592653589793238462643383279

#define level_finish 7

using namespace FMOD;

typedef struct BOARD {
	double x[2], y, z[2];
	double range;
	double m_range;
	bool mark;
	bool move;
	bool clicked;
	int item;
};

typedef struct OBJECT {
	double x, y, z;
};
#include "GameObject.h"
#include "GameSystem.h"
#include "GameSound.h"
// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
