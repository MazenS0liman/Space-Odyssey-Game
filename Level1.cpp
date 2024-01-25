#pragma once
#include "TextureBuilder.h"
#include "Level1.h"
#include "GLTexture.h"

using namespace std;

//=======================================================================
// Vector3f Class
//=======================================================================
Vector3f::Vector3f(float _x, float _y, float _z) {
	x = _x;
	y = _y;
	z = _z;
}

Vector3f Vector3f::operator+(Vector3f& v) {
	return Vector3f(x + v.x, y + v.y, z + v.z);
}

Vector3f Vector3f::operator-(Vector3f& v) {
	return Vector3f(x - v.x, y - v.y, z - v.z);
}

Vector3f Vector3f::operator*(float n) {
	return Vector3f(x * n, y * n, z * n);
}

Vector3f Vector3f::operator/(float n) {
	return Vector3f(x / n, y / n, z / n);
}

Vector3f Vector3f::unit() {
	return *this / sqrt(x * x + y * y + z * z);
}

Vector3f Vector3f::cross(Vector3f v) {
	return Vector3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

//=======================================================================
// Camera Class
//=======================================================================
//Creates a viewing matrix that allows you to look somewhere other than the origin of your scene.
Camera::Camera(float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ) {
	eye = Vector3f(eyeX, eyeY, eyeZ);
	center = Vector3f(centerX, centerY, centerZ);
	up = Vector3f(upX, upY, upZ);
}

void Camera::set(float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ) {
	eye = Vector3f(eyeX, eyeY, eyeZ);
	center = Vector3f(centerX, centerY, centerZ);
	up = Vector3f(upX, upY, upZ);
}

void Camera::moveX(float d) {
	Vector3f right = up.cross(center - eye).unit();
	eye = eye + right * d;
	center = center + right * d;
}

void Camera::moveY(float d) {
	eye = eye + up.unit() * d;
	center = center + up.unit() * d;
}

void Camera::moveZ(float d) {
	Vector3f view = (center - eye).unit();
	eye = eye + view * d;
	center = center + view * d;
}

void Camera::rotateX(float a) {
	Vector3f view = (center - eye).unit();
	Vector3f right = up.cross(view).unit();
	view = view * cos(DEG2RAD(a)) + up * sin(DEG2RAD(a));
	up = view.cross(right);
	center = eye + view;
}

void Camera::rotateY(float a) {
	Vector3f view = (center - eye).unit();
	Vector3f right = up.cross(view).unit();
	view = view * cos(DEG2RAD(a)) + right * sin(DEG2RAD(a));
	right = view.cross(up);
	center = eye + view;
}

void Camera::look() {
	gluLookAt(
		eye.x, eye.y, eye.z,
		center.x, center.y, center.z,
		up.x, up.y, up.z
	);
}

//=======================================================================
// Triple Class
//=======================================================================
Triple::Triple() : x(0), y(0), z(0) {}

Triple::Triple(double x, double y, double z) : x(x), y(y), z(z) {}

//=======================================================================
// Quad Class
//=======================================================================
Quad::Quad() : x(0), y(0), z(0), angle(0) {}

Quad::Quad(double x, double y, double z, double angle) : x(x), y(y), z(z), angle(angle) {}

//=======================================================================
// Player Class
//=======================================================================
Player::Player() : playerX(0), playerY(0), playerZ(0), playerRotationAngle(0), playerHealth(10), playerAttackDamage(1), playerState(0), playerRange(0), playerDirection(0) {}

Player::Player(double playerX, double playerY, double playerZ, double rotationAngle, double playerHealth, double playerAttackDamage, int playerState, double playerRange, int playerDirection) : playerX(playerX), playerY(playerY), playerZ(playerZ), playerRotationAngle(playerRotationAngle), playerHealth(playerHealth), playerAttackDamage(playerAttackDamage), playerState(playerState), playerRange(playerRange), playerDirection(playerDirection) {}

void Player::drawPlayer(Triple translatef, Triple scalef, Quad rotatef) {
	glPushMatrix();
	glTranslatef(translatef.x, translatef.y, translatef.z);
	glRotatef(rotatef.angle, rotatef.x, rotatef.y, rotatef.z);
	glScalef(scalef.x, scalef.y, scalef.z);
	model_player.Draw();
	glPopMatrix();
}

void Player::loadPlayer() {
	model_player.Load("Models/player/player.3DS");
}

//=======================================================================
// Alien Class
//=======================================================================
Alien::Alien() : x(0), y(0), z(0), alienHealth(0), alienAttackDamage(0), alienRange(5) {}

Alien::Alien(double x, double y, double z, double alienHealth, double alienAttackDamage, double alienRange) : x(x), y(y), z(z), alienHealth(alienHealth), alienAttackDamage(alienAttackDamage), alienRange(alienRange) {}

void Alien::drawAlien(Triple translatef, Triple scalef, Quad rotatef) {
	glPushMatrix();
	//glColor3f(1, 0, 0);
	glTranslatef(translatef.x, translatef.y, translatef.z);
	glRotatef(rotatef.angle, rotatef.x, rotatef.y, rotatef.z);
	glScalef(scalef.x, scalef.y, scalef.z);
	model_alien.Draw();
	glPopMatrix();
}

void Alien::loadAlien() {
	model_alien.Load("Models/alien/alien.3ds");
}

//=======================================================================
// Spaceship Class
//=======================================================================
Spaceship::Spaceship() : spaceshipX(0), spaceshipY(0), spaceshipZ(0), spaceshipRange(0) {}

Spaceship::Spaceship(double spaceshipX, double spaceshipY, double spaceshipZ, double spaceshipRange) : spaceshipX(spaceshipX), spaceshipY(spaceshipY), spaceshipZ(spaceshipZ), spaceshipRange(spaceshipRange) {}

void Spaceship::drawSpaceship(Triple translatef, Triple scalef, Quad rotatef) {
	translatef.x += 5;
	translatef.z += 5;
	glPushMatrix();
	glTranslatef(translatef.x, translatef.y, translatef.z);
	glRotatef(rotatef.angle, rotatef.x, rotatef.y, rotatef.z);
	glScalef(scalef.x, scalef.y, scalef.z);
	model_spaceship.Draw();
	glPopMatrix();
}

void Spaceship::loadSpaceship() {
	model_spaceship.Load("Models/spaceship/Sample_Ship.3DS");
}

//=======================================================================
// Gun Class
//=======================================================================
Gun::Gun() : x(0), y(0), z(0), isGunPickedUp(false) {}

Gun::Gun(double x, double y, double z, bool isGunPicked)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->isGunPickedUp = isGunPicked;
}

