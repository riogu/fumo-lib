#include "fumo_lib.h"

Result get_input();

int main() {
    match(get_input())({
        _Ok(int, var) printf("_Ok: %d.\n", *var);
        _Err(char*, errval) {
            // if scanf() fails, we go in here and get our string
            printf("error message: %s", *errval);
        }
    });
    return 0;
}
