#include "tests.h"
#include "test_runner.h"
#include "phone_number.h"

#include <exception>
#include <iostream>

void GoodNumberTest() {
	{
		PhoneNumber n("+7-495-111-22-33");
		AssertEqual(n.GetCountryCode(), "7", "Get country code.");
		AssertEqual(n.GetCityCode(), "495", "Get city code.");
		AssertEqual(n.GetLocalNumber(), "111-22-33", "Get local number.");
		AssertEqual(n.GetInternationalNumber(), "+7-495-111-22-33", "Get full number.");
	}
	{
		PhoneNumber n("+1-2-coursera-cpp");
		AssertEqual(n.GetCountryCode(), "1", "Get country code.");
		AssertEqual(n.GetCityCode(), "2", "Get city code.");
		AssertEqual(n.GetLocalNumber(), "coursera-cpp", "Get local number.");
		AssertEqual(n.GetInternationalNumber(), "+1-2-coursera-cpp", "Get full number.");
	}
}

void BadNumberTest() {
	try {
		PhoneNumber n("1-2-333");
	} catch (exception& e) {
		cerr << e.what() << endl;
	}
	try {
		PhoneNumber n("+7-1233");
	} catch (exception& e) {
		cerr << e.what() << endl;
	}
}

void TestAll() {
	TestRunner tr;
	tr.RunTest(GoodNumberTest, "Good number test");
	tr.RunTest(BadNumberTest, "Good number test");
}
