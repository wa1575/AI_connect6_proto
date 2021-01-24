#include "server.h"


Server::Server (const int &MAX_X, const int &MAX_Y, const int &port, QObject *parent) : QObject(parent)
{
	this->socket=NULL;
	this->port=port;
	this->MAX_X=MAX_X;
	this->MAX_Y=MAX_Y;
}

bool Server::start ()//드롭다운 서버모드
{
    this->tcpServer = new QTcpServer (this);//서버 생성
	this->tcpServer->setMaxPendingConnections(1);

    if (!this->tcpServer->listen (QHostAddress::Any, this->port)){//주어진 포트에서 들을 수 있는지 테스트
		QMessageBox::critical(NULL, "Tic Tac Toe Server", "Unable to start the server, this port isn't available.");
		this->dropConnection ();
		cout << "Unable to start the server, this port isn't available." << endl;
		return 1;
	}

	connect(this->tcpServer, SIGNAL (newConnection ()), this, SLOT (clientService ()));

	return 0;
}

void Server::clientService ()
{
    if (!this->socket){////////게임이 이미 생성 된 경우 다른 사람이 참여할 수 없습니다.
        this->socket = this->tcpServer->nextPendingConnection();//서버 소켓 가져 오기
		connect(this->socket, SIGNAL (disconnected ()), this, SLOT (dropConnection (void)));
		connect (this->socket, SIGNAL (readyRead ()), this, SLOT (handleClient ()));

		//writeToClient("100 "+QString::number(MAX_X)+" "+QString::number(MAX_Y)+"\n");//zasle velikost sachovnice
		emit this->connectionStatus (1);
	}
}

void Server::handleClient ()
{
	this->readFromClient ();
	//cout << buffer.toLatin1().data() <<endl;

	if(!this->parseMessage ()){
		this->dropConnection ();
		this->start ();
	}
}

bool Server::parseMessage ()
{
	QStringList p = this->buffer.split(" ");

    if(p.length() != 3){//프로토콜 준수 확인
		QMessageBox::critical (NULL, "Tic Tac Toe Server", "Client don't use our protocol!");
		return false;
	}
    //새로운 게임에 대한 신호를 additem (또는 다른 것)에 추가하기 위해 다양한 코드를 보낼 수 있도록

	switch (p[0].toInt()){
	case 100:
        if (p[1].toInt()!=MAX_X || p[2].toInt()!=MAX_Y){//두 사람 모두 같은 플레이 공간이 없어서 목소리가 튀어 나오지 않도록
			QMessageBox::critical(NULL, "Tic Tac Toe Server", "Server and Client don't have the same size of playboard");
			return false;
		}
		break;
	case 200:
		emit this->move (p[1].toInt (), p[2].toInt ());
		break;
	case 300:
		switch (p[1].toInt()){
		case 300:
			switch (MsgDialog ("Your opponent wants to reset game.")){
				case QMessageBox::Yes:
					this->writeToClient("300 1 1\n");
					emit reset_net ();
				   break;
				case QMessageBox::No:
				   this->writeToClient("300 0 0\n");
				   break;
			}
			break;
		case 1:
			emit this->reset_net ();
			emit this->NewGamePressed (1);
			emit this->buttonPressed (1);
			//QMessageBox::information(NULL, "Game reseted.", "Your opponent accepted your offeer.");
			this->statusChanged (8);
			break;
		case 0:
			emit this->NewGamePressed (1);
			emit this->buttonPressed (1);
			//QMessageBox::information(NULL, "Game wasn't reseted.", "Your opponent rejected your offer.");
			emit this->statusChanged (9);
			break;
		case 200:

			switch (MsgDialog ("Your opponent wants to take his move back.")){
				case QMessageBox::Yes:
					this->writeToClient("300 20 20\n");
					emit this->moveBack ();
				   break;
				case QMessageBox::No:
				   this->writeToClient("300 30 30\n");
				   break;
			}

			break;
		case 20:
			emit this->moveBack ();
			emit this->NewGamePressed (1);
			emit this->buttonPressed (1);
			//QMessageBox::information(NULL, "Game reseted.", "Your opponent accepted your offeer.");
			emit this->statusChanged (8);
			break;
		case 30:
			emit this->NewGamePressed (1);
			emit this->buttonPressed (1);
			//QMessageBox::information(NULL, "Game wasn't reseted.", "Your opponent rejected your offer.");
			emit this->statusChanged (9);
			break;

		}

		break;
	case 400:
		emit this->reset_net ();
		break;
	}
	return true;
}

bool Server::readFromClient () // 주어진 네트워크 소켓에서 읽습니다.
{
	QByteArray line=this->socket->readLine().trimmed();

	if(!line.isEmpty ()){
		this->buffer = QString (line);
		return true;
	}
	QMessageBox::critical (NULL, "Tic Tac Toe Server", "Invalid read");
	this->dropConnection ();
	this->start ();
	return false;
}

bool Server::writeToClient (const QString &output)
{
    if(this->socket != NULL && !this->socket->isValid() || !this->socket || !this->socket->isOpen()){//소켓의 개방성과 유효성 확인
		return false;
	}

	if (this->socket){
		this->socket->write (output.toAscii());
		this->socket->flush ();
		return true;
	}else{
		//QMessageBox::critical(NULL, "Tic Tac Toe Server", "Nobody has connected yet!");
		return false;
	}
}

int Server::MsgDialog (const QString &message)
{
	QMessageBox msgBox;
	msgBox.setText(message);
	msgBox.setInformativeText("Do you want agree?");
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	msgBox.setDefaultButton(QMessageBox::No);
	return msgBox.exec();
}

void Server::dropConnection (void)
{
	emit connectionStatus (0);
	tcpServer->close ();
	if (socket){
		socket->close ();
	}
	socket=NULL;

    //start ();//연결재설정
}
