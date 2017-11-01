#include <stdio.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#define N 20

#ifndef SUCCESSED
#define SUCCESSED 0
#endif

#ifndef FAILED
#define FAILED -1
#endif

#ifndef _CONFIG_FILE_NAME_
#define _CONFIG_FILE_NAME_ "./.BJTUweihai.campus.DST.config"
#endif

#ifndef _CONFIG_FILE_SIZE_
#define _CONFIG_FILE_SIZE_ 100 * 10000	
#endif

#ifndef DEBUG 
#define DEBUG 0 
#endif


typedef struct studentGrades {
    char stuName[20];
    int particiScore;//参加活动的成绩
    int assigScore1;//作业1的成绩
    int assigScore2;//作业2的成绩
    int assigScore3;//作业3的成绩
    int assigScore4;//作业4的成绩
    int courseScore;//课程项目的成绩
    int finalExamScore;//期末考试成绩
    int finalGrade;//总成绩
    
    int standardScore;	//debug
    int normaScore;	//debug
}STU;


//=================================================================================
void showScoreList(STU *scoreList, unsigned int studentCount, char flag_sortStuScore);
void findStudent(STU *scoreList, unsigned int studentCount, char *stuName);
void deleteStudent(STU *scoreList, unsigned int *studentcount, char *stuName);
void sortStuScore(STU *scoreList, unsigned int studentcount, char *flag_sortStuScore);
void show_mindata(STU * scoreList, unsigned int studentcount);
void show_maxdata(STU * scoreList, unsigned int studentcount);
void distribution(STU * scoreList, unsigned int studentcount);
char exitSystem(STU *scoreList, unsigned int studentCount);
char readConfig(STU *scoreList, unsigned int *studentCount);
char writeConfig(STU *scoreList, unsigned int studentCount);
void normalize(STU *scorelist,unsigned int *studentcount);


