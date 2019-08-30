#ifndef Enemy_hpp
#define Enemy_hpp

#include <Siv3D.hpp>

class Enemy{
private:
    
public:
    static constexpr Size blockSize = Size(64,64);
    Rect rect;
    
    Enemy(Vec2 p){
        rect = Rect(p.x * Enemy::blockSize.x, 60 + p.y * Enemy::blockSize.y,
                    Enemy::blockSize.x,Enemy::blockSize.y);
    }
    bool collision(Circle& c){
        return rect.intersects(c);
    }
    void update(){
        
    }
    
    void draw() const{
        rect.stretched(-1).draw(HSV(rect.y - 40));
    };
    
};

#endif /* Enemy_hpp */
