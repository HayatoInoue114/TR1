#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <Novice.h>
#include<time.h>
#include<Vector2.h>


float Clamp(float number, float min, float max);

int GetRandom(int min, int max);

float GetRandom(float min, float max);

float Degree2Radian(float degree);

Vector2 PolarToVector2(float theta, float radius);

int intEasingMove(long int start, long int end, float easingVolume);

unsigned int ColorEasingMove(unsigned int statColor, unsigned int endColor, float easingVolume);