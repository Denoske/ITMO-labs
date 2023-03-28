file(GLOB_RECURSE sources CONFIGURE_DEPENDS
    src/*.c
    src/*.h
    include/*.h
)

add_executable(image-transformer ${sources} include/format/bmp.h include/image/image.h src/file/file.c include/file/file.h)
target_include_directories(image-transformer PRIVATE src include)
