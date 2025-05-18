#pragma once
#include "impl_fumo_variant/fumo_get.h" // IWYU pragma: export
#include "impl_fumo_variant/variant_and_typenames.h" // IWYU pragma: export
#include <stdlib.h> // IWYU pragma : export

// Automatically frees a value at the end of scope.
#define autofree __attribute__((__cleanup__(autofree_impl)))

/* __cleanup__ gives void** not void* so can't pass free directly */
static inline void autofree_impl(void* p) {
    free(*((void**)p));
}
