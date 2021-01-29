#include "ai.h"
#include "board.h"

AI::AI(const int &y, const int &x, QPixmap *empty, Board *parent)
{

    //int i, j;
    this->x=x;
    this->y=y;
    this->empty=empty;
    this->type=TYPE_EMPTY;
    this->parentPtr=parent;
    this->gameType=TYPE_LOCAL;
    this->game=1;
    this->setPixmap(*empty);
    for(i=0; i<19; i++)    /*모든 바둑판위의 값 0으로 초기화*/
        {
            for(j=0; j<19; j++)
            {
                b[i][j] = 0;
                w[i][j] = 0;
            }
        }
        for(i=0; i<19; i++)
        {
            b[i][19] = 3;
            w[i][19] = 3;
        }

}

void AI::bsituation()//연속흑돌갯수새기
{
    bcnt2 = 0, bcnt3 = 0, bcnt4 = 0, bcnt5 = 0;

        //흑돌이 연속으로 2개 놓여져 있는 경우부터 카운트.
        for(int y2=0 ; y2<19 ; y2++)//0열부터 18열까지
        {
          for(int x2=0 ; x2<19 ; x2++)//0행부터 18행까지
          {
              if(b[y2][x2-1]!=theone && b[y2][x2]==theone && b[y2][x2+1]==theone && b[y2][x2+2] !=theone)
                //2개일때 열 앞뒤막고 카운트
              bcnt2++;
              if(b[y2-1][x2]!=theone && b[y2][x2]==theone && b[y2+1][x2]==theone && b[y2+2][x2]!=theone)
                //2개일때 행 앞뒤막고 카운트
              bcnt2++;
              if(b[y2-1][x2-1]!=theone && b[y2][x2]==theone && b[y2+1][x2+1]==theone && b[y2+2][x2+2]!=theone)
                //2개일때 오른쪽대각아래 앞뒤막고 카운트
              bcnt2++;
              if(b[y2-1][x2+1]!=theone && b[y2][x2]==theone && b[y2+1][x2-1]==theone && b[y2+2][x2-2]!=theone)
                //2개일때 왼쪽대각아래 앞뒤막고 카운트
              bcnt2++;
          }
        }
        //흑돌이 연속으로 3개 놓여져 있는 경우 카운트.
        for(int y3=0 ; y3<19 ; y3++)
        {
            for(int x3=0 ; x3<19 ; x3++)
            {
                if(b[y3][x3-1]!=theone && b[y3][x3]==theone && b[y3][x3+1]==theone &&
                    b[y3][x3+2]==theone && b[y3][x3+3]!=theone)
                   //3개일때 열 앞뒤 막고 카운트
                bcnt3++;
                if(b[y3-1][x3]!=theone && b[y3][x3]==theone && b[y3+1][x3]==theone &&
                    b[y3+2][x3]==theone && b[y3+3][x3]!=theone)
                   //3개일때 행 앞뒤 막고 카운트
                bcnt3++;
                if(b[y3-1][x3-1]!=theone && b[y3][x3]==theone && b[y3+1][x3+1]==theone &&
                   b[y3+2][x3+2]==theone && b[y3+3][x3+3]!=theone)
                   //3개일때 대각오른아래 카운트
                bcnt3++;
                if(b[y3-1][x3+1]!=theone && b[y3][x3]==theone && b[y3+1][x3-1]==theone &&
                    b[y3+2][x3-2]==theone && b[y3+3][x3-3]!=theone)
                   //3개 일때 대각왼아래 카운트
                bcnt3++;
            }
        }
        //흑돌이 연속으로 4개 놓여져 있는 경우 카운트.
        for(int y4=0 ; y4<19 ; y4++)
        {
            for(int x4=0 ; x4<19 ; x4++)
            {
                if(b[y4][x4-1]!=theone && b[y4][x4]==theone && b[y4][x4+1]==theone &&
                    b[y4][x4+2]==theone && b[y4][x4+3]==theone && b[y4][x4+4]!=theone)
                    //4개일 때 열방향 카운트
                bcnt4++;
                if(b[y4-1][x4]!=theone && b[y4][x4]==theone && b[y4+1][x4]==theone &&
                    b[y4+2][x4]==theone && b[y4+3][x4]==theone&&b[y4+4][x4]!=theone)
                    //4개일 때 행방향 카운트
                bcnt4++;
                if(b[y4-1][x4-1]!=theone && b[y4][x4]==theone && b[y4+1][x4+1]==theone &&
                    b[y4+2][x4+2]==theone &&b[y4+3][x4+3]==theone&&b[y4+4][x4+4]!=theone)
                    //4개일 때 대각오른아래방향 카운트
                bcnt4++;
                if(b[y4-1][x4+1]!=theone && b[y4][x4]==theone && b[y4+1][x4-1]==theone &&
                    b[y4+2][x4-2]==theone && b[y4+3][x4-3]==theone&&b[y4+4][x4-4]!=theone)
                    //4개일 때 대각왼아래방향 카운트
                bcnt4++;
            }
        }
        //흑돌이 연속으로 5개 놓여져 있는 경우 카운트.
        for(int y5=0;y5<19;y5++)
        {
            for(int x5=0; x5<19;x5++)
            {
                if(b[y5][x5-1]!=theone && b[y5][x5]==theone && b[y5][x5+1]==theone &&
                    b[y5][x5+2]==theone && b[y5][x5+3]==theone && b[y5][x5+4]==theone && b[y5][x5+5]!=theone)
                    //5개 일 때 열 방향 카운트
                bcnt5++;
                if(b[y5-1][x5]!=theone && b[y5][x5]==theone && b[y5+1][x5]==theone &&
                    b[y5+2][x5]==theone && b[y5+3][x5]==theone && b[y5+4][x5]==theone && b[y5+5][x5]!=theone)
                    //5개 일 때 행 방향 카운트
                bcnt5++;
                if(b[y5-1][x5-1]!=theone&& b[y5][x5]==theone && b[y5+1][x5+1]==theone &&
                    b[y5+2][x5+2]==theone && b[y5+3][x5+3]==theone && b[y5+4][x5+4]==theone && b[y5+5][x5+5]!=theone)
                    //5개 일 때 대각선 오른쪽아래 방향 카운트
                bcnt5++;
                if(b[y5-1][x5+1]!=theone && b[y5][x5]==theone && b[y5+1][x5-1]==theone &&
                    b[y5+2][x5-2]==theone && b[y5+3][x5-3]==theone && b[y5+4][x5-4]==theone && b[y5+5][x5-5] !=theone)
                        //5개 일 때 대각선 왼쪽아래 방향 카운트
                bcnt5++;
            }
        }
}

void AI::wsituation()//연속흰돌갯수새기
{
    wcnt2 = 0, wcnt3 = 0, wcnt4 = 0, wcnt5 = 0;

        //백돌이 연속으로 2개 놓여져 있는 경우부터 카운트.
        for(int y2=0 ; y2<19 ; y2++)//0열부터 18열까지
        {
          for(int x2=0 ; x2<19 ; x2++)//0행부터 18행까지
          {
              if(w[y2][x2-1]!=thetwo && w[y2][x2]==thetwo && w[y2][x2+1]==thetwo && w[y2][x2+2] !=thetwo)
                //2개일때 열 앞뒤막고 카운트
              wcnt2++;
              if(w[y2-1][x2]!=thetwo && w[y2][x2]==thetwo && w[y2+1][x2]==thetwo && w[y2+2][x2]!=thetwo)
                //2개일때 행 앞뒤막고 카운트
              wcnt2++;
              if(w[y2-1][x2-1]!=thetwo && w[y2][x2]==thetwo && w[y2+1][x2+1]==thetwo && w[y2+2][x2+2]!=thetwo)
                //2개일때 오른쪽대각아래 앞뒤막고 카운트
              wcnt2++;
              if(w[y2-1][x2+1]!=thetwo && w[y2][x2]==thetwo && w[y2+1][x2-1]==thetwo && w[y2+2][x2-2]!=thetwo)
                //2개일때 왼쪽대각아래 앞뒤막고 카운트
              wcnt2++;
          }
        }
        //백돌이 연속으로 3개 놓여져 있는 경우 카운트.
        for(int y3=0 ; y3<19 ; y3++)
        {
            for(int x3=0 ; x3<19 ; x3++)
            {
                if(w[y3][x3-1]!=thetwo && w[y3][x3]==thetwo && w[y3][x3+1]==thetwo &&
                    w[y3][x3+2]==thetwo && w[y3][x3+3]!=thetwo)
                   //3개일때 열 앞뒤 막고 카운트
                wcnt3++;
                if(w[y3-1][x3]!=thetwo && w[y3][x3]==thetwo && w[y3+1][x3]==thetwo &&
                    w[y3+2][x3]==thetwo && w[y3+3][x3]!=thetwo)
                   //3개일때 행 앞뒤 막고 카운트
                wcnt3++;
                if(w[y3-1][x3-1]!=thetwo && w[y3][x3]==thetwo && w[y3+1][x3+1]==thetwo &&
                   w[y3+2][x3+2]==thetwo && w[y3+3][x3+3]!=thetwo)
                   //3개일때 대각오른아래 카운트
                wcnt3++;
                if(w[y3-1][x3+1]!=thetwo && w[y3][x3]==thetwo && w[y3+1][x3-1]==thetwo &&
                    w[y3+2][x3-2]==thetwo && w[y3+3][x3-3]!=thetwo)
                   //3개 일때 대각왼아래 카운트
                wcnt3++;
            }
        }
        //백돌이 연속으로 4개 놓여져 있는 경우 카운트.
        for(int y4=0 ; y4<19 ; y4++)
        {
            for(int x4=0 ; x4<19 ; x4++)
            {
                if(w[y4][x4-1]!=thetwo && w[y4][x4]==thetwo && w[y4][x4+1]==thetwo &&
                    w[y4][x4+2]==thetwo && w[y4][x4+3]==thetwo && w[y4][x4+4]!=thetwo)
                    //4개일 때 열방향 카운트
                wcnt4++;
                if(w[y4-1][x4]!=thetwo && w[y4][x4]==thetwo && w[y4+1][x4]==thetwo &&
                    w[y4+2][x4]==thetwo && w[y4+3][x4]==thetwo&&w[y4+4][x4]!=thetwo)
                    //4개일 때 행방향 카운트
                wcnt4++;
                if(w[y4-1][x4-1]!=thetwo && w[y4][x4]==thetwo && w[y4+1][x4+1]==thetwo &&
                    w[y4+2][x4+2]==thetwo &&w[y4+3][x4+3]==thetwo&&w[y4+4][x4+4]!=thetwo)
                    //4개일 때 대각오른아래방향 카운트
                wcnt4++;
                if(w[y4-1][x4+1]!=thetwo && w[y4][x4]==thetwo && w[y4+1][x4-1]==thetwo &&
                    w[y4+2][x4-2]==thetwo && w[y4+3][x4-3]==thetwo && w[y4+4][x4-4]!=thetwo)
                    //4개일 때 대각왼아래방향 카운트
                wcnt4++;
            }
        }
        //백돌이 연속으로 5개 놓여져 있는 경우 카운트.
        for(int y5=0 ; y5<19 ; y5++)
        {
            for(int x5=0 ;  x5<19 ; x5++)
            {
                if(w[y5][x5-1]!=thetwo && w[y5][x5]==thetwo && w[y5][x5+1]==thetwo &&
                    w[y5][x5+2]==thetwo && w[y5][x5+3]==thetwo && w[y5][x5+4]==thetwo && w[y5][x5+5]!=thetwo)
                    //5개 일 때 열 방향 카운트
                wcnt5++;
                if(w[y5-1][x5]!=thetwo && w[y5][x5]==thetwo && w[y5+1][x5]==thetwo &&
                    w[y5+2][x5]==thetwo && w[y5+3][x5]==thetwo && w[y5+4][x5]==thetwo && w[y5+5][x5]!=thetwo)
                    //5개 일 때 행 방향 카운트
                wcnt5++;
                if(w[y5-1][x5-1]!=thetwo && w[y5][x5]==thetwo && w[y5+1][x5+1]==thetwo &&
                    w[y5+2][x5+2]==thetwo && w[y5+3][x5+3]==thetwo && w[y5+4][x5+4]==thetwo && w[y5+5][x5+5]!=thetwo)
                    //5개 일 때 대각선 오른쪽아래 방향 카운트
                wcnt5++;
                if(w[y5-1][x5+1]!=thetwo && w[y5][x5]==thetwo && w[y5+1][x5-1]==thetwo &&
                    w[y5+2][x5-2]==thetwo && w[y5+3][x5-3]==thetwo && w[y5+4][x5-4]==thetwo && w[y5+5][x5-5]!=thetwo)
                        //5개 일 때 대각선 왼쪽아래 방향 카운트
                wcnt5++;
            }
        }

}

void AI::prn()
{
    bsituation();
    wsituation();
}

void AI::insertAI_W(GAME_DATA gamedata)
{   //TYPE_CIRCLE:흑돌 , TYPE_CROSS//백돌
    if ((this->type==TYPE_EMPTY) && parentPtr->game && this->parentPtr->AImode[1]==1 && this->parentPtr->activeType==TYPE_CROSS){
        switch (parentPtr->gameType){//로컬,서버,클라이언트모드
            case Board::TYPE_LOCAL:
                //받을 정보
                this->x = gamedata.x; //wy or wx
                this->y = gamedata.y;
                this->parentPtr->addItem (this->x, this->y);
                break;

            case Board::TYPE_SERVER:
                if ((int)parentPtr->activeType==(int)Board::TYPE_SERVER){
                    this->x = gamedata.x; //y or x
                    this->y = gamedata.y;
                    this->parentPtr->server->writeToClient("200 "+QString::number(this->x)+" "+QString::number(this->y)+"\n");
                    this->parentPtr->addItem (this->x, this->y);
                }
                break;

            case Board::TYPE_CLIENT:
                if ((int)this->parentPtr->activeType==(int)Board::TYPE_CLIENT){
                    this->x = gamedata.x; //y or x
                    this->y = gamedata.y;
                    this->parentPtr->client->writeToServer ("200 "+QString::number(this->x)+" "+QString::number(this->y)+"\n");
                    this->parentPtr->addItem (this->x, this->y);
                }
                break;
            }
            w[this->x][this->y]=2;
    }

}

void AI::insertAI_B(GAME_DATA gamedata)
{
    //TYPE_CIRCLE:흑돌 , TYPE_CROSS//백돌
        if ((this->type==TYPE_EMPTY) && parentPtr->game && this->parentPtr->AImode[0]==1 && this->parentPtr->activeType==TYPE_CIRCLE){
            switch (parentPtr->gameType){//로컬,서버,클라이언트모드
                case Board::TYPE_LOCAL:
                    //받을 정보
                    this->x = gamedata.x; //y or x
                    this->y = gamedata.y;
                    this->parentPtr->addItem (this->x, this->y);
                    break;

                case Board::TYPE_SERVER:
                    if ((int)parentPtr->activeType==(int)Board::TYPE_SERVER){
                        this->x = gamedata.x; //y or x
                        this->y = gamedata.y;
                        this->parentPtr->server->writeToClient("200 "+QString::number(this->x)+" "+QString::number(this->y)+"\n");
                        this->parentPtr->addItem (this->x, this->y);
                    }
                    break;

                case Board::TYPE_CLIENT:
                    if ((int)this->parentPtr->activeType==(int)Board::TYPE_CLIENT){
                        this->x = gamedata.x; //y or x
                        this->y = gamedata.y;
                        this->parentPtr->client->writeToServer ("200 "+QString::number(this->x)+" "+QString::number(this->y)+"\n");
                        this->parentPtr->addItem (this->x, this->y);
                    }
                    break;
                }
                b[this->x][this->y]=2;
        }

}



void AI::W_AI_allcheck()
{
    for(int x_new=0; x_new<19; x_new++) // 모든 가중치배열좌표값을 0으로 초기화
        {
            for(int y_new=0; y_new<19; y_new++)
            {
                act2[x_new][y_new] = 0;		//가중치배열 0으로 초기화.
                if( w[x_new][y_new] == 2 )
                {
                    newblack[x_new][y_new] = 2;
                }
                if( b[x_new][y_new] == 1 )
                {
                    newblack[x_new][y_new] = 1;
                }
                else;
            }
        }
    W_AI_5_6_7_check();

        defense_garo_check_W();
        defense_sero_check_W();
        defense_slash_check_W();
        defense_in_slash_check_W();

        W_AI_2_garo_check();
        W_AI_3_garo_check();
        W_AI_4_garo_check();

        W_AI_2_sero_check();
        W_AI_3_sero_check();
        W_AI_4_sero_check();

        W_AI_2_slash_check();
        W_AI_3_slash_check();
        W_AI_4_slash_check();

        W_AI_2_in_slash_check();
        W_AI_3_in_slash_check();
        W_AI_4_in_slash_check();

        for(int x=0; x<19; x++)
        {
            for(int y=0; y<19; y++)
            {
                if(b[x][y] ==1 || w[x][y] == 2)
                {
                    act[x][y] = 0;
                }
            }
        }

        maxactpnt = 0;


        for(int max_x=0; max_x<19; max_x++) // 최대 가중치 찾기
        {
            for(int max_y=0; max_y<19; max_y++)
            {
                if(maxactpnt < act[max_x][max_y])
                {
                    maxactpnt = act[max_x][max_y];
                    wx = max_x;
                    wy = max_y;
                }
                //같은점수일때 랜덤으로 놓게함. 일단문제없어보임.
                else if(maxactpnt == act[max_x][max_y])
                {
                    srand((unsigned)time(NULL));
                    int random = rand()%2;
                    if(random == 0)
                    {
                        maxactpnt = act[max_x][max_y];
                        wx = max_x;
                        wy = max_y;
                    }
                    else;
                }
                else;
            }
        }
        w[wx][wy] = 2;
}


void AI::W_AI_5_6_7_check()
{
    for(int m=0 ; m<19 ; m++)
        {
          for(int n=0 ; n<19 ; n++)
          {
              if( newwhite[m][n] == 0 )
              {
              newwhite[m][n] = 2;
              }
              else if( newwhite[m][n] == 1 || newwhite[m][n] == 2 )
              {
                  continue;
              }

              for(int x=0; x<19; x++)
              {
                  for(int y=0; y<19; y++)
                  {

                if(turn == 1)	//첫 번째 턴일때만 적용되는 함수. 4개를 5개로 만들거나 4개가있으면 한쪽을 막음.
                {				//단 이길수있는상황에만 4개를 5개로 만들게함.
                                //X 는 !2 이다. 즉 2가 아니라고 명시한 것.
                    //첫째턴, 6개까지 만들 여지가 있을 경우 & 가로
                    if( newwhite[x][y] == 0 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 2 && newwhite[x][y+3] == 2 && newwhite[x][y+4] == 2 &&
                        newwhite[x][y+5] == 2 )
                        act[m][n] += 45000000;	//022222
                    if( newwhite[x][y] == 2 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 2 && newwhite[x][y+3] == 2 && newwhite[x][y+4] == 2 &&
                        newwhite[x][y+5] == 0 )
                        act[m][n] += 45000000;  //222220
                    if( newwhite[x][y] == 2 && newwhite[x][y+1] == 0 && newwhite[x][y+2] == 2 && newwhite[x][y+3] == 2 && newwhite[x][y+4] == 2 &&
                        newwhite[x][y+5] == 2 )
                        act[m][n] += 45000000;	//202222
                    if( newwhite[x][y] == 2 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 2 && newwhite[x][y+3] == 2 && newwhite[x][y+4] == 0 &&
                        newwhite[x][y+5] == 2 )
                        act[m][n] += 45000000;	//222202
                    if( newwhite[x][y] == 2 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 0 && newwhite[x][y+3] == 2 && newwhite[x][y+4] == 2 &&
                        newwhite[x][y+5] == 2 )
                        act[m][n] += 45000000;	//220222
                    if( newwhite[x][y] == 2 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 2 && newwhite[x][y+3] == 0 && newwhite[x][y+4] == 2 &&
                        newwhite[x][y+5] == 2 )
                        act[m][n] += 45000000;	//222022

                    //첫째턴, 6개까지 만들 여지가 있을 경우 & 세로
                    if( newwhite[x][y] == 0 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 2 && newwhite[x+3][y] == 2 && newwhite[x+4][y] == 2 &&
                        newwhite[x+5][y] == 2 )
                        act[m][n] += 45000000;	//022222
                    if( newwhite[x][y] == 2 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 2 && newwhite[x+3][y] == 2 && newwhite[x+4][y] == 2 &&
                        newwhite[x+5][y] == 0 )
                        act[m][n] += 45000000;  //222220
                    if( newwhite[x][y] == 2 && newwhite[x+1][y] == 0 && newwhite[x+2][y] == 2 && newwhite[x+3][y] == 2 && newwhite[x+4][y] == 2 &&
                        newwhite[x+5][y] == 2 )
                        act[m][n] += 45000000;	//202222
                    if( newwhite[x][y] == 2 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 2 && newwhite[x+3][y] == 2 && newwhite[x+4][y] == 0 &&
                        newwhite[x+5][y] == 2 )
                        act[m][n] += 45000000;	//222202
                    if( newwhite[x][y] == 2 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 0 && newwhite[x+3][y] == 2 && newwhite[x+4][y] == 2 &&
                        newwhite[x+5][y] == 2 )
                        act[m][n] += 45000000;	//220222
                    if( newwhite[x][y] == 2 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 2 && newwhite[x+3][y] == 0 && newwhite[x+4][y] == 2 &&
                        newwhite[x+5][y] == 2 )
                        act[m][n] += 45000000;	//222022

                    //첫째턴, 6개까지 만들 여지가 있을 경우 & 대각선
                    if( newwhite[x][y] == 0 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 2 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] == 2 &&
                        newwhite[x+5][y+5] == 2 )
                        act[m][n] += 45000000;	//022222
                    if( newwhite[x][y] == 2 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 2 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] == 2 &&
                        newwhite[x+5][y+5] == 0 )
                        act[m][n] += 45000000;  //222220
                    if( newwhite[x][y] == 2 && newwhite[x+1][y+1] == 0 && newwhite[x+2][y+2] == 2 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] == 2 &&
                        newwhite[x+5][y+5] == 2 )
                        act[m][n] += 45000000;	//202222
                    if( newwhite[x][y] == 2 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 2 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] == 0 &&
                        newwhite[x+5][y+5] == 2 )
                        act[m][n] += 45000000;	//222202
                    if( newwhite[x][y] == 2 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 0 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] == 2 &&
                        newwhite[x+5][y+5] == 2 )
                        act[m][n] += 45000000;	//220222
                    if( newwhite[x][y] == 2 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 2 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] == 2 &&
                        newwhite[x+5][y+5] == 2 )
                        act[m][n] += 45000000;	//222022

                    //첫째턴, 6개까지 만들 여지가 있을 경우 & 역대각선
                    if( newwhite[x][y] == 0 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 2 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] == 2 &&
                        newwhite[x+5][y-5] == 2 )
                        act[m][n] += 45000000;	//022222
                    if( newwhite[x][y] == 2 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 2 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] == 2 &&
                        newwhite[x+5][y-5] == 0 )
                        act[m][n] += 45000000;  //222220
                    if( newwhite[x][y] == 2 && newwhite[x+1][y-1] == 0 && newwhite[x+2][y-2] == 2 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] == 2 &&
                        newwhite[x+5][y-5] == 2 )
                        act[m][n] += 45000000;	//202222
                    if( newwhite[x][y] == 2 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 2 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] == 0 &&
                        newwhite[x+5][y-5] == 2 )
                        act[m][n] += 45000000;	//222202
                    if( newwhite[x][y] == 2 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 0 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] == 2 &&
                        newwhite[x+5][y-5] == 2 )
                        act[m][n] += 45000000;	//220222
                    if( newwhite[x][y] == 2 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 2 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] == 2 &&
                        newwhite[x+5][y-5] == 2 )
                        act[m][n] += 45000000;	//222022
                }
                //1222221
                if( newwhite[x][y] == 1 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 2 && newwhite[x][y+3] == 2 && newwhite[x][y+4] == 2 &&
                    newwhite[x][y+5] == 2 && newwhite[x][y+6] == 1 )
                    act[m][n] = 0;
                if( newwhite[x][y] == 1 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 2 && newwhite[x+3][y] == 2 && newwhite[x+4][y] == 2 &&
                    newwhite[x+5][y] == 2 && newwhite[x+6][y] == 1 )
                    act[m][n] = 0;
                if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 2 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] == 2 &&
                    newwhite[x+5][y+5] == 2 && newwhite[x+6][y+6] == 1 )
                    act[m][n] = 0;
                if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 2 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] == 2 &&
                    newwhite[x+5][y-5] == 2 && newwhite[x+6][y-6] == 1 )
                    act[m][n] = 0;
                                //양쪽다막힌 양쪽모두 막힌 곳에 돌을 5개로 만드는 것은 점수필요없음.
                //222222가로로 이길수있을때
                if( newwhite[x][y] == 2 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 2 && newwhite[x][y+3] == 2 && newwhite[x][y+4] == 2 &&
                    newwhite[x][y+5] == 2 )
                    act[m][n] += 99999999;
                //세로로 이길수있을때
                if( newwhite[x][y] == 2 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 2 && newwhite[x+3][y] == 2 && newwhite[x+4][y] == 2 &&
                    newwhite[x+5][y] == 2 )
                    act[m][n] += 99999999;
                //대각선으로 이길수있을때
                if( newwhite[x][y] == 2 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 2 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] == 2 &&
                    newwhite[x+5][y+5] == 2 )
                    act[m][n] += 99999999;
                if( newwhite[x][y] == 2 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 2 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] == 2 &&
                    newwhite[x+5][y-5] == 2 )
                    act[m][n] += 99999999;
                  }
              }
              newwhite[m][n] = 0;
          }
        }

}

