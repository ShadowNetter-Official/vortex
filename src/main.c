#include <stdio.h>
#include "cs50.h"
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


typedef struct
{
	int width;
	int height;
	int fps;
	int count;
	double cx;
	double cy;
	double dt;
}
Config;

typedef struct
{
	double x;
	double y;
	double vx;
	double vy;
}
Object;


Config config();
void clear(int height, int width, int space[height][width]);
void init(int len, Object objects[len], int height, int width);
void calc(double cx, double cy, int height, int width, int space[height][width], int len, Object objects[len], double dt);
void draw(int height, int width, int space[height][width]);


int main(void)
{
	Config cfg = config();
	int width = cfg.width;
	int height = cfg.height;
	int fps = cfg.fps;
	Object objects[cfg.count];
	init(cfg.count, objects, height, width);
	int space[height][width];
	clear(height, width, space);
	int delay = (int)(1.0 / fps * 1000000);

	printf("\033[2J\033[1;1H");
	printf("\033[?25l");
	while (true)
	{
		printf("\033[H");
		calc(cfg.cx, cfg.cy, height, width, space, cfg.count, objects, cfg.dt);
		draw(height, width, space);
		usleep(delay);
	}
	return 0;
}

Config config()
{
	int fps = get_int("FPS: ");
	double dt = get_double("Delta Time: ");
	int width = get_int("Width: ");
	int height = get_int("Height: ");
	int count = get_int("Object Count: ");
	int cx = get_int("Center x: ");
	int cy = get_int("Center y: ");
	Config cfg;
	cfg.fps = fps;
	cfg.width = width;
	cfg.height = height;
	cfg.cx = cx;
	cfg.cy = cy;
	cfg.count = count;
	cfg.dt = dt;
	return cfg;
}

void clear(int height, int width, int space[height][width])
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			space[y][x] = 0;
		}
	}
}

void init(int len, Object objects[len], int height, int width)
{
	srand(time(NULL));
	int min = 1;
	int maxx = width - 2;
	int maxy = height - 2;
	for (int i = 0; i < len; i++)
	{
		int randx = min + rand() % (maxx - min + 1);
		int randy = min + rand() % (maxy - min + 1);
		objects[i].x = randx;
		objects[i].y = randy;
		objects[i].vx = 1;
		objects[i].vy = 0.5;
	}
}

void calc(double cx, double cy, int height, int width, int space[height][width], int len, Object objects[len], double dt)
{
	double pull = dt;
	clear(height, width, space);
	int speed = 1;
	int count = 0;
	double tolerance = 0.5;
	for (int i = 0; i < len; i++)
	{
		if (fabs(objects[i].x - cx) < tolerance && fabs(objects[i].y - cy) < tolerance)
		{
			count++;
		}
	}
	if (count == len)
	{
		init(len, objects, height, width);
	}
	for (int obj = 0; obj < len; obj++)
	{

		objects[obj].vx = (speed * (-1)) * (objects[obj].y - cy) - pull * (objects[obj].x - cx);
		objects[obj].vy =  speed * (objects[obj].x - cx) - pull * (objects[obj].y - cy);
		objects[obj].x += objects[obj].vx * dt;
		objects[obj].y += objects[obj].vy * dt;

		if (objects[obj].x < 0) objects[obj].x += width;
		if (objects[obj].x >= width) objects[obj].x -= width;
		if (objects[obj].y < 0) objects[obj].y += height;
		if (objects[obj].y >= height) objects[obj].y -= height;

		space[(int)round(objects[obj].y)][(int)round(objects[obj].x)] = 1;
	}
}

void draw(int height, int width, int space[height][width])
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (x == 0)
			{
				printf("▓");
			}
			else if (x == (width - 1))
			{
				printf("▓");
			}
			else if (y == 0)
			{
				printf("▓");
			}
			else if (y == (height - 1))
			{
				printf("▓");
			}
			else if (space[y][x] == 0)
			{
				printf(" ");
			}
			else
			{
				printf("");
			}
		}
		printf("\n");
	}
}

