//
//  Debug.hpp
//  empty
//
//  Created by 坂井創一 on 2019/09/05.
//

#ifndef Debug_hpp
#define Debug_hpp
#include <stdio.h>
#include <Siv3D.hpp>
#include "GameInfo.h"
#include "Game.hpp"
class Debug : public Game{
private:
    bool palletmode = true;
    int mapid = 0;
    Circle ChBox01 = Circle(160,40, 20);
    Circle ChBox02 = Circle(160,80, 20);
    Circle ChBox03 = Circle(160,120, 20);
    Circle ChBox04 = Circle(160,160, 20);
    
    Rect SaveBtn = Rect(40,200,80,30);
    Rect ExitBtn = Rect(40,240,80,30);
    bool mapcheck1 = false;
    bool mapcheck2 = false;
    bool mapcheck3 = false;
    bool ResetStartPos = false;
public:
    Debug(const InitData& init): Game(init) {};
    void update() override;
    void draw() const override;
};
#endif /* Debug_hpp */
