#include <bits/stdc++.h>

using namespace std;

set<string>nouns = {"tom", "jerry", "goofy", "mickey", "jimmy", "dog", "cat", "mouse"};
set<string>verb = {"hate", "love", "know", "like",
                  "hates", "loves", "knows", "likes"};
set<string>article = {"a", "the"};

int ptr;

vector<string>statement;

string s;

bool get_Actor(){
  if(ptr == statement.size())return 0;

  if(nouns.find(statement[ptr]) == nouns.end()){

    if(ptr + 1 == statement.size())return 0;

    if(article.find(statement[ptr]) == article.end())return 0;
    ptr++;
    if(nouns.find(statement[ptr]) == nouns.end())return 0;
    ptr++;
    return 1;
  }
  ptr++;
  return 1;
}

bool get_ActiveList(){


  if(ptr == statement.size())return 0;

  if(get_Actor()){


    if(ptr == statement.size())return 1;

    if(statement[ptr] == "and"){
      ptr++;
      get_ActiveList();
    }
    return 1;
  }
  return 0;
}

bool get_Action(){

  if(get_ActiveList()){

    if(ptr == statement.size())return 0;

    if(verb.find(statement[ptr]) == verb.end())return 0;
    ptr++;

    return get_ActiveList();
  }

  return 0;

}
bool get_Statement(){

  if(ptr == statement.size())return 0;

  if(get_Action()){

    if(ptr == statement.size())return 1;
    if(statement[ptr] == ","){
      ptr++;
      return get_Statement();
    }
  }

  return 0;

}

int main(){

  //freopen("out.out", "w", stdout);

  while(getline(cin, s)){

    statement.clear();

    string str;

    s.push_back(' ');

    for(int i = 0; i < s.size(); i++){

      if(s[i] >= 'a' && s[i] <= 'z')str.push_back(s[i]);
      else{
        if(str.size())
          statement.push_back(str);
        str.clear();

        if(s[i] == ' ')continue;

        str.push_back(s[i]);

        statement.push_back(str);

        str.clear();

      }

    }

    ptr = 0;

    if(get_Statement())puts("YES I WILL");
    else
      puts("NO I WON'T");

  }


}

