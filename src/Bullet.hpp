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

class Bullet{
private:
    s3d::Vec2 pos = Vec2(400,400);
    
public:
    static constexpr double speed = 480.0;
    Vec2 m_ballVelocity = Vec2(0, -speed);
    Circle m_ball = Circle(pos.x,pos.y,8);
    Bullet(double x,double y){
        pos.x = x;
        pos.y = y;
    }
    bool collision(Rect& c){
        return m_ball.intersects(c);
    }
    
    void update(int32& HP){
        // ボールを移動
        m_ball.moveBy(m_ballVelocity * Scene::DeltaTime());
        // 天井にぶつかったらはね返る
        if (m_ball.y < 0 && m_ballVelocity.y < 0)
        {
            m_ballVelocity.y *= -1;
        }
        // 左右の壁にぶつかったらはね返る
        if ((m_ball.x < 0 && m_ballVelocity.x < 0) ||
            (Scene::Width() < m_ball.x && m_ballVelocity.x > 0))
        {
            m_ballVelocity.x *= -1;
        }
        if (m_ball.y > Scene::Height())
        {
            HP-=1;
        }
    }
    
    void draw() const{
        m_ball.draw();
    };
    
};

#endif /* Bullet_hpp */
