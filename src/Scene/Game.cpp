#include "Game.hpp"
#include "Burn.hpp"

void Game::camera_update(){
    if(KeyC.pressed()) {
        if(camera_scale >0.4) camera_scale *= 0.99;
    }else if(camera_scale < 1) camera_scale += 0.02;
    
    
    
    camera.update();
    camera.setScale(camera_scale);
    camera.setTargetCenter(m_player.center());
    
    
    if(MULTI_SCROLL!=0b0100){
        frontcamera.update();
        bgcamera_1.update();
        bgcamera_2.update();
        frontcamera.setScale(camera_scale*1.2);
        bgcamera_1.setScale(camera_scale*0.4);
        bgcamera_2.setScale(camera_scale*0.85);
        frontcamera.setTargetCenter(m_player.center());
        bgcamera_1.setTargetCenter(m_player.center());
        bgcamera_2.setTargetCenter(m_player.center());
    }
}

void Game::update(){
    
    camera_update();
    
    m_player.update();
    
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
    
}

void Game::draw() const{
    TimeProfiler tp;
    tp.begin(U"MainDraw");
    if(MULTI_SCROLL & 0b0001){
        const auto t1 = bgcamera_1.createTransformer();
//        m_player.draw();
        game_stage.draw(m_player.center());
        m_player.draw();
    }
    if(MULTI_SCROLL & 0b0010){
        const auto t2 = bgcamera_2.createTransformer();
        game_stage.draw(m_player.center());
        m_player.draw();
    }
    
    {
        const auto t3 = camera.createTransformer();
        
        game_stage.draw(m_player.center());
        m_player.draw();
        m_hook.draw();
        for (const auto& bullet : playerBullets)
        {
            bullet.draw();
        }
        
    }
    if(MULTI_SCROLL &0b1000){
        const auto t4 = frontcamera.createTransformer();
        game_stage.draw(m_player.center());

        m_player.draw();
        
    }
   
    camera.draw();
    tp.end();
    
}
