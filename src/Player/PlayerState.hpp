//
//  PlayerState.hpp
//  empty
//
//  Created by 坂井創一 on 2019/08/23.
//

#ifndef PlayerState_hpp
#define PlayerState_hpp

#include <stdio.h>

class State{
    virtual State* Update(PlayerState* ix){return NULL;}
};

class IdleState : State{
    virtual State* Update(Actor* ix){
        
    }
};
class PlayerState{
private:
    enum eState{
        IDLE,
        WALKING,
        JUMPING,
        RUNNING,
        DAMEGED,
    };
    PlayerState(){
        m_Statepool.push_back(new IdleState());
    }
}


#endif /* PlayerState_hpp */
