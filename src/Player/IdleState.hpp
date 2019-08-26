////
////  IdleState.hpp
////  empty
////
////  Created by 坂井創一 on 2019/08/26.
////
//
//#ifndef IdleState_hpp
//#define IdleState_hpp
//
//#include <stdio.h>
//#include <Player.hpp>
//class IdleState:public Player{
//private:
//    s3d::Vec2 pos = Vec2(500,500);
//    s3d::Vec2 size = Vec2(60,10);
//    Rect rect = Rect(pos.x-size.x/2,pos.y-size.y/2, size.x, size.y);
//public:
//    IdleState(Game* m_game):Player(m_game){}
//    bool collision(Circle& c){
//        return rect.intersects(c);
//    }
//    
//    s3d::Vec2 center(){
//        return rect.center();
//    }
//    
//    void update(){
//        rect = Rect(pos.x-size.x/2,pos.y-size.y/2, size.x, size.y);
//    }
//    
//    void move_left(){
//        pos.x -= 10;
//    }
//    void move_right(){
//        pos.x += 10;
//    }
//    void shot_bullet();
//    //メンバ関数の右側にconstをつけると、そのメンバ関数内ではメンバ変数の変更ができなくなる
//    void draw() const{
//        rect.draw();
//    };
//};
//#endif /* IdleState_hpp */