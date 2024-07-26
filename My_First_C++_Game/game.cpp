#define is_down(b) input->buttons[b].is_down
#define pressed(b) input->buttons[b].is_down && input->buttons[b].changed
#define released(b) !(input->buttons[b].is_down && input->buttons[b].changed)


float player_px = -20.f, player_dpx, player_py, player_dpy;
float grass_box_x = 80, grass_box_y = 40;
float player_half_size_x = 5, player_half_size_y = 5;
float ball_px, ball_py, ball_dpx = 150, ball_dpy = 30, ball_half_size = 2;
float health_x;

int static player_health_max = 100, player_health = 100;

internal void simulate_game(Input* input, float dt) {
    clear_screen(0xe6ff00); 

    draw_rect(0, 0, grass_box_x, grass_box_y, 0x8dbc49);
    

    // Player Health Bar
    draw_rect(0 + 18, grass_box_y + 5, 36, 2, 0xff0000);
    draw_rect(health_x + 18, grass_box_y + 5, clamp(0, (37 - player_health), 36), 2, 0xffffff);
    draw_rect(36, grass_box_y + 5, 18, 2, 0xe6ff00);

    float player_ddpy = 0.f;
    float player_ddpx = 0.f;


    if (is_down(BUTTON_UP)) player_ddpy += 2000;
    if (is_down(BUTTON_DOWN)) player_ddpy -= 2000;
    if (is_down(BUTTON_RIGHT)) player_ddpx += 2000;
    if (is_down(BUTTON_LEFT)) player_ddpx -= 2000;

    player_ddpy -= player_dpy * 10.f;
    player_ddpx -= player_dpx * 10.f;


    player_py = player_py + player_dpy * dt + player_ddpy * dt * dt * .5f;
    player_dpy = player_dpy + player_ddpy * dt;

    player_px = player_px + player_dpx * dt + player_ddpx * dt * dt * .5f;
    player_dpx = player_dpx + player_ddpx * dt;

    
    // Player-Ball Collision Detection

    if (ball_px + ball_half_size > player_px - player_half_size_x &&
        ball_px - ball_half_size < player_px + player_half_size_x &&
        ball_py + ball_half_size > player_py - player_half_size_y &&
        ball_py - ball_half_size < player_py + player_half_size_y) {

        // Figure a way to interrupt game play loop here to end game when a collision is detected. Or implement a life system?
        player_health -= 7;
        draw_rect(0, 0, 30, 30, 0xffffff);
    }
    
    // Player Collision Detection


    if (player_py + player_half_size_y > grass_box_y) {
        player_py = grass_box_y - player_half_size_y;
    }
    else if (player_py - player_half_size_y < -grass_box_y) {
        player_py = -grass_box_y + player_half_size_y;
    } 
    
    if (player_px + player_half_size_x > grass_box_x) {
        player_px = grass_box_x - player_half_size_x;
    }
    else if (player_px - player_half_size_x < -grass_box_x) {
        player_px = -grass_box_x + player_half_size_x;
    }
    
    ball_px += ball_dpx * dt;
    ball_py += ball_dpy * dt;

    draw_rect(ball_px, ball_py, ball_half_size, ball_half_size, 0xff0000);

    //Collision Detection for the ball (small rectangle)

    if (ball_px + ball_half_size > grass_box_x) {

        ball_px = grass_box_x - ball_half_size;
        ball_dpx += (grass_box_x / 30 - ball_half_size);
        ball_dpx *= -1;
    }
    else if (ball_px - ball_half_size < -grass_box_x) {
        ball_px = -grass_box_x + ball_half_size;
        ball_dpx += (-grass_box_x / 30 + ball_half_size);
        ball_dpx *= -1;
    }

    if (ball_py + ball_half_size > grass_box_y) {

        ball_py = grass_box_y - ball_half_size;
        ball_dpy += (grass_box_y / 30 - ball_half_size);
        ball_dpy *= -1;
    }
    else if (ball_py - ball_half_size < -grass_box_y) {
        ball_py = -grass_box_y + ball_half_size;
        ball_dpy += (-grass_box_y / 30 + ball_half_size);
        ball_dpy *= -1;
    }
    


    draw_rect(player_px, player_py, player_half_size_x, player_half_size_y, 0x00f0f0);
    draw_rect(player_px - 2, player_py + 1.5, player_half_size_x / 4, player_half_size_y / 4, 0x000000);
    draw_rect(player_px + 2, player_py + 1.5, player_half_size_x / 4, player_half_size_y / 4, 0x000000);

    draw_rect(player_px, player_py - 2.5, player_half_size_x / 1.5 , player_half_size_y / 5, 0x000000);
}