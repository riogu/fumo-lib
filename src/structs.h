#pragma once

typedef struct Position {
    int x;
    int y;
} Position;

typedef struct Body {
    Position position;
    float radius;
} Body;

typedef struct Circle {
    float radius;
} Circle;

typedef struct Shape {
    int shape_id;
} Shape;

typedef struct Piece {
} Piece;

typedef struct Camera {
} Camera;

typedef struct Rectangle {
    int width;
    int height;
} Rectangle;

typedef struct Board {
} Board;
