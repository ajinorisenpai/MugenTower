#include "Hook.hpp"
#include "Game.hpp"
#include "Burn.hpp"
void Hook::update(){
    if(mState!= State::Dead){
        if(hooked){
            if(!once_hooked){
                length += HOOK_TIME;
                once_hooked=true;
            }
            GetGame()->GetPlayer().hooked(pos);
        }else{
            auto checkMapData = [this](const Vec2 po)->int{
                if(pos.x<0 || pos.y<0 || pos.x > 300*64 || pos.y > 300*64 ) return 0;
                return GetGame()->GetMapData()[(int)po.x/64][(int)po.y/64];
            };
            if(checkMapData(pos) & 2){
                effect.add<Burn>(pos);
                length = 0.0;
            }else if(checkMapData(pos) & 1) {
                effect.add<Burn>(pos);
                hooked= true;
            }else{
                pos += Scene::DeltaTime()*Velocity;
            }
            
        }
        s_pos = GetGame()->GetPlayer().GetPos();
        s_pos.x +=32.0;
        s_pos.y += 20.0;
        length-=Scene::DeltaTime()*50.0;
        if(length<0.0){
            mState = State::Dead;
            once_hooked=false;
        }
    }
}
void Hook::draw() const {
    if(mState!= State::Dead){
        Circle(pos.x,pos.y,5).draw();
        
        Line(s_pos,pos).draw(1,Palette::White);
        
    }
    effect.update();
};
