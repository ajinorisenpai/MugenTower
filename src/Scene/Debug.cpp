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
        if(ChBox01.leftClicked()){
            mapid ^= 0b0001;
        }
        if(ChBox02.leftClicked()){
            mapid ^= 0b0010;
        }
        if(ChBox03.leftClicked()){
            mapid ^= 0b0100;
        }
        if(ChBox04.leftClicked()){
            ResetStartPos = true;
        }
        if(SaveBtn.leftClicked())
           game_stage.ExportMapData();
        if(ExitBtn.leftClicked()){
            game_stage.ExportMapData();
            changeScene(State::Title);
        }
        
//        mapid = mapcheck1 + 2*mapcheck2 + 4*mapcheck3;
    }
    Game::update();
}
void Debug::draw() const{
    Game::draw();
    ClearPrint();
    Print << U"{:.0f}"_fmt(camera.getCenter());

    if(mapid&0b0001){
        ChBox01.draw(Color(100,100,100));
    }else{
        ChBox01.draw(Color(255,255,255));
    }
    if(mapid&0b0010){
        ChBox02.draw(Color(100,100,100));
    }else{
        ChBox02.draw(Color(255,255,255));
    }
    if(mapid&0b0100){
        ChBox03.draw(Color(100,100,100));
    }else{
        ChBox03.draw(Color(255,255,255));
    }
    if(ResetStartPos){
        ChBox04.draw(Color(100,100,100));
    }else{
        ChBox04.draw(Color(255,255,255));
    }
    SaveBtn.draw(Color(255,255,255));
    ExitBtn.draw(Color(255,255,255));
    FontAsset(U"Debug")(U"触れるか").drawAt(Vec2(80,40), Color(255));
    FontAsset(U"Debug")(U"フック不可").drawAt(Vec2(80,80), Color(255));
    FontAsset(U"Debug")(U"即死").drawAt(Vec2(80,120), Color(255));
    FontAsset(U"Debug")(U"スタート位置").drawAt(Vec2(80,160), Color(255));
    FontAsset(U"Debug")(U"保存").drawAt(Vec2(100,220), Color(0));
    FontAsset(U"Debug")(U"終了(保存)").drawAt(Vec2(100,260), Color(0));
}
