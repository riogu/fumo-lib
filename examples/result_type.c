#include <stdio.h>
#include <math.h>
#include "fumo/fumo_data_structures.h"
#include "fumo/fumo_type_name.h"

Result divide(int a, int b) {
    if (b == 0) {
        char* error_message = "Division by zero";
        return (Result){
            .Err = (T_value){._char_ptr = error_message},
            .type_id = T_id_char_ptr,
            .was_err = 1
        };
    }

    int result = a / b;
    return (Result){
        .Ok = (T_value){._int = result},
        .type_id = T_id_int,
        .was_err = 0
    };
}

Result sqrt_positive(double x) {
    if (x < 0) {
        return (Result){
            .Err = (T_value){._char_ptr = "Cannot take square root of negative number"},
            .type_id = T_id_char_ptr,
            .was_err = 1
        };
    }

    double result = sqrt(x);
    return (Result){
        .Ok = (T_value){._double = result},
        .type_id = T_id_double,
        .was_err = 0
    };
}

int main() {
    Result div_result = divide(10, 2);

    if (!div_result.was_err) {
        printf("[success]: 10 / 2 = %d\n", div_result.Ok._int);
    } else {
        printf("[error]: %s\n", div_result.Err._char_ptr);
    }

    Result div_error = divide(5, 0);

    if (!div_error.was_err) {
        printf("[success]: 5 / 0 = %d\n", div_error.Ok._int);
    } else {
        printf("[error]: %s\n", div_error.Err._char_ptr);
    }

    Result div_result2 = divide(10, 2);
    if (div_result2.was_err) {
        printf("Failed at division step %s\n", div_result2.Err._char_ptr);
        return 1;
    }

    int div_value = div_result2.Ok._int;
    printf("Division result: %d\n", div_value);

    // Then sqrt
    Result sqrt_result = sqrt_positive(div_value);
    if (sqrt_result.was_err) {
        printf("Failed at square root step %s\n", sqrt_result.Err._char_ptr);
        return 1;
    }

    double final_result = sqrt_result.Ok._double;
    printf("Final result > sqrt(%d) = %.4f\n", div_value, final_result);
    return 0;
}
