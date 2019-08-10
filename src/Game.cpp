//
//  Game.cpp
//  empty
//
//  Created by 坂井創一 on 2019/08/10.
//
  
#include "Game.hpp"
void Game::update(){
    // パドルを操作
    m_paddle.update();
    
    m_ball.update();
    
    // ブロックを順にチェック
    for (auto it = m_blocks.begin(); it != m_blocks.end(); ++it)
    {
        // ボールとブロックが交差していたら
        if (it->rect.intersects(m_ball.m_ball))
        {
            // ボールの向きを反転する
            (it->rect.bottom().intersects(m_ball.m_ball) || it->rect.top().intersects(m_ball.m_ball) ? m_ball.m_ballVelocity.y : m_ball.m_ballVelocity.x) *= -1;
            
            // ブロックを配列から削除（イテレータが無効になるので注意）
            m_blocks.erase(it);
            
            // スコアを加算
            ++m_score;
            
            // これ以上チェックしない
            break;
        }
    }
    
    // 天井にぶつかったらはね返る
    if (m_ball.m_ball.y < 0 && m_ball.m_ballVelocity.y < 0)
    {
        m_ball.m_ballVelocity.y *= -1;
    }
    
    if (m_ball.m_ball.y > Scene::Height())
    {
        changeScene(State::Title);
        getData().highScore = Max(getData().highScore, m_score);
    }
    
    // 左右の壁にぶつかったらはね返る
    if ((m_ball.m_ball.x < 0 && m_ball.m_ballVelocity.x < 0) || (Scene::Width() < m_ball.m_ball.x && m_ball.m_ballVelocity.x > 0))
    {
        m_ball.m_ballVelocity.x *= -1;
    }
    
    // パドルにあたったらはね返る
    if (m_ball.m_ballVelocity.y > 0 && m_paddle.collision(m_ball.m_ball))
    {
        // パドルの中心からの距離に応じてはね返る向きを変える
        m_ball.m_ballVelocity = Vec2((m_ball.m_ball.x - m_paddle.center().x) * 10, -m_ball.m_ballVelocity.y).setLength(m_ball.speed);
    }
}
void Game::draw() const {
    {
        FontAsset(U"Score")(m_score).drawAt(Scene::Center().x, 30);
        
        // すべてのブロックを描画する
        for (const auto& block : m_blocks)
        {
            block.draw();
        }
        
        // ボールを描く
        m_ball.draw();
        
        // パドルを描く
        m_paddle.draw();
    }
}