void AI::W_AI_2_garo_check()
{
    for(int m=0 ; m<19 ; m++)
        {
          for(int n=0 ; n<19 ; n++)
          {
              if( newwhite[m][n] == 0 )
              {
              newwhite[m][n] = 2;
              }
              else if( newwhite[m][n] == 1 || newwhite[m][n] == 2 )
              {
                  continue;
              }

              for(int x=0; x<19; x++)
              {
                  for(int y=0; y<19; y++)
                  {
                //00022000
                if( newwhite[x][y-2] == 0 && newwhite[x][y-1] == 0 && newwhite[x][y] == 0 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 2 &&
                    newwhite[x][y+3] == 0 && newwhite[x][y+4] == 0 && newwhite[x][y+5] == 0 )
                    act[m][n] += 2000;
                //0020200
                if( newwhite[x][y-1] == 0 && newwhite[x][y] == 0 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 0 && newwhite[x][y+3] == 2 && newwhite[x][y+4] == 0 &&
                    newwhite[x][y+5] == 0 )
                    act[m][n] += 1500;
                //020020
                if( newwhite[x][y] == 0 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 0 && newwhite[x][y+3] == 0 && newwhite[x][y+4] == 2 && newwhite[x][y+5] == 0 )
                    act[m][n] += 1000;
                //여기까지 양쪽에 안 막힌, 흰 돌이 2개가 발견 될 때 경우의 수들

                //122000
                if( newwhite[x][y] == 1 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 2 && newwhite[x][y+3] == 0 && newwhite[x][y+4] == 0 && newwhite[x][y+5] == 0 )
                    act[m][n] += 500;
                //120200
                if( newwhite[x][y] == 1 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 0 && newwhite[x][y+3] == 2 && newwhite[x][y+4] == 0 && newwhite[x][y+5] == 0 )
                    act[m][n] += 500;
                //120020
                if( newwhite[x][y] == 1 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 0 && newwhite[x][y+3] == 0 && newwhite[x][y+4] == 2 && newwhite[x][y+5] == 0 )
                    act[m][n] += 500;
                //102200
                if( newwhite[x][y] == 1 && newwhite[x][y+1] == 0 && newwhite[x][y+2] == 2 && newwhite[x][y+3] == 2 && newwhite[x][y+4] == 0 && newwhite[x][y+5] == 0 )
                    act[m][n] += 800;
                //102020
                if( newwhite[x][y] == 1 && newwhite[x][y+1] == 0 && newwhite[x][y+2] == 2 && newwhite[x][y+3] == 0 && newwhite[x][y+4] == 2 && newwhite[x][y+5] == 0 )
                    act[m][n] += 800;
                //여기까지 왼쪽에 검은돌로 막힌 경우.
                //오른쪽에 검은돌로 막힌 경우는 이 대칭으로만 작성해주면됌

                //000221
                if( newwhite[x][y-2] == 0 && newwhite[x][y-1] == 0 && newwhite[x][y] == 0 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 2 && newwhite[x][y+3] == 1 )
                    act[m][n] += 500;
                //002021
                if( newwhite[x][y-1] == 0 && newwhite[x][y] == 0 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 0 && newwhite[x][y+3] == 2 && newwhite[x][y+4] == 1 )
                    act[m][n] += 500;
                //020021
                if( newwhite[x][y] == 0 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 0 && newwhite[x][y+3] == 0 && newwhite[x][y+4] == 2 && newwhite[x][y+5] == 1 )
                    act[m][n] += 500;
                //002201
                if( newwhite[x][y-1] == 0 && newwhite[x][y] == 0 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 2 && newwhite[x][y+3] == 0 && newwhite[x][y+4] == 1 )
                    act[m][n] += 800;
                //020201
                if( newwhite[x][y] == 0 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 0 && newwhite[x][y+3] == 2 && newwhite[x][y+4] == 0 && newwhite[x][y+5] == 1 )
                    act[m][n] += 800;
                //여기까지 한쪽이 막힌 경우.
                //그 다음은 양쪽이 막힌 경우. 양쪽이 막힌 경우는 안이 6칸일 경우만 따지자.

                //12200001
                if( newwhite[x][y] == 1 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 2 && newwhite[x][y+3] == 0 && newwhite[x][y+4] == 0 && newwhite[x][y+5] == 0 &&
                    newwhite[x][y+6] == 0 && newwhite[x][y+7] == 1 )
                    act[m][n] += 300;
                //12020001
                if( newwhite[x][y] == 1 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 0 && newwhite[x][y+3] == 2 && newwhite[x][y+4] == 0 && newwhite[x][y+5] == 0 &&
                    newwhite[x][y+6] == 0 && newwhite[x][y+7] == 1 )
                    act[m][n] += 300;
                //12002001
                if( newwhite[x][y] == 1 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 0 && newwhite[x][y+3] == 0 && newwhite[x][y+4] == 2 && newwhite[x][y+5] == 0 &&
                    newwhite[x][y+6] == 0 && newwhite[x][y+7] == 1 )
                    act[m][n] += 300;
                //12000201
                if( newwhite[x][y] == 1 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 0 && newwhite[x][y+3] == 0 && newwhite[x][y+4] == 0 && newwhite[x][y+5] == 2 &&
                    newwhite[x][y+6] == 0 && newwhite[x][y+7] == 1 )
                    act[m][n] += 300;
                //12000021
                if( newwhite[x][y] == 1 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 0 && newwhite[x][y+3] == 0 && newwhite[x][y+4] == 0 && newwhite[x][y+5] == 0 &&
                    newwhite[x][y+6] == 2 && newwhite[x][y+7] == 1 )
                    act[m][n] += 300;
                //10220001
                if( newwhite[x][y] == 1 && newwhite[x][y+1] == 0 && newwhite[x][y+2] == 2 && newwhite[x][y+3] == 2 && newwhite[x][y+4] == 0 && newwhite[x][y+5] == 0 &&
                    newwhite[x][y+6] == 0 && newwhite[x][y+7] == 1 )
                    act[m][n] += 300;
                //10202001
                if( newwhite[x][y] == 1 && newwhite[x][y+1] == 0 && newwhite[x][y+2] == 2 && newwhite[x][y+3] == 0 && newwhite[x][y+4] == 2 && newwhite[x][y+5] == 0 &&
                    newwhite[x][y+6] == 0 && newwhite[x][y+7] == 1 )
                    act[m][n] += 300;
                //10200201
                if( newwhite[x][y] == 1 && newwhite[x][y+1] == 0 && newwhite[x][y+2] == 2 && newwhite[x][y+3] == 0 && newwhite[x][y+4] == 0 && newwhite[x][y+5] == 2 &&
                    newwhite[x][y+6] == 0 && newwhite[x][y+7] == 1 )
                    act[m][n] += 300;
                //10200021
                if( newwhite[x][y] == 1 && newwhite[x][y+1] == 0 && newwhite[x][y+2] == 2 && newwhite[x][y+3] == 0 && newwhite[x][y+4] == 0 && newwhite[x][y+5] == 0 &&
                    newwhite[x][y+6] == 2 && newwhite[x][y+7] == 1 )
                    act[m][n] += 300;
                //10022001
                if( newwhite[x][y] == 1 && newwhite[x][y+1] == 0 && newwhite[x][y+2] == 0 && newwhite[x][y+3] == 2 && newwhite[x][y+4] == 2 && newwhite[x][y+5] == 0 &&
                    newwhite[x][y+6] == 0 && newwhite[x][y+7] == 1 )
                    act[m][n] += 300;
                //10020201
                if( newwhite[x][y] == 1 && newwhite[x][y+1] == 0 && newwhite[x][y+2] == 0 && newwhite[x][y+3] == 2 && newwhite[x][y+4] == 0 && newwhite[x][y+5] == 2 &&
                    newwhite[x][y+6] == 0 && newwhite[x][y+7] == 1 )
                    act[m][n] += 300;
                //10020021
                if( newwhite[x][y] == 1 && newwhite[x][y+1] == 0 && newwhite[x][y+2] == 0 && newwhite[x][y+3] == 2 && newwhite[x][y+4] == 0 && newwhite[x][y+5] == 0 &&
                    newwhite[x][y+6] == 2 && newwhite[x][y+7] == 1 )
                    act[m][n] += 300;
                //10002201
                if( newwhite[x][y] == 1 && newwhite[x][y+1] == 0 && newwhite[x][y+2] == 0 && newwhite[x][y+3] == 0 && newwhite[x][y+4] == 2 && newwhite[x][y+5] == 2 &&
                    newwhite[x][y+6] == 0 && newwhite[x][y+7] == 1 )
                    act[m][n] += 300;
                //10002021
                if( newwhite[x][y] == 1 && newwhite[x][y+1] == 0 && newwhite[x][y+2] == 0 && newwhite[x][y+3] == 2 && newwhite[x][y+4] == 0 && newwhite[x][y+5] == 2 &&
                    newwhite[x][y+6] == 0 && newwhite[x][y+7] == 1 )
                    act[m][n] += 300;
                //10000221
                if( newwhite[x][y] == 1 && newwhite[x][y+1] == 0 && newwhite[x][y+2] == 0 && newwhite[x][y+3] == 0 && newwhite[x][y+4] == 0 && newwhite[x][y+5] == 2 &&
                    newwhite[x][y+6] == 2 && newwhite[x][y+7] == 1 )
                    act[m][n] += 300;
                  }
              }
              newwhite[m][n] = 0;
          }
        }

}

void AI::W_AI_3_garo_check()
{
    for(int m=0 ; m<19 ; m++)
        {
          for(int n=0 ; n<19 ; n++)
          {
              if( newwhite[m][n] == 0 )
              {
              newwhite[m][n] = 2;
              }
              else if( newwhite[m][n] == 1 || newwhite[m][n] == 2 )
              {
                  continue;
              }

              for(int x=0; x<19; x++)
              {
                  for(int y=0; y<19; y++)
                  {
                //000222000
                if( newwhite[x][y-1] == 0 && newwhite[x][y] == 0 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 2 && newwhite[x][y+3] == 2&& newwhite[x][y+4]==0 &&
                    newwhite[x][y+5] == 0 )
                    act[m][n] += 5000;
                //00202200
                if( newwhite[x][y-1] == 0 && newwhite[x][y] == 0 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 0 && newwhite[x][y+3] == 2 && newwhite[x][y+4] == 2 &&
                    newwhite[x][y+5]==0 && newwhite[x][y+6] == 0 )
                    act[m][n] += 3500;
                //00220200
                if( newwhite[x][y-1] == 0 && newwhite[x][y] == 0 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 2 && newwhite[x][y+3] == 0 && newwhite[x][y+4] == 2 &&
                    newwhite[x][y+5] == 0 && newwhite[x][y+6] == 0 )
                    act[m][n] += 3500;
                //0200220
                if( newwhite[x][y] == 0 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 0 && newwhite[x][y+3] == 0 && newwhite[x][y+4] == 2 && newwhite[x][y+5] == 2
                    &&newwhite[x][y+6] ==0 )
                    act[m][n] += 3000;
                //0202020
                if( newwhite[x][y] == 0 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 0 && newwhite[x][y+3] == 2 && newwhite[x][y+4] == 0 && newwhite[x][y+5] == 2
                    &&newwhite[x][y+6]==0 )
                    act[m][n] += 3000;
                //0220020
                if( newwhite[x][y] == 0 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 2 && newwhite[x][y+3] == 0 && newwhite[x][y+4] == 0 && newwhite[x][y+5] == 2
                    && newwhite[x][y+6] ==0 )
                    act[m][n] += 3000;
                //여기까지 양쪽에 안 막힌, 흰 돌이 2개가 발견 될 때 경우의 수들

                //122200
                if( newwhite[x][y] == 1 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 2 && newwhite[x][y+3] == 2 && newwhite[x][y+4] ==0 && newwhite[x][y+5] == 0 )
                    act[m][n] += 1000;
                //1202200
                if( newwhite[x][y] == 1 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 0 && newwhite[x][y+3] == 2 && newwhite[x][y+4] == 2 && newwhite[x][y+5] ==0 &&
                    newwhite[x][y+6] == 0 )
                    act[m][n] += 1000;
                //1220200
                if( newwhite[x][y] == 1 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 2 && newwhite[x][y+3] == 0 && newwhite[x][y+4] == 2 && newwhite[x][y+5] == 0 &&
                    newwhite[x][y+6] == 0 )
                    act[m][n] += 1000;
                //1022200
                if( newwhite[x][y] == 1 && newwhite[x][y+1] == 0 && newwhite[x][y+2] == 2 && newwhite[x][y+3] == 2 && newwhite[x][y+4] == 2 && newwhite[x][y+5] ==0 &&
                    newwhite[x][y+6] == 0 )
                    act[m][n] += 1300;
                //1200220
                if( newwhite[x][y] == 1 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 0 && newwhite[x][y+3] == 0 && newwhite[x][y+4] == 2 && newwhite[x][y+5] == 2 &&
                newwhite[x][y+6] ==0 )
                    act[m][n] += 1300;
                //1220020
                if( newwhite[x][y] == 1 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 2 && newwhite[x][y+3] == 0 && newwhite[x][y+4] == 0 && newwhite[x][y+5] == 2 &&
                    newwhite[x][y+6] == 0 )
                    act[m][n] += 1000;
                //1202020
                if( newwhite[x][y] == 1 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 0 && newwhite[x][y+3] == 2 && newwhite[x][y+4] == 0 && newwhite[x][y+5] == 2 &&
                    newwhite[x][y+6] ==0 )
                    act[m][n] += 1000;
                //1020220
                if( newwhite[x][y] == 1 && newwhite[x][y+1] == 0 && newwhite[x][y+2] == 2 && newwhite[x][y+3] == 0 && newwhite[x][y+4] == 2 && newwhite[x][y+5] == 2 &&
                    newwhite[x][y+6] == 0)
                    act[m][n] += 1300;

                //여기까지 왼쪽에 검은돌로 막힌 경우.
                //오른쪽에 검은돌로 막힌 경우는 이 대칭으로만 작성해주면됌

                //002221
                if( newwhite[x][y-1] == 0 && newwhite[x][y] == 0 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 2 && newwhite[x][y+3] == 2 && newwhite[x][y+4] == 1 )
                    act[m][n] += 1000;
                //0022021
                if( newwhite[x][y-1] == 0 && newwhite[x][y] == 0 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 2 && newwhite[x][y+3] == 0 && newwhite[x][y+4] == 2 &&
                    newwhite[x][y+5]==1 )
                    act[m][n] += 1000;
                //0020221
                if( newwhite[x][y-1] == 0 && newwhite[x][y] == 0 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 0 && newwhite[x][y+3] == 2 && newwhite[x][y+4] == 2 &&
                    newwhite[x][y+5] == 1 )
                    act[m][n] += 1000;
                //0022201
                if( newwhite[x][y-1] == 0 && newwhite[x][y] == 0 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 2 && newwhite[x][y+3] == 2 && newwhite[x][y+4] == 0 &&
                    newwhite[x][y+5] == 1 )
                    act[m][n] += 1300;
                //0220021
                if( newwhite[x][y] == 0 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 2 && newwhite[x][y+3] == 0 && newwhite[x][y+4] == 0 && newwhite[x][y+5] == 2 &&
                    newwhite[x][y+6] == 1 )
                    act[m][n] += 1300;
                //0200221
                if( newwhite[x][y] == 0 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 0 && newwhite[x][y+3] == 0 && newwhite[x][y+4] == 2 && newwhite[x][y+5] == 2 &&
                    newwhite[x][y+6] == 1 )
                    act[m][n] += 1000;
                //0202021
                if( newwhite[x][y] == 0 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 0 && newwhite[x][y+3] == 2 && newwhite[x][y+4] == 0 && newwhite[x][y+5] == 2 &&
                    newwhite[x][y+6] == 1 )
                    act[m][n] += 1000;
                //0220201
                if( newwhite[x][y] == 0 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 2 && newwhite[x][y+3] == 0 && newwhite[x][y+4] == 2 && newwhite[x][y+5] == 0 &&
                    newwhite[x][y+6] == 1 )
                    act[m][n] += 1300;

                //여기까지 한쪽이 막힌 경우.
                //그 다음은 양쪽이 막힌 경우. 양쪽이 막힌 경우는 안이 6칸일 경우만 따지자.

                //12220001
                if( newwhite[x][y] == 1 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 2 && newwhite[x][y+3] == 2 && newwhite[x][y+4] == 0 && newwhite[x][y+5] == 0 &&
                    newwhite[x][y+6] == 0 && newwhite[x][y+7] == 1 )
                    act[m][n] += 300;
                //12022001
                if( newwhite[x][y] == 1 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 0 && newwhite[x][y+3] == 2 && newwhite[x][y+4] == 2 && newwhite[x][y+5] == 0 &&
                    newwhite[x][y+6] == 0 && newwhite[x][y+7] == 1 )
                    act[m][n] += 300;
                //12002201
                if( newwhite[x][y] == 1 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 0 && newwhite[x][y+3] == 0 && newwhite[x][y+4] == 2 && newwhite[x][y+5] == 2 &&
                    newwhite[x][y+6] == 0 && newwhite[x][y+7] == 1 )
                    act[m][n] += 300;
                //12000221
                if( newwhite[x][y] == 1 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 0 && newwhite[x][y+3] == 0 && newwhite[x][y+4] == 0 && newwhite[x][y+5] == 2 &&
                    newwhite[x][y+6] == 2 && newwhite[x][y+7] == 1 )
                    act[m][n] += 300;
                //12202001
                if( newwhite[x][y] == 1 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 2 && newwhite[x][y+3] == 0 && newwhite[x][y+4] == 2 && newwhite[x][y+5] == 0 &&
                    newwhite[x][y+6] == 0 && newwhite[x][y+7] == 1 )
                    act[m][n] += 300;
                //12200201
                if( newwhite[x][y] == 1 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 2 && newwhite[x][y+3] == 0 && newwhite[x][y+4] == 0 && newwhite[x][y+5] == 2 &&
                    newwhite[x][y+6] == 0 && newwhite[x][y+7] == 1 )
                    act[m][n] += 300;
                //12200021
                if( newwhite[x][y] == 1 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 2 && newwhite[x][y+3] == 0 && newwhite[x][y+4] == 0 && newwhite[x][y+5] == 0 &&
                    newwhite[x][y+6] == 2 && newwhite[x][y+7] == 1 )
                    act[m][n] += 300;
                //12002021
                if( newwhite[x][y] == 1 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 0 && newwhite[x][y+3] == 0 && newwhite[x][y+4] == 2 && newwhite[x][y+5] == 0 &&
                    newwhite[x][y+6] == 2 && newwhite[x][y+7] == 1 )
                    act[m][n] += 300;
                //12020021
                if( newwhite[x][y] == 1 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 0 && newwhite[x][y+3] == 2 && newwhite[x][y+4] == 0 && newwhite[x][y+5] == 0 &&
                    newwhite[x][y+6] == 2 && newwhite[x][y+7] == 1 )
                    act[m][n] += 300;
                //12020201
                if( newwhite[x][y] == 1 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 0 && newwhite[x][y+3] == 2 && newwhite[x][y+4] == 0 && newwhite[x][y+5] == 2 &&
                    newwhite[x][y+6] == 0 && newwhite[x][y+7] == 1 )
                    act[m][n] += 300;
                //10222001
                if( newwhite[x][y] == 1 && newwhite[x][y+1] == 0 && newwhite[x][y+2] == 2 && newwhite[x][y+3] == 2 && newwhite[x][y+4] == 2 && newwhite[x][y+5] == 0 &&
                    newwhite[x][y+6] == 0 && newwhite[x][y+7] == 1 )
                    act[m][n] += 300;
                //10202201
                if( newwhite[x][y] == 1 && newwhite[x][y+1] == 0 && newwhite[x][y+2] == 2 && newwhite[x][y+3] == 0 && newwhite[x][y+4] == 2 && newwhite[x][y+5] == 2 &&
                    newwhite[x][y+6] == 0 && newwhite[x][y+7] == 1 )
                    act[m][n] += 300;
                //10200221
                if( newwhite[x][y] == 1 && newwhite[x][y+1] == 0 && newwhite[x][y+2] == 2 && newwhite[x][y+3] == 0 && newwhite[x][y+4] == 0 && newwhite[x][y+5] == 2 &&
                    newwhite[x][y+6] == 2 && newwhite[x][y+7] == 1 )
                    act[m][n] += 300;
                //10220201
                if( newwhite[x][y] == 1 && newwhite[x][y+1] == 0 && newwhite[x][y+2] == 2 && newwhite[x][y+3] == 2 && newwhite[x][y+4] == 0 && newwhite[x][y+5] == 2 &&
                    newwhite[x][y+6] == 0 && newwhite[x][y+7] == 1 )
                    act[m][n] += 300;
                //10220021
                if( newwhite[x][y] == 1 && newwhite[x][y+1] == 0 && newwhite[x][y+2] == 2 && newwhite[x][y+3] == 2 && newwhite[x][y+4] == 0 && newwhite[x][y+5] == 0 &&
                    newwhite[x][y+6] == 2 && newwhite[x][y+7] == 1 )
                    act[m][n] += 300;
                //10022021
                if( newwhite[x][y] == 1 && newwhite[x][y+1] == 0 && newwhite[x][y+2] == 0 && newwhite[x][y+3] == 2 && newwhite[x][y+4] == 2 && newwhite[x][y+5] == 0 &&
                    newwhite[x][y+6] == 2 && newwhite[x][y+7] == 1 )
                    act[m][n] += 300;
                //10022201
                if( newwhite[x][y] == 1 && newwhite[x][y+1] == 0 && newwhite[x][y+2] == 0 && newwhite[x][y+3] == 2 && newwhite[x][y+4] == 2 && newwhite[x][y+5] == 2 &&
                    newwhite[x][y+6] == 0 && newwhite[x][y+7] == 1 )
                    act[m][n] += 300;
                //10020221
                if( newwhite[x][y] == 1 && newwhite[x][y+1] == 0 && newwhite[x][y+2] == 0 && newwhite[x][y+3] == 2 && newwhite[x][y+4] == 0 && newwhite[x][y+5] == 2 &&
                    newwhite[x][y+6] == 2 && newwhite[x][y+7] == 1 )
                    act[m][n] += 300;
                //10002221
                if( newwhite[x][y] == 1 && newwhite[x][y+1] == 0 && newwhite[x][y+2] == 0 && newwhite[x][y+3] == 0 && newwhite[x][y+4] == 0 && newwhite[x][y+5] == 2 &&
                    newwhite[x][y+6] == 2 && newwhite[x][y+7] == 1 )
                    act[m][n] += 300;
                //10202021
                if( newwhite[x][y] == 1 && newwhite[x][y+1] == 0 && newwhite[x][y+2] == 2 && newwhite[x][y+3] == 0 && newwhite[x][y+4] == 2 && newwhite[x][y+5] == 0 &&
                    newwhite[x][y+6] == 2 && newwhite[x][y+7] == 1 )
                    act[m][n] += 300;
                    }
              }
              newwhite[m][n] = 0;
          }
        }

}

