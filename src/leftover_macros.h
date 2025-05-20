
// clang-format off

#define optional_t(T) typedef struct { T value; _Bool nullopt_t;}

#define Some(_v) (optional_t) {.value = (typeof(_v)*)& _v}

#define None(T)

// #define dict() 1

// typedef struct dict {
// } dict;


#define CONCAT_(left, counter) left##counter
#define CONCAT(left, counter) CONCAT_(left, counter)
#define ___unique_name_(left) CONCAT(left, __COUNTER__)

// clang-format off
#define CONCAT_2(left1, left, counter) #left1"_"#left"_"#counter
#define CONCAT2(left1, left, counter) CONCAT_2(left1, left, counter)
#define ___unique_name2_(left1, left) CONCAT2(left1, left, __COUNTER__)

#define CONCAT_3(left, counter) #left#counter
#define CONCAT3(left, counter) CONCAT_3(left, counter)
#define ___unique_name_3(left) CONCAT3(left, BOOST_PP_COUNTER)

#define MAC_IMPL(A, B, EXP_COUNTER) \
    static const int CONCAT3(A, EXP_COUNTER) CONCAT3(B, __COUNTER__)

#define MAC(A, B) MAC_IMPL(A, B, __COUNTER__)

// __attribute__((alias( ___unique_name2_(T, U) ))) Result_##T##_##U ___unique_name_(____r_)() ;
