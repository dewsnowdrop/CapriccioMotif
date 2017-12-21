#pragma once
#include<stdio.h>
#include"Status.h"
#include"System_Flow.h"

//�v���C���[�̎������Ԃ��܂�
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
		printf("Error�FCheck_Player_Piece�s���ȏ����ł�%d\n",__LINE__);
        printf("Check_Player_Piece put_piece=%d\n",put_piece);
        return 0;
        break;

	}

}

//���u���邩�ǂ������ʂ��܂�
int Check_Put_Piece(int player_id,int put_target,int put_piece,int put_number){//�v���C���[�A�u���ꏊ�A�u���s�[�X�̎�ށA�u����
	//�u�����Ƃ��Ă����,�v���C���[�̎�����
	//0�ȉ���u�����Ƃ��Ă��邩�茳�̋�ȏ��u�����Ƃ��Ă���
	int player_piece;
	player_piece = 0;
   
	player_piece = Check_Player_Piece(player_id, put_piece);

    if (player_piece == 0) {printf ("�����u���܂���ł���"); return 0; }
	else if (0 > put_number || player_piece < put_number) { printf("�u�����Ƃ��Ă��鐔���K���ł͂���܂���B"); return 1; }
	else if (put_target != put_piece && put_number > 1) { printf("��̈قȂ�ꏊ�ɂ�1�����u���܂���"); return 1; }
    else if (put_target != put_piece && put_number == 1) {  return 2; }
    else {  return 0; }//����
}

//������邩�ǂ������f���܂�
int Check_Motif(int target , int type ,int num) {

	switch (target) {

	case SNOW:
		switch (type) {

		case SNOW:
			if (snow.snow_piece >= num * 3) { return 1; }
			else { printf("�쐬���邽�߂̋����܂���\n"); return 0; }
		case MOONLIGHT:
			if (snow.moonlight_piece >= num * 3) {  return 1; }
			else { printf("�쐬���邽�߂̋����܂���\n"); return 0; }
		case FLOWER:
			if (snow.flower_piece >= num * 3) { return 1; }
			else { printf("�쐬���邽�߂̋����܂���\n"); return 0; }

		}
	case MOONLIGHT:
		switch (type) {

		case SNOW:
			if (moonlight.snow_piece >= num * 3) { return 1; }
			else { printf("�쐬���邽�߂̋����܂���\n"); return 0; }
		case MOONLIGHT:
			if (moonlight.moonlight_piece >= num * 3) { return 1; }
			else { printf("�쐬���邽�߂̋����܂���\n"); return 0; }
		case FLOWER:
			if (moonlight.flower_piece >= num * 3) {  return 1; }
			else { printf("�쐬���邽�߂̋����܂���\n"); return 0; }

		}
	case FLOWER:
		switch (type) {

		case SNOW:
			if (flower.snow_piece >= num * 3) { return 1; }
			else { printf("�쐬���邽�߂̋����܂���\n"); return 0; }
		case MOONLIGHT:
			if (flower.moonlight_piece >= num * 3) { return 1; }
			else { printf("�쐬���邽�߂̋����܂���\n"); return 0; }

		case FLOWER:
			if (flower.flower_piece >= num * 3) { return 1; }
			else { printf("�쐬���邽�߂̋����܂���\n"); return 0; }


		}
	default:
		return 0;
		break;
	}

}

//�ጎ�Ԃ��쐬�\���ǂ������f���܂�
int Check_BeautiesSeasonMotif(int player_id,int target) {
	if (snow.snow_motif > 0 && moonlight.moonlight_motif > 0 && flower.flower_motif > 0) {//�Ή������䂪��ȏ゠��

		if (player[player_id].snow_piece == player[player_id].moonlight_piece == player[player_id].flower_piece == 0) {//�育�܂�0�ł���

			switch (target)
			{
			case SNOW:
				if (player[player_id].contract_priestess == NONE && snow.beauties_season_motif == 0) { return 1; }//�܂��N�ɂ��Ƃ��Ă��Ȃ�
				else if(player[player_id].contract_priestess == SNOW){ return 1; }//��ȏ゠�邪�����̐w�n�ł���
				else if (player[player_id].contract_priestess > NONE && player[(player_id + 1) % 2].contract_priestess != SNOW) { return 1; }//�w�n�͂��邪�܂��Ƃ��Ă��Ȃ�
				else { return 0; }
				break;

			case MOONLIGHT:
				if (player[player_id].contract_priestess == NONE && moonlight.beauties_season_motif == 0) { return 1; }
				else if (player[player_id].contract_priestess == MOONLIGHT) { return 1; }//��ȏ゠�邪�����̐w�n�ł���
				else if (player[player_id].contract_priestess > NONE && player[(player_id + 1) % 2].contract_priestess != MOONLIGHT) {return 1; }//�w�n�͂��邪�܂��Ƃ��Ă��Ȃ�
				else { return 0; }
				break;

			case FLOWER:
				if (player[player_id].contract_priestess == NONE && flower.beauties_season_motif == 0) { return 1; }
				else if (player[player_id].contract_priestess == FLOWER) { return 1; }//��ȏ゠�邪�����̐w�n�ł���
				else if (player[player_id].contract_priestess > NONE && player[(player_id + 1) % 2].contract_priestess != FLOWER) { return 1; }//�w�n�͂��邪�܂��Ƃ��Ă��Ȃ�
				else { return 0; }
				break;

			default:
				break;
			}
		}
	}
	return 0;
}

