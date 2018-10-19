#include "GeometryPlugin/utils.h"

Orientation Point::getOrientation(const glm::vec2 &a, const glm::vec2 &b, const glm::vec2 &c)
{
    float cross = glm::determinant(glm::mat2(b - a, c - a));
    if (approxEq(cross, 0.0f)) return Orientation::COLLINEAR;
    else if (cross > 0.0f) return Orientation::CCW;
    else return Orientation::CW;
}

bool approxEq(float a, float b, float EPS) {
    return fabsf(a - b) < EPS;
}
