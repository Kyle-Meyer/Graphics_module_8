#include "scene/color_node.hpp"

namespace cg
{

ColorNode::ColorNode() : PresentationNode() {
    // Set default material properties
    material_ambient_ = Color4(0.2f, 0.2f, 0.2f, 1.0f);
    material_diffuse_ = Color4(0.8f, 0.8f, 0.8f, 1.0f);
    material_specular_ = Color4(0.0f, 0.0f, 0.0f, 1.0f);
    material_emission_ = Color4(0.0f, 0.0f, 0.0f, 1.0f);
    material_shininess_ = 1.0f;
}

ColorNode::ColorNode(const Color4 &c) : PresentationNode()
{     
   // Use the provided color as the diffuse component
   // Set ambient to a darker version (30% of diffuse)
   material_ambient_ = Color4(c.r * 0.3f, c.g * 0.3f, c.b * 0.3f, 1.0f);
   material_diffuse_ = c;
   material_specular_ = Color4(0.2f, 0.2f, 0.2f, 1.0f);  // Small specular highlight
   material_emission_ = Color4(0.0f, 0.0f, 0.0f, 1.0f);
   material_shininess_ = 20.0f;  // Moderate shininess
}

void ColorNode::draw(SceneState &scene_state)
{
    PresentationNode::draw(scene_state);
}

} // namespace cg
