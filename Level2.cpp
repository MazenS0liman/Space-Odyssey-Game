#pragma once
//#include "TextureBuilder.h"
#include "Level2.h"
//#include "GLTexture.h"

using namespace std;

//=======================================================================
// Vector3f Class
//=======================================================================
Vector3f2::Vector3f2(float _x, float _y, float _z) {
	x = _x;
	y = _y;
	z = _z;
}

Vector3f2 Vector3f2::operator+(Vector3f2& v) {
	return Vector3f2(x + v.x, y + v.y, z + v.z);
}

Vector3f2 Vector3f2::operator-(Vector3f2& v) {
	return Vector3f2(x - v.x, y - v.y, z - v.z);
}

Vector3f2 Vector3f2::operator*(float n) {
	return Vector3f2(x * n, y * n, z * n);
}

Vector3f2 Vector3f2::operator/(float n) {
	return Vector3f2(x / n, y / n, z / n);
}

Vector3f2 Vector3f2::unit() {
	return *this / sqrt(x * x + y * y + z * z);
}

Vector3f2 Vector3f2::cross(Vector3f2 v) {
	return Vector3f2(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

//=======================================================================
// Camera Class
//=======================================================================
//Creates a viewing matrix that allows you to look somewhere other than the origin of your scene.
Camera2::Camera2(float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ) {
	eye = Vector3f2(eyeX, eyeY, eyeZ);
	center = Vector3f2(centerX, centerY, centerZ);
	up = Vector3f2(upX, upY, upZ);
}

void Camera2::set(float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ) {
	eye = Vector3f2(eyeX, eyeY, eyeZ);
	center = Vector3f2(centerX, centerY, centerZ);
	up = Vector3f2(upX, upY, upZ);
}

void Camera2::moveX(float d) {
	Vector3f2 right = up.cross(center - eye).unit();
	eye = eye + right * d;
	center = center + right * d;
}

void Camera2::moveY(float d) {
	eye = eye + up.unit() * d;
	center = center + up.unit() * d;
}

void Camera2::moveZ(float d) {
	Vector3f2 view = (center - eye).unit();
	eye = eye + view * d;
	center = center + view * d;
}

void Camera2::rotateX(float a) {
	Vector3f2 view = (center - eye).unit();
	Vector3f2 right = up.cross(view).unit();
	view = view * cos(DEG2RAD(a)) + up * sin(DEG2RAD(a));
	up = view.cross(right);
	center = eye + view;
}

void Camera2::rotateY(float a) {
	Vector3f2 view = (center - eye).unit();
	Vector3f2 right = up.cross(view).unit();
	view = view * cos(DEG2RAD(a)) + right * sin(DEG2RAD(a));
	right = view.cross(up);
	center = eye + view;
}

void Camera2::look() {
	gluLookAt(
		eye.x, eye.y, eye.z,
		center.x, center.y, center.z,
		up.x, up.y, up.z
	);
}


//=======================================================================
// Triple Class
//=======================================================================
Triple2::Triple2() : x(0), y(0), z(0) {}

Triple2::Triple2(double x, double y, double z) : x(x), y(y), z(z) {}

//=======================================================================
// Quad Class
//=======================================================================
Quad2::Quad2() : x(0), y(0), z(0), angle(0) {}

Quad2::Quad2(double x, double y, double z, double angle) : x(x), y(y), z(z), angle(angle) {}

//=======================================================================
// Player Class
//=======================================================================
Player2::Player2() : playerX(0), playerY(0), playerZ(0), playerRotationAngle(0), playerHealth(10), playerAttackDamage(1), playerState(0), playerRange(0), playerDirection(0) {}

Player2::Player2(double playerX, double playerY, double playerZ, double rotationAngle, double playerHealth, double playerAttackDamage, int playerState, double playerRange, int playerDirection) : playerX(playerX), playerY(playerY), playerZ(playerZ), playerRotationAngle(playerRotationAngle), playerHealth(playerHealth), playerAttackDamage(playerAttackDamage), playerState(playerState), playerRange(playerRange), playerDirection(playerDirection) {}

void Player2::drawPlayer(Triple2 translatef, Triple2 scalef, Quad2 rotatef) {
	glPushMatrix();
	glTranslatef(translatef.x, translatef.y, translatef.z);
	glRotatef(rotatef.angle - 90, rotatef.x, rotatef.y, rotatef.z);
	glScalef(scalef.x, scalef.y, scalef.z);
	model_player.Draw();
	glPopMatrix();
}

void Player2::loadPlayer() {
	model_player.Load("Models/player/player.3DS");
}

//=======================================================================
// Boss Class
//=======================================================================
Boss::Boss() : x(0), y(0), z(0), bossHealth(0), bossAttackDamage(0), bossRange(5) {}

Boss::Boss(double x, double y, double z, double alienHealth, double alienAttackDamage, double alienRange) : x(x), y(y), z(z), bossHealth(alienHealth), bossAttackDamage(alienAttackDamage), bossRange(alienRange) {}

void Boss::drawBoss(Triple2 translatef, Triple2 scalef, Quad2 rotatef) {
	glPushMatrix();
	glTranslatef(translatef.x, translatef.y, translatef.z);
	glRotatef(rotatef.angle - 45, rotatef.x, rotatef.y, rotatef.z);
	glScalef(scalef.x, scalef.y, scalef.z);
	model_boss.Draw();
	glPopMatrix();
}

void Boss::loadBoss() {
	model_boss.Load("Models/boss/Librarian.3ds");
}

//=======================================================================
// Gun Class
//=======================================================================
Gun2::Gun2() : x(0), y(0), z(0), isGunPickedUp(false) {}

Gun2::Gun2(double x, double y, double z, bool isGunPicked)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->isGunPickedUp = isGunPicked;
}

void Gun2::drawGun(Triple2 translatef, Triple2 scalef, Quad2 rotatef) {
	glPushMatrix();
	glTranslatef(translatef.x, translatef.y + 2, translatef.z);
	glRotatef(rotatef.angle, rotatef.x, rotatef.y, rotatef.z);
	glRotatef(90, 1, 0, 0);
	glScalef(scalef.x, scalef.y, scalef.z);
	model_gun.Draw();
	glPopMatrix();
}

void Gun2::loadGun() {
	model_gun.Load("Models/gun/m16.3ds");
}

//=======================================================================
// Coin Class
//=======================================================================
Apple::Apple() : x(0), y(0), z(0), appleRange(0), isApplePickedUp(false) {}

Apple::Apple(double x, double y, double z, double appleRange, bool isApplePickedUp) : x(x), y(y), z(z), appleRange(appleRange), isApplePickedUp(isApplePickedUp) {}

void Apple::drawApple(Triple2 translatef, Triple2 scalef, Quad2 rotatef) {
	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslatef(translatef.x, translatef.y, translatef.z);
	glRotatef(rotatef.angle, rotatef.x, rotatef.y, rotatef.z);
	glScalef(scalef.x, scalef.y, scalef.z);
	model_apple.Draw();
	glPopMatrix();
}

void Apple::loadApple() {
	//model_coin.Load("Models/Money/Money/Money.3ds");
	model_apple.Load("Models/apple/apple.3ds");
}

//=======================================================================
// Level 1 Functions
//=======================================================================

void Level2::drawPlayerDetails(double playerHealth) {
	glDisable(GL_LIGHTING);
	float temp = WIDTH - 100;
	float plusHealth = temp + playerHealth;
	// Switch to 2D rendering for the health bar
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, WIDTH, 0, HEIGHT);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();


	// Draw the health bar
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex2f(temp, HEIGHT); // Top left
	glVertex2f(plusHealth, HEIGHT); // Top right
	glVertex2f(plusHealth, HEIGHT - 20); // Bottom right
	glVertex2f(temp, HEIGHT - 20); // Bottom left
	glEnd();

	glColor3f(1.0f, 0.0f, 0.0f); // Red color
	glBegin(GL_QUADS);
	glVertex2f(temp, HEIGHT); // Top left
	glVertex2f(WIDTH, HEIGHT); // Top right
	glVertex2f(WIDTH, HEIGHT - 20); // Bottom right
	glVertex2f(temp, HEIGHT - 20); // Bottom left
	glEnd();



	// Restore the original 3D projection and modelview matrices
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_LIGHTING);


	glEnable(GL_LIGHTING);
}

