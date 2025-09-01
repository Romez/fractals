#include <stdio.h>
#include <raylib.h>
#include <raymath.h>

int screenWidth = 1600;
int screenHeight = 1200;



void draw_koch(int depth, Vector2 pt1, float angle, float len) {
    if (depth == 0) {
        Vector2 pt2 = (Vector2) {
            .x = pt1.x + len * cosf(angle),
            .y = pt1.y + len * sinf(angle),
        };

        DrawLineV(pt1, pt2, WHITE);
    } else {
        Vector2 pt2 = (Vector2) {
            .x = pt1.x + (len / 3) * cosf(angle),
            .y = pt1.y + (len / 3) * sinf(angle),
        };

        Vector2 pt3 = (Vector2) {
            .x = pt2.x + (len / 3) * cosf(angle - (PI / 3)),
            .y = pt2.y + (len / 3) * sinf(angle - (PI / 3)),
        };

        Vector2 pt4 = (Vector2) {
            .x = pt3.x + (len / 3) * cosf(angle + (PI / 3)),
            .y = pt3.y + (len / 3) * sinf(angle + (PI / 3)),
        };

        draw_koch(depth - 1, pt1, angle, len / 3);
        draw_koch(depth - 1, pt2, angle - (PI / 3), len / 3);
        draw_koch(depth - 1, pt3, angle + (PI / 3), len / 3);
        draw_koch(depth - 1, pt4, angle, len / 3);
    }
}

int main () {
    InitWindow(screenWidth, screenHeight, "Koch");

    SetTargetFPS(1);

    float len = 1200;
    Vector2 pt1 = (Vector2){.x = 200, .y = 600};

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BLACK);

        draw_koch(4, pt1, 0, len);  

        EndDrawing();
    }

    CloseWindow();
    return 0;
}