void Gun::drawGun(Triple translatef, Triple scalef, Quad rotatef) {
	glPushMatrix();
	glTranslatef(translatef.x, translatef.y, translatef.z);
	glRotatef(rotatef.angle, rotatef.x, rotatef.y, rotatef.z);
	glScalef(scalef.x, scalef.y, scalef.z);
	model_gun.Draw();
	glPopMatrix();
}

void Gun::loadGun() {
	model_gun.Load("Models/gun/m16.3ds");
}

//=======================================================================
// Spacecraft Class
//=======================================================================
Spacecraft::Spacecraft() : spacecraftX(0), spacecraftY(0), spacecraftZ(0) {}

Spacecraft::Spacecraft(double spacecraftX, double spacecraftY, double spacecraftZ) : spacecraftX(spacecraftX), spacecraftY(spacecraftY), spacecraftZ(spacecraftZ) {}

void Spacecraft::drawSpacecraft(Triple translatef, Triple scalef, Quad rotatef) {
	glPushMatrix();
	glTranslatef(translatef.x, translatef.y, translatef.z);
	glRotatef(rotatef.angle, rotatef.x, rotatef.y, rotatef.z);
	glScalef(scalef.x, scalef.y, scalef.z);
	model_spacecraft.Draw();
	glPopMatrix();
}

void Spacecraft::loadSpacecraft() {
	model_spacecraft.Load("Models/spacecraft/C3PO.3DS");
}

//=======================================================================
// Rock Class
//=======================================================================
Rock::Rock() : rockX(0), rockY(0), rockZ(0) {}

Rock::Rock(double rockX, double rockY, double rockZ) : rockX(rockX), rockY(rockY), rockZ(rockZ) {}

void Rock::drawRock(Triple translatef, Triple scalef, Quad rotatef) {
	glPushMatrix();
	glTranslatef(translatef.x, translatef.y, translatef.z);
	glRotatef(rotatef.angle, rotatef.x, rotatef.y, rotatef.z);
	glScalef(scalef.x, scalef.y, scalef.z);
	model_rock.Draw();
	glPopMatrix();
}

void Rock::loadRock() {
	model_rock.Load("Models/rocks/CavePlatform4.3DS");
}

//=======================================================================
// Coin Class
//=======================================================================
Coin::Coin() : x(0), y(0), z(0), coinRange(0), isCoinPickedUp(false) {}

Coin::Coin(double x, double y, double z, double coinRange, bool isCoinPickedUp) : x(x), y(y), z(z), coinRange(coinRange), isCoinPickedUp(isCoinPickedUp) {}

void Coin::drawCoin(Triple translatef, Triple scalef, Quad rotatef) {
	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslatef(translatef.x, translatef.y, translatef.z);
	glRotatef(rotatef.angle, rotatef.x, rotatef.y, rotatef.z);
	glScalef(scalef.x, scalef.y, scalef.z);
	model_coin.Draw();
	glPopMatrix();
}

void Coin::loadCoin() {
	//model_coin.Load("Models/Money/Money/Money.3ds");
	model_coin.Load("Models/atm/british_coin.3ds");
}

//=======================================================================
// Old Tree Class
//=======================================================================
OldTree::OldTree() : treeX(0), treeY(0), treeZ(0) {}
OldTree::OldTree(double treeX, double treeY, double treeZ) : treeX(treeX), treeY(treeY), treeZ(treeZ) {}

