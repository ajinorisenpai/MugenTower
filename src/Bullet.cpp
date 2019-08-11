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
//        HP-=1;
        mState = State::Dead;
    }
    
    if(m_ballVelocity.y > 0 && GetGame()->GetPlayer().collision(m_ball)){
        // パドルの中心からの距離に応じてはね返る向きを変える
        m_ballVelocity = Vec2((m_ball.x - GetGame()->GetPlayer().center().x) * 10, -m_ballVelocity.y).setLength(speed);
    }
    
    for(auto it = GetGame()->GetEnemy().begin();it!=GetGame()->GetEnemy().end();++it){
        // ボールとブロックが交差していたら
        if (it->collision(m_ball))
        {
            // ボールの向きを反転する
            (it->rect.bottom().intersects(m_ball) || it->rect.top().intersects(m_ball) ? m_ballVelocity.y : m_ballVelocity.x) *= -1;
            
            // スコアを加算
            GetGame()->m_score++;
            
            // ブロックを配列から削除（イテレータが無効になるので注意）
            GetGame()->GetEnemy().erase(it);
            
            
            // これ以上チェックしない
            break;
        }
        
    }
}
