//
//  Player.cpp
//  empty
//
//  Created by 坂井創一 on 2019/08/10.
//

#include "Player.hpp"
#include "Game.hpp"
void Player::shot_bullet(){
GetGame()->make_bullet(center().x,center().y); 
}

void Player::handle_input(){
    float d_time = Scene::DeltaTime();
    //いずれ状態遷移を表で書き直す
    //攻撃ボタン
    if(KeyC.pressed()){
        shot_bullet();
    }
    
    //ジャンプボタン
    if(KeyX.pressed()&&p_st!=State::Jump){
        p_st = State::Jump;
        frame = 0;
        effect.add<Burn>(Vec2(pos.x+size.x/2,pos.y+size.y));
        velocity.y = -jump_power;
        pos.y -= 1;
    }
    
    //移動ボタン+Zダッシュ
    State before_st = p_st;
    switch(p_st){
        case Idle:
            if(velocity.x > 15*d_time) velocity.x -=30*d_time;
            else if(velocity.x < -15*d_time) velocity.x +=30*d_time;
            else velocity.x = 0;
            if(KeyLeft.pressed()){
                if(facing_left){
                    p_st = State::Walk;
                }else{
                    facing_left = !facing_left;
                    pos.x -=10;
                }
            }else if(KeyRight.pressed()){
                if(!facing_left){
                    p_st = State::Walk;
                }else{
                    facing_left = !facing_left;
                    pos.x +=10;
                }
            }
            break;
        case Walk:
            if(KeyLeft.pressed()){
                if(facing_left){
                    if(KeyZ.pressed()){
                        p_st = State::Run;
                        velocity.x = std::max<double>(-walkspeed_limit,velocity.x-walkspeed*d_time);
                    }else{
                        velocity.x = std::max<double>(-walkspeed_limit,velocity.x-walkspeed*d_time);
                    }
                }else{
                    p_st = State::Idle;
                    facing_left = !facing_left;
                }
            }else
                if(KeyRight.pressed()){
                    if(!facing_left){
                        if(KeyZ.pressed()){
                            p_st = State::Run;
                            velocity.x = std::min<double>(walkspeed_limit,velocity.x+walkspeed*d_time);
                        }else{
                            velocity.x =
                            std::min<double>(walkspeed_limit,velocity.x+walkspeed*d_time);
                        }
                    }else{
                        p_st = State::Idle;
                        facing_left = !facing_left;
                    }
                }else{
                    p_st = State::Idle;
                }
            break;
        case Run:
            if(KeyLeft.pressed()){
                if(facing_left){
                    velocity.x = std::max<double>(-Runspeed_limit,velocity.x-20*d_time);
                    if(!KeyZ.pressed()){
                       p_st = State::Walk;
                    }
                }else{
                    p_st = State::Idle;
                    facing_left = !facing_left;
                }
            }else if(KeyRight.pressed()){
                if(!facing_left){
                    if(KeyZ.pressed()){
                        velocity.x = std::min<double>(Runspeed_limit,velocity.x+20*d_time);
                    }else{
                        p_st = State::Walk;
                        velocity.x = std::min<double>(Runspeed_limit,velocity.x+20*d_time);
                    }
                }else{
                    p_st = State::Idle;
                    facing_left = !facing_left;
                }
            }else{
                p_st = State::Idle;
            }
            break;
        case Jump:
            if(velocity.x > 0) velocity.x -=3*d_time;
            if(velocity.x < 0) velocity.x +=3*d_time;
            velocity.y+=20*d_time;
            if(pos.y>=500) {
                pos.y = 500;
                velocity.y = 0;
                p_st = State::Idle;
            }
            if(KeyLeft.pressed()){
                if(facing_left){
                    if(velocity.x > -5) velocity.x-= 1 * d_time;
                        else velocity.x = -5;
                            }else{
                                facing_left = !facing_left;
                            }
            }else if(KeyRight.pressed()){
                if(!facing_left){
                    if(velocity.x < 5) velocity.x += 1 * d_time;
                        else velocity.x = 5;
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
    //もし前の状態と違うなら初期化
    if(p_st != before_st){
        frame = 0;
    }
    
}

const void Player::draw() const{
    switch(p_st){
        case Idle:
            texture_idle(72*(anime_idle[(frame/10) % anime_idle.size()]),0,72,72).mirrored(facing_left).draw(pos.x,pos.y);
            break;
        case Walk:
            texture_walk(72*(anime_walk[(frame/6) % anime_walk.size()]),0,72,72).mirrored(facing_left).draw(pos.x,pos.y);
            break;
        case Turn:
            texture_turn(72*(anime_turn[(frame/6) % anime_turn.size()]),0,72,72).mirrored(facing_left).draw(pos.x,pos.y);
            break;
        case Run:
            texture_run(72*(anime_run[(frame/4) % anime_run.size()]),0,72,72).mirrored(facing_left).draw(pos.x,pos.y);
            break;
        case Jump:
            if(velocity.y<-2)  texture_jump(72*(anime_jump_up[(frame/6) % anime_jump_up.size()]),0,72,72).mirrored(facing_left).draw(pos.x,pos.y);
            else if(velocity.y>=2) texture_jump(72*(anime_jump_fall[(frame/6) % anime_jump_fall.size()]),0,72,72).mirrored(facing_left).draw(pos.x,pos.y);
            else texture_jump(72*(anime_jump_mid[(frame/6) % anime_jump_mid.size()]),0,72,72).mirrored(facing_left).draw(pos.x,pos.y);
            break;
    }
    
    effect.update();
    HitBox.drawFrame();
};

void Player::update(){
    // 移動
    pos += velocity;
    
    
    if(velocity.x > 0){
        //右との衝突
        if(pos.x+size.x>Scene::Width()){
            velocity.x = 0;
            pos.x = Scene::Width()-size.x;
        }
    }else{
        //左との衝突
        if(pos.x < 0){
            velocity.x = 0;
            pos.x = 0;
        }
    }
    if(velocity.y > 0){
        //上との衝突
    }else{
        //下との衝突
    }
    
    handle_input();
    frame+=1;
    
    
    
    HitBox = Rect(pos.x+HitBox_size.x,pos.y+HitBox_size.y/2, HitBox_size.x,HitBox_size.y);
        
    
}
