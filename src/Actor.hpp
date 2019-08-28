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

class Game;

class Actor{
private:
    class Game* m_game;
protected:
    enum State{
        Active,
        Dead
    };
    State mState;
    
    class Game* GetGame() { return m_game; }
public:
    virtual void update(){};
    virtual void draw(){};
    Actor(Game* m_game);
    bool isDead() const {
        return mState==Dead;
    }
    
};
#endif /* Actor_hpp */
