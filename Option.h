#pragma once
#include<Windows.h>
#include<stdio.h>

/*
画面のクリアや数字、文字の入力などの汎用性のあるシステム
*/

//文字の入力をします
int GetKeyInput() {
	int key;
	while (1) {
		key = getchar();
		//入力されたキーが改行の場合、不正入力
		if (key == '\n')printf("Illegal Input(Enter)\n");
		//改行以外の場合、以下の処理へ
		else {
			//次に読み込んだ文字が改行なら、正常入力
			if (getchar() == '\n') {
				//printf("Success\n");
				break;
			}
			//それ以外の文字が入っていたら、不正入力
			//その後、バッファをクリアする
			else {
				while (getchar() != '\n');
				printf("Illegal Input(not 1 char)\n");
			}
		}
	}
	return key;
}

//数字の入力をします
int GetNumberInput() {
	int key;
	while (1) {

		key = getchar()-'0';

		//入力されたキーが改行の場合、不正入力
		if (key == '\n')printf("Illegal Input(Enter)\n");
       else if (0 >= key || key >= 9) {while (getchar() != '\n'); printf("数値を入力しなおしてください\n"); continue; }
        //改行以外の場合、以下の処理へ
		else {
			//次に読み込んだ文字が改行なら、正常入力
			if (getchar() == '\n') {
				//printf("Success\n");
				break;
			}
			//それ以外の文字が入っていたら、不正入力
			//その後、バッファをクリアする
			else {
				while (getchar() != '\n');
				printf("Illegal Input(not 1 char)\n");
			}
		}
	}
	return (int)key;
}

//Enterを押してから画面を一新します
void Renew() {//Enterを押すと画面を更新します
	int c;
	printf("enterを押すと次に進みます");
	if ((c = getchar()) == '\n') {}
	else { while (getchar() != '\n'); }
	system("cls");

}

//Enterを押したら進みます
void Pause() {//Enterを押すまで先に進みません
	int c;
	printf("enterを押すと次に進みます");
	if ((c = getchar()) == '\n') {}
	else { while (getchar() != '\n'); }
}

//プレイヤーの手番を教えてくれます
void Player(int player_id) {
	if (player_id == 0) {printf("player1の手番です。\n");}
	else if(player_id == 1){printf("player2の手番です。\n");}
}

//相手の手番を参照します
int Enemy(int player_id) {
	if (player_id == 1) {
		return 0;
	}
	else if (player_id == 0) {
		return 1;
    }
    else { printf("error!\n"); return 10; }

}
