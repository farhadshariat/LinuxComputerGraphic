#include "display/include/display.h"
#include "geometry/vector.h"
#include "geometry/triangle.h"
#include "geometry/mesh.h"
#include "geometry/matrix.h"
#include "asset/BlenederObjParser.h"
#include "asset/utility.h"
#include <memory>

std::vector<triangle_t> triangles_to_render;
Mesh cube_mesh;

vec3_t camera_position = {.x=0, .y=0, .z=0};
vec3_t cube_rotation = {.x=0, .y=0, .z=0};

float fov_factor = 640;

static bool is_running = false;
int previous_frame_time = 0;

//c++ way :(
void setup(Display& display)
{
	render_method_config = render_method::RENDER_WIRE;
	cull_method_config = cull_method::CULL_BACKFACE;

	display.color_buffer.reserve(display.window_height* display.window_width);

	display.color_buffer_texture = SDL_CreateTexture(
		display.renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		display.window_width,
		display.window_height
	);

	cube_mesh.load_cube_mesh_data();
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
		if (event.key.keysym.sym == SDLK_1)
			render_method_config = render_method::RENDER_WIRE_VERTEX;
		if (event.key.keysym.sym == SDLK_2)
			render_method_config = render_method::RENDER_WIRE;
		if (event.key.keysym.sym == SDLK_3)
			render_method_config = render_method::RENDER_FILL_TRIANGLE;
		if (event.key.keysym.sym == SDLK_4)
			render_method_config = render_method::RENDER_FILL_TRIANGLE_WIRE;
		if (event.key.keysym.sym == SDLK_c)
			cull_method_config = cull_method::CULL_BACKFACE;
		if (event.key.keysym.sym == SDLK_d)
			cull_method_config = cull_method::CULL_NONE;
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

	//clear every frame
	triangles_to_render.clear();

	//cube_mesh.rotataion.x += 0.01;
	cube_mesh.rotataion.y += 0.01;
	//cube_mesh.rotataion.z += 0.01;
	
	//cube_mesh.scale.x += 0.002;
	//cube_mesh.scale.y += 0.002;
	//cube_mesh.translation.x += 0.01;
	//cube_mesh.translation.y += 0.01;
	cube_mesh.translation.z = 5;

	matrix4_t scale_matrix;
	matrix4_t translation_matrix;
	matrix4_t rotation_matrix_x;
	matrix4_t rotation_matrix_y;
	matrix4_t rotation_matrix_z;
	scale_matrix.make_scale(cube_mesh.scale.x, cube_mesh.scale.y, cube_mesh.scale.z);
	translation_matrix.make_translation(cube_mesh.translation.x, cube_mesh.translation.y, cube_mesh.translation.z);
	rotation_matrix_x.make_rotation_x(cube_mesh.rotataion.x);
	rotation_matrix_y.make_rotation_y(cube_mesh.rotataion.y);
	rotation_matrix_z.make_rotation_z(cube_mesh.rotataion.z);

	for (size_t i = 0; i < cube_mesh.faces.size(); i++)
	{
		auto mesh_face = cube_mesh.faces[i];

		std::array<vec3_t,3> face_vertices;
		face_vertices[0] = cube_mesh.vertices[mesh_face.a - 1];
		face_vertices[1] = cube_mesh.vertices[mesh_face.b - 1];
		face_vertices[2] = cube_mesh.vertices[mesh_face.c - 1];

		std::array<vec4_t,3> transformed_vertices;

		for (size_t j = 0; j < face_vertices.size(); j++)
		{
			auto transformed_vertex = face_vertices[j].convert_to_vec4();

			// //scaling operation
			// transformed_vertex = scale_matrix.mul_vec4(transformed_vertex);

			// //rotation operation
			// transformed_vertex = rotation_matrix_x.mul_vec4(transformed_vertex);
			// transformed_vertex = rotation_matrix_y.mul_vec4(transformed_vertex);
			// transformed_vertex = rotation_matrix_z.mul_vec4(transformed_vertex);

			// //translation operation
			// transformed_vertex = translation_matrix.mul_vec4(transformed_vertex);

			//world matrix
			matrix4_t world_matrix;
			world_matrix = world_matrix.identity();
			world_matrix = scale_matrix.mul_mat4(world_matrix);
			world_matrix = rotation_matrix_z.mul_mat4(world_matrix);
			world_matrix = rotation_matrix_y.mul_mat4(world_matrix);
			world_matrix = rotation_matrix_x.mul_mat4(world_matrix);
			world_matrix = translation_matrix.mul_mat4(world_matrix);
			
			//apply world matrix trasnsformation to a vector
			transformed_vertex = world_matrix.mul_vec4(transformed_vertex);

			//save transformed vertices
			transformed_vertices[j] = transformed_vertex;
		}

		if(cull_method_config == cull_method::CULL_BACKFACE)
		{
			//check backface culling
			// A B C Clockwise
			vec3_t vector_a = transformed_vertices[0].convert_to_vec3();/*    A    */
			vec3_t vector_b = transformed_vertices[1].convert_to_vec3();/*   / \   */
			vec3_t vector_c = transformed_vertices[2].convert_to_vec3();/*  C---B  */

			//get vector subtraction AC AB
			vec3_t vector_ab = vector_b - vector_a;
			vec3_t vector_ac = vector_c - vector_a;

			//compute the face normal (left handed system for cross product)
			vec3_t normal = vector_ab.cross(vector_ac);

			// normalize face normal vector
			normal.normalize();

			//find vector between point on face triangle and camera
			vec3_t camera_ray = camera_position - vector_a;

			float dot_product = normal * camera_ray;

			if(dot_product < 0)
				continue;
		}

		std::array<vec2_t, 3> projected_points;

		for(size_t j = 0; j < transformed_vertices.size(); j++)
		{
			//project 3D to 2D
			projected_points[j] = project(transformed_vertices[j].convert_to_vec3());
			
			//scale and translate points to middle of screen
			projected_points[j].x += (display.window_width / 2);
			projected_points[j].y += (display.window_height / 2);
		}

		float avg_depth = (float)(transformed_vertices[0].z + transformed_vertices[1].z + transformed_vertices[2].z) / 3;

		triangle_t projected_triangle;
		projected_triangle.points = projected_points;
		projected_triangle.color = mesh_face.color;
		projected_triangle.avg_depth = avg_depth;


		//save projected triangle to triangle renderer
		triangles_to_render.push_back(projected_triangle);
	}

	//acsending order by
	std::sort(triangles_to_render.begin(), triangles_to_render.end(), [ ]( const auto& lhs, const auto& rhs )
	{
		return lhs.avg_depth > rhs.avg_depth;
	});
}

