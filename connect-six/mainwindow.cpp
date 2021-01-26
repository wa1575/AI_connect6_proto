#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(char *argv[], int argc, QWidget *parent) : QMainWindow (parent), ui(new Ui::MainWindow)
{
	this->ui->setupUi(this);

    this->circle=new QPixmap (":/images/black.png"); //white
    this->cross=new QPixmap (":/images/white.png");  //black
	this->empty=new QPixmap (":/images/empty.png");
    this->black1 = new QPixmap (":images/black1.png");
    this->white1 = new QPixmap (":/images/white1.png");
    this->black2 = new QPixmap (":images/black2.png");
    this->white2 = new QPixmap (":/images/white2.png");
    this->black3 = new QPixmap (":images/black3.png");
    this->white3 = new QPixmap (":/images/white3.png");
    this->blackcow = new QPixmap(":/images/blackcow.jpg");
    this->whitecow = new QPixmap(":/images/whitecow.jpg");

    this->setMinimumSize(26*MAX_X+50,26*MAX_Y+100);
	this->array=new Board (argv, argc, empty, circle, cross, this);
	this->ui->gridLayout->addWidget(array,2,0);
    this->ui->gridLayout->setRowMinimumHeight (2, 26*MAX_Y);
    this->ui->gridLayout->setColumnMinimumWidth(0, 26*MAX_X);
    this->ui->label_turn->setFixedHeight(75);
    this->ui->label_turn->setFixedWidth(75);
	this->ui->label_color->setFixedHeight(25);
	this->ui->label_color->setFixedWidth(25);
	this->ui->label_turn->setScaledContents(1);
	this->ui->label_color->setScaledContents(1);


	this->ui->label_score->setAlignment(Qt::AlignCenter);
	this->ui->label_score_black->setAlignment(Qt::AlignCenter);
	this->ui->label_score_white->setAlignment(Qt::AlignCenter);

    this->ui->label_4->setPixmap(*blackcow);//*circle
    this->ui->label_5->setPixmap(*whitecow); //*cross

    //창제목 설정
	if ((argc==3) && (QString(argv[1])=="server")){
        this->setWindowTitle("[BoB9]Connect Six Game Server");
	}else if ((argc==4) && (QString(argv[1])=="client")){
        this->setWindowTitle("[BoB9]Connect Six Game Client");
	}else{
        this->setWindowTitle("[BoB9]Connect Six Game");
	}

	connect (this->array, SIGNAL (statusChanged (int)), this, SLOT (displayStatus (const int&)));
	connect (this->array, SIGNAL (NewGamePressed (int)), this, SLOT (buttonPressHandle (int)));

	connect (this->ui->actionMove_Back_2, SIGNAL (triggered ()), this->array, SLOT (moveBackClicked (void)));
	connect (this->ui->actionReset_Game, SIGNAL (triggered ()), this->array, SLOT (reset ()));
	connect (this->ui->actionNew_Network_Game, SIGNAL (triggered ()), this, SLOT (startNetworkGame()));
	connect (this->ui->actionConnect_to_Game, SIGNAL (triggered ()), this, SLOT (ConnectToGame ()));

	if (this->array->server){
		this->setStatusBar (2);
	}else if (this->array->client){
		this->setStatusBar (2);
	}else{
		this->displayStatus(this->array->activeType);
	}

}

void MainWindow::startNetworkGame(){

	int port =0;

	if (this->array->server){
		//this->array->server->dropConnection();
		delete this->array->server;
		this->array->server = NULL;
	}
	if (this->array->client){
		//this->array->client->dropConnection();
		delete this->array->client;
		this->array->client = NULL;
	}

	bool ok;
	port = QInputDialog::getInt(this, tr("Server port number"),
                                tr("Server port number:"), 8089, 0, 65535 ,1, &ok);

	if (ok == false){
		return;
	}


	this->array->server=new Server (MAX_X, MAX_Y, port, this->array);

	if (this->array->server->start() == 1){
		return;
	}


	this->array->gameType=Board::TYPE_LOCAL;
	this->array->reset();
	this->setStatusBar (2);
	this->array->gameType=Board::TYPE_SERVER;
	this->array->game=0;

	connect (this->array->server, SIGNAL(move(int, int)), this->array, SLOT(addItem_net (int, int)));
	connect (this->array->server, SIGNAL(connectionStatus (int)), this->array, SLOT(setGame (int)));
	connect (this->array->server, SIGNAL(NewGamePressed (int)), this->array, SLOT(setGame (int)));
	connect (this->array->server, SIGNAL(reset_net ()), this->array, SLOT(reset_net()));
	connect (this->array->server, SIGNAL(moveBack ()), this->array, SLOT(moveBack()));

    connect (this->array->server, SIGNAL (connectionStatus (int)), this, SLOT (setStatusBar (int)));
	connect (this->array->server, SIGNAL (buttonPressed (int)), this, SLOT (buttonPressHandle (int)));
	connect (this->array->server, SIGNAL (statusChanged (int)), this, SLOT (displayStatus (int)));

	this->ui->label_3->setText ("You are ");
	this->ui->label_color->setPixmap (*circle);

}