void Level2::renderBitmapString(float x, float y, void* font, const char* string) {
	const char* c;
	glRasterPos2f(x, y);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}

void Level2::writeText(float playerAttackPower, int WIDTH, int HEIGHT) {
	// Switch to 2D orthographic projection for the text
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, WIDTH, 0, HEIGHT);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(-1130, 680, 0);
	// Disable lighting for text rendering
	glDisable(GL_LIGHTING);

	// Set the color and position for the text
	glColor3f(0.0f, 0.0f, 0.0f); // White color

	char result[100]; // Assuming a maximum string length of 100

	// Use sprintf to format the float value as a string and concatenate it
	sprintf(result, "Attack: %.1f", playerAttackPower); // %.2f specifies 2 decimal places


	renderBitmapString(WIDTH - 130, 10, GLUT_BITMAP_TIMES_ROMAN_24, result);

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glVertex2f(WIDTH - 150, 40); // Top left
	glVertex2f(WIDTH, 40); // Top right
	glVertex2f(WIDTH, 0); // Bottom right
	glVertex2f(WIDTH - 150, 0); // Bottom left
	glEnd();

	// Restore the lighting state
	glEnable(GL_LIGHTING);

	// Restore the original 3D projection and modelview matrices
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void Level2::writeScore(float score) {
	// Switch to 2D orthographic projection for the text
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, WIDTH, 0, HEIGHT);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(-WIDTH / 2.0 + 75, 680, 0);
	// Disable lighting for text rendering
	glDisable(GL_LIGHTING);

	// Set the color and position for the text
	glColor3f(0.0f, 0.0f, 0.0f); // White color

	char result[100]; // Assuming a maximum string length of 100

	// Use sprintf to format the float value as a string and concatenate it
	sprintf(result, "Score: %.1f", score); // %.2f specifies 2 decimal places


	renderBitmapString(WIDTH - 130, 10, GLUT_BITMAP_TIMES_ROMAN_24, result);

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glVertex2f(WIDTH - 150, 40); // Top left
	glVertex2f(WIDTH, 40); // Top right
	glVertex2f(WIDTH, 0); // Bottom right
	glVertex2f(WIDTH - 150, 0); // Bottom left
	glEnd();

	// Restore the lighting state
	glEnable(GL_LIGHTING);

	// Restore the original 3D projection and modelview matrices
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void Level2::drawBossHealthBar(float health) {
	float mid = WIDTH / 2.0;
	float bossLi = mid - 200 + 4 * health;
	glDisable(GL_LIGHTING);
	// Switch to 2D rendering for the health bar
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, WIDTH, 0, HEIGHT);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	// Draw the health bar
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex2f(mid - 200, HEIGHT - 50); // Top left
	glVertex2f(bossLi, HEIGHT - 50); // Top right
	glVertex2f(bossLi, HEIGHT - 70); // Bottom right
	glVertex2f(mid - 200, HEIGHT - 70); // Bottom left
	glEnd();

	glColor3f(1.0f, 0.0f, 0.0f); // Red color
	glBegin(GL_QUADS);
	glVertex2f(mid - 200, HEIGHT - 50); // Top left
	glVertex2f(mid + 200, HEIGHT - 50); // Top right
	glVertex2f(mid + 200, HEIGHT - 70); // Bottom right
	glVertex2f(mid - 200, HEIGHT - 70); // Bottom left
	glEnd();

	// Restore the original 3D projection and modelview matrices
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void Level2::playerAttack() {
	if (eucDistance(player.playerX, boss.x, player.playerZ, boss.z) < 1.3 && boss.bossHealth > 0) {
		PlaySound(TEXT("sounds/player_punch.wav"), NULL, SND_FILENAME | SND_ASYNC);
		boss.bossHealth -= player.playerAttackDamage;
		if (boss.bossHealth < 0) boss.bossHealth = 0;
		if (boss.bossHealth == 0) isFinished = true;
	}
}

