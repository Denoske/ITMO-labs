#ifndef EMPTY_GENERATOR_H
#define GENERATOR_H
#include "../interface/signatures.h"
#include "../filetools/basic_file_manager.h"
#include <stdlib.h>
#include "../interface/configuration.h"
#include "../filetools/big_data_tools.h"

/**
 * Генерирует пустой заголовок для файла
 * @param pattern шаблон вершин
 * @param types типы для шаблона
 * @param pattern_size размер массива шаблона
 * @param key_sizes длины строк шаблона
 * @param header контейнер для заголовка
 */
void generate_empty_tree_header(char** pattern, uint32_t* types, size_t pattern_size, size_t* key_sizes, struct tree_header* header);

#endif