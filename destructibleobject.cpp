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
    b2Vec2 points[8] = {
        {2*4, 2},
        {3*4, 0},
        {2*4, -1},
        {0*4, 0},
        {-2*4, -1},
        {-3*4, 0},
        {-2*4, 2},
        {0*4, 3}
    };
    //b2PolygonShape shape;
    b2ChainShape shape;
    //shape.CreateChain(points, 8);
    shape.CreateLoop(points, 8);

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
    x /= BOX2D_SCALE;
    y /= BOX2D_SCALE;

    b2Vec2 position = _body->GetPosition();

    // Create Circle Polygon
    std::vector<model::d2::point_xy<float>> circlePoints = {{1.0f + x, 1.0f + y},   {1.5f + x, 0.0f + y},
                                                            {1.0f + x, -1.0f + y},  {0.0f + x, -1.5f + y},
                                                            {-1.0f + x, -1.0f + y}, {-1.5f + x, 0.0f + y},
                                                            {-1.0f + x, 1.0f + y},  {0.0f + x, 1.5f + y}};
    model::polygon< model::d2::point_xy<float> > circlePolygon;
    append(circlePolygon, circlePoints);

    // Create Terrain Polygon
    b2Fixture* fixture = &(_body->GetFixtureList()[0]);
    b2ChainShape* shape = static_cast<b2ChainShape*>(fixture->GetShape());
    std::vector<model::d2::point_xy<float>> terrainPoints(shape->m_count);
    for (int i = 0; i < shape->m_count; ++i) {
            terrainPoints[i].x(shape->m_vertices[i].x + position.x);
            terrainPoints[i].y(shape->m_vertices[i].y + position.y);
    }
    model::polygon<model::d2::point_xy<float>> terrainPolygon;
    append(terrainPolygon, terrainPoints);


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
    for (auto& terrainFragment : collection) {
        b2ChainShape newShape;

        std::vector<model::d2::point_xy<float>>& outerPoints = terrainFragment.outer();
        b2Vec2* b2Vec2Points = new b2Vec2[outerPoints.size()];
        for (unsigned int i = 0; i < (outerPoints.size() - 1); ++i) {
            b2Vec2Points[i].x = outerPoints[i].x();
            b2Vec2Points[i].y = outerPoints[i].y();
            std::cout << "x=" << b2Vec2Points[i].x << " " << "y=" << b2Vec2Points[i].y << std::endl;
        }
        newShape.CreateLoop(b2Vec2Points, outerPoints.size());

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
        //destroy(x, y, 1.0f);
    }
}
