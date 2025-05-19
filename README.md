# How to use fumo_variant

1- copy the file `fumo_variant.c`.

2- to run the given example main function run:

    `gcc fumo_variant.c && ./a.out`

...thats it!
to use it yourself, simply copy the macros before main, and replace the example structs i provided with your own structs.

# Example of how the implementation works:
Simple usage:
```c
int main() {
    Position pos = {.x = 69420};
    _variant variant = _variant(pos);

    auto result2 = get_if(Shape, variant) {
        // is never reached
        result2->shape_id = 213;
    }
    else {
        // fails to get the value, result2 is NULL
        printf("couldn't get shape from variant.\n");
        printf("type in variant: %s\n", variant_type_name(variant));
    }

    Shape shape = {.shape_id = 13};
    _variant var = _variant(shape); // making variant struct

    // variables are only avaible inside the case label
    match(var) {
        case(Shape) _Shape->shape_id = 123; // goes here
        case(Rectangle) //etc...
        _default printf("we dont get a value here");
    }

    return 0;
}
```
More detailed showcase of how you would use fumo$variant:
```c
#include "fumo_variant/fumo_variant.h"
#include "structs.h"
#include <stdio.h>
typedef struct NewStruct {} NewStruct;

int main() {
    Rectangle rect = {.width = 123, .height = 1231};
    _variant variant = _variant(rect);

    
    Shape shape = {.shape_id = 13};
    _variant var = _variant(shape); // making variant struct

    // variables are only avaible inside the case label
    match(var) {
        case(Shape) _Shape->shape_id = 123; // goes here
        case(Rectangle) {
            _Rectangle->height = 222;
        }
        case (Position) //...etc (add more code)
        _default printf("we dont get a value here");
    }



    is_same_t((Position) {}, variant) ? printf("true\n") : printf("false\n");
    is_same_t(rect, variant) ? printf("true\n") : printf("false\n");
    is_same_t((NewStruct) {}, rect) ? printf("true\n") : printf("false\n");

    let result1 = get_if(Rectangle, variant) {

        printf("width before: %d \n", result1->width);
        result1->width = 213123;
        printf("there was a rectangle, width: %d\n", result1->width);
        printf("type_name: %s\n\n", variant_type_name(variant));
    }
    else {
        printf("didnt have a rectangle!\n");
    }

    Position pos = {.x = 69420};
    variant = _variant(pos);

    auto result2 = get_if(Shape, variant) {
        // is never reached
        result2->shape_id = 213;
    }
    else {
        // fails to get the value, result2 is NULL
        printf("couldn't get shape from variant.\n");
        printf("type in variant: %s\n", variant_type_name(variant));
    }

    return 0;
}


```
Output:
```
false
true
false
width before: 123 
there was a rectangle, width: 213123
type_name: Rectangle

couldn't get shape from variant.
type in variant: Position
```
