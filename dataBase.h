#ifndef DATABASE_H
#define DATABASE_H
#include <string>
#include <map>
#include<vector>
#include<set>
using namespace std;

typedef pair<string, string>Pair;
typedef set<string>Set;
typedef multimap<string, string> Map;

class dataBase {
public:
	dataBase(ifstream &is1, ifstream &is2);
	~dataBase() {}
	/* Sort functions, in a ascending order */
	void SortByName() {
		type_no = 0;
		PrintSort();
	}
	void SortBySex() {
		type_no = 1;
		PrintSort();
	}
	void SortByBirthday() {
		//In ascending order of age
		type_no = 2;
		PrintSort();
	}
	void SortBySchool_year() {
		type_no = 3;
		PrintSort();
	}
	void SortByBirthplace() {
		type_no = 4;
		PrintSort();
	}
	void SortByCourse() {
		type_no = 5;
		PrintSort();
	}
	void SortByCredits() {
		type_no = 6;
		PrintSort();
	}
	void SortByScore() {
		type_no = 7;
		PrintSort();
	}
	void Print();
	void PrintSort();

	/* Search functions */
	void search(const string&p, const Map*map_);
	void searchById(const string&p);
	void searchByCourse(const string&p);
	void searchBySchool_year(const string&p);
	void searchByScore(const string&p);

	/* Delete functions */
	void deleteById(const string&p);
	void delete_pattern(const string&p, const Map*map_);
	void deleteByCourse(const string&p);
	void deleteBySchool_year(const string&p);
	void deleteByScore(const string &p);

	void conditionalSearch(const string&p);

private:
	int d;
	Map self_info;
	Set ids;
	Map school_year_;
	Map score;
	Map course_;
	int type_no;
};
#endif // !DATABASE.H

