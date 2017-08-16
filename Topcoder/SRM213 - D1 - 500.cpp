#include <bits/stdc++.h>

using namespace std;

bool isLeap(int x){

	if(x%4 == 0){
		if(x%100 == 0 && x % 400)return 0;
		return 1;
	}

	return 0;

}

int days[2][12] = {{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

map<string, int> mp{{"Jan", 0}, {"Feb", 1}, {"Mar", 2}, {"Apr",3}, {"May", 4}, {"Jun",5}, {"Jul", 6}, {"Aug",7}, {"Sep", 8}, {"Oct", 9}, {"Nov", 10}, {"Dec", 11}};



pair<int, bool>hours[24] = {{12, 0},
							{1, 0},
							{2, 0},
							{3, 0},
							{4, 0},
							{5, 0},
							{6, 0},
							{7, 0},
							{8, 0},
							{9, 0},
							{10, 0},
							{11, 0},
							{12, 1},
							{1, 1},
							{2, 1},
							{3, 1},
							{4, 1},
							{5, 1},
							{6, 1},
							{7, 1},
							{8, 1},
							{9, 1},
							{10, 1},
							{11, 1}
							};

struct date{

	int day, month, year, hour, minute, second;
	bool state;

	void fix(){

		int idx = 0;

		if(second == 60){
			second = 0;
			minute++;
		}
		if(minute == 60){
			minute = 0;

			for(int i = 0; i < 24; i++){

				if(make_pair(hour, state) == hours[i])idx = i;

			}

			if(idx == 23)day++;

			hour = hours[(idx + 1)%24].first;
			state = hours[(idx + 1)%24].second;

		}


		if(hour == 13){
      hour = 1;
		}

		if(day > days[isLeap(year)][month]){
			month++;
			day = 1;
		}
		if(month == 12){
			month = 0;
			year++;
		}



	}

	bool operator > (date other){
		if(year > other.year)return 1;
		if(year < other.year)return 0;
		if(month > other.month)return 1;
		if(month < other.month)return 0;
		if(day > other.day)return 1;
		if(day < other.day)return 0;
		int idx1 = 0, idx2 = 0;

		for(int i = 0; i < 24; i++){

			if(make_pair(hour, state) == hours[i])idx1 = i;
			if(make_pair(other.hour, other.state) == hours[i])idx2 = i;

		}
		if(idx1 > idx2)return 1;
		if(idx1 < idx2)return 0;
		if(minute > other.minute)return 1;
		if(minute < other.minute)return 0;
		if(second > other.second)return 1;
		return 0;
	}

};

int con(string s){
	while(s[0] == '0')s.erase(s.begin());
	if(s.size() == 0)s = "0";
	istringstream iss(s);
	int x;
	iss >> x;
	return x;
}

//#d month #year at #hr:#min:#sec (PM - AM)

string get_nxt(int &ptr, string s){
	string ret = "";
	while(s[ptr] != ' ')ret.push_back(s[ptr++]);
	return ret;
}

date get(string x){

	date ret;

	x = x + " ";
	int ptr= 0;

	for(auto &c : x)if(c == ':')c = ' ';

	ret.day = con(get_nxt(ptr, x));
	ptr++;
	ret.month = mp[get_nxt(ptr, x)];
	ptr++;
	ret.year = con(get_nxt(ptr, x));
	ptr++;
	get_nxt(ptr, x);
  ptr++;
  ret.hour = con(get_nxt(ptr, x));
	ptr++;
	ret.minute = con(get_nxt(ptr, x));
	ptr++;
	ret.second = con(get_nxt(ptr, x));
	ptr++;

	ret.state = (get_nxt(ptr, x) == "AM" ? 0 : 1);



	return ret;
}
string con(int x){
	stringstream ss;
	ss << x;
	return ss.str();
}

void out(date lo){
    cout << lo.year << ' ' << lo.month << ' ' << lo.day << ' ' << lo.hour << ' ' << lo.minute << ' ' << lo.second << ' ' << lo.state << '\n';
		system("pause");
}
class Uptime {
public:
	string calcUptime(string started, string now) {

		date lo = get(started);
		date hi = get(now);

		//out(lo);

		int days = 0, hours = 0, minutes = 0, seconds = 0;
		date tmp;
		while(true){
			tmp = lo;
			lo.day++;
			lo.fix();
		//	out(lo);
			if(lo > hi){
				lo = tmp;
				break;
			}
			days++;
		}
		while(true){
			tmp = lo;
			lo.hour++;
			if(lo.hour==12){
        if(lo.state == 0)lo.state = 1;
        else lo.state = 0, lo.day++;
			}
			lo.fix();
			if(lo > hi){
				lo = tmp;
				break;
			}
			hours++;
		}
		while(true){
			tmp = lo;
			lo.minute++;
			lo.fix();
			if(lo > hi){
				lo = tmp;
				break;
			}
			minutes++;
		}
		while(true){
			tmp = lo;
			lo.second++;
			lo.fix();
			if(lo > hi){
				lo = tmp;
				break;
			}
			seconds++;
		}

		string ans = "";

		if(days)ans += con(days) + "d ";
		if(hours)ans += con(hours) + "h ";
		if(minutes)ans += con(minutes) + "m ";
		if(seconds)ans += con(seconds) + "s ";
		if(ans.size())ans.pop_back();
		return ans;
	}
};
