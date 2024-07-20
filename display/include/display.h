#pragma once

#include <iostream>
#include <vector>
#include <utility>
#include <SDL2/SDL.h>

extern const int fps;
extern const int frame_target_time;

//config
enum class cull_method 
{
    CULL_NONE,
    CULL_BACKFACE,
};

//config
enum class render_method 
{
    RENDER_WIRE,
    RENDER_WIRE_VERTEX,
    RENDER_FILL_TRIANGLE,
    RENDER_FILL_TRIANGLE_WIRE,
};

inline render_method render_method_config;
inline cull_method cull_method_config;

class Display
{

public:
    Display(int window_height = 600, int window_width = 800);

    bool initialize_window();
    void destroye_window();

    void draw_grid();
    void draw_pixel(int x, int y, uint32_t color);
    void draw_line(int x0, int y0, int x1, int y1, uint32_t color);
    void draw_triangle(int x0, int y0, int x1, int y1,int x2, int y2, uint32_t color);
    void draw_filled_triangle(int x0, int y0, int x1, int y1,int x2, int y2, uint32_t color);
    void fill_flat_bottom_triangle(int x0, int y0, int x1, int y1,int x2, int y2, uint32_t color);
    void fill_flat_top_triangle(int x0, int y0, int x1, int y1,int x2, int y2, uint32_t color);
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