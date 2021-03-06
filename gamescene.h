#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "scene.h"
#include <list>
#include <Box2D/Box2D.h>
#include "player.h"
#include "contactlistener.h"
#include <opencv2/opencv.hpp>

class GameObject;

class GameScene : public Scene
{
    //Distance off the screen a object can travel before being deleted
    static const int _worldBoundaryOffset = 100;

    b2Vec2 _gravity;
    b2World _world;
    ContactListener _contactListener;

    std::list<GameObject*> _gameObjects;

    bool    _drawStatic = true;

public:
    GameScene(Window& window, bool clean=true);
    ~GameScene();

    virtual void draw() const;
    virtual void update(float deltaTime);
    virtual void handleEvent(const SDL_Event& event);

    void clear();

    void createGround(float x, float y, float w, float h);
    void createBox(float x, float y, float w, float h);
    void createDestructibleObject(float x, float y, const std::vector<cv::Point>& points);
    void createPlayer(float x, float y);
    void createMissile(float x, float y, float a);
    void createBall(float x, float y);

    void        addShape(const std::vector<cv::Point>& shape);
    void        addShapes(const std::vector<std::vector<cv::Point>>& shapes);
};

#endif // GAMESCENE_H
