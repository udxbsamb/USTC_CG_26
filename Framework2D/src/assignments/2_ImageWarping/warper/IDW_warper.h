// HW2_TODO: Implement the IDWWarper class
#pragma once

#include "warper.h"
#include "common/image_widget.h"
namespace USTC_CG
{
class IDWWarper : public Warper
{
   public:
    IDWWarper() = default;
    virtual ~IDWWarper() = default;
    std::pair<int, int> warp(const int x,const int y); 
    void get_points(std::vector<ImVec2>& start_points, std::vector<ImVec2>& end_points); 
    void determine_coefficients() ;
    // HW2_TODO: Implement the warp(...) function with IDW interpolation
    private:
    std::vector<ImVec2> start_points_, end_points_;//store the selected points for interpolation

    // HW2_TODO: other functions or variables if you need
};
}  // namespace USTC_CG