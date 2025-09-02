#include <stdio.h>
#include <raylib.h>
#include <raymath.h>

int screenWidth = 1600;
int screenHeight = 1200;

Vector2 calc_next_point(Vector2 pt, float angle, float len) {
    return (Vector2) {
        .x = pt.x + len * cosf(angle),
        .y = pt.y + len * sinf(angle),
    };
}

void draw_koch(int depth, Vector2 pt1, float angle, float len) {
    if (depth == 0) {
        Vector2 pt2 = calc_next_point(pt1, angle, len);

        DrawLineV(pt1, pt2, (Color){ 224, 255, 79, 255});
    } else {
        float part_len = len / 3;
        float part_angle = PI / 3;

        Vector2 pt2 = calc_next_point(pt1, angle, part_len);
        Vector2 pt3 = calc_next_point(pt2, angle - part_angle, part_len);
        Vector2 pt4 = calc_next_point(pt3, angle + part_angle, part_len);

        draw_koch(depth - 1, pt1, angle, part_len);
        draw_koch(depth - 1, pt2, angle - part_angle, part_len);
        draw_koch(depth - 1, pt3, angle + part_angle, part_len);
        draw_koch(depth - 1, pt4, angle, part_len);
    }
}

int main () {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(screenWidth, screenHeight, "Koch curve");

    SetTargetFPS(3);

    float len = screenWidth - 10;
    Vector2 pt1 = (Vector2){
        .x = 10,
        .y = screenHeight / 1.5,
    };

    while (!WindowShouldClose()) {
        if (IsWindowResized()) {
            screenWidth = GetScreenWidth();
            screenHeight = GetScreenHeight();

            len = screenWidth - 20;
            pt1 = (Vector2){
                .x = 10,
                .y = screenHeight / 1.5,
            };
		}

        BeginDrawing();

        ClearBackground(BLACK);

        draw_koch(4, pt1, 0, len);  

        EndDrawing();
    }

    CloseWindow();
    return 0;
}