int main(int argc, const char * argv[])
{
	// insert code here...
	int studentCount = 10;
	int n = 0;
	int i = 0;
	STU stu[10000];	//最多管理10000人
	STU stuSort[100];
	char stuName[20];
	char flag_sortStuScore = 0;	//是否有做排名处理
	char ret = SUCCESSED;

	
	#if DEBUG
	studentCount = 4;
	
	char name0[20] = "张三";
	char name1[20] = "李四";
	char name2[20] = "王五";
	char name3[20] = "赵六";

	i = 0;
	memcpy(stu[0].stuName, name0,   sizeof(name0));
	stu[i].particiScore = 1; 
	stu[i].assigScore1 = 2;
	stu[i].assigScore2 = 3;
	stu[i].assigScore3 = 4;
	stu[i].assigScore4 = 5;
	stu[i].courseScore = 6;
	stu[i].finalExamScore = 7;
	stu[i].finalGrade = 
		((stu[i].particiScore)
		+ (stu[i].assigScore1)
		+ (stu[i].assigScore2)
		+ (stu[i].assigScore3)
		+ (stu[i].assigScore4)
		+ (stu[i].courseScore)
		+ (stu[i].finalExamScore)
		);

	i = 1;
	memcpy(stu[1].stuName, name1,   sizeof(name1));
	stu[i].particiScore = 8; 
	stu[i].assigScore1 = 8;
	stu[i].assigScore2 = 8;
	stu[i].assigScore3 = 8;
	stu[i].assigScore4 = 8;
	stu[i].courseScore = 8;
	stu[i].finalExamScore = 8;
	stu[i].finalGrade = 
		((stu[i].particiScore)
		+ (stu[i].assigScore1)
		+ (stu[i].assigScore2) 
		+ (stu[i].assigScore3)
		+ (stu[i].assigScore4)
		+ (stu[i].courseScore)
		+ (stu[i].finalExamScor)
		);

	i = 2;
	memcpy(stu[2].stuName, name2,   sizeof(name2));
	stu[i].particiScore = 1; 
	stu[i].assigScore1 = 2;
	stu[i].assigScore2 = 3;
	stu[i].assigScore3 = 4;
	stu[i].assigScore4 = 5;
	stu[i].courseScore = 6;
	stu[i].finalExamScore = 7;
	stu[i].finalGrade = 
		((stu[i].particiScore   )
		+ (stu[i].assigScore1   )
		+ (stu[i].assigScore2   )
		+ (stu[i].assigScore3   )
		+ (stu[i].assigScore4   )
		+ (stu[i].courseScore   )
		+ (stu[i].finalExamScore   )
		);

		
	i = 3;
	memcpy(stu[3].stuName, name3,   sizeof(name3));
	stu[i].particiScore = 1; 
	stu[i].assigScore1 = 2;
	stu[i].assigScore2 = 3;
	stu[i].assigScore3 = 4;
	stu[i].assigScore4 = 5;
	stu[i].courseScore = 6;
	stu[i].finalExamScore = 7;
	stu[i].finalGrade = 
		((stu[i].particiScore )
		+ (stu[i].assigScore1 )
		+ (stu[i].assigScore2 )
		+ (stu[i].assigScore3   )
		+ (stu[i].assigScore4   )
		+ (stu[i].courseScore   )
		+ (stu[i].finalExamScore   )
		);
		printf("stu[%d].finalGrade is %d\n", i, stu[i].finalGrade);
	#else	
	ret = readConfig(stu, &studentCount);
	if (SUCCESSED != ret)
	{
		printf("Please input the number of students:");
		scanf("%d", &studentCount);
		printf("student count number is %d\n\n", studentCount);

	
		printf("Please input the data as :name particiScore assigScore1 assigScore2 assigScore3  assigScore4 courseScore finalExamScore\n");
		for (i = 0; i < studentCount; ++i)
		{
			//printf("111\n");
			scanf("%s %d %d %d %d %d %d %d",
				stu[i].stuName,
				&stu[i].particiScore, 
				&stu[i].assigScore1,
				&stu[i].assigScore2,
				&stu[i].assigScore3,
				&stu[i].assigScore4,
				&stu[i].courseScore,
				&stu[i].finalExamScore);
			//printf("222\n");
			//sleep(3);
			/*printf("%s %d %d %d %d %d %d %d\n",
				stu[i].stuName,
				stu[i].particiScore,
				stu[i].assigScore1,
				stu[i].assigScore2,
				stu[i].assigScore3,
				stu[i].assigScore4,
				stu[i].courseScore,
				stu[i].finalExamScore);*/
	
			//乘权重 	
			stu[i].finalGrade = 
				stu[i].particiScore
				+ stu[i].assigScore1 
				+ stu[i].assigScore2 
				+ stu[i].assigScore3	
				+ stu[i].assigScore4
				+ stu[i].courseScore
				+ stu[i].finalExamScore;
			printf("stu[%d].finalGrade is %d\n", i, stu[i].finalGrade);
		}
	}	
	else
	{
		printf("read config successed!\n");
		//printf("studentCount = %d\n", studentCount);
	}
	#endif

	//sortStuScore(stu, studentCount, &flag_sortStuScore);
	//flag_sortStuScore = 1;

	while(1)
	{	
		//getchar();
		//printf("\033[2J") ; 
		printf("\n\n---------------------------成绩单展示------------------------------\n");
		printf("选择序号，查看你想查看的内容:\n");
		printf("1.查看成绩单\n");
		printf("2.查找指定学生\n");
		printf("3.删除学生资料\n");
		printf("4.对成绩单排名\n");
		printf("5.显示最低分学生的数据\n");
		printf("6.显示最高分学生的数据\n");
		printf("7.区域分布显示\n");
		printf("8.将学生成绩正态分布化\n");
		printf("0.离开系统\n");
		printf("请输入序号：");
		
		scanf("%d",&n);	//scanf会在处理字母字符串时导致程序出错
		getchar();
		//n = getchar();
		//printf("getchar n = %c\n", n);

		switch (n) 
		{
			case 1:
			{
				printf("\033[2J") ; 
				printf("\n1.查看成绩单\n");				
				showScoreList(stu, studentCount, flag_sortStuScore);//展示成绩单
				break;
			}
			
			case 2:
			{
				printf("\033[2J") ; 
				printf("\n2.查找指定学生\n");
				printf("请输入您想要查找的学生姓名:");
				scanf("%s",stuName);
				printf("您想要查找的学生姓名是%s\n", stuName);
				findStudent(stu, studentCount, stuName);//查找指定学生
				break;
			}
			
			case 3:
			{
				printf("\033[2J") ; 
				printf("\n3.删除学生资料\n");
				printf("请输入您想要删除的学生姓名（学生无重名）:");
				scanf("%s", stuName);
				printf("您想要删除的学生姓名是 %s :\n", stuName);
				deleteStudent(stu, &studentCount, stuName);
				break;
			}

			case 4:
			{
				printf("\033[2J") ; 
				printf("\n4.对成绩单排名\n");
				sortStuScore(stu, studentCount, &flag_sortStuScore);
				//printf("flag_sortStuScore = %d\n", flag_sortStuScore);
				showScoreList(stu, studentCount, flag_sortStuScore);//展示成绩单
				break;
			}

			case 5:
			{
				printf("\033[2J") ; 
				printf("\n5.显示最低分学生的数据\n");
				//printf("flag_sortStuScore = %d\n", flag_sortStuScore);
				if (1 != flag_sortStuScore)
				{
					sortStuScore(stu, studentCount, &flag_sortStuScore);
				}
				show_mindata(stu, studentCount);
				break;
			}

			case 6:
			{
				printf("\033[2J") ; 
				printf("\n6.显示最高分学生的数据\n");
				//printf("flag_sortStuScore = %d\n", flag_sortStuScore);
				if (1 != flag_sortStuScore)
				{
					sortStuScore(stu, studentCount, &flag_sortStuScore);
				}
				show_maxdata(stu, studentCount);
				break;
			}

			case 7:
			{
				printf("\033[2J") ; 
				printf("\n7.区域分布\n");
				distribution(stu, studentCount);
				break;
			}

			case 8:
			{
				printf("\033[2J") ; 
				printf("\n8.将学生成绩正态分布化\n");
				normalize(stu, &studentCount);
				break;
			}
			

			case 0:
			{
				printf("\033[2J") ; 
				printf("\n0.ready exit system!\n");
				exitSystem(stu, studentCount);
				return FAILED;
			}

			default:
			{
				//printf("\033[2J") ; 
				printf("\n错误输入，请重新输入！\n");
				printf("n = %d\n", n);
				//sleep(3);
				break;
			}
		}
	}
}


