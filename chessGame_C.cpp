// chess_game_c.cpp : ���̃t�@�C���ɂ� 'main' �֐����܂܂�Ă��܂��B�v���O�������s�̊J�n�ƏI���������ōs���܂��B
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define sizeH 8 //�c�T�C�Y
#define sizeW 8 //���T�C�Y
#define dim 2 //������

//�Ֆʂ̏o��
void output_board(char board[sizeH][sizeW], char subBoard[sizeH][sizeW]) {
    putchar('\n');
    printf("  0 1 2 3 4 5 6 7 |   0 1 2 3 4 5 6 7\n");

    for (int i = 0; i < sizeH; i++) {
        printf("%d ", i);

        for (int j = 0; j < sizeW; j++) {
            printf("%c ", board[i][j]);
        }

        printf("| %d ", i);

        for (int t = 0; t < sizeW; t++) {
            printf("%c ", subBoard[i][t]);
        }

        putchar('\n');
    }

    printf("  <main board>    |    <sub board>\n");
}

//�~�Q����
void player_surrender() {
    printf("�~�Q����\n");
    exit(0);
}

//�ړ��\�ȍ��W�� : ��̎�ށA���݂̋�̍��W�A�ړ���̋�̍��W
int canMove_piece(char piece, int nowCoord[dim], int nextCoord[dim], char subBoard[sizeH][sizeW]) {
    int dirX = 0;
    int dirY = 0;
    int i = 0;
    int j = 0;

    //��̎�� : pawn
    if (piece == 'p') {
        //����
        //printf("pawn\n");
        if (subBoard[nowCoord[0]][nowCoord[1]] == 'a') {
            //�O�����i�̂�
            if (nowCoord[0] - 1 == nextCoord[0] && nowCoord[1] == nextCoord[1]) {
                //�ړ��ꏊ�ɋ���邩
                //printf("pawn\n");
                if (subBoard[nextCoord[0]][nextCoord[1]] == '*') {
                    return 1; //�ړ��\
                }
                else {
                    //printf("ill\n");
                    return 0; //�ړ��s�\
                }
            }
            //�΂߈ړ� : ����̋����ꍇ
            else if ((nowCoord[0] - 1 == nextCoord[0] && nowCoord[1] - 1 == nextCoord[1]) || (nowCoord[0] - 1 == nextCoord[0] && nowCoord[1] + 1 == nextCoord[1])) {
                //
                if (subBoard[nextCoord[0]][nextCoord[1]] == 'e') {
                    return 1;
                }
                else {
                    return 0;
                }

            }
            //����ȊO
            else {
                return 0; //�ړ��s�\
            }
        }

        //�G
        else {
            if (nowCoord[0] + 1 == nextCoord[0] && nowCoord[1] == nextCoord[1]) {
                //�ړ��ꏊ�ɋ���邩
                if (subBoard[nextCoord[0]][nextCoord[1]] == '*') {
                    return 1; //�ړ��\
                }
                else {
                    return 0; //�ړ��s�\
                }
            }
            //�΂߈ړ� : ����̋����ꍇ
            else if ((nowCoord[0] + 1 == nextCoord[0] && nowCoord[1] - 1 == nextCoord[1]) || (nowCoord[0] + 1 == nextCoord[0] && nowCoord[1] + 1 == nextCoord[1])) {
                //
                if (subBoard[nextCoord[0]][nextCoord[1]] == 'a') {
                    return 1;
                }
                else {
                    return 0;
                }
            }
            else {
                return 0; //�ړ��s�\
            }
        }

    }

    //��̎�� : knight
    else if (piece == 'k') {
        if (nowCoord[0] - 2 == nextCoord[0] && nowCoord[1] + 1 == nextCoord[1]) {
            return 1; //�ړ��\
        }
        else if (nowCoord[0] - 2 == nextCoord[0] && nowCoord[1] - 1 == nextCoord[1]) {
            return 1; //�ړ��\
        }
        else if (nowCoord[0] + 2 == nextCoord[0] && nowCoord[1] + 1 == nextCoord[1]) {
            return 1; //�ړ��\
        }
        else if (nowCoord[0] + 2 == nextCoord[0] && nowCoord[1] - 1 == nextCoord[1]) {
            return 1; //�ړ��\
        }
        else if (nowCoord[0] + 1 == nextCoord[0] && nowCoord[1] - 2 == nextCoord[1]) {
            return 1; //�ړ��\
        }
        else if (nowCoord[0] - 1 == nextCoord[0] && nowCoord[1] - 2 == nextCoord[1]) {
            return 1; //�ړ��\
        }
        else if (nowCoord[0] + 1 == nextCoord[0] && nowCoord[1] + 2 == nextCoord[1]) {
            return 1; //�ړ��\
        }
        else if (nowCoord[0] - 1 == nextCoord[0] && nowCoord[1] + 2 == nextCoord[1]) {
            return 1; //�ړ��\
        }
        else {
            return 0; //�ړ��s�\
        }
    }

    //��̎�� : bishop
    else if (piece == 'b') {
        //�΂߂Ɉړ����Ă���
        if (abs(nowCoord[0] - nextCoord[0]) == abs(nowCoord[1] - nextCoord[1])) {
            //�ړ��Ԃɋ�Ȃ���
            dirY = nowCoord[0] - nextCoord[0]; // + : ��Ɉړ�, - : ���Ɉړ�
            dirX = nowCoord[1] - nextCoord[1]; // + : ���Ɉړ�, - : �E�Ɉړ�

            //�ړ���1�}�X�̂�
            if (abs(dirY) <= 1 && abs(dirX) <= 1) {
                return 1; //�ړ��\
            }

            //����Ɉړ�
            if (dirX > 0 && dirY > 0) {
                //printf("move : bishop\n");
                i = nowCoord[0] - 1;
                j = nowCoord[1] - 1;

                while (i > nextCoord[0] && j > nextCoord[1]) {
                    //��������ꍇ
                    if (subBoard[i][j] == 'a' || subBoard[i][j] == 'e') {
                        return 0; //�ړ��s�\
                    }
                    i--;
                    j--;
                }

                return 1; //�ړ��\
            }

            //�E��Ɉړ�
            if (dirX < 0 && dirY > 0) {
                i = nowCoord[0] - 1;
                j = nowCoord[1] + 1;

                while (i > nextCoord[0] && j < nextCoord[1]) {
                    //��������ꍇ
                    if (subBoard[i][j] == 'a' || subBoard[i][j] == 'e') {
                        return 0; //�ړ��s�\
                    }
                    i--;
                    j++;
                }

                return 1; //�ړ��\
            }

            //�����Ɉړ�
            if (dirX > 0 && dirY < 0) {
                i = nowCoord[0] + 1;
                j = nowCoord[1] - 1;

                while (i < nextCoord[0] && j > nextCoord[1]) {
                    //��������ꍇ
                    if (subBoard[i][j] == 'a' || subBoard[i][j] == 'e') {
                        return 0; //�ړ��s�\
                    }
                    i++;
                    j--;
                }

                return 1; //�ړ��\
            }

            //�E���Ɉړ�
            if (dirX < 0 && dirY < 0) {
                i = nowCoord[0] + 1;
                j = nowCoord[1] + 1;

                while (i < nextCoord[0] && j < nextCoord[1]) {
                    //��������ꍇ
                    if (subBoard[i][j] == 'a' || subBoard[i][j] == 'e') {
                        return 0; //�ړ��s�\
                    }
                    i++;
                    j++;
                }

                return 1; //�ړ��\
            }

            //��O
            else {
                printf("�ړ�����s��\n");
                exit(0);
            }
        }
        else {
            return 0; //�ړ��s�\
        }
    }

    //��̎�� : rook
    else if (piece == 'r') {
        //�c�������Ɉړ����Ă��邩
        if (nowCoord[0] == nextCoord[0] || nowCoord[1] == nextCoord[1]) {
            //�ړ��Ԃɋ�Ȃ���
            dirY = nowCoord[0] - nextCoord[0];
            dirX = nowCoord[1] - nextCoord[1];

            //�ړ���1�}�X�̂�
            if (abs(dirY) <= 1 && abs(dirX) <= 1) {
                //printf("�ړ����P�}�X\n");
                return 1; //�ړ��\
            }

            //�E�Ɉړ�
            if (dirX < 0) {
                //printf("�E�Ɉړ�\n");
                i = nowCoord[0];
                j = nowCoord[1] + 1;

                while (j < nextCoord[1]) {
                    //�ړ��Ԃɋ���邩
                    if (subBoard[i][j] == 'a' || subBoard[i][j] == 'e') {
                        return 0; //�ړ��s�\
                    }

                    j++;
                }

                return 1; //�ړ��\
            }

            //���Ɉړ�
            else if (dirX > 0) {
                i = nowCoord[0];
                j = nowCoord[1] - 1;

                while (j > nextCoord[1]) {
                    //�ړ��Ԃɋ���邩
                    if (subBoard[i][j] == 'a' || subBoard[i][j] == 'e') {
                        return 0; //�ړ��s�\
                    }

                    j--;
                }

                return 1; //�ړ��\
            }

            //��Ɉړ�
            else if (dirY > 0) {
                //printf("��Ɉړ�\n");
                i = nowCoord[0] - 1;
                j = nowCoord[1];

                while (i > nextCoord[0]) {
                    //�ړ��Ԃɋ���邩
                    if (subBoard[i][j] == 'a' || subBoard[i][j] == 'e') {
                        return 0; //�ړ��s�\
                    }

                    i--;
                }

                return 1; //�ړ��\
            }

            //���Ɉړ�
            else if (dirY < 0) {
                i = nowCoord[0] + 1;
                j = nowCoord[1];

                while (i < nextCoord[0]) {
                    //�ړ��Ԃɋ���邩
                    if (subBoard[i][j] == 'a' || subBoard[i][j] == 'e') {
                        return 0; //�ړ��s�\
                    }

                    i++;
                }

                return 1; //�ړ��\
            }

            //��O
            else {
                printf("�ړ�����s��\n");
                exit(0);
            }
        }
        else {
            return 0; //�ړ��s�\
        }
    }

    //��̎�� : queen
    else if (piece == 'Q') {
        //rook
        //�c�������Ɉړ����Ă��邩
        if (nowCoord[0] == nextCoord[0] || nowCoord[1] == nextCoord[1]) {
            //�ړ��Ԃɋ�Ȃ���
            dirY = nowCoord[0] - nextCoord[0];
            dirX = nowCoord[1] - nextCoord[1];

            //�ړ���1�}�X�̂�
            if (abs(dirY) <= 1 && abs(dirX) <= 1) {
                //printf("�ړ����P�}�X\n");
                return 1; //�ړ��\
            }

            //�E�Ɉړ�
            if (dirX < 0) {
                //printf("�E�Ɉړ�\n");
                i = nowCoord[0];
                j = nowCoord[1] + 1;

                while (j < nextCoord[1]) {
                    //�ړ��Ԃɋ���邩
                    if (subBoard[i][j] == 'a' || subBoard[i][j] == 'e') {
                        return 0; //�ړ��s�\
                    }

                    j++;
                }

                return 1; //�ړ��\
            }

            //���Ɉړ�
            else if (dirX > 0) {
                i = nowCoord[0];
                j = nowCoord[1] - 1;

                while (j > nextCoord[1]) {
                    //�ړ��Ԃɋ���邩
                    if (subBoard[i][j] == 'a' || subBoard[i][j] == 'e') {
                        return 0; //�ړ��s�\
                    }

                    j--;
                }

                return 1; //�ړ��\
            }

            //��Ɉړ�
            else if (dirY > 0) {
                //printf("��Ɉړ�\n");
                i = nowCoord[0] - 1;
                j = nowCoord[1];

                while (i > nextCoord[0]) {
                    //�ړ��Ԃɋ���邩
                    if (subBoard[i][j] == 'a' || subBoard[i][j] == 'e') {
                        return 0; //�ړ��s�\
                    }

                    i--;
                }

                return 1; //�ړ��\
            }

            //���Ɉړ�
            else if (dirY < 0) {
                i = nowCoord[0] + 1;
                j = nowCoord[1];

                while (i < nextCoord[0]) {
                    //�ړ��Ԃɋ���邩
                    if (subBoard[i][j] == 'a' || subBoard[i][j] == 'e') {
                        return 0; //�ړ��s�\
                    }

                    i++;
                }

                return 1; //�ړ��\
            }

            //��O
            else {
                printf("�ړ�����s��\n");
                exit(0);
            }
        }

        //bishop
        //�΂߂Ɉړ����Ă���
        if (abs(nowCoord[0] - nextCoord[0]) == abs(nowCoord[1] - nextCoord[1])) {
            //�ړ��Ԃɋ�Ȃ���
            dirY = nowCoord[0] - nextCoord[0]; // + : ��Ɉړ�, - : ���Ɉړ�
            dirX = nowCoord[1] - nextCoord[1]; // + : ���Ɉړ�, - : �E�Ɉړ�

            //�ړ���1�}�X�̂�
            if (abs(dirY) <= 1 && abs(dirX) <= 1) {
                return 1; //�ړ��\
            }

            //����Ɉړ�
            if (dirX > 0 && dirY > 0) {
                i = nowCoord[0] - 1;
                j = nowCoord[1] - 1;

                while (i > nextCoord[0] && j > nextCoord[1]) {
                    //��������ꍇ
                    if (subBoard[i][j] == 'a' || subBoard[i][j] == 'e') {
                        return 0; //�ړ��s�\
                    }
                    i--;
                    j--;
                }

                return 1; //�ړ��\
            }

            //�E��Ɉړ�
            if (dirX < 0 && dirY > 0) {
                i = nowCoord[0] - 1;
                j = nowCoord[1] + 1;

                while (i > nextCoord[0] && j < nextCoord[1]) {
                    //��������ꍇ
                    if (subBoard[i][j] == 'a' || subBoard[i][j] == 'e') {
                        return 0; //�ړ��s�\
                    }
                    i--;
                    j++;
                }

                return 1; //�ړ��\
            }

            //�����Ɉړ�
            if (dirX > 0 && dirY < 0) {
                i = nowCoord[0] + 1;
                j = nowCoord[1] - 1;

                while (i < nextCoord[0] && j > nextCoord[1]) {
                    //��������ꍇ
                    if (subBoard[i][j] == 'a' || subBoard[i][j] == 'e') {
                        return 0; //�ړ��s�\
                    }
                    i++;
                    j--;
                }

                return 1; //�ړ��\
            }

            //�E���Ɉړ�
            if (dirX < 0 && dirY < 0) {
                i = nowCoord[0] + 1;
                j = nowCoord[1] + 1;

                while (i < nextCoord[0] && j < nextCoord[1]) {
                    //��������ꍇ
                    if (subBoard[i][j] == 'a' || subBoard[i][j] == 'e') {
                        return 0; //�ړ��s�\
                    }
                    i++;
                    j++;
                }

                return 1; //�ړ��\
            }

            //��O
            else {
                printf("�ړ�����s��\n");
                exit(0);
            }
        }
        else {
            return 0; //�ړ��s�\
        }
    }

    //��̎�� : king
    else if (piece == 'K') {
        if (abs(nowCoord[0] - nextCoord[0]) <= 1 && abs(nowCoord[1] - nextCoord[1]) <= 1) {
            return 1; //�ړ��\
        }
        else {
            return 0; //�ړ��s�\
        }
    }

    //��O
    else {
        printf("�Q�[���I�� : canMove_piece\n");
        exit(0);
    }
}

