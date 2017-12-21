#pragma once
#include<stdio.h>
#include<time.h>
#include<Windows.h>

#include"Game_Flow.h"
#include"Status.h"
#include"Checker.h"
#include"Option.h"

//ターンの交代を行います
int GetNextTurnPlayer(int player_id) {
    if (player_id == 0) { return 1; }
    else if (player_id == 1) { return 0; }
}
//ダイスで駒を得ます
DICE GetDice() {
	DICE dice;
	switch (rand() % 6) {
	case 0:
		dice = (DICE)SNOW_ONLY;
		printf("賽の目：SNOW_ONLY\n");
		break;
	case 1:
		dice = (DICE)MOONLIGHT_ONLY;
		printf("賽の目：MOONLIGHT_ONLY\n");
		break;
	case 2:
		dice = (DICE)FLOWER_ONLY;
		printf("賽の目：FLOWER_ONLY\n");
		break;
	case 3:
		dice = (DICE)SNOW_MOONLIGHT;
		printf("賽の目：SNOW_MOONLIGHT\n");
		break;
	case 4:
		dice = (DICE)SNOW_FLOWER;
		printf("賽の目：SNOW_FLOWER\n");
		break;
	case 5:
		dice = (DICE)MOONLIGHT_FLOWER;
		printf("賽の目：MOONLIGHT_FLOWER\n");
		break;
	default:
		break;
	}
	return dice;
}

//ダイスの目によって得られる駒です
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

//指定されたタイプの紋を破壊します。
void Destroy_Motif(int motif) {//紋の破壊
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
	if (flag[0] == flag[1] == flag[2] == 0) { printf("壊せる紋がありません\n"); Pause(); return; }
	if (flag[0] == 1) { printf("z:雪陣地の紋を崩す"); }
	if (flag[1] == 1) { printf("x:月陣地の紋を崩す"); }
	if (flag[2] == 1) { printf("c:花陣地の紋を崩す\n"); }
	if (motif == SNOW) {//雪の紋を壊す
		switch ((char)GetKeyInput())
		{
		case 'z':
			if (snow.snow_motif > 0) {
				snow.snow_motif--;
				source.snow_piece += 3;
			}
			else { printf("雪の陣地に紋がありません\n"); }
			break;
		case 'x':
			if (moonlight.snow_motif > 0) {
				moonlight.snow_motif--;
				source.snow_piece += 3;
			}
			else { printf("月の陣地に紋がありません\n"); }
			break;
		case 'c':
			if (flower.snow_motif > 0) {
				flower.snow_motif--;
				source.snow_piece += 3;
			}
			else { printf("花の陣地に紋がありません\n"); }
			break;
		default:
			printf("不正な入力です\n");
			break;
		}
	}
	else if (motif == MOONLIGHT) {//月の紋を壊す
		switch ((char)GetKeyInput())
		{
		case 'z':
			if (snow.moonlight_motif > 0) {
				snow.moonlight_motif--;
				source.moonlight_piece += 3;
			}
			else { printf("雪の陣地に紋がありません\n"); }
			break;
		case 'x':
			if (moonlight.moonlight_motif > 0) {
				moonlight.moonlight_motif--;
				source.moonlight_piece += 3;
			}
			else { printf("月の陣地に紋がありません\n"); }
			break;
		case 'c':
			if (flower.moonlight_motif > 0) {
				flower.moonlight_motif--;
				source.moonlight_piece += 3;
			}
			else { printf("花の陣地に紋がありません\n"); }

			break;
		default:
			printf("不正な入力です\n");
			break;
		}
	}
	else if (motif == FLOWER) {//花の紋を壊す
		switch ((char)GetKeyInput()) {

		case 'z':
			if (snow.flower_motif > 0) {
				snow.flower_motif--;
				source.flower_piece += 3;
			}
			else { printf("雪の陣地に紋がありません\n"); }
			break;
		case 'x':
			if (moonlight.flower_motif > 0) {
				moonlight.flower_motif--;
				source.flower_piece += 3;
			}
			else { printf("月の陣地に紋がありません\n"); }
			break;
		case 'c':
			if (flower.flower_motif > 0) {
				flower.flower_motif--;
				source.flower_piece += 3;
			}
			else { printf("花の陣地に紋がありません\n"); }
			break;
		default:
			printf("不正な入力です\n");
			break;
		}
	}
	return;
}

