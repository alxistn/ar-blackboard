#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "scene.h"
#include <list>
#include <Box2D/Box2D.h>
#include <gameobject.hpp>


class GameScene : public Scene
{

    b2Vec2 _gravity;
    b2World _world;
    std::list<GameObject*> _gameObjects;

public:
    GameScene(Window& window);

    virtual void draw() const;
    virtual void update(float deltaTime);
    virtual void handleEvent(const SDL_Event& event);

    void createGround(float x, float y, float w, float h);
    void createBox(int x, int y, float w, float h);
    void createPlayer(int x, int y);

};

#endif // GAMESCENE_H
