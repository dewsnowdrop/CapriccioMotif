#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#include"Status.h"
#include"Checker.h"
#include"System.h"
#include"Option.h"
/*
インデントを下げてどのような関数で構成されているか示しています
コメントアウトで同じ関数を表記している場合があります
*/


/*mainループ内*/
void Ramdom_Set_Target(int);

void AI_Get_Piece(int);
    void AI_Destroy_Motif(int);//紋の破壊
//最も良い手を探します
void Select_Best_Uct(int);

    //ノードを作成します
    int Create_Node(int);
        //小木を追加していきます
        void Add_Child(NODE *, int, int, int, int, int, int);
            //指定された数値に対応したタイプを返します
            int Set_NumberType(int );
    //相手と盤面すべての手を保存します
    void Backup_All(int);
        //ボード上の駒の保存
        void Backup_Board();
        //プレイヤー手持ちの保存
        void Backup_PlayerHand(int);

    //UCBで手を選び降りていく
    int Search_Uct(int, int);//※
        //小木のノードに配置した手を呼び出します
        void Call_ChildHand(CHILD*);
        //AI内で実行する用
        int AI_Move(int);
        int AI_Check_Put_Piece(int, int, int, int);
        //プレイアウト
        int Playout(int);//※
            //プレイヤーが行える手の全列挙を行い,何手あったか返します
            int Kouho_List(int);
                //候補を構造体に値を入れる関数です
                void KouhoList_Set(int, int, int, int, int, int, int);
            //候補に手をセットします
            void Kouho_MoveSet(int);
            //AI_Move（）；
            //候補から数値を減らします
            void KouhoList_Delete(int,int);
            //未完成
            int Count_Score(int);
        //Search_Uct(int, int);

    //保存した相手と盤面すべての手を呼び出します
    void Call_All(int);
    //保存した盤面の駒の呼び出し
    void Call_Board();
    //プレイヤー手持ちの呼び出し
    void Call_PlayerHand(int);

    //最も良かった手をmoveの構造体に格納します
    void Best_Move_Set(NODE*, int);

//モンテカルロ用
int Move(int player_id);
    //駒を置いたとき、実際に数値を移動させる関数
    void Move_Num(int, int, int, int);
    
    //雪月花を作ろうとしているエリアで出来るかどうかを選定します
    int Check_BeautiesSeasonMotif_Flag(int);
    
    //AIの紋の作成
    void AI_Make_Motif(int player_id);
        //紋を作る際の数値の移動などをまとめた関数
        void MoveNum_Motif(int, int, int, int);
            //雪の紋の効果　
            void AI_Snow_Effect(int);
            //月の紋の効果 
            void AI_Moonlight_Effect(int, int);
            //花の紋の効果
            void AI_Flower_Effect(int);
                //void AI_Destroy_Motif(int);//紋の破壊
    
    //雪月花をAIが作成
    void AI_Make_BeautiesSeasonMotif(int);
        //雪月花作成の効果
        void AI_BeautiesSeasonMotif_Effect(int);


//構造体の処理が正しく行われているか怪しい
void Set_kifu(int);

