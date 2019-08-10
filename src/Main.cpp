#include <Siv3D.hpp>
#include "Game.hpp"
#include "Title.hpp"


// シーン管理クラス

void Main()
{
    // 使用するフォントアセットを登録
    FontAsset::Register(U"Title", 120, U"example/font/AnnyantRoman/AnnyantRoman.ttf");
    FontAsset::Register(U"Menu", 30, Typeface::Regular);
    FontAsset::Register(U"Score", 36, Typeface::Bold);
    
    // 背景色を設定
    Scene::SetBackground(ColorF(0.2, 0.8, 0.4));
    
    // シーンと遷移時の色を設定
    SceneManager<State, GameData> manager;
    manager
    .add<Title>(State::Title)
    .add<Game>(State::Game)
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
