#include "board.h"



Board::Board (char *argv[], int argc, QPixmap *empty, QPixmap *circle, QPixmap *cross, QWidget *parent) : QWidget(parent)
{
	int i, j;
	this->server=NULL;
	this->client=NULL;


	this->gameType=TYPE_LOCAL;
	this->game=1;


	QGridLayout *layout=new QGridLayout (this);
    layout->setSpacing (0);//폴리 키 사이 1 픽셀의 거리

    this->items=new Item**[MAX_Y];// 행렬에 대한 포인터 (addWidget으로 인해)가있는 2 차원 배열의 동적 할당
    for (i=0;i<MAX_Y;i++){ //행렬 생성
		layout->setRowMinimumHeight (i, 26);
		this->items[i]=new Item*[MAX_X];
		for (j=0;j<MAX_X;j++){
			this->items[i][j]=new Item (i, j, empty, this);
			layout->setColumnMinimumWidth(j, 26);
			layout->addWidget (this->items[i][j], i, j);
		}
	}
	this->activeType=Item::TYPE_CIRCLE;
	this->firstPlayer=Item::TYPE_CIRCLE;
	this->win=Item::TYPE_EMPTY;

	this->empty=empty;
	this->circle=circle;
	this->cross=cross;
	this->score[0]=0;
	this->score[1]=0;

	circleHighlighted.load(":/images/white_highlighted.png");
	crossHighlighted.load(":/images/black_highlighted.png");
}

void Board::unHighlight (void)//마지막 동작의 강조 표시를 취소합니다.
{
	if (this->moves.size()>0){
		if (this->activeType==Item::TYPE_CIRCLE){
			this->items[moves[moves.size()-1].second][moves[moves.size()-1].first]->setPixmap(*cross);
		}else if (this->activeType==Item::TYPE_CROSS){
			this->items[moves[moves.size()-1].second][moves[moves.size()-1].first]->setPixmap(*circle);
		}
	}
}

void Board::addItem_net (const int &x, const int &y)
{
	if (x<MAX_X && y<MAX_Y && x>-1 && y>-1){
		if (this->server && ((int)this->items[y][x]->type==(int)Item::TYPE_EMPTY) && this->game && ((int)this->activeType==(int)TYPE_CLIENT)){
			this->addItem (x, y);
        }
        else if (client && ((int)this->items[y][x]->type==(int)Item::TYPE_EMPTY) && this->game && ((int)this->activeType==(int)TYPE_SERVER)){
			this->addItem (x, y);
		}
	}
}

void Board::addItem (const int &x, const int &y)//사이트에서 좌표를 보내는 다른 방법을 만듭니다
{
	if (x<MAX_X && y<MAX_Y && x>-1 && y>-1){
		int i;
		Item::Type t=this->activeType;
		this->items[y][x]->type=t;

		this->unHighlight ();
		this->moves.append(QPair <int, int>(x, y));

		if (t==Item::TYPE_CIRCLE){
			this->items[y][x]->setPixmap(circleHighlighted);
			this->activeType=Item::TYPE_CROSS;
		}else{
			this->items[y][x]->setPixmap(crossHighlighted);
			this->activeType=Item::TYPE_CIRCLE;
		}
		
		emit this->statusChanged (activeType);

        //승리 검증
		if (testwin (x, y) || moves.size()==MAX_ITEMS){
			this->game=0;
			this->win=t;
			this->score[(int)win-1]++;

            //청원 강조
			if (this->win==Item::TYPE_CIRCLE){
				for (i=0;i<5;i++){
					this->items[this->pentad[i].second][this->pentad[i].first]->setPixmap(circleHighlighted);
				}
			}else{
				for (i=0;i<5;i++){
					this->items[this->pentad[i].second][this->pentad[i].first]->setPixmap(crossHighlighted);
				}
			}
			emit this->statusChanged(t+2);
		}

        //무승부인지 확인
		if (moves.size()==MAX_ITEMS){
			this->game=0;
			this->win=t;
			this->score[0]++;
			this->score[1]++;
			emit this->statusChanged(t+4);
		}
	}
}

void Board::moveBack (void)
{
	if (!this->win){
		if (this->moves.size()>1){
			this->items[this->moves[this->moves.size()-1].second][this->moves[this->moves.size()-1].first]->setPixmap (*empty);
			this->items[this->moves[this->moves.size()-1].second][this->moves[this->moves.size()-1].first]->type=Item::TYPE_EMPTY;
			moves.removeLast ();

			if (this->activeType==Item::TYPE_CIRCLE){
				this->items[this->moves[this->moves.size()-1].second][this->moves[this->moves.size()-1].first]->setPixmap (circleHighlighted);
				this->activeType=Item::TYPE_CROSS;
			}else{
				this->items[this->moves[this->moves.size()-1].second][this->moves[this->moves.size()-1].first]->setPixmap (crossHighlighted);
				this->activeType=Item::TYPE_CIRCLE;
			}

			emit this->statusChanged (this->activeType);
			emit this->statusChanged (7);
		}
	}
}

void Board::moveBackClicked (void)
{
	if (this->win){
		emit this->statusChanged (11);
	}else{
		switch (this->gameType){

			case Board::TYPE_LOCAL:
				this->moveBack ();
				this->game=1;
				break;

			case Board::TYPE_SERVER:
					emit this->NewGamePressed (0);
					this->game=0;
                    this->server->writeToClient ("300 200 200\n");//reset 요청
					//QMessageBox::information (NULL, "Asking oponent.", "You asked your opponent to reset this game");
					emit this->statusChanged(10);
					return;
				break;

			case Board::TYPE_CLIENT:
					emit this->NewGamePressed (0);
					this->game=0;
                    this->client->writeToServer ("300 200 200\n");//re set 요청
					emit this->statusChanged(10);
					//QMessageBox::information (NULL, "Asking oponent.", "You asked your opponent to reset this game");
					return;
				break;
		}
	}
}

