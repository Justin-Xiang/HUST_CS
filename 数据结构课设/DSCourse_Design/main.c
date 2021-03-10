#include "define.h"

int main(void)
{
    for(i=0;i<2000;i++)
    {
        nums[i] = 0;
    }
    char filename[200], copy_filename[200];  //cnf文件读取 与结果保存
    char sudo_filename[20]; //数独文件
    int op = 1, SAT = 1, SuDoKu = 1; //用于switch分支
    int flag_cnf = 0; //用于判断cnf文件是否读取成功
    int flag_sudo = 0; //用于判断数独文件是否读取成功
    int way_sudo = 0; //sudo处理方式
    struct Clause * root;

    while(op)
    {

        printf("|--------------------Choose SAT or BinaryPuzzle--------------------|\n");
        printf("|                                                                  |\n");
        printf("|           1.SAT                         2.BinaryPuzzle           |\n");
        printf("|                                                                  |\n");
        printf("|           0.Exit                                                 |\n");
        printf("|                                                                  |\n");
        printf("|                       CopyRight @CS1906 LX                       |\n");
        printf("|                                                                  |\n");
        printf("|------------------------------------------------------------------|\n");
        printf("|                                                                  |\n");
        printf("|                    Make your choice ( 0 - 2 )                    |\n");
        printf("|                                                                  |\n");
        printf("|------------------------------------------------------------------|\n");
        scanf("%d",&op);
        switch(op)
        {
            case 1:
                while(SAT){

                    printf("|-------------------------- Menu For SAT --------------------------|\n");
                    printf("|                                                                  |\n");
                    printf("|            1.Readfile                         2.Savefile         |\n");
                    printf("|                                                                  |\n");
                    printf("|            3.Traversefile                     4.Dpll             |\n");
                    printf("|                                                                  |\n");
                    printf("|            0.Exit                                                |\n");
                    printf("|                                                                  |\n");
                    printf("|                       CopyRight @CS1906 LX                       |\n");
                    printf("|                                                                  |\n");
                    printf("|------------------------------------------------------------------|\n");
                    printf("|                                                                  |\n");
                    printf("|                    Make your choice ( 0 - 4 )                    |\n");
                    printf("|                                                                  |\n");
                    printf("|------------------------------------------------------------------|\n");
                    scanf("%d",&SAT);
                    switch(SAT) {
                        case 1:
                            for(i=0;i<2000;i++)
                            {
                                nums[i] = 0;
                            }
                            printf("请输入读取的cnf文件名:\n");

                            scanf("%s", filename);
                            strcpy(copy_filename, filename);
                            root = Readfile(filename);
                            if (root != NULL) {
                                printf("文件读取成功\n");
                                flag_cnf = 1;
                            } else {
                                printf("文件读取失败！\n");
                            }
                            getchar();
                            printf("请输入c继续：\n");
                            getchar();
                            break;

                        case 2: {
                            if (flag_cnf) {
                                if (Savefile(root)) {
                                    printf("文件保存成功！\n");
                                } else {
                                    printf("文件保存失败！\n");
                                }
                            } else printf("文件还未读取！\n");
                                getchar();
                                printf("请输入c继续：\n");
                                getchar();
                                break;
                        }
                        case 3:
                        {
                            if(flag_cnf) Traversefile(root);
                            else printf("文件还未读取！\n");
                            getchar();
                            printf("请输入c继续：\n");
                            getchar();
                            break;
                        }
                        case 4:
                        {
                            if(flag_cnf)
                            {
                                printf("请选取求解方式:\n");
                                printf("1.优化前  2.优化后\n");
                                scanf("%d",&Way);
                                clock_t start,end;
                                start = clock();

                                if(dpll(root)==OK)
                                {
                                    end = clock();
                                    printf("文件有解!\n");
                                    printf("        \n");
                                    printf("求解时间:%d ms\n",(end-start)*1000/CLOCKS_PER_SEC);
                                    for(i=1;i<=word_number;i++)
                                    {
                                        temp = (variable[i] ==0 ?-1:1)*i;
                                        printf("%d ",temp);
                                        if(i%10==0) putchar('\n');
                                    }
                                    putchar('\n');
                                    writeResult(copy_filename,1,(end-start)*1000/CLOCKS_PER_SEC);
                                }
                                else
                                {
                                    end = clock();
                                    printf("文件无解！\n");
                                    printf("        \n");
                                    printf("求解时间:%d ms\n",(end-start)*1000/CLOCKS_PER_SEC);
                                    putchar('\n');
                                    writeResult(copy_filename,0,(end-start)*1000/CLOCKS_PER_SEC);
                                }
                                flag_cnf = 0;
                                //destroyClauses(root);
                            }
                            else{
                                printf("文件还未读取!\n");
                            }
                            getchar();
                            printf("请输入c继续：\n");
                            getchar();
                            break;
                        }
                        case 0:{
                            break;
                        }
                        default:
                        {
                            printf("输入错误！\n");
                            getchar();
                            printf("请输入c继续：\n");
                            getchar();
                            break;
                        }

                    }
                }
                getchar();
                printf("请输入c继续：\n");
                getchar();
                break;

            case 2:
                while(SuDoKu)
                {
                    //system("cls");

                    printf("|---------------------  Menu For BinaryPuzzle  --------------------|\n");
                    printf("|                                                                  |\n");
                    printf("|        1.ReadSudoKuFile                          2.Play          |\n");
                    printf("|                                                                  |\n");
                    printf("|        3.SetCNFfile                     4.Dpll For Answer Check  |\n");
                    printf("|                                                                  |\n");
                    printf("|        5.Randomly Generate                       0.Exit          |\n");
                    printf("|                                                                  |\n");
                    printf("|                       CopyRight @CS1906 LX                       |\n");
                    printf("|                                                                  |\n");
                    printf("|------------------------------------------------------------------|\n");
                    printf("|                                                                  |\n");
                    printf("|                    Make your choice ( 0 - 4 )                    |\n");
                    printf("|                                                                  |\n");
                    printf("|------------------------------------------------------------------|\n");
                    scanf("%d",&SuDoKu);
                    switch(SuDoKu)
                    {
                        case 1:
                            printf("请输入要读取的数独棋盘文件名:\n");
                            scanf("%s",sudo_filename);
                            Readqipan(sudo_filename);
                            Showqipan(qipan);
                            flag_sudo = 1;
                            getchar();
                            printf("请输入c继续：\n");
                            getchar();
                            break;
                        case 2:
                            if(flag_sudo) PlaySuDoKu(qipan);
                            else printf("数独文件还未读取!\n");
                            getchar();
                            printf("请输入c继续：\n");
                            getchar();
                            break;
                        case 3:
                            if(flag_sudo)
                            {

                                printf("请选择:\n1.直接求解     2.检验Play后的结果！\n");
                                scanf("%d",&way_sudo);
                                if(way_sudo==1)
                                {
                                    Resetqipan(qipan);
                                    SetCNFfile(qipan);
                                }
                                else
                                {
                                    if(Checkqipan(qipan)) SetCNFfile(qipan);
                                    else printf("棋盘还未填充完整,请填充完毕!\n");
                                }
                            }
                            else printf("数独文件还未读取!\n");
                            getchar();
                            printf("请输入c继续：\n");
                            getchar();
                            break;
                        case 4:

                            if(flag_sudo){
                                char filename_sudocopy[15];

                                strcpy(filename_sudocopy,filename_setcnf);
                                struct Clause * root_sudo = Readfile(filename_sudocopy);
                                clock_t t1,t2;
                                t1 = clock();
                                if(dpll(root_sudo) == OK){
                                    t2 = clock();
                                    char file_sudoresult[15];
                                    strcpy(file_sudoresult,filename_sudocopy);
                                    if(way_sudo == 1){
                                        printf("Dpll求解成功！结果为:\n");
                                        for(i = 0 ; i<36; i++)
                                        {
                                            printf("%d ", variable[i+1]);
                                            if((i+1) % 6 == 0) putchar('\n');
                                        }
                                    }
                                    else
                                    {
                                        printf("Dpll求解成功，结果正确!\n");
                                        writeResult(file_sudoresult,1,t2-t1);
                                        //destroyClauses(root_sudo);
                                    }
                                }
                                else printf("Dpll求解失败,结果错误!\n可继续尝试！\n");
                            }
                            else printf("数独文件还未读取！\n");
                            getchar();
                            printf("请输入c继续：\n");
                            getchar();
                            break;

                        case 5: {
                            char *random_filename[]={"StanSudo_1.txt","StanSudo_2.txt","StanSudo_3.txt","StanSudo_4.txt","StanSudo_5.txt"};
                            srand((unsigned)time(NULL));
                            int z =rand()%5;
                            RandGener(random_filename[z]);
                            Showqipan(qipan);
                            flag_sudo = 1;
                            getchar();
                            printf("请输入c继续：\n");
                            getchar();
                            break;
                        }
                        case 0:
                            break;
                        default:
                            printf("输入错误!\n");
                            getchar();
                            printf("请输入c继续：\n");
                            getchar();
                            break;
                    }


                }
            case 0:
                break;
            default:
                printf("输入错误！\n");
                getchar();
                printf("请输入c继续：\n");
                getchar();
                break;
        }
    }
    printf("下次再见！\n");
    return 0;
}
