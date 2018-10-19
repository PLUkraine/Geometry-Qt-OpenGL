#ifndef POLYGON_H_INCLUDED
#define POLYGON_H_INCLUDED

#include <vector>
#include <list>
#include <glm/glm.hpp>

/**
 * @brief The Polygon class
 * Represent polygon by points (clock-wise)
 */
class Polygon {
private:
    std::list<glm::vec2> m_points;

public:
    Polygon();
    ~Polygon();

    void addPoint(glm::vec2 point);
};

#endif // POLYGON_H_INCLUDED
