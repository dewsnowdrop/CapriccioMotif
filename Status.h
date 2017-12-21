#pragma once
#include<stdio.h>
#define snow_max 13
#define moonlight_max 13
#define flower_max 13
#define other_max 3
#define all_max snow_max*moonlight_max*flower_max*other_max
#define node_max 1000
/*
�Q�[���̐��l���܂Ƃ߂��t�@�C���ł�
all_max�ɂ��ā@{��̍ő�ݒu���{�O�̎聖���i�ȉ������j���ԁi�ȉ������j����قȂ����������Ȃ���}

*/

enum PRIESTESS {
	NONE,
	SNOW,
	MOONLIGHT,
	FLOWER,
};

struct player {
	//�������Ă����
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
	
	//�ݒu���ꂽ��̐�
	int snow_piece;
	int moonlight_piece;
	int flower_piece;

	//�ݒu���ꂽ��,�ጎ�Ԃ̐�
	int snow_motif;
	int moonlight_motif;
	int flower_motif;
	int beauties_season_motif;

	int card[3];

};

struct start {
	//�ݒu���ꂽ��̐�
	int snow_piece;
	int moonlight_piece;
	int flower_piece;
};

struct flag {
	int moon_card_flag_1;
	int moon_card_flag_2;
	int flower_card_flag;
};


/*AI�p*/
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

//��R��@��3�Ɛጎ�ԂP�@����3��
struct position snow = { 0,0,0, 0,0,0,0 ,{1,2,3} };
struct position moonlight = { 0,0,0, 0,0,0,0 ,{ 1,2,3 } };
struct position flower = { 0,0,0, 0,0,0,0 ,{ 1,2,3 } };
/*���������AI�p*/
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


/*�f�o�b�N���[�h�p*/
/*
struct player player[2];
//��R��@��3�Ɛጎ�ԂP�@����3��
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
