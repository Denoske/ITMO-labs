#include "optional.h"

#define defOptional(T) opt_##T not_present_##T() { \
    return (opt_##T) { false, 0 };                  \
}                                                   \
opt_##T wrap_##T(T value) {                         \
    return (opt_##T) { true, value };               \
}

defOptional(uint8_t)
defOptional(int64_t)
defOptional(uint64_t)