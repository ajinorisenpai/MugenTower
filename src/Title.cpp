//
//  Title.cpp
//  empty
//
//  Created by 坂井創一 on 2019/08/10.
//

#include "Title.hpp"

void Title::update(){
    m_tutorialTransition.update(m_tutorialButton.mouseOver());
    
    m_stage1Transition.update(m_stage1Button.mouseOver());
    m_stage2Transition.update(m_stage2Button.mouseOver());
    m_stage3Transition.update(m_stage3Button.mouseOver());
    m_exitTransition.update(m_exitButton.mouseOver());
    
    if (m_tutorialButton.mouseOver() || m_exitButton.mouseOver())
    {
        Cursor::RequestStyle(CursorStyle::Hand);
    }
    
    if (m_tutorialButton.leftClicked())
    {
        getData().StageFile = U"Levels/tutorial.csv";
        changeScene(State::Game);
    }
    if (m_stage1Button.leftClicked())
    {
        getData().StageFile = U"Levels/stage1.csv";
        changeScene(State::Game);
    }
    if (m_stage2Button.leftClicked())
    {
        getData().StageFile = U"Levels/stage2.csv";
        changeScene(State::Game);
    }
    if (m_stage3Button.leftClicked())
    {
        getData().StageFile = U"Levels/stage3.csv";
        changeScene(State::Game);
    }
    
    if (m_exitButton.leftClicked())
    {
        System::Exit();
    }
}
void Title::draw() const{
    const String titleText = U"ワイヤージャンプ";
    const Vec2 center(Scene::Center().x, 120);
    FontAsset(U"Title")(titleText).drawAt(center.movedBy(4, 6), ColorF(0.0, 0.5));
    FontAsset(U"Title")(titleText).drawAt(center);
    
    m_tutorialButton.draw(ColorF(1.0, m_tutorialTransition.value())).drawFrame(2);
    
    m_stage1Button.draw(ColorF(1.0, m_stage1Transition.value())).drawFrame(2);
    m_stage2Button.draw(ColorF(1.0, m_stage2Transition.value())).drawFrame(2);
    m_stage3Button.draw(ColorF(1.0, m_stage3Transition.value())).drawFrame(2);
    
    
    m_exitButton.draw(ColorF(1.0, m_exitTransition.value())).drawFrame(2);
    
    FontAsset(U"Menu")(U"チュートリアル").drawAt(m_tutorialButton.center(), ColorF(0.25));
    FontAsset(U"Menu")(U"ステージ 1").drawAt(m_stage1Button.center(), ColorF(0.25));
    FontAsset(U"Menu")(U"ステージ 2").drawAt(m_stage2Button.center(), ColorF(0.25));
    FontAsset(U"Menu")(U"ステージ 3").drawAt(m_stage3Button.center(), ColorF(0.25));
    
    FontAsset(U"Menu")(U"おわる").drawAt(m_exitButton.center(), ColorF(0.25));
    
    Rect(0, 500, Scene::Width(), Scene::Height() - 500)
    .draw(Arg::top = ColorF(0.0, 0.0), Arg::bottom = ColorF(0.0, 0.5));
    
//    const int32 highScore = getData().highScore;
//    FontAsset(U"Score")(U"High score: {}"_fmt(highScore)).drawAt(Vec2(620, 550));
}