bool Level2::couldBossAttack() {
	return eucDistance(player.playerX, boss.x, player.playerZ, boss.z);
}
void Level2::bossAttack() {
	if (eucDistance(player.playerX, boss.x, player.playerZ, boss.z) < 2 && player.playerHealth > 0) {
		PlaySound(TEXT("sounds/alien_roar.wav"), NULL, SND_FILENAME | SND_ASYNC);
		player.playerHealth -= boss.bossAttackDamage;
		if (player.playerHealth < 0) player.playerHealth = 0;
		if (player.playerHealth == 0) isFinished = true;
	}
}

void Level2::drawWall() {
	glBegin(GL_QUADS);
	glNormal3f(1, 1, 1);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-20, 0, 0);
	glTexCoord2f(5, 0);
	glVertex3f(20, 0, 0);
	glTexCoord2f(5, 5);
	glVertex3f(20, 0, 20);
	glTexCoord2f(0, 5);
	glVertex3f(-20, 0, 20);
	glEnd();
}

void Level2::RenderGround()
{
	/*glDisable(GL_LIGHTING);
	glColor3f(0.6, 0.6, 0.6);*/	// Dim the ground texture a bit

	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing

	glBindTexture(GL_TEXTURE_2D, tex_ground.texture[0]);	// Bind the ground texture

	// Ground
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-17, 0.1, -17);
	glTexCoord2f(5, 0);
	glVertex3f(17, 0.1, -17);
	glTexCoord2f(5, 5);
	glVertex3f(17, 0.1, 17);
	glTexCoord2f(0, 5);
	glVertex3f(-17, 0.1, 17);
	glEnd();
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tex_lava.texture[0]);

	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-20, 0, -20);
	glTexCoord2f(5, 0);
	glVertex3f(20, 0, -20);
	glTexCoord2f(5, 5);
	glVertex3f(20, 0, 20);
	glTexCoord2f(0, 5);
	glVertex3f(-20, 0, 20);
	glEnd();
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tex_ceiling.texture[0]);


	//Ceiling
	glPushMatrix();
	glTranslated(0, 20, 0);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-20, 0, -20);
	glTexCoord2f(5, 0);
	glVertex3f(20, 0, -20);
	glTexCoord2f(5, 5);
	glVertex3f(20, 0, 20);
	glTexCoord2f(0, 5);
	glVertex3f(-20, 0, 20);
	glEnd();
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tex_wall.texture[0]);
	//First wall

	glPushMatrix();
	glTranslated(0, 0, -20);
	glRotated(-90, 1, 0, 0);
	drawWall();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0, 20);
	glRotated(-90, 1, 0, 0);
	drawWall();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-20, 0, 0);
	glRotated(90, 0, 1, 0);
	glRotated(-90, 1, 0, 0);
	drawWall();
	glPopMatrix();

	glPushMatrix();
	glTranslated(20, 0, 0);
	glRotated(90, 0, 1, 0);
	glRotated(-90, 1, 0, 0);
	drawWall();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	/*glEnable(GL_LIGHTING);*/	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.
}

