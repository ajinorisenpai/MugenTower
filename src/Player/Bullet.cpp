#include "Bullet.hpp"
#include "Game.hpp"
#include <Siv3D.hpp>
#include "Burn.hpp"
void Bullet::update(int32& HP){
    
    
    pos.moveBy(m_ballVelocity * Scene::DeltaTime());
    m_ball = Circle(pos.x,pos.y,4);
    
    if(abs(pos.x - GetGame()->GetPlayer().GetPos().x) >1000){
        
        mState = State::Dead;
    }
    
    for(auto it = GetGame()->GetEnemy().begin();it!=GetGame()->GetEnemy().end();++it){
        if (it->collision(m_ball))
        {
            effect.add<Burn>(pos);
            (it->rect.bottom().intersects(m_ball) || it->rect.top().intersects(m_ball) ? m_ballVelocity.y : m_ballVelocity.x) *= -1;
            

            GetGame()->GetEnemy().erase(it);
            
            break;
        }
    }
}
