#pragma once
#ifndef LEVEL2_H
#define LEVEL2_H

// Assuming the necessary OpenGL and other library headers are included
#pragma once
#include "Model_3DS.h"
#include <irrKlang.h>
#include <glut.h>
#include <math.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <Windows.h>

class Vector3f2 {
public:
    float x, y, z;

    Vector3f2(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f);

    Vector3f2 operator+(Vector3f2& v);
    Vector3f2 operator-(Vector3f2& v);
    Vector3f2 operator*(float n);
    Vector3f2 operator/(float n);
    Vector3f2 unit();
    Vector3f2 cross(Vector3f2 v);
};

class Camera2 {
public:
    Vector3f2 eye, center, up;

    //Creates a viewing matrix that allows you to look somewhere other than the origin of your scene.
    Camera2(float eyeX = 12.0f, float eyeY = 3.0f, float eyeZ = 12.0f, float centerX = -10.0f, float centerY = 0.0f, float centerZ = -10.0f, float upX = 0.0f, float upY = 1.0f, float upZ = 0.0f);

    void set(float eyeX = 0.0f, float eyeY = 0.0f, float eyeZ = 0.0f, float centerX = 0.0f, float centerY = 0.0f, float centerZ = 0.0f, float upX = 0.0f, float upY = 1.0f, float upZ = 0.0f);
    void moveX(float d);
    void moveY(float d);
    void moveZ(float d);
    void rotateX(float a);
    void rotateY(float a);
    void look();
};

// Triple class for 3D coordinates
class Triple2 {
public:
    double x, y, z;
    Triple2();
    Triple2(double x, double y, double z);
};

// Quad class for rotation data
class Quad2 {
public:
    double x, y, z, angle;
    Quad2();
    Quad2(double x, double y, double z, double angle);
};

class Player2 {
public:
    Model_3DS model_player;
    double playerX, playerY, playerZ;
    double playerRotationAngle;
    double playerHealth;
    double playerAttackDamage;
    int playerState; // 0: Default, 1: Attack, 2: Sheild
    double playerRange;
    int playerDirection;

    Player2();
    Player2(double playerX, double playerY, double playerZ, double playerRotationAngle, double playerHealth, double playerAttackDamage, int playerState, double playerRange, int playerDirection);

    void drawPlayer(Triple2 translatef, Triple2 scalef, Quad2 rotatef);
    void loadPlayer();
};

class Boss {
public:
    Model_3DS model_boss;
    double x, y, z;
    double bossHealth;
    double bossAttackDamage;
    double bossRange;

    Boss();
    Boss(double x, double y, double z, double alienHealth, double alienAttackDamage, double alienRange);

    void drawBoss(Triple2 translatef, Triple2 scalef, Quad2 rotatef);
    void loadBoss();
};


class Gun2 {
public:
    Model_3DS model_gun;
    double x, y, z;
    bool isGunPickedUp;
    Gun2();
    Gun2(double x, double y, double z, bool isGunPicked);

    void drawGun(Triple2 translatef, Triple2 scalef, Quad2 rotatef);
    void loadGun();
};

class Apple {
public:
    double x, y, z;
    double appleRange;
    bool isApplePickedUp;
    Model_3DS model_apple;

    Apple();
    Apple(double x, double y, double z, double appleRange, bool isApplePickedUp);

    void drawApple(Triple2 translatef, Triple2 scalef, Quad2 rotatef);
    void loadApple();
};

class Coin2 {
public:
    double x, y, z;
    double coinRange;
    bool isCoinPickedUp;
    Model_3DS model_coin;

    Coin2();
    Coin2(double x, double y, double z, double coinRange, bool isCoinPickedUp);

    void drawCoin(Triple2 translatef, Triple2 scalef, Quad2 rotatef);
    void loadCoin();
};

class Obstacle2 {
public:
    double x, y, z;
    Model_3DS model_obstacle;

    Obstacle2();
    Obstacle2(double x, double y, double z);

    void drawObstacle(Triple2 translatef, Triple2 scalef, Quad2 rotatef);
    void loadObstacle();
};


// Level 1 Class
class Level2 {
public:
    void drawWall();
    void drawPlayerDetails(double playerHealth);
    void drawBossHealthBar(float health); // done
    void renderBitmapString(float x, float y, void* font, const char* string);
    void writeText(float playerAttackPower, int WIDTH, int HEIGHT);
    void writeScore(float score);
    void myDisplay(void);
    void Keyboard(unsigned char key, int x, int y);
    void Mouse(int x, int y);
    void myMouse(int button, int state, int x, int y);
    void myMotion(int x, int y);
    void RenderGround();
    void playerAttack();
    float eucDistance(float x1, float x2, float y1, float y2);
    void checkAppleCollisions();
    void checkGunCollisions();
    void checkCoinCollisions();
    bool checkLegalMove(unsigned char key);
    void bossAttack();
    void LoadAssets();
    void changePrepective();
    bool couldBossAttack();
    float rotateBossWithMovement();
    void moveBoss();
    void InitLightSource2();
    void startUpdateGameVariables(double startScore, float startHealth, float startAttackPower);
    void writeWin();
    void writeLose();

public:
    // Game Configurations
#define GLUT_KEY_ESCAPE 27
#define DEG2RAD(a) (a * 0.0174532925)

    int WIDTH = 1280;
    int HEIGHT = 720;

    // 3D Projection Options
    GLdouble fovy = 45.0;
    GLdouble aspectRatio = (GLdouble)WIDTH / (GLdouble)HEIGHT;
    GLdouble zNear = 0.1;
    GLdouble zFar = 100;

    // Camera
    int cameraZoom = 0;
    bool firstPrespective = false;
    bool thirdPrespective = true;

    // Model instances
    // Player
    Player2 player = Player2(0, 0, 16, 0, 100, 1, 0, 1.5, 0);
    Camera2 camera = Camera2(player.playerX, 6, player.playerZ + 4, player.playerX, 1, player.playerZ - 8, 0, 2, 0);


    // Score
    double score = 0;

    // bossAttack
    int bossAttackTime = 3;

    // Boss
    Boss boss = Boss(0, 0, 0, 100, 20, 10);

    // Collectables
    Gun2 guns[3] = { Gun2(15, 0, 0, false), Gun2(-10, 0, 0, false), Gun2(0, 0, 10, false) };
    Gun2& gun1 = guns[0];
    Gun2& gun2 = guns[1];
    Gun2& gun3 = guns[2];
    int size2 = (int)(sizeof(guns) / sizeof(guns[0]));

    // Apples
    Apple apples[2] = { Apple(10, 1, 0, 0.1, false), Apple(-8, 1, 5, 0.1, false)};
    int appleArraySize = (int)(sizeof(apples) / sizeof(apples[0]));

    // coins
    Coin2 coins[2] = { Coin2(5, 1, 0, 0.05, false), Coin2(-5, 1, 0, 0.05, false)};
    int coinsArraySize = (int)(sizeof(coins) / sizeof(coins[0]));

    //Obstacle2 obstacles[1] = {Obstacle2(0, 0, 15)};

    // Texture instances
    GLTexture tex_ground;
    GLTexture tex_wall;
    GLTexture tex_ceiling;
    GLTexture tex_lava;
    GLuint tex;

    // mouse movement
    int lastMouseX = WIDTH / 2;
    int lastMouseY = HEIGHT / 2;

    // game finished and start
    bool isStarted = false;
    bool isFinished = false;
};

#endif // LEVEL1_H