//
//  Game.hpp
//  empty
// 
//  Created by 坂井創一 on 2019/08/10.
//

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
    Array<Enemy> m_blocks;
    Array<Bullet> playerBullets;
    Stage game_stage;
    Player m_player = Player(this);
    int32 HP = 50;
    Hook m_hook = Hook(this,Vec2(0.0,0.0),Vec2(0.0,0.0));
    Camera2D camera;
public:
    
    Player& GetPlayer() {return m_player;}
    Array<Enemy>& GetEnemy(){return m_blocks;}
    Array<Bullet>& GetPlayerBullet(){return playerBullets;}
    Hook& GetHook(){return m_hook;}
    // スコア
    int32 m_score = 0;
    Game(const InitData& init)
    : IScene(init)
    {
        // 横 (Scene::Width() / blockSize.x) 個、縦 5 個のブロックを配列に追加する
//        for (auto p : step(Size((Scene::Width() / Enemy::blockSize.x), 5)))
//        {
//            m_blocks << Enemy(p);
//        }
    }
    
    void update() override;

    void make_bullet(Vec2 pos,Vec2 dir){
        playerBullets << Bullet(this,pos,dir);
    }
//メンバ関数の右側にconstをつけると、そのメンバ関数内ではメンバ変数の変更ができなくなる
    void draw() const override;
    vector<vector<int>> GetMapData() const {
        return game_stage.GetMapData();
    };
    void make_hook(Vec2 pos,Vec2 dir){
        m_hook.init(pos,dir);
    }
    void GameOver(){
        changeScene(State::Title);
    }
};

#endif /* Game_hpp */
