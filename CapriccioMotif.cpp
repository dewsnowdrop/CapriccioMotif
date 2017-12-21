// CapplitioMoiif.cpp : ƒRƒ“ƒ\[ƒ‹ ƒAƒvƒŠƒP[ƒVƒ‡ƒ“‚ÌƒGƒ“ƒgƒŠ ƒ|ƒCƒ“ƒg‚ğ’è‹`‚µ‚Ü‚·B
//

#include"stdio.h"
#include<time.h>
#include"Game_Flow.h"
#include"Status.h"
#include"Option.h"
#include"Checker.h"
#include"System.h"
#include"AI.h"
#define STR(var) #var //ˆø”‚É‚µ‚½•Ï”‚ğ•Ï”–¼‚ğ¦‚·•¶š—ñƒŠƒeƒ‰ƒ‹‚Æ‚µ‚Ä•Ô‚·ƒ}ƒNƒŠÖ”

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
//”Õ–Ê•\¦
void Draw_Board() {
    printf("||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|\t@@@á‚Ìw’n\t\t|\t@@@Œ‚Ìw’n\t\t|\t@@@‰Ô‚Ìw’n\t\t|\n");
    //ŠeƒGƒŠƒA‚Ì‹î‚Ì”
    printf("|‹îF ¡~%d\tœ~%d\t£~%d\t|", snow.snow_piece, snow.moonlight_piece, snow.flower_piece);
    printf("‹îF ¡~%d\tœ~%d\t£~%d\t|", moonlight.snow_piece, moonlight.moonlight_piece, moonlight.flower_piece);
    printf("‹îF ¡~%d\tœ~%d\t£~%d\t|", flower.snow_piece, flower.moonlight_piece, flower.flower_piece);
    printf("\n");
    //ŠeƒGƒŠƒA‚Ì–ä‚Ì”
    printf("|–äF  ~%d\t›~%d\t¢~%d\t|", snow.snow_motif, snow.moonlight_motif, snow.flower_motif);
    printf("–äF  ~%d\t›~%d\t¢~%d\t|", moonlight.snow_motif, moonlight.moonlight_motif, moonlight.flower_motif);
    printf("–äF  ~%d\t›~%d\t¢~%d\t|", flower.snow_motif, flower.moonlight_motif, flower.flower_motif);
    printf("\n");
    //ŠeƒGƒŠƒA‚ÌáŒ‰Ô‚Ì”
    printf("|\táŒ‰Ô:\t~%d\t\t|", snow.beauties_season_motif);
    printf("\táŒ‰Ô:\t~%d\t\t|", moonlight.beauties_season_motif);
    printf("\táŒ‰Ô:\t~%d\t\t|", flower.beauties_season_motif);
    printf("\n");
    //ŠeƒGƒŠƒA‚ÌƒJ[ƒh‚Ì”
    printf("|\t@D@:\t%d %d %d\t\t|", snow.card[0], snow.card[1], snow.card[2]);
    printf("\t@D@:\t%d %d %d\t\t|", moonlight.card[0], moonlight.card[1], moonlight.card[2]);
    printf("\t@D@:\t%d %d %d\t\t|", flower.card[0], flower.card[1], flower.card[2]);
    printf("\n");

    printf("||||||||||||||||||||||||||||||||||||||||||||||||\n");
    //ƒvƒŒƒCƒ„[‚ÌŠØ‚Ì•\¦
    printf("|\t@@@PL1\t\t|\t@@@Œ¹ò\t\t|\t@@@PL2\t\t|\n");
    printf("|\t    ØF");
    if (player[0].contract_priestess == SNOW) { printf("á"); }
    else if (player[0].contract_priestess == MOONLIGHT) { printf("Œ"); }
    else if (player[0].contract_priestess == FLOWER) { printf("‰Ô"); }
    else { printf("–³"); }
    printf("           \t|");

    printf("\t                 \t|");

    printf("\t    ØF");
    if (player[1].contract_priestess == SNOW) { printf("á"); }
    else if (player[1].contract_priestess == MOONLIGHT) { printf("Œ"); }
    else if (player[1].contract_priestess == FLOWER) { printf("‰Ô"); }
    else { printf("–³"); }
    printf("           \t|");
    printf("\n");
    //ƒvƒŒƒCƒ„[‚ÌŠ‹î
    printf("|‹îF ¡~%d\tœ~%d\t£~%d\t", player[0].snow_piece, player[0].moonlight_piece, player[0].flower_piece);
    printf("|\t                 \t");
    printf("|‹îF ¡~%d\tœ~%d\t£~%d\t|", player[1].snow_piece, player[1].moonlight_piece, player[1].flower_piece);
    printf("\n");
    //ƒvƒŒƒCƒ„[‚ÌD‚Ì”
    printf("|\tŠáD:%d ,%d ,%d\t", player[0].snow_card[0], player[0].snow_card[1], player[0].snow_card[2]);
    printf("|‹îF ¡~%d\tœ~%d\t£~%d\t", source.snow_piece, source.moonlight_piece, source.flower_piece);
    printf("|\tŠáD:%d ,%d ,%d\t|", player[1].snow_card[0], player[1].snow_card[1], player[1].snow_card[2]);
    printf("\n");

    printf("|\tŠŒD:%d ,%d ,%d\t", player[0].moonlight_card[0], player[0].moonlight_card[1], player[0].moonlight_card[2]);
    printf("|\t                 \t");
    printf("|\tŠŒD:%d ,%d ,%d\t|", player[1].moonlight_card[0], player[1].moonlight_card[1], player[1].moonlight_card[2]);
    printf("\n");

    printf("|\tŠ‰ÔD:%d ,%d ,%d\t", player[0].flower_card[0], player[0].flower_card[1], player[0].flower_card[2]);
    printf("|\t                 \t");
    printf("|\tŠ‰ÔD:%d ,%d ,%d\t|", player[1].flower_card[0], player[1].flower_card[1], player[1].flower_card[2]);
    printf("\n");

    printf("||||||||||||||||||||||||||||||||||||||||||||||||\n");
}
//‹î‚Ìİ’u
void Put_Piece(int player_id)
{//‹î‚ğİ’u‚·‚é
    PRIESTESS put_target;
    PRIESTESS put_piece;
    int put_num = 0;
    int flag = 0;


    while (1) {
        system("cls");
        Draw_Board();
        put_num = 0;
        Player(player_id);

        printf("‹î‚ğİ’u‚·‚éw’n‚ğ“ü—Í‚µ‚Ä‚­‚¾‚³‚¢(áFz@ŒFx@‰ÔFc@İ’uI—¹Fv)\n");
        if (flag == 0) { printf("–ä‚ÆˆÙ‚È‚é‹î‚ğ‚ ‚Æ1‰ñ’u‚¯‚Ü‚·\n"); }
        else if (flag == 1) { printf("–ä‚ÆˆÙ‚È‚é‹î‚Í‚à‚¤‚¨‚¯‚Ü‚¹‚ñ\n"); }
        printf("“ü—Í>>");
        put_target = (PRIESTESS)Set_Crest();
        if (put_target == NONE) { printf("Ÿ‚ÌƒXƒeƒbƒv‚És‚«‚Ü‚·B"); Pause(); return; }
        else if (3 < put_target || put_target < 0) { printf("“ü—Í‚ª•s³‚Å‚·\n"); Pause(); continue; }

        printf("İ’u‚·‚é‹î‚Ìí—Ş‚ğ“ü—Í‚µ‚Ä‚­‚¾‚³‚¢(áFz@ŒFx@‰ÔFc)\n");
        printf("“ü—Í>>");
        put_piece = (PRIESTESS)Set_Crest();
        if (3 < put_target || put_target <= 0) { printf("Å‰‚É–ß‚è‚Ü‚·\n"); Pause(); continue; }


        printf("’u‚­‹î‚ÌŒÂ”‚ğ“ü—Í‚µ‚Ä‚­‚¾‚³‚¢:");
        printf("“ü—Í>>");
        put_num = GetNumberInput();
        if (Check_Put_Piece(player_id, put_target, put_piece, put_num) == 1) {
            ("’l‚ª•s³‚Å‚·\n");
            put_num = 0;
            Pause();
            continue;
        }
        else if (Check_Put_Piece(player_id, put_target, put_piece, put_num) == 2) {
            if (flag == 1) {
                printf("‚à‚¤ˆÙ‚È‚éw’n‚É‹î‚ğ’u‚­‚±‚Æ‚Í‚Å‚«‚Ü‚¹‚ñ\n");
                Pause();
            }
            else {
                flag = 1;

            }
        }

        switch (put_target) {
        case SNOW: //áw’n‚Ì‹î‚Ìİ’u
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
            else { printf("ErrorFİ’u‚·‚é‹î‚Ìw’è\n"); }

            break;
        case MOONLIGHT://Œw’n‚Ì‹î‚Ìİ’u
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
            else { printf("ErrorFİ’u‚·‚é‹î‚Ìw’è\n"); }
            break;
        case FLOWER://‰Ôw’n‚Ì‹î‚Ìİ’u
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
            else { printf("ErrorFİ’u‚·‚é‹î‚Ìw’è\n"); }
            break;
        default:
            printf("ErrorFPut_Piece•s³‚Èˆ—‚Å‚·%d\n",__LINE__);
            break;
        }
    }
}

