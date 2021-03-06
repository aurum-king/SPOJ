#include <cstdio>
#include <algorithm>
#include <stack>

#define INF 1e9

using namespace std;

int main( void )
{
	int T;
	scanf("%d",&T);
	while( T-- ) {
		int N,M,*A;
		long long sum = 0,minpage;
		scanf("%d%d",&N,&M);
		stack< int > pos;
		A = new int[ N + 1 ];
		for( int i = 1; i <= N; i++ ) {
			scanf("%d",A + i );
			sum += A[ i ];
		}
		minpage = sum;
		for( long long i = 0, j = sum; i <= j; ) {
			long long mid = ( i + j ) / 2, S = 0, maxpage = 0;
			int num = 0;
			for( int k = 1; k <= N; k++ ) {
				if( S + A[ k ] > mid ) {
					S = 0;
					num++;
				}
				S += A[ k ];
				maxpage = max( S, maxpage );
			}
			if( num < M ) {
				j = mid - 1;
				minpage = min( maxpage, minpage );
			} else {
				i = mid + 1;
			}
		}
		sum = 0;
		for( int i = N; i > 0; i-- ) {
			sum += A[ i ];
			if( M == i + 1 ) {
                                while( i > 0 ) {
					pos.push( -1 ); 
                                       	pos.push( A[ i ] );                                
                                        i--;
                                }
				break;
                        }
			if( sum > minpage ) {
				sum = A[ i ];
				pos.push( -1 );
				M--;
			}
			pos.push( A[ i ] );
		}
		if( pos.top() == -1 ) {
			pos.pop();
		}
		printf( "%d",pos.top() );
		pos.pop();
		while( !pos.empty() ) {
			if( pos.top() == -1 ) {
				printf(" /");
			} else {
				printf(" %d",pos.top() );
			}
			pos.pop();
		}
		printf("\n");
	}
	return 0;
}
