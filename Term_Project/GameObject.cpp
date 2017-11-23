#include "stdafx.h"
#include "GameObject.h"

#pragma warning (disable :4996)

double  getRadian(int n)
{
	return (double)n*(Pi / 180);
};

GameObject::GameObject() 
{
	position.x = 0;
	position.y = 60.0;
	position.z = 0;

	height_buffer = 0.0;
	startstate = 0;
	t = new Texture();
	e = new Etc(&stopmotion, &ballspeed_switch, &ballpower, &fog_switch, &balldisappear, &timeup, &nextstage, &ballstate, &position, t, b, &startstate);
	ball = new Ball(&balldisappear, &ballbottom, &position);
	board = new Board(&stopmotion, b, t);
	system = new GameSystem(&height_buffer, &position, b, &ballbottom, &ballpower, &startstate, &ballspeed_switch, &balldisappear, &fog_switch, &timeup, &stopmotion, &finish, &ballstate, &nextstage);
	p = new Particle();
}

GameObject::~GameObject()
{
}

void  GameObject::Draw_Menu()
{
	GLfloat White[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	float position[3] = { -80,805,25 };
	glRasterPos3f(position[0], position[1], position[2]);
	glPushMatrix();
	glRotatef(90, 1, 0, 0);

	glPopMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, White);
	t->SetBind(15);
	glPushMatrix();
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-300, 600, 300);
	glTexCoord2f(1, 0);
	glVertex3f(300, 600, 300);
	glTexCoord2f(1, 1);
	glVertex3f(300, 600, -300);
	glTexCoord2f(0, 1);
	glVertex3f(-300, 600, -300);
	glEnd();
	glPopMatrix();
}

