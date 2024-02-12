// chess_game_c.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define sizeH 8 //縦サイズ
#define sizeW 8 //横サイズ
#define dim 2 //次元数

//盤面の出力
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

//降参する
void player_surrender() {
    printf("降参した\n");
    exit(0);
}

//移動可能な座標か : 駒の種類、現在の駒の座標、移動後の駒の座標
int canMove_piece(char piece, int nowCoord[dim], int nextCoord[dim], char subBoard[sizeH][sizeW]) {
    int dirX = 0;
    int dirY = 0;
    int i = 0;
    int j = 0;

    //駒の種類 : pawn
    if (piece == 'p') {
        //味方
        //printf("pawn\n");
        if (subBoard[nowCoord[0]][nowCoord[1]] == 'a') {
            //前方直進のみ
            if (nowCoord[0] - 1 == nextCoord[0] && nowCoord[1] == nextCoord[1]) {
                //移動場所に駒があるか
                //printf("pawn\n");
                if (subBoard[nextCoord[0]][nextCoord[1]] == '*') {
                    return 1; //移動可能
                }
                else {
                    //printf("ill\n");
                    return 0; //移動不可能
                }
            }
            //斜め移動 : 相手の駒がある場合
            else if ((nowCoord[0] - 1 == nextCoord[0] && nowCoord[1] - 1 == nextCoord[1]) || (nowCoord[0] - 1 == nextCoord[0] && nowCoord[1] + 1 == nextCoord[1])) {
                //
                if (subBoard[nextCoord[0]][nextCoord[1]] == 'e') {
                    return 1;
                }
                else {
                    return 0;
                }

            }
            //それ以外
            else {
                return 0; //移動不可能
            }
        }

        //敵
        else {
            if (nowCoord[0] + 1 == nextCoord[0] && nowCoord[1] == nextCoord[1]) {
                //移動場所に駒があるか
                if (subBoard[nextCoord[0]][nextCoord[1]] == '*') {
                    return 1; //移動可能
                }
                else {
                    return 0; //移動不可能
                }
            }
            //斜め移動 : 相手の駒がある場合
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
                return 0; //移動不可能
            }
        }

    }

    //駒の種類 : knight
    else if (piece == 'k') {
        if (nowCoord[0] - 2 == nextCoord[0] && nowCoord[1] + 1 == nextCoord[1]) {
            return 1; //移動可能
        }
        else if (nowCoord[0] - 2 == nextCoord[0] && nowCoord[1] - 1 == nextCoord[1]) {
            return 1; //移動可能
        }
        else if (nowCoord[0] + 2 == nextCoord[0] && nowCoord[1] + 1 == nextCoord[1]) {
            return 1; //移動可能
        }
        else if (nowCoord[0] + 2 == nextCoord[0] && nowCoord[1] - 1 == nextCoord[1]) {
            return 1; //移動可能
        }
        else if (nowCoord[0] + 1 == nextCoord[0] && nowCoord[1] - 2 == nextCoord[1]) {
            return 1; //移動可能
        }
        else if (nowCoord[0] - 1 == nextCoord[0] && nowCoord[1] - 2 == nextCoord[1]) {
            return 1; //移動可能
        }
        else if (nowCoord[0] + 1 == nextCoord[0] && nowCoord[1] + 2 == nextCoord[1]) {
            return 1; //移動可能
        }
        else if (nowCoord[0] - 1 == nextCoord[0] && nowCoord[1] + 2 == nextCoord[1]) {
            return 1; //移動可能
        }
        else {
            return 0; //移動不可能
        }
    }

    //駒の種類 : bishop
    else if (piece == 'b') {
        //斜めに移動している
        if (abs(nowCoord[0] - nextCoord[0]) == abs(nowCoord[1] - nextCoord[1])) {
            //移動間に駒がないか
            dirY = nowCoord[0] - nextCoord[0]; // + : 上に移動, - : 下に移動
            dirX = nowCoord[1] - nextCoord[1]; // + : 左に移動, - : 右に移動

            //移動が1マスのみ
            if (abs(dirY) <= 1 && abs(dirX) <= 1) {
                return 1; //移動可能
            }

            //左上に移動
            if (dirX > 0 && dirY > 0) {
                //printf("move : bishop\n");
                i = nowCoord[0] - 1;
                j = nowCoord[1] - 1;

                while (i > nextCoord[0] && j > nextCoord[1]) {
                    //駒があった場合
                    if (subBoard[i][j] == 'a' || subBoard[i][j] == 'e') {
                        return 0; //移動不可能
                    }
                    i--;
                    j--;
                }

                return 1; //移動可能
            }

            //右上に移動
            if (dirX < 0 && dirY > 0) {
                i = nowCoord[0] - 1;
                j = nowCoord[1] + 1;

                while (i > nextCoord[0] && j < nextCoord[1]) {
                    //駒があった場合
                    if (subBoard[i][j] == 'a' || subBoard[i][j] == 'e') {
                        return 0; //移動不可能
                    }
                    i--;
                    j++;
                }

                return 1; //移動可能
            }

            //左下に移動
            if (dirX > 0 && dirY < 0) {
                i = nowCoord[0] + 1;
                j = nowCoord[1] - 1;

                while (i < nextCoord[0] && j > nextCoord[1]) {
                    //駒があった場合
                    if (subBoard[i][j] == 'a' || subBoard[i][j] == 'e') {
                        return 0; //移動不可能
                    }
                    i++;
                    j--;
                }

                return 1; //移動可能
            }

            //右下に移動
            if (dirX < 0 && dirY < 0) {
                i = nowCoord[0] + 1;
                j = nowCoord[1] + 1;

                while (i < nextCoord[0] && j < nextCoord[1]) {
                    //駒があった場合
                    if (subBoard[i][j] == 'a' || subBoard[i][j] == 'e') {
                        return 0; //移動不可能
                    }
                    i++;
                    j++;
                }

                return 1; //移動可能
            }

            //例外
            else {
                printf("移動判定不可\n");
                exit(0);
            }
        }
        else {
            return 0; //移動不可能
        }
    }

    //駒の種類 : rook
    else if (piece == 'r') {
        //縦横直線に移動しているか
        if (nowCoord[0] == nextCoord[0] || nowCoord[1] == nextCoord[1]) {
            //移動間に駒がないか
            dirY = nowCoord[0] - nextCoord[0];
            dirX = nowCoord[1] - nextCoord[1];

            //移動が1マスのみ
            if (abs(dirY) <= 1 && abs(dirX) <= 1) {
                //printf("移動が１マス\n");
                return 1; //移動可能
            }

            //右に移動
            if (dirX < 0) {
                //printf("右に移動\n");
                i = nowCoord[0];
                j = nowCoord[1] + 1;

                while (j < nextCoord[1]) {
                    //移動間に駒があるか
                    if (subBoard[i][j] == 'a' || subBoard[i][j] == 'e') {
                        return 0; //移動不可能
                    }

                    j++;
                }

                return 1; //移動可能
            }

            //左に移動
            else if (dirX > 0) {
                i = nowCoord[0];
                j = nowCoord[1] - 1;

                while (j > nextCoord[1]) {
                    //移動間に駒があるか
                    if (subBoard[i][j] == 'a' || subBoard[i][j] == 'e') {
                        return 0; //移動不可能
                    }

                    j--;
                }

                return 1; //移動可能
            }

            //上に移動
            else if (dirY > 0) {
                //printf("上に移動\n");
                i = nowCoord[0] - 1;
                j = nowCoord[1];

                while (i > nextCoord[0]) {
                    //移動間に駒があるか
                    if (subBoard[i][j] == 'a' || subBoard[i][j] == 'e') {
                        return 0; //移動不可能
                    }

                    i--;
                }

                return 1; //移動可能
            }

            //下に移動
            else if (dirY < 0) {
                i = nowCoord[0] + 1;
                j = nowCoord[1];

                while (i < nextCoord[0]) {
                    //移動間に駒があるか
                    if (subBoard[i][j] == 'a' || subBoard[i][j] == 'e') {
                        return 0; //移動不可能
                    }

                    i++;
                }

                return 1; //移動可能
            }

            //例外
            else {
                printf("移動判定不可\n");
                exit(0);
            }
        }
        else {
            return 0; //移動不可能
        }
    }

    //駒の種類 : queen
    else if (piece == 'Q') {
        //rook
        //縦横直線に移動しているか
        if (nowCoord[0] == nextCoord[0] || nowCoord[1] == nextCoord[1]) {
            //移動間に駒がないか
            dirY = nowCoord[0] - nextCoord[0];
            dirX = nowCoord[1] - nextCoord[1];

            //移動が1マスのみ
            if (abs(dirY) <= 1 && abs(dirX) <= 1) {
                //printf("移動が１マス\n");
                return 1; //移動可能
            }

            //右に移動
            if (dirX < 0) {
                //printf("右に移動\n");
                i = nowCoord[0];
                j = nowCoord[1] + 1;

                while (j < nextCoord[1]) {
                    //移動間に駒があるか
                    if (subBoard[i][j] == 'a' || subBoard[i][j] == 'e') {
                        return 0; //移動不可能
                    }

                    j++;
                }

                return 1; //移動可能
            }

            //左に移動
            else if (dirX > 0) {
                i = nowCoord[0];
                j = nowCoord[1] - 1;

                while (j > nextCoord[1]) {
                    //移動間に駒があるか
                    if (subBoard[i][j] == 'a' || subBoard[i][j] == 'e') {
                        return 0; //移動不可能
                    }

                    j--;
                }

                return 1; //移動可能
            }

            //上に移動
            else if (dirY > 0) {
                //printf("上に移動\n");
                i = nowCoord[0] - 1;
                j = nowCoord[1];

                while (i > nextCoord[0]) {
                    //移動間に駒があるか
                    if (subBoard[i][j] == 'a' || subBoard[i][j] == 'e') {
                        return 0; //移動不可能
                    }

                    i--;
                }

                return 1; //移動可能
            }

            //下に移動
            else if (dirY < 0) {
                i = nowCoord[0] + 1;
                j = nowCoord[1];

                while (i < nextCoord[0]) {
                    //移動間に駒があるか
                    if (subBoard[i][j] == 'a' || subBoard[i][j] == 'e') {
                        return 0; //移動不可能
                    }

                    i++;
                }

                return 1; //移動可能
            }

            //例外
            else {
                printf("移動判定不可\n");
                exit(0);
            }
        }

        //bishop
        //斜めに移動している
        if (abs(nowCoord[0] - nextCoord[0]) == abs(nowCoord[1] - nextCoord[1])) {
            //移動間に駒がないか
            dirY = nowCoord[0] - nextCoord[0]; // + : 上に移動, - : 下に移動
            dirX = nowCoord[1] - nextCoord[1]; // + : 左に移動, - : 右に移動

            //移動が1マスのみ
            if (abs(dirY) <= 1 && abs(dirX) <= 1) {
                return 1; //移動可能
            }

            //左上に移動
            if (dirX > 0 && dirY > 0) {
                i = nowCoord[0] - 1;
                j = nowCoord[1] - 1;

                while (i > nextCoord[0] && j > nextCoord[1]) {
                    //駒があった場合
                    if (subBoard[i][j] == 'a' || subBoard[i][j] == 'e') {
                        return 0; //移動不可能
                    }
                    i--;
                    j--;
                }

                return 1; //移動可能
            }

            //右上に移動
            if (dirX < 0 && dirY > 0) {
                i = nowCoord[0] - 1;
                j = nowCoord[1] + 1;

                while (i > nextCoord[0] && j < nextCoord[1]) {
                    //駒があった場合
                    if (subBoard[i][j] == 'a' || subBoard[i][j] == 'e') {
                        return 0; //移動不可能
                    }
                    i--;
                    j++;
                }

                return 1; //移動可能
            }

            //左下に移動
            if (dirX > 0 && dirY < 0) {
                i = nowCoord[0] + 1;
                j = nowCoord[1] - 1;

                while (i < nextCoord[0] && j > nextCoord[1]) {
                    //駒があった場合
                    if (subBoard[i][j] == 'a' || subBoard[i][j] == 'e') {
                        return 0; //移動不可能
                    }
                    i++;
                    j--;
                }

                return 1; //移動可能
            }

            //右下に移動
            if (dirX < 0 && dirY < 0) {
                i = nowCoord[0] + 1;
                j = nowCoord[1] + 1;

                while (i < nextCoord[0] && j < nextCoord[1]) {
                    //駒があった場合
                    if (subBoard[i][j] == 'a' || subBoard[i][j] == 'e') {
                        return 0; //移動不可能
                    }
                    i++;
                    j++;
                }

                return 1; //移動可能
            }

            //例外
            else {
                printf("移動判定不可\n");
                exit(0);
            }
        }
        else {
            return 0; //移動不可能
        }
    }

    //駒の種類 : king
    else if (piece == 'K') {
        if (abs(nowCoord[0] - nextCoord[0]) <= 1 && abs(nowCoord[1] - nextCoord[1]) <= 1) {
            return 1; //移動可能
        }
        else {
            return 0; //移動不可能
        }
    }

    //例外
    else {
        printf("ゲーム終了 : canMove_piece\n");
        exit(0);
    }
}

