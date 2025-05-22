#include "fumo/fumo_data_structures.h"
#include "fumo/fumo_type_name.h"

Result divide(int a, int b) {
	if (b == 0) return Err("division by zero");
	int result = a / b;
	return Ok(result);
}

Result get_number() {
	int n;
	printf("enter number: ");
	if (scanf("%d", &n)) {
		return Ok(n);
	}
	return Err("invalid input");
}

int main() {
	match(get_number())({
		_Ok(int, a) {
			match(get_number())({
				_Ok(int, b) {
					match(divide(*a, *b))({
						_Ok(int, result) printf("[success]: %d\n", *result);
						_Err(char_ptr, err) printf("[error]: %s\n", *err);
					});
				}
				_Err(char_ptr, err) printf("second number error");
			});
		}
		_Err(char_ptr, err) printf("first number error");
	});

	return 0;
}
