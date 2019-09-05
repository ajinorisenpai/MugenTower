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

class Debug : public SceneManager<State, GameData>::Scene{

private:

public:
    Debug(const InitData& init): IScene(init) {};
    void update() override;
    void draw() const override;
};
#endif /* Debug_hpp */
