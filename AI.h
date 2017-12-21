#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<assert.h>

#include"AI_Flow.h"
#include"Status.h"
#include"Checker.h"
#include"System.h"
#include"Option.h"

/*�ϐ������@��ɈقȂ�w�n�Ɉ�u���ꍇ��a=�ݒu����w�n�@b=�ݒu�����@g=�u���������Ȃ���
x=��̐w�n�ɉ��u�����@y=���̐w�n�ɉ��u�����@z=�Ԃ̐w�n�ɉ��u�����@�Őݒ肵�Ă��܂�*/
/*
���_�F
    �v���C�A�E�g���ł��ĂȂ�
    kouho�X�V����Ă��Ȃ�
*/

/*
Move���Ă�ł���ꏊ
Search_Uct(int, int);
int Playout(int);
main()


��肭�����ĂȂ������ȂƂ���

//�m�[�h���쐬���܂�
int Create_Node(int);
//�q�؂�ǉ����Ă����܂�
void Add_Child(NODE *, int, int, int, int, int, int);
�q�̎���Ăяo���܂�
void Call_ChildHand(CHILD*);


//�v���C���[���s�����̑S�񋓂��s��,���肠�������Ԃ��܂�
int Kouho_List(int);
//�����\���̂ɒl������֐��ł�
void KouhoList_Set(int, int, int, int, int, int, int);
//������ɃZ�b�g���܂�
void Kouho_MoveSet(int);

//�ł��ǂ��������move�̍\���̂Ɋi�[���܂�
void best_move_set(NODE*, int);

*/
int all_playouts;
int clock_counter;


//�����̎�낤�Ƃ��Ă���w�n�����߂܂�
void Ramdom_Set_Target(int player_id) {
    int target = 0;
    int box[3] = { SNOW,MOONLIGHT,FLOWER };
    int snow_box[2] = { MOONLIGHT,FLOWER };
    int moonlight_box[2] = { SNOW,FLOWER };
    int flower_box[2] = { SNOW,MOONLIGHT };
    target = box[(rand() % 3)];
    if (player[Enemy(player_id)].target_priestess != (PRIESTESS)target) {
        player[player_id].target_priestess = (PRIESTESS)target;
        return;
    }
    else if (player[Enemy(player_id)].target_priestess == (PRIESTESS)target) {
        switch (target) {
        case SNOW:
            target = snow_box[(rand() % 2)];
            break;
        case MOONLIGHT:
            target = moonlight_box[(rand() % 2)];
            break;
        case FLOWER:
            target = flower_box[(rand() % 2)];
            break;

        }
        player[player_id].target_priestess = (PRIESTESS)target;
        return;
    }
}

//�_�C�X�̖ڂɂ���ē������ł�
void AI_Get_Piece(int player_id) {
    switch (GetDice()) {
    case SNOW_ONLY:
        if (source.snow_piece == 0) { AI_Destroy_Motif(SNOW); }

        if (source.snow_piece == 0) { break; }
        else if (source.snow_piece == 1) {
            source.snow_piece--;
            player[player_id].snow_piece++;
        }
        else {
            source.snow_piece -= 2;
            player[player_id].snow_piece += 2;
        }
        break;
    case MOONLIGHT_ONLY:
        if (source.moonlight_piece == 0) { AI_Destroy_Motif(MOONLIGHT); }

        if (source.moonlight_piece == 0) { break; }
        else if (source.moonlight_piece == 1) {
            source.moonlight_piece--;
            player[player_id].moonlight_piece++;

        }
        else {
            source.moonlight_piece -= 2;
            player[player_id].moonlight_piece += 2;
        }
        break;
    case FLOWER_ONLY:
        if (source.flower_piece == 0) { AI_Destroy_Motif(FLOWER); }

        if (source.flower_piece == 0) { break; }
        else if (source.flower_piece == 1) {
            source.flower_piece--;
            player[player_id].flower_piece++;
        }
        else {
            source.flower_piece -= 2;
            player[player_id].flower_piece += 2;
        }
        break;
    case SNOW_MOONLIGHT:
        if (source.snow_piece == 0) { AI_Destroy_Motif(SNOW); }
        if (source.moonlight_piece == 0) { AI_Destroy_Motif(MOONLIGHT); }

        if (source.snow_piece == 0 && source.moonlight_piece == 0) { break; }
        else if (source.snow_piece == 0) {
            source.moonlight_piece--;
            player[player_id].moonlight_piece++;
        }
        else if (source.moonlight_piece == 0) {
            source.snow_piece--;
            player[player_id].snow_piece++;
        }
        else {
            source.snow_piece--;
            source.moonlight_piece--;
            player[player_id].snow_piece++;
            player[player_id].moonlight_piece++;
        }
        break;
    case SNOW_FLOWER:
        if (source.snow_piece == 0) { AI_Destroy_Motif(SNOW); }
        if (source.flower_piece == 0) { AI_Destroy_Motif(FLOWER); }

        if (source.snow_piece == 0 && source.flower_piece == 0) { break; }
        else if (source.snow_piece == 0) {
            source.flower_piece--;
            player[player_id].flower_piece++;
        }
        else if (source.flower_piece == 0) {
            source.snow_piece--;
            player[player_id].snow_piece++;
        }
        else {
            source.snow_piece--;
            source.flower_piece--;
            player[player_id].snow_piece++;
            player[player_id].flower_piece++;
        }
        break;
    case MOONLIGHT_FLOWER:
        if (source.moonlight_piece == 0) { AI_Destroy_Motif(MOONLIGHT); }
        if (source.flower_piece == 0) { AI_Destroy_Motif(FLOWER); }

        if (source.moonlight_piece == 0 && source.flower_piece == 0) { break; }
        else if (source.flower_piece == 0) {
            source.moonlight_piece--;
            player[player_id].moonlight_piece++;
        }
        else if (source.moonlight_piece == 0) {
            source.flower_piece--;
            player[player_id].flower_piece++;
        }
        else {
            source.moonlight_piece--;
            source.flower_piece--;
            player[player_id].moonlight_piece++;
            player[player_id].flower_piece++;
        }
        break;
    default:
        exit(0);
        break;
    }
}

