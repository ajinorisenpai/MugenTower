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
    const int jump_power = 20;
    const int Runspeed_limit = 10;
    const int walkspeed_limit = 6;
    s3d::Vec2 pos = Vec2(500,500);
    s3d::Vec2 size = Vec2(72,72);
    Vec2 velocity = Vec2(0,0);
    Rect HitBox = Rect(pos.x,pos.y, size.x, size.y);
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
    Array<int> anime_jump = {0,1};
    
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
    
    s3d::Vec2 center(){
        return HitBox.center();
    }
    
    void update(){
        pos += velocity;
        HitBox = Rect(pos.x,pos.y, size.x,size.y);
        handle_input();
        frame+=1;
        effect.update();
    }
    void handle_input(){
        
        //壁との衝突
        if(pos.x<0){
            velocity.x = 0;
            pos.x = 0;
        }
        if(pos.x+size.x>Scene::Width()){
            velocity.x = 0;
            pos.x = Scene::Width()-size.x;
        }
        
        //攻撃ボタン
        if(KeyC.pressed()){
            shot_bullet();
        }
        
        //ジャンプボタン
        if(KeyX.pressed()&&p_st!=State::Jump){
            p_st = State::Jump;
            effect.add<Burn>(Vec2(pos.x+size.x/2,pos.y+size.y));
            velocity.y = -jump_power;
            pos.y -= 1;
        }
        
        //移動ボタン+Zダッシュ
        switch(p_st){
            case Idle:
                if(velocity.x > 0) velocity.x -=1;
                if(velocity.x < 0) velocity.x +=1;
                if(KeyLeft.pressed()){
                    if(facing_left){
                        p_st = State::Walk;
                        frame = 0;
                    }else{
                        p_st = State::Idle;
                        facing_left = !facing_left;
                        frame = 0;
                    }
                }else
                if(KeyRight.pressed()){
                    if(!facing_left){
                        p_st = State::Walk;
                        frame = 0;
                    }else{
                        p_st = State::Idle;
                        facing_left = !facing_left;
                        frame = 0;
                    }
                }
                break;
            case Walk:
                if(KeyLeft.pressed()){
                    if(facing_left){
                        if(KeyZ.pressed()){
                            p_st = State::Run;
                            frame = 0;
                            if(velocity.x > -walkspeed_limit) velocity.x-=1;
                            else velocity.x = -walkspeed_limit;
                        }else{
                            if(velocity.x > -walkspeed_limit) velocity.x-=1;
                            else velocity.x = -walkspeed_limit;
                        }
                    }else{
                        p_st = State::Idle;
                        facing_left = !facing_left;
                        frame = 0;
                    }
                }else
                if(KeyRight.pressed()){
                    if(!facing_left){
                        if(KeyZ.pressed()){
                            p_st = State::Run;
                            frame = 0;
                            if(velocity.x < walkspeed_limit) velocity.x+=1;
                            else velocity.x = walkspeed_limit;
                        }else{
                           if(velocity.x < walkspeed_limit) velocity.x+=1;
                            else velocity.x = walkspeed_limit;
                        }
                    }else{
                        p_st = State::Idle;
                        facing_left = !facing_left;
                        frame = 0;
                    }
                }else{
                    p_st = State::Idle;
                }
                break;
            case Run:
                if(KeyLeft.pressed()){
                    if(facing_left){
                        if(KeyZ.pressed()){
                            if(velocity.x > -Runspeed_limit) velocity.x-=2;
                        }else{
                            p_st = State::Walk;
                            if(velocity.x > -Runspeed_limit) velocity.x-=2;
                        }
                    }else{
                        p_st = State::Idle;
                        facing_left = !facing_left;
                        frame = 0;
                    }
                }else
                    if(KeyRight.pressed()){
                        if(!facing_left){
                            if(KeyZ.pressed()){
                                if(velocity.x < Runspeed_limit) velocity.x+=2;
                            }else{
                                p_st = State::Walk;
                                if(velocity.x < Runspeed_limit) velocity.x+=2;
                            }
                        }else{
                            p_st = State::Idle;
                            facing_left = !facing_left;
                            frame = 0;
                        }
                    }else{
                        p_st = State::Idle;
                    }
                break;
            case Jump:
                velocity.y+=1;
                if(pos.y>=500) {
                    pos.y = 500;
                    velocity.y = 0;
                    p_st = State::Idle;
                }
                if(KeyLeft.pressed()){
                    if(facing_left){
                        if(velocity.x > -5) velocity.x-=1;
                        else velocity.x=-5;
                    }else{
                        facing_left = !facing_left;
                    }
                }else if(KeyRight.pressed()){
                    if(!facing_left){
                        if(velocity.x < 5) velocity.x+=1;
                        else velocity.x=5;
                    }else{
                        facing_left = !facing_left;
                    }
                }
                break;
            case Turn:
                if((frame/10) > anime_turn.size()-1){
                    p_st = State::Walk;
                    facing_left = !facing_left;
                }
                break;
        }
        
    }
    
    void shot_bullet();
    //メンバ関数の右側にconstをつけると、そのメンバ関数内ではメンバ変数の変更ができなくなる
    const void draw() const{
        switch(p_st){
            case Idle:
                texture_idle(72*(anime_idle[(frame/10) % anime_idle.size()]),0,72,72).mirrored(facing_left).draw(pos.x,pos.y);
                break;
            case Walk:
                texture_walk(72*(anime_walk[(frame/10) % anime_walk.size()]),0,72,72).mirrored(facing_left).draw(pos.x,pos.y);
                break;
            case Turn:
                texture_turn(72*(anime_turn[(frame/10) % anime_turn.size()]),0,72,72).mirrored(facing_left).draw(pos.x,pos.y);
                break;
            case Run:
                texture_run(72*(anime_run[(frame/6) % anime_run.size()]),0,72,72).mirrored(facing_left).draw(pos.x,pos.y);
                break;
            case Jump:
                texture_jump(72*(anime_jump[(frame/10) % anime_jump.size()]),0,72,72).mirrored(facing_left).draw(pos.x,pos.y);
                break;
        }
    };
    
};

#endif /* Player_hpp */
