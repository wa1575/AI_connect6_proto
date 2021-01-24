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

	/*!
	 *
	 *	\fn Client::Client (int MAX_X, int MAX_Y, const QHostAddress hostname, int port, QObject *parent=NULL)
     *  \brief 클라이언트
     *  \param[in] MAX_X 은 X에 대한 보드판 치수
     *  \param[in] MAX_Y 은 Y에 대한 보드판 치수
     *  \param[in] hostname 은 클라이언트가 연결되는 서버의 IP 주소입니다.
     *  \param[in] port 는 클라이언트가 연결하는 포트입니다.
     *  \param[in] parent Qt가 부모 클래스를 소멸 시킬 때 객체의 할당 해제를 처리하도록합니다.
	 *
     *  필요한 변수 설정
	 *
	 *
	 *  \fn Client::writeToServer (QString)
     *  \brief 소켓에 한 줄을 씁니다.
     *  \param[in] output 기록할 출력 라인
	 *  \return bool
	 *
	 *  \fn Client::start ()
     *  \brief 서버에 대한 연결 시도
	 *
	 *
	 */

	explicit Client (const int &MAX_X, const int &MAX_Y, const QHostAddress &hostname, const int &port, QObject *parent=NULL);
	bool start (void);
	bool writeToServer (QString);

signals:

	/*!
	 *
	 *  \fn Client::move (int, int)
     *  \brief 네트워크에서 이동이있을 때 호출됩니다.
     *  \param[in] x - 필드의 X 좌표
     *  \param[in] y - 필드의 Y 좌표
	 *
	 *  \fn Client::connectionStatus (int)
     *  \brief 연결 / 연결 해제를 나타냅니다.
     *  \param[in] x - 연결 해제 / 연결됨
	 *
	 *  \fn Client::reset_net (void)
     *  \brief 게임을 초기화하는 서버 명령을 나타냅니다.
	 *
	 *  \fn Board::NewGamePressed (int)
     *  \brief 새 게임 버튼을 누를 때 호출됩니다
     *  \param[in] x 창에서 버튼을 비활성화 / 활성화합니다.
	 *
	 *  \fn Client::moveBack (void)
     *  \brief 이동을 반환하는 서버 명령을 나타냅니다
	 *
	 *  \fn Client::statusChanged (int)
     *  \brief 각 이동 / 승리 / 무승부 후 상태 변경을 나타냅니다.
     *  \param[in] 이벤트 신호 상태
	 *
	 *  \fn Client::buttonPressed (int)
     *  \brief 아무 버튼이나 눌렀 음을 나타냅니다.
     *  \param[in] x 누르기 비활성화 / 누르기 활성화
	 *
	 */

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
