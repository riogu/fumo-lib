Example of how the implementation works:
```c
#include "fumo_variant/fumo_variant.h"
#include "structs.h"
#include <stdio.h>

int main() {
    Rectangle rect = {.width = 123, .height = 1231};
    fumo$variant variant = fumo$variant(rect);

    auto result1 = fumo$get(Rectangle, variant) {

        printf("width before: %d \n", result1->width);
        result1->width = 213123;
        printf("there was a rectangle, width: %d\n", result1->width);
        printf("type_name: %s\n\n", fumo$variant_type_name(variant));
    } else { printf("didnt have a rectangle!\n"); }

    Position pos = {.x = 69420};
    variant = fumo$variant(pos);

    auto result2 = fumo$get(Shape, variant) {
        // is never reached
        result2->somevar = 213;
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
width before: 123 
there was a rectangle, width: 213123
type_name: Rectangle

couldn't get shape from variant.
type in variant: Position
```
