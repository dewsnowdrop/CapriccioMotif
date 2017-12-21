#pragma once
#include<stdio.h>
#include"Status.h"
#include"System_Flow.h"

//プレイヤーの持ち駒を返します
int Check_Player_Piece(int player_id,int put_piece) {
	switch (put_piece) {
	case SNOW: 
		return player[player_id].snow_piece;
		break;
	case MOONLIGHT:
		return player[player_id].moonlight_piece;
		break;
	case FLOWER:
		return player[player_id].flower_piece;
		break;
	default:
		printf("Error：Check_Player_Piece不正な処理です%d\n",__LINE__);
        printf("Check_Player_Piece put_piece=%d\n",put_piece);
        return 0;
        break;

	}

}

//駒を置けるかどうか判別します
int Check_Put_Piece(int player_id,int put_target,int put_piece,int put_number){//プレイヤー、置く場所、置くピースの種類、置く数
	//置こうとしている駒,プレイヤーの持ち駒
	//0以下を置こうとしているか手元の駒以上を置こうとしている
	int player_piece;
	player_piece = 0;
   
	player_piece = Check_Player_Piece(player_id, put_piece);

    if (player_piece == 0) {printf ("何も置けませんでした"); return 0; }
	else if (0 > put_number || player_piece < put_number) { printf("置こうとしている数が適正ではありません。"); return 1; }
	else if (put_target != put_piece && put_number > 1) { printf("紋の異なる場所には1つしか置けません"); return 1; }
    else if (put_target != put_piece && put_number == 1) {  return 2; }
    else {  return 0; }//正常
}

//紋を作れるかどうか判断します
int Check_Motif(int target , int type ,int num) {

	switch (target) {

	case SNOW:
		switch (type) {

		case SNOW:
			if (snow.snow_piece >= num * 3) { return 1; }
			else { printf("作成するための駒が足りません\n"); return 0; }
		case MOONLIGHT:
			if (snow.moonlight_piece >= num * 3) {  return 1; }
			else { printf("作成するための駒が足りません\n"); return 0; }
		case FLOWER:
			if (snow.flower_piece >= num * 3) { return 1; }
			else { printf("作成するための駒が足りません\n"); return 0; }

		}
	case MOONLIGHT:
		switch (type) {

		case SNOW:
			if (moonlight.snow_piece >= num * 3) { return 1; }
			else { printf("作成するための駒が足りません\n"); return 0; }
		case MOONLIGHT:
			if (moonlight.moonlight_piece >= num * 3) { return 1; }
			else { printf("作成するための駒が足りません\n"); return 0; }
		case FLOWER:
			if (moonlight.flower_piece >= num * 3) {  return 1; }
			else { printf("作成するための駒が足りません\n"); return 0; }

		}
	case FLOWER:
		switch (type) {

		case SNOW:
			if (flower.snow_piece >= num * 3) { return 1; }
			else { printf("作成するための駒が足りません\n"); return 0; }
		case MOONLIGHT:
			if (flower.moonlight_piece >= num * 3) { return 1; }
			else { printf("作成するための駒が足りません\n"); return 0; }

		case FLOWER:
			if (flower.flower_piece >= num * 3) { return 1; }
			else { printf("作成するための駒が足りません\n"); return 0; }


		}
	default:
		return 0;
		break;
	}

}

//雪月花が作成可能かどうか判断します
int Check_BeautiesSeasonMotif(int player_id,int target) {
	if (snow.snow_motif > 0 && moonlight.moonlight_motif > 0 && flower.flower_motif > 0) {//対応した紋が一つ以上ある

		if (player[player_id].snow_piece == player[player_id].moonlight_piece == player[player_id].flower_piece == 0) {//手ごまが0である

			switch (target)
			{
			case SNOW:
				if (player[player_id].contract_priestess == NONE && snow.beauties_season_motif == 0) { return 1; }//まだ誰にもとられていない
				else if(player[player_id].contract_priestess == SNOW){ return 1; }//一個以上あるが自分の陣地である
				else if (player[player_id].contract_priestess > NONE && player[(player_id + 1) % 2].contract_priestess != SNOW) { return 1; }//陣地はあるがまだとられていない
				else { return 0; }
				break;

			case MOONLIGHT:
				if (player[player_id].contract_priestess == NONE && moonlight.beauties_season_motif == 0) { return 1; }
				else if (player[player_id].contract_priestess == MOONLIGHT) { return 1; }//一個以上あるが自分の陣地である
				else if (player[player_id].contract_priestess > NONE && player[(player_id + 1) % 2].contract_priestess != MOONLIGHT) {return 1; }//陣地はあるがまだとられていない
				else { return 0; }
				break;

			case FLOWER:
				if (player[player_id].contract_priestess == NONE && flower.beauties_season_motif == 0) { return 1; }
				else if (player[player_id].contract_priestess == FLOWER) { return 1; }//一個以上あるが自分の陣地である
				else if (player[player_id].contract_priestess > NONE && player[(player_id + 1) % 2].contract_priestess != FLOWER) { return 1; }//陣地はあるがまだとられていない
				else { return 0; }
				break;

			default:
				break;
			}
		}
	}
	return 0;
}