//=======================================================================
// OpenGL Function
//=======================================================================
//=======================================================================
// Level 1 Keyboard Function
//=======================================================================
void Level2::Keyboard(unsigned char key, int x, int y) {
	float d = 0.1;
	double prevPlayerX = player.playerX;
	double prevPlayerY = player.playerY;
	double prevPlayerZ = player.playerZ;

	switch (key) {
		// -- Camera Views -- //
	case 'i':
		camera.moveY(d);
		break;
	case 'j':
		camera.moveY(-d);
		break;
	case 'k':
		camera.moveX(d);
		break;
	case 'l':
		camera.moveX(-d);
		break;
	case 'o':
		camera.moveZ(d);
		break;
	case 'p':
		camera.moveZ(-d);
		break;

	case '1':
		camera.set(0, 20, 0.1, 0, 1, 0, 0, 2, 0);
		break;

	case '2':
		camera.set(0.05, 0.5, 20, 0.05, 0.5, 0, 0, 2, 0);
		break;

	case '3':
		camera.set(20, 1, 0, 0, 1, 0, 0, 2, 0);
		break;

	case '4':
		camera.set(0.05, 1, 10, 0.05, 0.5, 0, 0, 2, 0);
		break;

	case '5': // general view
		camera.set(0.05, 7, 40, 0.05, 0.5, 0, 0, 2, 0);
		break;

	case 'c': // first prespective view
		firstPrespective = !firstPrespective;
		thirdPrespective = !thirdPrespective;
		changePrepective();
		break;

	case '8':
		firstPrespective = false;
		thirdPrespective = false;
		break;

		// -- Player Keys -- //
	case 'd': // right
		if (checkLegalMove('d')) player.playerX += 0.1;
		player.playerRotationAngle = -90;
		player.playerDirection = 1;

		if (firstPrespective) {
			camera.set(player.playerX, 4, player.playerZ, player.playerX + 3, 4, player.playerZ, 0, 2, 0);
		}

		if (thirdPrespective) {
			camera.set(player.playerX - 4, 6, player.playerZ, player.playerX + 6, 1, player.playerZ, 0, 2, 0);
		}

		break;
	case 'w': // forward
		if (checkLegalMove('w')) player.playerZ -= 0.1;
		player.playerRotationAngle = 0;
		player.playerDirection = -2;

		if (firstPrespective) {
			camera.set(player.playerX, 4, player.playerZ, player.playerX, 4, player.playerZ - 3, 0, 2, 0);
		}

		if (thirdPrespective) {
			camera.set(player.playerX, 6, player.playerZ + 4, player.playerX, 1, player.playerZ - 8, 0, 2, 0);
		}

		break;
	case 'a': // left
		if (checkLegalMove('a')) player.playerX -= 0.1;
		player.playerRotationAngle = 90;
		player.playerDirection = -1;

		if (firstPrespective) {
			camera.set(player.playerX, 4, player.playerZ, player.playerX - 3, 4, player.playerZ, 0, 2, 0);
		}

		if (thirdPrespective) {
			camera.set(player.playerX + 4, 6, player.playerZ, player.playerX - 8, 1, player.playerZ, 0, 2, 0);
		}

		break;
	case 's': // backward
		if(checkLegalMove('s')) player.playerZ += 0.1;
		player.playerRotationAngle = 180;
		player.playerDirection = 2;

		if (firstPrespective) {
			camera.set(player.playerX, 4, player.playerZ, player.playerX, 4, player.playerZ + 3, 0, 2, 0);
		}

		if (thirdPrespective) {
			camera.set(player.playerX, 6, player.playerZ - 4, player.playerX, 1, player.playerZ + 8, 0, 2, 0);
		}
		break;

	case 'u':
		player.playerState = 0;
		break;

	case 'z': // Change the state of the player to attack
		player.playerState = 1;
		break;

	case 'x': // Change the state of the player to shield
		if (player.playerHealth > 0) {
			player.playerState = 2;
		}
		else {
			player.playerHealth = 0;
		}
		break;

	case 'f':
		playerAttack();
		break;
	case GLUT_KEY_ESCAPE:
		exit(EXIT_SUCCESS);
		break;
	default:
		break;
	}

	// checks
	checkAppleCollisions();
	checkGunCollisions();
	checkCoinCollisions();

}

