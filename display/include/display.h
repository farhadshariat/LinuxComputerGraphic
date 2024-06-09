#pragma once

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

class Display
{

public:
    Display(int window_height = 600, int window_width = 800);

    bool initialize_window();
    void destroye_window();

    void draw_grid();
    void draw_rect(int x_a, int y_a, int width, int height, uint32_t color);

    void clear_color_buffer(uint32_t color);
    void render_color_buffer();

public:
    int window_height;
    int window_width;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    std::vector<uint32_t> color_buffer;
    SDL_Texture* color_buffer_texture = nullptr;
};