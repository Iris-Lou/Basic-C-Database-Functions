#include <iostream>
#include<algorithm>
#include<fstream>
#include<sstream>
#include<ctype.h>
#include<utility>
#include"dataBase.h"
using namespace std;

dataBase::dataBase(ifstream &is1, ifstream &is2) {
	string text;
	vector<string>line;
	getline(is1, text);
	while (getline(is1, text))
		line.push_back(text);
	for (auto p : line) {
		istringstream sep_line(p);
		string id, name, sex, birthday, school_year, birthplace;
		while (sep_line >> id >> name >> sex >> birthday >> school_year >> birthplace) {
			ids.insert(id);
			self_info.insert(Pair(id, name));
			self_info.insert(Pair(id, sex));
			self_info.insert(Pair(id, birthday));
			self_info.insert(Pair(id, school_year));
			school_year_.insert(Pair(school_year, id));
			self_info.insert(Pair(id, birthplace));
		}
	}
	line.clear();
	getline(is2, text);
	while (getline(is2, text))
		line.push_back(text);
	for (auto p : line) {
		istringstream sep_line(p);
		string id;
		sep_line >> id;
		string word;
		vector<string>courses;
		while (sep_line >> word) {
			if (isalpha(word[0]))
				courses.push_back(word);
			else if (word.size() == 2) {
				self_info.insert(Pair(id, word));
				score.insert(Pair(word, id));
			}
			else
				self_info.insert(Pair(id, word));
		}
		string course;
		for (auto p : courses)
			course = course + p + ' ';
		self_info.insert(pair<string, string>(id, course));
		course_.insert(pair<string, string>(course, id));
		courses.clear();
	}
}

bool compare(const Pair &p1, const Pair &p2) { return p1.second < p2.second; }

void dataBase::PrintSort() {
	vector<Pair>sort_temp;
	Set::iterator it;
	Map::iterator iter;
	for (it = ids.begin(); it != ids.end(); ++it) {
		iter = self_info.find(*it);
		for (int i = 0; i != self_info.count(*it); i++, iter++) {
			if (i == type_no) {
				sort_temp.push_back(Pair(iter->first, iter->second));
				break;
			}
		}
	}
	sort(sort_temp.begin(), sort_temp.end(), compare);

	for (auto p : sort_temp) {
		iter = self_info.find(p.first);
		for (int i = 0; i != self_info.count(p.first); i++, iter++) {
			if (i == 0)
				cout << iter->first << "\t";
			cout << iter->second << "\t";
		}
		cout << endl << endl;
	}
}

void dataBase::Print() {
	Set::iterator it;
	for (it = ids.begin(); it != ids.end(); ++it) {
		Map::iterator iter;
		iter = self_info.find(*it);
		for (int i = 0; i != self_info.count(*it); i++, iter++) {
			if (i == 0)
				cout << iter->first << "\t";
			cout << iter->second << "\t";
		}
		cout << endl << endl;
	}
}

void dataBase::searchById(const string&p) {
	cout << p << '\t';
	Map::iterator beg, end;
	beg = self_info.lower_bound(p);
	end = self_info.upper_bound(p);
	for (auto m = beg; m != end; m++) {
		cout << m->second << "\t";
	}
	cout << endl << endl;
}

vector<string> Only_For_Search(const string&s, const Map*map_) {
	vector<string>id_search;
		auto begPtr = (*map_).lower_bound(s);
		auto endPtr = (*map_).upper_bound(s);
		for (auto ptr = begPtr; ptr != endPtr; ptr++) {
			auto p = ptr->second;
			id_search.push_back(p);
		}
	return id_search;
}

void dataBase::search(const string&s, const Map*map_) {
	auto vec = Only_For_Search(s, map_);
	for (auto p : vec) {
		;
		auto beg = self_info.lower_bound(p);
		auto end = self_info.upper_bound(p);
		int i = 0;
		for (auto m = beg; m != end; m++, i++) {
			if (i == 0)
				cout << m->first << "\t";
			cout << m->second << "\t";
		}
		cout << endl;
	}
	cout << endl;
}

void dataBase::searchBySchool_year(const string&s) { search(s, &school_year_); }
void dataBase::searchByScore(const string&p) { search(p, &score); }
void dataBase::searchByCourse(const string&s) { search(s, &course_); }

void dataBase::deleteById(const string&p) { self_info.erase(p); }

void dataBase::delete_pattern(const string&p, const Map*map_) {
	vector<string>vec = Only_For_Search(p, map_);
	for (auto p : vec)
		deleteById(p);
}

void dataBase::deleteByCourse(const string&p) { delete_pattern(p, &course_); }
void dataBase::deleteBySchool_year(const string&p) { delete_pattern(p, &school_year_); }
void dataBase::deleteByScore(const string &p) { delete_pattern(p, &score); }

void dataBase::conditionalSearch(const string&p) {
	vector<string>operator_;
	vector<string>object;
	auto pos1 = p.find_first_not_of(" ");
	auto pos2 = p.find_first_of(" ");
	while (pos1 != string::npos) {
		string word(p, pos1, pos2 - pos1);
		if (ispunct(word[0]))
			operator_.push_back(word);
		else
			object.push_back(word);
		pos1 = p.find_first_not_of(" ", pos2);
		pos2 = p.find_first_of(" ", pos1);
	}
	int condition = 1;
	vector<string>con;
	for (unsigned i = 0; i < operator_.size();i++) {
		if (i % 2 == 0) {
			unsigned t;
			if (i == 0)
				t = 1;
			else
				t = 2 * i;
			if (object.at(t-1) == "id") {
				if (operator_.at(i) == ">=") {
					for (auto ptr = self_info.begin(); ptr != self_info.end(); ptr++) {
						if (ptr->first < object.at(t))
							deleteById(ptr->first);
					}
				}
				else if (operator_.at(i) == "==")
					deleteById(object.at(t));
				else if (operator_.at(i) == "<=") {
					for (auto ptr = self_info.begin(); ptr != self_info.end(); ptr++) {
						if (ptr->first > object.at(t))
							deleteById(ptr->first);
					}
				}
			}
			else if (object.at(t - 1) == "score") {
				if (operator_.at(i) == ">=") {
				}
			}
		}
	}

}
