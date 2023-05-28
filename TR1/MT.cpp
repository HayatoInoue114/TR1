#include "MT.h"

float Clamp(float number, float min, float max) {
	if (min > number) {
		return min;
	}
	else if (max < number) {
		return max;
	}
	else {
		return number;
	}
}


int GetRandom(int min, int max) {
	static int flag;

	if (flag == 0) {
		srand((unsigned int)time(NULL));
		flag = 1;
	}

	return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}

float GetRandom(float min, float max) {
	static int flag;

	if (flag == 0) {
		srand((float)time(NULL));
		flag = 1;
	}

	return min + (float)(rand() * (max - min + 1.0f) / (1.0f + RAND_MAX));
}

float Degree2Radian(float degree) {
	return (degree)*M_PI / 180;
}

Vector2 PolarToVector2(float theta, float radius) {
	return Vector2{ ((float)cos(theta) * radius), ((float)sin(theta) * radius) };
}

int intEasingMove(long int start, long int end, float easingVolume) {
	return ((start)+(((end)-(start)) * (easingVolume)));
}

unsigned int ColorEasingMove(unsigned int statColor, unsigned int endColor, float easingVolume) {

	unsigned int redColor = Clamp(intEasingMove((((statColor & 0xFF000000) >> (4 * 6)) & 0xFF), (((endColor & 0xFF000000) >> (4 * 6)) & 0xFF), easingVolume), 0x00, 0xFF);
	unsigned int greenColor = Clamp(intEasingMove((((statColor & 0x00FF0000) >> (4 * 4)) & 0xFF), (((endColor & 0x00FF0000) >> (4 * 4)) & 0xFF), easingVolume), 0x00, 0xFF);
	unsigned int blueColor = Clamp(intEasingMove((((statColor & 0x0000FF00) >> (4 * 2)) & 0xFF), (((endColor & 0x0000FF00) >> (4 * 2)) & 0xFF), easingVolume), 0x00, 0xFF);

	unsigned int alphaColor = Clamp(intEasingMove((statColor & 0x000000FF), (endColor & 0x000000FF), easingVolume), 0x00, 0xFF);

	return (redColor << (4 * 6)) + (greenColor << (4 * 4)) + (blueColor << (4 * 2)) + (alphaColor);

}
