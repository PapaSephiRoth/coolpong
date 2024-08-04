#include "components.h"
#include "raylib.h"

void move_paddle(Paddle *paddle, float time_delta);

// Screen values
static const int screen_width = 800;
static const int screen_height = 450;

// Paddle values
static const int players_offset = screen_width * 0.1;
static const int paddle_height = 60;
static const int paddle_width = 10;
static const int paddle_speed = 100;

typedef enum { PADDLE_RIGHT = 0, PADDLE_LEFT, PADDLE_COUNT } paddle_dir_e;
typedef struct {
  KeyboardKey UP;
  KeyboardKey DOWN;
} ControlScheme;

// TODO(SEAN) change control keys to be different for both
static const ControlScheme control_schemes[PADDLE_COUNT] = {
    [PADDLE_RIGHT] = {KEY_W, KEY_S}, [PADDLE_LEFT] = {KEY_W, KEY_S}};

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
                          50, -50);
  InitWindow(screen_width, screen_height, "Pong");
  SetTargetFPS(120);

  float time_delta;
  
  while (!WindowShouldClose()) {
    time_delta = GetFrameTime();

    // MOVE PADDLES
    for (int i = 0; i < PADDLE_COUNT; ++i) {
      move_paddle(&paddles[i], time_delta);
    }

    // MOVE BALL
    update_position(&ball.pos, &ball.vel, time_delta);

    BeginDrawing();
    ClearBackground(BLACK);

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

void move_paddle(Paddle *paddle, float time_delta) {

  static const Velocity UP = {.speed = paddle_speed,
                              .direction = (Vector2){0, -1}};
  static const Velocity DOWN = {.speed = paddle_speed,
                                .direction = (Vector2){0, 1}};

  for (int i = 0; i < PADDLE_COUNT; ++i) {
    if (IsKeyDown(control_schemes[i].UP)) {
      update_position(&paddle->pos, &UP, time_delta);
    }

    if (IsKeyDown(control_schemes[i].DOWN)) {
      update_position(&paddle->pos, &DOWN, time_delta);
    }
  }
}