void OldTree::drawOldTree(Triple translatef, Triple scalef, Quad rotatef) {
	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslatef(translatef.x, translatef.y, translatef.z);
	glRotatef(rotatef.angle, rotatef.x, rotatef.y, rotatef.z);
	glScalef(scalef.x, scalef.y, scalef.z);
	model_tree.Draw();
	glPopMatrix();
}

void OldTree::loadOldTree() {
	model_tree.Load("Models/old_tree/Tree1.3DS");
}

//=======================================================================
// Level 1 Functions
//=======================================================================
//bool Level1::objectCollisionDetection(Triple playerPosition, double playerBoundaryRadius, Triple objectPosition, double objectBoundaryRadius) {
//	// Calculate player and object boundaries
//	double playerMinX = playerPosition.x - playerBoundaryRadius;
//	double playerMaxX = playerPosition.x + playerBoundaryRadius;
//	double playerMinZ = playerPosition.z - playerBoundaryRadius;
//	double playerMaxZ = playerPosition.z + playerBoundaryRadius;
//
//	double objectMinX = objectPosition.x - objectBoundaryRadius;
//	double objectMaxX = objectPosition.x + objectBoundaryRadius;
//	double objectMinZ = objectPosition.z - objectBoundaryRadius;
//	double objectMaxZ = objectPosition.z + objectBoundaryRadius;
//
//	// Check for collision
//	if (playerMaxX >= objectMinX && playerMinX <= objectMaxX && playerMaxZ >= objectMinZ && playerMinZ <= objectMaxZ) {
//		return true; // Collision detected
//	}
//
//	return false; // No collision
//}

bool Level1::objectCollisionDetection(Triple playerPosition, double playerBoundaryRadius, Triple objectPosition, double objectBoundaryRadius) {
	double distance = sqrt(pow(playerPosition.x - objectPosition.x, 2) + pow(playerPosition.z - objectPosition.z, 2));

	return distance <= playerBoundaryRadius + objectBoundaryRadius;
}

bool Level1::specialObjectCollisionDetection(Triple playerPosition, double playerBoundaryRadius, Triple objectPosition, double objectBoundaryX, double objectBoundaryZ) {
	// Calculate player and object boundaries
	double playerMinX = playerPosition.x - playerBoundaryRadius;
	double playerMaxX = playerPosition.x + playerBoundaryRadius;
	double playerMinZ = playerPosition.z - playerBoundaryRadius;
	double playerMaxZ = playerPosition.z + playerBoundaryRadius;

	double objectMinX = objectPosition.x - objectBoundaryX;
	double objectMaxX = objectPosition.x + objectBoundaryX;
	double objectMinZ = objectPosition.z - objectBoundaryZ;
	double objectMaxZ = objectPosition.z + objectBoundaryZ;

	// Check for collision
	if (playerMaxX >= objectMinX && playerMinX <= objectMaxX && playerMaxZ >= objectMinZ && playerMinZ <= objectMaxZ) {
		return true; // Collision detected
	}

	return false; // No collision
}

bool Level1::hitTarget(Spaceship& spacehip, Player& player) {
	spaceship.spaceshipZ -= 2.5;
	spaceship.spaceshipX -= 5;
	double distance = sqrt(pow(player.playerX - spacehip.spaceshipX, 2) + pow(player.playerZ - spacehip.spaceshipZ, 2));
	//cout << player.playerX << " " << player.playerZ << " " << spaceship.spaceshipX << " " << spaceship.spaceshipZ << endl;
	//cout << distance << endl;
	spaceship.spaceshipZ += 2.5;
	spaceship.spaceshipX += 5;
	return distance <= 1.5;
}

void Level1::drawBoundaries(double sphereRadius, Triple translatef, Triple scalef, Quad rotatef) {
	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslatef(translatef.x, translatef.y, translatef.z);
	glRotatef(rotatef.angle, rotatef.x, rotatef.y, rotatef.z);
	glScalef(scalef.x, scalef.y, scalef.z);
	glutSolidSphere(sphereRadius, 30, 30);
	glPopMatrix();
}

void Level1::killOutOfBound(Alien* aliens, int size, double posX, double posZ, double negX, double negZ) {
	for (int i = 0; i < size; i++) {
		Alien& alien = aliens[i];
		if (alien.x > posX || alien.x < negX || alien.z > posZ || alien.z < negZ) {
			alien.alienHealth = 0;
		}
	}
}

