#include<iostream.h>
#include<memory.h>
struct L      //��ʾ��ͻ����Ľṹ
{
	int a,b,c,d ;
	char ch ;
};
L lin[200] ;   //��ʾ��ͻ���������
int flag[10][10] ;   //�����i�е�j�е���Ʒ�����ĸ���
int x , y ;
int schr( int lasti , int lastj, int z )   
//�ݹ鳢�Ե�ǰλ��lasti��ʾ�ڼ����ˣ�lastj��ʾ�ڼ�����Ʒ�� z��ʾ�и����ٳ�ͻ
{
	int i,j,ff;
	if( lasti == y ) return 1 ;     // ����������򷵻ر�־1 
	for( i = 0 ; i < y ; i++ )
	{
		if( flag[lastj][i] != -1 ) continue ;   // ����ǰλ���Ѿ���ռ���������µ�λ��
		for( j = 0 ; j < z ; j++ )  // �����Ƿ��г�ͻ����
		{
			ff = 0 ;
			if ( lastj == lin[j].a && i == lin[j].b && flag[lin[j].c][lin[j].d] != -1)
			{
					if( lin[j].ch == 'R' )
					{
						if( flag[lin[j].c][lin[j].d] != lasti ){ ff = 1;break;}
					}
					if (lin[j].ch == 'N' )
					{
						if ( flag[lin[j].c][lin[j].d] == lasti ){ ff = 1;break ;}
					}
			}
			else if ( lastj == lin[j].c && i == lin[j].d &&flag[lin[j].a][lin[j].b]!=-1 )
			{
					if( lin[j].ch == 'R' )
					{
						if( flag[lin[j].a][lin[j].b] != lasti ) { ff = 1;break ;}
					}
					if (lin[j].ch == 'N' )
					{
						if ( flag[lin[j].a][lin[j].b] == lasti ){ ff = 1;break ;}
					}
			}
		}	
		if ( ff == 1 ) continue ;   //���г�ͻ�����µĿ���
		flag[lastj][i] = lasti ;   
		if ( lastj == x-1 )       
		{
			if ( schr( lasti+1,0,z ) ) return 1 ;
		}
		else
		{
			if ( schr( lasti,lastj+1,z)) return 1 ;
		}
		flag[lastj][i] = -1 ;
	}
	return 0 ;
}
void main()
{
	int n,i,j,k ;
	char item[10][10] ;
	cin >> n ;
	while( n-- )
	{
		// ����
		cin >> x >> y ;
		for( i = 0 ; i< x ; i++ )
			cin >> item[i] ;
		i = 0 ;
		for( i = 0 ; i < x ; i++)
			for( j = 0 ; j < y ; j++ )
				flag[i][j] = -1 ;
		i = 0 ;
		while(1)
		{
			cin >> lin[i].a >> lin[i].b >> lin[i].ch >> lin[i].c >> lin[i].d ;
			if ( lin[i].a == 0 ) break ;
			lin[i].a--;
			lin[i].b--;
			lin[i].c--;
			lin[i].d--;
			i++ ;
		}
		//����
		schr( 0 , 0 , i ) ;
		// ������
		for( i = 0 ; i < y ; i++ )
		{
			for( j = 0 ; j < x ; j++ )
			{
				for( k = 0 ; k < y ; k++ )
				{
					if ( flag[j][k] == i ) 
					cout << item[j][k] ;
				}
			}
			cout << endl ;
		}
		cout << endl;

	}
}
			

