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

// ゲームシーン
class Game : public SceneManager<State, GameData>::Scene
{
private:
    
    Array<Enemy> m_blocks;
    Array<Bullet> playerBullets;
    Stage geme_stage;
    Player m_player = Player(this);
    int32 HP = 50;
    
public:
    Player& GetPlayer() {return m_player;}
    Array<Enemy>& GetEnemy(){return m_blocks;}
    Array<Bullet>& GetPlayerBullet(){return playerBullets;};
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

    void make_bullet(double x,double y){
        playerBullets << Bullet(this,x,y);
    }
//メンバ関数の右側にconstをつけると、そのメンバ関数内ではメンバ変数の変更ができなくなる
    void draw() const override;
    
};

#endif /* Game_hpp */
