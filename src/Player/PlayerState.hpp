//
//  PlayerState.hpp
//  empty
//
//  Created by 坂井創一 on 2019/08/23.
//

#ifndef PlayerState_hpp
#define PlayerState_hpp

#include <stdio.h>
#include <Siv3D.hpp>
//
//
class PlayerState{

public:
    virtual PlayerState* draw(){
        return NULL;
    }
    virtual PlayerState* update(){
        return NULL;
    }
};

#endif /* PlayerState_hpp */