void MainWindow::ConnectToGame(){
	QHostAddress hostname;
	bool ok1, ok2;
	int port =0;

	if (this->array->client){
		//this->array->client->dropConnection();
		delete this->array->client;
		this->array->client = NULL;
	}
	if (this->array->server){
		//this->array->server->dropConnection();
		delete this->array->server;
		this->array->server = NULL;
	}

	QString address = QInputDialog::getText(this, tr("Server IP address"),
											tr("Server IP address:"), QLineEdit::Normal,
											"127.0.0.1", &ok1);
	port = QInputDialog::getInt(this, tr("Server port number"),
                                    tr("Server port number:"), 8089, 0, 65535, 1, &ok2);

	if (ok1 && ok2 && !address.isEmpty() && port!=0){
		if(!hostname.setAddress (address)){
			QMessageBox::critical(NULL, "Invalid IP address", "You've entered an invalid IP address!");
			cout << "Unable to start the client, you've entered an invalid IP address!." << endl;
			exit (0);
		}

		this->array->client=new Client (MAX_X, MAX_Y, hostname, port, this->array);
		if (this->array->client->start() == 1){
			return;
		}

		this->array->gameType=Board::TYPE_LOCAL;
		this->array->reset();
		this->array->gameType=Board::TYPE_CLIENT;
		this->array->game=0;
		this->setStatusBar (2);


		connect (this->array->client, SIGNAL(move(int, int)), this->array, SLOT(addItem_net (int, int)));
		connect (this->array->client, SIGNAL(connectionStatus (int)), this->array, SLOT(setGame (int)));
		connect (this->array->client, SIGNAL(NewGamePressed (int)), this->array, SLOT(setGame (int)));
		connect (this->array->client, SIGNAL(reset_net ()), this->array, SLOT(reset_net()));
		connect (this->array->client, SIGNAL(moveBack ()), this->array, SLOT(moveBack ()));

        connect (this->array->client, SIGNAL (connectionStatus (int)), this, SLOT (setStatusBar (int)));//누군가 참여 / 연결 해제 된 상태 표시 줄을 가리켜 야합니다
		connect (this->array->client, SIGNAL (buttonPressed (int)), this, SLOT (buttonPressHandle (int)));
		connect (this->array->client, SIGNAL (statusChanged (int)), this, SLOT (displayStatus (int)));

		this->ui->label_color->setPixmap (*cross);
		this->ui->label_3->setText ("You are ");
	}
}



void MainWindow::setStatusBar (const int &x)
{
	switch (x){
	case 0:
		this->ui->statusBar->showMessage ("Peer disconnected");
		break;

	case 1:
		this->ui->statusBar->showMessage ("Peer connected");

		if (this->array->activeType==Item::TYPE_CIRCLE){
            this->ui->label_turn->setPixmap (*circle);//white
		}else{
            this->ui->label_turn->setPixmap (*cross);//black
            //this->ui->label_turn->setPixmap (*black1);
		}
        this->ui->label_2->setText ("Turns ");

		break;
	case 2:
		this->ui->statusBar->showMessage ("Waiting for peer");
		break;

	case 3:
        this->ui->statusBar->showMessage ("Black won");//White won
		this->ui->label_score_white->setText(QString::number (array->score[0]));
        this->ui->label_turn->setPixmap (*black3);
        QMessageBox::information(NULL, "Black won", "Black WIN");
		break;

	case 4:
        this->ui->statusBar->showMessage ("White won");//Black won
		this->ui->label_score_black->setText (QString::number (array->score[1]));
        this->ui->label_turn->setPixmap (*white3);
        QMessageBox::information(NULL, "White won", "White WIN");
		break;

	case 5:
		this->ui->statusBar->showMessage ("Draw");
		this->ui->label_score_white->setText (QString::number (array->score[0]));
		this->ui->label_score_black->setText (QString::number (array->score[1]));
		//QMessageBox::information(NULL, "Draw", "Draw");
		break;
	case 6:
		this->ui->statusBar->showMessage ("Draw");
		this->ui->label_score_white->setText (QString::number (array->score[0]));
		this->ui->label_score_black->setText (QString::number (array->score[1]));
		//QMessageBox::information(NULL, "Draw", "Draw");
		break;
	}
}


void MainWindow::displayStatus (const int &event)
{
	switch (event){
	case 1:
        //this->ui->label_turn->setPixmap (*circle);
        this->ui->label_turn->setPixmap (*black1);
        this->ui->label_2->setText ("Black's Turn.");
		break;
	case 2:
        //this->ui->label_turn->setPixmap (*cross);
        this->ui->label_turn->setPixmap (*white1);
        this->ui->label_2->setText ("White's Turn.");
		break;
	case 7:
		this->ui->statusBar->showMessage ("");
		break;
	case 8:
		this->ui->statusBar->showMessage ("Your opponent accepted your offeer.");
		break;
	case 9:
		this->ui->statusBar->showMessage ("Your opponent rejected your offer.");
		break;
	case 10:
		this->ui->statusBar->showMessage ("Asking your opponent...");
		break;
	case 11:
		this->ui->statusBar->showMessage ("You can't take back your move if the game is over.");
		break;
	default:
		this->ui->label_turn->clear();
		this->ui->label_2->clear ();
        //this->ui->label_6->setText ("Game Over");
		this->ui->label_3->clear();
		this->setStatusBar (event);
	}
}

void MainWindow::buttonPressHandle (const int &x)
{
	//this->ui->pushButton->setEnabled ((bool)x);
	//this->ui->pushButton_moveBack->setEnabled ((bool)x);

	this->ui->actionMove_Back_2->setEnabled ((bool)x);
	this->ui->actionReset_Game->setEnabled ((bool)x);
}

MainWindow::~MainWindow ()
{
	delete ui;
}



