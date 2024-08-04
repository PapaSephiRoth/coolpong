#pragma once
#include "raylib.h"

typedef struct {
  float x;
  float y;
} Position;

typedef struct {
  float speed;
  Vector2 direction;
} Velocity;

typedef struct {
  int width;
  int height;
  Position pos;
} Paddle;

typedef struct {
  int radius;
  Position pos;
  Velocity vel;
}  Ball;

Paddle paddle_create(int width, int height, float x, float y);
Ball ball_create(int radius, float x, float y, float dx, float dy);

void update_position(Position* pos, Velocity const* vel, float time_delta);