//ready exit system
char exitSystem(STU *scoreList, unsigned int studentCount)
{
	writeConfig(scoreList, studentCount);
	//readConfig(scoreList, &studentCount);
}


//查看成绩单
void showScoreList(STU *scoreList, unsigned int studentCount, char flag_sortStuScore)
{
	unsigned grade = 1;
	int i = 0;
	printf("studentCount = %d\n", studentCount);

	if (1 == flag_sortStuScore)
	{
		printf ("名次\t姓名\t参加活动成绩\t作业1成绩\t作业2成绩\t作业3成绩\t作业4成绩\t课程项目成绩\t期末考试成绩\t总成绩\n");
		for (i = 0; i < studentCount; i++)
		{
			//printf("%d\t %s\t %.2f\t %.2f\t %.2f\t %.2f\t %.2f\t %.2f\t %.2f\t %.2f\n",grade++,scoreList[i].stuName,scoreList[i].particiScore,scoreList[i].assigScore1,scoreList[i].assigScore2,scoreList[i].assigScore3,scoreList[i].assigScore4,scoreList[i].courseScore,scoreList[i].finalExamScore,scoreList[i].finalGrade);
			printf("%d\t %s\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\n",
				(char)grade++,
				scoreList[i].stuName,
				(char)scoreList[i].particiScore,
				(char)scoreList[i].assigScore1,
				(char)scoreList[i].assigScore2,
				(char)scoreList[i].assigScore3,
				(char)scoreList[i].assigScore4,
				(char)scoreList[i].courseScore,
				(char)scoreList[i].finalExamScore,
				(char)scoreList[i].finalGrade);
		}
	}
	else
	{
		printf ("姓名\t参加活动成绩\t作业1成绩\t作业2成绩\t作业3成绩\t作业4成绩\t课程项目成绩\t期末考试成绩\t总成绩\n");

		for (i = 0; i < studentCount; i++)
		{
			//printf("%s\t %.2f\t %.2f\t %.2f\t %.2f\t %.2f\t %.2f\t %.2f\t %.2f\n",scoreList[i].stuName,scoreList[i].particiScore,scoreList[i].assigScore1,scoreList[i].assigScore2,scoreList[i].assigScore3,scoreList[i].assigScore4,scoreList[i].courseScore,scoreList[i].finalExamScore,scoreList[i].finalGrade);
			printf("%s\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\n",
				scoreList[i].stuName,
				(char)scoreList[i].particiScore,
				(char)scoreList[i].assigScore1,
				(char)scoreList[i].assigScore2,
				(char)scoreList[i].assigScore3,
				(char)scoreList[i].assigScore4,
				(char)scoreList[i].courseScore,
				(char)scoreList[i].finalExamScore,
				(char)scoreList[i].finalGrade);
		}
	}

	return;
}


