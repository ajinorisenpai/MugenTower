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



// ゲームシーン
class Game : public SceneManager<State, GameData>::Scene
{
private:
    
    // ブロックのサイズ
    static constexpr Size blockSize = Size(40, 20);
    
    // ボールの速さ
    static constexpr double speed = 480.0;
    
    // ブロックの配列
    Array<Rect> m_blocks;
    
    // ボールの速度
    Vec2 m_ballVelocity = Vec2(0, -speed);
    
    // ボール
    Circle m_ball = Circle(400, 400, 8);
    
    // パドル
    Rect m_paddle = Rect(Arg::center(Cursor::Pos().x, 500), 60, 10);
    
    // スコア
    int32 m_score = 0;
    
public:
    
    Game(const InitData& init)
    : IScene(init)
    {
        // 横 (Scene::Width() / blockSize.x) 個、縦 5 個のブロックを配列に追加する
        for (auto p : step(Size((Scene::Width() / blockSize.x), 5)))
        {
            m_blocks << Rect(p.x * blockSize.x, 60 + p.y * blockSize.y, blockSize);
        }
    }
    
    void update() override;
    
    //メンバ関数の右側にconstをつけると、そのメンバ関数内ではメンバ変数の変更ができなくなる
    void draw() const override;
    
};

#endif /* Game_hpp */