void Level1::fight(double posX, double posZ, double negX, double negZ) {

	for (int i = 0; i < aliensArraySize; i++) {

		if (player.playerHealth <= 0) {
			return;
		}

		Alien& alien = aliens[i];

		bool isCollide = objectCollisionDetection(
			Triple(player.playerX, player.playerY, player.playerZ),
			player.playerRange,
			Triple(alien.x, alien.y, alien.z),
			alien.alienRange
		);

		switch (player.playerState) {
		case 0: // Default
			if (isCollide) {
				if (alien.alienHealth > 0) {
					player.playerHealth -= alien.alienAttackDamage;
					alienAttackRemtime = val;
					playerPainRemTime = val;
					alienAttackSound->play2D("media/alienAttack.wav", false);
					playerPainSound->play2D("media/playerPain.mp3", false);
				}
			}
			break;
		case 1: // Attack
			if (isCollide) {
				playerAttackRemTime = val;
				playerAttackSound->play2D("media/playerAttack.mp3", false);
				alien.alienHealth -= player.playerAttackDamage;
				switch (player.playerDirection) {
				case 1: // "+ve X-direction"
					alien.x += 1;
					break;
				case -1: // "-ve X-direction"
					alien.x -= 1;
					break;
				case 2: // "+ve Z-direction"
					alien.z += 1;
					break;
				case -2: // "-ve Z-direction"
					alien.z -= 1;
					break;
				}
			}
			break;
		case 2: // Shield
			if (isCollide) {
				shieldRemTime = val;
				shieldSound->play2D("media/shield.wav", false);
				player.playerHealth += 1;
			}
			break;
		}
	}

	killOutOfBound(aliens, aliensArraySize, posX, posZ, negX, negZ);
}
void Level1::validatePlayerPosition(Triple prevPosition, Player& player, Alien* aliens, int aliensArraySize) {
	bool isCollide = false;

	// Check passing through with aliens
	for (int i = 0; i < aliensArraySize; i++) {
		Alien& alien = aliens[i];
		if (alien.alienHealth > 0) {
			isCollide = objectCollisionDetection(Triple(player.playerX, player.playerY, player.playerZ), 0.5, Triple(alien.x, alien.y, alien.z), 0.5);
		}
		else {
			isCollide = false;
		}

		if (isCollide) {
			player.playerX = prevPosition.x;
			player.playerY = prevPosition.y;
			player.playerZ = prevPosition.z;
			break;
		}
	}

	for (int i = 0; i < treesArraySize; i++) {
		OldTree& tree = trees[i];
		isCollide = objectCollisionDetection(Triple(player.playerX, player.playerY, player.playerZ), 0.5, Triple(tree.treeX, tree.treeY, tree.treeZ), 0.5);

		if (isCollide) {
			player.playerX = prevPosition.x;
			player.playerY = prevPosition.y;
			player.playerZ = prevPosition.z;
			break;
		}
	}

	for (int i = 0; i < rocksArraySize; i++) {
		Rock& rock = rocks[i];
		isCollide = specialObjectCollisionDetection(Triple(player.playerX, player.playerY, player.playerZ), 0.5, Triple(rock.rockX, rock.rockY, rock.rockZ), 3.8, 2.2);

		if (isCollide) {
			player.playerX = prevPosition.x;
			player.playerY = prevPosition.y;
			player.playerZ = prevPosition.z;
			break;
		}
	}
}

void Level1::checkPlayerWithinBoundaries(Triple prevPosition, Player& player, double posX, double posZ, double negX, double negZ) {
	if (player.playerX > posX || player.playerZ > posZ || player.playerX < negX || player.playerZ < negZ) {
		player.playerX = prevPosition.x;
		player.playerZ = prevPosition.z;
	}
}

void Level1::collectWeapons(Gun* guns, Player& player, int size) {
	for (int i = 0; i < size; i++) {
		if (guns[i].isGunPickedUp)
			continue;
		Gun& gun = guns[i];
		bool isCollide = specialObjectCollisionDetection(
			Triple(player.playerX, player.playerY, player.playerZ),
			player.playerRange - 0.25,
			Triple(gun.x, gun.y, gun.z),
			0.5,
			0.1
		);

		if (isCollide) {
			gunRemTime = val;
			gunPickupSound->play2D("media/gunPickup.wav", false);
			gun.isGunPickedUp = true;
			player.playerAttackDamage += 1;
		}
	}
}

void Level1::collectCoins(Coin* coins, Player& player, int size, double& score) {

	for (int i = 0; i < size; i++) {
		if (coins[i].isCoinPickedUp)
			continue;
		Coin& coin = coins[i];
		bool isCollide = objectCollisionDetection(
			Triple(player.playerX, player.playerY, player.playerZ),
			player.playerRange,
			Triple(coin.x, coin.y, coin.z),
			0.005
		);

		if (isCollide) {
			coinRemTime = val;
			coinPickupSound->play2D("media/coinPickup.mp3", false);
			coin.isCoinPickedUp = true;
			score += 10;
		}
	}
}

void Level1::drawPlayerDetails(double playerHealth, double playerMaxHealth, int WIDTH, int HEIGHT) {
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

}

void Level1::renderBitmapString(float x, float y, void* font, const char* string) {
	const char* c;
	glRasterPos2f(x, y);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}

