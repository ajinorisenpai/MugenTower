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

class Player{
private:
    
public:
    Rect rect = Rect(Arg::center(Cursor::Pos().x, 500), 60, 10);
    Player(){
    }
    bool collision(Circle& c){
        return rect.intersects(c);
    }
    
    void update(){
        rect = Rect(Arg::center(Cursor::Pos().x, 500), 60, 10);
    }
    
    //メンバ関数の右側にconstをつけると、そのメンバ関数内ではメンバ変数の変更ができなくなる
    void draw() const{
        rect.draw();
    };
    
};

#endif /* Player_hpp */
