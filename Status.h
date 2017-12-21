#pragma once
#include<stdio.h>
#define snow_max 13
#define moonlight_max 13
#define flower_max 13
#define other_max 3
#define all_max snow_max*moonlight_max*flower_max*other_max
#define node_max 1000
/*
ゲームの数値をまとめたファイルです
all_maxについて　{雪の最大設置数＋０の手＊月（以下同文）＊花（以下同文）＊一個異なる駒おくかおかないか}

*/

enum PRIESTESS {
	NONE,
	SNOW,
	MOONLIGHT,
	FLOWER,
};

struct player {
	//所持している駒
	int snow_piece;
	int moonlight_piece;
	int flower_piece;

	int snow_card[3];
	int moonlight_card[3];
	int flower_card[3];

	PRIESTESS contract_priestess;
    PRIESTESS target_priestess;
};

struct position {
	
	//設置された駒の数
	int snow_piece;
	int moonlight_piece;
	int flower_piece;

	//設置された紋,雪月花の数
	int snow_motif;
	int moonlight_motif;
	int flower_motif;
	int beauties_season_motif;

	int card[3];

};

struct start {
	//設置された駒の数
	int snow_piece;
	int moonlight_piece;
	int flower_piece;
};

struct flag {
	int moon_card_flag_1;
	int moon_card_flag_2;
	int flower_card_flag;
};


/*AI用*/
struct play {
    int erea;
    int type;
    int number;
};

struct hand {
    struct play forecast_move[4];
    int hand_count;
};

struct target_erea {
    int snow_erea;
    int moonlight_erea;
    int flower_erea;
};

typedef struct child {
    struct play one_move[4];
    int games;
    double rate;
    int next;
}CHILD;

typedef struct node {
    int child_num;
    CHILD child[all_max];
    int game_sum;
}NODE;


struct player player[2];
struct player backup_player[2];
struct play move[4];

//駒３種　紋3つと雪月花１つ　ｶｰﾄﾞ3種
struct position snow = { 0,0,0, 0,0,0,0 ,{1,2,3} };
struct position moonlight = { 0,0,0, 0,0,0,0 ,{ 1,2,3 } };
struct position flower = { 0,0,0, 0,0,0,0 ,{ 1,2,3 } };
/*ここからはAI用*/
struct hand kouho[all_max];
struct hand kifu[all_max];
struct position backup_snow;
struct position backup_moonlight;
struct position backup_flower;
struct start backup_source;
struct start source = { 10,10,10 };
struct flag card_flag = {0,0,0};
struct target_erea ai_target {0,0,0};
NODE node[node_max];


/*デバックモード用*/
/*
struct player player[2];
//駒３種　紋3つと雪月花１つ　ｶｰﾄﾞ3種
struct position snow = { 12,12,12, 12,12,12,0 ,{1,2,3} };
struct position moonlight = { 12,12,12, 12,12,12,0 ,{ 1,2,3 } };
struct position flower = { 12,12,12, 12,12,12,0 ,{ 1,2,3 } };
struct start source = { 12,12,12 };
struct flag card_flag = {0,0,0};
*/

enum DICE {
	SNOW_ONLY,
	MOONLIGHT_ONLY,
	FLOWER_ONLY,
	SNOW_MOONLIGHT,
	SNOW_FLOWER,
	MOONLIGHT_FLOWER,
};

int node_num;
