#include "display/include/display.h"
#include "geometry/vector.h"
#include "geometry/triangle.h"
#include "geometry/mesh.h"
#include <array>

std::vector<triangle_t> triangles_to_render(12, {0,0,0}); 

vec3_t camera_position = {.x=0, .y=0, .z=-5};
vec3_t cube_rotation = {.x=0, .y=0, .z=0};

float fov_factor = 640;

static bool is_running = false;
int previous_frame_time = 0;

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

vec2_t project(vec3_t point)
{
	vec2_t projected_point= 
	{
		.x= (fov_factor * point.x) / point.z,
		.y= (fov_factor * point.y) / point.z
	};
	return projected_point;
} 

void update(Display& display)
{
	while(!SDL_TICKS_PASSED(SDL_GetTicks(), previous_frame_time + frame_target_time));

	previous_frame_time = SDL_GetTicks();

	cube_rotation.x += 0.01;
	cube_rotation.y += 0.01;
	cube_rotation.z += 0.01;

	for (size_t i = 0; i < mesh_faces.size(); i++)
	{
		auto mesh_face = mesh_faces[i];

		std::array<vec3_t,3> face_vertices;
		face_vertices[0] = mesh_vertices[mesh_face.a - 1];
		face_vertices[1] = mesh_vertices[mesh_face.b - 1];
		face_vertices[2] = mesh_vertices[mesh_face.c - 1];

		triangle_t projected_triangle;

		for (size_t j = 0; j < face_vertices.size(); j++)
		{
			auto transformed_vertex = face_vertices[j];

			transformed_vertex.rotate_x(cube_rotation.x);
			transformed_vertex.rotate_y(cube_rotation.y);
			transformed_vertex.rotate_z(cube_rotation.z);

			transformed_vertex.z -= camera_position.z;

			//project 3D to 2D
			vec2_t projected_point = project(transformed_vertex);
			
			//scale and translate points to middle of screen
			projected_point.x += (display.window_width / 2);
			projected_point.y += (display.window_height / 2);

			projected_triangle.points[j] = projected_point;
		}

		//save projected triangle to triangle renderer
		triangles_to_render[i] = projected_triangle;
	}

}

//TODO: use static display
void render(Display& display)
{
	display.draw_grid();

	//loop through triangles
	for (size_t i = 0; i < triangles_to_render.size(); i++)
	{	
		triangle_t triangle = triangles_to_render[i];
		display.draw_rect(triangle.points[0].x , triangle.points[0].y , 3, 3, 0xFFFFFF00);
		display.draw_rect(triangle.points[1].x , triangle.points[1].y , 3, 3, 0xFFFFFF00);
		display.draw_rect(triangle.points[2].x , triangle.points[2].y , 3, 3, 0xFFFFFF00);
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
		update(display);
		render(display);
	}

	display.destroye_window();

    std::cout<<"i hate cmake"<<'\n';

    return 0;
}