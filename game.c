#include "game.h"


void setup_console_encoding() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}



void InitBoard(char board[ROWS][COLS],int rows,int cols,char set)
{
    int i = 0;
    int j = 0;
    for(i=0;i<rows;i++)
    {
        for(j=0;j<cols;j++)
        {
            board[i][j]= set;
        }
    }
}


void DisplayBoard(char board[ROWS][COLS],int row,int col)
{
    int i = 0;
    int j = 1;
    //打印列号
    for(i=0;i<=col;i++)
    {
        printf("%d ",i);
    }
    printf("\n");
    for(i=1;i<=row;i++)
    {   printf("%d ",i);
        for(j=1;j<=col;j++)
        {
            printf("%c ",board[i][j]);
        }
        printf("\n");
    }

}


void SetMine(char board[ROWS][COLS],int row,int col)
{
    int count = EASY_COUNT;
    while(count)
    {
        int x = rand()%row+1;  //雷的x坐标1到9
        int y = rand()%row+1;  //雷的y坐标1到9
        if(board[x][y]=='0')
        {
            board[x][y]= '1';
            count--;
        }
    }
}


void FindMine(char mine[ROWS][COLS],char show[ROWS][COLS],int row,int col)
{
    int x = 0;
    int y = 0;
    int win = 0;
    while(win< row*col - EASY_COUNT)
    {
        printf("请输入排查雷的坐标：\n");
        scanf("%d %d",&x,&y);
        if(x>=1 && x<=row && y>=1 && y<=col)
        {
            //坐标合法
            if(mine[x][y]=='1')
            {
                printf("很遗憾，你被炸死了\n");
                DisplayBoard(mine,row,col);
                break;
            }
            else   //不是雷
            {
                //计算（x，y）坐标周围有几个雷
                int count = get_mine_count(mine, x, y);
                if (count == 0) {
                    ExpandEmptyArea(mine, show, x, y, row, col);
                } else {
                    show[x][y] = count + '0';
                }
                DisplayBoard(show, row, col);
                win++;

            }
        }
        else
        {
            printf("输入的坐标非法，请重新输入！\n");
        }
    }
    if(win == row*col - EASY_COUNT)
    {
        printf("恭喜你，排雷成功\n");
        DisplayBoard(mine,row,col);
    }

}



int get_mine_count(char mine[ROWS][COLS],int x,int y)
{
    return mine[x-1][y] +
    mine[x-1][y-1] +
    mine[x][y-1] +
    mine[x+1][y] +
    mine[x+1][y+1] +
    mine[x][y+1] +
    mine[x-1][y+1] - 8*'0';
}



void ExpandEmptyArea(char mine[ROWS][COLS], char show[ROWS][COLS], int x, int y, int row, int col) {
    // 检查坐标是否越界
    if (x < 1 || x > row || y < 1 || y > col) {
        return;
    }

    // 如果该位置已经展开或者是雷，则返回
    if (show[x][y] != '*' || mine[x][y] == '1') {
        return;
    }

    // 计算周围雷的数量
    int count = get_mine_count(mine, x, y);
    if (count > 0) {
        show[x][y] = count + '0';
        return;
    }

    // 如果是空白区域，递归展开周围8个格子
    show[x][y] = ' ';

    // 递归调用展开周围区域
    ExpandEmptyArea(mine, show, x-1, y-1, row, col);
    ExpandEmptyArea(mine, show, x-1, y, row, col);
    ExpandEmptyArea(mine, show, x-1, y+1, row, col);
    ExpandEmptyArea(mine, show, x, y-1, row, col);
    ExpandEmptyArea(mine, show, x, y+1, row, col);
    ExpandEmptyArea(mine, show, x+1, y-1, row, col);
    ExpandEmptyArea(mine, show, x+1, y, row, col);
    ExpandEmptyArea(mine, show, x+1, y+1, row, col);
}
