// CapplitioMoiif.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include"stdio.h"
#include<time.h>
#include"Game_Flow.h"
#include"Status.h"
#include"Option.h"
#include"Checker.h"
#include"System.h"
#include"AI.h"
#define STR(var) #var //引数にした変数を変数名を示す文字列リテラルとして返すマクロ関数

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
//盤面表示
void Draw_Board() {
    printf("−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−\n");
    printf("|\t　　　雪の陣地\t\t|\t　　　月の陣地\t\t|\t　　　花の陣地\t\t|\n");
    //各エリアの駒の数
    printf("|駒： ■×%d\t●×%d\t▲×%d\t|", snow.snow_piece, snow.moonlight_piece, snow.flower_piece);
    printf("駒： ■×%d\t●×%d\t▲×%d\t|", moonlight.snow_piece, moonlight.moonlight_piece, moonlight.flower_piece);
    printf("駒： ■×%d\t●×%d\t▲×%d\t|", flower.snow_piece, flower.moonlight_piece, flower.flower_piece);
    printf("\n");
    //各エリアの紋の数
    printf("|紋： □×%d\t○×%d\t△×%d\t|", snow.snow_motif, snow.moonlight_motif, snow.flower_motif);
    printf("紋： □×%d\t○×%d\t△×%d\t|", moonlight.snow_motif, moonlight.moonlight_motif, moonlight.flower_motif);
    printf("紋： □×%d\t○×%d\t△×%d\t|", flower.snow_motif, flower.moonlight_motif, flower.flower_motif);
    printf("\n");
    //各エリアの雪月花の数
    printf("|\t雪月花:\t×%d\t\t|", snow.beauties_season_motif);
    printf("\t雪月花:\t×%d\t\t|", moonlight.beauties_season_motif);
    printf("\t雪月花:\t×%d\t\t|", flower.beauties_season_motif);
    printf("\n");
    //各エリアのカードの数
    printf("|\t　札　:\t%d %d %d\t\t|", snow.card[0], snow.card[1], snow.card[2]);
    printf("\t　札　:\t%d %d %d\t\t|", moonlight.card[0], moonlight.card[1], moonlight.card[2]);
    printf("\t　札　:\t%d %d %d\t\t|", flower.card[0], flower.card[1], flower.card[2]);
    printf("\n");

    printf("−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−\n");
    //プレイヤーの所持証の表示
    printf("|\t　　　PL1\t\t|\t　　　源泉\t\t|\t　　　PL2\t\t|\n");
    printf("|\t    証：");
    if (player[0].contract_priestess == SNOW) { printf("雪"); }
    else if (player[0].contract_priestess == MOONLIGHT) { printf("月"); }
    else if (player[0].contract_priestess == FLOWER) { printf("花"); }
    else { printf("無"); }
    printf("           \t|");

    printf("\t                 \t|");

    printf("\t    証：");
    if (player[1].contract_priestess == SNOW) { printf("雪"); }
    else if (player[1].contract_priestess == MOONLIGHT) { printf("月"); }
    else if (player[1].contract_priestess == FLOWER) { printf("花"); }
    else { printf("無"); }
    printf("           \t|");
    printf("\n");
    //プレイヤーの所持駒
    printf("|駒： ■×%d\t●×%d\t▲×%d\t", player[0].snow_piece, player[0].moonlight_piece, player[0].flower_piece);
    printf("|\t                 \t");
    printf("|駒： ■×%d\t●×%d\t▲×%d\t|", player[1].snow_piece, player[1].moonlight_piece, player[1].flower_piece);
    printf("\n");
    //プレイヤーの札の数
    printf("|\t所持雪札:%d ,%d ,%d\t", player[0].snow_card[0], player[0].snow_card[1], player[0].snow_card[2]);
    printf("|駒： ■×%d\t●×%d\t▲×%d\t", source.snow_piece, source.moonlight_piece, source.flower_piece);
    printf("|\t所持雪札:%d ,%d ,%d\t|", player[1].snow_card[0], player[1].snow_card[1], player[1].snow_card[2]);
    printf("\n");

    printf("|\t所持月札:%d ,%d ,%d\t", player[0].moonlight_card[0], player[0].moonlight_card[1], player[0].moonlight_card[2]);
    printf("|\t                 \t");
    printf("|\t所持月札:%d ,%d ,%d\t|", player[1].moonlight_card[0], player[1].moonlight_card[1], player[1].moonlight_card[2]);
    printf("\n");

    printf("|\t所持花札:%d ,%d ,%d\t", player[0].flower_card[0], player[0].flower_card[1], player[0].flower_card[2]);
    printf("|\t                 \t");
    printf("|\t所持花札:%d ,%d ,%d\t|", player[1].flower_card[0], player[1].flower_card[1], player[1].flower_card[2]);
    printf("\n");

    printf("−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−\n");
}
//駒の設置
void Put_Piece(int player_id)
{//駒を設置する
    PRIESTESS put_target;
    PRIESTESS put_piece;
    int put_num = 0;
    int flag = 0;


    while (1) {
        system("cls");
        Draw_Board();
        put_num = 0;
        Player(player_id);

        printf("駒を設置する陣地を入力してください(雪：z　月：x　花：c　設置終了：v)\n");
        if (flag == 0) { printf("紋と異なる駒をあと1回置けます\n"); }
        else if (flag == 1) { printf("紋と異なる駒はもうおけません\n"); }
        printf("入力>>");
        put_target = (PRIESTESS)Set_Crest();
        if (put_target == NONE) { printf("次のステップに行きます。"); Pause(); return; }
        else if (3 < put_target || put_target < 0) { printf("入力が不正です\n"); Pause(); continue; }

        printf("設置する駒の種類を入力してください(雪：z　月：x　花：c)\n");
        printf("入力>>");
        put_piece = (PRIESTESS)Set_Crest();
        if (3 < put_target || put_target <= 0) { printf("最初に戻ります\n"); Pause(); continue; }


        printf("置く駒の個数を入力してください:");
        printf("入力>>");
        put_num = GetNumberInput();
        if (Check_Put_Piece(player_id, put_target, put_piece, put_num) == 1) {
            ("値が不正です\n");
            put_num = 0;
            Pause();
            continue;
        }
        else if (Check_Put_Piece(player_id, put_target, put_piece, put_num) == 2) {
            if (flag == 1) {
                printf("もう異なる陣地に駒を置くことはできません\n");
                Pause();
            }
            else {
                flag = 1;

            }
        }

        switch (put_target) {
        case SNOW: //雪陣地の駒の設置
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
            else { printf("Error：設置する駒の指定\n"); }

            break;
        case MOONLIGHT://月陣地の駒の設置
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
            else { printf("Error：設置する駒の指定\n"); }
            break;
        case FLOWER://花陣地の駒の設置
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
            else { printf("Error：設置する駒の指定\n"); }
            break;
        default:
            printf("Error：Put_Piece不正な処理です%d\n",__LINE__);
            break;
        }
    }
}

