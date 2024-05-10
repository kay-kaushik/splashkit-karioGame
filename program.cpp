#include "splashkit.h"
#include <iostream>
#include <list>
#include <string>



// i will have to better understand the splashkit camera system. it is casuing a lot of confusion 


// struct Camera
// {
//     double x,y;
// };

// void update_camera(Camera &camera, const sprite &target, double screenWidth, double screenHeight)
// {
//     // Center the camera on the target sprite
//     camera.x = sprite_x(target) - screenWidth / 2;
//     camera.y = sprite_y(target) - screenHeight / 2;

//     // Ensure camera stays within the bounds of the game world
//     if (camera.x < 0)
//     {
//         camera.x = 0;
//     }
//     if (camera.y < 0)
//     {
//         camera.y = 0;
//     }
// }


void drawGround(sprite spr, double startx, double starty)
{
    double x = 0; 
    while (x < screen_width())
    {
        //std::cout << screen_width() << std::endl;
        //std::cout << x - cameraX << std::endl;

        sprite_set_x(spr, x);
        sprite_set_y(spr,starty);
        draw_sprite(spr);
        x = x + sprite_width(spr);
    }
}
int main()
{
    // screen data
    window start = open_window("Kario", 1000, 600);
    bitmap bg = load_bitmap("bG", "background.jpg");
    sprite bgSpr = create_sprite(bg);

    // gound data 
    bitmap groundBmp = load_bitmap("ground", "assets/images/ground4.png");
    sprite groundSprite = create_sprite(groundBmp);
    sprite_set_x(groundSprite, 0);
    double groundY =  window_height(start) - bitmap_height(groundBmp);
    sprite_set_y(groundSprite, groundY);

    // character data
    double charGround = groundY -32;

    // air ground data
    bitmap AgroundBmp = load_bitmap("Aground", "assets/images/groundAir.png");
    sprite Aground = create_sprite(AgroundBmp);
    sprite_set_x(Aground, 600);
    double AgroundY =  charGround - 50;
    sprite_set_y(Aground, AgroundY);

    // player data
    bitmap player = load_bitmap("playerBmp", "protSpriteSheet.png");
    bitmap_set_cell_details(player, 31, 32, 4, 3, 12);
    animation_script playAnimScript = load_animation_script("playRunR", "playerRunR.txt");
    animation_script playIdleScript = load_animation_script("playIdle", "playerIdle.txt");
    animation playRunR = create_animation(playAnimScript, "runR");
    animation playRunL = create_animation(playAnimScript, "runL");
    animation playIdle = create_animation(playIdleScript, "idle");
    sprite playerIdle = create_sprite(player, playIdleScript);
    sprite playerRunR = create_sprite(player, playAnimScript);
    drawing_options runRopt = option_with_animation(playRunR);
    drawing_options idleOpt = option_with_animation(playIdle);
    drawing_options runLopt = option_with_animation(playRunL);

    // sprite_start_animation(playerRunR, animation_name(playRunR));
    sprite_set_x(playerIdle, 100);
    sprite_set_y(playerIdle, charGround);
    sprite_set_x(playerRunR, 100);
    sprite_set_y(playerRunR, charGround);

    // zombie data
    bitmap zomb = load_bitmap("zombieBmp", "zombieSpriteSheet.png");
    bitmap_set_cell_details(zomb, 31, 32, 4, 3, 12);
    animation_script zombAnimS = load_animation_script("zombRun", "playerRunR.txt");
    animation zombAnim = create_animation(zombAnimS, "runL");
    sprite zombRun = create_sprite(zomb, zombAnimS);
    sprite_set_x(zombRun, 500);
    sprite_set_y(zombRun, charGround);
    sprite_start_animation(zombRun, "runl");

    // coin data
    bitmap coin1 = load_bitmap("coins", "assets/images/coinspritesheet.png");
    bitmap_set_cell_details(coin1, 64, 63, 8, 1, 8);
    animation_script coinScript = load_animation_script("coinAnimationScript", "coinAnimationScript.txt");
    animation coinAnim = create_animation(coinScript, "coin");
    sprite coinSprite = create_sprite(coin1, coinScript);
    sprite_start_animation(coinSprite, "coin");
    sprite_set_x(coinSprite, 500);
    sprite_set_y(coinSprite, charGround - 20);
    sound_effect coinSound = load_sound_effect("coinCollected", "coinCollected.wav");

    // portal data
    bitmap port = load_bitmap("port", "assets/images/portals.png");
    bitmap_set_cell_details(port, 32,32,4,5,17);
    animation_script portScript = load_animation_script("portalAnimationScript", "portalScript.txt");
    animation portalAnim = create_animation(portScript, "portal");
    sprite portal = create_sprite(port, portScript);
    sprite_start_animation(portal,"portal");
    sprite_set_x(portal, 800);
    sprite_set_y(portal, charGround);

    


    // ground level in the game
    //int ground = 300;

    bool isMoving = false;
    bool isJumping = false;
    bool collected = false;

    // jumping velocity
    vector_2d vec = vector_to(1, -1.25);
    // gravity velocity
    vector_2d gravity = vector_to(0, 0.02);
    // zombie velocity
    vector_2d zombVel = vector_to(-1, 0);
    // normal velocity
    vector_2d groundVel = vector_to(0, 0);

    // score
    int score = 0;
    string scoreString;

    while (!quit_requested())
    {
        clear_screen(COLOR_BLACK);
        //update_camera(camera, playerRunR, screen_width(), screen_height());
        draw_bitmap(bg,0,0);
        drawGround(bgSpr,0,0);
        draw_sprite(Aground, -camera.x, -camera.y);
        draw_sprite(portal);
        //draw_sprite(bgSpr, -camera.x, -camera.y);
        draw_sprite(playerRunR);
        
        if (sprite_offscreen(zombRun))
        {
            //move_sprite_to(zombRun, screen_width() - 10 ,charGround);
            sprite_set_x(zombRun, screen_width() - 10);
            sprite_set_y(zombRun, charGround);
        }
        else
        {
            draw_sprite(zombRun);
        }
        
        if (!collected)
        {
            draw_sprite(coinSprite);
        }
        drawGround(groundSprite,0,groundY, camera.x);
        


        //draw_sprite(groundSprite);
        
        // draw_rectangle(COLOR_RED, 200, 300, 25,40);
        string scoreString = "Score: " + std::to_string(score);
        draw_text(scoreString, COLOR_BLACK, 500 - 25, 10);
        refresh_screen(60);

        // update_sprite_animation(coinSprite);
        // update_sprite(coinSprite);
        if (!collected)
        {
            update_sprite_animation(coinSprite);
            update_sprite(coinSprite);
        }

        update_sprite_animation(portal);
        update_sprite(portal);
        sprite_set_velocity(zombRun, zombVel);
        update_sprite_animation(playerRunR);
        update_sprite(playerRunR);
        update_sprite_animation(zombRun);
        update_sprite(zombRun);
        update_sprite_animation(playerIdle);
        update_sprite(playerIdle);
        process_events();

        point_2d beforeJump;

        if (key_down(RIGHT_KEY))
        {
            if (sprite_animation_name(playerRunR) != "runr")
            {
                sprite_start_animation(playerRunR, "runr");
            }

            sprite_set_x(playerRunR, sprite_position(playerRunR).x + 1);
            sprite_set_x(playerIdle, sprite_position(playerIdle).x + 1);
            isMoving = true;
        }
        else if (key_down(LEFT_KEY))
        {
            if (sprite_animation_name(playerRunR) != "runl")
            {
                sprite_start_animation(playerRunR, "runl");
            }

            sprite_set_x(playerRunR, sprite_position(playerRunR).x - 1);
            sprite_set_x(playerIdle, sprite_position(playerIdle).x - 1);
            isMoving = true;
        }
        else if (key_typed(UP_KEY))
        {
            // sprite_set_y(playerRunR,sprite_position(playerRunR).y -1);
            sprite_set_velocity(playerRunR, vec);
            isJumping = true;

            // how to apply gravity once jump has initiated
        }
        else if (!isMoving)
        {
            sprite_start_animation(playerIdle, "idle");
        }

        if (isJumping)
        {

            // add the gravity to the player's velocity
            sprite_set_velocity(playerRunR, vector_add(sprite_velocity(playerRunR), gravity));

            if (sprite_position(playerRunR).y > charGround)
            {
                sprite_set_velocity(playerRunR, groundVel);
                sprite_set_y(playerRunR, charGround);
                isJumping = false;
            }
        }

        if (bitmap_collision(player, sprite_position(playerRunR), zomb, sprite_position(zombRun)))
        {
            clear_screen(COLOR_BLACK);

            draw_text("GAME OVER", COLOR_WHITE, 300, 300);
            refresh_screen();

            delay(5000);
            close_window(start);
            std::cout << "collisssionm soaunsuan" << std::endl;
        }

        //if (bitmap_collision(player, sprite_position(playerRunR), coin1, sprite_position(coinSprite)))
        if (sprite_collision(playerRunR,coinSprite))
        {
            free_sprite(coinSprite);
            play_sound_effect("coinCollected");
            std::cout << "collisssionm detected" << std::endl;
            score++;
            collected = true;
            
        }

        if(sprite_collision(playerRunR, portal))
        {
            //charGround = AgroundY;
        }

        // there is no way to differentiate multiple re draws of a sprite, either you will have to create multiple sprites with diff variable names or you could
        // store the different positions in an array

        // stroing coin sprites into a vector won't work as that would be problematic, can

        // best option I have found till now is to create less coins, individual sprites, which will be needed to be collected to win the game.
    }

    return 0;
}