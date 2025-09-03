emcc koch.c -o docs/koch/index.html \
    -I../raylib/build_web/raylib/include -L../raylib/build_web/raylib -lraylib\
    -s USE_GLFW=3 -s ASYNCIFY\
    -O3 \
    --shell-file ./koch.html

emcc snowflake_koch.c -o docs/snowkoch/index.html \
    -I../raylib/build_web/raylib/include -L../raylib/build_web/raylib -lraylib\
    -s USE_GLFW=3 -s ASYNCIFY\
    -O3 \
    --shell-file ./snowkoch.html