void AI::W_AI_4_garo_check()
{
    for(int m=0 ; m<19 ; m++)
        {
          for(int n=0 ; n<19 ; n++)
          {
              if( newwhite[m][n] == 0 )
              {
              newwhite[m][n] = 2;
              }
              else if( newwhite[m][n] == 1 || newwhite[m][n] == 2 )
              {
                  continue;
              }

              for(int x=0; x<19; x++)
              {
                  for(int y=0; y<19; y++)
                  {
       /*4개 -> 안막혔을 때*/
             //00222200
             if( newwhite[x][y-1] == 0 && newwhite[x][y]== 0 && newwhite[x][y+1]== 2 && newwhite[x][y+2]== 2 &&newwhite[x][y+3] == 2 && newwhite[x][y+4] == 2 &&
                 newwhite[x][y+5] == 0 )
                act[m][n] += 10000;
             //002022200
             if( newwhite[x][y-1] == 0 && newwhite[x][y]==0 && newwhite[x][y+1]==2 && newwhite[x][y+2]==0 && newwhite[x][y+3] == 2 && newwhite[x][y+4] ==2 &&
                 newwhite[x][y+5]==2 &&newwhite[x][y+6] ==0 && newwhite[x][y+7] == 0 )
                act[m][n] += 7000;
             //002220200
             if( newwhite[x][y-1] == 0 && newwhite[x][y]== 0 && newwhite[x][y+1]== 2 && newwhite[x][y+2]== 2 && newwhite[x][y+3] == 2 && newwhite[x][y+4] == 0 &&
                 newwhite[x][y+5] ==2 &&newwhite[x][y+6] == 0 && newwhite[x][y+7] == 0 )
                act[m][n] += 7000;
             //002202200
             if( newwhite[x][y-1] == 0 && newwhite[x][y]== 0 && newwhite[x][y+1]== 2 && newwhite[x][y+2]== 2 && newwhite[x][y+3] == 0 && newwhite[x][y+4] == 2 &&
                 newwhite[x][y+5] == 2 && newwhite[x][y+6] == 0 && newwhite[x][y+7] == 0 )
                act[m][n] += 7000;
             //02220020
             if( newwhite[x][y]==0 && newwhite[x][y+1]==2 && newwhite[x][y+2]==2 && newwhite[x][y+3] == 2 && newwhite[x][y+4] ==0 && newwhite[x][y+5] ==0 &&
                 newwhite[x][y+6] ==2 && newwhite[x][y+7] ==0 )
                act[m][n] += 5000;
             //02002220
             if( newwhite[x][y] == 0 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 0 && newwhite[x][y+3] == 0 && newwhite[x][y+4] == 2 && newwhite[x][y+5] == 2 &&
                 newwhite[x][y+6] == 2 && newwhite[x][y+7] == 0 )
                act[m][n] += 5000;
             //02202020
             if( newwhite[x][y] == 0 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 2 && newwhite[x][y+3] == 0 && newwhite[x][y+4] == 2 && newwhite[x][y+5] == 2 &&
                 newwhite[x][y+6] == 2 && newwhite[x][y+7] == 0 )
                act[m][n] += 4000;
             //02020220
             if(newwhite[x][y] == 0 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 0 && newwhite[x][y+3] == 2 && newwhite[x][y+4] == 0 && newwhite[x][y+5] == 2 &&
                 newwhite[x][y+6] == 2 && newwhite[x][y+7] == 0 )
                act[m][n] += 4000;

             //4개 한쪽 막혔을 때
             //122220
             if(newwhite[x][y]==1 && newwhite[x][y+1]==2 && newwhite[x][y+2]==2 && newwhite[x][y+3] == 2 && newwhite[x][y+4] ==2 && newwhite[x][y+5] ==0)
                act[m][n] += 4000;
             //1202220
             if(newwhite[x][y]==1 && newwhite[x][y+1]==2 && newwhite[x][y+2]==0 && newwhite[x][y+3] == 2 && newwhite[x][y+4] ==2 && newwhite[x][y+5] ==2 &&newwhite[x][y+6] ==0)
                act[m][n] += 3500;
             //1220220
             if(newwhite[x][y]==1 && newwhite[x][y+1]==2 && newwhite[x][y+2]==2 && newwhite[x][y+3] ==0 && newwhite[x][y+4] ==2 && newwhite[x][y+5] ==2 &&newwhite[x][y+6] ==0)
                act[m][n] += 3500;
             //1222020
             if(newwhite[x][y]==1 && newwhite[x][y+1]==2 && newwhite[x][y+2]==2 && newwhite[x][y+3] == 2 && newwhite[x][y+4] ==0 && newwhite[x][y+5] ==2 &&newwhite[x][y+6] ==0)
                act[m][n] += 3500;
             //1022220
             if(newwhite[x][y]==1 && newwhite[x][y+1]==0 && newwhite[x][y+2]==2 && newwhite[x][y+3] == 2 && newwhite[x][y+4] ==2 && newwhite[x][y+5] ==2 &&newwhite[x][y+6] ==0)
                act[m][n] += 3500;
             //12002220
             if(newwhite[x][y]==1 && newwhite[x][y+1]==2 && newwhite[x][y+2]==0 && newwhite[x][y+3] == 0 && newwhite[x][y+4] ==2 && newwhite[x][y+5] ==2 &&newwhite[x][y+6] ==2 &&
                 newwhite[x][y+7]==0)
                act[m][n] += 3500;
             //12020220
             if(newwhite[x][y]==1 && newwhite[x][y+1]==2 && newwhite[x][y+2]==0 && newwhite[x][y+3] == 2 && newwhite[x][y+4] ==0 && newwhite[x][y+5] ==2 &&newwhite[x][y+6] ==2 &&
                 newwhite[x][y+7]==0)
                act[m][n] += 3500;
             //12022020
             if(newwhite[x][y]==1 && newwhite[x][y+1]==2 && newwhite[x][y+2]==0 && newwhite[x][y+3] == 2 && newwhite[x][y+4] ==2 && newwhite[x][y+5] ==0 &&newwhite[x][y+6] ==2 &&
                 newwhite[x][y+7]==0)
                act[m][n] += 3500;
             //12200220
             if(newwhite[x][y]==1 && newwhite[x][y+1]==2 && newwhite[x][y+2]==2 && newwhite[x][y+3] == 0 && newwhite[x][y+4] ==0 && newwhite[x][y+5] ==2 &&newwhite[x][y+6] ==2 &&
                 newwhite[x][y+7]==0 )
                act[m][n] += 3500;
             //12202020
             if(newwhite[x][y]==1 && newwhite[x][y+1]==2 && newwhite[x][y+2]==2 && newwhite[x][y+3] == 0 && newwhite[x][y+4] ==2 && newwhite[x][y+5] ==0 &&newwhite[x][y+6] ==2 &&
                 newwhite[x][y+7]==0)
                act[m][n] += 3500;
             //12220020
             if(newwhite[x][y]==1 && newwhite[x][y+1]==2 && newwhite[x][y+2]==2 && newwhite[x][y+3] == 2 && newwhite[x][y+4] ==0 && newwhite[x][y+5] ==0 &&newwhite[x][y+6] ==2 &&
                 newwhite[x][y+7]==0)
                act[m][n] += 3500;
             //10220220
             if(newwhite[x][y]==1 && newwhite[x][y+1]==0 && newwhite[x][y+2]==2 && newwhite[x][y+3] == 2 && newwhite[x][y+4] ==0 && newwhite[x][y+5] ==2 &&newwhite[x][y+6] ==2 &&
                 newwhite[x][y+7]==0)
                act[m][n] += 3500;
             //10222020
             if(newwhite[x][y]==1 && newwhite[x][y+1]==0 && newwhite[x][y+2]==2 && newwhite[x][y+3] == 2 && newwhite[x][y+4] ==2 && newwhite[x][y+5] ==0 &&newwhite[x][y+6] ==2 &&
                 newwhite[x][y+7]==0)
                act[m][n] += 3500;
             //10202220
             if(newwhite[x][y]==1 && newwhite[x][y+1]==0 && newwhite[x][y+2]==2 && newwhite[x][y+3] == 0 && newwhite[x][y+4] ==2 && newwhite[x][y+5] ==2 &&newwhite[x][y+6] ==2 &&
                 newwhite[x][y+7]==0)
                act[m][n] += 3500;


             //4개 한쪽 막혔을 때 reverse
             //022221
             if(newwhite[x][y]==0 && newwhite[x][y+1]==2 && newwhite[x][y+2]==2 && newwhite[x][y+3] == 2 && newwhite[x][y+4] ==2 && newwhite[x][y+5] ==1)
                act[m][n] += 3500;
             //0222021
             if(newwhite[x][y]==0 && newwhite[x][y+1]==2 && newwhite[x][y+2]==2 && newwhite[x][y+3] == 2 && newwhite[x][y+4] ==0 && newwhite[x][y+5] ==2 &&newwhite[x][y+6] ==1)
                act[m][n] += 3500;
             //0220221
             if(newwhite[x][y]==0 && newwhite[x][y+1]==2 && newwhite[x][y+2]==2 && newwhite[x][y+3] ==0 && newwhite[x][y+4] ==2 && newwhite[x][y+5] ==2 &&newwhite[x][y+6] ==1)
                act[m][n] += 3500;
             //0202221
             if(newwhite[x][y]==0 && newwhite[x][y+1]==2 && newwhite[x][y+2]==0 && newwhite[x][y+3] == 2 && newwhite[x][y+4] ==2 && newwhite[x][y+5] ==2 &&newwhite[x][y+6] ==1)
                act[m][n] += 3500;
             //0222201
             if(newwhite[x][y]==0 && newwhite[x][y+1]==2 && newwhite[x][y+2]==2 && newwhite[x][y+3] == 2 && newwhite[x][y+4] ==2 && newwhite[x][y+5] ==0 &&newwhite[x][y+6] ==1)
                act[m][n] += 3500;
             //02220021
             if(newwhite[x][y]==0 && newwhite[x][y+1]==2 && newwhite[x][y+2]==2 && newwhite[x][y+3] == 2 && newwhite[x][y+4] ==0 && newwhite[x][y+5] ==0 &&newwhite[x][y+6] ==2 &&
                 newwhite[x][y+7] ==1)
                act[m][n] += 3500;
             //02202021
             if(newwhite[x][y]==0 && newwhite[x][y+1]==2 && newwhite[x][y+2]==2 && newwhite[x][y+3] == 0 && newwhite[x][y+4] ==2 && newwhite[x][y+5] ==0 &&newwhite[x][y+6] ==2 &&
                 newwhite[x][y+7] ==1)
                act[m][n] += 3500;
             //02022021
             if(newwhite[x][y]==0 && newwhite[x][y+1]==2 && newwhite[x][y+2]==0 && newwhite[x][y+3] == 2 && newwhite[x][y+4] ==2 && newwhite[x][y+5] ==0 &&newwhite[x][y+6] ==2 &&
                 newwhite[x][y+7] ==1)
                act[m][n] += 3500;
             //02200221
             if(newwhite[x][y]==0 && newwhite[x][y+1]==2 && newwhite[x][y+2]==2 && newwhite[x][y+3] == 0 && newwhite[x][y+4] ==0 && newwhite[x][y+5] ==2 &&newwhite[x][y+6] ==2 &&
                 newwhite[x][y+7] ==1 )
                act[m][n] += 3500;
             //02020221
             if(newwhite[x][y]==0 && newwhite[x][y+1]==2 && newwhite[x][y+2]==0 && newwhite[x][y+3] == 2 && newwhite[x][y+4] ==0 && newwhite[x][y+5] ==2 &&newwhite[x][y+6] ==2 &&
                 newwhite[x][y+7] ==1)
                act[m][n] += 3500;
             //02002221
             if(newwhite[x][y]==0 && newwhite[x][y+1]==2 && newwhite[x][y+2]==0 && newwhite[x][y+3] == 0 && newwhite[x][y+4] ==2 && newwhite[x][y+5] ==2 &&newwhite[x][y+6] ==2 &&
                 newwhite[x][y+7] ==1)
                act[m][n] += 3500;
             //02202201
             if(newwhite[x][y]==0 && newwhite[x][y+1]==2 && newwhite[x][y+2]==2 && newwhite[x][y+3] == 0 && newwhite[x][y+4] ==2 && newwhite[x][y+5] ==2 &&newwhite[x][y+6] ==0 &&
                 newwhite[x][y+7] ==1)
                act[m][n] += 3500;
             //02022201
             if(newwhite[x][y]==0 && newwhite[x][y+1]==2 && newwhite[x][y+2]==0 && newwhite[x][y+3] == 2 && newwhite[x][y+4] ==2 && newwhite[x][y+5] ==2 &&newwhite[x][y+6] ==0 &&
                 newwhite[x][y+7] ==1)
                act[m][n] += 3500;
             //02220201
             if(newwhite[x][y]==0 && newwhite[x][y+1]==2 && newwhite[x][y+2]==2 && newwhite[x][y+3] == 2 && newwhite[x][y+4] ==0 && newwhite[x][y+5] ==2 &&newwhite[x][y+6] ==0 &&
                 newwhite[x][y+7] ==1)
                act[m][n] += 3500;



             //양쪽 다 막혔을 때

             //12022021
             if(newwhite[x][y]==1 && newwhite[x][y+1]==2 && newwhite[x][y+2]==0 && newwhite[x][y+3] == 2 && newwhite[x][y+4] ==2 && newwhite[x][y+5] ==0 &&newwhite[x][y+6] ==2 &&newwhite[x][y+7] ==1 )
                act[m][n] += 1000;
             //12200221
             if(newwhite[x][y]==1 && newwhite[x][y+1]==2 && newwhite[x][y+2]==2 && newwhite[x][y+3] == 0 && newwhite[x][y+4] ==0 && newwhite[x][y+5] ==2 &&newwhite[x][y+6] ==2 &&newwhite[x][y+7] ==1 )
                act[m][n] += 1000;
             //12220021
             if(newwhite[x][y]==1 && newwhite[x][y+1]==2 && newwhite[x][y+2]==2 && newwhite[x][y+3] == 2 && newwhite[x][y+4] ==0 && newwhite[x][y+5] ==0 &&newwhite[x][y+6] ==2 &&newwhite[x][y+7] ==1)
                act[m][n] += 1000;
             //12002221
             if(newwhite[x][y]==1 && newwhite[x][y+1]==2 && newwhite[x][y+2]==0 && newwhite[x][y+3] == 0 && newwhite[x][y+4] ==2 && newwhite[x][y+5] ==2 &&newwhite[x][y+6] ==2 &&newwhite[x][y+7] ==1 )
                act[m][n] += 1000;
             //12202021
             if(newwhite[x][y]==1 && newwhite[x][y+1]==2 && newwhite[x][y+2]==2 && newwhite[x][y+3] == 0 && newwhite[x][y+4] ==2 && newwhite[x][y+5] ==2 &&newwhite[x][y+6] ==2 &&newwhite[x][y+7] ==1)
                act[m][n] += 1000;
             //12020221
             if(newwhite[x][y]==1 && newwhite[x][y+1]==2 && newwhite[x][y+2]==0 && newwhite[x][y+3] == 2 && newwhite[x][y+4] ==0 && newwhite[x][y+5] ==2 &&newwhite[x][y+6] ==2 &&newwhite[x][y+7] ==1 )
                act[m][n] += 1000;
             //10222201
           if(newwhite[x][y]==1 && newwhite[x][y+1]==0 && newwhite[x][y+2]==2 && newwhite[x][y+3] == 2 && newwhite[x][y+4] ==2 && newwhite[x][y+5] ==2 &&newwhite[x][y+6] ==0 &&newwhite[x][y+7] ==1 )
                act[m][n] += 1000;
           //10222021
           if(newwhite[x][y]==1 && newwhite[x][y+1]==0 && newwhite[x][y+2]==2 && newwhite[x][y+3] == 2 && newwhite[x][y+4] ==2 && newwhite[x][y+5] ==0 &&newwhite[x][y+6] ==2 &&newwhite[x][y+7] ==1 )
                act[m][n] += 1000;
           //10220221
           if(newwhite[x][y]==1 && newwhite[x][y+1]==0 && newwhite[x][y+2]==2 && newwhite[x][y+3] == 2 && newwhite[x][y+4] ==0 && newwhite[x][y+5] ==2 &&newwhite[x][y+6] ==2 &&newwhite[x][y+7] ==1 )
                act[m][n] += 1000;
            //10202221
           if(newwhite[x][y]==1 && newwhite[x][y+1]==0 && newwhite[x][y+2]==2 && newwhite[x][y+3] == 0 && newwhite[x][y+4] ==2 && newwhite[x][y+5] ==2 &&newwhite[x][y+6] ==2 &&newwhite[x][y+7] ==1 )
                act[m][n] += 1000;
           //10022221
           if(newwhite[x][y]==1 && newwhite[x][y+1]==0 && newwhite[x][y+2]==0 && newwhite[x][y+3] == 2 && newwhite[x][y+4] ==2 && newwhite[x][y+5] ==2 &&newwhite[x][y+6] ==2 &&newwhite[x][y+7] ==1 )
                act[m][n] += 1000;
           //12022201
           if(newwhite[x][y]==1 && newwhite[x][y+1]==2 && newwhite[x][y+2]==0 && newwhite[x][y+3] == 2 && newwhite[x][y+4] ==2 && newwhite[x][y+5] ==2 &&newwhite[x][y+6] ==0 &&newwhite[x][y+7] ==1 )
                act[m][n] += 1000;
           //12202201
           if(newwhite[x][y]==1 && newwhite[x][y+1]==2 && newwhite[x][y+2]==2 && newwhite[x][y+3] == 0 && newwhite[x][y+4] ==2 && newwhite[x][y+5] ==2 &&newwhite[x][y+6] ==0 &&newwhite[x][y+7] ==1 )
                act[m][n] += 1000;
           //12220201
           if(newwhite[x][y]==1 && newwhite[x][y+1]==2 && newwhite[x][y+2]==2 && newwhite[x][y+3] == 2 && newwhite[x][y+4] ==0 && newwhite[x][y+5] ==2 &&newwhite[x][y+6] ==0 &&newwhite[x][y+7] ==1 )
                act[m][n] += 1000;
           //12222001
           if(newwhite[x][y]==1 && newwhite[x][y+1]==2 && newwhite[x][y+2]==2 && newwhite[x][y+3] == 2 && newwhite[x][y+4] ==2 && newwhite[x][y+5] ==0 &&newwhite[x][y+6] ==0 &&newwhite[x][y+7] ==1 )
                act[m][n] += 1000;
             }
             }
             newwhite[m][n] = 0;
             }
             }


}




void AI::W_AI_2_sero_check()
{
    for(int m=0 ; m<19 ; m++)
        {
          for(int n=0 ; n<19 ; n++)
          {
              if( newwhite[m][n] == 0 )
              {
              newwhite[m][n] = 2;
              }
              else if( newwhite[m][n] == 1 || newwhite[m][n] == 2 )
              {
                  continue;
              }

              for(int x=0; x<19; x++)
              {
                  for(int y=0; y<19; y++)
                  {
                //00022000
                if( newwhite[x-2][y] == 0 && newwhite[x-1][y] == 0 && newwhite[x][y] == 0 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 2 &&
                    newwhite[x+3][y] == 0 && newwhite[x+4][y] == 0 && newwhite[x+5][y] == 0 )
                    act[m][n] += 2000;
                //0020200
                if( newwhite[x-1][y] == 0 && newwhite[x][y] == 0 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 0 && newwhite[x+3][y] == 2 && newwhite[x+4][y] == 0 &&
                    newwhite[x+5][y] == 0 )
                    act[m][n] += 1500;
                //020020
                if( newwhite[x][y] == 0 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 0 && newwhite[x+3][y] == 0 && newwhite[x+4][y] == 2 && newwhite[x+5][y] == 0 )
                    act[m][n] += 1000;
                //여기까지 양쪽에 안 막힌, 흰 돌이 2개가 발견 될 때 경우의 수들

                //122000
                if( newwhite[x][y] == 1 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 2 && newwhite[x+3][y] == 0 && newwhite[x+4][y] == 0 && newwhite[x+5][y] == 0 )
                    act[m][n] += 500;
                //120200
                if( newwhite[x][y] == 1 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 0 && newwhite[x+3][y] == 2 && newwhite[x+4][y] == 0 && newwhite[x+5][y] == 0 )
                    act[m][n] += 500;
                //120020
                if( newwhite[x][y] == 1 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 0 && newwhite[x+3][y] == 0 && newwhite[x+4][y] == 2 && newwhite[x+5][y] == 0 )
                    act[m][n] += 500;
                //102200
                if( newwhite[x][y] == 1 && newwhite[x+1][y] == 0 && newwhite[x+2][y] == 2 && newwhite[x+3][y] == 2 && newwhite[x+4][y] == 0 && newwhite[x+5][y] == 0 )
                    act[m][n] += 800;
                //102020
                if( newwhite[x][y] == 1 && newwhite[x+1][y] == 0 && newwhite[x+2][y] == 2 && newwhite[x+3][y] == 0 && newwhite[x+4][y] == 2 && newwhite[x+5][y] == 0 )
                    act[m][n] += 800;
                //여기까지 왼쪽에 검은돌로 막힌 경우.
                //오른쪽에 검은돌로 막힌 경우는 이 대칭으로만 작성해주면됌

                //000221
                if( newwhite[x-2][y] == 0 && newwhite[x-1][y] == 0 && newwhite[x][y] == 0 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 2 && newwhite[x+3][y] == 1 )
                    act[m][n] += 500;
                //002021
                if( newwhite[x-1][y] == 0 && newwhite[x][y] == 0 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 0 && newwhite[x+3][y] == 2 && newwhite[x+4][y] == 1 )
                    act[m][n] += 500;
                //020021
                if( newwhite[x][y] == 0 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 0 && newwhite[x+3][y] == 0 && newwhite[x+4][y] == 2 && newwhite[x+5][y] == 1 )
                    act[m][n] += 500;
                //002201
                if( newwhite[x-1][y] == 0 && newwhite[x][y] == 0 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 2 && newwhite[x+3][y] == 0 && newwhite[x+4][y] == 1 )
                    act[m][n] += 800;
                //020201
                if( newwhite[x][y] == 0 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 0 && newwhite[x+3][y] == 2 && newwhite[x+4][y] == 0 && newwhite[x+5][y] == 1 )
                    act[m][n] += 800;
                //여기까지 한쪽이 막힌 경우.
                //그 다음은 양쪽이 막힌 경우. 양쪽이 막힌 경우는 안이 6칸일 경우만 따지자.

                //12200001
                if( newwhite[x][y] == 1 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 2 && newwhite[x+3][y] == 0 && newwhite[x+4][y] == 0 && newwhite[x+5][y] == 0 &&
                    newwhite[x+6][y] == 0 && newwhite[x+7][y] == 1 )
                    act[m][n] += 300;
                //12020001
                if( newwhite[x][y] == 1 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 0 && newwhite[x+3][y] == 2 && newwhite[x+4][y] == 0 && newwhite[x+5][y] == 0 &&
                    newwhite[x+6][y] == 0 && newwhite[x+7][y] == 1 )
                    act[m][n] += 300;
                //12002001
                if( newwhite[x][y] == 1 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 0 && newwhite[x+3][y] == 0 && newwhite[x+4][y] == 2 && newwhite[x+5][y] == 0 &&
                    newwhite[x+6][y] == 0 && newwhite[x+7][y] == 1 )
                    act[m][n] += 300;
                //12000201
                if( newwhite[x][y] == 1 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 0 && newwhite[x+3][y] == 0 && newwhite[x+4][y] == 0 && newwhite[x+5][y] == 2 &&
                    newwhite[x+6][y] == 0 && newwhite[x+7][y] == 1 )
                    act[m][n] += 300;
                //12000021
                if( newwhite[x][y] == 1 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 0 && newwhite[x+3][y] == 0 && newwhite[x+4][y] == 0 && newwhite[x+5][y] == 0 &&
                    newwhite[x+6][y] == 2 && newwhite[x+7][y] == 1 )
                    act[m][n] += 300;
                //10220001
                if( newwhite[x][y] == 1 && newwhite[x+1][y] == 0 && newwhite[x+2][y] == 2 && newwhite[x+3][y] == 2 && newwhite[x+4][y] == 0 && newwhite[x+5][y] == 0 &&
                    newwhite[x+6][y] == 0 && newwhite[x+7][y] == 1 )
                    act[m][n] += 300;
                //10202001
                if( newwhite[x][y] == 1 && newwhite[x+1][y] == 0 && newwhite[x+2][y] == 2 && newwhite[x+3][y] == 0 && newwhite[x+4][y] == 2 && newwhite[x+5][y] == 0 &&
                    newwhite[x+6][y] == 0 && newwhite[x+7][y] == 1 )
                    act[m][n] += 300;
                //10200201
                if( newwhite[x][y] == 1 && newwhite[x+1][y] == 0 && newwhite[x+2][y] == 2 && newwhite[x+3][y] == 0 && newwhite[x+4][y] == 0 && newwhite[x+5][y] == 2 &&
                    newwhite[x+6][y] == 0 && newwhite[x+7][y] == 1 )
                    act[m][n] += 300;
                //10200021
                if( newwhite[x][y] == 1 && newwhite[x+1][y] == 0 && newwhite[x+2][y] == 2 && newwhite[x+3][y] == 0 && newwhite[x+4][y] == 0 && newwhite[x+5][y] == 0 &&
                    newwhite[x+6][y] == 2 && newwhite[x+7][y] == 1 )
                    act[m][n] += 300;
                //10022001
                if( newwhite[x][y] == 1 && newwhite[x+1][y] == 0 && newwhite[x+2][y] == 0 && newwhite[x+3][y] == 2 && newwhite[x+4][y] == 2 && newwhite[x+5][y] == 0 &&
                    newwhite[x+6][y] == 0 && newwhite[x+7][y] == 1 )
                    act[m][n] += 300;
                //10020201
                if( newwhite[x][y] == 1 && newwhite[x+1][y] == 0 && newwhite[x+2][y] == 0 && newwhite[x+3][y] == 2 && newwhite[x+4][y] == 0 && newwhite[x+5][y] == 2 &&
                    newwhite[x+6][y] == 0 && newwhite[x+7][y] == 1 )
                    act[m][n] += 300;
                //10020021
                if( newwhite[x][y] == 1 && newwhite[x+1][y] == 0 && newwhite[x+2][y] == 0 && newwhite[x+3][y] == 2 && newwhite[x+4][y] == 0 && newwhite[x+5][y] == 0 &&
                    newwhite[x+6][y] == 2 && newwhite[x+7][y] == 1 )
                    act[m][n] += 300;
                //10002201
                if( newwhite[x][y] == 1 && newwhite[x+1][y] == 0 && newwhite[x+2][y] == 0 && newwhite[x+3][y] == 0 && newwhite[x+4][y] == 2 && newwhite[x+5][y] == 2 &&
                    newwhite[x+6][y] == 0 && newwhite[x+7][y] == 1 )
                    act[m][n] += 300;
                //10002021
                if( newwhite[x][y] == 1 && newwhite[x+1][y] == 0 && newwhite[x+2][y] == 0 && newwhite[x+3][y] == 2 && newwhite[x+4][y] == 0 && newwhite[x+5][y] == 2 &&
                    newwhite[x+6][y] == 0 && newwhite[x+7][y] == 1 )
                    act[m][n] += 300;
                //10000221
                if( newwhite[x][y] == 1 && newwhite[x+1][y] == 0 && newwhite[x+2][y] == 0 && newwhite[x+3][y] == 0 && newwhite[x+4][y] == 0 && newwhite[x+5][y] == 2 &&
                    newwhite[x+6][y] == 2 && newwhite[x+7][y] == 1 )
                    act[m][n] += 300;
                  }
              }
              newwhite[m][n] = 0;
          }
        }

}

void AI::W_AI_3_sero_check()
{
    for(int m=0 ; m<19 ; m++)
        {
          for(int n=0 ; n<19 ; n++)
          {
              if( newwhite[m][n] == 0 )
              {
              newwhite[m][n] = 2;
              }
              else if( newwhite[m][n] == 1 || newwhite[m][n] == 2 )
              {
                  continue;
              }

              for(int x=0; x<19; x++)
              {
                  for(int y=0; y<19; y++)
                  {
                //000222000
                if( newwhite[x-1][y] == 0 && newwhite[x][y] == 0 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 2 && newwhite[x+3][y] == 2&& newwhite[x+4][y]==0 &&
                    newwhite[x+5][y] == 0 )
                    act[m][n] += 5000;
                //00202200
                if( newwhite[x-1][y] == 0 && newwhite[x][y] == 0 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 0 && newwhite[x+3][y] == 2 && newwhite[x+4][y] == 2 &&
                    newwhite[x+5][y]==0 && newwhite[x+6][y] == 0 )
                    act[m][n] += 3500;
                //00220200
                if( newwhite[x-1][y] == 0 && newwhite[x][y] == 0 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 2 && newwhite[x+3][y] == 0 && newwhite[x+4][y] == 2 &&
                    newwhite[x+5][y] == 0 && newwhite[x+6][y] == 0 )
                    act[m][n] += 3500;
                //0200220
                if( newwhite[x][y] == 0 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 0 && newwhite[x+3][y] == 0 && newwhite[x+4][y] == 2 && newwhite[x+5][y] == 2
                    &&newwhite[x+6][y] ==0 )
                    act[m][n] += 3000;
                //0202020
                if( newwhite[x][y] == 0 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 0 && newwhite[x+3][y] == 2 && newwhite[x+4][y] == 0 && newwhite[x+5][y] == 2
                    &&newwhite[x+6][y]==0 )
                    act[m][n] += 3000;
                //0220020
                if( newwhite[x][y] == 0 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 2 && newwhite[x+3][y] == 0 && newwhite[x+4][y] == 0 && newwhite[x+5][y] == 2
                    && newwhite[x+6][y] ==0 )
                    act[m][n] += 3000;
                //여기까지 양쪽에 안 막힌, 흰 돌이 2개가 발견 될 때 경우의 수들

                //122200
                if( newwhite[x][y] == 1 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 2 && newwhite[x+3][y] == 2 && newwhite[x+4][y] ==0 && newwhite[x+5][y] == 0 )
                    act[m][n] += 1000;
                //1202200
                if( newwhite[x][y] == 1 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 0 && newwhite[x+3][y] == 2 && newwhite[x+4][y] == 2 && newwhite[x+5][y] ==0 &&
                    newwhite[x][y] == 0 )
                    act[m][n] += 1000;
                //1220200
                if( newwhite[x][y] == 1 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 2 && newwhite[x+3][y] == 0 && newwhite[x+4][y] == 2 && newwhite[x+5][y] == 0 &&
                    newwhite[x+6][y] == 0 )
                    act[m][n] += 1000;
                //1022200
                if( newwhite[x][y] == 1 && newwhite[x+1][y] == 0 && newwhite[x+2][y] == 2 && newwhite[x+3][y] == 2 && newwhite[x+4][y] == 2 && newwhite[x+5][y] ==0 &&
                    newwhite[x+6][y] == 0 )
                    act[m][n] += 1300;
                //1200220
                if( newwhite[x][y] == 1 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 0 && newwhite[x+3][y] == 0 && newwhite[x+4][y] == 2 && newwhite[x+5][y] == 2 &&
                newwhite[x+6][y] ==0 )
                    act[m][n] += 1300;
                //1220020
                if( newwhite[x][y] == 1 && newwhite[x][y] == 2 && newwhite[x][y] == 2 && newwhite[x][y] == 0 && newwhite[x][y] == 0 && newwhite[x][y] == 2 &&
                    newwhite[x][y] == 0 )
                    act[m][n] += 1000;
                //1202020
                if( newwhite[x][y] == 1 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 0 && newwhite[x+3][y] == 2 && newwhite[x+4][y] == 0 && newwhite[x+5][y] == 2 &&
                    newwhite[x+6][y] ==0 )
                    act[m][n] += 1000;
                //1020220
                if( newwhite[x][y] == 1 && newwhite[x+1][y] == 0 && newwhite[x+2][y] == 2 && newwhite[x+3][y] == 0 && newwhite[x+4][y] == 2 && newwhite[x+5][y] == 2 &&
                    newwhite[x+6][y] == 0)
                    act[m][n] += 1300;

                //여기까지 왼쪽에 검은돌로 막힌 경우.
                //오른쪽에 검은돌로 막힌 경우는 이 대칭으로만 작성해주면됌

                //002221
                if( newwhite[x-1][y] == 0 && newwhite[x][y] == 0 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 2 && newwhite[x+3][y] == 2 && newwhite[x+4][y] == 1 )
                    act[m][n] += 1000;
                //0022021
                if( newwhite[x-1][y] == 0 && newwhite[x][y] == 0 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 2 && newwhite[x+3][y] == 0 && newwhite[x+4][y] == 2 &&
                    newwhite[x+5][y]==1 )
                    act[m][n] += 1000;
                //0020221
                if( newwhite[x-1][y] == 0 && newwhite[x][y] == 0 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 0 && newwhite[x+3][y] == 2 && newwhite[x+4][y] == 2 &&
                    newwhite[x+5][y] == 1 )
                    act[m][n] += 1000;
                //0022201
                if( newwhite[x-1][y] == 0 && newwhite[x][y] == 0 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 2 && newwhite[x+3][y] == 2 && newwhite[x+4][y] == 0 &&
                    newwhite[x+5][y] == 1 )
                    act[m][n] += 1300;
                //0220021
                if( newwhite[x][y] == 0 && newwhite[x][y] == 2 && newwhite[x][y] == 2 && newwhite[x][y] == 0 && newwhite[x][y] == 0 && newwhite[x][y] == 2 &&
                    newwhite[x][y] == 1 )
                    act[m][n] += 1300;
                //0200221
                if( newwhite[x][y] == 0 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 0 && newwhite[x+3][y] == 0 && newwhite[x+4][y] == 2 && newwhite[x+5][y] == 2 &&
                    newwhite[x+6][y] == 1 )
                    act[m][n] += 1000;
                //0202021
                if( newwhite[x][y] == 0 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 0 && newwhite[x+3][y] == 2 && newwhite[x+4][y] == 0 && newwhite[x+5][y] == 2 &&
                    newwhite[x+6][y] == 1 )
                    act[m][n] += 1000;
                //0220201
                if( newwhite[x][y] == 0 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 2 && newwhite[x+3][y] == 0 && newwhite[x+4][y] == 2 && newwhite[x+5][y] == 0 &&
                    newwhite[x+6][y] == 1 )
                    act[m][n] += 1300;

                //여기까지 한쪽이 막힌 경우.
                //그 다음은 양쪽이 막힌 경우. 양쪽이 막힌 경우는 안이 6칸일 경우만 따지자.

                //12220001
                if( newwhite[x][y] == 1 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 2 && newwhite[x+3][y] == 2 && newwhite[x+4][y] == 0 && newwhite[x+5][y] == 0 &&
                    newwhite[x+6][y] == 0 && newwhite[x+7][y] == 1 )
                    act[m][n] += 300;
                //12022001
                if( newwhite[x][y] == 1 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 0 && newwhite[x+3][y] == 2 && newwhite[x+4][y] == 2 && newwhite[x+5][y] == 0 &&
                    newwhite[x+6][y] == 0 && newwhite[x+7][y] == 1 )
                    act[m][n] += 300;
                //12002201
                if( newwhite[x][y] == 1 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 0 && newwhite[x+3][y] == 0 && newwhite[x+4][y] == 2 && newwhite[x+5][y] == 2 &&
                    newwhite[x+6][y] == 0 && newwhite[x+7][y] == 1 )
                    act[m][n] += 300;
                //12000221
                if( newwhite[x][y] == 1 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 0 && newwhite[x+3][y] == 0 && newwhite[x+4][y] == 0 && newwhite[x+5][y] == 2 &&
                    newwhite[x+6][y] == 2 && newwhite[x+7][y] == 1 )
                    act[m][n] += 300;
                //12202001
                if( newwhite[x][y] == 1 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 2 && newwhite[x+3][y] == 0 && newwhite[x+4][y] == 2 && newwhite[x+5][y] == 0 &&
                    newwhite[x+6][y] == 0 && newwhite[x+7][y] == 1 )
                    act[m][n] += 300;
                //12200201
                if( newwhite[x][y] == 1 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 2 && newwhite[x+3][y] == 0 && newwhite[x+4][y] == 0 && newwhite[x+5][y] == 2 &&
                    newwhite[x+6][y] == 0 && newwhite[x+7][y] == 1 )
                    act[m][n] += 300;
                //12200021
                if( newwhite[x][y] == 1 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 2 && newwhite[x+3][y] == 0 && newwhite[x+4][y] == 0 && newwhite[x+5][y] == 0 &&
                    newwhite[x+6][y] == 2 && newwhite[x+7][y] == 1 )
                    act[m][n] += 300;
                //12002021
                if( newwhite[x][y] == 1 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 0 && newwhite[x+3][y] == 0 && newwhite[x+4][y] == 2 && newwhite[x+5][y] == 0 &&
                    newwhite[x+6][y] == 2 && newwhite[x+7][y] == 1 )
                    act[m][n] += 300;
                //12020021
                if( newwhite[x][y] == 1 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 0 && newwhite[x+3][y] == 2 && newwhite[x+4][y] == 0 && newwhite[x+5][y] == 0 &&
                    newwhite[x+6][y] == 2 && newwhite[x+7][y] == 1 )
                    act[m][n] += 300;
                //12020201
                if( newwhite[x][y] == 1 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 0 && newwhite[x+3][y] == 2 && newwhite[x+4][y] == 0 && newwhite[x+5][y] == 2 &&
                    newwhite[x+6][y] == 0 && newwhite[x+7][y] == 1 )
                    act[m][n] += 300;
                //10222001
                if( newwhite[x][y] == 1 && newwhite[x+1][y] == 0 && newwhite[x+2][y] == 2 && newwhite[x+3][y] == 2 && newwhite[x+4][y] == 2 && newwhite[x+5][y] == 0 &&
                    newwhite[x+6][y] == 0 && newwhite[x+7][y] == 1 )
                    act[m][n] += 300;
                //10202201
                if( newwhite[x][y] == 1 && newwhite[x+1][y] == 0 && newwhite[x+2][y] == 2 && newwhite[x+3][y] == 0 && newwhite[x+4][y] == 2 && newwhite[x+5][y] == 2 &&
                    newwhite[x+6][y] == 0 && newwhite[x+7][y] == 1 )
                    act[m][n] += 300;
                //10200221
                if( newwhite[x][y] == 1 && newwhite[x+1][y] == 0 && newwhite[x+2][y] == 2 && newwhite[x+3][y] == 0 && newwhite[x+4][y] == 0 && newwhite[x+5][y] == 2 &&
                    newwhite[x+6][y] == 2 && newwhite[x+7][y] == 1 )
                    act[m][n] += 300;
                //10220201
                if( newwhite[x][y] == 1 && newwhite[x+1][y] == 0 && newwhite[x+2][y] == 2 && newwhite[x+3][y] == 2 && newwhite[x+4][y] == 0 && newwhite[x+5][y] == 2 &&
                    newwhite[x+6][y] == 0 && newwhite[x+7][y] == 1 )
                    act[m][n] += 300;
                //10220021
                if( newwhite[x][y] == 1 && newwhite[x+1][y] == 0 && newwhite[x+2][y] == 2 && newwhite[x+3][y] == 2 && newwhite[x+4][y] == 0 && newwhite[x+5][y] == 0 &&
                    newwhite[x+6][y] == 2 && newwhite[x+7][y] == 1 )
                    act[m][n] += 300;
                //10022021
                if( newwhite[x][y] == 1 && newwhite[x+1][y] == 0 && newwhite[x+2][y] == 0 && newwhite[x+3][y] == 2 && newwhite[x+4][y] == 2 && newwhite[x+5][y] == 0 &&
                    newwhite[x+6][y] == 2 && newwhite[x+7][y] == 1 )
                    act[m][n] += 300;
                //10022201
                if( newwhite[x][y] == 1 && newwhite[x+1][y] == 0 && newwhite[x+2][y] == 0 && newwhite[x+3][y] == 2 && newwhite[x+4][y] == 2 && newwhite[x+5][y] == 2 &&
                    newwhite[x+6][y] == 0 && newwhite[x+7][y] == 1 )
                    act[m][n] += 300;
                //10020221
                if( newwhite[x][y] == 1 && newwhite[x+1][y] == 0 && newwhite[x+2][y] == 0 && newwhite[x+3][y] == 2 && newwhite[x+4][y] == 0 && newwhite[x+5][y] == 2 &&
                    newwhite[x+6][y] == 2 && newwhite[x+7][y] == 1 )
                    act[m][n] += 300;
                //10002221
                if( newwhite[x][y] == 1 && newwhite[x+1][y] == 0 && newwhite[x+2][y] == 0 && newwhite[x+3][y] == 0 && newwhite[x+4][y] == 0 && newwhite[x+5][y] == 2 &&
                    newwhite[x+6][y] == 2 && newwhite[x+7][y] == 1 )
                    act[m][n] += 300;
                //10202021
                if( newwhite[x][y] == 1 && newwhite[x+1][y] == 0 && newwhite[x+2][y] == 2 && newwhite[x+3][y] == 0 && newwhite[x+4][y] == 2 && newwhite[x+5][y] == 0 &&
                    newwhite[x+6][y] == 2 && newwhite[x+7][y] == 1 )
                    act[m][n] += 300;
                    }
              }
              newwhite[m][n] = 0;
          }
        }

}

