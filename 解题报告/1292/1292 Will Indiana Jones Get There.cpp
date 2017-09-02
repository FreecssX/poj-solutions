#include<iostream.h>
#include<math.h>
#include<iomanip.h>
struct point// һ����
{
  int x,y;
};

struct 
{
	point begin,end;
    int sign;
}edge[1000];//һ����

double calculate(point a,point b) //����������֮��ľ���
{
	return (sqrt((a.x-b.x+0.0)*1.0*(a.x-b.x)+(a.y-b.y+0.0)*1.0*(a.y-b.y)));
}

double distance(int i,int last)//����������֮��ľ���
{ 
	int erect,flat;
	double between;
    if(edge[i].sign==edge[last].sign)
	{
		if(edge[i].sign==1) //�����߶ζ���ˮƽ��
		{
			if(edge[i].end.x<edge[last].begin.x) between=calculate(edge[i].end,edge[last].begin);
			   else if(edge[i].begin.x>edge[last].end.x) between=calculate(edge[i].begin,edge[last].end);
				else between=fabs(edge[i].begin.y-edge[last].begin.y);
		}
		else //�����߶ζ�����ֱ��
		{
			if(edge[i].begin.y>edge[last].end.y) between=calculate(edge[i].begin,edge[last].end);
			   else if(edge[i].end.y<edge[last].begin.y) between=calculate(edge[i].end,edge[last].begin);
					else between=fabs(edge[i].begin.x-edge[last].begin.x);
		}
	}
	else 
	{
		 if(edge[i].sign==1) {erect=last;flat=i;}
		 else {erect=i;flat=last;} //erect ��¼���ߣ�flat��¼����
		 if(edge[erect].end.x<edge[flat].begin.x) //ͼ4��5��6�У����߾��ں��ߵ���ࡣ
		 {
			if(edge[erect].begin.y>edge[flat].begin.y)
				between=calculate(edge[erect].begin,edge[flat].begin);
			else if(edge[erect].end.y<edge[flat].begin.y)
				between=calculate(edge[erect].end,edge[flat].begin);
			else between=fabs(edge[erect].begin.x-edge[flat].begin.x);
		}
		else if(edge[erect].begin.x>edge[flat].end.x)//ͼ7��8��9�У����߾��ں��ߵ��Ҳ�
		{
			if(edge[erect].begin.y>edge[flat].begin.y)
				between=calculate(edge[erect].begin,edge[flat].end);
			else if(edge[erect].end.y<edge[flat].begin.y)
				between=calculate(edge[erect].end,edge[flat].end);
			else between=fabs(edge[erect].begin.x-edge[flat].end.x);
		}
		else //ͼ10��ͼ11��ͼ12�У����ߵ�x������ں������˵�x����֮��
		{ 
			if(edge[erect].begin.y>edge[flat].begin.y)
				between=fabs(edge[erect].begin.y-edge[flat].begin.y);
			else if(edge[erect].end.y<edge[flat].begin.y)
				between=fabs(edge[erect].end.y-edge[flat].begin.y);
			else between=0;
		}
	}
    return between;
}
void main()
{
	int i,n,l,min,used[1000],last;
	double between,weight[1000];
	cin>>n;
	while(n>0)
	{ 
		for(i=0;i<n;i++)//��ʼ������¼������
		{
			cin>>edge[i].begin.x>>edge[i].begin.y>>l;
			if(l>0)
			{
				edge[i].end.x=edge[i].begin.x+l;
                edge[i].end.y=edge[i].begin.y; 
				edge[i].sign=1;//1 ��ʾweihengxian
			}
			else 
			{
				edge[i].end.x=edge[i].begin.x;
				edge[i].end.y=edge[i].begin.y-l;
				edge[i].sign=-1;// -1 ��ʾΪ����
			}
		}
		for(i=0;i<n;i++)
		{   
			weight[i]=9999999;
   	        used[i]=0;// 0 ��ʾδ����ǹ�
		}
		last=0;
	    used[0]=1;//�����ʼ���ѱ�ѡ��
		weight[0]=0;//��ʼ��������ĵ�ȨֵΪ0
	    while(last!=1)//ֻҪlast��ΪĿ���
		{
			
			for(i=0;i<n;i++)
				if(used[i]==0)//���iδ����ǹ�
				{   
				    between=distance(i,last);//��i��last�ľ���
				    if(weight[last]>between) between=weight[last];
				    if((weight[i]-between)>1e-10) weight[i]=between;
				}
	       	   
				//��δ����ǵĵ���ѡ��Ȩֵ��С�ĵ�
				i=0;
				while(used[i]==1) i++;
				min=i;
				for(i;i<n;i++)
					if((used[i]==0)&&((weight[min]-weight[i])>1e-10))
			              min=i;
                last=min;
				used[min]=1;
		}
		cout<<setiosflags(ios::fixed)<<setprecision(2)<<weight[1]<<endl;
		cin>>n;
	}
}