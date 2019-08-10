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
class Game;

class Bullet{
private:
    s3d::Vec2 pos = Vec2(400,400);
    class Game* m_Game;
public:
    static constexpr double speed = 480.0;
    Vec2 m_ballVelocity = Vec2(0, -speed);
    Circle m_ball = Circle(pos.x,pos.y,8);
    Game* GetGame(){
        return m_Game;
    }
    Bullet(Game* m_Game,double x,double y):
    m_Game(m_Game){
        pos.x = x;
        pos.y = y;
    }
    bool collision(Rect& c){
        return m_ball.intersects(c);
    }
    
    void update(int32& HP);
    
    void draw() const{
        m_ball.draw();
    };
    
};

#endif /* Bullet_hpp */