void Level1::writeText(float playerAttackPower, int WIDTH, int HEIGHT) {
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

void Level1::writeScore(int WIDTH, int HEIGHT, double& score) {
	// Switch to 2D orthographic projection for the text
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, WIDTH, 0, HEIGHT);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(-600, 680, 0);
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

void Level1::writeLose(int WIDTH, int HEIGHT) {
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
	glColor3f(0.0f, 0.0f, 0.0f); // White color

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

void Level1::RenderGround()
{
	glDisable(GL_LIGHTING);	// Disable lighting 

	glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit

	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing

	glBindTexture(GL_TEXTURE_2D, tex_ground.texture[0]);	// Bind the ground texture

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

	glDisable(GL_TEXTURE_2D);

	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.
}

//=======================================================================
// OpenGL Function
//=======================================================================
//=======================================================================
// Change Prespective Function
//=======================================================================
void Level1::changePrepective() {
	if (firstPrespective) {
		if (player.playerRotationAngle == 0) { // -ve X direction
			camera.set(player.playerX, 2, player.playerZ, player.playerX - 3, 1, player.playerZ, 0, 2, 0);
		}
		else if (player.playerRotationAngle == -90) { // -ve Z direction
			camera.set(player.playerX, 2, player.playerZ, player.playerX, 1, player.playerZ - 3, 0, 2, 0);
		}
		else if (player.playerRotationAngle == 90) { // +ve Z direction
			camera.set(player.playerX, 2, player.playerZ, player.playerX, 1, player.playerZ + 3, 0, 2, 0);
		}
		else if (player.playerRotationAngle == 180) { // v+e X direction
			camera.set(player.playerX, 2, player.playerZ, player.playerX + 3, 1, player.playerZ, 0, 2, 0);
		}
	}
	else { // third prespective
		if (player.playerRotationAngle == 0) { // -ve X direction
			camera.set(player.playerX + 3.2, 3, player.playerZ, player.playerX - 3, 1, player.playerZ, 0, 2, 0);
		}
		else if (player.playerRotationAngle == -90) { // -ve Z direction
			camera.set(player.playerX, 3, player.playerZ + 3.2, player.playerX, 1, player.playerZ - 3, 0, 2, 0);
		}
		else if (player.playerRotationAngle == 90) { // +ve Z direction
			camera.set(player.playerX, 3, player.playerZ - 2.9, player.playerX, 1, player.playerZ + 3, 0, 2, 0);
		}
		else if (player.playerRotationAngle == 180) { // v+e X direction
			camera.set(player.playerX - 2.8, 3, player.playerZ, player.playerX + 3, 1, player.playerZ, 0, 2, 0);
		}
	}
}


//=======================================================================
// Level 1 Light Source Function
//=======================================================================
void Level1::InitLightSource1()
{
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);

	// Ambient light
	GLfloat ambient0[] = { 0.1f, 0.1f, 0.1, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);

	GLfloat ambientColor[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientColor);

	GLfloat ambientColor2[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	glLightfv(GL_LIGHT2, GL_AMBIENT, ambientColor2);

	// Diffuse light
	GLfloat diffuse0[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);

	GLfloat diffuseColor[] = { 0.6f, 0.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseColor);

	GLfloat diffuseColor2[] = { 0.5f, 0.5f, 0.5f, 0.5f };
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseColor2);

	// Specular light
	GLfloat specular0[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);

	GLfloat specularColor[] = { 0.6f, 0.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT1, GL_SPECULAR, specularColor);

	GLfloat specularColor2[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	glLightfv(GL_LIGHT2, GL_SPECULAR, specularColor2);

	// Finally, define light source 0 position in World Space
	GLfloat light_position0[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);

	GLfloat light_position1[] = { 0, 30, 0, 0.0 };
	glLightfv(GL_LIGHT2, GL_POSITION, light_position1);

	GLfloat light_position[] = { player.playerX, 1, player.playerZ , 1.0 };
	glLightfv(GL_LIGHT1, GL_POSITION, light_position);

	GLfloat spotDirectionW[] = { lightX, lightY, lightZ };
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDirectionW);

	// Set up the spotlight direction
	if (firstPrespective) {
		// Set the spotlight cutoff angle
		glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 15.0f);  // Angle in degrees
	}
	else {
		// Set the spotlight cutoff angle
		glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 15.0f);  // Angle in degrees
	}
}

//=======================================================================
// Level 1 Configuration Function
//=======================================================================
void Level1::myInit(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(fovy, aspectRatio, zNear, zFar);
	//***********//
	// fovy:			Angle between the bottom and top of the projectors, in degrees.			 //
	// aspectRatio:		Ratio of width to height of the clipping plane.							 //
	// zNear and zFar:	Specify the front and back clipping planes distances from camera.		 //
	//***********//

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	gluLookAt(camera.eye.x, camera.eye.y, camera.eye.z, camera.center.x, camera.center.y, camera.center.z, camera.up.x, camera.up.y, camera.up.z);
	//***********//
	// EYE (ex, ey, ez): defines the location of the camera.									 //
	// AT (ax, ay, az):	 denotes the direction where the camera is aiming at.					 //
	// UP (ux, uy, uz):  denotes the upward orientation of the camera.							 //
	//***********//

	// InitLightSource();

	InitMaterial();

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_NORMALIZE);
}