//紋の作成
void Create_Motif(int player_id) {//紋の作成
    PRIESTESS put_target;
    PRIESTESS motif_type;
    int make_num;
    while (1) {
        system("cls");
        Draw_Board();
        printf("陣地にある駒3つを1つの紋にすることができます。\n");
        printf("紋を作成する陣地を入力してください(雪：z　月：x　花：c　設置終了：v)\n");
        printf("入力>>");
        put_target = (PRIESTESS)Set_Crest();
        if (put_target == NONE) { printf("次のステップに行きます。"); Pause(); return; }
        else if (3 < put_target || put_target < 0) { continue; }

        printf("作成する紋の種類を入力してください(雪：z　月：x　花：c)\n");
        printf("入力>>");
        motif_type = (PRIESTESS)Set_Crest();
        if (3 < put_target || put_target <= 0) { printf("最初に戻ります\n"); Pause(); continue; }

        printf("作成する紋の個数を入力してください\n");
        printf("入力>>");
        make_num = GetNumberInput();

        if (Check_Motif(put_target, motif_type, make_num) == 0) { make_num = 0; Pause(); continue; }
        else { Make_Motif(player_id, put_target, motif_type, make_num); Pause(); }
    }

}
//雪月花の作成
void Create_BeautiesSeasonMotif(int player_id) {//雪月花の作成
    int put_target;
    while (1) {
        system("cls");
        Draw_Board();
        printf("どこに雪月花を設置しますか？\n");
        printf("作成する陣地を入力してください(雪：z　月：x　花：c　設置終了：v)\n");
        printf("入力>>");
        put_target = Set_Crest();
        if (put_target == NONE) { printf("次のステップに行きます。"); Pause(); return; }
        else if (3 < put_target || put_target < 0) { continue; }

        if (Check_BeautiesSeasonMotif(player_id, put_target) == 1) {//雪月花が作れた場合
            Make_BeautiesSeasonMotif(player_id, put_target);		//雪月花の作成
            Renew();
            Draw_Board();
        }
        else if (Check_BeautiesSeasonMotif(player_id, put_target) == 0) {
            printf("雪月花の作成条件が満たされていません\n");
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
        //駒の獲得
        AcquirePiece(player_id);

        Renew();


        //カードの使用
        Use_Card(player_id);

        /*駒の設置*/
        if (mooncard2_effect_flag == 0) { Put_Piece(player_id); }
        //カード２の効果
        else if (mooncard2_effect_flag == 1) {
            printf("カードの効果でスキップします\n");
            mooncard2_effect_flag = 0;
            card_flag.moon_card_flag_2 = 0;
        }
        /*駒の設置終了*/

        /*紋の作成*/
        if (mooncard1_effect_flag == 0) { Create_Motif(player_id); }
        //カード１の効果
        else if (mooncard1_effect_flag == 1) { printf("カードの効果でスキップします\n"); }
        /*紋の作成終了*/

        /*雪月花の作成*/
        if (mooncard1_effect_flag == 0) { Create_BeautiesSeasonMotif(player_id); }
        //カード１の効果
        else if (mooncard1_effect_flag == 1) {
            mooncard1_effect_flag = 0;
            card_flag.moon_card_flag_1 = 0;
            printf("カードの効果でスキップします\n");
        }
        /*雪月花の作成終了*/


        /*勝利条件の判定*/
        system("cls");
        Draw_Board();
        winner = Judge(player_id);
        if (winner == 0) { printf("player1の勝ち！"); break; }
        else if (winner == 1) { printf("player2の勝ち！"); break; }
        else { printf("ターンを交代します。"); }
        /*勝利判定終了*/

        //ターンの交代
        player_id = GetNextTurnPlayer(player_id);

        Renew();
        //カードの効果
        if (card_flag.moon_card_flag_1 == 1) {//月のカード１の効果　紋と雪月花作成不可
            mooncard1_effect_flag = 1;
        }
        if (card_flag.moon_card_flag_2 == 1) {//月のカード２の効果　ダイスで駒を得れない
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
        printf("手数=%d,プレイヤー=%d,all_playouts=%d\n", tesuu, player_id, all_playouts);
        winner = Judge(player_id);
        if (winner == 0) { printf("player1の勝ち！"); break; }
        else if (winner == 1) { printf("player2の勝ち！"); break; }
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

