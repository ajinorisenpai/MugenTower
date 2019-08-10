# include <Siv3D.hpp>

void Main()
{
    // フレームレートを 60 に固定
    Graphics::SetTargetFrameRateHz(60);
  
    // 背景色を設定
    Scene::SetBackground(ColorF(0.2, 0.3, 0.4));
    
  
    while (System::Update())
    {
  
    }
}
