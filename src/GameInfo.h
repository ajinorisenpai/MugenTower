//
//  GameInfo.h
//  MugenTower
//
//  Created by 坂井創一 on 2019/08/10.
//

#ifndef GameInfo_h
#define GameInfo_h
#include <Siv3D.hpp>

// シーンの名前
enum class State
{
    Title,
    Game
};

// ゲームデータ
struct GameData
{
    // ハイスコア
    int32 highScore = 0;
};


#endif /* GameInfo_h */
