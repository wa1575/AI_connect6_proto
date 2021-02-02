#include "ai.h"
#include "board.h"

AI::AI(const int &y, const int &x, QPixmap *empty, Board *parent)
{

    this->x=y;
    this->y=x;
    this->empty=empty;
    this->type=TYPE_EMPTY;
    this->parentPtr=parent;
    this->gameType=TYPE_LOCAL;
    this->game=1;
    this->setPixmap(*empty);

    for(i=0; i<19; i++)
        {
            for(j=0; j<19; j++)
            {
                this->b[i][j] = 0;
                this->w[i][j] = 0;
            }
        }

        for(i=0; i<19; i++)
        {
            this->b[i][18] = 3;
            this->w[i][18] = 3;
        }


}

void AI::insertAI_W()
{
        W_AI_allcheck();
        switch (this->parentPtr->gameType){//로컬,클라이언트 모드
            case Board::TYPE_LOCAL:
                this->parentPtr->addItem (this->wx, this->wy);
                break;

            case Board::TYPE_SERVER:
                if ((int)parentPtr->activeType==(int)Board::TYPE_SERVER){
                    this->parentPtr->server->writeToClient("200 "+QString::number(this->wx)+" "+QString::number(this->wy)+"\n");
                    this->parentPtr->addItem (wx, wy);
                }
                break;

            case Board::TYPE_CLIENT:
                if ((int)this->parentPtr->activeType==(int)Board::TYPE_CLIENT){
                    this->parentPtr->client->writeToServer ("200 "+QString::number(this->wx)+" "+QString::number(this->wy)+"\n");
                    this->parentPtr->addItem (wx, wy);
                }
                break;
            }
           w[wx][wy]=2;
}


void AI::insertAI_B()
{
     B_AI_allcheck();
    switch (this->parentPtr->gameType){
        case Board::TYPE_LOCAL:
            this->parentPtr->addItem (this->bx, this->by);
            break;

        case Board::TYPE_SERVER:
            if ((int)parentPtr->activeType==(int)Board::TYPE_SERVER){
                this->parentPtr->server->writeToClient("200 "+QString::number(this->bx)+" "+QString::number(this->by)+"\n");
                this->parentPtr->addItem (bx, by);
            }
            break;

        case Board::TYPE_CLIENT:
            if ((int)this->parentPtr->activeType==(int)Board::TYPE_CLIENT){
                this->parentPtr->client->writeToServer ("200 "+QString::number(this->bx)+" "+QString::number(this->by)+"\n");
                this->parentPtr->addItem (this->bx, this->by);
            }
            break;
        }
       b[bx][by]=1;
}




void AI::insertAI_B_first()
{
    int temp_rand_x;
    int temp_rand_y;
    srand((unsigned)time(NULL));
    temp_rand_x = rand()%3+9;
    temp_rand_y = rand()%3+9;
    bx = temp_rand_x;
    by = temp_rand_y;
    switch (this->parentPtr->gameType){
        case Board::TYPE_LOCAL:
            this->parentPtr->addItem (this->bx, this->by);
            break;

        case Board::TYPE_SERVER:
            if ((int)parentPtr->activeType==(int)Board::TYPE_SERVER){
                this->parentPtr->server->writeToClient("200 "+QString::number(this->bx)+" "+QString::number(this->by)+"\n");
                this->parentPtr->addItem (bx, by);
            }
            break;

        case Board::TYPE_CLIENT:
            if ((int)this->parentPtr->activeType==(int)Board::TYPE_CLIENT){
                this->parentPtr->client->writeToServer ("200 "+QString::number(this->bx)+" "+QString::number(this->by)+"\n");
                this->parentPtr->addItem (this->bx, this->by);
            }
            break;
        }
}


void AI::insertAI_W_first1()//잘 됨
{
    for(int x=0; x<19; x++)
    {
        for(int y=0; y<19; y++)
        {
            if(this->b[x][y] == 1)
            {
                this->wx = x;
                this->wy = y-1;
            }
        }
    }

    switch (this->parentPtr->gameType){
        case Board::TYPE_LOCAL:
            this->parentPtr->addItem (this->wx, this->wy);
            break;

        case Board::TYPE_SERVER:
            if ((int)parentPtr->activeType==(int)Board::TYPE_SERVER){
                this->parentPtr->server->writeToClient("200 "+QString::number(this->wx)+" "+QString::number(this->wy)+"\n");
                this->parentPtr->addItem (wx, wy);
            }
            break;

        case Board::TYPE_CLIENT:
            if ((int)this->parentPtr->activeType==(int)Board::TYPE_CLIENT){
                this->parentPtr->client->writeToServer ("200 "+QString::number(this->wx)+" "+QString::number(this->wy)+"\n");
                this->parentPtr->addItem (wx, wy);
            }
            break;
        }
}


void AI::insertAI_W_first2()
{
        for(int x=0; x<19; x++)
        {
            for(int y=0; y<19; y++)
            {
                if(this->b[x][y] == 1)
                {
                    this->wx = x;
                    this->wy = y+1;
                }
            }
        }
        switch (this->parentPtr->gameType){//로컬,서버,클라이언트모드
            case Board::TYPE_LOCAL:
                this->parentPtr->addItem (this->wx, this->wy);//x,y좌표 그대로 넣으면 됨
                break;

            case Board::TYPE_SERVER:
                if ((int)parentPtr->activeType==(int)Board::TYPE_SERVER){
                    this->parentPtr->server->writeToClient("200 "+QString::number(this->wx)+" "+QString::number(this->wy)+"\n");
                    this->parentPtr->addItem (wx, wy);
                }
                break;

            case Board::TYPE_CLIENT:
                if ((int)this->parentPtr->activeType==(int)Board::TYPE_CLIENT){
                    this->parentPtr->client->writeToServer ("200 "+QString::number(this->wx)+" "+QString::number(this->wy)+"\n");
                    this->parentPtr->addItem (wx, wy);
                }
                break;
            }

}

void AI::change_w(int a, int b)
{
    this->w[a][b] = 2;
}

void AI::change_b(int c, int d)
{
    this->b[c][d] = 1;
}



void AI::W_AI_allcheck()//킬각을 잘 못봄...
{   //가중치 초기화
    for(int x_new=0; x_new<19; x_new++)
        {
            for(int y_new=0; y_new<19; y_new++)
            {
                W_weight[x_new][y_new] = 0;
                if( w[x_new][y_new] == 2 )
                {
                    if_w[x_new][y_new] = 2;
                }
                if( b[x_new][y_new] == 1 )
                {
                    if_w[x_new][y_new] = 1;
                }
                else;
            }
        }

        W_AI_5_6_7_check();

        defense_Horizontal_check_W();
        defense_Vertical_check_W();
        defense_Diagonal_check_W();
        defense_in_Diagonal_check_W();

        W_AI_2_Horizontal_check();
        W_AI_3_Horizontal_check();
        W_AI_4_Horizontal_check();

        W_AI_2_Vertical_check();
        W_AI_3_Vertical_check();
        W_AI_4_Vertical_check();

        W_AI_2_Diagonal_check();
        W_AI_3_Diagonal_check();
        W_AI_4_Diagonal_check();

        W_AI_2_in_Diagonal_check();
        W_AI_3_in_Diagonal_check();
        W_AI_4_in_Diagonal_check();

        for(int x=0; x<19; x++)
        {
            for(int y=0; y<19; y++)
            {
                if(b[x][y] ==1 || w[x][y] == 2)
                {
                    W_weight[x][y] = 0;
                }
            }
        }

        max_weight = 0;


        for(int max_x=0; max_x<19; max_x++) // 최대 가중치 찾기
        {
            for(int max_y=0; max_y<19; max_y++)
            {
                if(max_weight < W_weight[max_x][max_y])
                {
                    max_weight = W_weight[max_x][max_y];
                    wx = max_x;
                    wy = max_y;
                }
                //만약 같은점수라면 랜덤으로
                else if(max_weight == W_weight[max_x][max_y])
                {
                    srand((unsigned)time(NULL));
                    int random = rand()%2;
                    if(random == 0)
                    {
                        max_weight = W_weight[max_x][max_y];
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
          if( if_w[m][n] == 0 )
          {
          if_w[m][n] = 2;
          }
          else if( if_w[m][n] == 1 || if_w[m][n] == 2 )
          {
              continue;
          }

          for(int x=0; x<19; x++)
          {
              for(int y=0; y<19; y++)
              {

            if(turn == 1)	//첫 번째 턴일때만 적요으 이길수있는상황에는 4개를 5개로 만들게함
            {
                //첫째턴, 6개까지 만들 여지가 있을 경우 & 가로
                if( if_w[x][y] == 0 && if_w[x][y+1] == 2 && if_w[x][y+2] == 2 && if_w[x][y+3] == 2 && if_w[x][y+4] == 2 &&
                    if_w[x][y+5] == 2 )
                    W_weight[m][n] += 45000000;
                if( if_w[x][y] == 2 && if_w[x][y+1] == 2 && if_w[x][y+2] == 2 && if_w[x][y+3] == 2 && if_w[x][y+4] == 2 &&
                    if_w[x][y+5] == 0 )
                    W_weight[m][n] += 45000000;
                if( if_w[x][y] == 2 && if_w[x][y+1] == 0 && if_w[x][y+2] == 2 && if_w[x][y+3] == 2 && if_w[x][y+4] == 2 &&
                    if_w[x][y+5] == 2 )
                    W_weight[m][n] += 45000000;
                if( if_w[x][y] == 2 && if_w[x][y+1] == 2 && if_w[x][y+2] == 2 && if_w[x][y+3] == 2 && if_w[x][y+4] == 0 &&
                    if_w[x][y+5] == 2 )
                    W_weight[m][n] += 45000000;
                if( if_w[x][y] == 2 && if_w[x][y+1] == 2 && if_w[x][y+2] == 0 && if_w[x][y+3] == 2 && if_w[x][y+4] == 2 &&
                    if_w[x][y+5] == 2 )
                    W_weight[m][n] += 45000000;
                if( if_w[x][y] == 2 && if_w[x][y+1] == 2 && if_w[x][y+2] == 2 && if_w[x][y+3] == 0 && if_w[x][y+4] == 2 &&
                    if_w[x][y+5] == 2 )
                    W_weight[m][n] += 45000000;

                //첫째턴, 6개까지 만들 여지가 있을 경우 & 세로
                if( if_w[x][y] == 0 && if_w[x+1][y] == 2 && if_w[x+2][y] == 2 && if_w[x+3][y] == 2 && if_w[x+4][y] == 2 &&
                    if_w[x+5][y] == 2 )
                    W_weight[m][n] += 45000000;
                if( if_w[x][y] == 2 && if_w[x+1][y] == 2 && if_w[x+2][y] == 2 && if_w[x+3][y] == 2 && if_w[x+4][y] == 2 &&
                    if_w[x+5][y] == 0 )
                    W_weight[m][n] += 45000000;
                if( if_w[x][y] == 2 && if_w[x+1][y] == 0 && if_w[x+2][y] == 2 && if_w[x+3][y] == 2 && if_w[x+4][y] == 2 &&
                    if_w[x+5][y] == 2 )
                    W_weight[m][n] += 45000000;
                if( if_w[x][y] == 2 && if_w[x+1][y] == 2 && if_w[x+2][y] == 2 && if_w[x+3][y] == 2 && if_w[x+4][y] == 0 &&
                    if_w[x+5][y] == 2 )
                    W_weight[m][n] += 45000000;
                if( if_w[x][y] == 2 && if_w[x+1][y] == 2 && if_w[x+2][y] == 0 && if_w[x+3][y] == 2 && if_w[x+4][y] == 2 &&
                    if_w[x+5][y] == 2 )
                    W_weight[m][n] += 45000000;
                if( if_w[x][y] == 2 && if_w[x+1][y] == 2 && if_w[x+2][y] == 2 && if_w[x+3][y] == 0 && if_w[x+4][y] == 2 &&
                    if_w[x+5][y] == 2 )
                    W_weight[m][n] += 45000000;

                //첫째턴, 6개까지 만들 여지가 있을 경우 & 대각선
                if( if_w[x][y] == 0 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 2 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] == 2 &&
                    if_w[x+5][y+5] == 2 )
                    W_weight[m][n] += 45000000;
                if( if_w[x][y] == 2 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 2 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] == 2 &&
                    if_w[x+5][y+5] == 0 )
                    W_weight[m][n] += 45000000;
                if( if_w[x][y] == 2 && if_w[x+1][y+1] == 0 && if_w[x+2][y+2] == 2 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] == 2 &&
                    if_w[x+5][y+5] == 2 )
                    W_weight[m][n] += 45000000;
                if( if_w[x][y] == 2 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 2 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] == 0 &&
                    if_w[x+5][y+5] == 2 )
                    W_weight[m][n] += 45000000;
                if( if_w[x][y] == 2 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 0 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] == 2 &&
                    if_w[x+5][y+5] == 2 )
                    W_weight[m][n] += 45000000;
                if( if_w[x][y] == 2 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 2 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] == 2 &&
                    if_w[x+5][y+5] == 2 )
                    W_weight[m][n] += 45000000;

                //첫째턴, 6개까지 만들 여지가 있을 경우 & 역대각선
                if( if_w[x][y] == 0 && if_w[x+1][y-1] == 2 && if_w[x+2][y-2] == 2 && if_w[x+3][y-3] == 2 && if_w[x+4][y-4] == 2 &&
                    if_w[x+5][y-5] == 2 )
                    W_weight[m][n] += 45000000;
                if( if_w[x][y] == 2 && if_w[x+1][y-1] == 2 && if_w[x+2][y-2] == 2 && if_w[x+3][y-3] == 2 && if_w[x+4][y-4] == 2 &&
                    if_w[x+5][y-5] == 0 )
                    W_weight[m][n] += 45000000;
                if( if_w[x][y] == 2 && if_w[x+1][y-1] == 0 && if_w[x+2][y-2] == 2 && if_w[x+3][y-3] == 2 && if_w[x+4][y-4] == 2 &&
                    if_w[x+5][y-5] == 2 )
                    W_weight[m][n] += 45000000;
                if( if_w[x][y] == 2 && if_w[x+1][y-1] == 2 && if_w[x+2][y-2] == 2 && if_w[x+3][y-3] == 2 && if_w[x+4][y-4] == 0 &&
                    if_w[x+5][y-5] == 2 )
                    W_weight[m][n] += 45000000;
                if( if_w[x][y] == 2 && if_w[x+1][y-1] == 2 && if_w[x+2][y-2] == 0 && if_w[x+3][y-3] == 2 && if_w[x+4][y-4] == 2 &&
                    if_w[x+5][y-5] == 2 )
                    W_weight[m][n] += 45000000;
                if( if_w[x][y] == 2 && if_w[x+1][y-1] == 2 && if_w[x+2][y-2] == 2 && if_w[x+3][y-3] == 0 && if_w[x+4][y-4] == 2 &&
                    if_w[x+5][y-5] == 2 )
                    W_weight[m][n] += 45000000;
            }
            // 양쪽이 막힌 경우엔... 의미없음...
            if( if_w[x][y] == 1 && if_w[x][y+1] == 2 && if_w[x][y+2] == 2 && if_w[x][y+3] == 2 && if_w[x][y+4] == 2 &&
                if_w[x][y+5] == 2 && if_w[x][y+6] == 1 )
                W_weight[m][n] = 0;
            if( if_w[x][y] == 1 && if_w[x+1][y] == 2 && if_w[x+2][y] == 2 && if_w[x+3][y] == 2 && if_w[x+4][y] == 2 &&
                if_w[x+5][y] == 2 && if_w[x+6][y] == 1 )
                W_weight[m][n] = 0;
            if( if_w[x][y] == 1 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 2 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] == 2 &&
                if_w[x+5][y+5] == 2 && if_w[x+6][y+6] == 1 )
                W_weight[m][n] = 0;
            if( if_w[x][y] == 1 && if_w[x+1][y-1] == 2 && if_w[x+2][y-2] == 2 && if_w[x+3][y-3] == 2 && if_w[x+4][y-4] == 2 &&
                if_w[x+5][y-5] == 2 && if_w[x+6][y-6] == 1 )
                W_weight[m][n] = 0;

            //가로로 이길수있을때...킬각재기 잘 안됨
            if( if_w[x][y] == 2 && if_w[x][y+1] == 2 && if_w[x][y+2] == 2 && if_w[x][y+3] == 2 && if_w[x][y+4] == 2 &&
                if_w[x][y+5] == 2 )
                W_weight[m][n] += 99999999999;
            //세로로 이길수있을때
            if( if_w[x][y] == 2 && if_w[x+1][y] == 2 && if_w[x+2][y] == 2 && if_w[x+3][y] == 2 && if_w[x+4][y] == 2 &&
                if_w[x+5][y] == 2 )
                W_weight[m][n] += 99999999999;
            //대각선으로 이길수있을때음
            if( if_w[x][y] == 2 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 2 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] == 2 &&
                if_w[x+5][y+5] == 2 )
                W_weight[m][n] += 99999999999;
            if( if_w[x][y] == 2 && if_w[x+1][y-1] == 2 && if_w[x+2][y-2] == 2 && if_w[x+3][y-3] == 2 && if_w[x+4][y-4] == 2 &&
                if_w[x+5][y-5] == 2 )
                W_weight[m][n] += 99999999999;
              }
          }
          if_w[m][n] = 0;
      }
    }

}

void AI::W_AI_2_Horizontal_check()
{
    for(int m=0 ; m<19 ; m++)
    {
      for(int n=0 ; n<19 ; n++)
      {
          if( if_w[m][n] == 0 )
          {
          if_w[m][n] = 2;
          }
          else if( if_w[m][n] == 1 || if_w[m][n] == 2 )
          {
              continue;
          }

          for(int x=0; x<19; x++)
          {
              for(int y=0; y<19; y++)
              {
            //00022000
            if( if_w[x][y-2] == 0 && if_w[x][y-1] == 0 && if_w[x][y] == 0 && if_w[x][y+1] == 2 && if_w[x][y+2] == 2 &&
                if_w[x][y+3] == 0 && if_w[x][y+4] == 0 && if_w[x][y+5] == 0 )
                W_weight[m][n] += 2000;
            //0020200
            if( if_w[x][y-1] == 0 && if_w[x][y] == 0 && if_w[x][y+1] == 2 && if_w[x][y+2] == 0 && if_w[x][y+3] == 2 && if_w[x][y+4] == 0 &&
                if_w[x][y+5] == 0 )
                W_weight[m][n] += 1500;
            //020020
            if( if_w[x][y] == 0 && if_w[x][y+1] == 2 && if_w[x][y+2] == 0 && if_w[x][y+3] == 0 && if_w[x][y+4] == 2 && if_w[x][y+5] == 0 )
                W_weight[m][n] += 1000;
            //여기까지 양쪽에 안 막힌, 흰 돌이 2개가 발견 될 때 경우의 수들

            //122000
            if( if_w[x][y] == 1 && if_w[x][y+1] == 2 && if_w[x][y+2] == 2 && if_w[x][y+3] == 0 && if_w[x][y+4] == 0 && if_w[x][y+5] == 0 )
                W_weight[m][n] += 500;
            //120200
            if( if_w[x][y] == 1 && if_w[x][y+1] == 2 && if_w[x][y+2] == 0 && if_w[x][y+3] == 2 && if_w[x][y+4] == 0 && if_w[x][y+5] == 0 )
                W_weight[m][n] += 500;
            //120020
            if( if_w[x][y] == 1 && if_w[x][y+1] == 2 && if_w[x][y+2] == 0 && if_w[x][y+3] == 0 && if_w[x][y+4] == 2 && if_w[x][y+5] == 0 )
                W_weight[m][n] += 500;
            //102200
            if( if_w[x][y] == 1 && if_w[x][y+1] == 0 && if_w[x][y+2] == 2 && if_w[x][y+3] == 2 && if_w[x][y+4] == 0 && if_w[x][y+5] == 0 )
                W_weight[m][n] += 800;
            //102020
            if( if_w[x][y] == 1 && if_w[x][y+1] == 0 && if_w[x][y+2] == 2 && if_w[x][y+3] == 0 && if_w[x][y+4] == 2 && if_w[x][y+5] == 0 )
                W_weight[m][n] += 800;
            //여기까지 왼쪽에 검은돌로 막힌 경우.
            //오른쪽에 검은돌로 막힌 경우는 이 대칭으로만 작성해주면됌

            //000221
            if( if_w[x][y-2] == 0 && if_w[x][y-1] == 0 && if_w[x][y] == 0 && if_w[x][y+1] == 2 && if_w[x][y+2] == 2 && if_w[x][y+3] == 1 )
                W_weight[m][n] += 500;
            //002021
            if( if_w[x][y-1] == 0 && if_w[x][y] == 0 && if_w[x][y+1] == 2 && if_w[x][y+2] == 0 && if_w[x][y+3] == 2 && if_w[x][y+4] == 1 )
                W_weight[m][n] += 500;
            //020021
            if( if_w[x][y] == 0 && if_w[x][y+1] == 2 && if_w[x][y+2] == 0 && if_w[x][y+3] == 0 && if_w[x][y+4] == 2 && if_w[x][y+5] == 1 )
                W_weight[m][n] += 500;
            //002201
            if( if_w[x][y-1] == 0 && if_w[x][y] == 0 && if_w[x][y+1] == 2 && if_w[x][y+2] == 2 && if_w[x][y+3] == 0 && if_w[x][y+4] == 1 )
                W_weight[m][n] += 800;
            //020201
            if( if_w[x][y] == 0 && if_w[x][y+1] == 2 && if_w[x][y+2] == 0 && if_w[x][y+3] == 2 && if_w[x][y+4] == 0 && if_w[x][y+5] == 1 )
                W_weight[m][n] += 800;
            //여기까지 한쪽이 막힌 경우.
            //그 다음은 양쪽이 막힌 경우. 양쪽이 막힌 경우는 안이 6칸일 경우만 따지자.

            //12200001
            if( if_w[x][y] == 1 && if_w[x][y+1] == 2 && if_w[x][y+2] == 2 && if_w[x][y+3] == 0 && if_w[x][y+4] == 0 && if_w[x][y+5] == 0 &&
                if_w[x][y+6] == 0 && if_w[x][y+7] == 1 )
                W_weight[m][n] += 300;
            //12020001
            if( if_w[x][y] == 1 && if_w[x][y+1] == 2 && if_w[x][y+2] == 0 && if_w[x][y+3] == 2 && if_w[x][y+4] == 0 && if_w[x][y+5] == 0 &&
                if_w[x][y+6] == 0 && if_w[x][y+7] == 1 )
                W_weight[m][n] += 300;
            //12002001
            if( if_w[x][y] == 1 && if_w[x][y+1] == 2 && if_w[x][y+2] == 0 && if_w[x][y+3] == 0 && if_w[x][y+4] == 2 && if_w[x][y+5] == 0 &&
                if_w[x][y+6] == 0 && if_w[x][y+7] == 1 )
                W_weight[m][n] += 300;
            //12000201
            if( if_w[x][y] == 1 && if_w[x][y+1] == 2 && if_w[x][y+2] == 0 && if_w[x][y+3] == 0 && if_w[x][y+4] == 0 && if_w[x][y+5] == 2 &&
                if_w[x][y+6] == 0 && if_w[x][y+7] == 1 )
                W_weight[m][n] += 300;
            //12000021
            if( if_w[x][y] == 1 && if_w[x][y+1] == 2 && if_w[x][y+2] == 0 && if_w[x][y+3] == 0 && if_w[x][y+4] == 0 && if_w[x][y+5] == 0 &&
                if_w[x][y+6] == 2 && if_w[x][y+7] == 1 )
                W_weight[m][n] += 300;
            //10220001
            if( if_w[x][y] == 1 && if_w[x][y+1] == 0 && if_w[x][y+2] == 2 && if_w[x][y+3] == 2 && if_w[x][y+4] == 0 && if_w[x][y+5] == 0 &&
                if_w[x][y+6] == 0 && if_w[x][y+7] == 1 )
                W_weight[m][n] += 300;
            //10202001
            if( if_w[x][y] == 1 && if_w[x][y+1] == 0 && if_w[x][y+2] == 2 && if_w[x][y+3] == 0 && if_w[x][y+4] == 2 && if_w[x][y+5] == 0 &&
                if_w[x][y+6] == 0 && if_w[x][y+7] == 1 )
                W_weight[m][n] += 300;
            //10200201
            if( if_w[x][y] == 1 && if_w[x][y+1] == 0 && if_w[x][y+2] == 2 && if_w[x][y+3] == 0 && if_w[x][y+4] == 0 && if_w[x][y+5] == 2 &&
                if_w[x][y+6] == 0 && if_w[x][y+7] == 1 )
                W_weight[m][n] += 300;
            //10200021
            if( if_w[x][y] == 1 && if_w[x][y+1] == 0 && if_w[x][y+2] == 2 && if_w[x][y+3] == 0 && if_w[x][y+4] == 0 && if_w[x][y+5] == 0 &&
                if_w[x][y+6] == 2 && if_w[x][y+7] == 1 )
                W_weight[m][n] += 300;
            //10022001
            if( if_w[x][y] == 1 && if_w[x][y+1] == 0 && if_w[x][y+2] == 0 && if_w[x][y+3] == 2 && if_w[x][y+4] == 2 && if_w[x][y+5] == 0 &&
                if_w[x][y+6] == 0 && if_w[x][y+7] == 1 )
                W_weight[m][n] += 300;
            //10020201
            if( if_w[x][y] == 1 && if_w[x][y+1] == 0 && if_w[x][y+2] == 0 && if_w[x][y+3] == 2 && if_w[x][y+4] == 0 && if_w[x][y+5] == 2 &&
                if_w[x][y+6] == 0 && if_w[x][y+7] == 1 )
                W_weight[m][n] += 300;
            //10020021
            if( if_w[x][y] == 1 && if_w[x][y+1] == 0 && if_w[x][y+2] == 0 && if_w[x][y+3] == 2 && if_w[x][y+4] == 0 && if_w[x][y+5] == 0 &&
                if_w[x][y+6] == 2 && if_w[x][y+7] == 1 )
                W_weight[m][n] += 300;
            //10002201
            if( if_w[x][y] == 1 && if_w[x][y+1] == 0 && if_w[x][y+2] == 0 && if_w[x][y+3] == 0 && if_w[x][y+4] == 2 && if_w[x][y+5] == 2 &&
                if_w[x][y+6] == 0 && if_w[x][y+7] == 1 )
                W_weight[m][n] += 300;
            //10002021
            if( if_w[x][y] == 1 && if_w[x][y+1] == 0 && if_w[x][y+2] == 0 && if_w[x][y+3] == 2 && if_w[x][y+4] == 0 && if_w[x][y+5] == 2 &&
                if_w[x][y+6] == 0 && if_w[x][y+7] == 1 )
                W_weight[m][n] += 300;
            //10000221
            if( if_w[x][y] == 1 && if_w[x][y+1] == 0 && if_w[x][y+2] == 0 && if_w[x][y+3] == 0 && if_w[x][y+4] == 0 && if_w[x][y+5] == 2 &&
                if_w[x][y+6] == 2 && if_w[x][y+7] == 1 )
                W_weight[m][n] += 300;
              }
          }
          if_w[m][n] = 0;
      }
    }
}

void AI::W_AI_3_Horizontal_check()
{
    for(int m=0 ; m<19 ; m++)
    {
      for(int n=0 ; n<19 ; n++)
      {
          if( if_w[m][n] == 0 )
          {
          if_w[m][n] = 2;
          }
          else if( if_w[m][n] == 1 || if_w[m][n] == 2 )
          {
              continue;
          }

          for(int x=0; x<19; x++)
          {
              for(int y=0; y<19; y++)
              {
            //000222000
            if( if_w[x][y-1] == 0 && if_w[x][y] == 0 && if_w[x][y+1] == 2 && if_w[x][y+2] == 2 && if_w[x][y+3] == 2&& if_w[x][y+4]==0 &&
                if_w[x][y+5] == 0 )
                W_weight[m][n] += 5000;
            //00202200
            if( if_w[x][y-1] == 0 && if_w[x][y] == 0 && if_w[x][y+1] == 2 && if_w[x][y+2] == 0 && if_w[x][y+3] == 2 && if_w[x][y+4] == 2 &&
                if_w[x][y+5]==0 && if_w[x][y+6] == 0 )
                W_weight[m][n] += 3500;
            //00220200
            if( if_w[x][y-1] == 0 && if_w[x][y] == 0 && if_w[x][y+1] == 2 && if_w[x][y+2] == 2 && if_w[x][y+3] == 0 && if_w[x][y+4] == 2 &&
                if_w[x][y+5] == 0 && if_w[x][y+6] == 0 )
                W_weight[m][n] += 3500;
            //0200220
            if( if_w[x][y] == 0 && if_w[x][y+1] == 2 && if_w[x][y+2] == 0 && if_w[x][y+3] == 0 && if_w[x][y+4] == 2 && if_w[x][y+5] == 2
                &&if_w[x][y+6] ==0 )
                W_weight[m][n] += 3000;
            //0202020
            if( if_w[x][y] == 0 && if_w[x][y+1] == 2 && if_w[x][y+2] == 0 && if_w[x][y+3] == 2 && if_w[x][y+4] == 0 && if_w[x][y+5] == 2
                &&if_w[x][y+6]==0 )
                W_weight[m][n] += 3000;
            //0220020
            if( if_w[x][y] == 0 && if_w[x][y+1] == 2 && if_w[x][y+2] == 2 && if_w[x][y+3] == 0 && if_w[x][y+4] == 0 && if_w[x][y+5] == 2
                && if_w[x][y+6] ==0 )
                W_weight[m][n] += 3000;
            //여기까지 양쪽에 안 막힌, 흰 돌이 2개가 발견 될 때 경우의 수들

            //122200
            if( if_w[x][y] == 1 && if_w[x][y+1] == 2 && if_w[x][y+2] == 2 && if_w[x][y+3] == 2 && if_w[x][y+4] ==0 && if_w[x][y+5] == 0 )
                W_weight[m][n] += 1000;
            //1202200
            if( if_w[x][y] == 1 && if_w[x][y+1] == 2 && if_w[x][y+2] == 0 && if_w[x][y+3] == 2 && if_w[x][y+4] == 2 && if_w[x][y+5] ==0 &&
                if_w[x][y+6] == 0 )
                W_weight[m][n] += 1000;
            //1220200
            if( if_w[x][y] == 1 && if_w[x][y+1] == 2 && if_w[x][y+2] == 2 && if_w[x][y+3] == 0 && if_w[x][y+4] == 2 && if_w[x][y+5] == 0 &&
                if_w[x][y+6] == 0 )
                W_weight[m][n] += 1000;
            //1022200
            if( if_w[x][y] == 1 && if_w[x][y+1] == 0 && if_w[x][y+2] == 2 && if_w[x][y+3] == 2 && if_w[x][y+4] == 2 && if_w[x][y+5] ==0 &&
                if_w[x][y+6] == 0 )
                W_weight[m][n] += 1300;
            //1200220
            if( if_w[x][y] == 1 && if_w[x][y+1] == 2 && if_w[x][y+2] == 0 && if_w[x][y+3] == 0 && if_w[x][y+4] == 2 && if_w[x][y+5] == 2 &&
            if_w[x][y+6] ==0 )
                W_weight[m][n] += 1300;
            //1220020
            if( if_w[x][y] == 1 && if_w[x][y+1] == 2 && if_w[x][y+2] == 2 && if_w[x][y+3] == 0 && if_w[x][y+4] == 0 && if_w[x][y+5] == 2 &&
                if_w[x][y+6] == 0 )
                W_weight[m][n] += 1000;
            //1202020
            if( if_w[x][y] == 1 && if_w[x][y+1] == 2 && if_w[x][y+2] == 0 && if_w[x][y+3] == 2 && if_w[x][y+4] == 0 && if_w[x][y+5] == 2 &&
                if_w[x][y+6] ==0 )
                W_weight[m][n] += 1000;
            //1020220
            if( if_w[x][y] == 1 && if_w[x][y+1] == 0 && if_w[x][y+2] == 2 && if_w[x][y+3] == 0 && if_w[x][y+4] == 2 && if_w[x][y+5] == 2 &&
                if_w[x][y+6] == 0)
                W_weight[m][n] += 1300;

            //여기까지 왼쪽에 검은돌로 막힌 경우.
            //오른쪽에 검은돌로 막힌 경우는 이 대칭으로만 작성해주면됌

            //002221
            if( if_w[x][y-1] == 0 && if_w[x][y] == 0 && if_w[x][y+1] == 2 && if_w[x][y+2] == 2 && if_w[x][y+3] == 2 && if_w[x][y+4] == 1 )
                W_weight[m][n] += 1000;
            //0022021
            if( if_w[x][y-1] == 0 && if_w[x][y] == 0 && if_w[x][y+1] == 2 && if_w[x][y+2] == 2 && if_w[x][y+3] == 0 && if_w[x][y+4] == 2 &&
                if_w[x][y+5]==1 )
                W_weight[m][n] += 1000;
            //0020221
            if( if_w[x][y-1] == 0 && if_w[x][y] == 0 && if_w[x][y+1] == 2 && if_w[x][y+2] == 0 && if_w[x][y+3] == 2 && if_w[x][y+4] == 2 &&
                if_w[x][y+5] == 1 )
                W_weight[m][n] += 1000;
            //0022201
            if( if_w[x][y-1] == 0 && if_w[x][y] == 0 && if_w[x][y+1] == 2 && if_w[x][y+2] == 2 && if_w[x][y+3] == 2 && if_w[x][y+4] == 0 &&
                if_w[x][y+5] == 1 )
                W_weight[m][n] += 1300;
            //0220021
            if( if_w[x][y] == 0 && if_w[x][y+1] == 2 && if_w[x][y+2] == 2 && if_w[x][y+3] == 0 && if_w[x][y+4] == 0 && if_w[x][y+5] == 2 &&
                if_w[x][y+6] == 1 )
                W_weight[m][n] += 1300;
            //0200221
            if( if_w[x][y] == 0 && if_w[x][y+1] == 2 && if_w[x][y+2] == 0 && if_w[x][y+3] == 0 && if_w[x][y+4] == 2 && if_w[x][y+5] == 2 &&
                if_w[x][y+6] == 1 )
                W_weight[m][n] += 1000;
            //0202021
            if( if_w[x][y] == 0 && if_w[x][y+1] == 2 && if_w[x][y+2] == 0 && if_w[x][y+3] == 2 && if_w[x][y+4] == 0 && if_w[x][y+5] == 2 &&
                if_w[x][y+6] == 1 )
                W_weight[m][n] += 1000;
            //0220201
            if( if_w[x][y] == 0 && if_w[x][y+1] == 2 && if_w[x][y+2] == 2 && if_w[x][y+3] == 0 && if_w[x][y+4] == 2 && if_w[x][y+5] == 0 &&
                if_w[x][y+6] == 1 )
                W_weight[m][n] += 1300;

            //여기까지 한쪽이 막힌 경우.
            //그 다음은 양쪽이 막힌 경우. 양쪽이 막힌 경우는 안이 6칸일 경우만 따지자.

            //12220001
            if( if_w[x][y] == 1 && if_w[x][y+1] == 2 && if_w[x][y+2] == 2 && if_w[x][y+3] == 2 && if_w[x][y+4] == 0 && if_w[x][y+5] == 0 &&
                if_w[x][y+6] == 0 && if_w[x][y+7] == 1 )
                W_weight[m][n] += 300;
            //12022001
            if( if_w[x][y] == 1 && if_w[x][y+1] == 2 && if_w[x][y+2] == 0 && if_w[x][y+3] == 2 && if_w[x][y+4] == 2 && if_w[x][y+5] == 0 &&
                if_w[x][y+6] == 0 && if_w[x][y+7] == 1 )
                W_weight[m][n] += 300;
            //12002201
            if( if_w[x][y] == 1 && if_w[x][y+1] == 2 && if_w[x][y+2] == 0 && if_w[x][y+3] == 0 && if_w[x][y+4] == 2 && if_w[x][y+5] == 2 &&
                if_w[x][y+6] == 0 && if_w[x][y+7] == 1 )
                W_weight[m][n] += 300;
            //12000221
            if( if_w[x][y] == 1 && if_w[x][y+1] == 2 && if_w[x][y+2] == 0 && if_w[x][y+3] == 0 && if_w[x][y+4] == 0 && if_w[x][y+5] == 2 &&
                if_w[x][y+6] == 2 && if_w[x][y+7] == 1 )
                W_weight[m][n] += 300;
            //12202001
            if( if_w[x][y] == 1 && if_w[x][y+1] == 2 && if_w[x][y+2] == 2 && if_w[x][y+3] == 0 && if_w[x][y+4] == 2 && if_w[x][y+5] == 0 &&
                if_w[x][y+6] == 0 && if_w[x][y+7] == 1 )
                W_weight[m][n] += 300;
            //12200201
            if( if_w[x][y] == 1 && if_w[x][y+1] == 2 && if_w[x][y+2] == 2 && if_w[x][y+3] == 0 && if_w[x][y+4] == 0 && if_w[x][y+5] == 2 &&
                if_w[x][y+6] == 0 && if_w[x][y+7] == 1 )
                W_weight[m][n] += 300;
            //12200021
            if( if_w[x][y] == 1 && if_w[x][y+1] == 2 && if_w[x][y+2] == 2 && if_w[x][y+3] == 0 && if_w[x][y+4] == 0 && if_w[x][y+5] == 0 &&
                if_w[x][y+6] == 2 && if_w[x][y+7] == 1 )
                W_weight[m][n] += 300;
            //12002021
            if( if_w[x][y] == 1 && if_w[x][y+1] == 2 && if_w[x][y+2] == 0 && if_w[x][y+3] == 0 && if_w[x][y+4] == 2 && if_w[x][y+5] == 0 &&
                if_w[x][y+6] == 2 && if_w[x][y+7] == 1 )
                W_weight[m][n] += 300;
            //12020021
            if( if_w[x][y] == 1 && if_w[x][y+1] == 2 && if_w[x][y+2] == 0 && if_w[x][y+3] == 2 && if_w[x][y+4] == 0 && if_w[x][y+5] == 0 &&
                if_w[x][y+6] == 2 && if_w[x][y+7] == 1 )
                W_weight[m][n] += 300;
            //12020201
            if( if_w[x][y] == 1 && if_w[x][y+1] == 2 && if_w[x][y+2] == 0 && if_w[x][y+3] == 2 && if_w[x][y+4] == 0 && if_w[x][y+5] == 2 &&
                if_w[x][y+6] == 0 && if_w[x][y+7] == 1 )
                W_weight[m][n] += 300;
            //10222001
            if( if_w[x][y] == 1 && if_w[x][y+1] == 0 && if_w[x][y+2] == 2 && if_w[x][y+3] == 2 && if_w[x][y+4] == 2 && if_w[x][y+5] == 0 &&
                if_w[x][y+6] == 0 && if_w[x][y+7] == 1 )
                W_weight[m][n] += 300;
            //10202201
            if( if_w[x][y] == 1 && if_w[x][y+1] == 0 && if_w[x][y+2] == 2 && if_w[x][y+3] == 0 && if_w[x][y+4] == 2 && if_w[x][y+5] == 2 &&
                if_w[x][y+6] == 0 && if_w[x][y+7] == 1 )
                W_weight[m][n] += 300;
            //10200221
            if( if_w[x][y] == 1 && if_w[x][y+1] == 0 && if_w[x][y+2] == 2 && if_w[x][y+3] == 0 && if_w[x][y+4] == 0 && if_w[x][y+5] == 2 &&
                if_w[x][y+6] == 2 && if_w[x][y+7] == 1 )
                W_weight[m][n] += 300;
            //10220201
            if( if_w[x][y] == 1 && if_w[x][y+1] == 0 && if_w[x][y+2] == 2 && if_w[x][y+3] == 2 && if_w[x][y+4] == 0 && if_w[x][y+5] == 2 &&
                if_w[x][y+6] == 0 && if_w[x][y+7] == 1 )
                W_weight[m][n] += 300;
            //10220021
            if( if_w[x][y] == 1 && if_w[x][y+1] == 0 && if_w[x][y+2] == 2 && if_w[x][y+3] == 2 && if_w[x][y+4] == 0 && if_w[x][y+5] == 0 &&
                if_w[x][y+6] == 2 && if_w[x][y+7] == 1 )
                W_weight[m][n] += 300;
            //10022021
            if( if_w[x][y] == 1 && if_w[x][y+1] == 0 && if_w[x][y+2] == 0 && if_w[x][y+3] == 2 && if_w[x][y+4] == 2 && if_w[x][y+5] == 0 &&
                if_w[x][y+6] == 2 && if_w[x][y+7] == 1 )
                W_weight[m][n] += 300;
            //10022201
            if( if_w[x][y] == 1 && if_w[x][y+1] == 0 && if_w[x][y+2] == 0 && if_w[x][y+3] == 2 && if_w[x][y+4] == 2 && if_w[x][y+5] == 2 &&
                if_w[x][y+6] == 0 && if_w[x][y+7] == 1 )
                W_weight[m][n] += 300;
            //10020221
            if( if_w[x][y] == 1 && if_w[x][y+1] == 0 && if_w[x][y+2] == 0 && if_w[x][y+3] == 2 && if_w[x][y+4] == 0 && if_w[x][y+5] == 2 &&
                if_w[x][y+6] == 2 && if_w[x][y+7] == 1 )
                W_weight[m][n] += 300;
            //10002221
            if( if_w[x][y] == 1 && if_w[x][y+1] == 0 && if_w[x][y+2] == 0 && if_w[x][y+3] == 0 && if_w[x][y+4] == 0 && if_w[x][y+5] == 2 &&
                if_w[x][y+6] == 2 && if_w[x][y+7] == 1 )
                W_weight[m][n] += 300;
            //10202021
            if( if_w[x][y] == 1 && if_w[x][y+1] == 0 && if_w[x][y+2] == 2 && if_w[x][y+3] == 0 && if_w[x][y+4] == 2 && if_w[x][y+5] == 0 &&
                if_w[x][y+6] == 2 && if_w[x][y+7] == 1 )
                W_weight[m][n] += 300;
                }
          }
          if_w[m][n] = 0;
      }
    }
}

void AI::W_AI_4_Horizontal_check()
{
    for(int m=0 ; m<19 ; m++)
    {
      for(int n=0 ; n<19 ; n++)
      {
          if( if_w[m][n] == 0 )
          {
          if_w[m][n] = 2;
          }
          else if( if_w[m][n] == 1 || if_w[m][n] == 2 )
          {
              continue;
          }

          for(int x=0; x<19; x++)
          {
              for(int y=0; y<19; y++)
              {
   /*4개 -> 안막혔을 때*/
         //00222200
         if( if_w[x][y-1] == 0 && if_w[x][y]== 0 && if_w[x][y+1]== 2 && if_w[x][y+2]== 2 &&if_w[x][y+3] == 2 && if_w[x][y+4] == 2 &&
             if_w[x][y+5] == 0 )
            W_weight[m][n] += 10000;
         //002022200
         if( if_w[x][y-1] == 0 && if_w[x][y]==0 && if_w[x][y+1]==2 && if_w[x][y+2]==0 && if_w[x][y+3] == 2 && if_w[x][y+4] ==2 &&
             if_w[x][y+5]==2 &&if_w[x][y+6] ==0 && if_w[x][y+7] == 0 )
            W_weight[m][n] += 7000;
         //002220200
         if( if_w[x][y-1] == 0 && if_w[x][y]== 0 && if_w[x][y+1]== 2 && if_w[x][y+2]== 2 && if_w[x][y+3] == 2 && if_w[x][y+4] == 0 &&
             if_w[x][y+5] ==2 &&if_w[x][y+6] == 0 && if_w[x][y+7] == 0 )
            W_weight[m][n] += 7000;
         //002202200
         if( if_w[x][y-1] == 0 && if_w[x][y]== 0 && if_w[x][y+1]== 2 && if_w[x][y+2]== 2 && if_w[x][y+3] == 0 && if_w[x][y+4] == 2 &&
             if_w[x][y+5] == 2 && if_w[x][y+6] == 0 && if_w[x][y+7] == 0 )
            W_weight[m][n] += 7000;
         //02220020
         if( if_w[x][y]==0 && if_w[x][y+1]==2 && if_w[x][y+2]==2 && if_w[x][y+3] == 2 && if_w[x][y+4] ==0 && if_w[x][y+5] ==0 &&
             if_w[x][y+6] ==2 && if_w[x][y+7] ==0 )
            W_weight[m][n] += 5000;
         //02002220
         if( if_w[x][y] == 0 && if_w[x][y+1] == 2 && if_w[x][y+2] == 0 && if_w[x][y+3] == 0 && if_w[x][y+4] == 2 && if_w[x][y+5] == 2 &&
             if_w[x][y+6] == 2 && if_w[x][y+7] == 0 )
            W_weight[m][n] += 5000;
         //02202020
         if( if_w[x][y] == 0 && if_w[x][y+1] == 2 && if_w[x][y+2] == 2 && if_w[x][y+3] == 0 && if_w[x][y+4] == 2 && if_w[x][y+5] == 2 &&
             if_w[x][y+6] == 2 && if_w[x][y+7] == 0 )
            W_weight[m][n] += 4000;
         //02020220
         if(if_w[x][y] == 0 && if_w[x][y+1] == 2 && if_w[x][y+2] == 0 && if_w[x][y+3] == 2 && if_w[x][y+4] == 0 && if_w[x][y+5] == 2 &&
             if_w[x][y+6] == 2 && if_w[x][y+7] == 0 )
            W_weight[m][n] += 4000;

         //4개 한쪽 막혔을 때
         //122220
         if(if_w[x][y]==1 && if_w[x][y+1]==2 && if_w[x][y+2]==2 && if_w[x][y+3] == 2 && if_w[x][y+4] ==2 && if_w[x][y+5] ==0)
            W_weight[m][n] += 4000;
         //1202220
         if(if_w[x][y]==1 && if_w[x][y+1]==2 && if_w[x][y+2]==0 && if_w[x][y+3] == 2 && if_w[x][y+4] ==2 && if_w[x][y+5] ==2 &&if_w[x][y+6] ==0)
            W_weight[m][n] += 3500;
         //1220220
         if(if_w[x][y]==1 && if_w[x][y+1]==2 && if_w[x][y+2]==2 && if_w[x][y+3] ==0 && if_w[x][y+4] ==2 && if_w[x][y+5] ==2 &&if_w[x][y+6] ==0)
            W_weight[m][n] += 3500;
         //1222020
         if(if_w[x][y]==1 && if_w[x][y+1]==2 && if_w[x][y+2]==2 && if_w[x][y+3] == 2 && if_w[x][y+4] ==0 && if_w[x][y+5] ==2 &&if_w[x][y+6] ==0)
            W_weight[m][n] += 3500;
         //1022220
         if(if_w[x][y]==1 && if_w[x][y+1]==0 && if_w[x][y+2]==2 && if_w[x][y+3] == 2 && if_w[x][y+4] ==2 && if_w[x][y+5] ==2 &&if_w[x][y+6] ==0)
            W_weight[m][n] += 3500;
         //12002220
         if(if_w[x][y]==1 && if_w[x][y+1]==2 && if_w[x][y+2]==0 && if_w[x][y+3] == 0 && if_w[x][y+4] ==2 && if_w[x][y+5] ==2 &&if_w[x][y+6] ==2 &&
             if_w[x][y+7]==0)
            W_weight[m][n] += 3500;
         //12020220
         if(if_w[x][y]==1 && if_w[x][y+1]==2 && if_w[x][y+2]==0 && if_w[x][y+3] == 2 && if_w[x][y+4] ==0 && if_w[x][y+5] ==2 &&if_w[x][y+6] ==2 &&
             if_w[x][y+7]==0)
            W_weight[m][n] += 3500;
         //12022020
         if(if_w[x][y]==1 && if_w[x][y+1]==2 && if_w[x][y+2]==0 && if_w[x][y+3] == 2 && if_w[x][y+4] ==2 && if_w[x][y+5] ==0 &&if_w[x][y+6] ==2 &&
             if_w[x][y+7]==0)
            W_weight[m][n] += 3500;
         //12200220
         if(if_w[x][y]==1 && if_w[x][y+1]==2 && if_w[x][y+2]==2 && if_w[x][y+3] == 0 && if_w[x][y+4] ==0 && if_w[x][y+5] ==2 &&if_w[x][y+6] ==2 &&
             if_w[x][y+7]==0 )
            W_weight[m][n] += 3500;
         //12202020
         if(if_w[x][y]==1 && if_w[x][y+1]==2 && if_w[x][y+2]==2 && if_w[x][y+3] == 0 && if_w[x][y+4] ==2 && if_w[x][y+5] ==0 &&if_w[x][y+6] ==2 &&
             if_w[x][y+7]==0)
            W_weight[m][n] += 3500;
         //12220020
         if(if_w[x][y]==1 && if_w[x][y+1]==2 && if_w[x][y+2]==2 && if_w[x][y+3] == 2 && if_w[x][y+4] ==0 && if_w[x][y+5] ==0 &&if_w[x][y+6] ==2 &&
             if_w[x][y+7]==0)
            W_weight[m][n] += 3500;
         //10220220
         if(if_w[x][y]==1 && if_w[x][y+1]==0 && if_w[x][y+2]==2 && if_w[x][y+3] == 2 && if_w[x][y+4] ==0 && if_w[x][y+5] ==2 &&if_w[x][y+6] ==2 &&
             if_w[x][y+7]==0)
            W_weight[m][n] += 3500;
         //10222020
         if(if_w[x][y]==1 && if_w[x][y+1]==0 && if_w[x][y+2]==2 && if_w[x][y+3] == 2 && if_w[x][y+4] ==2 && if_w[x][y+5] ==0 &&if_w[x][y+6] ==2 &&
             if_w[x][y+7]==0)
            W_weight[m][n] += 3500;
         //10202220
         if(if_w[x][y]==1 && if_w[x][y+1]==0 && if_w[x][y+2]==2 && if_w[x][y+3] == 0 && if_w[x][y+4] ==2 && if_w[x][y+5] ==2 &&if_w[x][y+6] ==2 &&
             if_w[x][y+7]==0)
            W_weight[m][n] += 3500;


         //4개 한쪽 막혔을 때 reverse
         //022221
         if(if_w[x][y]==0 && if_w[x][y+1]==2 && if_w[x][y+2]==2 && if_w[x][y+3] == 2 && if_w[x][y+4] ==2 && if_w[x][y+5] ==1)
            W_weight[m][n] += 3500;
         //0222021
         if(if_w[x][y]==0 && if_w[x][y+1]==2 && if_w[x][y+2]==2 && if_w[x][y+3] == 2 && if_w[x][y+4] ==0 && if_w[x][y+5] ==2 &&if_w[x][y+6] ==1)
            W_weight[m][n] += 3500;
         //0220221
         if(if_w[x][y]==0 && if_w[x][y+1]==2 && if_w[x][y+2]==2 && if_w[x][y+3] ==0 && if_w[x][y+4] ==2 && if_w[x][y+5] ==2 &&if_w[x][y+6] ==1)
            W_weight[m][n] += 3500;
         //0202221
         if(if_w[x][y]==0 && if_w[x][y+1]==2 && if_w[x][y+2]==0 && if_w[x][y+3] == 2 && if_w[x][y+4] ==2 && if_w[x][y+5] ==2 &&if_w[x][y+6] ==1)
            W_weight[m][n] += 3500;
         //0222201
         if(if_w[x][y]==0 && if_w[x][y+1]==2 && if_w[x][y+2]==2 && if_w[x][y+3] == 2 && if_w[x][y+4] ==2 && if_w[x][y+5] ==0 &&if_w[x][y+6] ==1)
            W_weight[m][n] += 3500;
         //02220021
         if(if_w[x][y]==0 && if_w[x][y+1]==2 && if_w[x][y+2]==2 && if_w[x][y+3] == 2 && if_w[x][y+4] ==0 && if_w[x][y+5] ==0 &&if_w[x][y+6] ==2 &&
             if_w[x][y+7] ==1)
            W_weight[m][n] += 3500;
         //02202021
         if(if_w[x][y]==0 && if_w[x][y+1]==2 && if_w[x][y+2]==2 && if_w[x][y+3] == 0 && if_w[x][y+4] ==2 && if_w[x][y+5] ==0 &&if_w[x][y+6] ==2 &&
             if_w[x][y+7] ==1)
            W_weight[m][n] += 3500;
         //02022021
         if(if_w[x][y]==0 && if_w[x][y+1]==2 && if_w[x][y+2]==0 && if_w[x][y+3] == 2 && if_w[x][y+4] ==2 && if_w[x][y+5] ==0 &&if_w[x][y+6] ==2 &&
             if_w[x][y+7] ==1)
            W_weight[m][n] += 3500;
         //02200221
         if(if_w[x][y]==0 && if_w[x][y+1]==2 && if_w[x][y+2]==2 && if_w[x][y+3] == 0 && if_w[x][y+4] ==0 && if_w[x][y+5] ==2 &&if_w[x][y+6] ==2 &&
             if_w[x][y+7] ==1 )
            W_weight[m][n] += 3500;
         //02020221
         if(if_w[x][y]==0 && if_w[x][y+1]==2 && if_w[x][y+2]==0 && if_w[x][y+3] == 2 && if_w[x][y+4] ==0 && if_w[x][y+5] ==2 &&if_w[x][y+6] ==2 &&
             if_w[x][y+7] ==1)
            W_weight[m][n] += 3500;
         //02002221
         if(if_w[x][y]==0 && if_w[x][y+1]==2 && if_w[x][y+2]==0 && if_w[x][y+3] == 0 && if_w[x][y+4] ==2 && if_w[x][y+5] ==2 &&if_w[x][y+6] ==2 &&
             if_w[x][y+7] ==1)
            W_weight[m][n] += 3500;
         //02202201
         if(if_w[x][y]==0 && if_w[x][y+1]==2 && if_w[x][y+2]==2 && if_w[x][y+3] == 0 && if_w[x][y+4] ==2 && if_w[x][y+5] ==2 &&if_w[x][y+6] ==0 &&
             if_w[x][y+7] ==1)
            W_weight[m][n] += 3500;
         //02022201
         if(if_w[x][y]==0 && if_w[x][y+1]==2 && if_w[x][y+2]==0 && if_w[x][y+3] == 2 && if_w[x][y+4] ==2 && if_w[x][y+5] ==2 &&if_w[x][y+6] ==0 &&
             if_w[x][y+7] ==1)
            W_weight[m][n] += 3500;
         //02220201
         if(if_w[x][y]==0 && if_w[x][y+1]==2 && if_w[x][y+2]==2 && if_w[x][y+3] == 2 && if_w[x][y+4] ==0 && if_w[x][y+5] ==2 &&if_w[x][y+6] ==0 &&
             if_w[x][y+7] ==1)
            W_weight[m][n] += 3500;



         //양쪽 다 막혔을 때

         //12022021
         if(if_w[x][y]==1 && if_w[x][y+1]==2 && if_w[x][y+2]==0 && if_w[x][y+3] == 2 && if_w[x][y+4] ==2 && if_w[x][y+5] ==0 &&if_w[x][y+6] ==2 &&if_w[x][y+7] ==1 )
            W_weight[m][n] += 1000;
         //12200221
         if(if_w[x][y]==1 && if_w[x][y+1]==2 && if_w[x][y+2]==2 && if_w[x][y+3] == 0 && if_w[x][y+4] ==0 && if_w[x][y+5] ==2 &&if_w[x][y+6] ==2 &&if_w[x][y+7] ==1 )
            W_weight[m][n] += 1000;
         //12220021
         if(if_w[x][y]==1 && if_w[x][y+1]==2 && if_w[x][y+2]==2 && if_w[x][y+3] == 2 && if_w[x][y+4] ==0 && if_w[x][y+5] ==0 &&if_w[x][y+6] ==2 &&if_w[x][y+7] ==1)
            W_weight[m][n] += 1000;
         //12002221
         if(if_w[x][y]==1 && if_w[x][y+1]==2 && if_w[x][y+2]==0 && if_w[x][y+3] == 0 && if_w[x][y+4] ==2 && if_w[x][y+5] ==2 &&if_w[x][y+6] ==2 &&if_w[x][y+7] ==1 )
            W_weight[m][n] += 1000;
         //12202021
         if(if_w[x][y]==1 && if_w[x][y+1]==2 && if_w[x][y+2]==2 && if_w[x][y+3] == 0 && if_w[x][y+4] ==2 && if_w[x][y+5] ==2 &&if_w[x][y+6] ==2 &&if_w[x][y+7] ==1)
            W_weight[m][n] += 1000;
         //12020221
         if(if_w[x][y]==1 && if_w[x][y+1]==2 && if_w[x][y+2]==0 && if_w[x][y+3] == 2 && if_w[x][y+4] ==0 && if_w[x][y+5] ==2 &&if_w[x][y+6] ==2 &&if_w[x][y+7] ==1 )
            W_weight[m][n] += 1000;
         //10222201
       if(if_w[x][y]==1 && if_w[x][y+1]==0 && if_w[x][y+2]==2 && if_w[x][y+3] == 2 && if_w[x][y+4] ==2 && if_w[x][y+5] ==2 &&if_w[x][y+6] ==0 &&if_w[x][y+7] ==1 )
            W_weight[m][n] += 1000;
       //10222021
       if(if_w[x][y]==1 && if_w[x][y+1]==0 && if_w[x][y+2]==2 && if_w[x][y+3] == 2 && if_w[x][y+4] ==2 && if_w[x][y+5] ==0 &&if_w[x][y+6] ==2 &&if_w[x][y+7] ==1 )
            W_weight[m][n] += 1000;
       //10220221
       if(if_w[x][y]==1 && if_w[x][y+1]==0 && if_w[x][y+2]==2 && if_w[x][y+3] == 2 && if_w[x][y+4] ==0 && if_w[x][y+5] ==2 &&if_w[x][y+6] ==2 &&if_w[x][y+7] ==1 )
            W_weight[m][n] += 1000;
        //10202221
       if(if_w[x][y]==1 && if_w[x][y+1]==0 && if_w[x][y+2]==2 && if_w[x][y+3] == 0 && if_w[x][y+4] ==2 && if_w[x][y+5] ==2 &&if_w[x][y+6] ==2 &&if_w[x][y+7] ==1 )
            W_weight[m][n] += 1000;
       //10022221
       if(if_w[x][y]==1 && if_w[x][y+1]==0 && if_w[x][y+2]==0 && if_w[x][y+3] == 2 && if_w[x][y+4] ==2 && if_w[x][y+5] ==2 &&if_w[x][y+6] ==2 &&if_w[x][y+7] ==1 )
            W_weight[m][n] += 1000;
       //12022201
       if(if_w[x][y]==1 && if_w[x][y+1]==2 && if_w[x][y+2]==0 && if_w[x][y+3] == 2 && if_w[x][y+4] ==2 && if_w[x][y+5] ==2 &&if_w[x][y+6] ==0 &&if_w[x][y+7] ==1 )
            W_weight[m][n] += 1000;
       //12202201
       if(if_w[x][y]==1 && if_w[x][y+1]==2 && if_w[x][y+2]==2 && if_w[x][y+3] == 0 && if_w[x][y+4] ==2 && if_w[x][y+5] ==2 &&if_w[x][y+6] ==0 &&if_w[x][y+7] ==1 )
            W_weight[m][n] += 1000;
       //12220201
       if(if_w[x][y]==1 && if_w[x][y+1]==2 && if_w[x][y+2]==2 && if_w[x][y+3] == 2 && if_w[x][y+4] ==0 && if_w[x][y+5] ==2 &&if_w[x][y+6] ==0 &&if_w[x][y+7] ==1 )
            W_weight[m][n] += 1000;
       //12222001
       if(if_w[x][y]==1 && if_w[x][y+1]==2 && if_w[x][y+2]==2 && if_w[x][y+3] == 2 && if_w[x][y+4] ==2 && if_w[x][y+5] ==0 &&if_w[x][y+6] ==0 &&if_w[x][y+7] ==1 )
            W_weight[m][n] += 1000;
         }
     }
         if_w[m][n] = 0;
         }
     }

}




void AI::W_AI_2_Vertical_check()
{
    for(int m=0 ; m<19 ; m++)
        {
          for(int n=0 ; n<19 ; n++)
          {
              if( if_w[m][n] == 0 )
              {
              if_w[m][n] = 2;
              }
              else if( if_w[m][n] == 1 || if_w[m][n] == 2 )
              {
                  continue;
              }

              for(int x=0; x<19; x++)
              {
                  for(int y=0; y<19; y++)
                  {
                //00022000
                if( if_w[x-2][y] == 0 && if_w[x-1][y] == 0 && if_w[x][y] == 0 && if_w[x+1][y] == 2 && if_w[x+2][y] == 2 &&
                    if_w[x+3][y] == 0 && if_w[x+4][y] == 0 && if_w[x+5][y] == 0 )
                    W_weight[m][n] += 2000;
                //0020200
                if( if_w[x-1][y] == 0 && if_w[x][y] == 0 && if_w[x+1][y] == 2 && if_w[x+2][y] == 0 && if_w[x+3][y] == 2 && if_w[x+4][y] == 0 &&
                    if_w[x+5][y] == 0 )
                    W_weight[m][n] += 1500;
                //020020
                if( if_w[x][y] == 0 && if_w[x+1][y] == 2 && if_w[x+2][y] == 0 && if_w[x+3][y] == 0 && if_w[x+4][y] == 2 && if_w[x+5][y] == 0 )
                    W_weight[m][n] += 1000;
                //여기까지 양쪽에 안 막힌, 흰 돌이 2개가 발견 될 때 경우의 수들

                //122000
                if( if_w[x][y] == 1 && if_w[x+1][y] == 2 && if_w[x+2][y] == 2 && if_w[x+3][y] == 0 && if_w[x+4][y] == 0 && if_w[x+5][y] == 0 )
                    W_weight[m][n] += 500;
                //120200
                if( if_w[x][y] == 1 && if_w[x+1][y] == 2 && if_w[x+2][y] == 0 && if_w[x+3][y] == 2 && if_w[x+4][y] == 0 && if_w[x+5][y] == 0 )
                    W_weight[m][n] += 500;
                //120020
                if( if_w[x][y] == 1 && if_w[x+1][y] == 2 && if_w[x+2][y] == 0 && if_w[x+3][y] == 0 && if_w[x+4][y] == 2 && if_w[x+5][y] == 0 )
                    W_weight[m][n] += 500;
                //102200
                if( if_w[x][y] == 1 && if_w[x+1][y] == 0 && if_w[x+2][y] == 2 && if_w[x+3][y] == 2 && if_w[x+4][y] == 0 && if_w[x+5][y] == 0 )
                    W_weight[m][n] += 800;
                //102020
                if( if_w[x][y] == 1 && if_w[x+1][y] == 0 && if_w[x+2][y] == 2 && if_w[x+3][y] == 0 && if_w[x+4][y] == 2 && if_w[x+5][y] == 0 )
                    W_weight[m][n] += 800;
                //여기까지 왼쪽에 검은돌로 막힌 경우.
                //오른쪽에 검은돌로 막힌 경우는 이 대칭으로만 작성해주면됌

                //000221
                if( if_w[x-2][y] == 0 && if_w[x-1][y] == 0 && if_w[x][y] == 0 && if_w[x+1][y] == 2 && if_w[x+2][y] == 2 && if_w[x+3][y] == 1 )
                    W_weight[m][n] += 500;
                //002021
                if( if_w[x-1][y] == 0 && if_w[x][y] == 0 && if_w[x+1][y] == 2 && if_w[x+2][y] == 0 && if_w[x+3][y] == 2 && if_w[x+4][y] == 1 )
                    W_weight[m][n] += 500;
                //020021
                if( if_w[x][y] == 0 && if_w[x+1][y] == 2 && if_w[x+2][y] == 0 && if_w[x+3][y] == 0 && if_w[x+4][y] == 2 && if_w[x+5][y] == 1 )
                    W_weight[m][n] += 500;
                //002201
                if( if_w[x-1][y] == 0 && if_w[x][y] == 0 && if_w[x+1][y] == 2 && if_w[x+2][y] == 2 && if_w[x+3][y] == 0 && if_w[x+4][y] == 1 )
                    W_weight[m][n] += 800;
                //020201
                if( if_w[x][y] == 0 && if_w[x+1][y] == 2 && if_w[x+2][y] == 0 && if_w[x+3][y] == 2 && if_w[x+4][y] == 0 && if_w[x+5][y] == 1 )
                    W_weight[m][n] += 800;
                //여기까지 한쪽이 막힌 경우.
                //그 다음은 양쪽이 막힌 경우. 양쪽이 막힌 경우는 안이 6칸일 경우만 따지자.

                //12200001
                if( if_w[x][y] == 1 && if_w[x+1][y] == 2 && if_w[x+2][y] == 2 && if_w[x+3][y] == 0 && if_w[x+4][y] == 0 && if_w[x+5][y] == 0 &&
                    if_w[x+6][y] == 0 && if_w[x+7][y] == 1 )
                    W_weight[m][n] += 300;
                //12020001
                if( if_w[x][y] == 1 && if_w[x+1][y] == 2 && if_w[x+2][y] == 0 && if_w[x+3][y] == 2 && if_w[x+4][y] == 0 && if_w[x+5][y] == 0 &&
                    if_w[x+6][y] == 0 && if_w[x+7][y] == 1 )
                    W_weight[m][n] += 300;
                //12002001
                if( if_w[x][y] == 1 && if_w[x+1][y] == 2 && if_w[x+2][y] == 0 && if_w[x+3][y] == 0 && if_w[x+4][y] == 2 && if_w[x+5][y] == 0 &&
                    if_w[x+6][y] == 0 && if_w[x+7][y] == 1 )
                    W_weight[m][n] += 300;
                //12000201
                if( if_w[x][y] == 1 && if_w[x+1][y] == 2 && if_w[x+2][y] == 0 && if_w[x+3][y] == 0 && if_w[x+4][y] == 0 && if_w[x+5][y] == 2 &&
                    if_w[x+6][y] == 0 && if_w[x+7][y] == 1 )
                    W_weight[m][n] += 300;
                //12000021
                if( if_w[x][y] == 1 && if_w[x+1][y] == 2 && if_w[x+2][y] == 0 && if_w[x+3][y] == 0 && if_w[x+4][y] == 0 && if_w[x+5][y] == 0 &&
                    if_w[x+6][y] == 2 && if_w[x+7][y] == 1 )
                    W_weight[m][n] += 300;
                //10220001
                if( if_w[x][y] == 1 && if_w[x+1][y] == 0 && if_w[x+2][y] == 2 && if_w[x+3][y] == 2 && if_w[x+4][y] == 0 && if_w[x+5][y] == 0 &&
                    if_w[x+6][y] == 0 && if_w[x+7][y] == 1 )
                    W_weight[m][n] += 300;
                //10202001
                if( if_w[x][y] == 1 && if_w[x+1][y] == 0 && if_w[x+2][y] == 2 && if_w[x+3][y] == 0 && if_w[x+4][y] == 2 && if_w[x+5][y] == 0 &&
                    if_w[x+6][y] == 0 && if_w[x+7][y] == 1 )
                    W_weight[m][n] += 300;
                //10200201
                if( if_w[x][y] == 1 && if_w[x+1][y] == 0 && if_w[x+2][y] == 2 && if_w[x+3][y] == 0 && if_w[x+4][y] == 0 && if_w[x+5][y] == 2 &&
                    if_w[x+6][y] == 0 && if_w[x+7][y] == 1 )
                    W_weight[m][n] += 300;
                //10200021
                if( if_w[x][y] == 1 && if_w[x+1][y] == 0 && if_w[x+2][y] == 2 && if_w[x+3][y] == 0 && if_w[x+4][y] == 0 && if_w[x+5][y] == 0 &&
                    if_w[x+6][y] == 2 && if_w[x+7][y] == 1 )
                    W_weight[m][n] += 300;
                //10022001
                if( if_w[x][y] == 1 && if_w[x+1][y] == 0 && if_w[x+2][y] == 0 && if_w[x+3][y] == 2 && if_w[x+4][y] == 2 && if_w[x+5][y] == 0 &&
                    if_w[x+6][y] == 0 && if_w[x+7][y] == 1 )
                    W_weight[m][n] += 300;
                //10020201
                if( if_w[x][y] == 1 && if_w[x+1][y] == 0 && if_w[x+2][y] == 0 && if_w[x+3][y] == 2 && if_w[x+4][y] == 0 && if_w[x+5][y] == 2 &&
                    if_w[x+6][y] == 0 && if_w[x+7][y] == 1 )
                    W_weight[m][n] += 300;
                //10020021
                if( if_w[x][y] == 1 && if_w[x+1][y] == 0 && if_w[x+2][y] == 0 && if_w[x+3][y] == 2 && if_w[x+4][y] == 0 && if_w[x+5][y] == 0 &&
                    if_w[x+6][y] == 2 && if_w[x+7][y] == 1 )
                    W_weight[m][n] += 300;
                //10002201
                if( if_w[x][y] == 1 && if_w[x+1][y] == 0 && if_w[x+2][y] == 0 && if_w[x+3][y] == 0 && if_w[x+4][y] == 2 && if_w[x+5][y] == 2 &&
                    if_w[x+6][y] == 0 && if_w[x+7][y] == 1 )
                    W_weight[m][n] += 300;
                //10002021
                if( if_w[x][y] == 1 && if_w[x+1][y] == 0 && if_w[x+2][y] == 0 && if_w[x+3][y] == 2 && if_w[x+4][y] == 0 && if_w[x+5][y] == 2 &&
                    if_w[x+6][y] == 0 && if_w[x+7][y] == 1 )
                    W_weight[m][n] += 300;
                //10000221
                if( if_w[x][y] == 1 && if_w[x+1][y] == 0 && if_w[x+2][y] == 0 && if_w[x+3][y] == 0 && if_w[x+4][y] == 0 && if_w[x+5][y] == 2 &&
                    if_w[x+6][y] == 2 && if_w[x+7][y] == 1 )
                    W_weight[m][n] += 300;
                  }
              }
              if_w[m][n] = 0;
          }
        }
}

void AI::W_AI_3_Vertical_check()
{
    for(int m=0 ; m<19 ; m++)
    {
      for(int n=0 ; n<19 ; n++)
      {
          if( if_w[m][n] == 0 )
          {
          if_w[m][n] = 2;
          }
          else if( if_w[m][n] == 1 || if_w[m][n] == 2 )
          {
              continue;
          }

          for(int x=0; x<19; x++)
          {
              for(int y=0; y<19; y++)
              {
            //000222000
            if( if_w[x-1][y] == 0 && if_w[x][y] == 0 && if_w[x+1][y] == 2 && if_w[x+2][y] == 2 && if_w[x+3][y] == 2&& if_w[x+4][y]==0 &&
                if_w[x+5][y] == 0 )
                W_weight[m][n] += 5000;
            //00202200
            if( if_w[x-1][y] == 0 && if_w[x][y] == 0 && if_w[x+1][y] == 2 && if_w[x+2][y] == 0 && if_w[x+3][y] == 2 && if_w[x+4][y] == 2 &&
                if_w[x+5][y]==0 && if_w[x+6][y] == 0 )
                W_weight[m][n] += 3500;
            //00220200
            if( if_w[x-1][y] == 0 && if_w[x][y] == 0 && if_w[x+1][y] == 2 && if_w[x+2][y] == 2 && if_w[x+3][y] == 0 && if_w[x+4][y] == 2 &&
                if_w[x+5][y] == 0 && if_w[x+6][y] == 0 )
                W_weight[m][n] += 3500;
            //0200220
            if( if_w[x][y] == 0 && if_w[x+1][y] == 2 && if_w[x+2][y] == 0 && if_w[x+3][y] == 0 && if_w[x+4][y] == 2 && if_w[x+5][y] == 2
                &&if_w[x+6][y] ==0 )
                W_weight[m][n] += 3000;
            //0202020
            if( if_w[x][y] == 0 && if_w[x+1][y] == 2 && if_w[x+2][y] == 0 && if_w[x+3][y] == 2 && if_w[x+4][y] == 0 && if_w[x+5][y] == 2
                &&if_w[x+6][y]==0 )
                W_weight[m][n] += 3000;
            //0220020
            if( if_w[x][y] == 0 && if_w[x+1][y] == 2 && if_w[x+2][y] == 2 && if_w[x+3][y] == 0 && if_w[x+4][y] == 0 && if_w[x+5][y] == 2
                && if_w[x+6][y] ==0 )
                W_weight[m][n] += 3000;
            //여기까지 양쪽에 안 막힌, 흰 돌이 2개가 발견 될 때 경우의 수들

            //122200
            if( if_w[x][y] == 1 && if_w[x+1][y] == 2 && if_w[x+2][y] == 2 && if_w[x+3][y] == 2 && if_w[x+4][y] ==0 && if_w[x+5][y] == 0 )
                W_weight[m][n] += 1000;
            //1202200
            if( if_w[x][y] == 1 && if_w[x+1][y] == 2 && if_w[x+2][y] == 0 && if_w[x+3][y] == 2 && if_w[x+4][y] == 2 && if_w[x+5][y] ==0 &&
                if_w[x][y] == 0 )
                W_weight[m][n] += 1000;
            //1220200
            if( if_w[x][y] == 1 && if_w[x+1][y] == 2 && if_w[x+2][y] == 2 && if_w[x+3][y] == 0 && if_w[x+4][y] == 2 && if_w[x+5][y] == 0 &&
                if_w[x+6][y] == 0 )
                W_weight[m][n] += 1000;
            //1022200
            if( if_w[x][y] == 1 && if_w[x+1][y] == 0 && if_w[x+2][y] == 2 && if_w[x+3][y] == 2 && if_w[x+4][y] == 2 && if_w[x+5][y] ==0 &&
                if_w[x+6][y] == 0 )
                W_weight[m][n] += 1300;
            //1200220
            if( if_w[x][y] == 1 && if_w[x+1][y] == 2 && if_w[x+2][y] == 0 && if_w[x+3][y] == 0 && if_w[x+4][y] == 2 && if_w[x+5][y] == 2 &&
            if_w[x+6][y] ==0 )
                W_weight[m][n] += 1300;
            //1220020
            if( if_w[x][y] == 1 && if_w[x][y] == 2 && if_w[x][y] == 2 && if_w[x][y] == 0 && if_w[x][y] == 0 && if_w[x][y] == 2 &&
                if_w[x][y] == 0 )
                W_weight[m][n] += 1000;
            //1202020
            if( if_w[x][y] == 1 && if_w[x+1][y] == 2 && if_w[x+2][y] == 0 && if_w[x+3][y] == 2 && if_w[x+4][y] == 0 && if_w[x+5][y] == 2 &&
                if_w[x+6][y] ==0 )
                W_weight[m][n] += 1000;
            //1020220
            if( if_w[x][y] == 1 && if_w[x+1][y] == 0 && if_w[x+2][y] == 2 && if_w[x+3][y] == 0 && if_w[x+4][y] == 2 && if_w[x+5][y] == 2 &&
                if_w[x+6][y] == 0)
                W_weight[m][n] += 1300;

            //여기까지 왼쪽에 검은돌로 막힌 경우.
            //오른쪽에 검은돌로 막힌 경우는 이 대칭으로만 작성해주면됌

            //002221
            if( if_w[x-1][y] == 0 && if_w[x][y] == 0 && if_w[x+1][y] == 2 && if_w[x+2][y] == 2 && if_w[x+3][y] == 2 && if_w[x+4][y] == 1 )
                W_weight[m][n] += 1000;
            //0022021
            if( if_w[x-1][y] == 0 && if_w[x][y] == 0 && if_w[x+1][y] == 2 && if_w[x+2][y] == 2 && if_w[x+3][y] == 0 && if_w[x+4][y] == 2 &&
                if_w[x+5][y]==1 )
                W_weight[m][n] += 1000;
            //0020221
            if( if_w[x-1][y] == 0 && if_w[x][y] == 0 && if_w[x+1][y] == 2 && if_w[x+2][y] == 0 && if_w[x+3][y] == 2 && if_w[x+4][y] == 2 &&
                if_w[x+5][y] == 1 )
                W_weight[m][n] += 1000;
            //0022201
            if( if_w[x-1][y] == 0 && if_w[x][y] == 0 && if_w[x+1][y] == 2 && if_w[x+2][y] == 2 && if_w[x+3][y] == 2 && if_w[x+4][y] == 0 &&
                if_w[x+5][y] == 1 )
                W_weight[m][n] += 1300;
            //0220021
            if( if_w[x][y] == 0 && if_w[x][y] == 2 && if_w[x][y] == 2 && if_w[x][y] == 0 && if_w[x][y] == 0 && if_w[x][y] == 2 &&
                if_w[x][y] == 1 )
                W_weight[m][n] += 1300;
            //0200221
            if( if_w[x][y] == 0 && if_w[x+1][y] == 2 && if_w[x+2][y] == 0 && if_w[x+3][y] == 0 && if_w[x+4][y] == 2 && if_w[x+5][y] == 2 &&
                if_w[x+6][y] == 1 )
                W_weight[m][n] += 1000;
            //0202021
            if( if_w[x][y] == 0 && if_w[x+1][y] == 2 && if_w[x+2][y] == 0 && if_w[x+3][y] == 2 && if_w[x+4][y] == 0 && if_w[x+5][y] == 2 &&
                if_w[x+6][y] == 1 )
                W_weight[m][n] += 1000;
            //0220201
            if( if_w[x][y] == 0 && if_w[x+1][y] == 2 && if_w[x+2][y] == 2 && if_w[x+3][y] == 0 && if_w[x+4][y] == 2 && if_w[x+5][y] == 0 &&
                if_w[x+6][y] == 1 )
                W_weight[m][n] += 1300;

            //여기까지 한쪽이 막힌 경우.
            //그 다음은 양쪽이 막힌 경우. 양쪽이 막힌 경우는 안이 6칸일 경우만 따지자.

            //12220001
            if( if_w[x][y] == 1 && if_w[x+1][y] == 2 && if_w[x+2][y] == 2 && if_w[x+3][y] == 2 && if_w[x+4][y] == 0 && if_w[x+5][y] == 0 &&
                if_w[x+6][y] == 0 && if_w[x+7][y] == 1 )
                W_weight[m][n] += 300;
            //12022001
            if( if_w[x][y] == 1 && if_w[x+1][y] == 2 && if_w[x+2][y] == 0 && if_w[x+3][y] == 2 && if_w[x+4][y] == 2 && if_w[x+5][y] == 0 &&
                if_w[x+6][y] == 0 && if_w[x+7][y] == 1 )
                W_weight[m][n] += 300;
            //12002201
            if( if_w[x][y] == 1 && if_w[x+1][y] == 2 && if_w[x+2][y] == 0 && if_w[x+3][y] == 0 && if_w[x+4][y] == 2 && if_w[x+5][y] == 2 &&
                if_w[x+6][y] == 0 && if_w[x+7][y] == 1 )
                W_weight[m][n] += 300;
            //12000221
            if( if_w[x][y] == 1 && if_w[x+1][y] == 2 && if_w[x+2][y] == 0 && if_w[x+3][y] == 0 && if_w[x+4][y] == 0 && if_w[x+5][y] == 2 &&
                if_w[x+6][y] == 2 && if_w[x+7][y] == 1 )
                W_weight[m][n] += 300;
            //12202001
            if( if_w[x][y] == 1 && if_w[x+1][y] == 2 && if_w[x+2][y] == 2 && if_w[x+3][y] == 0 && if_w[x+4][y] == 2 && if_w[x+5][y] == 0 &&
                if_w[x+6][y] == 0 && if_w[x+7][y] == 1 )
                W_weight[m][n] += 300;
            //12200201
            if( if_w[x][y] == 1 && if_w[x+1][y] == 2 && if_w[x+2][y] == 2 && if_w[x+3][y] == 0 && if_w[x+4][y] == 0 && if_w[x+5][y] == 2 &&
                if_w[x+6][y] == 0 && if_w[x+7][y] == 1 )
                W_weight[m][n] += 300;
            //12200021
            if( if_w[x][y] == 1 && if_w[x+1][y] == 2 && if_w[x+2][y] == 2 && if_w[x+3][y] == 0 && if_w[x+4][y] == 0 && if_w[x+5][y] == 0 &&
                if_w[x+6][y] == 2 && if_w[x+7][y] == 1 )
                W_weight[m][n] += 300;
            //12002021
            if( if_w[x][y] == 1 && if_w[x+1][y] == 2 && if_w[x+2][y] == 0 && if_w[x+3][y] == 0 && if_w[x+4][y] == 2 && if_w[x+5][y] == 0 &&
                if_w[x+6][y] == 2 && if_w[x+7][y] == 1 )
                W_weight[m][n] += 300;
            //12020021
            if( if_w[x][y] == 1 && if_w[x+1][y] == 2 && if_w[x+2][y] == 0 && if_w[x+3][y] == 2 && if_w[x+4][y] == 0 && if_w[x+5][y] == 0 &&
                if_w[x+6][y] == 2 && if_w[x+7][y] == 1 )
                W_weight[m][n] += 300;
            //12020201
            if( if_w[x][y] == 1 && if_w[x+1][y] == 2 && if_w[x+2][y] == 0 && if_w[x+3][y] == 2 && if_w[x+4][y] == 0 && if_w[x+5][y] == 2 &&
                if_w[x+6][y] == 0 && if_w[x+7][y] == 1 )
                W_weight[m][n] += 300;
            //10222001
            if( if_w[x][y] == 1 && if_w[x+1][y] == 0 && if_w[x+2][y] == 2 && if_w[x+3][y] == 2 && if_w[x+4][y] == 2 && if_w[x+5][y] == 0 &&
                if_w[x+6][y] == 0 && if_w[x+7][y] == 1 )
                W_weight[m][n] += 300;
            //10202201
            if( if_w[x][y] == 1 && if_w[x+1][y] == 0 && if_w[x+2][y] == 2 && if_w[x+3][y] == 0 && if_w[x+4][y] == 2 && if_w[x+5][y] == 2 &&
                if_w[x+6][y] == 0 && if_w[x+7][y] == 1 )
                W_weight[m][n] += 300;
            //10200221
            if( if_w[x][y] == 1 && if_w[x+1][y] == 0 && if_w[x+2][y] == 2 && if_w[x+3][y] == 0 && if_w[x+4][y] == 0 && if_w[x+5][y] == 2 &&
                if_w[x+6][y] == 2 && if_w[x+7][y] == 1 )
                W_weight[m][n] += 300;
            //10220201
            if( if_w[x][y] == 1 && if_w[x+1][y] == 0 && if_w[x+2][y] == 2 && if_w[x+3][y] == 2 && if_w[x+4][y] == 0 && if_w[x+5][y] == 2 &&
                if_w[x+6][y] == 0 && if_w[x+7][y] == 1 )
                W_weight[m][n] += 300;
            //10220021
            if( if_w[x][y] == 1 && if_w[x+1][y] == 0 && if_w[x+2][y] == 2 && if_w[x+3][y] == 2 && if_w[x+4][y] == 0 && if_w[x+5][y] == 0 &&
                if_w[x+6][y] == 2 && if_w[x+7][y] == 1 )
                W_weight[m][n] += 300;
            //10022021
            if( if_w[x][y] == 1 && if_w[x+1][y] == 0 && if_w[x+2][y] == 0 && if_w[x+3][y] == 2 && if_w[x+4][y] == 2 && if_w[x+5][y] == 0 &&
                if_w[x+6][y] == 2 && if_w[x+7][y] == 1 )
                W_weight[m][n] += 300;
            //10022201
            if( if_w[x][y] == 1 && if_w[x+1][y] == 0 && if_w[x+2][y] == 0 && if_w[x+3][y] == 2 && if_w[x+4][y] == 2 && if_w[x+5][y] == 2 &&
                if_w[x+6][y] == 0 && if_w[x+7][y] == 1 )
                W_weight[m][n] += 300;
            //10020221
            if( if_w[x][y] == 1 && if_w[x+1][y] == 0 && if_w[x+2][y] == 0 && if_w[x+3][y] == 2 && if_w[x+4][y] == 0 && if_w[x+5][y] == 2 &&
                if_w[x+6][y] == 2 && if_w[x+7][y] == 1 )
                W_weight[m][n] += 300;
            //10002221
            if( if_w[x][y] == 1 && if_w[x+1][y] == 0 && if_w[x+2][y] == 0 && if_w[x+3][y] == 0 && if_w[x+4][y] == 0 && if_w[x+5][y] == 2 &&
                if_w[x+6][y] == 2 && if_w[x+7][y] == 1 )
                W_weight[m][n] += 300;
            //10202021
            if( if_w[x][y] == 1 && if_w[x+1][y] == 0 && if_w[x+2][y] == 2 && if_w[x+3][y] == 0 && if_w[x+4][y] == 2 && if_w[x+5][y] == 0 &&
                if_w[x+6][y] == 2 && if_w[x+7][y] == 1 )
                W_weight[m][n] += 300;
                }
          }
          if_w[m][n] = 0;
      }
    }

}

void AI::W_AI_4_Vertical_check()
{
    for(int m=0 ; m<19 ; m++)
    {
      for(int n=0 ; n<19 ; n++)
      {
          if( if_w[m][n] == 0 )
          {
          if_w[m][n] = 2;
          }
          else if( if_w[m][n] == 1 || if_w[m][n] == 2 )
          {
              continue;
          }

          for(int x=0; x<19; x++)
          {
              for(int y=0; y<19; y++)
              {
                    /*4개 -> 안막혔을 때*/
         //00222200
         if( if_w[x-1][y] == 0 && if_w[x][y]== 0 && if_w[x+1][y]== 2 && if_w[x+2][y]== 2 &&if_w[x+3][y] == 2 && if_w[x+4][y] == 2 &&
             if_w[x+5][y] == 0 )
            W_weight[m][n] += 10000;
         //002022200
         if( if_w[x-1][y] == 0 && if_w[x][y]==0 && if_w[x+1][y]==2 && if_w[x+2][y]==0 && if_w[x+3][y] == 2 && if_w[x+4][y] ==2 &&
             if_w[x+5][y]==2 &&if_w[x+6][y] ==0 && if_w[x+7][y] == 0 )
            W_weight[m][n] += 7000;
         //002220200
         if( if_w[x-1][y] == 0 && if_w[x][y]== 0 && if_w[x+1][y]== 2 && if_w[x+2][y]== 2 && if_w[x+3][y] == 2 && if_w[x+4][y] == 0 &&
             if_w[x+5][y] ==2 &&if_w[x+6][y] == 0 && if_w[x+7][y] == 0 )
            W_weight[m][n] += 7000;
         //002202200
         if( if_w[x-1][y] == 0 && if_w[x][y]== 0 && if_w[x+1][y]== 2 && if_w[x+2][y]== 2 && if_w[x+3][y] == 0 && if_w[x+4][y] == 2 &&
             if_w[x+5][y] == 2 && if_w[x+6][y] == 0 && if_w[x+7][y] == 0 )
            W_weight[m][n] += 7000;
         //02220020
         if( if_w[x][y]==0 && if_w[x+1][y]==2 && if_w[x+2][y]==2 && if_w[x+3][y] == 2 && if_w[x+4][y] ==0 && if_w[x+5][y] ==0 &&
             if_w[x+6][y] ==2 && if_w[x+7][y] ==0 )
            W_weight[m][n] += 5000;
         //02002220
         if( if_w[x][y] == 0 && if_w[x+1][y] == 2 && if_w[x+2][y] == 0 && if_w[x+3][y] == 0 && if_w[x+4][y] == 2 && if_w[x+5][y] == 2 &&
             if_w[x+6][y] == 2 && if_w[x+7][y] == 0 )
            W_weight[m][n] += 5000;
         //02202020
         if( if_w[x][y] == 0 && if_w[x+1][y] == 2 && if_w[x+2][y] == 2 && if_w[x+3][y] == 0 && if_w[x+4][y] == 2 && if_w[x+5][y] == 2 &&
             if_w[x+6][y] == 2 && if_w[x+7][y] == 0 )
            W_weight[m][n] += 4000;
         //02020220
         if(if_w[x][y] == 0 && if_w[x+1][y] == 2 && if_w[x+2][y] == 0 && if_w[x+3][y] == 2 && if_w[x+4][y] == 0 && if_w[x+5][y] == 2 &&
             if_w[x+6][y] == 2 && if_w[x+7][y] == 0 )
            W_weight[m][n] += 4000;

         //4개 한쪽 막혔을 때
         //122220
         if(if_w[x][y]==1 && if_w[x+1][y]==2 && if_w[x+2][y]==2 && if_w[x+3][y] == 2 && if_w[x+4][y] ==2 && if_w[x+5][y] ==0)
            W_weight[m][n] += 3500;
         //1202220
         if(if_w[x][y]==1 && if_w[x+1][y]==2 && if_w[x+2][y]==0 && if_w[x+3][y] == 2 && if_w[x+4][y] ==2 && if_w[x+5][y] ==2 &&if_w[x+6][y] ==0)
            W_weight[m][n] += 3500;
         //1220220
         if(if_w[x][y]==1 && if_w[x+1][y]==2 && if_w[x+2][y]==2 && if_w[x+3][y] ==0 && if_w[x+4][y] ==2 && if_w[x+5][y] ==2 &&if_w[x+6][y] ==0)
            W_weight[m][n] += 3500;
         //1222020
         if(if_w[x][y]==1 && if_w[x+1][y]==2 && if_w[x+2][y]==2 && if_w[x+3][y] == 2 && if_w[x+4][y] ==0 && if_w[x+5][y] ==2 &&if_w[x+6][y] ==0)
            W_weight[m][n] += 3500;
         //1022220
         if(if_w[x][y]==1 && if_w[x+1][y]==0 && if_w[x+2][y]==2 && if_w[x+3][y] == 2 && if_w[x+4][y] ==2 && if_w[x+5][y] ==2 &&if_w[x+6][y] ==0)
            W_weight[m][n] += 3500;
         //12002220
         if(if_w[x][y]==1 && if_w[x+1][y]==2 && if_w[x+2][y]==0 && if_w[x+3][y] == 0 && if_w[x+4][y] ==2 && if_w[x+5][y] ==2 &&if_w[x+6][y] ==2 &&
             if_w[x+7][y]==0)
            W_weight[m][n] += 3500;
         //12020220
         if(if_w[x][y]==1 && if_w[x+1][y]==2 && if_w[x+2][y]==0 && if_w[x+3][y] == 2 && if_w[x+4][y] ==0 && if_w[x+5][y] ==2 &&if_w[x+6][y] ==2 &&
             if_w[x+7][y]==0)
            W_weight[m][n] += 3500;
         //12022020
         if(if_w[x][y]==1 && if_w[x+1][y]==2 && if_w[x+2][y]==0 && if_w[x+3][y] == 2 && if_w[x+4][y] ==2 && if_w[x+5][y] ==0 &&if_w[x+6][y] ==2 &&
             if_w[x+7][y]==0)
            W_weight[m][n] += 3500;
         //12200220
         if(if_w[x][y]==1 && if_w[x+1][y]==2 && if_w[x+2][y]==2 && if_w[x+3][y] == 0 && if_w[x+4][y] ==0 && if_w[x+5][y] ==2 &&if_w[x+6][y] ==2 &&
             if_w[x+7][y]==0 )
            W_weight[m][n] += 3500;
         //12202020
         if(if_w[x][y]==1 && if_w[x+1][y]==2 && if_w[x+2][y]==2 && if_w[x+3][y] == 0 && if_w[x+4][y] ==2 && if_w[x+5][y] ==0 &&if_w[x+6][y] ==2 &&
             if_w[x+7][y]==0)
            W_weight[m][n] += 3500;
         //12220020
         if(if_w[x][y]==1 && if_w[x+1][y]==2 && if_w[x+2][y]==2 && if_w[x+3][y] == 2 && if_w[x+4][y] ==0 && if_w[x+5][y] ==0 &&if_w[x+6][y] ==2 &&
             if_w[x+7][y]==0)
            W_weight[m][n] += 3500;
         //10220220
         if(if_w[x][y]==1 && if_w[x+1][y]==0 && if_w[x+2][y]==2 && if_w[x+3][y] == 2 && if_w[x+4][y] ==0 && if_w[x+5][y] ==2 &&if_w[x+6][y] ==2 &&
             if_w[x+7][y]==0)
            W_weight[m][n] += 3500;
         //10222020
         if(if_w[x][y]==1 && if_w[x+1][y]==0 && if_w[x+2][y]==2 && if_w[x+3][y] == 2 && if_w[x+4][y] ==2 && if_w[x+5][y] ==0 &&if_w[x+6][y] ==2 &&
             if_w[x+7][y]==0)
            W_weight[m][n] += 3500;
         //10202220
         if(if_w[x][y]==1 && if_w[x+1][y]==0 && if_w[x+2][y]==2 && if_w[x+3][y] == 0 && if_w[x+4][y] ==2 && if_w[x+5][y] ==2 &&if_w[x+6][y] ==2 &&
             if_w[x+7][y]==0)
            W_weight[m][n] += 3500;


         //4개 한쪽 막혔을 때 reverse
         //022221
         if(if_w[x][y]==0 && if_w[x+1][y]==2 && if_w[x+2][y]==2 && if_w[x+3][y] == 2 && if_w[x+4][y] ==2 && if_w[x+5][y] ==1)
            W_weight[m][n] += 3500;
         //0222021
         if(if_w[x][y]==0 && if_w[x+1][y]==2 && if_w[x+2][y]==2 && if_w[x+3][y] == 2 && if_w[x+4][y] ==0 && if_w[x+5][y] ==2 &&if_w[x+6][y] ==1)
            W_weight[m][n] += 3500;
         //0220221
         if(if_w[x][y]==0 && if_w[x+1][y]==2 && if_w[x+2][y]==2 && if_w[x+3][y] ==0 && if_w[x+4][y] ==2 && if_w[x+5][y] ==2 &&if_w[x+6][y] ==1)
            W_weight[m][n] += 3500;
         //0202221
         if(if_w[x][y]==0 && if_w[x+1][y]==2 && if_w[x+2][y]==0 && if_w[x+3][y] == 2 && if_w[x+4][y] ==2 && if_w[x+5][y] ==2 &&if_w[x+6][y] ==1)
            W_weight[m][n] += 3500;
         //0222201
         if(if_w[x][y]==0 && if_w[x+1][y]==2 && if_w[x+2][y]==2 && if_w[x+3][y] == 2 && if_w[x+4][y] ==2 && if_w[x+5][y] ==0 &&if_w[x+6][y] ==1)
            W_weight[m][n] += 3500;
         //02220021
         if(if_w[x][y]==0 && if_w[x+1][y]==2 && if_w[x+2][y]==2 && if_w[x+3][y] == 2 && if_w[x+4][y] ==0 && if_w[x+5][y] ==0 &&if_w[x+6][y] ==2 &&
             if_w[x+7][y] ==1)
            W_weight[m][n] += 3500;
         //02202021
         if(if_w[x][y]==0 && if_w[x+1][y]==2 && if_w[x+2][y]==2 && if_w[x+3][y] == 0 && if_w[x+4][y] ==2 && if_w[x+5][y] ==0 &&if_w[x+6][y] ==2 &&
             if_w[x+7][y] ==1)
            W_weight[m][n] += 3500;
         //02022021
         if(if_w[x][y]==0 && if_w[x+1][y]==2 && if_w[x+2][y]==0 && if_w[x+3][y] == 2 && if_w[x+4][y] ==2 && if_w[x+5][y] ==0 &&if_w[x+6][y] ==2 &&
             if_w[x+7][y] ==1)
            W_weight[m][n] += 3500;
         //02200221
         if(if_w[x][y]==0 && if_w[x+1][y]==2 && if_w[x+2][y]==2 && if_w[x+3][y] == 0 && if_w[x+4][y] ==0 && if_w[x+5][y] ==2 &&if_w[x+6][y] ==2 &&
             if_w[x+7][y] ==1 )
            W_weight[m][n] += 3500;
         //02020221
         if(if_w[x][y]==0 && if_w[x+1][y]==2 && if_w[x+2][y]==0 && if_w[x+3][y] == 2 && if_w[x+4][y] ==0 && if_w[x+5][y] ==2 &&if_w[x+6][y] ==2 &&
             if_w[x+7][y] ==1)
            W_weight[m][n] += 3500;
         //02002221
         if(if_w[x][y]==0 && if_w[x+1][y]==2 && if_w[x+2][y]==0 && if_w[x+3][y] == 0 && if_w[x+4][y] ==2 && if_w[x+5][y] ==2 &&if_w[x+6][y] ==2 &&
             if_w[x+7][y] ==1)
            W_weight[m][n] += 3500;
         //02202201
         if(if_w[x][y]==0 && if_w[x+1][y]==2 && if_w[x+2][y]==2 && if_w[x+3][y] == 0 && if_w[x+4][y] ==2 && if_w[x+5][y] ==2 &&if_w[x+6][y] ==0 &&
             if_w[x+7][y] ==1)
            W_weight[m][n] += 3500;
         //02022201
         if(if_w[x][y]==0 && if_w[x+1][y]==2 && if_w[x+2][y]==0 && if_w[x+3][y] == 2 && if_w[x+4][y] ==2 && if_w[x+5][y] ==2 &&if_w[x+6][y] ==0 &&
             if_w[x+7][y] ==1)
            W_weight[m][n] += 3500;
         //02220201
         if(if_w[x][y]==0 && if_w[x+1][y]==2 && if_w[x+2][y]==2 && if_w[x+3][y] == 2 && if_w[x+4][y] ==0 && if_w[x+5][y] ==2 &&if_w[x+6][y] ==0 &&
             if_w[x+7][y] ==1)
            W_weight[m][n] += 3500;



         //양쪽 다 막혔을 때

         //12022021
         if(if_w[x][y]==1 && if_w[x+1][y]==2 && if_w[x+2][y]==0 && if_w[x+3][y] == 2 && if_w[x+4][y] ==2 && if_w[x+5][y] ==0 &&if_w[x+6][y] ==2 &&if_w[x+7][y] ==1 )
            W_weight[m][n] += 1000;
         //12200221
         if(if_w[x][y]==1 && if_w[x+1][y]==2 && if_w[x+2][y]==2 && if_w[x+3][y] == 0 && if_w[x+4][y] ==0 && if_w[x+5][y] ==2 &&if_w[x+6][y] ==2 &&if_w[x+7][y] ==1 )
            W_weight[m][n] += 1000;
         //12220021
         if(if_w[x][y]==1 && if_w[x+1][y]==2 && if_w[x+2][y]==2 && if_w[x+3][y] == 2 && if_w[x+4][y] ==0 && if_w[x+5][y] ==0 &&if_w[x+6][y] ==2 &&if_w[x+7][y] ==1)
            W_weight[m][n] += 1000;
         //12002221
         if(if_w[x][y]==1 && if_w[x+1][y]==2 && if_w[x+2][y]==0 && if_w[x+3][y] == 0 && if_w[x+4][y] ==2 && if_w[x+5][y] ==2 &&if_w[x+6][y] ==2 &&if_w[x+7][y] ==1 )
            W_weight[m][n] += 1000;
         //12202021
         if(if_w[x][y]==1 && if_w[x+1][y]==2 && if_w[x+2][y]==2 && if_w[x+3][y] == 0 && if_w[x+4][y] ==2 && if_w[x+5][y] ==2 &&if_w[x+6][y] ==2 &&if_w[x+7][y] ==1)
            W_weight[m][n] += 1000;
         //12020221
         if(if_w[x][y]==1 && if_w[x+1][y]==2 && if_w[x+2][y]==0 && if_w[x+3][y] == 2 && if_w[x+4][y] ==0 && if_w[x+5][y] ==2 &&if_w[x+6][y] ==2 &&if_w[x+7][y] ==1 )
            W_weight[m][n] += 1000;
         //10222201
       if(if_w[x][y]==1 && if_w[x+1][y]==0 && if_w[x+2][y]==2 && if_w[x+3][y] == 2 && if_w[x+4][y] ==2 && if_w[x+5][y] ==2 &&if_w[x+6][y] ==0 &&if_w[x+7][y] ==1 )
            W_weight[m][n] += 1000;
       //10222021
       if(if_w[x][y]==1 && if_w[x+1][y]==0 && if_w[x+2][y]==2 && if_w[x+3][y] == 2 && if_w[x+4][y] ==2 && if_w[x+5][y] ==0 &&if_w[x+6][y] ==2 &&if_w[x+7][y] ==1 )
            W_weight[m][n] += 1000;
       //10220221
       if(if_w[x][y]==1 && if_w[x+1][y]==0 && if_w[x+2][y]==2 && if_w[x+3][y] == 2 && if_w[x+4][y] ==0 && if_w[x+5][y] ==2 &&if_w[x+6][y] ==2 &&if_w[x+7][y] ==1 )
            W_weight[m][n] += 1000;
        //10202221
       if(if_w[x][y]==1 && if_w[x+1][y]==0 && if_w[x+2][y]==2 && if_w[x+3][y] == 0 && if_w[x+4][y] ==2 && if_w[x+5][y] ==2 &&if_w[x+6][y] ==2 &&if_w[x+7][y] ==1 )
            W_weight[m][n] += 1000;
       //10022221
       if(if_w[x][y]==1 && if_w[x+1][y]==0 && if_w[x+2][y]==0 && if_w[x+3][y] == 2 && if_w[x+4][y] ==2 && if_w[x+5][y] ==2 &&if_w[x+6][y] ==2 &&if_w[x+7][y] ==1 )
            W_weight[m][n] += 1000;
       //12022201
       if(if_w[x][y]==1 && if_w[x+1][y]==2 && if_w[x+2][y]==0 && if_w[x+3][y] == 2 && if_w[x+4][y] ==2 && if_w[x+5][y] ==2 &&if_w[x+6][y] ==0 &&if_w[x+7][y] ==1 )
            W_weight[m][n] += 1000;
       //12202201
       if(if_w[x][y]==1 && if_w[x+1][y]==2 && if_w[x+2][y]==2 && if_w[x+3][y] == 0 && if_w[x+4][y] ==2 && if_w[x+5][y] ==2 &&if_w[x+6][y] ==0 &&if_w[x+7][y] ==1 )
            W_weight[m][n] += 1000;
       //12220201
       if(if_w[x][y]==1 && if_w[x+1][y]==2 && if_w[x+2][y]==2 && if_w[x+3][y] == 2 && if_w[x+4][y] ==0 && if_w[x+5][y] ==2 &&if_w[x+6][y] ==0 &&if_w[x+7][y] ==1 )
            W_weight[m][n] += 1000;
       //12222001
       if(if_w[x][y]==1 && if_w[x+1][y]==2 && if_w[x+2][y]==2 && if_w[x+3][y] == 2 && if_w[x+4][y] ==2 && if_w[x+5][y] ==0 &&if_w[x+6][y] ==0 &&if_w[x+7][y] ==1 )
            W_weight[m][n] += 1000;
         }
         }
         if_w[m][n] = 0;
         }
         }


}

void AI::W_AI_2_Diagonal_check()
{
    for(int m=0 ; m<19 ; m++)
    {
      for(int n=0 ; n<19 ; n++)
      {
          if( if_w[m][n] == 0 )
          {
          if_w[m][n] = 2;
          }
          else if( if_w[m][n] == 1 || if_w[m][n] == 2 )
          {
              continue;
          }

          for(int x=0; x<19; x++)
          {
              for(int y=0; y<19; y++)
              {
            //00022000
            if( if_w[x-2][y-2] == 0 && if_w[x-1][y-1] == 0 && if_w[x][y] == 0 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 2 &&
                if_w[x+3][y+3] == 0 && if_w[x+4][y+4] == 0 && if_w[x+5][y+5] == 0 )
                W_weight[m][n] += 2000;
            //0020200
            if( if_w[x-1][y-1] == 0 && if_w[x][y] == 0 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 0 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] == 0 &&
                if_w[x+5][y+5] == 0 )
                W_weight[m][n] += 1500;
            //020020
            if( if_w[x][y] == 0 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 0 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] == 2 && if_w[x+5][y+5] == 0 )
                W_weight[m][n] += 1000;
            //여기까지 양쪽에 안 막힌, 흰 돌이 2개가 발견 될 때 경우의 수들

            //122000
            if( if_w[x][y] == 1 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 2 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] == 0 && if_w[x+5][y+5] == 0 )
                W_weight[m][n] += 500;
            //120200
            if( if_w[x][y] == 1 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 0 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] == 0 && if_w[x+5][y+5] == 0 )
                W_weight[m][n] += 500;
            //120020
            if( if_w[x][y] == 1 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 0 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] == 2 && if_w[x+5][y+5] == 0 )
                W_weight[m][n] += 500;
            //102200
            if( if_w[x][y] == 1 && if_w[x+1][y+1] == 0 && if_w[x+2][y+2] == 2 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] == 0 && if_w[x+5][y+5] == 0 )
                W_weight[m][n] += 800;
            //102020
            if( if_w[x][y] == 1 && if_w[x+1][y+1] == 0 && if_w[x+2][y+2] == 2 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] == 2 && if_w[x+5][y+5] == 0 )
                W_weight[m][n] += 800;
            //여기까지 왼쪽에 검은돌로 막힌 경우.
            //오른쪽에 검은돌로 막힌 경우는 이 대칭으로만 작성해주면됌

            //000221
            if( if_w[x-2][y-2] == 0 && if_w[x-1][y-1] == 0 && if_w[x][y] == 0 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 2 && if_w[x+3][y+3] == 1 )
                W_weight[m][n] += 500;
            //002021
            if( if_w[x-1][y-1] == 0 && if_w[x][y] == 0 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 0 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] == 1 )
                W_weight[m][n] += 500;
            //020021
            if( if_w[x][y] == 0 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 0 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] == 2 && if_w[x+5][y+5] == 1 )
                W_weight[m][n] += 500;
            //002201
            if( if_w[x-1][y-1] == 0 && if_w[x][y] == 0 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 2 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] == 1 )
                W_weight[m][n] += 800;
            //020201
            if( if_w[x][y] == 0 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 0 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] == 0 && if_w[x+5][y+5] == 1 )
                W_weight[m][n] += 800;
            //여기까지 한쪽이 막힌 경우.
            //그 다음은 양쪽이 막힌 경우. 양쪽이 막힌 경우는 안이 6칸일 경우만 따지자.

            //12200001
            if( if_w[x][y] == 1 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 2 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] == 0 && if_w[x+5][y+5] == 0 &&
                if_w[x+6][y+6] == 0 && if_w[x+7][y+7] == 1 )
                W_weight[m][n] += 300;
            //12020001
            if( if_w[x][y] == 1 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 0 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] == 0 && if_w[x+5][y+5] == 0 &&
                if_w[x+6][y+6] == 0 && if_w[x+7][y+7] == 1 )
                W_weight[m][n] += 300;
            //12002001
            if( if_w[x][y] == 1 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 0 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] == 2 && if_w[x+5][y+5] == 0 &&
                if_w[x+6][y+6] == 0 && if_w[x+7][y+7] == 1 )
                W_weight[m][n] += 300;
            //12000201
            if( if_w[x][y] == 1 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 0 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] == 0 && if_w[x+5][y+5] == 2 &&
                if_w[x+6][y+6] == 0 && if_w[x+7][y+7] == 1 )
                W_weight[m][n] += 300;
            //12000021
            if( if_w[x][y] == 1 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 0 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] == 0 && if_w[x+5][y+5] == 0 &&
                if_w[x+6][y+6] == 2 && if_w[x+7][y+7] == 1 )
                W_weight[m][n] += 300;
            //10220001
            if( if_w[x][y] == 1 && if_w[x+1][y+1] == 0 && if_w[x+2][y+2] == 2 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] == 0 && if_w[x+5][y+5] == 0 &&
                if_w[x+6][y+6] == 0 && if_w[x+7][y+7] == 1 )
                W_weight[m][n] += 300;
            //10202001
            if( if_w[x][y] == 1 && if_w[x+1][y+1] == 0 && if_w[x+2][y+2] == 2 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] == 2 && if_w[x+5][y+5] == 0 &&
                if_w[x+6][y+6] == 0 && if_w[x+7][y+7] == 1 )
                W_weight[m][n] += 300;
            //10200201
            if( if_w[x][y] == 1 && if_w[x+1][y+1] == 0 && if_w[x+2][y+2] == 2 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] == 0 && if_w[x+5][y+5] == 2 &&
                if_w[x+6][y+6] == 0 && if_w[x+7][y+7] == 1 )
                W_weight[m][n] += 300;
            //10200021
            if( if_w[x][y] == 1 && if_w[x+1][y+1] == 0 && if_w[x+2][y+2] == 2 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] == 0 && if_w[x+5][y+5] == 0 &&
                if_w[x+6][y+6] == 2 && if_w[x+7][y+7] == 1 )
                W_weight[m][n] += 300;
            //10022001
            if( if_w[x][y] == 1 && if_w[x+1][y+1] == 0 && if_w[x+2][y+2] == 0 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] == 2 && if_w[x+5][y+5] == 0 &&
                if_w[x+6][y+6] == 0 && if_w[x+7][y+7] == 1 )
                W_weight[m][n] += 300;
            //10020201
            if( if_w[x][y] == 1 && if_w[x+1][y+1] == 0 && if_w[x+2][y+2] == 0 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] == 0 && if_w[x+5][y+5] == 2 &&
                if_w[x+6][y+6] == 0 && if_w[x+7][y+7] == 1 )
                W_weight[m][n] += 300;
            //10020021
            if( if_w[x][y] == 1 && if_w[x+1][y+1] == 0 && if_w[x+2][y+2] == 0 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] == 0 && if_w[x+5][y+5] == 0 &&
                if_w[x+6][y+6] == 2 && if_w[x+7][y+7] == 1 )
                W_weight[m][n] += 300;
            //10002201
            if( if_w[x][y] == 1 && if_w[x+1][y+1] == 0 && if_w[x+2][y+2] == 0 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] == 2 && if_w[x+5][y+5] == 2 &&
                if_w[x+6][y+6] == 0 && if_w[x+7][y+7] == 1 )
                W_weight[m][n] += 300;
            //10002021
            if( if_w[x][y] == 1 && if_w[x+1][y+1] == 0 && if_w[x+2][y+2] == 0 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] == 0 && if_w[x+5][y+5] == 2 &&
                if_w[x+6][y+6] == 0 && if_w[x+7][y+7] == 1 )
                W_weight[m][n] += 300;
            //10000221
            if( if_w[x][y] == 1 && if_w[x+1][y+1] == 0 && if_w[x+2][y+2] == 0 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] == 0 && if_w[x+5][y+5] == 2 &&
                if_w[x+6][y+6] == 2 && if_w[x+7][y+7] == 1 )
                W_weight[m][n] += 300;
              }
          }
          if_w[m][n] = 0;
      }
    }
}

void AI::W_AI_3_Diagonal_check()
{
    for(int m=0 ; m<19 ; m++)
    {
      for(int n=0 ; n<19 ; n++)
      {
          if( if_w[m][n] == 0 )
          {
          if_w[m][n] = 2;
          }
          else if( if_w[m][n] == 1 || if_w[m][n] == 2 )
          {
              continue;
          }

          for(int x=0; x<19; x++)
          {
              for(int y=0; y<19; y++)
              {
            //000222000
            if( if_w[x-1][y-1] == 0 && if_w[x][y] == 0 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 2 && if_w[x+3][y+3] == 2&& if_w[x+4][y+4]==0 &&
                if_w[x+5][y+5] == 0 )
                W_weight[m][n] += 5000;
            //00202200
            if( if_w[x-1][y-1] == 0 && if_w[x][y] == 0 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 0 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] == 2 &&
                if_w[x+5][y+5]==0 && if_w[x+6][y+6] == 0 )
                W_weight[m][n] += 3500;
            //00220200
            if( if_w[x-1][y-1] == 0 && if_w[x][y] == 0 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 2 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] == 2 &&
                if_w[x+5][y+5] == 0 && if_w[x+6][y+6] == 0 )
                W_weight[m][n] += 3500;
            //0200220
            if( if_w[x][y] == 0 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 0 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] == 2 && if_w[x+5][y+5] == 2
                &&if_w[x+6][y+6] ==0 )
                W_weight[m][n] += 3000;
            //0202020
            if( if_w[x][y] == 0 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 0 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] == 0 && if_w[x+5][y+5] == 2
                &&if_w[x+6][y+6]==0 )
                W_weight[m][n] += 3000;
            //0220020
            if( if_w[x][y] == 0 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 2 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] == 0 && if_w[x+5][y+5] == 2
                && if_w[x+6][y+6] ==0 )
                W_weight[m][n] += 3000;
            //여기까지 양쪽에 안 막힌, 흰 돌이 2개가 발견 될 때 경우의 수들

            //122200
            if( if_w[x][y] == 1 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 2 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] ==0 && if_w[x+5][y+5] == 0 )
                W_weight[m][n] += 1000;
            //1202200
            if( if_w[x][y] == 1 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 0 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] == 2 && if_w[x+5][y+5] ==0 &&
                if_w[x][y+6] == 0 )
                W_weight[m][n] += 1000;
            //1220200
            if( if_w[x][y] == 1 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 2 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] == 2 && if_w[x+5][y+5] == 0 &&
                if_w[x+6][y+6] == 0 )
                W_weight[m][n] += 1000;
            //1022200
            if( if_w[x][y] == 1 && if_w[x+1][y+1] == 0 && if_w[x+2][y+2] == 2 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] == 2 && if_w[x+5][y+5] ==0 &&
                if_w[x+6][y+6] == 0 )
                W_weight[m][n] += 1300;
            //1200220
            if( if_w[x][y] == 1 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 0 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] == 2 && if_w[x+5][y+5] == 2 &&
            if_w[x+6][y+6] ==0 )
                W_weight[m][n] += 1300;
            //1220020
            if( if_w[x][y] == 1 && if_w[x][y+1] == 2 && if_w[x][y+2] == 2 && if_w[x][y+3] == 0 && if_w[x][y+4] == 0 && if_w[x][y+5] == 2 &&
                if_w[x][y+6] == 0 )
                W_weight[m][n] += 1000;
            //1202020
            if( if_w[x][y] == 1 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 0 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] == 0 && if_w[x+5][y+5] == 2 &&
                if_w[x+6][y+6] ==0 )
                W_weight[m][n] += 1000;
            //1020220
            if( if_w[x][y] == 1 && if_w[x+1][y+1] == 0 && if_w[x+2][y+2] == 2 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] == 2 && if_w[x+5][y+5] == 2 &&
                if_w[x+6][y+6] == 0)
                W_weight[m][n] += 1300;

            //여기까지 왼쪽에 검은돌로 막힌 경우.
            //오른쪽에 검은돌로 막힌 경우는 이 대칭으로만 작성해주면됌

            //002221
            if( if_w[x-1][y-1] == 0 && if_w[x][y] == 0 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 2 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] == 1 )
                W_weight[m][n] += 1000;
            //0022021
            if( if_w[x-1][y-1] == 0 && if_w[x][y] == 0 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 2 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] == 2 &&
                if_w[x+5][y+5]==1 )
                W_weight[m][n] += 1000;
            //0020221
            if( if_w[x-1][y-1] == 0 && if_w[x][y] == 0 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 0 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] == 2 &&
                if_w[x+5][y+5] == 1 )
                W_weight[m][n] += 1000;
            //0022201
            if( if_w[x-1][y-1] == 0 && if_w[x][y] == 0 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 2 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] == 0 &&
                if_w[x+5][y+5] == 1 )
                W_weight[m][n] += 1300;
            //0220021
            if( if_w[x][y] == 0 && if_w[x][y+1] == 2 && if_w[x][y+2] == 2 && if_w[x][y+3] == 0 && if_w[x][y+4] == 0 && if_w[x][y+5] == 2 &&
                if_w[x][y+6] == 1 )
                W_weight[m][n] += 1300;
            //0200221
            if( if_w[x][y] == 0 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 0 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] == 2 && if_w[x+5][y+5] == 2 &&
                if_w[x+6][y+6] == 1 )
                W_weight[m][n] += 1000;
            //0202021
            if( if_w[x][y] == 0 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 0 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] == 0 && if_w[x+5][y+5] == 2 &&
                if_w[x+6][y+6] == 1 )
                W_weight[m][n] += 1000;
            //0220201
            if( if_w[x][y] == 0 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 2 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] == 2 && if_w[x+5][y+5] == 0 &&
                if_w[x+6][y+6] == 1 )
                W_weight[m][n] += 1300;

            //여기까지 한쪽이 막힌 경우.
            //그 다음은 양쪽이 막힌 경우. 양쪽이 막힌 경우는 안이 6칸일 경우만 따지자.

            //12220001
            if( if_w[x][y] == 1 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 2 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] == 0 && if_w[x+5][y+5] == 0 &&
                if_w[x+6][y+6] == 0 && if_w[x+7][y+7] == 1 )
                W_weight[m][n] += 300;
            //12022001
            if( if_w[x][y] == 1 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 0 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] == 2 && if_w[x+5][y+5] == 0 &&
                if_w[x+6][y+6] == 0 && if_w[x+7][y+7] == 1 )
                W_weight[m][n] += 300;
            //12002201
            if( if_w[x][y] == 1 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 0 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] == 2 && if_w[x+5][y+5] == 2 &&
                if_w[x+6][y+6] == 0 && if_w[x+7][y+7] == 1 )
                W_weight[m][n] += 300;
            //12000221
            if( if_w[x][y] == 1 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 0 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] == 0 && if_w[x+5][y+5] == 2 &&
                if_w[x+6][y+6] == 2 && if_w[x+7][y+7] == 1 )
                W_weight[m][n] += 300;
            //12202001
            if( if_w[x][y] == 1 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 2 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] == 2 && if_w[x+5][y+5] == 0 &&
                if_w[x+6][y+6] == 0 && if_w[x+7][y+7] == 1 )
                W_weight[m][n] += 300;
            //12200201
            if( if_w[x][y] == 1 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 2 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] == 0 && if_w[x+5][y+5] == 2 &&
                if_w[x+6][y+6] == 0 && if_w[x+7][y+7] == 1 )
                W_weight[m][n] += 300;
            //12200021
            if( if_w[x][y] == 1 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 2 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] == 0 && if_w[x+5][y+5] == 0 &&
                if_w[x+6][y+6] == 2 && if_w[x+7][y+7] == 1 )
                W_weight[m][n] += 300;
            //12002021
            if( if_w[x][y] == 1 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 0 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] == 2 && if_w[x+5][y+5] == 0 &&
                if_w[x+6][y+6] == 2 && if_w[x+7][y+7] == 1 )
                W_weight[m][n] += 300;
            //12020021
            if( if_w[x][y] == 1 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 0 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] == 0 && if_w[x+5][y+5] == 0 &&
                if_w[x+6][y+6] == 2 && if_w[x+7][y+7] == 1 )
                W_weight[m][n] += 300;
            //12020201
            if( if_w[x][y] == 1 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 0 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] == 0 && if_w[x+5][y+5] == 2 &&
                if_w[x+6][y+6] == 0 && if_w[x+7][y+7] == 1 )
                W_weight[m][n] += 300;
            //10222001
            if( if_w[x][y] == 1 && if_w[x+1][y+1] == 0 && if_w[x+2][y+2] == 2 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] == 2 && if_w[x+5][y+5] == 0 &&
                if_w[x+6][y+6] == 0 && if_w[x+7][y+7] == 1 )
                W_weight[m][n] += 300;
            //10202201
            if( if_w[x][y] == 1 && if_w[x+1][y+1] == 0 && if_w[x+2][y+2] == 2 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] == 2 && if_w[x+5][y+5] == 2 &&
                if_w[x+6][y+6] == 0 && if_w[x+7][y+7] == 1 )
                W_weight[m][n] += 300;
            //10200221
            if( if_w[x][y] == 1 && if_w[x+1][y+1] == 0 && if_w[x+2][y+2] == 2 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] == 0 && if_w[x+5][y+5] == 2 &&
                if_w[x+6][y+6] == 2 && if_w[x+7][y+7] == 1 )
                W_weight[m][n] += 300;
            //10220201
            if( if_w[x][y] == 1 && if_w[x+1][y+1] == 0 && if_w[x+2][y+2] == 2 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] == 0 && if_w[x+5][y+5] == 2 &&
                if_w[x+6][y+6] == 0 && if_w[x+7][y+7] == 1 )
                W_weight[m][n] += 300;
            //10220021
            if( if_w[x][y] == 1 && if_w[x+1][y+1] == 0 && if_w[x+2][y+2] == 2 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] == 0 && if_w[x+5][y+5] == 0 &&
                if_w[x+6][y+6] == 2 && if_w[x+7][y+7] == 1 )
                W_weight[m][n] += 300;
            //10022021
            if( if_w[x][y] == 1 && if_w[x+1][y+1] == 0 && if_w[x+2][y+2] == 0 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] == 2 && if_w[x+5][y+5] == 0 &&
                if_w[x+6][y+6] == 2 && if_w[x+7][y+7] == 1 )
                W_weight[m][n] += 300;
            //10022201
            if( if_w[x][y] == 1 && if_w[x+1][y+1] == 0 && if_w[x+2][y+2] == 0 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] == 2 && if_w[x+5][y+5] == 2 &&
                if_w[x+6][y+6] == 0 && if_w[x+7][y+7] == 1 )
                W_weight[m][n] += 300;
            //10020221
            if( if_w[x][y] == 1 && if_w[x+1][y+1] == 0 && if_w[x+2][y+2] == 0 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] == 0 && if_w[x+5][y+5] == 2 &&
                if_w[x+6][y+6] == 2 && if_w[x+7][y+7] == 1 )
                W_weight[m][n] += 300;
            //10002221
            if( if_w[x][y] == 1 && if_w[x+1][y+1] == 0 && if_w[x+2][y+2] == 0 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] == 0 && if_w[x+5][y+5] == 2 &&
                if_w[x+6][y+6] == 2 && if_w[x+7][y+7] == 1 )
                W_weight[m][n] += 300;
            //10202021
            if( if_w[x][y] == 1 && if_w[x+1][y+1] == 0 && if_w[x+2][y+2] == 2 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] == 2 && if_w[x+5][y+5] == 0 &&
                if_w[x+6][y+6] == 2 && if_w[x+7][y+7] == 1 )
                W_weight[m][n] += 300;
                }
          }
          if_w[m][n] = 0;
      }
    }
}

void AI::W_AI_4_Diagonal_check()
{
    for(int m=0 ; m<19 ; m++)
    {
      for(int n=0 ; n<19 ; n++)
      {
          if( if_w[m][n] == 0 )
          {
          if_w[m][n] = 2;
          }
          else if( if_w[m][n] == 1 || if_w[m][n] == 2 )
          {
              continue;
          }

          for(int x=0; x<19; x++)
          {
              for(int y=0; y<19; y++)
              {

   /*4개 -> 안막혔을 때*/
         //00222200
         if( if_w[x-1][y-1] == 0 && if_w[x][y]== 0 && if_w[x+1][y+1]== 2 && if_w[x+2][y+2]== 2 &&if_w[x+3][y+3] == 2 && if_w[x+4][y+4] == 2 &&
             if_w[x+5][y+5] == 0 )
            W_weight[m][n] += 10000;
         //002022200
         if( if_w[x-1][y-1] == 0 && if_w[x][y]==0 && if_w[x+1][y+1]==2 && if_w[x+2][y+2]==0 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] ==2 &&
             if_w[x+5][y+5]==2 &&if_w[x+6][y+6] ==0 && if_w[x+7][y+7] == 0 )
            W_weight[m][n] += 7000;
         //002220200
         if( if_w[x-1][y-1] == 0 && if_w[x][y]== 0 && if_w[x+1][y+1]== 2 && if_w[x+2][y+2]== 2 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] == 0 &&
             if_w[x+5][y+5] ==2 &&if_w[x+6][y+6] == 0 && if_w[x+7][y+7] == 0 )
            W_weight[m][n] += 7000;
         //002202200
         if( if_w[x-1][y-1] == 0 && if_w[x][y]== 0 && if_w[x+1][y+1]== 2 && if_w[x+2][y+2]== 2 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] == 2 &&
             if_w[x+5][y+5] == 2 && if_w[x+6][y+6] == 0 && if_w[x+7][y+7] == 0 )
            W_weight[m][n] += 7000;
         //02220020
         if( if_w[x][y]==0 && if_w[x+1][y+1]==2 && if_w[x+2][y+2]==2 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] ==0 && if_w[x+5][y+5] ==0 &&
             if_w[x+6][y+6] ==2 && if_w[x+7][y+7] ==0 )
            W_weight[m][n] += 5000;
         //02002220
         if( if_w[x][y] == 0 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 0 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] == 2 && if_w[x+5][y+5] == 2 &&
             if_w[x+6][y+6] == 2 && if_w[x+7][y+7] == 0 )
            W_weight[m][n] += 5000;
         //02202020
         if( if_w[x][y] == 0 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 2 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] == 2 && if_w[x+5][y+5] == 2 &&
             if_w[x+6][y+6] == 2 && if_w[x+7][y+7] == 0 )
            W_weight[m][n] += 4000;
         //02020220
         if(if_w[x][y] == 0 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 0 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] == 0 && if_w[x+5][y+5] == 2 &&
             if_w[x+6][y+6] == 2 && if_w[x+7][y+7] == 0 )
            W_weight[m][n] += 4000;

         //4개 한쪽 막혔을 때
         //122220
         if(if_w[x][y]==1 && if_w[x+1][y+1]==2 && if_w[x+2][y+2]==2 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] ==2 && if_w[x+5][y+5] ==0)
            W_weight[m][n] += 3500;
         //1202220
         if(if_w[x][y]==1 && if_w[x+1][y+1]==2 && if_w[x+2][y+2]==0 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] ==2 && if_w[x+5][y+5] ==2 &&if_w[x+6][y+6] ==0)
            W_weight[m][n] += 3500;
         //1220220
         if(if_w[x][y]==1 && if_w[x+1][y+1]==2 && if_w[x+2][y+2]==2 && if_w[x+3][y+3] ==0 && if_w[x+4][y+4] ==2 && if_w[x+5][y+5] ==2 &&if_w[x+6][y+6] ==0)
            W_weight[m][n] += 3500;
         //1222020
         if(if_w[x][y]==1 && if_w[x+1][y+1]==2 && if_w[x+2][y+2]==2 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] ==0 && if_w[x+5][y+5] ==2 &&if_w[x+6][y+6] ==0)
            W_weight[m][n] += 3500;
         //1022220
         if(if_w[x][y]==1 && if_w[x+1][y+1]==0 && if_w[x+2][y+2]==2 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] ==2 && if_w[x+5][y+5] ==2 &&if_w[x+6][y+6] ==0)
            W_weight[m][n] += 3500;
         //12002220
         if(if_w[x][y]==1 && if_w[x+1][y+1]==2 && if_w[x+2][y+2]==0 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] ==2 && if_w[x+5][y+5] ==2 &&if_w[x+6][y+6] ==2 &&
             if_w[x+7][y+7]==0)
            W_weight[m][n] += 3500;
         //12020220
         if(if_w[x][y]==1 && if_w[x+1][y+1]==2 && if_w[x+2][y+2]==0 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] ==0 && if_w[x+5][y+5] ==2 &&if_w[x+6][y+6] ==2 &&
             if_w[x+7][y+7]==0)
            W_weight[m][n] += 3500;
         //12022020
         if(if_w[x][y]==1 && if_w[x+1][y+1]==2 && if_w[x+2][y+2]==0 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] ==2 && if_w[x+5][y+5] ==0 &&if_w[x+6][y+6] ==2 &&
             if_w[x+7][y+7]==0)
            W_weight[m][n] += 3500;
         //12200220
         if(if_w[x][y]==1 && if_w[x+1][y+1]==2 && if_w[x+2][y+2]==2 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] ==0 && if_w[x+5][y+5] ==2 &&if_w[x+6][y+6] ==2 &&
             if_w[x+7][y+7]==0 )
            W_weight[m][n] += 3500;
         //12202020
         if(if_w[x][y]==1 && if_w[x+1][y+1]==2 && if_w[x+2][y+2]==2 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] ==2 && if_w[x+5][y+5] ==0 &&if_w[x+6][y+6] ==2 &&
             if_w[x+7][y+7]==0)
            W_weight[m][n] += 3500;
         //12220020
         if(if_w[x][y]==1 && if_w[x+1][y+1]==2 && if_w[x+2][y+2]==2 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] ==0 && if_w[x+5][y+5] ==0 &&if_w[x+6][y+6] ==2 &&
             if_w[x+7][y+7]==0)
            W_weight[m][n] += 3500;
         //10220220
         if(if_w[x][y]==1 && if_w[x+1][y+1]==0 && if_w[x+2][y+2]==2 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] ==0 && if_w[x+5][y+5] ==2 &&if_w[x+6][y+6] ==2 &&
             if_w[x+7][y+7]==0)
            W_weight[m][n] += 3500;
         //10222020
         if(if_w[x][y]==1 && if_w[x+1][y+1]==0 && if_w[x+2][y+2]==2 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] ==2 && if_w[x+5][y+5] ==0 &&if_w[x+6][y+6] ==2 &&
             if_w[x+7][y+7]==0)
            W_weight[m][n] += 3500;
         //10202220
         if(if_w[x][y]==1 && if_w[x+1][y+1]==0 && if_w[x+2][y+2]==2 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] ==2 && if_w[x+5][y+5] ==2 &&if_w[x+6][y+6] ==2 &&
             if_w[x+7][y+7]==0)
            W_weight[m][n] += 3500;


         //4개 한쪽 막혔을 때 reverse
         //022221
         if(if_w[x][y]==0 && if_w[x+1][y+1]==2 && if_w[x+2][y+2]==2 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] ==2 && if_w[x+5][y+5] ==1)
            W_weight[m][n] += 3500;
         //0222021
         if(if_w[x][y]==0 && if_w[x+1][y+1]==2 && if_w[x+2][y+2]==2 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] ==0 && if_w[x+5][y+5] ==2 &&if_w[x+6][y+6] ==1)
            W_weight[m][n] += 3500;
         //0220221
         if(if_w[x][y]==0 && if_w[x+1][y+1]==2 && if_w[x+2][y+2]==2 && if_w[x+3][y+3] ==0 && if_w[x+4][y+4] ==2 && if_w[x+5][y+5] ==2 &&if_w[x+6][y+6] ==1)
            W_weight[m][n] += 3500;
         //0202221
         if(if_w[x][y]==0 && if_w[x+1][y+1]==2 && if_w[x+2][y+2]==0 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] ==2 && if_w[x+5][y+5] ==2 &&if_w[x+6][y+6] ==1)
            W_weight[m][n] += 3500;
         //0222201
         if(if_w[x][y]==0 && if_w[x+1][y+1]==2 && if_w[x+2][y+2]==2 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] ==2 && if_w[x+5][y+5] ==0 &&if_w[x+6][y+6] ==1)
            W_weight[m][n] += 3500;
         //02220021
         if(if_w[x][y]==0 && if_w[x+1][y+1]==2 && if_w[x+2][y+2]==2 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] ==0 && if_w[x+5][y+5] ==0 &&if_w[x+6][y+6] ==2 &&
             if_w[x+7][y+7] ==1)
            W_weight[m][n] += 3500;
         //02202021
         if(if_w[x][y]==0 && if_w[x+1][y+1]==2 && if_w[x+2][y+2]==2 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] ==2 && if_w[x+5][y+5] ==0 &&if_w[x+6][y+6] ==2 &&
             if_w[x+7][y+7] ==1)
            W_weight[m][n] += 3500;
         //02022021
         if(if_w[x][y]==0 && if_w[x+1][y+1]==2 && if_w[x+2][y+2]==0 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] ==2 && if_w[x+5][y+5] ==0 &&if_w[x+6][y+6] ==2 &&
             if_w[x+7][y+7] ==1)
            W_weight[m][n] += 3500;
         //02200221
         if(if_w[x][y]==0 && if_w[x+1][y+1]==2 && if_w[x+2][y+2]==2 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] ==0 && if_w[x+5][y+5] ==2 &&if_w[x+6][y+6] ==2 &&
             if_w[x+7][y+7] ==1 )
            W_weight[m][n] += 3500;
         //02020221
         if(if_w[x][y]==0 && if_w[x+1][y+1]==2 && if_w[x+2][y+2]==0 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] ==0 && if_w[x+5][y+5] ==2 &&if_w[x+6][y+6] ==2 &&
             if_w[x+7][y+7] ==1)
            W_weight[m][n] += 3500;
         //02002221
         if(if_w[x][y]==0 && if_w[x+1][y+1]==2 && if_w[x+2][y+2]==0 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] ==2 && if_w[x+5][y+5] ==2 &&if_w[x+6][y+6] ==2 &&
             if_w[x+7][y+7] ==1)
            W_weight[m][n] += 3500;
         //02202201
         if(if_w[x][y]==0 && if_w[x+1][y+1]==2 && if_w[x+2][y+2]==2 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] ==2 && if_w[x+5][y+5] ==2 &&if_w[x+6][y+6] ==0 &&
             if_w[x+7][y+7] ==1)
            W_weight[m][n] += 3500;
         //02022201
         if(if_w[x][y]==0 && if_w[x+1][y+1]==2 && if_w[x+2][y+2]==0 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] ==2 && if_w[x+5][y+5] ==2 &&if_w[x+6][y+6] ==0 &&
             if_w[x+7][y+7] ==1)
            W_weight[m][n] += 3500;
         //02220201
         if(if_w[x][y]==0 && if_w[x+1][y+1]==2 && if_w[x+2][y+2]==2 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] ==0 && if_w[x+5][y+5] ==2 &&if_w[x+6][y+6] ==0 &&
             if_w[x+7][y+7] ==1)
            W_weight[m][n] += 3500;



         //양쪽 다 막혔을 때

         //12022021
         if(if_w[x][y]==1 && if_w[x+1][y+1]==2 && if_w[x+2][y+2]==0 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] ==2 && if_w[x+5][y+5] ==0 &&if_w[x+6][y+6] ==2 &&if_w[x+7][y+7] ==1 )
            W_weight[m][n] += 1000;
         //12200221
         if(if_w[x][y]==1 && if_w[x+1][y+1]==2 && if_w[x+2][y+2]==2 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] ==0 && if_w[x+5][y+5] ==2 &&if_w[x+6][y+6] ==2 &&if_w[x+7][y+7] ==1 )
            W_weight[m][n] += 1000;
         //12220021
         if(if_w[x][y]==1 && if_w[x+1][y+1]==2 && if_w[x+2][y+2]==2 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] ==0 && if_w[x+5][y+5] ==0 &&if_w[x+6][y+6] ==2 &&if_w[x+7][y+7] ==1)
            W_weight[m][n] += 1000;
         //12002221
         if(if_w[x][y]==1 && if_w[x+1][y+1]==2 && if_w[x+2][y+2]==0 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] ==2 && if_w[x+5][y+5] ==2 &&if_w[x+6][y+6] ==2 &&if_w[x+7][y+7] ==1 )
            W_weight[m][n] += 1000;
         //12202021
         if(if_w[x][y]==1 && if_w[x+1][y+1]==2 && if_w[x+2][y+2]==2 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] ==2 && if_w[x+5][y+5] ==2 &&if_w[x+6][y+6] ==2 &&if_w[x+7][y+7] ==1)
            W_weight[m][n] += 1000;
         //12020221
         if(if_w[x][y]==1 && if_w[x+1][y+1]==2 && if_w[x+2][y+2]==0 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] ==0 && if_w[x+5][y+5] ==2 &&if_w[x+6][y+6] ==2 &&if_w[x+7][y+7] ==1 )
            W_weight[m][n] += 1000;
         //10222201
       if(if_w[x][y]==1 && if_w[x+1][y+1]==0 && if_w[x+2][y+2]==2 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] ==2 && if_w[x+5][y+5] ==2 &&if_w[x+6][y+6] ==0 &&if_w[x+7][y+7] ==1 )
            W_weight[m][n] += 1000;
       //10222021
       if(if_w[x][y]==1 && if_w[x+1][y+1]==0 && if_w[x+2][y+2]==2 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] ==2 && if_w[x+5][y+5] ==0 &&if_w[x+6][y+6] ==2 &&if_w[x+7][y+7] ==1 )
            W_weight[m][n] += 1000;
       //10220221
       if(if_w[x][y]==1 && if_w[x+1][y+1]==0 && if_w[x+2][y+2]==2 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] ==0 && if_w[x+5][y+5] ==2 &&if_w[x+6][y+6] ==2 &&if_w[x+7][y+7] ==1 )
            W_weight[m][n] += 1000;
        //10202221
       if(if_w[x][y]==1 && if_w[x+1][y+1]==0 && if_w[x+2][y+2]==2 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] ==2 && if_w[x+5][y+5] ==2 &&if_w[x+6][y+6] ==2 &&if_w[x+7][y+7] ==1 )
            W_weight[m][n] += 1000;
       //10022221
       if(if_w[x][y]==1 && if_w[x+1][y+1]==0 && if_w[x+2][y+2]==0 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] ==2 && if_w[x+5][y+5] ==2 &&if_w[x+6][y+6] ==2 &&if_w[x+7][y+7] ==1 )
            W_weight[m][n] += 1000;
       //12022201
       if(if_w[x][y]==1 && if_w[x+1][y+1]==2 && if_w[x+2][y+2]==0 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] ==2 && if_w[x+5][y+5] ==2 &&if_w[x+6][y+6] ==0 &&if_w[x+7][y+7] ==1 )
            W_weight[m][n] += 1000;
       //12202201
       if(if_w[x][y]==1 && if_w[x+1][y+1]==2 && if_w[x+2][y+2]==2 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] ==2 && if_w[x+5][y+5] ==2 &&if_w[x+6][y+6] ==0 &&if_w[x+7][y+7] ==1 )
            W_weight[m][n] += 1000;
       //12220201
       if(if_w[x][y]==1 && if_w[x+1][y+1]==2 && if_w[x+2][y+2]==2 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] ==0 && if_w[x+5][y+5] ==2 &&if_w[x+6][y+6] ==0 &&if_w[x+7][y+7] ==1 )
            W_weight[m][n] += 1000;
       //12222001
       if(if_w[x][y]==1 && if_w[x+1][y+1]==2 && if_w[x+2][y+2]==2 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] ==2 && if_w[x+5][y+5] ==0 &&if_w[x+6][y+6] ==0 &&if_w[x+7][y+7] ==1 )
            W_weight[m][n] += 1000;
         }
         }
         if_w[m][n] = 0;
         }
         }
}



void AI::W_AI_2_in_Diagonal_check()
{
    for(int m=0 ; m<19 ; m++)
    {
      for(int n=0 ; n<19 ; n++)
      {
          if( if_w[m][n] == 0 )
          {
          if_w[m][n] = 2;
          }
          else if( if_w[m][n] == 1 || if_w[m][n] == 2 )
          {
              continue;
          }

          for(int x=0; x<19; x++)
          {
              for(int y=0; y<19; y++)
              {
            //00022000
            if( if_w[x-2][y+2] == 0 && if_w[x-1][y+1] == 0 && if_w[x][y] == 0 && if_w[x+1][y-1] == 2 && if_w[x+2][y-2] == 2 &&
                if_w[x+3][y-3] == 0 && if_w[x+4][y-4] == 0 && if_w[x+5][y-5] == 0 )
                W_weight[m][n] += 2000;
            //0020200
            if( if_w[x-1][y+1] == 0 && if_w[x][y] == 0 && if_w[x+1][y-1] == 2 && if_w[x+2][y-2] == 0 && if_w[x+3][y-3] == 2 && if_w[x+4][y-4] == 0 &&
                if_w[x+5][y-5] == 0 )
                W_weight[m][n] += 1500;
            //020020
            if( if_w[x][y] == 0 && if_w[x+1][y-1] == 2 && if_w[x+2][y-2] == 0 && if_w[x+3][y-3] == 0 && if_w[x+4][y-4] == 2 && if_w[x+5][y-5] == 0 )
                W_weight[m][n] += 1000;
            //여기까지 양쪽에 안 막힌, 흰 돌이 2개가 발견 될 때 경우의 수들

            //122000
            if( if_w[x][y] == 1 && if_w[x+1][y-1] == 2 && if_w[x+2][y-2] == 2 && if_w[x+3][y-3] == 0 && if_w[x+4][y-4] == 0 && if_w[x+5][y-5] == 0 )
                W_weight[m][n] += 500;
            //120200
            if( if_w[x][y] == 1 && if_w[x+1][y-1] == 2 && if_w[x+2][y-2] == 0 && if_w[x+3][y-3] == 2 && if_w[x+4][y-4] == 0 && if_w[x+5][y-5] == 0 )
                W_weight[m][n] += 500;
            //120020
            if( if_w[x][y] == 1 && if_w[x+1][y-1] == 2 && if_w[x+2][y-2] == 0 && if_w[x+3][y-3] == 0 && if_w[x+4][y-4] == 2 && if_w[x+5][y-5] == 0 )
                W_weight[m][n] += 500;
            //102200
            if( if_w[x][y] == 1 && if_w[x+1][y-1] == 0 && if_w[x+2][y-2] == 2 && if_w[x+3][y-3] == 2 && if_w[x+4][y-4] == 0 && if_w[x+5][y-5] == 0 )
                W_weight[m][n] += 800;
            //102020
            if( if_w[x][y] == 1 && if_w[x+1][y-1] == 0 && if_w[x+2][y-2] == 2 && if_w[x+3][y-3] == 0 && if_w[x+4][y-4] == 2 && if_w[x+5][y-5] == 0 )
                W_weight[m][n] += 800;
            //여기까지 왼쪽에 검은돌로 막힌 경우.
            //오른쪽에 검은돌로 막힌 경우는 이 대칭으로만 작성해주면됌

            //000221
            if( if_w[x-2][y+2] == 0 && if_w[x-1][y+1] == 0 && if_w[x][y] == 0 && if_w[x+1][y-1] == 2 && if_w[x+2][y-2] == 2 && if_w[x+3][y-3] == 1 )
                W_weight[m][n] += 500;
            //002021
            if( if_w[x-1][y+1] == 0 && if_w[x][y] == 0 && if_w[x+1][y-1] == 2 && if_w[x+2][y-2] == 0 && if_w[x+3][y-3] == 2 && if_w[x+4][y-4] == 1 )
                W_weight[m][n] += 500;
            //020021
            if( if_w[x][y] == 0 && if_w[x+1][y-1] == 2 && if_w[x+2][y-2] == 0 && if_w[x+3][y-3] == 0 && if_w[x+4][y-4] == 2 && if_w[x+5][y-5] == 1 )
                W_weight[m][n] += 500;
            //002201
            if( if_w[x-1][y+1] == 0 && if_w[x][y] == 0 && if_w[x+1][y-1] == 2 && if_w[x+2][y-2] == 2 && if_w[x+3][y-3] == 0 && if_w[x+4][y-4] == 1 )
                W_weight[m][n] += 800;
            //020201
            if( if_w[x][y] == 0 && if_w[x+1][y-1] == 2 && if_w[x+2][y-2] == 0 && if_w[x+3][y-3] == 2 && if_w[x+4][y-4] == 0 && if_w[x+5][y-5] == 1 )
                W_weight[m][n] += 800;
            //여기까지 한쪽이 막힌 경우.
            //그 다음은 양쪽이 막힌 경우. 양쪽이 막힌 경우는 안이 6칸일 경우만 따지자.

            //12200001
            if( if_w[x][y] == 1 && if_w[x+1][y-1] == 2 && if_w[x+2][y-2] == 2 && if_w[x+3][y-3] == 0 && if_w[x+4][y-4] == 0 && if_w[x+5][y-5] == 0 &&
                if_w[x+6][y-6] == 0 && if_w[x+7][y-7] == 1 )
                W_weight[m][n] += 300;
            //12020001
            if( if_w[x][y] == 1 && if_w[x+1][y-1] == 2 && if_w[x+2][y-2] == 0 && if_w[x+3][y-3] == 2 && if_w[x+4][y-4] == 0 && if_w[x+5][y-5] == 0 &&
                if_w[x+6][y-6] == 0 && if_w[x+7][y-7] == 1 )
                W_weight[m][n] += 300;
            //12002001
            if( if_w[x][y] == 1 && if_w[x+1][y-1] == 2 && if_w[x+2][y-2] == 0 && if_w[x+3][y-3] == 0 && if_w[x+4][y-4] == 2 && if_w[x+5][y-5] == 0 &&
                if_w[x+6][y-6] == 0 && if_w[x+7][y-7] == 1 )
                W_weight[m][n] += 300;
            //12000201
            if( if_w[x][y] == 1 && if_w[x+1][y-1] == 2 && if_w[x+2][y-2] == 0 && if_w[x+3][y-3] == 0 && if_w[x+4][y-4] == 0 && if_w[x+5][y-5] == 2 &&
                if_w[x+6][y-6] == 0 && if_w[x+7][y-7] == 1 )
                W_weight[m][n] += 300;
            //12000021
            if( if_w[x][y] == 1 && if_w[x+1][y-1] == 2 && if_w[x+2][y-2] == 0 && if_w[x+3][y-3] == 0 && if_w[x+4][y-4] == 0 && if_w[x+5][y-5] == 0 &&
                if_w[x+6][y-6] == 2 && if_w[x+7][y-7] == 1 )
                W_weight[m][n] += 300;
            //10220001
            if( if_w[x][y] == 1 && if_w[x+1][y-1] == 0 && if_w[x+2][y-2] == 2 && if_w[x+3][y-3] == 2 && if_w[x+4][y-4] == 0 && if_w[x+5][y-5] == 0 &&
                if_w[x+6][y-6] == 0 && if_w[x+7][y-7] == 1 )
                W_weight[m][n] += 300;
            //10202001
            if( if_w[x][y] == 1 && if_w[x+1][y-1] == 0 && if_w[x+2][y-2] == 2 && if_w[x+3][y-3] == 0 && if_w[x+4][y-4] == 2 && if_w[x+5][y-5] == 0 &&
                if_w[x+6][y-6] == 0 && if_w[x+7][y-7] == 1 )
                W_weight[m][n] += 300;
            //10200201
            if( if_w[x][y] == 1 && if_w[x+1][y-1] == 0 && if_w[x+2][y-2] == 2 && if_w[x+3][y-3] == 0 && if_w[x+4][y-4] == 0 && if_w[x+5][y-5] == 2 &&
                if_w[x+6][y-6] == 0 && if_w[x+7][y-7] == 1 )
                W_weight[m][n] += 300;
            //10200021
            if( if_w[x][y] == 1 && if_w[x+1][y-1] == 0 && if_w[x+2][y-2] == 2 && if_w[x+3][y-3] == 0 && if_w[x+4][y-4] == 0 && if_w[x+5][y-5] == 0 &&
                if_w[x+6][y-6] == 2 && if_w[x+7][y-7] == 1 )
                W_weight[m][n] += 300;
            //10022001
            if( if_w[x][y] == 1 && if_w[x+1][y-1] == 0 && if_w[x+2][y-2] == 0 && if_w[x+3][y-3] == 2 && if_w[x+4][y-4] == 2 && if_w[x+5][y-5] == 0 &&
                if_w[x+6][y-6] == 0 && if_w[x+7][y-7] == 1 )
                W_weight[m][n] += 300;
            //10020201
            if( if_w[x][y] == 1 && if_w[x+1][y-1] == 0 && if_w[x+2][y-2] == 0 && if_w[x+3][y-3] == 2 && if_w[x+4][y-4] == 0 && if_w[x+5][y-5] == 2 &&
                if_w[x+6][y-6] == 0 && if_w[x+7][y-7] == 1 )
                W_weight[m][n] += 300;
            //10020021
            if( if_w[x][y] == 1 && if_w[x+1][y-1] == 0 && if_w[x+2][y-2] == 0 && if_w[x+3][y-3] == 2 && if_w[x+4][y-4] == 0 && if_w[x+5][y-5] == 0 &&
                if_w[x+6][y-6] == 2 && if_w[x+7][y-7] == 1 )
                W_weight[m][n] += 300;
            //10002201
            if( if_w[x][y] == 1 && if_w[x+1][y-1] == 0 && if_w[x+2][y-2] == 0 && if_w[x+3][y-3] == 0 && if_w[x+4][y-4] == 2 && if_w[x+5][y-5] == 2 &&
                if_w[x+6][y-6] == 0 && if_w[x+7][y-7] == 1 )
                W_weight[m][n] += 300;
            //10002021
            if( if_w[x][y] == 1 && if_w[x+1][y-1] == 0 && if_w[x+2][y-2] == 0 && if_w[x+3][y-3] == 2 && if_w[x+4][y-4] == 0 && if_w[x+5][y-5] == 2 &&
                if_w[x+6][y-6] == 0 && if_w[x+7][y-7] == 1 )
                W_weight[m][n] += 300;
            //10000221
            if( if_w[x][y] == 1 && if_w[x+1][y-1] == 0 && if_w[x+2][y-2] == 0 && if_w[x+3][y-3] == 0 && if_w[x+4][y-4] == 0 && if_w[x+5][y-5] == 2 &&
                if_w[x+6][y-6] == 2 && if_w[x+7][y-7] == 1 )
                W_weight[m][n] += 300;
              }
          }
          if_w[m][n] = 0;
      }
    }
}

void AI::W_AI_3_in_Diagonal_check()
{
    for(int m=0 ; m<19 ; m++)
        {
          for(int n=0 ; n<19 ; n++)
          {
              if( this->if_w[m][n] == 0 )
              {
              this->if_w[m][n] = 2;
              }
              else if( this->if_w[m][n] == 1 || this->if_w[m][n] == 2 )
              {
                  continue;
              }

              for(int x=0; x<19; x++)
              {
                  for(int y=0; y<19; y++)
                  {
                //000222000
                if( this->if_w[x-1][y+1] == 0 && this->if_w[x][y] == 0 && this->if_w[x+1][y-1] == 2 && this->if_w[x+2][y-2] == 2 && this->if_w[x+3][y-3] == 2&& this->if_w[x+4][y-4]==0 &&
                    this->if_w[x+5][y-5] == 0 )
                    this->W_weight[m][n] += 5000;
                //00202200
                if( this->if_w[x-1][y+1] == 0 && this->if_w[x][y] == 0 && this->if_w[x+1][y-1] == 2 && this->if_w[x+2][y-2] == 0 && this->if_w[x+3][y-3] == 2 && this->if_w[x+4][y-4] == 2 &&
                    this->if_w[x+5][y-5]==0 && this->if_w[x+6][y-6] == 0 )
                    this->W_weight[m][n] += 3500;
                //00220200
                if( this->if_w[x-1][y+1] == 0 && this->if_w[x][y] == 0 && this->if_w[x+1][y-1] == 2 && this->if_w[x+2][y-2] == 2 && this->if_w[x+3][y-3] == 0 && this->if_w[x+4][y-4] == 2 &&
                    this->if_w[x+5][y-5] == 0 && this->if_w[x+6][y-6] == 0 )
                    this->W_weight[m][n] += 3500;
                //0200220
                if( this->if_w[x][y] == 0 && this->if_w[x+1][y-1] == 2 && this->if_w[x+2][y-2] == 0 && this->if_w[x+3][y-3] == 0 && this->if_w[x+4][y-4] == 2 && this->if_w[x+5][y-5] == 2
                    &&this->if_w[x+6][y-6] ==0 )
                    this->W_weight[m][n] += 3000;
                //0202020
                if( this->if_w[x][y] == 0 && this->if_w[x+1][y-1] == 2 && this->if_w[x+2][y-2] == 0 && this->if_w[x+3][y-3] == 2 && this->if_w[x+4][y-4] == 0 && this->if_w[x+5][y-5] == 2
                    &&this->if_w[x+6][y-6]==0 )
                    this->W_weight[m][n] += 3000;
                //0220020
                if( this->if_w[x][y] == 0 && this->if_w[x+1][y-1] == 2 && this->if_w[x+2][y-2] == 2 && this->if_w[x+3][y-3] == 0 && this->if_w[x+4][y-4] == 0 && this->if_w[x+5][y-5] == 2
                    && this->if_w[x+6][y-6] ==0 )
                    this->W_weight[m][n] += 3000;
                //여기까지 양쪽에 안 막힌, 흰 돌이 2개가 발견 될 때 경우의 수들

                //122200
                if( this->if_w[x][y] == 1 && this->if_w[x+1][y-1] == 2 && this->if_w[x+2][y-2] == 2 && this->if_w[x+3][y-3] == 2 && this->if_w[x+4][y-4] ==0 && this->if_w[x+5][y-5] == 0 )
                    this->W_weight[m][n] += 1000;
                //1202200
                if( this->if_w[x][y] == 1 && this->if_w[x+1][y-1] == 2 && this->if_w[x+2][y-2] == 0 && this->if_w[x+3][y-3] == 2 && this->if_w[x+4][y-4] == 2 && this->if_w[x+5][y-5] ==0 &&
                    this->if_w[x][y-6] == 0 )
                    this->W_weight[m][n] += 1000;
                //1220200
                if( this->if_w[x][y] == 1 && this->if_w[x+1][y-1] == 2 && this->if_w[x+2][y-2] == 2 && this->if_w[x+3][y-3] == 0 && this->if_w[x+4][y-4] == 2 && this->if_w[x+5][y-5] == 0 &&
                    this->if_w[x+6][y-6] == 0 )
                    this->W_weight[m][n] += 1000;
                //1022200
                if( this->if_w[x][y] == 1 && this->if_w[x+1][y-1] == 0 && this->if_w[x+2][y-2] == 2 && this->if_w[x+3][y-3] == 2 && this->if_w[x+4][y-4] == 2 && this->if_w[x+5][y-5] ==0 &&
                    this->if_w[x+6][y-6] == 0 )
                    this->W_weight[m][n] += 1300;
                //1200220
                if( this->if_w[x][y] == 1 && this->if_w[x+1][y-1] == 2 && this->if_w[x+2][y-2] == 0 && this->if_w[x+3][y-3] == 0 && this->if_w[x+4][y-4] == 2 && this->if_w[x+5][y-5] == 2 &&
                this->if_w[x+6][y-6] ==0 )
                    this->W_weight[m][n] += 1300;
                //1220020
                if( this->if_w[x][y] == 1 && this->if_w[x][y-1] == 2 && this->if_w[x][y-2] == 2 && this->if_w[x][y-3] == 0 && this->if_w[x][y-4] == 0 && this->if_w[x][y-5] == 2 &&
                    this->if_w[x][y-6] == 0 )
                    this->W_weight[m][n] += 1000;
                //1202020
                if( this->if_w[x][y] == 1 && this->if_w[x+1][y-1] == 2 && this->if_w[x+2][y-2] == 0 && this->if_w[x+3][y-3] == 2 && this->if_w[x+4][y-4] == 0 && this->if_w[x+5][y-5] == 2 &&
                    this->if_w[x+6][y-6] ==0 )
                    this->W_weight[m][n] += 1000;
                //1020220
                if( this->if_w[x][y] == 1 && this->if_w[x+1][y-1] == 0 && this->if_w[x+2][y-2] == 2 && this->if_w[x+3][y-3] == 0 && this->if_w[x+4][y-4] == 2 && this->if_w[x+5][y-5] == 2 &&
                    this->if_w[x+6][y-6] == 0)
                    this->W_weight[m][n] += 1300;

                //여기까지 왼쪽에 검은돌로 막힌 경우.
                //오른쪽에 검은돌로 막힌 경우는 이 대칭으로만 작성해주면됌

                //002221
                if( this->if_w[x-1][y+1] == 0 && this->if_w[x][y] == 0 && this->if_w[x+1][y-1] == 2 && this->if_w[x+2][y-2] == 2 && this->if_w[x+3][y-3] == 2 && this->if_w[x+4][y-4] == 1 )
                    this->W_weight[m][n] += 1000;
                //0022021
                if( this->if_w[x-1][y+1] == 0 && this->if_w[x][y] == 0 && this->if_w[x+1][y-1] == 2 && this->if_w[x+2][y-2] == 2 && this->if_w[x+3][y-3] == 0 && this->if_w[x+4][y-4] == 2 &&
                    this->if_w[x+5][y-5]==1 )
                    this->W_weight[m][n] += 1000;
                //0020221
                if( this->if_w[x-1][y+1] == 0 && this->if_w[x][y] == 0 && this->if_w[x+1][y-1] == 2 && this->if_w[x+2][y-2] == 0 && this->if_w[x+3][y-3] == 2 && this->if_w[x+4][y-4] == 2 &&
                    this->if_w[x+5][y-5] == 1 )
                    this->W_weight[m][n] += 1000;
                //0022201
                if( this->if_w[x-1][y+1] == 0 && this->if_w[x][y] == 0 && this->if_w[x+1][y-1] == 2 && this->if_w[x+2][y-2] == 2 && this->if_w[x+3][y-3] == 2 && this->if_w[x+4][y-4] == 0 &&
                    this->if_w[x+5][y-5] == 1 )
                    this->W_weight[m][n] += 1300;
                //0220021
                if( this->if_w[x][y] == 0 && this->if_w[x][y-1] == 2 && this->if_w[x][y-2] == 2 && this->if_w[x][y-3] == 0 && this->if_w[x][y-4] == 0 && this->if_w[x][y-5] == 2 &&
                    this->if_w[x][y-6] == 1 )
                    this->W_weight[m][n] += 1300;
                //0200221
                if( this->if_w[x][y] == 0 && this->if_w[x+1][y-1] == 2 && this->if_w[x+2][y-2] == 0 && this->if_w[x+3][y-3] == 0 && this->if_w[x+4][y-4] == 2 && this->if_w[x+5][y-5] == 2 &&
                    this->if_w[x+6][y-6] == 1 )
                    this->W_weight[m][n] += 1000;
                //0202021
                if( this->if_w[x][y] == 0 && this->if_w[x+1][y-1] == 2 && this->if_w[x+2][y-2] == 0 && this->if_w[x+3][y-3] == 2 && this->if_w[x+4][y-4] == 0 && this->if_w[x+5][y-5] == 2 &&
                    this->if_w[x+6][y-6] == 1 )
                    this->W_weight[m][n] += 1000;
                //0220201
                if( this->if_w[x][y] == 0 && this->if_w[x+1][y-1] == 2 && this->if_w[x+2][y-2] == 2 && this->if_w[x+3][y-3] == 0 && this->if_w[x+4][y-4] == 2 && this->if_w[x+5][y-5] == 0 &&
                    this->if_w[x+6][y-6] == 1 )
                    this->W_weight[m][n] += 1300;

                //여기까지 한쪽이 막힌 경우.
                //그 다음은 양쪽이 막힌 경우. 양쪽이 막힌 경우는 안이 6칸일 경우만 따지자.

                //12220001
                if( this->if_w[x][y] == 1 && this->if_w[x+1][y-1] == 2 && this->if_w[x+2][y-2] == 2 && this->if_w[x+3][y-3] == 2 && this->if_w[x+4][y-4] == 0 && this->if_w[x+5][y-5] == 0 &&
                    this->if_w[x+6][y-6] == 0 && this->if_w[x+7][y-7] == 1 )
                    this->W_weight[m][n] += 300;
                //12022001
                if( this->if_w[x][y] == 1 && this->if_w[x+1][y-1] == 2 && this->if_w[x+2][y-2] == 0 && this->if_w[x+3][y-3] == 2 && this->if_w[x+4][y-4] == 2 && this->if_w[x+5][y-5] == 0 &&
                    this->if_w[x+6][y-6] == 0 && this->if_w[x+7][y-7] == 1 )
                    this->W_weight[m][n] += 300;
                //12002201
                if( this->if_w[x][y] == 1 && this->if_w[x+1][y-1] == 2 && this->if_w[x+2][y-2] == 0 && this->if_w[x+3][y-3] == 0 && this->if_w[x+4][y-4] == 2 && this->if_w[x+5][y-5] == 2 &&
                    this->if_w[x+6][y-6] == 0 && this->if_w[x+7][y-7] == 1 )
                    this->W_weight[m][n] += 300;
                //12000221
                if( this->if_w[x][y] == 1 && this->if_w[x+1][y-1] == 2 && this->if_w[x+2][y-2] == 0 && this->if_w[x+3][y-3] == 0 && this->if_w[x+4][y-4] == 0 && this->if_w[x+5][y-5] == 2 &&
                    this->if_w[x+6][y-6] == 2 && this->if_w[x+7][y-7] == 1 )
                    this->W_weight[m][n] += 300;
                //12202001
                if( this->if_w[x][y] == 1 && this->if_w[x+1][y-1] == 2 && this->if_w[x+2][y-2] == 2 && this->if_w[x+3][y-3] == 0 && this->if_w[x+4][y-4] == 2 && this->if_w[x+5][y-5] == 0 &&
                    this->if_w[x+6][y-6] == 0 && this->if_w[x+7][y-7] == 1 )
                    this->W_weight[m][n] += 300;
                //12200201
                if( this->if_w[x][y] == 1 && this->if_w[x+1][y-1] == 2 && this->if_w[x+2][y-2] == 2 && this->if_w[x+3][y-3] == 0 && this->if_w[x+4][y-4] == 0 && this->if_w[x+5][y-5] == 2 &&
                    this->if_w[x+6][y-6] == 0 && this->if_w[x+7][y-7] == 1 )
                    this->W_weight[m][n] += 300;
                //12200021
                if( this->if_w[x][y] == 1 && this->if_w[x+1][y-1] == 2 && this->if_w[x+2][y-2] == 2 && this->if_w[x+3][y-3] == 0 && this->if_w[x+4][y-4] == 0 && this->if_w[x+5][y-5] == 0 &&
                    this->if_w[x+6][y-6] == 2 && this->if_w[x+7][y-7] == 1 )
                    this->W_weight[m][n] += 300;
                //12002021
                if( this->if_w[x][y] == 1 && this->if_w[x+1][y-1] == 2 && this->if_w[x+2][y-2] == 0 && this->if_w[x+3][y-3] == 0 && this->if_w[x+4][y-4] == 2 && this->if_w[x+5][y-5] == 0 &&
                    this->if_w[x+6][y-6] == 2 && this->if_w[x+7][y-7] == 1 )
                    this->W_weight[m][n] += 300;
                //12020021
                if( this->if_w[x][y] == 1 && this->if_w[x+1][y-1] == 2 && this->if_w[x+2][y-2] == 0 && this->if_w[x+3][y-3] == 2 && this->if_w[x+4][y-4] == 0 && this->if_w[x+5][y-5] == 0 &&
                    this->if_w[x+6][y-6] == 2 && this->if_w[x+7][y-7] == 1 )
                    this->W_weight[m][n] += 300;
                //12020201
                if( this->if_w[x][y] == 1 && this->if_w[x+1][y-1] == 2 && this->if_w[x+2][y-2] == 0 && this->if_w[x+3][y-3] == 2 && this->if_w[x+4][y-4] == 0 && this->if_w[x+5][y-5] == 2 &&
                    this->if_w[x+6][y-6] == 0 && this->if_w[x+7][y-7] == 1 )
                    this->W_weight[m][n] += 300;
                //10222001
                if( this->if_w[x][y] == 1 && this->if_w[x+1][y-1] == 0 && this->if_w[x+2][y-2] == 2 && this->if_w[x+3][y-3] == 2 && this->if_w[x+4][y-4] == 2 && this->if_w[x+5][y-5] == 0 &&
                    this->if_w[x+6][y-6] == 0 && this->if_w[x+7][y-7] == 1 )
                    this->W_weight[m][n] += 300;
                //10202201
                if( this->if_w[x][y] == 1 && this->if_w[x+1][y-1] == 0 && this->if_w[x+2][y-2] == 2 && this->if_w[x+3][y-3] == 0 && this->if_w[x+4][y-4] == 2 && this->if_w[x+5][y-5] == 2 &&
                    this->if_w[x+6][y-6] == 0 && this->if_w[x+7][y-7] == 1 )
                    this->W_weight[m][n] += 300;
                //10200221
                if( this->if_w[x][y] == 1 && this->if_w[x+1][y-1] == 0 && this->if_w[x+2][y-2] == 2 && this->if_w[x+3][y-3] == 0 && this->if_w[x+4][y-4] == 0 && this->if_w[x+5][y-5] == 2 &&
                    this->if_w[x+6][y-6] == 2 && this->if_w[x+7][y-7] == 1 )
                    this->W_weight[m][n] += 300;
                //10220201
                if( this->if_w[x][y] == 1 && this->if_w[x+1][y-1] == 0 && this->if_w[x+2][y-2] == 2 && this->if_w[x+3][y-3] == 2 && this->if_w[x+4][y-4] == 0 && this->if_w[x+5][y-5] == 2 &&
                    this->if_w[x+6][y-6] == 0 && this->if_w[x+7][y-7] == 1 )
                    this->W_weight[m][n] += 300;
                //10220021
                if( this->if_w[x][y] == 1 && this->if_w[x+1][y-1] == 0 && this->if_w[x+2][y-2] == 2 && this->if_w[x+3][y-3] == 2 && this->if_w[x+4][y-4] == 0 && this->if_w[x+5][y-5] == 0 &&
                    this->if_w[x+6][y-6] == 2 && this->if_w[x+7][y-7] == 1 )
                    this->W_weight[m][n] += 300;
                //10022021
                if( this->if_w[x][y] == 1 && this->if_w[x+1][y-1] == 0 && this->if_w[x+2][y-2] == 0 && this->if_w[x+3][y-3] == 2 && this->if_w[x+4][y-4] == 2 && this->if_w[x+5][y-5] == 0 &&
                    this->if_w[x+6][y-6] == 2 && this->if_w[x+7][y-7] == 1 )
                    this->W_weight[m][n] += 300;
                //10022201
                if( this->if_w[x][y] == 1 && this->if_w[x+1][y-1] == 0 && this->if_w[x+2][y-2] == 0 && this->if_w[x+3][y-3] == 2 && this->if_w[x+4][y-4] == 2 && this->if_w[x+5][y-5] == 2 &&
                    this->if_w[x+6][y-6] == 0 && this->if_w[x+7][y-7] == 1 )
                    this->W_weight[m][n] += 300;
                //10020221
                if( this->if_w[x][y] == 1 && this->if_w[x+1][y-1] == 0 && this->if_w[x+2][y-2] == 0 && this->if_w[x+3][y-3] == 2 && this->if_w[x+4][y-4] == 0 && this->if_w[x+5][y-5] == 2 &&
                    this->if_w[x+6][y-6] == 2 && this->if_w[x+7][y-7] == 1 )
                    this->W_weight[m][n] += 300;
                //10002221
                if( this->if_w[x][y] == 1 && this->if_w[x+1][y-1] == 0 && this->if_w[x+2][y-2] == 0 && this->if_w[x+3][y-3] == 0 && this->if_w[x+4][y-4] == 0 && this->if_w[x+5][y-5] == 2 &&
                    this->if_w[x+6][y-6] == 2 && this->if_w[x+7][y-7] == 1 )
                    this->W_weight[m][n] += 300;
                //10202021
                if( this->if_w[x][y] == 1 && this->if_w[x+1][y-1] == 0 && this->if_w[x+2][y-2] == 2 && this->if_w[x+3][y-3] == 0 && this->if_w[x+4][y-4] == 2 && this->if_w[x+5][y-5] == 0 &&
                    this->if_w[x+6][y-6] == 2 && this->if_w[x+7][y-7] == 1 )
                    this->W_weight[m][n] += 300;
                    }
              }
              this->if_w[m][n] = 0;
          }
        }

}

void AI::W_AI_4_in_Diagonal_check()
{
    for (int m = 0; m < 19; m++)
        {
            for (int n = 0; n < 19; n++)
            {
                if (this->if_w[m][n] == 0)
                {
                    this->if_w[m][n] = 2;
                }
                else if (this->if_w[m][n] == 1 || this->if_w[m][n] == 2)
                {
                    continue;
                }

                for (int x = 0; x < 19; x++)
                {
                    for (int y = 0; y < 19; y++)
                    {
                        /*4개 -> 안막혔을 때*/
                              //00222200
                        if (this->if_w[x - 1][y + 1] == 0 && this->if_w[x][y] == 0 && this->if_w[x + 1][y - 1] == 2 && this->if_w[x + 2][y - 2] == 2 && this->if_w[x + 3][y - 3] == 2 && this->if_w[x + 4][y - 4] == 2 &&
                            this->if_w[x + 5][y - 5] == 0)
                            this->W_weight[m][n] += 10000;
                        //002022200
                        if (this->if_w[x - 1][y + 1] == 0 && this->if_w[x][y] == 0 && this->if_w[x + 1][y - 1] == 2 && this->if_w[x + 2][y - 2] == 0 && this->if_w[x + 3][y - 3] == 2 && this->if_w[x + 4][y - 4] == 2 &&
                            this->if_w[x + 5][y - 5] == 2 && this->if_w[x + 6][y - 6] == 0 && this->if_w[x + 7][y - 7] == 0)
                            this->W_weight[m][n] += 7000;
                        //002220200
                        if (this->if_w[x - 1][y + 1] == 0 && this->if_w[x][y] == 0 && this->if_w[x + 1][y - 1] == 2 && this->if_w[x + 2][y - 2] == 2 && this->if_w[x + 3][y - 3] == 2 && this->if_w[x + 4][y - 4] == 0 &&
                            this->if_w[x + 5][y - 5] == 2 && this->if_w[x + 6][y - 6] == 0 && this->if_w[x + 7][y - 7] == 0)
                            this->W_weight[m][n] += 7000;
                        //002202200
                        if (this->if_w[x - 1][y + 1] == 0 && this->if_w[x][y] == 0 && this->if_w[x + 1][y - 1] == 2 && this->if_w[x + 2][y - 2] == 2 && this->if_w[x + 3][y - 3] == 0 && this->if_w[x + 4][y - 4] == 2 &&
                            this->if_w[x + 5][y - 5] == 2 && this->if_w[x + 6][y - 6] == 0 && this->if_w[x + 7][y - 7] == 0)
                            this->W_weight[m][n] += 7000;
                        //02220020
                        if (this->if_w[x][y] == 0 && this->if_w[x + 1][y - 1] == 2 && this->if_w[x + 2][y - 2] == 2 && this->if_w[x + 3][y - 3] == 2 && this->if_w[x + 4][y - 4] == 0 && this->if_w[x + 5][y - 5] == 0 &&
                            this->if_w[x + 6][y - 6] == 2 && this->if_w[x + 7][y - 7] == 0)
                            this->W_weight[m][n] += 5000;
                        //02002220
                        if (this->if_w[x][y] == 0 && this->if_w[x + 1][y - 1] == 2 && this->if_w[x + 2][y - 2] == 0 && this->if_w[x + 3][y - 3] == 0 && this->if_w[x + 4][y - 4] == 2 && this->if_w[x + 5][y - 5] == 2 &&
                            this->if_w[x + 6][y - 6] == 2 && this->if_w[x + 7][y - 7] == 0)
                            this->W_weight[m][n] += 5000;
                        //02202020
                        if (this->if_w[x][y] == 0 && this->if_w[x + 1][y - 1] == 2 && this->if_w[x + 2][y - 2] == 2 && this->if_w[x + 3][y - 3] == 0 && this->if_w[x + 4][y - 4] == 2 && this->if_w[x + 5][y - 5] == 2 &&
                            this->if_w[x + 6][y - 6] == 2 && this->if_w[x + 7][y - 7] == 0)
                            this->W_weight[m][n] += 4000;
                        //02020220
                        if (this->if_w[x][y] == 0 && this->if_w[x + 1][y - 1] == 2 && this->if_w[x + 2][y - 2] == 0 && this->if_w[x + 3][y - 3] == 2 && this->if_w[x + 4][y - 4] == 0 && this->if_w[x + 5][y - 5] == 2 &&
                            this->if_w[x + 6][y - 6] == 2 && this->if_w[x + 7][y - 7] == 0)
                            this->W_weight[m][n] += 4000;

                        //4개 한쪽 막혔을 때
                        //122220
                        if (this->if_w[x][y] == 1 && this->if_w[x + 1][y - 1] == 2 && this->if_w[x + 2][y - 2] == 2 && this->if_w[x + 3][y - 3] == 2 && this->if_w[x + 4][y - 4] == 2 && this->if_w[x + 5][y - 5] == 0)
                            this->W_weight[m][n] += 3500;
                        //1202220
                        if (this->if_w[x][y] == 1 && this->if_w[x + 1][y - 1] == 2 && this->if_w[x + 2][y - 2] == 0 && this->if_w[x + 3][y - 3] == 2 && this->if_w[x + 4][y - 4] == 2 && this->if_w[x + 5][y - 5] == 2 && this->if_w[x + 6][y - 6] == 0)
                            this->W_weight[m][n] += 3500;
                        //1220220
                        if (this->if_w[x][y] == 1 && this->if_w[x + 1][y - 1] == 2 && this->if_w[x + 2][y - 2] == 2 && this->if_w[x + 3][y - 3] == 0 && this->if_w[x + 4][y - 4] == 2 && this->if_w[x + 5][y - 5] == 2 && this->if_w[x + 6][y - 6] == 0)
                            this->W_weight[m][n] += 3500;
                        //1222020
                        if (this->if_w[x][y] == 1 && this->if_w[x + 1][y - 1] == 2 && this->if_w[x + 2][y - 2] == 2 && this->if_w[x + 3][y - 3] == 2 && this->if_w[x + 4][y - 4] == 0 && this->if_w[x + 5][y - 5] == 2 && this->if_w[x + 6][y - 6] == 0)
                            this->W_weight[m][n] += 3500;
                        //1022220
                        if (this->if_w[x][y] == 1 && this->if_w[x + 1][y - 1] == 0 && this->if_w[x + 2][y - 2] == 2 && this->if_w[x + 3][y - 3] == 2 && this->if_w[x + 4][y - 4] == 2 && this->if_w[x + 5][y - 5] == 2 && this->if_w[x + 6][y - 6] == 0)
                            this->W_weight[m][n] += 3500;
                        //12002220
                        if (this->if_w[x][y] == 1 && this->if_w[x + 1][y - 1] == 2 && this->if_w[x + 2][y - 2] == 0 && this->if_w[x + 3][y - 3] == 0 && this->if_w[x + 4][y - 4] == 2 && this->if_w[x + 5][y - 5] == 2 && this->if_w[x + 6][y - 6] == 2 &&
                            this->if_w[x + 7][y - 7] == 0)
                            this->W_weight[m][n] += 3500;
                        //12020220
                        if (this->if_w[x][y] == 1 && this->if_w[x + 1][y - 1] == 2 && this->if_w[x + 2][y - 2] == 0 && this->if_w[x + 3][y - 3] == 2 && this->if_w[x + 4][y - 4] == 0 && this->if_w[x + 5][y - 5] == 2 && this->if_w[x + 6][y - 6] == 2 &&
                            this->if_w[x + 7][y - 7] == 0)
                            this->W_weight[m][n] += 3500;
                        //12022020
                        if (this->if_w[x][y] == 1 && this->if_w[x + 1][y - 1] == 2 && this->if_w[x + 2][y - 2] == 0 && this->if_w[x + 3][y - 3] == 2 && this->if_w[x + 4][y - 4] == 2 && this->if_w[x + 5][y - 5] == 0 && this->if_w[x + 6][y - 6] == 2 &&
                            this->if_w[x + 7][y - 7] == 0)
                            this->W_weight[m][n] += 3500;
                        //12200220
                        if (this->if_w[x][y] == 1 && this->if_w[x + 1][y - 1] == 2 && this->if_w[x + 2][y - 2] == 2 && this->if_w[x + 3][y - 3] == 0 && this->if_w[x + 4][y - 4] == 0 && this->if_w[x + 5][y - 5] == 2 && this->if_w[x + 6][y - 6] == 2 &&
                            this->if_w[x + 7][y - 7] == 0)
                            this->W_weight[m][n] += 3500;
                        //12202020
                        if (this->if_w[x][y] == 1 && this->if_w[x + 1][y - 1] == 2 && this->if_w[x + 2][y - 2] == 2 && this->if_w[x + 3][y - 3] == 0 && this->if_w[x + 4][y - 4] == 2 && this->if_w[x + 5][y - 5] == 0 && this->if_w[x + 6][y - 6] == 2 &&
                            this->if_w[x + 7][y - 7] == 0)
                            this->W_weight[m][n] += 3500;
                        //12220020
                        if (this->if_w[x][y] == 1 && this->if_w[x + 1][y - 1] == 2 && this->if_w[x + 2][y - 2] == 2 && this->if_w[x + 3][y - 3] == 2 && this->if_w[x + 4][y - 4] == 0 && this->if_w[x + 5][y - 5] == 0 && this->if_w[x + 6][y - 6] == 2 &&
                            this->if_w[x + 7][y - 7] == 0)
                            this->W_weight[m][n] += 3500;
                        //10220220
                        if (this->if_w[x][y] == 1 && this->if_w[x + 1][y - 1] == 0 && this->if_w[x + 2][y - 2] == 2 && this->if_w[x + 3][y - 3] == 2 && this->if_w[x + 4][y - 4] == 0 && this->if_w[x + 5][y - 5] == 2 && this->if_w[x + 6][y - 6] == 2 &&
                            this->if_w[x + 7][y - 7] == 0)
                            this->W_weight[m][n] += 3500;
                        //10222020
                        if (this->if_w[x][y] == 1 && this->if_w[x + 1][y - 1] == 0 && this->if_w[x + 2][y - 2] == 2 && this->if_w[x + 3][y - 3] == 2 && this->if_w[x + 4][y - 4] == 2 && this->if_w[x + 5][y - 5] == 0 && this->if_w[x + 6][y - 6] == 2 &&
                            this->if_w[x + 7][y - 7] == 0)
                            this->W_weight[m][n] += 3500;
                        //10202220
                        if (this->if_w[x][y] == 1 && this->if_w[x + 1][y - 1] == 0 && this->if_w[x + 2][y - 2] == 2 && this->if_w[x + 3][y - 3] == 0 && this->if_w[x + 4][y - 4] == 2 && this->if_w[x + 5][y - 5] == 2 && this->if_w[x + 6][y - 6] == 2 &&
                            this->if_w[x + 7][y - 7] == 0)
                            this->W_weight[m][n] += 3500;


                        //4개 한쪽 막혔을 때 reverse
                        //022221
                        if (this->if_w[x][y] == 0 && this->if_w[x + 1][y - 1] == 2 && this->if_w[x + 2][y - 2] == 2 && this->if_w[x + 3][y - 3] == 2 && this->if_w[x + 4][y - 4] == 2 && this->if_w[x + 5][y - 5] == 1)
                            this->W_weight[m][n] += 3500;
                        //0222021
                        if (this->if_w[x][y] == 0 && this->if_w[x + 1][y - 1] == 2 && this->if_w[x + 2][y - 2] == 2 && this->if_w[x + 3][y - 3] == 2 && this->if_w[x + 4][y - 4] == 0 && this->if_w[x + 5][y - 5] == 2 && this->if_w[x + 6][y - 6] == 1)
                            this->W_weight[m][n] += 3500;
                        //0220221
                        if (this->if_w[x][y] == 0 && this->if_w[x + 1][y - 1] == 2 && this->if_w[x + 2][y - 2] == 2 && this->if_w[x + 3][y - 3] == 0 && this->if_w[x + 4][y - 4] == 2 && this->if_w[x + 5][y - 5] == 2 && this->if_w[x + 6][y - 6] == 1)
                            this->W_weight[m][n] += 3500;
                        //0202221
                        if (this->if_w[x][y] == 0 && this->if_w[x + 1][y - 1] == 2 && this->if_w[x + 2][y - 2] == 0 && this->if_w[x + 3][y - 3] == 2 && this->if_w[x + 4][y - 4] == 2 && this->if_w[x + 5][y - 5] == 2 && this->if_w[x + 6][y - 6] == 1)
                            this->W_weight[m][n] += 3500;
                        //0222201
                        if (this->if_w[x][y] == 0 && this->if_w[x + 1][y - 1] == 2 && this->if_w[x + 2][y - 2] == 2 && this->if_w[x + 3][y - 3] == 2 && this->if_w[x + 4][y - 4] == 2 && this->if_w[x + 5][y - 5] == 0 && this->if_w[x + 6][y - 6] == 1)
                            this->W_weight[m][n] += 3500;
                        //02220021
                        if (this->if_w[x][y] == 0 && this->if_w[x + 1][y - 1] == 2 && this->if_w[x + 2][y - 2] == 2 && this->if_w[x + 3][y - 3] == 2 && this->if_w[x + 4][y - 4] == 0 && this->if_w[x + 5][y - 5] == 0 && this->if_w[x + 6][y - 6] == 2 &&
                            this->if_w[x + 7][y - 7] == 1)
                            this->W_weight[m][n] += 3500;
                        //02202021
                        if (this->if_w[x][y] == 0 && this->if_w[x + 1][y - 1] == 2 && this->if_w[x + 2][y - 2] == 2 && this->if_w[x + 3][y - 3] == 0 && this->if_w[x + 4][y - 4] == 2 && this->if_w[x + 5][y - 5] == 0 && this->if_w[x + 6][y - 6] == 2 &&
                            this->if_w[x + 7][y - 7] == 1)
                            this->W_weight[m][n] += 3500;
                        //02022021
                        if (this->if_w[x][y] == 0 && this->if_w[x + 1][y - 1] == 2 && this->if_w[x + 2][y - 2] == 0 && this->if_w[x + 3][y - 3] == 2 && this->if_w[x + 4][y - 4] == 2 && this->if_w[x + 5][y - 5] == 0 && this->if_w[x + 6][y - 6] == 2 &&
                            this->if_w[x + 7][y - 7] == 1)
                            this->W_weight[m][n] += 3500;
                        //02200221
                        if (this->if_w[x][y] == 0 && this->if_w[x + 1][y - 1] == 2 && this->if_w[x + 2][y - 2] == 2 && this->if_w[x + 3][y - 3] == 0 && this->if_w[x + 4][y - 4] == 0 && this->if_w[x + 5][y - 5] == 2 && this->if_w[x + 6][y - 6] == 2 &&
                            this->if_w[x + 7][y - 7] == 1)
                            this->W_weight[m][n] += 3500;
                        //02020221
                        if (this->if_w[x][y] == 0 && this->if_w[x + 1][y - 1] == 2 && this->if_w[x + 2][y - 2] == 0 && this->if_w[x + 3][y - 3] == 2 && this->if_w[x + 4][y - 4] == 0 && this->if_w[x + 5][y - 5] == 2 && this->if_w[x + 6][y - 6] == 2 &&
                            this->if_w[x + 7][y - 7] == 1)
                            this->W_weight[m][n] += 3500;
                        //02002221
                        if (this->if_w[x][y] == 0 && this->if_w[x + 1][y - 1] == 2 && this->if_w[x + 2][y - 2] == 0 && this->if_w[x + 3][y - 3] == 0 && this->if_w[x + 4][y - 4] == 2 && this->if_w[x + 5][y - 5] == 2 && this->if_w[x + 6][y - 6] == 2 &&
                            this->if_w[x + 7][y - 7] == 1)
                            this->W_weight[m][n] += 3500;
                        //02202201
                        if (this->if_w[x][y] == 0 && this->if_w[x + 1][y - 1] == 2 && this->if_w[x + 2][y - 2] == 2 && this->if_w[x + 3][y - 3] == 0 && this->if_w[x + 4][y - 4] == 2 && this->if_w[x + 5][y - 5] == 2 && this->if_w[x + 6][y - 6] == 0 &&
                            this->if_w[x + 7][y - 7] == 1)
                            this->W_weight[m][n] += 3500;
                        //02022201
                        if (this->if_w[x][y] == 0 && this->if_w[x + 1][y - 1] == 2 && this->if_w[x + 2][y - 2] == 0 && this->if_w[x + 3][y - 3] == 2 && this->if_w[x + 4][y - 4] == 2 && this->if_w[x + 5][y - 5] == 2 && this->if_w[x + 6][y - 6] == 0 &&
                            this->if_w[x + 7][y - 7] == 1)
                            this->W_weight[m][n] += 3500;
                        //02220201
                        if (this->if_w[x][y] == 0 && this->if_w[x + 1][y - 1] == 2 && this->if_w[x + 2][y - 2] == 2 && this->if_w[x + 3][y - 3] == 2 && this->if_w[x + 4][y - 4] == 0 && this->if_w[x + 5][y - 5] == 2 && this->if_w[x + 6][y - 6] == 0 &&
                            this->if_w[x + 7][y - 7] == 1)
                            this->W_weight[m][n] += 3500;



                        //양쪽 다 막혔을 때

                        //12022021
                        if (this->if_w[x][y] == 1 && this->if_w[x + 1][y - 1] == 2 && this->if_w[x + 2][y - 2] == 0 && this->if_w[x + 3][y - 3] == 2 && this->if_w[x + 4][y - 4] == 2 && this->if_w[x + 5][y - 5] == 0 && this->if_w[x + 6][y - 6] == 2 && this->if_w[x + 7][y - 7] == 1)
                            this->W_weight[m][n] += 1000;
                        //12200221
                        if (this->if_w[x][y] == 1 && this->if_w[x + 1][y - 1] == 2 && this->if_w[x + 2][y - 2] == 2 && this->if_w[x + 3][y - 3] == 0 && this->if_w[x + 4][y - 4] == 0 && this->if_w[x + 5][y - 5] == 2 && this->if_w[x + 6][y - 6] == 2 && this->if_w[x + 7][y - 7] == 1)
                            this->W_weight[m][n] += 1000;
                        //12220021
                        if (this->if_w[x][y] == 1 && this->if_w[x + 1][y - 1] == 2 && this->if_w[x + 2][y - 2] == 2 && this->if_w[x + 3][y - 3] == 2 && this->if_w[x + 4][y - 4] == 0 && this->if_w[x + 5][y - 5] == 0 && this->if_w[x + 6][y - 6] == 2 && this->if_w[x + 7][y - 7] == 1)
                            this->W_weight[m][n] += 1000;
                        //12002221
                        if (this->if_w[x][y] == 1 && this->if_w[x + 1][y - 1] == 2 && this->if_w[x + 2][y - 2] == 0 && this->if_w[x + 3][y - 3] == 0 && this->if_w[x + 4][y - 4] == 2 && this->if_w[x + 5][y - 5] == 2 && this->if_w[x + 6][y - 6] == 2 && this->if_w[x + 7][y - 7] == 1)
                            this->W_weight[m][n] += 1000;
                        //12202021
                        if (this->if_w[x][y] == 1 && this->if_w[x + 1][y - 1] == 2 && this->if_w[x + 2][y - 2] == 2 && this->if_w[x + 3][y - 3] == 0 && this->if_w[x + 4][y - 4] == 2 && this->if_w[x + 5][y - 5] == 2 && this->if_w[x + 6][y - 6] == 2 && this->if_w[x + 7][y - 7] == 1)
                            this->W_weight[m][n] += 1000;
                        //12020221
                        if (this->if_w[x][y] == 1 && this->if_w[x + 1][y - 1] == 2 && this->if_w[x + 2][y - 2] == 0 && this->if_w[x + 3][y - 3] == 2 && this->if_w[x + 4][y - 4] == 0 && this->if_w[x + 5][y - 5] == 2 && this->if_w[x + 6][y - 6] == 2 && this->if_w[x + 7][y - 7] == 1)
                            this->W_weight[m][n] += 1000;
                        //10222201
                        if (this->if_w[x][y] == 1 && this->if_w[x + 1][y - 1] == 0 && this->if_w[x + 2][y - 2] == 2 && this->if_w[x + 3][y - 3] == 2 && this->if_w[x + 4][y - 4] == 2 && this->if_w[x + 5][y - 5] == 2 && this->if_w[x + 6][y - 6] == 0 && this->if_w[x + 7][y - 7] == 1)
                            this->W_weight[m][n] += 1000;
                        //10222021
                        if (this->if_w[x][y] == 1 && this->if_w[x + 1][y - 1] == 0 && this->if_w[x + 2][y - 2] == 2 && this->if_w[x + 3][y - 3] == 2 && this->if_w[x + 4][y - 4] == 2 && this->if_w[x + 5][y - 5] == 0 && this->if_w[x + 6][y - 6] == 2 && this->if_w[x + 7][y - 7] == 1)
                            this->W_weight[m][n] += 1000;
                        //10220221
                        if (this->if_w[x][y] == 1 && this->if_w[x + 1][y - 1] == 0 && this->if_w[x + 2][y - 2] == 2 && this->if_w[x + 3][y - 3] == 2 && this->if_w[x + 4][y - 4] == 0 && this->if_w[x + 5][y - 5] == 2 && this->if_w[x + 6][y - 6] == 2 && this->if_w[x + 7][y - 7] == 1)
                            this->W_weight[m][n] += 1000;
                        //10202221
                        if (this->if_w[x][y] == 1 && this->if_w[x + 1][y - 1] == 0 && this->if_w[x + 2][y - 2] == 2 && this->if_w[x + 3][y - 3] == 0 && this->if_w[x + 4][y - 4] == 2 && this->if_w[x + 5][y - 5] == 2 && this->if_w[x + 6][y - 6] == 2 && this->if_w[x + 7][y - 7] == 1)
                            this->W_weight[m][n] += 1000;
                        //10022221
                        if (this->if_w[x][y] == 1 && this->if_w[x + 1][y - 1] == 0 && this->if_w[x + 2][y - 2] == 0 && this->if_w[x + 3][y - 3] == 2 && this->if_w[x + 4][y - 4] == 2 && this->if_w[x + 5][y - 5] == 2 && this->if_w[x + 6][y - 6] == 2 && this->if_w[x + 7][y - 7] == 1)
                            this->W_weight[m][n] += 1000;
                        //12022201
                        if (this->if_w[x][y] == 1 && this->if_w[x + 1][y - 1] == 2 && this->if_w[x + 2][y - 2] == 0 && this->if_w[x + 3][y - 3] == 2 && this->if_w[x + 4][y - 4] == 2 && this->if_w[x + 5][y - 5] == 2 && this->if_w[x + 6][y - 6] == 0 && this->if_w[x + 7][y - 7] == 1)
                            this->W_weight[m][n] += 1000;
                        //12202201
                        if (this->if_w[x][y] == 1 && this->if_w[x + 1][y - 1] == 2 && this->if_w[x + 2][y - 2] == 2 && this->if_w[x + 3][y - 3] == 0 && this->if_w[x + 4][y - 4] == 2 && this->if_w[x + 5][y - 5] == 2 && this->if_w[x + 6][y - 6] == 0 && this->if_w[x + 7][y - 7] == 1)
                            this->W_weight[m][n] += 1000;
                        //12220201
                        if (this->if_w[x][y] == 1 && this->if_w[x + 1][y - 1] == 2 && this->if_w[x + 2][y - 2] == 2 && this->if_w[x + 3][y - 3] == 2 && this->if_w[x + 4][y - 4] == 0 && this->if_w[x + 5][y - 5] == 2 && this->if_w[x + 6][y - 6] == 0 && this->if_w[x + 7][y - 7] == 1)
                            this->W_weight[m][n] += 1000;
                        //12222001
                        if (this->if_w[x][y] == 1 && this->if_w[x + 1][y - 1] == 2 && this->if_w[x + 2][y - 2] == 2 && this->if_w[x + 3][y - 3] == 2 && this->if_w[x + 4][y - 4] == 2 && this->if_w[x + 5][y - 5] == 0 && this->if_w[x + 6][y - 6] == 0 && this->if_w[x + 7][y - 7] == 1)
                            this->W_weight[m][n] += 1000;
                    }
                }
                this->if_w[m][n] = 0;
            }
        }
}

void AI::defense_Horizontal_check_W()
{
    for(int m=0 ; m<19 ; m++)
        {
            for(int n=0 ; n<19 ; n++)
            {
                if( if_w[m][n] == 0 )
                {
                    if_w[m][n] = 2;
                }
                else if( if_w[m][n] == 1 || if_w[m][n] == 2 )
                {
                    continue;
                }

                for(int x=0; x<19; x++)
                {
                    for(int y=0; y<19; y++)
                    {
                        //다섯개에 양쪽다 막도록.
                        //2111112 이런상황이 되게 할때 점수가 높이 준다.
                        if( if_w[x][y] == 2 && if_w[x][y+1] == 1 && if_w[x][y+2] == 1 && if_w[x][y+3] == 1 && if_w[x][y+4] == 1 &&
                            if_w[x][y+5] == 1 && if_w[x][y+6] == 2 )
                            W_weight[m][n] += 750000;
                        //2111110
                        if( if_w[x][y] == 2 && if_w[x][y+1] == 1 && if_w[x][y+2] == 1 && if_w[x][y+3] == 1 && if_w[x][y+4] == 1 &&
                            if_w[x][y+5] == 1 && if_w[x][y+6] == 0 )
                            W_weight[m][n] += 500000;
                        //0111112
                        if( if_w[x][y] == 0 && if_w[x][y+1] == 1 && if_w[x][y+2] == 1 && if_w[x][y+3] == 1 && if_w[x][y+4] == 1 &&
                            if_w[x][y+5] == 1 && if_w[x][y+6] == 2 )
                            W_weight[m][n] += 500000;
                        //121111
                        if( if_w[x][y] == 1 && if_w[x][y+1] == 2 && if_w[x][y+2] == 1 && if_w[x][y+3] == 1 && if_w[x][y+4] == 1 &&
                            if_w[x][y+5] == 1 )
                            W_weight[m][n] += 500000;
                        //112111
                        if( if_w[x][y] == 1 && if_w[x][y+1] == 1 && if_w[x][y+2] == 2 && if_w[x][y+3] == 1 && if_w[x][y+4] == 1 &&
                            if_w[x][y+5] == 1 )
                            W_weight[m][n] += 500000;
                        //111211
                        if( if_w[x][y] == 1 && if_w[x][y+1] == 1 && if_w[x][y+2] == 1 && if_w[x][y+3] == 2 && if_w[x][y+4] == 1 &&
                            if_w[x][y+5] == 1 )
                            W_weight[m][n] += 500000;
                        //111121
                        if( if_w[x][y] == 1 && if_w[x][y+1] == 1 && if_w[x][y+2] == 1 && if_w[x][y+3] == 1 && if_w[x][y+4] == 2 &&
                            if_w[x][y+5] == 1 )
                            W_weight[m][n] += 500000;

                        //추가부분 상대방 4개짜리 사이 빈칸있을때 사이 막기
                        //202122
                        if( if_w[x][y] == 1 && if_w[x][y+1] == 0 && if_w[x][y+2] == 1 && if_w[x][y+3] == 2 && if_w[x][y+4] == 1 &&
                            if_w[x][y+5] == 1 )
                            W_weight[m][n] += 500000;
                        //202212
                        if( if_w[x][y] == 1 && if_w[x][y+1] == 0 && if_w[x][y+2] == 1 && if_w[x][y+3] == 1 && if_w[x][y+4] == 2 &&
                            if_w[x][y+5] == 1 )
                            W_weight[m][n] += 500000;
                        //212022
                        if( if_w[x][y] == 1 && if_w[x][y+1] == 2 && if_w[x][y+2] == 1 && if_w[x][y+3] == 0 && if_w[x][y+4] == 1 &&
                            if_w[x][y+5] == 1 )
                            W_weight[m][n] += 500000;
                        //212202
                        if( if_w[x][y] == 1 && if_w[x][y+1] == 2 && if_w[x][y+2] == 1 && if_w[x][y+3] == 1 && if_w[x][y+4] == 0 &&
                            if_w[x][y+5] == 1 )
                            W_weight[m][n] += 500000;
                        //221202
                        if( if_w[x][y] == 1 && if_w[x][y+1] == 1 && if_w[x][y+2] == 2 && if_w[x][y+3] == 1 && if_w[x][y+4] == 0 &&
                            if_w[x][y+5] == 1 )
                            W_weight[m][n] += 500000;
                        //220212
                        if( if_w[x][y] == 1 && if_w[x][y+1] == 1 && if_w[x][y+2] == 0 && if_w[x][y+3] == 1 && if_w[x][y+4] == 2 &&
                            if_w[x][y+5] == 1 )
                            W_weight[m][n] += 500000;

                        //211112
                        if( if_w[x][y] == 2 && if_w[x][y+1] == 1 && if_w[x][y+2] == 1 && if_w[x][y+3] == 1 && if_w[x][y+4] == 1 &&
                            if_w[x][y+5] == 2 )
                            W_weight[m][n] += 500000;

                        //211110
                        if( if_w[x][y] == 2 && if_w[x][y+1] == 1 && if_w[x][y+2] == 1 && if_w[x][y+3] == 1 && if_w[x][y+4] == 1 &&
                            if_w[x][y+5] == 0 )
                            W_weight[m][n] += 500000;
                        //011112
                        if( if_w[x][y] == 0 && if_w[x][y+1] == 1 && if_w[x][y+2] == 1 && if_w[x][y+3] == 1 && if_w[x][y+4] == 1 &&
                            if_w[x][y+5] == 2)
                            W_weight[m][n] += 500000;
                        //2111102
                        if( if_w[x][y] == 2 && if_w[x][y+1] == 1 && if_w[x][y+2] == 1 && if_w[x][y+3] == 1 && if_w[x][y+4] == 1 &&
                            if_w[x][y+5] == 0 && if_w[x][y+6] == 2 )
                            W_weight[m][n] += 500000;
                        //2011112
                        if( if_w[x][y] == 2 && if_w[x][y+1] == 0 && if_w[x][y+2] == 1 && if_w[x][y+3] == 1 && if_w[x][y+4] == 1 &&
                            if_w[x][y+5] == 1 && if_w[x][y+6] == 2 )
                            W_weight[m][n] += 500000;

                        //x12111x
                        if( if_w[x][y+1] == 1 && if_w[x][y+2] == 2 && if_w[x][y+3] == 1 && if_w[x][y+4] == 1 &&
                            if_w[x][y+5] == 1 && if_w[x][y+6] != 2 )
                            W_weight[m][n] += 500000;
                        //x11211x
                        if( if_w[x][y+1] == 1 && if_w[x][y+2] == 1 && if_w[x][y+3] == 2 && if_w[x][y+4] == 1 &&
                            if_w[x][y+5] == 1 && if_w[x][y+6] != 2 )
                            W_weight[m][n] += 500000;
                        //x11121x
                        if( if_w[x][y+1] == 1 && if_w[x][y+2] == 1 && if_w[x][y+3] == 1 && if_w[x][y+4] == 2 &&
                            if_w[x][y+5] == 1 && if_w[x][y+6] != 2 )
                            W_weight[m][n] += 500000;
                        //x12111x
                        if( if_w[x][y] != 2 && if_w[x][y+1] == 1 && if_w[x][y+2] == 2 && if_w[x][y+3] == 1 && if_w[x][y+4] == 1 &&
                            if_w[x][y+5] == 1 )
                            W_weight[m][n] += 500000;
                        //x11211x
                        if( if_w[x][y] != 2 && if_w[x][y+1] == 1 && if_w[x][y+2] == 1 && if_w[x][y+3] == 2 && if_w[x][y+4] == 1 &&
                            if_w[x][y+5] == 1 )
                            W_weight[m][n] += 500000;
                        //x11121x
                        if( if_w[x][y] != 2 && if_w[x][y+1] == 1 && if_w[x][y+2] == 1 && if_w[x][y+3] == 1 && if_w[x][y+4] == 2 &&
                            if_w[x][y+5] == 1 )
                            W_weight[m][n] += 500000;

                        //120111
                        if( if_w[x][y] == 1 && if_w[x][y+1] == 2 && if_w[x][y+2] == 0 && if_w[x][y+3] == 1 && if_w[x][y+4] == 1 &&
                            if_w[x][y+5] == 1 )
                            W_weight[m][n] += 500000;
                        //102111
                        if( if_w[x][y] == 1 && if_w[x][y+1] == 0 && if_w[x][y+2] == 2 && if_w[x][y+3] == 1 && if_w[x][y+4] == 1 &&
                            if_w[x][y+5] == 1 )
                            W_weight[m][n] += 500000;
                        //111201
                        if( if_w[x][y] == 1 && if_w[x][y+1] == 1 && if_w[x][y+2] == 1 && if_w[x][y+3] == 2 && if_w[x][y+4] == 0 &&
                            if_w[x][y+5] == 1 )
                            W_weight[m][n] += 500000;
                        //111021
                        if( if_w[x][y] == 1 && if_w[x][y+1] == 1 && if_w[x][y+2] == 1 && if_w[x][y+3] == 0 && if_w[x][y+4] == 2 &&
                            if_w[x][y+5] == 1 )
                            W_weight[m][n] += 500000;
                        //112011
                        if( if_w[x][y] == 1 && if_w[x][y+1] == 1 && if_w[x][y+2] == 2 && if_w[x][y+3] == 0 && if_w[x][y+4] == 1 &&
                            if_w[x][y+5] == 1 )
                            W_weight[m][n] += 500000;
                        //110211
                        if( if_w[x][y] == 1 && if_w[x][y+1] == 1 && if_w[x][y+2] == 0 && if_w[x][y+3] == 2 && if_w[x][y+4] == 1 &&
                            if_w[x][y+5] == 1 )
                            W_weight[m][n] += 500000;



                        //여기서부터 간단한 가중치 줄 것. 즉, 2개 3개 막게하는것들
                        //2111
                        if( if_w[x][y] == 2 && if_w[x][y+1] == 1 && if_w[x][y+2] == 1 && if_w[x][y+3] == 1 )
                            W_weight[m][n] += 3500;
                        //1112
                        if( if_w[x][y] == 1 && if_w[x][y+1] == 1 && if_w[x][y+2] == 1 && if_w[x][y+3] == 2 )
                            W_weight[m][n] += 3500;
                        //1211
                        if( if_w[x][y] == 1 && if_w[x][y+1] == 2 && if_w[x][y+2] == 1 && if_w[x][y+3] == 1 )
                            W_weight[m][n] += 4000;
                        //1121
                        if( if_w[x][y] == 1 && if_w[x][y+1] == 1 && if_w[x][y+2] == 2 && if_w[x][y+3] == 1 )
                            W_weight[m][n] += 4000;
                        //11102		분기해서 막는것도 필요한 경우가 있을수있음. 단 점수는 낮게
                        if( if_w[x][y] == 1 && if_w[x][y+1] == 1 && if_w[x][y+2] == 1 && if_w[x][y+3] == 0 && if_w[x][y+4] == 2 )
                            W_weight[m][n] += 1500;
                        //20111
                        if( if_w[x][y] == 2 && if_w[x][y+1] == 0 && if_w[x][y+2] == 1 && if_w[x][y+3] == 1 && if_w[x][y+4] == 1 )
                            W_weight[m][n] += 1500;

                        //21011		점수낮게
                        if( if_w[x][y] == 2 && if_w[x][y+1] == 1 && if_w[x][y+2] == 0 && if_w[x][y+3] == 1 && if_w[x][y+4] == 1 )
                            W_weight[m][n] += 1500;
                        //21101		점수낮게
                        if( if_w[x][y] == 2 && if_w[x][y+1] == 1 && if_w[x][y+2] == 1 && if_w[x][y+3] == 0 && if_w[x][y+4] == 1 )
                            W_weight[m][n] += 1500;
                        //10112		점수낮게
                        if( if_w[x][y] == 1 && if_w[x][y+1] == 0 && if_w[x][y+2] == 1 && if_w[x][y+3] == 1 && if_w[x][y+4] == 2 )
                            W_weight[m][n] += 1500;
                        //11012		점수낮게
                        if( if_w[x][y] == 1 && if_w[x][y+1] == 1 && if_w[x][y+2] == 0 && if_w[x][y+3] == 1 && if_w[x][y+4] == 2 )
                            W_weight[m][n] += 1500;

                        //211
                        if( if_w[x][y] == 2 && if_w[x][y+1] == 1 && if_w[x][y+2] == 1 )
                            W_weight[m][n] += 500;
                        //112
                        if( if_w[x][y] == 1 && if_w[x][y+1] == 1 && if_w[x][y+2] == 2 )
                            W_weight[m][n] += 500;
                        //121
                        if( if_w[x][y] == 1 && if_w[x][y+1] == 2 && if_w[x][y+2] == 1 )
                            W_weight[m][n] += 800;
                    }
                }
                if_w[m][n] = 0;
            }
        }
}

void AI::defense_Vertical_check_W()
{
    for(int m=0 ; m<19 ; m++)
    {
        for(int n=0 ; n<19 ; n++)
        {
            if( if_w[m][n] == 0 )
            {
                if_w[m][n] = 2;
            }
            else if( if_w[m][n] == 1 || if_w[m][n] == 2 )
            {
                continue;
            }

            for(int x=0; x<19; x++)
            {
                for(int y=0; y<19; y++)
                {
                    //다섯개에 양쪽다 막도록.
                    //2111112 이런상황이 되게 할때 점수가 높이 준다.
                    if( if_w[x][y] == 2 && if_w[x+1][y] == 1 && if_w[x+2][y] == 1 && if_w[x+3][y] == 1 && if_w[x+4][y] == 1 &&
                        if_w[x+5][y] == 1 && if_w[x+6][y] == 2 )
                        W_weight[m][n] += 750000;
                    //2111110
                    if( if_w[x][y] == 2 && if_w[x+1][y] == 1 && if_w[x+2][y] == 1 && if_w[x+3][y] == 1 && if_w[x+4][y] == 1 &&
                        if_w[x+5][y] == 1 && if_w[x+6][y] == 0 )
                        W_weight[m][n] += 500000;
                    //0111112
                    if( if_w[x][y] == 0 && if_w[x+1][y] == 1 && if_w[x+2][y] == 1 && if_w[x+3][y] == 1 && if_w[x+4][y] == 1 &&
                        if_w[x+5][y] == 1 && if_w[x+6][y] == 2 )
                        W_weight[m][n] += 500000;
                    //121111
                    if( if_w[x][y] == 1 && if_w[x+1][y] == 2 && if_w[x+2][y] == 1 && if_w[x+3][y] == 1 && if_w[x+4][y] == 1 &&
                        if_w[x+5][y] == 1 )
                        W_weight[m][n] += 500000;
                    //112111
                    if( if_w[x][y] == 1 && if_w[x+1][y] == 1 && if_w[x+2][y] == 2 && if_w[x+3][y] == 1 && if_w[x+4][y] == 1 &&
                        if_w[x+5][y] == 1 )
                        W_weight[m][n] += 500000;
                    //111211
                    if( if_w[x][y] == 1 && if_w[x+1][y] == 1 && if_w[x+2][y] == 1 && if_w[x+3][y] == 2 && if_w[x+4][y] == 1 &&
                        if_w[x+5][y] == 1 )
                        W_weight[m][n] += 500000;
                    //111121
                    if( if_w[x][y] == 1 && if_w[x+1][y] == 1 && if_w[x+2][y] == 1 && if_w[x+3][y] == 1 && if_w[x+4][y] == 2 &&
                        if_w[x+5][y] == 1 )
                        W_weight[m][n] += 500000;

                    //추가부분 상대방 4개짜리 사이 빈칸있을때 사이 막기
                    //202122
                    if( if_w[x][y] == 1 && if_w[x+1][y] == 0 && if_w[x+2][y] == 1 && if_w[x+3][y] == 2 && if_w[x+4][y] == 1 &&
                        if_w[x+5][y] == 1 )
                        W_weight[m][n] += 500000;
                    //202212
                    if( if_w[x][y] == 1 && if_w[x+1][y] == 0 && if_w[x+2][y] == 1 && if_w[x+3][y] == 1 && if_w[x+4][y] == 2 &&
                        if_w[x+5][y] == 1 )
                        W_weight[m][n] += 500000;
                    //212022
                    if( if_w[x][y] == 1 && if_w[x+1][y] == 2 && if_w[x+2][y] == 1 && if_w[x+3][y] == 0 && if_w[x+4][y] == 1 &&
                        if_w[x+5][y] == 1 )
                        W_weight[m][n] += 500000;
                    //212202
                    if( if_w[x][y] == 1 && if_w[x+1][y] == 2 && if_w[x+2][y] == 1 && if_w[x+3][y] == 1 && if_w[x+4][y] == 0 &&
                        if_w[x+5][y] == 1 )
                        W_weight[m][n] += 500000;
                    //221202
                    if( if_w[x][y] == 1 && if_w[x+1][y] == 1 && if_w[x+2][y] == 2 && if_w[x+3][y] == 1 && if_w[x+4][y] == 0 &&
                        if_w[x+5][y] == 1 )
                        W_weight[m][n] += 500000;
                    //220212
                    if( if_w[x][y] == 1 && if_w[x+1][y] == 1 && if_w[x+2][y] == 0 && if_w[x+3][y] == 1 && if_w[x+4][y] == 2 &&
                        if_w[x+5][y] == 1 )
                        W_weight[m][n] += 500000;

                    //211112
                    if( if_w[x][y] == 2 && if_w[x+1][y] == 1 && if_w[x+2][y] == 1 && if_w[x+3][y] == 1 && if_w[x+4][y] == 1 &&
                        if_w[x+5][y] == 2 )
                        W_weight[m][n] += 500000;
                    //211110
                    if( if_w[x][y] == 2 && if_w[x+1][y] == 1 && if_w[x+2][y] == 1 && if_w[x+3][y] == 1 && if_w[x+4][y] == 1 &&
                        if_w[x+5][y] == 0 )
                        W_weight[m][n] += 500000;
                    //011112
                    if( if_w[x][y] == 0 && if_w[x+1][y] == 1 && if_w[x+2][y] == 1 && if_w[x+3][y] == 1 && if_w[x+4][y] == 1 &&
                        if_w[x+5][y] == 2)
                        W_weight[m][n] += 500000;
                    //2111102
                    if( if_w[x][y] == 2 && if_w[x+1][y] == 1 && if_w[x+2][y] == 1 && if_w[x+3][y] == 1 && if_w[x+4][y] == 1 &&
                        if_w[x+5][y] == 0 && if_w[x+6][y] == 2 )
                        W_weight[m][n] += 500000;
                    //2011112
                    if( if_w[x][y] == 2 && if_w[x+1][y] == 0 && if_w[x+2][y] == 1 && if_w[x+3][y] == 1 && if_w[x+4][y] == 1 &&
                        if_w[x+5][y] == 1 && if_w[x+6][y] == 2 )
                        W_weight[m][n] += 500000;

                    //x12111x
                    if( if_w[x+1][y] == 1 && if_w[x+2][y] == 2 && if_w[x+3][y] == 1 && if_w[x+4][y] == 1 &&
                        if_w[x+5][y] == 1 && if_w[x+6][y] != 2 )
                        W_weight[m][n] += 500000;
                    //x11211x
                    if( if_w[x+1][y] == 1 && if_w[x+2][y] == 1 && if_w[x+3][y] == 2 && if_w[x+4][y] == 1 &&
                        if_w[x+5][y] == 1 && if_w[x+6][y] != 2 )
                        W_weight[m][n] += 500000;
                    //x11121x
                    if( if_w[x+1][y] == 1 && if_w[x+2][y] == 1 && if_w[x+3][y] == 1 && if_w[x+4][y] == 2 &&
                        if_w[x+5][y] == 1 && if_w[x+6][y] != 2 )
                        W_weight[m][n] += 500000;
                    //x12111x
                    if( if_w[x][y] != 2 && if_w[x+1][y] == 1 && if_w[x+2][y] == 2 && if_w[x+3][y] == 1 && if_w[x+4][y] == 1 &&
                        if_w[x+5][y] == 1 )
                        W_weight[m][n] += 500000;
                    //x11211x
                    if( if_w[x][y] != 2 && if_w[x+1][y] == 1 && if_w[x+2][y] == 1 && if_w[x+3][y] == 2 && if_w[x+4][y] == 1 &&
                        if_w[x+5][y] == 1 )
                        W_weight[m][n] += 500000;
                    //x11121x
                    if( if_w[x][y] != 2 && if_w[x+1][y] == 1 && if_w[x+2][y] == 1 && if_w[x+3][y] == 1 && if_w[x+4][y] == 2 &&
                        if_w[x+5][y] == 1 )
                        W_weight[m][n] += 500000;

                    //120111
                    if( if_w[x][y] == 1 && if_w[x+1][y] == 2 && if_w[x+2][y] == 0 && if_w[x+3][y] == 1 && if_w[x+4][y] == 1 &&
                        if_w[x+5][y] == 1 )
                        W_weight[m][n] += 500000;
                    //102111
                    if( if_w[x][y] == 1 && if_w[x+1][y] == 0 && if_w[x+2][y] == 2 && if_w[x+3][y] == 1 && if_w[x+4][y] == 1 &&
                        if_w[x+5][y] == 1 )
                        W_weight[m][n] += 500000;
                    //111201
                    if( if_w[x][y] == 1 && if_w[x+1][y] == 1 && if_w[x+2][y] == 1 && if_w[x+3][y] == 2 && if_w[x+4][y] == 0 &&
                        if_w[x+5][y] == 1 )
                        W_weight[m][n] += 500000;
                    //111021
                    if( if_w[x][y] == 1 && if_w[x+1][y] == 1 && if_w[x+2][y] == 1 && if_w[x+3][y] == 0 && if_w[x+4][y] == 2 &&
                        if_w[x+5][y] == 1 )
                        W_weight[m][n] += 500000;
                    //112011
                    if( if_w[x][y] == 1 && if_w[x+1][y] == 1 && if_w[x+2][y] == 2 && if_w[x+3][y] == 0 && if_w[x+4][y] == 1 &&
                        if_w[x+5][y] == 1 )
                        W_weight[m][n] += 500000;
                    //110211
                    if( if_w[x][y] == 1 && if_w[x+1][y] == 1 && if_w[x+2][y] == 0 && if_w[x+3][y] == 2 && if_w[x+4][y] == 1 &&
                        if_w[x+5][y] == 1 )
                        W_weight[m][n] += 500000;

                    //여기서부터 간단한 가중치 줄 것. 즉, 2개 3개 막게하는것들
                    //2111
                    if( if_w[x][y] == 2 && if_w[x+1][y] == 1 && if_w[x+2][y] == 1 && if_w[x+3][y] == 1 )
                        W_weight[m][n] += 3500;
                    //1112
                    if( if_w[x][y] == 1 && if_w[x+1][y] == 1 && if_w[x+2][y] == 1 && if_w[x+3][y] == 2 )
                        W_weight[m][n] += 3500;
                    //1211
                    if( if_w[x][y] == 1 && if_w[x+1][y] == 2 && if_w[x+2][y] == 1 && if_w[x+3][y] == 1 )
                        W_weight[m][n] += 4000;
                    //1121
                    if( if_w[x][y] == 1 && if_w[x+1][y] == 1 && if_w[x+2][y] == 2 && if_w[x+3][y] == 1 )
                        W_weight[m][n] += 4000;
                    //11102		분기해서 막는것도 필요한 경우가 있을수있음. 단 점수는 낮게
                    if( if_w[x][y] == 1 && if_w[x+1][y] == 1 && if_w[x+2][y] == 1 && if_w[x+3][y] == 0 && if_w[x+4][y] == 2 )
                        W_weight[m][n] += 1500;
                    //20111
                    if( if_w[x][y] == 2 && if_w[x+1][y] == 0 && if_w[x+2][y] == 1 && if_w[x+3][y] == 1 && if_w[x+4][y] == 1 )
                        W_weight[m][n] += 1500;

                    //21011		점수낮게
                    if( if_w[x][y] == 2 && if_w[x+1][y] == 1 && if_w[x+2][y] == 0 && if_w[x+3][y] == 1 && if_w[x+4][y] == 1 )
                        W_weight[m][n] += 1500;
                    //21101		점수낮게
                    if( if_w[x][y] == 2 && if_w[x+1][y] == 1 && if_w[x+2][y] == 1 && if_w[x+3][y] == 0 && if_w[x+4][y] == 1 )
                        W_weight[m][n] += 1500;
                    //10112		점수낮게
                    if( if_w[x][y] == 1 && if_w[x+1][y] == 0 && if_w[x+2][y] == 1 && if_w[x+3][y] == 1 && if_w[x+4][y] == 2 )
                        W_weight[m][n] += 1500;
                    //11012		점수낮게
                    if( if_w[x][y] == 1 && if_w[x+1][y] == 1 && if_w[x+2][y] == 0 && if_w[x+3][y] == 1 && if_w[x+4][y] == 2 )
                        W_weight[m][n] += 1500;

                    //211
                    if( if_w[x][y] == 2 && if_w[x+1][y] == 1 && if_w[x+2][y] == 1 )
                        W_weight[m][n] += 500;
                    //112
                    if( if_w[x][y] == 1 && if_w[x+1][y] == 1 && if_w[x+2][y] == 2 )
                        W_weight[m][n] += 500;
                    //121
                    if( if_w[x][y] == 1 && if_w[x+1][y] == 2 && if_w[x+2][y] == 1 )
                        W_weight[m][n] += 800;
                }
            }
            if_w[m][n] = 0;
        }
    }
}

void AI::defense_Diagonal_check_W()
{
    for(int m=0 ; m<19 ; m++)
    {
        for(int n=0 ; n<19 ; n++)
        {
            if( if_w[m][n] == 0 )
            {
                if_w[m][n] = 2;
            }
            else if( if_w[m][n] == 1 || if_w[m][n] == 2 )
            {
                continue;
            }

            for(int x=0; x<19; x++)
            {
                for(int y=0; y<19; y++)
                {
                    //다섯개에 양쪽다 막도록.
                    //2111112 이런상황이 되게 할때 점수가 높이 준다.
                    if( if_w[x][y] == 2 && if_w[x+1][y+1] == 1 && if_w[x+2][y+2] == 1 && if_w[x+3][y+3] == 1 && if_w[x+4][y+4] == 1 &&
                        if_w[x+5][y+5] == 1 && if_w[x+6][y+6] == 2 )
                        W_weight[m][n] += 750000;
                    //2111110
                    if( if_w[x][y] == 2 && if_w[x+1][y+1] == 1 && if_w[x+2][y+2] == 1 && if_w[x+3][y+3] == 1 && if_w[x+4][y+4] == 1 &&
                        if_w[x+5][y+5] == 1 && if_w[x+6][y+6] == 0 )
                        W_weight[m][n] += 500000;
                    //0111112
                    if( if_w[x][y] == 0 && if_w[x+1][y+1] == 1 && if_w[x+2][y+2] == 1 && if_w[x+3][y+3] == 1 && if_w[x+4][y+4] == 1 &&
                        if_w[x+5][y+5] == 1 && if_w[x+6][y+6] == 2 )
                        W_weight[m][n] += 500000;
                    //121111
                    if( if_w[x][y] == 1 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 1 && if_w[x+3][y+3] == 1 && if_w[x+4][y+4] == 1 &&
                        if_w[x+5][y+5] == 1 )
                        W_weight[m][n] += 500000;
                    //112111
                    if( if_w[x][y] == 1 && if_w[x+1][y+1] == 1 && if_w[x+2][y+2] == 2 && if_w[x+3][y+3] == 1 && if_w[x+4][y+4] == 1 &&
                        if_w[x+5][y+5] == 1 )
                        W_weight[m][n] += 500000;
                    //111211
                    if( if_w[x][y] == 1 && if_w[x+1][y+1] == 1 && if_w[x+2][y+2] == 1 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] == 1 &&
                        if_w[x+5][y+5] == 1 )
                        W_weight[m][n] += 500000;
                    //111121
                    if( if_w[x][y] == 1 && if_w[x+1][y+1] == 1 && if_w[x+2][y+2] == 1 && if_w[x+3][y+3] == 1 && if_w[x+4][y+4] == 2 &&
                        if_w[x+5][y+5] == 1 )
                        W_weight[m][n] += 500000;

                    //추가부분 상대방 4개짜리 사이 빈칸있을때 사이 막기
                    //202122
                    if( if_w[x][y] == 1 && if_w[x+1][y+1] == 0 && if_w[x+2][y+2] == 1 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] == 1 &&
                        if_w[x+5][y+5] == 1 )
                        W_weight[m][n] += 500000;
                    //202212
                    if( if_w[x][y] == 1 && if_w[x+1][y+1] == 0 && if_w[x+2][y+2] == 1 && if_w[x+3][y+3] == 1 && if_w[x+4][y+4] == 2 &&
                        if_w[x+5][y+5] == 1 )
                        W_weight[m][n] += 500000;
                    //212022
                    if( if_w[x][y] == 1 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 1 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] == 1 &&
                        if_w[x+5][y+5] == 1 )
                        W_weight[m][n] += 500000;
                    //212202
                    if( if_w[x][y] == 1 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 1 && if_w[x+3][y+3] == 1 && if_w[x+4][y+4] == 0 &&
                        if_w[x+5][y+5] == 1 )
                        W_weight[m][n] += 500000;
                    //221202
                    if( if_w[x][y] == 1 && if_w[x+1][y+1] == 1 && if_w[x+2][y+2] == 2 && if_w[x+3][y+3] == 1 && if_w[x+4][y+4] == 0 &&
                        if_w[x+5][y+5] == 1 )
                        W_weight[m][n] += 500000;
                    //220212
                    if( if_w[x][y] == 1 && if_w[x+1][y+1] == 1 && if_w[x+2][y+2] == 0 && if_w[x+3][y+3] == 1 && if_w[x+4][y+4] == 2 &&
                        if_w[x+5][y+5] == 1 )
                        W_weight[m][n] += 500000;

                    //211112
                    if( if_w[x][y] == 2 && if_w[x+1][y+1] == 1 && if_w[x+2][y+2] == 1 && if_w[x+3][y+3] == 1 && if_w[x+4][y+4] == 1 &&
                        if_w[x+5][y+5] == 2 )
                        W_weight[m][n] += 500000;
                    //211110
                    if( if_w[x][y] == 2 && if_w[x+1][y+1] == 1 && if_w[x+2][y+2] == 1 && if_w[x+3][y+3] == 1 && if_w[x+4][y+4] == 1 &&
                        if_w[x+5][y+5] == 0 )
                        W_weight[m][n] += 500000;
                    //011112
                    if( if_w[x][y] == 0 && if_w[x+1][y+1] == 1 && if_w[x+2][y+2] == 1 && if_w[x+3][y+3] == 1 && if_w[x+4][y+4] == 1 &&
                        if_w[x+5][y+5] == 2)
                        W_weight[m][n] += 500000;
                    //2111102
                    if( if_w[x][y] == 2 && if_w[x+1][y+1] == 1 && if_w[x+2][y+2] == 1 && if_w[x+3][y+3] == 1 && if_w[x+4][y+4] == 1 &&
                        if_w[x+5][y+5] == 0 && if_w[x+6][y+6] == 2 )
                        W_weight[m][n] += 500000;
                    //2011112
                    if( if_w[x][y] == 2 && if_w[x+1][y+1] == 0 && if_w[x+2][y+2] == 1 && if_w[x+3][y+3] == 1 && if_w[x+4][y+4] == 1 &&
                        if_w[x+5][y+5] == 1 && if_w[x+6][y+6] == 2 )
                        W_weight[m][n] += 500000;

                    //x12111
                    if( if_w[x][y] != 2 && if_w[x+1][y+1] == 1 && if_w[x+2][y+2] == 2 && if_w[x+3][y+3] == 1 && if_w[x+4][y+4] == 1 &&
                        if_w[x+5][y+5] == 1  )
                        W_weight[m][n] += 500000;
                    //12111x
                    if( if_w[x+1][y+1] == 1 && if_w[x+2][y+2] == 2 && if_w[x+3][y+3] == 1 && if_w[x+4][y+4] == 1 &&
                        if_w[x+5][y+5] == 1 && if_w[x+6][y+6] != 2 )
                        W_weight[m][n] += 500000;
                    //x11211
                    if( if_w[x][y] != 2 && if_w[x+1][y+1] == 1 && if_w[x+2][y+2] == 1 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] == 1 &&
                        if_w[x+5][y+5] == 1 )
                        W_weight[m][n] += 500000;
                    //11211x
                    if( if_w[x+1][y+1] == 1 && if_w[x+2][y+2] == 1 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] == 1 &&
                        if_w[x+5][y+5] == 1 && if_w[x+6][y+6] != 2 )
                        W_weight[m][n] += 500000;
                    //x11121
                    if( if_w[x][y] != 2 && if_w[x+1][y+1] == 1 && if_w[x+2][y+2] == 1 && if_w[x+3][y+3] == 1 && if_w[x+4][y+4] == 2 &&
                        if_w[x+5][y+5] == 1 )
                        W_weight[m][n] += 500000;
                    //11121x
                    if( if_w[x+1][y+1] == 1 && if_w[x+2][y+2] == 1 && if_w[x+3][y+3] == 1 && if_w[x+4][y+4] == 2 &&
                        if_w[x+5][y+5] == 1 && if_w[x+6][y+6] != 2 )
                        W_weight[m][n] += 500000;


                    //120111
                    if( if_w[x][y] == 1 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 0 && if_w[x+3][y+3] == 1 && if_w[x+4][y+4] == 1 &&
                        if_w[x+5][y+5] == 1 )
                        W_weight[m][n] += 500000;
                    //102111
                    if( if_w[x][y] == 1 && if_w[x+1][y+1] == 0 && if_w[x+2][y+2] == 2 && if_w[x+3][y+3] == 1 && if_w[x+4][y+4] == 1 &&
                        if_w[x+5][y+5] == 1 )
                        W_weight[m][n] += 500000;
                    //111201
                    if( if_w[x][y] == 1 && if_w[x+1][y+1] == 1 && if_w[x+2][y+2] == 1 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] == 0 &&
                        if_w[x+5][y+5] == 1 )
                        W_weight[m][n] += 500000;
                    //111021
                    if( if_w[x][y] == 1 && if_w[x+1][y+1] == 1 && if_w[x+2][y+2] == 1 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] == 2 &&
                        if_w[x+5][y+5] == 1 )
                        W_weight[m][n] += 500000;
                    //112011
                    if( if_w[x][y] == 1 && if_w[x+1][y+1] == 1 && if_w[x+2][y+2] == 2 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] == 1 &&
                        if_w[x+5][y+5] == 1 )
                        W_weight[m][n] += 500000;
                    //110211
                    if( if_w[x][y] == 1 && if_w[x+1][y+1] == 1 && if_w[x+2][y+2] == 0 && if_w[x+3][y+3] == 2 && if_w[x+4][y+4] == 1 &&
                        if_w[x+5][y+5] == 1 )
                        W_weight[m][n] += 500000;


                    //여기서부터 간단한 가중치 줄 것. 즉, 2개 3개 막게하는것들
                    //2111
                    if( if_w[x][y] == 2 && if_w[x+1][y+1] == 1 && if_w[x+2][y+2] == 1 && if_w[x+3][y+3] == 1 )
                        W_weight[m][n] += 3500;
                    //1112
                    if( if_w[x][y] == 1 && if_w[x+1][y+1] == 1 && if_w[x+2][y+2] == 1 && if_w[x+3][y+3] == 2 )
                        W_weight[m][n] += 3500;
                    //1211
                    if( if_w[x][y] == 1 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 1 && if_w[x+3][y+3] == 1 )
                        W_weight[m][n] += 4000;
                    //1121
                    if( if_w[x][y] == 1 && if_w[x+1][y+1] == 1 && if_w[x+2][y+2] == 2 && if_w[x+3][y+3] == 1 )
                        W_weight[m][n] += 4000;
                    //11102		분기해서 막는것도 필요한 경우가 있을수있음. 단 점수는 낮게
                    if( if_w[x][y] == 1 && if_w[x+1][y+1] == 1 && if_w[x+2][y+2] == 1 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] == 2 )
                        W_weight[m][n] += 1500;
                    //20111
                    if( if_w[x][y] == 2 && if_w[x+1][y+1] == 0 && if_w[x+2][y+2] == 1 && if_w[x+3][y+3] == 1 && if_w[x+4][y+4] == 1 )
                        W_weight[m][n] += 1500;

                    //21011		점수낮게
                    if( if_w[x][y] == 2 && if_w[x+1][y+1] == 1 && if_w[x+2][y+2] == 0 && if_w[x+3][y+3] == 1 && if_w[x+4][y+4] == 1 )
                        W_weight[m][n] += 1500;
                    //21101		점수낮게
                    if( if_w[x][y] == 2 && if_w[x+1][y+1] == 1 && if_w[x+2][y+2] == 1 && if_w[x+3][y+3] == 0 && if_w[x+4][y+4] == 1 )
                        W_weight[m][n] += 1500;
                    //10112		점수낮게
                    if( if_w[x][y] == 1 && if_w[x+1][y+1] == 0 && if_w[x+2][y+2] == 1 && if_w[x+3][y+3] == 1 && if_w[x+4][y+4] == 2 )
                        W_weight[m][n] += 1500;
                    //11012		점수낮게
                    if( if_w[x][y] == 1 && if_w[x+1][y+1] == 1 && if_w[x+2][y+2] == 0 && if_w[x+3][y+3] == 1 && if_w[x+4][y+4] == 2 )
                        W_weight[m][n] += 1500;

                    //211
                    if( if_w[x][y] == 2 && if_w[x+1][y+1] == 1 && if_w[x+2][y+2] == 1 )
                        W_weight[m][n] += 500;
                    //112
                    if( if_w[x][y] == 1 && if_w[x+1][y+1] == 1 && if_w[x+2][y+2] == 2 )
                        W_weight[m][n] += 500;
                    //121
                    if( if_w[x][y] == 1 && if_w[x+1][y+1] == 2 && if_w[x+2][y+2] == 1 )
                        W_weight[m][n] += 800;

                }
            }
            if_w[m][n] = 0;
        }
    }

}

void AI::defense_in_Diagonal_check_W()
{
    for(int m=0 ; m<19 ; m++)
    {
        for(int n=0 ; n<19 ; n++)
        {
            if( if_w[m][n] == 0 )
            {
                if_w[m][n] = 2;
            }
            else if( if_w[m][n] == 1 || if_w[m][n] == 2 )
            {
                continue;
            }

            for(int x=0; x<19; x++)
            {
                for(int y=0; y<19; y++)
                {
                    //다섯개에 양쪽다 막도록.
                    //2111112 이런상황이 되게 할때 점수가 높이 준다.
                    if( if_w[x][y] == 2 && if_w[x+1][y-1] == 1 && if_w[x+2][y-2] == 1 && if_w[x+3][y-3] == 1 && if_w[x+4][y-4] == 1 &&
                        if_w[x+5][y-5] == 1 && if_w[x+6][y-6] == 2 )
                        W_weight[m][n] += 750000;
                    //2111110
                    if( if_w[x][y] == 2 && if_w[x+1][y-1] == 1 && if_w[x+2][y-2] == 1 && if_w[x+3][y-3] == 1 && if_w[x+4][y-4] == 1 &&
                        if_w[x+5][y-5] == 1 && if_w[x+6][y-6] == 0 )
                        W_weight[m][n] += 500000;
                    //0111112
                    if( if_w[x][y] == 0 && if_w[x+1][y-1] == 1 && if_w[x+2][y-2] == 1 && if_w[x+3][y-3] == 1 && if_w[x+4][y-4] == 1 &&
                        if_w[x+5][y-5] == 1 && if_w[x+6][y-6] == 2 )
                        W_weight[m][n] += 500000;
                    //121111
                    if( if_w[x][y] == 1 && if_w[x+1][y-1] == 2 && if_w[x+2][y-2] == 1 && if_w[x+3][y-3] == 1 && if_w[x+4][y-4] == 1 &&
                        if_w[x+5][y-5] == 1 )
                        W_weight[m][n] += 500000;
                    //112111
                    if( if_w[x][y] == 1 && if_w[x+1][y-1] == 1 && if_w[x+2][y-2] == 2 && if_w[x+3][y-3] == 1 && if_w[x+4][y-4] == 1 &&
                        if_w[x+5][y-5] == 1 )
                        W_weight[m][n] += 500000;
                    //111211
                    if( if_w[x][y] == 1 && if_w[x+1][y-1] == 1 && if_w[x+2][y-2] == 1 && if_w[x+3][y-3] == 2 && if_w[x+4][y-4] == 1 &&
                        if_w[x+5][y-5] == 1 )
                        W_weight[m][n] += 500000;
                    //111121
                    if( if_w[x][y] == 1 && if_w[x+1][y-1] == 1 && if_w[x+2][y-2] == 1 && if_w[x+3][y-3] == 1 && if_w[x+4][y-4] == 2 &&
                        if_w[x+5][y-5] == 1 )
                        W_weight[m][n] += 500000;

                    //추가부분 상대방 4개짜리 사이 빈칸있을때 사이 막기
                    //202122
                    if( if_w[x][y] == 1 && if_w[x+1][y-1] == 0 && if_w[x+2][y-2] == 1 && if_w[x+3][y-3] == 2 && if_w[x+4][y-4] == 1 &&
                        if_w[x+5][y-5] == 1 )
                        W_weight[m][n] += 500000;
                    //202212
                    if( if_w[x][y] == 1 && if_w[x+1][y-1] == 0 && if_w[x+2][y-2] == 1 && if_w[x+3][y-3] == 1 && if_w[x+4][y-4] == 2 &&
                        if_w[x+5][y-5] == 1 )
                        W_weight[m][n] += 500000;
                    //212022
                    if( if_w[x][y] == 1 && if_w[x+1][y-1] == 2 && if_w[x+2][y-2] == 1 && if_w[x+3][y-3] == 0 && if_w[x+4][y-4] == 1 &&
                        if_w[x+5][y-5] == 1 )
                        W_weight[m][n] += 500000;
                    //212202
                    if( if_w[x][y] == 1 && if_w[x+1][y-1] == 2 && if_w[x+2][y-2] == 1 && if_w[x+3][y-3] == 1 && if_w[x+4][y-4] == 0 &&
                        if_w[x+5][y-5] == 1 )
                        W_weight[m][n] += 500000;
                    //221202
                    if( if_w[x][y] == 1 && if_w[x+1][y-1] == 1 && if_w[x+2][y-2] == 2 && if_w[x+3][y-3] == 1 && if_w[x+4][y-4] == 0 &&
                        if_w[x+5][y-5] == 1 )
                        W_weight[m][n] += 500000;
                    //220212
                    if( if_w[x][y] == 1 && if_w[x+1][y-1] == 1 && if_w[x+2][y-2] == 0 && if_w[x+3][y-3] == 1 && if_w[x+4][y-4] == 2 &&
                        if_w[x+5][y-5] == 1 )
                        W_weight[m][n] += 500000;

                    //211112
                    if( if_w[x][y] == 2 && if_w[x+1][y-1] == 1 && if_w[x+2][y-2] == 1 && if_w[x+3][y-3] == 1 && if_w[x+4][y-4] == 1 &&
                        if_w[x+5][y-5] == 2 )
                        W_weight[m][n] += 500000;
                    //211110
                    if( if_w[x][y] == 2 && if_w[x+1][y-1] == 1 && if_w[x+2][y-2] == 1 && if_w[x+3][y-3] == 1 && if_w[x+4][y-4] == 1 &&
                        if_w[x+5][y-5] == 0 )
                        W_weight[m][n] += 500000;
                    //011112
                    if( if_w[x][y] == 0 && if_w[x+1][y-1] == 1 && if_w[x+2][y-2] == 1 && if_w[x+3][y-3] == 1 && if_w[x+4][y-4] == 1 &&
                        if_w[x+5][y-5] == 2)
                        W_weight[m][n] += 500000;
                    //2111102
                    if( if_w[x][y] == 2 && if_w[x+1][y-1] == 1 && if_w[x+2][y-2] == 1 && if_w[x+3][y-3] == 1 && if_w[x+4][y-4] == 1 &&
                        if_w[x+5][y-5] == 0 && if_w[x+6][y-6] == 2 )
                        W_weight[m][n] += 500000;
                    //2011112
                    if( if_w[x][y] == 2 && if_w[x+1][y-1] == 0 && if_w[x+2][y-2] == 1 && if_w[x+3][y-3] == 1 && if_w[x+4][y-4] == 1 &&
                        if_w[x+5][y-5] == 1 && if_w[x+6][y-6] == 2 )
                        W_weight[m][n] += 500000;

                    //x12111x
                    if( if_w[x+1][y-1] == 1 && if_w[x+2][y-2] == 2 && if_w[x+3][y-3] == 1 && if_w[x+4][y-4] == 1 &&
                        if_w[x+5][y-5] == 1 && if_w[x+6][y-6] != 2 )
                        W_weight[m][n] += 500000;
                    //x11211x
                    if( if_w[x+1][y-1] == 1 && if_w[x+2][y-2] == 1 && if_w[x+3][y-3] == 2 && if_w[x+4][y-4] == 1 &&
                        if_w[x+5][y-5] == 1 && if_w[x+6][y-6] != 2 )
                        W_weight[m][n] += 500000;
                    //x11121x
                    if( if_w[x+1][y-1] == 1 && if_w[x+2][y-2] == 1 && if_w[x+3][y-3] == 1 && if_w[x+4][y-4] == 2 &&
                        if_w[x+5][y-5] == 1 && if_w[x+6][y-6] != 2 )
                        W_weight[m][n] += 500000;
                    //x12111x
                    if( if_w[x][y] != 2 && if_w[x+1][y-1] == 1 && if_w[x+2][y-2] == 2 && if_w[x+3][y-3] == 1 && if_w[x+4][y-4] == 1 &&
                        if_w[x+5][y-5] == 1 )
                        W_weight[m][n] += 500000;
                    //x11211x
                    if( if_w[x][y] != 2 && if_w[x+1][y-1] == 1 && if_w[x+2][y-2] == 1 && if_w[x+3][y-3] == 2 && if_w[x+4][y-4] == 1 &&
                        if_w[x+5][y-5] == 1 )
                        W_weight[m][n] += 500000;
                    //x11121x
                    if( if_w[x][y] != 2 && if_w[x+1][y-1] == 1 && if_w[x+2][y-2] == 1 && if_w[x+3][y-3] == 1 && if_w[x+4][y-4] == 2 &&
                        if_w[x+5][y-5] == 1 )
                        W_weight[m][n] += 500000;

                    //120111
                    if( if_w[x][y] == 1 && if_w[x+1][y-1] == 2 && if_w[x+2][y-2] == 0 && if_w[x+3][y-3] == 1 && if_w[x+4][y-4] == 1 &&
                        if_w[x+5][y-5] == 1 )
                        W_weight[m][n] += 500000;
                    //102111
                    if( if_w[x][y] == 1 && if_w[x+1][y-1] == 0 && if_w[x+2][y-2] == 2 && if_w[x+3][y-3] == 1 && if_w[x+4][y-4] == 1 &&
                        if_w[x+5][y-5] == 1 )
                        W_weight[m][n] += 500000;
                    //111201
                    if( if_w[x][y] == 1 && if_w[x+1][y-1] == 1 && if_w[x+2][y-2] == 1 && if_w[x+3][y-3] == 2 && if_w[x+4][y-4] == 0 &&
                        if_w[x+5][y-5] == 1 )
                        W_weight[m][n] += 500000;
                    //111021
                    if( if_w[x][y] == 1 && if_w[x+1][y-1] == 1 && if_w[x+2][y-2] == 1 && if_w[x+3][y-3] == 0 && if_w[x+4][y-4] == 2 &&
                        if_w[x+5][y-5] == 1 )
                        W_weight[m][n] += 500000;
                    //112011
                    if( if_w[x][y] == 1 && if_w[x+1][y-1] == 1 && if_w[x+2][y-2] == 2 && if_w[x+3][y-3] == 0 && if_w[x+4][y-4] == 1 &&
                        if_w[x+5][y-5] == 1 )
                        W_weight[m][n] += 500000;
                    //110211
                    if( if_w[x][y] == 1 && if_w[x+1][y-1] == 1 && if_w[x+2][y-2] == 0 && if_w[x+3][y-3] == 2 && if_w[x+4][y-4] == 1 &&
                        if_w[x+5][y-5] == 1 )
                        W_weight[m][n] += 500000;

                    //여기서부터 간단한 가중치 줄 것. 즉, 2개 3개 막게하는것들
                    //2111
                    if( if_w[x][y] == 2 && if_w[x+1][y-1] == 1 && if_w[x+2][y-2] == 1 && if_w[x+3][y-3] == 1 )
                        W_weight[m][n] += 3500;
                    //1112
                    if( if_w[x][y] == 1 && if_w[x+1][y-1] == 1 && if_w[x+2][y-2] == 1 && if_w[x+3][y-3] == 2 )
                        W_weight[m][n] += 3500;
                    //1211
                    if( if_w[x][y] == 1 && if_w[x+1][y-1] == 2 && if_w[x+2][y-2] == 1 && if_w[x+3][y-3] == 1 )
                        W_weight[m][n] += 4000;
                    //1121
                    if( if_w[x][y] == 1 && if_w[x+1][y-1] == 1 && if_w[x+2][y-2] == 2 && if_w[x+3][y-3] == 1 )
                        W_weight[m][n] += 4000;
                    //11102		분기해서 막는것도 필요한 경우가 있을수있음. 단 점수는 낮게
                    if( if_w[x][y] == 1 && if_w[x+1][y-1] == 1 && if_w[x+2][y-2] == 1 && if_w[x+3][y-3] == 0 && if_w[x+4][y-4] == 2 )
                        W_weight[m][n] += 1500;
                    //20111
                    if( if_w[x][y] == 2 && if_w[x+1][y-1] == 0 && if_w[x+2][y-2] == 1 && if_w[x+3][y-3] == 1 && if_w[x+4][y-4] == 1 )
                        W_weight[m][n] += 1500;

                    //21011		점수낮게
                    if( if_w[x][y] == 2 && if_w[x+1][y-1] == 1 && if_w[x+2][y-2] == 0 && if_w[x+3][y-3] == 1 && if_w[x+4][y-4] == 1 )
                        W_weight[m][n] += 1500;
                    //21101		점수낮게
                    if( if_w[x][y] == 2 && if_w[x+1][y-1] == 1 && if_w[x+2][y-2] == 1 && if_w[x+3][y-3] == 0 && if_w[x+4][y-4] == 1 )
                        W_weight[m][n] += 1500;
                    //10112		점수낮게
                    if( if_w[x][y] == 1 && if_w[x+1][y-1] == 0 && if_w[x+2][y-2] == 1 && if_w[x+3][y-3] == 1 && if_w[x+4][y-4] == 2 )
                        W_weight[m][n] += 1500;
                    //11012		점수낮게
                    if( if_w[x][y] == 1 && if_w[x+1][y-1] == 1 && if_w[x+2][y-2] == 0 && if_w[x+3][y-3] == 1 && if_w[x+4][y-4] == 2 )
                        W_weight[m][n] += 1500;

                    //211
                    if( if_w[x][y] == 2 && if_w[x+1][y-1] == 1 && if_w[x+2][y-2] == 1 )
                        W_weight[m][n] += 500;
                    //112
                    if( if_w[x][y] == 1 && if_w[x+1][y-1] == 1 && if_w[x+2][y-2] == 2 )
                        W_weight[m][n] += 500;
                    //121
                    if( if_w[x][y] == 1 && if_w[x+1][y-1] == 2 && if_w[x+2][y-2] == 1 )
                        W_weight[m][n] += 800;
                }
            }
            if_w[m][n] = 0;
        }
    }
}

void AI::B_AI_allcheck()
{
    for(int x_new=0; x_new<19; x_new++) // 모든 가중치배열좌표값을 0으로 초기화
        {
            for(int y_new=0; y_new<19; y_new++)
            {
                B_weight[x_new][y_new] = 0;		//가중치배열 0으로 초기화.
                if( w[x_new][y_new] == 2 )
                {
                    if_b[x_new][y_new] = 2;
                }
                if( b[x_new][y_new] == 1 )
                {
                    if_b[x_new][y_new] = 1;
                }
                else;
            }
        }

        B_AI_5_6_7_check();

        defense_Horizontal_check_B();
        defense_Vertical_check_B();
        defense_Diagonal_check_B();
        defense_in_Diagonal_check_B();

        B_AI_2_Horizontal_check();
        B_AI_3_Horizontal_check();
        B_AI_4_Horizontal_check();

        B_AI_2_Vertical_check();
        B_AI_3_Vertical_check();
        B_AI_4_Vertical_check();

        B_AI_2_Diagonal_check();
        B_AI_3_Diagonal_check();
        B_AI_4_Diagonal_check();

        B_AI_2_in_Diagonal_check();
        B_AI_3_in_Diagonal_check();
        B_AI_4_in_Diagonal_check();

        for(int x=0; x<19; x++)
        {
            for(int y=0; y<19; y++)
            {
                if(b[x][y] ==1 || w[x][y] == 2)
                {
                    B_weight[x][y] = 0;
                }
            }
        }

        max_weight = 0;

        for(int max_x=0; max_x<19; max_x++) // 최대 가중치 찾기
        {
            for(int max_y=0; max_y<19; max_y++)
            {
                if(max_weight < B_weight[max_x][max_y])
                {
                    max_weight = B_weight[max_x][max_y];
                    bx = max_x;
                    by = max_y;
                }
                //같은 가중치일 때 랜덤
                else if(max_weight == W_weight[max_x][max_y])
                {
                    srand((unsigned)time(NULL));
                    int random = rand()%2;
                    if(random == 0)
                    {
                        max_weight = W_weight[max_x][max_y];
                        bx = max_x;
                        by = max_y;
                    }
                    else;
                }
                else;
            }
        }

        b[bx][by] = 1;
}

void AI::B_AI_5_6_7_check()
{
    for(int m=0 ; m<19 ; m++)
        {
          for(int n=0 ; n<19 ; n++)
          {
              if( if_b[m][n] == 0 )
              {
              if_b[m][n] = 1;
              }
              else if( if_b[m][n] == 1 || if_b[m][n] == 2 )
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
                    if( if_b[x][y] == 0 && if_b[x][y+1] == 1 && if_b[x][y+2] == 1 && if_b[x][y+3] == 1 && if_b[x][y+4] == 1 &&
                        if_b[x][y+5] == 1 )
                        B_weight[m][n] += 45000000;	//022222
                    if( if_b[x][y] == 1 && if_b[x][y+1] == 1 && if_b[x][y+2] == 1 && if_b[x][y+3] == 1 && if_b[x][y+4] == 1 &&
                        if_b[x][y+5] == 0 )
                        B_weight[m][n] += 45000000;  //222220
                    if( if_b[x][y] == 1 && if_b[x][y+1] == 0 && if_b[x][y+2] == 1 && if_b[x][y+3] == 1 && if_b[x][y+4] == 1 &&
                        if_b[x][y+5] == 1 )
                        B_weight[m][n] += 45000000;	//202222
                    if( if_b[x][y] == 1 && if_b[x][y+1] == 1 && if_b[x][y+2] == 1 && if_b[x][y+3] == 1 && if_b[x][y+4] == 0 &&
                        if_b[x][y+5] == 1 )
                        B_weight[m][n] += 45000000;	//222202
                    if( if_b[x][y] == 1 && if_b[x][y+1] == 1 && if_b[x][y+2] == 0 && if_b[x][y+3] == 1 && if_b[x][y+4] == 1 &&
                        if_b[x][y+5] == 1 )
                        B_weight[m][n] += 45000000;	//220222
                    if( if_b[x][y] == 1 && if_b[x][y+1] == 1 && if_b[x][y+2] == 1 && if_b[x][y+3] == 0 && if_b[x][y+4] == 1 &&
                        if_b[x][y+5] == 1 )
                        B_weight[m][n] += 45000000;	//222022

                    //첫째턴, 6개까지 만들 여지가 있을 경우 & 세로
                    if( if_b[x][y] == 0 && if_b[x+1][y] == 1 && if_b[x+2][y] == 1 && if_b[x+3][y] == 1 && if_b[x+4][y] == 1 &&
                        if_b[x+5][y] == 1 )
                        B_weight[m][n] += 45000000;	//022222
                    if( if_b[x][y] == 1 && if_b[x+1][y] == 1 && if_b[x+2][y] == 1 && if_b[x+3][y] == 1 && if_b[x+4][y] == 1 &&
                        if_b[x+5][y] == 0 )
                        B_weight[m][n] += 45000000;  //222220
                    if( if_b[x][y] == 1 && if_b[x+1][y] == 0 && if_b[x+2][y] == 1 && if_b[x+3][y] == 1 && if_b[x+4][y] == 1 &&
                        if_b[x+5][y] == 1 )
                        B_weight[m][n] += 45000000;	//202222
                    if( if_b[x][y] == 1 && if_b[x+1][y] == 1 && if_b[x+2][y] == 1 && if_b[x+3][y] == 1 && if_b[x+4][y] == 0 &&
                        if_b[x+5][y] == 1 )
                        B_weight[m][n] += 45000000;	//222202
                    if( if_b[x][y] == 1 && if_b[x+1][y] == 1 && if_b[x+2][y] == 0 && if_b[x+3][y] == 1 && if_b[x+4][y] == 1 &&
                        if_b[x+5][y] == 1 )
                        B_weight[m][n] += 45000000;	//220222
                    if( if_b[x][y] == 1 && if_b[x+1][y] == 1 && if_b[x+2][y] == 1 && if_b[x+3][y] == 0 && if_b[x+4][y] == 1 &&
                        if_b[x+5][y] == 1 )
                        B_weight[m][n] += 45000000;	//222022

                    //첫째턴, 6개까지 만들 여지가 있을 경우 & 대각선
                    if( if_b[x][y] == 0 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 1 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] == 1 &&
                        if_b[x+5][y+5] == 1 )
                        B_weight[m][n] += 45000000;	//022222
                    if( if_b[x][y] == 1 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 1 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] == 1 &&
                        if_b[x+5][y+5] == 0 )
                        B_weight[m][n] += 45000000;  //222220
                    if( if_b[x][y] == 1 && if_b[x+1][y+1] == 0 && if_b[x+2][y+2] == 1 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] == 1 &&
                        if_b[x+5][y+5] == 1 )
                        B_weight[m][n] += 45000000;	//202222
                    if( if_b[x][y] == 1 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 1 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] == 0 &&
                        if_b[x+5][y+5] == 1 )
                        B_weight[m][n] += 45000000;	//222202
                    if( if_b[x][y] == 1 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 0 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] == 1 &&
                        if_b[x+5][y+5] == 1 )
                        B_weight[m][n] += 45000000;	//220222
                    if( if_b[x][y] == 1 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 1 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] == 1 &&
                        if_b[x+5][y+5] == 1 )
                        B_weight[m][n] += 45000000;	//222022

                    //첫째턴, 6개까지 만들 여지가 있을 경우 & 역대각선
                    if( if_b[x][y] == 0 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 1 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] == 1 &&
                        if_b[x+5][y-5] == 1 )
                        B_weight[m][n] += 45000000;	//022222
                    if( if_b[x][y] == 1 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 1 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] == 1 &&
                        if_b[x+5][y-5] == 0 )
                        B_weight[m][n] += 45000000;  //222220
                    if( if_b[x][y] == 1 && if_b[x+1][y-1] == 0 && if_b[x+2][y-2] == 1 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] == 1 &&
                        if_b[x+5][y-5] == 1 )
                        B_weight[m][n] += 45000000;	//202222
                    if( if_b[x][y] == 1 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 1 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] == 0 &&
                        if_b[x+5][y-5] == 1 )
                        B_weight[m][n] += 45000000;	//222202
                    if( if_b[x][y] == 1 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 0 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] == 1 &&
                        if_b[x+5][y-5] == 1 )
                        B_weight[m][n] += 45000000;	//220222
                    if( if_b[x][y] == 1 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 1 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] == 1 &&
                        if_b[x+5][y-5] == 1 )
                        B_weight[m][n] += 45000000;	//222022
                }
                    //양쪽다막힌 양쪽모두 막힌 곳에 돌을 5개로 만드는 것은 점수필요없음.
                //1222221
                if( if_b[x][y] == 2 && if_b[x][y+1] == 1 && if_b[x][y+2] == 1 && if_b[x][y+3] == 1 && if_b[x][y+4] == 1 &&
                    if_b[x][y+5] == 1 && if_b[x][y+6] == 2 )
                    B_weight[m][n] = 0;
                if( if_b[x][y] == 2 && if_b[x+1][y] == 1 && if_b[x+2][y] == 1 && if_b[x+3][y] == 1 && if_b[x+4][y] == 1 &&
                    if_b[x+5][y] == 1 && if_b[x+6][y] == 2 )
                    B_weight[m][n] = 0;
                if( if_b[x][y] == 2 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 1 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] == 1 &&
                    if_b[x+5][y+5] == 1 && if_b[x+6][y+6] == 2 )
                    B_weight[m][n] = 0;
                if( if_b[x][y] == 2 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 1 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] == 1 &&
                    if_b[x+5][y-5] == 1 && if_b[x+6][y-6] == 2 )
                    B_weight[m][n] = 0;
                //111111가로로 이길수있을때
                if( if_b[x][y] == 1 && if_b[x][y+1] == 1 && if_b[x][y+2] == 1 && if_b[x][y+3] == 1 && if_b[x][y+4] == 1 &&
                    if_b[x][y+5] == 1 )
                    B_weight[m][n] += 99999999999;
                //세로로 이길수있을때
                if( if_b[x][y] == 1 && if_b[x+1][y] == 1 && if_b[x+2][y] == 1 && if_b[x+3][y] == 1 && if_b[x+4][y] == 1 &&
                    if_b[x+5][y] == 1 )
                    B_weight[m][n] += 99999999999;
                //대각선으로 이길수있을때
                if( if_b[x][y] == 1 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 1 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] == 1 &&
                    if_b[x+5][y+5] == 1 )
                    B_weight[m][n] += 99999999999;
                if( if_b[x][y] == 1 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 1 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] == 1 &&
                    if_b[x+5][y-5] == 1 )
                    B_weight[m][n] += 99999999999;
                  }
              }
              if_b[m][n] = 0;
          }
        }
}

void AI::B_AI_2_Horizontal_check()
{
    for(int m=0 ; m<19 ; m++)
        {
          for(int n=0 ; n<19 ; n++)
          {
              if( if_b[m][n] == 0 )
              {
              if_b[m][n] = 1;
              }
              else if( if_b[m][n] == 2 || if_b[m][n] == 1 )
              {
                  continue;
              }

              for(int x=0; x<19; x++)
              {
                  for(int y=0; y<19; y++)
                  {
                //00022000
                if( if_b[x][y-2] == 0 && if_b[x][y-1] == 0 && if_b[x][y] == 0 && if_b[x][y+1] == 1 && if_b[x][y+2] == 1 &&
                    if_b[x][y+3] == 0 && if_b[x][y+4] == 0 && if_b[x][y+5] == 0 )
                    B_weight[m][n] += 2000;
                //0020200
                if( if_b[x][y-1] == 0 && if_b[x][y] == 0 && if_b[x][y+1] == 1 && if_b[x][y+2] == 0 && if_b[x][y+3] == 1 && if_b[x][y+4] == 0 &&
                    if_b[x][y+5] == 0 )
                    B_weight[m][n] += 1500;
                //020020
                if( if_b[x][y] == 0 && if_b[x][y+1] == 1 && if_b[x][y+2] == 0 && if_b[x][y+3] == 0 && if_b[x][y+4] == 1 && if_b[x][y+5] == 0 )
                    B_weight[m][n] = 1000;
                //여기까지 양쪽에 안 막힌, 흰 돌이 2개가 발견 될 때 경우의 수들

                //122000
                if( if_b[x][y] == 2 && if_b[x][y+1] == 1 && if_b[x][y+2] == 1 && if_b[x][y+3] == 0 && if_b[x][y+4] == 0 && if_b[x][y+5] == 0 )
                    B_weight[m][n] += 500;
                //120200
                if( if_b[x][y] == 2 && if_b[x][y+1] == 1 && if_b[x][y+2] == 0 && if_b[x][y+3] == 1 && if_b[x][y+4] == 0 && if_b[x][y+5] == 0 )
                    B_weight[m][n] += 500;
                //120020
                if( if_b[x][y] == 2 && if_b[x][y+1] == 1 && if_b[x][y+2] == 0 && if_b[x][y+3] == 0 && if_b[x][y+4] == 1 && if_b[x][y+5] == 0 )
                    B_weight[m][n] += 500;
                //102200
                if( if_b[x][y] == 2 && if_b[x][y+1] == 0 && if_b[x][y+2] == 1 && if_b[x][y+3] == 1 && if_b[x][y+4] == 0 && if_b[x][y+5] == 0 )
                    B_weight[m][n] += 800;
                //102020
                if( if_b[x][y] == 2 && if_b[x][y+1] == 0 && if_b[x][y+2] == 1 && if_b[x][y+3] == 0 && if_b[x][y+4] == 1 && if_b[x][y+5] == 0 )
                    B_weight[m][n] += 800;
                //여기까지 왼쪽에 검은돌로 막힌 경우.
                //오른쪽에 검은돌로 막힌 경우는 이 대칭으로만 작성해주면됌

                //000221
                if( if_b[x][y-2] == 0 && if_b[x][y-1] == 0 && if_b[x][y] == 0 && if_b[x][y+1] == 1 && if_b[x][y+2] == 1 && if_b[x][y+3] == 2 )
                    B_weight[m][n] += 500;
                //002021
                if( if_b[x][y-1] == 0 && if_b[x][y] == 0 && if_b[x][y+1] == 1 && if_b[x][y+2] == 0 && if_b[x][y+3] == 1 && if_b[x][y+4] == 2 )
                    B_weight[m][n] += 500;
                //020021
                if( if_b[x][y] == 0 && if_b[x][y+1] == 1 && if_b[x][y+2] == 0 && if_b[x][y+3] == 0 && if_b[x][y+4] == 1 && if_b[x][y+5] == 2 )
                    B_weight[m][n] += 500;
                //002201
                if( if_b[x][y-1] == 0 && if_b[x][y] == 0 && if_b[x][y+1] == 1 && if_b[x][y+2] == 1 && if_b[x][y+3] == 0 && if_b[x][y+4] == 2 )
                    B_weight[m][n] += 800;
                //020201
                if( if_b[x][y] == 0 && if_b[x][y+1] == 1 && if_b[x][y+2] == 0 && if_b[x][y+3] == 1 && if_b[x][y+4] == 0 && if_b[x][y+5] == 2 )
                    B_weight[m][n] += 800;
                //여기까지 한쪽이 막힌 경우.
                //그 다음은 양쪽이 막힌 경우. 양쪽이 막힌 경우는 안이 6칸일 경우만 따지자.

                //12200001
                if( if_b[x][y] == 2 && if_b[x][y+1] == 1 && if_b[x][y+2] == 1 && if_b[x][y+3] == 0 && if_b[x][y+4] == 0 && if_b[x][y+5] == 0 &&
                    if_b[x][y+6] == 0 && if_b[x][y+7] == 2 )
                    B_weight[m][n] += 300;
                //12020001
                if( if_b[x][y] == 2 && if_b[x][y+1] == 1 && if_b[x][y+2] == 0 && if_b[x][y+3] == 1 && if_b[x][y+4] == 0 && if_b[x][y+5] == 0 &&
                    if_b[x][y+6] == 0 && if_b[x][y+7] == 2 )
                    B_weight[m][n] += 300;
                //12002001
                if( if_b[x][y] == 2 && if_b[x][y+1] == 1 && if_b[x][y+2] == 0 && if_b[x][y+3] == 0 && if_b[x][y+4] == 1 && if_b[x][y+5] == 0 &&
                    if_b[x][y+6] == 0 && if_b[x][y+7] == 2 )
                    B_weight[m][n] += 300;
                //12000201
                if( if_b[x][y] == 2 && if_b[x][y+1] == 1 && if_b[x][y+2] == 0 && if_b[x][y+3] == 0 && if_b[x][y+4] == 0 && if_b[x][y+5] == 1 &&
                    if_b[x][y+6] == 0 && if_b[x][y+7] == 2 )
                    B_weight[m][n] += 300;
                //12000021
                if( if_b[x][y] == 2 && if_b[x][y+1] == 1 && if_b[x][y+2] == 0 && if_b[x][y+3] == 0 && if_b[x][y+4] == 0 && if_b[x][y+5] == 0 &&
                    if_b[x][y+6] == 1 && if_b[x][y+7] == 2 )
                    B_weight[m][n] += 300;
                //10220001
                if( if_b[x][y] == 2 && if_b[x][y+1] == 0 && if_b[x][y+2] == 1 && if_b[x][y+3] == 1 && if_b[x][y+4] == 0 && if_b[x][y+5] == 0 &&
                    if_b[x][y+6] == 0 && if_b[x][y+7] == 2 )
                    B_weight[m][n] += 300;
                //10202001
                if( if_b[x][y] == 2 && if_b[x][y+1] == 0 && if_b[x][y+2] == 1 && if_b[x][y+3] == 0 && if_b[x][y+4] == 1 && if_b[x][y+5] == 0 &&
                    if_b[x][y+6] == 0 && if_b[x][y+7] == 2 )
                    B_weight[m][n] += 300;
                //10200201
                if( if_b[x][y] == 2 && if_b[x][y+1] == 0 && if_b[x][y+2] == 1 && if_b[x][y+3] == 0 && if_b[x][y+4] == 0 && if_b[x][y+5] == 1 &&
                    if_b[x][y+6] == 0 && if_b[x][y+7] == 2 )
                    B_weight[m][n] += 300;
                //10200021
                if( if_b[x][y] == 2 && if_b[x][y+1] == 0 && if_b[x][y+2] == 1 && if_b[x][y+3] == 0 && if_b[x][y+4] == 0 && if_b[x][y+5] == 0 &&
                    if_b[x][y+6] == 1 && if_b[x][y+7] == 2 )
                    B_weight[m][n] += 300;
                //10022001
                if( if_b[x][y] == 2 && if_b[x][y+1] == 0 && if_b[x][y+2] == 0 && if_b[x][y+3] == 1 && if_b[x][y+4] == 1 && if_b[x][y+5] == 0 &&
                    if_b[x][y+6] == 0 && if_b[x][y+7] == 2 )
                    B_weight[m][n] += 300;
                //10020201
                if( if_b[x][y] == 2 && if_b[x][y+1] == 0 && if_b[x][y+2] == 0 && if_b[x][y+3] == 1 && if_b[x][y+4] == 0 && if_b[x][y+5] == 1 &&
                    if_b[x][y+6] == 0 && if_b[x][y+7] == 2 )
                    B_weight[m][n] += 300;
                //10020021
                if( if_b[x][y] == 2 && if_b[x][y+1] == 0 && if_b[x][y+2] == 0 && if_b[x][y+3] == 1 && if_b[x][y+4] == 0 && if_b[x][y+5] == 0 &&
                    if_b[x][y+6] == 1 && if_b[x][y+7] == 2 )
                    B_weight[m][n] += 300;
                //10002201
                if( if_b[x][y] == 2 && if_b[x][y+1] == 0 && if_b[x][y+2] == 0 && if_b[x][y+3] == 0 && if_b[x][y+4] == 1 && if_b[x][y+5] == 1 &&
                    if_b[x][y+6] == 0 && if_b[x][y+7] == 2 )
                    B_weight[m][n] += 300;
                //10002021
                if( if_b[x][y] == 2 && if_b[x][y+1] == 0 && if_b[x][y+2] == 0 && if_b[x][y+3] == 1 && if_b[x][y+4] == 0 && if_b[x][y+5] == 1 &&
                    if_b[x][y+6] == 0 && if_b[x][y+7] == 2 )
                    B_weight[m][n] += 300;
                //10000221
                if( if_b[x][y] == 2 && if_b[x][y+1] == 0 && if_b[x][y+2] == 0 && if_b[x][y+3] == 0 && if_b[x][y+4] == 0 && if_b[x][y+5] == 1 &&
                    if_b[x][y+6] == 1 && if_b[x][y+7] == 2 )
                    B_weight[m][n] += 300;
                  }
              }
              if_b[m][n] = 0;
          }
        }
}

void AI::B_AI_3_Horizontal_check()
{
    for(int m=0 ; m<19 ; m++)
    {
      for(int n=0 ; n<19 ; n++)
      {
          if( if_b[m][n] == 0 )
          {
          if_b[m][n] = 1;
          }
          else if( if_b[m][n] == 2 || if_b[m][n] == 1 )
          {
              continue;
          }

          for(int x=0; x<19; x++)
          {
              for(int y=0; y<19; y++)
              {
            //000222000
            if( if_b[x][y-1] == 0 && if_b[x][y] == 0 && if_b[x][y+1] == 1 && if_b[x][y+2] == 1 && if_b[x][y+3] == 1&& if_b[x][y+4]==0 &&
                if_b[x][y+5] == 0 )
                B_weight[m][n] += 5000;
            //00202200
            if( if_b[x][y-1] == 0 && if_b[x][y] == 0 && if_b[x][y+1] == 1 && if_b[x][y+2] == 0 && if_b[x][y+3] == 1 && if_b[x][y+4] == 1 &&
                if_b[x][y+5]==0 && if_b[x][y+6] == 0 )
                B_weight[m][n] += 3500;
            //00220200
            if( if_b[x][y-1] == 0 && if_b[x][y] == 0 && if_b[x][y+1] == 1 && if_b[x][y+2] == 1 && if_b[x][y+3] == 0 && if_b[x][y+4] == 1 &&
                if_b[x][y+5] == 0 && if_b[x][y+6] == 0 )
                B_weight[m][n] += 3500;
            //0200220
            if( if_b[x][y] == 0 && if_b[x][y+1] == 1 && if_b[x][y+2] == 0 && if_b[x][y+3] == 0 && if_b[x][y+4] == 1 && if_b[x][y+5] == 1
                &&if_b[x][y+6] ==0 )
                B_weight[m][n] += 3000;
            //0202020
            if( if_b[x][y] == 0 && if_b[x][y+1] == 1 && if_b[x][y+2] == 0 && if_b[x][y+3] == 1 && if_b[x][y+4] == 0 && if_b[x][y+5] == 1
                &&if_b[x][y+6]==0 )
                B_weight[m][n] += 3000;
            //0220020
            if( if_b[x][y] == 0 && if_b[x][y+1] == 1 && if_b[x][y+2] == 1 && if_b[x][y+3] == 0 && if_b[x][y+4] == 0 && if_b[x][y+5] == 1
                && if_b[x][y+6] ==0 )
                B_weight[m][n] += 3000;
            //여기까지 양쪽에 안 막힌, 흰 돌이 2개가 발견 될 때 경우의 수들

            //122200
            if( if_b[x][y] == 2 && if_b[x][y+1] == 1 && if_b[x][y+2] == 1 && if_b[x][y+3] == 1 && if_b[x][y+4] ==0 && if_b[x][y+5] == 0 )
                B_weight[m][n] += 1000;
            //1202200
            if( if_b[x][y] == 2 && if_b[x][y+1] == 1 && if_b[x][y+2] == 0 && if_b[x][y+3] == 1 && if_b[x][y+4] == 1 && if_b[x][y+5] ==0 &&
                if_b[x][y+6] == 0 )
                B_weight[m][n] += 1000;
            //1220200
            if( if_b[x][y] == 2 && if_b[x][y+1] == 1 && if_b[x][y+2] == 1 && if_b[x][y+3] == 0 && if_b[x][y+4] == 1 && if_b[x][y+5] == 0 &&
                if_b[x][y+6] == 0 )
                B_weight[m][n] += 1000;
            //1022200
            if( if_b[x][y] == 2 && if_b[x][y+1] == 0 && if_b[x][y+2] == 1 && if_b[x][y+3] == 1 && if_b[x][y+4] == 1 && if_b[x][y+5] ==0 &&
                if_b[x][y+6] == 0 )
                B_weight[m][n] += 1300;
            //1200220
            if( if_b[x][y] == 2 && if_b[x][y+1] == 1 && if_b[x][y+2] == 0 && if_b[x][y+3] == 0 && if_b[x][y+4] == 1 && if_b[x][y+5] == 1 &&
            if_b[x][y+6] ==0 )
                B_weight[m][n] += 1300;
            //1220020
            if( if_b[x][y] == 2 && if_b[x][y+1] == 1 && if_b[x][y+2] == 1 && if_b[x][y+3] == 0 && if_b[x][y+4] == 0 && if_b[x][y+5] == 1 &&
                if_b[x][y+6] == 0 )
                B_weight[m][n] += 1000;
            //1202020
            if( if_b[x][y] == 2 && if_b[x][y+1] == 1 && if_b[x][y+2] == 0 && if_b[x][y+3] == 1 && if_b[x][y+4] == 0 && if_b[x][y+5] == 1 &&
                if_b[x][y+6] ==0 )
                B_weight[m][n] += 1000;
            //1020220
            if( if_b[x][y] == 2 && if_b[x][y+1] == 0 && if_b[x][y+2] == 1 && if_b[x][y+3] == 0 && if_b[x][y+4] == 1 && if_b[x][y+5] == 1 &&
                if_b[x][y+6] == 0)
                B_weight[m][n] += 1300;

            //여기까지 왼쪽에 검은돌로 막힌 경우.
            //오른쪽에 검은돌로 막힌 경우는 이 대칭으로만 작성해주면됌

            //002221
            if( if_b[x][y-1] == 0 && if_b[x][y] == 0 && if_b[x][y+1] == 1 && if_b[x][y+2] == 1 && if_b[x][y+3] == 1 && if_b[x][y+4] == 2 )
                B_weight[m][n] += 1000;
            //0022021
            if( if_b[x][y-1] == 0 && if_b[x][y] == 0 && if_b[x][y+1] == 1 && if_b[x][y+2] == 1 && if_b[x][y+3] == 0 && if_b[x][y+4] == 1 &&
                if_b[x][y+5]==2 )
                B_weight[m][n] += 1000;
            //0020221
            if( if_b[x][y-1] == 0 && if_b[x][y] == 0 && if_b[x][y+1] == 1 && if_b[x][y+2] == 0 && if_b[x][y+3] == 1 && if_b[x][y+4] == 1 &&
                if_b[x][y+5] == 2 )
                B_weight[m][n] += 1000;
            //0022201
            if( if_b[x][y-1] == 0 && if_b[x][y] == 0 && if_b[x][y+1] == 1 && if_b[x][y+2] == 1 && if_b[x][y+3] == 1 && if_b[x][y+4] == 0 &&
                if_b[x][y+5] == 2 )
                B_weight[m][n] += 1300;
            //0220021
            if( if_b[x][y] == 0 && if_b[x][y+1] == 1 && if_b[x][y+2] == 1 && if_b[x][y+3] == 0 && if_b[x][y+4] == 0 && if_b[x][y+5] == 1 &&
                if_b[x][y+6] == 2 )
                B_weight[m][n] += 1300;
            //0200221
            if( if_b[x][y] == 0 && if_b[x][y+1] == 1 && if_b[x][y+2] == 0 && if_b[x][y+3] == 0 && if_b[x][y+4] == 1 && if_b[x][y+5] == 1 &&
                if_b[x][y+6] == 2 )
                B_weight[m][n] += 1000;
            //0202021
            if( if_b[x][y] == 0 && if_b[x][y+1] == 1 && if_b[x][y+2] == 0 && if_b[x][y+3] == 1 && if_b[x][y+4] == 0 && if_b[x][y+5] == 1 &&
                if_b[x][y+6] == 2 )
                B_weight[m][n] += 1000;
            //0220201
            if( if_b[x][y] == 0 && if_b[x][y+1] == 1 && if_b[x][y+2] == 1 && if_b[x][y+3] == 0 && if_b[x][y+4] == 1 && if_b[x][y+5] == 0 &&
                if_b[x][y+6] == 2 )
                B_weight[m][n] += 1300;

            //여기까지 한쪽이 막힌 경우.
            //그 다음은 양쪽이 막힌 경우. 양쪽이 막힌 경우는 안이 6칸일 경우만 따지자.

            //12220001
            if( if_b[x][y] == 2 && if_b[x][y+1] == 1 && if_b[x][y+2] == 1 && if_b[x][y+3] == 1 && if_b[x][y+4] == 0 && if_b[x][y+5] == 0 &&
                if_b[x][y+6] == 0 && if_b[x][y+7] == 2 )
                B_weight[m][n] += 300;
            //12022001
            if( if_b[x][y] == 2 && if_b[x][y+1] == 1 && if_b[x][y+2] == 0 && if_b[x][y+3] == 1 && if_b[x][y+4] == 1 && if_b[x][y+5] == 0 &&
                if_b[x][y+6] == 0 && if_b[x][y+7] == 2 )
                B_weight[m][n] += 300;
            //12002201
            if( if_b[x][y] == 2 && if_b[x][y+1] == 1 && if_b[x][y+2] == 0 && if_b[x][y+3] == 0 && if_b[x][y+4] == 1 && if_b[x][y+5] == 1 &&
                if_b[x][y+6] == 0 && if_b[x][y+7] == 2 )
                B_weight[m][n] += 300;
            //12000221
            if( if_b[x][y] == 2 && if_b[x][y+1] == 1 && if_b[x][y+2] == 0 && if_b[x][y+3] == 0 && if_b[x][y+4] == 0 && if_b[x][y+5] == 1 &&
                if_b[x][y+6] == 1 && if_b[x][y+7] == 2 )
                B_weight[m][n] += 300;
            //12202001
            if( if_b[x][y] == 2 && if_b[x][y+1] == 1 && if_b[x][y+2] == 1 && if_b[x][y+3] == 0 && if_b[x][y+4] == 1 && if_b[x][y+5] == 0 &&
                if_b[x][y+6] == 0 && if_b[x][y+7] == 2 )
                B_weight[m][n] += 300;
            //12200201
            if( if_b[x][y] == 2 && if_b[x][y+1] == 1 && if_b[x][y+2] == 1 && if_b[x][y+3] == 0 && if_b[x][y+4] == 0 && if_b[x][y+5] == 1 &&
                if_b[x][y+6] == 0 && if_b[x][y+7] == 2 )
                B_weight[m][n] += 300;
            //12200021
            if( if_b[x][y] == 2 && if_b[x][y+1] == 1 && if_b[x][y+2] == 1 && if_b[x][y+3] == 0 && if_b[x][y+4] == 0 && if_b[x][y+5] == 0 &&
                if_b[x][y+6] == 1 && if_b[x][y+7] == 2 )
                B_weight[m][n] += 300;
            //12002021
            if( if_b[x][y] == 2 && if_b[x][y+1] == 1 && if_b[x][y+2] == 0 && if_b[x][y+3] == 0 && if_b[x][y+4] == 1 && if_b[x][y+5] == 0 &&
                if_b[x][y+6] == 1 && if_b[x][y+7] == 2 )
                B_weight[m][n] += 300;
            //12020021
            if( if_b[x][y] == 2 && if_b[x][y+1] == 1 && if_b[x][y+2] == 0 && if_b[x][y+3] == 1 && if_b[x][y+4] == 0 && if_b[x][y+5] == 0 &&
                if_b[x][y+6] == 1 && if_b[x][y+7] == 2 )
                B_weight[m][n] += 300;
            //12020201
            if( if_b[x][y] == 2 && if_b[x][y+1] == 1 && if_b[x][y+2] == 0 && if_b[x][y+3] == 1 && if_b[x][y+4] == 0 && if_b[x][y+5] == 1 &&
                if_b[x][y+6] == 0 && if_b[x][y+7] == 2 )
                B_weight[m][n] += 300;
            //10222001
            if( if_b[x][y] == 2 && if_b[x][y+1] == 0 && if_b[x][y+2] == 1 && if_b[x][y+3] == 1 && if_b[x][y+4] == 1 && if_b[x][y+5] == 0 &&
                if_b[x][y+6] == 0 && if_b[x][y+7] == 2 )
                B_weight[m][n] += 300;
            //10202201
            if( if_b[x][y] == 2 && if_b[x][y+1] == 0 && if_b[x][y+2] == 1 && if_b[x][y+3] == 0 && if_b[x][y+4] == 1 && if_b[x][y+5] == 1 &&
                if_b[x][y+6] == 0 && if_b[x][y+7] == 2 )
                B_weight[m][n] += 300;
            //10200221
            if( if_b[x][y] == 2 && if_b[x][y+1] == 0 && if_b[x][y+2] == 1 && if_b[x][y+3] == 0 && if_b[x][y+4] == 0 && if_b[x][y+5] == 1 &&
                if_b[x][y+6] == 1 && if_b[x][y+7] == 2 )
                B_weight[m][n] += 300;
            //10220201
            if( if_b[x][y] == 2 && if_b[x][y+1] == 0 && if_b[x][y+2] == 1 && if_b[x][y+3] == 1 && if_b[x][y+4] == 0 && if_b[x][y+5] == 1 &&
                if_b[x][y+6] == 0 && if_b[x][y+7] == 2 )
                B_weight[m][n] += 300;
            //10220021
            if( if_b[x][y] == 2 && if_b[x][y+1] == 0 && if_b[x][y+2] == 1 && if_b[x][y+3] == 1 && if_b[x][y+4] == 0 && if_b[x][y+5] == 0 &&
                if_b[x][y+6] == 1 && if_b[x][y+7] == 2 )
                B_weight[m][n] += 300;
            //10022021
            if( if_b[x][y] == 2 && if_b[x][y+1] == 0 && if_b[x][y+2] == 0 && if_b[x][y+3] == 1 && if_b[x][y+4] == 1 && if_b[x][y+5] == 0 &&
                if_b[x][y+6] == 1 && if_b[x][y+7] == 2 )
                B_weight[m][n] += 300;
            //10022201
            if( if_b[x][y] == 2 && if_b[x][y+1] == 0 && if_b[x][y+2] == 0 && if_b[x][y+3] == 1 && if_b[x][y+4] == 1 && if_b[x][y+5] == 1 &&
                if_b[x][y+6] == 0 && if_b[x][y+7] == 2 )
                B_weight[m][n] += 300;
            //10020221
            if( if_b[x][y] == 2 && if_b[x][y+1] == 0 && if_b[x][y+2] == 0 && if_b[x][y+3] == 1 && if_b[x][y+4] == 0 && if_b[x][y+5] == 1 &&
                if_b[x][y+6] == 1 && if_b[x][y+7] == 2 )
                B_weight[m][n] += 300;
            //10002221
            if( if_b[x][y] == 2 && if_b[x][y+1] == 0 && if_b[x][y+2] == 0 && if_b[x][y+3] == 0 && if_b[x][y+4] == 0 && if_b[x][y+5] == 1 &&
                if_b[x][y+6] == 1 && if_b[x][y+7] == 2 )
                B_weight[m][n] += 300;
            //10202021
            if( if_b[x][y] == 2 && if_b[x][y+1] == 0 && if_b[x][y+2] == 1 && if_b[x][y+3] == 0 && if_b[x][y+4] == 1 && if_b[x][y+5] == 0 &&
                if_b[x][y+6] == 1 && if_b[x][y+7] == 2 )
                B_weight[m][n] += 300;
                }
          }
          if_b[m][n] = 0;
      }
    }

}

void AI::B_AI_4_Horizontal_check()
{
    for(int m=0 ; m<19 ; m++)
        {
          for(int n=0 ; n<19 ; n++)
          {
              if( if_b[m][n] == 0 )
              {
              if_b[m][n] = 1;
              }
              else if( if_b[m][n] == 2 || if_b[m][n] == 1 )
              {
                  continue;
              }

              for(int x=0; x<19; x++)
              {
                  for(int y=0; y<19; y++)
                  {
       /*4개 -> 안막혔을 때*/
             //00222200
             if( if_b[x][y-1] == 0 && if_b[x][y]== 0 && if_b[x][y+1]== 1 && if_b[x][y+2]== 1 &&if_b[x][y+3] == 1 && if_b[x][y+4] == 1 &&
                 if_b[x][y+5] == 0 )
                B_weight[m][n] += 10000;
             //002022200
             if( if_b[x][y-1] == 0 && if_b[x][y]==0 && if_b[x][y+1]==1 && if_b[x][y+2]==0 && if_b[x][y+3] == 1 && if_b[x][y+4] ==1 &&
                 if_b[x][y+5]==1 &&if_b[x][y+6] ==0 && if_b[x][y+7] == 0 )
                B_weight[m][n] += 7000;
             //002220200
             if( if_b[x][y-1] == 0 && if_b[x][y]== 0 && if_b[x][y+1]== 1 && if_b[x][y+2]== 1 && if_b[x][y+3] == 1 && if_b[x][y+4] == 0 &&
                 if_b[x][y+5] ==1 &&if_b[x][y+6] == 0 && if_b[x][y+7] == 0 )
                B_weight[m][n] += 7000;
             //002202200
             if( if_b[x][y-1] == 0 && if_b[x][y]== 0 && if_b[x][y+1]== 1 && if_b[x][y+2]== 1 && if_b[x][y+3] == 0 && if_b[x][y+4] == 1 &&
                 if_b[x][y+5] == 1 && if_b[x][y+6] == 0 && if_b[x][y+7] == 0 )
                B_weight[m][n] += 7000;
             //02220020
             if( if_b[x][y]==0 && if_b[x][y+1]==1 && if_b[x][y+2]==1 && if_b[x][y+3] == 1 && if_b[x][y+4] ==0 && if_b[x][y+5] ==0 &&
                 if_b[x][y+6] ==1 && if_b[x][y+7] ==0 )
                B_weight[m][n] += 5000;
             //02002220
             if( if_b[x][y] == 0 && if_b[x][y+1] == 1 && if_b[x][y+2] == 0 && if_b[x][y+3] == 0 && if_b[x][y+4] == 1 && if_b[x][y+5] == 1 &&
                 if_b[x][y+6] == 1 && if_b[x][y+7] == 0 )
                B_weight[m][n] += 5000;
             //02202020
             if( if_b[x][y] == 0 && if_b[x][y+1] == 1 && if_b[x][y+2] == 1 && if_b[x][y+3] == 0 && if_b[x][y+4] == 1 && if_b[x][y+5] == 1 &&
                 if_b[x][y+6] == 1 && if_b[x][y+7] == 0 )
                B_weight[m][n] += 4000;
             //02020220
             if(if_b[x][y] == 0 && if_b[x][y+1] == 1 && if_b[x][y+2] == 0 && if_b[x][y+3] == 1 && if_b[x][y+4] == 0 && if_b[x][y+5] == 1 &&
                 if_b[x][y+6] == 1 && if_b[x][y+7] == 0 )
                B_weight[m][n] += 4000;

             //4개 한쪽 막혔을 때
             //122220
             if(if_b[x][y]==2 && if_b[x][y+1]==1 && if_b[x][y+2]==1 && if_b[x][y+3] == 1 && if_b[x][y+4] ==1 && if_b[x][y+5] ==0)
                B_weight[m][n] += 2500;
             //1202220
             if(if_b[x][y]==2 && if_b[x][y+1]==1 && if_b[x][y+2]==0 && if_b[x][y+3] == 1 && if_b[x][y+4] ==1 && if_b[x][y+5] ==1 &&if_b[x][y+6] ==0)
                B_weight[m][n] += 2500;
             //1220220
             if(if_b[x][y]==2 && if_b[x][y+1]==1 && if_b[x][y+2]==1 && if_b[x][y+3] ==0 && if_b[x][y+4] ==1 && if_b[x][y+5] ==1 &&if_b[x][y+6] ==0)
                B_weight[m][n] += 2500;
             //1222020
             if(if_b[x][y]==2 && if_b[x][y+1]==1 && if_b[x][y+2]==1 && if_b[x][y+3] == 1 && if_b[x][y+4] ==0 && if_b[x][y+5] ==1 &&if_b[x][y+6] ==0)
                B_weight[m][n] += 2500;
             //1022220
             if(if_b[x][y]==2 && if_b[x][y+1]==0 && if_b[x][y+2]==1 && if_b[x][y+3] == 1 && if_b[x][y+4] ==1 && if_b[x][y+5] ==1 &&if_b[x][y+6] ==0)
                B_weight[m][n] += 2500;
             //12002220
             if(if_b[x][y]==2 && if_b[x][y+1]==1 && if_b[x][y+2]==0 && if_b[x][y+3] == 0 && if_b[x][y+4] ==1 && if_b[x][y+5] ==1 &&if_b[x][y+6] ==1 &&
                 if_b[x][y+7]==0)
                B_weight[m][n] += 2500;
             //12020220
             if(if_b[x][y]==2 && if_b[x][y+1]==1 && if_b[x][y+2]==0 && if_b[x][y+3] == 1 && if_b[x][y+4] ==0 && if_b[x][y+5] ==1 &&if_b[x][y+6] ==1 &&
                 if_b[x][y+7]==0)
                B_weight[m][n] += 2500;
             //12022020
             if(if_b[x][y]==2 && if_b[x][y+1]==1 && if_b[x][y+2]==0 && if_b[x][y+3] == 1 && if_b[x][y+4] ==1 && if_b[x][y+5] ==0 &&if_b[x][y+6] ==1 &&
                 if_b[x][y+7]==0)
                B_weight[m][n] += 2500;
             //12200220
             if(if_b[x][y]==2 && if_b[x][y+1]==1 && if_b[x][y+2]==1 && if_b[x][y+3] == 0 && if_b[x][y+4] ==0 && if_b[x][y+5] ==1 &&if_b[x][y+6] ==1 &&
                 if_b[x][y+7]==0 )
                B_weight[m][n] += 2500;
             //12202020
             if(if_b[x][y]==2 && if_b[x][y+1]==1 && if_b[x][y+2]==1 && if_b[x][y+3] == 0 && if_b[x][y+4] ==1 && if_b[x][y+5] ==0 &&if_b[x][y+6] ==1 &&
                 if_b[x][y+7]==0)
                B_weight[m][n] += 2500;
             //12220020
             if(if_b[x][y]==2 && if_b[x][y+1]==1 && if_b[x][y+2]==1 && if_b[x][y+3] == 1 && if_b[x][y+4] ==0 && if_b[x][y+5] ==0 &&if_b[x][y+6] ==1 &&
                 if_b[x][y+7]==0)
                B_weight[m][n] += 2500;
             //10220220
             if(if_b[x][y]==2 && if_b[x][y+1]==0 && if_b[x][y+2]==1 && if_b[x][y+3] == 1 && if_b[x][y+4] ==0 && if_b[x][y+5] ==1 &&if_b[x][y+6] ==1 &&
                 if_b[x][y+7]==0)
                B_weight[m][n] += 2500;
             //10222020
             if(if_b[x][y]==2 && if_b[x][y+1]==0 && if_b[x][y+2]==1 && if_b[x][y+3] == 1 && if_b[x][y+4] ==1 && if_b[x][y+5] ==0 &&if_b[x][y+6] ==1 &&
                 if_b[x][y+7]==0)
                B_weight[m][n] += 2500;
             //10202220
             if(if_b[x][y]==2 && if_b[x][y+1]==0 && if_b[x][y+2]==1 && if_b[x][y+3] == 0 && if_b[x][y+4] ==1 && if_b[x][y+5] ==1 &&if_b[x][y+6] ==1 &&
                 if_b[x][y+7]==0)
                B_weight[m][n] += 2500;


             //4개 한쪽 막혔을 때 reverse
             //022221
             if(if_b[x][y]==0 && if_b[x][y+1]==1 && if_b[x][y+2]==1 && if_b[x][y+3] == 1 && if_b[x][y+4] ==1 && if_b[x][y+5] ==2)
                B_weight[m][n] += 2500;
             //0222021
             if(if_b[x][y]==0 && if_b[x][y+1]==1 && if_b[x][y+2]==1 && if_b[x][y+3] == 1 && if_b[x][y+4] ==0 && if_b[x][y+5] ==1 &&if_b[x][y+6] ==2)
                B_weight[m][n] += 2500;
             //0220221
             if(if_b[x][y]==0 && if_b[x][y+1]==1 && if_b[x][y+2]==1 && if_b[x][y+3] ==0 && if_b[x][y+4] ==1 && if_b[x][y+5] ==1 &&if_b[x][y+6] ==2)
                B_weight[m][n] += 2500;
             //0202221
             if(if_b[x][y]==0 && if_b[x][y+1]==1 && if_b[x][y+2]==0 && if_b[x][y+3] == 1 && if_b[x][y+4] ==1 && if_b[x][y+5] ==1 &&if_b[x][y+6] ==2)
                B_weight[m][n] += 2500;
             //0222201
             if(if_b[x][y]==0 && if_b[x][y+1]==1 && if_b[x][y+2]==1 && if_b[x][y+3] == 1 && if_b[x][y+4] ==1 && if_b[x][y+5] ==0 &&if_b[x][y+6] ==2)
                B_weight[m][n] += 2500;
             //02220021
             if(if_b[x][y]==0 && if_b[x][y+1]==1 && if_b[x][y+2]==1 && if_b[x][y+3] == 1 && if_b[x][y+4] ==0 && if_b[x][y+5] ==0 &&if_b[x][y+6] ==1 &&
                 if_b[x][y+7] ==2)
                B_weight[m][n] += 2500;
             //02202021
             if(if_b[x][y]==0 && if_b[x][y+1]==1 && if_b[x][y+2]==1 && if_b[x][y+3] == 0 && if_b[x][y+4] ==1 && if_b[x][y+5] ==0 &&if_b[x][y+6] ==1 &&
                 if_b[x][y+7] ==2)
                B_weight[m][n] += 2500;
             //02022021
             if(if_b[x][y]==0 && if_b[x][y+1]==1 && if_b[x][y+2]==0 && if_b[x][y+3] == 1 && if_b[x][y+4] ==1 && if_b[x][y+5] ==0 &&if_b[x][y+6] ==1 &&
                 if_b[x][y+7] ==2)
                B_weight[m][n] += 2500;
             //02200221
             if(if_b[x][y]==0 && if_b[x][y+1]==1 && if_b[x][y+2]==1 && if_b[x][y+3] == 0 && if_b[x][y+4] ==0 && if_b[x][y+5] ==1 &&if_b[x][y+6] ==1 &&
                 if_b[x][y+7] ==2 )
                B_weight[m][n] += 2500;
             //02020221
             if(if_b[x][y]==0 && if_b[x][y+1]==1 && if_b[x][y+2]==0 && if_b[x][y+3] == 1 && if_b[x][y+4] ==0 && if_b[x][y+5] ==1 &&if_b[x][y+6] ==1 &&
                 if_b[x][y+7] ==2)
                B_weight[m][n] += 2500;
             //02002221
             if(if_b[x][y]==0 && if_b[x][y+1]==1 && if_b[x][y+2]==0 && if_b[x][y+3] == 0 && if_b[x][y+4] ==1 && if_b[x][y+5] ==1 &&if_b[x][y+6] ==1 &&
                 if_b[x][y+7] ==2)
                B_weight[m][n] += 2500;
             //02202201
             if(if_b[x][y]==0 && if_b[x][y+1]==1 && if_b[x][y+2]==1 && if_b[x][y+3] == 0 && if_b[x][y+4] ==1 && if_b[x][y+5] ==1 &&if_b[x][y+6] ==0 &&
                 if_b[x][y+7] ==2)
                B_weight[m][n] += 2500;
             //02022201
             if(if_b[x][y]==0 && if_b[x][y+1]==1 && if_b[x][y+2]==0 && if_b[x][y+3] == 1 && if_b[x][y+4] ==1 && if_b[x][y+5] ==1 &&if_b[x][y+6] ==0 &&
                 if_b[x][y+7] ==2)
                B_weight[m][n] += 2500;
             //02220201
             if(if_b[x][y]==0 && if_b[x][y+1]==1 && if_b[x][y+2]==1 && if_b[x][y+3] == 1 && if_b[x][y+4] ==0 && if_b[x][y+5] ==1 &&if_b[x][y+6] ==0 &&
                 if_b[x][y+7] ==2)
                B_weight[m][n] += 2500;



             //양쪽 다 막혔을 때

             //12022021
             if(if_b[x][y]==2 && if_b[x][y+1]==1 && if_b[x][y+2]==0 && if_b[x][y+3] == 1 && if_b[x][y+4] ==1 && if_b[x][y+5] ==0 &&if_b[x][y+6] ==1 &&if_b[x][y+7] ==2 )
                B_weight[m][n] += 1000;
             //12200221
             if(if_b[x][y]==2 && if_b[x][y+1]==1 && if_b[x][y+2]==1 && if_b[x][y+3] == 0 && if_b[x][y+4] ==0 && if_b[x][y+5] ==1 &&if_b[x][y+6] ==1 &&if_b[x][y+7] ==2 )
                B_weight[m][n] += 1000;
             //12220021
             if(if_b[x][y]==2 && if_b[x][y+1]==1 && if_b[x][y+2]==1 && if_b[x][y+3] == 1 && if_b[x][y+4] ==0 && if_b[x][y+5] ==0 &&if_b[x][y+6] ==1 &&if_b[x][y+7] ==2)
                B_weight[m][n] += 1000;
             //12002221
             if(if_b[x][y]==2 && if_b[x][y+1]==1 && if_b[x][y+2]==0 && if_b[x][y+3] == 0 && if_b[x][y+4] ==1 && if_b[x][y+5] ==1 &&if_b[x][y+6] ==1 &&if_b[x][y+7] ==2 )
                B_weight[m][n] += 1000;
             //12202021
             if(if_b[x][y]==2 && if_b[x][y+1]==1 && if_b[x][y+2]==1 && if_b[x][y+3] == 0 && if_b[x][y+4] ==1 && if_b[x][y+5] ==1 &&if_b[x][y+6] ==1 &&if_b[x][y+7] ==2)
                B_weight[m][n] += 1000;
             //12020221
             if(if_b[x][y]==2 && if_b[x][y+1]==1 && if_b[x][y+2]==0 && if_b[x][y+3] == 1 && if_b[x][y+4] ==0 && if_b[x][y+5] ==1 &&if_b[x][y+6] ==1 &&if_b[x][y+7] ==2 )
                B_weight[m][n] += 1000;
             //10222201
           if(if_b[x][y]==2 && if_b[x][y+1]==0 && if_b[x][y+2]==1 && if_b[x][y+3] == 1 && if_b[x][y+4] ==1 && if_b[x][y+5] ==1 &&if_b[x][y+6] ==0 &&if_b[x][y+7] ==2 )
                B_weight[m][n] += 1000;
           //10222021
           if(if_b[x][y]==2 && if_b[x][y+1]==0 && if_b[x][y+2]==1 && if_b[x][y+3] == 1 && if_b[x][y+4] ==1 && if_b[x][y+5] ==0 &&if_b[x][y+6] ==1 &&if_b[x][y+7] ==2 )
                B_weight[m][n] += 1000;
           //10220221
           if(if_b[x][y]==2 && if_b[x][y+1]==0 && if_b[x][y+2]==1 && if_b[x][y+3] == 1 && if_b[x][y+4] ==0 && if_b[x][y+5] ==1 &&if_b[x][y+6] ==1 &&if_b[x][y+7] ==2 )
                B_weight[m][n] += 1000;
            //10202221
           if(if_b[x][y]==2 && if_b[x][y+1]==0 && if_b[x][y+2]==1 && if_b[x][y+3] == 0 && if_b[x][y+4] ==1 && if_b[x][y+5] ==1 &&if_b[x][y+6] ==1 &&if_b[x][y+7] ==2 )
                B_weight[m][n] += 1000;
           //10022221
           if(if_b[x][y]==2 && if_b[x][y+1]==0 && if_b[x][y+2]==0 && if_b[x][y+3] == 1 && if_b[x][y+4] ==1 && if_b[x][y+5] ==1 &&if_b[x][y+6] ==1 &&if_b[x][y+7] ==2 )
                B_weight[m][n] += 1000;
           //12022201
           if(if_b[x][y]==2 && if_b[x][y+1]==1 && if_b[x][y+2]==0 && if_b[x][y+3] == 1 && if_b[x][y+4] ==1 && if_b[x][y+5] ==1 &&if_b[x][y+6] ==0 &&if_b[x][y+7] ==2 )
                B_weight[m][n] += 1000;
           //12202201
           if(if_b[x][y]==2 && if_b[x][y+1]==1 && if_b[x][y+2]==1 && if_b[x][y+3] == 0 && if_b[x][y+4] ==1 && if_b[x][y+5] ==1 &&if_b[x][y+6] ==0 &&if_b[x][y+7] ==2 )
                B_weight[m][n] += 1000;
           //12220201
           if(if_b[x][y]==2 && if_b[x][y+1]==1 && if_b[x][y+2]==1 && if_b[x][y+3] == 1 && if_b[x][y+4] ==0 && if_b[x][y+5] ==1 &&if_b[x][y+6] ==0 &&if_b[x][y+7] ==2 )
                B_weight[m][n] += 1000;
           //12222001
           if(if_b[x][y]==2 && if_b[x][y+1]==1 && if_b[x][y+2]==1 && if_b[x][y+3] == 1 && if_b[x][y+4] ==1 && if_b[x][y+5] ==0 &&if_b[x][y+6] ==0 &&if_b[x][y+7] ==2 )
                B_weight[m][n] += 1000;
             }
             }
             if_b[m][n] = 0;
             }
             }


}

void AI::B_AI_2_Vertical_check()
{
    for(int m=0 ; m<19 ; m++)
        {
          for(int n=0 ; n<19 ; n++)
          {
              if( if_b[m][n] == 0 )
              {
              if_b[m][n] = 1;
              }
              else if( if_b[m][n] == 2 || if_b[m][n] == 1 )
              {
                  continue;
              }

              for(int x=0; x<19; x++)
              {
                  for(int y=0; y<19; y++)
                  {
                //00022000
                if( if_b[x-2][y] == 0 && if_b[x-1][y] == 0 && if_b[x][y] == 0 && if_b[x+1][y] == 1 && if_b[x+2][y] == 1 &&
                    if_b[x+3][y] == 0 && if_b[x+4][y] == 0 && if_b[x+5][y] == 0 )
                    B_weight[m][n] += 2000;
                //0020200
                if( if_b[x-1][y] == 0 && if_b[x][y] == 0 && if_b[x+1][y] == 1 && if_b[x+2][y] == 0 && if_b[x+3][y] == 1 && if_b[x+4][y] == 0 &&
                    if_b[x+5][y] == 0 )
                    B_weight[m][n] += 1500;
                //020020
                if( if_b[x][y] == 0 && if_b[x+1][y] == 1 && if_b[x+2][y] == 0 && if_b[x+3][y] == 0 && if_b[x+4][y] == 1 && if_b[x+5][y] == 0 )
                    B_weight[m][n] += 1000;
                //여기까지 양쪽에 안 막힌, 흰 돌이 2개가 발견 될 때 경우의 수들

                //122000
                if( if_b[x][y] == 2 && if_b[x+1][y] == 1 && if_b[x+2][y] == 1 && if_b[x+3][y] == 0 && if_b[x+4][y] == 0 && if_b[x+5][y] == 0 )
                    B_weight[m][n] += 500;
                //120200
                if( if_b[x][y] == 2 && if_b[x+1][y] == 1 && if_b[x+2][y] == 0 && if_b[x+3][y] == 1 && if_b[x+4][y] == 0 && if_b[x+5][y] == 0 )
                    B_weight[m][n] += 500;
                //120020
                if( if_b[x][y] == 2 && if_b[x+1][y] == 1 && if_b[x+2][y] == 0 && if_b[x+3][y] == 0 && if_b[x+4][y] == 1 && if_b[x+5][y] == 0 )
                    B_weight[m][n] += 500;
                //102200
                if( if_b[x][y] == 2 && if_b[x+1][y] == 0 && if_b[x+2][y] == 1 && if_b[x+3][y] == 1 && if_b[x+4][y] == 0 && if_b[x+5][y] == 0 )
                    B_weight[m][n] += 800;
                //102020
                if( if_b[x][y] == 2 && if_b[x+1][y] == 0 && if_b[x+2][y] == 1 && if_b[x+3][y] == 0 && if_b[x+4][y] == 1 && if_b[x+5][y] == 0 )
                    B_weight[m][n] += 800;
                //여기까지 왼쪽에 검은돌로 막힌 경우.
                //오른쪽에 검은돌로 막힌 경우는 이 대칭으로만 작성해주면됌

                //000221
                if( if_b[x-2][y] == 0 && if_b[x-1][y] == 0 && if_b[x][y] == 0 && if_b[x+1][y] == 1 && if_b[x+2][y] == 1 && if_b[x+3][y] == 2 )
                    B_weight[m][n] += 500;
                //002021
                if( if_b[x-1][y] == 0 && if_b[x][y] == 0 && if_b[x+1][y] == 1 && if_b[x+2][y] == 0 && if_b[x+3][y] == 1 && if_b[x+4][y] == 2 )
                    B_weight[m][n] += 500;
                //020021
                if( if_b[x][y] == 0 && if_b[x+1][y] == 1 && if_b[x+2][y] == 0 && if_b[x+3][y] == 0 && if_b[x+4][y] == 1 && if_b[x+5][y] == 2 )
                    B_weight[m][n] += 500;
                //002201
                if( if_b[x-1][y] == 0 && if_b[x][y] == 0 && if_b[x+1][y] == 1 && if_b[x+2][y] == 1 && if_b[x+3][y] == 0 && if_b[x+4][y] == 2 )
                    B_weight[m][n] += 800;
                //020201
                if( if_b[x][y] == 0 && if_b[x+1][y] == 1 && if_b[x+2][y] == 0 && if_b[x+3][y] == 1 && if_b[x+4][y] == 0 && if_b[x+5][y] == 2 )
                    B_weight[m][n] += 800;
                //여기까지 한쪽이 막힌 경우.
                //그 다음은 양쪽이 막힌 경우. 양쪽이 막힌 경우는 안이 6칸일 경우만 따지자.

                //12200001
                if( if_b[x][y] == 2 && if_b[x+1][y] == 1 && if_b[x+2][y] == 1 && if_b[x+3][y] == 0 && if_b[x+4][y] == 0 && if_b[x+5][y] == 0 &&
                    if_b[x+6][y] == 0 && if_b[x+7][y] == 2 )
                    B_weight[m][n] += 300;
                //12020001
                if( if_b[x][y] == 2 && if_b[x+1][y] == 1 && if_b[x+2][y] == 0 && if_b[x+3][y] == 1 && if_b[x+4][y] == 0 && if_b[x+5][y] == 0 &&
                    if_b[x+6][y] == 0 && if_b[x+7][y] == 2 )
                    B_weight[m][n] += 300;
                //12002001
                if( if_b[x][y] == 2 && if_b[x+1][y] == 1 && if_b[x+2][y] == 0 && if_b[x+3][y] == 0 && if_b[x+4][y] == 1 && if_b[x+5][y] == 0 &&
                    if_b[x+6][y] == 0 && if_b[x+7][y] == 2 )
                    B_weight[m][n] += 300;
                //12000201
                if( if_b[x][y] == 2 && if_b[x+1][y] == 1 && if_b[x+2][y] == 0 && if_b[x+3][y] == 0 && if_b[x+4][y] == 0 && if_b[x+5][y] == 1 &&
                    if_b[x+6][y] == 0 && if_b[x+7][y] == 2 )
                    B_weight[m][n] += 300;
                //12000021
                if( if_b[x][y] == 2 && if_b[x+1][y] == 1 && if_b[x+2][y] == 0 && if_b[x+3][y] == 0 && if_b[x+4][y] == 0 && if_b[x+5][y] == 0 &&
                    if_b[x+6][y] == 1 && if_b[x+7][y] == 2 )
                    B_weight[m][n] += 300;
                //10220001
                if( if_b[x][y] == 2 && if_b[x+1][y] == 0 && if_b[x+2][y] == 1 && if_b[x+3][y] == 1 && if_b[x+4][y] == 0 && if_b[x+5][y] == 0 &&
                    if_b[x+6][y] == 0 && if_b[x+7][y] == 2 )
                    B_weight[m][n] += 300;
                //10202001
                if( if_b[x][y] == 2 && if_b[x+1][y] == 0 && if_b[x+2][y] == 1 && if_b[x+3][y] == 0 && if_b[x+4][y] == 1 && if_b[x+5][y] == 0 &&
                    if_b[x+6][y] == 0 && if_b[x+7][y] == 2 )
                    B_weight[m][n] += 300;
                //10200201
                if( if_b[x][y] == 2 && if_b[x+1][y] == 0 && if_b[x+2][y] == 1 && if_b[x+3][y] == 0 && if_b[x+4][y] == 0 && if_b[x+5][y] == 1 &&
                    if_b[x+6][y] == 0 && if_b[x+7][y] == 2 )
                    B_weight[m][n] += 300;
                //10200021
                if( if_b[x][y] == 2 && if_b[x+1][y] == 0 && if_b[x+2][y] == 1 && if_b[x+3][y] == 0 && if_b[x+4][y] == 0 && if_b[x+5][y] == 0 &&
                    if_b[x+6][y] == 1 && if_b[x+7][y] == 2 )
                    B_weight[m][n] += 300;
                //10022001
                if( if_b[x][y] == 2 && if_b[x+1][y] == 0 && if_b[x+2][y] == 0 && if_b[x+3][y] == 1 && if_b[x+4][y] == 1 && if_b[x+5][y] == 0 &&
                    if_b[x+6][y] == 0 && if_b[x+7][y] == 2 )
                    B_weight[m][n] += 300;
                //10020201
                if( if_b[x][y] == 2 && if_b[x+1][y] == 0 && if_b[x+2][y] == 0 && if_b[x+3][y] == 1 && if_b[x+4][y] == 0 && if_b[x+5][y] == 1 &&
                    if_b[x+6][y] == 0 && if_b[x+7][y] == 2 )
                    B_weight[m][n] += 300;
                //10020021
                if( if_b[x][y] == 2 && if_b[x+1][y] == 0 && if_b[x+2][y] == 0 && if_b[x+3][y] == 1 && if_b[x+4][y] == 0 && if_b[x+5][y] == 0 &&
                    if_b[x+6][y] == 1 && if_b[x+7][y] == 2 )
                    B_weight[m][n] += 300;
                //10002201
                if( if_b[x][y] == 2 && if_b[x+1][y] == 0 && if_b[x+2][y] == 0 && if_b[x+3][y] == 0 && if_b[x+4][y] == 1 && if_b[x+5][y] == 1 &&
                    if_b[x+6][y] == 0 && if_b[x+7][y] == 2 )
                    B_weight[m][n] += 300;
                //10002021
                if( if_b[x][y] == 2 && if_b[x+1][y] == 0 && if_b[x+2][y] == 0 && if_b[x+3][y] == 1 && if_b[x+4][y] == 0 && if_b[x+5][y] == 1 &&
                    if_b[x+6][y] == 0 && if_b[x+7][y] == 2 )
                    B_weight[m][n] += 300;
                //10000221
                if( if_b[x][y] == 2 && if_b[x+1][y] == 0 && if_b[x+2][y] == 0 && if_b[x+3][y] == 0 && if_b[x+4][y] == 0 && if_b[x+5][y] == 1 &&
                    if_b[x+6][y] == 1 && if_b[x+7][y] == 2 )
                    B_weight[m][n] += 300;
                  }
              }
              if_b[m][n] = 0;
          }
        }

}

void AI::B_AI_3_Vertical_check()
{
    for(int m=0 ; m<19 ; m++)
    {
      for(int n=0 ; n<19 ; n++)
      {
          if( if_b[m][n] == 0 )
          {
          if_b[m][n] = 1;
          }
          else if( if_b[m][n] == 2 || if_b[m][n] == 1 )
          {
              continue;
          }

          for(int x=0; x<19; x++)
          {
              for(int y=0; y<19; y++)
              {
            //000222000
            if( if_b[x-1][y] == 0 && if_b[x][y] == 0 && if_b[x+1][y] == 1 && if_b[x+2][y] == 1 && if_b[x+3][y] == 1&& if_b[x+4][y]==0 &&
                if_b[x+5][y] == 0 )
                B_weight[m][n] += 5000;
            //00202200
            if( if_b[x-1][y] == 0 && if_b[x][y] == 0 && if_b[x+1][y] == 1 && if_b[x+2][y] == 0 && if_b[x+3][y] == 1 && if_b[x+4][y] == 1 &&
                if_b[x+5][y]==0 && if_b[x+6][y] == 0 )
                B_weight[m][n] += 3500;
            //00220200
            if( if_b[x-1][y] == 0 && if_b[x][y] == 0 && if_b[x+1][y] == 1 && if_b[x+2][y] == 1 && if_b[x+3][y] == 0 && if_b[x+4][y] == 1 &&
                if_b[x+5][y] == 0 && if_b[x+6][y] == 0 )
                B_weight[m][n] += 3500;
            //0200220
            if( if_b[x][y] == 0 && if_b[x+1][y] == 1 && if_b[x+2][y] == 0 && if_b[x+3][y] == 0 && if_b[x+4][y] == 1 && if_b[x+5][y] == 1
                &&if_b[x+6][y] ==0 )
                B_weight[m][n] += 3000;
            //0202020
            if( if_b[x][y] == 0 && if_b[x+1][y] == 1 && if_b[x+2][y] == 0 && if_b[x+3][y] == 1 && if_b[x+4][y] == 0 && if_b[x+5][y] == 1
                &&if_b[x+6][y]==0 )
                B_weight[m][n] += 3000;
            //0220020
            if( if_b[x][y] == 0 && if_b[x+1][y] == 1 && if_b[x+2][y] == 1 && if_b[x+3][y] == 0 && if_b[x+4][y] == 0 && if_b[x+5][y] == 1
                && if_b[x+6][y] ==0 )
                B_weight[m][n] += 3000;
            //여기까지 양쪽에 안 막힌, 흰 돌이 2개가 발견 될 때 경우의 수들

            //122200
            if( if_b[x][y] == 2 && if_b[x+1][y] == 1 && if_b[x+2][y] == 1 && if_b[x+3][y] == 1 && if_b[x+4][y] ==0 && if_b[x+5][y] == 0 )
                B_weight[m][n] += 1000;
            //1202200
            if( if_b[x][y] == 2 && if_b[x+1][y] == 1 && if_b[x+2][y] == 0 && if_b[x+3][y] == 1 && if_b[x+4][y] == 1 && if_b[x+5][y] ==0 &&
                if_b[x][y] == 0 )
                B_weight[m][n] += 1000;
            //1220200
            if( if_b[x][y] == 2 && if_b[x+1][y] == 1 && if_b[x+2][y] == 1 && if_b[x+3][y] == 0 && if_b[x+4][y] == 1 && if_b[x+5][y] == 0 &&
                if_b[x+6][y] == 0 )
                B_weight[m][n] += 1000;
            //1022200
            if( if_b[x][y] == 2 && if_b[x+1][y] == 0 && if_b[x+2][y] == 1 && if_b[x+3][y] == 1 && if_b[x+4][y] == 1 && if_b[x+5][y] ==0 &&
                if_b[x+6][y] == 0 )
                B_weight[m][n] += 1300;
            //1200220
            if( if_b[x][y] == 2 && if_b[x+1][y] == 1 && if_b[x+2][y] == 0 && if_b[x+3][y] == 0 && if_b[x+4][y] == 1 && if_b[x+5][y] == 1 &&
            if_b[x+6][y] ==0 )
                B_weight[m][n] += 1300;
            //1220020
            if( if_b[x][y] == 2 && if_b[x][y] == 1 && if_b[x][y] == 1 && if_b[x][y] == 0 && if_b[x][y] == 0 && if_b[x][y] == 1 &&
                if_b[x][y] == 0 )
                B_weight[m][n] += 1000;
            //1202020
            if( if_b[x][y] == 2 && if_b[x+1][y] == 1 && if_b[x+2][y] == 0 && if_b[x+3][y] == 1 && if_b[x+4][y] == 0 && if_b[x+5][y] == 1 &&
                if_b[x+6][y] ==0 )
                B_weight[m][n] += 1000;
            //1020220
            if( if_b[x][y] == 2 && if_b[x+1][y] == 0 && if_b[x+2][y] == 1 && if_b[x+3][y] == 0 && if_b[x+4][y] == 1 && if_b[x+5][y] == 1 &&
                if_b[x+6][y] == 0)
                B_weight[m][n] += 1300;

            //여기까지 왼쪽에 검은돌로 막힌 경우.
            //오른쪽에 검은돌로 막힌 경우는 이 대칭으로만 작성해주면됌

            //002221
            if( if_b[x-1][y] == 0 && if_b[x][y] == 0 && if_b[x+1][y] == 1 && if_b[x+2][y] == 1 && if_b[x+3][y] == 1 && if_b[x+4][y] == 2 )
                B_weight[m][n] += 1000;
            //0022021
            if( if_b[x-1][y] == 0 && if_b[x][y] == 0 && if_b[x+1][y] == 1 && if_b[x+2][y] == 1 && if_b[x+3][y] == 0 && if_b[x+4][y] == 1 &&
                if_b[x+5][y]==2 )
                B_weight[m][n] += 1000;
            //0020221
            if( if_b[x-1][y] == 0 && if_b[x][y] == 0 && if_b[x+1][y] == 1 && if_b[x+2][y] == 0 && if_b[x+3][y] == 1 && if_b[x+4][y] == 1 &&
                if_b[x+5][y] == 2 )
                B_weight[m][n] += 1000;
            //0022201
            if( if_b[x-1][y] == 0 && if_b[x][y] == 0 && if_b[x+1][y] == 1 && if_b[x+2][y] == 1 && if_b[x+3][y] == 1 && if_b[x+4][y] == 0 &&
                if_b[x+5][y] == 2 )
                B_weight[m][n] += 1300;
            //0220021
            if( if_b[x][y] == 0 && if_b[x][y] == 1 && if_b[x][y] == 1 && if_b[x][y] == 0 && if_b[x][y] == 0 && if_b[x][y] == 1 &&
                if_b[x][y] == 2 )
                B_weight[m][n] += 1300;
            //0200221
            if( if_b[x][y] == 0 && if_b[x+1][y] == 1 && if_b[x+2][y] == 0 && if_b[x+3][y] == 0 && if_b[x+4][y] == 1 && if_b[x+5][y] == 1 &&
                if_b[x+6][y] == 2 )
                B_weight[m][n] += 1000;
            //0202021
            if( if_b[x][y] == 0 && if_b[x+1][y] == 1 && if_b[x+2][y] == 0 && if_b[x+3][y] == 1 && if_b[x+4][y] == 0 && if_b[x+5][y] == 1 &&
                if_b[x+6][y] == 2 )
                B_weight[m][n] += 1000;
            //0220201
            if( if_b[x][y] == 0 && if_b[x+1][y] == 1 && if_b[x+2][y] == 1 && if_b[x+3][y] == 0 && if_b[x+4][y] == 1 && if_b[x+5][y] == 0 &&
                if_b[x+6][y] == 2 )
                B_weight[m][n] += 1300;

            //여기까지 한쪽이 막힌 경우.
            //그 다음은 양쪽이 막힌 경우. 양쪽이 막힌 경우는 안이 6칸일 경우만 따지자.

            //12220001
            if( if_b[x][y] == 2 && if_b[x+1][y] == 1 && if_b[x+2][y] == 1 && if_b[x+3][y] == 1 && if_b[x+4][y] == 0 && if_b[x+5][y] == 0 &&
                if_b[x+6][y] == 0 && if_b[x+7][y] == 2 )
                B_weight[m][n] += 300;
            //12022001
            if( if_b[x][y] == 2 && if_b[x+1][y] == 1 && if_b[x+2][y] == 0 && if_b[x+3][y] == 1 && if_b[x+4][y] == 1 && if_b[x+5][y] == 0 &&
                if_b[x+6][y] == 0 && if_b[x+7][y] == 2 )
                B_weight[m][n] += 300;
            //12002201
            if( if_b[x][y] == 2 && if_b[x+1][y] == 1 && if_b[x+2][y] == 0 && if_b[x+3][y] == 0 && if_b[x+4][y] == 1 && if_b[x+5][y] == 1 &&
                if_b[x+6][y] == 0 && if_b[x+7][y] == 2 )
                B_weight[m][n] += 300;
            //12000221
            if( if_b[x][y] == 2 && if_b[x+1][y] == 1 && if_b[x+2][y] == 0 && if_b[x+3][y] == 0 && if_b[x+4][y] == 0 && if_b[x+5][y] == 1 &&
                if_b[x+6][y] == 1 && if_b[x+7][y] == 2 )
                B_weight[m][n] += 300;
            //12202001
            if( if_b[x][y] == 2 && if_b[x+1][y] == 1 && if_b[x+2][y] == 1 && if_b[x+3][y] == 0 && if_b[x+4][y] == 1 && if_b[x+5][y] == 0 &&
                if_b[x+6][y] == 0 && if_b[x+7][y] == 2 )
                B_weight[m][n] += 300;
            //12200201
            if( if_b[x][y] == 2 && if_b[x+1][y] == 1 && if_b[x+2][y] == 1 && if_b[x+3][y] == 0 && if_b[x+4][y] == 0 && if_b[x+5][y] == 1 &&
                if_b[x+6][y] == 0 && if_b[x+7][y] == 2 )
                B_weight[m][n] += 300;
            //12200021
            if( if_b[x][y] == 2 && if_b[x+1][y] == 1 && if_b[x+2][y] == 1 && if_b[x+3][y] == 0 && if_b[x+4][y] == 0 && if_b[x+5][y] == 0 &&
                if_b[x+6][y] == 1 && if_b[x+7][y] == 2 )
                B_weight[m][n] += 300;
            //12002021
            if( if_b[x][y] == 2 && if_b[x+1][y] == 1 && if_b[x+2][y] == 0 && if_b[x+3][y] == 0 && if_b[x+4][y] == 1 && if_b[x+5][y] == 0 &&
                if_b[x+6][y] == 1 && if_b[x+7][y] == 2 )
                B_weight[m][n] += 300;
            //12020021
            if( if_b[x][y] == 2 && if_b[x+1][y] == 1 && if_b[x+2][y] == 0 && if_b[x+3][y] == 1 && if_b[x+4][y] == 0 && if_b[x+5][y] == 0 &&
                if_b[x+6][y] == 1 && if_b[x+7][y] == 2 )
                B_weight[m][n] += 300;
            //12020201
            if( if_b[x][y] == 2 && if_b[x+1][y] == 1 && if_b[x+2][y] == 0 && if_b[x+3][y] == 1 && if_b[x+4][y] == 0 && if_b[x+5][y] == 1 &&
                if_b[x+6][y] == 0 && if_b[x+7][y] == 2 )
                B_weight[m][n] += 300;
            //10222001
            if( if_b[x][y] == 2 && if_b[x+1][y] == 0 && if_b[x+2][y] == 1 && if_b[x+3][y] == 1 && if_b[x+4][y] == 1 && if_b[x+5][y] == 0 &&
                if_b[x+6][y] == 0 && if_b[x+7][y] == 2 )
                B_weight[m][n] += 300;
            //10202201
            if( if_b[x][y] == 2 && if_b[x+1][y] == 0 && if_b[x+2][y] == 1 && if_b[x+3][y] == 0 && if_b[x+4][y] == 1 && if_b[x+5][y] == 1 &&
                if_b[x+6][y] == 0 && if_b[x+7][y] == 2 )
                B_weight[m][n] += 300;
            //10200221
            if( if_b[x][y] == 2 && if_b[x+1][y] == 0 && if_b[x+2][y] == 1 && if_b[x+3][y] == 0 && if_b[x+4][y] == 0 && if_b[x+5][y] == 1 &&
                if_b[x+6][y] == 1 && if_b[x+7][y] == 2 )
                B_weight[m][n] += 300;
            //10220201
            if( if_b[x][y] == 2 && if_b[x+1][y] == 0 && if_b[x+2][y] == 1 && if_b[x+3][y] == 1 && if_b[x+4][y] == 0 && if_b[x+5][y] == 1 &&
                if_b[x+6][y] == 0 && if_b[x+7][y] == 2 )
                B_weight[m][n] += 300;
            //10220021
            if( if_b[x][y] == 2 && if_b[x+1][y] == 0 && if_b[x+2][y] == 1 && if_b[x+3][y] == 1 && if_b[x+4][y] == 0 && if_b[x+5][y] == 0 &&
                if_b[x+6][y] == 1 && if_b[x+7][y] == 2 )
                B_weight[m][n] += 300;
            //10022021
            if( if_b[x][y] == 2 && if_b[x+1][y] == 0 && if_b[x+2][y] == 0 && if_b[x+3][y] == 1 && if_b[x+4][y] == 1 && if_b[x+5][y] == 0 &&
                if_b[x+6][y] == 1 && if_b[x+7][y] == 2 )
                B_weight[m][n] += 300;
            //10022201
            if( if_b[x][y] == 2 && if_b[x+1][y] == 0 && if_b[x+2][y] == 0 && if_b[x+3][y] == 1 && if_b[x+4][y] == 1 && if_b[x+5][y] == 1 &&
                if_b[x+6][y] == 0 && if_b[x+7][y] == 2 )
                B_weight[m][n] += 300;
            //10020221
            if( if_b[x][y] == 2 && if_b[x+1][y] == 0 && if_b[x+2][y] == 0 && if_b[x+3][y] == 1 && if_b[x+4][y] == 0 && if_b[x+5][y] == 1 &&
                if_b[x+6][y] == 1 && if_b[x+7][y] == 2 )
                B_weight[m][n] += 300;
            //10002221
            if( if_b[x][y] == 2 && if_b[x+1][y] == 0 && if_b[x+2][y] == 0 && if_b[x+3][y] == 0 && if_b[x+4][y] == 0 && if_b[x+5][y] == 1 &&
                if_b[x+6][y] == 1 && if_b[x+7][y] == 2 )
                B_weight[m][n] += 300;
            //10202021
            if( if_b[x][y] == 2 && if_b[x+1][y] == 0 && if_b[x+2][y] == 1 && if_b[x+3][y] == 0 && if_b[x+4][y] == 1 && if_b[x+5][y] == 0 &&
                if_b[x+6][y] == 1 && if_b[x+7][y] == 2 )
                B_weight[m][n] += 300;
                }
          }
          if_b[m][n] = 0;
      }
    }

}

void AI::B_AI_4_Vertical_check()
{
    for(int m=0 ; m<19 ; m++)
        {
          for(int n=0 ; n<19 ; n++)
          {
              if( if_b[m][n] == 0 )
              {
              if_b[m][n] = 1;
              }
              else if( if_b[m][n] == 2 || if_b[m][n] == 1 )
              {
                  continue;
              }

              for(int x=0; x<19; x++)
              {
                  for(int y=0; y<19; y++)
                  {
                        /*4개 -> 안막혔을 때*/
             //00222200
             if( if_b[x-1][y] == 0 && if_b[x][y]== 0 && if_b[x+1][y]== 1 && if_b[x+2][y]== 1 &&if_b[x+3][y] == 1 && if_b[x+4][y] == 1 &&
                 if_b[x+5][y] == 0 )
                B_weight[m][n] += 10000;
             //002022200
             if( if_b[x-1][y] == 0 && if_b[x][y]==0 && if_b[x+1][y]==1 && if_b[x+2][y]==0 && if_b[x+3][y] == 1 && if_b[x+4][y] ==1 &&
                 if_b[x+5][y]==1 &&if_b[x+6][y] ==0 && if_b[x+7][y] == 0 )
                B_weight[m][n] += 7000;
             //002220200
             if( if_b[x-1][y] == 0 && if_b[x][y]== 0 && if_b[x+1][y]== 1 && if_b[x+2][y]== 1 && if_b[x+3][y] == 1 && if_b[x+4][y] == 0 &&
                 if_b[x+5][y] ==1 &&if_b[x+6][y] == 0 && if_b[x+7][y] == 0 )
                B_weight[m][n] += 7000;
             //002202200
             if( if_b[x-1][y] == 0 && if_b[x][y]== 0 && if_b[x+1][y]== 1 && if_b[x+2][y]== 1 && if_b[x+3][y] == 0 && if_b[x+4][y] == 1 &&
                 if_b[x+5][y] == 1 && if_b[x+6][y] == 0 && if_b[x+7][y] == 0 )
                B_weight[m][n] += 7000;
             //02220020
             if( if_b[x][y]==0 && if_b[x+1][y]==1 && if_b[x+2][y]==1 && if_b[x+3][y] == 1 && if_b[x+4][y] ==0 && if_b[x+5][y] ==0 &&
                 if_b[x+6][y] ==1 && if_b[x+7][y] ==0 )
                B_weight[m][n] += 5000;
             //02002220
             if( if_b[x][y] == 0 && if_b[x+1][y] == 1 && if_b[x+2][y] == 0 && if_b[x+3][y] == 0 && if_b[x+4][y] == 1 && if_b[x+5][y] == 1 &&
                 if_b[x+6][y] == 1 && if_b[x+7][y] == 0 )
                B_weight[m][n] += 5000;
             //02202020
             if( if_b[x][y] == 0 && if_b[x+1][y] == 1 && if_b[x+2][y] == 1 && if_b[x+3][y] == 0 && if_b[x+4][y] == 1 && if_b[x+5][y] == 1 &&
                 if_b[x+6][y] == 1 && if_b[x+7][y] == 0 )
                B_weight[m][n] += 4000;
             //02020220
             if(if_b[x][y] == 0 && if_b[x+1][y] == 1 && if_b[x+2][y] == 0 && if_b[x+3][y] == 1 && if_b[x+4][y] == 0 && if_b[x+5][y] == 1 &&
                 if_b[x+6][y] == 1 && if_b[x+7][y] == 0 )
                B_weight[m][n] += 4000;

             //4개 한쪽 막혔을 때
             //122220
             if(if_b[x][y]==2 && if_b[x+1][y]==1 && if_b[x+2][y]==1 && if_b[x+3][y] == 1 && if_b[x+4][y] ==1 && if_b[x+5][y] ==0)
                B_weight[m][n] += 2500;
             //1202220
             if(if_b[x][y]==2 && if_b[x+1][y]==1 && if_b[x+2][y]==0 && if_b[x+3][y] == 1 && if_b[x+4][y] ==1 && if_b[x+5][y] ==1 &&if_b[x+6][y] ==0)
                B_weight[m][n] += 2500;
             //1220220
             if(if_b[x][y]==2 && if_b[x+1][y]==1 && if_b[x+2][y]==1 && if_b[x+3][y] ==0 && if_b[x+4][y] ==1 && if_b[x+5][y] ==1 &&if_b[x+6][y] ==0)
                B_weight[m][n] += 2500;
             //1222020
             if(if_b[x][y]==2 && if_b[x+1][y]==1 && if_b[x+2][y]==1 && if_b[x+3][y] == 1 && if_b[x+4][y] ==0 && if_b[x+5][y] ==1 &&if_b[x+6][y] ==0)
                B_weight[m][n] += 2500;
             //1022220
             if(if_b[x][y]==2 && if_b[x+1][y]==0 && if_b[x+2][y]==1 && if_b[x+3][y] == 1 && if_b[x+4][y] ==1 && if_b[x+5][y] ==1 &&if_b[x+6][y] ==0)
                B_weight[m][n] += 2500;
             //12002220
             if(if_b[x][y]==2 && if_b[x+1][y]==1 && if_b[x+2][y]==0 && if_b[x+3][y] == 0 && if_b[x+4][y] ==1 && if_b[x+5][y] ==1 &&if_b[x+6][y] ==1 &&
                 if_b[x+7][y]==0)
                B_weight[m][n] += 2500;
             //12020220
             if(if_b[x][y]==2 && if_b[x+1][y]==1 && if_b[x+2][y]==0 && if_b[x+3][y] == 1 && if_b[x+4][y] ==0 && if_b[x+5][y] ==1 &&if_b[x+6][y] ==1 &&
                 if_b[x+7][y]==0)
                B_weight[m][n] += 2500;
             //12022020
             if(if_b[x][y]==2 && if_b[x+1][y]==1 && if_b[x+2][y]==0 && if_b[x+3][y] == 1 && if_b[x+4][y] ==1 && if_b[x+5][y] ==0 &&if_b[x+6][y] ==1 &&
                 if_b[x+7][y]==0)
                B_weight[m][n] += 2500;
             //12200220
             if(if_b[x][y]==2 && if_b[x+1][y]==1 && if_b[x+2][y]==1 && if_b[x+3][y] == 0 && if_b[x+4][y] ==0 && if_b[x+5][y] ==1 &&if_b[x+6][y] ==1 &&
                 if_b[x+7][y]==0 )
                B_weight[m][n] += 2500;
             //12202020
             if(if_b[x][y]==2 && if_b[x+1][y]==1 && if_b[x+2][y]==1 && if_b[x+3][y] == 0 && if_b[x+4][y] ==1 && if_b[x+5][y] ==0 &&if_b[x+6][y] ==1 &&
                 if_b[x+7][y]==0)
                B_weight[m][n] += 2500;
             //12220020
             if(if_b[x][y]==2 && if_b[x+1][y]==1 && if_b[x+2][y]==1 && if_b[x+3][y] == 1 && if_b[x+4][y] ==0 && if_b[x+5][y] ==0 &&if_b[x+6][y] ==1 &&
                 if_b[x+7][y]==0)
                B_weight[m][n] += 2500;
             //10220220
             if(if_b[x][y]==2 && if_b[x+1][y]==0 && if_b[x+2][y]==1 && if_b[x+3][y] == 1 && if_b[x+4][y] ==0 && if_b[x+5][y] ==1 &&if_b[x+6][y] ==1 &&
                 if_b[x+7][y]==0)
                B_weight[m][n] += 2500;
             //10222020
             if(if_b[x][y]==2 && if_b[x+1][y]==0 && if_b[x+2][y]==1 && if_b[x+3][y] == 1 && if_b[x+4][y] ==1 && if_b[x+5][y] ==0 &&if_b[x+6][y] ==1 &&
                 if_b[x+7][y]==0)
                B_weight[m][n] += 2500;
             //10202220
             if(if_b[x][y]==2 && if_b[x+1][y]==0 && if_b[x+2][y]==1 && if_b[x+3][y] == 0 && if_b[x+4][y] ==1 && if_b[x+5][y] ==1 &&if_b[x+6][y] ==1 &&
                 if_b[x+7][y]==0)
                B_weight[m][n] += 2500;


             //4개 한쪽 막혔을 때 reverse
             //022221
             if(if_b[x][y]==0 && if_b[x+1][y]==1 && if_b[x+2][y]==1 && if_b[x+3][y] == 1 && if_b[x+4][y] ==1 && if_b[x+5][y] ==2)
                B_weight[m][n] += 2500;
             //0222021
             if(if_b[x][y]==0 && if_b[x+1][y]==1 && if_b[x+2][y]==1 && if_b[x+3][y] == 1 && if_b[x+4][y] ==0 && if_b[x+5][y] ==1 &&if_b[x+6][y] ==2)
                B_weight[m][n] += 2500;
             //0220221
             if(if_b[x][y]==0 && if_b[x+1][y]==1 && if_b[x+2][y]==1 && if_b[x+3][y] ==0 && if_b[x+4][y] ==1 && if_b[x+5][y] ==1 &&if_b[x+6][y] ==2)
                B_weight[m][n] += 2500;
             //0202221
             if(if_b[x][y]==0 && if_b[x+1][y]==1 && if_b[x+2][y]==0 && if_b[x+3][y] == 1 && if_b[x+4][y] ==1 && if_b[x+5][y] ==1 &&if_b[x+6][y] ==2)
                B_weight[m][n] += 2500;
             //0222201
             if(if_b[x][y]==0 && if_b[x+1][y]==1 && if_b[x+2][y]==1 && if_b[x+3][y] == 1 && if_b[x+4][y] ==1 && if_b[x+5][y] ==0 &&if_b[x+6][y] ==2)
                B_weight[m][n] += 2500;
             //02220021
             if(if_b[x][y]==0 && if_b[x+1][y]==1 && if_b[x+2][y]==1 && if_b[x+3][y] == 1 && if_b[x+4][y] ==0 && if_b[x+5][y] ==0 &&if_b[x+6][y] ==1 &&
                 if_b[x+7][y] ==2)
                B_weight[m][n] += 2500;
             //02202021
             if(if_b[x][y]==0 && if_b[x+1][y]==1 && if_b[x+2][y]==1 && if_b[x+3][y] == 0 && if_b[x+4][y] ==1 && if_b[x+5][y] ==0 &&if_b[x+6][y] ==1 &&
                 if_b[x+7][y] ==2)
                B_weight[m][n] += 2500;
             //02022021
             if(if_b[x][y]==0 && if_b[x+1][y]==1 && if_b[x+2][y]==0 && if_b[x+3][y] == 1 && if_b[x+4][y] ==1 && if_b[x+5][y] ==0 &&if_b[x+6][y] ==1 &&
                 if_b[x+7][y] ==2)
                B_weight[m][n] += 2500;
             //02200221
             if(if_b[x][y]==0 && if_b[x+1][y]==1 && if_b[x+2][y]==1 && if_b[x+3][y] == 0 && if_b[x+4][y] ==0 && if_b[x+5][y] ==1 &&if_b[x+6][y] ==1 &&
                 if_b[x+7][y] ==2 )
                B_weight[m][n] += 2500;
             //02020221
             if(if_b[x][y]==0 && if_b[x+1][y]==1 && if_b[x+2][y]==0 && if_b[x+3][y] == 1 && if_b[x+4][y] ==0 && if_b[x+5][y] ==1 &&if_b[x+6][y] ==1 &&
                 if_b[x+7][y] ==2)
                B_weight[m][n] += 2500;
             //02002221
             if(if_b[x][y]==0 && if_b[x+1][y]==1 && if_b[x+2][y]==0 && if_b[x+3][y] == 0 && if_b[x+4][y] ==1 && if_b[x+5][y] ==1 &&if_b[x+6][y] ==1 &&
                 if_b[x+7][y] ==2)
                B_weight[m][n] += 2500;
             //02202201
             if(if_b[x][y]==0 && if_b[x+1][y]==1 && if_b[x+2][y]==1 && if_b[x+3][y] == 0 && if_b[x+4][y] ==1 && if_b[x+5][y] ==1 &&if_b[x+6][y] ==0 &&
                 if_b[x+7][y] ==2)
                B_weight[m][n] += 2500;
             //02022201
             if(if_b[x][y]==0 && if_b[x+1][y]==1 && if_b[x+2][y]==0 && if_b[x+3][y] == 1 && if_b[x+4][y] ==1 && if_b[x+5][y] ==1 &&if_b[x+6][y] ==0 &&
                 if_b[x+7][y] ==2)
                B_weight[m][n] += 2500;
             //02220201
             if(if_b[x][y]==0 && if_b[x+1][y]==1 && if_b[x+2][y]==1 && if_b[x+3][y] == 1 && if_b[x+4][y] ==0 && if_b[x+5][y] ==1 &&if_b[x+6][y] ==0 &&
                 if_b[x+7][y] ==2)
                B_weight[m][n] += 2500;



             //양쪽 다 막혔을 때

             //12022021
             if(if_b[x][y]==2 && if_b[x+1][y]==1 && if_b[x+2][y]==0 && if_b[x+3][y] == 1 && if_b[x+4][y] ==1 && if_b[x+5][y] ==0 &&if_b[x+6][y] ==1 &&if_b[x+7][y] ==2 )
                B_weight[m][n] += 1000;
             //12200221
             if(if_b[x][y]==2 && if_b[x+1][y]==1 && if_b[x+2][y]==1 && if_b[x+3][y] == 0 && if_b[x+4][y] ==0 && if_b[x+5][y] ==1 &&if_b[x+6][y] ==1 &&if_b[x+7][y] ==2 )
                B_weight[m][n] += 1000;
             //12220021
             if(if_b[x][y]==2 && if_b[x+1][y]==1 && if_b[x+2][y]==1 && if_b[x+3][y] == 1 && if_b[x+4][y] ==0 && if_b[x+5][y] ==0 &&if_b[x+6][y] ==1 &&if_b[x+7][y] ==2)
                B_weight[m][n] += 1000;
             //12002221
             if(if_b[x][y]==2 && if_b[x+1][y]==1 && if_b[x+2][y]==0 && if_b[x+3][y] == 0 && if_b[x+4][y] ==1 && if_b[x+5][y] ==1 &&if_b[x+6][y] ==1 &&if_b[x+7][y] ==2 )
                B_weight[m][n] += 1000;
             //12202021
             if(if_b[x][y]==2 && if_b[x+1][y]==1 && if_b[x+2][y]==1 && if_b[x+3][y] == 0 && if_b[x+4][y] ==1 && if_b[x+5][y] ==1 &&if_b[x+6][y] ==1 &&if_b[x+7][y] ==2)
                B_weight[m][n] += 1000;
             //12020221
             if(if_b[x][y]==2 && if_b[x+1][y]==1 && if_b[x+2][y]==0 && if_b[x+3][y] == 1 && if_b[x+4][y] ==0 && if_b[x+5][y] ==1 &&if_b[x+6][y] ==1 &&if_b[x+7][y] ==2 )
                B_weight[m][n] += 1000;
             //10222201
           if(if_b[x][y]==2 && if_b[x+1][y]==0 && if_b[x+2][y]==1 && if_b[x+3][y] == 1 && if_b[x+4][y] ==1 && if_b[x+5][y] ==1 &&if_b[x+6][y] ==0 &&if_b[x+7][y] ==2 )
                B_weight[m][n] += 1000;
           //10222021
           if(if_b[x][y]==2 && if_b[x+1][y]==0 && if_b[x+2][y]==1 && if_b[x+3][y] == 1 && if_b[x+4][y] ==1 && if_b[x+5][y] ==0 &&if_b[x+6][y] ==1 &&if_b[x+7][y] ==2 )
                B_weight[m][n] += 1000;
           //10220221
           if(if_b[x][y]==2 && if_b[x+1][y]==0 && if_b[x+2][y]==1 && if_b[x+3][y] == 1 && if_b[x+4][y] ==0 && if_b[x+5][y] ==1 &&if_b[x+6][y] ==1 &&if_b[x+7][y] ==2 )
                B_weight[m][n] += 1000;
            //10202221
           if(if_b[x][y]==2 && if_b[x+1][y]==0 && if_b[x+2][y]==1 && if_b[x+3][y] == 0 && if_b[x+4][y] ==1 && if_b[x+5][y] ==1 &&if_b[x+6][y] ==1 &&if_b[x+7][y] ==2 )
                B_weight[m][n] += 1000;
           //10022221
           if(if_b[x][y]==2 && if_b[x+1][y]==0 && if_b[x+2][y]==0 && if_b[x+3][y] == 1 && if_b[x+4][y] ==1 && if_b[x+5][y] ==1 &&if_b[x+6][y] ==1 &&if_b[x+7][y] ==2 )
                B_weight[m][n] += 1000;
           //12022201
           if(if_b[x][y]==2 && if_b[x+1][y]==1 && if_b[x+2][y]==0 && if_b[x+3][y] == 1 && if_b[x+4][y] ==1 && if_b[x+5][y] ==1 &&if_b[x+6][y] ==0 &&if_b[x+7][y] ==2 )
                B_weight[m][n] += 1000;
           //12202201
           if(if_b[x][y]==2 && if_b[x+1][y]==1 && if_b[x+2][y]==1 && if_b[x+3][y] == 0 && if_b[x+4][y] ==1 && if_b[x+5][y] ==1 &&if_b[x+6][y] ==0 &&if_b[x+7][y] ==2 )
                B_weight[m][n] += 1000;
           //12220201
           if(if_b[x][y]==2 && if_b[x+1][y]==1 && if_b[x+2][y]==1 && if_b[x+3][y] == 1 && if_b[x+4][y] ==0 && if_b[x+5][y] ==1 &&if_b[x+6][y] ==0 &&if_b[x+7][y] ==2 )
                B_weight[m][n] += 1000;
           //12222001
           if(if_b[x][y]==2 && if_b[x+1][y]==1 && if_b[x+2][y]==1 && if_b[x+3][y] == 1 && if_b[x+4][y] ==1 && if_b[x+5][y] ==0 &&if_b[x+6][y] ==0 &&if_b[x+7][y] ==2 )
                B_weight[m][n] += 1000;
             }
             }
             if_b[m][n] = 0;
             }
             }


}

void AI::B_AI_2_Diagonal_check()
{
    for(int m=0 ; m<19 ; m++)
        {
          for(int n=0 ; n<19 ; n++)
          {
              if( if_b[m][n] == 0 )
              {
              if_b[m][n] = 1;
              }
              else if( if_b[m][n] == 2 || if_b[m][n] == 1 )
              {
                  continue;
              }

              for(int x=0; x<19; x++)
              {
                  for(int y=0; y<19; y++)
                  {
                //00022000
                if( if_b[x-2][y-2] == 0 && if_b[x-1][y-1] == 0 && if_b[x][y] == 0 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 1 &&
                    if_b[x+3][y+3] == 0 && if_b[x+4][y+4] == 0 && if_b[x+5][y+5] == 0 )
                    B_weight[m][n] += 2000;
                //0020200
                if( if_b[x-1][y-1] == 0 && if_b[x][y] == 0 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 0 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] == 0 &&
                    if_b[x+5][y+5] == 0 )
                    B_weight[m][n] += 1500;
                //020020
                if( if_b[x][y] == 0 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 0 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] == 1 && if_b[x+5][y+5] == 0 )
                    B_weight[m][n] += 1000;
                //여기까지 양쪽에 안 막힌, 흰 돌이 2개가 발견 될 때 경우의 수들

                //122000
                if( if_b[x][y] == 2 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 1 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] == 0 && if_b[x+5][y+5] == 0 )
                    B_weight[m][n] += 500;
                //120200
                if( if_b[x][y] == 2 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 0 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] == 0 && if_b[x+5][y+5] == 0 )
                    B_weight[m][n] += 500;
                //120020
                if( if_b[x][y] == 2 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 0 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] == 1 && if_b[x+5][y+5] == 0 )
                    B_weight[m][n] += 500;
                //102200
                if( if_b[x][y] == 2 && if_b[x+1][y+1] == 0 && if_b[x+2][y+2] == 1 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] == 0 && if_b[x+5][y+5] == 0 )
                    B_weight[m][n] += 800;
                //102020
                if( if_b[x][y] == 2 && if_b[x+1][y+1] == 0 && if_b[x+2][y+2] == 1 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] == 1 && if_b[x+5][y+5] == 0 )
                    B_weight[m][n] += 800;
                //여기까지 왼쪽에 검은돌로 막힌 경우.
                //오른쪽에 검은돌로 막힌 경우는 이 대칭으로만 작성해주면됌

                //000221
                if( if_b[x-2][y-2] == 0 && if_b[x-1][y-1] == 0 && if_b[x][y] == 0 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 1 && if_b[x+3][y+3] == 2 )
                    B_weight[m][n] += 500;
                //002021
                if( if_b[x-1][y-1] == 0 && if_b[x][y] == 0 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 0 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] == 2 )
                    B_weight[m][n] += 500;
                //020021
                if( if_b[x][y] == 0 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 0 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] == 1 && if_b[x+5][y+5] == 2 )
                    B_weight[m][n] += 500;
                //002201
                if( if_b[x-1][y-1] == 0 && if_b[x][y] == 0 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 1 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] == 2 )
                    B_weight[m][n] += 800;
                //020201
                if( if_b[x][y] == 0 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 0 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] == 0 && if_b[x+5][y+5] == 2 )
                    B_weight[m][n] += 800;
                //여기까지 한쪽이 막힌 경우.
                //그 다음은 양쪽이 막힌 경우. 양쪽이 막힌 경우는 안이 6칸일 경우만 따지자.

                //12200001
                if( if_b[x][y] == 2 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 1 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] == 0 && if_b[x+5][y+5] == 0 &&
                    if_b[x+6][y+6] == 0 && if_b[x+7][y+7] == 2 )
                    B_weight[m][n] += 300;
                //12020001
                if( if_b[x][y] == 2 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 0 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] == 0 && if_b[x+5][y+5] == 0 &&
                    if_b[x+6][y+6] == 0 && if_b[x+7][y+7] == 2 )
                    B_weight[m][n] += 300;
                //12002001
                if( if_b[x][y] == 2 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 0 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] == 1 && if_b[x+5][y+5] == 0 &&
                    if_b[x+6][y+6] == 0 && if_b[x+7][y+7] == 2 )
                    B_weight[m][n] += 300;
                //12000201
                if( if_b[x][y] == 2 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 0 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] == 0 && if_b[x+5][y+5] == 1 &&
                    if_b[x+6][y+6] == 0 && if_b[x+7][y+7] == 2 )
                    B_weight[m][n] += 300;
                //12000021
                if( if_b[x][y] == 2 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 0 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] == 0 && if_b[x+5][y+5] == 0 &&
                    if_b[x+6][y+6] == 1 && if_b[x+7][y+7] == 2 )
                    B_weight[m][n] += 300;
                //10220001
                if( if_b[x][y] == 2 && if_b[x+1][y+1] == 0 && if_b[x+2][y+2] == 1 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] == 0 && if_b[x+5][y+5] == 0 &&
                    if_b[x+6][y+6] == 0 && if_b[x+7][y+7] == 2 )
                    B_weight[m][n] += 300;
                //10202001
                if( if_b[x][y] == 2 && if_b[x+1][y+1] == 0 && if_b[x+2][y+2] == 1 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] == 1 && if_b[x+5][y+5] == 0 &&
                    if_b[x+6][y+6] == 0 && if_b[x+7][y+7] == 2 )
                    B_weight[m][n] += 300;
                //10200201
                if( if_b[x][y] == 2 && if_b[x+1][y+1] == 0 && if_b[x+2][y+2] == 1 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] == 0 && if_b[x+5][y+5] == 1 &&
                    if_b[x+6][y+6] == 0 && if_b[x+7][y+7] == 2 )
                    B_weight[m][n] += 300;
                //10200021
                if( if_b[x][y] == 2 && if_b[x+1][y+1] == 0 && if_b[x+2][y+2] == 1 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] == 0 && if_b[x+5][y+5] == 0 &&
                    if_b[x+6][y+6] == 1 && if_b[x+7][y+7] == 2 )
                    B_weight[m][n] += 300;
                //10022001
                if( if_b[x][y] == 2 && if_b[x+1][y+1] == 0 && if_b[x+2][y+2] == 0 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] == 1 && if_b[x+5][y+5] == 0 &&
                    if_b[x+6][y+6] == 0 && if_b[x+7][y+7] == 2 )
                    B_weight[m][n] += 300;
                //10020201
                if( if_b[x][y] == 2 && if_b[x+1][y+1] == 0 && if_b[x+2][y+2] == 0 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] == 0 && if_b[x+5][y+5] == 1 &&
                    if_b[x+6][y+6] == 0 && if_b[x+7][y+7] == 2 )
                    B_weight[m][n] += 300;
                //10020021
                if( if_b[x][y] == 2 && if_b[x+1][y+1] == 0 && if_b[x+2][y+2] == 0 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] == 0 && if_b[x+5][y+5] == 0 &&
                    if_b[x+6][y+6] == 1 && if_b[x+7][y+7] == 2 )
                    B_weight[m][n] += 300;
                //10002201
                if( if_b[x][y] == 2 && if_b[x+1][y+1] == 0 && if_b[x+2][y+2] == 0 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] == 1 && if_b[x+5][y+5] == 1 &&
                    if_b[x+6][y+6] == 0 && if_b[x+7][y+7] == 2 )
                    B_weight[m][n] += 300;
                //10002021
                if( if_b[x][y] == 2 && if_b[x+1][y+1] == 0 && if_b[x+2][y+2] == 0 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] == 0 && if_b[x+5][y+5] == 1 &&
                    if_b[x+6][y+6] == 0 && if_b[x+7][y+7] == 2 )
                    B_weight[m][n] += 300;
                //10000221
                if( if_b[x][y] == 2 && if_b[x+1][y+1] == 0 && if_b[x+2][y+2] == 0 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] == 0 && if_b[x+5][y+5] == 1 &&
                    if_b[x+6][y+6] == 1 && if_b[x+7][y+7] == 2 )
                    B_weight[m][n] += 300;
                  }
              }
              if_b[m][n] = 0;
          }
        }

}

void AI::B_AI_3_Diagonal_check()
{
    for(int m=0 ; m<19 ; m++)
        {
          for(int n=0 ; n<19 ; n++)
          {
              if( if_b[m][n] == 0 )
              {
              if_b[m][n] = 1;
              }
              else if( if_b[m][n] == 2 || if_b[m][n] == 1 )
              {
                  continue;
              }

              for(int x=0; x<19; x++)
              {
                  for(int y=0; y<19; y++)
                  {
                //000222000
                if( if_b[x-1][y-1] == 0 && if_b[x][y] == 0 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 1 && if_b[x+3][y+3] == 1&& if_b[x+4][y+4]==0 &&
                    if_b[x+5][y+5] == 0 )
                    B_weight[m][n] += 5000;
                //00202200
                if( if_b[x-1][y-1] == 0 && if_b[x][y] == 0 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 0 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] == 1 &&
                    if_b[x+5][y+5]==0 && if_b[x+6][y+6] == 0 )
                    B_weight[m][n] += 3500;
                //00220200
                if( if_b[x-1][y-1] == 0 && if_b[x][y] == 0 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 1 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] == 1 &&
                    if_b[x+5][y+5] == 0 && if_b[x+6][y+6] == 0 )
                    B_weight[m][n] += 3500;
                //0200220
                if( if_b[x][y] == 0 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 0 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] == 1 && if_b[x+5][y+5] == 1
                    &&if_b[x+6][y+6] ==0 )
                    B_weight[m][n] += 3000;
                //0202020
                if( if_b[x][y] == 0 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 0 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] == 0 && if_b[x+5][y+5] == 1
                    &&if_b[x+6][y+6]==0 )
                    B_weight[m][n] += 3000;
                //0220020
                if( if_b[x][y] == 0 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 1 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] == 0 && if_b[x+5][y+5] == 1
                    && if_b[x+6][y+6] ==0 )
                    B_weight[m][n] += 3000;
                //여기까지 양쪽에 안 막힌, 흰 돌이 2개가 발견 될 때 경우의 수들

                //122200
                if( if_b[x][y] == 2 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 1 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] ==0 && if_b[x+5][y+5] == 0 )
                    B_weight[m][n] += 1000;
                //1202200
                if( if_b[x][y] == 2 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 0 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] == 1 && if_b[x+5][y+5] ==0 &&
                    if_b[x][y+6] == 0 )
                    B_weight[m][n] += 1000;
                //1220200
                if( if_b[x][y] == 2 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 1 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] == 1 && if_b[x+5][y+5] == 0 &&
                    if_b[x+6][y+6] == 0 )
                    B_weight[m][n] += 1000;
                //1022200
                if( if_b[x][y] == 2 && if_b[x+1][y+1] == 0 && if_b[x+2][y+2] == 1 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] == 1 && if_b[x+5][y+5] ==0 &&
                    if_b[x+6][y+6] == 0 )
                    B_weight[m][n] += 1300;
                //1200220
                if( if_b[x][y] == 2 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 0 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] == 1 && if_b[x+5][y+5] == 1 &&
                if_b[x+6][y+6] ==0 )
                    B_weight[m][n] += 1300;
                //1220020
                if( if_b[x][y] == 2 && if_b[x][y+1] == 1 && if_b[x][y+2] == 1 && if_b[x][y+3] == 0 && if_b[x][y+4] == 0 && if_b[x][y+5] == 1 &&
                    if_b[x][y+6] == 0 )
                    B_weight[m][n] += 1000;
                //1202020
                if( if_b[x][y] == 2 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 0 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] == 0 && if_b[x+5][y+5] == 1 &&
                    if_b[x+6][y+6] ==0 )
                    B_weight[m][n] += 1000;
                //1020220
                if( if_b[x][y] == 2 && if_b[x+1][y+1] == 0 && if_b[x+2][y+2] == 1 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] == 1 && if_b[x+5][y+5] == 1 &&
                    if_b[x+6][y+6] == 0)
                    B_weight[m][n] += 1300;

                //여기까지 왼쪽에 검은돌로 막힌 경우.
                //오른쪽에 검은돌로 막힌 경우는 이 대칭으로만 작성해주면됌

                //002221
                if( if_b[x-1][y-1] == 0 && if_b[x][y] == 0 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 1 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] == 2 )
                    B_weight[m][n] += 1000;
                //0022021
                if( if_b[x-1][y-1] == 0 && if_b[x][y] == 0 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 1 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] == 1 &&
                    if_b[x+5][y+5]==2 )
                    B_weight[m][n] += 1000;
                //0020221
                if( if_b[x-1][y-1] == 0 && if_b[x][y] == 0 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 0 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] == 1 &&
                    if_b[x+5][y+5] == 2 )
                    B_weight[m][n] += 1000;
                //0022201
                if( if_b[x-1][y-1] == 0 && if_b[x][y] == 0 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 1 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] == 0 &&
                    if_b[x+5][y+5] == 2 )
                    B_weight[m][n] += 1300;
                //0220021
                if( if_b[x][y] == 0 && if_b[x][y+1] == 1 && if_b[x][y+2] == 1 && if_b[x][y+3] == 0 && if_b[x][y+4] == 0 && if_b[x][y+5] == 1 &&
                    if_b[x][y+6] == 2 )
                    B_weight[m][n] += 1300;
                //0200221
                if( if_b[x][y] == 0 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 0 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] == 1 && if_b[x+5][y+5] == 1 &&
                    if_b[x+6][y+6] == 2 )
                    B_weight[m][n] += 1000;
                //0202021
                if( if_b[x][y] == 0 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 0 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] == 0 && if_b[x+5][y+5] == 1 &&
                    if_b[x+6][y+6] == 2 )
                    B_weight[m][n] += 1000;
                //0220201
                if( if_b[x][y] == 0 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 1 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] == 1 && if_b[x+5][y+5] == 0 &&
                    if_b[x+6][y+6] == 2 )
                    B_weight[m][n] += 1300;

                //여기까지 한쪽이 막힌 경우.
                //그 다음은 양쪽이 막힌 경우. 양쪽이 막힌 경우는 안이 6칸일 경우만 따지자.

                //12220001
                if( if_b[x][y] == 2 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 1 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] == 0 && if_b[x+5][y+5] == 0 &&
                    if_b[x+6][y+6] == 0 && if_b[x+7][y+7] == 2 )
                    B_weight[m][n] += 300;
                //12022001
                if( if_b[x][y] == 2 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 0 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] == 1 && if_b[x+5][y+5] == 0 &&
                    if_b[x+6][y+6] == 0 && if_b[x+7][y+7] == 2 )
                    B_weight[m][n] += 300;
                //12002201
                if( if_b[x][y] == 2 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 0 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] == 1 && if_b[x+5][y+5] == 1 &&
                    if_b[x+6][y+6] == 0 && if_b[x+7][y+7] == 2 )
                    B_weight[m][n] += 300;
                //12000221
                if( if_b[x][y] == 2 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 0 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] == 0 && if_b[x+5][y+5] == 1 &&
                    if_b[x+6][y+6] == 1 && if_b[x+7][y+7] == 2 )
                    B_weight[m][n] += 300;
                //12202001
                if( if_b[x][y] == 2 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 1 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] == 1 && if_b[x+5][y+5] == 0 &&
                    if_b[x+6][y+6] == 0 && if_b[x+7][y+7] == 2 )
                    B_weight[m][n] += 300;
                //12200201
                if( if_b[x][y] == 2 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 1 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] == 0 && if_b[x+5][y+5] == 1 &&
                    if_b[x+6][y+6] == 0 && if_b[x+7][y+7] == 2 )
                    B_weight[m][n] += 300;
                //12200021
                if( if_b[x][y] == 2 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 1 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] == 0 && if_b[x+5][y+5] == 0 &&
                    if_b[x+6][y+6] == 1 && if_b[x+7][y+7] == 2 )
                    B_weight[m][n] += 300;
                //12002021
                if( if_b[x][y] == 2 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 0 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] == 1 && if_b[x+5][y+5] == 0 &&
                    if_b[x+6][y+6] == 1 && if_b[x+7][y+7] == 2 )
                    B_weight[m][n] += 300;
                //12020021
                if( if_b[x][y] == 2 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 0 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] == 0 && if_b[x+5][y+5] == 0 &&
                    if_b[x+6][y+6] == 1 && if_b[x+7][y+7] == 2 )
                    B_weight[m][n] += 300;
                //12020201
                if( if_b[x][y] == 2 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 0 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] == 0 && if_b[x+5][y+5] == 1 &&
                    if_b[x+6][y+6] == 0 && if_b[x+7][y+7] == 2 )
                    B_weight[m][n] += 300;
                //10222001
                if( if_b[x][y] == 2 && if_b[x+1][y+1] == 0 && if_b[x+2][y+2] == 1 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] == 1 && if_b[x+5][y+5] == 0 &&
                    if_b[x+6][y+6] == 0 && if_b[x+7][y+7] == 2 )
                    B_weight[m][n] += 300;
                //10202201
                if( if_b[x][y] == 2 && if_b[x+1][y+1] == 0 && if_b[x+2][y+2] == 1 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] == 1 && if_b[x+5][y+5] == 1 &&
                    if_b[x+6][y+6] == 0 && if_b[x+7][y+7] == 2 )
                    B_weight[m][n] += 300;
                //10200221
                if( if_b[x][y] == 2 && if_b[x+1][y+1] == 0 && if_b[x+2][y+2] == 1 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] == 0 && if_b[x+5][y+5] == 1 &&
                    if_b[x+6][y+6] == 1 && if_b[x+7][y+7] == 2 )
                    B_weight[m][n] += 300;
                //10220201
                if( if_b[x][y] == 2 && if_b[x+1][y+1] == 0 && if_b[x+2][y+2] == 1 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] == 0 && if_b[x+5][y+5] == 1 &&
                    if_b[x+6][y+6] == 0 && if_b[x+7][y+7] == 2 )
                    B_weight[m][n] += 300;
                //10220021
                if( if_b[x][y] == 2 && if_b[x+1][y+1] == 0 && if_b[x+2][y+2] == 1 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] == 0 && if_b[x+5][y+5] == 0 &&
                    if_b[x+6][y+6] == 1 && if_b[x+7][y+7] == 2 )
                    B_weight[m][n] += 300;
                //10022021
                if( if_b[x][y] == 2 && if_b[x+1][y+1] == 0 && if_b[x+2][y+2] == 0 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] == 1 && if_b[x+5][y+5] == 0 &&
                    if_b[x+6][y+6] == 1 && if_b[x+7][y+7] == 2 )
                    B_weight[m][n] += 300;
                //10022201
                if( if_b[x][y] == 2 && if_b[x+1][y+1] == 0 && if_b[x+2][y+2] == 0 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] == 1 && if_b[x+5][y+5] == 1 &&
                    if_b[x+6][y+6] == 0 && if_b[x+7][y+7] == 2 )
                    B_weight[m][n] += 300;
                //10020221
                if( if_b[x][y] == 2 && if_b[x+1][y+1] == 0 && if_b[x+2][y+2] == 0 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] == 0 && if_b[x+5][y+5] == 1 &&
                    if_b[x+6][y+6] == 1 && if_b[x+7][y+7] == 2 )
                    B_weight[m][n] += 300;
                //10002221
                if( if_b[x][y] == 2 && if_b[x+1][y+1] == 0 && if_b[x+2][y+2] == 0 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] == 0 && if_b[x+5][y+5] == 1 &&
                    if_b[x+6][y+6] == 1 && if_b[x+7][y+7] == 2 )
                    B_weight[m][n] += 300;
                //10202021
                if( if_b[x][y] == 2 && if_b[x+1][y+1] == 0 && if_b[x+2][y+2] == 1 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] == 1 && if_b[x+5][y+5] == 0 &&
                    if_b[x+6][y+6] == 1 && if_b[x+7][y+7] == 2 )
                    B_weight[m][n] += 300;
                    }
              }
              if_b[m][n] = 0;
          }
        }

}

void AI::B_AI_4_Diagonal_check()
{
    for(int m=0 ; m<19 ; m++)
        {
          for(int n=0 ; n<19 ; n++)
          {
              if( if_b[m][n] == 0 )
              {
              if_b[m][n] = 1;
              }
              else if( if_b[m][n] == 2 || if_b[m][n] == 1 )
              {
                  continue;
              }

              for(int x=0; x<19; x++)
              {
                  for(int y=0; y<19; y++)
                  {

       /*4개 -> 안막혔을 때*/
             //00222200
             if( if_b[x-1][y-1] == 0 && if_b[x][y]== 0 && if_b[x+1][y+1]== 1 && if_b[x+2][y+2]== 1 &&if_b[x+3][y+3] == 1 && if_b[x+4][y+4] == 1 &&
                 if_b[x+5][y+5] == 0 )
                B_weight[m][n] += 10000;
             //002022200
             if( if_b[x-1][y-1] == 0 && if_b[x][y]==0 && if_b[x+1][y+1]==1 && if_b[x+2][y+2]==0 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] ==1 &&
                 if_b[x+5][y+5]==1 &&if_b[x+6][y+6] ==0 && if_b[x+7][y+7] == 0 )
                B_weight[m][n] += 7000;
             //002220200
             if( if_b[x-1][y-1] == 0 && if_b[x][y]== 0 && if_b[x+1][y+1]== 1 && if_b[x+2][y+2]== 1 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] == 0 &&
                 if_b[x+5][y+5] ==1 &&if_b[x+6][y+6] == 0 && if_b[x+7][y+7] == 0 )
                B_weight[m][n] += 7000;
             //002202200
             if( if_b[x-1][y-1] == 0 && if_b[x][y]== 0 && if_b[x+1][y+1]== 1 && if_b[x+2][y+2]== 1 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] == 1 &&
                 if_b[x+5][y+5] == 1 && if_b[x+6][y+6] == 0 && if_b[x+7][y+7] == 0 )
                B_weight[m][n] += 7000;
             //02220020
             if( if_b[x][y]==0 && if_b[x+1][y+1]==1 && if_b[x+2][y+2]==1 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] ==0 && if_b[x+5][y+5] ==0 &&
                 if_b[x+6][y+6] ==1 && if_b[x+7][y+7] ==0 )
                B_weight[m][n] += 5000;
             //02002220
             if( if_b[x][y] == 0 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 0 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] == 1 && if_b[x+5][y+5] == 1 &&
                 if_b[x+6][y+6] == 1 && if_b[x+7][y+7] == 0 )
                B_weight[m][n] += 5000;
             //02202020
             if( if_b[x][y] == 0 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 1 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] == 1 && if_b[x+5][y+5] == 1 &&
                 if_b[x+6][y+6] == 1 && if_b[x+7][y+7] == 0 )
                B_weight[m][n] += 4000;
             //02020220
             if(if_b[x][y] == 0 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 0 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] == 0 && if_b[x+5][y+5] == 1 &&
                 if_b[x+6][y+6] == 1 && if_b[x+7][y+7] == 0 )
                B_weight[m][n] += 4000;

             //4개 한쪽 막혔을 때
             //122220
             if(if_b[x][y]==2 && if_b[x+1][y+1]==1 && if_b[x+2][y+2]==1 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] ==1 && if_b[x+5][y+5] ==0)
                B_weight[m][n] += 2500;
             //1202220
             if(if_b[x][y]==2 && if_b[x+1][y+1]==1 && if_b[x+2][y+2]==0 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] ==1 && if_b[x+5][y+5] ==1 &&if_b[x+6][y+6] ==0)
                B_weight[m][n] += 2500;
             //1220220
             if(if_b[x][y]==2 && if_b[x+1][y+1]==1 && if_b[x+2][y+2]==1 && if_b[x+3][y+3] ==0 && if_b[x+4][y+4] ==1 && if_b[x+5][y+5] ==1 &&if_b[x+6][y+6] ==0)
                B_weight[m][n] += 2500;
             //1222020
             if(if_b[x][y]==2 && if_b[x+1][y+1]==1 && if_b[x+2][y+2]==1 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] ==0 && if_b[x+5][y+5] ==1 &&if_b[x+6][y+6] ==0)
                B_weight[m][n] += 2500;
             //1022220
             if(if_b[x][y]==2 && if_b[x+1][y+1]==0 && if_b[x+2][y+2]==1 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] ==1 && if_b[x+5][y+5] ==1 &&if_b[x+6][y+6] ==0)
                B_weight[m][n] += 2500;
             //12002220
             if(if_b[x][y]==2 && if_b[x+1][y+1]==1 && if_b[x+2][y+2]==0 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] ==1 && if_b[x+5][y+5] ==1 &&if_b[x+6][y+6] ==1 &&
                 if_b[x+7][y+7]==0)
                B_weight[m][n] += 2500;
             //12020220
             if(if_b[x][y]==2 && if_b[x+1][y+1]==1 && if_b[x+2][y+2]==0 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] ==0 && if_b[x+5][y+5] ==1 &&if_b[x+6][y+6] ==1 &&
                 if_b[x+7][y+7]==0)
                B_weight[m][n] += 2500;
             //12022020
             if(if_b[x][y]==2 && if_b[x+1][y+1]==1 && if_b[x+2][y+2]==0 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] ==1 && if_b[x+5][y+5] ==0 &&if_b[x+6][y+6] ==1 &&
                 if_b[x+7][y+7]==0)
                B_weight[m][n] += 2500;
             //12200220
             if(if_b[x][y]==2 && if_b[x+1][y+1]==1 && if_b[x+2][y+2]==1 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] ==0 && if_b[x+5][y+5] ==1 &&if_b[x+6][y+6] ==1 &&
                 if_b[x+7][y+7]==0 )
                B_weight[m][n] += 2500;
             //12202020
             if(if_b[x][y]==2 && if_b[x+1][y+1]==1 && if_b[x+2][y+2]==1 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] ==1 && if_b[x+5][y+5] ==0 &&if_b[x+6][y+6] ==1 &&
                 if_b[x+7][y+7]==0)
                B_weight[m][n] += 2500;
             //12220020
             if(if_b[x][y]==2 && if_b[x+1][y+1]==1 && if_b[x+2][y+2]==1 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] ==0 && if_b[x+5][y+5] ==0 &&if_b[x+6][y+6] ==1 &&
                 if_b[x+7][y+7]==0)
                B_weight[m][n] += 2500;
             //10220220
             if(if_b[x][y]==2 && if_b[x+1][y+1]==0 && if_b[x+2][y+2]==1 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] ==0 && if_b[x+5][y+5] ==1 &&if_b[x+6][y+6] ==1 &&
                 if_b[x+7][y+7]==0)
                B_weight[m][n] += 2500;
             //10222020
             if(if_b[x][y]==2 && if_b[x+1][y+1]==0 && if_b[x+2][y+2]==1 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] ==1 && if_b[x+5][y+5] ==0 &&if_b[x+6][y+6] ==1 &&
                 if_b[x+7][y+7]==0)
                B_weight[m][n] += 2500;
             //10202220
             if(if_b[x][y]==2 && if_b[x+1][y+1]==0 && if_b[x+2][y+2]==1 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] ==1 && if_b[x+5][y+5] ==1 &&if_b[x+6][y+6] ==1 &&
                 if_b[x+7][y+7]==0)
                B_weight[m][n] += 2500;


             //4개 한쪽 막혔을 때 reverse
             //022221
             if(if_b[x][y]==0 && if_b[x+1][y+1]==1 && if_b[x+2][y+2]==1 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] ==1 && if_b[x+5][y+5] ==2)
                B_weight[m][n] += 2500;
             //0222021
             if(if_b[x][y]==0 && if_b[x+1][y+1]==1 && if_b[x+2][y+2]==1 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] ==0 && if_b[x+5][y+5] ==1 &&if_b[x+6][y+6] ==2)
                B_weight[m][n] += 2500;
             //0220221
             if(if_b[x][y]==0 && if_b[x+1][y+1]==1 && if_b[x+2][y+2]==1 && if_b[x+3][y+3] ==0 && if_b[x+4][y+4] ==1 && if_b[x+5][y+5] ==1 &&if_b[x+6][y+6] ==2)
                B_weight[m][n] += 2500;
             //0202221
             if(if_b[x][y]==0 && if_b[x+1][y+1]==1 && if_b[x+2][y+2]==0 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] ==1 && if_b[x+5][y+5] ==1 &&if_b[x+6][y+6] ==2)
                B_weight[m][n] += 2500;
             //0222201
             if(if_b[x][y]==0 && if_b[x+1][y+1]==1 && if_b[x+2][y+2]==1 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] ==1 && if_b[x+5][y+5] ==0 &&if_b[x+6][y+6] ==2)
                B_weight[m][n] += 2500;
             //02220021
             if(if_b[x][y]==0 && if_b[x+1][y+1]==1 && if_b[x+2][y+2]==1 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] ==0 && if_b[x+5][y+5] ==0 &&if_b[x+6][y+6] ==1 &&
                 if_b[x+7][y+7] ==2)
                B_weight[m][n] += 2500;
             //02202021
             if(if_b[x][y]==0 && if_b[x+1][y+1]==1 && if_b[x+2][y+2]==1 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] ==1 && if_b[x+5][y+5] ==0 &&if_b[x+6][y+6] ==1 &&
                 if_b[x+7][y+7] ==2)
                B_weight[m][n] += 2500;
             //02022021
             if(if_b[x][y]==0 && if_b[x+1][y+1]==1 && if_b[x+2][y+2]==0 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] ==1 && if_b[x+5][y+5] ==0 &&if_b[x+6][y+6] ==1 &&
                 if_b[x+7][y+7] ==2)
                B_weight[m][n] += 2500;
             //02200221
             if(if_b[x][y]==0 && if_b[x+1][y+1]==1 && if_b[x+2][y+2]==1 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] ==0 && if_b[x+5][y+5] ==1 &&if_b[x+6][y+6] ==1 &&
                 if_b[x+7][y+7] ==2 )
                B_weight[m][n] += 2500;
             //02020221
             if(if_b[x][y]==0 && if_b[x+1][y+1]==1 && if_b[x+2][y+2]==0 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] ==0 && if_b[x+5][y+5] ==1 &&if_b[x+6][y+6] ==1 &&
                 if_b[x+7][y+7] ==2)
                B_weight[m][n] += 2500;
             //02002221
             if(if_b[x][y]==0 && if_b[x+1][y+1]==1 && if_b[x+2][y+2]==0 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] ==1 && if_b[x+5][y+5] ==1 &&if_b[x+6][y+6] ==1 &&
                 if_b[x+7][y+7] ==2)
                B_weight[m][n] += 2500;
             //02202201
             if(if_b[x][y]==0 && if_b[x+1][y+1]==1 && if_b[x+2][y+2]==1 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] ==1 && if_b[x+5][y+5] ==1 &&if_b[x+6][y+6] ==0 &&
                 if_b[x+7][y+7] ==2)
                B_weight[m][n] += 2500;
             //02022201
             if(if_b[x][y]==0 && if_b[x+1][y+1]==1 && if_b[x+2][y+2]==0 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] ==1 && if_b[x+5][y+5] ==1 &&if_b[x+6][y+6] ==0 &&
                 if_b[x+7][y+7] ==2)
                B_weight[m][n] += 2500;
             //02220201
             if(if_b[x][y]==0 && if_b[x+1][y+1]==1 && if_b[x+2][y+2]==1 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] ==0 && if_b[x+5][y+5] ==1 &&if_b[x+6][y+6] ==0 &&
                 if_b[x+7][y+7] ==2)
                B_weight[m][n] += 2500;



             //양쪽 다 막혔을 때

             //12022021
             if(if_b[x][y]==2 && if_b[x+1][y+1]==1 && if_b[x+2][y+2]==0 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] ==1 && if_b[x+5][y+5] ==0 &&if_b[x+6][y+6] ==1 &&if_b[x+7][y+7] ==2 )
                B_weight[m][n] += 1000;
             //12200221
             if(if_b[x][y]==2 && if_b[x+1][y+1]==1 && if_b[x+2][y+2]==1 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] ==0 && if_b[x+5][y+5] ==1 &&if_b[x+6][y+6] ==1 &&if_b[x+7][y+7] ==2 )
                B_weight[m][n] += 1000;
             //12220021
             if(if_b[x][y]==2 && if_b[x+1][y+1]==1 && if_b[x+2][y+2]==1 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] ==0 && if_b[x+5][y+5] ==0 &&if_b[x+6][y+6] ==1 &&if_b[x+7][y+7] ==2)
                B_weight[m][n] += 1000;
             //12002221
             if(if_b[x][y]==2 && if_b[x+1][y+1]==1 && if_b[x+2][y+2]==0 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] ==1 && if_b[x+5][y+5] ==1 &&if_b[x+6][y+6] ==1 &&if_b[x+7][y+7] ==2 )
                B_weight[m][n] += 1000;
             //12202021
             if(if_b[x][y]==2 && if_b[x+1][y+1]==1 && if_b[x+2][y+2]==1 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] ==1 && if_b[x+5][y+5] ==1 &&if_b[x+6][y+6] ==1 &&if_b[x+7][y+7] ==2)
                B_weight[m][n] += 1000;
             //12020221
             if(if_b[x][y]==2 && if_b[x+1][y+1]==1 && if_b[x+2][y+2]==0 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] ==0 && if_b[x+5][y+5] ==1 &&if_b[x+6][y+6] ==1 &&if_b[x+7][y+7] ==2 )
                B_weight[m][n] += 1000;
             //10222201
           if(if_b[x][y]==2 && if_b[x+1][y+1]==0 && if_b[x+2][y+2]==1 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] ==1 && if_b[x+5][y+5] ==1 &&if_b[x+6][y+6] ==0 &&if_b[x+7][y+7] ==2 )
                B_weight[m][n] += 1000;
           //10222021
           if(if_b[x][y]==2 && if_b[x+1][y+1]==0 && if_b[x+2][y+2]==1 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] ==1 && if_b[x+5][y+5] ==0 &&if_b[x+6][y+6] ==1 &&if_b[x+7][y+7] ==2 )
                B_weight[m][n] += 1000;
           //10220221
           if(if_b[x][y]==2 && if_b[x+1][y+1]==0 && if_b[x+2][y+2]==1 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] ==0 && if_b[x+5][y+5] ==1 &&if_b[x+6][y+6] ==1 &&if_b[x+7][y+7] ==2 )
                B_weight[m][n] += 1000;
            //10202221
           if(if_b[x][y]==2 && if_b[x+1][y+1]==0 && if_b[x+2][y+2]==1 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] ==1 && if_b[x+5][y+5] ==1 &&if_b[x+6][y+6] ==1 &&if_b[x+7][y+7] ==2 )
                B_weight[m][n] += 1000;
           //10022221
           if(if_b[x][y]==2 && if_b[x+1][y+1]==0 && if_b[x+2][y+2]==0 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] ==1 && if_b[x+5][y+5] ==1 &&if_b[x+6][y+6] ==1 &&if_b[x+7][y+7] ==2 )
                B_weight[m][n] += 1000;
           //12022201
           if(if_b[x][y]==2 && if_b[x+1][y+1]==1 && if_b[x+2][y+2]==0 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] ==1 && if_b[x+5][y+5] ==1 &&if_b[x+6][y+6] ==0 &&if_b[x+7][y+7] ==2 )
                B_weight[m][n] += 1000;
           //12202201
           if(if_b[x][y]==2 && if_b[x+1][y+1]==1 && if_b[x+2][y+2]==1 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] ==1 && if_b[x+5][y+5] ==1 &&if_b[x+6][y+6] ==0 &&if_b[x+7][y+7] ==2 )
                B_weight[m][n] += 1000;
           //12220201
           if(if_b[x][y]==2 && if_b[x+1][y+1]==1 && if_b[x+2][y+2]==1 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] ==0 && if_b[x+5][y+5] ==1 &&if_b[x+6][y+6] ==0 &&if_b[x+7][y+7] ==2 )
                B_weight[m][n] += 1000;
           //12222001
           if(if_b[x][y]==2 && if_b[x+1][y+1]==1 && if_b[x+2][y+2]==1 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] ==1 && if_b[x+5][y+5] ==0 &&if_b[x+6][y+6] ==0 &&if_b[x+7][y+7] ==2 )
                B_weight[m][n] += 1000;
             }
             }
             if_b[m][n] = 0;
             }
             }

}

void AI::B_AI_2_in_Diagonal_check()
{
    for(int m=0 ; m<19 ; m++)
        {
          for(int n=0 ; n<19 ; n++)
          {
              if( if_b[m][n] == 0 )
              {
              if_b[m][n] = 1;
              }
              else if( if_b[m][n] == 2 || if_b[m][n] == 1 )
              {
                  continue;
              }

              for(int x=0; x<19; x++)
              {
                  for(int y=0; y<19; y++)
                  {
                //00022000
                if( if_b[x-2][y+2] == 0 && if_b[x-1][y+1] == 0 && if_b[x][y] == 0 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 1 &&
                    if_b[x+3][y-3] == 0 && if_b[x+4][y-4] == 0 && if_b[x+5][y-5] == 0 )
                    B_weight[m][n] += 2000;
                //0020200
                if( if_b[x-1][y+1] == 0 && if_b[x][y] == 0 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 0 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] == 0 &&
                    if_b[x+5][y-5] == 0 )
                    B_weight[m][n] += 1500;
                //020020
                if( if_b[x][y] == 0 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 0 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] == 1 && if_b[x+5][y-5] == 0 )
                    B_weight[m][n] += 1000;
                //여기까지 양쪽에 안 막힌, 흰 돌이 2개가 발견 될 때 경우의 수들

                //122000
                if( if_b[x][y] == 2 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 1 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] == 0 && if_b[x+5][y-5] == 0 )
                    B_weight[m][n] += 500;
                //120200
                if( if_b[x][y] == 2 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 0 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] == 0 && if_b[x+5][y-5] == 0 )
                    B_weight[m][n] += 500;
                //120020
                if( if_b[x][y] == 2 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 0 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] == 1 && if_b[x+5][y-5] == 0 )
                    B_weight[m][n] += 500;
                //102200
                if( if_b[x][y] == 2 && if_b[x+1][y-1] == 0 && if_b[x+2][y-2] == 1 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] == 0 && if_b[x+5][y-5] == 0 )
                    B_weight[m][n] += 800;
                //102020
                if( if_b[x][y] == 2 && if_b[x+1][y-1] == 0 && if_b[x+2][y-2] == 1 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] == 1 && if_b[x+5][y-5] == 0 )
                    B_weight[m][n] += 800;
                //여기까지 왼쪽에 검은돌로 막힌 경우.
                //오른쪽에 검은돌로 막힌 경우는 이 대칭으로만 작성해주면됌

                //000221
                if( if_b[x-2][y+2] == 0 && if_b[x-1][y+1] == 0 && if_b[x][y] == 0 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 1 && if_b[x+3][y-3] == 2 )
                    B_weight[m][n] += 500;
                //002021
                if( if_b[x-1][y+1] == 0 && if_b[x][y] == 0 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 0 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] == 2 )
                    B_weight[m][n] += 500;
                //020021
                if( if_b[x][y] == 0 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 0 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] == 1 && if_b[x+5][y-5] == 2 )
                    B_weight[m][n] += 500;
                //002201
                if( if_b[x-1][y+1] == 0 && if_b[x][y] == 0 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 1 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] == 2 )
                    B_weight[m][n] += 800;
                //020201
                if( if_b[x][y] == 0 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 0 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] == 0 && if_b[x+5][y-5] == 2 )
                    B_weight[m][n] += 800;
                //여기까지 한쪽이 막힌 경우.
                //그 다음은 양쪽이 막힌 경우. 양쪽이 막힌 경우는 안이 6칸일 경우만 따지자.

                //12200001
                if( if_b[x][y] == 2 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 1 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] == 0 && if_b[x+5][y-5] == 0 &&
                    if_b[x+6][y-6] == 0 && if_b[x+7][y-7] == 2 )
                    B_weight[m][n] += 300;
                //12020001
                if( if_b[x][y] == 2 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 0 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] == 0 && if_b[x+5][y-5] == 0 &&
                    if_b[x+6][y-6] == 0 && if_b[x+7][y-7] == 2 )
                    B_weight[m][n] += 300;
                //12002001
                if( if_b[x][y] == 2 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 0 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] == 1 && if_b[x+5][y-5] == 0 &&
                    if_b[x+6][y-6] == 0 && if_b[x+7][y-7] == 2 )
                    B_weight[m][n] += 300;
                //12000201
                if( if_b[x][y] == 2 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 0 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] == 0 && if_b[x+5][y-5] == 1 &&
                    if_b[x+6][y-6] == 0 && if_b[x+7][y-7] == 2 )
                    B_weight[m][n] += 300;
                //12000021
                if( if_b[x][y] == 2 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 0 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] == 0 && if_b[x+5][y-5] == 0 &&
                    if_b[x+6][y-6] == 1 && if_b[x+7][y-7] == 2 )
                    B_weight[m][n] += 300;
                //10220001
                if( if_b[x][y] == 2 && if_b[x+1][y-1] == 0 && if_b[x+2][y-2] == 1 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] == 0 && if_b[x+5][y-5] == 0 &&
                    if_b[x+6][y-6] == 0 && if_b[x+7][y-7] == 2 )
                    B_weight[m][n] += 300;
                //10202001
                if( if_b[x][y] == 2 && if_b[x+1][y-1] == 0 && if_b[x+2][y-2] == 1 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] == 1 && if_b[x+5][y-5] == 0 &&
                    if_b[x+6][y-6] == 0 && if_b[x+7][y-7] == 2 )
                    B_weight[m][n] += 300;
                //10200201
                if( if_b[x][y] == 2 && if_b[x+1][y-1] == 0 && if_b[x+2][y-2] == 1 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] == 0 && if_b[x+5][y-5] == 1 &&
                    if_b[x+6][y-6] == 0 && if_b[x+7][y-7] == 2 )
                    B_weight[m][n] += 300;
                //10200021
                if( if_b[x][y] == 2 && if_b[x+1][y-1] == 0 && if_b[x+2][y-2] == 1 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] == 0 && if_b[x+5][y-5] == 0 &&
                    if_b[x+6][y-6] == 1 && if_b[x+7][y-7] == 2 )
                    B_weight[m][n] += 300;
                //10022001
                if( if_b[x][y] == 2 && if_b[x+1][y-1] == 0 && if_b[x+2][y-2] == 0 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] == 1 && if_b[x+5][y-5] == 0 &&
                    if_b[x+6][y-6] == 0 && if_b[x+7][y-7] == 2 )
                    B_weight[m][n] += 300;
                //10020201
                if( if_b[x][y] == 2 && if_b[x+1][y-1] == 0 && if_b[x+2][y-2] == 0 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] == 0 && if_b[x+5][y-5] == 1 &&
                    if_b[x+6][y-6] == 0 && if_b[x+7][y-7] == 2 )
                    B_weight[m][n] += 300;
                //10020021
                if( if_b[x][y] == 2 && if_b[x+1][y-1] == 0 && if_b[x+2][y-2] == 0 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] == 0 && if_b[x+5][y-5] == 0 &&
                    if_b[x+6][y-6] == 1 && if_b[x+7][y-7] == 2 )
                    B_weight[m][n] += 300;
                //10002201
                if( if_b[x][y] == 2 && if_b[x+1][y-1] == 0 && if_b[x+2][y-2] == 0 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] == 1 && if_b[x+5][y-5] == 1 &&
                    if_b[x+6][y-6] == 0 && if_b[x+7][y-7] == 2 )
                    B_weight[m][n] += 300;
                //10002021
                if( if_b[x][y] == 2 && if_b[x+1][y-1] == 0 && if_b[x+2][y-2] == 0 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] == 0 && if_b[x+5][y-5] == 1 &&
                    if_b[x+6][y-6] == 0 && if_b[x+7][y-7] == 2 )
                    B_weight[m][n] += 300;
                //10000221
                if( if_b[x][y] == 2 && if_b[x+1][y-1] == 0 && if_b[x+2][y-2] == 0 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] == 0 && if_b[x+5][y-5] == 1 &&
                    if_b[x+6][y-6] == 1 && if_b[x+7][y-7] == 2 )
                    B_weight[m][n] += 300;
                  }
              }
              if_b[m][n] = 0;
          }
        }

}

void AI::B_AI_3_in_Diagonal_check()
{
    for(int m=0 ; m<19 ; m++)
    {
      for(int n=0 ; n<19 ; n++)
      {
          if( if_b[m][n] == 0 )
          {
          if_b[m][n] = 1;
          }
          else if( if_b[m][n] == 2 || if_b[m][n] == 1 )
          {
              continue;
          }

          for(int x=0; x<19; x++)
          {
              for(int y=0; y<19; y++)
              {
            //000222000
            if( if_b[x-1][y+1] == 0 && if_b[x][y] == 0 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 1 && if_b[x+3][y-3] == 1&& if_b[x+4][y-4]==0 &&
                if_b[x+5][y-5] == 0 )
                B_weight[m][n] += 5000;
            //00202200
            if( if_b[x-1][y+1] == 0 && if_b[x][y] == 0 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 0 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] == 1 &&
                if_b[x+5][y-5]==0 && if_b[x+6][y-6] == 0 )
                B_weight[m][n] += 3500;
            //00220200
            if( if_b[x-1][y+1] == 0 && if_b[x][y] == 0 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 1 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] == 1 &&
                if_b[x+5][y-5] == 0 && if_b[x+6][y-6] == 0 )
                B_weight[m][n] += 3500;
            //0200220
            if( if_b[x][y] == 0 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 0 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] == 1 && if_b[x+5][y-5] == 1
                &&if_b[x+6][y-6] ==0 )
                B_weight[m][n] += 3000;
            //0202020
            if( if_b[x][y] == 0 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 0 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] == 0 && if_b[x+5][y-5] == 1
                &&if_b[x+6][y-6]==0 )
                B_weight[m][n] += 3000;
            //0220020
            if( if_b[x][y] == 0 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 1 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] == 0 && if_b[x+5][y-5] == 1
                && if_b[x+6][y-6] ==0 )
                B_weight[m][n] += 3000;
            //여기까지 양쪽에 안 막힌, 흰 돌이 2개가 발견 될 때 경우의 수들

            //122200
            if( if_b[x][y] == 2 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 1 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] ==0 && if_b[x+5][y-5] == 0 )
                B_weight[m][n] += 1000;
            //1202200
            if( if_b[x][y] == 2 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 0 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] == 1 && if_b[x+5][y-5] ==0 &&
                if_b[x][y-6] == 0 )
                B_weight[m][n] += 1000;
            //1220200
            if( if_b[x][y] == 2 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 1 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] == 1 && if_b[x+5][y-5] == 0 &&
                if_b[x+6][y-6] == 0 )
                B_weight[m][n] += 1000;
            //1022200
            if( if_b[x][y] == 2 && if_b[x+1][y-1] == 0 && if_b[x+2][y-2] == 1 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] == 1 && if_b[x+5][y-5] ==0 &&
                if_b[x+6][y-6] == 0 )
                B_weight[m][n] += 1300;
            //1200220
            if( if_b[x][y] == 2 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 0 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] == 1 && if_b[x+5][y-5] == 1 &&
            if_b[x+6][y-6] ==0 )
                B_weight[m][n] += 1300;
            //1220020
            if( if_b[x][y] == 2 && if_b[x][y-1] == 1 && if_b[x][y-2] == 1 && if_b[x][y-3] == 0 && if_b[x][y-4] == 0 && if_b[x][y-5] == 1 &&
                if_b[x][y-6] == 0 )
                B_weight[m][n] += 1000;
            //1202020
            if( if_b[x][y] == 2 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 0 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] == 0 && if_b[x+5][y-5] == 1 &&
                if_b[x+6][y-6] ==0 )
                B_weight[m][n] += 1000;
            //1020220
            if( if_b[x][y] == 2 && if_b[x+1][y-1] == 0 && if_b[x+2][y-2] == 1 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] == 1 && if_b[x+5][y-5] == 1 &&
                if_b[x+6][y-6] == 0)
                B_weight[m][n] += 1300;

            //여기까지 왼쪽에 검은돌로 막힌 경우.
            //오른쪽에 검은돌로 막힌 경우는 이 대칭으로만 작성해주면됌

            //002221
            if( if_b[x-1][y+1] == 0 && if_b[x][y] == 0 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 1 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] == 2 )
                B_weight[m][n] += 1000;
            //0022021
            if( if_b[x-1][y+1] == 0 && if_b[x][y] == 0 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 1 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] == 1 &&
                if_b[x+5][y-5]==2 )
                B_weight[m][n] += 1000;
            //0020221
            if( if_b[x-1][y+1] == 0 && if_b[x][y] == 0 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 0 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] == 1 &&
                if_b[x+5][y-5] == 2 )
                B_weight[m][n] += 1000;
            //0022201
            if( if_b[x-1][y+1] == 0 && if_b[x][y] == 0 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 1 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] == 0 &&
                if_b[x+5][y-5] == 2 )
                B_weight[m][n] += 1300;
            //0220021
            if( if_b[x][y] == 0 && if_b[x][y-1] == 1 && if_b[x][y-2] == 1 && if_b[x][y-3] == 0 && if_b[x][y-4] == 0 && if_b[x][y-5] == 1 &&
                if_b[x][y-6] == 2 )
                B_weight[m][n] += 1300;
            //0200221
            if( if_b[x][y] == 0 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 0 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] == 1 && if_b[x+5][y-5] == 1 &&
                if_b[x+6][y-6] == 2 )
                B_weight[m][n] += 1000;
            //0202021
            if( if_b[x][y] == 0 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 0 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] == 0 && if_b[x+5][y-5] == 1 &&
                if_b[x+6][y-6] == 2 )
                B_weight[m][n] += 1000;
            //0220201
            if( if_b[x][y] == 0 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 1 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] == 1 && if_b[x+5][y-5] == 0 &&
                if_b[x+6][y-6] == 2 )
                B_weight[m][n] += 1300;

            //여기까지 한쪽이 막힌 경우.
            //그 다음은 양쪽이 막힌 경우. 양쪽이 막힌 경우는 안이 6칸일 경우만 따지자.

            //12220001
            if( if_b[x][y] == 2 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 1 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] == 0 && if_b[x+5][y-5] == 0 &&
                if_b[x+6][y-6] == 0 && if_b[x+7][y-7] == 2 )
                B_weight[m][n] += 300;
            //12022001
            if( if_b[x][y] == 2 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 0 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] == 1 && if_b[x+5][y-5] == 0 &&
                if_b[x+6][y-6] == 0 && if_b[x+7][y-7] == 2 )
                B_weight[m][n] += 300;
            //12002201
            if( if_b[x][y] == 2 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 0 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] == 1 && if_b[x+5][y-5] == 1 &&
                if_b[x+6][y-6] == 0 && if_b[x+7][y-7] == 2 )
                B_weight[m][n] += 300;
            //12000221
            if( if_b[x][y] == 2 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 0 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] == 0 && if_b[x+5][y-5] == 1 &&
                if_b[x+6][y-6] == 1 && if_b[x+7][y-7] == 2 )
                B_weight[m][n] += 300;
            //12202001
            if( if_b[x][y] == 2 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 1 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] == 1 && if_b[x+5][y-5] == 0 &&
                if_b[x+6][y-6] == 0 && if_b[x+7][y-7] == 2 )
                B_weight[m][n] += 300;
            //12200201
            if( if_b[x][y] == 2 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 1 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] == 0 && if_b[x+5][y-5] == 1 &&
                if_b[x+6][y-6] == 0 && if_b[x+7][y-7] == 2 )
                B_weight[m][n] += 300;
            //12200021
            if( if_b[x][y] == 2 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 1 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] == 0 && if_b[x+5][y-5] == 0 &&
                if_b[x+6][y-6] == 1 && if_b[x+7][y-7] == 2 )
                B_weight[m][n] += 300;
            //12002021
            if( if_b[x][y] == 2 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 0 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] == 1 && if_b[x+5][y-5] == 0 &&
                if_b[x+6][y-6] == 1 && if_b[x+7][y-7] == 2 )
                B_weight[m][n] += 300;
            //12020021
            if( if_b[x][y] == 2 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 0 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] == 0 && if_b[x+5][y-5] == 0 &&
                if_b[x+6][y-6] == 1 && if_b[x+7][y-7] == 2 )
                B_weight[m][n] += 300;
            //12020201
            if( if_b[x][y] == 2 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 0 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] == 0 && if_b[x+5][y-5] == 1 &&
                if_b[x+6][y-6] == 0 && if_b[x+7][y-7] == 2 )
                B_weight[m][n] += 300;
            //10222001
            if( if_b[x][y] == 2 && if_b[x+1][y-1] == 0 && if_b[x+2][y-2] == 1 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] == 1 && if_b[x+5][y-5] == 0 &&
                if_b[x+6][y-6] == 0 && if_b[x+7][y-7] == 2 )
                B_weight[m][n] += 300;
            //10202201
            if( if_b[x][y] == 2 && if_b[x+1][y-1] == 0 && if_b[x+2][y-2] == 1 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] == 1 && if_b[x+5][y-5] == 1 &&
                if_b[x+6][y-6] == 0 && if_b[x+7][y-7] == 2 )
                B_weight[m][n] += 300;
            //10200221
            if( if_b[x][y] == 2 && if_b[x+1][y-1] == 0 && if_b[x+2][y-2] == 1 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] == 0 && if_b[x+5][y-5] == 1 &&
                if_b[x+6][y-6] == 1 && if_b[x+7][y-7] == 2 )
                B_weight[m][n] += 300;
            //10220201
            if( if_b[x][y] == 2 && if_b[x+1][y-1] == 0 && if_b[x+2][y-2] == 1 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] == 0 && if_b[x+5][y-5] == 1 &&
                if_b[x+6][y-6] == 0 && if_b[x+7][y-7] == 2 )
                B_weight[m][n] += 300;
            //10220021
            if( if_b[x][y] == 2 && if_b[x+1][y-1] == 0 && if_b[x+2][y-2] == 1 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] == 0 && if_b[x+5][y-5] == 0 &&
                if_b[x+6][y-6] == 1 && if_b[x+7][y-7] == 2 )
                B_weight[m][n] += 300;
            //10022021
            if( if_b[x][y] == 2 && if_b[x+1][y-1] == 0 && if_b[x+2][y-2] == 0 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] == 1 && if_b[x+5][y-5] == 0 &&
                if_b[x+6][y-6] == 1 && if_b[x+7][y-7] == 2 )
                B_weight[m][n] += 300;
            //10022201
            if( if_b[x][y] == 2 && if_b[x+1][y-1] == 0 && if_b[x+2][y-2] == 0 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] == 1 && if_b[x+5][y-5] == 1 &&
                if_b[x+6][y-6] == 0 && if_b[x+7][y-7] == 2 )
                B_weight[m][n] += 300;
            //10020221
            if( if_b[x][y] == 2 && if_b[x+1][y-1] == 0 && if_b[x+2][y-2] == 0 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] == 0 && if_b[x+5][y-5] == 1 &&
                if_b[x+6][y-6] == 1 && if_b[x+7][y-7] == 2 )
                B_weight[m][n] += 300;
            //10002221
            if( if_b[x][y] == 2 && if_b[x+1][y-1] == 0 && if_b[x+2][y-2] == 0 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] == 0 && if_b[x+5][y-5] == 1 &&
                if_b[x+6][y-6] == 1 && if_b[x+7][y-7] == 2 )
                B_weight[m][n] += 300;
            //10202021
            if( if_b[x][y] == 2 && if_b[x+1][y-1] == 0 && if_b[x+2][y-2] == 1 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] == 1 && if_b[x+5][y-5] == 0 &&
                if_b[x+6][y-6] == 1 && if_b[x+7][y-7] == 2 )
                B_weight[m][n] += 300;
                }
          }
          if_b[m][n] = 0;
      }
    }

}

void AI::B_AI_4_in_Diagonal_check()
{
    for(int m=0 ; m<19 ; m++)
        {
          for(int n=0 ; n<19 ; n++)
          {
              if( if_b[m][n] == 0 )
              {
              if_b[m][n] = 1;
              }
              else if( if_b[m][n] == 2 || if_b[m][n] == 1 )
              {
                  continue;
              }

              for(int x=0; x<19; x++)
              {
                  for(int y=0; y<19; y++)
                  {
       /*4개 -> 안막혔을 때*/
             //00222200
             if( if_b[x-1][y+1] == 0 && if_b[x][y]== 0 && if_b[x+1][y-1]== 1 && if_b[x+2][y-2]== 1 &&if_b[x+3][y-3] == 1 && if_b[x+4][y-4] == 1 &&
                 if_b[x+5][y-5] == 0 )
                B_weight[m][n] += 10000;
             //002022200
             if( if_b[x-1][y+1] == 0 && if_b[x][y]==0 && if_b[x+1][y-1]==1 && if_b[x+2][y-2]==0 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] ==1 &&
                 if_b[x+5][y-5]==1 &&if_b[x+6][y-6] ==0 && if_b[x+7][y-7] == 0 )
                B_weight[m][n] += 7000;
             //002220200
             if( if_b[x-1][y+1] == 0 && if_b[x][y]== 0 && if_b[x+1][y-1]== 1 && if_b[x+2][y-2]== 1 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] == 0 &&
                 if_b[x+5][y-5] ==1 &&if_b[x+6][y-6] == 0 && if_b[x+7][y-7] == 0 )
                B_weight[m][n] += 7000;
             //002202200
             if( if_b[x-1][y+1] == 0 && if_b[x][y]== 0 && if_b[x+1][y-1]== 1 && if_b[x+2][y-2]== 1 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] == 1 &&
                 if_b[x+5][y-5] == 1 && if_b[x+6][y-6] == 0 && if_b[x+7][y-7] == 0 )
                B_weight[m][n] += 7000;
             //02220020
             if( if_b[x][y]==0 && if_b[x+1][y-1]==1 && if_b[x+2][y-2]==1 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] ==0 && if_b[x+5][y-5] ==0 &&
                 if_b[x+6][y-6] ==1 && if_b[x+7][y-7] ==0 )
                B_weight[m][n] += 5000;
             //02002220
             if( if_b[x][y] == 0 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 0 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] == 1 && if_b[x+5][y-5] == 1 &&
                 if_b[x+6][y-6] == 1 && if_b[x+7][y-7] == 0 )
                B_weight[m][n] += 5000;
             //02202020
             if( if_b[x][y] == 0 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 1 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] == 1 && if_b[x+5][y-5] == 1 &&
                 if_b[x+6][y-6] == 1 && if_b[x+7][y-7] == 0 )
                B_weight[m][n] += 4000;
             //02020220
             if(if_b[x][y] == 0 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 0 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] == 0 && if_b[x+5][y-5] == 1 &&
                 if_b[x+6][y-6] == 1 && if_b[x+7][y-7] == 0 )
                B_weight[m][n] += 4000;

             //4개 한쪽 막혔을 때
             //122220
             if(if_b[x][y]==2 && if_b[x+1][y-1]==1 && if_b[x+2][y-2]==1 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] ==1 && if_b[x+5][y-5] ==0)
                B_weight[m][n] += 2500;
             //1202220
             if(if_b[x][y]==2 && if_b[x+1][y-1]==1 && if_b[x+2][y-2]==0 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] ==1 && if_b[x+5][y-5] ==1 &&if_b[x+6][y-6] ==0)
                B_weight[m][n] += 2500;
             //1220220
             if(if_b[x][y]==2 && if_b[x+1][y-1]==1 && if_b[x+2][y-2]==1 && if_b[x+3][y-3] ==0 && if_b[x+4][y-4] ==1 && if_b[x+5][y-5] ==1 &&if_b[x+6][y-6] ==0)
                B_weight[m][n] += 2500;
             //1222020
             if(if_b[x][y]==2 && if_b[x+1][y-1]==1 && if_b[x+2][y-2]==1 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] ==0 && if_b[x+5][y-5] ==1 &&if_b[x+6][y-6] ==0)
                B_weight[m][n] += 2500;
             //1022220
             if(if_b[x][y]==2 && if_b[x+1][y-1]==0 && if_b[x+2][y-2]==1 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] ==1 && if_b[x+5][y-5] ==1 &&if_b[x+6][y-6] ==0)
                B_weight[m][n] += 2500;
             //12002220
             if(if_b[x][y]==2 && if_b[x+1][y-1]==1 && if_b[x+2][y-2]==0 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] ==1 && if_b[x+5][y-5] ==1 &&if_b[x+6][y-6] ==1 &&
                 if_b[x+7][y-7]==0)
                B_weight[m][n] += 2500;
             //12020220
             if(if_b[x][y]==2 && if_b[x+1][y-1]==1 && if_b[x+2][y-2]==0 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] ==0 && if_b[x+5][y-5] ==1 &&if_b[x+6][y-6] ==1 &&
                 if_b[x+7][y-7]==0)
                B_weight[m][n] += 2500;
             //12022020
             if(if_b[x][y]==2 && if_b[x+1][y-1]==1 && if_b[x+2][y-2]==0 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] ==1 && if_b[x+5][y-5] ==0 &&if_b[x+6][y-6] ==1 &&
                 if_b[x+7][y-7]==0)
                B_weight[m][n] += 2500;
             //12200220
             if(if_b[x][y]==2 && if_b[x+1][y-1]==1 && if_b[x+2][y-2]==1 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] ==0 && if_b[x+5][y-5] ==1 &&if_b[x+6][y-6] ==1 &&
                 if_b[x+7][y-7]==0 )
                B_weight[m][n] += 2500;
             //12202020
             if(if_b[x][y]==2 && if_b[x+1][y-1]==1 && if_b[x+2][y-2]==1 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] ==1 && if_b[x+5][y-5] ==0 &&if_b[x+6][y-6] ==1 &&
                 if_b[x+7][y-7]==0)
                B_weight[m][n] += 2500;
             //12220020
             if(if_b[x][y]==2 && if_b[x+1][y-1]==1 && if_b[x+2][y-2]==1 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] ==0 && if_b[x+5][y-5] ==0 &&if_b[x+6][y-6] ==1 &&
                 if_b[x+7][y-7]==0)
                B_weight[m][n] += 2500;
             //10220220
             if(if_b[x][y]==2 && if_b[x+1][y-1]==0 && if_b[x+2][y-2]==1 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] ==0 && if_b[x+5][y-5] ==1 &&if_b[x+6][y-6] ==1 &&
                 if_b[x+7][y-7]==0)
                B_weight[m][n] += 2500;
             //10222020
             if(if_b[x][y]==2 && if_b[x+1][y-1]==0 && if_b[x+2][y-2]==1 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] ==1 && if_b[x+5][y-5] ==0 &&if_b[x+6][y-6] ==1 &&
                 if_b[x+7][y-7]==0)
                B_weight[m][n] += 2500;
             //10202220
             if(if_b[x][y]==2 && if_b[x+1][y-1]==0 && if_b[x+2][y-2]==1 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] ==1 && if_b[x+5][y-5] ==1 &&if_b[x+6][y-6] ==1 &&
                 if_b[x+7][y-7]==0)
                B_weight[m][n] += 2500;


             //4개 한쪽 막혔을 때 reverse
             //022221
             if(if_b[x][y]==0 && if_b[x+1][y-1]==1 && if_b[x+2][y-2]==1 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] ==1 && if_b[x+5][y-5] ==2)
                B_weight[m][n] += 2500;
             //0222021
             if(if_b[x][y]==0 && if_b[x+1][y-1]==1 && if_b[x+2][y-2]==1 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] ==0 && if_b[x+5][y-5] ==1 &&if_b[x+6][y-6] ==2)
                B_weight[m][n] += 2500;
             //0220221
             if(if_b[x][y]==0 && if_b[x+1][y-1]==1 && if_b[x+2][y-2]==1 && if_b[x+3][y-3] ==0 && if_b[x+4][y-4] ==1 && if_b[x+5][y-5] ==1 &&if_b[x+6][y-6] ==2)
                B_weight[m][n] += 2500;
             //0202221
             if(if_b[x][y]==0 && if_b[x+1][y-1]==1 && if_b[x+2][y-2]==0 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] ==1 && if_b[x+5][y-5] ==1 &&if_b[x+6][y-6] ==2)
                B_weight[m][n] += 2500;
             //0222201
             if(if_b[x][y]==0 && if_b[x+1][y-1]==1 && if_b[x+2][y-2]==1 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] ==1 && if_b[x+5][y-5] ==0 &&if_b[x+6][y-6] ==2)
                B_weight[m][n] += 2500;
             //02220021
             if(if_b[x][y]==0 && if_b[x+1][y-1]==1 && if_b[x+2][y-2]==1 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] ==0 && if_b[x+5][y-5] ==0 &&if_b[x+6][y-6] ==1 &&
                 if_b[x+7][y-7] ==2)
                B_weight[m][n] += 2500;
             //02202021
             if(if_b[x][y]==0 && if_b[x+1][y-1]==1 && if_b[x+2][y-2]==1 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] ==1 && if_b[x+5][y-5] ==0 &&if_b[x+6][y-6] ==1 &&
                 if_b[x+7][y-7] ==2)
                B_weight[m][n] += 2500;
             //02022021
             if(if_b[x][y]==0 && if_b[x+1][y-1]==1 && if_b[x+2][y-2]==0 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] ==1 && if_b[x+5][y-5] ==0 &&if_b[x+6][y-6] ==1 &&
                 if_b[x+7][y-7] ==2)
                B_weight[m][n] += 2500;
             //02200221
             if(if_b[x][y]==0 && if_b[x+1][y-1]==1 && if_b[x+2][y-2]==1 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] ==0 && if_b[x+5][y-5] ==1 &&if_b[x+6][y-6] ==1 &&
                 if_b[x+7][y-7] ==2 )
                B_weight[m][n] += 2500;
             //02020221
             if(if_b[x][y]==0 && if_b[x+1][y-1]==1 && if_b[x+2][y-2]==0 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] ==0 && if_b[x+5][y-5] ==1 &&if_b[x+6][y-6] ==1 &&
                 if_b[x+7][y-7] ==2)
                B_weight[m][n] += 2500;
             //02002221
             if(if_b[x][y]==0 && if_b[x+1][y-1]==1 && if_b[x+2][y-2]==0 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] ==1 && if_b[x+5][y-5] ==1 &&if_b[x+6][y-6] ==1 &&
                 if_b[x+7][y-7] ==2)
                B_weight[m][n] += 2500;
             //02202201
             if(if_b[x][y]==0 && if_b[x+1][y-1]==1 && if_b[x+2][y-2]==1 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] ==1 && if_b[x+5][y-5] ==1 &&if_b[x+6][y-6] ==0 &&
                 if_b[x+7][y-7] ==2)
                B_weight[m][n] += 2500;
             //02022201
             if(if_b[x][y]==0 && if_b[x+1][y-1]==1 && if_b[x+2][y-2]==0 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] ==1 && if_b[x+5][y-5] ==1 &&if_b[x+6][y-6] ==0 &&
                 if_b[x+7][y-7] ==2)
                B_weight[m][n] += 2500;
             //02220201
             if(if_b[x][y]==0 && if_b[x+1][y-1]==1 && if_b[x+2][y-2]==1 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] ==0 && if_b[x+5][y-5] ==1 &&if_b[x+6][y-6] ==0 &&
                 if_b[x+7][y-7] ==2)
                B_weight[m][n] += 2500;



             //양쪽 다 막혔을 때

             //12022021
             if(if_b[x][y]==2 && if_b[x+1][y-1]==1 && if_b[x+2][y-2]==0 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] ==1 && if_b[x+5][y-5] ==0 &&if_b[x+6][y-6] ==1 &&if_b[x+7][y-7] ==2 )
                B_weight[m][n] += 1000;
             //12200221
             if(if_b[x][y]==2 && if_b[x+1][y-1]==1 && if_b[x+2][y-2]==1 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] ==0 && if_b[x+5][y-5] ==1 &&if_b[x+6][y-6] ==1 &&if_b[x+7][y-7] ==2 )
                B_weight[m][n] += 1000;
             //12220021
             if(if_b[x][y]==2 && if_b[x+1][y-1]==1 && if_b[x+2][y-2]==1 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] ==0 && if_b[x+5][y-5] ==0 &&if_b[x+6][y-6] ==1 &&if_b[x+7][y-7] ==2)
                B_weight[m][n] += 1000;
             //12002221
             if(if_b[x][y]==2 && if_b[x+1][y-1]==1 && if_b[x+2][y-2]==0 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] ==1 && if_b[x+5][y-5] ==1 &&if_b[x+6][y-6] ==1 &&if_b[x+7][y-7] ==2 )
                B_weight[m][n] += 1000;
             //12202021
             if(if_b[x][y]==2 && if_b[x+1][y-1]==1 && if_b[x+2][y-2]==1 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] ==1 && if_b[x+5][y-5] ==1 &&if_b[x+6][y-6] ==1 &&if_b[x+7][y-7] ==2)
                B_weight[m][n] += 1000;
             //12020221
             if(if_b[x][y]==2 && if_b[x+1][y-1]==1 && if_b[x+2][y-2]==0 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] ==0 && if_b[x+5][y-5] ==1 &&if_b[x+6][y-6] ==1 &&if_b[x+7][y-7] ==2 )
                B_weight[m][n] += 1000;
             //10222201
           if(if_b[x][y]==2 && if_b[x+1][y-1]==0 && if_b[x+2][y-2]==1 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] ==1 && if_b[x+5][y-5] ==1 &&if_b[x+6][y-6] ==0 &&if_b[x+7][y-7] ==2 )
                B_weight[m][n] += 1000;
           //10222021
           if(if_b[x][y]==2 && if_b[x+1][y-1]==0 && if_b[x+2][y-2]==1 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] ==1 && if_b[x+5][y-5] ==0 &&if_b[x+6][y-6] ==1 &&if_b[x+7][y-7] ==2 )
                B_weight[m][n] += 1000;
           //10220221
           if(if_b[x][y]==2 && if_b[x+1][y-1]==0 && if_b[x+2][y-2]==1 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] ==0 && if_b[x+5][y-5] ==1 &&if_b[x+6][y-6] ==1 &&if_b[x+7][y-7] ==2 )
                B_weight[m][n] += 1000;
            //10202221
           if(if_b[x][y]==2 && if_b[x+1][y-1]==0 && if_b[x+2][y-2]==1 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] ==1 && if_b[x+5][y-5] ==1 &&if_b[x+6][y-6] ==1 &&if_b[x+7][y-7] ==2 )
                B_weight[m][n] += 1000;
           //10022221
           if(if_b[x][y]==2 && if_b[x+1][y-1]==0 && if_b[x+2][y-2]==0 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] ==1 && if_b[x+5][y-5] ==1 &&if_b[x+6][y-6] ==1 &&if_b[x+7][y-7] ==2 )
                B_weight[m][n] += 1000;
           //12022201
           if(if_b[x][y]==2 && if_b[x+1][y-1]==1 && if_b[x+2][y-2]==0 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] ==1 && if_b[x+5][y-5] ==1 &&if_b[x+6][y-6] ==0 &&if_b[x+7][y-7] ==2 )
                B_weight[m][n] += 1000;
           //12202201
           if(if_b[x][y]==2 && if_b[x+1][y-1]==1 && if_b[x+2][y-2]==1 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] ==1 && if_b[x+5][y-5] ==1 &&if_b[x+6][y-6] ==0 &&if_b[x+7][y-7] ==2 )
                B_weight[m][n] += 1000;
           //12220201
           if(if_b[x][y]==2 && if_b[x+1][y-1]==1 && if_b[x+2][y-2]==1 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] ==0 && if_b[x+5][y-5] ==1 &&if_b[x+6][y-6] ==0 &&if_b[x+7][y-7] ==2 )
                B_weight[m][n] += 1000;
           //12222001
           if(if_b[x][y]==2 && if_b[x+1][y-1]==1 && if_b[x+2][y-2]==1 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] ==1 && if_b[x+5][y-5] ==0 &&if_b[x+6][y-6] ==0 &&if_b[x+7][y-7] ==2 )
                B_weight[m][n] += 1000;
             }
             }
             if_b[m][n] = 0;
             }
             }

}

void AI::defense_Horizontal_check_B()
{
    for(int m=0 ; m<19 ; m++)
    {
        for(int n=0 ; n<19 ; n++)
        {
            if( if_b[m][n] == 0 )
            {
                if_b[m][n] = 1;
            }
            else if( if_b[m][n] == 2 || if_b[m][n] == 1 )
            {
                continue;
            }

            for(int x=0; x<19; x++)
            {
                for(int y=0; y<19; y++)
                {
                    //다섯개에 양쪽다 막도록.
                    //2111112 이런상황이 되게 할때 점수가 높이 준다.
                    if( if_b[x][y] == 1 && if_b[x][y+1] == 2 && if_b[x][y+2] == 2 && if_b[x][y+3] == 2 && if_b[x][y+4] == 2 &&
                        if_b[x][y+5] == 2 && if_b[x][y+6] == 1 )
                        B_weight[m][n] += 750000;
                    //2111110
                    if( if_b[x][y] == 1 && if_b[x][y+1] == 2 && if_b[x][y+2] == 2 && if_b[x][y+3] == 2 && if_b[x][y+4] == 2 &&
                        if_b[x][y+5] == 2 && if_b[x][y+6] == 0 )
                        B_weight[m][n] += 500000;
                    //0111112
                    if( if_b[x][y] == 0 && if_b[x][y+1] == 2 && if_b[x][y+2] == 2 && if_b[x][y+3] == 2 && if_b[x][y+4] == 2 &&
                        if_b[x][y+5] == 2 && if_b[x][y+6] == 1 )
                        B_weight[m][n] += 500000;
                    //121111
                    if( if_b[x][y] == 2 && if_b[x][y+1] == 1 && if_b[x][y+2] == 2 && if_b[x][y+3] == 2 && if_b[x][y+4] == 2 &&
                        if_b[x][y+5] == 2 )
                        B_weight[m][n] += 500000;
                    //112111
                    if( if_b[x][y] == 2 && if_b[x][y+1] == 2 && if_b[x][y+2] == 1 && if_b[x][y+3] == 2 && if_b[x][y+4] == 2 &&
                        if_b[x][y+5] == 2 )
                        B_weight[m][n] += 500000;
                    //111211
                    if( if_b[x][y] == 2 && if_b[x][y+1] == 2 && if_b[x][y+2] == 2 && if_b[x][y+3] == 1 && if_b[x][y+4] == 2 &&
                        if_b[x][y+5] == 2 )
                        B_weight[m][n] += 500000;
                    //111121
                    if( if_b[x][y] == 2 && if_b[x][y+1] == 2 && if_b[x][y+2] == 2 && if_b[x][y+3] == 2 && if_b[x][y+4] == 1 &&
                        if_b[x][y+5] == 2 )
                        B_weight[m][n] += 500000;

                    //추가부분 상대방 4개짜리 사이 빈칸있을때 사이 막기
                    //202122
                    if( if_b[x][y] == 2 && if_b[x][y+1] == 0 && if_b[x][y+2] == 2 && if_b[x][y+3] == 1 && if_b[x][y+4] == 2 &&
                        if_b[x][y+5] == 2 )
                        B_weight[m][n] += 500000;
                    //202212
                    if( if_b[x][y] == 2 && if_b[x][y+1] == 0 && if_b[x][y+2] == 2 && if_b[x][y+3] == 2 && if_b[x][y+4] == 1 &&
                        if_b[x][y+5] == 2 )
                        B_weight[m][n] += 500000;
                    //212022
                    if( if_b[x][y] == 2 && if_b[x][y+1] == 1 && if_b[x][y+2] == 2 && if_b[x][y+3] == 0 && if_b[x][y+4] == 2 &&
                        if_b[x][y+5] == 2 )
                        B_weight[m][n] += 500000;
                    //212202
                    if( if_b[x][y] == 2 && if_b[x][y+1] == 1 && if_b[x][y+2] == 2 && if_b[x][y+3] == 2 && if_b[x][y+4] == 0 &&
                        if_b[x][y+5] == 2 )
                        B_weight[m][n] += 500000;
                    //221202
                    if( if_b[x][y] == 2 && if_b[x][y+1] == 2 && if_b[x][y+2] == 1 && if_b[x][y+3] == 2 && if_b[x][y+4] == 0 &&
                        if_b[x][y+5] == 2 )
                        B_weight[m][n] += 500000;
                    //220212
                    if( if_b[x][y] == 2 && if_b[x][y+1] == 2 && if_b[x][y+2] == 0 && if_b[x][y+3] == 2 && if_b[x][y+4] == 1 &&
                        if_b[x][y+5] == 2 )
                        B_weight[m][n] += 500000;


                    //211112
                    if( if_b[x][y] == 1 && if_b[x][y+1] == 2 && if_b[x][y+2] == 2 && if_b[x][y+3] == 2 && if_b[x][y+4] == 2 &&
                        if_b[x][y+5] == 1 )
                        B_weight[m][n] += 500000;
                    //211110
                    if( if_b[x][y] == 1 && if_b[x][y+1] == 2 && if_b[x][y+2] == 2 && if_b[x][y+3] == 2 && if_b[x][y+4] == 2 &&
                        if_b[x][y+5] == 0 )
                        B_weight[m][n] += 500000;
                    //X11112
                    if( if_b[x][y] != 1 && if_b[x][y+1] == 2 && if_b[x][y+2] == 2 && if_b[x][y+3] == 2 && if_b[x][y+4] == 2 &&
                        if_b[x][y+5] == 1)
                        B_weight[m][n] += 500000;
                    //2111102
                    if( if_b[x][y] == 1 && if_b[x][y+1] == 2 && if_b[x][y+2] == 2 && if_b[x][y+3] == 2 && if_b[x][y+4] == 2 &&
                        if_b[x][y+5] == 0 && if_b[x][y+6] == 1 )
                        B_weight[m][n] += 500000;
                    //2011112
                    if( if_b[x][y] == 1 && if_b[x][y+1] == 0 && if_b[x][y+2] == 2 && if_b[x][y+3] == 2 && if_b[x][y+4] == 2 &&
                        if_b[x][y+5] == 2 && if_b[x][y+6] == 1 )
                        B_weight[m][n] += 500000;

                    //x12111x
                    if( if_b[x][y+1] == 2 && if_b[x][y+2] == 1 && if_b[x][y+3] == 2 && if_b[x][y+4] == 2 &&
                        if_b[x][y+5] == 2 && if_b[x][y+6] != 1 )
                        B_weight[m][n] += 500000;
                    //x11211x
                    if( if_b[x][y+1] == 2 && if_b[x][y+2] == 2 && if_b[x][y+3] == 1 && if_b[x][y+4] == 2 &&
                        if_b[x][y+5] == 2 && if_b[x][y+6] != 1 )
                        B_weight[m][n] += 500000;
                    //x11121x
                    if( if_b[x][y+1] == 2 && if_b[x][y+2] == 2 && if_b[x][y+3] == 2 && if_b[x][y+4] == 1 &&
                        if_b[x][y+5] == 2 && if_b[x][y+6] != 1 )
                        B_weight[m][n] += 500000;
                    //x12111x
                    if( if_b[x][y] != 1 && if_b[x][y+1] == 2 && if_b[x][y+2] == 1 && if_b[x][y+3] == 2 && if_b[x][y+4] == 2 &&
                        if_b[x][y+5] == 2 )
                        B_weight[m][n] += 500000;
                    //x11211x
                    if( if_b[x][y] != 1 && if_b[x][y+1] == 2 && if_b[x][y+2] == 2 && if_b[x][y+3] == 1 && if_b[x][y+4] == 2 &&
                        if_b[x][y+5] == 2 )
                        B_weight[m][n] += 500000;
                    //x11121x
                    if( if_b[x][y] != 1 && if_b[x][y+1] == 2 && if_b[x][y+2] == 2 && if_b[x][y+3] == 2 && if_b[x][y+4] == 1 &&
                        if_b[x][y+5] == 2 )
                        B_weight[m][n] += 500000;

                    //120111
                    if( if_b[x][y] == 2 && if_b[x][y+1] == 1 && if_b[x][y+2] == 0 && if_b[x][y+3] == 2 && if_b[x][y+4] == 2 &&
                        if_b[x][y+5] == 2 )
                        B_weight[m][n] += 500000;
                    //102111
                    if( if_b[x][y] == 2 && if_b[x][y+1] == 0 && if_b[x][y+2] == 1 && if_b[x][y+3] == 2 && if_b[x][y+4] == 2 &&
                        if_b[x][y+5] == 2 )
                        B_weight[m][n] += 500000;
                    //111201
                    if( if_b[x][y] == 2 && if_b[x][y+1] == 2 && if_b[x][y+2] == 2 && if_b[x][y+3] == 1 && if_b[x][y+4] == 0 &&
                        if_b[x][y+5] == 2 )
                        B_weight[m][n] += 500000;
                    //111021
                    if( if_b[x][y] == 2 && if_b[x][y+1] == 2 && if_b[x][y+2] == 2 && if_b[x][y+3] == 0 && if_b[x][y+4] == 1 &&
                        if_b[x][y+5] == 2 )
                        B_weight[m][n] += 500000;
                    //112011
                    if( if_b[x][y] == 2 && if_b[x][y+1] == 2 && if_b[x][y+2] == 1 && if_b[x][y+3] == 0 && if_b[x][y+4] == 2 &&
                        if_b[x][y+5] == 2 )
                        B_weight[m][n] += 500000;
                    //110211
                    if( if_b[x][y] == 2 && if_b[x][y+1] == 2 && if_b[x][y+2] == 0 && if_b[x][y+3] == 1 && if_b[x][y+4] == 2 &&
                        if_b[x][y+5] == 2 )
                        B_weight[m][n] += 500000;

                    //여기서부터 간단한 가중치 줄 것. 즉, 2개 3개 막게하는것들
                    //2111
                    if( if_b[x][y] == 1 && if_b[x][y+1] == 2 && if_b[x][y+2] == 2 && if_b[x][y+3] == 2 )
                        B_weight[m][n] += 3500;
                    //1112
                    if( if_b[x][y] == 2 && if_b[x][y+1] == 2 && if_b[x][y+2] == 2 && if_b[x][y+3] == 1 )
                        B_weight[m][n] += 3500;
                    //1211
                    if( if_b[x][y] == 2 && if_b[x][y+1] == 1 && if_b[x][y+2] == 2 && if_b[x][y+3] == 2 )
                        B_weight[m][n] += 4000;
                    //1121
                    if( if_b[x][y] == 2 && if_b[x][y+1] == 2 && if_b[x][y+2] == 1 && if_b[x][y+3] == 2 )
                        B_weight[m][n] += 4000;
                    //11102		분기해서 막는것도 필요한 경우가 있을수있음. 단 점수는 낮게
                    if( if_b[x][y] == 2 && if_b[x][y+1] == 2 && if_b[x][y+2] == 2 && if_b[x][y+3] == 0 && if_b[x][y+4] == 1 )
                        B_weight[m][n] += 1500;
                    //20111
                    if( if_b[x][y] == 1 && if_b[x][y+1] == 0 && if_b[x][y+2] == 2 && if_b[x][y+3] == 2 && if_b[x][y+4] == 2 )
                        B_weight[m][n] += 1500;

                    //21011		점수낮게
                    if( if_b[x][y] == 1 && if_b[x][y+1] == 2 && if_b[x][y+2] == 0 && if_b[x][y+3] == 2 && if_b[x][y+4] == 2 )
                        B_weight[m][n] += 1500;
                    //21101		점수낮게
                    if( if_b[x][y] == 1 && if_b[x][y+1] == 2 && if_b[x][y+2] == 2 && if_b[x][y+3] == 0 && if_b[x][y+4] == 2 )
                        B_weight[m][n] += 1500;
                    //10112		점수낮게
                    if( if_b[x][y] == 2 && if_b[x][y+1] == 0 && if_b[x][y+2] == 2 && if_b[x][y+3] == 2 && if_b[x][y+4] == 1 )
                        B_weight[m][n] += 1500;
                    //11012		점수낮게
                    if( if_b[x][y] == 2 && if_b[x][y+1] == 2 && if_b[x][y+2] == 0 && if_b[x][y+3] == 2 && if_b[x][y+4] == 1 )
                        B_weight[m][n] += 1500;

                    //211
                    if( if_b[x][y] == 1 && if_b[x][y+1] == 2 && if_b[x][y+2] == 2 )
                        B_weight[m][n] += 500;
                    //112
                    if( if_b[x][y] == 2 && if_b[x][y+1] == 2 && if_b[x][y+2] == 1 )
                        B_weight[m][n] += 500;
                    //121
                    if( if_b[x][y] == 2 && if_b[x][y+1] == 1 && if_b[x][y+2] == 2 )
                        B_weight[m][n] += 800;
                }
            }
            if_b[m][n] = 0;
        }
    }

}

void AI::defense_Vertical_check_B()
{
    for(int m=0 ; m<19 ; m++)
    {
        for(int n=0 ; n<19 ; n++)
        {
            if( if_b[m][n] == 0 )
            {
                if_b[m][n] = 1;
            }
            else if( if_b[m][n] == 2 || if_b[m][n] == 1 )
            {
                continue;
            }

            for(int x=0; x<19; x++)
            {
                for(int y=0; y<19; y++)
                {
                    //다섯개에 양쪽다 막도록.
                    //2111112 이런상황이 되게 할때 점수가 높이 준다.
                    if( if_b[x][y] == 1 && if_b[x+1][y] == 2 && if_b[x+2][y] == 2 && if_b[x+3][y] == 2 && if_b[x+4][y] == 2 &&
                        if_b[x+5][y] == 2 && if_b[x+6][y] == 1 )
                        B_weight[m][n] += 750000;
                    //2111110
                    if( if_b[x][y] == 1 && if_b[x+1][y] == 2 && if_b[x+2][y] == 2 && if_b[x+3][y] == 2 && if_b[x+4][y] == 2 &&
                        if_b[x+5][y] == 2 && if_b[x+6][y] == 0 )
                        B_weight[m][n] += 500000;
                    //0111112
                    if( if_b[x][y] == 0 && if_b[x+1][y] == 2 && if_b[x+2][y] == 2 && if_b[x+3][y] == 2 && if_b[x+4][y] == 2 &&
                        if_b[x+5][y] == 2 && if_b[x+6][y] == 1 )
                        B_weight[m][n] += 500000;
                    //121111
                    if( if_b[x][y] == 2 && if_b[x+1][y] == 1 && if_b[x+2][y] == 2 && if_b[x+3][y] == 2 && if_b[x+4][y] == 2 &&
                        if_b[x+5][y] == 2 )
                        B_weight[m][n] += 500000;
                    //112111
                    if( if_b[x][y] == 2 && if_b[x+1][y] == 2 && if_b[x+2][y] == 1 && if_b[x+3][y] == 2 && if_b[x+4][y] == 2 &&
                        if_b[x+5][y] == 2 )
                        B_weight[m][n] += 500000;
                    //111211
                    if( if_b[x][y] == 2 && if_b[x+1][y] == 2 && if_b[x+2][y] == 2 && if_b[x+3][y] == 1 && if_b[x+4][y] == 2 &&
                        if_b[x+5][y] == 2 )
                        B_weight[m][n] += 500000;
                    //111121
                    if( if_b[x][y] == 2 && if_b[x+1][y] == 2 && if_b[x+2][y] == 2 && if_b[x+3][y] == 2 && if_b[x+4][y] == 1 &&
                        if_b[x+5][y] == 2 )
                        B_weight[m][n] += 500000;

                    //추가부분 상대방 4개짜리 사이 빈칸있을때 사이 막기
                    //202122
                    if( if_b[x][y] == 2 && if_b[x+1][y] == 0 && if_b[x+2][y] == 2 && if_b[x+3][y] == 1 && if_b[x+4][y] == 2 &&
                        if_b[x+5][y] == 2 )
                        B_weight[m][n] += 500000;
                    //202212
                    if( if_b[x][y] == 2 && if_b[x+1][y] == 0 && if_b[x+2][y] == 2 && if_b[x+3][y] == 2 && if_b[x+4][y] == 1 &&
                        if_b[x+5][y] == 2 )
                        B_weight[m][n] += 500000;
                    //212022
                    if( if_b[x][y] == 2 && if_b[x+1][y] == 1 && if_b[x+2][y] == 2 && if_b[x+3][y] == 0 && if_b[x+4][y] == 2 &&
                        if_b[x+5][y] == 2 )
                        B_weight[m][n] += 500000;
                    //212202
                    if( if_b[x][y] == 2 && if_b[x+1][y] == 1 && if_b[x+2][y] == 2 && if_b[x+3][y] == 2 && if_b[x+4][y] == 0 &&
                        if_b[x+5][y] == 2 )
                        B_weight[m][n] += 500000;
                    //221202
                    if( if_b[x][y] == 2 && if_b[x+1][y] == 2 && if_b[x+2][y] == 1 && if_b[x+3][y] == 2 && if_b[x+4][y] == 0 &&
                        if_b[x+5][y] == 2 )
                        B_weight[m][n] += 500000;
                    //220212
                    if( if_b[x][y] == 2 && if_b[x+1][y] == 2 && if_b[x+2][y] == 0 && if_b[x+3][y] == 2 && if_b[x+4][y] == 1 &&
                        if_b[x+5][y] == 2 )
                        B_weight[m][n] += 500000;

                    //211112
                    if( if_b[x][y] == 1 && if_b[x+1][y] == 2 && if_b[x+2][y] == 2 && if_b[x+3][y] == 2 && if_b[x+4][y] == 2 &&
                        if_b[x+5][y] == 1 )
                        B_weight[m][n] += 500000;
                    //211110
                    if( if_b[x][y] == 1 && if_b[x+1][y] == 2 && if_b[x+2][y] == 2 && if_b[x+3][y] == 2 && if_b[x+4][y] == 2 &&
                        if_b[x+5][y] == 0 )
                        B_weight[m][n] += 500000;
                    //011112
                    if( if_b[x][y] == 0 && if_b[x+1][y] == 2 && if_b[x+2][y] == 2 && if_b[x+3][y] == 2 && if_b[x+4][y] == 2 &&
                        if_b[x+5][y] == 1)
                        B_weight[m][n] += 500000;
                    //2111102
                    if( if_b[x][y] == 1 && if_b[x+1][y] == 2 && if_b[x+2][y] == 2 && if_b[x+3][y] == 2 && if_b[x+4][y] == 2 &&
                        if_b[x+5][y] == 0 && if_b[x+6][y] == 1 )
                        B_weight[m][n] += 500000;
                    //2011112
                    if( if_b[x][y] == 1 && if_b[x+1][y] == 0 && if_b[x+2][y] == 2 && if_b[x+3][y] == 2 && if_b[x+4][y] == 2 &&
                        if_b[x+5][y] == 2 && if_b[x+6][y] == 1 )
                        B_weight[m][n] += 500000;


                    //x12111x
                    if( if_b[x+1][y] == 2 && if_b[x+2][y] == 1 && if_b[x+3][y] == 2 && if_b[x+4][y] == 2 &&
                        if_b[x+5][y] == 2 && if_b[x+6][y] != 1 )
                        B_weight[m][n] += 500000;
                    //x11211x
                    if( if_b[x+1][y] == 2 && if_b[x+2][y] == 2 && if_b[x+3][y] == 1 && if_b[x+4][y] == 2 &&
                        if_b[x+5][y] == 2 && if_b[x+6][y] != 1 )
                        B_weight[m][n] += 500000;
                    //x11121x
                    if( if_b[x+1][y] == 2 && if_b[x+2][y] == 2 && if_b[x+3][y] == 2 && if_b[x+4][y] == 1 &&
                        if_b[x+5][y] == 2 && if_b[x+6][y] != 1 )
                        B_weight[m][n] += 500000;
                    //x12111x
                    if( if_b[x][y] != 1 && if_b[x+1][y] == 2 && if_b[x+2][y] == 1 && if_b[x+3][y] == 2 && if_b[x+4][y] == 2 &&
                        if_b[x+5][y] == 2 )
                        B_weight[m][n] += 500000;
                    //x11211x
                    if( if_b[x][y] != 1 && if_b[x+1][y] == 2 && if_b[x+2][y] == 2 && if_b[x+3][y] == 1 && if_b[x+4][y] == 2 &&
                        if_b[x+5][y] == 2 )
                        B_weight[m][n] += 500000;
                    //x11121x
                    if( if_b[x][y] != 1 && if_b[x+1][y] == 2 && if_b[x+2][y] == 2 && if_b[x+3][y] == 2 && if_b[x+4][y] == 1 &&
                        if_b[x+5][y] == 2 )
                        B_weight[m][n] += 500000;

                    //120111
                    if( if_b[x][y] == 2 && if_b[x+1][y] == 1 && if_b[x+2][y] == 0 && if_b[x+3][y] == 2 && if_b[x+4][y] == 2 &&
                        if_b[x+5][y] == 2 )
                        B_weight[m][n] += 500000;
                    //102111
                    if( if_b[x][y] == 2 && if_b[x+1][y] == 0 && if_b[x+2][y] == 1 && if_b[x+3][y] == 2 && if_b[x+4][y] == 2 &&
                        if_b[x+5][y] == 2 )
                        B_weight[m][n] += 500000;
                    //111201
                    if( if_b[x][y] == 2 && if_b[x+1][y] == 2 && if_b[x+2][y] == 2 && if_b[x+3][y] == 1 && if_b[x+4][y] == 0 &&
                        if_b[x+5][y] == 2 )
                        B_weight[m][n] += 500000;
                    //111021
                    if( if_b[x][y] == 2 && if_b[x+1][y] == 2 && if_b[x+2][y] == 2 && if_b[x+3][y] == 0 && if_b[x+4][y] == 1 &&
                        if_b[x+5][y] == 2 )
                        B_weight[m][n] += 500000;
                    //112011
                    if( if_b[x][y] == 2 && if_b[x+1][y] == 2 && if_b[x+2][y] == 1 && if_b[x+3][y] == 0 && if_b[x+4][y] == 2 &&
                        if_b[x+5][y] == 2 )
                        B_weight[m][n] += 500000;
                    //110211
                    if( if_b[x][y] == 2 && if_b[x+1][y] == 2 && if_b[x+2][y] == 0 && if_b[x+3][y] == 1 && if_b[x+4][y] == 2 &&
                        if_b[x+5][y] == 2 )
                        B_weight[m][n] += 500000;

                    //여기서부터 간단한 가중치 줄 것. 즉, 2개 3개 막게하는것들
                    //2111
                    if( if_b[x][y] == 1 && if_b[x+1][y] == 2 && if_b[x+2][y] == 2 && if_b[x+3][y] == 2 )
                        B_weight[m][n] += 3500;
                    //1112
                    if( if_b[x][y] == 2 && if_b[x+1][y] == 2 && if_b[x+2][y] == 2 && if_b[x+3][y] == 1 )
                        B_weight[m][n] += 3500;
                    //1211
                    if( if_b[x][y] == 2 && if_b[x+1][y] == 1 && if_b[x+2][y] == 2 && if_b[x+3][y] == 2 )
                        B_weight[m][n] += 4000;
                    //1121
                    if( if_b[x][y] == 2 && if_b[x+1][y] == 2 && if_b[x+2][y] == 1 && if_b[x+3][y] == 2 )
                        B_weight[m][n] += 4000;
                    //11102		분기해서 막는것도 필요한 경우가 있을수있음. 단 점수는 낮게
                    if( if_b[x][y] == 2 && if_b[x+1][y] == 2 && if_b[x+2][y] == 2 && if_b[x+3][y] == 0 && if_b[x+4][y] == 1 )
                        B_weight[m][n] += 1500;
                    //20111
                    if( if_b[x][y] == 1 && if_b[x+1][y] == 0 && if_b[x+2][y] == 2 && if_b[x+3][y] == 2 && if_b[x+4][y] == 2 )
                        B_weight[m][n] += 1500;

                    //21011		점수낮게
                    if( if_b[x][y] == 1 && if_b[x+1][y] == 2 && if_b[x+2][y] == 0 && if_b[x+3][y] == 2 && if_b[x+4][y] == 2 )
                        B_weight[m][n] += 1500;
                    //21101		점수낮게
                    if( if_b[x][y] == 1 && if_b[x+1][y] == 2 && if_b[x+2][y] == 2 && if_b[x+3][y] == 0 && if_b[x+4][y] == 2 )
                        B_weight[m][n] += 1500;
                    //10112		점수낮게
                    if( if_b[x][y] == 2 && if_b[x+1][y] == 0 && if_b[x+2][y] == 2 && if_b[x+3][y] == 2 && if_b[x+4][y] == 1 )
                        B_weight[m][n] += 1500;
                    //11012		점수낮게
                    if( if_b[x][y] == 2 && if_b[x+1][y] == 2 && if_b[x+2][y] == 0 && if_b[x+3][y] == 2 && if_b[x+4][y] == 1 )
                        B_weight[m][n] += 1500;

                    //211
                    if( if_b[x][y] == 1 && if_b[x+1][y] == 2 && if_b[x+2][y] == 2 )
                        B_weight[m][n] += 500;
                    //112
                    if( if_b[x][y] == 2 && if_b[x+1][y] == 2 && if_b[x+2][y] == 1 )
                        B_weight[m][n] += 500;
                    //121
                    if( if_b[x][y] == 2 && if_b[x+1][y] == 1 && if_b[x+2][y] == 2 )
                        B_weight[m][n] += 800;
                }
            }
            if_b[m][n] = 0;
        }
    }

}

void AI::defense_Diagonal_check_B()
{
    for(int m=0 ; m<19 ; m++)
        {
            for(int n=0 ; n<19 ; n++)
            {
                if( if_b[m][n] == 0 )
                {
                    if_b[m][n] = 1;
                }
                else if( if_b[m][n] == 2 || if_b[m][n] == 1 )
                {
                    continue;
                }

                for(int x=0; x<19; x++)
                {
                    for(int y=0; y<19; y++)
                    {
                        //다섯개에 양쪽다 막도록.
                        //2111112 이런상황이 되게 할때 점수가 높이 준다.
                        if( if_b[x][y] == 1 && if_b[x+1][y+1] == 2 && if_b[x+2][y+2] == 2 && if_b[x+3][y+3] == 2 && if_b[x+4][y+4] == 2 &&
                            if_b[x+5][y+5] == 2 && if_b[x+6][y+6] == 1 )
                            B_weight[m][n] += 750000;
                        //2111110
                        if( if_b[x][y] == 1 && if_b[x+1][y+1] == 2 && if_b[x+2][y+2] == 2 && if_b[x+3][y+3] == 2 && if_b[x+4][y+4] == 2 &&
                            if_b[x+5][y+5] == 2 && if_b[x+6][y+6] == 0 )
                            B_weight[m][n] += 500000;
                        //0111112
                        if( if_b[x][y] == 0 && if_b[x+1][y+1] == 2 && if_b[x+2][y+2] == 2 && if_b[x+3][y+3] == 2 && if_b[x+4][y+4] == 2 &&
                            if_b[x+5][y+5] == 2 && if_b[x+6][y+6] == 1 )
                            B_weight[m][n] += 500000;
                        //121111
                        if( if_b[x][y] == 2 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 2 && if_b[x+3][y+3] == 2 && if_b[x+4][y+4] == 2 &&
                            if_b[x+5][y+5] == 2 )
                            B_weight[m][n] += 500000;
                        //112111
                        if( if_b[x][y] == 2 && if_b[x+1][y+1] == 2 && if_b[x+2][y+2] == 1 && if_b[x+3][y+3] == 2 && if_b[x+4][y+4] == 2 &&
                            if_b[x+5][y+5] == 2 )
                            B_weight[m][n] += 500000;
                        //111211
                        if( if_b[x][y] == 2 && if_b[x+1][y+1] == 2 && if_b[x+2][y+2] == 2 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] == 2 &&
                            if_b[x+5][y+5] == 2 )
                            B_weight[m][n] += 500000;
                        //111121
                        if( if_b[x][y] == 2 && if_b[x+1][y+1] == 2 && if_b[x+2][y+2] == 2 && if_b[x+3][y+3] == 2 && if_b[x+4][y+4] == 1 &&
                            if_b[x+5][y+5] == 2 )
                            B_weight[m][n] += 500000;


                        //추가부분 상대방 4개짜리 사이 빈칸있을때 사이 막기
                        //202122
                        if( if_b[x][y] == 2 && if_b[x+1][y+1] == 0 && if_b[x+2][y+2] == 2 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] == 2 &&
                            if_b[x+5][y+5] == 2 )
                            B_weight[m][n] += 500000;
                        //202212
                        if( if_b[x][y] == 2 && if_b[x+1][y+1] == 0 && if_b[x+2][y+2] == 2 && if_b[x+3][y+3] == 2 && if_b[x+4][y+4] == 1 &&
                            if_b[x+5][y+5] == 2 )
                            B_weight[m][n] += 500000;
                        //212022
                        if( if_b[x][y] == 2 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 2 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] == 2 &&
                            if_b[x+5][y+5] == 2 )
                            B_weight[m][n] += 500000;
                        //212202
                        if( if_b[x][y] == 2 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 2 && if_b[x+3][y+3] == 2 && if_b[x+4][y+4] == 0 &&
                            if_b[x+5][y+5] == 2 )
                            B_weight[m][n] += 500000;
                        //221202
                        if( if_b[x][y] == 2 && if_b[x+1][y+1] == 2 && if_b[x+2][y+2] == 1 && if_b[x+3][y+3] == 2 && if_b[x+4][y+4] == 0 &&
                            if_b[x+5][y+5] == 2 )
                            B_weight[m][n] += 500000;
                        //220212
                        if( if_b[x][y] == 2 && if_b[x+1][y+1] == 2 && if_b[x+2][y+2] == 0 && if_b[x+3][y+3] == 2 && if_b[x+4][y+4] == 1 &&
                            if_b[x+5][y+5] == 2 )
                            B_weight[m][n] += 500000;


                        //211112
                        if( if_b[x][y] == 1 && if_b[x+1][y+1] == 2 && if_b[x+2][y+2] == 2 && if_b[x+3][y+3] == 2 && if_b[x+4][y+4] == 2 &&
                            if_b[x+5][y+5] == 1 )
                            B_weight[m][n] += 500000;
                        //211110
                        if( if_b[x][y] == 1 && if_b[x+1][y+1] == 2 && if_b[x+2][y+2] == 2 && if_b[x+3][y+3] == 2 && if_b[x+4][y+4] == 2 &&
                            if_b[x+5][y+5] == 0 )
                            B_weight[m][n] += 500000;
                        //011112
                        if( if_b[x][y] == 0 && if_b[x+1][y+1] == 2 && if_b[x+2][y+2] == 2 && if_b[x+3][y+3] == 2 && if_b[x+4][y+4] == 2 &&
                            if_b[x+5][y+5] == 1)
                            B_weight[m][n] += 500000;
                        //2111102
                        if( if_b[x][y] == 1 && if_b[x+1][y+1] == 2 && if_b[x+2][y+2] == 2 && if_b[x+3][y+3] == 2 && if_b[x+4][y+4] == 2 &&
                            if_b[x+5][y+5] == 0 && if_b[x+6][y+6] == 1 )
                            B_weight[m][n] += 500000;
                        //2011112
                        if( if_b[x][y] == 1 && if_b[x+1][y+1] == 0 && if_b[x+2][y+2] == 2 && if_b[x+3][y+3] == 2 && if_b[x+4][y+4] == 2 &&
                            if_b[x+5][y+5] == 2 && if_b[x+6][y+6] == 1 )
                            B_weight[m][n] += 500000;

                        //x12111x
                        if( if_b[x+1][y+1] == 2 && if_b[x+2][y+2] == 1 && if_b[x+3][y+3] == 2 && if_b[x+4][y+4] == 2 &&
                            if_b[x+5][y+5] == 2 && if_b[x+6][y+6] != 1 )
                            B_weight[m][n] += 500000;
                        //x11211x
                        if( if_b[x+1][y+1] == 2 && if_b[x+2][y+2] == 2 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] == 2 &&
                            if_b[x+5][y+5] == 2 && if_b[x+6][y+6] != 1 )
                            B_weight[m][n] += 500000;
                        //x11121x
                        if( if_b[x+1][y+1] == 2 && if_b[x+2][y+2] == 2 && if_b[x+3][y+3] == 2 && if_b[x+4][y+4] == 1 &&
                            if_b[x+5][y+5] == 2 && if_b[x+6][y+6] != 1 )
                            B_weight[m][n] += 500000;
                        //x12111x
                        if( if_b[x][y] != 1 && if_b[x+1][y+1] == 2 && if_b[x+2][y+2] == 1 && if_b[x+3][y+3] == 2 && if_b[x+4][y+4] == 2 &&
                            if_b[x+5][y+5] == 2 )
                            B_weight[m][n] += 500000;
                        //x11211x
                        if( if_b[x][y] != 1 && if_b[x+1][y+1] == 2 && if_b[x+2][y+2] == 2 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] == 2 &&
                            if_b[x+5][y+5] == 2 )
                            B_weight[m][n] += 500000;
                        //x11121x
                        if( if_b[x][y] != 1 && if_b[x+1][y+1] == 2 && if_b[x+2][y+2] == 2 && if_b[x+3][y+3] == 2 && if_b[x+4][y+4] == 1 &&
                            if_b[x+5][y+5] == 2 )
                            B_weight[m][n] += 500000;

                        //120111
                        if( if_b[x][y] == 2 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 0 && if_b[x+3][y+3] == 2 && if_b[x+4][y+4] == 2 &&
                            if_b[x+5][y+5] == 2 )
                            B_weight[m][n] += 500000;
                        //102111
                        if( if_b[x][y] == 2 && if_b[x+1][y+1] == 0 && if_b[x+2][y+2] == 1 && if_b[x+3][y+3] == 2 && if_b[x+4][y+4] == 2 &&
                            if_b[x+5][y+5] == 2 )
                            B_weight[m][n] += 500000;
                        //111201
                        if( if_b[x][y] == 2 && if_b[x+1][y+1] == 2 && if_b[x+2][y+2] == 2 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] == 0 &&
                            if_b[x+5][y+5] == 2 )
                            B_weight[m][n] += 500000;
                        //111021
                        if( if_b[x][y] == 2 && if_b[x+1][y+1] == 2 && if_b[x+2][y+2] == 2 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] == 1 &&
                            if_b[x+5][y+5] == 2 )
                            B_weight[m][n] += 500000;
                        //112011
                        if( if_b[x][y] == 2 && if_b[x+1][y+1] == 2 && if_b[x+2][y+2] == 1 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] == 2 &&
                            if_b[x+5][y+5] == 2 )
                            B_weight[m][n] += 500000;
                        //110211
                        if( if_b[x][y] == 2 && if_b[x+1][y+1] == 2 && if_b[x+2][y+2] == 0 && if_b[x+3][y+3] == 1 && if_b[x+4][y+4] == 2 &&
                            if_b[x+5][y+5] == 2 )
                            B_weight[m][n] += 500000;

                        //여기서부터 간단한 가중치 줄 것. 즉, 2개 3개 막게하는것들
                        //2111
                        if( if_b[x][y] == 1 && if_b[x+1][y+1] == 2 && if_b[x+2][y+2] == 2 && if_b[x+3][y+3] == 2 )
                            B_weight[m][n] += 3500;
                        //1112
                        if( if_b[x][y] == 2 && if_b[x+1][y+1] == 2 && if_b[x+2][y+2] == 2 && if_b[x+3][y+3] == 1 )
                            B_weight[m][n] += 3500;
                        //1211
                        if( if_b[x][y] == 2 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 2 && if_b[x+3][y+3] == 2 )
                            B_weight[m][n] += 4000;
                        //1121
                        if( if_b[x][y] == 2 && if_b[x+1][y+1] == 2 && if_b[x+2][y+2] == 1 && if_b[x+3][y+3] == 2 )
                            B_weight[m][n] += 4000;
                        //11102		분기해서 막는것도 필요한 경우가 있을수있음. 단 점수는 낮게
                        if( if_b[x][y] == 2 && if_b[x+1][y+1] == 2 && if_b[x+2][y+2] == 2 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] == 1 )
                            B_weight[m][n] += 1500;
                        //20111
                        if( if_b[x][y] == 1 && if_b[x+1][y+1] == 0 && if_b[x+2][y+2] == 2 && if_b[x+3][y+3] == 2 && if_b[x+4][y+4] == 2 )
                            B_weight[m][n] += 1500;

                        //21011		점수낮게
                        if( if_b[x][y] == 1 && if_b[x+1][y+1] == 2 && if_b[x+2][y+2] == 0 && if_b[x+3][y+3] == 2 && if_b[x+4][y+4] == 2 )
                            B_weight[m][n] += 1500;
                        //21101		점수낮게
                        if( if_b[x][y] == 1 && if_b[x+1][y+1] == 2 && if_b[x+2][y+2] == 2 && if_b[x+3][y+3] == 0 && if_b[x+4][y+4] == 2 )
                            B_weight[m][n] += 1500;
                        //10112		점수낮게
                        if( if_b[x][y] == 2 && if_b[x+1][y+1] == 0 && if_b[x+2][y+2] == 2 && if_b[x+3][y+3] == 2 && if_b[x+4][y+4] == 1 )
                            B_weight[m][n] += 1500;
                        //11012		점수낮게
                        if( if_b[x][y] == 2 && if_b[x+1][y+1] == 2 && if_b[x+2][y+2] == 0 && if_b[x+3][y+3] == 2 && if_b[x+4][y+4] == 1 )
                            B_weight[m][n] += 1500;

                        //211
                        if( if_b[x][y] == 1 && if_b[x+1][y+1] == 2 && if_b[x+2][y+2] == 2 )
                            B_weight[m][n] += 500;
                        //112
                        if( if_b[x][y] == 2 && if_b[x+1][y+1] == 2 && if_b[x+2][y+2] == 1 )
                            B_weight[m][n] += 500;
                        //121
                        if( if_b[x][y] == 2 && if_b[x+1][y+1] == 1 && if_b[x+2][y+2] == 2 )
                            B_weight[m][n] += 800;
                    }
                }
                if_b[m][n] = 0;
            }
        }

}

void AI::defense_in_Diagonal_check_B()
{
    for(int m=0 ; m<19 ; m++)
    {
        for(int n=0 ; n<19 ; n++)
        {
            if( if_b[m][n] == 0 )
            {
                if_b[m][n] = 1;
            }
            else if( if_b[m][n] == 2 || if_b[m][n] == 1 )
            {
                continue;
            }

            for(int x=0; x<19; x++)
            {
                for(int y=0; y<19; y++)
                {
                    //다섯개에 양쪽다 막도록.
                    //2111112 이런상황이 되게 할때 점수가 높이 준다.
                    if( if_b[x][y] == 1 && if_b[x+1][y-1] == 2 && if_b[x+2][y-2] == 2 && if_b[x+3][y-3] == 2 && if_b[x+4][y-4] == 2 &&
                        if_b[x+5][y-5] == 2 && if_b[x+6][y-6] == 1 )
                        B_weight[m][n] += 750000;
                    //2111110
                    if( if_b[x][y] == 1 && if_b[x+1][y-1] == 2 && if_b[x+2][y-2] == 2 && if_b[x+3][y-3] == 2 && if_b[x+4][y-4] == 2 &&
                        if_b[x+5][y-5] == 2 && if_b[x+6][y-6] == 0 )
                        B_weight[m][n] += 500000;
                    //0111112
                    if( if_b[x][y] == 0 && if_b[x+1][y-1] == 2 && if_b[x+2][y-2] == 2 && if_b[x+3][y-3] == 2 && if_b[x+4][y-4] == 2 &&
                        if_b[x+5][y-5] == 2 && if_b[x+6][y-6] == 1 )
                        B_weight[m][n] += 500000;
                    //121111
                    if( if_b[x][y] == 2 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 2 && if_b[x+3][y-3] == 2 && if_b[x+4][y-4] == 2 &&
                        if_b[x+5][y-5] == 2 )
                        B_weight[m][n] += 500000;
                    //112111
                    if( if_b[x][y] == 2 && if_b[x+1][y-1] == 2 && if_b[x+2][y-2] == 1 && if_b[x+3][y-3] == 2 && if_b[x+4][y-4] == 2 &&
                        if_b[x+5][y-5] == 2 )
                        B_weight[m][n] += 500000;
                    //111211
                    if( if_b[x][y] == 2 && if_b[x+1][y-1] == 2 && if_b[x+2][y-2] == 2 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] == 2 &&
                        if_b[x+5][y-5] == 2 )
                        B_weight[m][n] += 500000;
                    //111121
                    if( if_b[x][y] == 2 && if_b[x+1][y-1] == 2 && if_b[x+2][y-2] == 2 && if_b[x+3][y-3] == 2 && if_b[x+4][y-4] == 1 &&
                        if_b[x+5][y-5] == 2 )
                        B_weight[m][n] += 500000;


                    //추가부분 상대방 4개짜리 사이 빈칸있을때 사이 막기
                    //202122
                    if( if_b[x][y] == 2 && if_b[x+1][y-1] == 0 && if_b[x+2][y-2] == 2 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] == 2 &&
                        if_b[x+5][y-5] == 2 )
                        B_weight[m][n] += 500000;
                    //202212
                    if( if_b[x][y] == 2 && if_b[x+1][y-1] == 0 && if_b[x+2][y-2] == 2 && if_b[x+3][y-3] == 2 && if_b[x+4][y-4] == 1 &&
                        if_b[x+5][y-5] == 2 )
                        B_weight[m][n] += 500000;
                    //212022
                    if( if_b[x][y] == 2 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 2 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] == 2 &&
                        if_b[x+5][y-5] == 2 )
                        B_weight[m][n] += 500000;
                    //212202
                    if( if_b[x][y] == 2 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 2 && if_b[x+3][y-3] == 2 && if_b[x+4][y-4] == 0 &&
                        if_b[x+5][y-5] == 2 )
                        B_weight[m][n] += 500000;
                    //221202
                    if( if_b[x][y] == 2 && if_b[x+1][y-1] == 2 && if_b[x+2][y-2] == 1 && if_b[x+3][y-3] == 2 && if_b[x+4][y-4] == 0 &&
                        if_b[x+5][y-5] == 2 )
                        B_weight[m][n] += 500000;
                    //220212
                    if( if_b[x][y] == 2 && if_b[x+1][y-1] == 2 && if_b[x+2][y-2] == 0 && if_b[x+3][y-3] == 2 && if_b[x+4][y-4] == 1 &&
                        if_b[x+5][y-5] == 2 )
                        B_weight[m][n] += 500000;

                    //211112
                    if( if_b[x][y] == 1 && if_b[x+1][y-1] == 2 && if_b[x+2][y-2] == 2 && if_b[x+3][y-3] == 2 && if_b[x+4][y-4] == 2 &&
                        if_b[x+5][y-5] == 1 )
                        B_weight[m][n] += 500000;
                    //211110
                    if( if_b[x][y] == 1 && if_b[x+1][y-1] == 2 && if_b[x+2][y-2] == 2 && if_b[x+3][y-3] == 2 && if_b[x+4][y-4] == 2 &&
                        if_b[x+5][y-5] == 0 )
                        B_weight[m][n] += 500000;
                    //011112
                    if( if_b[x][y] == 0 && if_b[x+1][y-1] == 2 && if_b[x+2][y-2] == 2 && if_b[x+3][y-3] == 2 && if_b[x+4][y-4] == 2 &&
                        if_b[x+5][y-5] == 1)
                        B_weight[m][n] += 500000;
                    //2111102
                    if( if_b[x][y] == 1 && if_b[x+1][y-1] == 2 && if_b[x+2][y-2] == 2 && if_b[x+3][y-3] == 2 && if_b[x+4][y-4] == 2 &&
                        if_b[x+5][y-5] == 0 && if_b[x+6][y-6] == 1 )
                        B_weight[m][n] += 500000;
                    //2011112
                    if( if_b[x][y] == 1 && if_b[x+1][y-1] == 0 && if_b[x+2][y-2] == 2 && if_b[x+3][y-3] == 2 && if_b[x+4][y-4] == 2 &&
                        if_b[x+5][y-5] == 2 && if_b[x+6][y-6] == 1 )
                        B_weight[m][n] += 500000;

                    //x12111x
                    if( if_b[x+1][y-1] == 2 && if_b[x+2][y-2] == 1 && if_b[x+3][y-3] == 2 && if_b[x+4][y-4] == 2 &&
                        if_b[x+5][y-5] == 2 && if_b[x+6][y-6] != 1 )
                        B_weight[m][n] += 500000;
                    //x11211x
                    if( if_b[x+1][y-1] == 2 && if_b[x+2][y-2] == 2 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] == 2 &&
                        if_b[x+5][y-5] == 2 && if_b[x+6][y-6] != 1 )
                        B_weight[m][n] += 500000;
                    //x11121x
                    if( if_b[x+1][y-1] == 2 && if_b[x+2][y-2] == 2 && if_b[x+3][y-3] == 2 && if_b[x+4][y-4] == 1 &&
                        if_b[x+5][y-5] == 2 && if_b[x+6][y-6] != 1 )
                        B_weight[m][n] += 500000;
                    //x12111x
                    if( if_b[x][y] != 1 && if_b[x+1][y-1] == 2 && if_b[x+2][y-2] == 1 && if_b[x+3][y-3] == 2 && if_b[x+4][y-4] == 2 &&
                        if_b[x+5][y-5] == 2 )
                        B_weight[m][n] += 500000;
                    //x11211x
                    if( if_b[x][y] != 1 && if_b[x+1][y-1] == 2 && if_b[x+2][y-2] == 2 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] == 2 &&
                        if_b[x+5][y-5] == 2 )
                        B_weight[m][n] += 500000;
                    //x11121x
                    if( if_b[x][y] != 1 && if_b[x+1][y-1] == 2 && if_b[x+2][y-2] == 2 && if_b[x+3][y-3] == 2 && if_b[x+4][y-4] == 1 &&
                        if_b[x+5][y-5] == 2 )
                        B_weight[m][n] += 500000;

                    //120111
                    if( if_b[x][y] == 2 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 0 && if_b[x+3][y-3] == 2 && if_b[x+4][y-4] == 2 &&
                        if_b[x+5][y-5] == 2 )
                        B_weight[m][n] += 500000;
                    //102111
                    if( if_b[x][y] == 2 && if_b[x+1][y-1] == 0 && if_b[x+2][y-2] == 1 && if_b[x+3][y-3] == 2 && if_b[x+4][y-4] == 2 &&
                        if_b[x+5][y-5] == 2 )
                        B_weight[m][n] += 500000;
                    //111201
                    if( if_b[x][y] == 2 && if_b[x+1][y-1] == 2 && if_b[x+2][y-2] == 2 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] == 0 &&
                        if_b[x+5][y-5] == 2 )
                        B_weight[m][n] += 500000;
                    //111021
                    if( if_b[x][y] == 2 && if_b[x+1][y-1] == 2 && if_b[x+2][y-2] == 2 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] == 1 &&
                        if_b[x+5][y-5] == 2 )
                        B_weight[m][n] += 500000;
                    //112011
                    if( if_b[x][y] == 2 && if_b[x+1][y-1] == 2 && if_b[x+2][y-2] == 1 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] == 2 &&
                        if_b[x+5][y-5] == 2 )
                        B_weight[m][n] += 500000;
                    //110211
                    if( if_b[x][y] == 2 && if_b[x+1][y-1] == 2 && if_b[x+2][y-2] == 0 && if_b[x+3][y-3] == 1 && if_b[x+4][y-4] == 2 &&
                        if_b[x+5][y-5] == 2 )
                        B_weight[m][n] += 500000;

                    //여기서부터 간단한 가중치 줄 것. 즉, 2개 3개 막게하는것들
                    //2111
                    if( if_b[x][y] == 1 && if_b[x+1][y-1] == 2 && if_b[x+2][y-2] == 2 && if_b[x+3][y-3] == 2 )
                        B_weight[m][n] += 3500;
                    //1112
                    if( if_b[x][y] == 2 && if_b[x+1][y-1] == 2 && if_b[x+2][y-2] == 2 && if_b[x+3][y-3] == 1 )
                        B_weight[m][n] += 3500;
                    //1211
                    if( if_b[x][y] == 2 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 2 && if_b[x+3][y-3] == 2 )
                        B_weight[m][n] += 4000;
                    //1121
                    if( if_b[x][y] == 2 && if_b[x+1][y-1] == 2 && if_b[x+2][y-2] == 1 && if_b[x+3][y-3] == 2 )
                        B_weight[m][n] += 4000;
                    //11102		분기해서 막는것도 필요한 경우가 있을수있음. 단 점수는 낮게
                    if( if_b[x][y] == 2 && if_b[x+1][y-1] == 2 && if_b[x+2][y-2] == 2 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] == 1 )
                        B_weight[m][n] += 1500;
                    //20111
                    if( if_b[x][y] == 1 && if_b[x+1][y-1] == 0 && if_b[x+2][y-2] == 2 && if_b[x+3][y-3] == 2 && if_b[x+4][y-4] == 2 )
                        B_weight[m][n] += 1500;

                    //21011		점수낮게
                    if( if_b[x][y] == 1 && if_b[x+1][y-1] == 2 && if_b[x+2][y-2] == 0 && if_b[x+3][y-3] == 2 && if_b[x+4][y-4] == 2 )
                        B_weight[m][n] += 1500;
                    //21101		점수낮게
                    if( if_b[x][y] == 1 && if_b[x+1][y-1] == 2 && if_b[x+2][y-2] == 2 && if_b[x+3][y-3] == 0 && if_b[x+4][y-4] == 2 )
                        B_weight[m][n] += 1500;
                    //10112		점수낮게
                    if( if_b[x][y] == 2 && if_b[x+1][y-1] == 0 && if_b[x+2][y-2] == 2 && if_b[x+3][y-3] == 2 && if_b[x+4][y-4] == 1 )
                        B_weight[m][n] += 1500;
                    //11012		점수낮게
                    if( if_b[x][y] == 2 && if_b[x+1][y-1] == 2 && if_b[x+2][y-2] == 0 && if_b[x+3][y-3] == 2 && if_b[x+4][y-4] == 1 )
                        B_weight[m][n] += 1500;

                    //211
                    if( if_b[x][y] == 1 && if_b[x+1][y-1] == 2 && if_b[x+2][y-2] == 2 )
                        B_weight[m][n] += 500;
                    //112
                    if( if_b[x][y] == 2 && if_b[x+1][y-1] == 2 && if_b[x+2][y-2] == 1 )
                        B_weight[m][n] += 500;
                    //121
                    if( if_b[x][y] == 2 && if_b[x+1][y-1] == 1 && if_b[x+2][y-2] == 2 )
                        B_weight[m][n] += 800;
                }
            }
            if_b[m][n] = 0;
        }
    }

}



void AI::clear (void){

    this->type=TYPE_EMPTY;
    this->setPixmap(*empty);

    for(i=0; i<19; i++)    //모든 바둑판위의 값 0으로 초기화
        {
            for(j=0; j<19; j++)
            {
                this->b[i][j] = 0;
                this->w[i][j] = 0;
            }
        }
        for(i=0; i<19; i++)
        {
            this->b[i][19] = 3;
            this->w[i][19] = 3;
        }


}

