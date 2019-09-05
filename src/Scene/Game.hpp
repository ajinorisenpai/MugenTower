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
// ゲームシーン
class Game : public SceneManager<State, GameData>::Scene
{
private:
    Array<Enemy> m_enemy;
    Array<Bullet> playerBullets;
    float camera_scale = 1.0;
    Stage game_stage = Stage(getData().StageFile);
    Player m_player = Player(this,game_stage.GetStartPos());
    int32 HP = 50;
    Hook m_hook = Hook(this,Vec2(0.0,0.0),Vec2(0.0,0.0));
    Camera2D camera = Camera2D(1.0,Camera2DParameters::MouseOnly());
    Audio HouseBGM;
    bool Config_Mode = false;
public:
    
    Player& GetPlayer() {return m_player;}
    Array<Enemy>& GetEnemy(){return m_enemy;}
    Array<Bullet>& GetPlayerBullet(){return playerBullets;}
    Hook& GetHook(){return m_hook;}
    int32 m_score = 0;
    Game(const InitData& init)
    : IScene(init)
    {
        HouseBGM = Audio(U"Sound/HouseBGM.mp3");
        HouseBGM.setLoop(true);
        HouseBGM.play();
    }
    
    void update() override;

    void make_bullet(Vec2 pos,Vec2 dir){
        playerBullets << Bullet(this,pos,dir);
    }
    
    void draw() const override;
    vector<vector<int>> GetMapData() const {
        return game_stage.GetMapData();
    };
    void make_hook(Vec2 pos,Vec2 dir){
        m_hook.init(pos,dir);
    }
    void GameOver(){
        HouseBGM.stop();
        changeScene(State::Title);
    }
};

#endif /* Game_hpp */