//��̔j��
void AI_Destroy_Motif(int motif) {//��̔j��
    int i;

    if (motif == SNOW) {//��̖����
        for (i = 0; i < 3; i++) {
            switch (i)
            {
            case 0:
                if (flower.snow_motif > 0) {
                    flower.snow_motif--;
                    source.snow_piece += 3;
                }
                else { continue; }
                break;
            case 1:
                if (moonlight.snow_motif > 0) {
                    moonlight.snow_motif--;
                    source.snow_piece += 3;
                }
                else { continue; }
                break;
            case 2:

                if (snow.snow_motif > 0) {
                    snow.snow_motif--;
                    source.snow_piece += 3;
                }
                else { return; }
                break;
            default:
                printf("�s���ȓ��͂ł�\n");
                break;
            }
        }
    }
    else if (motif == MOONLIGHT) {//���̖����
        for (i = 0; i < 3; i++) {
            switch (i)
            {
            case 0:
                if (snow.moonlight_motif > 0) {
                    snow.moonlight_motif--;
                    source.moonlight_piece += 3;
                }
                else { continue; }
                break;
            case 1:
                if (flower.moonlight_motif > 0) {
                    flower.moonlight_motif--;
                    source.moonlight_piece += 3;
                }
                else { continue; }
                break;
            case 2:

                if (moonlight.moonlight_motif > 0) {
                    moonlight.moonlight_motif--;
                    source.moonlight_piece += 3;
                }
                else { return; }

                break;
            default:
                printf("�s���ȓ��͂ł�\n");
                break;
            }
        }
    }
    else if (motif == FLOWER) {//�Ԃ̖����
        for (i = 0; i < 3; i++) {
            switch (i) {

            case 0:
                if (snow.flower_motif > 0) {
                    snow.flower_motif--;
                    source.flower_piece += 3;
                }
                else { continue; }
                break;
            case 1:
                if (moonlight.flower_motif > 0) {
                    moonlight.flower_motif--;
                    source.flower_piece += 3;
                }
                else { continue;; }
                break;
            case 2:
                if (flower.flower_motif > 0) {
                    flower.flower_motif--;
                    source.flower_piece += 3;
                }
                else { return; }
                break;
            default:
                printf("�s���ȓ��͂ł�\n");
                break;
            }
        }
    }
    return;
}

//�ł��ǂ����T���܂�
void Select_Best_Uct(int player_id) {
    node_num = 0;
    int next = Create_Node(player_id);
    int uct_loop = 1000;

    int i;

    for (i = 0; i < uct_loop; i++) {
        Backup_All(player_id);
        Search_Uct(player_id, next);
        Call_All(player_id);
    }
    int best_i = -1;
    int max = -999;
    NODE *pN = &node[next];
    for (i = 0; i < pN->child_num; i++) {
        CHILD*c = &pN->child[i];
        if (c->games > max) {
            best_i = i;
            max = c->games;
        }
    }

    Best_Move_Set(pN, best_i);
    printf("rate=%f,games=%d,playouts=%d,nodes=%d\n", pN->child[best_i].rate, max, all_playouts, node_num);
}

//�m�[�h���쐬���܂�
int Create_Node(int player_id) {
    clock_counter++;
    int set_type[3] = { SNOW,MOONLIGHT,FLOWER };
    int snow = 0;
    int moonlight = 0;
    int flower = 0;
    if (node_num == node_max) { printf("node over\n"); exit(0); }
    NODE*pN = &node[node_num];
    pN->child_num = 0;


    for (int a = 0; a < 3; a++)  for (int b = 0; b < 3; b++) {
        // if ((set_type[a] == set_type[b]) && (set_type[a]=!player[player_id].target_priestess)) { continue; }
        if ((set_type[a] == set_type[b]) || (set_type[a] != player[player_id].target_priestess)) { continue; }
        for (int g = 0; g <= 1; g++) {
            snow = player[player_id].snow_piece;
            moonlight = player[player_id].moonlight_piece;
            flower = player[player_id].flower_piece;

           
            if (set_type[b] == SNOW && g == 1 && snow > 0) { snow = snow - 1; }
            else if (snow == 0 && g == 1) { continue; }
            if (set_type[b] == MOONLIGHT && g == 1 && moonlight > 0) { moonlight = moonlight - 1; }
            else if (moonlight == 0 && g == 1) { continue; }
            if (set_type[b] == FLOWER && g == 1&& flower > 0) { flower = flower - 1; }
            else if (flower == 0 && g == 1) { continue; }

            

            for (int snow_count = 0; snow_count <= snow; snow_count++) {
                for (int moonlight_count = 0; moonlight_count <= moonlight; moonlight_count++) {
                    for (int flower_count = 0; flower_count <= flower; flower_count++){
                       
                        Add_Child(pN, set_type[a], set_type[b], g, snow_count, moonlight_count, flower_count);
                    }
                }
            }

        }
    }

    node_num++;
    return node_num - 1;
}