//=======================================================================
// Level 1 Material Configuration Function
//======================================================================
void Level1::InitMaterial()
{
	// Enable Material Tracking
	glEnable(GL_COLOR_MATERIAL);

	// Sich will be assigneet Material Properties whd by glColor
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Set Material's Specular Color
	// Will be applied to all objects
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

	// Set Material's Shine value (0->128)
	GLfloat shininess[] = { 96.0f };
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}


//=======================================================================
// Level 1 Keyboard Function
//=======================================================================
void Level1::Keyboard(unsigned char key, int x, int y) {
	float d = 0.1;
	double prevPlayerX = player.playerX;
	double prevPlayerY = player.playerY;
	double prevPlayerZ = player.playerZ;

	switch (key) {
		// -- Camera Views -- //
	case 'i':
		camera.moveY(d);
		if (isPlayerMoving)
		{
			playerWalkSound->stopAllSounds();
			isPlayerMoving = false;
			remTime = 0;
		}
		break;
	case 'j':
		camera.moveY(-d);
		if (isPlayerMoving)
		{
			playerWalkSound->stopAllSounds();
			isPlayerMoving = false;
			remTime = 0;
		}
		break;
	case 'k':
		camera.moveX(d);
		if (isPlayerMoving)
		{
			playerWalkSound->stopAllSounds();
			isPlayerMoving = false;
			remTime = 0;
		}
		break;
	case 'l':
		camera.moveX(-d);
		if (isPlayerMoving)
		{
			playerWalkSound->stopAllSounds();
			isPlayerMoving = false;
			remTime = 0;
		}
		break;
	case 'q':
		camera.moveZ(d);
		if (isPlayerMoving)
		{
			playerWalkSound->stopAllSounds();
			isPlayerMoving = false;
			remTime = 0;
		}
		break;
	case 'e':
		camera.moveZ(-d);
		if (isPlayerMoving)
		{
			playerWalkSound->stopAllSounds();
			isPlayerMoving = false;
			remTime = 0;
		}
		break;
	case '1':
		camera.set(0, 20, 0.1, 0, 1, 0, 0, 2, 0);
		if (isPlayerMoving)
		{
			playerWalkSound->stopAllSounds();
			isPlayerMoving = false;
			remTime = 0;
		}
		break;
	case '2':
		camera.set(0.05, 0.5, 20, 0.05, 0.5, 0, 0, 2, 0);
		if (isPlayerMoving)
		{
			playerWalkSound->stopAllSounds();
			isPlayerMoving = false;
			remTime = 0;
		}
		break;
	case '3':
		camera.set(20, 1, 0, 0, 1, 0, 0, 2, 0);
		if (isPlayerMoving)
		{
			playerWalkSound->stopAllSounds();
			isPlayerMoving = false;
			remTime = 0;
		}
		break;

	case '4':
		camera.set(0.05, 1, 10, 0.05, 0.5, 0, 0, 2, 0);
		if (isPlayerMoving)
		{
			playerWalkSound->stopAllSounds();
			isPlayerMoving = false;
			remTime = 0;
		}
		break;

	case '5': // general view
		camera.set(0.05, 7, 40, 0.05, 0.5, 0, 0, 2, 0);
		if (isPlayerMoving)
		{
			playerWalkSound->stopAllSounds();
			isPlayerMoving = false;
			remTime = 0;
		}
		break;

	case '6': // first prespective view
		firstPrespective = true;
		thirdPrespective = false;
		if (isPlayerMoving)
		{
			playerWalkSound->stopAllSounds();
			isPlayerMoving = false;
			remTime = 0;
		}
		break;

	case '7': // second prespective view
		thirdPrespective = true;
		firstPrespective = false;
		if (isPlayerMoving)
		{
			playerWalkSound->stopAllSounds();
			isPlayerMoving = false;
			remTime = 0;
		}
		break;

	case '8':
		firstPrespective = false;
		thirdPrespective = false;
		if (isPlayerMoving)
		{
			playerWalkSound->stopAllSounds();
			isPlayerMoving = false;
			remTime = 0;
		}
		break;

		// -- Player Keys -- //
	case 'd': //  +ve X-direction
		key = 'd';
		lightX = 1.0;
		lightY = 0.0;
		lightZ = 0.0;
		player.playerX += 0.1;
		player.playerRotationAngle = 180;
		player.playerDirection = 1;
		if (!isPlayerMoving)
		{
			playerWalkSound->play2D("media/walk.mp3", true);
			isPlayerMoving = true;
			remTime = val;
		}
		if (firstPrespective) {
			camera.set(player.playerX, 2, player.playerZ, player.playerX + 3, 1, player.playerZ, 0, 2, 0);
		}

		if (thirdPrespective) {
			camera.set(player.playerX - 2.8, 3, player.playerZ, player.playerX + 3, 1, player.playerZ, 0, 2, 0);
		}

		break;
	case 'w': // -ve Z-direction
		key = 'w';
		lightX = 0.0;
		lightY = 0.0;
		lightZ = -1.0;
		player.playerZ -= 0.1;
		player.playerRotationAngle = -90;
		player.playerDirection = -2;
		if (!isPlayerMoving)
		{
			playerWalkSound->play2D("media/walk.mp3", true);
			isPlayerMoving = true;
			remTime = val;
		}
		if (firstPrespective) {
			camera.set(player.playerX, 2, player.playerZ, player.playerX, 1, player.playerZ - 3, 0, 2, 0);
		}

		if (thirdPrespective) {
			camera.set(player.playerX, 3, player.playerZ + 3.2, player.playerX, 1, player.playerZ - 3, 0, 2, 0);
		}

		break;
	case 'a': // -ve X-direction
		key = 'a';
		lightX = -1.0;
		lightY = 0.0;
		lightZ = 0.0;
		player.playerX -= 0.1;
		player.playerRotationAngle = 0;
		player.playerDirection = -1;
		if (!isPlayerMoving)
		{
			playerWalkSound->play2D("media/walk.mp3", true);
			isPlayerMoving = true;
			remTime = val;
		}
		if (firstPrespective) {
			camera.set(player.playerX, 2, player.playerZ, player.playerX - 3, 1, player.playerZ, 0, 2, 0);
		}

		if (thirdPrespective) {
			camera.set(player.playerX + 3.2, 3, player.playerZ, player.playerX - 3, 1, player.playerZ, 0, 2, 0);
		}

		break;
	case 's': // +ve Z-direction
		key = 's';
		lightX = 0.0;
		lightY = 0.0;
		lightZ = 1.0;
		player.playerZ += 0.1;
		player.playerRotationAngle = 90;
		player.playerDirection = 2;
		if (!isPlayerMoving)
		{
			playerWalkSound->play2D("media/walk.mp3", true);
			isPlayerMoving = true;
			remTime = val;
		}
		if (firstPrespective) {
			camera.set(player.playerX, 2, player.playerZ, player.playerX, 1, player.playerZ + 3, 0, 2, 0);
		}

		if (thirdPrespective) {
			camera.set(player.playerX, 3, player.playerZ - 2.9, player.playerX, 1, player.playerZ + 3, 0, 2, 0);
		}
		break;
	case 'u':
		player.playerState = 0;
		if (isPlayerMoving)
		{
			playerWalkSound->stopAllSounds();
			isPlayerMoving = false;
			remTime = 0;
		}
		break;
	case 'f': // Change the state of the player to attack
		player.playerState = 1;
		if (isPlayerMoving)
		{
			playerWalkSound->stopAllSounds();
			isPlayerMoving = false;
			remTime = 0;
		}
		break;
	case 'p': // Change the state of the player to shield
		if (player.playerHealth > 0) {
			player.playerState = 2;
		}
		else {
			player.playerHealth = 0;
		}
		break;
	case 'c':
		firstPrespective = !firstPrespective;
		thirdPrespective = !thirdPrespective;
		changePrepective();
		break;

	default:
		if (isPlayerMoving) {
			playerWalkSound->stopAllSounds();
			isPlayerMoving = false;
			remTime = 0;
		}
		break;

	case GLUT_KEY_ESCAPE:
		exit(EXIT_SUCCESS);
	}

	// Level 1 Checks
	validatePlayerPosition(Triple(prevPlayerX, prevPlayerY, prevPlayerZ), player, aliens, aliensArraySize);
	checkPlayerWithinBoundaries(Triple(prevPlayerX, prevPlayerY, prevPlayerZ), player, 20, 20, -20, -20);
}

