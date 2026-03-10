#include "IDW_warper.h"
#include "common/image_widget.h"
#include <cmath>
static double EPSILON = 1e-6;//to avoid division by zero in weight calculation
static double power = 2.0;//the power parameter for IDW interpolation. 
namespace USTC_CG
{
std::pair<int, int> IDWWarper::warp(const int x, const int y) {//using sigma = \frac{1}{||0-p_i||^power}
    std::vector<double> weights(start_points_.size(), 0.0);
    double weight_sum = 0.0;
    double xv = 0.0, yv = 0.0;
    double weight=0.0; 
    for (size_t i = 0; i < start_points_.size(); ++i) {
        weight = std::pow((x - start_points_[i].x) * (x - start_points_[i].x) + (y - start_points_[i].y) * (y - start_points_[i].y) + EPSILON, -power / 2.0);
        //if power is 2, then we can compute directly for better performance.
        weight_sum += weight;
        xv += weight * end_points_[i].x;
        yv += weight * end_points_[i].y;
    }
    xv /= weight_sum;
    yv /= weight_sum;

    return {static_cast<int>(xv), static_cast<int>(yv)};
}//to be added: degree 1.
void IDWWarper::get_points(std::vector<ImVec2> & start_points, std::vector<ImVec2> & end_points)
{
    start_points_ = start_points;
    end_points_ = end_points;
}//before using warp, use this to load the selected points
void IDWWarper::determine_coefficients(){
    
}
}