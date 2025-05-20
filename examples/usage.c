#include <stdio.h>
#include "fumo/fumo_data_structures.h"
#include "fumo/fumo_type_name.h"

int main() {
	// Primitive type
	int num = 42;
	float pi = 3.14159f;
	char* message = "Hello, variants!";

	Variant int_var = Variant(num);
	Variant float_var = Variant(pi);
	Variant str_var = Variant(message);

	// Custom type
	Position pos = {.x = 10, .y = 20};
	Rectangle rect = {.width = 30, .height = 40};

	Variant pos_var = Variant(pos);
	Variant rect_var = Variant(rect);

	// Get type info
	printf("int_var contains: %s\n", ___variant_type_name(int_var));
	printf("float_var contains: %s\n", ___variant_type_name(float_var));
	printf("str_var contains: %s\n", ___variant_type_name(str_var));
	printf("pos_var contains: %s\n", ___variant_type_name(pos_var));
	printf("rect_var contains: %s\n", ___variant_type_name(rect_var));

	// Accessing and modifying values
	{
		match(int_var) {
			case(int) {
				printf("value: %d\n", *_int);
				*_int *= 2;
				printf("modified value: %d\n", *_int);
			}
			_default printf("Not an int\n");
		}
	}

	{
		match(pos_var) {
			case(Position) {
				printf("before: (%d, %d)\n", _Position->x, _Position->y);
				_Position->x += 5;
				_Position->y += 10;
				printf("after: (%d, %d)\n", _Position->x, _Position->y);
			}
			_default printf("not position\n");
		}
	}

	// Type checking
	if (is_same_t(pos, pos_var)) {
		printf("pos_var contains a Position\n");
	}

	if (!is_same_t(rect, pos_var)) {
		printf("pos_var does not contain a Rectangle\n");
	}

	return 0;
}
