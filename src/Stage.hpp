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
    const int VIS_RANGE = 20;
    Texture texture_tile01;
    Texture texture_background;
    Texture global_map;
public:
    Stage(String path){
        map_data = vector<vector<int>>(110,vector<int>(110,0));
        CSVData csv(Resource(path));
        Array<Array<String>> in_file = csv.getData();
        //あとで直す
        int yy = 0;
        for(auto row : in_file){
            int xx = 0;
            for(auto column: row){
                if(xx>=100 || yy >=100) break;
                map_data[xx][yy] = Parse<int32>(column);
                if(map_data[xx][yy] == 16){
                    StartPos = Vec2(xx*64+32,yy*64+32);
                }
                xx++;
            }
            yy++;
        }
        if(path==Resource(U"Levels/tutorial.csv")){
            tutorial_flag = true;
        }
        texture_tile01 = Texture(U"Image/map_tile.png");
        texture_background = Texture(U"Image/background.png");
        for(auto y : step(100)){
            for(auto x : step(100)){
                if(map_data[x][y] == 0b0001){
                    
                }
            }
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
    const void bg_draw(Vec2 pos) const{
        Point bgsize = texture_background.size();
        //あとでなおす
        texture_background.draw(-800,0);
        texture_background.draw(bgsize.x-800,0);
        texture_background.draw(-800,bgsize.y);
        texture_background.draw(bgsize.x-800,bgsize.y);
    }
    const void draw(Vec2 pos) const{
        int sx = (int)pos.x/64;
        int sy = (int)pos.y/64;
        for(int y = sy-VIS_RANGE;y<sy+VIS_RANGE;y++){
            for(int x =sx-VIS_RANGE;x<sx+VIS_RANGE;x++){
                if(y<0||x<0||y>=100||x>=100) continue;
                if(map_data[x][y] == 0b0001){
//                    texture_tile01(2*64,1*64,64,64).draw(x*64,y*64);
                    RoundRect(x*64+2,y*64+2,64-4,64-4,10).draw(Color(80,80,80,150)).drawFrame(3, 3,Color(30, 200, 30));
                }
                
                else if(map_data[x][y] == 0b0010)
                    RoundRect(x*64,y*64,64,64,10).drawFrame(3, 3, Palette::Black);
                else if(map_data[x][y] == 0b0011)
                     RoundRect(x*64+2,y*64+2,64-4,64-4,10).draw(Color(10,10,10,200)).drawFrame(3, 3, Color(40,40,40));
                else if(map_data[x][y] == 0b0100)
                    RoundRect(x*64,y*64,64,64,10).drawFrame(3, 3,Color(180, 0, 100));
                else if(map_data[x][y] == 0b0101)
                    RoundRect(x*64,y*64,64,64,10).draw(Color(225, 190, 190));
                else if(map_data[x][y] == 0b0110)
                    RoundRect(x*64,y*64,64,64,10).drawFrame(3, 3,Color(200, 40,40));
                else if(map_data[x][y] == 0b0111)
                    RoundRect(x*64,y*64,64,64,10).draw(Color(200, 0,0));
                else if(map_data[x][y] == 0b1000)
                    Rect(x*64+10,y*64-10,44,74).draw(Color(200, 200,100));
                    
            }
        }
        
        if(tutorial_flag){
            FontAsset(U"Menu")(U"左右キーで移動").drawAt(Vec2(64*4,64*96), ColorF(0.25));
            FontAsset(U"Menu")(U"Xキーでジャンプ").drawAt(Vec2(64*16,64*96), ColorF(0.25));
        FontAsset(U"Menu")(U"ジャンプ中にXキーでワイヤーアクション").drawAt(Vec2(64*30,64*96), ColorF(0.25));
        FontAsset(U"Menu")(U"押す長さによって角度を変えられる").drawAt(Vec2(64*30,64*97), ColorF(0.25));
            
        FontAsset(U"Menu")(U"灰色ブロックはワイヤーが引っかからない").drawAt(Vec2(64*50,64*96), ColorF(0.25));
       
       FontAsset(U"Menu")(U"Cキーを長押しすれば周りを見ることができる").drawAt(Vec2(64*60,64*97), ColorF(0.25)); FontAsset(U"Menu")(U"赤色ブロックに当たるとゲームオーバー").drawAt(Vec2(64*70,64*96), ColorF(0.25));
        FontAsset(U"Menu")(U"黄色い扉の前でジャンプするとゲームクリアだ").drawAt(Vec2(64*92,64*96), ColorF(0.25));
        }
        
        
    };
    void EditStage(Vec2 pos,int id){
        int px = (int)pos.x/64;
        int py = (int)pos.y/64;
        if(py<0||px<0||py>=100||px>=100) return;
        map_data[px][py] = id;
    }
    void ResetStartPos(Vec2 pos){
        StartPos = pos;
    }
    void ExportMapData(){
        CSVData csv;
        for(int y=0;y<100;y++){
            for(int x=0;x<100;x++){
                csv.write(map_data[x][y]);
            }
            csv.newLine();
        }
        csv.save(Resource(U"./Levels/stage_edit.csv"));
    }
};
#endif /* Stage_hpp */
