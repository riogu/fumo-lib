#include "fumo/optional_t.h"
#include "fumo/variant.h"
#include "structs.h"
#include <stdbool.h>
#include <stdio.h>

#define _else else

// void dict_add(dict d, char* key, int value) {
//     // snip
// }
//
// bool dict_has_key(dict d, char* key) {
//     // snip
// }
//
// optional_t dict_get(dict d, char* key) {
//     if (!dict_has_key(d, key)) return None();
//
//     return Some(d[key]);
// }

int main() {

    Rectangle rect = {.width = 12312};
    _variant var = _variant(rect); // making variant struct

    // match(var) {
    //     case(Shape) _Shape->shape_id = 123;
    //     case(Rectangle) {
    //         _Rectangle->height = 213123;
    //         _Rectangle->width = 123123;
    //     }
    //     _default printf("we dont get a value here");
    // }

    // printf("You just obtained: %d fumo", result);

    // let fumo_count = 0;

    get_if(Shape, var)->Some(value) {

        printf("You indeed have %d fumo", value);
        fumo_count = value;
        // result implictly gets fumo_count as the value;
        fumo_count;
    }
    _else {
        // result becomes None()
        printf("no fumo :(");
        fumo_count = 0;
    }

    return 0;
}

// #define Result(x) e
// #define Ok(x)
// #define Err(x)

typedef struct str {
} str;

typedef struct Result_int_str {
    int _Ok;
    str _Err;
} Result_int;

typedef struct Result_Position_str {
    Position _Ok;
    str _Err;
} Result_Position;

typedef struct Result {
    union _Result_value_t {
        Result_Position _Result_Position_int;
        Result_int _Result_int_str;
    } _value;
} Result;

#define _ 0
#define add_result_t(...)

add_result_t(int, str) add_result_t(str, Position)
    add_result_t(Rectangle, Position)

#define Ok(_v) (typeof(__func__)) {._Ok = _v};
#define Err(_v) (typeof(*(*__func__))) {._Err = _v};

// clang-format off
// #define Result(T, U) ({auto _____first___ =0 ; auto ____second____ = 0;}); Result

#define Result(T, U)  Result_##T##_##U


Result(int, str) get_input() {
    int n;
    if (scanf("%d", &n)) {
        return (typeof(*(get_input())0)){._Ok = 1} ;
    }
    return Err(n);
}

void func() {
    match(get_input()) {
        Ok(var) {
            printf("what happened", var);
            }
        Err(_) printf("what the hell %s", errval);
    }
}
