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
    
    if(abs(pos.x - GetGame()->GetPlayer().pos.x) >1000){
        
        mState = State::Dead;
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
}