void AI::W_AI_4_sero_check()
{
    for(int m=0 ; m<19 ; m++)
        {
          for(int n=0 ; n<19 ; n++)
          {
              if( newwhite[m][n] == 0 )
              {
              newwhite[m][n] = 2;
              }
              else if( newwhite[m][n] == 1 || newwhite[m][n] == 2 )
              {
                  continue;
              }

              for(int x=0; x<19; x++)
              {
                  for(int y=0; y<19; y++)
                  {
                        /*4개 -> 안막혔을 때*/
             //00222200
             if( newwhite[x-1][y] == 0 && newwhite[x][y]== 0 && newwhite[x+1][y]== 2 && newwhite[x+2][y]== 2 &&newwhite[x+3][y] == 2 && newwhite[x+4][y] == 2 &&
                 newwhite[x+5][y] == 0 )
                act[m][n] += 10000;
             //002022200
             if( newwhite[x-1][y] == 0 && newwhite[x][y]==0 && newwhite[x+1][y]==2 && newwhite[x+2][y]==0 && newwhite[x+3][y] == 2 && newwhite[x+4][y] ==2 &&
                 newwhite[x+5][y]==2 &&newwhite[x+6][y] ==0 && newwhite[x+7][y] == 0 )
                act[m][n] += 7000;
             //002220200
             if( newwhite[x-1][y] == 0 && newwhite[x][y]== 0 && newwhite[x+1][y]== 2 && newwhite[x+2][y]== 2 && newwhite[x+3][y] == 2 && newwhite[x+4][y] == 0 &&
                 newwhite[x+5][y] ==2 &&newwhite[x+6][y] == 0 && newwhite[x+7][y] == 0 )
                act[m][n] += 7000;
             //002202200
             if( newwhite[x-1][y] == 0 && newwhite[x][y]== 0 && newwhite[x+1][y]== 2 && newwhite[x+2][y]== 2 && newwhite[x+3][y] == 0 && newwhite[x+4][y] == 2 &&
                 newwhite[x+5][y] == 2 && newwhite[x+6][y] == 0 && newwhite[x+7][y] == 0 )
                act[m][n] += 7000;
             //02220020
             if( newwhite[x][y]==0 && newwhite[x+1][y]==2 && newwhite[x+2][y]==2 && newwhite[x+3][y] == 2 && newwhite[x+4][y] ==0 && newwhite[x+5][y] ==0 &&
                 newwhite[x+6][y] ==2 && newwhite[x+7][y] ==0 )
                act[m][n] += 5000;
             //02002220
             if( newwhite[x][y] == 0 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 0 && newwhite[x+3][y] == 0 && newwhite[x+4][y] == 2 && newwhite[x+5][y] == 2 &&
                 newwhite[x+6][y] == 2 && newwhite[x+7][y] == 0 )
                act[m][n] += 5000;
             //02202020
             if( newwhite[x][y] == 0 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 2 && newwhite[x+3][y] == 0 && newwhite[x+4][y] == 2 && newwhite[x+5][y] == 2 &&
                 newwhite[x+6][y] == 2 && newwhite[x+7][y] == 0 )
                act[m][n] += 4000;
             //02020220
             if(newwhite[x][y] == 0 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 0 && newwhite[x+3][y] == 2 && newwhite[x+4][y] == 0 && newwhite[x+5][y] == 2 &&
                 newwhite[x+6][y] == 2 && newwhite[x+7][y] == 0 )
                act[m][n] += 4000;

             //4개 한쪽 막혔을 때
             //122220
             if(newwhite[x][y]==1 && newwhite[x+1][y]==2 && newwhite[x+2][y]==2 && newwhite[x+3][y] == 2 && newwhite[x+4][y] ==2 && newwhite[x+5][y] ==0)
                act[m][n] += 3500;
             //1202220
             if(newwhite[x][y]==1 && newwhite[x+1][y]==2 && newwhite[x+2][y]==0 && newwhite[x+3][y] == 2 && newwhite[x+4][y] ==2 && newwhite[x+5][y] ==2 &&newwhite[x+6][y] ==0)
                act[m][n] += 3500;
             //1220220
             if(newwhite[x][y]==1 && newwhite[x+1][y]==2 && newwhite[x+2][y]==2 && newwhite[x+3][y] ==0 && newwhite[x+4][y] ==2 && newwhite[x+5][y] ==2 &&newwhite[x+6][y] ==0)
                act[m][n] += 3500;
             //1222020
             if(newwhite[x][y]==1 && newwhite[x+1][y]==2 && newwhite[x+2][y]==2 && newwhite[x+3][y] == 2 && newwhite[x+4][y] ==0 && newwhite[x+5][y] ==2 &&newwhite[x+6][y] ==0)
                act[m][n] += 3500;
             //1022220
             if(newwhite[x][y]==1 && newwhite[x+1][y]==0 && newwhite[x+2][y]==2 && newwhite[x+3][y] == 2 && newwhite[x+4][y] ==2 && newwhite[x+5][y] ==2 &&newwhite[x+6][y] ==0)
                act[m][n] += 3500;
             //12002220
             if(newwhite[x][y]==1 && newwhite[x+1][y]==2 && newwhite[x+2][y]==0 && newwhite[x+3][y] == 0 && newwhite[x+4][y] ==2 && newwhite[x+5][y] ==2 &&newwhite[x+6][y] ==2 &&
                 newwhite[x+7][y]==0)
                act[m][n] += 3500;
             //12020220
             if(newwhite[x][y]==1 && newwhite[x+1][y]==2 && newwhite[x+2][y]==0 && newwhite[x+3][y] == 2 && newwhite[x+4][y] ==0 && newwhite[x+5][y] ==2 &&newwhite[x+6][y] ==2 &&
                 newwhite[x+7][y]==0)
                act[m][n] += 3500;
             //12022020
             if(newwhite[x][y]==1 && newwhite[x+1][y]==2 && newwhite[x+2][y]==0 && newwhite[x+3][y] == 2 && newwhite[x+4][y] ==2 && newwhite[x+5][y] ==0 &&newwhite[x+6][y] ==2 &&
                 newwhite[x+7][y]==0)
                act[m][n] += 3500;
             //12200220
             if(newwhite[x][y]==1 && newwhite[x+1][y]==2 && newwhite[x+2][y]==2 && newwhite[x+3][y] == 0 && newwhite[x+4][y] ==0 && newwhite[x+5][y] ==2 &&newwhite[x+6][y] ==2 &&
                 newwhite[x+7][y]==0 )
                act[m][n] += 3500;
             //12202020
             if(newwhite[x][y]==1 && newwhite[x+1][y]==2 && newwhite[x+2][y]==2 && newwhite[x+3][y] == 0 && newwhite[x+4][y] ==2 && newwhite[x+5][y] ==0 &&newwhite[x+6][y] ==2 &&
                 newwhite[x+7][y]==0)
                act[m][n] += 3500;
             //12220020
             if(newwhite[x][y]==1 && newwhite[x+1][y]==2 && newwhite[x+2][y]==2 && newwhite[x+3][y] == 2 && newwhite[x+4][y] ==0 && newwhite[x+5][y] ==0 &&newwhite[x+6][y] ==2 &&
                 newwhite[x+7][y]==0)
                act[m][n] += 3500;
             //10220220
             if(newwhite[x][y]==1 && newwhite[x+1][y]==0 && newwhite[x+2][y]==2 && newwhite[x+3][y] == 2 && newwhite[x+4][y] ==0 && newwhite[x+5][y] ==2 &&newwhite[x+6][y] ==2 &&
                 newwhite[x+7][y]==0)
                act[m][n] += 3500;
             //10222020
             if(newwhite[x][y]==1 && newwhite[x+1][y]==0 && newwhite[x+2][y]==2 && newwhite[x+3][y] == 2 && newwhite[x+4][y] ==2 && newwhite[x+5][y] ==0 &&newwhite[x+6][y] ==2 &&
                 newwhite[x+7][y]==0)
                act[m][n] += 3500;
             //10202220
             if(newwhite[x][y]==1 && newwhite[x+1][y]==0 && newwhite[x+2][y]==2 && newwhite[x+3][y] == 0 && newwhite[x+4][y] ==2 && newwhite[x+5][y] ==2 &&newwhite[x+6][y] ==2 &&
                 newwhite[x+7][y]==0)
                act[m][n] += 3500;


             //4개 한쪽 막혔을 때 reverse
             //022221
             if(newwhite[x][y]==0 && newwhite[x+1][y]==2 && newwhite[x+2][y]==2 && newwhite[x+3][y] == 2 && newwhite[x+4][y] ==2 && newwhite[x+5][y] ==1)
                act[m][n] += 3500;
             //0222021
             if(newwhite[x][y]==0 && newwhite[x+1][y]==2 && newwhite[x+2][y]==2 && newwhite[x+3][y] == 2 && newwhite[x+4][y] ==0 && newwhite[x+5][y] ==2 &&newwhite[x+6][y] ==1)
                act[m][n] += 3500;
             //0220221
             if(newwhite[x][y]==0 && newwhite[x+1][y]==2 && newwhite[x+2][y]==2 && newwhite[x+3][y] ==0 && newwhite[x+4][y] ==2 && newwhite[x+5][y] ==2 &&newwhite[x+6][y] ==1)
                act[m][n] += 3500;
             //0202221
             if(newwhite[x][y]==0 && newwhite[x+1][y]==2 && newwhite[x+2][y]==0 && newwhite[x+3][y] == 2 && newwhite[x+4][y] ==2 && newwhite[x+5][y] ==2 &&newwhite[x+6][y] ==1)
                act[m][n] += 3500;
             //0222201
             if(newwhite[x][y]==0 && newwhite[x+1][y]==2 && newwhite[x+2][y]==2 && newwhite[x+3][y] == 2 && newwhite[x+4][y] ==2 && newwhite[x+5][y] ==0 &&newwhite[x+6][y] ==1)
                act[m][n] += 3500;
             //02220021
             if(newwhite[x][y]==0 && newwhite[x+1][y]==2 && newwhite[x+2][y]==2 && newwhite[x+3][y] == 2 && newwhite[x+4][y] ==0 && newwhite[x+5][y] ==0 &&newwhite[x+6][y] ==2 &&
                 newwhite[x+7][y] ==1)
                act[m][n] += 3500;
             //02202021
             if(newwhite[x][y]==0 && newwhite[x+1][y]==2 && newwhite[x+2][y]==2 && newwhite[x+3][y] == 0 && newwhite[x+4][y] ==2 && newwhite[x+5][y] ==0 &&newwhite[x+6][y] ==2 &&
                 newwhite[x+7][y] ==1)
                act[m][n] += 3500;
             //02022021
             if(newwhite[x][y]==0 && newwhite[x+1][y]==2 && newwhite[x+2][y]==0 && newwhite[x+3][y] == 2 && newwhite[x+4][y] ==2 && newwhite[x+5][y] ==0 &&newwhite[x+6][y] ==2 &&
                 newwhite[x+7][y] ==1)
                act[m][n] += 3500;
             //02200221
             if(newwhite[x][y]==0 && newwhite[x+1][y]==2 && newwhite[x+2][y]==2 && newwhite[x+3][y] == 0 && newwhite[x+4][y] ==0 && newwhite[x+5][y] ==2 &&newwhite[x+6][y] ==2 &&
                 newwhite[x+7][y] ==1 )
                act[m][n] += 3500;
             //02020221
             if(newwhite[x][y]==0 && newwhite[x+1][y]==2 && newwhite[x+2][y]==0 && newwhite[x+3][y] == 2 && newwhite[x+4][y] ==0 && newwhite[x+5][y] ==2 &&newwhite[x+6][y] ==2 &&
                 newwhite[x+7][y] ==1)
                act[m][n] += 3500;
             //02002221
             if(newwhite[x][y]==0 && newwhite[x+1][y]==2 && newwhite[x+2][y]==0 && newwhite[x+3][y] == 0 && newwhite[x+4][y] ==2 && newwhite[x+5][y] ==2 &&newwhite[x+6][y] ==2 &&
                 newwhite[x+7][y] ==1)
                act[m][n] += 3500;
             //02202201
             if(newwhite[x][y]==0 && newwhite[x+1][y]==2 && newwhite[x+2][y]==2 && newwhite[x+3][y] == 0 && newwhite[x+4][y] ==2 && newwhite[x+5][y] ==2 &&newwhite[x+6][y] ==0 &&
                 newwhite[x+7][y] ==1)
                act[m][n] += 3500;
             //02022201
             if(newwhite[x][y]==0 && newwhite[x+1][y]==2 && newwhite[x+2][y]==0 && newwhite[x+3][y] == 2 && newwhite[x+4][y] ==2 && newwhite[x+5][y] ==2 &&newwhite[x+6][y] ==0 &&
                 newwhite[x+7][y] ==1)
                act[m][n] += 3500;
             //02220201
             if(newwhite[x][y]==0 && newwhite[x+1][y]==2 && newwhite[x+2][y]==2 && newwhite[x+3][y] == 2 && newwhite[x+4][y] ==0 && newwhite[x+5][y] ==2 &&newwhite[x+6][y] ==0 &&
                 newwhite[x+7][y] ==1)
                act[m][n] += 3500;



             //양쪽 다 막혔을 때

             //12022021
             if(newwhite[x][y]==1 && newwhite[x+1][y]==2 && newwhite[x+2][y]==0 && newwhite[x+3][y] == 2 && newwhite[x+4][y] ==2 && newwhite[x+5][y] ==0 &&newwhite[x+6][y] ==2 &&newwhite[x+7][y] ==1 )
                act[m][n] += 1000;
             //12200221
             if(newwhite[x][y]==1 && newwhite[x+1][y]==2 && newwhite[x+2][y]==2 && newwhite[x+3][y] == 0 && newwhite[x+4][y] ==0 && newwhite[x+5][y] ==2 &&newwhite[x+6][y] ==2 &&newwhite[x+7][y] ==1 )
                act[m][n] += 1000;
             //12220021
             if(newwhite[x][y]==1 && newwhite[x+1][y]==2 && newwhite[x+2][y]==2 && newwhite[x+3][y] == 2 && newwhite[x+4][y] ==0 && newwhite[x+5][y] ==0 &&newwhite[x+6][y] ==2 &&newwhite[x+7][y] ==1)
                act[m][n] += 1000;
             //12002221
             if(newwhite[x][y]==1 && newwhite[x+1][y]==2 && newwhite[x+2][y]==0 && newwhite[x+3][y] == 0 && newwhite[x+4][y] ==2 && newwhite[x+5][y] ==2 &&newwhite[x+6][y] ==2 &&newwhite[x+7][y] ==1 )
                act[m][n] += 1000;
             //12202021
             if(newwhite[x][y]==1 && newwhite[x+1][y]==2 && newwhite[x+2][y]==2 && newwhite[x+3][y] == 0 && newwhite[x+4][y] ==2 && newwhite[x+5][y] ==2 &&newwhite[x+6][y] ==2 &&newwhite[x+7][y] ==1)
                act[m][n] += 1000;
             //12020221
             if(newwhite[x][y]==1 && newwhite[x+1][y]==2 && newwhite[x+2][y]==0 && newwhite[x+3][y] == 2 && newwhite[x+4][y] ==0 && newwhite[x+5][y] ==2 &&newwhite[x+6][y] ==2 &&newwhite[x+7][y] ==1 )
                act[m][n] += 1000;
             //10222201
           if(newwhite[x][y]==1 && newwhite[x+1][y]==0 && newwhite[x+2][y]==2 && newwhite[x+3][y] == 2 && newwhite[x+4][y] ==2 && newwhite[x+5][y] ==2 &&newwhite[x+6][y] ==0 &&newwhite[x+7][y] ==1 )
                act[m][n] += 1000;
           //10222021
           if(newwhite[x][y]==1 && newwhite[x+1][y]==0 && newwhite[x+2][y]==2 && newwhite[x+3][y] == 2 && newwhite[x+4][y] ==2 && newwhite[x+5][y] ==0 &&newwhite[x+6][y] ==2 &&newwhite[x+7][y] ==1 )
                act[m][n] += 1000;
           //10220221
           if(newwhite[x][y]==1 && newwhite[x+1][y]==0 && newwhite[x+2][y]==2 && newwhite[x+3][y] == 2 && newwhite[x+4][y] ==0 && newwhite[x+5][y] ==2 &&newwhite[x+6][y] ==2 &&newwhite[x+7][y] ==1 )
                act[m][n] += 1000;
            //10202221
           if(newwhite[x][y]==1 && newwhite[x+1][y]==0 && newwhite[x+2][y]==2 && newwhite[x+3][y] == 0 && newwhite[x+4][y] ==2 && newwhite[x+5][y] ==2 &&newwhite[x+6][y] ==2 &&newwhite[x+7][y] ==1 )
                act[m][n] += 1000;
           //10022221
           if(newwhite[x][y]==1 && newwhite[x+1][y]==0 && newwhite[x+2][y]==0 && newwhite[x+3][y] == 2 && newwhite[x+4][y] ==2 && newwhite[x+5][y] ==2 &&newwhite[x+6][y] ==2 &&newwhite[x+7][y] ==1 )
                act[m][n] += 1000;
           //12022201
           if(newwhite[x][y]==1 && newwhite[x+1][y]==2 && newwhite[x+2][y]==0 && newwhite[x+3][y] == 2 && newwhite[x+4][y] ==2 && newwhite[x+5][y] ==2 &&newwhite[x+6][y] ==0 &&newwhite[x+7][y] ==1 )
                act[m][n] += 1000;
           //12202201
           if(newwhite[x][y]==1 && newwhite[x+1][y]==2 && newwhite[x+2][y]==2 && newwhite[x+3][y] == 0 && newwhite[x+4][y] ==2 && newwhite[x+5][y] ==2 &&newwhite[x+6][y] ==0 &&newwhite[x+7][y] ==1 )
                act[m][n] += 1000;
           //12220201
           if(newwhite[x][y]==1 && newwhite[x+1][y]==2 && newwhite[x+2][y]==2 && newwhite[x+3][y] == 2 && newwhite[x+4][y] ==0 && newwhite[x+5][y] ==2 &&newwhite[x+6][y] ==0 &&newwhite[x+7][y] ==1 )
                act[m][n] += 1000;
           //12222001
           if(newwhite[x][y]==1 && newwhite[x+1][y]==2 && newwhite[x+2][y]==2 && newwhite[x+3][y] == 2 && newwhite[x+4][y] ==2 && newwhite[x+5][y] ==0 &&newwhite[x+6][y] ==0 &&newwhite[x+7][y] ==1 )
                act[m][n] += 1000;
             }
             }
             newwhite[m][n] = 0;
             }
             }


}

void AI::W_AI_2_slash_check()
{
    for(int m=0 ; m<19 ; m++)
    {
      for(int n=0 ; n<19 ; n++)
      {
          if( newwhite[m][n] == 0 )
          {
          newwhite[m][n] = 2;
          }
          else if( newwhite[m][n] == 1 || newwhite[m][n] == 2 )
          {
              continue;
          }

          for(int x=0; x<19; x++)
          {
              for(int y=0; y<19; y++)
              {
            //00022000
            if( newwhite[x-2][y-2] == 0 && newwhite[x-1][y-1] == 0 && newwhite[x][y] == 0 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 2 &&
                newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] == 0 && newwhite[x+5][y+5] == 0 )
                act[m][n] += 2000;
            //0020200
            if( newwhite[x-1][y-1] == 0 && newwhite[x][y] == 0 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 0 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] == 0 &&
                newwhite[x+5][y+5] == 0 )
                act[m][n] += 1500;
            //020020
            if( newwhite[x][y] == 0 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 0 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] == 2 && newwhite[x+5][y+5] == 0 )
                act[m][n] += 1000;
            //여기까지 양쪽에 안 막힌, 흰 돌이 2개가 발견 될 때 경우의 수들

            //122000
            if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 2 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] == 0 && newwhite[x+5][y+5] == 0 )
                act[m][n] += 500;
            //120200
            if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 0 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] == 0 && newwhite[x+5][y+5] == 0 )
                act[m][n] += 500;
            //120020
            if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 0 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] == 2 && newwhite[x+5][y+5] == 0 )
                act[m][n] += 500;
            //102200
            if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 0 && newwhite[x+2][y+2] == 2 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] == 0 && newwhite[x+5][y+5] == 0 )
                act[m][n] += 800;
            //102020
            if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 0 && newwhite[x+2][y+2] == 2 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] == 2 && newwhite[x+5][y+5] == 0 )
                act[m][n] += 800;
            //여기까지 왼쪽에 검은돌로 막힌 경우.
            //오른쪽에 검은돌로 막힌 경우는 이 대칭으로만 작성해주면됌

            //000221
            if( newwhite[x-2][y-2] == 0 && newwhite[x-1][y-1] == 0 && newwhite[x][y] == 0 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 2 && newwhite[x+3][y+3] == 1 )
                act[m][n] += 500;
            //002021
            if( newwhite[x-1][y-1] == 0 && newwhite[x][y] == 0 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 0 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] == 1 )
                act[m][n] += 500;
            //020021
            if( newwhite[x][y] == 0 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 0 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] == 2 && newwhite[x+5][y+5] == 1 )
                act[m][n] += 500;
            //002201
            if( newwhite[x-1][y-1] == 0 && newwhite[x][y] == 0 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 2 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] == 1 )
                act[m][n] += 800;
            //020201
            if( newwhite[x][y] == 0 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 0 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] == 0 && newwhite[x+5][y+5] == 1 )
                act[m][n] += 800;
            //여기까지 한쪽이 막힌 경우.
            //그 다음은 양쪽이 막힌 경우. 양쪽이 막힌 경우는 안이 6칸일 경우만 따지자.

            //12200001
            if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 2 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] == 0 && newwhite[x+5][y+5] == 0 &&
                newwhite[x+6][y+6] == 0 && newwhite[x+7][y+7] == 1 )
                act[m][n] += 300;
            //12020001
            if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 0 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] == 0 && newwhite[x+5][y+5] == 0 &&
                newwhite[x+6][y+6] == 0 && newwhite[x+7][y+7] == 1 )
                act[m][n] += 300;
            //12002001
            if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 0 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] == 2 && newwhite[x+5][y+5] == 0 &&
                newwhite[x+6][y+6] == 0 && newwhite[x+7][y+7] == 1 )
                act[m][n] += 300;
            //12000201
            if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 0 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] == 0 && newwhite[x+5][y+5] == 2 &&
                newwhite[x+6][y+6] == 0 && newwhite[x+7][y+7] == 1 )
                act[m][n] += 300;
            //12000021
            if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 0 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] == 0 && newwhite[x+5][y+5] == 0 &&
                newwhite[x+6][y+6] == 2 && newwhite[x+7][y+7] == 1 )
                act[m][n] += 300;
            //10220001
            if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 0 && newwhite[x+2][y+2] == 2 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] == 0 && newwhite[x+5][y+5] == 0 &&
                newwhite[x+6][y+6] == 0 && newwhite[x+7][y+7] == 1 )
                act[m][n] += 300;
            //10202001
            if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 0 && newwhite[x+2][y+2] == 2 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] == 2 && newwhite[x+5][y+5] == 0 &&
                newwhite[x+6][y+6] == 0 && newwhite[x+7][y+7] == 1 )
                act[m][n] += 300;
            //10200201
            if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 0 && newwhite[x+2][y+2] == 2 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] == 0 && newwhite[x+5][y+5] == 2 &&
                newwhite[x+6][y+6] == 0 && newwhite[x+7][y+7] == 1 )
                act[m][n] += 300;
            //10200021
            if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 0 && newwhite[x+2][y+2] == 2 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] == 0 && newwhite[x+5][y+5] == 0 &&
                newwhite[x+6][y+6] == 2 && newwhite[x+7][y+7] == 1 )
                act[m][n] += 300;
            //10022001
            if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 0 && newwhite[x+2][y+2] == 0 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] == 2 && newwhite[x+5][y+5] == 0 &&
                newwhite[x+6][y+6] == 0 && newwhite[x+7][y+7] == 1 )
                act[m][n] += 300;
            //10020201
            if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 0 && newwhite[x+2][y+2] == 0 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] == 0 && newwhite[x+5][y+5] == 2 &&
                newwhite[x+6][y+6] == 0 && newwhite[x+7][y+7] == 1 )
                act[m][n] += 300;
            //10020021
            if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 0 && newwhite[x+2][y+2] == 0 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] == 0 && newwhite[x+5][y+5] == 0 &&
                newwhite[x+6][y+6] == 2 && newwhite[x+7][y+7] == 1 )
                act[m][n] += 300;
            //10002201
            if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 0 && newwhite[x+2][y+2] == 0 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] == 2 && newwhite[x+5][y+5] == 2 &&
                newwhite[x+6][y+6] == 0 && newwhite[x+7][y+7] == 1 )
                act[m][n] += 300;
            //10002021
            if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 0 && newwhite[x+2][y+2] == 0 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] == 0 && newwhite[x+5][y+5] == 2 &&
                newwhite[x+6][y+6] == 0 && newwhite[x+7][y+7] == 1 )
                act[m][n] += 300;
            //10000221
            if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 0 && newwhite[x+2][y+2] == 0 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] == 0 && newwhite[x+5][y+5] == 2 &&
                newwhite[x+6][y+6] == 2 && newwhite[x+7][y+7] == 1 )
                act[m][n] += 300;
              }
          }
          newwhite[m][n] = 0;
      }
    }

}

