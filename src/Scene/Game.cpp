#include "Game.hpp"
#include "Burn.hpp"

void Game::update(){
    
    camera.update();
    if(KeyC.pressed()) {
        if(camera_scale >0.4) camera_scale *= 0.99;
    }else if(camera_scale < 1) camera_scale += 0.02;
    camera.setScale(camera_scale);
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
    camera.setTargetCenter(m_player.center());
}
void Game::draw() const{
    {
        const auto t1 = camera.createTransformer();
        
        game_stage.draw();

        m_player.draw();
        for (const auto& bullet : playerBullets)
        {
            bullet.draw();
        }
        m_hook.draw();
        camera.draw(Palette::Orange);
    }
    if(Config_Mode){
        Rect(10,10,10,10).draw();
    }
}