//場所とタイプを指定し、紋を破壊します。
int Dissase_Motif(int erea, int type) {

    if (erea == SNOW) {//雪の紋を壊す
        switch (type)
        {
        case SNOW:
            if (snow.snow_motif != 0) {
                snow.snow_motif--;
                source.snow_piece += 3;
                return 1;
            }
            else { printf("雪の陣地に紋がありません\n"); return 0; }
            break;
        case MOONLIGHT:
            if (snow.moonlight_motif != 0) {
                snow.moonlight_motif--;
                source.moonlight_piece += 3;
                return 1;
            }
            else { printf("月の陣地に紋がありません\n"); return 0; }
            break;
        case FLOWER:
            if (snow.flower_motif != 0) {
                snow.flower_motif--;
                source.flower_piece += 3;
                return 1;
            }
            else { printf("花の陣地に紋がありません\n"); return 0; }
            break;
        default:
            printf("不正な入力です\n");
            break;
        }
    }
    else if (erea == MOONLIGHT) {//月の紋を壊す
        switch (type)
        {
        case SNOW:
            if (moonlight.snow_motif != 0) {
                moonlight.snow_motif--;
                source.snow_piece += 3;
                return 1;
            }
            else { printf("雪の陣地に紋がありません\n"); return 0; }
            break;
        case MOONLIGHT:
            if (moonlight.moonlight_motif != 0) {
                moonlight.moonlight_motif--;
                source.moonlight_piece += 3;
                return 1;
            }
            else { printf("月の陣地に紋がありません\n"); return 0; }
            break;
        case FLOWER:
            if (moonlight.flower_motif != 0) {
                moonlight.flower_motif--;
                source.flower_piece += 3;
                return 1;
            }
            else { printf("花の陣地に紋がありません\n"); return 0; }

            break;
        default:
            printf("不正な入力です\n");
            break;
        }
    }
    else if (erea == FLOWER) {//花の紋を壊す
        switch (type) {

        case SNOW:
            if (flower.snow_motif != 0) {
                flower.snow_motif--;
                source.snow_piece += 3;
                return 1;
            }
            else { printf("雪の陣地に紋がありません\n"); return 0; }
            break;
        case MOONLIGHT:
            if (flower.moonlight_motif != 0) {
                flower.moonlight_motif--;
                source.moonlight_piece += 3;
                return 1;
            }
            else { printf("月の陣地に紋がありません\n"); return 0; }
            break;
        case FLOWER:
            if (flower.flower_motif != 0) {
                flower.flower_motif--;
                source.flower_piece += 3;
                return 1;
            }
            else { printf("花の陣地に紋がありません\n"); return 0; }
            break;
        default:
            printf("不正な入力です\n");
            return 0;
            break;
        }
    }
    printf("error\n");
    return 0;
}

//雪月花を破壊します
int Destroy_BeautiesSeasonMotif(int motif) {//雪月花を壊します
	switch (motif) {
	case SNOW:
		if (snow.beauties_season_motif > 0) {
			snow.beauties_season_motif--;
			source.snow_piece++;
			source.moonlight_piece++;
			source.flower_piece++;
			return 1;
		}
		else { printf("壊せる雪月花がありません\n"); return 0; }
		break;
	case MOONLIGHT:
		if (moonlight.beauties_season_motif > 0) {
			moonlight.beauties_season_motif--;
			source.snow_piece++;
			source.moonlight_piece++;
			source.flower_piece++;
			return 1;
		}
		else { printf("壊せる雪月花がありません\n"); return 0;}
		break;
	case FLOWER:
		if (flower.beauties_season_motif > 0) {
			flower.beauties_season_motif--;
			source.snow_piece++;
			source.moonlight_piece++;
			source.flower_piece++;
			return 1;
		}
		else { printf("壊せる雪月花がありません\n"); return 0;}
		break;

	}
    printf("error\n");
    return 0;
}

