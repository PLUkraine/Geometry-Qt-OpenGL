#include "GeometryPlugin/polygon.h"

Polygon::Polygon()
{

}

void Polygon::addPoint(glm::vec2 point)
{
    m_points.push_back(point);
}
