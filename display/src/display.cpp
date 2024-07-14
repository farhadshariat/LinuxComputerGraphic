#include "../include/display.h"

const int fps = 30;
const int frame_target_time = 1000/fps;

Display::Display(int windowheight, int window_width)
        :window_height(window_height), window_width(window_width){}

bool Display::initialize_window()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		const char* error_message = SDL_GetError();
		std::cout<<"[SDL_Init] Error Message: "<< error_message << '\n';
		return false;
	}

	//maximizing our screen buffer(Fake Full Screen)
	SDL_DisplayMode display_mode;
	SDL_GetCurrentDisplayMode(0, &display_mode);

	//maximize width and height
	window_width = display_mode.w;
	window_height = display_mode.h;

	//create sdl widnow
	window = SDL_CreateWindow(
		nullptr,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		window_width,
		window_height,
		SDL_WINDOW_BORDERLESS
	);

	if (!window)
	{
		std::cout << "SDL window object doesnt created" << std::endl;
		return false;
	}

	//create sdl renderer
	//index: -1 for default widnow type (one widnow)
	//falgs: 0 no flag needed
	renderer = SDL_CreateRenderer(window, -1, 0);

	if (!renderer)
	{
		std::cout << "SDL renderer object doesnt created" << std::endl;
		return false;
	}

	//have sdl to be real full screen
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

	return true;
}

void Display::destroye_window()
{
    //release vector resoursed
    color_buffer.clear();
    color_buffer.shrink_to_fit();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Display::draw_grid()
{
	for (int y = 0; y < window_height; y += 10)
		for (int x = 0; x < window_width; x += 10)
			color_buffer[window_width * y + x] = 0xFF333333;
}

void Display::draw_pixel(int x, int y, uint32_t color)
{	
	if(x>=0 && x< window_width && y>=0 && y < window_height)
		color_buffer[window_width * y + x] = color;
}

void Display::draw_line(int x0, int y0, int x1, int y1, uint32_t color)
{	
	int delta_x = x1 - x0;
	int delta_y = y1 - y0;

	int longest_side_length = abs(delta_x) >= abs(delta_y) ? abs(delta_x) : abs(delta_y);

	float x_inc = delta_x / (float) longest_side_length;
	float y_inc = delta_y / (float) longest_side_length;

	float current_x = x0;
	float current_y = y0;

	for (size_t i = 0; i <= longest_side_length; i++)
	{
		draw_pixel(round(current_x), round(current_y), color);
		current_x += x_inc;
		current_y += y_inc;
	}
}

void Display::draw_triangle(int x0, int y0, int x1, int y1,int x2, int y2, uint32_t color)
{
	draw_line(x0, y0, x1, y1, color);
	draw_line(x1, y1, x2, y2, color);
	draw_line(x2, y2, x0, y0, color);
}


void Display::draw_rect(int x_a, int y_a, int width, int height, uint32_t color)
{
	for (int y = y_a; y < height + y_a; ++y)
		for (int x = x_a; x < width + x_a; ++x)
			draw_pixel(x, y, color);
}

void Display::clear_color_buffer(uint32_t color)
{
	for (int y = 0; y < window_height; ++y)
		for (int x = 0; x < window_width; ++x)
			color_buffer[window_width * y + x] = color;
}

void Display::render_color_buffer()
{
	SDL_UpdateTexture(
		color_buffer_texture,
		NULL,
		&color_buffer[0],
		(int)(window_width * sizeof(uint32_t))
	);

	SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}