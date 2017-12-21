#pragma once
#include<stdio.h>
#include<time.h>
#include<Windows.h>

#include"Game_Flow.h"
#include"Status.h"
#include"Checker.h"
#include"Option.h"

//�^�[���̌����s���܂�
int GetNextTurnPlayer(int player_id) {
    if (player_id == 0) { return 1; }
    else if (player_id == 1) { return 0; }
}
//�_�C�X�ŋ�𓾂܂�
DICE GetDice() {
	DICE dice;
	switch (rand() % 6) {
	case 0:
		dice = (DICE)SNOW_ONLY;
		printf("�΂̖ځFSNOW_ONLY\n");
		break;
	case 1:
		dice = (DICE)MOONLIGHT_ONLY;
		printf("�΂̖ځFMOONLIGHT_ONLY\n");
		break;
	case 2:
		dice = (DICE)FLOWER_ONLY;
		printf("�΂̖ځFFLOWER_ONLY\n");
		break;
	case 3:
		dice = (DICE)SNOW_MOONLIGHT;
		printf("�΂̖ځFSNOW_MOONLIGHT\n");
		break;
	case 4:
		dice = (DICE)SNOW_FLOWER;
		printf("�΂̖ځFSNOW_FLOWER\n");
		break;
	case 5:
		dice = (DICE)MOONLIGHT_FLOWER;
		printf("�΂̖ځFMOONLIGHT_FLOWER\n");
		break;
	default:
		break;
	}
	return dice;
}

//�_�C�X�̖ڂɂ���ē������ł�
void AcquirePiece(int player_id) {
	switch (GetDice()) {
	case SNOW_ONLY:
		if (source.snow_piece == 0) { Destroy_Motif(SNOW); }

		if (source.snow_piece == 0) { break; }
		else if (source.snow_piece == 1) {
			source.snow_piece --;
			player[player_id].snow_piece++;
		}
		else {
			source.snow_piece -= 2;
			player[player_id].snow_piece += 2;
		}
		break;
	case MOONLIGHT_ONLY:
		if (source.moonlight_piece == 0) { Destroy_Motif(MOONLIGHT); }

		if (source.moonlight_piece == 0) { break; }
		else if(source.moonlight_piece == 1){
			source.moonlight_piece --;
			player[player_id].moonlight_piece ++;

		}
		else {
			source.moonlight_piece -= 2;
			player[player_id].moonlight_piece += 2;
		}
		break;
	case FLOWER_ONLY:
		if (source.flower_piece == 0) { Destroy_Motif(FLOWER); }

		if (source.flower_piece == 0) { break; }
		else if(source.flower_piece == 1){
			source.flower_piece --;
			player[player_id].flower_piece ++;
		}
		else {
			source.flower_piece -= 2;
			player[player_id].flower_piece += 2;
		}
		break;
	case SNOW_MOONLIGHT:
		if (source.snow_piece == 0) { Destroy_Motif(SNOW); }
		if (source.moonlight_piece == 0) { Destroy_Motif(MOONLIGHT); }

		if (source.snow_piece == 0 && source.moonlight_piece == 0) { break; }
		else if(source.snow_piece == 0){ 
			source.moonlight_piece --;	
			player[player_id].moonlight_piece ++;
		}
		else if (source.moonlight_piece == 0) {
			source.snow_piece --;
			player[player_id].snow_piece ++;
		}
		else {
			source.snow_piece --;
			source.moonlight_piece --;
			player[player_id].snow_piece ++;
			player[player_id].moonlight_piece ++;
		}
		break;
	case SNOW_FLOWER:
		if (source.snow_piece == 0) { Destroy_Motif(SNOW); }
		if (source.flower_piece == 0) { Destroy_Motif(FLOWER); }

		if (source.snow_piece == 0 && source.flower_piece == 0) { break; }
		else if (source.snow_piece == 0) { 
		source.flower_piece --;
		player[player_id].flower_piece ++;
		}
		else if (source.flower_piece == 0) {
			source.snow_piece --;
			player[player_id].snow_piece ++;
		}
		else {
			source.snow_piece --;
			source.flower_piece --;
			player[player_id].snow_piece ++;
			player[player_id].flower_piece ++;
		}
		break;
	case MOONLIGHT_FLOWER:
		if (source.moonlight_piece == 0) { Destroy_Motif(MOONLIGHT); }
		if (source.flower_piece == 0) { Destroy_Motif(FLOWER); }

		if (source.moonlight_piece == 0 && source.flower_piece == 0) { break; }
		else if (source.flower_piece == 0) {
			source.moonlight_piece --;
			player[player_id].moonlight_piece ++;
		}
		else if (source.moonlight_piece == 0) {
			source.flower_piece --;
			player[player_id].flower_piece ++;
		}
		else {
			source.moonlight_piece --;
			source.flower_piece --;
			player[player_id].moonlight_piece ++;
			player[player_id].flower_piece ++;
		}
		break;
	default:
		break;
	}
}

