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
    
    m_ball.update(HP);
    
    
    if(HP<=0){
        changeScene(State::Title);
        getData().highScore = Max(getData().highScore, m_score);
    };
    
    for(auto actor : playerBullets){
        if(actor.isDead()){
            changeScene(State::Title);
            //actorの削除
        }
    }
}
void Game::draw() const {
    {
        FontAsset(U"Score")(m_score).drawAt(Scene::Center().x, 30);
        FontAsset(U"Score")(U"HP : "+Format(HP)).drawAt(Scene::Center().x+250, 30);
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
