//
//  Player.cpp
//  empty
//
//  Created by 坂井創一 on 2019/08/10.
//

#include "Player.hpp"
#include "Game.hpp"
void Player::shot_bullet(){
GetGame()->make_bullet(center().x,center().y); 
}
