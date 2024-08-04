#include "components.h"
#include <raymath.h>

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