//�Q�[���I������ : �L���O������Ă���
int isGame_finish(char board[sizeH][sizeW], char subBoard[sizeH][sizeW]) {
    int kingP = 0; //�v���C���[�̃L���O
    int kingE = 0; //�G�̃L���O
    for (int i = 0; i < sizeH; i++) {
        for (int j = 0; j < sizeW; j++) {
            //�L���O�����݂���
            if (board[i][j] == 'K') {
                //�����̃L���O
                if (subBoard[i][j] == 'a') {
                    kingP = 1;
                }
                else {
                    kingE = 1;
                }
            }

            if (kingP == 1 && kingE == 1) {
                return 0; //�Q�[���p��
            }
        }
    }

    if (kingP == 1 && kingE == 0) {
        printf("\n���Ȃ��̏���\n");
        return 1;
    }
    else if (kingP == 0 && kingE == 1) {
        printf("\n���Ȃ��̕���\n");
        return 1;
    }
    else {
        printf("\n��������\n");
        exit(0);
    }
}

//�������� : �L���O�����c���Ă��Ȃ�
int isGame_draw(char subBoard[sizeH][sizeW]) {
    int countPiece = 0;

    for (int i = 0; i < sizeH; i++) {
        for (int j = 0; j < sizeW; j++) {
            //���ȏォ�@isGame_finish�̌��ʂ��
            if (subBoard[i][j] != '*') {
                countPiece++;
            }
            else {
                continue;
            }

            //���ȏ�
            if (countPiece > 2) {
                return 0; //�Q�[���p��
            }
        }
    }

    //���ȉ�
    printf("��������\n");
    return 1; //�����킯
}

