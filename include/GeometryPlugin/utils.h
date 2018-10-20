#ifndef GEOM_UTILS_H_INCLUDED
#define GEOM_UTILS_H_INCLUDED

#include <glm/glm.hpp>

enum class Orientation {
    CW = -1, COLLINEAR = 0, CCW = 1,
};

namespace Point {
    float cross(const glm::vec2 &a, const glm::vec2 &b, const glm::vec2 &c);
    Orientation getOrientation(const glm::vec2& a,
                                      const glm::vec2& b,
                                      const glm::vec2& c);
    bool pointTriangleTest(const glm::vec2& a,
                           const glm::vec2& b,
                           const glm::vec2& c,
                           const glm::vec2& p);
}

bool approxEq(float a, float b, float EPS = 1e-6f);

#endif // GEOM_UTILS_H_INCLUDED
