#include "Player.hpp"
#include "Game.hpp"
void Player::shot_bullet(){
    if(facing_left) GetGame()->make_bullet(Vec2(pos.x+30.0,pos.y+32.0),Vec2(-480.0,Random<double>(-100.0,100.0)));
    else GetGame()->make_bullet(Vec2(pos.x+50.0,pos.y+32.0),Vec2(480.0,Random<double>(-100.0,100.0)));

}
void Player::shot_hook(){
    hook_se.playOneShot(0.5);
    Vec2 dir;
    if(facing_left) dir = Vec2(-100.0*sin(hooktime+M_PI/2),100.0*cos(hooktime+M_PI/2));
    else dir = Vec2(100.0*sin(hooktime+M_PI/2),100.0*cos(hooktime+M_PI/2));;
    return GetGame()->make_hook(Vec2(pos.x+32.0,pos.y+30.0),dir*20);
}
void Player::handle_input(){
    
    if(p_st==Dead || p_st==Clear) return;
    float d_time = Scene::DeltaTime();
    //いずれ状態遷移を表で書き直す
//    攻撃ボタン
//    if(KeyC.pressed()){
//        shot_bullet();
//    }
    State before_st = p_st;
    
    
    //ジャンプボタン
    if(KeyX.pressed()&&p_st!=Jump){
        if(GetGame()->GetMapData()[(int)(pos.x+32.0)/64][(int)(pos.y+32.0)/64]==8){
            GameClear();
            return;
        }
        jump_se.playOneShot(0.2);
        p_st = State::Jump;
        frame = 0;
        effect.add<Burn>(Vec2(pos.x+size.x/2,pos.y+size.y));
        velocity.y = -jump_power;
        pos.y -= 1;
        can_hook = false;
    }
    
    
    
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
                }
            }else if(KeyRight.pressed()){
                if(!facing_left){
                    p_st = State::Walk;
                }else{
                    facing_left = !facing_left;
                }
            }
            break;
        case Walk:
            if(KeyLeft.pressed()){
                if(facing_left){
                    if(velocity.x<-5){
                        p_st = State::Run;
                        velocity.x = std::max<double>(-Walkspeed_limit,velocity.x-walkspeed*d_time);
                    }else{
                        velocity.x = std::max<double>(-Walkspeed_limit,velocity.x-walkspeed*d_time);
                    }
                }else{
                    p_st = State::Idle;
                    facing_left = !facing_left;
                }
            }else
                if(KeyRight.pressed()){
                    if(!facing_left){
                        if(velocity.x>5){
                            p_st = State::Run;
                            velocity.x = std::min<double>(Walkspeed_limit,velocity.x+walkspeed*d_time);
                        }else{
                            velocity.x =
                            std::min<double>(Walkspeed_limit,velocity.x+walkspeed*d_time);
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
                    velocity.x = std::max<double>(-Runspeed_limit,velocity.x-5*d_time);

                }else{
                    p_st = State::Idle;
                    facing_left = !facing_left;
                }
            }else if(KeyRight.pressed()){
                if(!facing_left){

                    velocity.x = std::min<double>(Runspeed_limit,velocity.x+5*d_time);
                    
                }else{
                    p_st = State::Idle;
                    facing_left = !facing_left;
                }
            }else{
                p_st = State::Idle;
            }
            break;
        case Jump:
            if(velocity.x > 0) velocity.x -=10*d_time;
            if(velocity.x < 0) velocity.x +=10*d_time;
            velocity.y+= GRAVITY * d_time;
            if(KeyLeft.pressed()){
                if(facing_left){
                    if(velocity.x > -Walkspeed_limit)
                        velocity.x -= 30.0*d_time;
                    
                }else{
                                facing_left = !facing_left;
                }
            }else if(KeyRight.pressed()){
                if(!facing_left){
                    if(velocity.x < Walkspeed_limit)
                        velocity.x += 30.0*d_time;
                    
                }else{
                        facing_left = !facing_left;
                }
            }
            //フックボタン
            if(KeyX.pressed()){
                if(can_hook){
                    
                    hooktime+=d_time*hookspeed;
                    can_shoot_hook = true;
                }
            }else{
                if(can_shoot_hook){
                    shot_hook();
                    hooktime = 0;
                    can_shoot_hook = false;
                }else{
                    hooktime = 0;
                    can_hook = true;
                }
            }
            break;
        case Turn:
            if((frame/10) > anime_turn.size()-1){
                p_st = State::Walk;
                facing_left = !facing_left;
            }
            break;
        case Hooking:
            break;
        case Dead:
            break;
        case Clear:
            break;
    }
    //もし前の状態と違うなら初期化
    if(p_st != before_st){
        frame = 0;
    }
    
}

