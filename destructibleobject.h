#ifndef DESTRUCTIBLEOBJECT_H
#define DESTRUCTIBLEOBJECT_H

#include "gameobject.hpp"

#include <list>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>

using namespace boost::geometry;

class DestructibleObject : public GameObject
{    
public:
    DestructibleObject(b2World* world, SDL_Renderer* renderer, float x, float y);

    void destroy(float x, float y, float r);
    void handleEvent(const SDL_Event& event);
};

#endif // DESTRUCTIBLEOBJECT_H
