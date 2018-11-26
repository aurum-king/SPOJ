#include <cstdio>
#include <algorithm>
#include <ctime>

using namespace std;

int main( void )
{
	freopen("test.in","wt",stdout);
	srand( time( NULL ) );
	int N = 1000, M = 300000;
	printf("%d\n%d\n", N, M );
	for( int i = 0; i < M; i++ ) {
 		int u = rand() % N + 1;
		int v = rand() % N + 1;
		printf("%d %d\n", u, v );
	}
	return 0;
}
