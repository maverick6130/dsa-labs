#include<stdio.h>
#include <unordered_map>
#include<vector>
#include<set>
#include<climits>
#include<algorithm>
#include<iterator>
using namespace std;

struct course {
	int slot;
	int cap;
	set<string> students;
	course(int s,int c) : slot(s) {
		if(c==-1)
			cap=INT_MAX;
		else
			cap=c;
	}
	bool is_free() {
		return (students.size()<cap);
	}
};

struct student {
	set<string> courses;
	vector<bool> slots;
	student() {
		courses = set<string> ();
		slots = vector<bool> (21,false);
	}
};

int main() {

	int nc,ns,reglim,t;
	
	scanf(" %d %d %d %d",&nc,&ns,&reglim,&t);
	
	unordered_map<string,course> courses;
	unordered_map<string,student> students;
	
	while(nc--) {
		char str[7];
		scanf(" %6s",str);
		int slot,lim;
		scanf(" %d %d",&slot,&lim);
		courses.insert(pair<string,course>(string(str),course(slot,lim)));
	}
	while(ns--) {
		char str[10];
		scanf(" %9s",str);
		students.insert(pair<string,student> (string(str),student()));
	}

	while(t--) {
		
		char op;
		scanf(" %c",&op);
		char rno[10],cno[7];
		
		if(op=='R') {
			scanf(" %s %s",rno,cno);
			auto roll = students.find(string(rno));
			auto crs = courses.find(string(cno));
			if((roll!=students.end()) && (crs!=courses.end())) {
				if(roll->second.courses.size()==reglim) {
					printf("fail\n");
				}
				else if(roll->second.courses.find(crs->first)!=roll->second.courses.end()) {
					printf("fail\n");
				}
				else if (!crs->second.is_free()) {
					printf("fail\n");
				}
				else if (roll->second.slots[crs->second.slot]) {
					printf("fail\n");
				}
				else {
					roll->second.slots[crs->second.slot]=true;
					roll->second.courses.insert(crs->first);
					crs->second.students.insert(roll->first);
					printf("success\n");
				}
			}
			else {
				printf("fail\n");
			}
		}
		
		else if (op=='D') {
			scanf(" %s %s",rno,cno);
			auto roll = students.find(string(rno));
			auto crs = courses.find(string(cno));
			if((roll!=students.end()) && (crs!=courses.end())) {
				if(roll->second.courses.erase(crs->first)!=0) {
					roll->second.slots[crs->second.slot]=false;
					crs->second.students.erase(roll->first);
					printf("success\n");
				}
				else {
					printf("fail\n");					
				}
			}
			else {
				printf("fail\n");
			}
		}
		
		else {
			char line[20];
			scanf(" %[^\n]s",line);
			string input(line);
		
			if(input.size()==6) {
				// course info
				auto crs = courses.find(input);
				if(crs!=courses.end()) {
					for(auto x : crs->second.students) {
						printf("%s ",x.c_str());
					}
					printf("\n");
				}
			}
		
			else if(input.size()==9) {
				// student info
				auto roll = students.find(input);
				if(roll!=students.end()) {	
					for(auto x : roll->second.courses) {
						printf("%s ",x.c_str());
					}
					printf("\n");
				}
			}
		
			else if(input.size()==19) {
				// common courses in students
				auto roll1 = students.find(input.substr(0,9));
				auto roll2 = students.find(input.substr(10,9));
				if((roll1!=students.end()) && (roll2!=students.end())) {
					vector<string> x;
					set_intersection(roll1->second.courses.begin(),roll1->second.courses.end(),roll2->second.courses.begin(),roll2->second.courses.end(),back_inserter(x));
					for(auto i : x) {
						printf("%s ",i.c_str());
					}
					printf("\n");
				}
			}
		
			else if(input.size()==13){
				// common students in courses
				auto crs1 = courses.find(input.substr(0,6));
				auto crs2 = courses.find(input.substr(7,6));
				if((crs1!=courses.end()) && (crs2!=courses.end())) {
					vector<string> x;
					set_intersection(crs1->second.students.begin(),crs1->second.students.end(),crs2->second.students.begin(),crs2->second.students.end(),back_inserter(x));
					for(auto i : x) {
						printf("%s ",i.c_str());
					}
					printf("\n");
				}
			}
			else {;}
		}
	}
	return 0;
}