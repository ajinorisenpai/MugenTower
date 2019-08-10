//
//  Title.hpp
//  empty
//
//  Created by 坂井創一 on 2019/08/10.
//

#ifndef Title_hpp
#define Title_hpp

#include <stdio.h>
#include <Siv3D.hpp>
#include "GameInfo.h"

// タイトルシーン
class Title : public SceneManager<State, GameData>::Scene
{
private:
    
    Rect m_startButton = Rect(Arg::center = Scene::Center().movedBy(0, 0), 300, 60);
    Transition m_startTransition = Transition(0.4s, 0.2s);
    
    Rect m_exitButton = Rect(Arg::center = Scene::Center().movedBy(0, 100), 300, 60);
    Transition m_exitTransition = Transition(0.4s, 0.2s);
    
public:
    Title(const InitData& init)
    : IScene(init) {}
    void update() override;
    void draw() const override;
    
};

#endif /* Title_hpp */