//–ä‚Ìì¬
void Create_Motif(int player_id) {//–ä‚Ìì¬
    PRIESTESS put_target;
    PRIESTESS motif_type;
    int make_num;
    while (1) {
        system("cls");
        Draw_Board();
        printf("w’n‚É‚ ‚é‹î3‚Â‚ğ1‚Â‚Ì–ä‚É‚·‚é‚±‚Æ‚ª‚Å‚«‚Ü‚·B\n");
        printf("–ä‚ğì¬‚·‚éw’n‚ğ“ü—Í‚µ‚Ä‚­‚¾‚³‚¢(áFz@ŒFx@‰ÔFc@İ’uI—¹Fv)\n");
        printf("“ü—Í>>");
        put_target = (PRIESTESS)Set_Crest();
        if (put_target == NONE) { printf("Ÿ‚ÌƒXƒeƒbƒv‚És‚«‚Ü‚·B"); Pause(); return; }
        else if (3 < put_target || put_target < 0) { continue; }

        printf("ì¬‚·‚é–ä‚Ìí—Ş‚ğ“ü—Í‚µ‚Ä‚­‚¾‚³‚¢(áFz@ŒFx@‰ÔFc)\n");
        printf("“ü—Í>>");
        motif_type = (PRIESTESS)Set_Crest();
        if (3 < put_target || put_target <= 0) { printf("Å‰‚É–ß‚è‚Ü‚·\n"); Pause(); continue; }

        printf("ì¬‚·‚é–ä‚ÌŒÂ”‚ğ“ü—Í‚µ‚Ä‚­‚¾‚³‚¢\n");
        printf("“ü—Í>>");
        make_num = GetNumberInput();

        if (Check_Motif(put_target, motif_type, make_num) == 0) { make_num = 0; Pause(); continue; }
        else { Make_Motif(player_id, put_target, motif_type, make_num); Pause(); }
    }

}
//áŒ‰Ô‚Ìì¬
void Create_BeautiesSeasonMotif(int player_id) {//áŒ‰Ô‚Ìì¬
    int put_target;
    while (1) {
        system("cls");
        Draw_Board();
        printf("‚Ç‚±‚ÉáŒ‰Ô‚ğİ’u‚µ‚Ü‚·‚©H\n");
        printf("ì¬‚·‚éw’n‚ğ“ü—Í‚µ‚Ä‚­‚¾‚³‚¢(áFz@ŒFx@‰ÔFc@İ’uI—¹Fv)\n");
        printf("“ü—Í>>");
        put_target = Set_Crest();
        if (put_target == NONE) { printf("Ÿ‚ÌƒXƒeƒbƒv‚És‚«‚Ü‚·B"); Pause(); return; }
        else if (3 < put_target || put_target < 0) { continue; }

        if (Check_BeautiesSeasonMotif(player_id, put_target) == 1) {//áŒ‰Ô‚ªì‚ê‚½ê‡
            Make_BeautiesSeasonMotif(player_id, put_target);		//áŒ‰Ô‚Ìì¬
            Renew();
            Draw_Board();
        }
        else if (Check_BeautiesSeasonMotif(player_id, put_target) == 0) {
            printf("áŒ‰Ô‚Ìì¬ğŒ‚ª–‚½‚³‚ê‚Ä‚¢‚Ü‚¹‚ñ\n");
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
        //‹î‚ÌŠl“¾
        AcquirePiece(player_id);

        Renew();


        //ƒJ[ƒh‚Ìg—p
        Use_Card(player_id);

        /*‹î‚Ìİ’u*/
        if (mooncard2_effect_flag == 0) { Put_Piece(player_id); }
        //ƒJ[ƒh‚Q‚ÌŒø‰Ê
        else if (mooncard2_effect_flag == 1) {
            printf("ƒJ[ƒh‚ÌŒø‰Ê‚ÅƒXƒLƒbƒv‚µ‚Ü‚·\n");
            mooncard2_effect_flag = 0;
            card_flag.moon_card_flag_2 = 0;
        }
        /*‹î‚Ìİ’uI—¹*/

        /*–ä‚Ìì¬*/
        if (mooncard1_effect_flag == 0) { Create_Motif(player_id); }
        //ƒJ[ƒh‚P‚ÌŒø‰Ê
        else if (mooncard1_effect_flag == 1) { printf("ƒJ[ƒh‚ÌŒø‰Ê‚ÅƒXƒLƒbƒv‚µ‚Ü‚·\n"); }
        /*–ä‚Ìì¬I—¹*/

        /*áŒ‰Ô‚Ìì¬*/
        if (mooncard1_effect_flag == 0) { Create_BeautiesSeasonMotif(player_id); }
        //ƒJ[ƒh‚P‚ÌŒø‰Ê
        else if (mooncard1_effect_flag == 1) {
            mooncard1_effect_flag = 0;
            card_flag.moon_card_flag_1 = 0;
            printf("ƒJ[ƒh‚ÌŒø‰Ê‚ÅƒXƒLƒbƒv‚µ‚Ü‚·\n");
        }
        /*áŒ‰Ô‚Ìì¬I—¹*/


        /*Ÿ—˜ğŒ‚Ì”»’è*/
        system("cls");
        Draw_Board();
        winner = Judge(player_id);
        if (winner == 0) { printf("player1‚ÌŸ‚¿I"); break; }
        else if (winner == 1) { printf("player2‚ÌŸ‚¿I"); break; }
        else { printf("ƒ^[ƒ“‚ğŒğ‘ã‚µ‚Ü‚·B"); }
        /*Ÿ—˜”»’èI—¹*/

        //ƒ^[ƒ“‚ÌŒğ‘ã
        player_id = GetNextTurnPlayer(player_id);

        Renew();
        //ƒJ[ƒh‚ÌŒø‰Ê
        if (card_flag.moon_card_flag_1 == 1) {//Œ‚ÌƒJ[ƒh‚P‚ÌŒø‰Ê@–ä‚ÆáŒ‰Ôì¬•s‰Â
            mooncard1_effect_flag = 1;
        }
        if (card_flag.moon_card_flag_2 == 1) {//Œ‚ÌƒJ[ƒh‚Q‚ÌŒø‰Ê@ƒ_ƒCƒX‚Å‹î‚ğ“¾‚ê‚È‚¢
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
        printf("è”=%d,ƒvƒŒƒCƒ„[=%d,all_playouts=%d\n", tesuu, player_id, all_playouts);
        winner = Judge(player_id);
        if (winner == 0) { printf("player1‚ÌŸ‚¿I"); break; }
        else if (winner == 1) { printf("player2‚ÌŸ‚¿I"); break; }
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