//=======================================================================
// Level 1 Mouse Function
//=======================================================================
void Level2::myMouse(int button, int state, int x, int y)
{
	y = HEIGHT - y;

	if (state == GLUT_DOWN)
	{
		cameraZoom = y;
	}
}

//=======================================================================
// Level 2 Display Function
//=======================================================================
void Level2::myDisplay(void)
{
	if (!isFinished) {
		// Draw env
		RenderGround();

		// -- Health Bars and details -- //
		drawPlayerDetails(player.playerHealth);
		drawBossHealthBar(boss.bossHealth);
		writeText(player.playerAttackDamage, WIDTH, HEIGHT);
		writeScore(score);

		// boss
		boss.drawBoss(
			Triple2(boss.x, boss.y, boss.z),
			Triple2(0.025, 0.025, 0.025),
			Quad2(0, 1, 0, 45 + rotateBossWithMovement())
		);
		// player
		player.drawPlayer(
			Triple2(player.playerX, player.playerY, player.playerZ),
			Triple2(0.0025, 0.0025, 0.0025),
			Quad2(0, 1, 0, player.playerRotationAngle)
		);

		// apples
		for (Apple& app : apples) {
			if (app.isApplePickedUp) continue;
			app.drawApple(
				Triple2(app.x, app.y, app.z),
				Triple2(0.1, 0.1, 0.1),
				Quad2(0, 1, 0, 0)
			);
		}

		// weapons
		for (Gun2& gun : guns) {
			if (gun.isGunPickedUp) continue;
			gun.drawGun(
				Triple2(gun.x, gun.y, gun.z),
				Triple2(0.025, 0.05, 0.05),
				Quad2(1, 0, 0, -90)
			);
		}

		// coins
		for (Coin2& coin : coins) {
			if (coin.isCoinPickedUp) continue;
			coin.drawCoin(
				Triple2(coin.x, coin.y, coin.z),
				Triple2(0.1, 0.3, 0.1),
				Quad2(1, 0, 0, 90)
			);
		}

		//for (Obstacle2& ob : obstacles) {
		//	ob.drawObstacle(
		//		Triple2(ob.x, ob.y, ob.z),
		//		Triple2(0.1, 0.3, 0.1),
		//		Quad2(1, 0, 0, 90)
		//	);
		//}

		//drawObstacle();

		// Sky box
		glPushMatrix();
		glColor3f(1, 1, 1);
		GLUquadricObj* qobj;
		qobj = gluNewQuadric();
		glTranslated(50, 0, 0);
		glRotated(90, 1, 0, 1);
		glBindTexture(GL_TEXTURE_2D, tex);
		gluQuadricTexture(qobj, true);
		gluQuadricNormals(qobj, GL_SMOOTH);
		gluSphere(qobj, 100, 100, 100);
		gluDeleteQuadric(qobj);
		glPopMatrix();


		InitLightSource2();
	}
	else {
		if (player.playerHealth <= 0) {
			writeLose();
			glutSwapBuffers();
			Sleep(2000);
			exit(0);
		}
		if (boss.bossHealth <= 0) {
			writeWin();
			glutSwapBuffers();
			Sleep(2000);
			exit(0);
		}

	}
}

