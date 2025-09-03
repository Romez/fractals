#include <stdio.h>
#include <raylib.h>
#include <raymath.h>

int screen_width = 1600;
int screen_height = 1200;

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

    InitWindow(screen_width, screen_height, "Koch curve");

    SetTargetFPS(3);

    float pt1_len = screen_width - 10;
    float pt1_angle = 0;
    Vector2 pt1 = (Vector2) {
        .x = 10,
        .y = screen_height / 1.5,
    };

    float pt2_len = pt1_len;
    float pt2_angle = 2 * PI / 3;
    Vector2 pt2 = (Vector2) {
        .x = pt1.x + pt1_len * cosf(pt1_angle),
        .y = pt1.y + pt1_len * sinf(pt1_angle),
    };

    while (!WindowShouldClose()) {
        if (IsWindowResized()) {
            screen_width = GetScreenWidth();
            screen_height = GetScreenHeight();

            pt1_len = screen_width - 20;
            pt1 = (Vector2){
                .x = 10,
                .y = screen_height / 1.5,
            };
		}

        BeginDrawing();

        ClearBackground(BLACK);

        draw_koch(0, pt1, pt1_angle, pt1_len);
        draw_koch(0, pt2, pt2_angle, pt2_len);  

        EndDrawing();
    }

    CloseWindow();
    return 0;
}