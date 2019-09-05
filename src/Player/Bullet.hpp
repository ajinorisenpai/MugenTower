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
    Vec2 m_ballVelocity = Vec2(speed, Random<double>(-1.0,1.0));
    Circle m_ball = Circle(pos.x,pos.y,2);
    
    Bullet(Game* m_game,Vec2 pos,Vec2 dir):Actor(m_game),pos(pos),m_ballVelocity(dir){
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
