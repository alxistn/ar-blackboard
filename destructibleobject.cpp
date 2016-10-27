#include "destructibleobject.h"
#include <iostream>


DestructibleObject::DestructibleObject(b2World* world, SDL_Renderer* renderer, float x, float y)
    : GameObject(world, renderer)
{
    x /= BOX2D_SCALE;
    y /= BOX2D_SCALE;

    // Creation of the body
    b2BodyDef bodyDef;
    bodyDef.position = b2Vec2(x, y);
    bodyDef.type = b2_staticBody;
    _body = _world->CreateBody(&bodyDef);

    // Definition of the ape
    b2Vec2 points[9] = {
        {2*4, 2},
        {3*4, 0},
        {2*4, -1},
        {0*4, 0},
        {-2*4, -1},
        {-3*4, 0},
        {-2*4, 2},
        {0*4, 3},
        {2*4, 2}
    };
    //b2PolygonShape shape;
    b2ChainShape shape;
    //shape.CreateChain(points, 8);
    shape.CreateChain(points, 9);

    // Create body fixture
    _fixtureDef.shape = &shape;
    _fixtureDef.density = 0.0f;
    _fixtureDef.friction = 0.75f;
    _fixtureDef.restitution = 0.0f;
    _body->CreateFixture(&_fixtureDef);
}

void DestructibleObject::destroy(float x, float y, float r)
{
    static const float minDistSquare = 0.01f * 0.01f;

    std::cout << "------ DestructibleObject::destroy() ------" << std::endl;

    r /= BOX2D_SCALE * 2.0f;
    x /= BOX2D_SCALE;
    y /= BOX2D_SCALE;


    /*
    ** Create Circle Polygon
    */
    model::d2::point_xy<float>                      circlePosition(x, y);
    /*DEBUG*/ std::cout << "circle position = " << "x:" << circlePosition.x() << " y:" << circlePosition.y() << std::endl;
    std::vector<model::d2::point_xy<float>>         circlePoints = {{1.0f + circlePosition.x(), 1.0f + circlePosition.y()}, {1.5f + circlePosition.x(), 0.0f + circlePosition.y()}, {1.0f + circlePosition.x(), -1.0f + circlePosition.y()}, {0.0f + circlePosition.x(), -1.5f + circlePosition.y()}, {-1.0f + circlePosition.x(), -1.0f + circlePosition.y()}, {-1.5f + circlePosition.x(), 0.0f + circlePosition.y()},{-1.0f + circlePosition.x(), 1.0f + circlePosition.y()}, {0.0f + circlePosition.x(), 1.5f + circlePosition.y()}, {1.0f + circlePosition.x(), 1.0f + circlePosition.y()}};
    model::polygon<model::d2::point_xy<float>>      circlePolygon;
    append(circlePolygon, circlePoints);


    /*
    ** Create Terrain Polygon
    */
    b2Vec2                                          terrainPosition = _body->GetPosition();
    /*DEBUG*/ std::cout << "terrain position = " << "x:" << terrainPosition.x << " y:" << terrainPosition.y << std::endl;
    b2Fixture*                                      terrainFixture = &(_body->GetFixtureList()[0]);
    b2ChainShape*                                   terrainShape = static_cast<b2ChainShape*>(terrainFixture->GetShape());
    std::vector<model::d2::point_xy<float>>         terrainPoints(terrainShape->m_count);
    for (unsigned int i = 0; i < terrainPoints.size(); ++i) {
            terrainPoints[i].x(terrainShape->m_vertices[i].x + terrainPosition.x);
            terrainPoints[i].y(terrainShape->m_vertices[i].y + terrainPosition.y);
            std::cout << "before x=" << terrainShape->m_vertices[i].x << " " << "y=" << terrainShape->m_vertices[i].y << std::endl;
    }
    model::polygon<model::d2::point_xy<float>>      terrainPolygon;
    append(terrainPolygon, terrainPoints);
    /*DEBUG*/ std::cout << "circle center is in terrian? " << std::boolalpha << within(circlePosition, terrainPolygon) << std::endl;



    /*
    ** Get Result Terrain Collection Polygons
    */
    std::vector<model::polygon<model::d2::point_xy<float>>> collection;
    difference(terrainPolygon, circlePolygon, collection);


    /*
    ** Remove terrain fixture
    */
    _body->DestroyFixture(terrainFixture);


    /*
    ** Create terrain fragment fixtures
    */
    for (model::polygon<model::d2::point_xy<float>>& fragmentPolygon : collection) {
        /*DEBUG*/ std::cout << "NEW FRAGMENT" << std::endl;
        b2ChainShape fragmentShape;

        std::vector<model::d2::point_xy<float>>& fragmentPoints = fragmentPolygon.outer();
        b2Vec2* fragmentB2Vec2s = new b2Vec2[fragmentPoints.size()];
        for (unsigned int i = 0; i < (fragmentPoints.size()); ++i) {
            fragmentB2Vec2s[i].x = fragmentPoints[i].x() - terrainPosition.x;
            fragmentB2Vec2s[i].y = fragmentPoints[i].y() - terrainPosition.y;
            /*DEBUG*/ std::cout << "after x=" << fragmentB2Vec2s[i].x << " " << "y=" << fragmentB2Vec2s[i].y << std::endl;
        }

        fragmentShape.CreateChain(fragmentB2Vec2s, fragmentPoints.size());
        _fixtureDef.shape = &fragmentShape;
        _body->CreateFixture(&_fixtureDef);

        delete fragmentB2Vec2s;
    }


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