//�w�n�ɂ���ጎ�Ԃ̐���Ԃ��܂�
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

//���������𔻕ʂ��܂�
int Check_Winner(int player_id) {//TODO
	int player1;
	int player2;
	player1 = BeautiesSeasonMotif_Numbers(player_id);
	player2 = BeautiesSeasonMotif_Numbers((player_id + 1) % 2);
	//�ጎ�Ԃ̍쐬�����R
	if (player1 == 3) { return 1; }
	//�����̐ጎ�Ԃ̍쐬�����R�i�ύt��ԁj
	else if (player1 == 3 && player2 == 3) { return 2; }
	//����̂ݏ��������𖞂����Ă���
	else if (player1 <= 3 && player2 == 3) { return 3; }
	//�ጎ�Ԃ̍쐬�����S
	else if (player1 == 4) { return 4; }
	else { return 5; }//���s
}

//�w�肵�����l�ȊO���͂����܂�
int Check_Nunber(int min, int max) {
	int number = 0;
	number = GetNumberInput();
	if (min <= number && number <= max) { return number; }
	else if (number < min) {
		printf("%d�ȉ��̐��l����͂��Ă��܂�\n",min);
		return 0;
	}
	else if (number > max) {
		printf("%d�ȏ�̐��l����͂��Ă��܂�\n",max);
		return 0;
	}
	else {
		printf("�s���Ȑ��l�ł�\n");
        return 0;
	}

}

//�Ֆʂɂ����̍��v����Ԃ��܂�
int Check_Motif_Number() {
	int motif_number = 0;
	for (int i = 1; i <= 3;i++) {
		motif_number = +SnowErea_Motif_Numbers(i) + MoonlightErea_Motif_Numbers(i) + FlowerErea_Motif_Numbers(i);
	}
	return motif_number;
}

//��̐w�n�̖�̐���Ԃ��܂�
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

//���̐w�n�̖�̐���Ԃ��܂�
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

//�Ԃ̐w�n�̖�̐���Ԃ��܂�
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

//�w�肵���^�C�v�̖䂪�����邩��Ԃ��܂�
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

//�茳�Ŗ��ጎ�Ԃ����邩�ǂ���
int Check_Player_Motif(int player_id,int type) {
	//�K��l�ɒB����̂��ǂ������ׂ�B�ϐ��P�F�N�́@�ϐ��Q�Fcase�ʁ@
	//�ϐ��Q�ɂ��āF�P�@�K�v���̖�̐��𒲂ׂ�@�Q�A�茳�Őጎ�Ԃ����邩���ׂ�
	//can �䂪���邩�ǂ����̈ꎞ�I�ȕϐ��ł��J�[�h�̌��ʂŎg�p����גǉ����܂����B
	//�P�ő��s�O�Ŏ��s�ł�
	int can_snow=0;
	int can_moonlight = 0;
	int can_flower = 0;
	int sum = 0;
	switch (type) {
	case 1://snow�J�[�h�Q�̌��ʂɕK�v
		
		can_snow = player[player_id].snow_piece / 3;
		can_moonlight = player[player_id].moonlight_piece / 3;
		can_flower = player[player_id].flower_piece / 3;
		sum = can_snow + can_moonlight + can_flower;
		if (sum >= 2) { return 1; }
		 return 0;
		break;
	case 2://���̃J�[�h�P�̌��ʂɕK�v�@�ጎ�Ԃ��茳�ō��邩�ǂ���
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

//�v���C���[�̋�̍��v�l���`�F�b�N���܂�
int Sum_Player_Piece(int player_id) {
	return Check_Player_Piece(player_id, SNOW) + Check_Player_Piece(player_id, MOONLIGHT) + Check_Player_Piece(player_id, FLOWER);
}

//�Ֆʂ̋�̍��v�l��Ԃ��܂�
int Sum_Board_Piece() {
	int sum = 0;
	sum += snow.snow_piece + snow.moonlight_piece + snow.flower_piece;
	sum += moonlight.snow_piece + moonlight.moonlight_piece + moonlight.flower_piece;
	sum += flower.snow_piece + flower.moonlight_piece + flower.flower_piece;
	return sum;
}

//�J�[�h���g�p�ł��邩�`�F�b�N���܂�
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
            if (player[player_id].flower_card[0] == 1) { printf("���̃J�[�h�͑���̃J�[�h�g�p���Ɋ��荞��Ŏg�����̂ł�"); return 0; }
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
//�Ֆʂ̐w�n�̋�̒l��Ԃ��܂�
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

//���s����𔻒f���܂�
int Judge(int player_id) {//�������� 0or1�ŏI���A�Q�ő��s

    if (Check_Winner(player_id) == 1) { return 2; }//�Е������������𖞂���
    else if (Check_Winner(player_id) == 2) { return 2; } //�ύt���
    else if (Check_Winner(player_id) == 3) { return (player_id + 1) % 2; } //�ύt��ԂɂȂ疳�������ꍇ
    else if (Check_Winner(player_id) == 4) { return (player_id); }//��ɂS�ጎ�Ԃ�������ꍇ
    else { return 2; }
}