#include "contactlistener.h"

#include "gameobject.h"

ContactListener::ContactListener()
{

}

void ContactListener::BeginContact(b2Contact* contact)
{
    GameObject* gameObjectA = static_cast<GameObject*>(contact->GetFixtureA()->GetUserData());
    GameObject* gameObjectB = static_cast<GameObject*>(contact->GetFixtureB()->GetUserData());

    if (gameObjectA != NULL)
        gameObjectA->beginContactEvent(gameObjectB);
    if (gameObjectB != NULL)
        gameObjectB->beginContactEvent(gameObjectA);
}

void ContactListener::EndContact(b2Contact* contact)
{
    GameObject* gameObjectA = static_cast<GameObject*>(contact->GetFixtureA()->GetUserData());
    GameObject* gameObjectB = static_cast<GameObject*>(contact->GetFixtureB()->GetUserData());

    if (gameObjectA != NULL)
        gameObjectA->endContactEvent(gameObjectB);
    if (gameObjectB != NULL)
        gameObjectB->endContactEvent(gameObjectA);
}
