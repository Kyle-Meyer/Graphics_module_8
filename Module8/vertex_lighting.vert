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

// Uniform to constrain the number of lights the application uses
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
	// Start with emission and global ambient contribution
	vec4 final_color = material_emission + (global_light_ambient * material_ambient);
	
	// Transform vertex position and normal to world space
	vec4 world_position = model_matrix * vec4(vtx_position, 1.0);
	vec3 N = normalize(vec3(normal_matrix * vec4(vtx_normal, 0.0)));
	
	// View vector - from vertex to camera
	vec3 V = normalize(camera_position - vec3(world_position));
	
	// Process each light source
	for(int i = 0; i < num_lights; i++)
	{
		if(lights[i].enabled == 1)
		{
			vec3 L;
			
			// Check if light is directional (w=0) or positional (w=1)
			if(lights[i].position.w == 0.0)
			{
				// Directional light - position is actually the direction
				L = normalize(vec3(lights[i].position));
			}
			else
			{
				// Positional light - calculate direction from vertex to light
				L = normalize(vec3(lights[i].position) - vec3(world_position));
			}
			
			// Calculate halfway vector for Blinn-Phong
			vec3 H = normalize(L + V);
			
			// Ambient contribution from this light
			vec4 ambient_contribution = lights[i].ambient * material_ambient;
			
			// Diffuse contribution - depends on angle between L and N
			float NdotL = max(dot(N, L), 0.0);
			vec4 diffuse_contribution = lights[i].diffuse * material_diffuse * NdotL;
			
			// Specular contribution - depends on angle between H and N
			float NdotH = max(dot(N, H), 0.0);
			vec4 specular_contribution = vec4(0.0);
			if(NdotL > 0.0)  // Only add specular if surface faces light
			{
				specular_contribution = lights[i].specular * material_specular * 
				                        pow(NdotH, material_shininess);
			}
			
			// Add this light's contribution
			final_color += ambient_contribution + diffuse_contribution + specular_contribution;
		}
	}
	
	// Set output color with full opacity
	color = vec4(vec3(final_color), 1.0);
	
	// Convert position to clip coordinates and pass along
	gl_Position = pvm_matrix * vec4(vtx_position, 1.0);
}
