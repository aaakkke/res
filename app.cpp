#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<fstream>
#include <cstdlib>
#include<graphics.h>
#include<Windows.h>
using namespace std;
struct space//�û���Ϣ
{
	char name[50];
	char password[20];
};
struct question
{
	char stem[600];//��Ŀ
	char choice1[100];//Aѡ��
	char choice2[100];//Bѡ��
	char choice3[100];//Cѡ��
	char answer;//��
};
struct contest
{
	char name[50];
	int score;
	int last_time;
};
void button(int x, int y, int w, int h,const char txt[30])
{
	setbkmode(TRANSPARENT);
	setfillcolor(RGB(121,205,205));
	fillrectangle(x,y,x+w,y+h);
	int tx = x + (w - textwidth(txt)) / 2;
	int ty = y + (h - textheight(txt)) / 2;
	outtextxy(tx, ty, txt);
}
void button1(int x, int y, int w, int h, const char txt[30])
{
	setbkmode(TRANSPARENT);
	setfillcolor(LIGHTGRAY);
	fillrectangle(x, y, x + w, y + h);
	int tx = x + (w - textwidth(txt)) / 2;
	int ty = y + (h - textheight(txt)) / 2;
	outtextxy(tx, ty, txt);
}
int* test_paper(int num[15])
{
	int i = 0;
    memset(num, -1, 200);
	for (i = 0; i < 10; i++)
	{
		srand(time(nullptr));
		int k = rand() % 20;
		num[i] =20*i+k;
	}
	return num;//num���ڴ洢�鵽�����
}
int random()
{
	int mark = 0;
	srand(time(nullptr));
	mark = rand() % 100;
	return mark;
}
int password_judge(char word[20])
{
	int i = 0, sign = 0;
	int len = strlen(word);
	if (len < 8)
	{
		return 0;
	}
	for (i = 0; i < len; i++)
	{
		if (word[i] > 47 && word[i] < 58)
		{
			sign++;
			break;
		}
	}
	for (i = 0; i < len; i++)
	{
		if (word[i] > 64 && word[i] < 91)
		{
			sign++;
			break;
		}
	}
	for (i = 0; i < len; i++)
	{
		if (word[i] > 96 && word[i] < 123)
		{
			sign++;
			break;
		}
	}
	if (sign == 3)
		return 1;
	else
		return 0;
}
void main_show()//������
{
	cleardevice();
	settextcolor(BLACK);
	settextstyle(24, 0, "����");
	outtextxy(380, 150, "��ѡ����Ĳ���");
	button(250, 220, 120, 70, "ע��");
	button(400, 220, 120, 70, "��¼");
	button(550, 220, 120, 70, "�˳�");
}
void second_show()//������
{
	cleardevice();
	IMAGE img1;
	loadimage(&img1, "./�߿�.jpg", 1000, 640);
	putimage(0, 0, &img1);
	settextcolor(BLACK);
	settextstyle(24, 0, "����");
	outtextxy(350, 40, "��ѡ��Ҫ���еĲ���");
	button(350, 80, 200, 80, "��ϰ");
	button(350, 190, 200, 80, "ģ�⾺��");
	button(350, 310, 200, 80, "��ʽ����");
	button(350, 430, 200, 80, "�鿴���а�");
	button(350, 550, 200, 80, "�˳���¼");
}
int question_show(question problem[205])
{
	int i = random();
	cleardevice();
	settextcolor(BLACK);
	settextstyle(14, 0, "����");
	outtextxy(20, 100, problem[i].stem);
	settextstyle(22, 0, "����");
	button(20, 150, 400, 50, problem[i].choice1);
	button(20, 250, 400, 50, problem[i].choice2);
	button(20, 350, 400, 50, problem[i].choice3);
	return i;
}
void question_show(int i, question problem[205])
{
	cleardevice();
	settextcolor(BLACK);
	settextstyle(14, 0, "����");
	outtextxy(20, 100, problem[i].stem);
	settextstyle(22, 0, "����");
	button(20, 150, 400, 50, problem[i].choice1);
	button(20, 250, 400, 50, problem[i].choice2);
	button(20, 350, 400, 50, problem[i].choice3);
}
void step()
{
	settextcolor(BLACK);
	button(20, 500, 80, 50, "�˳�");
	button(120, 500, 80, 50, "��һ��");
}
class GameClock
{
private:
	clock_t clockBegin;
	clock_t clockNow;
	int		timeMax;
	int		timeNow;

public:
	GameClock(int max)
	{
		clockBegin = clock();
		clockNow = 0;
		timeMax = max;
		timeNow = max;
	}
	clock_t begin()
	{
		return clockBegin;
	}
	int Now()
	{
		return timeNow;
	}
	int Elapse()
	{
		return timeMax - timeNow;
	}
	bool IsStop()
	{
		return timeNow > 0;
	}
	void Tick()
	{
		clockNow = clock();
		timeNow = timeMax - (clockNow - clockBegin) / 1000;
	}
};

