#include <iostream.h>
#include <string.h>
#include <stdlib.h>


int vnum=0;//��������

char exp[2][100];//�����ı��ʽ
int vval[26];//ÿ����Ŵ���ı�����ֵ
int vID[26];//ÿ��������Ӧ�ı��

int cur=0;

__int64 cal(char Exp[],int b,int e,int vval[])//������ʽ��ֵ
{

	__int64 left=0,right=0;//�������  �Ҳ�����


	int opernum=0;//���������
	int premin=1000;//��С���ȼ�
	int posi;//�����λ��
	int layer=0;//����(����)
	int x;
	for (int i=b;i<=e;i++)//��������������ȼ�
	{
		if (Exp[i]=='*')
			x=2+3*layer;

		else if (Exp[i]=='+')
			x=3*layer;

		else if (Exp[i]=='-')
			x=1+3*layer;

		else if (Exp[i]=='(')
		{
			layer++;
			continue;
		}
		else if (Exp[i]==')')
		{
			layer--;
			continue;
		}
		else 
			continue;

		opernum++;
		if (premin>=x )//�õ����ȼ���С������������ұߵ�һ�����Ӵ˴��Ͽ����ݹ����
		{
			premin=x;
			posi=i;
		}
	}

	if (opernum==1)//��һ������� ����ֱ������
	{
	
			int cur=b;
			while(Exp[cur]!='*' && Exp[cur]!='+' && Exp[cur]!='-')
				cur++;

			for (int j=b;j<cur;j++)
			{
				if (Exp[j]>='a' && Exp[j]<='z')
				{
					left=vval[vID[Exp[j]-'a']];
					break;
				}
				else if (Exp[j]>='0' && Exp[j]<='9')
				{
					left=Exp[j]-'0';
					break;
				}
			}

			for (j=cur+1;j<=e;j++)
			{
				if (Exp[j]>='a' && Exp[j]<='z')
				{
					right=vval[vID[Exp[j]-'a']];
					break;
				}
				else if (Exp[j]>='0' && Exp[j]<='9')
				{
					right=Exp[j]-'0';
					break;
				}
			}
			
			if (Exp[posi]=='*')
				return left*right;
			else if (Exp[posi]=='+')
				return left+right;
			else if (Exp[posi]=='-')
				return left-right;
	}

	else if (opernum==0)//��0������� ֱ�ӷ���ֵ
	{
		int cur=b;
re:		if (Exp[cur]>='a' && Exp[cur]<='z')
			left=vval[vID[Exp[cur]-'a']];
		else if (Exp[cur]>='0' && Exp[cur]<='9')
			left=Exp[cur]-'0';
		if (cur>e)
			return left;
		else 
		{
			cur++;
			goto re;
		}
		return left;
	}

	
	
	left=cal(Exp,b,posi-1,vval);//�ݹ� ������
	right=cal(Exp,posi+1,e,vval); //�ݹ� �����Ҳ�

	if (Exp[posi]=='*')
		return left*right;
	else if (Exp[posi]=='+')
		return left+right;
	else if (Exp[posi]=='-')
		return left-right;

}







int IsEqual()
{
	for (int i=0;i<vnum;i++)//ͨ����������� �������ʽ��ֵ�Ƿ���� 
		vval[i]=rand();

	cur=0;
	__int64 r1=cal(exp[0],0,(int )strlen(exp[0])-1,vval);
	cur=0;
	__int64 r2=cal(exp[1],0,(int )strlen(exp[1])-1,vval);
	if (r1==r2)
		return 1;
	else 
		return 0;
}
	
void main()
{
	int n;
	cin>>n;
	
	char str[200];
	cin.getline(str,200);
	for (int t=0;t<n;t++)
	{
		for (int i=0;i<2;i++)
		{
			cin.getline(str,200);			
			int k=0;
			for (int j=0;j<strlen(str);j++)//����дת��Сд  ȥ���ո���tab
			{
				if (str[j]==' '||str[j]=='	')
					continue;
				if (str[j]>='A' && str[j]<='Z')
					str[j]=str[j]-'A'+'a';
				exp[i][k++]=str[j];
			}
			exp[i][k]='\0';
		}

		int tag[26]={0};//��ǳ��ֹ��ı���


		for (i=0;i<2;i++)
		{
			for (int j=0;j<(int)strlen(exp[i]);j++)
			{
				if(exp[i][j]>='a' && exp[i][j]<='z')
					tag[exp[i][j]-'a']=1;
			}
		}

		
	
		for (i=0;i<26;i++)//�������
			vval[i]=0;
		for (i=0;i<26;i++)
			vID[i]=0;
		vnum=0;

		for (i=0;i<26;i++)
		{
			if (tag[i]==1)
				vID[i]=vnum++;
		}

		if (IsEqual()==0)
			cout<<"NO"<<endl;
		else
			cout<<"YES"<<endl;
	}
}



