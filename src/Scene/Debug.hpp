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