BOARD* GameObject::GetBOARD(double x, double z)
{
	for (int i = 0; i < b.size(); i++)
	{
		if ((b[i].x[0] <= x && b[i].x[1] >= x) && (b[i].z[0] <= z && b[i].z[1] >= z))
		{
			return &b[i];
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Ball::~Ball() {

}

void Ball::Draw()
{
	GLfloat Green[] = { 0.0f, 0.3f, 0.0f, 1.0f };
	GLfloat White[] = { 0.9f, 0.9f, 0.9f, 0.1f };

	glPushMatrix();
	if (*balldisappear) {
		glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, White);

	}
	else
	{
		glDisable(GL_CULL_FACE);
		glDisable(GL_BLEND);
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, Green);
	}
	glTranslatef(position->x, position->y, position->z);
	if (*ballbottom) {
		glScalef(1.2, 0.8, 1.2);
	}
	glScalef(1, 1.15, 1);
	glutSolidSphere(4, 80, 80);
	glPopMatrix();
}

void Ball::Update()
{

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Board::~Board()
{

}

void Board::Draw()
{
	GLfloat Blue[] = { 0.980392f, 0.980392f, 0.823529f, 1.0f };
	GLfloat White[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat Red[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	static double stop_timer = 30.0;

	int bind = rand() % 8 + 1;

	if (bind == 1)
	{
		t->SetBind(0);
	}
	else if (bind == 2)
	{
		t->SetBind(9);
	}
	else if (bind == 3)
	{
		t->SetBind(10);
	}
	else if (bind == 4)
	{
		t->SetBind(11);
	}
	else if (bind == 5)
	{
		t->SetBind(12);
	}
	else if (bind == 6)
	{
		t->SetBind(13);
	}
	else if (bind == 7)
	{
		t->SetBind(14);
	}
	else
	{
		t->SetBind(0);
	}
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, White);
	for (int i = 0; i < b.size(); i++)
	{
		glBegin(GL_POLYGON);
		glTexCoord2f(0, 1);
		glVertex3f(b[i].x[0], b[i].y - 4, b[i].z[0]);
		glTexCoord2f(0, 0);
		glVertex3f(b[i].x[0], b[i].y - 4, b[i].z[1]);
		glTexCoord2f(1, 0);
		glVertex3f(b[i].x[1], b[i].y - 4, b[i].z[1]);
		glTexCoord2f(1, 1);
		glVertex3f(b[i].x[1], b[i].y - 4, b[i].z[0]);
		glEnd();
		if (bind != 3) {
			glBegin(GL_POLYGON);
			glTexCoord2f(1, 1);
			glVertex3f(b[i].x[0], b[i].y - 8, b[i].z[1]);
			glTexCoord2f(0, 1);
			glVertex3f(b[i].x[1], b[i].y - 8, b[i].z[1]);
			glTexCoord2f(0, 0);
			glVertex3f(b[i].x[1], b[i].y - 4, b[i].z[1]);
			glTexCoord2f(1, 0);
			glVertex3f(b[i].x[0], b[i].y - 4, b[i].z[1]);
			glEnd();

			glBegin(GL_POLYGON);
			glTexCoord2f(1, 1);
			glVertex3f(b[i].x[0], b[i].y - 8, b[i].z[0]);
			glTexCoord2f(0, 1);
			glVertex3f(b[i].x[0], b[i].y - 8, b[i].z[1]);
			glTexCoord2f(0, 0);
			glVertex3f(b[i].x[0], b[i].y - 4, b[i].z[1]);
			glTexCoord2f(1, 0);
			glVertex3f(b[i].x[0], b[i].y - 4, b[i].z[0]);
			glEnd();

			glBegin(GL_POLYGON);
			glTexCoord2f(0, 1);
			glVertex3f(b[i].x[1], b[i].y - 8, b[i].z[1]);
			glTexCoord2f(1, 1);
			glVertex3f(b[i].x[1], b[i].y - 8, b[i].z[0]);
			glTexCoord2f(1, 0);
			glVertex3f(b[i].x[1], b[i].y - 4, b[i].z[0]);
			glTexCoord2f(0, 0);
			glVertex3f(b[i].x[1], b[i].y - 4, b[i].z[1]);
			glEnd();
		}
		if (b[i].move &&  *stopmotion)
		{
			if (b[i].m_range > b[i].range)
			{
				b[i].mark = false;
			}
			else if (b[i].m_range < -b[i].range)
			{
				b[i].mark = true;
			}
			if (b[i].mark)
			{
				b[i].x[0] += board_speed;
				b[i].x[1] += board_speed;
				b[i].m_range += board_speed;
			}
			else if (!b[i].mark)
			{
				b[i].x[0] -= board_speed;
				b[i].x[1] -= board_speed;
				b[i].m_range -= board_speed;
			}
		}


		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, Blue);
		glTranslatef((b[i].x[0] + b[i].x[1]) / 2, b[i].y + 0.2, (b[i].z[0] + b[i].z[1]) / 2);
		if (i == b.size() - 1) {
			int i = 0;
			while (i <= 360)
			{
				glBegin(GL_LINES);
				glVertex3f(0, 0, 0);
				glVertex3f(10 * cos(getRadian(i)), 0.0, 10 * sin(getRadian(i)));
				glEnd();
				i += 2;
			}
		}
		if (b[i].item != 0) {
			Draw_ItemBox(b[i].item);
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, White);
		}
		glPopMatrix();
	}
	if (!(*stopmotion)) {
		stop_timer -= 0.1;

		if (stop_timer <= 0)
		{
			*stopmotion = true;
			stop_timer = 30.0;
		}
	}
}

void  Board::Draw_ItemBox(int effect)
{
	static int ry = 0;
	if (effect == 1) {
		GLfloat Red[] = { 0.7f, 0.0f, 0.0f, 1.0f };
		glPushMatrix();
		glTranslatef(0, 4, 0);
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, Red);
		glRotatef(ry, 0, 1, 0);
		glutSolidCube(8);
		glPopMatrix();
		ry++;
	}
	else if (effect == 2)
	{
		GLfloat Black[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		glPushMatrix();
		glTranslatef(0, 6, 0);
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, Black);
		glRotatef(ry, 0, 1, 0);
		glutSolidCube(12);
		glPopMatrix();
		ry++;
	}
}

void Board::Update()
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Box::Box()
{

}

Box::~Box()
{

}

void Box::Draw()
{

}

void Box::Update()
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Particle::Particle()
{
	Init();
}

Particle::~Particle()
{
}

void Particle::Init()
{
	int x, y, z;
	for (int i = 0; i < particle_num; i++) {
		x = rand() % 10 - 5;
		y = rand() % 10 - 5;
		z = rand() % 10 - 5;

		p[i].x = x / sqrt(x*x + y*y + z*z);
		p[i].y = y / sqrt(x*x + y*y + z*z);
		p[i].z = z / sqrt(x*x + y*y + z*z);
	}
}

void Particle::Draw()
{
	GLfloat Green[] = { 0.0f, 0.3f, 0.0f, 1.0f };
	for (int i = 0; i < particle_num; i++) 
	{
		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, Green);
		glTranslatef(p[i].x, p[i].y, p[i].z);
		p[i].x += p[i].x / 10;
		p[i].y += p[i].y / 10;
		p[i].z += p[i].z / 10;
		glutSolidCube(1);
		glPopMatrix();
	}
}

