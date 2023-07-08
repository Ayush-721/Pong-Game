#include <iostream>
#include <raylib.h>

using namespace std;

class Ball
{
public:
    float x, y;
    int speed_x, speed_y;
    int radius;

    Ball(int x_coordinate, int y_coordinate, int ball_radius, int speedx, int speedy)
    {
        x = x_coordinate;
        y = y_coordinate;
        radius = ball_radius;
        speed_x = speedx;
        speed_y = speedy;
    }

    void Draw()
    {
        DrawCircle(x, y, radius, WHITE);
    }
    void Update()
    {
        x += speed_x;
        y += speed_y;

        if (y + radius >= GetScreenHeight() || y - radius <= 0)
        {
            speed_y*=-1;
        }
        if (x + radius >= GetScreenWidth() || x - radius <= 0)
        {
            speed_x*=-1;
        }
    }
};

class Paddle
{   
public:
    float x,y;
    float width,height;
    int speed;

    Paddle(int x_coordinate, int y_coordinate, int Paddlewidth, int PaddleHeight, int Paddlespeed)
    {
        x = x_coordinate;
        y = y_coordinate;
        width = Paddlewidth;
        height = PaddleHeight;
        speed = Paddlespeed;
    }
    void Draw()
    {
        DrawRectangle(x, y, width, height,WHITE);
    }

    void Update()
    {
        if(IsKeyDown(KEY_UP))
        {
            y = y - speed;
        }
        if(IsKeyDown(KEY_DOWN))
        {
            y = y + speed;
        }
        if(y<=0)
        {
            y = 0;
        }
        if(y + height >= GetScreenHeight())
        {
            y = GetScreenHeight() - height;
        }
    }
    
};

class CpuPaddle:public Paddle
{
    public:
    CpuPaddle(int xcoordinate, int ycoordinate, int Paddlewidth, int PaddleHeight, int Paddlespeed):Paddle(xcoordinate, ycoordinate, Paddlewidth, PaddleHeight, Paddlespeed)
    {

    }
    void Update(int ball_y)
    {
        if(y + height/2 > ball_y)
        {
            y = y - speed;
        }
        if(y + height/2 < ball_y)
        {
            y = y + speed;
        }
    }
};

int main()
{

    const int screenWidth = 1280;
    const int screenHeight = 800;
    const int RectangleMargin = 10;
    const int BallRadius = 20;
    const int Ballspeedx = 7;
    const int Ballspeedy = 7;
    const int PlayerWidth = 25;
    const int PlayerHeight = 120;
    const int PlayerX = screenWidth - PlayerWidth - RectangleMargin;
    const int PlayerY = screenHeight/2 - PlayerHeight/2;
    const int PlayerSpeed = 6;
    const int CpuX = RectangleMargin;
    const int CpuY = screenHeight/2 - PlayerHeight/2;
    
    //Creating objects
    Ball ball(screenWidth / 2, screenHeight / 2, BallRadius, Ballspeedx, Ballspeedy);
    Paddle player(PlayerX,PlayerY,PlayerWidth,PlayerHeight,PlayerSpeed);
    CpuPaddle CpuPlayer(CpuX,CpuY,PlayerWidth,PlayerHeight,PlayerSpeed);


    InitWindow(screenWidth, screenHeight, "My PONG Game!"); // initialise a window titled 'My PONG Game!'
    SetTargetFPS(60);  // no. of FPS we want(60)

    // Game Loop
    while (WindowShouldClose() == false) // check for any events : checks if Esc or X icon is pressed and ends the loop if it is the case
    {
        BeginDrawing(); // creates a blank canvas

        // Updating
        ball.Update();
        player.Update();
        CpuPlayer.Update(ball.y);

        ClearBackground(BLACK); // so that trace of objects is not left behind

        // Drawing
        DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);
        ball.Draw();
        CpuPlayer.Draw();
        player.Draw();

        EndDrawing(); // ends the blank canvas
    }

    CloseWindow(); // destroy the window
    return 0;
}