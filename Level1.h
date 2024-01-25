#ifndef LEVEL1_H
#define LEVEL1_H

// Assuming the necessary OpenGL and other library headers are included
#pragma once
#include "Model_3DS.h"

#include <glut.h>
#include <irrKlang.h>
#include <math.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>

using namespace irrklang;


class Vector3f {
public:
    float x, y, z;

    Vector3f(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f);

    Vector3f operator+(Vector3f& v);
    Vector3f operator-(Vector3f& v);
    Vector3f operator*(float n);
    Vector3f operator/(float n);
    Vector3f unit();
    Vector3f cross(Vector3f v);
};

class Camera {
public:
    Vector3f eye, center, up;

    //Creates a viewing matrix that allows you to look somewhere other than the origin of your scene.
    Camera(float eyeX = 1.0f, float eyeY = 1.0f, float eyeZ = 1.0f, float centerX = 0.0f, float centerY = 0.0f, float centerZ = 0.0f, float upX = 0.0f, float upY = 1.0f, float upZ = 0.0f);

    void set(float eyeX = 0.0f, float eyeY = 0.0f, float eyeZ = 0.0f, float centerX = 0.0f, float centerY = 0.0f, float centerZ = 0.0f, float upX = 0.0f, float upY = 1.0f, float upZ = 0.0f);
    void moveX(float d);
    void moveY(float d);
    void moveZ(float d);
    void rotateX(float a);
    void rotateY(float a);
    void look();
};

// Triple class for 3D coordinates
class Triple {
public:
    double x, y, z;
    Triple();
    Triple(double x, double y, double z);
};

// Quad class for rotation data
class Quad {
public:
    double x, y, z, angle;
    Quad();
    Quad(double x, double y, double z, double angle);
};

class Player {
public:
    Model_3DS model_player;
    double playerX, playerY, playerZ;
    double playerRotationAngle;
    double playerHealth;
    double playerAttackDamage;
    int playerState; // 0: Default, 1: Attack, 2: Sheild
    double playerRange;
    int playerDirection;

    Player();
    Player(double playerX, double playerY, double playerZ, double playerRotationAngle, double playerHealth, double playerAttackDamage, int playerState, double playerRange, int playerDirection);

    void drawPlayer(Triple translatef, Triple scalef, Quad rotatef);
    void loadPlayer();
};

class Alien {
public:
    Model_3DS model_alien;
    double x, y, z;
    double alienHealth;
    double alienAttackDamage;
    double alienRange;

    Alien();
    Alien(double x, double y, double z, double alienHealth, double alienAttackDamage, double alienRange);

    void drawAlien(Triple translatef, Triple scalef, Quad rotatef);
    void loadAlien();
};

class Spaceship { // A target that upon collision transfer the player to the next level
public:
    Model_3DS model_spaceship;
    double spaceshipX, spaceshipY, spaceshipZ;
    double spaceshipRange;

    Spaceship();
    Spaceship(double spaceshipX, double spaceshipY, double spaceshipZ, double spaceshipRange);

    void drawSpaceship(Triple translatef, Triple scalef, Quad rotatef);
    void loadSpaceship();
};

class Gun {
public:
    Model_3DS model_gun;
    double x, y, z;
    bool isGunPickedUp;
    Gun();
    Gun(double x, double y, double z, bool isGunPicked);

    void drawGun(Triple translatef, Triple scalef, Quad rotatef);
    void loadGun();
};

class Spacecraft {
public:
    Model_3DS model_spacecraft;
    double spacecraftX, spacecraftY, spacecraftZ;
    Spacecraft();
    Spacecraft(double x, double y, double z);

    void drawSpacecraft(Triple translatef, Triple scalef, Quad rotatef);
    void loadSpacecraft();
};

class Rock {
public:
    Model_3DS model_rock;
    double rockX, rockY, rockZ;
    Rock();
    Rock(double rockX, double rockY, double rockZ);

    void drawRock(Triple translatef, Triple scalef, Quad rotatef);
    void loadRock();
};

class OldTree {
public:
    Model_3DS model_tree;
    double treeX, treeY, treeZ;
    OldTree();
    OldTree(double treeX, double treeY, double treeZ);

    void drawOldTree(Triple translatef, Triple scalef, Quad rotatef);
    void loadOldTree();
};

//class CrystalCave {
//public:
//    Model_3DS model_crystal;
//    double crystalX, crystalY, crystalZ;
//    CrystalCave();
//};

class Coin {
public:
    double x, y, z;
    double coinRange;
    bool isCoinPickedUp;
    Model_3DS model_coin;

    Coin();
    Coin(double x, double y, double z, double coinRange, bool isCoinPickedUp);

    void drawCoin(Triple translatef, Triple scalef, Quad rotatef);
    void loadCoin();
};


