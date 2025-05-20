#include <stdio.h>
#include <math.h>
#include "fumo/fumo_data_structures.h"
#include "fumo/fumo_type_name.h"

double calculate_value(Variant variant) {
    double result = 0.0;
    {
        match(variant) {
            case(int) {
                result = (*_int) * (*_int);
            }
            case(float) {
                result = sin(*_float);
            }
            case(Rectangle) {
                result = _Rectangle->width * _Rectangle->height;
            }
            case(Position) {
                result = sqrt(_Position->x * _Position->x + _Position->y * _Position->y);
            }
            _default {
                printf("unsupported type <%s>\n", ___variant_type_name(variant));
                result = -1.0;
            }
        }
    }

    return result;
}

// Function demonstrating get_if for safe type access
void process_geometry(Variant shape_var) {
    printf("Processing geometry of type: %s\n", ___variant_type_name(shape_var));

    // Try to access as Rectangle
    auto rect = get_if(Rectangle, shape_var) {
        printf("found a rectangle: %d x %d\n", rect->width, rect->height);
        printf("area: %d square units\n", rect->width * rect->height);

        rect->width *= 2;
        rect->height *= 2;
        printf("after resizing: %d x %d\n", rect->width, rect->height);
    }
    else {
        // Try to access as Shape
        auto shape = get_if(Shape, shape_var) {
            printf("found a generic shape with ID [%d]\n", shape->shape_id);
            shape->shape_id += 100;
            printf("updated shape ID [%d]\n", shape->shape_id);
        }
        else {
            printf("Can't process.\n");
        }
    }
}

int main() {
    // Create structs first
    Rectangle rect = {.width = 10, .height = 20};
    Position pos = {.x = 30, .y = 40};
    Shape shape = {.shape_id = 5};

    // Create different variants
    Variant variants[5] = {
        Variant(42),
        Variant(3.14159f),
        Variant(rect),
        Variant(pos),
        Variant(shape)
    };

    for (int i = 0; i < 5; i++) {
        printf("variant of [%d] <%s>: value = %f\n",
               i,
               ___variant_type_name(variants[i]),
               calculate_value(variants[i]));
    }

    printf("\n---\n");
    process_geometry(variants[2]);  // Rect
    process_geometry(variants[4]);  // Shape
    process_geometry(variants[0]);  // int (unknown)

    return 0;
}
