#include <graphics.h>   
#include <conio.h>
#include <time.h>
#include <WINDOWS.H>
#include <queue>
#include <stdlib.h>
#include <stdio.h>
#pragma comment(lib,"Winmm.lib")
#define guozimax 4
#define wuditime 100  //无敌时间
#define jiasutime 50 //加速时间
#define jiansutime 20//减速时间
#define	WIDTH		65			// 游戏区域网格宽度
#define	HEIGHT		34			// 游戏区域网格高度
#define	ITEMSIZE	20			// 游戏元素大小
#define bloodmax 6				// 初始时的血量
#define sheshengdechangdu 7		// 初始时蛇身的长度
#define ztsdinit 50				//初始时正常速度//延时
#define xiebaomax 100			//血包出现频率
#define jiasubaomax 100			//空投加速包出现频率
#define jiansubaomax 100		//减速包出现频率
#define jiasuhousd 10		//加速后速度//延时
#define jiansuhousd 200		//减速后速度//延时
int a[HEIGHT][WIDTH]={0},dir=1;// dir 是 方向  1是向右 2是向左  3是向上 4是向下
int k=0, z=0, mon=0;//k是 调控 果子出现速率   在guozi函数中使用 z是控制障碍物葡萄 在zhangaiwu函数中使用 mon是控制小仓鼠"gif"闪烁
int sc=0, sc_=0; //sc 是分数   在画布的最下方 更新显示    最后报给玩家  我为什么要有两个sc呢 在fs函数中会具体说明 
int wudi=0, wudi_=0;    
int jiasu=0, jiasu_=0;
int jiansu=0, jiansu_=0;
int ztsd=100; 
int jiansubaodeshuliang=jiansubaomax;
int jiasubaodeshuliang=jiasubaomax;
int xiebaodeshuliang=xiebaomax;
int g1=1 , g2=1, g3=1, g4=1,g5, g2_=1,imax,jmax, ip, jp, max, it, jt;	// 	g1 g2 g3 g5 控制游戏结束	//游戏开始时 在Start()函数中重新赋值								
TCHAR s2[4]= _T("0"),s1[] = _T("分数:"), shengmingwenzi[]=_T("生命:"), shengmingshuzi[2]=_T("0");// 全局 字符串
TCHAR sorry1[] = _T("啊欧! 贪吃蛇撞在了树上, 请按任意键继续");
TCHAR sorry2[] = _T("啊欧! 贪吃蛇吃了太多的酸葡萄, 请按任意键继续");
TCHAR sorry3[] = _T("啊欧! 贪吃蛇撞自己身上了, 请按任意键继续");
TCHAR sorry4[] = _T("啊欧! 贪吃蛇被小仓鼠咬了, 请按任意键继续");
TCHAR s3[] = _T("点此暂停");
TCHAR wudizfc[] = _T("无敌");
TCHAR jiasuzfc[] = _T("加速");
TCHAR jiansuzfc[] = _T("减速");
//以下是函数声明
void jiansubao(int a[HEIGHT][WIDTH]);
void jiasubao(int a[HEIGHT][WIDTH]);
void inittext();// 文字格式初始化
void initimg();// 图片的初始化载入
void Show(int a[HEIGHT][WIDTH]);//这是显示函数 根据 二维数组a中的 具体值 输出图片
void Start(int a[HEIGHT][WIDTH]);// 初始化
void Loop(int a[HEIGHT][WIDTH]);// 移动函数
void hello();   // 初始画面函数
void bye();		//结束画面函数
void Interact();	//	按键函数   关键调整 全局变量dir 1是向右 2是向左  3是向上 4是向下
void guozi(int a[HEIGHT][WIDTH]);// 果子出现函数 调整全局变量k
void xiebao(int a[HEIGHT][WIDTH]); //血包出现函数 
void Game(int a[HEIGHT][WIDTH]); // 也可叫	撞墙吃果 函数
void chiguozi2(int a[HEIGHT][WIDTH]);// 这个函数 使得 数组a所有正元素+1   在chiguozi函数中被调用
void fs();							//分数统计
void zhangaiwu(int a[HEIGHT][WIDTH]);// 障碍物出现函数 调整全局变量j
void daojishi();//倒计时函数
int ryj();// 任意键继续
void pachong(int a[HEIGHT][WIDTH]) ; //仓鼠
//以下是图片名称的全局定义
IMAGE img1,img2,img3, img4;//蛇头 有4个方向
IMAGE imgpt, imgpg, imgpt2, imgpg2;//   苹果     葡萄(障碍物)   (小图标)
IMAGE imgfm;// 封面
IMAGE imgshesheng,imgshesheng2, imgshewei,imgshewei2,imgfmpt1, imgfmpg1, imgshu;// 蛇身, 蛇尾, 封面的葡萄, 封面的苹果, 树(墙壁)
IMAGE imgdjs1, imgdjs2, imgdjs3;// 倒计时的图片
IMAGE imgzt, imgzt_, imgsmaixin, imgmon,imgmon2;// 暂停图片 (包括精灵图 掩码图) 生命爱心   (小图标)   小仓鼠两张图片轮番显示 ("gif效果" 也是小图标)
IMAGE imgjiasu, imgjiansu; 
int main()
{	
	initgraph(1300, 700);
	hello();	//输出背景音乐 和 封面图片 还有游戏说明
l://		goto句型
	Start(a);
	while (g1==1 &&g2>=1 &&g3==1 && g5==1)//    g2是葡萄吃一个 生命减少
	{
        Interact();// 键盘
		Game(a);   //尽量多次使用Game函数 保证移动方向 和判定方向的一致性
        Loop(a);	//贪吃蛇的移动
        Show(a);    //显示
		Interact();	// dir 贪吃蛇的移动方向的修改
		Game(a);	//
	}
	bye();// 封底  输出最后的分数 如果玩家按下j键 归零  g4   使游戏彻底结束
	if(g4==0) 
		return 0;	// 程序终止
	goto l;
	
}
void Show(int a[HEIGHT][WIDTH])
{
	int i, j;
	for (i=1; i<HEIGHT-1; i++)			//   外围有一层树 
		for (j=1; j<WIDTH-1; j++)		//	所以不用遍历最外层的二维数组元素
		{							// 在整个二维数组中   元素1表示蛇头  元素2表示最靠近蛇头的那一节蛇身 
			if(a[i][j]==max)		//元素3表示第二靠近蛇头的蛇身  
			{						 //max表示蛇身长度 会在吃了(苹果 爱心 葡萄) 后加1  
				putimage(j * ITEMSIZE , i * ITEMSIZE , &imgshewei2);				// 元素max 表示蛇尾的长度
				continue;
			}
			else if (a[i][j]==max-1)// 最靠近蛇尾的一节蛇身 也是单独输出
			{
				putimage(j * ITEMSIZE , i * ITEMSIZE , &imgshewei);
				continue;
			}
			else
				switch(a[i][j])
			{
			case -3:
				if(mon==0)
					putimage(j * ITEMSIZE , i * ITEMSIZE , &imgpt);	//葡萄//障碍物(小图标)
				else
					putimage(j * ITEMSIZE , i * ITEMSIZE , &imgpt2);
				break;
			case 0:	
				setfillcolor(RGB(255,255,255));	  //这是背景 利用bar函数 输出一个又一个的棕色方格 
				bar(j * ITEMSIZE , i * ITEMSIZE , (j + 1) * ITEMSIZE - 1, (i + 1) * ITEMSIZE - 1);					
				break;//留白
			case -6:	
				putimage(j * ITEMSIZE , i * ITEMSIZE , &imgjiasu);					
				break;
			case -7:
				putimage(j * ITEMSIZE , i * ITEMSIZE , &imgjiansu);					
				break;
			case -5:
				if(mon==10)  // -5表示的是小仓鼠 为了生动形象 两图片交替输出
					putimage(j * ITEMSIZE , i * ITEMSIZE , &imgmon), mon=0;
				else
					putimage(j * ITEMSIZE , i * ITEMSIZE , &imgmon2),mon++;	
				break;
			case 1:	
				it=i, jt=j;// 蛇头
				switch(dir)// 1是向右 2是向左  3是向上 4是向下//蛇头
				{
				case 1:putimage(j * ITEMSIZE , i * ITEMSIZE , &img1); break;// 输出图片蛇头向右
				case 2:putimage(j * ITEMSIZE , i * ITEMSIZE , &img2); break;//			     左
				case 3:putimage(j * ITEMSIZE , i * ITEMSIZE , &img3); break;//				 上
				case 4:putimage(j * ITEMSIZE , i * ITEMSIZE , &img4); break;//				 下
				}
				break;
				case -1:
					if(mon==1)
						putimage(j * ITEMSIZE , i * ITEMSIZE , &imgpg);	// 苹果(小图标)		
					else
						putimage(j * ITEMSIZE , i * ITEMSIZE , &imgpg2);	// 苹果(小图标)	
					break;//果子
				case -4:// -4是生命爱心小图标
					putimage(j * ITEMSIZE , i * ITEMSIZE , &imgsmaixin);
					break;
				default:  //  蛇身(小图标)有一大一小两种 
					if(a[i][j]%2==0)// 代表蛇身的数组元素如果是偶数 输出大的
						putimage(j * ITEMSIZE , i * ITEMSIZE , &imgshesheng);	
					else   //奇数 输出小的
						putimage(j * ITEMSIZE , i * ITEMSIZE , &imgshesheng2);
					break;
			}
			
		}
}
void Start(int a[HEIGHT][WIDTH])
{
	ztsd=ztsdinit;
	max=sheshengdechangdu;// max为蛇身长度
	setbkcolor(RGB(255,255,255));	// 设置背景色为棕色
	cleardevice();// 用背景色清空屏幕
	jiansubaodeshuliang=jiansubaomax;
	jiasubaodeshuliang=jiasubaomax;
	xiebaodeshuliang=xiebaomax;
	jiansu=jiansu_=jiasu_=jiasu=wudi_=wudi=mon=z=k=sc=sc_=0;// mon控制小仓鼠"GIF闪烁"  z  k控制 果子  障碍物  分数 归零
	g4=g5=imax = jmax = g1 = g3 =1;//代表生命的全局变量 g imax 为蛇尾的横坐标 jmax为蛇尾的纵坐标
	ip=HEIGHT-2;//小仓鼠的横坐标
	jp=WIDTH-2;//小仓鼠的纵坐标
	g2_= g2 = bloodmax;// 生命值 我为什么要设置两个生命值 原理和两个分数是一样的 也会在fs函数中具体说明
	dir=1;	//全局变量dir表示 贪吃蛇的移动方向 1是向右 2是向左  3是向上 4是向下
	int i,j;
	for (i=1; i<HEIGHT-1;i++)
		for(j=1; j<WIDTH-1; j++)
			a[i][j]=0;
		for (i=0; i<WIDTH; i++)   //令代表上方 墙壁 与 下方 墙壁的数组元素为-2   //为了以后的判定 (Game)
			a[0][i]=a[HEIGHT-1][i]=-2;
		for (i=1; i<HEIGHT-1; i++)// 令代表左方 墙壁 与 右方 墙壁的数组元素为-2
			a[i][0]=a[i][WIDTH-1]=-2;
		for (i=4; i<=10; i++)// 蛇身与蛇头的初始化
			a[3][i]=11-i;
		for (j=0; j<WIDTH; j++)	//这是墙的上下	//由于easyx与win32平台不同 墙壁(在游戏界面中体现为树)只需要显示一次
			putimage(j * ITEMSIZE , 0 , &imgshu),putimage(j * ITEMSIZE ,(HEIGHT-1) *ITEMSIZE , &imgshu);
		for (i=1; i<HEIGHT -1; i++)//这是墙的左右   图片的输出
			putimage(0 , i * ITEMSIZE , &imgshu),putimage((WIDTH-1) *ITEMSIZE  ,i * ITEMSIZE , &imgshu);
		a[ip][jp]=-5; // -5 表示 小仓鼠
		outtextxy(550, 680, s1); //   游戏界面的底端  输出文字  "分数:"
		sprintf(s2, "%d", sc);      //整数0 转为 字符0
		outtextxy(600, 680, s2);     //输出 字符0
		outtextxy(800, 680, shengmingwenzi);//游戏界面的底端	输出文字"生命:"
		sprintf(shengmingshuzi, "%d", g2);// 生命文字 从整数 转为 字符串
		outtextxy(850, 680, shengmingshuzi);//输出具体的生命值(数字) 不是生命条
		outtextxy(0, 680, s3);
		int n;
		for(n=0; n<bloodmax; n++)
			putimage(900 +n*30, 680, &imgsmaixin);  // 这是生命条  显示为 一排爱心(小图标)
		Show(a);   //显示函数   除了墙壁树  其他的图片都在这个函数执行的时候 输出
		daojishi();// 倒计时函数  3 2 1 开始了
}
void Loop(int a[HEIGHT][WIDTH])
{
	
	int break1=0, break2=1;
	jiansubao(a);//减速包的随机出现
	jiasubao(a);//空投加速包的随机出现
	xiebao(a);// 血包的随机出现
	zhangaiwu(a);// 障碍物的随机出现
	Sleep(ztsd);	// 延时
	guozi(a);	// 苹果的随机出现
    int i,j;
    for (i=1; i<HEIGHT-1 && break1<max; i++)// 接下来的数组遍历 在于调控 贪吃蛇的移动
		for (j=1; j<WIDTH-1&& break1<max; j++)// 具体贪吃蛇移动 代码的备注上说不清楚 会在ppt上解释
            if(a[i][j]>0)
			{
				a[i][j]++;
				if(a[imax][jmax]<a[i][j])
					imax=i,jmax=j;
				break1++;
			}
			a[imax][jmax]=0;//使所有非零变量 +1 并且找出最大元素归零
			for (i=1; i<HEIGHT-1 &&break2==1; i++)
				for (j=1; j<WIDTH-1&&break2==1; j++)
					if(a[i][j]==2)
					{
						switch(dir)
						{//dir是方向 1是向右 2是向左  3是向上 4是向下
						case 1:				// 在图片中显示为最靠近蛇头的一节蛇身的右方为蛇头
							a[i][j+1]=1;break;//贪吃蛇向右 就把2号元素的右边元素赋值为1
						case 2:
							a[i][j-1]=1;break;//贪吃蛇向左 就把2号元素的左边元素赋值为1
						case 3:
							a[i-1][j]=1;break;//贪吃蛇向上 就把2号元素的上边元素赋值为1
						case 4:
							a[i+1][j]=1;break;//贪吃蛇向下 就把2号元素的下边元素赋值为1
						}
						
						break2--;
					}
					
					pachong(a); //小仓鼠的移动
					if(wudi!=0)
						wudi--;
					if(jiasu!=0)
						jiasu--;
					if(jiansu!=0)
						jiansu--;
}
void Interact()//按键函数
{
	if(kbhit())
		switch(getch())//dir是方向 1是向右 2是向左  3是向上 4是向下
	{
			case'a':
				if(dir==3 ||dir==4)//再次对	全局变量dir 进行判定  dir原本为3,4时才可以变为2
					dir=2;break;//也就是说  蛇头朝上或朝下时才可以往左
			case'w':
				if(dir==1 ||dir==2)//蛇头朝左或朝右时才可以往下
					dir=3;break;
			case'd':
				if(dir==3 ||dir==4)//同上
					dir=1;break;
			case's':
				if(dir==1 ||dir==2)//同上
					dir=4;break;
			case'p':// 暂停
				putimage(435, 175, &imgzt_, NOTSRCERASE);
				putimage(435, 175, &imgzt, SRCINVERT);
				ryj();
				break;
	}
	MOUSEMSG m; 
	while(MouseHit())
	{
		m=GetMouseMsg();//获取一条鼠标消息
		if(m.uMsg==WM_LBUTTONDOWN )//如果按下鼠标左键//dir是方向 1是向右 2是向左  3是向上 4是向下
		{
			if  (m.x>=0 && m.x<= WIDTH*20 && m.y>=0 && m.y<=HEIGHT*20)
			{
				if 	(dir==1 || dir==2) 
				{
					if(m.y<(it*20+9))
						dir=3;
					else if(m.y>(it*20+9))
						dir=4;
				}
				else if(dir==3 || dir==4)
				{
					if(m.x>(jt*20+9))
						dir=1;
					else if (m.x<(jt*20+9))
						dir=2;
				}
				
			}
			else if(m.x>=0 && m.x<=80 && m.y>=680 && m.y<=700 )// 暂停
			{
				putimage(435, 175, &imgzt_, NOTSRCERASE);
				putimage(435, 175, &imgzt, SRCINVERT);
				ryj();
			}
		}
	}
}
void xiebao(int a[HEIGHT][WIDTH])//血包出现函数
{
    int i,j;
	if (xiebaodeshuliang==xiebaomax)
    {
		i=(int)rand()%(HEIGHT-6)+3;
		j=(int)rand()%(WIDTH-6)+3;
		if(a[i][j]==0)
			a[i][j]=-4;
		xiebaodeshuliang=0;
    }
	else
		xiebaodeshuliang++;
}
void jiasubao(int a[HEIGHT][WIDTH])//闪电包出现函数
{
    int i,j;
	if (jiasubaodeshuliang==jiasubaomax)
    {
		i=(int)rand()%(HEIGHT-6)+3;
		j=(int)rand()%(WIDTH-6)+3;
		if(a[i][j]==0)
			a[i][j]=-6;
		jiasubaodeshuliang=0;
    }
	else
		jiasubaodeshuliang++;
}
void jiansubao(int a[HEIGHT][WIDTH])//闪电包出现函数
{
    int i,j;
	if (jiansubaodeshuliang==jiansubaomax)
    {
		i=(int)rand()%(HEIGHT-6)+3;
		j=(int)rand()%(WIDTH-6)+3;
		if(a[i][j]==0)
			a[i][j]=-7;
		jiansubaodeshuliang=0;
    }
	else
		jiansubaodeshuliang++;
}
void guozi(int a[HEIGHT][WIDTH])//果子出现函数
{
    int i,j;
    if( k<guozimax && k >=0)
    {
		i=(int)rand()%(HEIGHT-6)+3;
		j=(int)rand()%(WIDTH-6)+3;
		if(a[i][j]==0)// 
			a[i][j]=-1;
		else
			k--;
		k++;		//k==4 表示 还没吃果子
    }
}
void zhangaiwu(int a[HEIGHT][WIDTH])//表示障碍物出现的函数 吃一个果子 出一个障碍物
{
	int i,j;
	if( z<=3 && z >=0)
	{
		i=(int)rand()%(HEIGHT-6)+3;
		j=(int)rand()%(WIDTH-6)+3;
		if(a[i][j]==0)
			a[i][j]=-3;
		z++;        //z==4时  表示  还没吃果子 就不会增加葡萄
    }
}
void Game(int a[HEIGHT][WIDTH])
{
    int i,j, break2=1;
    for (i=1; i<HEIGHT-1&&break2==1; i++)  //由于 win32 与easyx 不同       树(墙壁)不用判定了
		for (j=1; j<WIDTH-1&&break2==1; j++)
			if(a[i][j]==1)
			{
				switch(dir)
				{
				case 1://dir是方向 1是向右 2是向左  3是向上 4是向下
					switch(a[i][j+1])
					{
					case 0:
						break;
					case -1:
						sc++,chiguozi2(a),a[i][j+1]=1,k--,z--;  //	在,k-- 原因在于减少 k 使得 再次随机出现果子
						break;
					case-3: 					//-3是葡萄(障碍物)
						chiguozi2(a),a[i][j+1]=1;
						if(wudi==0)
							g2--;		// g2减少 
						break;
					case-4:						//-4是爱心 
						sc+=2,chiguozi2(a),a[i][j+1]=1,wudi=wuditime, g2++;	//吃了爱心加两分
						break;
					case-6:						//-6是空投加速包
						sc+=2,chiguozi2(a),a[i][j+1]=1,jiasu=jiasutime,jiansu=0;	//吃了爱心加两分
						break;
					case-7:						//-6是空投加速包
						sc+=2,chiguozi2(a),a[i][j+1]=1,jiansu=jiansutime,jiasu=0;
						break;
					case-2:						//-2是树(墙壁)
						chiguozi2(a),a[i][j+1]=1,g1--;			// 归零g1
						break;
					default:						//>=2是蛇身
						chiguozi2(a),a[i][j+1]=1,g3--;			// 归零g3
						break;
					}
					break;
					case 2:
						switch(a[i][j-1])
						{
						case 0:
							break;
						case-1:
							sc++,chiguozi2(a),a[i][j-1]=1,k--,z--;   // sc++原因在于 加分
							break;
						case-3:
							chiguozi2(a),a[i][j-1]=1;
							if(wudi==0)
								g2--;
							break;
						case-4:
							sc+=2,chiguozi2(a),a[i][j-1]=1, wudi=wuditime, g2++; 
							break;
						case-6:
							sc+=2,chiguozi2(a),a[i][j-1]=1, jiasu=jiasutime,jiansu=0; 
							break;
						case-7:
							sc+=2,chiguozi2(a),a[i][j-1]=1, jiansu=jiansutime, jiasu=0;
							break;
						case-2:
							chiguozi2(a),a[i][j-1]=1,g1--;
							break;
						default:
							chiguozi2(a),a[i][j-1]=1,g3--;
							break;
						}
						break;
						case 3:
							switch(a[i-1][j])
							{
							case 0:
								break;
							case-1:
								sc++,chiguozi2(a),a[i-1][j]=1,k--,z--;
								break;
							case-3:
								chiguozi2(a),a[i-1][j]=1;
								if(wudi==0)
									g2--;
								break;
							case-4:
								sc+=2,chiguozi2(a),a[i-1][j]=1,wudi=wuditime, g2++; 
								break;
							case-6:
								sc+=2,chiguozi2(a),a[i-1][j]=1,jiasu=jiasutime,jiansu=0; 
								break;
							case-7:
								sc+=2,chiguozi2(a),a[i-1][j]=1,jiansu=jiansutime,jiasu=0; 
								break;
							case-2:
								chiguozi2(a),a[i-1][j]=1,g1--;
								break;
							default:
								chiguozi2(a),a[i-1][j]=1,g3--;
								break;
							}
							break;
							case 4:
								switch(a[i+1][j])
								{
								case 0:
									break;
								case-1:
									sc++,chiguozi2(a),a[i+1][j]=1,k--,z--;
									break;
								case-3:
									chiguozi2(a),a[i+1][j]=1;
									if(wudi==0)
										g2--;
									break;
									
								case-4:
									sc+=2,chiguozi2(a),a[i+1][j]=1, wudi=wuditime,g2++; 
									break;
								case-6:
									sc+=2,chiguozi2(a),a[i+1][j]=1, jiasu=jiasutime,jiansu=0; 
									break;
								case-7:
									sc+=2,chiguozi2(a),a[i+1][j]=1, jiansu=jiasutime,jiasu=0; 
									break;
								case-2:
									chiguozi2(a),a[i+1][j]=1,g1--;
									break;
								default:
									chiguozi2(a),a[i+1][j]=1,g3--;
									break;
								}
								break;
				}
				break2--;	
			}
			if(a[ip+1][jp+1]>0 ||a[ip-1][jp-1]>0 ||a[ip+1][jp-1]>0 ||a[ip-1][jp+1]>0 ||a[ip+1][jp+1]>0 ||a[ip-1][jp-1]>0 ||a[ip+1][jp-1]>0 ||a[ip-1][jp+1]>0)
				g5--;
			else if(a[ip][jp+1]>0 || a[ip+1][jp]>0 || a[ip-1][jp]>0 ||a[ip][jp-1]>0)
				g5--;
			fs();		//显示分数
}
void chiguozi2(int a[HEIGHT][WIDTH])// 这个函数的功能是 遍历数组 使非零元素加1(当然 不要墙壁) 在吃爱心吃葡萄吃苹果 时执行该函数
{
    int i,j, break1=0;
    for (i=1; i<HEIGHT-1&& break1<max; i++)
		for (j=1; j<WIDTH-1&& break1<max; j++)
            if(a[i][j]>0)
				break1++,a[i][j]++;
			max++;
}
void hello()	//以下是封面
{
	// 获取窗口句柄
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, "贪吃蛇-带你走进别样的世界");// 设置窗口标题文字
	initimg();// 图片的初始化	//一些图片的载入
	mciSendString("open \"res\\bm.mp3\" alias mymusic", NULL, 0, NULL);//背景音乐
	mciSendString("play mymusic repeat", NULL, 0, NULL);
	inittext();// 显示文字 的格式 的初始化
	setbkcolor(RGB(255,255,255));	// 设置背景色为棕色
	cleardevice();// 用背景色清空屏幕
	putimage(250, 0, &imgfm);//封面输出
	putimage(0, 0, &imgfmpg1);
	putimage(1000, 350, &imgfmpt1);
	settextcolor(BLACK);
	TCHAR hello1[] = _T("         大家好!");
	TCHAR hello2[] = _T("  欢迎来到贪吃蛇的世界!");
	TCHAR hello3[] = _T("    这个游戏版本很有趣");
	TCHAR hello4[] = _T("   wasd键或鼠标左键操作");
	TCHAR hello5[] = _T("   花是贪吃蛇的活动范围");
	TCHAR hello6[] = _T("  酸葡萄是障碍物, 要越过它");
	TCHAR hello7[] = _T("苹果吃了长长一截 爱心吃了加血");
	TCHAR hello8[] = _T("    小仓鼠会慢慢粘上你");
	TCHAR hello9[] = _T("在游戏过程中, 你可以按p键暂停");
	TCHAR hello10[]= _T("      请按任意键开始");
	outtextxy(500, 280, hello1);
	outtextxy(500, 300, hello2);
	outtextxy(500, 320, hello3);
	outtextxy(500, 340, hello4);
	outtextxy(500, 360, hello5);
	outtextxy(500, 380, hello6);
	outtextxy(500, 400, hello7);
	outtextxy(500, 420, hello8);
	outtextxy(500, 440, hello9);
	outtextxy(500, 460, hello10);
	ryj();	
}
void bye()
{
	ryj();
	setbkcolor(RGB(255,255,255));	// 设置背景色为白色
	cleardevice();// 用背景色清空屏幕
	putimage(250, 0, &imgfm);
	putimage(0, 0, &imgfmpg1);
	putimage(1000, 350, &imgfmpt1);
	settextcolor(BLACK);// 汉字颜色
	TCHAR bye1[] = _T("请按任意键重新开始   j键结束");
	TCHAR bye2[] = _T("你的分数为:");
	outtextxy(500, 400, bye1);
	outtextxy(500, 360, bye2);
	sprintf(s2, "%d", sc);
	outtextxy(620, 360, s2);//分数
	ryj();
	
}
void fs() //登记分数的函数 但是要把整形变量转化为字符串
{	
	
	if(sc!=sc_)// sc_是sc的替身 这样做的话 不用每一帧都输出分数 而是等到分数变化了在更新
		sc_=sc,sprintf(s2, "%d", sc_),outtextxy(600, 680, s2);//我这么做 避免蛇每次移动都要输出分数和生命
	if (g2<g2_)	
	{
		g2_=g2,sprintf(shengmingshuzi, "%d", g2),outtextxy(850, 680, shengmingshuzi);//生命数字的输出 
		bar(g2*30 +900, 680, g2*30 +920, 700);// 生命条的缩短 用bar函数 盖在爱心上
	}
	else if(g2>g2_)	
	{
		g2_=g2,sprintf(shengmingshuzi, "%d", g2),outtextxy(850, 680, shengmingshuzi);//生命数字
		putimage(g2*30 +870, 680, &imgsmaixin);// 生命条的伸长 用putimage函数 再输出一个爱心
	}
	if(wudi_!=wudi)
	{
		if(wudi==0)
			bar(200, 680, 240, 700);
		else
			outtextxy(200, 680, wudizfc);// 无敌字符串
		wudi_=wudi;
	}
	if (jiasu_!=jiasu)
	{
		if(jiasu==0)
			bar(260, 680, 300, 700), ztsd=ztsdinit;
		else
			outtextxy(260, 680, jiasuzfc), ztsd=jiasuhousd;
		jiasu_=jiasu;
	}
	if (jiansu_!=jiansu)
	{
		if(jiansu==0)
			bar(300, 680, 340, 700), ztsd=ztsdinit;
		else
			outtextxy(300, 680, jiansuzfc), ztsd=jiansuhousd;
		jiansu_=jiansu;
		
	}
	if(g1!=1)
		outtextxy(500, 300, sorry1);// 告诉玩家 贪吃蛇撞树上了
	if(g2<1)
		outtextxy(480, 300, sorry2);// 告诉玩家 贪吃蛇吃了太多的酸葡萄 
	if(g3!=1)
		outtextxy(500, 300, sorry3);// 告诉玩家 贪吃蛇撞到自己了
	if(g5<1)
		outtextxy(500, 300, sorry4);// 告诉玩家 贪吃蛇撞到小仓鼠了
}
void initimg()// 图片的初始化
{
	loadimage(&img1,_T("res\\1.gif"));//蛇头1是向右 2是向左  3是向上 4是向下
	loadimage(&img2,_T("res\\2.gif"));
	loadimage(&img3,_T("res\\3.gif"));
	loadimage(&img4,_T("res\\4.gif"));
	loadimage(&imgpt,_T("res\\pt.gif"));//葡萄
	loadimage(&imgpt2,_T("res\\pt2.gif"));//葡萄
	loadimage(&imgpg,_T("res\\pg.gif"));//苹果
	loadimage(&imgpg2,_T("res\\pg2.gif"));//苹果
	loadimage(&imgfm,_T("res\\fm.gif"));// 大封面
	loadimage(&imgshu,_T("res\\shu.gif"));//树 障碍物
	loadimage(&imgshesheng,_T("res\\shesheng.gif"));//蛇身
	loadimage(&imgshesheng2,_T("res\\shesheng2.gif"));//小蛇身
	loadimage(&imgfmpg1,_T("res\\fmpg1.gif"));//封面苹果
	loadimage(&imgfmpt1,_T("res\\fmpt1.gif"));//封面葡萄
	loadimage(&imgdjs1,_T("res\\djs1.gif"));//倒计时
	loadimage(&imgdjs2,_T("res\\djs2.gif"));//倒计时
	loadimage(&imgdjs3,_T("res\\djs3.gif"));//倒计时
	loadimage(&imgzt,_T("res\\zt.gif"));	//暂停精灵图
	loadimage(&imgzt_,_T("res\\zt_.gif"));	//暂停掩码图
	loadimage(&imgsmaixin,_T("res\\smaixin.gif"));//生命爱心
	loadimage(&imgmon,_T("res\\mon.gif"));		//小仓鼠
	loadimage(&imgmon2,_T("res\\mon2.gif"));	//小仓鼠
	loadimage(&imgshewei,_T("res\\shewei.gif"));//蛇尾
	loadimage(&imgshewei2,_T("res\\shewei2.gif"));//蛇尾
	loadimage(&imgjiasu, _T("res\\jiasu.gif"));//加速的空投
	loadimage(&imgjiansu, _T("res\\jiansu.gif"));//减速小人头像

	
	
}
void inittext()// 文字格式的初始设置
{
	LOGFONT f;
	gettextstyle(&f);                     // 获取当前字体设置
	f.lfHeight = 20;						// 设置字体高度为 20
	f.lfWeight = 1000;						//设置字体粗细
	_tcscpy(f.lfFaceName, _T("幼圆"));    // 设置字体为“黑体”(高版本 VC 推荐使用 _tcscpy_s 函数)
	f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
	settextstyle(&f);// 设置字体样式
}
void daojishi()// 倒计时函数 
{
	putimage(435, 175, &imgdjs3);//   3
	Sleep(1000);
	putimage(435, 175, &imgdjs2);//   2
	Sleep(1000);
	putimage(435, 175, &imgdjs1);//   1
	Sleep(1000);// 接下来游戏开始了
}
int ryj()// 任意键继续(为什么不用getch()呢 因为鼠标也是任意键 )
{
	g4=1;
	MOUSEMSG m; 
	while (1)
	{	
		if (kbhit())
		{
			if(getch()=='j')
				g4=0;
			return 0;
		}
		while(MouseHit())
		{
			m=GetMouseMsg();//获取一条鼠标消息
			if(m.uMsg==WM_LBUTTONDOWN)//如果按下鼠标左键。
				return 0;
		}
	}
}
void pachong(int a[HEIGHT][WIDTH])  //仓鼠判定函数
{
	static int pachongsudu=0;
	if (pachongsudu==5)
    {
		a[ip][jp]=0; //仓鼠所在的二维数组元素归零 Show函数中显示为背景
		if     (imax<ip && jmax<jp && a[ip-1][jp-1]!=-1)// 表示   仓鼠的左上方有蛇尾  而且 最近的左上格不是苹果
			ip--,jp--;
		else if(imax>ip && jmax<jp && a[ip+1][jp-1]!=-1)// 表示   仓鼠的右上方有蛇尾  而且 最近的右上格不是苹果
			ip++,jp--;
		else if(imax>ip && jmax>jp && a[ip+1][jp+1]!=-1)// 表示   仓鼠的右下方有蛇尾  而且 最近的右下格不是苹果
			ip++,jp++;
		else if(imax<ip && jmax>jp && a[ip-1][jp+1]!=-1)// 表示   仓鼠的左下方有蛇尾  而且 最近的左下格不是苹果
			ip--,jp++;
		a[ip][jp]=-5;// 仓鼠移动后所在的二维数组元素赋值为-5 Show函数中显示为仓鼠
		pachongsudu=0;// 为了仓鼠不要移动的太快 归零pachongsudu 下次的话 ++10次再动
    }
	else
		pachongsudu++;
}