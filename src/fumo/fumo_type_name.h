#include "fumo/fumo_c_definitions.h"
#include "fumo/fumo_data_structures.h"

/// fumo type_name for any variable implementation

#define TypeName(Type) #Type,
static const char* all_type_names[] = {ALL_VARIANT_TYPES(TypeName) //
                                       ALL_DATA_TYPES(TypeName)};
#undef TypeName

static inline const char* ___type_name(int type_id) {
    return all_type_names[type_id];
}

static inline const char* ___variant_type_name(Variant variant) {
    return all_type_names[variant.type_id];
}

static inline const char* ___result_type_name(Result result) {
    return all_type_names[result.type_id];
}

#define type_name(Var)                                  \
    _Generic(typeof(*(Var*)0),                          \
                _variant: __variant_type_name,          \
                _result: __result_type_name,            \
                default:)
