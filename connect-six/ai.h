#ifndef AI_H
#define AI_H

#include "stdafx.h"
#include <QLabel>

using namespace std;

namespace Ui {
    class MainWindow;
}

enum Type{
    TYPE_EMPTY=0,
    TYPE_CIRCLE=1,
    TYPE_CROSS=2
};


class Item;
class Board;

class AI : public QLabel
{
    friend class Board;
    friend class Item;
    Q_OBJECT

public:
    enum gameType{
        TYPE_LOCAL=0,
        TYPE_SERVER=1,
        TYPE_CLIENT=2,
        TYPE_WAI=3,
        TYPE_BAI=4
    };


    explicit AI (const int &, const int &, QPixmap *, Board *parent = NULL);

    bool game;
    gameType gameType;

    QList <QPair <int, int> > moves;
    QList <QPair <int, int> > pentad;
    int b[19][19], w[19][19]; //돌의 위치

    void insertAI_W();
    void insertAI_B();
    void insertAI_B_first();
    void insertAI_W_first1();
    void insertAI_W_first2();

    void change_w(int x, int y);
    void change_b(int x, int y);


signals:
    void statusChanged (const int&);//이동/승리/무승부
    void NewGamePressed (const int&);//새 게임 버튼 누를 때 호출

public slots:



private:
    void addItem (const int&, const int&);
    void clear (void);

    Item *** items;
    QPixmap *empty;

    Ui::MainWindow *ui;
    int x,y;
    Board* parentPtr;
    Type type;

    // AI 변수
    int i, j, z, bx, by, wx, wy, n;
    int max_weight; // 2차원 배열의 가중치 최대값을 저장하는 변수
    long int W_weight[19][19];	//좌표마다 가중치 점수 저장하는 배열
    long int B_weight[19][19];
    int if_w[19][19];	//바둑돌이 놓여지는 b, w배열에서 가중치를 판단하기 위한 추가배열
    int if_b[19][19];
    int turn;	//첫 번째 턴인지 두 번째 턴인지 구분해주는 함수이다.

    void W_AI_allcheck();

    void W_AI_5_6_7_check();

    void W_AI_2_Horizontal_check();
    void W_AI_3_Horizontal_check();
    void W_AI_4_Horizontal_check();

    void W_AI_2_Vertical_check();
    void W_AI_3_Vertical_check();
    void W_AI_4_Vertical_check();

    void W_AI_2_Diagonal_check();
    void W_AI_3_Diagonal_check();
    void W_AI_4_Diagonal_check();

    void W_AI_2_in_Diagonal_check();
    void W_AI_3_in_Diagonal_check();
    void W_AI_4_in_Diagonal_check();

    void defense_Horizontal_check_W();
    void defense_Vertical_check_W();
    void defense_Diagonal_check_W();
    void defense_in_Diagonal_check_W();




    void B_AI_allcheck();

    void B_AI_5_6_7_check();

    void B_AI_2_Horizontal_check();
    void B_AI_3_Horizontal_check();
    void B_AI_4_Horizontal_check();

    void B_AI_2_Vertical_check();
    void B_AI_3_Vertical_check();
    void B_AI_4_Vertical_check();

    void B_AI_2_Diagonal_check();
    void B_AI_3_Diagonal_check();
    void B_AI_4_Diagonal_check();

    void B_AI_2_in_Diagonal_check();
    void B_AI_3_in_Diagonal_check();
    void B_AI_4_in_Diagonal_check();

    void defense_Horizontal_check_B();
    void defense_Vertical_check_B();
    void defense_Diagonal_check_B();
    void defense_in_Diagonal_check_B();

};



#endif // AI_H
