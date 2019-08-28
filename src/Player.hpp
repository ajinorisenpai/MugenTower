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
#include "Burn.hpp"

class Player:public Actor{
private:
    Effect effect;
    const int jump_power = 14;
    const int Runspeed_limit = 10;
    const int walkspeed_limit = 6;
    const int walkspeed = 20;
    s3d::Vec2 pos = Vec2(500,500);
    s3d::Vec2 size = Vec2(72,72);
    Vec2 HitBox_size = Vec2(20,40);
    Vec2 velocity = Vec2(0,0);
    Rect HitBox;
    Texture texture_walk;
    Texture texture_idle;
    Texture texture_run;
    Texture texture_jump;
    Texture texture_turn;
    bool facing_left = false;
    int frame = 0;
    Array<int> anime_walk = {0,1,2,3,4,5,6,8,10,11,12,13};
    Array<int> anime_idle = {0,1,2,3};
    Array<int> anime_turn = {0,1,2};
    Array<int> anime_run = {0,1,2,3,4,5,6,8,10,11,12,13};
    Array<int> anime_jump_up = {0,1};
    Array<int> anime_jump_fall = {5,6};
    Array<int> anime_jump_mid = {2,3,4};
    enum State{
        Idle,
        Walk,
        Run,
        Jump,
        Turn
    };
    State p_st = State::Idle;
public:
    Player(Game* m_game):Actor(m_game){
        texture_walk = Texture(U"Image/Unitychan/Unitychan_Walk.png");
        texture_idle = Texture(U"Image/Unitychan/Unitychan_Idle.png");
        texture_turn = Texture(U"Image/Unitychan/Unitychan_Turn.png");
        texture_run = Texture(U"Image/Unitychan/Unitychan_Run.png");
        texture_jump = Texture(U"Image/Unitychan/Unitychan_Jump.png");
    }
    bool collision(Circle& c){
        return HitBox.intersects(c);
    }
    Vec2 center(){
        return HitBox.center();
    }
    
    void update(){
        pos += velocity;
        handle_input();
        frame+=1;
        //壁との衝突
        if(pos.x<0){
            velocity.x = 0;
            pos.x = 0;
        }
        if(pos.x+size.x>Scene::Width()){
            velocity.x = 0;
            pos.x = Scene::Width()-size.x;
        }
        
        
        HitBox = Rect(pos.x+HitBox_size.x,pos.y+HitBox_size.y/2, HitBox_size.x,HitBox_size.y);
        
    }
    void handle_input();
    
    void shot_bullet();
    //メンバ関数の右側にconstをつけると、そのメンバ関数内ではメンバ変数の変更ができなくなる
    const void draw() const;
    
};

#endif /* Player_hpp */