//���؂�ǉ����Ă����܂�
void Add_Child(NODE *pN, int a, int b, int g, int x, int y, int z) {
    int i;
    int n = pN->child_num;

    for (i = 0; i < 4; i++) {
        switch (i) {

        case 0:
            pN->child[n].one_move[i].erea = a;
            pN->child[n].one_move[i].type = b;
            pN->child[n].one_move[i].number = g;
            break;
        case 1:
            pN->child[n].one_move[i].erea = Set_NumberType(i);
            pN->child[n].one_move[i].type = Set_NumberType(i);
            pN->child[n].one_move[i].number = x;
            break;
        case 2:
            pN->child[n].one_move[i].erea = Set_NumberType(i);
            pN->child[n].one_move[i].type = Set_NumberType(i);
            pN->child[n].one_move[i].number = y;
            break;
        case 3:
            pN->child[n].one_move[i].erea = Set_NumberType(i);
            pN->child[n].one_move[i].type = Set_NumberType(i);
            pN->child[n].one_move[i].number = z;
            break;
        }
    }
    pN->child[n].games = 0;
    pN->child[n].rate = 0;
    pN->child[n].next = -1;
    pN->child_num++;

}
//�w�肳�ꂽ���l�ɑΉ������^�C�v��Ԃ��܂�
int Set_NumberType(int number) {
    switch (number) {
    case 1:
        return SNOW;
    case 2:
        return MOONLIGHT;
    case 3:
        return FLOWER;
    }
    return 0;
}
//����ƔՖʂ��ׂĂ̎��ۑ����܂�
void Backup_All(int player_id) {
    Backup_PlayerHand(player_id);
    Backup_PlayerHand(Enemy(player_id));
    Backup_Board();
}

//�{�[�h��̋�̕ۑ�
void Backup_Board() {
    backup_snow = snow;
    backup_moonlight = moonlight;
    backup_flower = flower;
    backup_source = source;
}

//�v���C���[�莝���̕ۑ�
void Backup_PlayerHand(int player_id) {
    backup_player[player_id] = player[player_id];
}

//UCB�Ŏ��I�э~��Ă���������
int Search_Uct(int player_id, int node_n) {
    NODE *pN = &node[node_n];
    re_try:
    int select = -1;
    double max_ucb = -999;
    int i;
    for (i = 0; i < pN->child_num; i++) {
        CHILD*c = &pN->child[i];
        double ucb = 0;
        if (c->games == 0) {
            ucb = node_max + rand();
        }
        else {
            const double C = 0.31;//�萔�i�����ŕς���j
            ucb = c->rate + C*sqrt(log(pN->game_sum) / c->games);
        }
        if (ucb > max_ucb) {
            max_ucb = ucb;
            select = i;
        }
    }
    if (select == -1) { printf("error!select"); exit(0); }
    CHILD*c = &pN->child[select];
    Call_ChildHand(c);
    if (AI_Move(player_id) == 1) { 
        goto re_try; }
    int win;

    if (c->games == 0) {
        win = -Playout(GetNextTurnPlayer(player_id));
    }
    else {
        if (c->next == -1)c->next = Create_Node(player_id);
        win = -Search_Uct(GetNextTurnPlayer(player_id), c->next);

    }
    c->rate = (c->rate*c->games + win) / (c->games + 1);
    c->games++;
    pN->game_sum++;
    return win;
}

//AI�̒��Ŏ��s����p
int AI_Move(int player_id) {//���ݒu����
    PRIESTESS put_target;
    PRIESTESS put_piece;
    int put_num = 0;
    int flag = 0;
    int random_piece = 0;
    int count;
    int sum = 0;

    for (count = 0; count < 4; count++) {
        put_num = 0;

        put_target = (PRIESTESS)move[count].erea;
        put_piece = (PRIESTESS)move[count].type;

        /*��̐ݒu���鐔*/
        put_num = move[count].number;

        /*����ۂɐݒu�ł��邩�ǂ����̏���*/

        if (AI_Check_Put_Piece(player_id, put_target, put_piece, put_num) == 1) {return 1;}
    }

    for (count = 0; count < 4; count++) {
        put_num = 0;

        put_target = (PRIESTESS)move[count].erea;
        put_piece = (PRIESTESS)move[count].type;
        put_num = move[count].number;

        Move_Num(player_id, put_target, put_piece, put_num);
    }
    flag = Check_BeautiesSeasonMotif_Flag(player_id);
    if (flag == 0) { AI_Make_Motif(player_id); }//���̖�Ȃǂ̌��؂�����Ȃ炱����ς���
    else if (flag == 1) { AI_Make_BeautiesSeasonMotif(player_id); }
    Draw_Board();
    AI_Get_Piece(Enemy(player_id)); printf("player_id=%d\n",player_id);
    return 0;
}

//���u���邩�ǂ������ʂ��܂�
int AI_Check_Put_Piece(int player_id, int put_target, int put_piece, int put_number) {
    //�v���C���[�A�u���ꏊ�A�u���s�[�X�̎�ށA�u����
//�u�����Ƃ��Ă����,�v���C���[�̎�����
 //0�ȉ���u�����Ƃ��Ă��邩�茳�̋�ȏ��u�����Ƃ��Ă���
    int player_piece;
    player_piece = 0;

    player_piece = Check_Player_Piece(player_id, put_piece);

    if (0 > put_number || player_piece < put_number) { printf("%d%d%d�u�����Ƃ��Ă��鐔���K���ł͂���܂���B",put_target,put_piece,put_number); exit(0); return 1; }
    else if (put_target != put_piece && put_number > 1) { printf("��̈قȂ�ꏊ�ɂ�1�����u���܂���"); return 1; }
    else {  return 0; }//����
}


