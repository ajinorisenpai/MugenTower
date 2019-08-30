#ifndef Burn_hpp
#define Burn_hpp

#include <Siv3D.hpp>

struct Burn:IEffect{
private:
    Vec2 m_pos;
    Color m_color;
public:
    Burn(const Vec2& pos)
    :m_pos(pos),
    m_color(RandomColor()){}
    bool update(double t) override{
        const double e = EaseOutExpo(t);
        Circle(m_pos,e * 100).drawFrame(20.0*(1.0-e),m_color);
        return t < 1.0;
    }
};
#endif /* Burn_hpp */
