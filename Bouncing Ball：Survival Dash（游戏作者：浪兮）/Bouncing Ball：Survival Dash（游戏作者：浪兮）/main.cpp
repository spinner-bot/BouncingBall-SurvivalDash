#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS
#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <random>
#include <string>
#include <cmath>
#include <cstdlib>
#include <format>
#include <tchar.h>
#include <stdio.h>
int main()
{
	//模式配置
	std::cout << "请选择运行模式：" << std::endl;
	std::cout << "输入模式代码（1 - 7）" << std::endl;
	std::cout << "1.动效 2.Dropping Ball 5.简单模式 6.挑战模式 7.Bouncing Ball：Survival Dash" << std::endl;
	int mode = 0;
	std::cin >> mode;
	std::cout << "是否启用管理员模式（打印数据）？启用：1" << std::endl;
	int record = 0;
	std::cin >> record;
	if (record == 1)
	{
		std::cout << "模式启用。注意部分模块不支持此功能！" << std::endl;
		std::cout << "数据记录：" << std::endl;
	}
	//图形界面初始化
	int width = 1600;
	int length = 900;
	initgraph(width, length);
	//分模块执行
	while (mode == 1)
	{
		cleardevice();
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis0(100, length - 99);
		int y = dis0(gen);
		std::uniform_int_distribution<> dis(100, width - 99);
		int x = dis(gen);
		std::uniform_int_distribution<> dis1024(1, 300);
		int r = dis1024(gen);
		fillcircle(x, y, r);
		Sleep(5);
	}
	if (mode == 2)
	{
		int x = 800;
		int r = 75;
		int n = 0;
		for (int y = 150;y < 1125;y += 40)
		{
			n = n + 1;
			cleardevice();
			fillcircle(x, y, r);
			Sleep(600 / n - 0.75 * n);//【!】并未限定停留时间为正。请谨慎改动参数
		}
	}
	if (mode > 2)
	{
		//初始化
		double x = 800;
		double y = 600;
		double vx = 0;
		double vy = 0;
		double ax = 0;
		double ay = 0;
		double ag = 1;
		double ua = 1;
		double uv = 6;
		int r = 50;
		double uf = 0.99;
		double uc = -0.9;
		int screen = 0;
		int blockspawn = 50;
		int blockpersist = 0;
		int blockminpersist = 300;
		int blockt1 = 0;
		int blockt2 = 0;
		int blockt3 = 0;
		int blockmaxsize = 30;
		int blockwarning = 30;
		int xblock = 0;
		int yblock = 0;
		int rblock = 0;
		int rewardspawn = 120;
		int rewardpersist = 0;
		int rewardminpersist = 180;
		int rewardt1 = 0;
		int rewardt2 = 0;
		int xreward = 0;
		int yreward = 0;
		int rreward = 0;
		bool blockexist = 0;
		bool rewardexist = 0;
		int pace = 30;
		bool blockcrash = 0;
		bool rewardcrash = 0;
		int blockcrashtimer = 150;
		double point = 0;
		int life = 5;
		wchar_t showpoint[30] = L"";
		int rewardglaretimer = 0;
		int finalpoint = 0;
		int getpoint = 0;
		wchar_t showfinalpoint[30] = L"";
		double lifepackspawn = 30;
		int red = 0;
		wchar_t showlife[10] = L"";
		int lppersist = 0;
		int lpminpersist = 10;
		int lpt1 = 0;
		int lpt2 = 0;
		int xlp = 0;
		int ylp = 0;
		int rlp = 0;
		double lpspawntimer = 450;
		int lpspawn = 45;
		bool lpexist = 0;
		int therapyglaretimer = 0;
		int xarmor = 0;
		int yarmor = 0;
		int rarmor = 0;
		double armorduration = 0;
		bool armorexist = 0;
		double armorminpersist = 0;
		int armorpersist = 0;
		int armorspawn = 10;
		int armort1 = 0;
		int armort2 = 0;
		wchar_t showarmor[20] = L"";
		wchar_t broadcast[20] = L"你获得150点入场护盾";
		int broadcasttimer = 85;
		int showarmorwidth = 0;
		int broadcastwidth = 0;
		int blockcrashpunishment = 50;
		int tipwidth = 0;
		int xtip = 0;
		int ytip = 0;
		std::random_device rd;
		std::mt19937 gen(rd());
		//入场提示
		wchar_t tips[][100] =
		{
			L"Bouncing Ball：Survival Dash",
			L"游戏作者：浪兮  (抖音、B站、视频号@浪兮有点浪)",
			L"Press ENTER to go on...",
			L"",
			L"欢迎来到Bouncing Ball：Survival Dash！",
			L"你的任务是控制小球生存下去，",
			L"在躲避障碍的同时尽可能多地吃掉积分...",
			L"按方向键可控制小球移动",
			L"随着时间流逝，游戏难度会越来越大，但奖励也会越来越丰厚！",
			L"场上还将刷新各种道具，帮助你更好地进行挑战！",
			L"如果你准备好了，我们就开始吧！",
		};
		int tipcount = sizeof(tips) / sizeof(tips[0]);
		for (int i = 0; i < tipcount; i++)
		{
			tipwidth = textwidth(tips[i]);
			xtip = 10;
			ytip = 10 + 55 * i;
			settextcolor(WHITE);
			settextstyle(45, 0, L"微软雅黑");
			outtextxy(xtip, ytip, tips[i]);
			do
			{
				Sleep(30);
			} while (GetAsyncKeyState(VK_RETURN) & 0x8000);
			if (i == 0)
			{
				Sleep(1250);
			}
			if (i == 1)
			{
				Sleep(3250);
			}
			if (i == 2 || i > 3)
			{
				fflush(stdin);
				do
				{
					Sleep(30);
				} while (!(GetAsyncKeyState(VK_RETURN) & 0x8000));
			}
		}
		cleardevice();
		//游戏开始
		BeginBatchDraw();
		while (life > 0)
		{
			screen = screen + 1;
			blockcrashtimer = blockcrashtimer - 1;
			rewardglaretimer = rewardglaretimer - 1;
			lpspawntimer = lpspawntimer - 1;
			therapyglaretimer = therapyglaretimer - 1;
			broadcasttimer = broadcasttimer - 1;
			point = point + 1 + 0.0035 * screen;
			if (record == 1)
			{
				std::cout << "第" << screen << "次刷新:" << std::endl;
			}
			if (life > 3)
			{
				red = 0;
			}
			else
			{
				red = 180 - 45 * life;
			}
			setbkcolor(RGB(red, 0, 0));
			settextstyle(72, 0, L"微软雅黑");
			if (rewardglaretimer > 0)
			{
				swprintf(showpoint, L"%08d+%d", (int)floor(point), (int)floor(getpoint));
			}
			else
			{
				swprintf(showpoint, L"%08d", (int)floor(point));
			}
			outtextxy(10, 10, showpoint);
			swprintf(showlife, L"x%d", (int)floor(life));
			outtextxy(1500, 10, showlife);
			if (broadcasttimer > 0)
			{
				broadcastwidth = textwidth(broadcast);
				outtextxy(825 - 0.5 * broadcastwidth, 10, broadcast);
			}
			if (blockcrashtimer > 0)
			{
				settextstyle(40, 0, L"微软雅黑");
				swprintf(showarmor, L"护盾值%d", (int)floor(blockcrashtimer));
				showarmorwidth = textwidth(showarmor);
				outtextxy(x - 0.5 * showarmorwidth, y - 85, showarmor);
			}
			setfillcolor(RGB(255, 50, 50));
			FlushBatchDraw();
			Sleep(pace);
			cleardevice();
			//运动学计算
			vx = uf * (vx + ua * ax);
			if (y < 975)
			{
				vy = vy + ua * (ay + ag);
			}
			else
			{
				vy = vy + ua * ay;
			}
			x = x + uv * vx;
			y = y + uv * vy;
			if (record == 1)
			{
				std::cout << "运动：vx=" << vx << "  vy=" << vy << "  x=" << x << "  y=" << y << std::endl;
			}
			//加速度重置
			ax = 0;
			ay = 0;
			//绘制小球
			if (blockcrashtimer > 0)
			{
				setfillcolor(RGB(238, 130, 238));
			}
			else
			{
				setfillcolor(WHITE);
			}
			if (therapyglaretimer > 0)
			{
				setlinecolor(RGB(255, 89, 0));
				setlinestyle(PS_SOLID, 10);
			}
			else if (rewardglaretimer > 0)
			{
				setlinecolor(RGB(0, 255, 255));
				setlinestyle(PS_SOLID, 10);
			}
			else
			{
				setlinestyle(PS_NULL, 1);
			}
			fillcircle(x, y, r);
			//位置侦测&碰撞响应
			if (x <= 50 && vx < 0)
			{
				vx = uc * vx;
			}
			if (x >= 1550 && vx > 0)
			{
				vx = uc * vx;
			}
			if (y >= 975 && vy > 0)
			{
				vy = uc * vy;
			}
			//运动控制
			if (GetAsyncKeyState(VK_UP) & 0x8000)
			{
				ay = ay - 1.75;
			}
			if (GetAsyncKeyState(VK_DOWN) & 0x8000)
			{
				Sleep(150);
			}
			if ((GetAsyncKeyState(VK_LEFT) & 0x8000) && x > 50)
			{
				ax = ax - 1;
			}
			if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) && x < 1550)
			{
				ax = ax + 1;
			}
			if (GetAsyncKeyState(VK_SPACE) & 0x8000)
			{
				x = 800;
				y = 600;
				vx = 0;
				vy = 0;
			}
			if (record == 1)
			{
				std::cout << "控制：ax=" << ax << "  ay=" << ay << std::endl;
			}
			//稳定性模块
			if (mode > 3)
			{
				//速度限制
				if (vx > 15)
				{
					vx = sqrt(15 * vx);
				}
				if (vy > 20)
				{
					vy = sqrt(20 * vy);
				}
				//自动复位
				if (!((x > -650) && (x < 2250) && (y > -10000) && (y < 1675)))
				{
					x = 800;
					y = 600;
					vx = 0.5 * vx;
					vy = 0.5 * vy;
				}
				//掉落抵抗
				if (y > 1075)
				{
					y = y + 1;
				}
				//震动消除
				if ((abs(vy) < 3.5) && (ay == 0))
				{
					vy = 0.85 * vy;
				}
				if ((abs(vx) < 3.5) && (ay == 0))
				{
					vx = 0.85 * vx;
				}
				if ((abs(vy) < 1.15) && (ay == 0))
				{
					vy = 0.65 * vy;
				}
				if ((abs(vx) < 1.15) && (ay == 0))
				{
					vx = 0.65 * vx;
				}
				if ((abs(vy) < 0.35) && (ay == 0))
				{
					vy = 0;
				}
				if ((abs(vx) < 0.35) && (ay == 0))
				{
					vx = 0;
				}
				//道具模块
				if (mode > 4)
				{
					//随机触发
					if (blockexist == 0)
					{
						std::uniform_int_distribution<> dis5011(0, 9999);
						int randomnumber501 = dis5011(gen);
						if (randomnumber501 < blockspawn);
						{
							blockt1 = screen;
							blockt2 = screen + blockwarning + 1;
							std::uniform_int_distribution<> dis501101(blockminpersist, 1.1 * blockminpersist + 30);
							blockpersist = dis501101(gen);
							blockt3 = blockt2 + blockpersist;
							std::uniform_int_distribution<> dis501201(150, 1450);
							xblock = dis501201(gen);
							std::uniform_int_distribution<> dis501202(100, 1100);
							yblock = dis501202(gen);
							std::uniform_int_distribution<> dis501203(20, blockmaxsize);
							rblock = dis501203(gen);
							blockexist = 1;
						}
					}
					if (rewardexist == 0)
					{
						std::uniform_int_distribution<> dis502(0, 9999);
						int randomnumber502 = dis502(gen);
						if (randomnumber502 < rewardspawn)
						{
							rewardt1 = screen;
							std::uniform_int_distribution<> dis5021(rewardminpersist, 1.1 * rewardminpersist + 30);
							rewardpersist = dis5021(gen);
							rewardt2 = rewardt1 + rewardpersist;
							std::uniform_int_distribution<> dis502201(150, 1450);
							xreward = dis502201(gen);
							std::uniform_int_distribution<> dis502202(100, 1100);
							yreward = dis502202(gen);
							std::uniform_int_distribution<> dis502203(20, 55);
							rreward = dis502203(gen);
							rewardexist = 1;
						}
					}
					//道具功能模块
					if (blockexist == 1)
					{
						if (screen >= blockt1 && screen < blockt2)
						{
							setlinecolor(RGB(255, 255, 0));
							setlinestyle(PS_SOLID, 10);
							circle(xblock, yblock, rblock - 5);
						}
						if (screen >= blockt2 && screen < blockt3)
						{
							setfillcolor(RGB(255, 127, 15));
							setlinestyle(PS_NULL, 1);
							fillcircle(xblock, yblock, rblock);
							if (pow(x - xblock, 2) + pow(y - yblock, 2) <= pow(r + rblock, 2))
							{
								if (blockcrashtimer <= 0)
								{
									blockcrash = 1;
									blockexist = 0;
									blockcrashtimer = 65;
									life = life - 1;
									broadcasttimer = 35;
									swprintf(broadcast, L"你中招了！生命值-1");
								}
								else
								{
									blockexist = 0;
									if (blockcrashtimer < 60)
									{
										blockcrashpunishment = 60;
									}
									else if (blockcrashtimer < 150)
									{
										blockcrashpunishment = 51 + 0.15 * blockcrashtimer;
									}
									else if (blockcrashtimer < 250)
									{
										blockcrashpunishment = 21 + 0.35 * blockcrashtimer;
									}
									else
									{
										blockcrashpunishment = -54 + 0.65 * blockcrashtimer;
									}
									blockcrashtimer = blockcrashtimer - blockcrashpunishment;
									broadcasttimer = 35;
									swprintf(broadcast, L"破甲：护盾值-%d", (int)floor(blockcrashpunishment));
								}
							}
						}
						if (screen >= blockt3)
						{
							blockexist = 0;
						}
					}
					if (rewardexist == 1)
					{
						if (screen >= rewardt1 && screen < rewardt2)
						{
							setlinecolor(RGB(5 * rreward - 100, 255, 0));
							setlinestyle(PS_SOLID, 8);
							circle(xreward, yreward, rreward - 4);
							if (pow(x - xreward, 2) + pow(y - yreward, 2) <= pow(r + rreward, 2))
							{
								rewardcrash = 1;
								rewardexist = 0;
								getpoint = (8 * (55 - rreward) + 220) * (1 + 0.0065 * screen);
								point = point + getpoint;
								rewardglaretimer = 35;
								therapyglaretimer = 0;
							}
						}
						if (screen >= rewardt2)
						{
							rewardexist = 0;
						}
					}
					//互动模块
					if (blockcrash == 1)
					{
						//预留功能
						blockcrash = 0;
					}
					if (rewardcrash == 1)
					{
						//预留功能
						rewardcrash = 0;
					}
					//难度倍增机制
					if (mode >= 6)
					{
						if (screen % 40 == 0)
						{
							rewardspawn = rewardspawn + 1;
						}
						if (screen % 350 == 0 && pace > 20)
						{
							pace = pace - 1;
						}
						else if (screen % 700 == 0 && pace > 15)
						{
							pace = pace - 1;
						}
						else if (screen % 1400 == 0 && pace > 10)
						{
							pace = pace - 1;
						}
						if (screen % 50 == 0 && blockmaxsize < 90)
						{
							blockmaxsize = blockmaxsize + 1;
						}
						else if (screen % 75 == 0 && blockmaxsize >= 90 && blockmaxsize < 200)
						{
							blockmaxsize = blockmaxsize + 1;
						}
						else if (screen % 100 == 0 && blockmaxsize >= 200 && blockmaxsize < 350)
						{
							blockmaxsize = blockmaxsize + 1;
						}
						else if (screen % 125 == 0 && blockmaxsize >= 350 && blockmaxsize < 500)
						{
							blockmaxsize = blockmaxsize + 1;
						}
						if (screen % 80 == 0 && blockminpersist > 200)
						{
							blockminpersist = blockminpersist - 1;
						}
						else if (screen % 120 == 0 && blockminpersist <= 200 && blockminpersist > 120)
						{
							blockminpersist = blockminpersist - 1;
						}
						else if (screen % 160 == 0 && blockminpersist <= 120 && blockminpersist > 80)
						{
							blockminpersist = blockminpersist - 1;
						}
						else if (screen % 200 == 0 && blockminpersist <= 80 && blockminpersist > 60)
						{
							blockminpersist = blockminpersist - 1;
						}
						else if (screen % 240 == 0 && blockminpersist <= 60 && blockminpersist > 45)
						{
							blockminpersist = blockminpersist - 1;
						}
						if (record == 1)
						{
							std::cout << "难度：pace=" << pace << " blockmaxsize=" << blockmaxsize << "  blockminpersist=" << blockminpersist << std::endl;
						}
						if (mode >= 7)
						{
							//治疗包模块
							if (lpexist == 0 && lpspawntimer < 0)
							{
								std::uniform_int_distribution<> dis7000(0, 9999);
								int randomnumber7000 = dis7000(gen);
								if (randomnumber7000 < 650)
								{
									lpminpersist = 65 + 0.00265 * screen;
									lpt1 = screen;
									std::uniform_int_distribution<> dis7001(lpminpersist, 1.1 * lpminpersist + 30);
									lppersist = dis7001(gen);
									lpt2 = lpt1 + lppersist;
									std::uniform_int_distribution<> dis7002(150, 1450);
									xlp = dis7002(gen);
									std::uniform_int_distribution<> dis7003(100, 1100);
									ylp = dis7003(gen);
									std::uniform_int_distribution<> dis7004(20, 35);
									rlp = dis7004(gen);
									lpexist = 1;
									lpspawntimer = 13500000 / screen;
									if (lpspawntimer > 2000)
									{
										lpspawntimer = 2000;
									}
									if (lpspawntimer < 200)
									{
										lpspawntimer = 200;
									}
								}
							}
							if (lpexist == 1)
							{
								if (screen >= lpt1 && screen < lpt2)
								{
									setlinecolor(RGB(0, 127, 255));
									setlinestyle(PS_SOLID, 6);
									setfillcolor(RGB(0, 255, 0));
									fillcircle(xlp, ylp, rlp - 3);
									if (pow(x - xlp, 2) + pow(y - ylp, 2) <= pow(r + rlp, 2))
									{
										lpexist = 0;
										life = life + 1;
										therapyglaretimer = 60;
										rewardglaretimer = 0;
										broadcasttimer = 35;
										swprintf(broadcast, L"治疗：生命值+1");
									}
								}
								if (screen >= lpt2)
								{
									lpexist = 0;
								}
							}
							//护盾模块
							if (screen % 135 == 0 && armorspawn < 25)
							{
								armorspawn = armorspawn + 1;
							}
							else if (screen % 270 == 0 && armorspawn < 45)
							{
								armorspawn = armorspawn + 1;
							}
							else if (screen % 540 == 0 && armorspawn > 75)
							{
								armorspawn = armorspawn + 1;
							}
							else if (screen % 1080 == 0 && armorspawn > 115)
							{
								armorspawn = armorspawn + 1;
							}
							else if (screen % 2160 == 0 && armorspawn > 165)
							{
								armorspawn = armorspawn + 1;
							}
							else if (screen % 4320 == 0 && armorspawn > 225)
							{
								armorspawn = armorspawn + 1;
							}
							if (armorexist == 0)
							{
								std::uniform_int_distribution<> dis7100(0, 9999);
								int randomnumber7100 = dis7100(gen);
								if (randomnumber7100 < armorspawn)
								{
									armorminpersist = 135 + 0.01265 * screen;
									armort1 = screen;
									std::uniform_int_distribution<> dis7101(armorminpersist, 1.1 * armorminpersist + 30);
									armorpersist = dis7101(gen);
									armort2 = armort1 + armorpersist;
									std::uniform_int_distribution<> dis7102(150, 1450);
									xarmor = dis7102(gen);
									std::uniform_int_distribution<> dis7103(100, 1100);
									yarmor = dis7103(gen);
									std::uniform_int_distribution<> dis7104(25, 45);
									rarmor = dis7104(gen);
									armorexist = 1;
								}
							}
							if (armorexist == 1)
							{
								if (screen >= armort1 && screen < armort2)
								{
									setlinecolor(RGB(240, 145, 162));
									setlinestyle(PS_SOLID, 6);
									setfillcolor(RGB(230, 203, 109));
									fillcircle(xarmor, yarmor, rarmor - 3);
									if (pow(x - xarmor, 2) + pow(y - yarmor, 2) <= pow(r + rarmor, 2))
									{
										armorexist = 0;
										std::uniform_int_distribution<> dis7110(65, 130 + 0.00085 * screen);
										armorduration = 0.00125 * screen + dis7110(gen);
										if (blockcrashtimer < 0)
										{
											blockcrashtimer = 0;
										}
										blockcrashtimer = blockcrashtimer + armorduration;
										broadcasttimer = 35;
										swprintf(broadcast, L"免疫：护盾值+%d", (int)floor(armorduration));
									}
								}
								if (screen >= armort2)
								{
									armorexist = 0;
								}
							}
							if (record == 1)
							{
								std::cout << "互动：rewardspawn=" << rewardspawn << " lpspawntimer=" << lpspawntimer << " armorspawn=" << armorspawn << std::endl;
							}
						}
					}
				}
			}
		}
		EndBatchDraw();
		finalpoint = (int)floor(point);
		setbkcolor(RGB(198, 130, 238));
		cleardevice();
		swprintf(showfinalpoint, L"最终得分：%08d", finalpoint);
		settextstyle(85, 0, L"微软雅黑");
		outtextxy(500, 465, showfinalpoint);
		Sleep(2000);
		_getch();
		Sleep(1500);
	}
	return 0;
}