//���؂̃m�[�h�ɔz�u��������Ăяo���܂�
void Call_ChildHand(CHILD *c) {
    int i;
  
    for (i = 0; i < 4; i++) {
        move[i] = c->one_move[i];

/*      move[i].erea = c->one_move[i].erea;
        move[i].type = c->one_move[i].type;
        move[i].number = c->one_move[i].number;*/
    }
    
}
//�v���C�A�E�g
int Playout(int player_id) {
    all_playouts++;
    int color = player_id;
    int loop;
    int loop_max = 100;//�ŏI�ǖʂ܂ŉ���J��Ԃ����A�I���Ȃ��̂�h��
    int i;

    for (loop = 0; loop < loop_max; loop++) {
        int kouho_num = 0;
     
        int r;
        kouho_num = Kouho_List(color);
        for (;;) {//��₪�����邩�ǂ���

            if (kouho_num == 0) {
                for (i = 0; i < 4; i++) { move[i] = { NONE,NONE,0 };}
                printf("��₪������܂���\n");
                break;
            }
            else if (kouho_num > 0) { r = rand() % kouho_num; Kouho_MoveSet(r); }
            
            //printf("�����Ă��܂�\n");

            int err = AI_Move(color);
            if (err == 0) { break; }
            KouhoList_Delete(r,kouho_num);
            kouho_num--;
        }


        if (Judge(color) < 2) {return Count_Score(color);}
        printf("player_id=%d\n",color);
        color = GetNextTurnPlayer(color);
    }
    
    return Count_Score(player_id);
}

//�v���C���[���s�����̑S�񋓂��s��,���肠�������Ԃ��܂�
/*a=�w�n�̑I���@b=��̃^�C�v�̑I���@g=���u���������Ȃ���x=��̋�����u�����@y=���̋�����u�����@z=�Ԃ̋�����u����*/
//���炩�Ɉ�����Ȃǂ��͂����Ƃ��͂�����ҏW����
int Kouho_List(int player_id) {
    int set_type[3] = { SNOW,MOONLIGHT,FLOWER };
    int snow = 0;
    int moonlight = 0;
    int flower = 0;
    int count = 0;
    int a, b, x, y, z;
    printf("player_Id=%d snow=%d flower=%d moonlight=%d\n",player_id,player[player_id].snow_piece, player[player_id].moonlight_piece, player[player_id].flower_piece);
    for (a = 0; a < 3; a++)  for (b = 0; b < 3; b++) {//�^�C�v���R���R�Ŋ|�����킹�Ă��܂�
        if ((set_type[a] == set_type[b]) || (set_type[a] != player[player_id].target_priestess)) { continue; }
        for (int g = 0; g <= 1; g++) {//��ƈقȂ���u���������Ȃ���

            snow = player[player_id].snow_piece;
            moonlight = player[player_id].moonlight_piece;
            flower = player[player_id].flower_piece;
            
            if (g == 1) {
                if ((set_type[b] == SNOW) && (snow > 0)) { snow = snow - 1; }
                else if (snow == 0) { continue; }

                if ((set_type[b] == MOONLIGHT) && (moonlight > 0)) { moonlight = moonlight - 1; }
                else if (moonlight == 0) { continue; }

                if ((set_type[b] == FLOWER) && (flower > 0)) { flower = flower - 1; }
                else if (flower == 0) { continue; }
            }

            for (x = 0; x <= snow; x++) {
                for (y = 0; y <= moonlight; y++) {
                    for (z = 0; z <= flower; z++) {

                        KouhoList_Set(count, set_type[a], set_type[b], g, x, y, z);
                        count++;
                    }
                }
            }
        }
    }
    if (count == 0) { printf("%d\n", all_playouts); exit(0); }
    return count;
}
//�����\���̂ɒl������֐��ł�
void KouhoList_Set(int count, int erea, int type, int other_num, int snow_num, int moonlight_num, int flower_num) {
    for (int times = 0; times < 4; times++) {
        switch (times) {
        case 0:
            kouho[count].forecast_move[times].erea = erea;
            kouho[count].forecast_move[times].type = type;
            kouho[count].forecast_move[times].number = other_num;
            break;
        case 1:
            kouho[count].forecast_move[times].erea = Set_NumberType(times);
            kouho[count].forecast_move[times].type = Set_NumberType(times);
            kouho[count].forecast_move[times].number = snow_num;
            break;
        case 2:
            kouho[count].forecast_move[times].erea = Set_NumberType(times);
            kouho[count].forecast_move[times].type = Set_NumberType(times);
            kouho[count].forecast_move[times].number = moonlight_num;
            break;
        case 3:
            kouho[count].forecast_move[times].erea = Set_NumberType(times);
            kouho[count].forecast_move[times].type = Set_NumberType(times);
            kouho[count].forecast_move[times].number = flower_num;
            break;
        }
        printf("�G���A=%d,��̌`=%d,��=%d", kouho[count].forecast_move[times].erea, kouho[count].forecast_move[times].type, kouho[count].forecast_move[times].number);
    }
    printf("\n");
}
//����move�ɃZ�b�g���܂�
void Kouho_MoveSet(int random) {

    for (int times = 0; times < 4; times++) {
        move[times] = kouho[random].forecast_move[times];
    }
    /*move[times].erea = kouho[random].forecast_move[times].erea;
    move[times].type = kouho[random].forecast_move[times].type;
    move[times].number = kouho[random].forecast_move[times].number;*/
}
//��₩�琔�l�����炵�܂�
void KouhoList_Delete(int random,int list_num) {
   
        for (int times = 0; times < 4; times++) {
            kouho[random].forecast_move[times] = kouho[list_num - 1].forecast_move[times];
        }
    
    /* kouho[list_num].forecast_move[times].erea = kouho[list_num - 1].forecast_move[times].erea;
        kouho[list_num].forecast_move[times].type = kouho[list_num - 1].forecast_move[times].type;
        kouho[list_num].forecast_move[times].number = kouho[list_num - 1].forecast_move[times].number;*/
}
//������
int Count_Score(int player_id) {
    int target = player[player_id].target_priestess;
    int enemy_target = player[player_id].target_priestess;
    int player_num;
    int score = 0;

    switch (target) {
    case SNOW:
        player_num = snow.beauties_season_motif;
        break;
    case MOONLIGHT:
        player_num = moonlight.beauties_season_motif;
        break;
    case FLOWER:
        player_num = flower.beauties_season_motif;
        break;
    }

    int  final_score = player_num;
    int win = 0;
    if (final_score >=3)win = 1;
    if (player_id == 1 && final_score >= 3) win = -win;
    return win;
}