//陣地にある雪月花の数を返します
int BeautiesSeasonMotif_Numbers(int player_id) {
	switch (player[player_id].contract_priestess) {
	case SNOW:
		return snow.beauties_season_motif;
		break;
	case MOONLIGHT:
		return moonlight.beauties_season_motif; 
		break;
	case FLOWER:
		return flower.beauties_season_motif; 
		break;
	default:
		return 0;
		break;

	}
}

//勝利条件を判別します
int Check_Winner(int player_id) {//TODO
	int player1;
	int player2;
	player1 = BeautiesSeasonMotif_Numbers(player_id);
	player2 = BeautiesSeasonMotif_Numbers((player_id + 1) % 2);
	//雪月花の作成数が３
	if (player1 == 3) { return 1; }
	//両方の雪月花の作成数が３（均衡状態）
	else if (player1 == 3 && player2 == 3) { return 2; }
	//相手のみ勝利条件を満たしている
	else if (player1 <= 3 && player2 == 3) { return 3; }
	//雪月花の作成数が４
	else if (player1 == 4) { return 4; }
	else { return 5; }//続行
}

//指定した数値以外をはじきます
int Check_Nunber(int min, int max) {
	int number = 0;
	number = GetNumberInput();
	if (min <= number && number <= max) { return number; }
	else if (number < min) {
		printf("%d以下の数値を入力しています\n",min);
		return 0;
	}
	else if (number > max) {
		printf("%d以上の数値を入力しています\n",max);
		return 0;
	}
	else {
		printf("不正な数値です\n");
        return 0;
	}

}

//盤面にある紋の合計数を返します
int Check_Motif_Number() {
	int motif_number = 0;
	for (int i = 1; i <= 3;i++) {
		motif_number = +SnowErea_Motif_Numbers(i) + MoonlightErea_Motif_Numbers(i) + FlowerErea_Motif_Numbers(i);
	}
	return motif_number;
}

//雪の陣地の紋の数を返します
int SnowErea_Motif_Numbers(int area) {
	switch (area) {
	case SNOW:
		return snow.snow_motif;
		break;
	case MOONLIGHT:
		return snow.moonlight_motif;
		break;
	case FLOWER:
		return snow.flower_motif;
		break;
	default:
        return 0;
		break;
	}
}

//月の陣地の紋の数を返します
int MoonlightErea_Motif_Numbers(int area) {
	switch (area) {
	case SNOW:
		return moonlight.snow_motif;
		break;
	case MOONLIGHT:
		return moonlight.moonlight_motif;
		break;
	case FLOWER:
		return moonlight.flower_motif;
		break;
	default:
        return 0;
		break;
	}
}

//花の陣地の紋の数を返します
int FlowerErea_Motif_Numbers(int area) {
	switch (area) {
	case SNOW:
		return flower.snow_motif;
		break;
	case MOONLIGHT:
		return flower.moonlight_motif;
		break;
	case FLOWER:
		return flower.flower_motif;
		break;
	default:
        printf("error\n");
        return 0;
		break;
	}
}

//指定したタイプの紋が何個あるかを返します
int Motif_SumNum(int type) {

    switch (type) {
    case SNOW:
        return snow.snow_motif + moonlight.snow_motif + flower.snow_motif;
    case MOONLIGHT:
        return snow.moonlight_motif + moonlight.moonlight_motif + flower.moonlight_motif;
    case FLOWER:
        return snow.flower_motif + moonlight.flower_motif + flower.flower_motif;


    }

    return 0;

}

//手元で紋や雪月花を作れるかどうか
int Check_Player_Motif(int player_id,int type) {
	//規定値に達するのかどうか調べる。変数１：誰の　変数２：case別　
	//変数２について：１　必要数の紋の数を調べる　２、手元で雪月花が作れるか調べる
	//can 紋が作れるかどうかの一時的な変数ですカードの効果で使用する為追加しました。
	//１で続行０で失敗です
	int can_snow=0;
	int can_moonlight = 0;
	int can_flower = 0;
	int sum = 0;
	switch (type) {
	case 1://snowカード２の効果に必要
		
		can_snow = player[player_id].snow_piece / 3;
		can_moonlight = player[player_id].moonlight_piece / 3;
		can_flower = player[player_id].flower_piece / 3;
		sum = can_snow + can_moonlight + can_flower;
		if (sum >= 2) { return 1; }
		 return 0;
		break;
	case 2://月のカード１の効果に必要　雪月花が手元で作れるかどうか
		if (player[player_id].snow_piece > 0) {
			if (player[player_id].moonlight_piece > 0) {
				if (player[player_id].flower_piece > 0) {
					return 1;
				}

			}

		}
		return 0;
		break;
	default:
        printf("error\n");
        return 0;
		break;
	}
}

