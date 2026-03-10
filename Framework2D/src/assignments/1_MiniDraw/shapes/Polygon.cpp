#include "Polygon.h"
//#include "line.h"
#include <imgui.h>
#include <iostream>

namespace USTC_CG
{
Polygon::Polygon(std::vector<float> x, std::vector<float> y)
{
    x_list=x;
    y_list=y;
}
// Draw the polygon using ImGui
void Polygon::draw(const Config& config) const
{//use the same procedure in line.cpp to draw lines.
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    
    for (int i = 0; i < x_list.size()-1 ; i++)
    {
        //std::cout<<1;
        draw_list->AddLine(
            ImVec2(config.bias[0] + x_list[i], config.bias[1] + y_list[i]),
            ImVec2(config.bias[0] + x_list[i+1], config.bias[1] + y_list[i+1]),
             IM_COL32(
                config.line_color[0],
                config.line_color[1],
                config.line_color[2],
                config.line_color[3]),
            config.line_thickness);//draw lines between exisiting points
        //std::cout<<2;
        draw_list->AddLine(
            ImVec2(config.bias[0] + x_list.back(), config.bias[1] + y_list.back()),
            ImVec2(config.bias[0] + end_point_x_, config.bias[1] + end_point_y_),
             IM_COL32(
                config.line_color[0],
                config.line_color[1],
                config.line_color[2],
                config.line_color[3]),
            config.line_thickness);//draw line between last point and current mouse position
        
            draw_list->AddLine(
            ImVec2(config.bias[0] + end_point_x_, config.bias[1] + end_point_y_),
            ImVec2(config.bias[0] + x_list[0], config.bias[1] + y_list[0]),
             IM_COL32(
                config.line_color[0],
                config.line_color[1],
                config.line_color[2],
                config.line_color[3]),
            config.line_thickness);//draw line between last point and current mouse position

    }
}

void Polygon::add_control_point(float x, float y) 
{
   // std::cout<< "added" << std::endl;
    x_list.push_back(end_point_x_);
    y_list.push_back(end_point_y_);
    //std::cout<<4;
}

void Polygon::update(float x, float y) 
{
    end_point_x_ = x;
    end_point_y_ = y;
}

}  // namespace USTC_CG