//ゲーム終了条件 : キングが取られている
int isGame_finish(char board[sizeH][sizeW], char subBoard[sizeH][sizeW]) {
    int kingP = 0; //プレイヤーのキング
    int kingE = 0; //敵のキング
    for (int i = 0; i < sizeH; i++) {
        for (int j = 0; j < sizeW; j++) {
            //キングが存在する
            if (board[i][j] == 'K') {
                //味方のキング
                if (subBoard[i][j] == 'a') {
                    kingP = 1;
                }
                else {
                    kingE = 1;
                }
            }

            if (kingP == 1 && kingE == 1) {
                return 0; //ゲーム継続
            }
        }
    }

    if (kingP == 1 && kingE == 0) {
        printf("\nあなたの勝ち\n");
        return 1;
    }
    else if (kingP == 0 && kingE == 1) {
        printf("\nあなたの負け\n");
        return 1;
    }
    else {
        printf("\n引き分け\n");
        exit(0);
    }
}

//引き分け : キングしか残っていない
int isGame_draw(char subBoard[sizeH][sizeW]) {
    int countPiece = 0;

    for (int i = 0; i < sizeH; i++) {
        for (int j = 0; j < sizeW; j++) {
            //駒が二つ以上か　isGame_finishの結果より
            if (subBoard[i][j] != '*') {
                countPiece++;
            }
            else {
                continue;
            }

            //駒が二つ以上
            if (countPiece > 2) {
                return 0; //ゲーム継続
            }
        }
    }

    //駒が二つ以下
    printf("引き分け\n");
    return 1; //引きわけ
}

