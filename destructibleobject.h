#ifndef DESTRUCTIBLEOBJECT_H
#define DESTRUCTIBLEOBJECT_H

#include "gameobject.hpp"

#include <vector>
#include <list>
#include <stack>
#include <opencv2/opencv.hpp>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>

using namespace boost::geometry;

class DestructibleObject : public GameObject
{
    std::stack<b2Vec2> _destructions;
    b2FixtureDef _fixtureDef;

public:
    DestructibleObject(b2World* world, SDL_Renderer* renderer, float x, float y, const std::vector<cv::Point>& points);
    ~DestructibleObject();

    void update();

    void pushDestroy(float x, float y, float r);
    void destroy(float x, float y, float r);
    void handleEvent(const SDL_Event& event);
};

#endif // DESTRUCTIBLEOBJECT_H
