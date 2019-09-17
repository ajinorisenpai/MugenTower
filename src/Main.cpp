#include <Siv3D.hpp>
#include "Game.hpp"
#include "Title.hpp"
#include "Debug.hpp"
void Main()
{
    //ウィンドウサイズなど
    Window::Resize(1280,900);
    Scene::SetBackground(Color(0x15, 0x13, 0x27));
    Window::SetStyle(WindowStyle::Frameless);
    
    
    //フォントアセット
    FontAsset::Register(U"Title", 80, Resource(U"font/AnnyantRoman.ttf"));
    FontAsset::Register(U"Menu", 30, Typeface::Regular);
    FontAsset::Register(U"Score", 36, Typeface::Bold);
    FontAsset::Register(U"Debug", 16, Typeface::Regular);
    
    
    //シーンマネージャー
    SceneManager<State, GameData> manager;
    manager
    .add<Title>(State::Title)
    .add<Game>(State::Game)
    .add<Debug>(State::Debug)
    .setFadeColor(ColorF(0.0))
    ;
   
    while (System::Update())
    {
        if (!manager.update())
        {
            break;
        }
    }
}
