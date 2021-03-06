#ifndef SCENECONTACTLISTENER_H
#define SCENECONTACTLISTENER_H

#include <Box2D/Box2D.h>

class ContactListener : public b2ContactListener
{
public:
    ContactListener();

    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);
};

#endif // SCENECONTACTLISTENER_H