//紋を手元に得ます
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

//タイプを選びます
int Set_Crest() {//雪、月、花の内どれかを選択することができます
	while (1) {
		switch ((char)GetKeyInput())//陣地選択
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
			printf("不正な入力です\n");
			printf("(雪：z　月：x　花：c)から入力してください\n");
			continue;
		}
	}
}

//紋を作成します
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

//紋の効果を選択します
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

//雪の紋の効果
void Snow_Effect(int player_id) {
    printf("雪の紋の効果を発動します\n");
	while (1) {
		printf("どこの場所から雪の駒を取りますか？\n");
		printf("z:陣地 x:相手 c:源泉\n");
		switch (GetKeyInput())
		{
		case 'z'://陣地からとる場合
			if (snow.snow_piece == moonlight.snow_piece == flower.snow_piece == 0) { printf("取れる駒がありません\n"); continue; }
			printf("どの陣地から駒を得ますか？\n");
			printf("z:雪陣地　x:月陣地　c:花陣地");
			switch ((char)GetKeyInput())
			{
			case 'z':
				if (snow.snow_piece > 0) {
					snow.snow_piece--;
					player[player_id].snow_piece++;
				}
				else { printf("駒がありません\n"); continue; }
				break;
			case 'x':
				if (moonlight.snow_piece > 0) {
					moonlight.snow_piece--;
					player[player_id].snow_piece++;
				}
				else { printf("駒がありません\n"); continue;}
				break;
			case 'c':
				if (flower.snow_piece > 0) {
					flower.snow_piece--;
					player[player_id].snow_piece++;
				}
				else { printf("駒がありません\n"); continue;}
				break;
			default:
				printf("不正な入力です\n");
				break;
			}
			break;
		case 'x'://相手	
				if (player[Enemy(player_id)].snow_piece > 0) {
					player[Enemy(player_id)].snow_piece--;
					player[player_id].snow_piece++;
				}
                else { printf("駒がありません\n"); continue; }
                break;
			break;
		case 'c'://源泉
			if (source.snow_piece > 0) {
				source.snow_piece--;
				player[player_id].snow_piece++;
			}
            else { printf("駒がありません\n"); continue; }
			break;

		default:
			printf("不正な入力です\n");
			break;
		}
		break;
	}
}

//月の紋の効果
void Moonlight_Effect(int player_id, int target) {
    printf("月の紋の効果を発動します\n");
    switch (target) {
    case SNOW:
        if (player[Enemy(player_id)].snow_piece > 0) {
            player[Enemy(player_id)].snow_piece--;
            player[player_id].snow_piece++;
        }
        else { printf("駒がありません\n"); }
        break;


    case MOONLIGHT:
        if (player[Enemy(player_id)].moonlight_piece > 0) {
            player[Enemy(player_id)].moonlight_piece--;
            player[player_id].moonlight_piece++;
        }
        else { printf("駒がありません\n"); }
        break;

    case FLOWER:

        if (player[Enemy(player_id)].flower_piece > 0) {
            player[Enemy(player_id)].flower_piece--;
            player[player_id].flower_piece++;
        }
        else { printf("駒がありません\n"); }
        break;

    }

}

