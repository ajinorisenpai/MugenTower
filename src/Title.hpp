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
#include "Game.hpp"

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
    void update() override
    {
        m_startTransition.update(m_startButton.mouseOver());
        m_exitTransition.update(m_exitButton.mouseOver());
        
        if (m_startButton.mouseOver() || m_exitButton.mouseOver())
        {
            Cursor::RequestStyle(CursorStyle::Hand);
        }
        
        if (m_startButton.leftClicked())
        {
            changeScene(State::Game);
        }
        
        if (m_exitButton.leftClicked())
        {
            System::Exit();
        }
    }
    
    void draw() const override
    {
        const String titleText = U"ブロックくずし";
        const Vec2 center(Scene::Center().x, 120);
        FontAsset(U"Title")(titleText).drawAt(center.movedBy(4, 6), ColorF(0.0, 0.5));
        FontAsset(U"Title")(titleText).drawAt(center);
        
        m_startButton.draw(ColorF(1.0, m_startTransition.value())).drawFrame(2);
        m_exitButton.draw(ColorF(1.0, m_exitTransition.value())).drawFrame(2);
        
        FontAsset(U"Menu")(U"はじめる").drawAt(m_startButton.center(), ColorF(0.25));
        FontAsset(U"Menu")(U"おわる").drawAt(m_exitButton.center(), ColorF(0.25));
        
        Rect(0, 500, Scene::Width(), Scene::Height() - 500)
        .draw(Arg::top = ColorF(0.0, 0.0), Arg::bottom = ColorF(0.0, 0.5));
        
        const int32 highScore = getData().highScore;
        FontAsset(U"Score")(U"High score: {}"_fmt(highScore)).drawAt(Vec2(620, 550));
    }
};

#endif /* Title_hpp */
