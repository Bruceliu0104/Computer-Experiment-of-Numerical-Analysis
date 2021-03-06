//=====================================================================================
//函数说明
//函数名称：PolyFit
//函数功能：最小二乘法曲线拟合
//使用方法：double *x ---- 存放n个数据点的X坐标
//          double *y ---- 存放n个数据点的Y坐标
//			int n -------- 给定数据点个数
//			double *a ---- 返回m-1次拟合多项式的m个系数
//          int m -------- 拟合多项式的项数，即拟合多项式的最高次为m-1。要求m<=n,且
//						   m<=20。若m>n或m>20，则本函数自动按m=min{n,20}处理
//			double *dt --- dt[0]返回拟合多项式与各数据点误差的平方和；dt[1]返回拟合多
//						   项式与各数据点的误差绝对值之和；dt[2]返回拟合多项式与各数据
//						   点误差绝对值的最大值
//注意事项：拟合多项式的形式为 y = b0 + b1*(x-Xavr)...
//=====================================================================================
#include "math.h"
void PolyFit(double *x, double *y, int n, double *a, int m, double *dt)
{
	int i, j, k;
	double z, p, c, g, q, d1, d2, s[20], t[20], b[20];
	for (i = 0; i <= m-1; i++)
	{
		a[i] = 0.0;
	}
	if (m > n)
	{
		m = n;
	}
	if (m > 20)
	{
		m = 20;
	}
	z = 0.0;
	for (i = 0; i <= n-1; i++)
	{
		z = z+x[i]/(1.0 *n);
	}
	b[0] = 1.0;
	d1 = 1.0 * n;
	p = 0.0;
	c = 0.0;
	for (i = 0; i <= n-1; i++)
	{
		p = p+(x[i]-z);
		c = c+y[i];
	}
	c = c/d1;
	p = p/d1;
	a[0] = c * b[0];
	if (m > 1)
	{
		t[1] = 1.0;
		t[0] = -p;
		d2 = 0.0;
		c = 0.0;
		g = 0.0;
		for (i = 0; i <= n-1; i++)
		{
			q = x[i]-z-p;
			d2 = d2+q * q;
			c = c+y[i] *q;
			g = g+(x[i]-z) *q * q;
		}
		c = c/d2;
		p = g/d2;
		q = d2/d1;
		d1 = d2;
		a[1] = c * t[1];
		a[0] = c * t[0]+a[0];
	}
	for (j = 2; j <= m-1; j++)
	{
		s[j] = t[j-1];
		s[j-1] = -p * t[j-1]+t[j-2];
		if (j >= 3)
			for (k = j-2; k >= 1; k--)
		    {
				s[k] = -p * t[k]+t[k-1]-q * b[k];
		    }
		s[0] = -p * t[0]-q * b[0];
		d2 = 0.0;
		c = 0.0;
		g = 0.0;
		for (i = 0; i <= n-1; i++)
		{
			q = s[j];
			for (k = j-1; k >= 0; k--)
			{
				q = q *(x[i]-z)+s[k];
			}
			d2 = d2+q * q;
			c = c+y[i] *q;
			g = g+(x[i]-z) *q * q;
		}
		c = c/d2;
		p = g/d2;
		q = d2/d1;
		d1 = d2;
		a[j] = c * s[j];
		t[j] = s[j];
		for (k = j-1; k >= 0; k--)
		{
			a[k] = c * s[k]+a[k];
			b[k] = t[k];
			t[k] = s[k];
		}
	}
	dt[0] = 0.0;
	dt[1] = 0.0;
	dt[2] = 0.0;
	for (i = 0; i <= n-1; i++)
	{
		q = a[m-1];
		for (k = m-2; k >= 0; k--)
		{
			q = a[k]+q *(x[i]-z);
		}
		p = q-y[i];
		if (fabs(p) > dt[2])
		{
			dt[2] = fabs(p);
		}
		dt[0] = dt[0]+p * p;
		dt[1] = dt[1]+fabs(p);
	}
	return ;
}
