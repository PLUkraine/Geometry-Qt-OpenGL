#include "GeometryPlugin/utils.h"

namespace Point {
    Orientation getOrientation(const glm::vec2 &a, const glm::vec2 &b, const glm::vec2 &c)
    {
        float crossRes = cross(a, b, c);
        if (approxEq(crossRes, 0.0f)) return Orientation::COLLINEAR;
        else if (crossRes > 0.0f) return Orientation::CCW;
        else return Orientation::CW;
    }

    bool pointTriangleTest(const glm::vec2 &a, const glm::vec2 &b, const glm::vec2 &c, const glm::vec2 &p)
    {
        bool b1 = cross(p, a, b) < 0.0f;
        bool b2 = cross(p, b, c) < 0.0f;
        bool b3 = cross(p, c, a) < 0.0f;

        return (b1 == b2) && (b2 == b3);
    }

    float cross(const glm::vec2 &a, const glm::vec2 &b, const glm::vec2 &c)
    {
        return glm::determinant(glm::mat2(b - a, c - a));
    }


}


bool approxEq(float a, float b, float EPS) {
    return fabsf(a - b) < EPS;
}
