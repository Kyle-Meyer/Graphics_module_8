#version 410 core

// Incoming vertex and normal attributes
// Vertex position attribute
layout (location = 0) in vec3 vtx_position;
// Vertex normal attribute
layout (location = 1) in vec3 vtx_normal;

// Per vertex lighting - vertex shader. Outputs a varying (intepolated) color to the 
// fragment shader
layout (location = 0) smooth out vec4 color;

// Uniforms for material properties
uniform vec4   material_ambient;
uniform vec4   material_diffuse;
uniform vec4   material_specular;
uniform vec4   material_emission;
uniform float  material_shininess;

// Global lighting environment ambient intensity
uniform vec4  global_light_ambient;

// Global camera position
uniform vec3  camera_position;

// Uniforms for matrices
uniform mat4 pvm_matrix;		// Composite projection, view, model matrix
uniform mat4 model_matrix;	// Modeling  matrix
uniform mat4 normal_matrix;	// Normal transformation matrix

// Uniform to constrian the number of lights the application uses
uniform int num_lights;

// Structure for a light source. Allow up to 8 lights. No attenuation or spotlight
// support yet.
const int MAX_LIGHTS = 2; 
struct LightSource
{
  int  enabled;
  vec4 position;
  vec4 ambient;
  vec4 diffuse;
  vec4 specular;
};
uniform LightSource lights[MAX_LIGHTS]; 

// Simple shader for per vertex lighting.
void main()
{
	// Student to define - support Blinn-Phong reflection model

  // Convert position to clip coordinates and pass along
  gl_Position = pvm_matrix * vec4(vtx_position, 1.0);
}