//�ۑ���������ƔՖʂ��ׂĂ̎���Ăяo���܂�
void Call_All(int player_id) {
    Call_PlayerHand(player_id);
    Call_PlayerHand(Enemy(player_id));
    Call_Board();
}
//�ۑ������Ֆʂ̋�̌Ăяo��
void Call_Board() {
    snow = backup_snow;
    moonlight = backup_moonlight;
    flower = backup_flower;
    source = backup_source;
}
//�v���C���[�莝���̌Ăяo��
void Call_PlayerHand(int player_id) {
    player[player_id] = backup_player[player_id];
}

//�ł��ǂ��������move�̍\���̂Ɋi�[���܂�
void Best_Move_Set(NODE *pN, int best_i) {
    int i;
    for (i = 0; i < 4; i++) {

        move[i] = pN->child[best_i].one_move[i];
        /*move[i].erea = pN->child[best_i].one_move[i].erea;
        move[i].type = pN->child[best_i].one_move[i].type;
        move[i].number = pN->child[best_i].one_move[i].number;*/
        /*�\���p*/
        if (move[i].erea == SNOW) { printf("Snow"); }
        else if (move[i].erea == MOONLIGHT) { printf("moonlight"); }
        else if (move[i].erea == FLOWER) { printf("flower"); }
        printf("Erea,");
        if (move[i].type == SNOW) { printf("Snow"); }
        else if (move[i].type == MOONLIGHT) { printf("moonlight"); }
        else if (move[i].type == FLOWER) { printf("flower"); }
        printf("Type,");
        printf("%d\n", move[i].number);

    }
}


//�����e�J�����p(move�̏���������肭�����Ă��Ȃ�)
int Move(int player_id) {//���ݒu����
    PRIESTESS put_target;
    PRIESTESS put_piece;
    int put_num = 0;
    int flag = 0;
    int random_piece = 0;
    int count;


    for (count = 0; count < 4; count++) {
        put_num = 0;

        put_target = (PRIESTESS)move[count].erea;
        put_piece = (PRIESTESS)move[count].type;

        /*��̐ݒu���鐔*/
        put_num = move[count].number;

        /*����ۂɐݒu�ł��邩�ǂ����̏���*/
        if (AI_Check_Put_Piece(player_id, put_target, put_piece, put_num) == 1) {
            put_num = 0;
            return 1;
        }
    }
    for (count = 0; count < 4; count++) {
        put_num = 0;

        put_target = (PRIESTESS)move[count].erea;
        put_piece = (PRIESTESS)move[count].type;
        put_num = move[count].number;

        Move_Num(player_id, put_target, put_piece, put_num);
    }
    flag = Check_BeautiesSeasonMotif_Flag(player_id);
    if (flag == 0) { AI_Make_Motif(player_id); }//���̖�Ȃǂ̌��؂�����Ȃ炱����ς���
    else if (flag == 1) { AI_Make_BeautiesSeasonMotif(player_id); }


    return 0;
}


