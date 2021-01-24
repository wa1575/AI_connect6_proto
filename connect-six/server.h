#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMessageBox>
#include <QString>
#include <iostream>
#include <QtNetwork>
using namespace std;


class Server : public QObject
{
Q_OBJECT
public:

	/*!
	 *
	 *	\fn Server::Server (int MAX_X, int MAX_Y, int port, QObject *parent=NULL)
     *  \brief 생성자
     *  \param[in] MAX_X 보드판 X 크기
     *  \param[in] MAX_Y 보드판 Y 크기
     *  \param[in] port 클라이언트가 연결하는 포트
     *  \param[in] parent Qt가 부모 클래스를 파괴 할 때 객체의 할당 해제를 처리하도록합니다
	 *
     *  필드 변수 설정
	 *
	 *
	 *
	 *  \fn Server::start ()
     *  \brief 클라이언트와 연결 설정
	 *
	 *  \fn Server::writeToClient (QString)
     *  \brief 소켓에 한 줄을 씁니다.
     *  \param[in] output 기록할 라인
	 *  \return bool
	 *
	 *
	 */

	explicit Server (const int &MAX_X, const int &MAX_Y, const int &port, QObject *parent = NULL);
	bool writeToClient (const QString &output);
	bool start ();

signals:

	/*!
	 *
	 *  \fn Server::move (int, int)
     *  \brief 네트워크에서 이동이있을 때 호출됩니다.
     *  \param[in] x - 필드의 X 좌표
     *  \param[in] y - 필드의 Y 좌표
	 *
	 *  \fn Server::connectionStatus (int)
     *  \brief 연결 / 연결 해제를 나타냅니다.
     *  \param[in] x - 연결 해제 / 연결됨
	 *
	 *  \fn Server::reset_net (void)
     *  \brief 게임을 재설정하는 클라이언트 명령을 나타냅니다.
	 *
	 *  \fn Board::NewGamePressed (int)
     *  \brief 새 게임 버튼을 누를 때 호출됩니다.
     *  \param[in] x 창에서 버튼을 비활성화 / 활성화합니다.
	 *
	 *  \fn Server::moveBack (void)
     *  \brief 클라이언트가 이동을 반환하는 명령을 나타냅니다.
	 *
	 *  \fn Server::statusChanged (int)
     *  \brief 각 이동 / 승리 / 무승부 후 상태 변경을 나타냅니다.
     *  \param[in] 이벤트 신호 상태
	 *
	 *  \fn Server::buttonPressed (int)
     *  \brief 아무 버튼이나 눌렀음을 나타냅니다.
     *  \param[in] x 누르기 비활성화 / 누르기 활성화
	 *
	 */

	void move (const int &, const int &);
	void connectionStatus (int);
	void reset_net (void);
	void NewGamePressed (int);
	void moveBack ();
	void statusChanged (int);
	void buttonPressed (int);

public slots:

	/*!
	 *
	 *  \fn Server::clientService (void)
     *  \brief 클라이언트 신호 제공, 통신 시작
	 *
	 *  \fn Server::handleClient (void)
     *  \brief 클라이언트 요청 처리
	 *
	 *  \fn Server::dropConnection (void)
     *  \brief 현재 연결을 닫습니다.
	 *
	 */

	void clientService(void);
	void handleClient(void);
	void dropConnection (void);


private:


	/*!
	 *
	 *  \fn Server::parseMessage ()
     *  \brief 네트워크에서 보낸 메시지를 구문 분석하고 처리합니다.
	 *  \return bool
	 *
	 *  \fn Server::readFromClient ()
     *  \brief 소켓에서 한 줄을 읽습니다.
	 *  \return bool
	 *
	 *  \fn Server::MsgDialog (QString)
     *  \brief 대화 상자를 호출합니다.
     *  \param[in] message 메시지는 창에 나타나는 메시지입니다.
	 *
	 *  \var Server::code
     *  \brief Typ 간단한 네트워크 명령 유형
     *  - 100 보드판 크기
	 *  - 200 tah
     *  - 300 게임 초기화 / 반환 이동을위한
     *  - 400 하드 보드 리셋
	 *
	 *  \var Server::buffer
     *  \brief 간단한 네트워크 명령 한 줄
	 *
	 *  \var Server::port
     *  \brief 클라이언트 포트 번호
	 *
	 *  \var Server::MAX_X
     *  \brief X 경기장의 X 치수
	 *
	 *  \var Server::MAX_Y
     *  \brief Y 경기장의 Y 치수
	 *
	 *  \var Server::socket
     *  \brief 소켓에 대한 포인터
	 *
	 *  \var Server::tcpServer
     *  \brief 서버에 대한 포인터
	 *
	 */
	bool readFromClient (void);
	bool parseMessage (void);

	int MsgDialog (const QString &);

	int code;
	QString buffer;

	int port;
	int MAX_X;
	int MAX_Y;
	QTcpSocket *socket;
	QTcpServer *tcpServer;


};

#endif // SERVER_H
