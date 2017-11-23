#include "stdafx.h"

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void TimerFunction(int value);
void Keyboard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void  Light();

int  speed = 10;
GameObject object;

int main()
{
	srand((unsigned)time(NULL));
	object.system->Initialization();
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutTimerFunc(speed, TimerFunction, 1);
	glutCreateWindow("컴그 팀 프로젝트");
	object.t->InitTexture();
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutMainLoop();
	return 0;
}
GLvoid drawScene(GLvoid)
{
	static double finish_time = 30.0;
	glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if (object.GetStartState() == 0)
	{
		glTranslatef(0.0, -10, -100);
		gluLookAt(0.0, 1000.0, 0.0, 0.0, 10.0, 0.0, 0.0, 0.0, -1.0);
		object.Draw_Menu();
	}
	else if (object.GetStartState() == 1)
	{
		glTranslatef(0.0, -10, -100);
		gluLookAt(object.GetBallPosition().x, 100.0, object.GetBallPosition().z + 70.0, object.GetBallPosition().x, 0.0, object.GetBallPosition().z, 0.0, 1.0, 0.0);
	}
	
	if (object.GetStartState() == 1) {
		Light();
		object.e->Draw_Fog();
		if (object.GetFogSwitch())
		{
			glEnable(GL_FOG);
		}
		else
		{
			glDisable(GL_FOG);
		}
		object.system->Move();
		object.e->Draw();
		if (!object.GetFinish()) {
			if (!object.GetBallState()) {
				object.e->Draw_RestartInform();
			}
		}
		object.system->Move();
		if (object.GetNextStage()) {
			object.system->DeleteBOARD();
			object.system->Initialization();
			object.system->ResetState(false);
		}
		if (object.GetFinish())
		{
			finish_time -= 0.1;
			object.e->Draw_Finish();
			if (finish_time <= 0.0)
			{
				exit(1);
			}
		}
		object.board->Draw();

		if (object.GetBallState()) {
			object.ball->Draw();
		}
		else if (!object.GetBallState()) {
			glPushMatrix();
			glTranslatef(object.GetBallPosition().x, object.GetBallPosition().y, object.GetBallPosition().z);
			object.p->Draw();
			glPopMatrix();
		}
	}
	glutSwapBuffers();
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(60.0f, 1.0, 1.0, 2000.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
}
void TimerFunction(int value)
{
	object.system->Move();
	object.system->BallUpdate();
	glutPostRedisplay();
	glutTimerFunc(speed, TimerFunction, 1);
}
void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'i':
		if (!object.GetBallState())
		{
			object.system->DeleteBOARD();
			object.system->Initialization();
			object.p->Init();
			object.system->ResetState(true);
		}
		break;
	}
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		object.system->sound.Play_GameSound(4);

		if (object.GetStartState() == 0) {
			if (x > 0 && x < 260 && y>290 && y < 420)
			{
				object.system->sound.Play_GameSound(0);
				object.SetStartState(1);
			}
			if (x > 0 && x < 260 && y>480 && y < 610)
			{
				exit(0);
			}
		}
	}
}

void  Light()
{
	GLfloat ambientLignt[] = { 0.6f, 0.6f, 0.6f, 1.0f };
	GLfloat diffuseLight[] = { 0.4f, 0.4f, 0.4f, 1.0f };
	GLfloat specular[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat lightPos[] = { 0.0f, 100.0f, 0.0f, 1.0f };

	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLignt);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos);
	glEnable(GL_LIGHT1);
}