//查找指定学生
void findStudent(STU *scoreList, unsigned int studentCount, char *stuName)
{
	char ret = 0;
	int i = 0;
	
    for (i = 0;i < studentCount; ++i)
	{
		ret = strcmp(scoreList[i].stuName, stuName);
        if (0 == ret)
		{
            printf("We find the student %s\n",stuName);
            printf ("姓名\t参加活动成绩\t作业1成绩\t作业2成绩\t作业3成绩\t作业4成绩\t课程项目成绩\t期末考试成绩\t总成绩\n");
            //printf("%s\t %.2f\t %.2f\t %.2f\t %.2f\t %.2f\t %.2f\t %.2f\t %.2f\n",scoreList[i].stuName,scoreList[i].particiScore,scoreList[i].assigScore1,scoreList[i].assigScore2,scoreList[i].assigScore3,scoreList[i].assigScore4,scoreList[i].courseScore,scoreList[i].finalExamScore,scoreList[i].finalGrade);
			printf("%s\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\n",
				scoreList[i].stuName,
				(char)scoreList[i].particiScore,
				(char)scoreList[i].assigScore1,
				(char)scoreList[i].assigScore2,
				(char)scoreList[i].assigScore3,
				(char)scoreList[i].assigScore4,
				(char)scoreList[i].courseScore,
				(char)scoreList[i].finalExamScore,
				(char)scoreList[i].finalGrade);	
			return;
        }
    }

	printf("Error: we can not find %s\n", stuName);
	return;
}


//删除指定学生
void deleteStudent(STU *scoreList, unsigned int *studentcount, char *stuName)
{
	int j = 0;
	char ret = 0;
    int flag = 0;
	char name_temp[20];
	char flag_copy = 0;
	char flag_find = 0;

	//printf("studentcount = %d\n", *studentcount);
	
    for (j = 0; j < *studentcount; j++)
	{
		//printf("flag_copy = %d, flag_find = %d\n", flag_copy, flag_find);
		
		if (1 != flag_copy)
		{
			//printf("scoreList[j].stuName = %s, stuName = %s\n", scoreList[j].stuName, stuName);
			ret = strcmp(scoreList[j].stuName, stuName);
		}
		else
		{
			ret = -1;

			//printf("j = %d, *studentcount = %d\n", j, *studentcount);

			if (j < *studentcount - 1)
			{
				//printf("scoreList[j].stuName = %s, scoreList[j + 1].stuName = %s\n", scoreList[j].stuName, scoreList[j + 1].stuName);
				memcpy(scoreList[j].stuName, scoreList[j + 1].stuName, sizeof(scoreList[j + 1].stuName));
				//printf("scoreList[j].stuName = %s\n", scoreList[j].stuName);
			
				scoreList[j].particiScore = scoreList[j + 1].particiScore;
				scoreList[j].assigScore1 = scoreList[j + 1].assigScore1;
				scoreList[j].assigScore2 = scoreList[j + 1].assigScore2;
				scoreList[j].assigScore3 = scoreList[j + 1].assigScore3;
				scoreList[j].assigScore4 = scoreList[j + 1].assigScore4;
				scoreList[j].courseScore = scoreList[j + 1].courseScore;
				scoreList[j].finalExamScore = scoreList[j + 1].finalExamScore;
				scoreList[j].finalGrade = scoreList[j + 1].finalGrade;
			}
		}
		
        if (0 == ret)
		{
            printf("We will delete   %s\n",stuName);
			flag_find = 1;

			if (j == (*studentcount - 1))
			{
				*studentcount = *studentcount - 1;
				memset(scoreList[j].stuName, 0, sizeof(char));
				scoreList[j].particiScore = 255;
				scoreList[j].assigScore1 = 255;
				scoreList[j].assigScore2 = 255;
				scoreList[j].assigScore3 = 255;
				scoreList[j].assigScore4 = 255;
				scoreList[j].courseScore = 255;
				scoreList[j].finalExamScore = 255;
				scoreList[j].finalGrade = 255;

				return;
			}
			else
			{
				flag_copy = 1;

				if (j < *studentcount - 1)
				{
					//printf("scoreList[j].stuName = %s, scoreList[j + 1].stuName = %s\n", scoreList[j].stuName, scoreList[j + 1].stuName);
					memcpy(scoreList[j].stuName, scoreList[j + 1].stuName, sizeof(scoreList[j + 1].stuName));
					//printf("scoreList[j].stuName = %s\n", scoreList[j].stuName);
				
					scoreList[j].particiScore = scoreList[j + 1].particiScore;
					scoreList[j].assigScore1 = scoreList[j + 1].assigScore1;
					scoreList[j].assigScore2 = scoreList[j + 1].assigScore2;
					scoreList[j].assigScore3 = scoreList[j + 1].assigScore3;
					scoreList[j].assigScore4 = scoreList[j + 1].assigScore4;
					scoreList[j].courseScore = scoreList[j + 1].courseScore;
					scoreList[j].finalExamScore = scoreList[j + 1].finalExamScore;
					scoreList[j].finalGrade = scoreList[j + 1].finalGrade;
				}
			}
        }
    }
	

	if (1 != flag_find)
	{
		printf("找不到您输入的名字，退出删除程序\n");
	}
	else
	{		
		*studentcount = *studentcount - 1;
	}
	return;
}


