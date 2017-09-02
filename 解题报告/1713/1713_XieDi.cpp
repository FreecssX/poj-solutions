#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <memory.h>

const ax[4] = {0, 1, 0, -1}, ay[4] = {1, 0, -1, 0};

struct Tnode
{
	short x, y;
} p[30], w[30], q[30], d[30];						//�ֱ����չ����У�Ϊ��*���ĸ��ӣ�����

char g[101][101];									//���������
short mark[101][101] = {0};							//���ĳ�������Ƿ�Ϊ����չ��
bool cover[101][101] = {0}, c[16][16], u[6][6];		//�ֱ�ΪA���ϱ�ǣ�B���ϱ�ǣ���ͨ��
int n, m, tt;

inline bool match(short minx2, short miny2, short maxx2, short maxy2, short maxx1, short maxy1)
{													//ͨ��ƽ���ж����������Ƿ�պù���N*N��ͼ��
	short rx, ry, j;
	bool suc;

	for (rx = maxx2 - n + 1; rx < n + minx2 - maxx1; rx++)
		for (ry = maxy2 - n + 1; ry < n + miny2 - maxy1; ry++)
		{
			suc = 1;
			for (j = 0; j < tt; j++)
				if (c[d[j].x + rx][d[j].y + ry])
				{
					suc = 0;
					break;
				}
			if (suc)
				return true;
		}
	return false;
}

inline short connect(int sx, int sy)
{													//�ж�B�����е���ͨ��
	int qs = 0, qt = 1, r, nx, ny;
	q[qt].x = sx; q[qt].y = sy; u[sx][sy] = 0;
	while (qs < qt)
	{
		qs++;
		for (r = 0; r < 4; r++)
		{
			nx = q[qs].x + ax[r]; ny = q[qs].y + ay[r];
			if (nx < n && nx >= 0 && ny < n && ny >= 0 && u[nx][ny])
			{
				u[nx][ny] = 0;
				qt++;
				q[qt].x = nx; q[qt].y = ny;
			}
		}
	}
	return qt;
}

inline bool ok(short minx2, short miny2, short maxx2, short maxy2)
{			//����true��ɹ����������������ʧ�ܡ�����Ĳ���ΪA���ϱ߽�
	short minx1, miny1, maxx1, maxy1, i, j, tmp;

	minx1 = miny1 = 200; maxx1 = maxy1 = 0;
	for (i = 0; i < m; i++)					//��¼B���ϵı߽�
		if (!cover[w[i].x][w[i].y])
		{
			if (w[i].x < minx1)
				minx1 = w[i].x;
			if (w[i].x > maxx1)
				maxx1 = w[i].x;
			if (w[i].y < miny1)
				miny1 = w[i].y;
			if (w[i].y > maxy1)
				maxy1 = w[i].y;
		}

	memset(c, 0, sizeof(c));
	tt = 0;
	for (i = 0; i < m; i++)
		if (!cover[w[i].x][w[i].y])
		{
			if (w[i].x - minx1 >= n || w[i].y - miny1 >= n)	//������N*N��ʧ��
				return false;
			d[tt].x = w[i].x - minx1;						//��B���ƶ������Ͻ�
			d[tt].y = w[i].y - miny1;
			tt++;
		}
		else
			c[w[i].x - minx2 + 5][w[i].y - miny2 + 5] = 1;	//��A���ƶ������Ͻ�

	memset(u, 0, sizeof(u));	//Ϊ�ж���ͨ�Գ�ʼ��
	for (i = 0; i < tt; i++)
		u[d[i].x][d[i].y] = 1;
	if (connect(d[0].x, d[0].y) < tt)	//������ͨ��ʧ��
		return false;
	maxx2 = maxx2 - minx2 + 5; maxy2 = maxy2 - miny2 + 5;
	minx2 = miny2 = 5;
	maxx1 = maxx1 - minx1; maxy1 = maxy1 - miny1;
	minx1 = miny1 = 0;

	for (i = 0; i < 4; i++)				//4����ת
	{
		if (match(minx2, miny2, maxx2, maxy2, maxx1, maxy1))
			return true;				//ͨ��ƽ�ƿ��ܷ񹹳�N*N��ͼ��
		minx1 = miny1 = 200; maxx1 = maxy1 = 0;
		for (j = 0; j < tt; j++)
		{								//��ת���̣�������б任
			tmp = d[j].y; d[j].y = n - d[j].x - 1;
			d[j].x = tmp;
			if (d[j].x < minx1)
				minx1 = d[j].x;
			if (d[j].x > maxx1)
				maxx1 = d[j].x;
			if (d[j].y < miny1)
				miny1 = d[j].y;
			if (d[j].y > maxy1)
				maxy1 = d[j].y;
		}
		for (j = 0; j < tt; j++)		//��ͼ���ƶ������Ͻ�
		{
			d[j].x -= minx1; d[j].y -= miny1;
		}
		maxx1 -= minx1; maxy1 -= miny1;
	}
	return false;
}