//=======================================================================
// Assets Loading Function
//=======================================================================
void Level2::LoadAssets()
{
	// -- Level 2 -- //

	for (Gun2& gun : guns) {
		gun.loadGun();
	}

	for (Apple& apple : apples) {
		apple.loadApple();
	}

	for (Coin2& coin : coins) {
		coin.loadCoin();
	}

	//for (Obstacle2& ob : obstacles) {
	//	ob.loadObstacle();
	//}


	player.loadPlayer();
	boss.loadBoss();
	// Loading texture files
	tex_lava.Load("Textures/lava.bmp");
	tex_ground.Load("Textures/ground2.bmp");
	tex_wall.Load("Textures/wall.bmp");
	tex_ceiling.Load("Textures/celing.bmp");
}

float Level2::eucDistance(float x1, float x2, float y1, float y2) {
	double sol = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
	return sqrt(sol);
}


void Level2::checkAppleCollisions() {
	for (Apple& apple : apples) {
		if (apple.isApplePickedUp || player.playerHealth == 100.0f) continue;
		double euc = eucDistance(player.playerX, apple.x, player.playerZ, apple.z);
		if (euc < 1) {
			PlaySound(TEXT("sounds/collect.wav"), NULL, SND_FILENAME | SND_ASYNC);
			player.playerHealth += 10.0f;
			apple.isApplePickedUp = true;
		}
	}
}

void Level2::checkGunCollisions() {
	for (Gun2& gun : guns) {
		if (gun.isGunPickedUp) continue;
		double euc = eucDistance(player.playerX, gun.x, player.playerZ, gun.z);
		if (euc < 1) {
			PlaySound(TEXT("media/gunPickup.wav"), NULL, SND_FILENAME | SND_ASYNC);
			player.playerAttackDamage += 1.0f;
			gun.isGunPickedUp = true;
		}
	}
}

void Level2::checkCoinCollisions() {
	for (Coin2& coin : coins) {
		if (coin.isCoinPickedUp) continue;
		double euc = eucDistance(player.playerX, coin.x, player.playerZ, coin.z);
		if (euc < 1) {
			PlaySound(TEXT("sounds/collect.wav"), NULL, SND_FILENAME | SND_ASYNC);
			score += 10.0f;
			coin.isCoinPickedUp = true;
		}
	}
}

