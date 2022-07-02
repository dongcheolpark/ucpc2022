#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class point{
public:
	int x;
	int y;
	bool operator>(point&p) {
		if(this->x > p.x) {
			return true;
		}
		else if(this->x == p.x) {
			return this->y > p.y;
		}
		return false;
	}
};

class Line {
public:
	point a;
	point b;
	int w;
};


int ccw(point a,point b,point c) {
	int res = (b.x-a.x)*(c.y-a.y) - (b.y-a.y)*(c.x-a.x);
	return res > 0 ? 1 : (res == 0 ? 0 : -1);
}

void swap(int& a,int& b) {
	int tmp = a;
	a = b;
	b = tmp;
}

int lineInterect(Line& l1,Line& l2) {
	auto a = l1.a,b = l1.b,c = l2.a,d = l2.b;
	int ab = ccw(a, b, c) * ccw(a, b, d);
	int cd = ccw(c, d, a) * ccw(c, d, b);

	if(ab == 0 && cd == 0) {
		if(a > b) swap(a,b);
		if(c > d) swap(c,d);
		return !(c>b)&&!(a>d);
	}
	return !(ab>0) && !(cd>0);
}

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int n;
	cin>>n;
	vector<Line> v;
	vector<pair<vector<int>,int>> countV;
	vector<bool> visit(n,false);
	v.resize(n);
	countV.resize(n);
	for(int i = 0;i<n;i++) {
		cin>>v[i].a.x>>v[i].a.y>>v[i].b.x>>v[i].b.y>>v[i].w;
	}
	for(int i = 0;i<n;i++) {
		for(int j = 0;j<n;j++) {
			countV[i].second = i;
			if(i==j) continue;
			if(lineInterect(v[i],v[j])) {
				countV[i].first.push_back(j);
			}
		}
	}

	sort(countV.begin(),countV.end(),[v](pair<vector<int>,int>&a,pair<vector<int>,int>&b) {
		if(a.first.size() == b.first.size()) {
			return v[a.second].w < v[b.second].w;
		}
		return a.first.size() > b.first.size();
	});

	for(int i = 0;i<n;i++) {
		cout<<countV[i].second<<' ';
		for(auto item : countV[i].first) {
			cout<<item<<' ';
		}
		cout<<'\n';
	}

	int res = 0;
	for(int i = 0;i<n;i++) {
		int sum = (1<<31)-1;
		int x = i;
		for(int j = 0;j<n;j++) {
			if(visit[j]) continue;
			int tmp = (countV[j].first.size()+1)*v[countV[j].second].w;
			if(sum > tmp) {
				sum = tmp;
				x = j;
			}
		}
		res += sum;
		visit[x] = true;
		for(int j = 0;j<n;j++) {
			for(auto k = countV[j].first.begin();k<countV[j].first.end();k++) {
				if(*k == countV[x].second) {
					countV[j].first.erase(k);
				}
			}
		}
	}
	cout<<res;
	return 0;
}