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
    s3d::Vec2 size = Vec2(72,72);
    Vec2 HitBox_size = Vec2(20,40);
    Vec2 velocity = Vec2(0,0);
    Rect HitBox;
    Texture texture_walk;
    Texture texture_idle;
    Texture texture_run;
    Texture texture_jump;
    Texture texture_turn;
    Texture texture_positive;
    bool facing_left = false;
    int frame = 0;
    Array<int> anime_walk = {0,1,2,3,4,5,6,8,10,11,12,13};
    Array<int> anime_idle = {0,1,2,3};
    Array<int> anime_turn = {0,1,2};
    Array<int> anime_run = {0,1,2,3,4,5,6,8,10,11,12,13};
    Array<int> anime_jump_up = {0,1};
    Array<int> anime_jump_fall = {5,6};
    Array<int> anime_jump_mid = {2,3,4};
    Array<int> anime_positive = {0,1,2,3,4,5};
    enum State{
        Idle,
        Walk,
        Run,
        Jump,
        Turn,
        Hooking,
        Dead,
        Clear
    };
    State p_st = State::Idle;
    const double hookspeed = 3.0; //フックアクションの動作速度
    double hooktime;
    bool can_hook;//フックアクションできる状態か
    
    bool hook_flag;//フックアクション中かどうか
    void shot_hook();
    void shot_bullet();
    bool can_shoot_hook =false;
    Audio jump_se;
    Audio landing_se;
    Audio hook_se;
    Audio gameover_se;
public:
    void GameOver();
    void GameClear();
    s3d::Vec2 pos = Vec2(100,100);
    Player(Game* m_game,Vec2 pos):Actor(m_game),pos(pos){
        texture_walk = Texture(U"Image/Unitychan/Unitychan_Walk.png");
        texture_idle = Texture(U"Image/Unitychan/Unitychan_Idle.png");
        texture_turn = Texture(U"Image/Unitychan/Unitychan_Turn.png");
        texture_run = Texture(U"Image/Unitychan/Unitychan_Run.png");
        texture_jump = Texture(U"Image/Unitychan/Unitychan_Jump.png");
        texture_positive = Texture(U"Image/Unitychan/Unitychan_Positive.png");
        jump_se = Audio(U"Sound/jump.wav");
        landing_se = Audio(U"Sound/landing.wav");
        hook_se = Audio(U"Sound/hook.wav");
        
        gameover_se = Audio(U"Sound/gameover.wav");
    }
    bool collision(Circle& c){
        return HitBox.intersects(c);
    }
    Vec2 center(){
        if(facing_left) return Vec2(pos.x-110.0,pos.y-32.0);
        else return Vec2(pos.x+172.0,pos.y-32.0);
    }
    bool hooked(Vec2 to_pos);
    
    void update();
    void handle_input();
    
    //メンバ関数の右側にconstをつけると、そのメンバ関数内ではメンバ変数の変更ができなくなる
    const void draw() const;
    void HitCheck();
    
};

#endif /* Player_hpp */
