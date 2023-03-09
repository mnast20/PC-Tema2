//Nastase Maria
//311 CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NMAX 100

void aloc_matrice_lin(int *v, int **a, int i)
{
	a[i] = (int *)calloc(v[i], sizeof(int));
		if (!a[i]) {
			fprintf(stderr, "calloc() failed\n");
			while (--i >= 0)
				free(a[i]);
			free(a);
		}
}

int **aloc_matrice(int n, int m)
{
	//alocare matrice bytes
	int **mat = (int **)calloc(n + 2, sizeof(int *));
	if (!mat) {
		fprintf(stderr, "calloc() failed\n");
		return NULL;
	}
	for (int i = 0; i <= n + 1; ++i) {
		mat[i] = (int *)calloc(m * 4 + 2, sizeof(int));
		if (!mat[i]) {
			fprintf(stderr, "calloc() failed\n");
			while (--i >= 0)
				free(mat[i]);
			free(mat);
			return NULL;
		}
	}

	return mat;
}

int *aloc_vect(int n)
{
	int *v = (int *)calloc(n, sizeof(int));
	if (!v) {
		fprintf(stderr, "calloc() failed");
		return NULL;
	}
	return v;
}

void free_matrice(int n, int **a)
{
	for (int i = 0; i < n; ++i)
		free(a[i]);
	free(a);
}

void constructie_vector(int **a, int i, int d, int *b)
{
	//vector bytes
	char *byte = (char *)&a[i][0] + d * 4;
	for (int i = 0; i <= 3; ++i) {
		b[i] = *byte;
		byte++;
	}
}

double task_1(int **a, int *v, int n)
{
	int S = 0, b[4], nr = 0;
	//suma contur
	for (int i = 0; i < n; ++i) {
		if (i == 0 || i == n - 1) {
			for (int j = 0; j < v[i]; ++j) {
				constructie_vector(a, i, j, b);
				S += b[0] + b[1] + b[2] + b[3];
				nr += 4;
			}
		} else {
			constructie_vector(a, i, 0, b);
			S = S + b[0];
			constructie_vector(a, i, v[i] - 1, b);
			S = S + b[3];
			nr += 2;
		}
	}
	double m_a = (double)S / nr;
	return m_a;
}

void modif(int **a, int *v, int d, int lin, int col)
{
	//comanda modify
	int mod, nr = 0, last;
	scanf("%X", &mod);
	nr = (col * d) / 4;
	if ((col * d) % 4 == 0)
		nr--;
	if (nr + 1 > v[lin]) {
		last = v[lin];
		v[lin] = nr + 1;
		int *tmp = realloc(a[lin], v[lin] * sizeof(int));
		if (tmp)
			a[lin] = tmp;
		else
			exit(0);
		for (int i = last; i < v[lin]; ++i)
			a[lin][i] = 0;
	}
	char *mod_p = (char *)&mod;
	char *byte = (char *)&a[lin][0] + d * (col - 1);
	for (int i = 0; i < d; i++) {
		*byte = *(mod_p + i);
		byte++;
	}
}

void del(int **a, int d, int lin, int col)
{
	//comanda delete
	char *byte = (char *)&a[lin][0] + d * (col - 1);
	for (int i = 0; i < d; i++) {
		*byte = 0;
		byte++;
	}
}

void schimb(int **a, int d, int lin, int col)
{
	//comanda swap
	char *byte = (char *)&a[lin][0] + d * col;
	for (int i = 0; i < d / 2; i++) {
		char tmp = *(byte + i);
		*(byte + i) = *(byte + d - i - 1);
		*(byte + d - i - 1) = tmp;
		byte += i;
	}
}

void task2(int **a, int *v)
{
	char comm, dim;
	int marime;
	int col; //bloc de date
	int lin; //linie
	scanf(" %c %c", &comm, &dim);
	scanf("%d%d", &lin, &col);
	if (dim == 'S')
		marime = 2;
	else if (dim == 'C')
		marime = 1;
	else if (dim == 'I')
		marime = 4;
	switch (comm) {
	case 'M':
		modif(a, v, marime, lin, col);
		break;
	case 'D':
		del(a, marime, lin, col);
		break;
	case 'S':
		schimb(a, marime, lin, col);
		break;
	}
}

void fill(int i, int j, int **mat, int nr)
{
	mat[i][j] = nr; //nr zona
	if (mat[i - 1][j] == 1)
		fill(i - 1, j, mat, nr);
	if (mat[i][j + 1] == 1)
		fill(i, j + 1, mat, nr);
	if (mat[i + 1][j] == 1)
		fill(i + 1, j, mat, nr);
	if (mat[i][j - 1] == 1)
		fill(i, j - 1, mat, nr);
}

void task3(int **mat, int n, int *v)
{
	int nr = 0, max = 0, gasit, ok = 0;
	//declarare zone de zero
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= v[i - 1] * 4; ++j) {
			if (mat[i][j] == 1) {
				nr++; //nr zona
				if (nr == 1)
					fill(i, j, mat, -1);
				else
					fill(i, j, mat, nr);
				}
		}
	int *arie = aloc_vect(nr + 1);
	//vector arii zone
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= v[i - 1] * 4; ++j) {
			if (mat[i][j] != 0)
				arie[abs(mat[i][j])]++;
		}
	//arie maxima
	for (int i = 1; i <= nr; ++i) {
		if (arie[i] > max) {
			gasit = i;
			max = arie[i];
		}
	}
	//poz initala
	for (int i = 1; i <= n && ok == 0; ++i)
		for (int j = 1; j <= v[i - 1] * 4 && ok == 0; ++j)
			if (abs(mat[i][j]) == gasit) {
				printf("%d %d ", i - 1, j - 1);
				ok = 1;
			}

	printf("%d\n", max);
	free(arie);
}

int main(void)
{
	int n, nrcom, b[4], max = 0;
	scanf("%d", &n);
	int *v = aloc_vect(n);
	//alocare matrice harta
	int **a = (int **)calloc(n, sizeof(int *));
	//citire harta
	for (int i = 0; i < n; ++i) {
		//vector nr elemente pe linie
		scanf("%d", &v[i]);
		aloc_matrice_lin(v, a, i);
		for (int j = 0; j < v[i]; ++j)
			scanf("%X", &a[i][j]);
	}
	if (!a) {
		fprintf(stderr, "calloc() failed\n");
		return -1;
	}
	//medie aritmetica contur
	double m_a = task_1(a, v, n);
	scanf("%d", &nrcom); //nr comenzi
	for (int i = 1; i <= nrcom; ++i)
		task2(a, v);

	printf("task 1\n");
	printf("%0.9lf\n", m_a);
	printf("task 2\n");
	//scriere matrice modificata
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < v[i]; ++j)
			printf("%08X ", a[i][j]);
		printf("\n");
	}

	//matricea divizarii nr hexa
	printf("task 3\n");
	for (int i = 0; i < n; i++)
		if (v[i] > max)
			max = v[i];
	//alocare matrice gauri negre
	int **mat = aloc_matrice(n, max);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < v[i]; j++) {
			constructie_vector(a, i, j, b);
			for (int k = 0; k <= 3; k++)
				if (b[k] == 0) {
					//memorare elemente egale cu 0
					mat[i + 1][j * 4 + k + 1] = 1;
				} else {
					mat[i + 1][j * 4 + k + 1] = 0;
				}
		}
	}
	//dealocare matrice harta
	free_matrice(n, a);
	task3(mat, n, v);
	//dealocare matrice divizare
	free_matrice(n + 2, mat);
	free(v);
	return 0;
}