void Player::GameClear(){
    p_st = Clear;
    frame = 0;
}
bool Player::hooked(Vec2 to_pos){
    velocity += (to_pos-pos).normalize()*1;
    if(p_st!=Dead) p_st = State::Jump;
    return false;
}
void Player::update(){
    TimeProfiler tp;
    tp.begin(U"Hitcheck");
    HitCheck();
    frame+=1;
    if(p_st==Clear){
        if(frame > 110) GetGame()->GameClear();
        return;
    }
    if(p_st == Dead){
        if(KeyC.pressed()){
            GetGame()->GameOver();
        }
        return;
    }
    pos += velocity;
    tp.end();
    
    tp.begin(U"Handleinput");
    handle_input();
    HitBox = Rect(pos.x,pos.y,size.x,size.y);
    tp.end();
    
}
void Player::GameOver(){
    gameover_se.playOneShot(0.5);
    p_st = Dead;
}
void Player::HitCheck(){
    if(p_st==Dead || p_st == Clear) return;
    int hit_r = 26.0;
    int hit_l = 45.0;
    int hit_u = 66.0;
    int hit_d = 20.0;
    int hit_mid = 36.0;
    auto checkMapData = [this](const Vec2 po)->int{
        if(po.x<0||po.y<0||po.x>=64*100||po.y>=64*100) return 4;
        return GetGame()->GetMapData()[(int)po.x/64][(int)po.y/64];
    };
    pos.y+= hit_u;
    TimeProfiler tp;
    tp.begin(U"one hit check");
    checkMapData(Vec2(pos.x+hit_r,pos.y+velocity.y));
    tp.end();
    if(velocity.y > 0){
        //下との衝突
        
        if((checkMapData(Vec2(pos.x+hit_r,pos.y+velocity.y)) |
           checkMapData(Vec2(pos.x+hit_mid,pos.y+velocity.y)) |
           checkMapData(Vec2(pos.x+hit_l,pos.y+velocity.y))) & 1){
            if((checkMapData(Vec2(pos.x+hit_r,pos.y+velocity.y)) &
                checkMapData(Vec2(pos.x+hit_mid,pos.y+velocity.y)) &
                checkMapData(Vec2(pos.x+hit_l,pos.y+velocity.y))) & 4){
                GameOver();
                return;
            }
            landing_se.playOneShot(1.0);
            velocity.y = 0;
            velocity.x /= 2;
            if(!((checkMapData(Vec2(pos.x+hit_r,pos.y-64+velocity.y)) |
               checkMapData(Vec2(pos.x+hit_mid,pos.y-64+velocity.y)) |
               checkMapData(Vec2(pos.x+hit_l,pos.y-64+velocity.y))) & 1))
                pos.y = (floor(pos.y/64)+1)*64-0.1;
            hooktime = 0;
            can_hook = false;
            p_st = State::Idle;
        }else{
            if((checkMapData(Vec2(pos.x+hit_r,pos.y+velocity.y)) |
                checkMapData(Vec2(pos.x+hit_mid,pos.y+velocity.y)) |
                checkMapData(Vec2(pos.x+hit_l,pos.y+velocity.y))) & 4){
                GameOver();
                return;
            }
        }
        
    }else if(velocity.y == 0){
        if(!((checkMapData(Vec2(pos.x+hit_r,pos.y+64+velocity.y)) |
            checkMapData(Vec2(pos.x+hit_l,pos.y+64+velocity.y)) |
            checkMapData(Vec2(pos.x+hit_mid,pos.y+64+velocity.y)))&1)){
            if((checkMapData(Vec2(pos.x+hit_r,pos.y+64+velocity.y)) |
                checkMapData(Vec2(pos.x+hit_l,pos.y+64+velocity.y)) |
                checkMapData(Vec2(pos.x+hit_mid,pos.y+64+velocity.y))) & 4){
                GameOver();
                return;
            }
            p_st = State::Jump;
        }else{
            if((checkMapData(Vec2(pos.x+hit_r,pos.y+64+velocity.y)) &
                checkMapData(Vec2(pos.x+hit_l,pos.y+64+velocity.y)) &
                checkMapData(Vec2(pos.x+hit_mid,pos.y+64+velocity.y))) & 4){
                GameOver();
                return;
            }
        }
    }
    
    pos.y-=hit_u;
    pos.y+=hit_d;
    if(velocity.y < 0){
        
        if((checkMapData(Vec2(pos.x+hit_r,pos.y+velocity.y)) |
            checkMapData(Vec2(pos.x+hit_mid,pos.y+velocity.y)) |
            checkMapData(Vec2(pos.x+hit_l,pos.y+velocity.y))) & 4){
            GameOver();
            return;
        }
        //上との衝突
        if((checkMapData(Vec2(pos.x+hit_r,pos.y+velocity.y)) |
           checkMapData(Vec2(pos.x+hit_mid,pos.y+velocity.y)) |
           checkMapData(Vec2(pos.x+hit_l,pos.y+velocity.y))) &1){
            landing_se.playOneShot(1.0);
            
            velocity.y = 0;
            if((checkMapData(Vec2(pos.x+hit_r,pos.y+64+velocity.y))   |
               checkMapData(Vec2(pos.x+hit_mid,pos.y+64+velocity.y)) |
               checkMapData(Vec2(pos.x+hit_l,pos.y+64+velocity.y)))==0)
                pos.y = (floor(pos.y/64))*64;
            
        }
    }
    pos.y-=hit_d;
    pos.x += hit_l;
    if(velocity.x > 0){
        //右との衝突
        if((
            checkMapData(Vec2(pos.x+velocity.x,pos.y+hit_d))   |
            checkMapData(Vec2(pos.x+velocity.x,pos.y+hit_mid)) |
            checkMapData(Vec2(pos.x+velocity.x,pos.y+hit_u))
            ) & 4){
            GameOver();
            return;
        }
        if((checkMapData(Vec2(pos.x+velocity.x,pos.y+hit_d)) |
           checkMapData(Vec2(pos.x+velocity.x,pos.y+hit_mid)) |
           checkMapData(Vec2(pos.x+velocity.x,pos.y+hit_u))) & 1){
            if(velocity.x>11.0) landing_se.playOneShot(1.0);
            
            velocity.x = 0;
            if((checkMapData(Vec2(pos.x,pos.y+hit_d)) |
               checkMapData(Vec2(pos.x,pos.y+hit_mid)) |
               checkMapData(Vec2(pos.x,pos.y+hit_u))) == 1)
                pos.x = (floor(pos.x/64))*64-0.2;
            else
                pos.x = (floor(pos.x/64)+1)*64-0.2;
            
            
        }
    }
    pos.x -= hit_l;
    pos.x += hit_r;
    if(velocity.x < 0){
        //左との衝突
        if((checkMapData(Vec2(pos.x+velocity.x,pos.y+hit_d))   |
            checkMapData(Vec2(pos.x+velocity.x,pos.y+hit_mid)) |
            checkMapData(Vec2(pos.x+velocity.x,pos.y+hit_u))
            ) & 4){
            GameOver();
            return;
        }
        if((checkMapData(Vec2(pos.x+velocity.x,pos.y+hit_d))   |
           checkMapData(Vec2(pos.x+velocity.x,pos.y+hit_mid)) |
           checkMapData(Vec2(pos.x+velocity.x,pos.y+hit_u))) & 1){
            if(velocity.x<-11.0) landing_se.playOneShot(1.0);
            
            velocity.x = 0;
            if((checkMapData(Vec2(pos.x,pos.y+hit_d)) |
               checkMapData(Vec2(pos.x,pos.y+hit_mid)) |
               checkMapData(Vec2(pos.x,pos.y+hit_u))) & 1)
                pos.x = (floor(pos.x/64)-1)*64+0.1;
            else
                pos.x = (floor(pos.x/64))*64+0.1;
            
        }
    }
    pos.x -= hit_r;
    
    
    
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
        case Hooking:
            if(velocity.y<-2)  texture_jump(72*(anime_jump_up[(frame/6) % anime_jump_up.size()]),0,72,72).mirrored(facing_left).draw(pos.x,pos.y);
            else if(velocity.y>=2) texture_jump(72*(anime_jump_fall[(frame/6) % anime_jump_fall.size()]),0,72,72).mirrored(facing_left).draw(pos.x,pos.y);
            else texture_jump(72*(anime_jump_mid[(frame/6) % anime_jump_mid.size()]),0,72,72).mirrored(facing_left).draw(pos.x,pos.y);
            
            if(hooktime>0){
                Vec2 hookpos;
                if(facing_left) hookpos = Vec2(pos.x+32.0,pos.y+32.0) + Vec2(-100.0*sin(hooktime+M_PI/2),100.0*cos(hooktime+M_PI/2));
                else  hookpos = Vec2(pos.x+32.0,pos.y+32.0) + Vec2(100.0*sin(hooktime+M_PI/2),100.0*cos(hooktime+M_PI/2));
                Circle(hookpos,20).drawFrame();
            }
            break;
        case Dead:
            FontAsset(U"Title")(U"げーむおーばー").drawAt(Vec2(pos.x, pos.y-120.0).movedBy(4, 6), ColorF(0.0, 0.5));
            FontAsset(U"Title")(U"げーむおーばー").drawAt(Vec2(pos.x, pos.y-120.0));
            if(frame%40<27) FontAsset(U"Score")(U"Press C key").drawAt(Vec2(pos.x, pos.y-200.0));
           if(frame%2==0) effect.add<Burn>(pos+Vec2(Random<float>(-10.0,10.0),Random<float>(-10.0,10.0)));
            break;
        case Clear:
            FontAsset(U"Title")(U"げーむくりあ").drawAt(Vec2(pos.x, pos.y-120.0).movedBy(4, 6), ColorF(0.0, 0.5));
            FontAsset(U"Title")(U"げーむくりあ").drawAt(Vec2(pos.x, pos.y-120.0));
           texture_positive(72*(anime_positive[(frame/10) % anime_positive.size()]),0,72,72).mirrored(facing_left).draw(pos.x,pos.y);
            if(frame%5==0)
                effect.add<Burn>(pos+Vec2(Random<float>(-200.0,200.0),Random<float>(-200.0,200.0)));
            break;
    }
//    int hit_r = 26.0;
//    int hit_l = 45.0;
//    int hit_u = 66.0;
//    int hit_d = 20.0;
//    int hit_mid = 36.0;
//    Rect(hit_r+pos.x,hit_u+pos.y,hit_l-hit_r,hit_d-hit_u).drawFrame();
    effect.update();
};
