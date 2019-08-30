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
