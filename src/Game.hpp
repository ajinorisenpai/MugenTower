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

// ゲームシーン
class Game : public SceneManager<State, GameData>::Scene
{
private:
    
    // ブロックのサイズ
//    static constexpr Size blockSize = Size(40, 20);
    
    // ボールの速さ
//    static constexpr double speed = 480.0;
    
    // ブロックの配列
//    Array<Rect> m_blocks;
    Array<Enemy> m_blocks;
    // ボールの速度
//    Vec2 m_ballVelocity = Vec2(0, -speed);
    
    // ボール
//    Circle m_ball = Circle(400, 400, 8);
    class Bullet m_ball = Bullet(this,400,400);;
    // パドル
    
    
    class Player m_paddle = Player();
    // スコア
    int32 m_score = 0;
    int32 HP = 1;
public:
    Player GetPlayer(){return m_paddle;}
    Game(const InitData& init)
    : IScene(init)
    {
        // 横 (Scene::Width() / blockSize.x) 個、縦 5 個のブロックを配列に追加する
        for (auto p : step(Size((Scene::Width() / Enemy::blockSize.x), 5)))
        {
            m_blocks << Enemy(p);
        }
    }
    
    void update() override;
    
    //メンバ関数の右側にconstをつけると、そのメンバ関数内ではメンバ変数の変更ができなくなる
    void draw() const override;
    
    
};

#endif /* Game_hpp */