void AI::W_AI_3_slash_check()
{
    for(int m=0 ; m<19 ; m++)
        {
          for(int n=0 ; n<19 ; n++)
          {
              if( newwhite[m][n] == 0 )
              {
              newwhite[m][n] = 2;
              }
              else if( newwhite[m][n] == 1 || newwhite[m][n] == 2 )
              {
                  continue;
              }

              for(int x=0; x<19; x++)
              {
                  for(int y=0; y<19; y++)
                  {
                //000222000
                if( newwhite[x-1][y-1] == 0 && newwhite[x][y] == 0 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 2 && newwhite[x+3][y+3] == 2&& newwhite[x+4][y+4]==0 &&
                    newwhite[x+5][y+5] == 0 )
                    act[m][n] += 5000;
                //00202200
                if( newwhite[x-1][y-1] == 0 && newwhite[x][y] == 0 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 0 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] == 2 &&
                    newwhite[x+5][y+5]==0 && newwhite[x+6][y+6] == 0 )
                    act[m][n] += 3500;
                //00220200
                if( newwhite[x-1][y-1] == 0 && newwhite[x][y] == 0 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 2 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] == 2 &&
                    newwhite[x+5][y+5] == 0 && newwhite[x+6][y+6] == 0 )
                    act[m][n] += 3500;
                //0200220
                if( newwhite[x][y] == 0 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 0 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] == 2 && newwhite[x+5][y+5] == 2
                    &&newwhite[x+6][y+6] ==0 )
                    act[m][n] += 3000;
                //0202020
                if( newwhite[x][y] == 0 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 0 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] == 0 && newwhite[x+5][y+5] == 2
                    &&newwhite[x+6][y+6]==0 )
                    act[m][n] += 3000;
                //0220020
                if( newwhite[x][y] == 0 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 2 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] == 0 && newwhite[x+5][y+5] == 2
                    && newwhite[x+6][y+6] ==0 )
                    act[m][n] += 3000;
                //여기까지 양쪽에 안 막힌, 흰 돌이 2개가 발견 될 때 경우의 수들

                //122200
                if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 2 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] ==0 && newwhite[x+5][y+5] == 0 )
                    act[m][n] += 1000;
                //1202200
                if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 0 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] == 2 && newwhite[x+5][y+5] ==0 &&
                    newwhite[x][y+6] == 0 )
                    act[m][n] += 1000;
                //1220200
                if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 2 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] == 2 && newwhite[x+5][y+5] == 0 &&
                    newwhite[x+6][y+6] == 0 )
                    act[m][n] += 1000;
                //1022200
                if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 0 && newwhite[x+2][y+2] == 2 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] == 2 && newwhite[x+5][y+5] ==0 &&
                    newwhite[x+6][y+6] == 0 )
                    act[m][n] += 1300;
                //1200220
                if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 0 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] == 2 && newwhite[x+5][y+5] == 2 &&
                newwhite[x+6][y+6] ==0 )
                    act[m][n] += 1300;
                //1220020
                if( newwhite[x][y] == 1 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 2 && newwhite[x][y+3] == 0 && newwhite[x][y+4] == 0 && newwhite[x][y+5] == 2 &&
                    newwhite[x][y+6] == 0 )
                    act[m][n] += 1000;
                //1202020
                if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 0 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] == 0 && newwhite[x+5][y+5] == 2 &&
                    newwhite[x+6][y+6] ==0 )
                    act[m][n] += 1000;
                //1020220
                if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 0 && newwhite[x+2][y+2] == 2 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] == 2 && newwhite[x+5][y+5] == 2 &&
                    newwhite[x+6][y+6] == 0)
                    act[m][n] += 1300;

                //여기까지 왼쪽에 검은돌로 막힌 경우.
                //오른쪽에 검은돌로 막힌 경우는 이 대칭으로만 작성해주면됌

                //002221
                if( newwhite[x-1][y-1] == 0 && newwhite[x][y] == 0 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 2 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] == 1 )
                    act[m][n] += 1000;
                //0022021
                if( newwhite[x-1][y-1] == 0 && newwhite[x][y] == 0 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 2 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] == 2 &&
                    newwhite[x+5][y+5]==1 )
                    act[m][n] += 1000;
                //0020221
                if( newwhite[x-1][y-1] == 0 && newwhite[x][y] == 0 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 0 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] == 2 &&
                    newwhite[x+5][y+5] == 1 )
                    act[m][n] += 1000;
                //0022201
                if( newwhite[x-1][y-1] == 0 && newwhite[x][y] == 0 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 2 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] == 0 &&
                    newwhite[x+5][y+5] == 1 )
                    act[m][n] += 1300;
                //0220021
                if( newwhite[x][y] == 0 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 2 && newwhite[x][y+3] == 0 && newwhite[x][y+4] == 0 && newwhite[x][y+5] == 2 &&
                    newwhite[x][y+6] == 1 )
                    act[m][n] += 1300;
                //0200221
                if( newwhite[x][y] == 0 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 0 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] == 2 && newwhite[x+5][y+5] == 2 &&
                    newwhite[x+6][y+6] == 1 )
                    act[m][n] += 1000;
                //0202021
                if( newwhite[x][y] == 0 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 0 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] == 0 && newwhite[x+5][y+5] == 2 &&
                    newwhite[x+6][y+6] == 1 )
                    act[m][n] += 1000;
                //0220201
                if( newwhite[x][y] == 0 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 2 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] == 2 && newwhite[x+5][y+5] == 0 &&
                    newwhite[x+6][y+6] == 1 )
                    act[m][n] += 1300;

                //여기까지 한쪽이 막힌 경우.
                //그 다음은 양쪽이 막힌 경우. 양쪽이 막힌 경우는 안이 6칸일 경우만 따지자.

                //12220001
                if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 2 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] == 0 && newwhite[x+5][y+5] == 0 &&
                    newwhite[x+6][y+6] == 0 && newwhite[x+7][y+7] == 1 )
                    act[m][n] += 300;
                //12022001
                if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 0 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] == 2 && newwhite[x+5][y+5] == 0 &&
                    newwhite[x+6][y+6] == 0 && newwhite[x+7][y+7] == 1 )
                    act[m][n] += 300;
                //12002201
                if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 0 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] == 2 && newwhite[x+5][y+5] == 2 &&
                    newwhite[x+6][y+6] == 0 && newwhite[x+7][y+7] == 1 )
                    act[m][n] += 300;
                //12000221
                if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 0 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] == 0 && newwhite[x+5][y+5] == 2 &&
                    newwhite[x+6][y+6] == 2 && newwhite[x+7][y+7] == 1 )
                    act[m][n] += 300;
                //12202001
                if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 2 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] == 2 && newwhite[x+5][y+5] == 0 &&
                    newwhite[x+6][y+6] == 0 && newwhite[x+7][y+7] == 1 )
                    act[m][n] += 300;
                //12200201
                if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 2 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] == 0 && newwhite[x+5][y+5] == 2 &&
                    newwhite[x+6][y+6] == 0 && newwhite[x+7][y+7] == 1 )
                    act[m][n] += 300;
                //12200021
                if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 2 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] == 0 && newwhite[x+5][y+5] == 0 &&
                    newwhite[x+6][y+6] == 2 && newwhite[x+7][y+7] == 1 )
                    act[m][n] += 300;
                //12002021
                if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 0 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] == 2 && newwhite[x+5][y+5] == 0 &&
                    newwhite[x+6][y+6] == 2 && newwhite[x+7][y+7] == 1 )
                    act[m][n] += 300;
                //12020021
                if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 0 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] == 0 && newwhite[x+5][y+5] == 0 &&
                    newwhite[x+6][y+6] == 2 && newwhite[x+7][y+7] == 1 )
                    act[m][n] += 300;
                //12020201
                if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 0 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] == 0 && newwhite[x+5][y+5] == 2 &&
                    newwhite[x+6][y+6] == 0 && newwhite[x+7][y+7] == 1 )
                    act[m][n] += 300;
                //10222001
                if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 0 && newwhite[x+2][y+2] == 2 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] == 2 && newwhite[x+5][y+5] == 0 &&
                    newwhite[x+6][y+6] == 0 && newwhite[x+7][y+7] == 1 )
                    act[m][n] += 300;
                //10202201
                if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 0 && newwhite[x+2][y+2] == 2 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] == 2 && newwhite[x+5][y+5] == 2 &&
                    newwhite[x+6][y+6] == 0 && newwhite[x+7][y+7] == 1 )
                    act[m][n] += 300;
                //10200221
                if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 0 && newwhite[x+2][y+2] == 2 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] == 0 && newwhite[x+5][y+5] == 2 &&
                    newwhite[x+6][y+6] == 2 && newwhite[x+7][y+7] == 1 )
                    act[m][n] += 300;
                //10220201
                if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 0 && newwhite[x+2][y+2] == 2 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] == 0 && newwhite[x+5][y+5] == 2 &&
                    newwhite[x+6][y+6] == 0 && newwhite[x+7][y+7] == 1 )
                    act[m][n] += 300;
                //10220021
                if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 0 && newwhite[x+2][y+2] == 2 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] == 0 && newwhite[x+5][y+5] == 0 &&
                    newwhite[x+6][y+6] == 2 && newwhite[x+7][y+7] == 1 )
                    act[m][n] += 300;
                //10022021
                if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 0 && newwhite[x+2][y+2] == 0 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] == 2 && newwhite[x+5][y+5] == 0 &&
                    newwhite[x+6][y+6] == 2 && newwhite[x+7][y+7] == 1 )
                    act[m][n] += 300;
                //10022201
                if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 0 && newwhite[x+2][y+2] == 0 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] == 2 && newwhite[x+5][y+5] == 2 &&
                    newwhite[x+6][y+6] == 0 && newwhite[x+7][y+7] == 1 )
                    act[m][n] += 300;
                //10020221
                if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 0 && newwhite[x+2][y+2] == 0 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] == 0 && newwhite[x+5][y+5] == 2 &&
                    newwhite[x+6][y+6] == 2 && newwhite[x+7][y+7] == 1 )
                    act[m][n] += 300;
                //10002221
                if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 0 && newwhite[x+2][y+2] == 0 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] == 0 && newwhite[x+5][y+5] == 2 &&
                    newwhite[x+6][y+6] == 2 && newwhite[x+7][y+7] == 1 )
                    act[m][n] += 300;
                //10202021
                if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 0 && newwhite[x+2][y+2] == 2 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] == 2 && newwhite[x+5][y+5] == 0 &&
                    newwhite[x+6][y+6] == 2 && newwhite[x+7][y+7] == 1 )
                    act[m][n] += 300;
                    }
              }
              newwhite[m][n] = 0;
          }
        }

}

void AI::W_AI_4_slash_check()
{
    for(int m=0 ; m<19 ; m++)
        {
          for(int n=0 ; n<19 ; n++)
          {
              if( newwhite[m][n] == 0 )
              {
              newwhite[m][n] = 2;
              }
              else if( newwhite[m][n] == 1 || newwhite[m][n] == 2 )
              {
                  continue;
              }

              for(int x=0; x<19; x++)
              {
                  for(int y=0; y<19; y++)
                  {

       /*4개 -> 안막혔을 때*/
             //00222200
             if( newwhite[x-1][y-1] == 0 && newwhite[x][y]== 0 && newwhite[x+1][y+1]== 2 && newwhite[x+2][y+2]== 2 &&newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] == 2 &&
                 newwhite[x+5][y+5] == 0 )
                act[m][n] += 10000;
             //002022200
             if( newwhite[x-1][y-1] == 0 && newwhite[x][y]==0 && newwhite[x+1][y+1]==2 && newwhite[x+2][y+2]==0 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] ==2 &&
                 newwhite[x+5][y+5]==2 &&newwhite[x+6][y+6] ==0 && newwhite[x+7][y+7] == 0 )
                act[m][n] += 7000;
             //002220200
             if( newwhite[x-1][y-1] == 0 && newwhite[x][y]== 0 && newwhite[x+1][y+1]== 2 && newwhite[x+2][y+2]== 2 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] == 0 &&
                 newwhite[x+5][y+5] ==2 &&newwhite[x+6][y+6] == 0 && newwhite[x+7][y+7] == 0 )
                act[m][n] += 7000;
             //002202200
             if( newwhite[x-1][y-1] == 0 && newwhite[x][y]== 0 && newwhite[x+1][y+1]== 2 && newwhite[x+2][y+2]== 2 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] == 2 &&
                 newwhite[x+5][y+5] == 2 && newwhite[x+6][y+6] == 0 && newwhite[x+7][y+7] == 0 )
                act[m][n] += 7000;
             //02220020
             if( newwhite[x][y]==0 && newwhite[x+1][y+1]==2 && newwhite[x+2][y+2]==2 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] ==0 && newwhite[x+5][y+5] ==0 &&
                 newwhite[x+6][y+6] ==2 && newwhite[x+7][y+7] ==0 )
                act[m][n] += 5000;
             //02002220
             if( newwhite[x][y] == 0 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 0 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] == 2 && newwhite[x+5][y+5] == 2 &&
                 newwhite[x+6][y+6] == 2 && newwhite[x+7][y+7] == 0 )
                act[m][n] += 5000;
             //02202020
             if( newwhite[x][y] == 0 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 2 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] == 2 && newwhite[x+5][y+5] == 2 &&
                 newwhite[x+6][y+6] == 2 && newwhite[x+7][y+7] == 0 )
                act[m][n] += 4000;
             //02020220
             if(newwhite[x][y] == 0 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 0 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] == 0 && newwhite[x+5][y+5] == 2 &&
                 newwhite[x+6][y+6] == 2 && newwhite[x+7][y+7] == 0 )
                act[m][n] += 4000;

             //4개 한쪽 막혔을 때
             //122220
             if(newwhite[x][y]==1 && newwhite[x+1][y+1]==2 && newwhite[x+2][y+2]==2 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] ==2 && newwhite[x+5][y+5] ==0)
                act[m][n] += 3500;
             //1202220
             if(newwhite[x][y]==1 && newwhite[x+1][y+1]==2 && newwhite[x+2][y+2]==0 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] ==2 && newwhite[x+5][y+5] ==2 &&newwhite[x+6][y+6] ==0)
                act[m][n] += 3500;
             //1220220
             if(newwhite[x][y]==1 && newwhite[x+1][y+1]==2 && newwhite[x+2][y+2]==2 && newwhite[x+3][y+3] ==0 && newwhite[x+4][y+4] ==2 && newwhite[x+5][y+5] ==2 &&newwhite[x+6][y+6] ==0)
                act[m][n] += 3500;
             //1222020
             if(newwhite[x][y]==1 && newwhite[x+1][y+1]==2 && newwhite[x+2][y+2]==2 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] ==0 && newwhite[x+5][y+5] ==2 &&newwhite[x+6][y+6] ==0)
                act[m][n] += 3500;
             //1022220
             if(newwhite[x][y]==1 && newwhite[x+1][y+1]==0 && newwhite[x+2][y+2]==2 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] ==2 && newwhite[x+5][y+5] ==2 &&newwhite[x+6][y+6] ==0)
                act[m][n] += 3500;
             //12002220
             if(newwhite[x][y]==1 && newwhite[x+1][y+1]==2 && newwhite[x+2][y+2]==0 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] ==2 && newwhite[x+5][y+5] ==2 &&newwhite[x+6][y+6] ==2 &&
                 newwhite[x+7][y+7]==0)
                act[m][n] += 3500;
             //12020220
             if(newwhite[x][y]==1 && newwhite[x+1][y+1]==2 && newwhite[x+2][y+2]==0 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] ==0 && newwhite[x+5][y+5] ==2 &&newwhite[x+6][y+6] ==2 &&
                 newwhite[x+7][y+7]==0)
                act[m][n] += 3500;
             //12022020
             if(newwhite[x][y]==1 && newwhite[x+1][y+1]==2 && newwhite[x+2][y+2]==0 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] ==2 && newwhite[x+5][y+5] ==0 &&newwhite[x+6][y+6] ==2 &&
                 newwhite[x+7][y+7]==0)
                act[m][n] += 3500;
             //12200220
             if(newwhite[x][y]==1 && newwhite[x+1][y+1]==2 && newwhite[x+2][y+2]==2 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] ==0 && newwhite[x+5][y+5] ==2 &&newwhite[x+6][y+6] ==2 &&
                 newwhite[x+7][y+7]==0 )
                act[m][n] += 3500;
             //12202020
             if(newwhite[x][y]==1 && newwhite[x+1][y+1]==2 && newwhite[x+2][y+2]==2 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] ==2 && newwhite[x+5][y+5] ==0 &&newwhite[x+6][y+6] ==2 &&
                 newwhite[x+7][y+7]==0)
                act[m][n] += 3500;
             //12220020
             if(newwhite[x][y]==1 && newwhite[x+1][y+1]==2 && newwhite[x+2][y+2]==2 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] ==0 && newwhite[x+5][y+5] ==0 &&newwhite[x+6][y+6] ==2 &&
                 newwhite[x+7][y+7]==0)
                act[m][n] += 3500;
             //10220220
             if(newwhite[x][y]==1 && newwhite[x+1][y+1]==0 && newwhite[x+2][y+2]==2 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] ==0 && newwhite[x+5][y+5] ==2 &&newwhite[x+6][y+6] ==2 &&
                 newwhite[x+7][y+7]==0)
                act[m][n] += 3500;
             //10222020
             if(newwhite[x][y]==1 && newwhite[x+1][y+1]==0 && newwhite[x+2][y+2]==2 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] ==2 && newwhite[x+5][y+5] ==0 &&newwhite[x+6][y+6] ==2 &&
                 newwhite[x+7][y+7]==0)
                act[m][n] += 3500;
             //10202220
             if(newwhite[x][y]==1 && newwhite[x+1][y+1]==0 && newwhite[x+2][y+2]==2 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] ==2 && newwhite[x+5][y+5] ==2 &&newwhite[x+6][y+6] ==2 &&
                 newwhite[x+7][y+7]==0)
                act[m][n] += 3500;


             //4개 한쪽 막혔을 때 reverse
             //022221
             if(newwhite[x][y]==0 && newwhite[x+1][y+1]==2 && newwhite[x+2][y+2]==2 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] ==2 && newwhite[x+5][y+5] ==1)
                act[m][n] += 3500;
             //0222021
             if(newwhite[x][y]==0 && newwhite[x+1][y+1]==2 && newwhite[x+2][y+2]==2 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] ==0 && newwhite[x+5][y+5] ==2 &&newwhite[x+6][y+6] ==1)
                act[m][n] += 3500;
             //0220221
             if(newwhite[x][y]==0 && newwhite[x+1][y+1]==2 && newwhite[x+2][y+2]==2 && newwhite[x+3][y+3] ==0 && newwhite[x+4][y+4] ==2 && newwhite[x+5][y+5] ==2 &&newwhite[x+6][y+6] ==1)
                act[m][n] += 3500;
             //0202221
             if(newwhite[x][y]==0 && newwhite[x+1][y+1]==2 && newwhite[x+2][y+2]==0 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] ==2 && newwhite[x+5][y+5] ==2 &&newwhite[x+6][y+6] ==1)
                act[m][n] += 3500;
             //0222201
             if(newwhite[x][y]==0 && newwhite[x+1][y+1]==2 && newwhite[x+2][y+2]==2 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] ==2 && newwhite[x+5][y+5] ==0 &&newwhite[x+6][y+6] ==1)
                act[m][n] += 3500;
             //02220021
             if(newwhite[x][y]==0 && newwhite[x+1][y+1]==2 && newwhite[x+2][y+2]==2 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] ==0 && newwhite[x+5][y+5] ==0 &&newwhite[x+6][y+6] ==2 &&
                 newwhite[x+7][y+7] ==1)
                act[m][n] += 3500;
             //02202021
             if(newwhite[x][y]==0 && newwhite[x+1][y+1]==2 && newwhite[x+2][y+2]==2 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] ==2 && newwhite[x+5][y+5] ==0 &&newwhite[x+6][y+6] ==2 &&
                 newwhite[x+7][y+7] ==1)
                act[m][n] += 3500;
             //02022021
             if(newwhite[x][y]==0 && newwhite[x+1][y+1]==2 && newwhite[x+2][y+2]==0 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] ==2 && newwhite[x+5][y+5] ==0 &&newwhite[x+6][y+6] ==2 &&
                 newwhite[x+7][y+7] ==1)
                act[m][n] += 3500;
             //02200221
             if(newwhite[x][y]==0 && newwhite[x+1][y+1]==2 && newwhite[x+2][y+2]==2 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] ==0 && newwhite[x+5][y+5] ==2 &&newwhite[x+6][y+6] ==2 &&
                 newwhite[x+7][y+7] ==1 )
                act[m][n] += 3500;
             //02020221
             if(newwhite[x][y]==0 && newwhite[x+1][y+1]==2 && newwhite[x+2][y+2]==0 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] ==0 && newwhite[x+5][y+5] ==2 &&newwhite[x+6][y+6] ==2 &&
                 newwhite[x+7][y+7] ==1)
                act[m][n] += 3500;
             //02002221
             if(newwhite[x][y]==0 && newwhite[x+1][y+1]==2 && newwhite[x+2][y+2]==0 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] ==2 && newwhite[x+5][y+5] ==2 &&newwhite[x+6][y+6] ==2 &&
                 newwhite[x+7][y+7] ==1)
                act[m][n] += 3500;
             //02202201
             if(newwhite[x][y]==0 && newwhite[x+1][y+1]==2 && newwhite[x+2][y+2]==2 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] ==2 && newwhite[x+5][y+5] ==2 &&newwhite[x+6][y+6] ==0 &&
                 newwhite[x+7][y+7] ==1)
                act[m][n] += 3500;
             //02022201
             if(newwhite[x][y]==0 && newwhite[x+1][y+1]==2 && newwhite[x+2][y+2]==0 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] ==2 && newwhite[x+5][y+5] ==2 &&newwhite[x+6][y+6] ==0 &&
                 newwhite[x+7][y+7] ==1)
                act[m][n] += 3500;
             //02220201
             if(newwhite[x][y]==0 && newwhite[x+1][y+1]==2 && newwhite[x+2][y+2]==2 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] ==0 && newwhite[x+5][y+5] ==2 &&newwhite[x+6][y+6] ==0 &&
                 newwhite[x+7][y+7] ==1)
                act[m][n] += 3500;



             //양쪽 다 막혔을 때

             //12022021
             if(newwhite[x][y]==1 && newwhite[x+1][y+1]==2 && newwhite[x+2][y+2]==0 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] ==2 && newwhite[x+5][y+5] ==0 &&newwhite[x+6][y+6] ==2 &&newwhite[x+7][y+7] ==1 )
                act[m][n] += 1000;
             //12200221
             if(newwhite[x][y]==1 && newwhite[x+1][y+1]==2 && newwhite[x+2][y+2]==2 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] ==0 && newwhite[x+5][y+5] ==2 &&newwhite[x+6][y+6] ==2 &&newwhite[x+7][y+7] ==1 )
                act[m][n] += 1000;
             //12220021
             if(newwhite[x][y]==1 && newwhite[x+1][y+1]==2 && newwhite[x+2][y+2]==2 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] ==0 && newwhite[x+5][y+5] ==0 &&newwhite[x+6][y+6] ==2 &&newwhite[x+7][y+7] ==1)
                act[m][n] += 1000;
             //12002221
             if(newwhite[x][y]==1 && newwhite[x+1][y+1]==2 && newwhite[x+2][y+2]==0 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] ==2 && newwhite[x+5][y+5] ==2 &&newwhite[x+6][y+6] ==2 &&newwhite[x+7][y+7] ==1 )
                act[m][n] += 1000;
             //12202021
             if(newwhite[x][y]==1 && newwhite[x+1][y+1]==2 && newwhite[x+2][y+2]==2 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] ==2 && newwhite[x+5][y+5] ==2 &&newwhite[x+6][y+6] ==2 &&newwhite[x+7][y+7] ==1)
                act[m][n] += 1000;
             //12020221
             if(newwhite[x][y]==1 && newwhite[x+1][y+1]==2 && newwhite[x+2][y+2]==0 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] ==0 && newwhite[x+5][y+5] ==2 &&newwhite[x+6][y+6] ==2 &&newwhite[x+7][y+7] ==1 )
                act[m][n] += 1000;
             //10222201
           if(newwhite[x][y]==1 && newwhite[x+1][y+1]==0 && newwhite[x+2][y+2]==2 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] ==2 && newwhite[x+5][y+5] ==2 &&newwhite[x+6][y+6] ==0 &&newwhite[x+7][y+7] ==1 )
                act[m][n] += 1000;
           //10222021
           if(newwhite[x][y]==1 && newwhite[x+1][y+1]==0 && newwhite[x+2][y+2]==2 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] ==2 && newwhite[x+5][y+5] ==0 &&newwhite[x+6][y+6] ==2 &&newwhite[x+7][y+7] ==1 )
                act[m][n] += 1000;
           //10220221
           if(newwhite[x][y]==1 && newwhite[x+1][y+1]==0 && newwhite[x+2][y+2]==2 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] ==0 && newwhite[x+5][y+5] ==2 &&newwhite[x+6][y+6] ==2 &&newwhite[x+7][y+7] ==1 )
                act[m][n] += 1000;
            //10202221
           if(newwhite[x][y]==1 && newwhite[x+1][y+1]==0 && newwhite[x+2][y+2]==2 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] ==2 && newwhite[x+5][y+5] ==2 &&newwhite[x+6][y+6] ==2 &&newwhite[x+7][y+7] ==1 )
                act[m][n] += 1000;
           //10022221
           if(newwhite[x][y]==1 && newwhite[x+1][y+1]==0 && newwhite[x+2][y+2]==0 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] ==2 && newwhite[x+5][y+5] ==2 &&newwhite[x+6][y+6] ==2 &&newwhite[x+7][y+7] ==1 )
                act[m][n] += 1000;
           //12022201
           if(newwhite[x][y]==1 && newwhite[x+1][y+1]==2 && newwhite[x+2][y+2]==0 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] ==2 && newwhite[x+5][y+5] ==2 &&newwhite[x+6][y+6] ==0 &&newwhite[x+7][y+7] ==1 )
                act[m][n] += 1000;
           //12202201
           if(newwhite[x][y]==1 && newwhite[x+1][y+1]==2 && newwhite[x+2][y+2]==2 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] ==2 && newwhite[x+5][y+5] ==2 &&newwhite[x+6][y+6] ==0 &&newwhite[x+7][y+7] ==1 )
                act[m][n] += 1000;
           //12220201
           if(newwhite[x][y]==1 && newwhite[x+1][y+1]==2 && newwhite[x+2][y+2]==2 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] ==0 && newwhite[x+5][y+5] ==2 &&newwhite[x+6][y+6] ==0 &&newwhite[x+7][y+7] ==1 )
                act[m][n] += 1000;
           //12222001
           if(newwhite[x][y]==1 && newwhite[x+1][y+1]==2 && newwhite[x+2][y+2]==2 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] ==2 && newwhite[x+5][y+5] ==0 &&newwhite[x+6][y+6] ==0 &&newwhite[x+7][y+7] ==1 )
                act[m][n] += 1000;
             }
             }
             newwhite[m][n] = 0;
             }
             }

}



