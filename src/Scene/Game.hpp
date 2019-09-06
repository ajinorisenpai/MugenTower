#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include "GameInfo.h"
#include <Siv3D.hpp>
#include "Player.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"
#include "Actor.hpp"
#include "Burn.hpp"
#include "Stage.hpp"
#include "Hook.hpp"
class Game : public SceneManager<State, GameData>::Scene
{
protected:
//オーディオ
    Audio HouseBGM;
//カメラ設定
    const int MULTI_SCROLL = 0b0100;
    float camera_scale = 1.0;
    Camera2D camera = Camera2D(1.0,Camera2DParameters::MouseOnly());
    
    Camera2D frontcamera = Camera2D(1.2,Camera2DParameters::MouseOnly());
    Camera2D bgcamera_1 = Camera2D(0.7,Camera2DParameters::MouseOnly());
    Camera2D bgcamera_2 = Camera2D(0.85,Camera2DParameters::MouseOnly());
    
    void camera_update();
//プレイヤー設定
    Stage game_stage = Stage(getData().StageFile);
    Player m_player = Player(this,game_stage.GetStartPos());
    int32 HP = 50;
    Hook m_hook = Hook(this,Vec2(0.0,0.0),Vec2(0.0,0.0));
    Array<Bullet> playerBullets;
    Array<Enemy> m_enemy;
public:
    Game(const InitData& init)
    : IScene(init)
    {
        HouseBGM = Audio(Resource(U"Sound/HouseBGM.mp3"));
        HouseBGM.setLoop(true);
        HouseBGM.play();
    }
//getter
    vector<vector<int>> GetMapData() const {
        return game_stage.GetMapData();
        
    };
    Player& GetPlayer() {return m_player;}
    Hook& GetHook(){return m_hook;}
    Array<Bullet>& GetPlayerBullet(){return playerBullets;}
    
//プレイヤー設定
    
    int32 m_score = 0;
    void make_bullet(Vec2 pos,Vec2 dir){
        playerBullets << Bullet(this,pos,dir);
    }
    
    void make_hook(Vec2 pos,Vec2 dir){
        m_hook.init(pos,dir);
    }
    void GameOver(){
        init();
    }
    
    void GameClear(){
        HouseBGM.stop();
        changeScene(State::Title);
    }
    
    //
    void init(){
        m_player.init(game_stage.GetStartPos());
    }
    
    Array<Enemy>& GetEnemy(){return m_enemy;}
    
    void update() override;

    void draw() const override;
    
    
    
    
};

#endif /* Game_hpp */
