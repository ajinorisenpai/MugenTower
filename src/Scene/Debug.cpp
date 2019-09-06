//
//  Debug.cpp
//  empty
//
//  Created by 坂井創一 on 2019/09/05.
//

#include "Debug.hpp"
#include "Burn.hpp"

void Debug::update(){
    
    if(KeyA.pressed()){
        camera_scale = 0.1;
    }else{
        
    }
    Game::update();
}
void Debug::draw() const{
    Rect(10,10,100,100).draw();
    Game::draw();
    ClearPrint();
    Print << U"{:.0f}"_fmt(camera.getCenter());
}
