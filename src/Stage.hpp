//
//  Stage.hpp
//  empty
//
//  Created by 坂井創一 on 2019/08/27.
//

#ifndef Stage_hpp
#define Stage_hpp

#include <stdio.h>
#include <Siv3D.hpp>

using std::vector;
class Stage{
private:
    vector<vector<int>> map_data;
public:
    Stage(){
        map_data = vector<vector<int>>(30,vector<int>(30,0));
        for(int i:step(30)){
            map_data[i][0] = 1;
            map_data[0][i] = 1;
            map_data[11][i] = 1;
            map_data[i][9] = 1;
        }
    }
    void load_stage(){
    }
    const void draw() const{
        for(int y:step(30)){
            for(int x:step(30)){
                if(map_data[x][y] != 0)
                RoundRect(x*64,y*64,64,64,10).draw(Color(30*y, 200, 30*x));
            }
        }
    };
};
#endif /* Stage_hpp */
