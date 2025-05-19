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
    return 0;
}
```
More detailed showcase of how you would use fumo$variant:
```c
#include "fumo_variant/fumo_variant.h"
#include "structs.h"
#include <stdio.h>

int main() {
    Rectangle rect = {.width = 123, .height = 1231};
    fumo$variant variant = fumo$variant(rect);

    fumo$is_same_t((Position) {}, variant) ? printf("true\n") : printf("false\n");
    // false
    fumo$is_same_t(rect, variant) ? printf("true\n") : printf("false\n");
    // true
    fumo$is_same_t((Shape) {}, rect) ? printf("true\n") : printf("false\n");
    // false

    auto result1 = fumo$get_if(Rectangle, variant) {

        printf("width before: %d \n", result1->width);
        result1->width = 213123;
        printf("there was a rectangle, width: %d\n", result1->width);
        printf("type_name: %s\n\n", fumo$variant_type_name(variant));

    } else {
        printf("didnt have a rectangle!\n");
    }

    Position pos = {.x = 69420};
    variant = fumo$variant(pos);

    auto result2 = fumo$get_if(Shape, variant) {
        // is never reached
        result2->shape_id = 213;

    } else {
        // fails to get the value, result2 is NULL
        printf("couldn't get shape from variant.\n");
        printf("type in variant: %s\n", fumo$variant_type_name(variant));
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