// Level 1 Class
class Level1 {
public:
    bool objectCollisionDetection(Triple playerPosition, double playerBoundaryRadius, Triple objectPosition, double objectBoundaryRadius);
    void drawBoundaries(double sphereRadius, Triple translatef, Triple scalef, Quad rotatef);
    void killOutOfBound(Alien* aliens, int size, double posX, double posZ, double negX, double negZ);
    //void fight(Player& player, Alien* aliens, int size, double posX, double posZ, double negX, double negZ);
    void fight(double posX, double posZ, double negX, double negZ);
    void validatePlayerPosition(Triple prevPosition, Player& player, Alien* aliens, int aliensArraySize);
    void checkPlayerWithinBoundaries(Triple prevPosition, Player& player, double posX, double posZ, double negX, double negZ);
    void collectWeapons(Gun* guns, Player& player, int size);
    void collectCoins(Coin* coins, Player& player, int size, double& score);
    void drawPlayerDetails(double playerHealth, double playerMaxHealth, int WIDTH, int HEIGHT);
    void renderBitmapString(float x, float y, void* font, const char* string);
    void writeText(float playerAttackPower, int WIDTH, int HEIGHT);
    void writeScore(int WIDTH, int HEIGHT, double& score);
    void writeLose(int WIDTH, int HEIGHT);
    void myDisplay(void);
    void Keyboard(unsigned char key, int x, int y);
    void myMouse(int button, int state, int x, int y);
    void myMotion(int x, int y);
    void Mouse(int x, int y);
    bool specialObjectCollisionDetection(Triple playerPosition, double playerBoundaryRadius, Triple objectPosition, double objectBoundaryX, double objectBoundaryZ);
    bool hitTarget(Spaceship& spacehip, Player& player);
    void InitLightSource1();
    void changePrepective();
    void InitMaterial();
    void myInit(void);
    void RenderGround();
    void LoadAssets();

public:
    // Game Configurations
#define GLUT_KEY_ESCAPE 27
#define DEG2RAD(a) (a * 0.0174532925)

    int WIDTH = 1280;
    int HEIGHT = 720;
    char key;
    double lightX, lightY, lightZ;

    // 3D Projection Options
    GLdouble fovy = 45.0;
    GLdouble aspectRatio = (GLdouble)WIDTH / (GLdouble)HEIGHT;
    GLdouble zNear = 0.1;
    GLdouble zFar = 200;

    // Camera
    int cameraZoom = 0;
    bool firstPrespective = false;
    bool thirdPrespective = true;

    // Model instances
    // Player
    Player player = Player(17, 0, 17, 0, 100, 1, 0, 0.5, 0);
    Camera camera = Camera(player.playerX + 3.2, 3, player.playerZ, player.playerX - 3, 1, player.playerZ, 0, 2, 0);


    // Score
    double score = 0;

    // Obstacles
    Alien aliens[3] = { Alien(10, 0, 10, 3, 5, 1), Alien(-10, 0, 10, 3, 5, 1), Alien(-15, 0, 15, 3, 5, 1) };
    Alien& alien1 = aliens[0];
    Alien& alien2 = aliens[1];
    Alien& alien3 = aliens[2];
    int aliensArraySize = (int)(sizeof(aliens) / sizeof(aliens[0]));

    // Collectables
    Gun guns[3] = { Gun(15, 1.5, 10, false), Gun(17, 1.5, 0, false), Gun(0, 1.5, 10, false) };
    Gun& gun1 = guns[0];
    Gun& gun2 = guns[1];
    Gun& gun3 = guns[2];
    int size2 = (int)(sizeof(guns) / sizeof(guns[0]));

    // Coins
    Coin coins[3] = { Coin(10, 1, 0, 0.0005, false), Coin(-10, 1, 5, 0.0005, false), Coin(-15, 1, 10, 0.0005, false) };
    int coinsArraySize = (int)(sizeof(coins) / sizeof(coins[0]));

    // Target
    Spaceship spaceship = Spaceship(9, 1, 5, 1);  //OldTree(-5 + 3.7, 1, 5 - 3.1)

    // Trees
    OldTree trees[4] = { OldTree(7, 0, 7), OldTree(-7, 0, -7), OldTree(5, 0, -5) };
    OldTree& tree1 = trees[0];
    OldTree& tree2 = trees[1];
    OldTree& tree3 = trees[2];
    int treesArraySize = (int)(sizeof(trees) / sizeof(trees[0]));

    // Rocks
    Rock rocks[3] = { Rock(1, 1, 0), Rock(-5, 1, -10), Rock(10, 1, -10) };
    int rocksArraySize = (int)(sizeof(rocks) / sizeof(rocks[0]));

    // Sound Engines
    ISoundEngine* background = createIrrKlangDevice();
    ISoundEngine* playerWalkSound = createIrrKlangDevice();
    ISoundEngine* playerAttackSound = createIrrKlangDevice();
    ISoundEngine* alienAttackSound = createIrrKlangDevice();
    ISoundEngine* playerPainSound = createIrrKlangDevice();
    ISoundEngine* coinPickupSound = createIrrKlangDevice();
    ISoundEngine* gunPickupSound = createIrrKlangDevice();
    ISoundEngine* spaceshipSound = createIrrKlangDevice();
    ISoundEngine* shieldSound = createIrrKlangDevice();

    bool isPlayerMoving = false;
    int remTime = 0, playerAttackRemTime = 0, alienAttackRemtime = 0, playerPainRemTime = 0;
    int spaceshipRemTime = 0;
    int gunRemTime = 0;
    int coinRemTime = 0;
    int val = 150;
    int shieldRemTime = 0;
    int lastMouseX = WIDTH / 2;
    int lastMouseY = HEIGHT / 2;
    bool finished = false;

    // Texture instances
    GLTexture tex_ground;
    GLuint tex;
};

#endif // LEVEL1_H