#include "item.h"
#include "board.h"

Item::Item(const int &y, const int &x, QPixmap *empty, Board *parent, AI *child)
{

    setPalette(QPalette (QColor ("#ffc74f")));
	setAutoFillBackground(true);

	this->x=x;
	this->y=y;
	this->empty=empty;
	this->type=TYPE_EMPTY;
	this->parentPtr=parent;
    this->childPtr=child;
	this->setPixmap(*empty);
	this->setMinimumSize ((*empty).width(), (*empty).height());

}

void Item::mousePressEvent (QMouseEvent *)
{
	if ((this->type==TYPE_EMPTY) && parentPtr->game){
		switch (parentPtr->gameType){
			case Board::TYPE_LOCAL:
            //흑우 첫수 vs 백우 ai
                if(parentPtr->activeType==TYPE_CROSS && parentPtr->AImode[1]==1 && parentPtr->wturn==1&& parentPtr->turn==1){
                    this->childPtr->insertAI_W_first1();
                    break;
                }else if(parentPtr->activeType==TYPE_CIRCLE && parentPtr->AImode[0]==1 && parentPtr->bturn==0&& parentPtr->turn==0){
                    this->childPtr->firstdol_B();
                    break;
                }
                else if(parentPtr->activeType==TYPE_CROSS && parentPtr->AImode[1]==1 && parentPtr->wturn==2&& parentPtr->turn==2){
                    this->childPtr->insertAI_W_first2();
                    break;
                }
                else if(parentPtr->activeType==TYPE_CROSS && parentPtr->AImode[1]==1&&parentPtr->turn >=3){
                    this->childPtr->insertAI_W();
                    break;
                } else if(parentPtr->activeType==TYPE_CIRCLE && parentPtr->AImode[0]==1&&parentPtr->turn >=3){
                    this->childPtr->insertAI_B();
                    break;
                }
                else{
                this->parentPtr->addItem (this->x, this->y);
                break;
                }


			case Board::TYPE_SERVER:
				if ((int)parentPtr->activeType==(int)Board::TYPE_SERVER){
                    if(parentPtr->activeType==TYPE_CROSS && parentPtr->AImode[1]==1 && parentPtr->wturn==1&& parentPtr->turn==1){
                        this->childPtr->insertAI_W_first1();
                        break;
                    }else if(parentPtr->activeType==TYPE_CIRCLE && parentPtr->AImode[0]==1 && parentPtr->bturn==0&& parentPtr->turn==0){
                        this->childPtr->firstdol_B();
                        break;
                    }else if(parentPtr->activeType==TYPE_CROSS && parentPtr->AImode[1]==1 && parentPtr->wturn==2&& parentPtr->turn==2){
                        this->childPtr->insertAI_W_first2();
                        break;
                    }else if(parentPtr->activeType==TYPE_CROSS && parentPtr->AImode[1]==1&&parentPtr->turn >=3){
                        this->childPtr->insertAI_W();
                        break;
                    }else if(parentPtr->activeType==TYPE_CIRCLE && parentPtr->AImode[0]==1&&parentPtr->turn >=3){
                        this->childPtr->insertAI_B();
                        break;
                    }
                    else{
					this->parentPtr->server->writeToClient("200 "+QString::number(this->x)+" "+QString::number(this->y)+"\n");
					this->parentPtr->addItem (this->x, this->y);
                    }
				}
				break;

			case Board::TYPE_CLIENT:
				if ((int)this->parentPtr->activeType==(int)Board::TYPE_CLIENT){
                    if(parentPtr->activeType==TYPE_CROSS && parentPtr->AImode[1]==1 && parentPtr->wturn==1&& parentPtr->turn==1){
                        this->childPtr->insertAI_W_first1();
                        break;
                    }else if(parentPtr->activeType==TYPE_CIRCLE && parentPtr->AImode[0]==1 && parentPtr->bturn==0&& parentPtr->turn==0){
                        this->childPtr->firstdol_B();
                        break;
                    }else if(parentPtr->activeType==TYPE_CROSS && parentPtr->AImode[1]==1 && parentPtr->wturn==2&& parentPtr->turn==2){
                        this->childPtr->insertAI_W_first2();
                        break;
                    }else if(parentPtr->activeType==TYPE_CROSS && parentPtr->AImode[1]==1&&parentPtr->turn >=3){
                        this->childPtr->insertAI_W();
                        break;
                    }else if(parentPtr->activeType==TYPE_CIRCLE && parentPtr->AImode[0]==1&&parentPtr->turn >=3){
                        this->childPtr->insertAI_B();
                        break;
                    }
                    else{
					this->parentPtr->client->writeToServer ("200 "+QString::number(this->x)+" "+QString::number(this->y)+"\n");
					this->parentPtr->addItem (this->x, this->y);
                    }
				}
				break;
			}
	}
}

void Item::clear (void){
	this->type=TYPE_EMPTY;
	this->setPixmap(*empty);
}
