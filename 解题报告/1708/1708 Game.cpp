#include<iostream.h>
#include<string.h>

struct circle{
	int line[150];	//ÿ����ָ���Բ
	int linenum;	//�ɸ�԰�������ߵĸ���
	int linecolor[150];		//ÿ���ߵ���ɫ
	int color;		//Բ����ɫ
} cir[150];

struct state{	//�������λ�ñ�ʾһ��״̬
	int x,y;
} queue[15000];

int p1,p2;		//���е���ָ���βָ��
state start;
bool use[150][150];		

void main()
{
	int n,i,m,a,b,c,end,time,yes,p;

	memset(use,false,sizeof(use));
	cin>>n>>queue[0].x>>queue[0].y>>end;
	for (i=1;i<=n;i++)
	{
		cin>>cir[i].color;
		cir[i].linenum=0;
	}
	cin>>m;
	for (i=0;i<m;i++)
	{
		cin>>a>>b>>c;
		cir[a].line[cir[a].linenum]=b;
		cir[a].linecolor[cir[a].linenum]=c;
		cir[a].linenum++;
	}
	p1=0;
	p2=1;
	time=1;
	yes=0;
	p=0;
	while(1)
	{
		//����һ�֣�time++
		if (p1>p)
		{
			p=p2-1;
			time++;
		}
		//�ӵ�һ�������һ���ߵ��ĵ㶼���
		for (i=0;i<cir[queue[p1].x].linenum;i++)
		{
			if (cir[queue[p1].x].linecolor[i]==cir[queue[p1].y].color
				&& use[cir[queue[p1].x].line[i]][queue[p1].y]==false
				&& cir[queue[p1].x].line[i]!=queue[p1].y)
			{	
				queue[p2].x=cir[queue[p1].x].line[i];
				queue[p2].y=queue[p1].y;
				use[queue[p2].x][queue[p2].y]=true;
				if (queue[p2].x==end || queue[p2].y==end)
				{
					yes=1;
					break;
				}
				p2++;
			}
		}
		//�ӵڶ��������һ���ߵ��ĵ㶼���
		for (i=0;i<cir[queue[p1].y].linenum;i++)
		{
			if (cir[queue[p1].y].linecolor[i]==cir[queue[p1].x].color
				&& use[queue[p1].x][cir[queue[p1].y].line[i]]==false
				&& queue[p1].x!=cir[queue[p1].y].line[i])
			{	
				queue[p2].y=cir[queue[p1].y].line[i];
				queue[p2].x=queue[p1].x;
				use[queue[p2].x][queue[p2].y]=true;
				if (queue[p2].x==end || queue[p2].y==end)
				{
					yes=1;
					break;
				}
				p2++;
			}
		}
		//���һ��������һ�����ߵ��õ㶼�ڶ�����õ����
		p1++;
		//��λָ���غ� �� �����յ��˳�ѭ��
		if (p1==p2 || yes==1) 
			break;
	}
	if (yes==1)
		cout<<"YES"<<endl<<time<<endl;
	else
		cout<<"NO"<<endl;	
}