int main()
{
    srand((unsigned int)time(NULL));

    //�Ղ̍쐬
    char board[sizeH][sizeW];
    char subBoard[sizeH][sizeW]; //��̓G�����̔���p

    for (int i = 0; i < sizeH; i++) {
        for (int j = 0; j < sizeW; j++) {
            if ((i + j) % 2 == 0) {
                board[i][j] = '*';
            }
            else {
                board[i][j] = '+';
            }
        }
    }

    //output_board(board);

    //subBoard�̍쐬
    int count = 0;

    for (int i = 0; i < sizeH; i++) {
        for (int j = 0; j < sizeW; j++) {
            if (i == 0 || i == 1) {
                subBoard[i][j] = 'e'; //�G
            }
            else if (i == 6 || i == 7) {
                subBoard[i][j] = 'a'; //����
            }
            else {
                subBoard[i][j] = '*';
            }
        }
        count++;
    }

    //output_board(subBoard);

    //��̔z�u : pawn
    for (int i = 1; i < sizeH; i += 5) {
        for (int j = 0; j < sizeW; j++) {
            board[i][j] = 'p';
        }
    }

    //output_board(board);

    //��̔z�u : knight
    board[0][1] = 'k';
    board[0][6] = 'k';
    board[7][1] = 'k';
    board[7][6] = 'k';

    //��̔z�u : bishop
    board[0][2] = 'b';
    board[0][5] = 'b';
    board[7][2] = 'b';
    board[7][5] = 'b';

    //��̔z�u : rook
    board[0][0] = 'r';
    board[0][7] = 'r';
    board[7][0] = 'r';
    board[7][7] = 'r';

    //��̔z�u : queen
    board[0][3] = 'Q';
    board[7][3] = 'Q';

    //��̔z�u : king
    board[0][4] = 'K';
    board[7][4] = 'K';

    output_board(board, subBoard);

    //��̈ړ�
    int whoseTurn = 0; //�^�[���̐؂�ւ�
    int checkMate = 0; //�Q�[���I���t���O
    int checkDraw = 0; //���������t���O
    int wherePiece[2] = { -1 }; //�ړ�����������̍��W
    int whereMove[2] = { -1 }; //�ړ���̋�̍��W
    int moveFlag = 0; //�ړ��\�t���O
    char temp; //��̍��W�̈ꎞ�ۑ��p
    int exitFlag = 0; //�������[�v���p

    //while : �Q�[���̌p��
    //���͂������ړ�������@�G�������݂�
    //���͂��������ړ��ɂȂ邩����
    //�������ꍇ�A�ړ��ƃ^�[���̌��@�����łȂ��ꍇ�A���͂̂�蒼��
    //�ύX�ꏊ : borad, subBorad
    ///*

    printf("\n<���[��>\n");
    printf("1 : �����̂ݓ��͂��Ă�������\n");
    printf("2 : �����̋�̉E�Ֆʂ�'a'�ł�\n");
    printf("3 : �~�Q�������ꍇ��(100 100)�����\n");
    printf("4 : ��̑I���ɖ߂�ꍇ��(-1 -1)�����\n");

    while (checkMate == 0 && checkDraw == 0) {
        //���Ȃ��̃^�[��
        if (whoseTurn % 2 == 0) {

            //���͑҂� : �ړ�����������̍��W
            while (1) {
                //���상�b�Z�[�W : �ړ�����������̍��W����͂��Ă�������
                printf("\n�ړ�����������̍��W(�c ��)����͂��Ă������� < ���オ(0 0)�A�E����(7 7)�ł� >\n");
                printf("�� < p : pawn, k : knight, b : bishop, r : rook, Q : queen, K : king >\n");
                exitFlag++;

                if (exitFlag > 5) {
                    printf("���̓~�X������܂���\n");
                    exit(0);
                }

                //�ړ�����������̍��W���󂯎��
                scanf_s("%d %d", &wherePiece[0], &wherePiece[1]);
                //printf("���� : %d %d\n", wherePiece[0], wherePiece[1]);

                //�~�Q����
                if (wherePiece[0] == 100 && wherePiece[1] == 100) {
                    player_surrender();
                }

                //���������W�����͂���Ă���
                if (wherePiece[0] >= 0 && wherePiece[0] < sizeH && wherePiece[1] >= 0 && wherePiece[1] < sizeW) {
                    //�ړ���������������ł���
                    if (subBoard[wherePiece[0]][wherePiece[1]] == 'a') {
                        break;
                    }

                    //�����łȂ�
                    else {
                        printf("���Ȃ��̋�ł͂���܂���\n");
                        continue;
                    }
                }

                //��@�ȍ��W�����͂���Ă���
                else {
                    printf("���������W�ł͂���܂���\n");
                    continue;
                }
            }

            exitFlag = 0;

            //���͑҂� : �ړ���̍��W
            while (1) {
                //���상�b�Z�[�W
                printf("\n�ړ���̋�̍��W����͂��Ă������� : %c\n", board[wherePiece[0]][wherePiece[1]]);
                exitFlag++;

                //�������[�v���p
                if (exitFlag > 5) {
                    printf("���̓~�X������܂���\n");
                    exit(0);
                }

                //�ړ���̋�̍��W���󂯎��
                scanf_s("%d %d", &whereMove[0], &whereMove[1]);
                //printf("���� : %d %d\n", whereMove[0], whereMove[1]);

                //�~�Q����
                if (whereMove[0] == 100 && whereMove[1] == 100) {
                    player_surrender();
                }

                //�O��̑���ɖ߂�
                if (whereMove[0] == -1 && whereMove[1] == -1) {
                    printf("��̑I���ɖ߂�܂�\n");
                    break;
                }

                //���������W�����͂���Ă���
                if (whereMove[0] >= 0 && whereMove[0] < sizeH && whereMove[1] >= 0 && whereMove[1] < sizeW) {
                    //�ړ���ɖ��������Ȃ�
                    if (subBoard[whereMove[0]][whereMove[1]] != 'a') {
                        //�ړ��\�ȍ��W�ł���
                        moveFlag = canMove_piece(board[wherePiece[0]][wherePiece[1]], wherePiece, whereMove, subBoard);
                        if (moveFlag == 1) {
                            //printf("moveFlag == 1\n");

                            //�ړ����� : board, subBoard�̏����X�V
                            temp = board[wherePiece[0]][wherePiece[1]]; //�ړ��O�̏���ۑ�

                            //�ړ��O�̍��W����ɂ���
                            if ((wherePiece[0] + wherePiece[1]) % 2 == 0) {
                                board[wherePiece[0]][wherePiece[1]] = '*';
                            }
                            else {
                                board[wherePiece[0]][wherePiece[1]] = '+';
                            }

                            board[whereMove[0]][whereMove[1]] = temp; //����ړ�

                            //subBoard�̍X�V
                            temp = subBoard[wherePiece[0]][wherePiece[1]]; //�ړ��O�̏���ۑ�
                            subBoard[wherePiece[0]][wherePiece[1]] = '*'; //�ړ��O�̍��W����ɂ���
                            subBoard[whereMove[0]][whereMove[1]] = temp; //����ړ�

                            printf("\n���Ȃ��̃^�[�����I�����܂���\n");
                            output_board(board, subBoard);
                            whoseTurn++;

                            break;
                        }

                        //��������̓����ł͂Ȃ� or �ړ��Ԃɖ���������
                        else {
                            printf("��������̓����ł͂���܂���B�������́A�ړ��Ԃɋ����܂�\n");
                            continue;
                        }
                    }

                    //�ړ���ɖ���������
                    else {
                        printf("�ړ���ɖ��������܂�\n");
                        continue;
                    }
                }

                //��@�ȍ��W�����͂���Ă���
                else {
                    printf("���������W�ł͂���܂���\n");
                    continue;
                }
            }
        }
        //���Ȃ��̃^�[���I��

        //����̃^�[��
        else {
            //�^�[���̐؂�ւ�
            whoseTurn++;

            //�����_���ňړ�
            while (1) {
                //�����_���ȍ��W���擾
                wherePiece[0] = rand() % 8; //�O�`�V
                wherePiece[1] = rand() % 8;

                //���g�̋
                if (subBoard[wherePiece[0]][wherePiece[1]] == 'e') {
                    whereMove[0] = rand() % 8;
                    whereMove[1] = rand() % 8;

                    //���g�̋�Əd�Ȃ邩
                    if (subBoard[whereMove[0]][whereMove[1]] != 'e') {
                        //�ړ��\��
                        moveFlag = canMove_piece(board[wherePiece[0]][wherePiece[1]], wherePiece, whereMove, subBoard);

                        if (moveFlag == 1) {
                            //printf("moveFlag == 1\n");

                            //�ړ����� : board, subBoard�̏����X�V
                            temp = board[wherePiece[0]][wherePiece[1]]; //�ړ��O�̏���ۑ�

                            //�ړ��O�̍��W����ɂ���
                            if ((wherePiece[0] + wherePiece[1]) % 2 == 0) {
                                board[wherePiece[0]][wherePiece[1]] = '*';
                            }
                            else {
                                board[wherePiece[0]][wherePiece[1]] = '+';
                            }

                            board[whereMove[0]][whereMove[1]] = temp; //����ړ�

                            //subBoard�̍X�V
                            temp = subBoard[wherePiece[0]][wherePiece[1]]; //�ړ��O�̏���ۑ�
                            subBoard[wherePiece[0]][wherePiece[1]] = '*'; //�ړ��O�̍��W����ɂ���
                            subBoard[whereMove[0]][whereMove[1]] = temp; //����ړ�

                            printf("\n����̃^�[�����I�����܂���\n");
                            output_board(board, subBoard);

                            break;
                        }

                        //��������̓����ł͂Ȃ� or �ړ��Ԃɖ���������
                        else {
                            //printf("��������̓����ł͂���܂���B�������́A�ړ��Ԃɖ��������܂�\n");
                            continue;
                        }
                    }

                    //���g�̋�Əd�Ȃ�
                    else {
                        continue;
                    }
                }

                //���g�̋�ł͂Ȃ�
                else {
                    continue;
                }
            }

            //�Q�[���I�������̊m�F
            checkMate = isGame_finish(board, subBoard);

            //���������̊m�F
            checkDraw = isGame_draw(subBoard);

        }

        //������
        wherePiece[0] = -1;
        wherePiece[1] = -1;
        whereMove[0] = -1;
        whereMove[1] = -1;
        moveFlag = 0;
        exitFlag = 0;

    }
    //*/

    return 0;
}