//�w�肳�ꂽ�^�C�v�̖��j�󂵂܂��B
void Destroy_Motif(int motif) {//��̔j��
	int flag[3] = { 0,0,0 };
	switch (motif)
	{
	case SNOW:
		if (snow.snow_motif != 0) { flag[0] = 1; }
		if (moonlight.snow_motif != 0) { flag[1] = 1; }
		if (flower.snow_motif != 0) { flag[2] = 1; }
	case MOONLIGHT:
		if (snow.moonlight_motif != 0) { flag[0] = 1; }
		if (moonlight.moonlight_motif != 0) { flag[1] = 1; }
		if (flower.moonlight_motif != 0) { flag[2] = 1; }
	case FLOWER:
		if (snow.flower_motif != 0) { flag[0] = 1; }
		if (moonlight.flower_motif != 0) { flag[1] = 1; }
		if (flower.flower_motif != 0) { flag[2] = 1; }
	default:
		break;

	}
	if (flag[0] == flag[1] == flag[2] == 0) { printf("�󂹂�䂪����܂���\n"); Pause(); return; }
	if (flag[0] == 1) { printf("z:��w�n�̖�����"); }
	if (flag[1] == 1) { printf("x:���w�n�̖�����"); }
	if (flag[2] == 1) { printf("c:�Ԑw�n�̖�����\n"); }
	if (motif == SNOW) {//��̖����
		switch ((char)GetKeyInput())
		{
		case 'z':
			if (snow.snow_motif > 0) {
				snow.snow_motif--;
				source.snow_piece += 3;
			}
			else { printf("��̐w�n�ɖ䂪����܂���\n"); }
			break;
		case 'x':
			if (moonlight.snow_motif > 0) {
				moonlight.snow_motif--;
				source.snow_piece += 3;
			}
			else { printf("���̐w�n�ɖ䂪����܂���\n"); }
			break;
		case 'c':
			if (flower.snow_motif > 0) {
				flower.snow_motif--;
				source.snow_piece += 3;
			}
			else { printf("�Ԃ̐w�n�ɖ䂪����܂���\n"); }
			break;
		default:
			printf("�s���ȓ��͂ł�\n");
			break;
		}
	}
	else if (motif == MOONLIGHT) {//���̖����
		switch ((char)GetKeyInput())
		{
		case 'z':
			if (snow.moonlight_motif > 0) {
				snow.moonlight_motif--;
				source.moonlight_piece += 3;
			}
			else { printf("��̐w�n�ɖ䂪����܂���\n"); }
			break;
		case 'x':
			if (moonlight.moonlight_motif > 0) {
				moonlight.moonlight_motif--;
				source.moonlight_piece += 3;
			}
			else { printf("���̐w�n�ɖ䂪����܂���\n"); }
			break;
		case 'c':
			if (flower.moonlight_motif > 0) {
				flower.moonlight_motif--;
				source.moonlight_piece += 3;
			}
			else { printf("�Ԃ̐w�n�ɖ䂪����܂���\n"); }

			break;
		default:
			printf("�s���ȓ��͂ł�\n");
			break;
		}
	}
	else if (motif == FLOWER) {//�Ԃ̖����
		switch ((char)GetKeyInput()) {

		case 'z':
			if (snow.flower_motif > 0) {
				snow.flower_motif--;
				source.flower_piece += 3;
			}
			else { printf("��̐w�n�ɖ䂪����܂���\n"); }
			break;
		case 'x':
			if (moonlight.flower_motif > 0) {
				moonlight.flower_motif--;
				source.flower_piece += 3;
			}
			else { printf("���̐w�n�ɖ䂪����܂���\n"); }
			break;
		case 'c':
			if (flower.flower_motif > 0) {
				flower.flower_motif--;
				source.flower_piece += 3;
			}
			else { printf("�Ԃ̐w�n�ɖ䂪����܂���\n"); }
			break;
		default:
			printf("�s���ȓ��͂ł�\n");
			break;
		}
	}
	return;
}

//�ꏊ�ƃ^�C�v���w�肵�A���j�󂵂܂��B
int Dissase_Motif(int erea, int type) {

    if (erea == SNOW) {//��̖����
        switch (type)
        {
        case SNOW:
            if (snow.snow_motif != 0) {
                snow.snow_motif--;
                source.snow_piece += 3;
                return 1;
            }
            else { printf("��̐w�n�ɖ䂪����܂���\n"); return 0; }
            break;
        case MOONLIGHT:
            if (snow.moonlight_motif != 0) {
                snow.moonlight_motif--;
                source.moonlight_piece += 3;
                return 1;
            }
            else { printf("���̐w�n�ɖ䂪����܂���\n"); return 0; }
            break;
        case FLOWER:
            if (snow.flower_motif != 0) {
                snow.flower_motif--;
                source.flower_piece += 3;
                return 1;
            }
            else { printf("�Ԃ̐w�n�ɖ䂪����܂���\n"); return 0; }
            break;
        default:
            printf("�s���ȓ��͂ł�\n");
            break;
        }
    }
    else if (erea == MOONLIGHT) {//���̖����
        switch (type)
        {
        case SNOW:
            if (moonlight.snow_motif != 0) {
                moonlight.snow_motif--;
                source.snow_piece += 3;
                return 1;
            }
            else { printf("��̐w�n�ɖ䂪����܂���\n"); return 0; }
            break;
        case MOONLIGHT:
            if (moonlight.moonlight_motif != 0) {
                moonlight.moonlight_motif--;
                source.moonlight_piece += 3;
                return 1;
            }
            else { printf("���̐w�n�ɖ䂪����܂���\n"); return 0; }
            break;
        case FLOWER:
            if (moonlight.flower_motif != 0) {
                moonlight.flower_motif--;
                source.flower_piece += 3;
                return 1;
            }
            else { printf("�Ԃ̐w�n�ɖ䂪����܂���\n"); return 0; }

            break;
        default:
            printf("�s���ȓ��͂ł�\n");
            break;
        }
    }
    else if (erea == FLOWER) {//�Ԃ̖����
        switch (type) {

        case SNOW:
            if (flower.snow_motif != 0) {
                flower.snow_motif--;
                source.snow_piece += 3;
                return 1;
            }
            else { printf("��̐w�n�ɖ䂪����܂���\n"); return 0; }
            break;
        case MOONLIGHT:
            if (flower.moonlight_motif != 0) {
                flower.moonlight_motif--;
                source.moonlight_piece += 3;
                return 1;
            }
            else { printf("���̐w�n�ɖ䂪����܂���\n"); return 0; }
            break;
        case FLOWER:
            if (flower.flower_motif != 0) {
                flower.flower_motif--;
                source.flower_piece += 3;
                return 1;
            }
            else { printf("�Ԃ̐w�n�ɖ䂪����܂���\n"); return 0; }
            break;
        default:
            printf("�s���ȓ��͂ł�\n");
            return 0;
            break;
        }
    }
    printf("error\n");
    return 0;
}

//�ጎ�Ԃ�j�󂵂܂�
int Destroy_BeautiesSeasonMotif(int motif) {//�ጎ�Ԃ��󂵂܂�
	switch (motif) {
	case SNOW:
		if (snow.beauties_season_motif > 0) {
			snow.beauties_season_motif--;
			source.snow_piece++;
			source.moonlight_piece++;
			source.flower_piece++;
			return 1;
		}
		else { printf("�󂹂�ጎ�Ԃ�����܂���\n"); return 0; }
		break;
	case MOONLIGHT:
		if (moonlight.beauties_season_motif > 0) {
			moonlight.beauties_season_motif--;
			source.snow_piece++;
			source.moonlight_piece++;
			source.flower_piece++;
			return 1;
		}
		else { printf("�󂹂�ጎ�Ԃ�����܂���\n"); return 0;}
		break;
	case FLOWER:
		if (flower.beauties_season_motif > 0) {
			flower.beauties_season_motif--;
			source.snow_piece++;
			source.moonlight_piece++;
			source.flower_piece++;
			return 1;
		}
		else { printf("�󂹂�ጎ�Ԃ�����܂���\n"); return 0;}
		break;

	}
    printf("error\n");
    return 0;
}

