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
        map_data = vector<vector<int>>(300,vector<int>(300,0));
        for(int i:step(30)){
            map_data[i][0] = 2;
            map_data[0][i] = 1;
            map_data[11][i] = 1;
            map_data[i][8] = 1;
            map_data[29][i] = 1;
            
            map_data[i][29] = 1;
        }
        map_data[10][0] = 1;
        map_data[5][7] = 1;
        map_data[5][6] = 1;
        map_data[11][3] = 0;
        map_data[4][5] = 3;
        map_data[4][7] = 3;
        map_data[4][6] = 3;
        
    }
    void load_stage(){
    }
    vector<vector<int>> GetMapData() const {return map_data;};
    const void draw() const{
        for(int y:step(30)){
            for(int x:step(30)){
                if(map_data[x][y] == 1) RoundRect(x*64,y*64,64,64,10).draw(Color(30, 200, 30));
                if(map_data[x][y] == 2) RoundRect(x*64,y*64,64,64,10).draw(Color(120, 120, 120));
                if(map_data[x][y] == 3)
                    RoundRect(x*64,y*64,64,64,10).draw(Color(200, 0,0));
            }
        }
    };
};
#endif /* Stage_hpp */
