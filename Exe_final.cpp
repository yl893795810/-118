#include <graphics.h>   
#include <conio.h>
#include <time.h>
#include <WINDOWS.H>
#include <queue>
#include <stdlib.h>
#include <stdio.h>
#pragma comment(lib,"Winmm.lib")
#define guozimax 4
#define wuditime 100  //�޵�ʱ��
#define jiasutime 50 //����ʱ��
#define jiansutime 20//����ʱ��
#define	WIDTH		65			// ��Ϸ����������
#define	HEIGHT		34			// ��Ϸ��������߶�
#define	ITEMSIZE	20			// ��ϷԪ�ش�С
#define bloodmax 6				// ��ʼʱ��Ѫ��
#define sheshengdechangdu 7		// ��ʼʱ����ĳ���
#define ztsdinit 50				//��ʼʱ�����ٶ�//��ʱ
#define xiebaomax 100			//Ѫ������Ƶ��
#define jiasubaomax 100			//��Ͷ���ٰ�����Ƶ��
#define jiansubaomax 100		//���ٰ�����Ƶ��
#define jiasuhousd 10		//���ٺ��ٶ�//��ʱ
#define jiansuhousd 200		//���ٺ��ٶ�//��ʱ
int a[HEIGHT][WIDTH]={0},dir=1;// dir �� ����  1������ 2������  3������ 4������
int k=0, z=0, mon=0;//k�� ���� ���ӳ�������   ��guozi������ʹ�� z�ǿ����ϰ������� ��zhangaiwu������ʹ�� mon�ǿ���С����"gif"��˸
int sc=0, sc_=0; //sc �Ƿ���   �ڻ��������·� ������ʾ    ��󱨸����  ��ΪʲôҪ������sc�� ��fs�����л����˵�� 
int wudi=0, wudi_=0;    
int jiasu=0, jiasu_=0;
int jiansu=0, jiansu_=0;
int ztsd=100; 
int jiansubaodeshuliang=jiansubaomax;
int jiasubaodeshuliang=jiasubaomax;
int xiebaodeshuliang=xiebaomax;
int g1=1 , g2=1, g3=1, g4=1,g5, g2_=1,imax,jmax, ip, jp, max, it, jt;	// 	g1 g2 g3 g5 ������Ϸ����	//��Ϸ��ʼʱ ��Start()���������¸�ֵ								
TCHAR s2[4]= _T("0"),s1[] = _T("����:"), shengmingwenzi[]=_T("����:"), shengmingshuzi[2]=_T("0");// ȫ�� �ַ���
TCHAR sorry1[] = _T("��ŷ! ̰����ײ��������, �밴���������");
TCHAR sorry2[] = _T("��ŷ! ̰���߳���̫���������, �밴���������");
TCHAR sorry3[] = _T("��ŷ! ̰����ײ�Լ�������, �밴���������");
TCHAR sorry4[] = _T("��ŷ! ̰���߱�С����ҧ��, �밴���������");
TCHAR s3[] = _T("�����ͣ");
TCHAR wudizfc[] = _T("�޵�");
TCHAR jiasuzfc[] = _T("����");
TCHAR jiansuzfc[] = _T("����");
//�����Ǻ�������
void jiansubao(int a[HEIGHT][WIDTH]);
void jiasubao(int a[HEIGHT][WIDTH]);
void inittext();// ���ָ�ʽ��ʼ��
void initimg();// ͼƬ�ĳ�ʼ������
void Show(int a[HEIGHT][WIDTH]);//������ʾ���� ���� ��ά����a�е� ����ֵ ���ͼƬ
void Start(int a[HEIGHT][WIDTH]);// ��ʼ��
void Loop(int a[HEIGHT][WIDTH]);// �ƶ�����
void hello();   // ��ʼ���溯��
void bye();		//�������溯��
void Interact();	//	��������   �ؼ����� ȫ�ֱ���dir 1������ 2������  3������ 4������
void guozi(int a[HEIGHT][WIDTH]);// ���ӳ��ֺ��� ����ȫ�ֱ���k
void xiebao(int a[HEIGHT][WIDTH]); //Ѫ�����ֺ��� 
void Game(int a[HEIGHT][WIDTH]); // Ҳ�ɽ�	ײǽ�Թ� ����
void chiguozi2(int a[HEIGHT][WIDTH]);// ������� ʹ�� ����a������Ԫ��+1   ��chiguozi�����б�����
void fs();							//����ͳ��
void zhangaiwu(int a[HEIGHT][WIDTH]);// �ϰ�����ֺ��� ����ȫ�ֱ���j
void daojishi();//����ʱ����
int ryj();// ���������
void pachong(int a[HEIGHT][WIDTH]) ; //����
//������ͼƬ���Ƶ�ȫ�ֶ���
IMAGE img1,img2,img3, img4;//��ͷ ��4������
IMAGE imgpt, imgpg, imgpt2, imgpg2;//   ƻ��     ����(�ϰ���)   (Сͼ��)
IMAGE imgfm;// ����
IMAGE imgshesheng,imgshesheng2, imgshewei,imgshewei2,imgfmpt1, imgfmpg1, imgshu;// ����, ��β, ���������, �����ƻ��, ��(ǽ��)
IMAGE imgdjs1, imgdjs2, imgdjs3;// ����ʱ��ͼƬ
IMAGE imgzt, imgzt_, imgsmaixin, imgmon,imgmon2;// ��ͣͼƬ (��������ͼ ����ͼ) ��������   (Сͼ��)   С��������ͼƬ�ַ���ʾ ("gifЧ��" Ҳ��Сͼ��)
IMAGE imgjiasu, imgjiansu; 
int main()
{	
	initgraph(1300, 700);
	hello();	//����������� �� ����ͼƬ ������Ϸ˵��
l://		goto����
	Start(a);
	while (g1==1 &&g2>=1 &&g3==1 && g5==1)//    g2�����ѳ�һ�� ��������
	{
        Interact();// ����
		Game(a);   //�������ʹ��Game���� ��֤�ƶ����� ���ж������һ����
        Loop(a);	//̰���ߵ��ƶ�
        Show(a);    //��ʾ
		Interact();	// dir ̰���ߵ��ƶ�������޸�
		Game(a);	//
	}
	bye();// ���  ������ķ��� �����Ұ���j�� ����  g4   ʹ��Ϸ���׽���
	if(g4==0) 
		return 0;	// ������ֹ
	goto l;
	
}
void Show(int a[HEIGHT][WIDTH])
{
	int i, j;
	for (i=1; i<HEIGHT-1; i++)			//   ��Χ��һ���� 
		for (j=1; j<WIDTH-1; j++)		//	���Բ��ñ��������Ķ�ά����Ԫ��
		{							// ��������ά������   Ԫ��1��ʾ��ͷ  Ԫ��2��ʾ�����ͷ����һ������ 
			if(a[i][j]==max)		//Ԫ��3��ʾ�ڶ�������ͷ������  
			{						 //max��ʾ������ ���ڳ���(ƻ�� ���� ����) ���1  
				putimage(j * ITEMSIZE , i * ITEMSIZE , &imgshewei2);				// Ԫ��max ��ʾ��β�ĳ���
				continue;
			}
			else if (a[i][j]==max-1)// �����β��һ������ Ҳ�ǵ������
			{
				putimage(j * ITEMSIZE , i * ITEMSIZE , &imgshewei);
				continue;
			}
			else
				switch(a[i][j])
			{
			case -3:
				if(mon==0)
					putimage(j * ITEMSIZE , i * ITEMSIZE , &imgpt);	//����//�ϰ���(Сͼ��)
				else
					putimage(j * ITEMSIZE , i * ITEMSIZE , &imgpt2);
				break;
			case 0:	
				setfillcolor(RGB(255,255,255));	  //���Ǳ��� ����bar���� ���һ����һ������ɫ���� 
				bar(j * ITEMSIZE , i * ITEMSIZE , (j + 1) * ITEMSIZE - 1, (i + 1) * ITEMSIZE - 1);					
				break;//����
			case -6:	
				putimage(j * ITEMSIZE , i * ITEMSIZE , &imgjiasu);					
				break;
			case -7:
				putimage(j * ITEMSIZE , i * ITEMSIZE , &imgjiansu);					
				break;
			case -5:
				if(mon==10)  // -5��ʾ����С���� Ϊ���������� ��ͼƬ�������
					putimage(j * ITEMSIZE , i * ITEMSIZE , &imgmon), mon=0;
				else
					putimage(j * ITEMSIZE , i * ITEMSIZE , &imgmon2),mon++;	
				break;
			case 1:	
				it=i, jt=j;// ��ͷ
				switch(dir)// 1������ 2������  3������ 4������//��ͷ
				{
				case 1:putimage(j * ITEMSIZE , i * ITEMSIZE , &img1); break;// ���ͼƬ��ͷ����
				case 2:putimage(j * ITEMSIZE , i * ITEMSIZE , &img2); break;//			     ��
				case 3:putimage(j * ITEMSIZE , i * ITEMSIZE , &img3); break;//				 ��
				case 4:putimage(j * ITEMSIZE , i * ITEMSIZE , &img4); break;//				 ��
				}
				break;
				case -1:
					if(mon==1)
						putimage(j * ITEMSIZE , i * ITEMSIZE , &imgpg);	// ƻ��(Сͼ��)		
					else
						putimage(j * ITEMSIZE , i * ITEMSIZE , &imgpg2);	// ƻ��(Сͼ��)	
					break;//����
				case -4:// -4����������Сͼ��
					putimage(j * ITEMSIZE , i * ITEMSIZE , &imgsmaixin);
					break;
				default:  //  ����(Сͼ��)��һ��һС���� 
					if(a[i][j]%2==0)// �������������Ԫ�������ż�� ������
						putimage(j * ITEMSIZE , i * ITEMSIZE , &imgshesheng);	
					else   //���� ���С��
						putimage(j * ITEMSIZE , i * ITEMSIZE , &imgshesheng2);
					break;
			}
			
		}
}
void Start(int a[HEIGHT][WIDTH])
{
	ztsd=ztsdinit;
	max=sheshengdechangdu;// maxΪ������
	setbkcolor(RGB(255,255,255));	// ���ñ���ɫΪ��ɫ
	cleardevice();// �ñ���ɫ�����Ļ
	jiansubaodeshuliang=jiansubaomax;
	jiasubaodeshuliang=jiasubaomax;
	xiebaodeshuliang=xiebaomax;
	jiansu=jiansu_=jiasu_=jiasu=wudi_=wudi=mon=z=k=sc=sc_=0;// mon����С����"GIF��˸"  z  k���� ����  �ϰ���  ���� ����
	g4=g5=imax = jmax = g1 = g3 =1;//����������ȫ�ֱ��� g imax Ϊ��β�ĺ����� jmaxΪ��β��������
	ip=HEIGHT-2;//С����ĺ�����
	jp=WIDTH-2;//С�����������
	g2_= g2 = bloodmax;// ����ֵ ��ΪʲôҪ������������ֵ ԭ�������������һ���� Ҳ����fs�����о���˵��
	dir=1;	//ȫ�ֱ���dir��ʾ ̰���ߵ��ƶ����� 1������ 2������  3������ 4������
	int i,j;
	for (i=1; i<HEIGHT-1;i++)
		for(j=1; j<WIDTH-1; j++)
			a[i][j]=0;
		for (i=0; i<WIDTH; i++)   //������Ϸ� ǽ�� �� �·� ǽ�ڵ�����Ԫ��Ϊ-2   //Ϊ���Ժ���ж� (Game)
			a[0][i]=a[HEIGHT-1][i]=-2;
		for (i=1; i<HEIGHT-1; i++)// ������� ǽ�� �� �ҷ� ǽ�ڵ�����Ԫ��Ϊ-2
			a[i][0]=a[i][WIDTH-1]=-2;
		for (i=4; i<=10; i++)// ��������ͷ�ĳ�ʼ��
			a[3][i]=11-i;
		for (j=0; j<WIDTH; j++)	//����ǽ������	//����easyx��win32ƽ̨��ͬ ǽ��(����Ϸ����������Ϊ��)ֻ��Ҫ��ʾһ��
			putimage(j * ITEMSIZE , 0 , &imgshu),putimage(j * ITEMSIZE ,(HEIGHT-1) *ITEMSIZE , &imgshu);
		for (i=1; i<HEIGHT -1; i++)//����ǽ������   ͼƬ�����
			putimage(0 , i * ITEMSIZE , &imgshu),putimage((WIDTH-1) *ITEMSIZE  ,i * ITEMSIZE , &imgshu);
		a[ip][jp]=-5; // -5 ��ʾ С����
		outtextxy(550, 680, s1); //   ��Ϸ����ĵ׶�  �������  "����:"
		sprintf(s2, "%d", sc);      //����0 תΪ �ַ�0
		outtextxy(600, 680, s2);     //��� �ַ�0
		outtextxy(800, 680, shengmingwenzi);//��Ϸ����ĵ׶�	�������"����:"
		sprintf(shengmingshuzi, "%d", g2);// �������� ������ תΪ �ַ���
		outtextxy(850, 680, shengmingshuzi);//������������ֵ(����) ����������
		outtextxy(0, 680, s3);
		int n;
		for(n=0; n<bloodmax; n++)
			putimage(900 +n*30, 680, &imgsmaixin);  // ����������  ��ʾΪ һ�Ű���(Сͼ��)
		Show(a);   //��ʾ����   ����ǽ����  ������ͼƬ�����������ִ�е�ʱ�� ���
		daojishi();// ����ʱ����  3 2 1 ��ʼ��
}
void Loop(int a[HEIGHT][WIDTH])
{
	
	int break1=0, break2=1;
	jiansubao(a);//���ٰ����������
	jiasubao(a);//��Ͷ���ٰ����������
	xiebao(a);// Ѫ�����������
	zhangaiwu(a);// �ϰ�����������
	Sleep(ztsd);	// ��ʱ
	guozi(a);	// ƻ�����������
    int i,j;
    for (i=1; i<HEIGHT-1 && break1<max; i++)// ��������������� ���ڵ��� ̰���ߵ��ƶ�
		for (j=1; j<WIDTH-1&& break1<max; j++)// ����̰�����ƶ� ����ı�ע��˵����� ����ppt�Ͻ���
            if(a[i][j]>0)
			{
				a[i][j]++;
				if(a[imax][jmax]<a[i][j])
					imax=i,jmax=j;
				break1++;
			}
			a[imax][jmax]=0;//ʹ���з������ +1 �����ҳ����Ԫ�ع���
			for (i=1; i<HEIGHT-1 &&break2==1; i++)
				for (j=1; j<WIDTH-1&&break2==1; j++)
					if(a[i][j]==2)
					{
						switch(dir)
						{//dir�Ƿ��� 1������ 2������  3������ 4������
						case 1:				// ��ͼƬ����ʾΪ�����ͷ��һ��������ҷ�Ϊ��ͷ
							a[i][j+1]=1;break;//̰�������� �Ͱ�2��Ԫ�ص��ұ�Ԫ�ظ�ֵΪ1
						case 2:
							a[i][j-1]=1;break;//̰�������� �Ͱ�2��Ԫ�ص����Ԫ�ظ�ֵΪ1
						case 3:
							a[i-1][j]=1;break;//̰�������� �Ͱ�2��Ԫ�ص��ϱ�Ԫ�ظ�ֵΪ1
						case 4:
							a[i+1][j]=1;break;//̰�������� �Ͱ�2��Ԫ�ص��±�Ԫ�ظ�ֵΪ1
						}
						
						break2--;
					}
					
					pachong(a); //С������ƶ�
					if(wudi!=0)
						wudi--;
					if(jiasu!=0)
						jiasu--;
					if(jiansu!=0)
						jiansu--;
}
void Interact()//��������
{
	if(kbhit())
		switch(getch())//dir�Ƿ��� 1������ 2������  3������ 4������
	{
			case'a':
				if(dir==3 ||dir==4)//�ٴζ�	ȫ�ֱ���dir �����ж�  dirԭ��Ϊ3,4ʱ�ſ��Ա�Ϊ2
					dir=2;break;//Ҳ����˵  ��ͷ���ϻ���ʱ�ſ�������
			case'w':
				if(dir==1 ||dir==2)//��ͷ�������ʱ�ſ�������
					dir=3;break;
			case'd':
				if(dir==3 ||dir==4)//ͬ��
					dir=1;break;
			case's':
				if(dir==1 ||dir==2)//ͬ��
					dir=4;break;
			case'p':// ��ͣ
				putimage(435, 175, &imgzt_, NOTSRCERASE);
				putimage(435, 175, &imgzt, SRCINVERT);
				ryj();
				break;
	}
	MOUSEMSG m; 
	while(MouseHit())
	{
		m=GetMouseMsg();//��ȡһ�������Ϣ
		if(m.uMsg==WM_LBUTTONDOWN )//�������������//dir�Ƿ��� 1������ 2������  3������ 4������
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
			else if(m.x>=0 && m.x<=80 && m.y>=680 && m.y<=700 )// ��ͣ
			{
				putimage(435, 175, &imgzt_, NOTSRCERASE);
				putimage(435, 175, &imgzt, SRCINVERT);
				ryj();
			}
		}
	}
}
void xiebao(int a[HEIGHT][WIDTH])//Ѫ�����ֺ���
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
void jiasubao(int a[HEIGHT][WIDTH])//��������ֺ���
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
void jiansubao(int a[HEIGHT][WIDTH])//��������ֺ���
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
void guozi(int a[HEIGHT][WIDTH])//���ӳ��ֺ���
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
		k++;		//k==4 ��ʾ ��û�Թ���
    }
}
void zhangaiwu(int a[HEIGHT][WIDTH])//��ʾ�ϰ�����ֵĺ��� ��һ������ ��һ���ϰ���
{
	int i,j;
	if( z<=3 && z >=0)
	{
		i=(int)rand()%(HEIGHT-6)+3;
		j=(int)rand()%(WIDTH-6)+3;
		if(a[i][j]==0)
			a[i][j]=-3;
		z++;        //z==4ʱ  ��ʾ  ��û�Թ��� �Ͳ�����������
    }
}
void Game(int a[HEIGHT][WIDTH])
{
    int i,j, break2=1;
    for (i=1; i<HEIGHT-1&&break2==1; i++)  //���� win32 ��easyx ��ͬ       ��(ǽ��)�����ж���
		for (j=1; j<WIDTH-1&&break2==1; j++)
			if(a[i][j]==1)
			{
				switch(dir)
				{
				case 1://dir�Ƿ��� 1������ 2������  3������ 4������
					switch(a[i][j+1])
					{
					case 0:
						break;
					case -1:
						sc++,chiguozi2(a),a[i][j+1]=1,k--,z--;  //	��,k-- ԭ�����ڼ��� k ʹ�� �ٴ�������ֹ���
						break;
					case-3: 					//-3������(�ϰ���)
						chiguozi2(a),a[i][j+1]=1;
						if(wudi==0)
							g2--;		// g2���� 
						break;
					case-4:						//-4�ǰ��� 
						sc+=2,chiguozi2(a),a[i][j+1]=1,wudi=wuditime, g2++;	//���˰��ļ�����
						break;
					case-6:						//-6�ǿ�Ͷ���ٰ�
						sc+=2,chiguozi2(a),a[i][j+1]=1,jiasu=jiasutime,jiansu=0;	//���˰��ļ�����
						break;
					case-7:						//-6�ǿ�Ͷ���ٰ�
						sc+=2,chiguozi2(a),a[i][j+1]=1,jiansu=jiansutime,jiasu=0;
						break;
					case-2:						//-2����(ǽ��)
						chiguozi2(a),a[i][j+1]=1,g1--;			// ����g1
						break;
					default:						//>=2������
						chiguozi2(a),a[i][j+1]=1,g3--;			// ����g3
						break;
					}
					break;
					case 2:
						switch(a[i][j-1])
						{
						case 0:
							break;
						case-1:
							sc++,chiguozi2(a),a[i][j-1]=1,k--,z--;   // sc++ԭ������ �ӷ�
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
			fs();		//��ʾ����
}
void chiguozi2(int a[HEIGHT][WIDTH])// ��������Ĺ����� �������� ʹ����Ԫ�ؼ�1(��Ȼ ��Ҫǽ��) �ڳ԰��ĳ����ѳ�ƻ�� ʱִ�иú���
{
    int i,j, break1=0;
    for (i=1; i<HEIGHT-1&& break1<max; i++)
		for (j=1; j<WIDTH-1&& break1<max; j++)
            if(a[i][j]>0)
				break1++,a[i][j]++;
			max++;
}
void hello()	//�����Ƿ���
{
	// ��ȡ���ھ��
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, "̰����-�����߽�����������");// ���ô��ڱ�������
	initimg();// ͼƬ�ĳ�ʼ��	//һЩͼƬ������
	mciSendString("open \"res\\bm.mp3\" alias mymusic", NULL, 0, NULL);//��������
	mciSendString("play mymusic repeat", NULL, 0, NULL);
	inittext();// ��ʾ���� �ĸ�ʽ �ĳ�ʼ��
	setbkcolor(RGB(255,255,255));	// ���ñ���ɫΪ��ɫ
	cleardevice();// �ñ���ɫ�����Ļ
	putimage(250, 0, &imgfm);//�������
	putimage(0, 0, &imgfmpg1);
	putimage(1000, 350, &imgfmpt1);
	settextcolor(BLACK);
	TCHAR hello1[] = _T("         ��Һ�!");
	TCHAR hello2[] = _T("  ��ӭ����̰���ߵ�����!");
	TCHAR hello3[] = _T("    �����Ϸ�汾����Ȥ");
	TCHAR hello4[] = _T("   wasd��������������");
	TCHAR hello5[] = _T("   ����̰���ߵĻ��Χ");
	TCHAR hello6[] = _T("  ���������ϰ���, ҪԽ����");
	TCHAR hello7[] = _T("ƻ�����˳���һ�� ���ĳ��˼�Ѫ");
	TCHAR hello8[] = _T("    С���������ճ����");
	TCHAR hello9[] = _T("����Ϸ������, ����԰�p����ͣ");
	TCHAR hello10[]= _T("      �밴�������ʼ");
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
	setbkcolor(RGB(255,255,255));	// ���ñ���ɫΪ��ɫ
	cleardevice();// �ñ���ɫ�����Ļ
	putimage(250, 0, &imgfm);
	putimage(0, 0, &imgfmpg1);
	putimage(1000, 350, &imgfmpt1);
	settextcolor(BLACK);// ������ɫ
	TCHAR bye1[] = _T("�밴��������¿�ʼ   j������");
	TCHAR bye2[] = _T("��ķ���Ϊ:");
	outtextxy(500, 400, bye1);
	outtextxy(500, 360, bye2);
	sprintf(s2, "%d", sc);
	outtextxy(620, 360, s2);//����
	ryj();
	
}
void fs() //�ǼǷ����ĺ��� ����Ҫ�����α���ת��Ϊ�ַ���
{	
	
	if(sc!=sc_)// sc_��sc������ �������Ļ� ����ÿһ֡��������� ���ǵȵ������仯���ڸ���
		sc_=sc,sprintf(s2, "%d", sc_),outtextxy(600, 680, s2);//����ô�� ������ÿ���ƶ���Ҫ�������������
	if (g2<g2_)	
	{
		g2_=g2,sprintf(shengmingshuzi, "%d", g2),outtextxy(850, 680, shengmingshuzi);//�������ֵ���� 
		bar(g2*30 +900, 680, g2*30 +920, 700);// ������������ ��bar���� ���ڰ�����
	}
	else if(g2>g2_)	
	{
		g2_=g2,sprintf(shengmingshuzi, "%d", g2),outtextxy(850, 680, shengmingshuzi);//��������
		putimage(g2*30 +870, 680, &imgsmaixin);// ���������쳤 ��putimage���� �����һ������
	}
	if(wudi_!=wudi)
	{
		if(wudi==0)
			bar(200, 680, 240, 700);
		else
			outtextxy(200, 680, wudizfc);// �޵��ַ���
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
		outtextxy(500, 300, sorry1);// ������� ̰����ײ������
	if(g2<1)
		outtextxy(480, 300, sorry2);// ������� ̰���߳���̫��������� 
	if(g3!=1)
		outtextxy(500, 300, sorry3);// ������� ̰����ײ���Լ���
	if(g5<1)
		outtextxy(500, 300, sorry4);// ������� ̰����ײ��С������
}
void initimg()// ͼƬ�ĳ�ʼ��
{
	loadimage(&img1,_T("res\\1.gif"));//��ͷ1������ 2������  3������ 4������
	loadimage(&img2,_T("res\\2.gif"));
	loadimage(&img3,_T("res\\3.gif"));
	loadimage(&img4,_T("res\\4.gif"));
	loadimage(&imgpt,_T("res\\pt.gif"));//����
	loadimage(&imgpt2,_T("res\\pt2.gif"));//����
	loadimage(&imgpg,_T("res\\pg.gif"));//ƻ��
	loadimage(&imgpg2,_T("res\\pg2.gif"));//ƻ��
	loadimage(&imgfm,_T("res\\fm.gif"));// �����
	loadimage(&imgshu,_T("res\\shu.gif"));//�� �ϰ���
	loadimage(&imgshesheng,_T("res\\shesheng.gif"));//����
	loadimage(&imgshesheng2,_T("res\\shesheng2.gif"));//С����
	loadimage(&imgfmpg1,_T("res\\fmpg1.gif"));//����ƻ��
	loadimage(&imgfmpt1,_T("res\\fmpt1.gif"));//��������
	loadimage(&imgdjs1,_T("res\\djs1.gif"));//����ʱ
	loadimage(&imgdjs2,_T("res\\djs2.gif"));//����ʱ
	loadimage(&imgdjs3,_T("res\\djs3.gif"));//����ʱ
	loadimage(&imgzt,_T("res\\zt.gif"));	//��ͣ����ͼ
	loadimage(&imgzt_,_T("res\\zt_.gif"));	//��ͣ����ͼ
	loadimage(&imgsmaixin,_T("res\\smaixin.gif"));//��������
	loadimage(&imgmon,_T("res\\mon.gif"));		//С����
	loadimage(&imgmon2,_T("res\\mon2.gif"));	//С����
	loadimage(&imgshewei,_T("res\\shewei.gif"));//��β
	loadimage(&imgshewei2,_T("res\\shewei2.gif"));//��β
	loadimage(&imgjiasu, _T("res\\jiasu.gif"));//���ٵĿ�Ͷ
	loadimage(&imgjiansu, _T("res\\jiansu.gif"));//����С��ͷ��

	
	
}
void inittext()// ���ָ�ʽ�ĳ�ʼ����
{
	LOGFONT f;
	gettextstyle(&f);                     // ��ȡ��ǰ��������
	f.lfHeight = 20;						// ��������߶�Ϊ 20
	f.lfWeight = 1000;						//���������ϸ
	_tcscpy(f.lfFaceName, _T("��Բ"));    // ��������Ϊ�����塱(�߰汾 VC �Ƽ�ʹ�� _tcscpy_s ����)
	f.lfQuality = ANTIALIASED_QUALITY;    // �������Ч��Ϊ�����  
	settextstyle(&f);// ����������ʽ
}
void daojishi()// ����ʱ���� 
{
	putimage(435, 175, &imgdjs3);//   3
	Sleep(1000);
	putimage(435, 175, &imgdjs2);//   2
	Sleep(1000);
	putimage(435, 175, &imgdjs1);//   1
	Sleep(1000);// ��������Ϸ��ʼ��
}
int ryj()// ���������(Ϊʲô����getch()�� ��Ϊ���Ҳ������� )
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
			m=GetMouseMsg();//��ȡһ�������Ϣ
			if(m.uMsg==WM_LBUTTONDOWN)//���������������
				return 0;
		}
	}
}
void pachong(int a[HEIGHT][WIDTH])  //�����ж�����
{
	static int pachongsudu=0;
	if (pachongsudu==5)
    {
		a[ip][jp]=0; //�������ڵĶ�ά����Ԫ�ع��� Show��������ʾΪ����
		if     (imax<ip && jmax<jp && a[ip-1][jp-1]!=-1)// ��ʾ   ��������Ϸ�����β  ���� ��������ϸ���ƻ��
			ip--,jp--;
		else if(imax>ip && jmax<jp && a[ip+1][jp-1]!=-1)// ��ʾ   ��������Ϸ�����β  ���� ��������ϸ���ƻ��
			ip++,jp--;
		else if(imax>ip && jmax>jp && a[ip+1][jp+1]!=-1)// ��ʾ   ��������·�����β  ���� ��������¸���ƻ��
			ip++,jp++;
		else if(imax<ip && jmax>jp && a[ip-1][jp+1]!=-1)// ��ʾ   ��������·�����β  ���� ��������¸���ƻ��
			ip--,jp++;
		a[ip][jp]=-5;// �����ƶ������ڵĶ�ά����Ԫ�ظ�ֵΪ-5 Show��������ʾΪ����
		pachongsudu=0;// Ϊ�˲���Ҫ�ƶ���̫�� ����pachongsudu �´εĻ� ++10���ٶ�
    }
	else
		pachongsudu++;
}