#include<gl/glut.h> 
#include <sstream>
#include <MMSystem.h>

void bullet(void);
void cannon(void);
void idle(void);
void shooting(void);
float randomX(void);
void checkLives(void);
void displayScore(void);
void displayLives(void);
void displayMenu(void);
void displayLose(void);
void menuButton(void);
void returnButton(void);
void background(void);

float cannonX = 0, cannonLWX = -20, cannonRWX = 20;
float bulletX = 0, bulletY = -101, score, lives;

float RotateX = 90.0;
float menuX = 90.0;

float bonusSpeed = 1;
float bounsX = randomX(), bonusY = 250, enemyX = randomX(), enemyY = 250;

BOOLEAN spaceBar = false, stopGame = false, startMenu = true, start = false, reset = false;

// a method to initialize the game window 
void init()
{
	// set the window ortho
	glClearColor(0.7, 0.9, 0.8, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-200.0, 200.0, -200.0, 200.0, -600.0, 600);
	glMatrixMode(GL_MODELVIEW);

	// set the lighting values
	GLfloat mat_specular[] = { 1.000, 0.871, 0.678, 1.0 };
	GLfloat mat_shininess[] = { 20 };
	GLfloat light_position[] = { -20, 20.0, 20.0, 0.0 };

	glLightfv(GL_LIGHT0, GL_SPECULAR, mat_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	// enable lighting
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}

// a method to draw the enemy and the bonus objects 
void enemy_bonus() {

	//BONUS
	glPushMatrix();
	glTranslatef(bounsX, bonusY, 0.0);
	glRotated(RotateX, 0.0, 1.0, 0.0);
	glColor3f(1.0, 1.0, 0.0);
	glutSolidTorus(5, 11, 15, 50);
	glPopMatrix();

	//ENEMY
	glPushMatrix();
	glTranslatef(enemyX, enemyY, 0.0);
	glRotated(RotateX, 0.0, 1.0, 0.0);
	glScalef(15, 15, 0.0);
	glColor3d(1.0, 0.0, 0.0);
	glutSolidOctahedron();
	glPopMatrix();

}

// a method to draw and write on the menu window
void displayMenu(void) {

	// menu bonus
	glPushMatrix();
	glTranslatef(100, 100, 0.0);
	glRotated(menuX, 0.0, 1.0, 0.0);
	glColor3f(1.0, 1.0, 0.0);
	glutSolidTorus(5, 11, 15, 50);
	glPopMatrix();

	// menu enemy
	glPushMatrix();
	glTranslatef(-90, 100, 0.0);
	glRotated(menuX, 0.0, 1.0, 0.0);
	glScalef(15, 15, 0.0);
	glColor3d(1.0, 0.0, 0.0);
	glutSolidOctahedron();
	glPopMatrix();

	// menu cannon ring 
	glPushMatrix();
	glColor3f(0.258, 0.258, 0.258);
	glTranslated(15, -101, 0);
	glRotatef(90, -20, -5, -5);
	glutSolidTorus(2, 10, 15, 50);
	glPopMatrix();

	// menu cannon body
	glPushMatrix();
	glColor3f(0.6, 0.6, 0.59);
	glTranslated(15, -150, 0);
	glRotatef(100, 1, -0.5, 0.5);
	glutSolidSphere(19, 100, 300);
	glPopMatrix();

	// menu cannon
	glPushMatrix();
	glColor3f(0.6, 0.6, 0.59);
	glTranslated(15, -100, 0);
	glRotatef(100, 1, -0.5, 0.5);
	gluCylinder(gluNewQuadric(), 10, 15, 40, 100, 100);
	glPopMatrix();

	// menu left wheel
	glPushMatrix();
	glColor3f(0.258, 0.258, 0.258);
	glTranslated(-5, -150, 0);
	glRotatef(180, -20, 0, 20);
	glutSolidTorus(2, 13, 15, 50);
	glPopMatrix();

	// menu right wheels
	glPushMatrix();
	glColor3f(0.258, 0.258, 0.258);
	glTranslated(35, -150, 0);
	glRotatef(180, -20, 0, 20);
	glutSolidTorus(2, 13, 15, 50);
	glPopMatrix();

	// menu bullet
	glPushMatrix();
	glColor3f(0.207f, 0.192f, 0.196f);
	glTranslated(15, -101, 0);
	glutSolidSphere(10, 100, 70);
	glPopMatrix();

	// menu choices 
	const char* string = "Cannon Shooting";
	glRasterPos2i(-19, 100);
	for (int i = 0; i < strlen(string); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);

	const char* string2 = "Start The Game [Press 'S']";
	glRasterPos2i(-30, 7);
	for (int i = 0; i < strlen(string2); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string2[i]);

	const char* string3 = "Exit The Game [Press 'E']";
	glRasterPos2i(-30, -20);
	for (int i = 0; i < strlen(string3); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string3[i]);

	const char* string4 = "Sarah Almeshaal				1907432";
	glRasterPos2i(-195, -130);
	for (int i = 0; i < strlen(string4); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string4[i]);

	const char* string5 = "Fatimah Alyami 				 1907018";
	glRasterPos2i(-195, -150);
	for (int i = 0; i < strlen(string5); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string5[i]);

	const char* string6 = "Fai Almarwani 			  	 1906864";
	glRasterPos2i(-195, -170);
	for (int i = 0; i < strlen(string6); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string6[i]);

}

// a method to draw 2d buttons
void menuButton(void) {
	
	glDisable(GL_LIGHTING);
	glColor3f(0.8, 0.8, 0.8);
	glBegin(GL_QUADS);
	glVertex2i(-36, 21);
	glVertex2i(-36, 0);
	glVertex2i(70, 0);
	glVertex2i(70, 21);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2i(-36, 22);
	glVertex2i(-36, 0);
	glVertex2i(70, 0);
	glVertex2i(70, 22);
	glEnd();

	glColor3f(0.8, 0.8, 0.8);
	glBegin(GL_QUADS);
	glVertex2i(-36, -6);
	glVertex2i(-36, -28);
	glVertex2i(70, -28);
	glVertex2i(70, -6);
	glEnd();


	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2i(-36, -5);
	glVertex2i(-36, -28);
	glVertex2i(70, -28);
	glVertex2i(70, -5);
	glEnd();
	glEnable(GL_LIGHTING);
}

// a method to draw a 2d button
void returnButton(void) {

	glDisable(GL_LIGHTING);
	glColor3f(0.8, 0.8, 0.8);
	glBegin(GL_QUADS);
	glVertex2i(-57, -6);
	glVertex2i(-57, -28);
	glVertex2i(70, -28);
	glVertex2i(70, -6);
	glEnd();


	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2i(-57, -5);
	glVertex2i(-57, -28);
	glVertex2i(70, -28);
	glVertex2i(70, -5);
	glEnd();
	glEnable(GL_LIGHTING);
}

// a method to display all the drawing 
void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// display the menu if the game hasn't start yet or if the player pressed 'R' to restart the game
	if (startMenu == true && start == false || reset == true) {
		displayMenu();
		menuButton();
		glutIdleFunc(idle);
		lives = 5;
		score = 0;
		enemyY = 250;
		bonusY = 250;
	}

	// the game will start if the player pressed 'S'
	if (start == true && reset == false) {
		cannon();
		bullet();
		enemy_bonus();
		displayScore();
		displayLives();

		// displaying losing message if the player lost
		if (stopGame == true) {
			displayLose();
			returnButton();
		}
		glutIdleFunc(idle);
	}
	glutPostRedisplay();
	glutSwapBuffers();
}

