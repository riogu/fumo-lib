# fumo-lib
fumo-lib is a small, single header library that explores new C23 features to add compile-time type safety around C's unions and enums.
it provides a std::variant implementation and a result type implementation.
it also provides a match() and get_if() construct API to access the inner values of Result and Variant.

fumo-lib makes use of some macro techniques to get close to the kind of generic code you would write in modern languages like C++.
it is limited in its usecase but is very powerful, and cover many common usecases of generics.

## Goal
the goal of fumo-lib is to experiment around what kind of typesafety you can obtain with modern C features.

## Features
- [x] compile-time type safe unions (like std::variant in C++)
- [x] compile-time safe Result types (inspired by Rust's Result)
- [x] match() construct syntax to access contents of Result and Variant in a type safe way.
- [x] get_if() construct for type safe access to contents of Variant.
- [x] macro system that resembles generics from other languages (like C++) 
## Quick example
```c
Result get_input();
int main() {
    Rectangle rect = {.width = 123, .height = 1231};
    Variant var = Variant(rect);

    let inner_value = get_if(Shape, var) {
        inner_value->shape_id = 123123;
    } else {
        printf("failed, type: %s\n", type_name(var));
    }

    is_compatible_t((Position) {}, var) ? printf("true\n") : printf("false\n");

    match(get_input()) {
        _Ok(Position, somepos) print("_Ok: stored position.x as: ", somepos->x);
        _Err(char*, errval) print("error message: ", *errval);
    }

    match(var) {
        holds(Shape, var) var->shape_id = 213;

        holds(Rectangle, rect) {
            rect->height = 123123;
            rect->width = 123123;
        }
        _ { printf("unknown type.\n"); }
    }
}
```
## Usage 
> [!WARNING]
> requires C23 to compile with gcc or clang.
> 
> no extra flags required.

- download fumo_lib.h and the helper_macro directory.
> helper macros are separated for convenience.
> if you want to use fumo-lib as a single header dependency, simply copy both files into 
> where they are included in fumo_lib.h
- write your user made structs here in the user_types macro found in fumo_lib.h, in this format:
```c
#define user_types Position, Shape, Body, Rectangle, YourUserStruct, etc....
```

## Example main.c

All features added by fumo-lib.h are showcased here in this example:
```c

typedef struct Position {int x;int y;} Position;
typedef struct Shape {int shape_id;} Shape;
typedef struct Body {Position position;float radius;} Body;
typedef struct Rectangle {int width;int height;} Rectangle;
typedef struct Circle {float radius;} Circle;
typedef struct Piece {} Piece;
typedef struct Camera {} Camera;
typedef struct Board {} Board;
// NOTE: structs should be typedef'd. we want them in the global namespace for this lib.
// implementation can be changed to allow for using the struct keyword too.

// ----------------------------------------------------------------
// write your user made structs here in the macro, in this format
#define user_types Position, Shape, Body, Rectangle
// ----------------------------------------------------------------

#include "fumo_lib.h"

Result get_input();

int main() {
    // NOTE: all accesses to contents of Variant or Result
    // must go through the match() or get_if() methods to be safe.
    // the user isn't meant to ever directly access the members of these classes.

    int x = 123;
    print("this is x: ", x); // printf helpful utility

    Rectangle rect = {.width = 123, .height = 1231};
    Variant var = Variant(rect); // variant takes any registered type

    let inner_value = get_if(Shape, var) {
        // only enters this scope if we held a Shape type
        // the type is checked at compile time and store in inner_value
        inner_value->shape_id = 123123;
    }
    else {
        // default scope for failure
        // inner_value is set to NULL if Shape was not inside the variant.
        printf("failed, type: %s\n", type_name(var));
    }

    // type comparison between any primitive data type or user defined struct
    // and also adds support for variant/result types against any type
    is_compatible_t((Position) {}, var) ? printf("true\n") : printf("false\n");

    Shape s = {.shape_id = 123123};
    Variant var1 = Variant(s);

    // match case picks case based on the held type of the variant
    // you can only make a case label if the type is registered.
    // failing to do so is a compile time error.
    // all type checking is done at compile time
    match(var) {
        holds(Shape, var) var->shape_id = 213;
        holds(Rectangle, rect) {
            // user specifies the name of the variable returned by the match
            // the variable is always a *pointer* to the variable stored in
            // the variant struct
            rect->height = 123; // code will go here since its a Rectangle type
        }
        holds(Position, pos) {
            // all variables only exist on each label scope.
            // that means you can only use "pos" inside of this label
            // (to guarantee more type safety)
            pos->x = 123;
            printf("%d sucessfully updated pos.\n", pos->x);
            pos->y = 123;
            printf("%d sucessfully updated pos.\n", pos->y);
        }
        _ {
            printf("unknown type.\n");
            // this is the default holds label.
            // triggered if none of the types the user added was valid
        }
    }

    // match also supports Result type
    // if the user doesnt specify the types they gave the Result they returned,
    // then the match wont trigger  _Ok() or _Err().
    // (warnings can be added if necessary by changing the implementation).
    match(get_input()) {

        _Ok(Position, somepos) printf("_Ok: stored position.x as: %d.\n", somepos->x);

        _Err(char*, errval) {
            // if scanf() fails, we go in here and get our string
            printf("error message: %s", *errval);
        }
    }

    match(var) {
        holds(int, someint) {
            (*someint)++;

            // you can indent as many match statements as you want
            match(var1) {
                holds(char*, str) {
                    // continue indenting....
                    printf("had a string %s", *str);
                }
                _ {} // you can do nothing on default
            }
        }

        holds(Position**, pos_ptr_ptr) {
            // double pointers are automatically declared for you
            // when you register a user type
            // (more than this needs implementation changes)
            // gets a Position***
            printf("position's x: %d", (*(*pos_ptr_ptr))->x);
        }
        _  printf("had nothing."); 
    }

    return 0;
}

Result get_input() {
    int n = 0;
    
    Position pos = {.x = 213, .y = 21312};

    let result = Ok(&pos); // valid code, stores Position*
    // can take any user type or standard type
    
    printf("please input a value for position.x:\n");
    if (scanf("%d", &n)) {
        pos.x = n;
        // Ok type, stores a Position
        return Ok(pos);
    }
    // Err type, stores a char*
    return Err("scanf failed. didn't recieve a number.\n");
}

```
compiling the main.c example.
Output:
```
╰─ ❯❯ gcc main.c -o a && ./a
this is x: 123
failed, type: Rectangle
false
please input a value for position.x:
ads
error message: scanf failed. didnt recieve a number.
had nothing.

╰─ ❯❯ gcc main.c -o a && ./a
this is x: 123
failed, type: Rectangle
false
please input a value for position.x:
213123
_Ok: stored position.x as: 213123.
had nothing.
```
