// ----------------------------------------------------------------
// example structs for testing, unnecessary for usage
// structs should be included before the macros.
typedef struct Position {int x;int y;} Position;
typedef struct Shape {int shape_id;} Shape;
typedef struct Body {Position position;float radius;} Body;
typedef struct Rectangle {int width;int height;} Rectangle;
typedef struct Circle {float radius;} Circle;
typedef struct Piece {} Piece;
typedef struct Camera {} Camera;
typedef struct Board {} Board;

// ----------------------------------------------------------------
// write your user made structs here in the macro, in this format
#define user_types Position, Shape, Body, Rectangle
// ----------------------------------------------------------------

// NOTE: structs should be typedef'd. we want them in the global namespace for this lib.
// implementation can be changed to allow for using the struct keyword too.

