#include "raylib.h"

const int screenWidth = 800;
const int screenHeight = 450;

int score1 = 0;
int score2 = 0;

class Ball{
    public:
    float speedX = -7.f;
    float speedY = 7.f;
    float radius = 10.f;
    float x = screenWidth / 2.f;
    float y = screenHeight / 2.f;

    void Draw()
    {
       DrawCircle(x, y, radius, WHITE);
    }
    // this function sucks
    void CollisionDetection(Rectangle paddle)
    {
        if (CheckCollisionCircleRec(Vector2{x, y}, radius, Rectangle{paddle.x, paddle.y, paddle.width, paddle.height}) && x >= paddle.width -5)
        {
            speedX *= -1;
        }
        else if (CheckCollisionCircleRec(Vector2{x, y}, radius, Rectangle{paddle.x, paddle.y, paddle.width, paddle.height}) && x >= screenWidth - paddle.width +5)
        {
            speedX *= -1;
        }
    }
    void Update()
    {
        x += speedX;
        y += speedY;

        if (y + radius >= GetScreenHeight() || y - radius <=0)
        {
            speedY *= -1;
        }
        //resets position if out-of-bounds
        if (x <= -300 || x >= screenWidth + 300) // the arithmetic is for an offset
        {
            x = screenWidth / 2.f;
            y = screenHeight / 2.f;
            speedX *= -1; // flips the direction so it's not boring
        }
    }
    void Score()
    {
        if (x <=0)
        {
            score2++;
        }
        else if (x >=screenWidth)
        {
            score1++;
        }
    }

};
class Paddle
{
    public:
    bool player1 = true;
    float speed = 7;
    float width = 10;
    float height = 70;
    float y = screenHeight / 2.f;
    float x = 0;

    void Draw()
    {
        DrawRectangle(x, y, width, height, WHITE);
    }
    void Update()
    {
        //user input
        if (!player1)
        {
            if (IsKeyDown(KEY_UP))
            {
                y -= speed;
            }
            else if (IsKeyDown(KEY_DOWN))
            {
                y += speed;
            }
        }
        else
        {
            if (IsKeyDown(KEY_W))
            {
                y -= speed;

            }
            else if (IsKeyDown(KEY_S))
            {
                y += speed;
            }
        }
        // clamps the paddles
        if (y < 0)
        {
            y = 0;
        }
        else if (y > screenHeight - height)
        {
            y = screenHeight - height;
        }
    }
};

int main()
{
    InitWindow(screenWidth, screenHeight, "Pong Game!");
    SetTargetFPS(60);

    Ball ball;
    Paddle paddle1;
    Paddle paddle2;

    paddle2.player1 = false;
    paddle2.x = screenWidth - paddle2.width;
    paddle2.y = 14;


    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        //update
        paddle1.Update();
        paddle2.Update();
        ball.Update();

        ball.CollisionDetection(Rectangle{paddle1.x, paddle1.y, paddle1.width, paddle1.height});
        ball.CollisionDetection(Rectangle{paddle2.x, paddle2.y, paddle2.width, paddle2.height});

        //draw
        DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);
        paddle1.Draw();
        paddle2.Draw();
        ball.Draw();

        EndDrawing();
    }

    return 0;
}
