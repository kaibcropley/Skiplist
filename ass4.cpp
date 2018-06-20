//
// Created by Kaib Cropley on 5/7/2018.
// Last edited by Kaib Cropley on 5/13/2018.
//

#include <iostream>
#include <cassert>
#include "skiplist.h"

using namespace std;

// Test add and contains method
void test1() {
	SkipList sl(10);
	for (int i{0}; i < 25; i++) {
		sl.Add(i);
	}
	//cout << sl;
	for (int i{0}; i < 25; i++) {
		assert(sl.Contains(i));
	}
}

// Test contains method when it is false
void test2() {
	SkipList sl(10);
	for (int i{0}; i < 25; i++) {
		sl.Add(i);
	}
	//cout << sl;
	for (int i{0}; i < 25; i++) {
		assert(!sl.Contains(i + 100));
	}
}

// Test small empty list size
void test3() {
	SkipList sl2(1);
}

// Test Remove function
void test4() {
	SkipList sl(3);
	for (int i{0}; i < 25; i++) {
		sl.Add(i);
	}
//	cout << "_____________________" << endl;
//	cout << sl;
//	cout << "_____________________" << endl;
	assert(sl.Contains(14));
	assert(sl.Remove(14));
//	cout << "_____________________" << endl;
//	cout << sl;
//	cout << "_____________________" << endl;


	assert(sl.Contains(0));
	assert(sl.Remove(0));
//	cout << "_____________________" << endl;
//	cout << sl;
//	cout << "_____________________" << endl;

	assert(sl.Contains(24));
	assert(sl.Remove(24));
//	cout << "_____________________" << endl;
//	cout << sl;
//	cout << "_____________________" << endl;

//	cout << sl;
}

// Tests a high depth. Functions: add, remove, contains both true and false
void test5() {
	SkipList s(15);
	for (int i = 0; i < 20; ++i) {
		int number = rand() % 100;
		assert(s.Add(number));
		assert(s.Contains(number));
		assert(s.Remove(number));
		assert(!s.Contains(number));
	}
}

// Runs all test
void testAll() {
	// My tests
	test1();
	test2();
	test3();
	test4();
	test5();

	cout << "All test successful" << endl;
}

int main() {
	testAll();
	std::cout << "Done" << std::endl;
	return 0;
}