//���u�����Ƃ��A���ۂɐ��l���ړ�������֐�
void Move_Num(int player_id, int put_target, int put_piece, int put_num) {
    switch (put_target) {
    case SNOW: //��w�n�̋�̐ݒu
        if (put_piece == SNOW) {
            snow.snow_piece += put_num;
            player[player_id].snow_piece -= put_num;
        }
        else if (put_piece == MOONLIGHT) {
            snow.moonlight_piece += put_num;
            player[player_id].moonlight_piece -= put_num;
        }
        else if (put_piece == FLOWER) {
            snow.flower_piece += put_num;
            player[player_id].flower_piece -= put_num;
        }
        else { printf("Error�F�ݒu�����̎w��\n"); }

        break;
    case MOONLIGHT://���w�n�̋�̐ݒu
        if (put_piece == SNOW) {
            moonlight.snow_piece += put_num;
            player[player_id].snow_piece -= put_num;
        }
        else if (put_piece == MOONLIGHT) {
            moonlight.moonlight_piece += put_num;
            player[player_id].moonlight_piece -= put_num;
        }
        else if (put_piece == FLOWER) {
            moonlight.flower_piece += put_num;
            player[player_id].flower_piece -= put_num;
        }
        else { printf("Error�F�ݒu�����̎w��\n"); }
        break;
    case FLOWER://�Ԑw�n�̋�̐ݒu
        if (put_piece == SNOW) {
            flower.snow_piece += put_num;
            player[player_id].snow_piece -= put_num;
        }
        else if (put_piece == MOONLIGHT) {
            flower.moonlight_piece += put_num;
            player[player_id].moonlight_piece -= put_num;
        }
        else if (put_piece == FLOWER) {
            flower.flower_piece += put_num;
            player[player_id].flower_piece -= put_num;
        }
        else { printf("Error�F�ݒu�����̎w��\n"); }
        break;
    case NONE:
        if (put_piece == NONE) {
            break;
        }
    default:
        printf("Error�FMove_Num�s���ȏ����ł�%d\n", __LINE__);
        assert(0);
        break;
    }
    assert(
        player[player_id].snow_piece>=0 ||
        player[player_id].moonlight_piece>=0 ||
        player[player_id].flower_piece>=0);
}
//�ጎ�Ԃ���낤�Ƃ��Ă���G���A�ŏo���邩�ǂ�����I�肵�܂�
int Check_BeautiesSeasonMotif_Flag(int player_id) {
    int target = player[player_id].target_priestess;
    if (snow.snow_motif >= 1 && moonlight.moonlight_motif >= 1 && flower.flower_motif >= 1) {
        if (player[player_id].snow_piece == 0 && player[player_id].moonlight_piece ==0 && player[player_id].flower_piece == 0) {
            switch (target) {
            case SNOW:
                if (snow.moonlight_piece >= 1 && snow.flower_piece >= 1 && snow.snow_piece >= 1) {
                    return 1;
                }
                else { return 0; }

                break;
            case MOONLIGHT:
                if (moonlight.moonlight_piece >= 1 && moonlight.flower_piece >= 1 && moonlight.snow_piece >= 1) {
                    return 1;
                }
                else { return 0; }

                break;
            case FLOWER:
                if (flower.moonlight_piece >= 1 && flower.flower_piece >= 1 && flower.snow_piece >= 1) {
                    return 1;
                }
                else { return 0; }

                break;
            default:
                return 0;
            }
        }
    }

    return 0;
}

