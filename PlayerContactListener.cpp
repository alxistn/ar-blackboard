//
//  PlayerContactListener.cpp
//  ar-blackboard
//
//  Created by Alexis Santini on 26/10/2016.
//  Copyright © 2016 ar-blackbord. All rights reserved.
//

#include "player.h"
#include "PlayerContactListener.hpp"

PlayerContactListener::PlayerContactListener(Player* player)
    : _player(player)
{}

void PlayerContactListener::BeginContact(b2Contact* contact)
{
        //check if fixture A was the foot sensor
        void* fixtureUserData = contact->GetFixtureA()->GetUserData();
        
        if ( *((int *)(&fixtureUserData)) == 3 )
        {
            _player->incrFootContacts();
        }
        
        //check if fixture B was the foot sensor
        fixtureUserData = contact->GetFixtureB()->GetUserData();
        if ( *((int *)(&fixtureUserData)) == 3 )
        {
            _player->incrFootContacts();
        }
}
    
void PlayerContactListener::EndContact(b2Contact* contact)
{
        //check if fixture A was the foot sensor
            void* fixtureUserData = contact->GetFixtureA()->GetUserData();
         if ( *((int *)(&fixtureUserData)) == 3 )
         {
             _player->decrFootContacts();
         }
        
         //check if fixture B was the foot sensor
         fixtureUserData = contact->GetFixtureB()->GetUserData();
         if ( *((int *)(&fixtureUserData)) == 3 )
         {
             _player->decrFootContacts();
         }
}