// display the losing message 
void displayLose(void) {

	const char* string = "YOU LOST!";
	glRasterPos2i(-19, 5);
	for (int i = 0; i < strlen(string); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);

	const char* string2 = "Return To The Menu [Press 'R']";
	glRasterPos2i(-50, -18);
	for (int i = 0; i < strlen(string2); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string2[i]);
}

// display the remaining lives for the player
void displayLives(void) {

	const char* string = "Lives";
	glRasterPos2i(-175, 180);
	for (int i = 0; i < strlen(string); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
	char Lives[10];
	std::stringstream Live;
	Live << lives;
	Live >> Lives;
	glRasterPos2i(-150, 180);
	for (int i = 0; i < strlen(Lives); i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, Lives[i]);
}

// display the player score
void displayScore(void) {

	const char* string = "Score";
	glRasterPos2i(150, 180);
	for (int i = 0; i < strlen(string); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
	char Scores[10];
	std::stringstream Score;
	Score << score;
	Score >> Scores;
	glRasterPos2i(175, 180);
	for (int i = 0; i < strlen(Scores); i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, Scores[i]);
}

// a method to draw the cannon bullet
void bullet(void) {

	glPushMatrix();
	glColor3f(0.207f, 0.192f, 0.196f);
	glTranslated(bulletX, bulletY, 0);
	glutSolidSphere(10, 100, 70);
	glPopMatrix();
}

// a method to draw the cannon object
void cannon(void) {

	// cannon ring
	glPushMatrix();
	glColor3f(0.258, 0.258, 0.258);
	glTranslated(cannonX, -101, 0);
	glRotatef(90, -20, -5, -5);
	glutSolidTorus(2, 10, 15, 50);
	glPopMatrix();

	// cannon body
	glPushMatrix();
	glColor3f(0.6, 0.6, 0.59);
	glTranslated(cannonX, -150, 0);
	glRotatef(100, 1, -0.5, 0.5);
	glutSolidSphere(19, 100, 300);
	glPopMatrix();

	// cannon
	glPushMatrix();
	glColor3f(0.6, 0.6, 0.59);
	glTranslated(cannonX, -100, 0);
	glRotatef(100, 1, -0.5, 0.5);
	gluCylinder(gluNewQuadric(), 10, 15, 40, 100, 100);
	glPopMatrix();

	// left wheel
	glPushMatrix();
	glColor3f(0.258, 0.258, 0.258);
	glTranslated(cannonLWX, -150, 0);
	glRotatef(180, -20, 0, 20);
	glutSolidTorus(2, 13, 15, 50);
	glPopMatrix();

	// right wheels
	glPushMatrix();
	glColor3f(0.258, 0.258, 0.258);
	glTranslated(cannonRWX, -150, 0);
	glRotatef(180, -20, 0, 20);
	glutSolidTorus(2, 13, 15, 50);
	glPopMatrix();
}

// a method to interact with the player using the keyboard arrows
void mySpecialKey(int key, int x, int y)
{
	// if the game stopped the player wont be able to move the cannon
	if (stopGame == false) {
		switch (key)
		{
		case GLUT_KEY_RIGHT:
			// moving the cannon only on the window coordinates 'cannon cant go right the window and disappear' 
			if (cannonRWX <= 200) {
				cannonRWX += 5;
				cannonLWX += 5;
				cannonX += 5;
				// moving the bullet along with the cannon
				if (bulletY == -101)
					bulletX += 5;
			}
			break;

		case GLUT_KEY_LEFT:
			// moving the cannon only on the window coordinates 'cannon cant go left the window and disappear' 
			if (cannonRWX >= -160) {
				cannonRWX -= 5;
				cannonLWX -= 5;
				cannonX -= 5;
				// moving the bullet along with the cannon
				if (bulletY == -101)
					bulletX -= 5;
			}
			break;
		}
	}
}

// a method to animate the objects
void idle(void) {

	// if the player on the menu the bonus and the enemy objects will be still
	if (stopGame == false && start == true) {
		RotateX += 5;
		enemyY -= 2;
		bonusY -= bonusSpeed;
	}

	// if the player on the menu window then animate 'rotate' the objects
	if (startMenu == true) {
		menuX += 5;
	}

	// if the player pressed the space bar then shoot the bullet
	if (spaceBar == true) {
		bulletY += 5;

		// if the bullet hit the bonus object then the player will score up
		if (bulletY >= bonusY && bulletX >= bounsX - 15 && bulletX <= bounsX + 15) {
			// shooting animation 
			shooting();
			// genrate a random coordinates (on x axis) for the bonus object
			bounsX = randomX();
			// return the bonus up the window
			bonusY = 250;
			score++;
			// randomly change the bonus speed (speed wont be slower that y+=2, and wont be faster than y+=4)
			bonusSpeed = rand() % ((4 - 2) + 1) + 1;
			// play a sound 
			PlaySound(TEXT("Score_up.wav"), NULL, SND_ASYNC);
		}

		// if the bullet hit the bonus object then the player wont lose a life
		else if (bulletY >= enemyY && bulletX >= enemyX - 10 && bulletX <= enemyX + 10) {
			shooting();
			enemyX = randomX();
			enemyY = 250;
		}
	}

	// if the bullet missed any object then the bullet will be returned to the cannon
	if (bulletY > 200) {
		shooting();
	}

	// if the bonus reached the end of the window then it will be generated randomly on the window again
	if (bonusY <= -200) {
		bonusY = 250;
		bounsX = randomX();
	}

	// if the enemy reached the end of the window then it will be generated randomly on the window again
	if (enemyY <= -200) {
		enemyY = 250;
		enemyX = randomX();
		// play a sound
		PlaySound(TEXT("Lost_Life.wav"), NULL, SND_ASYNC);
		// the player will lose a life
		lives--;
		// checking if the player lost 
		checkLives();
	}
}

// a method to generate random coordinates (coordinates range wont be bigger than the window coordinates)
float randomX(void) {
	return (rand() % (170 - (-170) + 1)) + (-170);
}

// a method to stop the game if the player lost the game (losing means lives = 0) and hold the objects in place
void checkLives(void) {
	if (lives == 0) {
		RotateX = 0;
		enemyY = enemyY;
		bonusY = bonusY;
		stopGame = true;
	}
}

// a method for the bullet to return it in with the cannon and stop its animation (also indcate that the space bar is not pressed)
void shooting(void) {
	bulletX = cannonX;
	bulletY = -101;
	glutIdleFunc(NULL);
	spaceBar = false;
}

// a method to interact with the player using the keyboard 
void processNormalKeys(unsigned char key, int x, int y) {

	switch (key)
	{
	case 32:
		// the player will be only able to shoot the bullet if the game started
		if (stopGame == false)
			spaceBar = true;
		break;

	case 's':
	case 'S':
		// the game will only start if the player hasn't lost 
		if (lives > 0) {
			start = true;
			reset = false;
			stopGame = false;
		}
		break;

	case 'e':
	case 'E':
		// to exit the game
		exit(0);
		break;

	case 'r':
	case 'R':
		// the player will be allowed to restart the game
		reset = true;
		lives = 5;
		break;
	}
}

// the main method
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(900, 800);
	glutInitWindowPosition(600, 10);
	glutCreateWindow("CANNON SHOOTING");
	init();
	glutDisplayFunc(myDisplay);
	glutSpecialFunc(mySpecialKey);
	glutKeyboardFunc(processNormalKeys);
	glutMainLoop();
	return 0;
}