//TODO: use static display
void render(Display& display)
{
	display.draw_grid();

	//loop through triangles
	for (size_t i = 0; i < triangles_to_render.size(); i++)
	{	
		triangle_t triangle = triangles_to_render[i];

		if(render_method_config == render_method::RENDER_FILL_TRIANGLE 
		|| render_method_config == render_method::RENDER_FILL_TRIANGLE_WIRE)
		{
			display.draw_filled_triangle(
				triangle.points[0].x, triangle.points[0].y,
				triangle.points[1].x, triangle.points[1].y,
				triangle.points[2].x, triangle.points[2].y,
				triangle.color
			);			
		}
		if(render_method_config == render_method::RENDER_WIRE 
		|| render_method_config == render_method::RENDER_WIRE_VERTEX 
		|| render_method_config == render_method::RENDER_FILL_TRIANGLE_WIRE)
		{
			// display.draw_rect(triangle.points[0].x , triangle.points[0].y , 3, 3, 0xFFFFFF00);
			// display.draw_rect(triangle.points[1].x , triangle.points[1].y , 3, 3, 0xFFFFFF00);
			// display.draw_rect(triangle.points[2].x , triangle.points[2].y , 3, 3, 0xFFFFFF00);

			display.draw_triangle(
				triangle.points[0].x, triangle.points[0].y,
				triangle.points[1].x, triangle.points[1].y,
				triangle.points[2].x, triangle.points[2].y,
				0xFFFFFFFF
				);
		}
		if(render_method_config == render_method::RENDER_WIRE_VERTEX)
		{
			display.draw_rect(triangle.points[0].x - 3 , triangle.points[0].y - 3 , 6, 6, 0xFFFFFF00);
			display.draw_rect(triangle.points[1].x - 3 , triangle.points[1].y - 3 , 6, 6, 0xFFFFFF00);
			display.draw_rect(triangle.points[2].x - 3 , triangle.points[2].y - 3 , 6, 6, 0xFFFFFF00);
		}
	}

	// display.draw_filled_triangle(500, 200, 100, 400, 500, 700, 0xFF00FF00);
	// display.draw_triangle(500, 200, 100, 400, 500, 700, 0xFF00FF00);

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

    return 0;
}