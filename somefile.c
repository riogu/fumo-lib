// clang-format off
typedef struct Box2D {} Box2D;
typedef struct Ball2d {} Ball2D;

typedef enum T_id { T_id_Box2D, T_id_Ball2D } T_id;
typedef union T_value { Box2D _Box2D; Ball2D _Ball2D;} T_value;

typedef struct Shape2D {
    T_value value;
    T_id type_id;
} Shape2D;


#define ___each_type_id_(T)                     \
static inline const T_id ___type_id_##T(T t){   \
    return T_id_##T;                            \
}
// clang-format on

static inline const T_id ___type_id_Box2D(Box2D t) {
    return T_id_Box2D;
}

static inline const T_id ___type_id_Ball2D(Ball2D t) {
    return T_id_Ball2D;
}

#define get_type_id(var) (enum T_id)                             \
    _Generic(var,                                                \
             Ball2D: ___type_id_Ball2D,                          \
             Box2D: ___type_id_Box2D)(var)

#define make_Shape2D(var) (Shape2D) {       \
    .value = (union T_value) var,           \
    .type_id = get_type_id(var)             \
}

int main() {
    Box2D box;

    T_id box_id = get_type_id(box);
    Shape2D shape = make_Shape2D(box);

    /*
     expands to:
     
    T_id box_id = (enum T_id) _Generic(box,
        Ball2D: ___type_id_Ball2D,
        Box2D: ___type_id_Box2D)(box);

    Shape2D shape = (Shape2D) {.value = (union T_value)box,
                               .type_id = (enum T_id) _Generic(box,
                                   Ball2D: ___type_id_Ball2D,
                                   Box2D: ___type_id_Box2D)(box)};
     */
}

#define foo(...)_Generic(__VA_ARGS__,                       \
                        int: _Generic(__VA_ARGS__,          \
                                      int: __VA_ARGS__,     \
                                      default:0)+1,         \
                        void*:__VA_ARGS__)

typedef enum {
    Shape_Box2D,
    Shape_Ball2D,
} Shape2DType;

#define __type_shape_getter(T)                                     \
    static inline const Shape2DType __get_type_shape##T(T shape) { \
        return Shape_##T;                                          \
    }

__type_shape_getter(Box2D);
__type_shape_getter(Ball2D);

// clang-format off

#define ShapeEnum(shape) _Generic(shape,                            \
                                  Box2D  : __get_type_shapeBox2D,   \
                                  Ball2D : __get_type_shapeBall2D)(shape)

// clang-format on
