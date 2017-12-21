// CapplitioMoiif.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include"stdio.h"
#include<time.h>
#include"Game_Flow.h"
#include"Status.h"
#include"Option.h"
#include"Checker.h"
#include"System.h"
#include"AI.h"
#define STR(var) #var //�����ɂ����ϐ���ϐ��������������񃊃e�����Ƃ��ĕԂ��}�N���֐�

//TODO
int Select_Player() {
    printf("1:PVP 2:AIvsAI\n");
    while (1) {
        switch (GetNumberInput()) {
        case 1:
            return 1;
        case 2:
            return 2;
        default:
            break;
        }
    }
    return 0;
}
void StartPlayer_Piece() {
    player[0].snow_piece = 1;
    player[0].moonlight_piece = 1;
    player[0].flower_piece = 1;
    player[1].snow_piece = 1;
    player[1].moonlight_piece = 1;
    player[1].flower_piece = 1;
}
//�Ֆʕ\��
void Draw_Board() {
    printf("�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|\n");
    printf("|\t�@�@�@��̐w�n\t\t|\t�@�@�@���̐w�n\t\t|\t�@�@�@�Ԃ̐w�n\t\t|\n");
    //�e�G���A�̋�̐�
    printf("|��F ���~%d\t���~%d\t���~%d\t|", snow.snow_piece, snow.moonlight_piece, snow.flower_piece);
    printf("��F ���~%d\t���~%d\t���~%d\t|", moonlight.snow_piece, moonlight.moonlight_piece, moonlight.flower_piece);
    printf("��F ���~%d\t���~%d\t���~%d\t|", flower.snow_piece, flower.moonlight_piece, flower.flower_piece);
    printf("\n");
    //�e�G���A�̖�̐�
    printf("|��F ���~%d\t���~%d\t���~%d\t|", snow.snow_motif, snow.moonlight_motif, snow.flower_motif);
    printf("��F ���~%d\t���~%d\t���~%d\t|", moonlight.snow_motif, moonlight.moonlight_motif, moonlight.flower_motif);
    printf("��F ���~%d\t���~%d\t���~%d\t|", flower.snow_motif, flower.moonlight_motif, flower.flower_motif);
    printf("\n");
    //�e�G���A�̐ጎ�Ԃ̐�
    printf("|\t�ጎ��:\t�~%d\t\t|", snow.beauties_season_motif);
    printf("\t�ጎ��:\t�~%d\t\t|", moonlight.beauties_season_motif);
    printf("\t�ጎ��:\t�~%d\t\t|", flower.beauties_season_motif);
    printf("\n");
    //�e�G���A�̃J�[�h�̐�
    printf("|\t�@�D�@:\t%d %d %d\t\t|", snow.card[0], snow.card[1], snow.card[2]);
    printf("\t�@�D�@:\t%d %d %d\t\t|", moonlight.card[0], moonlight.card[1], moonlight.card[2]);
    printf("\t�@�D�@:\t%d %d %d\t\t|", flower.card[0], flower.card[1], flower.card[2]);
    printf("\n");

    printf("�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|\n");
    //�v���C���[�̏����؂̕\��
    printf("|\t�@�@�@PL1\t\t|\t�@�@�@����\t\t|\t�@�@�@PL2\t\t|\n");
    printf("|\t    �؁F");
    if (player[0].contract_priestess == SNOW) { printf("��"); }
    else if (player[0].contract_priestess == MOONLIGHT) { printf("��"); }
    else if (player[0].contract_priestess == FLOWER) { printf("��"); }
    else { printf("��"); }
    printf("           \t|");

    printf("\t                 \t|");

    printf("\t    �؁F");
    if (player[1].contract_priestess == SNOW) { printf("��"); }
    else if (player[1].contract_priestess == MOONLIGHT) { printf("��"); }
    else if (player[1].contract_priestess == FLOWER) { printf("��"); }
    else { printf("��"); }
    printf("           \t|");
    printf("\n");
    //�v���C���[�̏�����
    printf("|��F ���~%d\t���~%d\t���~%d\t", player[0].snow_piece, player[0].moonlight_piece, player[0].flower_piece);
    printf("|\t                 \t");
    printf("|��F ���~%d\t���~%d\t���~%d\t|", player[1].snow_piece, player[1].moonlight_piece, player[1].flower_piece);
    printf("\n");
    //�v���C���[�̎D�̐�
    printf("|\t������D:%d ,%d ,%d\t", player[0].snow_card[0], player[0].snow_card[1], player[0].snow_card[2]);
    printf("|��F ���~%d\t���~%d\t���~%d\t", source.snow_piece, source.moonlight_piece, source.flower_piece);
    printf("|\t������D:%d ,%d ,%d\t|", player[1].snow_card[0], player[1].snow_card[1], player[1].snow_card[2]);
    printf("\n");

    printf("|\t�������D:%d ,%d ,%d\t", player[0].moonlight_card[0], player[0].moonlight_card[1], player[0].moonlight_card[2]);
    printf("|\t                 \t");
    printf("|\t�������D:%d ,%d ,%d\t|", player[1].moonlight_card[0], player[1].moonlight_card[1], player[1].moonlight_card[2]);
    printf("\n");

    printf("|\t�����ԎD:%d ,%d ,%d\t", player[0].flower_card[0], player[0].flower_card[1], player[0].flower_card[2]);
    printf("|\t                 \t");
    printf("|\t�����ԎD:%d ,%d ,%d\t|", player[1].flower_card[0], player[1].flower_card[1], player[1].flower_card[2]);
    printf("\n");

    printf("�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|\n");
}
//��̐ݒu
void Put_Piece(int player_id)
{//���ݒu����
    PRIESTESS put_target;
    PRIESTESS put_piece;
    int put_num = 0;
    int flag = 0;


    while (1) {
        system("cls");
        Draw_Board();
        put_num = 0;
        Player(player_id);

        printf("���ݒu����w�n����͂��Ă�������(��Fz�@���Fx�@�ԁFc�@�ݒu�I���Fv)\n");
        if (flag == 0) { printf("��ƈقȂ�������1��u���܂�\n"); }
        else if (flag == 1) { printf("��ƈقȂ��͂��������܂���\n"); }
        printf("����>>");
        put_target = (PRIESTESS)Set_Crest();
        if (put_target == NONE) { printf("���̃X�e�b�v�ɍs���܂��B"); Pause(); return; }
        else if (3 < put_target || put_target < 0) { printf("���͂��s���ł�\n"); Pause(); continue; }

        printf("�ݒu�����̎�ނ���͂��Ă�������(��Fz�@���Fx�@�ԁFc)\n");
        printf("����>>");
        put_piece = (PRIESTESS)Set_Crest();
        if (3 < put_target || put_target <= 0) { printf("�ŏ��ɖ߂�܂�\n"); Pause(); continue; }


        printf("�u����̌�����͂��Ă�������:");
        printf("����>>");
        put_num = GetNumberInput();
        if (Check_Put_Piece(player_id, put_target, put_piece, put_num) == 1) {
            ("�l���s���ł�\n");
            put_num = 0;
            Pause();
            continue;
        }
        else if (Check_Put_Piece(player_id, put_target, put_piece, put_num) == 2) {
            if (flag == 1) {
                printf("�����قȂ�w�n�ɋ��u�����Ƃ͂ł��܂���\n");
                Pause();
            }
            else {
                flag = 1;

            }
        }

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
        default:
            printf("Error�FPut_Piece�s���ȏ����ł�%d\n",__LINE__);
            break;
        }
    }
}

