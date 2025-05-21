#pragma once
#include "fumo/fumo_c_definitions.h" // IWYU pragma: export
#include "fumo/fumo_data_structures.h" // IWYU pragma: export

/// fumo type_name implementation

#define TypeName(Type) #Type,
const char* all_type_names[] = {ALL_VARIANT_TYPES(TypeName) //
                                ALL_DATA_TYPES(TypeName)};
#undef TypeName

#define ___each_type_name_(Type)

static inline const char* ___type_name(int type_id) {
    return all_type_names[type_id];
}

static inline const char* ___variant_type_name(Variant variant) {
    return all_type_names[variant.type_id];
}

static inline const char* ___result_type_name(Result result) {
    return all_type_names[result.type_id];
}

#define type_name(_v)                                  \
    _Generic(typeof(_v),                               \
                Variant: ___variant_type_name,          \
                Result: ___result_type_name             \
                )(_v)
