#include "components.h"
#include <raymath.h>
#include <stdio.h>

void update_position(Position* p, Velocity const* v, float time_delta) {
 p->x += v->speed * v->direction.x * time_delta;
 p->y += v->speed * v->direction.y * time_delta;
}

Paddle paddle_create(int width, int height, float x, float y) {
  return (Paddle){
    .width=width,
    .height=height,
    {
      .x=x,
      .y=y
    }
  };
}

Ball ball_create(int radius, float x, float y, float dx, float dy) {
  return (Ball){
    radius,
    {
      .x=x,
      .y=y
    },
    {
      .speed=Vector2Length((Vector2){dx, dy}),
      .direction=Vector2Normalize((Vector2){dx, dy})
    }
  };
}

typedef enum {
  NONE = 0,
  LEFT,
  RIGHT,
  UP,
  DOWN,
  COLLISION_DIRS
} Direction ;

typedef struct {
  Direction dir;

} BallCollData;


#define IN_RANGE(check_point, point, length_from_point) ((check_point >= point) && (check_point <= point+length_from_point))
// returns delta for ball X
float ball_paddle_collision(Ball const* ball, Paddle const* paddle) {
  float ball_left = ball->pos.x - ball->radius;
  if(
    IN_RANGE(ball_left, paddle->pos.x, paddle->width) &&
    IN_RANGE(ball->pos.y, paddle->pos.y, paddle->height)
    ) {
    return paddle->pos.x+paddle->width+1+ball->radius;
  }
  
  float ball_right = ball->pos.x + ball->radius;
  if(IN_RANGE(ball_right, paddle->pos.x, paddle->width) &&
    IN_RANGE(ball->pos.y, paddle->pos.y, paddle->height)
  ) {
    printf("iuo");
    return paddle->pos.x-(1+ball->radius);
  }

  return 0;
}
