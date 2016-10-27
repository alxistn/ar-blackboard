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
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 0.0f;
    fixtureDef.friction = 0.75f;
    fixtureDef.restitution = 0.0f;
    _body->CreateFixture(&fixtureDef);
}

void DestructibleObject::destroy(float x, float y, float r)
{
    std::cout << "------ DestructibleObject::destroy() ------" << std::endl;

    r /= BOX2D_SCALE * 2.0f;
    x /= BOX2D_SCALE;
    y /= BOX2D_SCALE;

    // Create Circle Polygon
    model::d2::point_xy<float> circlePosition(x, y);
    std::vector<model::d2::point_xy<float>> circlePoints = {{1.0f + x, 1.0f + y},   {1.5f + x, 0.0f + y},
                                                            {1.0f + x, -1.0f + y},  {0.0f + x, -1.5f + y},
                                                            {-1.0f + x, -1.0f + y}, {-1.5f + x, 0.0f + y},
                                                            {-1.0f + x, 1.0f + y},  {0.0f + x, 1.5f + y},
                                                           {1.0f + x, 1.0f + y}};
    model::polygon<model::d2::point_xy<float>> circlePolygon;
    append(circlePolygon, circlePoints);

    // Create Terrain Polygon
    b2Vec2 terrainPosition = _body->GetPosition();
    b2Fixture* fixture = &(_body->GetFixtureList()[0]);
    b2ChainShape* shape = static_cast<b2ChainShape*>(fixture->GetShape());
    std::vector<model::d2::point_xy<float>> terrainPoints(shape->m_count);
    for (int i = 0; i < terrainPoints.size(); ++i) {
            terrainPoints[i].x(shape->m_vertices[i].x + terrainPosition.x);
            terrainPoints[i].y(shape->m_vertices[i].y + terrainPosition.y);
            std::cout << "before x=" << shape->m_vertices[i].x << " " << "y=" << shape->m_vertices[i].y << std::endl;
    }
    model::polygon<model::d2::point_xy<float>> terrainPolygon;
    append(terrainPolygon, terrainPoints);


    //DEBUG
    std::cout << "terrain position = " << "x:" << terrainPosition.x << " y:" << terrainPosition.y << std::endl;
    std::cout << "circle position = " << "x:" << circlePosition.x() << " y:" << circlePosition.y() << std::endl;
    std::cout << "circle center is in terrian? " << std::boolalpha << within(circlePosition, terrainPolygon) << std::endl;


    // Get Result Terrain Collection Polygons
    std::vector<model::polygon<model::d2::point_xy<float>>> collection;
    difference(terrainPolygon, circlePolygon, collection);

    // Remove existing fixtures
    _body->DestroyFixture(fixture);

    // Create new fixtures and shapes
    b2FixtureDef fixtureDef;
    fixtureDef.density = 0.0f;
    fixtureDef.friction = 0.75f;
    fixtureDef.restitution = 0.0f;
    for (model::polygon<model::d2::point_xy<float>>& terrainFragment : collection) {
        std::cout << "FRAGMENT" << std::endl;
        b2ChainShape newShape;

        std::vector<model::d2::point_xy<float>>& outerPoints = terrainFragment.outer();
        b2Vec2* b2Vec2Points = new b2Vec2[outerPoints.size()];
        for (unsigned int i = 0; i < (outerPoints.size()); ++i) {
            b2Vec2Points[i].x = outerPoints[i].x() - terrainPosition.x;
            b2Vec2Points[i].y = outerPoints[i].y() - terrainPosition.y;
            std::cout << "after x=" << b2Vec2Points[i].x << " " << "y=" << b2Vec2Points[i].y << std::endl;
        }

        /*b2Vec2 pointsTEST[8] = {
            {2*4, 2},
            {3*4, 0},
            {2*4, -1},
            {0*4, 0},
            {-2*4, -1},
            {-3*4, 0},
            {-2*4, 2},
            {0*4, 3}
        };*/

        newShape.CreateChain(b2Vec2Points, outerPoints.size());

        fixtureDef.shape = &newShape;
        _body->CreateFixture(&fixtureDef);

        delete b2Vec2Points;
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
