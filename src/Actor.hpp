//
//  Actor.hpp
//  empty
//
//  Created by 坂井創一 on 2019/08/10.
//

#ifndef Actor_hpp
#define Actor_hpp

#include <stdio.h>
#include <Siv3D.hpp>
class Actor{
protected:
    enum State{
        Active,
        Dead
    };
    State mState;
public:
    virtual void update(){};
    virtual void draw(){};
    Actor():mState(State::Active){
    }
    bool isDead() const {
        return mState==Dead;
    }
};
#endif /* Actor_hpp */