//プレイヤーの駒の合計値をチェックします
int Sum_Player_Piece(int player_id) {
	return Check_Player_Piece(player_id, SNOW) + Check_Player_Piece(player_id, MOONLIGHT) + Check_Player_Piece(player_id, FLOWER);
}

//盤面の駒の合計値を返します
int Sum_Board_Piece() {
	int sum = 0;
	sum += snow.snow_piece + snow.moonlight_piece + snow.flower_piece;
	sum += moonlight.snow_piece + moonlight.moonlight_piece + moonlight.flower_piece;
	sum += flower.snow_piece + flower.moonlight_piece + flower.flower_piece;
	return sum;
}

//カードが使用できるかチェックします
int Check_Card(int player_id,int type,int number) {

    if (type == SNOW) {
        switch (number)
        {
        case 1:
            if(player[player_id].snow_card[0]==1){ return 1; }
            else { return 0; }
            break;
        case 2:
            if (player[player_id].snow_card[1] == 2) { return 1; }
            else { return 0; }
            break;
        case 3:
            if (player[player_id].snow_card[2] == 3) { return 1; }
            else { return 0; }
            break;
        default:
            printf("error\n");
            return 0;
            break;
        }
    }
    else if (type == MOONLIGHT) {
        switch (number)
        {
        case 1:
            if (player[player_id].moonlight_card[0] == 1) { return 1; }
            else { return 0; }
            break;
        case 2:
            if (player[player_id].moonlight_card[1] == 2) { return 1; }
            else { return 0; }
            break;
        case 3:
            if (player[player_id].moonlight_card[2] == 3) { return 1; }
            else { return 0; }
            break;
        default:
            printf("error\n");
            return 0;
            break;
        }
    }
    else if (type == FLOWER) {
        switch (number)
        {
        case 1:
            if (player[player_id].flower_card[0] == 1) { printf("このカードは相手のカード使用時に割り込んで使うものです"); return 0; }
            else { return 0; }
            break;
        case 2:
            if (player[player_id].flower_card[1] == 2) { return 1; }
            else { return 0; }
            break;
        case 3:
            if (player[player_id].flower_card[2] == 3) { return 1; }
            else { return 0; }
            break;
        default:
            printf("error\n");
            return 0;
            break;
        }
    }

    printf("error\n");
    return 0;
}

int Other_Piece_Checker(int player_id,int type) {
    int achieve = 0;
    switch (type) {
    case SNOW:
        
        return player[player_id].moonlight_piece + player[player_id].flower_piece;
        break;
    case MOONLIGHT:
        return player[player_id].snow_piece + player[player_id].flower_piece;
        break;
    case FLOWER:
        return player[player_id].snow_piece + player[player_id].moonlight_piece;
        break;

    }
    return 0;
}
//盤面の陣地の駒の値を返します
int Erea_PieceNumber(int erea,int type) {
    switch (erea) {
    case SNOW:
        if (type == SNOW) { return snow.snow_piece; }
        else if (type == MOONLIGHT) { return snow.moonlight_piece; }
        else if (type == FLOWER) { return snow.flower_piece; }
        break;
    case MOONLIGHT:
        if (type == SNOW) { return moonlight.snow_piece; }
        else if (type == MOONLIGHT) { return moonlight.moonlight_piece; }
        else if (type == FLOWER) { return moonlight.flower_piece; }
        break;
    case FLOWER:
        if (type == SNOW) { return flower.snow_piece; }
        else if (type == MOONLIGHT) { return flower.moonlight_piece; }
        else if (type == FLOWER) { return flower.flower_piece; }
        break;

    }

    return 0;

}

//勝敗判定を判断します
int Judge(int player_id) {//勝利判定 0or1で終了、２で続行

    if (Check_Winner(player_id) == 1) { return 2; }//片方が勝利条件を満たす
    else if (Check_Winner(player_id) == 2) { return 2; } //均衡状態
    else if (Check_Winner(player_id) == 3) { return (player_id + 1) % 2; } //均衡状態になら無かった場合
    else if (Check_Winner(player_id) == 4) { return (player_id); }//先に４つ雪月花を作った場合
    else { return 2; }
}