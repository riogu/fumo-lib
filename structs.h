#pragma once

typedef struct Position {
    int x;
    int y;
} Position;

typedef struct Circle {
    float radius;
} Circle;

typedef struct Shape {
    Circle circle;
} Shape;

typedef struct Body {
    Position position;
    float radius;
} Body;

typedef struct Piece {
} Piece;

typedef struct Camera {
} Camera;

typedef struct Rectangle {
    int epic;
} Rectangle;

typedef struct Board {
} Board;
