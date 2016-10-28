#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "scene.h"
#include <list>
#include <Box2D/Box2D.h>
#include <gameobject.hpp>
#include "player.h"
#include "scenecontactlistener.h"
#include <opencv2/opencv.hpp>

class GameScene : public Scene
{
    b2Vec2 _gravity;
    b2World _world;
    SceneContactListener _contactListener;

    std::list<GameObject*> _gameObjects;
    Player* _player = NULL;

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

    void        addShape(const std::vector<cv::Point>& shape);
    void        addShapes(const std::vector<std::vector<cv::Point>>& shapes);
};

#endif // GAMESCENE_H
