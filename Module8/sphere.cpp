#include "sphere.hpp"
#include <cmath>

namespace cg
{

SphereSurface::SphereSurface(uint32_t slices, uint32_t stacks, int32_t position_loc, int32_t normal_loc)
    : TriSurface()
{
    generate_sphere(slices, stacks);
    
    // Calculate vertex normals and create buffers
    end(position_loc, normal_loc);
}

SphereSurface::~SphereSurface()
{
    // Base class destructor handles cleanup
}

void SphereSurface::generate_sphere(uint32_t slices, uint32_t stacks)
{
    const float PI = 3.14159265359f;
    
    // Generate vertices
    // Top pole vertex
    VertexAndNormal top_vertex;
    top_vertex.vertex = Point3(0.0f, 0.0f, 1.0f);
    top_vertex.normal = Vector3(0.0f, 0.0f, 0.0f); // Will be calculated in end()
    vertices_.push_back(top_vertex);
    
    // Generate vertices for each stack (excluding poles)
    for(uint32_t stack = 1; stack < stacks; stack++)
    {
        float phi = PI * static_cast<float>(stack) / static_cast<float>(stacks);
        float sin_phi = std::sin(phi);
        float cos_phi = std::cos(phi);
        
        for(uint32_t slice = 0; slice < slices; slice++)
        {
            float theta = 2.0f * PI * static_cast<float>(slice) / static_cast<float>(slices);
            float sin_theta = std::sin(theta);
            float cos_theta = std::cos(theta);
            
            VertexAndNormal vertex;
            vertex.vertex.x = sin_phi * cos_theta;
            vertex.vertex.y = sin_phi * sin_theta;
            vertex.vertex.z = cos_phi;
            vertex.normal = Vector3(0.0f, 0.0f, 0.0f); // Will be calculated in end()
            
            vertices_.push_back(vertex);
        }
    }
    
    // Bottom pole vertex
    VertexAndNormal bottom_vertex;
    bottom_vertex.vertex = Point3(0.0f, 0.0f, -1.0f);
    bottom_vertex.normal = Vector3(0.0f, 0.0f, 0.0f); // Will be calculated in end()
    vertices_.push_back(bottom_vertex);
    
    // Generate faces
    // Top cap triangles (connect to top pole)
    for(uint32_t slice = 0; slice < slices; slice++)
    {
        uint16_t next_slice = (slice + 1) % slices;
        
        faces_.push_back(0); // Top pole
        faces_.push_back(1 + slice);
        faces_.push_back(1 + next_slice);
    }
    
    // Middle stacks (quads divided into triangles)
    for(uint32_t stack = 0; stack < stacks - 2; stack++)
    {
        for(uint32_t slice = 0; slice < slices; slice++)
        {
            uint16_t next_slice = (slice + 1) % slices;
            
            uint16_t current_row_start = 1 + stack * slices;
            uint16_t next_row_start = 1 + (stack + 1) * slices;
            
            // First triangle of quad
            faces_.push_back(current_row_start + slice);
            faces_.push_back(next_row_start + slice);
            faces_.push_back(next_row_start + next_slice);
            
            // Second triangle of quad
            faces_.push_back(current_row_start + slice);
            faces_.push_back(next_row_start + next_slice);
            faces_.push_back(current_row_start + next_slice);
        }
    }
    
    // Bottom cap triangles (connect to bottom pole)
    uint16_t bottom_pole_index = static_cast<uint16_t>(vertices_.size() - 1);
    uint16_t last_row_start = 1 + (stacks - 2) * slices;
    
    for(uint32_t slice = 0; slice < slices; slice++)
    {
        uint16_t next_slice = (slice + 1) % slices;
        
        faces_.push_back(bottom_pole_index); // Bottom pole
        faces_.push_back(last_row_start + next_slice);
        faces_.push_back(last_row_start + slice);
    }
}

} // namespace cg
