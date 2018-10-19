#ifndef GEOM_UTILS_H_INCLUDED
#define GEOM_UTILS_H_INCLUDED

#include <glm/glm.hpp>

enum class Orientation {
    CW, CCW, COLLINEAR
};

class Point {
    static Orientation getOrientation(const glm::vec2& a,
                                      const glm::vec2& b,
                                      const glm::vec2& c);
};

bool approxEq(float a, float b, float EPS = 1e-6f);

#endif // GEOM_UTILS_H_INCLUDED
