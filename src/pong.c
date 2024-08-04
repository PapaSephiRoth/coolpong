#include "components.h"
#include "raylib.h"
#include <stdio.h>

// Screen values
static const int screen_width = 800;
static const int screen_height = 450;

// Paddle values
static const int players_offset = screen_width * 0.1;
static const int paddle_height = 60;
static const int paddle_width = 10;
static const int paddle_speed = 400;

typedef enum { PADDLE_RIGHT = 0, PADDLE_LEFT, PADDLE_COUNT } paddle_dir_e;
typedef struct {
  KeyboardKey UP;
  KeyboardKey DOWN;
} ControlScheme;

// TODO(SEAN) change control keys to be different for both
static const ControlScheme control_schemes[PADDLE_COUNT] = {
    [PADDLE_RIGHT] = {KEY_W, KEY_S}, [PADDLE_LEFT] = {KEY_UP, KEY_DOWN}};

void move_paddle(Paddle *paddle, ControlScheme const *cs, float time_delta);
void ball_wall_collision_handler(Ball *ball);

int main(void) {

  Paddle paddles[PADDLE_COUNT] = {
      [PADDLE_RIGHT] =
          paddle_create(paddle_width, paddle_height, players_offset,
                        (screen_height - paddle_height) / 2.0),

      [PADDLE_LEFT] =
          paddle_create(paddle_width, paddle_height,
                        screen_width - paddle_width - players_offset,
                        (screen_height - paddle_height) / 2.0),
  };

  Ball ball = ball_create(10, (float)screen_width / 2, (float)screen_height / 2,
                          200, -250);
  InitWindow(screen_width, screen_height, "Pong");
  SetTargetFPS(120);

  float time_delta;
  char FPS[8];

  while (!WindowShouldClose()) {
    time_delta = GetFrameTime();

    // TODO(Sean) handle potential error
    sprintf(FPS, "%d", GetFPS());

    for (int i = 0; i < PADDLE_COUNT; ++i) {
      move_paddle(&paddles[i], &control_schemes[i], time_delta);
    }

    ball_wall_collision_handler(&ball);
    update_position(&ball.pos, &ball.vel, time_delta);

    BeginDrawing();
    ClearBackground(BLACK);
    DrawText(FPS, 20, 20, 20, YELLOW);

    Paddle *pdl;
    for (int i = 0; i < PADDLE_COUNT; ++i) {
      pdl = &paddles[i];
      DrawRectangle(pdl->pos.x, pdl->pos.y, pdl->width, pdl->height, WHITE);
    }

    DrawCircle(ball.pos.x, ball.pos.y, ball.radius, WHITE);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}

void move_paddle(Paddle *paddle, ControlScheme const *cs, float time_delta) {

  static const Velocity UP = {.speed = paddle_speed,
                              .direction = (Vector2){0, -1}};
  static const Velocity DOWN = {.speed = paddle_speed,
                                .direction = (Vector2){0, 1}};
  if (IsKeyDown(cs->UP)) {
    update_position(&paddle->pos, &UP, time_delta);
  }
  if (IsKeyDown(cs->DOWN)) {
    update_position(&paddle->pos, &DOWN, time_delta);
  }
}

void ball_wall_collision_handler(Ball *ball) {
  if ((ball->pos.x + ball->radius) > screen_width) {
    ball->pos.x = screen_width - ball->radius;
    ball->vel.direction.x *= -1;
  } else if ((ball->pos.x - ball->radius) < 0) {
    ball->pos.x = ball->radius;
    ball->vel.direction.x *= -1;
  }

  if ((ball->pos.y + ball->radius) > screen_height) {
    ball->pos.y = screen_height - ball->radius;
    ball->vel.direction.y *= -1;
  } else if ((ball->pos.y - ball->radius) < 0) {
    ball->pos.y = ball->radius;
    ball->vel.direction.y *= -1;
  }
}
