//
//  Actor.cpp
//  empty
//
//  Created by 坂井創一 on 2019/08/10.
//

#include "Actor.hpp"
#include "Game.hpp"

Actor::Actor(Game* m_game):mState(State::Active),m_game(m_game){
    
}
