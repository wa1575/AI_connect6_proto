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
    //AI();
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

    int bxaxis[360], byaxis[360], wxaxis[360], wyaxis[360];
    bool bwin(int one);
    bool wwin(int two);
    int b[20][20], w[20][20]; //가중치

    int wcnt2,wcnt3,wcnt4,wcnt5;
    int bcnt2,bcnt3, bcnt4, bcnt5;
    int tempbx, tempby, tempwx, tempwy;


    void W_AI_allcheck();

    void W_AI_5_6_7_check();

    void W_AI_2_garo_check();
    void W_AI_3_garo_check();
    void W_AI_4_garo_check();

    void W_AI_2_sero_check();
    void W_AI_3_sero_check();
    void W_AI_4_sero_check();

    void W_AI_2_slash_check();
    void W_AI_3_slash_check();
    void W_AI_4_slash_check();

    void W_AI_2_in_slash_check();
    void W_AI_3_in_slash_check();
    void W_AI_4_in_slash_check();

    void defense_garo_check_W();
    void defense_sero_check_W();
    void defense_slash_check_W();
    void defense_in_slash_check_W();




    void B_AI_allcheck();

    void B_AI_5_6_7_check();

    void B_AI_2_garo_check();
    void B_AI_3_garo_check();
    void B_AI_4_garo_check();

    void B_AI_2_sero_check();
    void B_AI_3_sero_check();
    void B_AI_4_sero_check();

    void B_AI_2_slash_check();
    void B_AI_3_slash_check();
    void B_AI_4_slash_check();

    void B_AI_2_in_slash_check();
    void B_AI_3_in_slash_check();
    void B_AI_4_in_slash_check();



    void defense_garo_check_B();
    void defense_sero_check_B();
    void defense_slash_check_B();
    void defense_in_slash_check_B();




   //수정필요
    void insertAI_W();
    void insertAI_B();
    void firstdol_B();
    void insertAI_W_first1();
    void insertAI_W_first2();

    void change_w(int x, int y);
    void change_b(int x, int y);


signals:

    /*!
     *  \fn Board::statusChanged (int)
     *  \brief 각 이동 / 승리 / 무승부 후 상태 변경을 나타냅니다.
     *  \param[in] 이벤트 신호 상태
     *
     *  \fn Board::NewGamePressed (int)
     *  \brief  간단한 새 게임 버튼(New game)을 누를 때 호출됩니다.
     *  \param[in] x 창에서 버튼을 비활성화 / 활성화합니다.
     *
     */
    void statusChanged (const int&);
    void NewGamePressed (const int&);

public slots:

    //void bsituation();
    //void wsituation();
    //void prn();

  /*
    void insertblack(MySocket *player,int gameMode);
    void insertwhite(MySocket *player,int gameMode);
    void firstdol_B(MySocket *player,int gameMode);

    bool draw(int zero);
    int winner();

    */

private:

    bool testwin (const int&, const int&);
    void addItem (const int&, const int&);
    void unHighlight (void);
    //void mousePressEvent (QMouseEvent *);
    void clear (void);

    //Item::Type win;
    //Item::Type firstPlayer;

    //QList <QPair <int, int> > moves;
    //QList <QPair <int, int> > pentad;

    Item *** items;
    QPixmap *empty;

    Ui::MainWindow *ui;
    int x,y;
    Board* parentPtr;
    Type type;

    typedef struct{
        int x,y;
        //int win;//0:game running, 1:client1 win ,2:client2 win
        //int turn;//1:client1 turn ,2:client2 turn
    }GAME_DATA;

    // AI 부분 //



    int ga, se, i, j, z, q, e, bx, by, wx, wy, n; // i, j는 display, wx, bx, by, wy, n는 setdol에서 사용. ga : 가로, se : 세로
    //int win; //0:game running, 1:sever win ,2:client win
    // AI 부분 //
    int actpnt; // AI 활동 가중치 변수
    int maxactpnt; // 2차원 배열의 가중치 최대값을 저장하는 변수
    long int act[19][19];	//좌표마다 가중치 점수 저장하는 배열
    long int act2[19][19];
    int newwhite[19][19];	//바둑돌이 놓여지는 b, w배열에서 가중치를 판단하기 위한 추가배열
    int newblack[19][19];
    int turn;	//첫 번째 턴인지 두 번째 턴인지 구분해주는 함수이다.

};



#endif // AI_H
