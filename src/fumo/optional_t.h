
// clang-format off

#define optional_t(T) typedef struct { T value; _Bool nullopt_t;}

#define Some(_v) (optional_t) {.value = (typeof(_v)*)& _v}

#define None(T)

// #define dict() 1

// typedef struct dict {
// } dict;
