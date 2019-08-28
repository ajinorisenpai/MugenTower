//
//  Hook.hpp
//  empty
//
//  Created by 坂井創一 on 2019/08/28.
//

#ifndef Hook_hpp
#define Hook_hpp

#include <stdio.h>
#include <Siv3D.hpp>
#include "Actor.hpp"

class Hook:public Actor{
private:
    Vec2 pos;
    Vec2 s_pos;
    Effect effect;
    double length = 40.0;
    static constexpr double speed = 480.0;
    Vec2 Velocity;
    bool hooked = false;
    bool once_hooked = false;
public:
//    Circle m_hook = ;
    
    Hook(Game* m_game,Vec2 pos,Vec2 dir):Actor(m_game),s_pos(pos),Velocity(dir){
        length = 0;
        mState = State::Dead;
        
    }
    void init(Vec2 tpos,Vec2 dir){
        s_pos = tpos;
        pos = tpos;
        Velocity = dir;
        length = 20.0;
        mState = State::Active;
        hooked = false;
        once_hooked = false;
    }
    
    void update();
    void draw() const;
    
};

#endif /* Hook_hpp */
