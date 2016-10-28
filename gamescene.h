#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "scene.h"
#include "vertexextractor.h"
#include <list>
#include <Box2D/Box2D.h>
#include <gameobject.hpp>
#include "player.h"
#include "scenecontactlistener.h"

class GameScene : public Scene
{
    VertexExtractor *_vertexExtractor;
    b2Vec2 _gravity;
    b2World _world;
    SceneContactListener _contactListener;

    std::list<GameObject*> _gameObjects;
    Player* _player = NULL;

public:
    GameScene(Window& window, VertexExtractor *vertexExtractor);

    virtual void draw() const;
    virtual void update(float deltaTime);
    virtual void handleEvent(const SDL_Event& event);

    void createGround(float x, float y, float w, float h);
    void createBox(float x, float y, float w, float h);
    void createDestructibleObject(float x, float y, std::vector<cv::Point>& points);
    void createPlayer(float x, float y);

    void reset();
};

#endif // GAMESCENE_H
