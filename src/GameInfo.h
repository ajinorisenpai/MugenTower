//
//  GameInfo.h
//  MugenTower
//
//  Created by 坂井創一 on 2019/08/10.
//

#ifndef GameInfo_h
#define GameInfo_h
#include <Siv3D.hpp>

enum class State
{
    Title,
    Game
};

struct GameData
{
    int32 highScore = 0;
    String StageFile;
};


#endif /* GameInfo_h */
