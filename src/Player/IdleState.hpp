////
////  IdleState.hpp
////  empty
////
////  Created by 坂井創一 on 2019/08/26.
////
//
#ifndef IdleState_hpp
#define IdleState_hpp
#include "PlayerState.hpp"
#include <Siv3D.hpp>

class IdleState : public PlayerState{
    virtual IdleState* draw(){
        return this;
    }
    virtual IdleState* update(){
        if(KeyLeft.pressed()) move_left();
        if(KeyRight.pressed()) move_right();
//        if(KeySpace.pressed()) shot_bullet();
        
        return this;
    }
    void move_left(){
//        pos.x-=5;
    }
    void move_right(){
//        pos.x+=5;
    }
};
#endif /* IdleState_hpp */