void AI::W_AI_2_in_slash_check()
{
    for(int m=0 ; m<19 ; m++)
        {
          for(int n=0 ; n<19 ; n++)
          {
              if( newwhite[m][n] == 0 )
              {
              newwhite[m][n] = 2;
              }
              else if( newwhite[m][n] == 1 || newwhite[m][n] == 2 )
              {
                  continue;
              }

              for(int x=0; x<19; x++)
              {
                  for(int y=0; y<19; y++)
                  {
                //00022000
                if( newwhite[x-2][y+2] == 0 && newwhite[x-1][y+1] == 0 && newwhite[x][y] == 0 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 2 &&
                    newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] == 0 && newwhite[x+5][y-5] == 0 )
                    act[m][n] += 2000;
                //0020200
                if( newwhite[x-1][y+1] == 0 && newwhite[x][y] == 0 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 0 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] == 0 &&
                    newwhite[x+5][y-5] == 0 )
                    act[m][n] += 1500;
                //020020
                if( newwhite[x][y] == 0 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 0 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] == 2 && newwhite[x+5][y-5] == 0 )
                    act[m][n] += 1000;
                //여기까지 양쪽에 안 막힌, 흰 돌이 2개가 발견 될 때 경우의 수들

                //122000
                if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 2 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] == 0 && newwhite[x+5][y-5] == 0 )
                    act[m][n] += 500;
                //120200
                if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 0 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] == 0 && newwhite[x+5][y-5] == 0 )
                    act[m][n] += 500;
                //120020
                if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 0 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] == 2 && newwhite[x+5][y-5] == 0 )
                    act[m][n] += 500;
                //102200
                if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 0 && newwhite[x+2][y-2] == 2 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] == 0 && newwhite[x+5][y-5] == 0 )
                    act[m][n] += 800;
                //102020
                if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 0 && newwhite[x+2][y-2] == 2 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] == 2 && newwhite[x+5][y-5] == 0 )
                    act[m][n] += 800;
                //여기까지 왼쪽에 검은돌로 막힌 경우.
                //오른쪽에 검은돌로 막힌 경우는 이 대칭으로만 작성해주면됌

                //000221
                if( newwhite[x-2][y+2] == 0 && newwhite[x-1][y+1] == 0 && newwhite[x][y] == 0 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 2 && newwhite[x+3][y-3] == 1 )
                    act[m][n] += 500;
                //002021
                if( newwhite[x-1][y+1] == 0 && newwhite[x][y] == 0 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 0 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] == 1 )
                    act[m][n] += 500;
                //020021
                if( newwhite[x][y] == 0 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 0 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] == 2 && newwhite[x+5][y-5] == 1 )
                    act[m][n] += 500;
                //002201
                if( newwhite[x-1][y+1] == 0 && newwhite[x][y] == 0 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 2 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] == 1 )
                    act[m][n] += 800;
                //020201
                if( newwhite[x][y] == 0 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 0 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] == 0 && newwhite[x+5][y-5] == 1 )
                    act[m][n] += 800;
                //여기까지 한쪽이 막힌 경우.
                //그 다음은 양쪽이 막힌 경우. 양쪽이 막힌 경우는 안이 6칸일 경우만 따지자.

                //12200001
                if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 2 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] == 0 && newwhite[x+5][y-5] == 0 &&
                    newwhite[x+6][y-6] == 0 && newwhite[x+7][y-7] == 1 )
                    act[m][n] += 300;
                //12020001
                if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 0 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] == 0 && newwhite[x+5][y-5] == 0 &&
                    newwhite[x+6][y-6] == 0 && newwhite[x+7][y-7] == 1 )
                    act[m][n] += 300;
                //12002001
                if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 0 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] == 2 && newwhite[x+5][y-5] == 0 &&
                    newwhite[x+6][y-6] == 0 && newwhite[x+7][y-7] == 1 )
                    act[m][n] += 300;
                //12000201
                if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 0 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] == 0 && newwhite[x+5][y-5] == 2 &&
                    newwhite[x+6][y-6] == 0 && newwhite[x+7][y-7] == 1 )
                    act[m][n] += 300;
                //12000021
                if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 0 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] == 0 && newwhite[x+5][y-5] == 0 &&
                    newwhite[x+6][y-6] == 2 && newwhite[x+7][y-7] == 1 )
                    act[m][n] += 300;
                //10220001
                if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 0 && newwhite[x+2][y-2] == 2 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] == 0 && newwhite[x+5][y-5] == 0 &&
                    newwhite[x+6][y-6] == 0 && newwhite[x+7][y-7] == 1 )
                    act[m][n] += 300;
                //10202001
                if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 0 && newwhite[x+2][y-2] == 2 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] == 2 && newwhite[x+5][y-5] == 0 &&
                    newwhite[x+6][y-6] == 0 && newwhite[x+7][y-7] == 1 )
                    act[m][n] += 300;
                //10200201
                if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 0 && newwhite[x+2][y-2] == 2 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] == 0 && newwhite[x+5][y-5] == 2 &&
                    newwhite[x+6][y-6] == 0 && newwhite[x+7][y-7] == 1 )
                    act[m][n] += 300;
                //10200021
                if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 0 && newwhite[x+2][y-2] == 2 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] == 0 && newwhite[x+5][y-5] == 0 &&
                    newwhite[x+6][y-6] == 2 && newwhite[x+7][y-7] == 1 )
                    act[m][n] += 300;
                //10022001
                if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 0 && newwhite[x+2][y-2] == 0 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] == 2 && newwhite[x+5][y-5] == 0 &&
                    newwhite[x+6][y-6] == 0 && newwhite[x+7][y-7] == 1 )
                    act[m][n] += 300;
                //10020201
                if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 0 && newwhite[x+2][y-2] == 0 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] == 0 && newwhite[x+5][y-5] == 2 &&
                    newwhite[x+6][y-6] == 0 && newwhite[x+7][y-7] == 1 )
                    act[m][n] += 300;
                //10020021
                if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 0 && newwhite[x+2][y-2] == 0 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] == 0 && newwhite[x+5][y-5] == 0 &&
                    newwhite[x+6][y-6] == 2 && newwhite[x+7][y-7] == 1 )
                    act[m][n] += 300;
                //10002201
                if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 0 && newwhite[x+2][y-2] == 0 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] == 2 && newwhite[x+5][y-5] == 2 &&
                    newwhite[x+6][y-6] == 0 && newwhite[x+7][y-7] == 1 )
                    act[m][n] += 300;
                //10002021
                if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 0 && newwhite[x+2][y-2] == 0 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] == 0 && newwhite[x+5][y-5] == 2 &&
                    newwhite[x+6][y-6] == 0 && newwhite[x+7][y-7] == 1 )
                    act[m][n] += 300;
                //10000221
                if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 0 && newwhite[x+2][y-2] == 0 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] == 0 && newwhite[x+5][y-5] == 2 &&
                    newwhite[x+6][y-6] == 2 && newwhite[x+7][y-7] == 1 )
                    act[m][n] += 300;
                  }
              }
              newwhite[m][n] = 0;
          }
        }

}

void AI::W_AI_3_in_slash_check()
{
    for(int m=0 ; m<19 ; m++)
        {
          for(int n=0 ; n<19 ; n++)
          {
              if( newwhite[m][n] == 0 )
              {
              newwhite[m][n] = 2;
              }
              else if( newwhite[m][n] == 1 || newwhite[m][n] == 2 )
              {
                  continue;
              }

              for(int x=0; x<19; x++)
              {
                  for(int y=0; y<19; y++)
                  {
                //000222000
                if( newwhite[x-1][y+1] == 0 && newwhite[x][y] == 0 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 2 && newwhite[x+3][y-3] == 2&& newwhite[x+4][y-4]==0 &&
                    newwhite[x+5][y-5] == 0 )
                    act[m][n] += 5000;
                //00202200
                if( newwhite[x-1][y+1] == 0 && newwhite[x][y] == 0 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 0 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] == 2 &&
                    newwhite[x+5][y-5]==0 && newwhite[x+6][y-6] == 0 )
                    act[m][n] += 3500;
                //00220200
                if( newwhite[x-1][y+1] == 0 && newwhite[x][y] == 0 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 2 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] == 2 &&
                    newwhite[x+5][y-5] == 0 && newwhite[x+6][y-6] == 0 )
                    act[m][n] += 3500;
                //0200220
                if( newwhite[x][y] == 0 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 0 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] == 2 && newwhite[x+5][y-5] == 2
                    &&newwhite[x+6][y-6] ==0 )
                    act[m][n] += 3000;
                //0202020
                if( newwhite[x][y] == 0 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 0 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] == 0 && newwhite[x+5][y-5] == 2
                    &&newwhite[x+6][y-6]==0 )
                    act[m][n] += 3000;
                //0220020
                if( newwhite[x][y] == 0 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 2 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] == 0 && newwhite[x+5][y-5] == 2
                    && newwhite[x+6][y-6] ==0 )
                    act[m][n] += 3000;
                //여기까지 양쪽에 안 막힌, 흰 돌이 2개가 발견 될 때 경우의 수들

                //122200
                if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 2 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] ==0 && newwhite[x+5][y-5] == 0 )
                    act[m][n] += 1000;
                //1202200
                if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 0 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] == 2 && newwhite[x+5][y-5] ==0 &&
                    newwhite[x][y-6] == 0 )
                    act[m][n] += 1000;
                //1220200
                if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 2 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] == 2 && newwhite[x+5][y-5] == 0 &&
                    newwhite[x+6][y-6] == 0 )
                    act[m][n] += 1000;
                //1022200
                if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 0 && newwhite[x+2][y-2] == 2 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] == 2 && newwhite[x+5][y-5] ==0 &&
                    newwhite[x+6][y-6] == 0 )
                    act[m][n] += 1300;
                //1200220
                if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 0 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] == 2 && newwhite[x+5][y-5] == 2 &&
                newwhite[x+6][y-6] ==0 )
                    act[m][n] += 1300;
                //1220020
                if( newwhite[x][y] == 1 && newwhite[x][y-1] == 2 && newwhite[x][y-2] == 2 && newwhite[x][y-3] == 0 && newwhite[x][y-4] == 0 && newwhite[x][y-5] == 2 &&
                    newwhite[x][y-6] == 0 )
                    act[m][n] += 1000;
                //1202020
                if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 0 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] == 0 && newwhite[x+5][y-5] == 2 &&
                    newwhite[x+6][y-6] ==0 )
                    act[m][n] += 1000;
                //1020220
                if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 0 && newwhite[x+2][y-2] == 2 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] == 2 && newwhite[x+5][y-5] == 2 &&
                    newwhite[x+6][y-6] == 0)
                    act[m][n] += 1300;

                //여기까지 왼쪽에 검은돌로 막힌 경우.
                //오른쪽에 검은돌로 막힌 경우는 이 대칭으로만 작성해주면됌

                //002221
                if( newwhite[x-1][y+1] == 0 && newwhite[x][y] == 0 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 2 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] == 1 )
                    act[m][n] += 1000;
                //0022021
                if( newwhite[x-1][y+1] == 0 && newwhite[x][y] == 0 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 2 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] == 2 &&
                    newwhite[x+5][y-5]==1 )
                    act[m][n] += 1000;
                //0020221
                if( newwhite[x-1][y+1] == 0 && newwhite[x][y] == 0 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 0 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] == 2 &&
                    newwhite[x+5][y-5] == 1 )
                    act[m][n] += 1000;
                //0022201
                if( newwhite[x-1][y+1] == 0 && newwhite[x][y] == 0 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 2 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] == 0 &&
                    newwhite[x+5][y-5] == 1 )
                    act[m][n] += 1300;
                //0220021
                if( newwhite[x][y] == 0 && newwhite[x][y-1] == 2 && newwhite[x][y-2] == 2 && newwhite[x][y-3] == 0 && newwhite[x][y-4] == 0 && newwhite[x][y-5] == 2 &&
                    newwhite[x][y-6] == 1 )
                    act[m][n] += 1300;
                //0200221
                if( newwhite[x][y] == 0 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 0 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] == 2 && newwhite[x+5][y-5] == 2 &&
                    newwhite[x+6][y-6] == 1 )
                    act[m][n] += 1000;
                //0202021
                if( newwhite[x][y] == 0 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 0 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] == 0 && newwhite[x+5][y-5] == 2 &&
                    newwhite[x+6][y-6] == 1 )
                    act[m][n] += 1000;
                //0220201
                if( newwhite[x][y] == 0 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 2 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] == 2 && newwhite[x+5][y-5] == 0 &&
                    newwhite[x+6][y-6] == 1 )
                    act[m][n] += 1300;

                //여기까지 한쪽이 막힌 경우.
                //그 다음은 양쪽이 막힌 경우. 양쪽이 막힌 경우는 안이 6칸일 경우만 따지자.

                //12220001
                if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 2 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] == 0 && newwhite[x+5][y-5] == 0 &&
                    newwhite[x+6][y-6] == 0 && newwhite[x+7][y-7] == 1 )
                    act[m][n] += 300;
                //12022001
                if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 0 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] == 2 && newwhite[x+5][y-5] == 0 &&
                    newwhite[x+6][y-6] == 0 && newwhite[x+7][y-7] == 1 )
                    act[m][n] += 300;
                //12002201
                if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 0 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] == 2 && newwhite[x+5][y-5] == 2 &&
                    newwhite[x+6][y-6] == 0 && newwhite[x+7][y-7] == 1 )
                    act[m][n] += 300;
                //12000221
                if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 0 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] == 0 && newwhite[x+5][y-5] == 2 &&
                    newwhite[x+6][y-6] == 2 && newwhite[x+7][y-7] == 1 )
                    act[m][n] += 300;
                //12202001
                if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 2 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] == 2 && newwhite[x+5][y-5] == 0 &&
                    newwhite[x+6][y-6] == 0 && newwhite[x+7][y-7] == 1 )
                    act[m][n] += 300;
                //12200201
                if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 2 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] == 0 && newwhite[x+5][y-5] == 2 &&
                    newwhite[x+6][y-6] == 0 && newwhite[x+7][y-7] == 1 )
                    act[m][n] += 300;
                //12200021
                if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 2 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] == 0 && newwhite[x+5][y-5] == 0 &&
                    newwhite[x+6][y-6] == 2 && newwhite[x+7][y-7] == 1 )
                    act[m][n] += 300;
                //12002021
                if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 0 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] == 2 && newwhite[x+5][y-5] == 0 &&
                    newwhite[x+6][y-6] == 2 && newwhite[x+7][y-7] == 1 )
                    act[m][n] += 300;
                //12020021
                if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 0 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] == 0 && newwhite[x+5][y-5] == 0 &&
                    newwhite[x+6][y-6] == 2 && newwhite[x+7][y-7] == 1 )
                    act[m][n] += 300;
                //12020201
                if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 0 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] == 0 && newwhite[x+5][y-5] == 2 &&
                    newwhite[x+6][y-6] == 0 && newwhite[x+7][y-7] == 1 )
                    act[m][n] += 300;
                //10222001
                if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 0 && newwhite[x+2][y-2] == 2 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] == 2 && newwhite[x+5][y-5] == 0 &&
                    newwhite[x+6][y-6] == 0 && newwhite[x+7][y-7] == 1 )
                    act[m][n] += 300;
                //10202201
                if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 0 && newwhite[x+2][y-2] == 2 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] == 2 && newwhite[x+5][y-5] == 2 &&
                    newwhite[x+6][y-6] == 0 && newwhite[x+7][y-7] == 1 )
                    act[m][n] += 300;
                //10200221
                if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 0 && newwhite[x+2][y-2] == 2 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] == 0 && newwhite[x+5][y-5] == 2 &&
                    newwhite[x+6][y-6] == 2 && newwhite[x+7][y-7] == 1 )
                    act[m][n] += 300;
                //10220201
                if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 0 && newwhite[x+2][y-2] == 2 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] == 0 && newwhite[x+5][y-5] == 2 &&
                    newwhite[x+6][y-6] == 0 && newwhite[x+7][y-7] == 1 )
                    act[m][n] += 300;
                //10220021
                if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 0 && newwhite[x+2][y-2] == 2 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] == 0 && newwhite[x+5][y-5] == 0 &&
                    newwhite[x+6][y-6] == 2 && newwhite[x+7][y-7] == 1 )
                    act[m][n] += 300;
                //10022021
                if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 0 && newwhite[x+2][y-2] == 0 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] == 2 && newwhite[x+5][y-5] == 0 &&
                    newwhite[x+6][y-6] == 2 && newwhite[x+7][y-7] == 1 )
                    act[m][n] += 300;
                //10022201
                if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 0 && newwhite[x+2][y-2] == 0 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] == 2 && newwhite[x+5][y-5] == 2 &&
                    newwhite[x+6][y-6] == 0 && newwhite[x+7][y-7] == 1 )
                    act[m][n] += 300;
                //10020221
                if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 0 && newwhite[x+2][y-2] == 0 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] == 0 && newwhite[x+5][y-5] == 2 &&
                    newwhite[x+6][y-6] == 2 && newwhite[x+7][y-7] == 1 )
                    act[m][n] += 300;
                //10002221
                if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 0 && newwhite[x+2][y-2] == 0 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] == 0 && newwhite[x+5][y-5] == 2 &&
                    newwhite[x+6][y-6] == 2 && newwhite[x+7][y-7] == 1 )
                    act[m][n] += 300;
                //10202021
                if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 0 && newwhite[x+2][y-2] == 2 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] == 2 && newwhite[x+5][y-5] == 0 &&
                    newwhite[x+6][y-6] == 2 && newwhite[x+7][y-7] == 1 )
                    act[m][n] += 300;
                    }
              }
              newwhite[m][n] = 0;
          }
        }

}

void AI::W_AI_4_in_slash_check()
{
    for(int m=0 ; m<19 ; m++)
        {
          for(int n=0 ; n<19 ; n++)
          {
              if( newwhite[m][n] == 0 )
              {
              newwhite[m][n] = 2;
              }
              else if( newwhite[m][n] == 1 || newwhite[m][n] == 2 )
              {
                  continue;
              }

              for(int x=0; x<19; x++)
              {
                  for(int y=0; y<19; y++)
                  {
       /*4개 -> 안막혔을 때*/
             //00222200
             if( newwhite[x-1][y+1] == 0 && newwhite[x][y]== 0 && newwhite[x+1][y-1]== 2 && newwhite[x+2][y-2]== 2 &&newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] == 2 &&
                 newwhite[x+5][y-5] == 0 )
                act[m][n] += 10000;
             //002022200
             if( newwhite[x-1][y+1] == 0 && newwhite[x][y]==0 && newwhite[x+1][y-1]==2 && newwhite[x+2][y-2]==0 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] ==2 &&
                 newwhite[x+5][y-5]==2 &&newwhite[x+6][y-6] ==0 && newwhite[x+7][y-7] == 0 )
                act[m][n] += 7000;
             //002220200
             if( newwhite[x-1][y+1] == 0 && newwhite[x][y]== 0 && newwhite[x+1][y-1]== 2 && newwhite[x+2][y-2]== 2 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] == 0 &&
                 newwhite[x+5][y-5] ==2 &&newwhite[x+6][y-6] == 0 && newwhite[x+7][y-7] == 0 )
                act[m][n] += 7000;
             //002202200
             if( newwhite[x-1][y+1] == 0 && newwhite[x][y]== 0 && newwhite[x+1][y-1]== 2 && newwhite[x+2][y-2]== 2 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] == 2 &&
                 newwhite[x+5][y-5] == 2 && newwhite[x+6][y-6] == 0 && newwhite[x+7][y-7] == 0 )
                act[m][n] += 7000;
             //02220020
             if( newwhite[x][y]==0 && newwhite[x+1][y-1]==2 && newwhite[x+2][y-2]==2 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] ==0 && newwhite[x+5][y-5] ==0 &&
                 newwhite[x+6][y-6] ==2 && newwhite[x+7][y-7] ==0 )
                act[m][n] += 5000;
             //02002220
             if( newwhite[x][y] == 0 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 0 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] == 2 && newwhite[x+5][y-5] == 2 &&
                 newwhite[x+6][y-6] == 2 && newwhite[x+7][y-7] == 0 )
                act[m][n] += 5000;
             //02202020
             if( newwhite[x][y] == 0 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 2 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] == 2 && newwhite[x+5][y-5] == 2 &&
                 newwhite[x+6][y-6] == 2 && newwhite[x+7][y-7] == 0 )
                act[m][n] += 4000;
             //02020220
             if(newwhite[x][y] == 0 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 0 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] == 0 && newwhite[x+5][y-5] == 2 &&
                 newwhite[x+6][y-6] == 2 && newwhite[x+7][y-7] == 0 )
                act[m][n] += 4000;

             //4개 한쪽 막혔을 때
             //122220
             if(newwhite[x][y]==1 && newwhite[x+1][y-1]==2 && newwhite[x+2][y-2]==2 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] ==2 && newwhite[x+5][y-5] ==0)
                act[m][n] += 3500;
             //1202220
             if(newwhite[x][y]==1 && newwhite[x+1][y-1]==2 && newwhite[x+2][y-2]==0 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] ==2 && newwhite[x+5][y-5] ==2 &&newwhite[x+6][y-6] ==0)
                act[m][n] += 3500;
             //1220220
             if(newwhite[x][y]==1 && newwhite[x+1][y-1]==2 && newwhite[x+2][y-2]==2 && newwhite[x+3][y-3] ==0 && newwhite[x+4][y-4] ==2 && newwhite[x+5][y-5] ==2 &&newwhite[x+6][y-6] ==0)
                act[m][n] += 3500;
             //1222020
             if(newwhite[x][y]==1 && newwhite[x+1][y-1]==2 && newwhite[x+2][y-2]==2 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] ==0 && newwhite[x+5][y-5] ==2 &&newwhite[x+6][y-6] ==0)
                act[m][n] += 3500;
             //1022220
             if(newwhite[x][y]==1 && newwhite[x+1][y-1]==0 && newwhite[x+2][y-2]==2 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] ==2 && newwhite[x+5][y-5] ==2 &&newwhite[x+6][y-6] ==0)
                act[m][n] += 3500;
             //12002220
             if(newwhite[x][y]==1 && newwhite[x+1][y-1]==2 && newwhite[x+2][y-2]==0 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] ==2 && newwhite[x+5][y-5] ==2 &&newwhite[x+6][y-6] ==2 &&
                 newwhite[x+7][y-7]==0)
                act[m][n] += 3500;
             //12020220
             if(newwhite[x][y]==1 && newwhite[x+1][y-1]==2 && newwhite[x+2][y-2]==0 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] ==0 && newwhite[x+5][y-5] ==2 &&newwhite[x+6][y-6] ==2 &&
                 newwhite[x+7][y-7]==0)
                act[m][n] += 3500;
             //12022020
             if(newwhite[x][y]==1 && newwhite[x+1][y-1]==2 && newwhite[x+2][y-2]==0 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] ==2 && newwhite[x+5][y-5] ==0 &&newwhite[x+6][y-6] ==2 &&
                 newwhite[x+7][y-7]==0)
                act[m][n] += 3500;
             //12200220
             if(newwhite[x][y]==1 && newwhite[x+1][y-1]==2 && newwhite[x+2][y-2]==2 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] ==0 && newwhite[x+5][y-5] ==2 &&newwhite[x+6][y-6] ==2 &&
                 newwhite[x+7][y-7]==0 )
                act[m][n] += 3500;
             //12202020
             if(newwhite[x][y]==1 && newwhite[x+1][y-1]==2 && newwhite[x+2][y-2]==2 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] ==2 && newwhite[x+5][y-5] ==0 &&newwhite[x+6][y-6] ==2 &&
                 newwhite[x+7][y-7]==0)
                act[m][n] += 3500;
             //12220020
             if(newwhite[x][y]==1 && newwhite[x+1][y-1]==2 && newwhite[x+2][y-2]==2 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] ==0 && newwhite[x+5][y-5] ==0 &&newwhite[x+6][y-6] ==2 &&
                 newwhite[x+7][y-7]==0)
                act[m][n] += 3500;
             //10220220
             if(newwhite[x][y]==1 && newwhite[x+1][y-1]==0 && newwhite[x+2][y-2]==2 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] ==0 && newwhite[x+5][y-5] ==2 &&newwhite[x+6][y-6] ==2 &&
                 newwhite[x+7][y-7]==0)
                act[m][n] += 3500;
             //10222020
             if(newwhite[x][y]==1 && newwhite[x+1][y-1]==0 && newwhite[x+2][y-2]==2 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] ==2 && newwhite[x+5][y-5] ==0 &&newwhite[x+6][y-6] ==2 &&
                 newwhite[x+7][y-7]==0)
                act[m][n] += 3500;
             //10202220
             if(newwhite[x][y]==1 && newwhite[x+1][y-1]==0 && newwhite[x+2][y-2]==2 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] ==2 && newwhite[x+5][y-5] ==2 &&newwhite[x+6][y-6] ==2 &&
                 newwhite[x+7][y-7]==0)
                act[m][n] += 3500;


             //4개 한쪽 막혔을 때 reverse
             //022221
             if(newwhite[x][y]==0 && newwhite[x+1][y-1]==2 && newwhite[x+2][y-2]==2 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] ==2 && newwhite[x+5][y-5] ==1)
                act[m][n] += 3500;
             //0222021
             if(newwhite[x][y]==0 && newwhite[x+1][y-1]==2 && newwhite[x+2][y-2]==2 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] ==0 && newwhite[x+5][y-5] ==2 &&newwhite[x+6][y-6] ==1)
                act[m][n] += 3500;
             //0220221
             if(newwhite[x][y]==0 && newwhite[x+1][y-1]==2 && newwhite[x+2][y-2]==2 && newwhite[x+3][y-3] ==0 && newwhite[x+4][y-4] ==2 && newwhite[x+5][y-5] ==2 &&newwhite[x+6][y-6] ==1)
                act[m][n] += 3500;
             //0202221
             if(newwhite[x][y]==0 && newwhite[x+1][y-1]==2 && newwhite[x+2][y-2]==0 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] ==2 && newwhite[x+5][y-5] ==2 &&newwhite[x+6][y-6] ==1)
                act[m][n] += 3500;
             //0222201
             if(newwhite[x][y]==0 && newwhite[x+1][y-1]==2 && newwhite[x+2][y-2]==2 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] ==2 && newwhite[x+5][y-5] ==0 &&newwhite[x+6][y-6] ==1)
                act[m][n] += 3500;
             //02220021
             if(newwhite[x][y]==0 && newwhite[x+1][y-1]==2 && newwhite[x+2][y-2]==2 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] ==0 && newwhite[x+5][y-5] ==0 &&newwhite[x+6][y-6] ==2 &&
                 newwhite[x+7][y-7] ==1)
                act[m][n] += 3500;
             //02202021
             if(newwhite[x][y]==0 && newwhite[x+1][y-1]==2 && newwhite[x+2][y-2]==2 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] ==2 && newwhite[x+5][y-5] ==0 &&newwhite[x+6][y-6] ==2 &&
                 newwhite[x+7][y-7] ==1)
                act[m][n] += 3500;
             //02022021
             if(newwhite[x][y]==0 && newwhite[x+1][y-1]==2 && newwhite[x+2][y-2]==0 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] ==2 && newwhite[x+5][y-5] ==0 &&newwhite[x+6][y-6] ==2 &&
                 newwhite[x+7][y-7] ==1)
                act[m][n] += 3500;
             //02200221
             if(newwhite[x][y]==0 && newwhite[x+1][y-1]==2 && newwhite[x+2][y-2]==2 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] ==0 && newwhite[x+5][y-5] ==2 &&newwhite[x+6][y-6] ==2 &&
                 newwhite[x+7][y-7] ==1 )
                act[m][n] += 3500;
             //02020221
             if(newwhite[x][y]==0 && newwhite[x+1][y-1]==2 && newwhite[x+2][y-2]==0 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] ==0 && newwhite[x+5][y-5] ==2 &&newwhite[x+6][y-6] ==2 &&
                 newwhite[x+7][y-7] ==1)
                act[m][n] += 3500;
             //02002221
             if(newwhite[x][y]==0 && newwhite[x+1][y-1]==2 && newwhite[x+2][y-2]==0 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] ==2 && newwhite[x+5][y-5] ==2 &&newwhite[x+6][y-6] ==2 &&
                 newwhite[x+7][y-7] ==1)
                act[m][n] += 3500;
             //02202201
             if(newwhite[x][y]==0 && newwhite[x+1][y-1]==2 && newwhite[x+2][y-2]==2 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] ==2 && newwhite[x+5][y-5] ==2 &&newwhite[x+6][y-6] ==0 &&
                 newwhite[x+7][y-7] ==1)
                act[m][n] += 3500;
             //02022201
             if(newwhite[x][y]==0 && newwhite[x+1][y-1]==2 && newwhite[x+2][y-2]==0 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] ==2 && newwhite[x+5][y-5] ==2 &&newwhite[x+6][y-6] ==0 &&
                 newwhite[x+7][y-7] ==1)
                act[m][n] += 3500;
             //02220201
             if(newwhite[x][y]==0 && newwhite[x+1][y-1]==2 && newwhite[x+2][y-2]==2 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] ==0 && newwhite[x+5][y-5] ==2 &&newwhite[x+6][y-6] ==0 &&
                 newwhite[x+7][y-7] ==1)
                act[m][n] += 3500;



             //양쪽 다 막혔을 때

             //12022021
             if(newwhite[x][y]==1 && newwhite[x+1][y-1]==2 && newwhite[x+2][y-2]==0 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] ==2 && newwhite[x+5][y-5] ==0 &&newwhite[x+6][y-6] ==2 &&newwhite[x+7][y-7] ==1 )
                act[m][n] += 1000;
             //12200221
             if(newwhite[x][y]==1 && newwhite[x+1][y-1]==2 && newwhite[x+2][y-2]==2 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] ==0 && newwhite[x+5][y-5] ==2 &&newwhite[x+6][y-6] ==2 &&newwhite[x+7][y-7] ==1 )
                act[m][n] += 1000;
             //12220021
             if(newwhite[x][y]==1 && newwhite[x+1][y-1]==2 && newwhite[x+2][y-2]==2 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] ==0 && newwhite[x+5][y-5] ==0 &&newwhite[x+6][y-6] ==2 &&newwhite[x+7][y-7] ==1)
                act[m][n] += 1000;
             //12002221
             if(newwhite[x][y]==1 && newwhite[x+1][y-1]==2 && newwhite[x+2][y-2]==0 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] ==2 && newwhite[x+5][y-5] ==2 &&newwhite[x+6][y-6] ==2 &&newwhite[x+7][y-7] ==1 )
                act[m][n] += 1000;
             //12202021
             if(newwhite[x][y]==1 && newwhite[x+1][y-1]==2 && newwhite[x+2][y-2]==2 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] ==2 && newwhite[x+5][y-5] ==2 &&newwhite[x+6][y-6] ==2 &&newwhite[x+7][y-7] ==1)
                act[m][n] += 1000;
             //12020221
             if(newwhite[x][y]==1 && newwhite[x+1][y-1]==2 && newwhite[x+2][y-2]==0 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] ==0 && newwhite[x+5][y-5] ==2 &&newwhite[x+6][y-6] ==2 &&newwhite[x+7][y-7] ==1 )
                act[m][n] += 1000;
             //10222201
           if(newwhite[x][y]==1 && newwhite[x+1][y-1]==0 && newwhite[x+2][y-2]==2 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] ==2 && newwhite[x+5][y-5] ==2 &&newwhite[x+6][y-6] ==0 &&newwhite[x+7][y-7] ==1 )
                act[m][n] += 1000;
           //10222021
           if(newwhite[x][y]==1 && newwhite[x+1][y-1]==0 && newwhite[x+2][y-2]==2 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] ==2 && newwhite[x+5][y-5] ==0 &&newwhite[x+6][y-6] ==2 &&newwhite[x+7][y-7] ==1 )
                act[m][n] += 1000;
           //10220221
           if(newwhite[x][y]==1 && newwhite[x+1][y-1]==0 && newwhite[x+2][y-2]==2 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] ==0 && newwhite[x+5][y-5] ==2 &&newwhite[x+6][y-6] ==2 &&newwhite[x+7][y-7] ==1 )
                act[m][n] += 1000;
            //10202221
           if(newwhite[x][y]==1 && newwhite[x+1][y-1]==0 && newwhite[x+2][y-2]==2 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] ==2 && newwhite[x+5][y-5] ==2 &&newwhite[x+6][y-6] ==2 &&newwhite[x+7][y-7] ==1 )
                act[m][n] += 1000;
           //10022221
           if(newwhite[x][y]==1 && newwhite[x+1][y-1]==0 && newwhite[x+2][y-2]==0 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] ==2 && newwhite[x+5][y-5] ==2 &&newwhite[x+6][y-6] ==2 &&newwhite[x+7][y-7] ==1 )
                act[m][n] += 1000;
           //12022201
           if(newwhite[x][y]==1 && newwhite[x+1][y-1]==2 && newwhite[x+2][y-2]==0 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] ==2 && newwhite[x+5][y-5] ==2 &&newwhite[x+6][y-6] ==0 &&newwhite[x+7][y-7] ==1 )
                act[m][n] += 1000;
           //12202201
           if(newwhite[x][y]==1 && newwhite[x+1][y-1]==2 && newwhite[x+2][y-2]==2 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] ==2 && newwhite[x+5][y-5] ==2 &&newwhite[x+6][y-6] ==0 &&newwhite[x+7][y-7] ==1 )
                act[m][n] += 1000;
           //12220201
           if(newwhite[x][y]==1 && newwhite[x+1][y-1]==2 && newwhite[x+2][y-2]==2 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] ==0 && newwhite[x+5][y-5] ==2 &&newwhite[x+6][y-6] ==0 &&newwhite[x+7][y-7] ==1 )
                act[m][n] += 1000;
           //12222001
           if(newwhite[x][y]==1 && newwhite[x+1][y-1]==2 && newwhite[x+2][y-2]==2 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] ==2 && newwhite[x+5][y-5] ==0 &&newwhite[x+6][y-6] ==0 &&newwhite[x+7][y-7] ==1 )
                act[m][n] += 1000;
             }
             }
             newwhite[m][n] = 0;
             }
             }

}

