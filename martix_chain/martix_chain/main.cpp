
#include <iostream>
void martix_chain(int martix_count, int *martix, int **chain_count, int **k_index);

int main()
{
	int p[7] = { 30,35,15,5,10,20,25 };
	int **m, **s;
	m = new int*[7];
	s = new int*[7];
	for(int i = 0;i < 7;i++)
	{
		m[i] = new int[7];
		s[i] = new int[7];
		for(int j = 0;j < 7;j++)
		{
			m[i][j] = 0;
			s[i][j] = 0;
		}
	}
	martix_chain(6, p, m, s);

	for(int i = 1;i < 7;i++)
	{
		for(int  j = 1;j < 7;j++)
		{
			std::cout << m[i][j] << " ";
		}
		std::cout << std::endl;
	}

	int q;
	std::cin >> q;

	return 0;
}


void martix_chain(int martix_count, int *martix, int **chain_count, int **k_index)
{

	for (int i = 0; i <= martix_count; i++)
	{
		chain_count[i][i] = 0;
	}

	for (int h = 2; h <= martix_count; h++)
	{
		for (int i = 1; i <= martix_count - h + 1; i++)
		{
			int j = i + h - 1;
			chain_count[i][j] = chain_count[i + 1][j] + martix[i - 1] * martix[i] * martix[j];
			k_index[i][j] = i;
			for (int k = i + 1; k < j; k++)
			{
				int t = chain_count[i][k] + chain_count[k + 1][j] + martix[i - 1] * martix[k] * martix[j];
				if (t < chain_count[i][j])
				{
					chain_count[i][j] = t;
					k_index[i][j] = k;
				}
			}
		}
	}
}