//对成绩单排名,下降沿
void sortStuScore(STU *scoreList, unsigned int studentcount, char *flag_sortStuScore)
{
	int i = 0;
	int j = 0;
	char name_temp[20];
	float temp;
	char flag_change = 0;

	/*printf("scoreList[0].stuName = %s, scoreList[1].stuName = %s,	scoreList[2].stuName = %s, scoreList[3].stuName = %s\n", 
					scoreList[0].stuName, 
					scoreList[1].stuName, 
					scoreList[2].stuName, 
					scoreList[3].stuName);
	*/
	
	for (i = 0; i < studentcount; i++)
	{
		//printf("start A: i = %d, j = %d\n\n\n", i, j);
		for (j = studentcount - 1; j > 0 + i; j--)
		{
			//printf("start B: i = %d, j = %d\n\n", i, j);
			//printf("start B: scoreList[j].finalGrade = %f, scoreList[j - 1].finalGrade = %f\n\n", scoreList[j].finalGrade, scoreList[j - 1].finalGrade);
			if (scoreList[j].finalGrade > scoreList[j - 1].finalGrade)				
			{
				if((1 != i) || (1 != j))
				{
					flag_change = 1;
				}
				//flag_change = 1;
			}

			//printf("i = %d, j = %d, flag_change = %d\n", i, j, flag_change);
			if (1 == flag_change)
			{
				memcpy(name_temp, scoreList[j].stuName, sizeof(scoreList[j].stuName));
				memcpy(scoreList[j].stuName, scoreList[j - 1].stuName, sizeof(scoreList[j - 1].stuName));
				memcpy(scoreList[j - 1].stuName, name_temp, sizeof(name_temp));

				temp = scoreList[j].particiScore;
				scoreList[j].particiScore = scoreList[j - 1].particiScore;
				scoreList[j - 1].particiScore = temp;
				
				temp = scoreList[j].assigScore1;
				scoreList[j].assigScore1 = scoreList[j - 1].assigScore1;
				scoreList[j - 1].assigScore1 = temp;
				
				temp = scoreList[j].assigScore2;
				scoreList[j].assigScore2 = scoreList[j - 1].assigScore2;
				scoreList[j - 1].assigScore2 = temp;
				
				temp = scoreList[j].assigScore3;
				scoreList[j].assigScore3 = scoreList[j - 1].assigScore3;
				scoreList[j - 1].assigScore3 = temp;
				
				temp = scoreList[j].assigScore4;
				scoreList[j].assigScore4 = scoreList[j - 1].assigScore4;
				scoreList[j - 1].assigScore4 = temp;
				
				temp = scoreList[j].courseScore;
				scoreList[j].courseScore = scoreList[j - 1].courseScore;
				scoreList[j - 1].courseScore = temp;				
				
				temp = scoreList[j].finalExamScore;
				scoreList[j].finalExamScore = scoreList[j - 1].finalExamScore;
				scoreList[j - 1].finalExamScore = temp;
				
				temp = scoreList[j].finalGrade;
				scoreList[j].finalGrade = scoreList[j - 1].finalGrade;
				scoreList[j - 1].finalGrade = temp;

				flag_change = 0;
			}
			//printf("over\n");
		}
	}
	
	*flag_sortStuScore = 1;

	return;
}


