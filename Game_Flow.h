#pragma once
#include<stdio.h>
/*
ゲームの流れを表現するファイルです
インデントが下がる理由として一つの関数に下がっているプログラムを内包していることを示している
プログラムの流れをプロトタイプ宣言を使って構築している
*/
void Draw_Board();      //画面表示
void AcquirePiece(int);	//駒の獲得
  void Destroy_Motif(int);	//紋の破壊
void Put_Piece(int);		//駒の設置
void Create_Motif(int);//紋の作成
  void Make_Motif(int, int, int, int);	//紋の選択  
    void Motif_Effect(int, int, int);	//紋の効果の選択  
      void Snow_Effect(int);			//雪の紋の効果
	  void Moonlight_Effect(int, int);	//月の紋の効果
	  void Flower_Effect(int);			//花の紋の効果
void Create_BeautiesSeasonMotif(int);	//雪月花の作成
  void Make_BeautiesSeasonMotif(int, int);//雪月花の処理
    void BeautiesSeasonMotif_Effect(int);//雪月花の効果
void Get_Card(int,int);					//カード取得の処理
  void Select_Card(int, int, int);		//カードの選択
    int Snow_CardEffect(int,int);		  //雪のカードの効果
    int Moonlight_CardEffect(int, int);	//月のカードの効果
    int Flower_CardEffect(int, int);		//花のカードの効果
int Judge(int);							//勝敗判定

/*未実装のシステムリスト：
エラーメッセージの追加
AI
PlayerSelect
現在行っている作業：AIの作成、コードの改善（数値の入力を変える作業）

*/