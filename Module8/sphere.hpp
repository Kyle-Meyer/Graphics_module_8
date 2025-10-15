#ifndef __SCENE_SPHERE_HPP__
#define __SCENE_SPHERE_HPP__

#include "scene/tri_surface.hpp"

namespace cg
{

/**
 * Sphere surface using indexed vertex arrays.
 * Extends TriSurface and uses GL_TRIANGLES for rendering.
 */
class SphereSurface : public TriSurface
{
  public:
    /**
     * Constructor. Creates a unit sphere centered at origin.
     * @param  slices       Number of longitudinal divisions
     * @param  stacks       Number of latitudinal divisions
     * @param  position_loc Vertex shader position location
     * @param  normal_loc   Vertex shader normal location
     */
    SphereSurface(uint32_t slices, uint32_t stacks, int32_t position_loc, int32_t normal_loc);

    /**
     * Destructor.
     */
    ~SphereSurface();

  private:
    /**
     * Generate the sphere vertices and faces using indexed triangulation.
     * @param  slices       Number of longitudinal divisions
     * @param  stacks       Number of latitudinal divisions
     */
    void generate_sphere(uint32_t slices, uint32_t stacks);
};

} // namespace cg

#endif
