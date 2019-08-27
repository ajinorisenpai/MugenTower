//
//  Player.cpp
//  empty
//
//  Created by 坂井創一 on 2019/08/10.
//

#include <algorithm>
#include "Player.hpp"
#include "Game.hpp"
void Player::shot_bullet(){
GetGame()->make_bullet(center().x,center().y); 
}

void Player::handle_input(){
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
                            pos.x -=10;
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
                                pos.x +=10;
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
                        velocity.x = std::max<double>(-walkspeed_limit,velocity.x-1);
                    }else{
                        velocity.x = std::max<double>(-walkspeed_limit,velocity.x-1);
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

const void Player::draw() const{
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
//    HitBox.drawFrame();
};
