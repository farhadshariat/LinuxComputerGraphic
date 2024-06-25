#include "display/include/display.h"
#include "geometry/vector.h"
// #include "eigen3/Eigen/Dense"

static bool is_running = false;

const int N_POINT = 9*9*9;

std::vector<vec3_t> cube_points(N_POINT, {0.0, 0.0, 0.0});
std::vector<vec2_t> projected_points(N_POINT, {0.0, 0.0});

vec3_t camera_position = {.x=0, .y=0, .z=-5};
vec3_t cube_rotation = {.x=0, .y=0, .z=0};

float fov_factor = 640;

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

	int point_count = 0;

	for (float x = -1; x <= 1; x+=0.25)
	{
		for (float y = -1; y <= 1; y+=0.25)
		{
			for (float z = -1; z <= 1; z+=0.25)
			{
				cube_points[point_count++] = (vec3_t){.x= x, .y=y, .z=z};
			}
		}
	}
	
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

vec2_t project(vec3_t point)
{
	vec2_t projected_point= 
	{
		.x= (fov_factor * point.x) / point.z,
		.y= (fov_factor * point.y) / point.z
	};
	return projected_point;
} 

void update()
{
	cube_rotation.x += 0.01;
	cube_rotation.y += 0.01;
	cube_rotation.z += 0.01;

	for (size_t i = 0; i < N_POINT; i++)
	{
		vec3_t point= cube_points[i];

		point.rotate_x(cube_rotation.x);
		point.rotate_y(cube_rotation.y);
		point.rotate_z(cube_rotation.z);

		point.z -= camera_position.z;

		vec2_t projected_point = project(point);

		projected_points[i] = projected_point;
	}
}

//c++ way :(
void render(Display& display)
{
	display.draw_grid();

	for (size_t i = 0; i < N_POINT; i++)
	{	
		vec2_t projected_point = projected_points[i];
		display.draw_rect(
			projected_point.x + (display.window_width / 2),
			projected_point.y + (display.window_height / 2),
			4,
			4,
			0xFFFFFF00);
	}	

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