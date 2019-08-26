//
//  Bullet.cpp
//  empty
//
//  Created by 坂井創一 on 2019/08/10.
//

#include "Bullet.hpp"
#include "Game.hpp"
#include <Siv3D.hpp>
#include "Burn.hpp"
void Bullet::update(int32& HP){
    // ボールを移動
    
    
    pos.moveBy(m_ballVelocity * Scene::DeltaTime());
    m_ball = Circle(pos.x,pos.y,4);
    // 天井にぶつかったらはね返る
    if (pos.y < 0 && m_ballVelocity.y < 0)
    {
        effect.add<Burn>(pos);
        m_ballVelocity.y *= -1;
    }
    // 左右の壁にぶつかったらはね返る
    if ((pos.x < 0 && m_ballVelocity.x < 0) ||
        (Scene::Width() < pos.x && m_ballVelocity.x > 0))
    {
        effect.add<Burn>(pos);
        m_ballVelocity.x *= -1;
    }
    if (pos.y > Scene::Height())
    {
        HP-=1;
        mState = State::Dead;
    }
    
    if(m_ballVelocity.y > 0 && GetGame()->GetPlayer().collision(m_ball)){
        // パドルの中心からの距離に応じてはね返る向きを変える
        effect.add<Burn>(pos);
        m_ballVelocity = Vec2((pos.x - GetGame()->GetPlayer().center().x) * 10, -m_ballVelocity.y).setLength(speed);
    }
    
    for(auto it = GetGame()->GetEnemy().begin();it!=GetGame()->GetEnemy().end();++it){
        // ボールとブロックが交差していたら
        if (it->collision(m_ball))
        {
            effect.add<Burn>(pos);
            // ボールの向きを反転する
            (it->rect.bottom().intersects(m_ball) || it->rect.top().intersects(m_ball) ? m_ballVelocity.y : m_ballVelocity.x) *= -1;
            
            // スコアを加算
            GetGame()->m_score++;
            
            // ブロックを配列から削除
            GetGame()->GetEnemy().erase(it);
            
            // これ以上チェックしない
            break;
        }
    }
    effect.update();
}
