//
//  PlayerContactListener.hpp
//  ar-blackboard
//
//  Created by Alexis Santini on 26/10/2016.
//  Copyright © 2016 ar-blackbord. All rights reserved.
//

#ifndef PlayerContactListener_hpp
#define PlayerContactListener_hpp

#include <stdio.h>
#include <Box2D/Box2D.h>

class Player;

class PlayerContactListener : public b2ContactListener
{
private:
    Player*  _contactListenerPlayer;
    
public:
    PlayerContactListener(Player* player);
    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);
    
    void setPlayer(Player* player);

};


#endif /* PlayerContactListener_hpp */
