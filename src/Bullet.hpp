//
//  Bullet.hpp
//  empty
//
//  Created by 坂井創一 on 2019/08/10.
//

#ifndef Bullet_hpp
#define Bullet_hpp

#include <stdio.h>
#include "GameInfo.h"
#include <Siv3D.hpp>
#include "Actor.hpp"

class Bullet:public Actor{
private:
    Vec2 pos;
    Effect effect;
public:
    static constexpr double speed = 480.0;
    Vec2 m_ballVelocity = Vec2(0, -speed);
    Circle m_ball = Circle(pos.x,pos.y,2);
    
    Bullet(Game* m_game,double x,double y):Actor(m_game),pos(Vec2(x,y)){
    }
    bool collision(Rect& c){
        return m_ball.intersects(c);
    }
    
    void update(int32& HP);
    
    void draw() const{
        
        m_ball.draw();
        effect.update();
    };
    
};

#endif /* Bullet_hpp */
