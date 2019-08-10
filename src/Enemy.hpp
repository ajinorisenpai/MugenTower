//
//  Enemy.hpp
//  empty
//
//  Created by 坂井創一 on 2019/08/10.
//

#ifndef Enemy_hpp
#define Enemy_hpp

#include <Siv3D.hpp>

class Enemy{
private:
    
public:
    static constexpr Size blockSize = Size(40,20);
    Rect rect;
    
    Enemy(Rect r){
        rect = r;
    }

    void update(){
        
    }
    
    //メンバ関数の右側にconstをつけると、そのメンバ関数内ではメンバ変数の変更ができなくなる
    void draw() const{
        rect.draw();
    };
    
};

#endif /* Enemy_hpp */
