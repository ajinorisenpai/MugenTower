//
//  Debug.cpp
//  empty
//
//  Created by 坂井創一 on 2019/09/05.
//

#include "Debug.hpp"
#include "Burn.hpp"

void Debug::update(){
    
    
    if(KeyP.down()){
        palletmode = !palletmode;
    }
    if(KeyF.down()){
        palletmode = !palletmode;
    }
    if(MouseL.pressed() && (Cursor::Pos().x >200 || !palletmode)){
        if(ResetStartPos){
            game_stage.ResetStartPos(camera.getCenter()+Cursor::Pos()-Vec2(Scene::Width()/2,Scene::Height()/2));
            ResetStartPos = false;
        }else{
            game_stage.EditStage(camera.getCenter()+Cursor::Pos()-Vec2(Scene::Width()/2,Scene::Height()/2),mapid);
        }
    }
    if(MouseR.pressed()){
        game_stage.EditStage(camera.getCenter()+Cursor::Pos()-Vec2(Scene::Width()/2,Scene::Height()/2),0);
    }
    if(palletmode){
        SimpleGUI::CheckBox(mapcheck1, U"touch", Vec2(40, 40));
        SimpleGUI::CheckBox(mapcheck2, U"unable hook", Vec2(40, 80));
        SimpleGUI::CheckBox(mapcheck3, U"death", Vec2(40, 120));
        SimpleGUI::CheckBox(ResetStartPos, U"StartPos", Vec2(40, 160));
        if(SimpleGUI::Button(U"Save", Vec2(40,200)))
           game_stage.ExportMapData();
        if(SimpleGUI::Button(U"Exit", Vec2(40,240))){
            game_stage.ExportMapData();
            changeScene(State::Title);
        }
        
        mapid = mapcheck1 + 2*mapcheck2 + 4*mapcheck3;
    }
    Game::update();
}
void Debug::draw() const{
    Game::draw();
    ClearPrint();
    Print << U"{:.0f}"_fmt(camera.getCenter());
}
