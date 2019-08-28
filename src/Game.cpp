//
//  Game.cpp
//  empty
//
//  Created by 坂井創一 on 2019/08/10.
//
  
#include "Game.hpp"
#include "Burn.hpp"

void Game::update(){
    
    camera.update();
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
    m_hook.update();
    
    playerBullets.remove_if([](const auto& actor){return actor.isDead();});
    camera.setTargetCenter(m_player.center());
}
void Game::draw() const{
    {
        const auto t1 = camera.createTransformer();
        
        game_stage.draw();

        // パドルを描く
        m_player.draw();
        for (const auto& bullet : playerBullets)
        {
            bullet.draw();
        }
        m_hook.draw();
        camera.draw(Palette::Orange);
        
    }
    FontAsset(U"Score")(m_score).drawAt(Scene::Center().x, 30);
    FontAsset(U"Score")(U"HP : "+Format(HP)).drawAt(Scene::Center().x+250, 30);
    FontAsset(U"Score")(playerBullets.size()).drawAt(Scene::Center().x-250,30);
}
