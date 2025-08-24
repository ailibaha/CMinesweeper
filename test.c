#include "game.h"
void menu()
{
    printf("*****扫雷小游戏*****\n");
    printf("******1.play******\n");
    printf("******0.exit******\n");
    printf("******************\n");
}
void game()
{
    //雷的信息存储
    //1.布置好的雷的信息   2.排查的雷的信息
    char mine[ROWS][COLS]={ 0 };
    char show[ROWS][COLS]={ 0 };
    //初始化
    InitBoard(mine,ROWS,COLS,'0');
    InitBoard(show,ROWS,COLS,'*');
    //展示面板
    //DisplayBoard(mine,ROW,COL);
    DisplayBoard(show,ROW,COL);
    //布置雷
    SetMine(mine,ROW,COL);
         //DisplayBoard(mine,ROW,COL);
    //找出雷
    FindMine(mine,show,ROW,COL);
}
void test()
{
    int input =0;
    srand((unsigned )time(NULL));
    do{
        menu();
        printf("请选择:\n");
        scanf("%d",&input);
        switch (input)
        {
            case 1:
                game();
                break;
            case 0:
                printf("退出游戏\n");
                break;
            default:
                printf("选择错误，请重新选择!\n");
                break;
        }

    }while(input);
}
int main()
{
    setup_console_encoding();
    test();
    return 0;
}