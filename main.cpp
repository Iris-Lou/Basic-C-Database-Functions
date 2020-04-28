#include<fstream>
#include<sstream>
#include <iostream>
#include"dataBase.h"

void Test() {
	ifstream file1("StudentInfo.txt");
	ifstream file2("StudentCourse.txt");
	dataBase test(file1, file2);
	cout << "ÒÀ´ÎÎª id\tname\tsex\tbirthday\tschool_year\tcredit\tscore\tcourse" << endl;
	cout << "--------------------------------------SortById-----------------------------------------" << endl;
	test.Print();
	cout << "--------------------------------------SortByBirthday-----------------------------------------" << endl;
	test.SortByBirthday();
	test.Print();
	cout << "--------------------------------------SortByBirthplace-----------------------------------------" << endl;
	test.SortByBirthplace();
	test.Print();
	cout << "--------------------------------------SortBySchool_year-----------------------------------------" << endl;
	test.SortBySchool_year();
	test.Print();
	cout << "--------------------------------------SortByScore-----------------------------------------" << endl;
	test.SortByScore();
	test.Print();
	cout << "--------------------------------------SortByCourse-----------------------------------------" << endl;
	test.SortByCourse();
	test.Print();
	cout << "--------------------------------------SortByName-----------------------------------------" << endl;
	test.SortByName();
	test.Print();
	cout << "--------------------------------------SortByCredits-----------------------------------------" << endl;
	test.SortByCredits();
	test.Print();
	cout << "--------------------------------------SearchId-----------------------------------------" << endl;
	test.searchById("10905");
	cout << "--------------------------------------SearchCourse-----------------------------------------" << endl;
	test.searchByCourse("Python ");
	cout << "--------------------------------------SearchSchool_year-----------------------------------------" << endl;
	test.searchBySchool_year("2017");
	cout << "--------------------------------------SearchScore-----------------------------------------" << endl;
	test.searchByScore("79");
	cout << "--------------------------------------deleteById-----------------------------------------" << endl;
	test.deleteById("10905");
	test.Print();
	cout << "------------------------------------deleteByCourse------------------------------------" << endl;
	test.deleteByCourse("Python ");
	test.Print();
	cout << "------------------------------------deleteBySchool_year------------------------------------" << endl;
	test.deleteBySchool_year("2016");
	test.Print();
	cout << "------------------------------------deleteByScore------------------------------------" << endl;
	test.deleteByScore("79");
	test.Print();
	//test.conditionalSearch("id >= 10914");
}

int main() {
	Test();
	return 0;
}