//显示最低分学员的数据
void show_mindata(STU *scoreList, unsigned int studentcount)
{
	unsigned int i = 0;
	i = studentcount - 1;

	printf ("姓名\t参加活动成绩\t作业1成绩\t作业2成绩\t作业3成绩\t作业4成绩\t课程项目成绩\t期末考试成绩\t总成绩\n");
/*	printf("%s\t %.2f\t %.2f\t %.2f\t %.2f\t %.2f\t %.2f\t %.2f\t %.2f\n",
		scoreList[i].stuName,
		scoreList[i].particiScore,
		scoreList[i].assigScore1,
		scoreList[i].assigScore2,
		scoreList[i].assigScore3,
		scoreList[i].assigScore4,
		scoreList[i].courseScore,
		scoreList[i].finalExamScore,
		scoreList[i].finalGrade);
*/
	printf("%s\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\n",
		scoreList[i].stuName,
		(char)scoreList[i].particiScore,
		(char)scoreList[i].assigScore1,
		(char)scoreList[i].assigScore2,
		(char)scoreList[i].assigScore3,
		(char)scoreList[i].assigScore4,
		(char)scoreList[i].courseScore,
		(char)scoreList[i].finalExamScore,
		(char)scoreList[i].finalGrade);	
			
	return;
}


//显示最高分学员的数据
void show_maxdata(STU *scoreList, unsigned int studentcount)
{
	unsigned int i = 0;
	i = 0;

	printf ("姓名\t参加活动成绩\t作业1成绩\t作业2成绩\t作业3成绩\t作业4成绩\t课程项目成绩\t期末考试成绩\t总成绩\n");
/*	printf("%s\t %.2f\t %.2f\t %.2f\t %.2f\t %.2f\t %.2f\t %.2f\t %.2f\n",
		scoreList[i].stuName,
		scoreList[i].particiScore,
		scoreList[i].assigScore1,
		scoreList[i].assigScore2,
		scoreList[i].assigScore3,
		scoreList[i].assigScore4,
		scoreList[i].courseScore,
		scoreList[i].finalExamScore,
		scoreList[i].finalGrade);
		*/
	printf("%s\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\n",
		scoreList[i].stuName,
		(char)scoreList[i].particiScore,
		(char)scoreList[i].assigScore1,
		(char)scoreList[i].assigScore2,
		(char)scoreList[i].assigScore3,
		(char)scoreList[i].assigScore4,
		(char)scoreList[i].courseScore,
		(char)scoreList[i].finalExamScore,
		(char)scoreList[i].finalGrade);	
	return;
}


//区域分布，未完成
void distribution(STU *scoreList, unsigned int studentcount)
{
	int a = 0;
	int b = 0;
	int c = 0;
	int d = 0;
	int e = 0;
	int f = 0;
	int g = 0;
	int h = 0;
	int i = 0;
	int j = 0;
	int score_temp = 0;
	int m = 0;

	for (m = 0; m < studentcount; m++)
	{
		score_temp = (int)scoreList[m].finalGrade;
		//printf("scoreList[%d].finalGrade = %f, score_temp = %d\n", m, scoreList[m].finalGrade, score_temp);	

		if(score_temp <= 100 && score_temp >= 90)
		{
			a++;
			//printf("a+++ scoreList[%d].%s finalExamScore = %f\n", m, scoreList[m].stuName, scoreList[m].finalExamScore);
		}
		else if(score_temp <= 90 && score_temp >= 80)
		{
			b++;
			//printf("b+++ scoreList[%d].%s finalExamScore = %f\n", m, scoreList[m].stuName, scoreList[m].finalExamScore);
		}
		else if(score_temp <= 80 && score_temp >= 70)
		{
			c++;
			//printf("c+++ scoreList[%d].%s finalExamScore = %f\n", m, scoreList[m].stuName, scoreList[m].finalExamScore);
		}
		else if(score_temp <= 70 && score_temp >= 60)
		{
			d++;
			//printf("d+++ scoreList[%d].%s finalExamScore = %f\n", m, scoreList[m].stuName, scoreList[m].finalExamScore);
		}
		else if(score_temp <= 60 && score_temp >= 50)
		{
			e++;
			//printf("e+++ scoreList[%d].%s finalExamScore = %f\n", m, scoreList[m].stuName, scoreList[m].finalExamScore);
		}
		else if(score_temp <= 50 && score_temp >= 40)
		{
			f++;
			//printf("f+++ scoreList[%d].%s finalExamScore = %f\n", m, scoreList[m].stuName, scoreList[m].finalExamScore);
		}
		else if(score_temp <= 40 && score_temp >= 30)
		{
			g++;
			//printf("g+++ scoreList[%d].%s finalExamScore = %f\n", m, scoreList[m].stuName, scoreList[m].finalExamScore);
		}
		else if(score_temp <= 30 && score_temp >= 20)
		{
			h++;
			//printf("h+++ scoreList[%d].%s finalExamScore = %f\n", m, scoreList[m].stuName, scoreList[m].finalExamScore);
		}
		else if(score_temp <= 20 && score_temp >= 10)
		{
			i++;
			//printf("i+++ scoreList[%d].%s finalExamScore = %f\n", m, scoreList[m].stuName, scoreList[m].finalExamScore);
		}
		else if(score_temp <= 10 && score_temp >= 0)
		{
			j++;
			//printf("j+++ scoreList[%d].%s finalExamScore = %f\n", m, scoreList[m].stuName, scoreList[m].finalExamScore);
		}
	}
	
	printf("score<=100 && score>=90: %d 人\n",a);
	printf("score<=90 && score>=80: %d 人\n",b);
	printf("score<=80 && score>=70: %d 人\n",c);
	printf("score<=70 && score>=60: %d 人\n",d);
	printf("score<=60 && score>=50: %d 人\n",e);
	printf("score<=50 && score>=40: %d 人\n",f);
	printf("score<=40 && score>=30: %d 人\n",g);
	printf("score<=30 && score>=20: %d 人\n",h);
	printf("score<=20 && score>=10: %d 人\n",i);
	printf("score<=10 && score>=0: %d 人\n",j);
	
    return;
} 


