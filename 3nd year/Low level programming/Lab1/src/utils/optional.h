#ifndef _OPTIONAL_H_
#define _OPTIONAL_H_

#include <stdint.h>
#include <stdbool.h>

/* Макрос для определения структуры "optional" opt_T, где T - оборачиваемый тип данных, и двух функций:
 * not_present_T - создаёт opt_T с isPresent = false
 * wrap_T - оборачивает значение в opt_T, isPresent = true */
#define declOptional(T) typedef struct {\
    bool isPresent;                     \
    T value;                            \
} opt_##T;                              \
opt_##T not_present_##T();              \
opt_##T wrap_##T(T value);

declOptional(uint8_t)
declOptional(int64_t)
declOptional(uint64_t)

#endif