#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

#define BASENUM 64

using namespace std;

typedef long long myint;

bool bBase[BASENUM] = {
	false,
};
void prepareToCheckSquare()
{
	for (int i = 0; i < BASENUM; i++)
	{
		bBase[i * i % BASENUM] = true;
	}
}
inline bool IsSquare(myint num)
{
	if (bBase[(myint)(num & (BASENUM - 1))])
	{
		myint temp = (myint)(sqrt((long double)num) + 0.5);
		return (temp * temp == num);
	}
	else return false;
}

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int n;
	cin>>n;
	vector<int> v(n);
	for(int i = 0;i<n;i++) {
		cin>>v[i];
	}
	prepareToCheckSquare();
	sort(v.begin(),v.end(),[](int &a,int &b) {
		myint sum = (myint)a *(myint)b;
		int res = IsSquare(sum);
		return res;
	});
	/*for(int i = 0;i<n;i++) {
		cout<<v[i]<<' ';
	}*/
	for(int i = 1;i<n;i++) {
		if(v[i] < v[i-1]) {
			cout<<"NO";
			return 0;
		}
	}
	cout<<"YES";
	return 0;
}