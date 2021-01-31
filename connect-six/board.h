#ifndef BOARD_H
#define BOARD_H

/*! \class Board
 *  \brief Board
 *
 *  플레이 영역
 */

#include <QWidget>
#include <QGridLayout>
#include <iostream>
#include "item.h"
#include "server.h"
#include "client.h"
#include "stdafx.h"


using namespace std;

/** 육목판 크기 */
#define MAX_X 19
#define MAX_Y 19
#define MAX_ITEMS MAX_Y*MAX_X

typedef struct{
    int x,y;
    //int win;//0:game running, 1:client1 win ,2:client2 win
    //int turn;//1:client1 turn ,2:client2 turn
}GAME_DATA;

class MainWindow;
class AI;

class Board : public QWidget
{
    friend class AI;
    friend class MainWindow;
	friend class Item;
    Q_OBJECT
public:

    /*!
     *
     *  \enum gameType
     *  \brief 프로그램이 계속 수행할 역할
     *
     *  2인용 PC/ 클라이언트/ 서버 게임
     *
     *	\fn Board::Board (QWidget  *parent = NULL)
     *  \brief Konstruktor
     *
     *  플레이 영역 초기화 및 필요한 변수 설정
     *
     *  \param[in] parent는 Qt 자체가 부모 클래스를 삭제할 때 객체 할당 해제를 처리하도록합니다
     *
     *  \fn Board::~Board ()
     *  \brief 소멸자
     *
     *  \var Board::gameType
     *  \brief 프로그램이 게임에서 수행할 역할
     *
     *  \var Board::activeType
     *  \brief 플레이 턴
     *
     *  \var Board::server
     *  \brief 서버 디렉토리
     *
     *  \var Board::client
     *  \brief 클라이언트 포인터
     *
     *  \var Board::score
     *  \brief 점수 정보 필드
     */

	enum gameType{
		TYPE_LOCAL=0,
		TYPE_SERVER=1,
        TYPE_CLIENT=2,
        TYPE_WAI=3,
        TYPE_BAI=4
    };

	explicit Board (char *argv[], int argc, QPixmap *, QPixmap *, QPixmap *, QWidget  *parent = NULL);
	~Board ();

	bool game;
	gameType gameType;
	Item::Type activeType;
	Server *server;
	Client *client;
    AI *ai;

	int score[2];
    int AImode[2];
    //QList <QPair <int, int> > moved;
    int wmoved[20][20] = {};
    int bmoved[20][20] = {};
    int bturn = 0 ;
    int wturn = 0 ;
    int turn = 0 ;

    //MainWindow * w;
    GAME_DATA gamedata;

    QList <QPair <int, int> > moves;
    QList <QPair <int, int> > pentad;



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
    /*!
     *  \fn void Board::reset (void)
     *  \brief 전체 경기장을 재설정하고 새 게임을 준비합니다.
     *
     *  \fn void Board::reset_net (void)
     *  \brief 전체 플레이 필드를 재설정하고 네트워크에서만 호출
     *
     *  \fn Board::addItem_net (int, int)
     *  \brief 네트워크에서 호출되며 <EM> addItem </ EM> 함수를 호출합니다.
     *  \param[in] x 필드 x의 좌표
     *  \param[in] y 필드 y의 좌표
     *
     *  \fn void Board::setGame (int)
     *  \brief <EM>game</EM> 변수 설정
     *
     *  \fn void Board::moveBack (void)
     *  \brief 간단한 이동 취소
     *
     *  \fn void Board::moveBackClicked (void)
     *  \brief 상대방에게 이동을 반환하도록 요청하거나 <EM>moveBack</EM> 함수를 직접 호출합니다.
     *
     */
	void reset (void);
	void reset_net (void);
	void addItem_net (const int &, const int &);
    void addItem (const int&, const int&);
	void setGame (const int&);
	void moveBack (void);
	void moveBackClicked (void);

private:

    /*!
     *
     *  \fn Board::testwin (int x, int y)
     *  \brief 누가 이겼는지 확인
     *  \param[in] x 필드 x의 좌표
     *  \param[in] y 필드 y의 좌표
     *
     *  \fn Board::addItem (int, int)
     *  \brief 강조 표시된 십자 / 원을 필드에 삽입합니다.
     *  \param[in] x 필드 x의 좌표
     *  \param[in] y 필드 y의 좌표
     *
     *  \fn Board::unHighlight (void)
     *  \brief 두 번째 움직임을 흐리게합니다.
     *
     *
     *  \var Board::game
     *  \brief 재생할 수 있는지 여부를 나타냅니다
     *
     *  \var Board::win
     *  \brief 누가 승리했는지 표시
     *
     *  \var Board::firstPlayer
     *  \brief 선공 결정
     *
     *  \var Board::moves
     *  \brief 동작에 대한 배열
     *
     *  \var Board::pentad
     *  \brief 승리 시 강조되는 표현
     *
     *  \var Board::items
     *  \brief 동적으로 할당된 2D 배열
     *
     *  동적으로 할당 된 2D 배열에 대한 포인터, 각 배열의 포인터는 동적으로 할당 된 항목을 가리킵니다.
     *
     *  \var Board::circle
     *  \brief 원 이미지에 대한 간략한 포인터
     *
     *  \var Board::circleHighlighted
     *  \brief 원 이미지 강조
     *
     *  \var Board::cross
     *  \brief 크로스 이미지에 대한 포인터
     *
     *  \var Board::crossHighlighted
     *  \brief 크로스 이미지 강조
     *
     * \var Board::empty
     * \brief 빈 필드에 대한 포인터
     */

	bool testwin (const int&, const int&);
    //void addItem (const int&, const int&);
	void unHighlight (void);


	Item::Type win;
	Item::Type firstPlayer;

    //QList <QPair <int, int> > moves;
    //QList <QPair <int, int> > pentad;

	Item *** items;
	QPixmap *circle;
	QPixmap circleHighlighted;
	QPixmap *cross;
	QPixmap crossHighlighted;
	QPixmap *empty;
};

#endif // BOARD_H