void AI::defense_garo_check_W()
{
    for(int m=0 ; m<19 ; m++)
    {
        for(int n=0 ; n<19 ; n++)
        {
            if( newwhite[m][n] == 0 )
            {
                newwhite[m][n] = 2;
            }
            else if( newwhite[m][n] == 1 || newwhite[m][n] == 2 )
            {
                continue;
            }

            for(int x=0; x<19; x++)
            {
                for(int y=0; y<19; y++)
                {
                    //다섯개에 양쪽다 막도록.
                    //2111112 이런상황이 되게 할때 점수가 높이 준다.
                    if( newwhite[x][y] == 2 && newwhite[x][y+1] == 1 && newwhite[x][y+2] == 1 && newwhite[x][y+3] == 1 && newwhite[x][y+4] == 1 &&
                        newwhite[x][y+5] == 1 && newwhite[x][y+6] == 2 )
                        act[m][n] += 750000;
                    //2111110
                    if( newwhite[x][y] == 2 && newwhite[x][y+1] == 1 && newwhite[x][y+2] == 1 && newwhite[x][y+3] == 1 && newwhite[x][y+4] == 1 &&
                        newwhite[x][y+5] == 1 && newwhite[x][y+6] == 0 )
                        act[m][n] += 500000;
                    //0111112
                    if( newwhite[x][y] == 0 && newwhite[x][y+1] == 1 && newwhite[x][y+2] == 1 && newwhite[x][y+3] == 1 && newwhite[x][y+4] == 1 &&
                        newwhite[x][y+5] == 1 && newwhite[x][y+6] == 2 )
                        act[m][n] += 500000;
                    //121111
                    if( newwhite[x][y] == 1 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 1 && newwhite[x][y+3] == 1 && newwhite[x][y+4] == 1 &&
                        newwhite[x][y+5] == 1 )
                        act[m][n] += 500000;
                    //112111
                    if( newwhite[x][y] == 1 && newwhite[x][y+1] == 1 && newwhite[x][y+2] == 2 && newwhite[x][y+3] == 1 && newwhite[x][y+4] == 1 &&
                        newwhite[x][y+5] == 1 )
                        act[m][n] += 500000;
                    //111211
                    if( newwhite[x][y] == 1 && newwhite[x][y+1] == 1 && newwhite[x][y+2] == 1 && newwhite[x][y+3] == 2 && newwhite[x][y+4] == 1 &&
                        newwhite[x][y+5] == 1 )
                        act[m][n] += 500000;
                    //111121
                    if( newwhite[x][y] == 1 && newwhite[x][y+1] == 1 && newwhite[x][y+2] == 1 && newwhite[x][y+3] == 1 && newwhite[x][y+4] == 2 &&
                        newwhite[x][y+5] == 1 )
                        act[m][n] += 500000;

                    //추가부분 상대방 4개짜리 사이 빈칸있을때 사이 막기
                    //202122
                    if( newwhite[x][y] == 1 && newwhite[x][y+1] == 0 && newwhite[x][y+2] == 1 && newwhite[x][y+3] == 2 && newwhite[x][y+4] == 1 &&
                        newwhite[x][y+5] == 1 )
                        act[m][n] += 500000;
                    //202212
                    if( newwhite[x][y] == 1 && newwhite[x][y+1] == 0 && newwhite[x][y+2] == 1 && newwhite[x][y+3] == 1 && newwhite[x][y+4] == 2 &&
                        newwhite[x][y+5] == 1 )
                        act[m][n] += 500000;
                    //212022
                    if( newwhite[x][y] == 1 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 1 && newwhite[x][y+3] == 0 && newwhite[x][y+4] == 1 &&
                        newwhite[x][y+5] == 1 )
                        act[m][n] += 500000;
                    //212202
                    if( newwhite[x][y] == 1 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 1 && newwhite[x][y+3] == 1 && newwhite[x][y+4] == 0 &&
                        newwhite[x][y+5] == 1 )
                        act[m][n] += 500000;
                    //221202
                    if( newwhite[x][y] == 1 && newwhite[x][y+1] == 1 && newwhite[x][y+2] == 2 && newwhite[x][y+3] == 1 && newwhite[x][y+4] == 0 &&
                        newwhite[x][y+5] == 1 )
                        act[m][n] += 500000;
                    //220212
                    if( newwhite[x][y] == 1 && newwhite[x][y+1] == 1 && newwhite[x][y+2] == 0 && newwhite[x][y+3] == 1 && newwhite[x][y+4] == 2 &&
                        newwhite[x][y+5] == 1 )
                        act[m][n] += 500000;

                    //211112
                    if( newwhite[x][y] == 2 && newwhite[x][y+1] == 1 && newwhite[x][y+2] == 1 && newwhite[x][y+3] == 1 && newwhite[x][y+4] == 1 &&
                        newwhite[x][y+5] == 2 )
                        act[m][n] += 500000;

                    //211110
                    if( newwhite[x][y] == 2 && newwhite[x][y+1] == 1 && newwhite[x][y+2] == 1 && newwhite[x][y+3] == 1 && newwhite[x][y+4] == 1 &&
                        newwhite[x][y+5] == 0 )
                        act[m][n] += 500000;
                    //011112
                    if( newwhite[x][y] == 0 && newwhite[x][y+1] == 1 && newwhite[x][y+2] == 1 && newwhite[x][y+3] == 1 && newwhite[x][y+4] == 1 &&
                        newwhite[x][y+5] == 2)
                        act[m][n] += 500000;
                    //2111102
                    if( newwhite[x][y] == 2 && newwhite[x][y+1] == 1 && newwhite[x][y+2] == 1 && newwhite[x][y+3] == 1 && newwhite[x][y+4] == 1 &&
                        newwhite[x][y+5] == 0 && newwhite[x][y+6] == 2 )
                        act[m][n] += 500000;
                    //2011112
                    if( newwhite[x][y] == 2 && newwhite[x][y+1] == 0 && newwhite[x][y+2] == 1 && newwhite[x][y+3] == 1 && newwhite[x][y+4] == 1 &&
                        newwhite[x][y+5] == 1 && newwhite[x][y+6] == 2 )
                        act[m][n] += 500000;

                    //x12111x
                    if( newwhite[x][y+1] == 1 && newwhite[x][y+2] == 2 && newwhite[x][y+3] == 1 && newwhite[x][y+4] == 1 &&
                        newwhite[x][y+5] == 1 && newwhite[x][y+6] != 2 )
                        act[m][n] += 500000;
                    //x11211x
                    if( newwhite[x][y+1] == 1 && newwhite[x][y+2] == 1 && newwhite[x][y+3] == 2 && newwhite[x][y+4] == 1 &&
                        newwhite[x][y+5] == 1 && newwhite[x][y+6] != 2 )
                        act[m][n] += 500000;
                    //x11121x
                    if( newwhite[x][y+1] == 1 && newwhite[x][y+2] == 1 && newwhite[x][y+3] == 1 && newwhite[x][y+4] == 2 &&
                        newwhite[x][y+5] == 1 && newwhite[x][y+6] != 2 )
                        act[m][n] += 500000;
                    //x12111x
                    if( newwhite[x][y] != 2 && newwhite[x][y+1] == 1 && newwhite[x][y+2] == 2 && newwhite[x][y+3] == 1 && newwhite[x][y+4] == 1 &&
                        newwhite[x][y+5] == 1 )
                        act[m][n] += 500000;
                    //x11211x
                    if( newwhite[x][y] != 2 && newwhite[x][y+1] == 1 && newwhite[x][y+2] == 1 && newwhite[x][y+3] == 2 && newwhite[x][y+4] == 1 &&
                        newwhite[x][y+5] == 1 )
                        act[m][n] += 500000;
                    //x11121x
                    if( newwhite[x][y] != 2 && newwhite[x][y+1] == 1 && newwhite[x][y+2] == 1 && newwhite[x][y+3] == 1 && newwhite[x][y+4] == 2 &&
                        newwhite[x][y+5] == 1 )
                        act[m][n] += 500000;

                    //120111
                    if( newwhite[x][y] == 1 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 0 && newwhite[x][y+3] == 1 && newwhite[x][y+4] == 1 &&
                        newwhite[x][y+5] == 1 )
                        act[m][n] += 500000;
                    //102111
                    if( newwhite[x][y] == 1 && newwhite[x][y+1] == 0 && newwhite[x][y+2] == 2 && newwhite[x][y+3] == 1 && newwhite[x][y+4] == 1 &&
                        newwhite[x][y+5] == 1 )
                        act[m][n] += 500000;
                    //111201
                    if( newwhite[x][y] == 1 && newwhite[x][y+1] == 1 && newwhite[x][y+2] == 1 && newwhite[x][y+3] == 2 && newwhite[x][y+4] == 0 &&
                        newwhite[x][y+5] == 1 )
                        act[m][n] += 500000;
                    //111021
                    if( newwhite[x][y] == 1 && newwhite[x][y+1] == 1 && newwhite[x][y+2] == 1 && newwhite[x][y+3] == 0 && newwhite[x][y+4] == 2 &&
                        newwhite[x][y+5] == 1 )
                        act[m][n] += 500000;
                    //112011
                    if( newwhite[x][y] == 1 && newwhite[x][y+1] == 1 && newwhite[x][y+2] == 2 && newwhite[x][y+3] == 0 && newwhite[x][y+4] == 1 &&
                        newwhite[x][y+5] == 1 )
                        act[m][n] += 500000;
                    //110211
                    if( newwhite[x][y] == 1 && newwhite[x][y+1] == 1 && newwhite[x][y+2] == 0 && newwhite[x][y+3] == 2 && newwhite[x][y+4] == 1 &&
                        newwhite[x][y+5] == 1 )
                        act[m][n] += 500000;



                    //여기서부터 간단한 가중치 줄 것. 즉, 2개 3개 막게하는것들
                    //2111
                    if( newwhite[x][y] == 2 && newwhite[x][y+1] == 1 && newwhite[x][y+2] == 1 && newwhite[x][y+3] == 1 )
                        act[m][n] += 3500;
                    //1112
                    if( newwhite[x][y] == 1 && newwhite[x][y+1] == 1 && newwhite[x][y+2] == 1 && newwhite[x][y+3] == 2 )
                        act[m][n] += 3500;
                    //1211
                    if( newwhite[x][y] == 1 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 1 && newwhite[x][y+3] == 1 )
                        act[m][n] += 4000;
                    //1121
                    if( newwhite[x][y] == 1 && newwhite[x][y+1] == 1 && newwhite[x][y+2] == 2 && newwhite[x][y+3] == 1 )
                        act[m][n] += 4000;
                    //11102		분기해서 막는것도 필요한 경우가 있을수있음. 단 점수는 낮게
                    if( newwhite[x][y] == 1 && newwhite[x][y+1] == 1 && newwhite[x][y+2] == 1 && newwhite[x][y+3] == 0 && newwhite[x][y+4] == 2 )
                        act[m][n] += 1500;
                    //20111
                    if( newwhite[x][y] == 2 && newwhite[x][y+1] == 0 && newwhite[x][y+2] == 1 && newwhite[x][y+3] == 1 && newwhite[x][y+4] == 1 )
                        act[m][n] += 1500;

                    //21011		점수낮게
                    if( newwhite[x][y] == 2 && newwhite[x][y+1] == 1 && newwhite[x][y+2] == 0 && newwhite[x][y+3] == 1 && newwhite[x][y+4] == 1 )
                        act[m][n] += 1500;
                    //21101		점수낮게
                    if( newwhite[x][y] == 2 && newwhite[x][y+1] == 1 && newwhite[x][y+2] == 1 && newwhite[x][y+3] == 0 && newwhite[x][y+4] == 1 )
                        act[m][n] += 1500;
                    //10112		점수낮게
                    if( newwhite[x][y] == 1 && newwhite[x][y+1] == 0 && newwhite[x][y+2] == 1 && newwhite[x][y+3] == 1 && newwhite[x][y+4] == 2 )
                        act[m][n] += 1500;
                    //11012		점수낮게
                    if( newwhite[x][y] == 1 && newwhite[x][y+1] == 1 && newwhite[x][y+2] == 0 && newwhite[x][y+3] == 1 && newwhite[x][y+4] == 2 )
                        act[m][n] += 1500;

                    //211
                    if( newwhite[x][y] == 2 && newwhite[x][y+1] == 1 && newwhite[x][y+2] == 1 )
                        act[m][n] += 500;
                    //112
                    if( newwhite[x][y] == 1 && newwhite[x][y+1] == 1 && newwhite[x][y+2] == 2 )
                        act[m][n] += 500;
                    //121
                    if( newwhite[x][y] == 1 && newwhite[x][y+1] == 2 && newwhite[x][y+2] == 1 )
                        act[m][n] += 800;
                }
            }
            newwhite[m][n] = 0;
        }
    }

}

void AI::defense_sero_check_W()
{
    for(int m=0 ; m<19 ; m++)
        {
            for(int n=0 ; n<19 ; n++)
            {
                if( newwhite[m][n] == 0 )
                {
                    newwhite[m][n] = 2;
                }
                else if( newwhite[m][n] == 1 || newwhite[m][n] == 2 )
                {
                    continue;
                }

                for(int x=0; x<19; x++)
                {
                    for(int y=0; y<19; y++)
                    {
                        //다섯개에 양쪽다 막도록.
                        //2111112 이런상황이 되게 할때 점수가 높이 준다.
                        if( newwhite[x][y] == 2 && newwhite[x+1][y] == 1 && newwhite[x+2][y] == 1 && newwhite[x+3][y] == 1 && newwhite[x+4][y] == 1 &&
                            newwhite[x+5][y] == 1 && newwhite[x+6][y] == 2 )
                            act[m][n] += 750000;
                        //2111110
                        if( newwhite[x][y] == 2 && newwhite[x+1][y] == 1 && newwhite[x+2][y] == 1 && newwhite[x+3][y] == 1 && newwhite[x+4][y] == 1 &&
                            newwhite[x+5][y] == 1 && newwhite[x+6][y] == 0 )
                            act[m][n] += 500000;
                        //0111112
                        if( newwhite[x][y] == 0 && newwhite[x+1][y] == 1 && newwhite[x+2][y] == 1 && newwhite[x+3][y] == 1 && newwhite[x+4][y] == 1 &&
                            newwhite[x+5][y] == 1 && newwhite[x+6][y] == 2 )
                            act[m][n] += 500000;
                        //121111
                        if( newwhite[x][y] == 1 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 1 && newwhite[x+3][y] == 1 && newwhite[x+4][y] == 1 &&
                            newwhite[x+5][y] == 1 )
                            act[m][n] += 500000;
                        //112111
                        if( newwhite[x][y] == 1 && newwhite[x+1][y] == 1 && newwhite[x+2][y] == 2 && newwhite[x+3][y] == 1 && newwhite[x+4][y] == 1 &&
                            newwhite[x+5][y] == 1 )
                            act[m][n] += 500000;
                        //111211
                        if( newwhite[x][y] == 1 && newwhite[x+1][y] == 1 && newwhite[x+2][y] == 1 && newwhite[x+3][y] == 2 && newwhite[x+4][y] == 1 &&
                            newwhite[x+5][y] == 1 )
                            act[m][n] += 500000;
                        //111121
                        if( newwhite[x][y] == 1 && newwhite[x+1][y] == 1 && newwhite[x+2][y] == 1 && newwhite[x+3][y] == 1 && newwhite[x+4][y] == 2 &&
                            newwhite[x+5][y] == 1 )
                            act[m][n] += 500000;

                        //추가부분 상대방 4개짜리 사이 빈칸있을때 사이 막기
                        //202122
                        if( newwhite[x][y] == 1 && newwhite[x+1][y] == 0 && newwhite[x+2][y] == 1 && newwhite[x+3][y] == 2 && newwhite[x+4][y] == 1 &&
                            newwhite[x+5][y] == 1 )
                            act[m][n] += 500000;
                        //202212
                        if( newwhite[x][y] == 1 && newwhite[x+1][y] == 0 && newwhite[x+2][y] == 1 && newwhite[x+3][y] == 1 && newwhite[x+4][y] == 2 &&
                            newwhite[x+5][y] == 1 )
                            act[m][n] += 500000;
                        //212022
                        if( newwhite[x][y] == 1 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 1 && newwhite[x+3][y] == 0 && newwhite[x+4][y] == 1 &&
                            newwhite[x+5][y] == 1 )
                            act[m][n] += 500000;
                        //212202
                        if( newwhite[x][y] == 1 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 1 && newwhite[x+3][y] == 1 && newwhite[x+4][y] == 0 &&
                            newwhite[x+5][y] == 1 )
                            act[m][n] += 500000;
                        //221202
                        if( newwhite[x][y] == 1 && newwhite[x+1][y] == 1 && newwhite[x+2][y] == 2 && newwhite[x+3][y] == 1 && newwhite[x+4][y] == 0 &&
                            newwhite[x+5][y] == 1 )
                            act[m][n] += 500000;
                        //220212
                        if( newwhite[x][y] == 1 && newwhite[x+1][y] == 1 && newwhite[x+2][y] == 0 && newwhite[x+3][y] == 1 && newwhite[x+4][y] == 2 &&
                            newwhite[x+5][y] == 1 )
                            act[m][n] += 500000;

                        //211112
                        if( newwhite[x][y] == 2 && newwhite[x+1][y] == 1 && newwhite[x+2][y] == 1 && newwhite[x+3][y] == 1 && newwhite[x+4][y] == 1 &&
                            newwhite[x+5][y] == 2 )
                            act[m][n] += 500000;
                        //211110
                        if( newwhite[x][y] == 2 && newwhite[x+1][y] == 1 && newwhite[x+2][y] == 1 && newwhite[x+3][y] == 1 && newwhite[x+4][y] == 1 &&
                            newwhite[x+5][y] == 0 )
                            act[m][n] += 500000;
                        //011112
                        if( newwhite[x][y] == 0 && newwhite[x+1][y] == 1 && newwhite[x+2][y] == 1 && newwhite[x+3][y] == 1 && newwhite[x+4][y] == 1 &&
                            newwhite[x+5][y] == 2)
                            act[m][n] += 500000;
                        //2111102
                        if( newwhite[x][y] == 2 && newwhite[x+1][y] == 1 && newwhite[x+2][y] == 1 && newwhite[x+3][y] == 1 && newwhite[x+4][y] == 1 &&
                            newwhite[x+5][y] == 0 && newwhite[x+6][y] == 2 )
                            act[m][n] += 500000;
                        //2011112
                        if( newwhite[x][y] == 2 && newwhite[x+1][y] == 0 && newwhite[x+2][y] == 1 && newwhite[x+3][y] == 1 && newwhite[x+4][y] == 1 &&
                            newwhite[x+5][y] == 1 && newwhite[x+6][y] == 2 )
                            act[m][n] += 500000;

                        //x12111x
                        if( newwhite[x+1][y] == 1 && newwhite[x+2][y] == 2 && newwhite[x+3][y] == 1 && newwhite[x+4][y] == 1 &&
                            newwhite[x+5][y] == 1 && newwhite[x+6][y] != 2 )
                            act[m][n] += 500000;
                        //x11211x
                        if( newwhite[x+1][y] == 1 && newwhite[x+2][y] == 1 && newwhite[x+3][y] == 2 && newwhite[x+4][y] == 1 &&
                            newwhite[x+5][y] == 1 && newwhite[x+6][y] != 2 )
                            act[m][n] += 500000;
                        //x11121x
                        if( newwhite[x+1][y] == 1 && newwhite[x+2][y] == 1 && newwhite[x+3][y] == 1 && newwhite[x+4][y] == 2 &&
                            newwhite[x+5][y] == 1 && newwhite[x+6][y] != 2 )
                            act[m][n] += 500000;
                        //x12111x
                        if( newwhite[x][y] != 2 && newwhite[x+1][y] == 1 && newwhite[x+2][y] == 2 && newwhite[x+3][y] == 1 && newwhite[x+4][y] == 1 &&
                            newwhite[x+5][y] == 1 )
                            act[m][n] += 500000;
                        //x11211x
                        if( newwhite[x][y] != 2 && newwhite[x+1][y] == 1 && newwhite[x+2][y] == 1 && newwhite[x+3][y] == 2 && newwhite[x+4][y] == 1 &&
                            newwhite[x+5][y] == 1 )
                            act[m][n] += 500000;
                        //x11121x
                        if( newwhite[x][y] != 2 && newwhite[x+1][y] == 1 && newwhite[x+2][y] == 1 && newwhite[x+3][y] == 1 && newwhite[x+4][y] == 2 &&
                            newwhite[x+5][y] == 1 )
                            act[m][n] += 500000;

                        //120111
                        if( newwhite[x][y] == 1 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 0 && newwhite[x+3][y] == 1 && newwhite[x+4][y] == 1 &&
                            newwhite[x+5][y] == 1 )
                            act[m][n] += 500000;
                        //102111
                        if( newwhite[x][y] == 1 && newwhite[x+1][y] == 0 && newwhite[x+2][y] == 2 && newwhite[x+3][y] == 1 && newwhite[x+4][y] == 1 &&
                            newwhite[x+5][y] == 1 )
                            act[m][n] += 500000;
                        //111201
                        if( newwhite[x][y] == 1 && newwhite[x+1][y] == 1 && newwhite[x+2][y] == 1 && newwhite[x+3][y] == 2 && newwhite[x+4][y] == 0 &&
                            newwhite[x+5][y] == 1 )
                            act[m][n] += 500000;
                        //111021
                        if( newwhite[x][y] == 1 && newwhite[x+1][y] == 1 && newwhite[x+2][y] == 1 && newwhite[x+3][y] == 0 && newwhite[x+4][y] == 2 &&
                            newwhite[x+5][y] == 1 )
                            act[m][n] += 500000;
                        //112011
                        if( newwhite[x][y] == 1 && newwhite[x+1][y] == 1 && newwhite[x+2][y] == 2 && newwhite[x+3][y] == 0 && newwhite[x+4][y] == 1 &&
                            newwhite[x+5][y] == 1 )
                            act[m][n] += 500000;
                        //110211
                        if( newwhite[x][y] == 1 && newwhite[x+1][y] == 1 && newwhite[x+2][y] == 0 && newwhite[x+3][y] == 2 && newwhite[x+4][y] == 1 &&
                            newwhite[x+5][y] == 1 )
                            act[m][n] += 500000;

                        //여기서부터 간단한 가중치 줄 것. 즉, 2개 3개 막게하는것들
                        //2111
                        if( newwhite[x][y] == 2 && newwhite[x+1][y] == 1 && newwhite[x+2][y] == 1 && newwhite[x+3][y] == 1 )
                            act[m][n] += 3500;
                        //1112
                        if( newwhite[x][y] == 1 && newwhite[x+1][y] == 1 && newwhite[x+2][y] == 1 && newwhite[x+3][y] == 2 )
                            act[m][n] += 3500;
                        //1211
                        if( newwhite[x][y] == 1 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 1 && newwhite[x+3][y] == 1 )
                            act[m][n] += 4000;
                        //1121
                        if( newwhite[x][y] == 1 && newwhite[x+1][y] == 1 && newwhite[x+2][y] == 2 && newwhite[x+3][y] == 1 )
                            act[m][n] += 4000;
                        //11102		분기해서 막는것도 필요한 경우가 있을수있음. 단 점수는 낮게
                        if( newwhite[x][y] == 1 && newwhite[x+1][y] == 1 && newwhite[x+2][y] == 1 && newwhite[x+3][y] == 0 && newwhite[x+4][y] == 2 )
                            act[m][n] += 1500;
                        //20111
                        if( newwhite[x][y] == 2 && newwhite[x+1][y] == 0 && newwhite[x+2][y] == 1 && newwhite[x+3][y] == 1 && newwhite[x+4][y] == 1 )
                            act[m][n] += 1500;

                        //21011		점수낮게
                        if( newwhite[x][y] == 2 && newwhite[x+1][y] == 1 && newwhite[x+2][y] == 0 && newwhite[x+3][y] == 1 && newwhite[x+4][y] == 1 )
                            act[m][n] += 1500;
                        //21101		점수낮게
                        if( newwhite[x][y] == 2 && newwhite[x+1][y] == 1 && newwhite[x+2][y] == 1 && newwhite[x+3][y] == 0 && newwhite[x+4][y] == 1 )
                            act[m][n] += 1500;
                        //10112		점수낮게
                        if( newwhite[x][y] == 1 && newwhite[x+1][y] == 0 && newwhite[x+2][y] == 1 && newwhite[x+3][y] == 1 && newwhite[x+4][y] == 2 )
                            act[m][n] += 1500;
                        //11012		점수낮게
                        if( newwhite[x][y] == 1 && newwhite[x+1][y] == 1 && newwhite[x+2][y] == 0 && newwhite[x+3][y] == 1 && newwhite[x+4][y] == 2 )
                            act[m][n] += 1500;

                        //211
                        if( newwhite[x][y] == 2 && newwhite[x+1][y] == 1 && newwhite[x+2][y] == 1 )
                            act[m][n] += 500;
                        //112
                        if( newwhite[x][y] == 1 && newwhite[x+1][y] == 1 && newwhite[x+2][y] == 2 )
                            act[m][n] += 500;
                        //121
                        if( newwhite[x][y] == 1 && newwhite[x+1][y] == 2 && newwhite[x+2][y] == 1 )
                            act[m][n] += 800;
                    }
                }
                newwhite[m][n] = 0;
            }
        }

}

