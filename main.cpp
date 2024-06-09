#include "display/include/display.h"

static bool is_running = false;

//c++ way :(
void setup(Display& display)
{
	display.color_buffer.reserve(display.window_height* display.window_width);

	display.color_buffer_texture = SDL_CreateTexture(
		display.renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		display.window_width,
		display.window_height
	);
}

void process_input()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		is_running = false;
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE)
			is_running = false;
		break;

	default:
		break;
	}
}

void update()
{

}

//c++ way :(
void render(Display& display)
{
	//r.g.b.a(transparency)
	SDL_SetRenderDrawColor(display.renderer, 0, 0, 0, 255);
	SDL_RenderClear(display.renderer);

	display.draw_grid();
	display.draw_rect(300, 200, 300, 150, 0xFFFF00FF);

	display.render_color_buffer();
	display.clear_color_buffer(0xFF000000);

	SDL_RenderPresent(display.renderer);
}


int main(int argc, char* argv[])
{
    Display display(600, 800);

	is_running = display.initialize_window();

	setup(display);

	while (is_running)
	{
		process_input();
		update();
		render(display);
	}

	display.destroye_window();

    std::cout<<"i hate cmake"<<'\n';

    return 0;
}