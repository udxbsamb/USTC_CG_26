// HW2_TODO: Please implement the abstract class Warper
// 1. The Warper class should abstract the **mathematical mapping** involved in
// the warping problem, **independent of image**.
// 2. The Warper class should have a virtual function warp(...) to be called in
// our image warping application.
//    - You should design the inputs and outputs of warp(...) according to the
//    mathematical abstraction discussed in class.
//    - Generally, the warping map should map one input point to another place.
// 3. Subclasses of Warper, IDWWarper and RBFWarper, should implement the
// warp(...) function to perform the actual warping.
#pragma once
#include "common/image_widget.h"//for ImVec2,vector,pair,etc.
namespace USTC_CG
{
class Warper
{
   public:
    virtual ~Warper() = default;
    virtual std::pair<int, int> warp(const int x,const int y) = 0; 
    virtual void get_points(std::vector<ImVec2>& start_points, std::vector<ImVec2>& end_points) = 0; //use the selected points to determine the coefficients for interpolation
    virtual void determine_coefficients() = 0;
    // HW2_TODO: A virtual function warp(...)
    
    // HW2_TODO: other functions or variables if you need
};
}  // namespace USTC_CG