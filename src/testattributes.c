#include <stdio.h>

// clang-format off

typedef struct Result_int_float {
    int _Ok;
    float _Err;
} Result_int_float;

void foo(void) {
    printf("%s\n", __FUNCTION__);
}

void bar(void) __attribute__((alias("foo")));

void gazonk(void) {

    bar(); // calls foo
}

int oldname2 = 5;

static int newname __attribute__((alias("oldname" "2")));

#define CONCAT_(left, counter) left##counter
#define CONCAT(left, counter) CONCAT_(left, counter)
#define ___unique_name_(left) CONCAT(left, __COUNTER__)

#define asstr(x) (const char*) x
#define Result(T, U) \
typedef Result_##T##_##U ___unique_name_(____r_);
// static int newname __attribute__((alias(__FILE__)));

// #define pr_fmt(fmt) "%s"mt"",  __func__
// #define pr_debug(fmt, ...) printf(pr_fmt(fmt), ##__VA_ARGS__)

// Result_##T##_##U
int main() {


    printf("Value of new name is :%d\n", newname);
    return 0;
}
