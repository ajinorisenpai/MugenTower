//
//  Bullet.cpp
//  empty
//
//  Created by 坂井創一 on 2019/08/10.
//

#include "Bullet.hpp"

#include "Game.hpp"

void Bullet::update(int32& HP){
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
    if(m_ballVelocity.y > 0 && GetGame()->GetPlayer().collision(m_ball)){
        // パドルの中心からの距離に応じてはね返る向きを変える
        m_ballVelocity = Vec2((m_ball.x - GetGame()->GetPlayer().center().x) * 10, -m_ballVelocity.y).setLength(speed);
    }
}
