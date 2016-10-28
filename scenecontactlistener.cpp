#include "scenecontactlistener.h"

#include "gameobject.hpp"

SceneContactListener::SceneContactListener()
{

}

void SceneContactListener::BeginContact(b2Contact* contact)
{
    GameObject* gameObjectA = static_cast<GameObject*>(contact->GetFixtureA()->GetUserData());
    GameObject* gameObjectB = static_cast<GameObject*>(contact->GetFixtureB()->GetUserData());

    if (gameObjectA != NULL)
        gameObjectA->beginContactEvent(gameObjectB);
    if (gameObjectB != NULL)
        gameObjectB->beginContactEvent(gameObjectA);
}

void SceneContactListener::EndContact(b2Contact* contact)
{
    GameObject* gameObjectA = static_cast<GameObject*>(contact->GetFixtureA()->GetUserData());
    GameObject* gameObjectB = static_cast<GameObject*>(contact->GetFixtureB()->GetUserData());

    if (gameObjectA != NULL)
        gameObjectA->endContactEvent(gameObjectB);
    if (gameObjectB != NULL)
        gameObjectB->endContactEvent(gameObjectA);
}
