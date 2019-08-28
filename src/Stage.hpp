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
    Vec2 StartPos = Vec2(400,400);
    bool tutorial_flag = false;
public:
    Stage(String path){
        map_data = vector<vector<int>>(100,vector<int>(100,0));
        CSVData csv(path);
        Array<Array<String>> in_file = csv.getData();
        //あとで直す
        int yy = 0;
        for(auto row : in_file){
            int xx = 0;
            for(auto column: row){
                map_data[xx][yy] = Parse<int32>(column);
                if(map_data[xx][yy] == 16){
                    StartPos = Vec2(xx*64+32,yy*64+32);
                }
                xx++;
            }
            yy++;
        }
        if(path==U"Levels/tutorial.csv"){
            tutorial_flag = true;
        }
        
    }
    
    void load_stage(){
    }
    vector<vector<int>> GetMapData() const {return map_data;};
    Vec2 GetStartPos() const {return StartPos;};
    // 0b00001：触れる
    // 0b00010 : ワイヤーかけられない
    // 0b00100 : 触ると死ぬ
    // 0b01000 : ゴール
    // 0b10000 : スタート
    const void draw() const{
        for(int y:step(100)){
            for(int x:step(100)){
                     if(map_data[x][y] == 0b0001) RoundRect(x*64,y*64,64,64,10).draw(Color(30, 200, 30));
                else if(map_data[x][y] == 0b0010)
                    RoundRect(x*64,y*64,64,64,10).draw(Color(50,50,50));
                else if(map_data[x][y] == 0b0011)
                     RoundRect(x*64,y*64,64,64,10).draw(Color(100,100,100));
                else if(map_data[x][y] == 0b0100)
                    RoundRect(x*64,y*64,64,64,10).draw(Color(180, 0, 100));
                else if(map_data[x][y] == 0b0101)
                    RoundRect(x*64,y*64,64,64,10).draw(Color(225, 190, 190));
                else if(map_data[x][y] == 0b0110)
                    RoundRect(x*64,y*64,64,64,10).draw(Color(200, 40,40));
                else if(map_data[x][y] == 0b0111)
                    RoundRect(x*64,y*64,64,64,10).draw(Color(200, 0,0));
                else if(map_data[x][y] == 0b1000)
                    Rect(x*64+10,y*64-10,44,74).draw(Color(200, 200,100));
                    
            }
        }
        if(tutorial_flag){
            
        }
    };
};
#endif /* Stage_hpp */