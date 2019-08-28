//
//  Game.cpp
//  empty
//
//  Created by 坂井創一 on 2019/08/10.
//
  
#include "Game.hpp"
#include "Burn.hpp"

void Game::update(){

    
    m_player.update();
    
//    m_ball.update(HP);
    for (auto& bullet : playerBullets)
    {
        bullet.update(HP);
    }
    if(HP<=0){
        changeScene(State::Title);
        getData().highScore = Max(getData().highScore, m_score);
    };
    
    playerBullets.remove_if([](const auto& actor){return actor.isDead();});
}
void Game::draw() const {
    geme_stage.draw();
    
    FontAsset(U"Score")(m_score).drawAt(Scene::Center().x, 30);
    FontAsset(U"Score")(U"HP : "+Format(HP)).drawAt(Scene::Center().x+250, 30);
    FontAsset(U"Score")(playerBullets.size()).drawAt(Scene::Center().x-250,30);
//    // すべてのブロックを描画する
//    for (const auto& block : m_blocks)
//    {
//        block.draw();
//    }
    // パドルを描く
    m_player.draw();
    for (const auto& bullet : playerBullets)
    {
        bullet.draw();
    }
}
