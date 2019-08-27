//
//  Player.hpp
//  empty
//
//  Created by 坂井創一 on 2019/08/10.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include "GameInfo.h"
#include <Siv3D.hpp>
#include "Actor.hpp"
#include "Player/PlayerState.hpp"
#include "Player/IdleState.hpp"
class Player:public Actor{
private:
    s3d::Vec2 pos = Vec2(500,500);
    s3d::Vec2 size = Vec2(60,10);
    Rect rect = Rect(pos.x-size.x/2,pos.y-size.y/2, size.x, size.y);
    Texture texture;
    int frame = 0;
    Array<int> anime = {0,1,2,3,4,5,6,8,10,11,12,13};
    PlayerState* playerState;
public:
    Player(Game* m_game):Actor(m_game){
        texture = Texture(U"Image/Unitychan/Unitychan_Walk.png");
        playerState = new IdleState();
    }
    bool collision(Circle& c){
        return rect.intersects(c);
        
    }
    
    s3d::Vec2 center(){
        return rect.center();
    }
    
    void update(){

        playerState->update();
    }
    
    void shot_bullet();
    //メンバ関数の右側にconstをつけると、そのメンバ関数内ではメンバ変数の変更ができなくなる
    const void draw() const{
        playerState->draw();
//        rect.draw();
        texture(72*(anime[(frame/10) % anime.size()]),0,72,72).draw(pos.x,pos.y);
    };
    
};

#endif /* Player_hpp */
