emcc koch.c -o docs/koch/index.html \
    -I../raylib/build_web/raylib/include -L../raylib/build_web/raylib -lraylib\
    -s USE_GLFW=3 -s ASYNCIFY\
    --shell-file ./koch_template.html