#include "raylib.h"
#include "raymath.h"
#include "BaseCharacter.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>



int main()
{
    const int windowDimensions[2]{384, 384};
    InitWindow(windowDimensions[0], windowDimensions[1], "Clasy Clash");

    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos{0.0, 0.0};
    const float mapScale{4.f};


    Character knigth(windowDimensions[0], windowDimensions[1]);


    Prop props[2]{
        Prop{Vector2{600.f,300.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{400.f,500.f}, LoadTexture("nature_tileset/Log.png")}
    };

    Enemy goblin{
        Vector2{800.f, 300.f},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png"),
    };

    Enemy slime{
        Vector2{500.f, 700.f},
        LoadTexture("characters/slime_idle_spritesheet.png"),
        LoadTexture("characters/slime_run_spritesheet.png"),
    };

    Enemy* enemies[]{
        &goblin,
        &slime
    };

    for(auto enemy : enemies)
    {
        enemy->setTarget(&knigth);
    }


    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knigth.getWorldPos(), -1.f);

        // draw the map
        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);

        for(auto prop : props)
        {
            prop.Render(knigth.getWorldPos());
        }

        knigth.tick(GetFrameTime());

        if (knigth.getWorldPos().x < 0.f ||
            knigth.getWorldPos().y < 0.f ||
            knigth.getWorldPos().x + windowDimensions[0] > map.width * mapScale ||
            knigth.getWorldPos().y + windowDimensions[1] > map.height * mapScale
        )
        {
            knigth.undoMovement();
        }

        for(auto prop : props)
        {
            if( CheckCollisionRecs(prop.getCollisionRec(knigth.getWorldPos()), knigth.getCollisionRec()))
            {
                knigth.undoMovement();
            }
        }


        if(!knigth.getAlive())
        {
            DrawText("GAME OVER!", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        }
        else
        {
            std::string knigthsHealth = "Health: ";
            knigthsHealth.append(std::to_string(knigth.getHealth()),0,5);
            DrawText(knigthsHealth.c_str(), 55.f, 45.f, 40, RED);
        }

        for(auto enemy : enemies)
        {
            enemy->tick(GetFrameTime());
        }

        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            for(auto enemy : enemies)
            {
                if (CheckCollisionRecs(enemy->getCollisionRec(),knigth.getWeaponCollisionRec())) enemy->setAlive(false);
            }

        }

        EndDrawing();
    }
    CloseWindow();
}