int main()
{
	space user[100]; int sort = 0,total=0;
	question problem[300]; contest contestant[50];
	ifstream in_file1("question.txt", ios::in);
	if (!in_file1) exit(-1);
	sort = 0;
	while (!in_file1.fail())
	{
		in_file1 >> problem[sort].stem;
		in_file1 >> problem[sort].choice1;
		in_file1 >> problem[sort].choice2;
		in_file1 >> problem[sort].choice3;
		in_file1 >> problem[sort].answer;
		sort++;
	}
	char temp[50] = { '0' };
	char in_name[50] = { '0' }, in_password[50] = { '0' };
	int num = 0, i = 0, j = 0,target=0,k=0,store[15]={0},store1[15]={0};
	initgraph(1000, 640);
	setbkcolor(WHITE);
	cleardevice();
	//k = question_show(problem);
	//second_show();
	main_show();
	while(1)
	{
		MOUSEMSG msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			num = 0;
			ifstream in_file("user.txt", ios::in);
			if (!in_file) exit(-1);
			while (!in_file.fail())
			{
				in_file>>user[num].name;
				in_file >> user[num].password;
				num++;
			}
			num = num - 1;
			int num1 = 0;
			ifstream in_file2("rank.txt", ios::in);
			if (!in_file2) exit(-1);
			while (!in_file2.fail())
			{
				in_file2 >> contestant[num1].name;
				in_file2 >> contestant[num1].score;
				in_file2 >> contestant[num1].last_time;
				num1++;
			}
			num1--;
			if (msg.x >= 250 && msg.x <= 250 + 120 && msg.y >= 220 && msg.y <= 290)
			{
				cleardevice();
				outtextxy(430, 220, "����������ǳ�");
				cin >> user[num].name; i = 0;
				while (i != num)
				{
					for (i = 0; i < num; i++)
					{
						if (strcmp(user[i].name, user[num].name) == 0)
						{
							cout << "�ǳ��ظ�������������" << endl;
							cin >> user[i].name;
							break;
						}
					}
				}
				if (i == num)
				{
					cleardevice();
					outtextxy(430, 220, "�������������");
					outtextxy(370, 250, "����Ҫ�������Сд��ĸ������");
					j = 0;
					cin >> user[num].password;
					while (password_judge(user[num].password) != 1)
					{
						cout << "�������벻���Ϲ淶������������" << endl;
						cin >> user[num].password;
					}
					while (j != num)
					{
						for (j = 0; j < num; j++)
						{
							if (strcmp(user[j].password, user[num].password) == 0)
							{
								cout << "�����������ظ�������������" << endl;
								cin >> user[num].password;
								break;
							}
						}
					}
				}
				if (i == num && j == num)
				{
					num++;
					cleardevice();
					settextstyle(40, 0, "����");
					outtextxy(400, 220, "ע��ɹ�");
					ofstream out_file("user.txt", ios::out);
					if (!out_file) exit(-1);
					for (k = 0; k < num; k++)
					{
						out_file << user[k].name << " " << user[k].password << endl;
					}
					Sleep(500);
					cleardevice();
					main_show();
				}
			}
			else if (msg.x >= 400 && msg.x <= 400 + 120 && msg.y >= 220 && msg.y <= 220 + 70)
			{
				cleardevice();
				outtextxy(430, 220, "����������ǳ�");
				cin >> in_name;
				for (i = 0; i < num; i++)
				{
					if (strcmp(in_name, user[i].name) == 0)
					{
						break;
					}
				}
				while (i == num)
				{
					cout << "���ǳƲ����ڣ�����������" << endl;
					cin >> in_name;
					for (i = 0; i < num; i++)
					{
						if (strcmp(in_name, user[i].name) == 0)
						{
							break;
						}
					}
				}
				if (i < num)
				{
					cleardevice();
					outtextxy(430, 220, "�������������");
					cin >> in_password;
					while (strcmp(in_password, user[i].password) != 0)
					{
						cout << "�����������������" << endl;
						cin >> in_password;
					}
				}
				if (strcmp(in_password, user[i].password) == 0)
				{
					target = i;
					cleardevice();
					settextstyle(40, 0, "����");
					outtextxy(400, 220, "��¼�ɹ�");
					cout << "��¼�ɹ���" << endl;					
					second_show();					
					while (1)
					{
						msg = GetMouseMsg();
						if(msg.uMsg == WM_LBUTTONDOWN)
						{
							if (msg.x >= 350 && msg.x <= 350 + 200 && msg.y >= 80 && msg.y <= 80 + 80)
							{
								cleardevice();
								k = question_show(problem);
								while (1)
								{
									msg = GetMouseMsg();
									if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 20 && msg.x <= 20 + 400 && ((msg.y >= 150 && msg.y <= 200) ||(msg.y>=250&&msg.y<=300)||(msg.y>=350&&msg.y<=400) ))
									{
										
										if (msg.x >= 20 && msg.x <= 20 + 400 && msg.y >= 150 + 100 * (problem[k].answer - 'A') && msg.y <= 200 + 100 * (problem[k].answer - 'A'))
										{
											settextstyle(20, 0, "����");
											outtextxy(20, 420, "��ѡ��");
											if (msg.y >= 150 && msg.y <= 200)
											{
												outtextxy(70, 420, "A");
											}
											else if (msg.y >= 250 && msg.y <= 300)
											{
												outtextxy(70, 420, "B");
											}
											else if (msg.y >= 350 && msg.y <= 400)
											{
												outtextxy(70, 420, "C");
											}
											step();
											break;
										}
										else
										{
											settextstyle(20, 0, "����");
											outtextxy(20, 420, "��ѡ��");
											if (msg.y >= 150 && msg.y <= 200)
											{
												outtextxy(70, 420, "A");
											}
											else if (msg.y >= 250 && msg.y <= 300)
											{
												outtextxy(70, 420, "B");
											}
											else if (msg.y >= 350 && msg.y <= 400)
											{
												outtextxy(70, 420, "C");
											}
											outtextxy(20, 450, "��ȷ�𰸣�");
											settextcolor(RED);
											outtextxy(150, 450, problem[k].answer);
											step();
											break;
										}
									}
								}
								while (1)
								{
									msg = GetMouseMsg();
									if (msg.uMsg == WM_LBUTTONDOWN)
									{
										if (msg.x >= 120 && msg.x <= 200 && msg.y >= 500 && msg.y <= 550)
										{
											cleardevice();
											k = question_show(problem);
											while (1)
											{
												msg = GetMouseMsg();
												if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 20 && msg.x <= 20 + 400 && ((msg.y >= 150 && msg.y <= 200) || (msg.y >= 250 && msg.y <= 300) || (msg.y >= 350 && msg.y <= 400)))
												{
													if (!(msg.x >= 20 && msg.x <= 20 + 400 && msg.y >= 150 + 100 * (problem[k].answer - 'A') && msg.y <= 200 + 100 * (problem[k].answer - 'A')))
													{
														settextstyle(20, 0, "����");
														outtextxy(20, 420, "��ѡ��");
														settextcolor(BLUE);
														if (msg.y >= 150 && msg.y <= 200)
														{
															outtextxy(70, 420, "A");
														}
														else if (msg.y >= 250 && msg.y <= 300)
														{
															outtextxy(70, 420, "B");
														}
														else if (msg.y >= 350 && msg.y <= 400)
														{
															outtextxy(70, 420, "C");
														}
														settextcolor(BLACK);
														outtextxy(20, 450, "��ȷ�𰸣�");
														settextcolor(RED);
														outtextxy(150, 450, problem[k].answer);
														step();
														break;
													}
													else if (msg.x >= 20 && msg.x <= 20 + 400 && msg.y >= 150 + 100 * (problem[k].answer - 'A') && msg.y <= 200 + 100 * (problem[k].answer - 'A'))
													{
														settextstyle(20, 0, "����");
														outtextxy(20, 420, "��ѡ��");
														if (msg.y >= 150 && msg.y <= 200)
														{
															outtextxy(70, 420, "A");
														}
														else if (msg.y >= 250 && msg.y <= 300)
														{
															outtextxy(70, 420, "B");
														}
														else if (msg.y >= 350 && msg.y <= 400)
														{
															outtextxy(70, 420, "C");
														}
														step();
														break;
													}
												}
											}
										}
										else if (msg.x >= 20 && msg.x <= 100 && msg.y >= 500 && msg.y <= 550)
										{
											second_show();
											break;
										}
									}
								}
							}
							else if (msg.x >= 350 && msg.x <= 350 + 200 && msg.y >= 190 && msg.y <= 190 + 80)
							{
							    memset(store1, -1, 15);
								test_paper(store);
								GameClock gameclock(30);
								for (j = 0; j < 10&& gameclock.IsStop(); j++)
								{
									gameclock.Tick();
									if (gameclock.IsStop()<=0)
									{
										break;
									}									
									question_show(store[j], problem);
									settextcolor(BLACK);
									settextstyle(30, 0, "����");
									sprintf(temp, "%d", gameclock.Now());
									outtextxy(900, 20, temp);
									settextstyle(20, 0, "����");
									while (1)
									{
										msg = GetMouseMsg();
										if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 20 && msg.x <= 20 + 400 && ((msg.y >= 150 && msg.y <= 200) || (msg.y >= 250 && msg.y <= 300) || (msg.y >= 350 && msg.y <= 400)))
										{
											int answerTop = 150 + 100 * (int)(problem[store[j]].answer - 'A');

											if (msg.x >= 20 && msg.x <= 420 && msg.y >= answerTop && msg.y <= answerTop + 50)
											{
												store1[j] = 1;
											}
											else
											{
												store1[j] = 0;
											}
											settextcolor(BLACK);
											outtextxy(20, 420, "��ѡ��");
											settextcolor(BLUE);
											if (msg.y >= 150 && msg.y <= 200)
											{
												outtextxy(80, 420, "A");
											}
											else if (msg.y >= 250 && msg.y <= 300)
											{
												outtextxy(80, 420, "B");
											}
											else if (msg.y >= 350 && msg.y <= 400)
											{
												outtextxy(80, 420, "C");
											}
											Sleep(500);
											break;
										}
									}
								}																	
								int count = 0;
								cleardevice();

								for (j = 0,total=0; j < 10; j++)
								{
									if (store1[j] == 0)
									{
										
										settextcolor(BLACK);
										settextstyle(15, 0, "����");
										outtextxy(20, 40 + (40 * count), problem[store[j]].stem);
										settextcolor(RED);
										settextstyle(20, 0, "����");
										outtextxy(20, 55 + (40 * count), problem[store[j]].answer);
										count++;
									}
									else
									{
										total++;
									}
								}
								sprintf(temp, "%d", total);
								settextstyle(20, 0, "����");
								button(20, 10,100,25, "������");
								outtextxy(90, 12, temp);
								button1(800, 520, 80, 60, "����");
								while (1)
								{
									msg = GetMouseMsg();
									if (msg.uMsg == WM_LBUTTONDOWN)
									{
										if (msg.x >= 800 && msg.x <= 880 && msg.y >= 520 && msg.y <= 580)
										{
											second_show();
											break;
										}
									}
								}
							}
							else if (msg.x >= 350 && msg.x <= 350 + 220 && msg.y >= 310 && msg.y <= 310 + 80)
							{
							int rank1 = num1+1;
							strcpy(contestant[num1].name, user[target].name);
							memset(store1, -1, 15);
							test_paper(store);
							GameClock gameclock(30);
							
							for (j = 0,total=0; j < 10 && gameclock.IsStop(); j++)
							{
								gameclock.Tick();
								if (gameclock.IsStop() <= 0)
								{
									break;
								}
								question_show(store[j], problem);
								settextcolor(BLACK);
								settextstyle(30, 0, "����");
								sprintf(temp, "%d", gameclock.Now());
								outtextxy(900, 20, temp);
								settextstyle(20, 0, "����");
								while (1)
								{
									msg = GetMouseMsg();
									if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 20 && msg.x <= 20 + 400 && ((msg.y >= 150 && msg.y <= 200) || (msg.y >= 250 && msg.y <= 300) || (msg.y >= 350 && msg.y <= 400)))
									{
										int answerTop = 150 + 100 * (int)(problem[store[j]].answer - 'A');

										if (msg.x >= 20 && msg.x <= 420 && msg.y >= answerTop && msg.y <= answerTop + 50)
										{
											store1[j] = 1;
											total++;
										}
										else
										{
											store1[j] = 0;
										}
										settextcolor(BLACK);
										outtextxy(20, 420, "��ѡ��");
										settextcolor(BLUE);
										if (msg.y >= 150 && msg.y <= 200)
										{
											outtextxy(80, 420, "A");
										}
										else if (msg.y >= 250 && msg.y <= 300)
										{
											outtextxy(80, 420, "B");
										}
										else if (msg.y >= 350 && msg.y <= 400)
										{
											outtextxy(80, 420, "C");
										}
										Sleep(500);
										break;
									}
								}
							}
							gameclock.Tick();
							contestant[num1].last_time = gameclock.Now();
							contestant[num1].score = total;
							for (i = 0; i < num1; i++)
							{
								if (contestant[i].score == contestant[num1].score)
								{
									if (contestant[num1].last_time > contestant[i].last_time)
									{
										for (j = num1; j >= i; j--)
										{
											contestant[j + 1] = contestant[j];
										}
										contestant[i] = contestant[num1 + 1];
										rank1 = i + 1;
									}
									else if (contestant[num1].last_time == contestant[i].last_time)
									{
										for (j = num1; j > i; j--)
										{
											contestant[j + 1] = contestant[j];
										}
										contestant[i+1] = contestant[num1 + 1];
										rank1 = i + 2;
									}
									break;
								}
								else if (contestant[i].score < contestant[num1].score)
								{
									for (j = num1; j >= i; j--)
									{
										contestant[j + 1] = contestant[j];
									}
									contestant[i] = contestant[num1 + 1];
									rank1 = i + 1;
									break;
								}
							}
							num1++;
							ofstream out_file2("rank.txt", ios::out);
							if (!out_file2) exit(-1);
							for (k = 0; k < num1; k++)
							{
								out_file2 << contestant[k].name << " " << contestant[k].score << " " << contestant[k].last_time << endl;
							}
							cleardevice();
							IMAGE img2;
							loadimage(&img2, "./�߿�2.png", 1000, 640);
							putimage(0, 0, &img2);
							settextstyle(35, 0, "�����п�");
							settextcolor(RGB(238,121,66));
							outtextxy(380, 200, "���Խ�����");
							settextstyle(24, 0, "����");
							settextcolor(BLACK);
							outtextxy(400, 290, "������");
							sprintf(temp, "%d", total);
							settextcolor(RED);
							outtextxy(480, 290, temp);
							settextcolor(BLACK);
							outtextxy(400, 370, "������");
							sprintf(temp, "%d", rank1);
							settextcolor(RED);
							outtextxy(480, 370, temp);
							button1(800, 520, 80, 60, "����");
							while (1)
							{
								msg = GetMouseMsg();
								if (msg.uMsg == WM_LBUTTONDOWN)
								{
									if (msg.x >= 800 && msg.x <= 880 && msg.y >= 520 && msg.y <= 580)
									{
										second_show();
										break;
									}
								}
							}
                            }
							else if (msg.x >= 350 && msg.x <= 350 + 220 && msg.y >= 430 && msg.y <= 430 + 80)
							{							    
							     int sum1 = 0;
							     cleardevice();
								 IMAGE img;
								 loadimage(&img, "./���ְ�.jpg", 1000, 640);
								 putimage(0, 0, &img);
								
							     for (i = 0; i < num1; i++)
							     {
									 for (j = 0; j < i; j++)
									 {
										 if (strcmp(contestant[i].name, contestant[j].name) == 0)
										 {
											 break;
										 }
									 }
									 if (j == i)
									 {
										 settextcolor(BLACK);
										 sprintf(temp, "%d", sum1+1);
										 button(300, 110 + sum1 * 50, 40, 30, temp);
										 settextcolor(WHITE);
										 outtextxy(370, 110+sum1*50, contestant[i].name);
										 sprintf(temp, "%d", contestant[i].score);
										 outtextxy(535, 110 + sum1 * 50, temp);
										 outtextxy(560, 110 + sum1 * 50, "��");
										 sprintf(temp, "%d", 30-contestant[i].last_time);
										 outtextxy(610, 110 + sum1 * 50, temp);
										 outtextxy(640, 110 + sum1 * 50, "��");
										 sum1++;
									 }
									 if (sum1 == 10)
									 {
										 break;
									 }
								 }
								 settextcolor(RED);
								 button1(800, 560, 80, 60, "����");
								 while (1)
								 {
									 msg = GetMouseMsg();
									 if (msg.uMsg == WM_LBUTTONDOWN)
									 {
										 if (msg.x >= 800 && msg.x <= 880 && msg.y >= 560 && msg.y <= 620)
										 {
											 second_show();
											 break;
										 }
									 }
								 }
                            }
							else if (msg.x >= 350 && msg.x <= 350 + 200 && msg.y >= 550 && msg.y <= 550 + 80)
							{
								target = -1;
								main_show();
								break;
							}
							
						}
					}
					
				}
			}
			
			else if (msg.x >= 550 && msg.x <= 550 + 120 && msg.y >= 220 && msg.y <= 290)
			{
			    int isok = MessageBox(NULL, "��ȷ��Ҫ�رճ�����", "��ʾ", MB_OKCANCEL);
				if(isok==IDOK)
				{
					cleardevice();
					settextstyle(40, 0, "�����п�");
					settextcolor(BROWN);
					outtextxy(300, 220, "�ڴ�����´�ʹ�ã�");
					Sleep(500);
					break;
				}
            }
			msg = GetMouseMsg();
		}
	}
	closegraph();
	return 0;
}