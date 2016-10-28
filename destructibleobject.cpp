#include "destructibleobject.h"
#include <iostream>
#include <stack>


DestructibleObject::DestructibleObject(b2World* world, SDL_Renderer* renderer, float x, float y, const std::vector<cv::Point>& points)
    : GameObject(world, renderer, Type::DESTRUCTIBLE)
{
    x /= BOX2D_SCALE;
    y /= BOX2D_SCALE;

    // Creation of the body
    b2BodyDef bodyDef;
    bodyDef.position = b2Vec2(x, y);
    bodyDef.type = b2_staticBody;
    _body = _world->CreateBody(&bodyDef);

    // Definition of the shape
    int b2Vec2Size = points.size() + 1;
    b2Vec2 *b2Vec2Points = new b2Vec2[b2Vec2Size];
    for (unsigned int i = 0; i < points.size(); ++i)
    {
        b2Vec2Points[i].x = points[i].x / BOX2D_SCALE;
        b2Vec2Points[i].y = points[i].y / BOX2D_SCALE;
    }
    b2Vec2Points[b2Vec2Size -1].x = points[0].x / BOX2D_SCALE;
    b2Vec2Points[b2Vec2Size -1].y = points[0].y / BOX2D_SCALE;
    //b2PolygonShape shape;
    b2ChainShape shape;
    //shape.CreateChain(points, 8);
    shape.CreateChain(b2Vec2Points, b2Vec2Size);

    // Create body fixture
    _fixtureDef.shape = &shape;
    _fixtureDef.density = 0.0f;
    _fixtureDef.friction = 0.75f;
    _fixtureDef.restitution = 0.0f;
    _fixtureDef.userData = this;
    _body->CreateFixture(&_fixtureDef);
}

DestructibleObject::~DestructibleObject()
{
    std::cout << "Destructible Object removed." << std::endl;
}

float distanceSquare(const model::d2::point_xy<float>& point1, const model::d2::point_xy<float>& point2)
{
    float dx = point2.x() - point1.x();
    float dy = point2.y() - point1.y();
    return dx*dx + dy*dy;
}

void DestructibleObject::update()
{
    b2Vec2 position;
    while (_destructions.size() > 0) {
        position = _destructions.top();
        _destructions.pop();
        destroy(position.x, position.y, 1.0f);
    }
}

void DestructibleObject::pushDestroy(float x, float y, float r)
{
    _destructions.push({x, y});
}

