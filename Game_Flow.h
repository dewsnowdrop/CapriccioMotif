#pragma once
#include<stdio.h>
/*
�Q�[���̗����\������t�@�C���ł�
�C���f���g�������闝�R�Ƃ��Ĉ�̊֐��ɉ������Ă���v���O���������Ă��邱�Ƃ������Ă���
�v���O�����̗�����v���g�^�C�v�錾���g���č\�z���Ă���
*/
void Draw_Board();      //��ʕ\��
void AcquirePiece(int);	//��̊l��
  void Destroy_Motif(int);	//��̔j��
void Put_Piece(int);		//��̐ݒu
void Create_Motif(int);//��̍쐬
  void Make_Motif(int, int, int, int);	//��̑I��  
    void Motif_Effect(int, int, int);	//��̌��ʂ̑I��  
      void Snow_Effect(int);			//��̖�̌���
	  void Moonlight_Effect(int, int);	//���̖�̌���
	  void Flower_Effect(int);			//�Ԃ̖�̌���
void Create_BeautiesSeasonMotif(int);	//�ጎ�Ԃ̍쐬
  void Make_BeautiesSeasonMotif(int, int);//�ጎ�Ԃ̏���
    void BeautiesSeasonMotif_Effect(int);//�ጎ�Ԃ̌���
void Get_Card(int,int);					//�J�[�h�擾�̏���
  void Select_Card(int, int, int);		//�J�[�h�̑I��
    int Snow_CardEffect(int,int);		  //��̃J�[�h�̌���
    int Moonlight_CardEffect(int, int);	//���̃J�[�h�̌���
    int Flower_CardEffect(int, int);		//�Ԃ̃J�[�h�̌���
int Judge(int);							//���s����

/*�������̃V�X�e�����X�g�F
�G���[���b�Z�[�W�̒ǉ�
AI
PlayerSelect
���ݍs���Ă����ƁFAI�̍쐬�A�R�[�h�̉��P�i���l�̓��͂�ς����Ɓj

*/