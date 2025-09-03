#include <stdio.h>
#include <raylib.h>
#include <raymath.h>

#define LINE_COLOR (Color){ 224, 255, 79, 255}

Vector2 calc_next_point(Vector2 pt, float angle, float len) {
    return (Vector2) {
        .x = pt.x + len * cosf(angle),
        .y = pt.y + len * sinf(angle),
    };
}

float max_len(int screen_width, int screen_height) {
    float len = screen_height / 2 * sqrt(3);
    if (len > screen_width) {
        len = screen_width;
    }
    return len;
}

void draw_koch(int depth, Vector2 pt1, float angle, float len) {
    if (depth == 0) {
        Vector2 pt2 = calc_next_point(pt1, angle, len);
        DrawLineV(pt1, pt2, LINE_COLOR);
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

float init_points(int screen_width, int screen_height, 
                 Vector2* pt1, float* pt1_angle, Vector2* pt2, float* pt2_angle, Vector2* pt3, float* pt3_angle) {
    float len = max_len(screen_width, screen_height);

    *pt1_angle = 0;
    float padding = (screen_width / 2 - len / 2);
    *pt1 = (Vector2) {
        .x = padding,
        .y = (len / 3) * sqrt(3) / 2,
    };

    *pt2_angle = 2 * PI / 3;
    *pt2 = calc_next_point(*pt1, *pt1_angle, len);

    *pt3_angle = -2 * PI / 3;
    *pt3 = calc_next_point(*pt2, *pt2_angle, len);

    return len;
}

int main () {
    int screen_width = 1600;
    int screen_height = 1600;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(screen_width, screen_height, "Koch curve");

    SetTargetFPS(30);

    float pt1_angle;
    Vector2 pt1;

    float pt2_angle;
    Vector2 pt2;

    float pt3_angle;
    Vector2 pt3;

    float len = init_points(screen_width, screen_height, &pt1, &pt1_angle, &pt2, &pt2_angle, &pt3, &pt3_angle);

    while (!WindowShouldClose()) {
        if (IsWindowResized()) {
            screen_width = GetScreenWidth();
            screen_height = GetScreenHeight();

            len = init_points(screen_width, screen_height, &pt1, &pt1_angle, &pt2, &pt2_angle, &pt3, &pt3_angle);
		}

        BeginDrawing();

        ClearBackground(BLACK);

        draw_koch(4, pt1, pt1_angle, len);
        draw_koch(4, pt2, pt2_angle, len);
        draw_koch(4, pt3, pt3_angle, len);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}