void DestructibleObject::destroy(float x, float y, float r)
{
    //std::cout << "Destroy: x=" << x << " y=" << y << std::endl;
    //static const float minDistSquare = 0.005f * 0.005f; //BOX2D MINIMUM
    static const float minDistSquare = 0.01f * 0.01f; // OPTIMISED MINIMUM


    r /= BOX2D_SCALE * 2.0f;
    x /= BOX2D_SCALE;
    y /= BOX2D_SCALE;


    /*
    ** Create Circle Polygon
    */
    model::d2::point_xy<float>                      circlePosition(x, y);
    std::vector<model::d2::point_xy<float>>         circlePoints = {{1.0f + circlePosition.x(), 1.0f + circlePosition.y()}, {1.5f + circlePosition.x(), 0.0f + circlePosition.y()},
                                                                    {1.0f + circlePosition.x(), -1.0f + circlePosition.y()}, {0.0f + circlePosition.x(), -1.5f + circlePosition.y()},
                                                                    {-1.0f + circlePosition.x(), -1.0f + circlePosition.y()}, {-1.5f + circlePosition.x(), 0.0f + circlePosition.y()},
                                                                    {-1.0f + circlePosition.x(), 1.0f + circlePosition.y()}, {0.0f + circlePosition.x(), 1.5f + circlePosition.y()},
                                                                    {1.0f + circlePosition.x(), 1.0f + circlePosition.y()}};
    model::polygon<model::d2::point_xy<float>>      circlePolygon;
    append(circlePolygon, circlePoints);


    //
    // Get all Terrain Fixtures to a stack
    //
    b2Vec2                                          terrainPosition = _body->GetPosition();
    b2Fixture*                                      terrainFixture = _body->GetFixtureList();
    std::stack<b2Fixture*>                          terrainFixtureStack;
    while (terrainFixture != NULL) {
        terrainFixtureStack.push(terrainFixture);
        terrainFixture = terrainFixture->GetNext();
    }


    //
    // Loop over all terrian fixtures from stack
    //
    int fixtureCount = 0;
    while (terrainFixtureStack.size() > 0) {
        terrainFixture = terrainFixtureStack.top();
        terrainFixtureStack.pop();
        //std::cout << "Terrain fixture loaded" << std::endl;


        //
        // Create Terrain Polygon
        //
        b2ChainShape*                                   terrainShape = static_cast<b2ChainShape*>(terrainFixture->GetShape());
        std::vector<model::d2::point_xy<float>>         terrainPoints(terrainShape->m_count);
        for (unsigned int i = 0; i < terrainPoints.size(); ++i) {
                terrainPoints[i].x(terrainShape->m_vertices[i].x + terrainPosition.x);
                terrainPoints[i].y(terrainShape->m_vertices[i].y + terrainPosition.y);
        }
        model::polygon<model::d2::point_xy<float>>      terrainPolygon;
        append(terrainPolygon, terrainPoints);
        //std::cout << "Circle center is in terrian? " << std::boolalpha << within(circlePosition, terrainPolygon) << std::endl;


        //
        // Get Result Terrain Collection Polygons
        //
        std::vector<model::polygon<model::d2::point_xy<float>>> collection;
        difference(terrainPolygon, circlePolygon, collection);


        //
        // Remove terrain fixture
        //
        _body->DestroyFixture(terrainFixture);


        //
        // Create terrain fragment fixtures
        //
        //std::cout << "collection size = " << collection.size() << std::endl;
        for (model::polygon<model::d2::point_xy<float>>& fragmentPolygon : collection) {


            //
            // From fragmentPoints create fragmentB2Vec2s necessary for the shape filtering points too close to each other
            //
            std::vector<model::d2::point_xy<float>>& fragmentPoints = fragmentPolygon.outer();
            b2Vec2* fragmentB2Vec2s = new b2Vec2[fragmentPoints.size()];
            unsigned int fragmentB2Vec2sCount = 0;
            unsigned int lastStoredFpi;
            for (unsigned int fpi = 0; fpi < fragmentPoints.size(); ++fpi) {
                if (fragmentB2Vec2sCount > 0 && distanceSquare(fragmentPoints[lastStoredFpi], fragmentPoints[fpi]) <= minDistSquare) {
                    //std::cout << "Point too close to last stored point : SKIPPED" << std::endl;
                    continue;
                }
                lastStoredFpi = fpi;
                fragmentB2Vec2s[fragmentB2Vec2sCount].x = fragmentPoints[fpi].x() - terrainPosition.x;
                fragmentB2Vec2s[fragmentB2Vec2sCount].y = fragmentPoints[fpi].y() - terrainPosition.y;
                ++fragmentB2Vec2sCount;
            }
            //The last point must be the same as the first point for the shape connection
            //If the filter above removed the last point it was because the previous was too close to the last and the previous must be removed instead
            //Therefore we make sure the last is the same as the first
            fragmentB2Vec2s[fragmentB2Vec2sCount - 1] = fragmentB2Vec2s[0];


            //
            // Create the new fixture and shape using the fragmentB2Vec2s on the condition that the shape is closed (at least a triangle therefore 4 point including the closing point)
            //
            if (fragmentB2Vec2sCount >= 4) {
                b2ChainShape fragmentShape;
                fragmentShape.CreateChain(fragmentB2Vec2s, fragmentB2Vec2sCount);
                _fixtureDef.shape = &fragmentShape;
                _body->CreateFixture(&_fixtureDef);
                fixtureCount += 1;
            }
            delete fragmentB2Vec2s;


        }
    }


    // If body has no more fixtures, make the scene delete it
    if (fixtureCount == 0)
        _toDelete = true;
}

void DestructibleObject::handleEvent(const SDL_Event& event)
{
    if (event.type == SDL_MOUSEBUTTONUP)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        destroy(x, y, 1.0f);
    }
}