void AI_Make_Motif(int player_id) {
    int set_type[3] = { SNOW,MOONLIGHT,FLOWER };
    PRIESTESS put_target;
    PRIESTESS motif_type;
    int piece_num;
    int make_num = 0;
    int x, y;
    for (x = 0; x < 3; x++)for (y = 0; y < 3; y++) {
        put_target = (PRIESTESS)set_type[x];
        motif_type = (PRIESTESS)set_type[y];
        piece_num = Erea_PieceNumber(put_target, motif_type);
        if (piece_num >= 3) {
            make_num = piece_num / 3;
        }
        else if (piece_num < 3) { continue; }
        MoveNum_Motif(player_id, put_target, motif_type, make_num);
    }
}
//������ۂ̐��l�̈ړ��Ȃǂ��܂Ƃ߂��֐�
void MoveNum_Motif(int player_id, int target, int motif, int num) {
    if (target == SNOW) {
        switch (motif) {

        case SNOW:
            snow.snow_piece -= num * 3;
            snow.snow_motif += num;
            AI_Snow_Effect(player_id);
            break;
        case MOONLIGHT:
            snow.moonlight_piece -= num * 3;
            snow.moonlight_motif += num;
            AI_Moonlight_Effect(player_id, target);
            break;
        case FLOWER:
            snow.flower_piece -= num * 3;
            snow.flower_motif += num;
            AI_Flower_Effect(player_id);
            break;
        }
    }
    else if (target == MOONLIGHT) {
        switch (motif) {

        case SNOW:
            moonlight.snow_piece -= num * 3;
            moonlight.snow_motif += num;
            AI_Snow_Effect(player_id);
            break;
        case MOONLIGHT:
            moonlight.moonlight_piece -= num * 3;
            moonlight.moonlight_motif += num;
            AI_Moonlight_Effect(player_id, target);
            break;
        case FLOWER:
            moonlight.flower_piece -= num * 3;
            moonlight.flower_motif += num;
            AI_Flower_Effect(player_id);
            break;
        }
    }
    else if (target == FLOWER) {
        switch (motif) {

        case SNOW:
            flower.snow_piece -= num * 3;
            flower.snow_motif += num;
            AI_Snow_Effect(player_id);
            break;
        case MOONLIGHT:
            flower.moonlight_piece -= num * 3;
            flower.moonlight_motif += num;
            AI_Moonlight_Effect(player_id, target);
            break;
        case FLOWER:
            flower.flower_piece -= num * 3;
            flower.flower_motif += num;
            AI_Flower_Effect(player_id);
            break;
        }
    }
    //if (target != motif) { Get_Card(player_id, target); }����͕ۗ�
}
//��̖�̌��ʁ@
void AI_Snow_Effect(int player_id) {
    int x, y;
    //printf("��̖�̌��ʂ𔭓����܂�\n");
    for (x = 0; x < 3; x++) {

        switch (x) {
        case 0://����
            if (player[Enemy(player_id)].snow_piece > 0) {
                player[Enemy(player_id)].snow_piece--;
                player[player_id].snow_piece++;
                return;
            }
            else { continue; }
            break;

        case 1://�w�n����Ƃ�ꍇ
            if (snow.snow_piece == moonlight.snow_piece == flower.snow_piece == 0) { continue; }
            for (y = 0; y < 3; y++) {
                switch (y) {
                case 0:
                    if (flower.snow_piece > 0) {
                        flower.snow_piece--;
                        player[player_id].snow_piece++;
                        return;
                    }
                    else { continue; }
                    break;
                case 1:
                    if (moonlight.snow_piece > 0) {
                        moonlight.snow_piece--;
                        player[player_id].snow_piece++;
                        return;
                    }
                    else { continue; }
                    break;
                case 2:
                    if (snow.snow_piece > 0) {
                        snow.snow_piece--;
                        player[player_id].snow_piece++;
                        return;
                    }
                    else { continue; }
                    break;
                default:
                    printf("�s���ȓ��͂ł�\n");
                    break;
                }
            }
            break;
        case 2://����
            if (source.snow_piece > 0) {
                source.snow_piece--;
                player[player_id].snow_piece++;
                return;
            }
            else { printf("�����܂���\n"); continue; }
            break;

        default:
            printf("�s���ȓ��͂ł�\n");
            break;
        }
    }
}
//���̖�̌��� 
void AI_Moonlight_Effect(int player_id, int target) {
    switch (target) {
    case SNOW:
        if (player[Enemy(player_id)].snow_piece > 0) {
            player[Enemy(player_id)].snow_piece--;
            player[player_id].snow_piece++;
        }
        break;


    case MOONLIGHT:
        if (player[Enemy(player_id)].moonlight_piece > 0) {
            player[Enemy(player_id)].moonlight_piece--;
            player[player_id].moonlight_piece++;
        }
        break;

    case FLOWER:

        if (player[Enemy(player_id)].flower_piece > 0) {
            player[Enemy(player_id)].flower_piece--;
            player[player_id].flower_piece++;
        }
        break;

    }

}
//�Ԃ̖�̌���
void AI_Flower_Effect(int player_id) {
    int i;
    switch (GetDice()) {
    case SNOW_ONLY:
        if (source.snow_piece == 0 && Motif_SumNum(SNOW)>0) { AI_Destroy_Motif(SNOW); }
        if (source.snow_piece == 0) { return; }
        source.snow_piece--;
        player[player_id].snow_piece++;
        break;
    case MOONLIGHT_ONLY:
        if (source.moonlight_piece == 0 && Motif_SumNum(MOONLIGHT)>0) { AI_Destroy_Motif(MOONLIGHT); }
        if (source.moonlight_piece == 0) { return; }
        source.moonlight_piece--;
        player[player_id].moonlight_piece++;
        break;
    case FLOWER_ONLY:
        if (source.flower_piece == 0 && Motif_SumNum(FLOWER)>0) { AI_Destroy_Motif(FLOWER); }
        if (source.flower_piece == 0) { return; }
        source.flower_piece--;
        player[player_id].flower_piece++;
        break;

    case SNOW_MOONLIGHT:
   
        for (i = 0; i < 2; i++) {
            switch (i) {
            case 0://��̏ꍇ
                if (source.snow_piece == 0 && Motif_SumNum(SNOW)>0) { AI_Destroy_Motif(SNOW); }
                if (source.snow_piece == 0) { continue; }
                source.snow_piece -= 1;
                player[player_id].snow_piece += 1;
            case 1://���̏ꍇ
                if (source.moonlight_piece == 0 && Motif_SumNum(MOONLIGHT)>0) { AI_Destroy_Motif(MOONLIGHT); }
                if (source.moonlight_piece == 0) { return; }
                source.moonlight_piece -= 1;
                player[player_id].moonlight_piece += 1;
            }
        }
        break;
    case SNOW_FLOWER:
        for (i = 0; i < 2; i++) {
            switch (i) {
            case 0://��
                if (source.moonlight_piece == 0 && Motif_SumNum(MOONLIGHT) > 0) { AI_Destroy_Motif(MOONLIGHT); }
                if (source.moonlight_piece == 0) { continue; }
                source.moonlight_piece--;
                player[player_id].moonlight_piece++;

                break;
            case 1://��
                if (source.flower_piece == 0 && Motif_SumNum(FLOWER) > 0) { AI_Destroy_Motif(FLOWER); }
                if (source.flower_piece == 0) { return; }
                source.flower_piece -= 1;
                player[player_id].flower_piece += 1;
                break;
            }
        }
        break;
    case MOONLIGHT_FLOWER:
   
        for (i = 0; i < 2; i++) {
            switch (i) {
            case 0:
                if (source.snow_piece == 0 && Motif_SumNum(SNOW) > 0) { AI_Destroy_Motif(SNOW); }
                if (source.snow_piece == 0) { continue; }
                source.snow_piece -= 1;
                player[player_id].snow_piece += 1;
                break;
            case 1:
                if (source.flower_piece == 0 && Motif_SumNum(FLOWER) > 0) { AI_Destroy_Motif(FLOWER); }
                if (source.flower_piece == 0) { return; }
                source.flower_piece--;
                player[player_id].flower_piece++;
                break;
            }
        }
        break;
    default:
        break;
    }

}