//��̍쐬
void Create_Motif(int player_id) {//��̍쐬
    PRIESTESS put_target;
    PRIESTESS motif_type;
    int make_num;
    while (1) {
        system("cls");
        Draw_Board();
        printf("�w�n�ɂ����3��1�̖�ɂ��邱�Ƃ��ł��܂��B\n");
        printf("����쐬����w�n����͂��Ă�������(��Fz�@���Fx�@�ԁFc�@�ݒu�I���Fv)\n");
        printf("����>>");
        put_target = (PRIESTESS)Set_Crest();
        if (put_target == NONE) { printf("���̃X�e�b�v�ɍs���܂��B"); Pause(); return; }
        else if (3 < put_target || put_target < 0) { continue; }

        printf("�쐬�����̎�ނ���͂��Ă�������(��Fz�@���Fx�@�ԁFc)\n");
        printf("����>>");
        motif_type = (PRIESTESS)Set_Crest();
        if (3 < put_target || put_target <= 0) { printf("�ŏ��ɖ߂�܂�\n"); Pause(); continue; }

        printf("�쐬�����̌�����͂��Ă�������\n");
        printf("����>>");
        make_num = GetNumberInput();

        if (Check_Motif(put_target, motif_type, make_num) == 0) { make_num = 0; Pause(); continue; }
        else { Make_Motif(player_id, put_target, motif_type, make_num); Pause(); }
    }

}
//�ጎ�Ԃ̍쐬
void Create_BeautiesSeasonMotif(int player_id) {//�ጎ�Ԃ̍쐬
    int put_target;
    while (1) {
        system("cls");
        Draw_Board();
        printf("�ǂ��ɐጎ�Ԃ�ݒu���܂����H\n");
        printf("�쐬����w�n����͂��Ă�������(��Fz�@���Fx�@�ԁFc�@�ݒu�I���Fv)\n");
        printf("����>>");
        put_target = Set_Crest();
        if (put_target == NONE) { printf("���̃X�e�b�v�ɍs���܂��B"); Pause(); return; }
        else if (3 < put_target || put_target < 0) { continue; }

        if (Check_BeautiesSeasonMotif(player_id, put_target) == 1) {//�ጎ�Ԃ���ꂽ�ꍇ
            Make_BeautiesSeasonMotif(player_id, put_target);		//�ጎ�Ԃ̍쐬
            Renew();
            Draw_Board();
        }
        else if (Check_BeautiesSeasonMotif(player_id, put_target) == 0) {
            printf("�ጎ�Ԃ̍쐬��������������Ă��܂���\n");
            continue;
        }
        else { continue; }
    }
}



