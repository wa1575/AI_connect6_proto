#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QMessageBox>
#include <QStringList>
#include <iostream>
#include <QString>
#include <QHostAddress>
using namespace std;

class Client : public QObject
{
Q_OBJECT
public:

    //보드판 치수, 클라이언트가 연결되는 ip주소, 포트번호, qt가 부모클래스 소멸시킬 때 객체 할당 해제 처리
    explicit Client (const int &MAX_X, const int &MAX_Y, const QHostAddress &hostname, const int &port, QObject *parent=NULL);
    bool start (void); //서버에 연결 시도
    bool writeToServer (QString);//소켓에 한줄 쓰기

signals:

	void move (const int&, const int&);
	void connectionStatus (const int&);
	void reset_net (void);
	void NewGamePressed (const int&);
	void moveBack (void);
	void statusChanged (const int&);
	void buttonPressed (const int&);

public slots:

    /*!
     *
     *  \fn Client::serverService (void)
     *  \brief 간단한 서버 신호 제공, 통신 시작
     *
     *  \fn Client::handleServer (void)
     *  \brief 간단한 서버 요청 처리
     *
     *  \fn Client::dropConnection (void)
     *  \brief 현재 연결을 닫습니다.
     *
     */


	void serverService (void);
	void handleServer (void);
	void dropConnection (void);

private:

    /*!
     *
     *  \fn Client::readFromServer ()
     *  \brief 소켓에서 한 줄을 읽습니다.
     *  \return bool
     *
     *  \fn Client::parseMessage ()
     *  \brief 네트워크에서 보낸 메시지를 구문 분석하고 처리합니다.
     *  \return bool
     *
     *  \fn Client::MsgDialog (QString)
     *  \brief 대화 상자를 호출합니다.
     *  \param[in] message  창에 나타나는 메시지입니다.
     *
     *  \var Client::code
     *  \brief  네트워크 명령 유형(type)
     *  - 100 게임 판 크기
     *  - 200 tah
     *  - 300 게임 초기화 / 반환 이동을 위한 상대 질문
     *  - 400 하드 보드 재설정
     *
     *  \var Client::buffer
     *  \brief 네트워크 명령 한 줄
     *
     *  \var Client::port
     *  \brief 서버의 포트 번호
     *
     *  \var Client::MAX_X
     *  \brief X 게임판 x축 크기
     *
     *  \var Client::MAX_Y
     *  \brief Y 게임판 y축 크기
     *
     *  \var Client::hostname
     *  \brief 서버 IP 주소
     *
     *  \var Client::socket
     *  \brief 소켓 지정
     *
     */
	bool readFromServer (void);
	bool parseMessage (void);

	int MsgDialog (QString);

	int code;
	QString buffer;

	int port;
	int MAX_X;
	int MAX_Y;
	QHostAddress hostname;
	QTcpSocket *socket;


};

#endif // CLIENT_H
