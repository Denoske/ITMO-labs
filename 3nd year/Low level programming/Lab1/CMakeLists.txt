cmake_minimum_required (VERSION 3.8)

project ("llp_lab1")

# add_executable (llp_lab1 "src/zgdb/format.c" "src/zgdb/format.h" "src/zgdb/document.h" "src/zgdb/document.c" "src/zgdb/list.c" "src/zgdb/list.h" "src/utils/optional.h" "src/utils/optional.c" "src/zgdb/document_public.h" "src/zgdb/format_public.h" "src/zgdb/element.c" "src/zgdb/element.h" "src/zgdb/element_public.h" "src/zgdb/query.h" "src/zgdb/query.c" "src/zgdb/query_public.h" "src/zgdb/iterator.c" "src/zgdb/iterator.h" "src/zgdb/iterator_public.h" "src/zgdb/schema.c" "src/zgdb/schema.h" "src/zgdb/schema_public.h" "src/zgdb/condition.c" "src/zgdb/condition.h" "src/zgdb/condition_public.h" "src/run_tests.c" "src/tests/test.c" "src/tests/test.h")
add_executable (llp_lab1 "src/demo.c" "src/zgdb/format.c" "src/zgdb/format.h" "src/zgdb/document.h" "src/zgdb/document.c" "src/zgdb/list.c" "src/zgdb/list.h" "src/utils/optional.h" "src/utils/optional.c" "src/zgdb/document_public.h" "src/zgdb/format_public.h" "src/zgdb/element.c" "src/zgdb/element.h" "src/zgdb/element_public.h" "src/zgdb/query.h" "src/zgdb/query.c" "src/zgdb/query_public.h" "src/zgdb/iterator.c" "src/zgdb/iterator.h" "src/zgdb/iterator_public.h" "src/zgdb/schema.c" "src/zgdb/schema.h" "src/zgdb/schema_public.h" "src/zgdb/condition.c" "src/zgdb/condition.h" "src/zgdb/condition_public.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET llp_lab1 PROPERTY C_STANDARD 17)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mno-ms-bitfields")
endif()