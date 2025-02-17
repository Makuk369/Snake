#pragma once

struct Vector2
{
    float x;
    float y;

    Vector2(float x = 0, float y = 0);
};

// Vector2 with rotation
struct Vector2Rot
{
    float x;
    float y;
    float rotarion;

    Vector2Rot(float x = 0, float y = 0, float rotation = 0);
};

