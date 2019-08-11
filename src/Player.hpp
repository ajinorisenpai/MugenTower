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

class Player:public Actor{
private:
    s3d::Vec2 pos = Vec2(500,500);
    Rect rect = Rect(pos.x,pos.y, 60, 10);
public:
    
    Player(){
    }
    bool collision(Circle& c){
        return rect.intersects(c);
    }
    
    s3d::Vec2 center(){
        return rect.center();
    }
    
    void update(){
        if(KeyLeft.pressed()) pos.x -= 10;
        if(KeyRight.pressed()) pos.x += 10;
        
        
        
        rect = Rect(pos.x,pos.y, 60, 10);
    }
    
    //メンバ関数の右側にconstをつけると、そのメンバ関数内ではメンバ変数の変更ができなくなる
    void draw() const{
        rect.draw();
    };
    
};

#endif /* Player_hpp */
