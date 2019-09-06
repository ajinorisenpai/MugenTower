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

public:
    Debug(const InitData& init): Game(init) {};
    void update() override;
    void draw() const override;
};
#endif /* Debug_hpp */