void Board::reset_net(void)
{
	for (int i=0; i< MAX_Y;i++){
		for (int j=0;j<MAX_X;j++){
			this->items[i][j]->clear ();
		}
	}
	this->game=1;
	if (this->win!=Item::TYPE_EMPTY){
        this->activeType=(Item::Type)(3-(int)this->firstPlayer);// 3은 typename Item :: Type의 요소 수입니다.
	}else{
		this->activeType=Item::TYPE_CIRCLE;
	}
	this->firstPlayer=activeType;
	this->win=Item::TYPE_EMPTY;
	this->moves.clear ();
	this->pentad.clear ();
	emit this->statusChanged(activeType);
	emit this->statusChanged(7);
}

void Board::reset (void)
{
	switch (this->gameType){

		case Board::TYPE_LOCAL:
            this->game=1;//게임이 즉시 준비되기 때문에 서버 / 클라이언트에 의존하지 않습니다.
			//emit statusChanged(activeType);
			break;

		case Board::TYPE_SERVER:
			if (win){
                this->game=1;//승리하면 게임이 초기화됩니다 ..
				this->server->writeToClient ("400 400 400\n");//reset
			}else{
				emit this->NewGamePressed (0);
				this->game=0;
                this->server->writeToClient ("300 300 300\n");//reset 요청
				emit this->statusChanged(10);
				//QMessageBox::information (NULL, "Asking oponent.", "You asked your opponent to reset this game");
				return;
			}
			break;

		case Board::TYPE_CLIENT:
			if (this->win){
				this->game=1;
				this->client->writeToServer ("400 400 400\n");//reset
			}else{
				emit this->NewGamePressed (0);
				this->game=0;
                this->client->writeToServer ("300 300 300\n");//reset 요청
				emit this->statusChanged(7);
				//QMessageBox::information (NULL, "Asking oponent.", "You asked your opponent to reset this game");
				return;
			}
			break;
	}

	for (int i=0; i< MAX_Y;i++){
		for (int j=0;j<MAX_X;j++){
			this->items[i][j]->clear ();
		}
	}

    if (this->win!=Item::TYPE_EMPTY){//우승 후 선수 교체 확인
		this->activeType=(Item::Type)(3-(int)this->firstPlayer);
	}else{
		this->activeType=Item::TYPE_CIRCLE;
	}

	if (this->game){
		emit this->statusChanged(activeType);
	}

	this->firstPlayer=activeType;
	this->win=Item::TYPE_EMPTY;
	this->moves.clear ();
	this->pentad.clear ();
	emit this->statusChanged(7);
}

void Board::setGame (const int &x)
{
	this->game=x;
}

bool Board::testwin (const int &x, const int &y)//승리 제어
{
	int i, count, itemRemainBottom, tmpX, tmpY;
	Item::Type searched=this->items[y][x]->type;

    //수평으로 5개
	for (i=0;i<MAX_X;i++){
		if (this->items[y][i]->type==searched){
			this->pentad.append(QPair <int, int>(i, y));
			if (this->pentad.size ()>=5){
				return 1;
			}
		}else{
			this->pentad.clear ();
		}
	}
	this->pentad.clear();

    //수직으로 5개
	for (i=0;i<MAX_Y;i++){
		if (this->items[i][x]->type==searched){
			this->pentad.append(QPair <int, int>(x, i));
			if (this->pentad.size ()>=5){
				return 1;
			}
		}else{
			this->pentad.clear ();
		}
	}
	this->pentad.clear();

    //대각선으로 왼쪽 위
    itemRemainBottom=((MAX_X-1-x) <= (MAX_Y-1-y)) ? (MAX_X-1-x) : (MAX_Y-1-y);//게임판의 가장 가까운 영역에 몇 개의 선반이 있는지
	tmpX=x+itemRemainBottom;
	tmpY=y+itemRemainBottom;

	while ((tmpX>=0) && (tmpY>=0)){
		if (this->items[tmpY][tmpX]->type==searched){
			this->pentad.append(QPair <int, int>(tmpX, tmpY));
			if (this->pentad.size ()>=5){
				return 1;
			}
		}else{
			this->pentad.clear ();
		}
		tmpX--;
		tmpY--;
	}
	this->pentad.clear();

    //대각선 오른쪽 위로
	itemRemainBottom=((x) <= (MAX_Y-1-y)) ? (x) : (MAX_Y-1-y);
	tmpX=x-itemRemainBottom;
	tmpY=y+itemRemainBottom;
	count=0;

	while ((tmpX<MAX_X) && (tmpY>=0)){
		if (this->items[tmpY][tmpX]->type==searched){
			this->pentad.append(QPair <int, int>(tmpX, tmpY));
			if (this->pentad.size ()>=5){
				return 1;
			}
		}else{
			this->pentad.clear ();
		}
		tmpX++;
		tmpY--;
    }
	this->pentad.clear();

    //아무도 이기지 않은 경우
	return 0;
}


Board::~Board ()
{
	int i;
	for (i=0;i<MAX_Y;i++){
		delete [] this->items[i];
	}
	delete [] this->items;
}
