#pragma once
#include<Windows.h>
#include<stdio.h>

/*
��ʂ̃N���A�␔���A�����̓��͂Ȃǂ̔ėp���̂���V�X�e��
*/

//�����̓��͂����܂�
int GetKeyInput() {
	int key;
	while (1) {
		key = getchar();
		//���͂��ꂽ�L�[�����s�̏ꍇ�A�s������
		if (key == '\n')printf("Illegal Input(Enter)\n");
		//���s�ȊO�̏ꍇ�A�ȉ��̏�����
		else {
			//���ɓǂݍ��񂾕��������s�Ȃ�A�������
			if (getchar() == '\n') {
				//printf("Success\n");
				break;
			}
			//����ȊO�̕����������Ă�����A�s������
			//���̌�A�o�b�t�@���N���A����
			else {
				while (getchar() != '\n');
				printf("Illegal Input(not 1 char)\n");
			}
		}
	}
	return key;
}

//�����̓��͂����܂�
int GetNumberInput() {
	int key;
	while (1) {

		key = getchar()-'0';

		//���͂��ꂽ�L�[�����s�̏ꍇ�A�s������
		if (key == '\n')printf("Illegal Input(Enter)\n");
       else if (0 >= key || key >= 9) {while (getchar() != '\n'); printf("���l����͂��Ȃ����Ă�������\n"); continue; }
        //���s�ȊO�̏ꍇ�A�ȉ��̏�����
		else {
			//���ɓǂݍ��񂾕��������s�Ȃ�A�������
			if (getchar() == '\n') {
				//printf("Success\n");
				break;
			}
			//����ȊO�̕����������Ă�����A�s������
			//���̌�A�o�b�t�@���N���A����
			else {
				while (getchar() != '\n');
				printf("Illegal Input(not 1 char)\n");
			}
		}
	}
	return (int)key;
}

//Enter�������Ă����ʂ���V���܂�
void Renew() {//Enter�������Ɖ�ʂ��X�V���܂�
	int c;
	printf("enter�������Ǝ��ɐi�݂܂�");
	if ((c = getchar()) == '\n') {}
	else { while (getchar() != '\n'); }
	system("cls");

}

//Enter����������i�݂܂�
void Pause() {//Enter�������܂Ő�ɐi�݂܂���
	int c;
	printf("enter�������Ǝ��ɐi�݂܂�");
	if ((c = getchar()) == '\n') {}
	else { while (getchar() != '\n'); }
}

//�v���C���[�̎�Ԃ������Ă���܂�
void Player(int player_id) {
	if (player_id == 0) {printf("player1�̎�Ԃł��B\n");}
	else if(player_id == 1){printf("player2�̎�Ԃł��B\n");}
}

//����̎�Ԃ��Q�Ƃ��܂�
int Enemy(int player_id) {
	if (player_id == 1) {
		return 0;
	}
	else if (player_id == 0) {
		return 1;
    }
    else { printf("error!\n"); return 10; }

}