//花の紋の効果
void Flower_Effect(int player_id) {
    printf("花の紋の効果を発動します\n");
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
		printf("雪と月どちらの駒を取りますか?");
		printf("z:雪の駒　x:月の駒");
		switch (GetKeyInput()) {
		case 'z'://雪の場合
			if (source.snow_piece == 0) { Destroy_Motif(SNOW); }
			source.snow_piece -= 1;
			player[player_id].snow_piece += 1;
		case 'x'://月の場合
			if (source.moonlight_piece == 0) { Destroy_Motif(MOONLIGHT); }
			source.moonlight_piece -= 1;
			player[player_id].moonlight_piece += 1;
		}
		break;
	case SNOW_FLOWER:
		printf("雪と花どちらの駒を取りますか?");
		printf("z:雪の駒　x:花の駒");
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
		printf("月と花どちらの駒を取りますか?");
		printf("z:月の駒　x:花の駒");
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

//雪月花作成
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

//雪月花作成の効果
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

//カードの説明を表記します
int Explain_CardEffect(int type) {
	switch (type)
	{
	case SNOW:
		if (snow.card[0] == 1) { printf("1[雪崩]:任意の紋を3つ源泉に返す\n"); }
		if (snow.card[1] == 2) { printf("2[雪崩弐]:手元で任意の紋を2つ源泉に返す、盤面の雪月花を一つ解体する\n"); }
		if (snow.card[2] == 3) { printf("3[雪風]:任意の紋を解体し手元に得る\n"); }
		if ((snow.card[0] + snow.card[1] + snow.card[2]) == 0) { printf("取れるカードがありません\n"); return 0; }
        else {
            printf("1:雪崩　2:雪崩弐 3:雪風\n");
            printf("入力>>"); 
            return 1; }
        break;
	case MOONLIGHT:
		if (moonlight.card[0] == 1) { printf("1[月影]:手元から■▲●の駒を源泉に返す。対戦相手は次のターン、紋と雪月花を作成不可\n"); }
		if (moonlight.card[1] == 2) { printf("2[月蝕]:全ての対戦相手は次のターン手元に新たな片を得られない\n"); }
		if (moonlight.card[2] == 3) { printf("3[朧月]:各領域、対戦相手の手元から任意の駒を3つ得る\n"); }

		if ((moonlight.card[0] + moonlight.card[1] + moonlight.card[2]) == 0) { printf("取れるカードがありません\n"); return 0; }
        else {
            printf("1:月影　2:月蝕 3:朧月\n");
            printf("入力>>"); 
            return 1; }
        break;
	case FLOWER:
		if (flower.card[0] == 1) { printf("1[徒花]:花札領域の紋2つを源泉に返す。カードの効果を打ち消す\n"); }
		if (flower.card[1] == 2) { printf("2[開花]:源泉より任意の駒を2つ花の陣地に設置する\n"); }
		if (flower.card[2] == 3) { printf("3[万花]:源泉より花の駒を5つ花の陣地に設置する\n"); }

		if ((flower.card[0] + flower.card[1] + flower.card[2]) == 0) { printf("取れるカードがありません\n"); return 0; }
        else {
            printf("1:徒花　2:開花 3:万花\n");
            printf("入力>>"); 
            return 1; }
        break;
	default:
		break;
	}
    printf("error\n");
    return 0;
}

//プレイヤーの所持するカードの説明をします
int Explain_PlayerCardEffect(int player_id,int type) {
    switch (type)
    {
    case SNOW:
        if (player[player_id].snow_card[0] == 1) { printf("1[雪崩]:任意の紋を3つ源泉に返す\n"); }
        if (player[player_id].snow_card[1] == 2) { printf("2[雪崩弐]:手元で任意の紋を2つ源泉に返す、盤面の雪月花を一つ解体する\n"); }
        if (player[player_id].snow_card[2] == 3) { printf("3[雪風]:任意の紋を解体し手元に得る\n"); }
        if ((player[player_id].snow_card[0] + player[player_id].snow_card[1] + player[player_id].snow_card[2]) == 0) { printf("取れるカードがありません\n"); return 0; }
        else { return 1; }
        break;
    case MOONLIGHT:
        if (player[player_id].moonlight_card[0] == 1) { printf("1[月影]:手元から■▲●の駒を源泉に返す。対戦相手は次のターン、紋と雪月花を作成不可\n"); }
        if (player[player_id].moonlight_card[1] == 2) { printf("2[月蝕]:全ての対戦相手は次のターン手元に新たな片を得られない\n"); }
        if (player[player_id].moonlight_card[2] == 3) { printf("3[朧月]:各領域、対戦相手の手元から任意の駒を3つ得る\n"); }

        if ((player[player_id].moonlight_card[0] + player[player_id].moonlight_card[1] + player[player_id].moonlight_card[2]) == 0) { printf("取れるカードがありません\n"); return 0; }
        else {return 1;}
        break;
    case FLOWER:
        if (player[player_id].flower_card[0] == 1) { printf("1[徒花]:花の領域の紋2つを源泉に返す。カードの効果を打ち消す\n"); }
        if (player[player_id].flower_card[1] == 2) { printf("2[開花]:源泉より任意の駒を2つ花の陣地に設置する\n"); }
        if (player[player_id].flower_card[2] == 3) { printf("3[万花]:源泉より花の駒を5つ花の陣地に設置する\n"); }

        if ((player[player_id].flower_card[0] + player[player_id].flower_card[1] + player[player_id].flower_card[2]) == 0) { printf("取れるカードがありません\n"); return 0; }
        else {  return 1; }
        break;
    default:
        break;
    }
    printf("error\n");
    return 0;
}

//各エリアから手元に駒を得ることができます
int Get_Erea_Piece(int player_id,int erea, int type) {
    switch (erea) {

    case SNOW:
        switch (type) {

        case SNOW:
            if (snow.snow_piece == 0) { printf("取る駒がありません\n"); return 0; }
            else {
                snow.snow_piece--;
                player[player_id].snow_piece++;
                return 1;
            }
            break;
        case MOONLIGHT:
            if (snow.moonlight_piece == 0) { printf("取る駒がありません\n"); return 0; }
            else {
                snow.moonlight_piece--;
                player[player_id].moonlight_piece++;
                return 1;
            }
            break;
        case FLOWER:
            if (snow.flower_piece == 0) { printf("取る駒がありません\n"); return 0; }
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
            if (moonlight.snow_piece == 0) { printf("取る駒がありません\n"); return 0; }
            else {
                moonlight.snow_piece--;
                player[player_id].snow_piece++;
                return 1;
            }
            break;
        case MOONLIGHT:
            if (moonlight.moonlight_piece == 0) { printf("取る駒がありません\n"); return 0; }
            else {
                moonlight.moonlight_piece--;
                player[player_id].moonlight_piece++;
                return 1;
            }
            break;
        case FLOWER:
            if (moonlight.flower_piece == 0) { printf("取る駒がありません\n"); return 0; }
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
            if (flower.snow_piece == 0) { printf("取る駒がありません\n"); return 0; }
            else {
                flower.snow_piece--;
                player[player_id].snow_piece++;
                return 1;
            }
            break;
        case MOONLIGHT:
            if (flower.moonlight_piece == 0) { printf("取る駒がありません\n"); return 0; }
            else {
                flower.moonlight_piece--;
                player[player_id].moonlight_piece++;
                return 1;
            }
            break;
        case FLOWER:
            if (flower.flower_piece == 0) { printf("取る駒がありません\n"); return 0; }
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

//相手の手元から駒を得れます
int Deprive_Piece(int player_id,int type){
	switch (type) {
	case SNOW:
        if (player[Enemy(player_id)].snow_piece == 0) { printf("駒を持っていません\n"); return 0; }
        else {
            player[player_id].snow_piece++;
            player[Enemy(player_id)].snow_piece--;
            return 1;
        }
		break;
	case MOONLIGHT:
        if (player[Enemy(player_id)].moonlight_piece == 0) { printf("駒を持っていません\n"); return 0; }
        else {
            player[player_id].moonlight_piece++;
            player[Enemy(player_id)].moonlight_piece--;
            return 1;
        }
		break;
	case FLOWER:
        if (player[Enemy(player_id)].flower_piece == 0) { printf("駒を持っていません\n"); return 0; }
        else {
            player[player_id].flower_piece++;
            player[Enemy(player_id)].flower_piece--;
            return 1;
        }
		break;

    default:
        printf("失敗\n");
        return 0;
        break;
	}
}

//駒を源泉から移動させます
int Source_Move_Erea(int erea, int type) {
    if (erea == FLOWER) {
        switch (type) {
        case SNOW:
            if (source.snow_piece == 0) { printf("駒がありません\n"); return 0; }
            else {
                source.snow_piece--;
                flower.snow_piece++;
                return 1;
            }
            break;
        case MOONLIGHT:
            if (source.moonlight_piece == 0) { printf("駒がありません\n"); return 0; }
            else {
                source.moonlight_piece--;
                flower.moonlight_piece++;
                return 1;
            }
            break;
        case FLOWER:
            if (source.snow_piece == 0) { printf("駒がありません\n"); return 0; }
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

//カードを得ることができます
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

//陣地からカードを得る処理を行っています
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
		else { printf("カードが存在しません\n"); }
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
		else { printf("カードが存在しません\n"); }
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
		else { printf("カードが存在しません\n"); }
		break;
	default:
		break;
	}
}

//雪のカードの効果
int Snow_CardEffect(int player_id, int number) {
	int select_erea = 0;
	int select_type = 0;
	int destroy_motif = 0;
	int piece_type = 0;
	int sum_piece = 0; //効果を満たすための蓄積値です

	switch (number) {
	case 1:
		if (Check_Motif_Number() <= 3) { printf("紋の数が足りません"); return 0; }
		else {
			printf("任意の紋を3つ源泉に返します\n");
			for (int i = 0; i < 3; i++) {
				printf("どの陣地の紋を破壊しますか？\n");
                printf("z:雪　x:月　c:花\n");
				select_erea = Set_Crest();
				printf("どの紋を破壊しますか？\n");
				Destroy_Motif(select_erea);
				system("cls");
				Draw_Board();
			}
			return 1;
		}
		break;


	case 2:
		printf("手元で任意の紋を2つ源泉に返す、盤面の雪月花を一つ解体する\n");
		if (Check_Player_Motif(player_id, 1) == 0) { printf("条件を満たせずカードの使用ができません\n"); return 0; }
		while (1) {

			printf("どの駒を捧げますか？\n");
			printf("z:雪　x:月　c:花\n");
			printf(">>");
			piece_type = Set_Crest();
			switch (piece_type) {
			case SNOW:
				if (player[player_id].snow_piece >= 3) {
					player[player_id].snow_piece -= 3;
					source.snow_piece += 3;
					sum_piece += 3;
				}
				else { printf("駒が足りません\n"); continue; }
				break;
			case MOONLIGHT:
				if (player[player_id].moonlight_piece >= 3) {
					player[player_id].moonlight_piece -= 3;
					source.moonlight_piece += 3;
					sum_piece += 3;
				}
				else { printf("駒が足りません\n"); continue; }
				break;
			case FLOWER:
				if (player[player_id].flower_piece >= 3) {
					player[player_id].flower_piece -= 3;
					source.flower_piece += 3;
					sum_piece += 3;
				}
				else { printf("駒が足りません\n"); continue; }
				break;

			}

			if (sum_piece == 6) {
				while (1) {
					printf("どこの陣地を壊しますか");
					select_erea = Set_Crest();
					if (Destroy_BeautiesSeasonMotif(select_erea) == 1) { return 1;  break; }
					else { continue; }
				}

			}
		}
		printf("失敗\n");
		return 0;
		break;
	case 3:
		while (1) {
			if (Check_Motif_Number() < 0) { printf("解体できる紋がありません\n"); return 0; break; }
			printf("任意の紋を解体し手元に得る事ができます\n");
			select_erea = Set_Crest();
			select_type = Set_Crest();
			if (Get_Motif_Piece(player_id, select_erea, select_type) == 0) { printf("紋が解体できませんでした\n"); continue; }
			else { return 1; break; }

		}
	default:
		break;
		
	}
    printf("error\n");
    return 0;
}

//月のカードの効果
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
		else { printf("駒がありません\n"); return 0; }

		break;

	case 2:
		card_flag.moon_card_flag_2 = 1;
        return 1;
		break;

    case 3:

        if (Sum_Player_Piece(Enemy(player_id)) + Sum_Board_Piece() < 3)
		{printf("取れる駒がありません\n");  return 0;}

		while (get_piece < 3) {
            system("cls");
            Draw_Board();
			printf("各領域と相手の手元から計三個駒を得ることができます\n");
			printf("z:各領域　x:相手の手元\n");
			printf("入力>>");
			switch (GetKeyInput())
			{
			case 'z':
                printf("取る陣地を選んでください\n");
                printf("z:雪　x:月　y:花\n");
                printf("入力>>");
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

//花のカードの効果
int  Flower_CardEffect(int player_id, int number) {
    int type = 0;
    int disasse_motif = 0;
    int piece_number = 0;
    switch (number) {
    case 1: //開花
        if ((FlowerErea_Motif_Numbers(SNOW) + FlowerErea_Motif_Numbers(MOONLIGHT) + FlowerErea_Motif_Numbers(FLOWER)) > 2) {
            while (disasse_motif < 2) {
                printf("花札領域の紋を二つ源泉に返す\n");
                type = Set_Crest();
                if (Dissase_Motif(FLOWER, type) == 1) {
                    disasse_motif++;
                }
            }
            return 1;
        }
        else { return 0; }
        break;
    case 2: //万花
        if ((source.snow_piece + source.moonlight_piece + source.flower_piece) < 2) { printf("効果を満たすだけの駒がありません\n"); return 0; }
        printf("源泉より、任意の片を2つ、花姫領域に設置します.");
        while (piece_number < 2) {
            printf("設置したい駒を指定してください\n");
            printf("z:雪　x:月　c:花　\n");
            printf("入力>>");
            type = Set_Crest();
            if (Source_Move_Erea(FLOWER, type) == 1) {
                piece_number++;
            }
            else { printf("失敗\n"); continue; }
        }

        if (piece_number == 2) { return 1; }
        else { printf("error\n"); return 0; }

        break;

    case 3: //徒花
        printf("源泉より、花片を5つ花姫領域に設置する\n");
        if (source.flower_piece > 5) {
            source.flower_piece -= 5;
            flower.flower_piece += 5;
            return 1;
        }
        else { return 0; }

        break;
    default: //エラー処理
        printf("Error:Flower?CardEffect");
        break;
    }
    printf("error\n");
    return 0;
}

//使用したカードが不発に終わった場合使用をカードの数を元に戻します
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

//カードを使った時の処理を行います.カードを使用したら盤面に戻す処理を行っています。
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

//カードを使う時の処理をまとめた関数です
void Use_Card(int player_id) {
    int type = 0;
    int number = 0;
    int sum = 0;
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            sum += Check_Card(player_id, i, j);
        }
    }
    if (sum == 0) { printf("使えるカードがありません\n"); return; }
    while (1) {
        Draw_Board();
        printf("どこの陣地のカードを使うか選んでください\n");
        printf("z:雪　x:月　c:花　v:終了　\n");
        printf(">>");
        type = Set_Crest();
        if (type == NONE) { return; }
        if (Explain_PlayerCardEffect(player_id,type) == 0) { system("cls"); continue; }
        printf("どのカードを使いますか？\n");
        if (type == SNOW) {printf("1:雪崩　2:雪崩弐 3:雪風\n");}
        else if(type == MOONLIGHT) {printf("1:月影　2:月蝕 3:朧月\n");}
        else if (type == FLOWER) {printf("1:徒花　2:開花 3:万花\n");}
        printf("入力>>");
        number = Check_Nunber(1, 3);
        if (Check_Card(player_id, type, number) == 0) { system("cls"); continue; }

        Card_Effect( player_id, type, number);

        /*徒花カード効果*/
        if(player[Enemy(player_id)].flower_card[0] == 1){
            printf("相手に交代してください\n");
            if (Flower_CardEffect(Enemy(player_id), 1) == 1) {
                printf("相手のカードの効果を打ち消します。");
                continue;
            }
            else { printf("条件が足りませんでした、相手カードの使用を続行します。"); }
        }
        /*割り込み終了*/
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

