//
//  Game.cpp
//  empty
//
//  Created by 坂井創一 on 2019/08/10.
//
  
#include "Game.hpp"
void Game::update(){
    // パドルを操作
    if(KeyLeft.pressed()) m_paddle.move_left();
    if(KeyRight.pressed()) m_paddle.move_right();
    if(KeySpace.pressed()) m_paddle.shot_bullet();
    
    m_paddle.update();
    
    m_ball.update(HP);
    for (auto& bullet : playerBullets)
    {
        bullet.update(HP);
    }
    
    if(HP<=0){
        changeScene(State::Title);
        getData().highScore = Max(getData().highScore, m_score);
    };
    
    for(auto actor : playerBullets){
        if(actor.isDead()){
//            changeScene(State::Title);
            //actorの削除
            
        }
    }
    playerBullets.remove_if([](const auto& actor){return actor.isDead();});
}
void Game::draw() const {
    {
        FontAsset(U"Score")(m_score).drawAt(Scene::Center().x, 30);
        FontAsset(U"Score")(U"HP : "+Format(HP)).drawAt(Scene::Center().x+250, 30);
        FontAsset(U"Score")(playerBullets.size()).drawAt(Scene::Center().x-250,30);
        // すべてのブロックを描画する
        for (const auto& block : m_blocks)
        {
            block.draw();
        }
        
        // ボールを描く
        m_ball.draw();
        // パドルを描く
        m_paddle.draw();
        for (const auto& bullet : playerBullets)
        {
            bullet.draw();
        }
    }
}