//read data from config
char readConfig(STU *scoreList, unsigned int *studentCount)
{
	FILE *fp;
	int len = 0;
	char *buf;
	char i = 0;		//student number
	char j = 0;		//type
	char count = 0;	//count
	char temp[100];
	char c_temp;
	char *p;
	
	buf = (char *)calloc(100, sizeof(char));

	fp = fopen(_CONFIG_FILE_NAME_, "r"); //以只读方式打开文件，该文件必须存在
	if (NULL == fp)
	{
		printf("Error: open file %s failed, return!\n", _CONFIG_FILE_NAME_);
		return FAILED;
	}

	#if 0
	fseek(fp, 0, SEEK_END); //把指针移动到文件的结尾 ，获取文件长度
	len = ftell(fp); //获取文件长度
	//printf("len = %d\n", len);
	char readBuffer[len + 1];

	rewind(fp); //把指针移动到文件开头
	
	fread(readBuffer, 1, len, fp); //读文件
	readBuffer[len] = '\0'; //把读到的文件最后一位 写为0 要不然系统会一直寻找到0后才结束

	printf("readBuffer = %s\n", readBuffer);
	#else
	rewind(fp);
	
	while(fgets(buf, 100, fp))
	{
		count++;	
		//if (NULL == buf)
		//{
		//	printf("read over, return!\n");
		//	return SUCCESSED;
		//}
		//else
		//{		
		  	//printf("buf = %s\n",buf);
		//}
		
		p = strtok(buf, " "); 
		while(p != NULL)
		{ 
			//printf("\nword: %s, j = %d\n" , p, j); 

			switch(j)
			{
				case 0:
					memcpy(scoreList[i].stuName, p, strlen(p));
					//scoreList[i].stuName = p;
					j++;
					//printf("\nscoreList[%d].stuName = %s\n", i, scoreList[i].stuName);
					break;

				case 1:
					scoreList[i].particiScore = atoi(p);
					//printf("scoreList[%d].particiScore = %f\n", i, scoreList[i].particiScore);
					j++;
					break;
					
				case 2:
					scoreList[i].assigScore1 = atoi(p);
					//printf("scoreList[%d].assigScore1 = %f\n", i, scoreList[i].assigScore1);
					j++;
					break;
					
				case 3:
					scoreList[i].assigScore2 = atoi(p);
					//printf("scoreList[%d].assigScore2 = %f\n", i, scoreList[i].assigScore2);
					j++;
					break;

					
				case 4:
					scoreList[i].assigScore3 = atoi(p);
					//printf("scoreList[%d].assigScore3 = %f\n", i, scoreList[i].assigScore3);
					j++;
					break;
					
				case 5:
					scoreList[i].assigScore4 = atoi(p);
					//printf("scoreList[%d].assigScore4 = %f\n", i, scoreList[i].assigScore4);
					j++;
					break;
					
				case 6:
					scoreList[i].courseScore = atoi(p);
					//printf("scoreList[%d].courseScore = %f\n", i, scoreList[i].courseScore);
					j++;
					break;
					
				case 7:
					scoreList[i].finalExamScore = atoi(p);
					//printf("scoreList[%d].finalExamScore = %f\n", i, scoreList[i].finalExamScore);
					j++;
					break;
					
				case 8:
					scoreList[i].finalGrade = atoi(p);	//atof to float
					//printf("scoreList[%d].finalGrade = %f\n", i, scoreList[i].finalGrade);
					j++;
					break;
					
				default:
					break;	
			}
			
	    	p = strtok(NULL, " "); 
		}

		i++;
		j = 0;
		//sleep(3);
  	}

	*studentCount = count;
	#endif
	
	fclose(fp);
}