// �v���O�����̎��s: Ctrl + F5 �܂��� [�f�o�b�O] > [�f�o�b�O�Ȃ��ŊJ�n] ���j���[
// �v���O�����̃f�o�b�O: F5 �܂��� [�f�o�b�O] > [�f�o�b�O�̊J�n] ���j���[

// ��Ƃ��J�n���邽�߂̃q���g: 
//    1. �\�����[�V���� �G�N�X�v���[���[ �E�B���h�E���g�p���ăt�@�C����ǉ�/�Ǘ����܂� 
//   2. �`�[�� �G�N�X�v���[���[ �E�B���h�E���g�p���ă\�[�X�Ǘ��ɐڑ����܂�
//   3. �o�̓E�B���h�E���g�p���āA�r���h�o�͂Ƃ��̑��̃��b�Z�[�W��\�����܂�
//   4. �G���[�ꗗ�E�B���h�E���g�p���ăG���[��\�����܂�
//   5. [�v���W�F�N�g] > [�V�������ڂ̒ǉ�] �ƈړ����ĐV�����R�[�h �t�@�C�����쐬���邩�A[�v���W�F�N�g] > [�����̍��ڂ̒ǉ�] �ƈړ����Ċ����̃R�[�h �t�@�C�����v���W�F�N�g�ɒǉ����܂�
//   6. ��قǂ��̃v���W�F�N�g���ĂъJ���ꍇ�A[�t�@�C��] > [�J��] > [�v���W�F�N�g] �ƈړ����� .sln �t�@�C����I�����܂