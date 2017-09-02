#include<iostream.h>
#include<string.h>

//����ʱ���Ǹ�������ʱ��
//����ʱ���Է���Ϊ��λ

struct station{
	char sn[6];		//�ɻ����
	int tag;		//Ŀ�ĵ�
	int leave;		//���ʱ��
	int run;		//����ʱ��
} st[110][310];		//��������������Ϣ

char name[110][30];		//����
char time[10];			
int delay[110];		//��������ʱ
int timedifference[110];	//������ʱ��
int airnum[110];	//������������
int starttime,namenum,n,m;
bool use[110];		//
int queue[110];		//����ÿ�������ı��
int quenum;			//���л�����
int quetime[110];		//���е�ÿ��������ʱ�� [0,24*60)
int sumtime[110];		//����ʼ���������и����������ʱ��
int father[110];		//�����и�������ǰһ���������
char quesn[110][6];		//���絽���и������ķɻ����
char temsn[110][6];		//û�豸��ô̫���ã��������˳�����һ��

void main()
{
	int i,j,k,p,pt,min,x,y,z;
	char place[30];
	char c;

	//�����ģ��������Ϣ��
	cin>>name[0]>>name[1];
	cin>>time;
	starttime=(time[0]-'0')*600+(time[1]-'0')*60+(time[3]-'0')*10+time[4]-'0';
	cin>>n;
	namenum=2;
	for (i=0;i<n;i++)
	{
		cin>>place;
		for (k=0;k<namenum;k++)
			if (strcmp(place,name[k])==0)
			{
				p=k;
				break;
			}
		if (k>=namenum) 
		{
			p=namenum;
			strcpy(name[namenum],place);
			namenum++;
		}
		cin>>c>>time;
		if (c=='+')
			timedifference[p]=(time[0]-'0')*600+(time[1]-'0')*60+(time[3]-'0')*10+time[4]-'0';
		else
			timedifference[p]=0-((time[0]-'0')*600+(time[1]-'0')*60+(time[3]-'0')*10+time[4]-'0');
		cin>>time;
		delay[p]=(time[0]-'0')*600+(time[1]-'0')*60+(time[3]-'0')*10+time[4]-'0';
		cin>>m;
		airnum[p]=m;
		for (j=0;j<m;j++)
		{
			cin>>st[p][j].sn;
			cin>>place;
			for (k=0;k<namenum;k++)
				if (strcmp(place,name[k])==0)
				{
					st[p][j].tag=k;
					break;
				}
			if (k>=namenum) 
			{
				st[p][j].tag=namenum;
				strcpy(name[namenum],place);
				namenum++;
			}
			cin>>time;
			st[p][j].leave=(time[0]-'0')*600+(time[1]-'0')*60+(time[3]-'0')*10+time[4]-'0';
			st[p][j].leave-=timedifference[p];		//���ɸ�������ʱ��
			while (st[p][j].leave<0) st[p][j].leave+=24*60;		//��֤��[0,24*60)��Χ��	
			while (st[p][j].leave>=24*60) st[p][j].leave-=24*60;
			cin>>time;
			st[p][j].run=(time[0]-'0')*600+(time[1]-'0')*60+(time[3]-'0')*10+time[4]-'0';
		}
	}
	//����������!!!  :~(

	//δ���κα䶯��dijkstra�����·�㷨
	quenum=1;
	queue[0]=0;
	use[0]=true;
	quetime[0]=starttime-timedifference[0];
	while (quetime[0]<0) quetime[0]+=24*60;
	while (quetime[0]>=24*60) quetime[0]-=24*60;
	sumtime[0]=0;
	father[0]=-1;
	while(1)
	{
		//�ҴӶ��л������Ƕ��л���������ʱ��
		min=2147483647;
		for (i=0;i<quenum;i++)
		{
			for (j=0;j<airnum[queue[i]];j++)
			{
				if (use[st[queue[i]][j].tag]==true) continue;
				if (quetime[i]+delay[queue[i]]<=st[queue[i]][j].leave)
					pt=sumtime[i]+st[queue[i]][j].leave-quetime[i]+st[queue[i]][j].run;
				else
					pt=sumtime[i]+st[queue[i]][j].leave-quetime[i]+st[queue[i]][j].run+24*60;
				if (pt<min)
				{
					min=pt;
					x=queue[i];
					y=j;
					z=i;
				}
			}
		}
		//���û����������
		queue[quenum]=st[x][y].tag;
		quetime[quenum]=st[x][y].leave+st[x][y].run;
		while (quetime[quenum]<0) quetime[quenum]+=60*24;
		while (quetime[quenum]>=24*60) quetime[quenum]-=24*60;
		sumtime[quenum]=min;
		strcpy(quesn[quenum],st[x][y].sn);
		father[quenum]=z;
		quenum++;
		use[st[x][y].tag]=true;
		if (st[x][y].tag==1) break;
	}

	//����ɵ�d:hh:mm��ʽ(���ַ����Ƚ�����)
	quenum--;
	cout<<sumtime[quenum]/(24*60)<<":";
	sumtime[quenum]=sumtime[quenum]%(24*60);
	cout<<sumtime[quenum]/600;
	sumtime[quenum]=sumtime[quenum]%600;
	cout<<sumtime[quenum]/60<<":";
	sumtime[quenum]=sumtime[quenum]%60;
	cout<<sumtime[quenum]/10;
	sumtime[quenum]=sumtime[quenum]%10;
	cout<<sumtime[quenum]<<endl;
	
	quetime[quenum]+=timedifference[1];
	while (quetime[quenum]<0) quetime[quenum]+=60*24;
	while (quetime[quenum]>=24*60) quetime[quenum]-=24*60;
	cout<<quetime[quenum]/600;
	quetime[quenum]=quetime[quenum]%600;
	cout<<quetime[quenum]/60<<":";
	quetime[quenum]=quetime[quenum]%60;
	cout<<quetime[quenum]/10;
	quetime[quenum]=quetime[quenum]%10;
	cout<<quetime[quenum]<<endl;

	//�������������
	j=0;
	for (i=quenum;father[i]!=-1;i=father[i])
	{	
		strcpy(temsn[j],quesn[i]);
		j++;
	}
	for (i=j-1;i>=0;i--)
		cout<<temsn[i]<<endl;
}