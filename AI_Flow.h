#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#include"Status.h"
#include"Checker.h"
#include"System.h"
#include"Option.h"
/*
�C���f���g�������Ăǂ̂悤�Ȋ֐��ō\������Ă��邩�����Ă��܂�
�R�����g�A�E�g�œ����֐���\�L���Ă���ꍇ������܂�
*/


/*main���[�v��*/
void Ramdom_Set_Target(int);

void AI_Get_Piece(int);
    void AI_Destroy_Motif(int);//��̔j��
//�ł��ǂ����T���܂�
void Select_Best_Uct(int);

    //�m�[�h���쐬���܂�
    int Create_Node(int);
        //���؂�ǉ����Ă����܂�
        void Add_Child(NODE *, int, int, int, int, int, int);
            //�w�肳�ꂽ���l�ɑΉ������^�C�v��Ԃ��܂�
            int Set_NumberType(int );
    //����ƔՖʂ��ׂĂ̎��ۑ����܂�
    void Backup_All(int);
        //�{�[�h��̋�̕ۑ�
        void Backup_Board();
        //�v���C���[�莝���̕ۑ�
        void Backup_PlayerHand(int);

    //UCB�Ŏ��I�э~��Ă���
    int Search_Uct(int, int);//��
        //���؂̃m�[�h�ɔz�u��������Ăяo���܂�
        void Call_ChildHand(CHILD*);
        //AI���Ŏ��s����p
        int AI_Move(int);
        int AI_Check_Put_Piece(int, int, int, int);
        //�v���C�A�E�g
        int Playout(int);//��
            //�v���C���[���s�����̑S�񋓂��s��,���肠�������Ԃ��܂�
            int Kouho_List(int);
                //�����\���̂ɒl������֐��ł�
                void KouhoList_Set(int, int, int, int, int, int, int);
            //���Ɏ���Z�b�g���܂�
            void Kouho_MoveSet(int);
            //AI_Move�i�j�G
            //��₩�琔�l�����炵�܂�
            void KouhoList_Delete(int,int);
            //������
            int Count_Score(int);
        //Search_Uct(int, int);

    //�ۑ���������ƔՖʂ��ׂĂ̎���Ăяo���܂�
    void Call_All(int);
    //�ۑ������Ֆʂ̋�̌Ăяo��
    void Call_Board();
    //�v���C���[�莝���̌Ăяo��
    void Call_PlayerHand(int);

    //�ł��ǂ��������move�̍\���̂Ɋi�[���܂�
    void Best_Move_Set(NODE*, int);

//�����e�J�����p
int Move(int player_id);
    //���u�����Ƃ��A���ۂɐ��l���ړ�������֐�
    void Move_Num(int, int, int, int);
    
    //�ጎ�Ԃ���낤�Ƃ��Ă���G���A�ŏo���邩�ǂ�����I�肵�܂�
    int Check_BeautiesSeasonMotif_Flag(int);
    
    //AI�̖�̍쐬
    void AI_Make_Motif(int player_id);
        //������ۂ̐��l�̈ړ��Ȃǂ��܂Ƃ߂��֐�
        void MoveNum_Motif(int, int, int, int);
            //��̖�̌��ʁ@
            void AI_Snow_Effect(int);
            //���̖�̌��� 
            void AI_Moonlight_Effect(int, int);
            //�Ԃ̖�̌���
            void AI_Flower_Effect(int);
                //void AI_Destroy_Motif(int);//��̔j��
    
    //�ጎ�Ԃ�AI���쐬
    void AI_Make_BeautiesSeasonMotif(int);
        //�ጎ�ԍ쐬�̌���
        void AI_BeautiesSeasonMotif_Effect(int);


//�\���̂̏������������s���Ă��邩������
void Set_kifu(int);