void AI::defense_slash_check_W()
{
    for(int m=0 ; m<19 ; m++)
        {
            for(int n=0 ; n<19 ; n++)
            {
                if( newwhite[m][n] == 0 )
                {
                    newwhite[m][n] = 2;
                }
                else if( newwhite[m][n] == 1 || newwhite[m][n] == 2 )
                {
                    continue;
                }

                for(int x=0; x<19; x++)
                {
                    for(int y=0; y<19; y++)
                    {
                        //다섯개에 양쪽다 막도록.
                        //2111112 이런상황이 되게 할때 점수가 높이 준다.
                        if( newwhite[x][y] == 2 && newwhite[x+1][y+1] == 1 && newwhite[x+2][y+2] == 1 && newwhite[x+3][y+3] == 1 && newwhite[x+4][y+4] == 1 &&
                            newwhite[x+5][y+5] == 1 && newwhite[x+6][y+6] == 2 )
                            act[m][n] += 750000;
                        //2111110
                        if( newwhite[x][y] == 2 && newwhite[x+1][y+1] == 1 && newwhite[x+2][y+2] == 1 && newwhite[x+3][y+3] == 1 && newwhite[x+4][y+4] == 1 &&
                            newwhite[x+5][y+5] == 1 && newwhite[x+6][y+6] == 0 )
                            act[m][n] += 500000;
                        //0111112
                        if( newwhite[x][y] == 0 && newwhite[x+1][y+1] == 1 && newwhite[x+2][y+2] == 1 && newwhite[x+3][y+3] == 1 && newwhite[x+4][y+4] == 1 &&
                            newwhite[x+5][y+5] == 1 && newwhite[x+6][y+6] == 2 )
                            act[m][n] += 500000;
                        //121111
                        if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 1 && newwhite[x+3][y+3] == 1 && newwhite[x+4][y+4] == 1 &&
                            newwhite[x+5][y+5] == 1 )
                            act[m][n] += 500000;
                        //112111
                        if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 1 && newwhite[x+2][y+2] == 2 && newwhite[x+3][y+3] == 1 && newwhite[x+4][y+4] == 1 &&
                            newwhite[x+5][y+5] == 1 )
                            act[m][n] += 500000;
                        //111211
                        if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 1 && newwhite[x+2][y+2] == 1 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] == 1 &&
                            newwhite[x+5][y+5] == 1 )
                            act[m][n] += 500000;
                        //111121
                        if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 1 && newwhite[x+2][y+2] == 1 && newwhite[x+3][y+3] == 1 && newwhite[x+4][y+4] == 2 &&
                            newwhite[x+5][y+5] == 1 )
                            act[m][n] += 500000;

                        //추가부분 상대방 4개짜리 사이 빈칸있을때 사이 막기
                        //202122
                        if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 0 && newwhite[x+2][y+2] == 1 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] == 1 &&
                            newwhite[x+5][y+5] == 1 )
                            act[m][n] += 500000;
                        //202212
                        if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 0 && newwhite[x+2][y+2] == 1 && newwhite[x+3][y+3] == 1 && newwhite[x+4][y+4] == 2 &&
                            newwhite[x+5][y+5] == 1 )
                            act[m][n] += 500000;
                        //212022
                        if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 1 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] == 1 &&
                            newwhite[x+5][y+5] == 1 )
                            act[m][n] += 500000;
                        //212202
                        if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 1 && newwhite[x+3][y+3] == 1 && newwhite[x+4][y+4] == 0 &&
                            newwhite[x+5][y+5] == 1 )
                            act[m][n] += 500000;
                        //221202
                        if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 1 && newwhite[x+2][y+2] == 2 && newwhite[x+3][y+3] == 1 && newwhite[x+4][y+4] == 0 &&
                            newwhite[x+5][y+5] == 1 )
                            act[m][n] += 500000;
                        //220212
                        if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 1 && newwhite[x+2][y+2] == 0 && newwhite[x+3][y+3] == 1 && newwhite[x+4][y+4] == 2 &&
                            newwhite[x+5][y+5] == 1 )
                            act[m][n] += 500000;

                        //211112
                        if( newwhite[x][y] == 2 && newwhite[x+1][y+1] == 1 && newwhite[x+2][y+2] == 1 && newwhite[x+3][y+3] == 1 && newwhite[x+4][y+4] == 1 &&
                            newwhite[x+5][y+5] == 2 )
                            act[m][n] += 500000;
                        //211110
                        if( newwhite[x][y] == 2 && newwhite[x+1][y+1] == 1 && newwhite[x+2][y+2] == 1 && newwhite[x+3][y+3] == 1 && newwhite[x+4][y+4] == 1 &&
                            newwhite[x+5][y+5] == 0 )
                            act[m][n] += 500000;
                        //011112
                        if( newwhite[x][y] == 0 && newwhite[x+1][y+1] == 1 && newwhite[x+2][y+2] == 1 && newwhite[x+3][y+3] == 1 && newwhite[x+4][y+4] == 1 &&
                            newwhite[x+5][y+5] == 2)
                            act[m][n] += 500000;
                        //2111102
                        if( newwhite[x][y] == 2 && newwhite[x+1][y+1] == 1 && newwhite[x+2][y+2] == 1 && newwhite[x+3][y+3] == 1 && newwhite[x+4][y+4] == 1 &&
                            newwhite[x+5][y+5] == 0 && newwhite[x+6][y+6] == 2 )
                            act[m][n] += 500000;
                        //2011112
                        if( newwhite[x][y] == 2 && newwhite[x+1][y+1] == 0 && newwhite[x+2][y+2] == 1 && newwhite[x+3][y+3] == 1 && newwhite[x+4][y+4] == 1 &&
                            newwhite[x+5][y+5] == 1 && newwhite[x+6][y+6] == 2 )
                            act[m][n] += 500000;

                        //x12111
                        if( newwhite[x][y] != 2 && newwhite[x+1][y+1] == 1 && newwhite[x+2][y+2] == 2 && newwhite[x+3][y+3] == 1 && newwhite[x+4][y+4] == 1 &&
                            newwhite[x+5][y+5] == 1  )
                            act[m][n] += 500000;
                        //12111x
                        if( newwhite[x+1][y+1] == 1 && newwhite[x+2][y+2] == 2 && newwhite[x+3][y+3] == 1 && newwhite[x+4][y+4] == 1 &&
                            newwhite[x+5][y+5] == 1 && newwhite[x+6][y+6] != 2 )
                            act[m][n] += 500000;
                        //x11211
                        if( newwhite[x][y] != 2 && newwhite[x+1][y+1] == 1 && newwhite[x+2][y+2] == 1 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] == 1 &&
                            newwhite[x+5][y+5] == 1 )
                            act[m][n] += 500000;
                        //11211x
                        if( newwhite[x+1][y+1] == 1 && newwhite[x+2][y+2] == 1 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] == 1 &&
                            newwhite[x+5][y+5] == 1 && newwhite[x+6][y+6] != 2 )
                            act[m][n] += 500000;
                        //x11121
                        if( newwhite[x][y] != 2 && newwhite[x+1][y+1] == 1 && newwhite[x+2][y+2] == 1 && newwhite[x+3][y+3] == 1 && newwhite[x+4][y+4] == 2 &&
                            newwhite[x+5][y+5] == 1 )
                            act[m][n] += 500000;
                        //11121x
                        if( newwhite[x+1][y+1] == 1 && newwhite[x+2][y+2] == 1 && newwhite[x+3][y+3] == 1 && newwhite[x+4][y+4] == 2 &&
                            newwhite[x+5][y+5] == 1 && newwhite[x+6][y+6] != 2 )
                            act[m][n] += 500000;


                        //120111
                        if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 0 && newwhite[x+3][y+3] == 1 && newwhite[x+4][y+4] == 1 &&
                            newwhite[x+5][y+5] == 1 )
                            act[m][n] += 500000;
                        //102111
                        if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 0 && newwhite[x+2][y+2] == 2 && newwhite[x+3][y+3] == 1 && newwhite[x+4][y+4] == 1 &&
                            newwhite[x+5][y+5] == 1 )
                            act[m][n] += 500000;
                        //111201
                        if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 1 && newwhite[x+2][y+2] == 1 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] == 0 &&
                            newwhite[x+5][y+5] == 1 )
                            act[m][n] += 500000;
                        //111021
                        if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 1 && newwhite[x+2][y+2] == 1 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] == 2 &&
                            newwhite[x+5][y+5] == 1 )
                            act[m][n] += 500000;
                        //112011
                        if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 1 && newwhite[x+2][y+2] == 2 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] == 1 &&
                            newwhite[x+5][y+5] == 1 )
                            act[m][n] += 500000;
                        //110211
                        if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 1 && newwhite[x+2][y+2] == 0 && newwhite[x+3][y+3] == 2 && newwhite[x+4][y+4] == 1 &&
                            newwhite[x+5][y+5] == 1 )
                            act[m][n] += 500000;


                        //여기서부터 간단한 가중치 줄 것. 즉, 2개 3개 막게하는것들
                        //2111
                        if( newwhite[x][y] == 2 && newwhite[x+1][y+1] == 1 && newwhite[x+2][y+2] == 1 && newwhite[x+3][y+3] == 1 )
                            act[m][n] += 3500;
                        //1112
                        if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 1 && newwhite[x+2][y+2] == 1 && newwhite[x+3][y+3] == 2 )
                            act[m][n] += 3500;
                        //1211
                        if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 1 && newwhite[x+3][y+3] == 1 )
                            act[m][n] += 4000;
                        //1121
                        if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 1 && newwhite[x+2][y+2] == 2 && newwhite[x+3][y+3] == 1 )
                            act[m][n] += 4000;
                        //11102		분기해서 막는것도 필요한 경우가 있을수있음. 단 점수는 낮게
                        if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 1 && newwhite[x+2][y+2] == 1 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] == 2 )
                            act[m][n] += 1500;
                        //20111
                        if( newwhite[x][y] == 2 && newwhite[x+1][y+1] == 0 && newwhite[x+2][y+2] == 1 && newwhite[x+3][y+3] == 1 && newwhite[x+4][y+4] == 1 )
                            act[m][n] += 1500;

                        //21011		점수낮게
                        if( newwhite[x][y] == 2 && newwhite[x+1][y+1] == 1 && newwhite[x+2][y+2] == 0 && newwhite[x+3][y+3] == 1 && newwhite[x+4][y+4] == 1 )
                            act[m][n] += 1500;
                        //21101		점수낮게
                        if( newwhite[x][y] == 2 && newwhite[x+1][y+1] == 1 && newwhite[x+2][y+2] == 1 && newwhite[x+3][y+3] == 0 && newwhite[x+4][y+4] == 1 )
                            act[m][n] += 1500;
                        //10112		점수낮게
                        if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 0 && newwhite[x+2][y+2] == 1 && newwhite[x+3][y+3] == 1 && newwhite[x+4][y+4] == 2 )
                            act[m][n] += 1500;
                        //11012		점수낮게
                        if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 1 && newwhite[x+2][y+2] == 0 && newwhite[x+3][y+3] == 1 && newwhite[x+4][y+4] == 2 )
                            act[m][n] += 1500;

                        //211
                        if( newwhite[x][y] == 2 && newwhite[x+1][y+1] == 1 && newwhite[x+2][y+2] == 1 )
                            act[m][n] += 500;
                        //112
                        if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 1 && newwhite[x+2][y+2] == 2 )
                            act[m][n] += 500;
                        //121
                        if( newwhite[x][y] == 1 && newwhite[x+1][y+1] == 2 && newwhite[x+2][y+2] == 1 )
                            act[m][n] += 800;

                    }
                }
                newwhite[m][n] = 0;
            }
        }

}

void AI::defense_in_slash_check_W()
{
    for(int m=0 ; m<19 ; m++)
        {
            for(int n=0 ; n<19 ; n++)
            {
                if( newwhite[m][n] == 0 )
                {
                    newwhite[m][n] = 2;
                }
                else if( newwhite[m][n] == 1 || newwhite[m][n] == 2 )
                {
                    continue;
                }

                for(int x=0; x<19; x++)
                {
                    for(int y=0; y<19; y++)
                    {
                        //다섯개에 양쪽다 막도록.
                        //2111112 이런상황이 되게 할때 점수가 높이 준다.
                        if( newwhite[x][y] == 2 && newwhite[x+1][y-1] == 1 && newwhite[x+2][y-2] == 1 && newwhite[x+3][y-3] == 1 && newwhite[x+4][y-4] == 1 &&
                            newwhite[x+5][y-5] == 1 && newwhite[x+6][y-6] == 2 )
                            act[m][n] += 750000;
                        //2111110
                        if( newwhite[x][y] == 2 && newwhite[x+1][y-1] == 1 && newwhite[x+2][y-2] == 1 && newwhite[x+3][y-3] == 1 && newwhite[x+4][y-4] == 1 &&
                            newwhite[x+5][y-5] == 1 && newwhite[x+6][y-6] == 0 )
                            act[m][n] += 500000;
                        //0111112
                        if( newwhite[x][y] == 0 && newwhite[x+1][y-1] == 1 && newwhite[x+2][y-2] == 1 && newwhite[x+3][y-3] == 1 && newwhite[x+4][y-4] == 1 &&
                            newwhite[x+5][y-5] == 1 && newwhite[x+6][y-6] == 2 )
                            act[m][n] += 500000;
                        //121111
                        if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 1 && newwhite[x+3][y-3] == 1 && newwhite[x+4][y-4] == 1 &&
                            newwhite[x+5][y-5] == 1 )
                            act[m][n] += 500000;
                        //112111
                        if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 1 && newwhite[x+2][y-2] == 2 && newwhite[x+3][y-3] == 1 && newwhite[x+4][y-4] == 1 &&
                            newwhite[x+5][y-5] == 1 )
                            act[m][n] += 500000;
                        //111211
                        if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 1 && newwhite[x+2][y-2] == 1 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] == 1 &&
                            newwhite[x+5][y-5] == 1 )
                            act[m][n] += 500000;
                        //111121
                        if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 1 && newwhite[x+2][y-2] == 1 && newwhite[x+3][y-3] == 1 && newwhite[x+4][y-4] == 2 &&
                            newwhite[x+5][y-5] == 1 )
                            act[m][n] += 500000;

                        //추가부분 상대방 4개짜리 사이 빈칸있을때 사이 막기
                        //202122
                        if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 0 && newwhite[x+2][y-2] == 1 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] == 1 &&
                            newwhite[x+5][y-5] == 1 )
                            act[m][n] += 500000;
                        //202212
                        if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 0 && newwhite[x+2][y-2] == 1 && newwhite[x+3][y-3] == 1 && newwhite[x+4][y-4] == 2 &&
                            newwhite[x+5][y-5] == 1 )
                            act[m][n] += 500000;
                        //212022
                        if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 1 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] == 1 &&
                            newwhite[x+5][y-5] == 1 )
                            act[m][n] += 500000;
                        //212202
                        if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 1 && newwhite[x+3][y-3] == 1 && newwhite[x+4][y-4] == 0 &&
                            newwhite[x+5][y-5] == 1 )
                            act[m][n] += 500000;
                        //221202
                        if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 1 && newwhite[x+2][y-2] == 2 && newwhite[x+3][y-3] == 1 && newwhite[x+4][y-4] == 0 &&
                            newwhite[x+5][y-5] == 1 )
                            act[m][n] += 500000;
                        //220212
                        if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 1 && newwhite[x+2][y-2] == 0 && newwhite[x+3][y-3] == 1 && newwhite[x+4][y-4] == 2 &&
                            newwhite[x+5][y-5] == 1 )
                            act[m][n] += 500000;

                        //211112
                        if( newwhite[x][y] == 2 && newwhite[x+1][y-1] == 1 && newwhite[x+2][y-2] == 1 && newwhite[x+3][y-3] == 1 && newwhite[x+4][y-4] == 1 &&
                            newwhite[x+5][y-5] == 2 )
                            act[m][n] += 500000;
                        //211110
                        if( newwhite[x][y] == 2 && newwhite[x+1][y-1] == 1 && newwhite[x+2][y-2] == 1 && newwhite[x+3][y-3] == 1 && newwhite[x+4][y-4] == 1 &&
                            newwhite[x+5][y-5] == 0 )
                            act[m][n] += 500000;
                        //011112
                        if( newwhite[x][y] == 0 && newwhite[x+1][y-1] == 1 && newwhite[x+2][y-2] == 1 && newwhite[x+3][y-3] == 1 && newwhite[x+4][y-4] == 1 &&
                            newwhite[x+5][y-5] == 2)
                            act[m][n] += 500000;
                        //2111102
                        if( newwhite[x][y] == 2 && newwhite[x+1][y-1] == 1 && newwhite[x+2][y-2] == 1 && newwhite[x+3][y-3] == 1 && newwhite[x+4][y-4] == 1 &&
                            newwhite[x+5][y-5] == 0 && newwhite[x+6][y-6] == 2 )
                            act[m][n] += 500000;
                        //2011112
                        if( newwhite[x][y] == 2 && newwhite[x+1][y-1] == 0 && newwhite[x+2][y-2] == 1 && newwhite[x+3][y-3] == 1 && newwhite[x+4][y-4] == 1 &&
                            newwhite[x+5][y-5] == 1 && newwhite[x+6][y-6] == 2 )
                            act[m][n] += 500000;

                        //x12111x
                        if( newwhite[x+1][y-1] == 1 && newwhite[x+2][y-2] == 2 && newwhite[x+3][y-3] == 1 && newwhite[x+4][y-4] == 1 &&
                            newwhite[x+5][y-5] == 1 && newwhite[x+6][y-6] != 2 )
                            act[m][n] += 500000;
                        //x11211x
                        if( newwhite[x+1][y-1] == 1 && newwhite[x+2][y-2] == 1 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] == 1 &&
                            newwhite[x+5][y-5] == 1 && newwhite[x+6][y-6] != 2 )
                            act[m][n] += 500000;
                        //x11121x
                        if( newwhite[x+1][y-1] == 1 && newwhite[x+2][y-2] == 1 && newwhite[x+3][y-3] == 1 && newwhite[x+4][y-4] == 2 &&
                            newwhite[x+5][y-5] == 1 && newwhite[x+6][y-6] != 2 )
                            act[m][n] += 500000;
                        //x12111x
                        if( newwhite[x][y] != 2 && newwhite[x+1][y-1] == 1 && newwhite[x+2][y-2] == 2 && newwhite[x+3][y-3] == 1 && newwhite[x+4][y-4] == 1 &&
                            newwhite[x+5][y-5] == 1 )
                            act[m][n] += 500000;
                        //x11211x
                        if( newwhite[x][y] != 2 && newwhite[x+1][y-1] == 1 && newwhite[x+2][y-2] == 1 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] == 1 &&
                            newwhite[x+5][y-5] == 1 )
                            act[m][n] += 500000;
                        //x11121x
                        if( newwhite[x][y] != 2 && newwhite[x+1][y-1] == 1 && newwhite[x+2][y-2] == 1 && newwhite[x+3][y-3] == 1 && newwhite[x+4][y-4] == 2 &&
                            newwhite[x+5][y-5] == 1 )
                            act[m][n] += 500000;

                        //120111
                        if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 0 && newwhite[x+3][y-3] == 1 && newwhite[x+4][y-4] == 1 &&
                            newwhite[x+5][y-5] == 1 )
                            act[m][n] += 500000;
                        //102111
                        if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 0 && newwhite[x+2][y-2] == 2 && newwhite[x+3][y-3] == 1 && newwhite[x+4][y-4] == 1 &&
                            newwhite[x+5][y-5] == 1 )
                            act[m][n] += 500000;
                        //111201
                        if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 1 && newwhite[x+2][y-2] == 1 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] == 0 &&
                            newwhite[x+5][y-5] == 1 )
                            act[m][n] += 500000;
                        //111021
                        if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 1 && newwhite[x+2][y-2] == 1 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] == 2 &&
                            newwhite[x+5][y-5] == 1 )
                            act[m][n] += 500000;
                        //112011
                        if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 1 && newwhite[x+2][y-2] == 2 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] == 1 &&
                            newwhite[x+5][y-5] == 1 )
                            act[m][n] += 500000;
                        //110211
                        if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 1 && newwhite[x+2][y-2] == 0 && newwhite[x+3][y-3] == 2 && newwhite[x+4][y-4] == 1 &&
                            newwhite[x+5][y-5] == 1 )
                            act[m][n] += 500000;

                        //여기서부터 간단한 가중치 줄 것. 즉, 2개 3개 막게하는것들
                        //2111
                        if( newwhite[x][y] == 2 && newwhite[x+1][y-1] == 1 && newwhite[x+2][y-2] == 1 && newwhite[x+3][y-3] == 1 )
                            act[m][n] += 3500;
                        //1112
                        if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 1 && newwhite[x+2][y-2] == 1 && newwhite[x+3][y-3] == 2 )
                            act[m][n] += 3500;
                        //1211
                        if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 1 && newwhite[x+3][y-3] == 1 )
                            act[m][n] += 4000;
                        //1121
                        if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 1 && newwhite[x+2][y-2] == 2 && newwhite[x+3][y-3] == 1 )
                            act[m][n] += 4000;
                        //11102		분기해서 막는것도 필요한 경우가 있을수있음. 단 점수는 낮게
                        if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 1 && newwhite[x+2][y-2] == 1 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] == 2 )
                            act[m][n] += 1500;
                        //20111
                        if( newwhite[x][y] == 2 && newwhite[x+1][y-1] == 0 && newwhite[x+2][y-2] == 1 && newwhite[x+3][y-3] == 1 && newwhite[x+4][y-4] == 1 )
                            act[m][n] += 1500;

                        //21011		점수낮게
                        if( newwhite[x][y] == 2 && newwhite[x+1][y-1] == 1 && newwhite[x+2][y-2] == 0 && newwhite[x+3][y-3] == 1 && newwhite[x+4][y-4] == 1 )
                            act[m][n] += 1500;
                        //21101		점수낮게
                        if( newwhite[x][y] == 2 && newwhite[x+1][y-1] == 1 && newwhite[x+2][y-2] == 1 && newwhite[x+3][y-3] == 0 && newwhite[x+4][y-4] == 1 )
                            act[m][n] += 1500;
                        //10112		점수낮게
                        if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 0 && newwhite[x+2][y-2] == 1 && newwhite[x+3][y-3] == 1 && newwhite[x+4][y-4] == 2 )
                            act[m][n] += 1500;
                        //11012		점수낮게
                        if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 1 && newwhite[x+2][y-2] == 0 && newwhite[x+3][y-3] == 1 && newwhite[x+4][y-4] == 2 )
                            act[m][n] += 1500;

                        //211
                        if( newwhite[x][y] == 2 && newwhite[x+1][y-1] == 1 && newwhite[x+2][y-2] == 1 )
                            act[m][n] += 500;
                        //112
                        if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 1 && newwhite[x+2][y-2] == 2 )
                            act[m][n] += 500;
                        //121
                        if( newwhite[x][y] == 1 && newwhite[x+1][y-1] == 2 && newwhite[x+2][y-2] == 1 )
                            act[m][n] += 800;
                    }
                }
                newwhite[m][n] = 0;
            }
        }

}










void AI::clear (void){

    this->type=TYPE_EMPTY;
    this->setPixmap(*empty);
}