int main()
{
    srand((unsigned int)time(NULL));

    //盤の作成
    char board[sizeH][sizeW];
    char subBoard[sizeH][sizeW]; //駒の敵味方の判定用

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

    //subBoardの作成
    int count = 0;

    for (int i = 0; i < sizeH; i++) {
        for (int j = 0; j < sizeW; j++) {
            if (i == 0 || i == 1) {
                subBoard[i][j] = 'e'; //敵
            }
            else if (i == 6 || i == 7) {
                subBoard[i][j] = 'a'; //味方
            }
            else {
                subBoard[i][j] = '*';
            }
        }
        count++;
    }

    //output_board(subBoard);

    //駒の配置 : pawn
    for (int i = 1; i < sizeH; i += 5) {
        for (int j = 0; j < sizeW; j++) {
            board[i][j] = 'p';
        }
    }

    //output_board(board);

    //駒の配置 : knight
    board[0][1] = 'k';
    board[0][6] = 'k';
    board[7][1] = 'k';
    board[7][6] = 'k';

    //駒の配置 : bishop
    board[0][2] = 'b';
    board[0][5] = 'b';
    board[7][2] = 'b';
    board[7][5] = 'b';

    //駒の配置 : rook
    board[0][0] = 'r';
    board[0][7] = 'r';
    board[7][0] = 'r';
    board[7][7] = 'r';

    //駒の配置 : queen
    board[0][3] = 'Q';
    board[7][3] = 'Q';

    //駒の配置 : king
    board[0][4] = 'K';
    board[7][4] = 'K';

    output_board(board, subBoard);

    //駒の移動
    int whoseTurn = 0; //ターンの切り替え
    int checkMate = 0; //ゲーム終了フラグ
    int checkDraw = 0; //引き分けフラグ
    int wherePiece[2] = { -1 }; //移動させたい駒の座標
    int whereMove[2] = { -1 }; //移動後の駒の座標
    int moveFlag = 0; //移動可能フラグ
    char temp; //駒の座標の一時保存用
    int exitFlag = 0; //無限ループ回避用

    //while : ゲームの継続
    //入力から駒を移動させる　敵味方交互に
    //入力が正しい移動になるか検証
    //正しい場合、移動とターンの交代　そうでない場合、入力のやり直し
    //変更場所 : borad, subBorad
    ///*

    printf("\n<ルール>\n");
    printf("1 : 数字のみ入力してください\n");
    printf("2 : 味方の駒の右盤面の'a'です\n");
    printf("3 : 降参したい場合は(100 100)を入力\n");
    printf("4 : 駒の選択に戻る場合は(-1 -1)を入力\n");

    while (checkMate == 0 && checkDraw == 0) {
        //あなたのターン
        if (whoseTurn % 2 == 0) {

            //入力待ち : 移動させたい駒の座標
            while (1) {
                //操作メッセージ : 移動させたい駒の座標を入力してください
                printf("\n移動させたい駒の座標(縦 横)を入力してください < 左上が(0 0)、右下が(7 7)です >\n");
                printf("駒 < p : pawn, k : knight, b : bishop, r : rook, Q : queen, K : king >\n");
                exitFlag++;

                if (exitFlag > 5) {
                    printf("入力ミスがありました\n");
                    exit(0);
                }

                //移動させたい駒の座標を受け取る
                scanf_s("%d %d", &wherePiece[0], &wherePiece[1]);
                //printf("入力 : %d %d\n", wherePiece[0], wherePiece[1]);

                //降参する
                if (wherePiece[0] == 100 && wherePiece[1] == 100) {
                    player_surrender();
                }

                //正しい座標が入力されている
                if (wherePiece[0] >= 0 && wherePiece[0] < sizeH && wherePiece[1] >= 0 && wherePiece[1] < sizeW) {
                    //移動させたい駒が味方である
                    if (subBoard[wherePiece[0]][wherePiece[1]] == 'a') {
                        break;
                    }

                    //味方でない
                    else {
                        printf("あなたの駒ではありません\n");
                        continue;
                    }
                }

                //違法な座標が入力されている
                else {
                    printf("正しい座標ではありません\n");
                    continue;
                }
            }

            exitFlag = 0;

            //入力待ち : 移動先の座標
            while (1) {
                //操作メッセージ
                printf("\n移動後の駒の座標を入力してください : %c\n", board[wherePiece[0]][wherePiece[1]]);
                exitFlag++;

                //無限ループ回避用
                if (exitFlag > 5) {
                    printf("入力ミスがありました\n");
                    exit(0);
                }

                //移動後の駒の座標を受け取る
                scanf_s("%d %d", &whereMove[0], &whereMove[1]);
                //printf("入力 : %d %d\n", whereMove[0], whereMove[1]);

                //降参する
                if (whereMove[0] == 100 && whereMove[1] == 100) {
                    player_surrender();
                }

                //前回の操作に戻る
                if (whereMove[0] == -1 && whereMove[1] == -1) {
                    printf("駒の選択に戻ります\n");
                    break;
                }

                //正しい座標が入力されている
                if (whereMove[0] >= 0 && whereMove[0] < sizeH && whereMove[1] >= 0 && whereMove[1] < sizeW) {
                    //移動先に味方がいない
                    if (subBoard[whereMove[0]][whereMove[1]] != 'a') {
                        //移動可能な座標である
                        moveFlag = canMove_piece(board[wherePiece[0]][wherePiece[1]], wherePiece, whereMove, subBoard);
                        if (moveFlag == 1) {
                            //printf("moveFlag == 1\n");

                            //移動処理 : board, subBoardの情報を更新
                            temp = board[wherePiece[0]][wherePiece[1]]; //移動前の情報を保存

                            //移動前の座標を空にする
                            if ((wherePiece[0] + wherePiece[1]) % 2 == 0) {
                                board[wherePiece[0]][wherePiece[1]] = '*';
                            }
                            else {
                                board[wherePiece[0]][wherePiece[1]] = '+';
                            }

                            board[whereMove[0]][whereMove[1]] = temp; //駒を移動

                            //subBoardの更新
                            temp = subBoard[wherePiece[0]][wherePiece[1]]; //移動前の情報を保存
                            subBoard[wherePiece[0]][wherePiece[1]] = '*'; //移動前の座標を空にする
                            subBoard[whereMove[0]][whereMove[1]] = temp; //駒を移動

                            printf("\nあなたのターンが終了しました\n");
                            output_board(board, subBoard);
                            whoseTurn++;

                            break;
                        }

                        //正しい駒の動きではない or 移動間に味方がいる
                        else {
                            printf("正しい駒の動きではありません。もしくは、移動間に駒があります\n");
                            continue;
                        }
                    }

                    //移動先に味方がいる
                    else {
                        printf("移動先に味方がいます\n");
                        continue;
                    }
                }

                //違法な座標が入力されている
                else {
                    printf("正しい座標ではありません\n");
                    continue;
                }
            }
        }
        //あなたのターン終了

        //相手のターン
        else {
            //ターンの切り替え
            whoseTurn++;

            //ランダムで移動
            while (1) {
                //ランダムな座標を取得
                wherePiece[0] = rand() % 8; //０～７
                wherePiece[1] = rand() % 8;

                //自身の駒か
                if (subBoard[wherePiece[0]][wherePiece[1]] == 'e') {
                    whereMove[0] = rand() % 8;
                    whereMove[1] = rand() % 8;

                    //自身の駒と重なるか
                    if (subBoard[whereMove[0]][whereMove[1]] != 'e') {
                        //移動可能か
                        moveFlag = canMove_piece(board[wherePiece[0]][wherePiece[1]], wherePiece, whereMove, subBoard);

                        if (moveFlag == 1) {
                            //printf("moveFlag == 1\n");

                            //移動処理 : board, subBoardの情報を更新
                            temp = board[wherePiece[0]][wherePiece[1]]; //移動前の情報を保存

                            //移動前の座標を空にする
                            if ((wherePiece[0] + wherePiece[1]) % 2 == 0) {
                                board[wherePiece[0]][wherePiece[1]] = '*';
                            }
                            else {
                                board[wherePiece[0]][wherePiece[1]] = '+';
                            }

                            board[whereMove[0]][whereMove[1]] = temp; //駒を移動

                            //subBoardの更新
                            temp = subBoard[wherePiece[0]][wherePiece[1]]; //移動前の情報を保存
                            subBoard[wherePiece[0]][wherePiece[1]] = '*'; //移動前の座標を空にする
                            subBoard[whereMove[0]][whereMove[1]] = temp; //駒を移動

                            printf("\n相手のターンが終了しました\n");
                            output_board(board, subBoard);

                            break;
                        }

                        //正しい駒の動きではない or 移動間に味方がいる
                        else {
                            //printf("正しい駒の動きではありません。もしくは、移動間に味方がいます\n");
                            continue;
                        }
                    }

                    //自身の駒と重なる
                    else {
                        continue;
                    }
                }

                //自身の駒ではない
                else {
                    continue;
                }
            }

            //ゲーム終了条件の確認
            checkMate = isGame_finish(board, subBoard);

            //引き分けの確認
            checkDraw = isGame_draw(subBoard);

        }

        //初期化
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

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します