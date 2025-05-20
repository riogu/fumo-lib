#include <boost/preprocessor.hpp>
#include <stdbool.h>
#include <stdio.h>

#include "fumo/result_t.h"

#define _else else

Result get_input() {

    int n = 10;
    if (scanf("%d", &n)) {
        return Ok(n);
    }
    return Err((Position) {.x = 213});
}

void func() {}

int main() {

    // match(get_input()) {
    //     _Ok(var) {
    //         printf("what happened", var);
    //     }
    //     _Err(errval) {
    //         printf("what the hell %s", errval);
    //     }
    // }
    Result result = get_input();

    return 0;
}