bool search(short minx, short miny, short maxx, short maxy, short t, short q)
{
	short r, nx, ny;

	if (q > t)							//����ǰ�Ѿ�û�п���չ�㣬���˳�
		return false;

	if (search(minx, miny, maxx, maxy, t, q + 1))	//��q���㲻����A����
		return true;					//���н��򷵻سɹ���־

	//��q��������A����

	if (abs(minx - p[q].x) >= n || abs(maxx - p[q].x) >= n ||
		abs(miny - p[q].y) >= n || abs(maxy - p[q].y) >= n)
		return false;					//��������N*N��Χ�ڣ���ʧ�ܣ�����

	for (r = 0; r < 4; r++)				//�ҳ����еĿ���չ��
	{
		nx = p[q].x + ax[r]; ny = p[q].y + ay[r];
		if (g[nx][ny] == '*' && !mark[nx][ny])
		{
			t++;
			p[t].x = nx; p[t].y = ny;
			mark[nx][ny] = q;			//����չ����б��
		}
	}

	nx = p[q].x; ny = p[q].y;
	cover[nx][ny] = 1;					//��ǰ������A����
	if (!ok(__min(minx, nx), __min(miny, ny), __max(maxx, nx), __max(maxy, ny)))
	{									//�����ܳɹ�����N*N�����������
		if (search(__min(minx, nx), __min(miny, ny), __max(maxx, nx), __max(maxy, ny), t, q + 1))
			return true;
	}
	else
		return true;					//���ɹ��ﵽĿ�꣬�򷵻�
	cover[nx][ny] = 0;					//������

	for (r = 0; r < 4; r++)
	{
		nx = p[q].x + ax[r]; ny = p[q].y + ay[r];
		if (mark[nx][ny] == q)
			mark[nx][ny] = 0;
	}	
	return false;
}

int main()
{
	int i, j, line;

	line = 0;
	while (gets(g[line++]));		//����ȫ������

	m = 0;
	for (i = 0; i < line; i++)
		for (j = 0; g[i][j] != 0; j++)
			if (g[i][j] == '*')		//����ǰ�ǡ�*�������¼����
			{
				w[m].x = i; w[m].y = j;
				m++;
			}
	n = (int) sqrt(m);				//���N
	p[1].x = w[0].x; p[1].y = w[0].y; mark[w[0].x][w[0].y] = -1;
	search(w[0].x, w[0].y, w[0].x, w[0].y, 1, 1);		//��ʼ����
	for (i = 0; i < line; i++)		//���
	{
		for (j = 0; g[i][j] != 0; j++)
			if (g[i][j] == '*')
				if (cover[i][j])
					printf("A");
				else
					printf("B");
			else
				printf(".");
		printf("\n");
	}
	return 0;
}