bool Level2::checkLegalMove(unsigned char key){
	if (key == 'w') {
		return eucDistance(player.playerX, boss.x, player.playerZ - 0.1, boss.z) > 1.2 && player.playerZ > -16;
	}
	else if (key == 's') {
		return eucDistance(player.playerX, boss.x, player.playerZ + 0.1, boss.z) > 1.2 && player.playerZ < 16;
	}
	else if (key == 'd') {
		return eucDistance(player.playerX + 0.1, boss.x, player.playerZ, boss.z) > 1.2 && player.playerX < 16;
	}
	else if (key == 'a') {
		return eucDistance(player.playerX - 0.1, boss.x, player.playerZ, boss.z) > 1.2 && player.playerX > -16;
	}

	return true;
}

void Level2::changePrepective() {
	if (firstPrespective) {
		if (player.playerRotationAngle == 0) {
			camera.set(player.playerX, 4, player.playerZ, player.playerX, 4, player.playerZ - 3, 0, 2, 0);
		}
		else if (player.playerRotationAngle == -90) {
			camera.set(player.playerX, 4, player.playerZ, player.playerX + 3, 4, player.playerZ, 0, 2, 0);
		}
		else if (player.playerRotationAngle == 90) {
			camera.set(player.playerX, 4, player.playerZ, player.playerX - 3, 4, player.playerZ, 0, 2, 0);
		}
		else if (player.playerRotationAngle == 180) {
			camera.set(player.playerX, 4, player.playerZ, player.playerX, 4, player.playerZ + 3, 0, 2, 0);
		}
	}
	else {
		if (player.playerRotationAngle == 0) {
			camera.set(player.playerX, 6, player.playerZ + 4, player.playerX, 1, player.playerZ - 8, 0, 2, 0);
		}
		else if (player.playerRotationAngle == -90) {
			camera.set(player.playerX - 4, 6, player.playerZ, player.playerX + 6, 1, player.playerZ, 0, 2, 0);
		}
		else if (player.playerRotationAngle == 90) {
			camera.set(player.playerX + 4, 6, player.playerZ, player.playerX - 8, 1, player.playerZ, 0, 2, 0);
		}
		else if (player.playerRotationAngle == 180) {
			camera.set(player.playerX, 6, player.playerZ - 4, player.playerX, 1, player.playerZ + 8, 0, 2, 0);
		}
	}
}

float Level2::rotateBossWithMovement() {
	int a = player.playerZ - boss.z;
	int o = player.playerX - boss.x;
	float angle = atan2(o, a) * 180.0 / 3.14159265359;
	return angle;
}

void Level2::moveBoss() {
	float moveX = 0;
	float moveZ = 0;
	// determine x step
	if (boss.x < player.playerX) moveX = 0.1;
	else if (boss.x > player.playerX) moveX = -0.1;
	// determine z step
	if (boss.z < player.playerZ) moveZ = 0.1;
	else if (boss.z > player.playerZ) moveZ = -0.1;
	
	// update boss location
	if (eucDistance(player.playerX, boss.x, player.playerZ, boss.z) > 1.8) {
		boss.x = boss.x + moveX;
		boss.z = boss.z + moveZ;
	}
}

void Level2::Mouse(int x, int y) {
	// Calculate the change in position (delta)
	float deltaX = x - lastMouseX;
	float deltaY = y - lastMouseY;
	lastMouseX = x;
	lastMouseY = y;

	// Sensitivity factor to adjust rotation speed
	float sensitivity = 0.1f;

	// Rotate the camera
	camera.rotateX(deltaY * sensitivity); // Rotating in X with vertical mouse movement
	camera.rotateY(deltaX * sensitivity); // Rotating in Y with horizontal mouse movement

	// Redraw the scene
	glutPostRedisplay();
}

//=======================================================================
// Coin Class
//=======================================================================
Coin2::Coin2() : x(0), y(0), z(0), coinRange(0), isCoinPickedUp(false) {}

Coin2::Coin2(double x, double y, double z, double coinRange, bool isCoinPickedUp) : x(x), y(y), z(z), coinRange(coinRange), isCoinPickedUp(isCoinPickedUp) {}

