#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
 
#define MAXN 10100
#define MAXK 210
#define MOD 1000000009LL
#define AB 26
 
using namespace std;
 
typedef long long ll;
 
vector< ll > hashes;
int memo[ MAXN + 1 ][ MAXK + 1 ][ 2 ], maxl, N, M, K;
char S[ MAXN + 1 ];
 
ll hash_it( char* A )
{
	ll hash = 0;
	for( int i = 0; i < strlen( A ); i++) {
		hash = ( ll )( hash * AB ) % MOD;
		hash = ( ll )( hash + ( int )( A[ i ] - 'a' ) ) % MOD;
	}
	return hash;
}
 
bool exist( ll hash )
{
	int lo = 0, hi = hashes.size() - 1, idx = 0;
	while( lo <= hi ) {
		int mid = ( lo + hi ) / 2;
		if( hashes[ mid ] <= hash ) {
			lo = mid + 1;
			idx = mid;
		} else {
			hi = mid - 1;
		}
	}
	return hashes[ idx ] == hash;
}
 
int dp( int n, int k, int bit )
{
	if( memo[ n ][ k ][ bit ] != -1 ) return memo[ n ][ k ][ bit ];
	if( k > K ) return memo[ n ][ k ][ bit ] = 0;
	if( n == N ) return memo[ n ][ k ][ bit ] = 1;
	memo[ n ][ k ][ bit ] = 0;
	if( !bit ) { // 0 is a noise
		memo[ n ][ k ][ bit ] = max( dp( n + 1, k + 1, !bit ), dp( n + 1, k, bit ) );
	} else { // 1 is not a noise
		ll newhash = 0;
		for( int i = n; i < min( N, n + maxl ); i++ ) {
			newhash = ( ll )( newhash * AB ) % MOD;
			newhash = ( ll )( newhash + S[ i ] - 'a' ) % MOD;
			if( exist( newhash ) ) {
				memo[ n ][ k ][ bit ] = max( memo[ n ][ k ][ bit ], 1 + max( dp( i + 1, k, bit ), dp( i + 1, k + 1, !bit ) ) );
			}
		}
	}
	return memo[ n ][ k ][ bit ];
}
 
int main( void )
{
	int T;
	//freopen("test.in","rt",stdin);
	scanf("%d", &T );
	while( T-- ) {
		hashes.clear();
		maxl = 0;
		memset( memo, -1, sizeof( memo ) );
		scanf("%d%d%s", &M, &K, S );
		N = strlen( S );
		for( int i = 0; i < M; i++ ) {
			char str[ MAXN + 1 ];
			scanf("%s", str );
			maxl = max( maxl, ( int )strlen( str ) );
			hashes.push_back( hash_it( str ) );
		}
		sort( hashes.begin(), hashes.end() );
		printf("%d\n", max( dp( 0, 0, 0 ), dp( 0, 0, 1 ) ) );
	}
	return 0;
}
