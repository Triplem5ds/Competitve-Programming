#include <bits/stdc++.h>

using namespace std;

int con(string s){
	istringstream iss(s);
	int x;
	iss >> x;
	return x;
}

int get(string s){
	if(s == "cups")return 48;
	if(s == "Tbsp")return 3;
	return 1;
}
map<string, int>needed;
map<string, int>have;
map<string, int>lft;
map<string, int>order;

bool chk(int hi, int lo){

	for(auto it : needed){
		if((it.second * hi)%lo)return 0;
		if(it.second * hi/lo < have[it.first])return 0;
	}

	return 1;
}

string con2(int x){
	stringstream ss;
	ss << x;
	return ss.str();
}

bool cmp(string a, string b){
	
	string x, y;
	
	int ptr = a.size() - 1;
	
	while(a[ptr] != ' ')x.push_back(a[ptr--]);

	ptr = b.size() - 1;
	
	while(b[ptr] != ' ')y.push_back(b[ptr--]);
	
	reverse(x.begin(), x.end());
	reverse(y.begin(), y.end());
	
	return order[x] < order[y];
}

class Recipe {
public:
	vector <string> fix(vector <string> recipe, vector <string> mixingBowl) {

		have.clear();
		needed.clear();
		lft.clear();
		int cnt = 0;

		for(auto v : recipe){

			istringstream iss(v);

			vector<string>elements;
			string s;

			while(iss >> s)elements.push_back(s);

			int quantity = get(elements[1]) * con(elements[0]);

			needed[elements[2]] = quantity;
			have[elements[2]];
			order[elements[2]] = cnt++;

		}
		for(auto v : mixingBowl){

			istringstream iss(v);

			vector<string>elements;
			string s;

			while(iss >> s)elements.push_back(s);

			int quantity = get(elements[1]) * con(elements[0]);

			have[elements[2]] = quantity;

		}

		
		int hi = 1000000, lo = 1;
					
		for(int i = 1; i <= 10000; i++){
			
			for(int j = 1; j <= i; j++)
				if(chk(i, j) && (double)i/j < (double)hi/lo)hi = i, lo = j;
		
		
		}

		for(auto &it : needed)
			it.second *= hi, it.second/=lo;

		for(auto &it : needed)
			lft[it.first] = it.second - have[it.first];

		vector<string>ans;

		for(auto it : lft){

			int diff = it.second;

			if(!diff)continue;

			array<int, 3>a;

			a[0] = diff/48;
			diff %= 48;
			a[1] = diff/3;
			diff %= 3;
			a[2] = diff;

			string out;

			if(a[0])out += con2(a[0]) + " cups ";
			if(a[1])out += con2(a[1]) + " Tbsp ";
			if(a[2])out += con2(a[2]) + " tsp ";

			if(a[0] || a[1] || a[2])
				out += it.first;

			if(out.size())ans.push_back(out);

		}

		sort(ans.begin(), ans.end(), cmp);

		return  ans;
	}
};