//=======================================================================
// Level 1 Mouse Function
//=======================================================================
void Level1::myMouse(int button, int state, int x, int y)
{
	y = HEIGHT - y;

	if (state == GLUT_DOWN)
	{
		cameraZoom = y;
	}
}

//=======================================================================
// Level 1 Motion Function
//=======================================================================
void Level1::myMotion(int x, int y)
{
	y = HEIGHT - y;

	if (cameraZoom - y > 0)
	{
		camera.eye.x += -0.1;
		camera.eye.z += -0.1;
	}
	else
	{
		camera.eye.x += 0.1;
		camera.eye.z += 0.1;
	}

	cameraZoom = y;

	glLoadIdentity();	//Clear Model_View Matrix

	camera.look();

	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

//=======================================================================
// Level 1 Mouse Function
//=======================================================================
void Level1::Mouse(int x, int y) {
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
// Level 1 Display Function
//=======================================================================
void Level1::myDisplay(void)
{
	if (player.playerHealth <= 0) {
		writeLose(WIDTH, HEIGHT);
		glutSwapBuffers();
		Sleep(2000);
		exit(0);
	}

	if (remTime > 0)
	{
		remTime--;
	}
	else if (isPlayerMoving)
	{
		playerWalkSound->stopAllSounds();
		isPlayerMoving = false;
	}

	if (playerAttackRemTime > 0)
	{
		playerAttackRemTime--;
	}
	else
	{
		playerAttackSound->stopAllSounds();
	}

	if (alienAttackRemtime > 0)
	{
		alienAttackRemtime--;
	}
	else
	{
		alienAttackSound->stopAllSounds();
	}

	if (playerPainRemTime > 0)
	{
		playerPainRemTime--;
	}
	else
	{
		playerPainSound->stopAllSounds();
	}

	if (shieldRemTime > 0)
	{
		shieldRemTime--;
	}
	else
	{
		shieldSound->stopAllSounds();
	}
	// -- Level 1 -- //
	// Draw Ground
	RenderGround();

	// -- Weapons -- //
	collectWeapons(guns, player, size2);
	collectCoins(coins, player, coinsArraySize, score);

	// -- Target -- //
	bool displayTarget = true;
	for (int i = 0; i < aliensArraySize; i++) {
		Alien& alien = aliens[i];
		if (alien.alienHealth > 0) {
			displayTarget = false;
		}
	}

	if (displayTarget) {
		if (hitTarget(spaceship, player)) {
			spaceshipRemTime = val;
			spaceshipSound->play2D("media/spaceshipCollision.mp3", false);
			Sleep(1000);
			finished = true;
			// exit(0);
		}
		spaceship.drawSpaceship(
			Triple(spaceship.spaceshipX, spaceship.spaceshipY, spaceship.spaceshipZ),
			Triple(5, 5, 5),
			Quad(0, 1, 0, -90)
		);

	}

	// -- Player -- //
	if (player.playerHealth > 0) {
		player.drawPlayer(
			Triple(player.playerX, player.playerY, player.playerZ),
			Triple(0.001, 0.001, 0.001),
			Quad(0, 1, 0, player.playerRotationAngle)
		);
	}

	// -- Aliens -- //
	if (alien1.alienHealth > 0) {
		alien1.drawAlien(
			Triple(alien1.x, alien1.y, alien1.z),
			Triple(0.05, 0.05, 0.05),
			Quad(0, 1, 0, 0)
		);
	}

	if (alien2.alienHealth > 0) {
		alien2.drawAlien(
			Triple(alien2.x, alien2.y, alien2.z),
			Triple(0.05, 0.05, 0.05),
			Quad(0, 1, 0, 0)
		);
	}

	if (alien3.alienHealth > 0) {
		alien3.drawAlien(
			Triple(alien3.x, alien3.y, alien3.z),
			Triple(0.05, 0.05, 0.05),
			Quad(0, 1, 0, 0)
		);
	}

	// -- Guns -- //
	if (!gun1.isGunPickedUp) {
		gun1.drawGun(
			Triple(gun1.x, gun1.y, gun1.z),
			Triple(0.03, 0.03, 0.03),
			Quad(0, 1, 0, 0)
		);
	}

	if (!gun2.isGunPickedUp) {
		gun2.drawGun(
			Triple(gun2.x, gun2.y, gun2.z),
			Triple(0.03, 0.03, 0.03),
			Quad(0, 1, 0, 0)
		);
	}

	if (!gun3.isGunPickedUp) {
		gun3.drawGun(
			Triple(gun3.x, gun3.y, gun3.z),
			Triple(0.03, 0.03, 0.03),
			Quad(0, 1, 0, 0)
		);
	}

	// -- Coins -- //
	for (Coin& coin : coins) {
		if (coin.isCoinPickedUp)
			continue;
		coin.drawCoin(
			Triple(coin.x, coin.y, coin.z),
			Triple(0.05, 0.05, 0.05),
			Quad(1, 0, 0, 90)
		);
	}

	// -- Tree -- //
	for (int i = 0; i < treesArraySize; i++) {
		OldTree& tree = trees[i];
		tree.drawOldTree(
			Triple(tree.treeX, tree.treeY, tree.treeZ),
			Triple(1, 1, 1),
			Quad(0, 1, 0, 0)
		);
	}

	// -- Rocks -- //
	for (int i = 0; i < rocksArraySize; i++) {
		Rock& rock = rocks[i];
		rock.drawRock(
			Triple(rock.rockX, rock.rockY, rock.rockZ),
			Triple(0.05, 0.05, 0.05),
			Quad(0, 1, 0, 0)
		);
	}
	glDisable(GL_TEXTURE_2D);

	// -- Health Bar -- //
	drawPlayerDetails(player.playerHealth, 25, WIDTH, HEIGHT);

	// -- Attack Power -- //
	writeText(player.playerAttackDamage, WIDTH, HEIGHT);

	// -- Score -- //
	writeScore(WIDTH, HEIGHT, score);

	// Sky box
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing
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
	glDisable(GL_TEXTURE_2D);
}

//=======================================================================
// Assets Loading Function
//=======================================================================
void Level1::LoadAssets()
{
	// -- Level 1 -- //
	for (int i = 0; i < aliensArraySize; i++) {
		Alien& alien = aliens[i];
		alien.loadAlien();
	}

	for (Gun& gun : guns) {
		gun.loadGun();
	}

	for (Coin& coin : coins) {
		coin.loadCoin();
	}

	for (OldTree& tree : trees) {
		tree.loadOldTree();
	}

	for (Rock& rock : rocks) {
		rock.loadRock();
	}

	player.loadPlayer();
	spaceship.loadSpaceship();

	// Loading texture files
	tex_ground.Load("Textures/ground.bmp");
	loadBMP(&tex, "Textures/blu-sky-3.bmp", true);
}