//�ጎ�Ԃ̍쐬
void AI_Make_BeautiesSeasonMotif(int player_id) {
    int target = player[player_id].target_priestess;
    switch (target) {
    case SNOW:
        if (snow.snow_piece > 0 && snow.moonlight_piece > 0 && snow.flower_piece > 0) {
            snow.snow_piece--;
            snow.moonlight_piece--;
            snow.flower_piece--;
            snow.beauties_season_motif++;
            AI_BeautiesSeasonMotif_Effect(player_id);
            if (player[player_id].contract_priestess == NONE) {
                player[player_id].contract_priestess = SNOW;
            }
        }
        return;
    case MOONLIGHT:
        if (moonlight.snow_piece > 0 && moonlight.moonlight_piece > 0 && moonlight.flower_piece > 0) {
            moonlight.snow_piece--;
            moonlight.moonlight_piece--;
            moonlight.flower_piece--;
            moonlight.beauties_season_motif++;
            AI_BeautiesSeasonMotif_Effect(player_id);
            if (player[player_id].contract_priestess == NONE) {
                player[player_id].contract_priestess = MOONLIGHT;
            }
        }
        return;
    case FLOWER:
        if (flower.snow_piece > 0 && flower.moonlight_piece > 0 && flower.flower_piece > 0) {
            flower.snow_piece--;
            flower.moonlight_piece--;
            flower.flower_piece--;
            flower.beauties_season_motif++;
            AI_BeautiesSeasonMotif_Effect(player_id);
            if (player[player_id].contract_priestess == NONE) {
                player[player_id].contract_priestess = FLOWER;
            }
        }
        return;
    }
}

//�ጎ�ԍ쐬�̌���
void AI_BeautiesSeasonMotif_Effect(int player_id) {
    if (player[Enemy(player_id)].contract_priestess == NONE) {

        if (source.snow_piece == 0) { AI_Destroy_Motif(SNOW); }
        if (source.snow_piece > 0) {
            source.snow_piece--;
            player[Enemy(player_id)].snow_piece++;
        }

        if(source.moonlight_piece == 0) { AI_Destroy_Motif(MOONLIGHT); }
        if (source.moonlight_piece > 0) {
            source.moonlight_piece--;
            player[Enemy(player_id)].moonlight_piece++;
        }

        if (source.flower_piece == 0) { AI_Destroy_Motif(FLOWER); }
        if (source.flower_piece > 0) {
            source.flower_piece--;
            player[Enemy(player_id)].flower_piece++;
        }
    }
    else if (player[Enemy(player_id)].contract_priestess == SNOW) {
        //Get_Card(Enemy(player_id), SNOW);
    }
    else if (player[Enemy(player_id)].contract_priestess == MOONLIGHT) {
        //Get_Card(Enemy(player_id), MOONLIGHT);
    }
    else if (player[Enemy(player_id)].contract_priestess == FLOWER) {
        //Get_Card(Enemy(player_id), FLOWER);
    }
}

//�\���̂̏������������s���Ă��邩������
void Set_kifu(int tesuu) {
    int i;
    int erea, type, num;
    for (i = 0; i < 4; i++) {
        kifu[tesuu].forecast_move[i] = move[i];

        erea = kifu[tesuu].forecast_move[i].erea;
        type = kifu[tesuu].forecast_move[i].type;
        num = kifu[tesuu].forecast_move[i].number;
        /*�\���p*/
        if (erea == SNOW) { printf("Snow"); }
        else if (erea == MOONLIGHT) { printf("moonlight"); }
        else if (erea == FLOWER) { printf("flower"); }
        printf("Erea,");
        if (type == SNOW) { printf("Snow"); }
        else if (type == MOONLIGHT) { printf("moonlight"); }
        else if (type == FLOWER) { printf("flower"); }
        printf("Type,");
        printf("%d\n", num);
    }
}


void File_Open() {
    FILE *fp;

    fp = fopen("board.csv", "w");
    fprintf(fp, "��w�n,��,��,��,���,����,�Ԗ�,�ጎ��,");
    fprintf(fp, "���w�n,��,��,��,���,����,�Ԗ�,�ጎ��,");
    fprintf(fp, "�Ԑw�n,��,��,��,���,����,�Ԗ�,�ጎ��,");
    fprintf(fp, "����,��,��,��\n");
    fclose(fp);


    fp = fopen("player.csv", "w");
    fprintf(fp, "�萔,�v���C���[ID,��,��,��,��\n");

    fclose(fp);

}

void File_Input(int player_id, int tesuu) {
    FILE *fp;
    fp = fopen("board.csv", "a");
    //�e�G���A�̋�̐�
    fprintf(fp, ",%d,%d,%d,%d,%d,%d,%d,", snow.snow_piece, snow.moonlight_piece, snow.flower_piece, snow.snow_motif, snow.moonlight_motif, snow.flower_motif, snow.beauties_season_motif);
    fprintf(fp, ",%d,%d,%d,%d,%d,%d,%d,", moonlight.snow_piece, moonlight.moonlight_piece, moonlight.flower_piece, moonlight.snow_motif, moonlight.moonlight_motif, moonlight.flower_motif, moonlight.beauties_season_motif);
    fprintf(fp, ",%d,%d,%d,%d,%d,%d,%d,", flower.snow_piece, flower.moonlight_piece, flower.flower_piece, flower.snow_motif, flower.moonlight_motif, flower.flower_motif, flower.beauties_season_motif);
    fprintf(fp, ",%d,%d,%d\n", source.snow_piece, source.moonlight_piece, source.flower_piece);
    //�e�G���A�̖�̐�

    fclose(fp);


    fp = fopen("player.csv", "a");
    fprintf(fp, "%d,%d,", tesuu, player_id);
    if (player[player_id].contract_priestess == SNOW) { fprintf(fp, "��,"); }
    else if (player[player_id].contract_priestess == MOONLIGHT) { fprintf(fp, "��,"); }
    else if (player[player_id].contract_priestess == FLOWER) { fprintf(fp, "��,"); }
    else { fprintf(fp, "��,"); }
    //�v���C���[�̏�����
    fprintf(fp, "%d,%d,%d\n", player[player_id].snow_piece, player[player_id].moonlight_piece, player[player_id].flower_piece);
    fclose(fp);
}
