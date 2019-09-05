#ifndef Title_hpp
#define Title_hpp

#include <stdio.h>
#include <Siv3D.hpp>
#include "GameInfo.h"

// タイトルシーン
class Title : public SceneManager<State, GameData>::Scene
{
private:
    
    Rect m_tutorialButton = Rect(Arg::center = Scene::Center().movedBy(0, 0), 300, 40);
    Transition m_tutorialTransition = Transition(0.2s, 0.2s);
    
    Rect m_stage1Button = Rect(Arg::center = Scene::Center().movedBy(0, 50), 300,40);
    Transition m_stage1Transition = Transition(0.2s, 0.2s);
    
    Rect m_stage2Button = Rect(Arg::center = Scene::Center().movedBy(0, 100), 300, 40);
    Transition m_stage2Transition = Transition(0.2s,0.2s);
    Rect m_stage3Button = Rect(Arg::center = Scene::Center().movedBy(0, 150), 300, 40);
    Transition m_stage3Transition = Transition(0.2s,0.2s);
    Rect m_exitButton = Rect(Arg::center = Scene::Center().movedBy(0, 200), 300, 40);
    Transition m_exitTransition = Transition(0.2s, 0.2s);
    
    Rect DebugButton = Rect(Arg::center = Scene::Center().movedBy(0, 250), 300,40);
    
    

public:
    Title(const InitData& init)
    : IScene(init) {}
    void update() override;
    void draw() const override;
    
};

#endif /* Title_hpp */
