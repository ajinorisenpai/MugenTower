#include <Siv3D.hpp>
#include "Game.hpp"
#include "Title.hpp"
#include "Debug.hpp"
void Main()
{
    FontAsset::Register(U"Title", 80, U"example/font/AnnyantRoman/AnnyantRoman.ttf");
    FontAsset::Register(U"Menu", 30, Typeface::Regular);
    FontAsset::Register(U"Score", 36, Typeface::Bold);

    Scene::SetBackground(ColorF(0.1, 0.1, 0.1));

    SceneManager<State, GameData> manager;
    manager
    .add<Title>(State::Title)
    .add<Game>(State::Game)
    .add<Debug>(State::Debug)
    .setFadeColor(ColorF(0.0))
    ;
    
    // 現在のモニタで使用可能なフルスクリーン解像度を取得
//    const Array<Size> resolutions = Graphics::GetFullscreenResolutions();
//    
//    if (!resolutions)
//    {
//        throw Error(U"フルスクリーンモードを利用できません。");
//    }
//    // 最大のフルスクリーン解像度にする
//    size_t index = resolutions.size() - 1;
//    if (!Window::SetFullscreen(true, resolutions[index]))
//    {
//        throw Error(U"フルスクリーンモードへの切り替えに失敗しました。");
//    }
//    
    while (System::Update())
    {
        if (!manager.update())
        {
            break;
        }
    }
}