//write data to config
char writeConfig(STU *scoreList, unsigned int studentCount)
{
	FILE *fp;
	char config_file_size_temp[_CONFIG_FILE_SIZE_];
	//char config_file_size_temp[100000];
	int count = 0;
	int count_temp = 0;
	int i = 0;

	memset(config_file_size_temp, '0', strlen(config_file_size_temp));

	//获取文件指针, 打开可读/写文件，若文件存在则文件长度清为零，即该文件内容会消失。若文件不存在则建立该文件
	fp = fopen(_CONFIG_FILE_NAME_, "w+");
	if (NULL == fp)
	{
		printf("Error: open file %s failed, return!\n", _CONFIG_FILE_NAME_);
		return FAILED;
	}
	
	//studentCount = 4;	//debug
	for (i = 0; i < studentCount; i++)
	{
		//count_temp = count;
		//count = 0;

		//printf("scoreList[i].stuName = %s\n", scoreList[i].stuName);
		count += sprintf(config_file_size_temp + count, "%s  ", scoreList[i].stuName);
		//printf("count = %d\n", count);

		//printf("scoreList[i].particiScore = %p\n", scoreList[i].particiScore);
	    count += sprintf(config_file_size_temp + count, "%d  ", (char)scoreList[i].particiScore);
		//printf("count = %d\n", count);

	    count += sprintf(config_file_size_temp + count, "%d  ", (char)scoreList[i].assigScore1);
		//printf("count = %d\n", count);
		
	    count += sprintf(config_file_size_temp + count, "%d  ", (char)scoreList[i].assigScore2);
		//printf("count = %d\n", count);
		
	    count += sprintf(config_file_size_temp + count, "%d  ", (char)scoreList[i].assigScore3);
		//printf("count = %d\n", count);
		
	    count += sprintf(config_file_size_temp + count, "%d  ", (char)scoreList[i].assigScore4);
		//printf("count = %d\n", count);
		
	    count += sprintf(config_file_size_temp + count, "%d  ", (char)scoreList[i].courseScore);
		//printf("count = %d\n", count);
		
	    count += sprintf(config_file_size_temp + count, "%d  ", (char)scoreList[i].finalExamScore);
		//printf("count = %d\n", count);
		
	    count += sprintf(config_file_size_temp + count, "%d\n", (char)scoreList[i].finalGrade);
		//printf("count = %d\n", count);

		//config_file_size_temp[count] = '\0';
	}
	//printf("==>count = %d\n\n", count);
	
	//向文件写数据
	fwrite (config_file_size_temp, 1, count, fp);
	
	fflush(fp);
	fclose(fp);

}


#if 1
//正态分布，未完成
void normalize(STU *scorelist,unsigned int *studentcount)
{
	int i, j, Tscore, Ascore;
	float s1, v1, v2, Ascore2;

	//debug
	float s2 = 0;

	for(i=0; i<*studentcount; i++)
	{
		Tscore+=scorelist[i].finalGrade;//求总成绩 
	}
	
	Ascore = Tscore/(*studentcount);//平均成绩 
	i=0;
	
	for(j=1;j<=*studentcount;j++)
	{
		i+=(scorelist[i].finalGrade-Ascore)*(scorelist[i].finalGrade-Ascore);//原始方差 的n倍 
	}
	
	v1=i/N;
	s1=sqrt(v1);//标准差 
	i=0;
	
	for(i = 0; i < *studentcount; i++)
	{
		scorelist[i].normaScore = (scorelist[i].finalGrade - Ascore)/s1;//标准分 
	}
	
	printf ("请输入均值，方差："); 
	scanf ("%f%f", &Ascore2,&v2); 
	s2 = sqrt(v2);
	printf("s2 = %f, studentcount = %d\n", s2, *studentcount);
	
	for(i = 0; i < *studentcount; i++)
	{
		scorelist[i].normaScore = s2*scorelist[i].standardScore + Ascore2;
		printf("学生正态化之后的成绩是%s\n", scorelist[i].normaScore);
	}
}
#endif

