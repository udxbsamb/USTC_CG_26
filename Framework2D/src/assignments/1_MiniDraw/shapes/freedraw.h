#pragma once
#include <vector>

#include "shape.h"
//considering possible further requirements,we need to store all the points.
namespace USTC_CG
{
class Freedraw : public Shape
{
   public:
    Freedraw() = default;

    // Initialize a Freedraw with a list of points
    Freedraw(std::vector<float> x_list, std::vector<float> y_list);

    virtual ~Freedraw() = default;

    // Draws the Freedraw on the screen
    // Overrides draw function to implement Freedraw-specific drawing logic
    void draw(const Config& config) const override;

    // Overrides Shape's update function to adjust the Freedraw's vertices during interaction
    void update(float x, float y) override;

    void add_control_point(float x, float y) override;

   private:
    std::vector<float> x_list, y_list;
    //float start_point_x_ = 0.0f, start_point_y_ = 0.0f;(already in list)
    float end_point_x_ = 0.0f, end_point_y_ = 0.0f;// tracks the current position of the mouse during drawing, used for dynamic updates of the Freedraw's shape
};
}  // namespace USTC_CG
