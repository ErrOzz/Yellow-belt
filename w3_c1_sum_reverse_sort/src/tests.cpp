#include "tests.h"
#include "test_runner.h"
#include "sum_reverse_sort.h"

void TestSum() {
	AssertEqual(Sum(0, 0), 0, "Sum of zeros.");
	AssertEqual(Sum(5, 16), 21, "Sum of positive.");
	AssertEqual(Sum(5, -16), -11, "Sum of positive and negative.");
	AssertEqual(Sum(-5, -21), -26, "Sum of negative.");
}

void TestReverse() {
	AssertEqual(Reverse("Apply"), "ylppA", "Reverse normal string.");
	AssertEqual(Reverse("Apply to protest!"), "!tsetorp ot ylppA", "Reverse normal string with spaces.");
	AssertEqual(Reverse(" "), " ", "Reverse one space.");
	AssertEqual(Reverse("R"), "R", "Reverse one char.");
}

void TestSort() {
	{
		vector<int> v = {2, 5, 3, 1, 4};
		Sort(v);
		AssertEqual(v, vector<int>({1, 2, 3, 4, 5}), "Normal vector sort.");
	}
	{
		vector<int> v = {0};
		AssertEqual(v, vector<int>({0}), "One element vector sort.");
	}
	{
		vector<int> v = {-2, -5, 2, 1, 0};
		Sort(v);
		AssertEqual(v, vector<int>({-5, -2, 0, 1, 2}), "Negative elements vector sort.");
	}
}

void TestAll() {
	TestRunner tr;
	tr.RunTest(TestSum, "Test Sum");
	tr.RunTest(TestReverse, "Test Reverse");
	tr.RunTest(TestSort, "Test Sort");
}