//����茳�ɓ��܂�
int Get_Motif_Piece(int player_id,int erea,int type) {
	switch (erea) {
	case SNOW:
		switch (type) {
		case SNOW:
			if (snow.snow_motif == 0) { return 0; }
			else {
				snow.snow_motif--;
				player[player_id].snow_piece += 3;
				return 1;
			}
			break;

		case MOONLIGHT:
			if (snow.moonlight_motif == 0) { return 0; }
			else {
				snow.moonlight_motif--;
				player[player_id].moonlight_piece += 3;
				return 1;
			}
			break;

		case FLOWER:
			if (snow.flower_motif == 0) { return 0; }
			else {
				snow.flower_motif--;
				player[player_id].flower_piece += 3;
				return 1;
			}
			break;

		default:
			break;
		}
		break;
	case MOONLIGHT:
		switch (erea) {
		case SNOW:
			if (moonlight.snow_motif == 0) { return 0; }
			else {
				moonlight.snow_motif--;
				player[player_id].snow_piece += 3; 
				return 1;
			}
			break;
		case MOONLIGHT:
			if (moonlight.moonlight_motif == 0) { return 0; }
			else {
				moonlight.moonlight_motif--;
				player[player_id].moonlight_piece += 3;
				return 1;
			}
			break;
		case FLOWER:
			if (moonlight.flower_motif == 0) { return 0; }
			else {
				moonlight.flower_motif--;
				player[player_id].flower_piece += 3;
				return 1;
			}
			break;
		default:
			break;
		}
		break;
	case FLOWER:
		switch (erea) {
		case SNOW:
			if (flower.snow_motif == 0) { return 0; }
			else {
				flower.snow_motif--;
				player[player_id].snow_piece += 3;
				return 1;
			}
			break;
		case MOONLIGHT:
			if (flower.moonlight_motif == 0) { return 0; }
			else {
				flower.moonlight_motif--;
				player[player_id].moonlight_piece += 3;
				return 1;
			}
			break;
		case FLOWER:
			if (flower.flower_motif == 0) { return 0; }
			else {
				flower.flower_motif--;
				player[player_id].flower_piece += 3;
				return 1;
			}
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
    printf("error\n");
    return 0;
}

//�^�C�v��I�т܂�
int Set_Crest() {//��A���A�Ԃ̓��ǂꂩ��I�����邱�Ƃ��ł��܂�
	while (1) {
		switch ((char)GetKeyInput())//�w�n�I��
		{
		case 'z':
			return SNOW;
			break;
		case 'x':
			return MOONLIGHT;
			break;
		case 'c':
			return FLOWER;
			break;
		case 'v':
			return NONE;
			break;
		default:
			printf("�s���ȓ��͂ł�\n");
			printf("(��Fz�@���Fx�@�ԁFc)������͂��Ă�������\n");
			continue;
		}
	}
}

//����쐬���܂�
void Make_Motif(int player_id, int target, int motif, int num) {
    if (target == SNOW) {
        switch (motif) {

        case SNOW:
            snow.snow_piece -= num * 3;
            snow.snow_motif += num;
            Motif_Effect(player_id, target, motif);
            break;
        case MOONLIGHT:
            snow.moonlight_piece -= num * 3;
            snow.moonlight_motif += num;
            Motif_Effect(player_id, target, motif);
            break;
        case FLOWER:
            snow.flower_piece -= num * 3;
            snow.flower_motif += num;
            Motif_Effect(player_id, target, motif);
            break;
        }
    }
    else if (target == MOONLIGHT) {
        switch (motif) {

        case SNOW:
            moonlight.snow_piece -= num * 3;
            moonlight.snow_motif += num;
            Motif_Effect(player_id, target, motif);
            break;
        case MOONLIGHT:
            moonlight.moonlight_piece -= num * 3;
            moonlight.moonlight_motif += num;
            Motif_Effect(player_id, target, motif);
            break;
        case FLOWER:
            moonlight.flower_piece -= num * 3;
            moonlight.flower_motif += num;
            Motif_Effect(player_id, target, motif);
            break;
        }
    }
    else if (target == FLOWER) {
        switch (motif) {

        case SNOW:
            flower.snow_piece -= num * 3;
            flower.snow_motif += num;
            Motif_Effect(player_id, target, motif);
            break;
        case MOONLIGHT:
            flower.moonlight_piece -= num * 3;
            flower.moonlight_motif += num;
            Motif_Effect(player_id, target, motif);
            break;
        case FLOWER:
            flower.flower_piece -= num * 3;
            flower.flower_motif += num;
            Motif_Effect(player_id, target, motif);
            break;
        }
    }
    if (target != motif) {Get_Card(player_id,target);}
}

//��̌��ʂ�I�����܂�
void Motif_Effect(int player_id,int target,int motif) {
	switch (motif) {
	case SNOW:
		Snow_Effect(player_id);
		break;
	case MOONLIGHT:
		Moonlight_Effect(player_id, target);
		break;
	case FLOWER:
		Flower_Effect(player_id);
		break;
	}

}

//��̖�̌���
void Snow_Effect(int player_id) {
    printf("��̖�̌��ʂ𔭓����܂�\n");
	while (1) {
		printf("�ǂ��̏ꏊ�����̋�����܂����H\n");
		printf("z:�w�n x:���� c:����\n");
		switch (GetKeyInput())
		{
		case 'z'://�w�n����Ƃ�ꍇ
			if (snow.snow_piece == moonlight.snow_piece == flower.snow_piece == 0) { printf("��������܂���\n"); continue; }
			printf("�ǂ̐w�n�����𓾂܂����H\n");
			printf("z:��w�n�@x:���w�n�@c:�Ԑw�n");
			switch ((char)GetKeyInput())
			{
			case 'z':
				if (snow.snow_piece > 0) {
					snow.snow_piece--;
					player[player_id].snow_piece++;
				}
				else { printf("�����܂���\n"); continue; }
				break;
			case 'x':
				if (moonlight.snow_piece > 0) {
					moonlight.snow_piece--;
					player[player_id].snow_piece++;
				}
				else { printf("�����܂���\n"); continue;}
				break;
			case 'c':
				if (flower.snow_piece > 0) {
					flower.snow_piece--;
					player[player_id].snow_piece++;
				}
				else { printf("�����܂���\n"); continue;}
				break;
			default:
				printf("�s���ȓ��͂ł�\n");
				break;
			}
			break;
		case 'x'://����	
				if (player[Enemy(player_id)].snow_piece > 0) {
					player[Enemy(player_id)].snow_piece--;
					player[player_id].snow_piece++;
				}
                else { printf("�����܂���\n"); continue; }
                break;
			break;
		case 'c'://����
			if (source.snow_piece > 0) {
				source.snow_piece--;
				player[player_id].snow_piece++;
			}
            else { printf("�����܂���\n"); continue; }
			break;

		default:
			printf("�s���ȓ��͂ł�\n");
			break;
		}
		break;
	}
}

//���̖�̌���
void Moonlight_Effect(int player_id, int target) {
    printf("���̖�̌��ʂ𔭓����܂�\n");
    switch (target) {
    case SNOW:
        if (player[Enemy(player_id)].snow_piece > 0) {
            player[Enemy(player_id)].snow_piece--;
            player[player_id].snow_piece++;
        }
        else { printf("�����܂���\n"); }
        break;


    case MOONLIGHT:
        if (player[Enemy(player_id)].moonlight_piece > 0) {
            player[Enemy(player_id)].moonlight_piece--;
            player[player_id].moonlight_piece++;
        }
        else { printf("�����܂���\n"); }
        break;

    case FLOWER:

        if (player[Enemy(player_id)].flower_piece > 0) {
            player[Enemy(player_id)].flower_piece--;
            player[player_id].flower_piece++;
        }
        else { printf("�����܂���\n"); }
        break;

    }

}

//�Ԃ̖�̌���
void Flower_Effect(int player_id) {
    printf("�Ԃ̖�̌��ʂ𔭓����܂�\n");
	switch (GetDice()) {
	case SNOW_ONLY:
		if (source.snow_piece == 0) { Destroy_Motif(SNOW); }
		source.snow_piece --;
		player[player_id].snow_piece ++;
		break;
	case MOONLIGHT_ONLY:
		if (source.moonlight_piece == 0) { Destroy_Motif(MOONLIGHT); }
		source.moonlight_piece -- ;
		player[player_id].moonlight_piece ++;
		break;
	case FLOWER_ONLY:
		if (source.flower_piece == 0) { Destroy_Motif(FLOWER); }
		source.flower_piece --;
		player[player_id].flower_piece ++;
		break;

	case SNOW_MOONLIGHT:
		printf("��ƌ��ǂ���̋�����܂���?");
		printf("z:��̋�@x:���̋�");
		switch (GetKeyInput()) {
		case 'z'://��̏ꍇ
			if (source.snow_piece == 0) { Destroy_Motif(SNOW); }
			source.snow_piece -= 1;
			player[player_id].snow_piece += 1;
		case 'x'://���̏ꍇ
			if (source.moonlight_piece == 0) { Destroy_Motif(MOONLIGHT); }
			source.moonlight_piece -= 1;
			player[player_id].moonlight_piece += 1;
		}
		break;
	case SNOW_FLOWER:
		printf("��ƉԂǂ���̋�����܂���?");
		printf("z:��̋�@x:�Ԃ̋�");
		switch (GetKeyInput()) {
		case 'z':
			if (source.snow_piece == 0) { Destroy_Motif(SNOW); }
			source.snow_piece -= 1;
			player[player_id].snow_piece += 1;
			break;
		case 'x':
			if (source.flower_piece == 0) { Destroy_Motif(FLOWER); }
			source.flower_piece -= 1;
			player[player_id].flower_piece += 1;
			break;
		}
		break;
	case MOONLIGHT_FLOWER:
		printf("���ƉԂǂ���̋�����܂���?");
		printf("z:���̋�@x:�Ԃ̋�");
		switch (GetKeyInput()) {
		case'z':
			if (source.moonlight_piece == 0) { Destroy_Motif(MOONLIGHT); }
			source.moonlight_piece --;
			player[player_id].moonlight_piece ++;
			break;
		case'x':
			if (source.flower_piece == 0) { Destroy_Motif(FLOWER); }
			source.flower_piece --;
			player[player_id].flower_piece ++;
			break;
		}
	default:
		break;
	}

}

//�ጎ�ԍ쐬
void Make_BeautiesSeasonMotif(int player_id,int target){
	switch (target) {
	case SNOW:
		if (snow.snow_piece > 0 && snow.moonlight_piece > 0 && snow.flower_piece > 0) {
			snow.snow_piece--;
			snow.moonlight_piece--;
			snow.flower_piece--;
			snow.beauties_season_motif++;
            BeautiesSeasonMotif_Effect(player_id);
			if (player[player_id].contract_priestess == NONE) {
				player[player_id].contract_priestess = SNOW;
			}
		}
		return;
		break;
	case MOONLIGHT:
		if (moonlight.snow_piece > 0 && moonlight.moonlight_piece > 0 && moonlight.flower_piece > 0) {
			moonlight.snow_piece--;
			moonlight.moonlight_piece--;
			moonlight.flower_piece--;
			moonlight.beauties_season_motif++;
            BeautiesSeasonMotif_Effect(player_id);
			if (player[player_id].contract_priestess == NONE) {
				player[player_id].contract_priestess = MOONLIGHT;
			}
		}
		return;
		break;
	case FLOWER:
		if (flower.snow_piece > 0 && flower.moonlight_piece > 0 && flower.flower_piece > 0) {
			flower.snow_piece--;
			flower.moonlight_piece--;
			flower.flower_piece--;
			flower.beauties_season_motif++;
            BeautiesSeasonMotif_Effect(player_id);
			if (player[player_id].contract_priestess == NONE) {
				player[player_id].contract_priestess = FLOWER;
			}
		}
		return;
		break;
	}
}

//�ጎ�ԍ쐬�̌���
void BeautiesSeasonMotif_Effect(int player_id) {
	if (player[Enemy(player_id)].contract_priestess == NONE) {
		player[Enemy(player_id)].snow_piece++;
		player[Enemy(player_id)].moonlight_piece++;
		player[Enemy(player_id)].flower_piece++;
	}
	else if (player[Enemy(player_id)].contract_priestess == SNOW) {
        Get_Card(Enemy(player_id), SNOW);
	}
    else if (player[Enemy(player_id)].contract_priestess == MOONLIGHT) {
        Get_Card(Enemy(player_id), MOONLIGHT);
    }
    else if (player[Enemy(player_id)].contract_priestess == FLOWER) {
        
        (Enemy(player_id), FLOWER);
    }
}

//�J�[�h�̐�����\�L���܂�
int Explain_CardEffect(int type) {
	switch (type)
	{
	case SNOW:
		if (snow.card[0] == 1) { printf("1[���]:�C�ӂ̖��3����ɕԂ�\n"); }
		if (snow.card[1] == 2) { printf("2[�����]:�茳�ŔC�ӂ̖��2����ɕԂ��A�Ֆʂ̐ጎ�Ԃ����̂���\n"); }
		if (snow.card[2] == 3) { printf("3[�ᕗ]:�C�ӂ̖����̂��茳�ɓ���\n"); }
		if ((snow.card[0] + snow.card[1] + snow.card[2]) == 0) { printf("����J�[�h������܂���\n"); return 0; }
        else {
            printf("1:����@2:����� 3:�ᕗ\n");
            printf("����>>"); 
            return 1; }
        break;
	case MOONLIGHT:
		if (moonlight.card[0] == 1) { printf("1[���e]:�茳���灡�����̋������ɕԂ��B�ΐ푊��͎��̃^�[���A��Ɛጎ�Ԃ��쐬�s��\n"); }
		if (moonlight.card[1] == 2) { printf("2[���I]:�S�Ă̑ΐ푊��͎��̃^�[���茳�ɐV���ȕЂ𓾂��Ȃ�\n"); }
		if (moonlight.card[2] == 3) { printf("3[�O��]:�e�̈�A�ΐ푊��̎茳����C�ӂ̋��3����\n"); }

		if ((moonlight.card[0] + moonlight.card[1] + moonlight.card[2]) == 0) { printf("����J�[�h������܂���\n"); return 0; }
        else {
            printf("1:���e�@2:���I 3:�O��\n");
            printf("����>>"); 
            return 1; }
        break;
	case FLOWER:
		if (flower.card[0] == 1) { printf("1[�k��]:�ԎD�̈�̖�2������ɕԂ��B�J�[�h�̌��ʂ�ł�����\n"); }
		if (flower.card[1] == 2) { printf("2[�J��]:������C�ӂ̋��2�Ԃ̐w�n�ɐݒu����\n"); }
		if (flower.card[2] == 3) { printf("3[����]:������Ԃ̋��5�Ԃ̐w�n�ɐݒu����\n"); }

		if ((flower.card[0] + flower.card[1] + flower.card[2]) == 0) { printf("����J�[�h������܂���\n"); return 0; }
        else {
            printf("1:�k�ԁ@2:�J�� 3:����\n");
            printf("����>>"); 
            return 1; }
        break;
	default:
		break;
	}
    printf("error\n");
    return 0;
}

//�v���C���[�̏�������J�[�h�̐��������܂�
int Explain_PlayerCardEffect(int player_id,int type) {
    switch (type)
    {
    case SNOW:
        if (player[player_id].snow_card[0] == 1) { printf("1[���]:�C�ӂ̖��3����ɕԂ�\n"); }
        if (player[player_id].snow_card[1] == 2) { printf("2[�����]:�茳�ŔC�ӂ̖��2����ɕԂ��A�Ֆʂ̐ጎ�Ԃ����̂���\n"); }
        if (player[player_id].snow_card[2] == 3) { printf("3[�ᕗ]:�C�ӂ̖����̂��茳�ɓ���\n"); }
        if ((player[player_id].snow_card[0] + player[player_id].snow_card[1] + player[player_id].snow_card[2]) == 0) { printf("����J�[�h������܂���\n"); return 0; }
        else { return 1; }
        break;
    case MOONLIGHT:
        if (player[player_id].moonlight_card[0] == 1) { printf("1[���e]:�茳���灡�����̋������ɕԂ��B�ΐ푊��͎��̃^�[���A��Ɛጎ�Ԃ��쐬�s��\n"); }
        if (player[player_id].moonlight_card[1] == 2) { printf("2[���I]:�S�Ă̑ΐ푊��͎��̃^�[���茳�ɐV���ȕЂ𓾂��Ȃ�\n"); }
        if (player[player_id].moonlight_card[2] == 3) { printf("3[�O��]:�e�̈�A�ΐ푊��̎茳����C�ӂ̋��3����\n"); }

        if ((player[player_id].moonlight_card[0] + player[player_id].moonlight_card[1] + player[player_id].moonlight_card[2]) == 0) { printf("����J�[�h������܂���\n"); return 0; }
        else {return 1;}
        break;
    case FLOWER:
        if (player[player_id].flower_card[0] == 1) { printf("1[�k��]:�Ԃ̗̈�̖�2������ɕԂ��B�J�[�h�̌��ʂ�ł�����\n"); }
        if (player[player_id].flower_card[1] == 2) { printf("2[�J��]:������C�ӂ̋��2�Ԃ̐w�n�ɐݒu����\n"); }
        if (player[player_id].flower_card[2] == 3) { printf("3[����]:������Ԃ̋��5�Ԃ̐w�n�ɐݒu����\n"); }

        if ((player[player_id].flower_card[0] + player[player_id].flower_card[1] + player[player_id].flower_card[2]) == 0) { printf("����J�[�h������܂���\n"); return 0; }
        else {  return 1; }
        break;
    default:
        break;
    }
    printf("error\n");
    return 0;
}

//�e�G���A����茳�ɋ�𓾂邱�Ƃ��ł��܂�
int Get_Erea_Piece(int player_id,int erea, int type) {
    switch (erea) {

    case SNOW:
        switch (type) {

        case SNOW:
            if (snow.snow_piece == 0) { printf("�������܂���\n"); return 0; }
            else {
                snow.snow_piece--;
                player[player_id].snow_piece++;
                return 1;
            }
            break;
        case MOONLIGHT:
            if (snow.moonlight_piece == 0) { printf("�������܂���\n"); return 0; }
            else {
                snow.moonlight_piece--;
                player[player_id].moonlight_piece++;
                return 1;
            }
            break;
        case FLOWER:
            if (snow.flower_piece == 0) { printf("�������܂���\n"); return 0; }
            else {
                snow.flower_piece--;
                player[player_id].flower_piece++;
                return 1;
            }
            break;
        }
        break;
    case MOONLIGHT:
        switch (type) {

        case SNOW:
            if (moonlight.snow_piece == 0) { printf("�������܂���\n"); return 0; }
            else {
                moonlight.snow_piece--;
                player[player_id].snow_piece++;
                return 1;
            }
            break;
        case MOONLIGHT:
            if (moonlight.moonlight_piece == 0) { printf("�������܂���\n"); return 0; }
            else {
                moonlight.moonlight_piece--;
                player[player_id].moonlight_piece++;
                return 1;
            }
            break;
        case FLOWER:
            if (moonlight.flower_piece == 0) { printf("�������܂���\n"); return 0; }
            else {
                moonlight.flower_piece--;
                player[player_id].flower_piece++;
                return 1;
            }
            break;
        }
        break;
    case FLOWER:
        switch (type) {

        case SNOW:
            if (flower.snow_piece == 0) { printf("�������܂���\n"); return 0; }
            else {
                flower.snow_piece--;
                player[player_id].snow_piece++;
                return 1;
            }
            break;
        case MOONLIGHT:
            if (flower.moonlight_piece == 0) { printf("�������܂���\n"); return 0; }
            else {
                flower.moonlight_piece--;
                player[player_id].moonlight_piece++;
                return 1;
            }
            break;
        case FLOWER:
            if (flower.flower_piece == 0) { printf("�������܂���\n"); return 0; }
            else {
                flower.flower_piece--;
                player[player_id].flower_piece++;
                return 1;
            }
            break;
        }
        break;
    default:
        printf("error\n");
        return 0;
        break;
    }
    printf("error\n");
    return 0;
}

//����̎茳�����𓾂�܂�
int Deprive_Piece(int player_id,int type){
	switch (type) {
	case SNOW:
        if (player[Enemy(player_id)].snow_piece == 0) { printf("��������Ă��܂���\n"); return 0; }
        else {
            player[player_id].snow_piece++;
            player[Enemy(player_id)].snow_piece--;
            return 1;
        }
		break;
	case MOONLIGHT:
        if (player[Enemy(player_id)].moonlight_piece == 0) { printf("��������Ă��܂���\n"); return 0; }
        else {
            player[player_id].moonlight_piece++;
            player[Enemy(player_id)].moonlight_piece--;
            return 1;
        }
		break;
	case FLOWER:
        if (player[Enemy(player_id)].flower_piece == 0) { printf("��������Ă��܂���\n"); return 0; }
        else {
            player[player_id].flower_piece++;
            player[Enemy(player_id)].flower_piece--;
            return 1;
        }
		break;

    default:
        printf("���s\n");
        return 0;
        break;
	}
}

//������򂩂�ړ������܂�
int Source_Move_Erea(int erea, int type) {
    if (erea == FLOWER) {
        switch (type) {
        case SNOW:
            if (source.snow_piece == 0) { printf("�����܂���\n"); return 0; }
            else {
                source.snow_piece--;
                flower.snow_piece++;
                return 1;
            }
            break;
        case MOONLIGHT:
            if (source.moonlight_piece == 0) { printf("�����܂���\n"); return 0; }
            else {
                source.moonlight_piece--;
                flower.moonlight_piece++;
                return 1;
            }
            break;
        case FLOWER:
            if (source.snow_piece == 0) { printf("�����܂���\n"); return 0; }
            else {
                source.flower_piece--;
                flower.flower_piece++;
                return 1;
            }
            break;

        }
    }
    printf("error\n");
    return 0;
}

//�J�[�h�𓾂邱�Ƃ��ł��܂�
void Get_Card(int player_id,int motif) {
	int select_number = 0;
	
	while (1) {
		switch (motif) {
		case SNOW:
            if (Explain_CardEffect(motif) == 1) {
                select_number = Check_Nunber(1, 3);
                if (0 >= select_number) { select_number = 0; continue; }
                Select_Card(player_id, motif, select_number);
                return;
            }
            else { Pause(); return; }
			break;
		case MOONLIGHT:
            if (Explain_CardEffect(motif) == 1) {
                select_number = Check_Nunber(1, 3);
                if (0 >= select_number) { select_number = 0; continue; }
                Select_Card(player_id, motif, select_number);
                return;
            }
            else { Pause(); return;}
			break;
		case FLOWER:
            if (Explain_CardEffect(motif) == 1) {
                select_number = Check_Nunber(1, 3);
                if (0 >= select_number) { select_number = 0; continue; }
                Select_Card(player_id, motif, select_number);
                return;
            }
            else { Pause(); return;}
            break;
		default:
			break;
		}
	}
}

//�w�n����J�[�h�𓾂鏈�����s���Ă��܂�
void Select_Card(int player_id, int motif, int number) {



	switch (motif)
	{
	case SNOW:
		if (snow.card[0] == 1 && number == 1) {
			player[player_id].snow_card[0] = 1;
			snow.card[0] = 0;
		}
		else if (snow.card[1] == 2 && number == 2) {
			player[player_id].snow_card[1] = 2;
			snow.card[1] = 0;
		}
		else if (snow.card[2] == 3 && number == 3) {
			player[player_id].snow_card[2] = 3;
			snow.card[2] = 0;
		}
		else { printf("�J�[�h�����݂��܂���\n"); }
		break;
	case MOONLIGHT:
		if (moonlight.card[0] == 1 && number == 1) {
			player[player_id].moonlight_card[0] = 1;
			moonlight.card[0] = 0;
		}
		else if (moonlight.card[1] == 2 && number == 2) {
			player[player_id].moonlight_card[1] = 2;
			moonlight.card[1] = 0;
		}
		else if (moonlight.card[2] == 3 && number == 3) {
			player[player_id].moonlight_card[2] = 3;
			moonlight.card[2] = 0;
		}
		else { printf("�J�[�h�����݂��܂���\n"); }
		break;
	case FLOWER:
		if (flower.card[0] == 1 && number == 1) {
			player[player_id].flower_card[0] = 1;
			flower.card[0] = 0;
		}
		else if (flower.card[1] == 2 && number == 2) {
			player[player_id].flower_card[1] = 2;
			flower.card[1] = 0;
		}
		else if (flower.card[2] == 3 && number == 3) {
			player[player_id].flower_card[2] = 3;
			flower.card[2] = 0;
		}
		else { printf("�J�[�h�����݂��܂���\n"); }
		break;
	default:
		break;
	}
}

//��̃J�[�h�̌���
int Snow_CardEffect(int player_id, int number) {
	int select_erea = 0;
	int select_type = 0;
	int destroy_motif = 0;
	int piece_type = 0;
	int sum_piece = 0; //���ʂ𖞂������߂̒~�ϒl�ł�

	switch (number) {
	case 1:
		if (Check_Motif_Number() <= 3) { printf("��̐�������܂���"); return 0; }
		else {
			printf("�C�ӂ̖��3����ɕԂ��܂�\n");
			for (int i = 0; i < 3; i++) {
				printf("�ǂ̐w�n�̖��j�󂵂܂����H\n");
                printf("z:��@x:���@c:��\n");
				select_erea = Set_Crest();
				printf("�ǂ̖��j�󂵂܂����H\n");
				Destroy_Motif(select_erea);
				system("cls");
				Draw_Board();
			}
			return 1;
		}
		break;


	case 2:
		printf("�茳�ŔC�ӂ̖��2����ɕԂ��A�Ֆʂ̐ጎ�Ԃ����̂���\n");
		if (Check_Player_Motif(player_id, 1) == 0) { printf("�����𖞂������J�[�h�̎g�p���ł��܂���\n"); return 0; }
		while (1) {

			printf("�ǂ̋������܂����H\n");
			printf("z:��@x:���@c:��\n");
			printf(">>");
			piece_type = Set_Crest();
			switch (piece_type) {
			case SNOW:
				if (player[player_id].snow_piece >= 3) {
					player[player_id].snow_piece -= 3;
					source.snow_piece += 3;
					sum_piece += 3;
				}
				else { printf("�����܂���\n"); continue; }
				break;
			case MOONLIGHT:
				if (player[player_id].moonlight_piece >= 3) {
					player[player_id].moonlight_piece -= 3;
					source.moonlight_piece += 3;
					sum_piece += 3;
				}
				else { printf("�����܂���\n"); continue; }
				break;
			case FLOWER:
				if (player[player_id].flower_piece >= 3) {
					player[player_id].flower_piece -= 3;
					source.flower_piece += 3;
					sum_piece += 3;
				}
				else { printf("�����܂���\n"); continue; }
				break;

			}

			if (sum_piece == 6) {
				while (1) {
					printf("�ǂ��̐w�n���󂵂܂���");
					select_erea = Set_Crest();
					if (Destroy_BeautiesSeasonMotif(select_erea) == 1) { return 1;  break; }
					else { continue; }
				}

			}
		}
		printf("���s\n");
		return 0;
		break;
	case 3:
		while (1) {
			if (Check_Motif_Number() < 0) { printf("��̂ł���䂪����܂���\n"); return 0; break; }
			printf("�C�ӂ̖����̂��茳�ɓ��鎖���ł��܂�\n");
			select_erea = Set_Crest();
			select_type = Set_Crest();
			if (Get_Motif_Piece(player_id, select_erea, select_type) == 0) { printf("�䂪��̂ł��܂���ł���\n"); continue; }
			else { return 1; break; }

		}
	default:
		break;
		
	}
    printf("error\n");
    return 0;
}

//���̃J�[�h�̌���
int Moonlight_CardEffect(int player_id, int number) {
	int get_piece = 0;
    int get_type = 0;
	int get_erea = 0;

	switch (number) {
	case 1:
		if (Check_Player_Motif(player_id,2) == 1) {
			player[player_id].snow_piece--;
			player[player_id].moonlight_piece--;
			player[player_id].flower_piece--;
			card_flag.moon_card_flag_1 = 1;
			return 1;
		}
		else { printf("�����܂���\n"); return 0; }

		break;

	case 2:
		card_flag.moon_card_flag_2 = 1;
        return 1;
		break;

    case 3:

        if (Sum_Player_Piece(Enemy(player_id)) + Sum_Board_Piece() < 3)
		{printf("��������܂���\n");  return 0;}

		while (get_piece < 3) {
            system("cls");
            Draw_Board();
			printf("�e�̈�Ƒ���̎茳����v�O��𓾂邱�Ƃ��ł��܂�\n");
			printf("z:�e�̈�@x:����̎茳\n");
			printf("����>>");
			switch (GetKeyInput())
			{
			case 'z':
                printf("���w�n��I��ł�������\n");
                printf("z:��@x:���@y:��\n");
                printf("����>>");
                get_type = Set_Crest();
                if (Deprive_Piece(player_id, get_type) == 1) {
                    get_piece++;
                    break;
                }
                else{break;}
				break;
			case 'x':
                get_erea = Set_Crest();
                get_type = Set_Crest();
                if(Get_Erea_Piece(player_id, get_erea, get_type)==1){
                    get_piece++;
                    break;
                }
                else { break; }
				break;
			default:
				break;
			}
		}
		break;
	default:
		break;

	}
    printf("error\n");
    return 0;
}

//�Ԃ̃J�[�h�̌���
int  Flower_CardEffect(int player_id, int number) {
    int type = 0;
    int disasse_motif = 0;
    int piece_number = 0;
    switch (number) {
    case 1: //�J��
        if ((FlowerErea_Motif_Numbers(SNOW) + FlowerErea_Motif_Numbers(MOONLIGHT) + FlowerErea_Motif_Numbers(FLOWER)) > 2) {
            while (disasse_motif < 2) {
                printf("�ԎD�̈�̖������ɕԂ�\n");
                type = Set_Crest();
                if (Dissase_Motif(FLOWER, type) == 1) {
                    disasse_motif++;
                }
            }
            return 1;
        }
        else { return 0; }
        break;
    case 2: //����
        if ((source.snow_piece + source.moonlight_piece + source.flower_piece) < 2) { printf("���ʂ𖞂��������̋����܂���\n"); return 0; }
        printf("������A�C�ӂ̕Ђ�2�A�ԕP�̈�ɐݒu���܂�.");
        while (piece_number < 2) {
            printf("�ݒu����������w�肵�Ă�������\n");
            printf("z:��@x:���@c:�ԁ@\n");
            printf("����>>");
            type = Set_Crest();
            if (Source_Move_Erea(FLOWER, type) == 1) {
                piece_number++;
            }
            else { printf("���s\n"); continue; }
        }

        if (piece_number == 2) { return 1; }
        else { printf("error\n"); return 0; }

        break;

    case 3: //�k��
        printf("������A�ԕЂ�5�ԕP�̈�ɐݒu����\n");
        if (source.flower_piece > 5) {
            source.flower_piece -= 5;
            flower.flower_piece += 5;
            return 1;
        }
        else { return 0; }

        break;
    default: //�G���[����
        printf("Error:Flower?CardEffect");
        break;
    }
    printf("error\n");
    return 0;
}

//�g�p�����J�[�h���s���ɏI������ꍇ�g�p���J�[�h�̐������ɖ߂��܂�
void Reset_Card(int player_id, int type, int number) {
    switch (type) {
    case SNOW:
        if (number == 1) {
            snow.card[0] = 0;
            player[player_id].snow_card[0] = 1;
        }
        else if (number == 2) {
            snow.card[1] = 0;
            player[player_id].snow_card[1] = 2;
        }
        else if (number == 3) {
            snow.card[2] = 0;
            player[player_id].snow_card[2] = 3;
        }

        break;

    case MOONLIGHT:
        if (number == 1) {
            moonlight.card[0] = 0;
            player[player_id].moonlight_card[0] = 1;
        }
        else if (number == 2) {
            moonlight.card[1] = 0;
            player[player_id].moonlight_card[1] = 2;
        }
        else if (number == 3) {
            moonlight.card[2] = 0;
            player[player_id].moonlight_card[2] = 3;
        }

        break;

    case FLOWER:
        if (number == 1) {
            flower.card[0] = 0;
            player[player_id].flower_card[0] = 1;
        }
        else if (number == 2) {
            flower.card[1] = 0;
            player[player_id].flower_card[1] = 2;
        }
        else if (number == 3) {
            flower.card[2] = 0;
            player[player_id].flower_card[2] = 3;
        }

        break;

    default:
        break;
    }
}

//�J�[�h���g�������̏������s���܂�.�J�[�h���g�p������Ֆʂɖ߂��������s���Ă��܂��B
void Card_Effect(int player_id, int type, int number) {

    switch (type) {
    case SNOW:
        if (number == 1) {
            snow.card[0] = 1;
            player[player_id].snow_card[0] = 0;
        }
        else if (number == 2) {
            snow.card[1] = 2;
            player[player_id].snow_card[1] = 0;
        }
        else if (number == 3) {
            snow.card[2] = 3;
            player[player_id].snow_card[2] = 0;
        }

        break;

    case MOONLIGHT:
        if (number == 1) {
            moonlight.card[0] = 1;
            player[player_id].moonlight_card[0] = 0;
        }
        else if (number == 2) {
            moonlight.card[1] = 2;
            player[player_id].moonlight_card[1] = 0;
        }
        else if (number == 3) {
            moonlight.card[2] = 3;
            player[player_id].moonlight_card[2] = 0;
        }

        break;

    case FLOWER:
        if (number == 1) {
            flower.card[0] = 1;
            player[player_id].flower_card[0] = 0;
        }
        else if (number == 2) {
            flower.card[1] = 2;
            player[player_id].flower_card[1] = 0;
        }
        else if (number == 3) {
            flower.card[2] = 3;
            player[player_id].flower_card[2] = 0;
        }

        break;

    default:
        break;
    }
}

//�J�[�h���g�����̏������܂Ƃ߂��֐��ł�
void Use_Card(int player_id) {
    int type = 0;
    int number = 0;
    int sum = 0;
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            sum += Check_Card(player_id, i, j);
        }
    }
    if (sum == 0) { printf("�g����J�[�h������܂���\n"); return; }
    while (1) {
        Draw_Board();
        printf("�ǂ��̐w�n�̃J�[�h���g�����I��ł�������\n");
        printf("z:��@x:���@c:�ԁ@v:�I���@\n");
        printf(">>");
        type = Set_Crest();
        if (type == NONE) { return; }
        if (Explain_PlayerCardEffect(player_id,type) == 0) { system("cls"); continue; }
        printf("�ǂ̃J�[�h���g���܂����H\n");
        if (type == SNOW) {printf("1:����@2:����� 3:�ᕗ\n");}
        else if(type == MOONLIGHT) {printf("1:���e�@2:���I 3:�O��\n");}
        else if (type == FLOWER) {printf("1:�k�ԁ@2:�J�� 3:����\n");}
        printf("����>>");
        number = Check_Nunber(1, 3);
        if (Check_Card(player_id, type, number) == 0) { system("cls"); continue; }

        Card_Effect( player_id, type, number);

        /*�k�ԃJ�[�h����*/
        if(player[Enemy(player_id)].flower_card[0] == 1){
            printf("����Ɍ�サ�Ă�������\n");
            if (Flower_CardEffect(Enemy(player_id), 1) == 1) {
                printf("����̃J�[�h�̌��ʂ�ł������܂��B");
                continue;
            }
            else { printf("����������܂���ł����A����J�[�h�̎g�p�𑱍s���܂��B"); }
        }
        /*���荞�ݏI��*/
        switch (type)
        {
        case SNOW:
            if (Snow_CardEffect(player_id, number) == 0) {Reset_Card( player_id, type, number);} 
            else{ return; }
            break;
        case MOONLIGHT:
            if(Moonlight_CardEffect(player_id, number) == 0 ){Reset_Card(player_id, type, number);}
            else { return; }
            break;
        case FLOWER:
            if (Flower_CardEffect(player_id, number) == 0) {Reset_Card(player_id, type, number);}
            else { return; }
            break;
        default:
            break;
        }
        system("cls");
    }
}