void Coin2::drawCoin(Triple2 translatef, Triple2 scalef, Quad2 rotatef) {
	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslatef(translatef.x, translatef.y, translatef.z);
	glRotatef(rotatef.angle, rotatef.x, rotatef.y, rotatef.z);
	glScalef(scalef.x, scalef.y, scalef.z);
	model_coin.Draw();
	glPopMatrix();
}

void Coin2::loadCoin() {
	model_coin.Load("Models/atm/british_coin.3ds");
}

void Level2:: InitLightSource2()
{
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	// Ambient light
	GLfloat ambientColor[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientColor);

	GLfloat ambientColor2[] = { 0.3f, 0.1f, 0.1f, 1.0f };
	glLightfv(GL_LIGHT2, GL_AMBIENT, ambientColor2);

	// Diffuse light
	GLfloat diffuseColor[] = { 0.6f, 0.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseColor);

	GLfloat diffuseColor2[] = { 0.5f, 0.5f, 0.5f, 0.5f };
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseColor2);

	// Specular light
	GLfloat specularColor[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT1, GL_SPECULAR, specularColor);

	GLfloat specularColor2[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	glLightfv(GL_LIGHT2, GL_SPECULAR, specularColor2);

	GLfloat light_position1[] = { 0, 30, 0, 0.0 };
	glLightfv(GL_LIGHT2, GL_POSITION, light_position1);


	GLfloat light_position[] = { player.playerX, 3, player.playerZ, 1.0 };
	float x = 0.0f;
	float z = 0.0f;
	if (player.playerRotationAngle == 0) z = -1.0f;
	else if (player.playerRotationAngle == 180) z = 1.0f;
	else if (player.playerRotationAngle == -90) x = 1.0f;
	else x = -1.0f;
	GLfloat spotDirection[] = { x, 0.0f, z };
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDirection);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position);

	if (firstPrespective) {
		glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 15.0f);

	}
	else {
		glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 15.0f);
	}
}

void Obstacle2::drawObstacle(Triple2 translatef, Triple2 scalef, Quad2 rotatef) {
	model_obstacle.Draw();
}

void Obstacle2::loadObstacle() {
	model_obstacle.Load("Models/rock2/rockk.3DS");

}

void Level2::startUpdateGameVariables(double startScore, float startHealth, float startAttackPower) {
	if (!isStarted) {
		isStarted = true;
		score = startScore;
		player.playerHealth = startHealth;
		player.playerAttackDamage = startAttackPower;
	}
}

void Level2::writeLose() {
	// Switch to 2D orthographic projection for the text
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, WIDTH, 0, HEIGHT);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(-500, 500, 0);
	// Disable lighting for text rendering
	glDisable(GL_LIGHTING);

	// Set the color and position for the text
	glColor3f(1.0f, 0.0f, 0.0f); // White color

	string s = "You Lose!";
	int n = s.length();
	char result[9]; // Assuming a maximum string length of 100

	for (int i = 0; i < s.length(); i++)
		result[i] = s[i];

	renderBitmapString(WIDTH - 130, 10, GLUT_BITMAP_TIMES_ROMAN_24, result);

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glVertex2f(WIDTH - 150, 40); // Top left
	glVertex2f(WIDTH, 40); // Top right
	glVertex2f(WIDTH, 0); // Bottom right
	glVertex2f(WIDTH - 150, 0); // Bottom left
	glEnd();

	// Restore the lighting state
	glEnable(GL_LIGHTING);

	// Restore the original 3D projection and modelview matrices
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void Level2::writeWin() {
	// Switch to 2D orthographic projection for the text
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, WIDTH, 0, HEIGHT);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(-500, 500, 0);
	// Disable lighting for text rendering
	glDisable(GL_LIGHTING);

	// Set the color and position for the text
	glColor3f(0.0f, 1.0f, 0.0f); // White color

	char result[100]; // Assuming a maximum string length of 100

	// Use sprintf to format the float value as a string and concatenate it
	sprintf(result, "You Win Score: %.1f", score); // %.2f specifies 2 decimal places

	renderBitmapString(WIDTH - 130, 10, GLUT_BITMAP_TIMES_ROMAN_24, result);

	// Restore the lighting state
	glEnable(GL_LIGHTING);

	// Restore the original 3D projection and modelview matrices
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}