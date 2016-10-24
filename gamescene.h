#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "scene.h"

#include <Box2D/Box2D.h>

class GameScene : public Scene
{

    b2Vec2 _gravity;
    b2World _world;

public:
    GameScene(const SDL_Rect& viewPort);

    virtual void draw(SDL_Renderer* renderer) const;
    virtual void update(float deltaTime);
    virtual void handleEvent(const SDL_Event& event);

    void createGround(float X, float Y);
    void createBox(int X, int Y);



};

#endif // GAMESCENE_H