void Particle::Update()
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Etc::~Etc()
{

}

void Etc::Draw()
{
	Draw_Inform();
}


void Etc::Draw_Inform()
{
	GLfloat White[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, White);
	if (!(*stopmotion))
	{
		t->SetBind(4);
	}
	else if (*ballpower)
	{
		t->SetBind(6);
	}
	else if (*ballspeed_switch)
	{
		t->SetBind(5);
	}
	else if (*balldisappear)
	{
		t->SetBind(7);
	}
	else if (*fog_switch)
	{
		t->SetBind(8);
	}
	else if (*timeup)
	{
		t->SetBind(3);
	}
	else
	{
		return;
	}
	glPushMatrix();
	glTranslatef(position->x - 75, 120, position->z + 12);
	glRotatef(-55, 1, 0, 0);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(5, -25, -2);
	glTexCoord2f(1, 0);
	glVertex3f(50, -25, -2);
	glTexCoord2f(1, 1);
	glVertex3f(50, 20, -2);
	glTexCoord2f(0, 1);
	glVertex3f(5, 20, -2);
	glEnd();
	glPopMatrix();
}

void Etc::Draw_Fog()
{
	GLfloat fog_color[4] = { 0.905, 0.905, 0.905, 1.0 };
	GLfloat density = 1.0;
	GLfloat start = 0.0f;
	GLfloat end = 230.0f;
	glFogf(GL_FOG_MODE, GL_LINEAR);
	glFogfv(GL_FOG_COLOR, fog_color);
	glFogf(GL_FOG_START, start);
	glFogf(GL_FOG_END, end);
	glFogf(GL_FOG_DENSITY, density);
}

void Etc::Draw_RestartInform()
{
	GLfloat Pink[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat White[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, Pink);
	glPushMatrix();
	glTranslatef(position->x - 25, 120, position->z + 70);
	glRotatef(-55, 1, 0, 0);

	glBegin(GL_POLYGON);
	glVertex3f(5, 9, -2);
	glVertex3f(50, 9, -2);
	glVertex3f(50, 10, -2);
	glVertex3f(5, 10, -2);

	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(50, 10, -2);
	glVertex3f(51, 10, -2);
	glVertex3f(51, 20, -2);
	glVertex3f(50, 20, -2);

	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(5, 20, -2);
	glVertex3f(50, 20, -2);
	glVertex3f(50, 21, -2);
	glVertex3f(5, 21, -2);

	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(50, 10, -2);
	glVertex3f(51, 10, -2);
	glVertex3f(51, 20, -2);
	glVertex3f(50, 20, -2);

	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(4, 10, -2);
	glVertex3f(5, 10, -2);
	glVertex3f(5, 20, -2);
	glVertex3f(4, 20, -2);
	glEnd();

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, White);
	t->SetBind(1);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(5, 10, -2);
	glTexCoord2f(1, 0);
	glVertex3f(50, 10, -2);
	glTexCoord2f(1, 1);
	glVertex3f(50, 20, -2);
	glTexCoord2f(0, 1);
	glVertex3f(5, 20, -2);
	glEnd();
	glPopMatrix();
}
void Etc::Draw_Finish()
{
	GLfloat White[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glPushMatrix();
	glTranslatef(position->x - 25, 120, position->z + 70);
	glRotatef(-55, 1, 0, 0);

	glBegin(GL_POLYGON);
	glVertex3f(50, -10, -2);
	glVertex3f(5, -10, -2);
	glVertex3f(5, -11, -2);
	glVertex3f(50, -11, -2);

	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(50, -10, -2);
	glVertex3f(51, -10, -2);
	glVertex3f(51, 20, -2);
	glVertex3f(50, 20, -2);

	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(5, 20, -2);
	glVertex3f(50, 20, -2);
	glVertex3f(50, 21, -2);
	glVertex3f(5, 21, -2);

	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(50, -10, -2);
	glVertex3f(51, -10, -2);
	glVertex3f(51, 20, -2);
	glVertex3f(50, 20, -2);

	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(4, -10, -2);
	glVertex3f(5, -10, -2);
	glVertex3f(5, 20, -2);
	glVertex3f(4, 20, -2);
	glEnd();

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, White);
	t->SetBind(2);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(5, -10, -2);
	glTexCoord2f(1, 0);
	glVertex3f(50, -10, -2);
	glTexCoord2f(1, 1);
	glVertex3f(50, 20, -2);
	glTexCoord2f(0, 1);
	glVertex3f(5, 20, -2);
	glEnd();
	glPopMatrix();
}

BOARD* Etc::GetBOARD(double x, double z)
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