void Player_Game(int player_id) {
    int winner = 0;
    int mooncard1_effect_flag = 0;
    int mooncard2_effect_flag = 0;
    while (1) {

        Draw_Board();
        //��̊l��
        AcquirePiece(player_id);

        Renew();


        //�J�[�h�̎g�p
        Use_Card(player_id);

        /*��̐ݒu*/
        if (mooncard2_effect_flag == 0) { Put_Piece(player_id); }
        //�J�[�h�Q�̌���
        else if (mooncard2_effect_flag == 1) {
            printf("�J�[�h�̌��ʂŃX�L�b�v���܂�\n");
            mooncard2_effect_flag = 0;
            card_flag.moon_card_flag_2 = 0;
        }
        /*��̐ݒu�I��*/

        /*��̍쐬*/
        if (mooncard1_effect_flag == 0) { Create_Motif(player_id); }
        //�J�[�h�P�̌���
        else if (mooncard1_effect_flag == 1) { printf("�J�[�h�̌��ʂŃX�L�b�v���܂�\n"); }
        /*��̍쐬�I��*/

        /*�ጎ�Ԃ̍쐬*/
        if (mooncard1_effect_flag == 0) { Create_BeautiesSeasonMotif(player_id); }
        //�J�[�h�P�̌���
        else if (mooncard1_effect_flag == 1) {
            mooncard1_effect_flag = 0;
            card_flag.moon_card_flag_1 = 0;
            printf("�J�[�h�̌��ʂŃX�L�b�v���܂�\n");
        }
        /*�ጎ�Ԃ̍쐬�I��*/


        /*���������̔���*/
        system("cls");
        Draw_Board();
        winner = Judge(player_id);
        if (winner == 0) { printf("player1�̏����I"); break; }
        else if (winner == 1) { printf("player2�̏����I"); break; }
        else { printf("�^�[������サ�܂��B"); }
        /*��������I��*/

        //�^�[���̌��
        player_id = GetNextTurnPlayer(player_id);

        Renew();
        //�J�[�h�̌���
        if (card_flag.moon_card_flag_1 == 1) {//���̃J�[�h�P�̌��ʁ@��Ɛጎ�ԍ쐬�s��
            mooncard1_effect_flag = 1;
        }
        if (card_flag.moon_card_flag_2 == 1) {//���̃J�[�h�Q�̌��ʁ@�_�C�X�ŋ�𓾂�Ȃ�
            mooncard2_effect_flag = 1;
        }
    }
}

int AI_Game(int player_id) {
    int tesuu = 0;
    int winner = 0;
    File_Open();
    Ramdom_Set_Target(player_id);
    Ramdom_Set_Target(Enemy(player_id));
    while (1) {
        all_playouts = 0;
        AI_Get_Piece(player_id);
        Select_Best_Uct(player_id);
        Move(player_id);
        Set_kifu(tesuu);
        tesuu++;
        Draw_Board();
       // Pause();
        File_Input(player_id, tesuu);
        printf("�萔=%d,�v���C���[=%d,all_playouts=%d\n", tesuu, player_id, all_playouts);
        winner = Judge(player_id);
        if (winner == 0) { printf("player1�̏����I"); break; }
        else if (winner == 1) { printf("player2�̏����I"); break; }
        player_id = GetNextTurnPlayer(player_id);
      

    }
    return 0;
}

int main() {
    //SetConsoleScreenBufferSize(100,100);
    //SetConsoleWindowInfo();
   // srand((unsigned)time(NULL));
    srand(1);
    StartPlayer_Piece();
    int mode = 0;
    int turn_player = 0;

    mode = Select_Player();
    switch (mode) {
    case 1:   
        Player_Game(turn_player);
        break;
    case 2:
        AI_Game(turn_player);
    }
    return 0;
}

