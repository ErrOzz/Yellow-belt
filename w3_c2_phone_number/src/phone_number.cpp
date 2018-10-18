#include "phone_number.h"

#include <sstream>
#include <exception>

void GetCode (istream& ss, string& code, const char& delim = '\n') {
	getline(ss, code, delim);
	if (code.empty()) {
		throw invalid_argument("Code can't be empty.");
	}
}

PhoneNumber::PhoneNumber(const string &international_number) {
	stringstream ss(international_number);

	if (ss) {
		if (ss.peek() != '+') {
			throw invalid_argument("First symbol must be a plus.");
		}
		ss.ignore(1);

		GetCode(ss,country_code_, '-');
	}
	if (ss) {
		GetCode(ss, city_code_, '-');
	}
	if (ss) {
		GetCode(ss, local_number_);
	} else {
		throw invalid_argument("Phone number is not full.");
	}
}

string PhoneNumber::GetCountryCode() const {
	return country_code_;
}

string PhoneNumber::GetCityCode() const {
	return city_code_;
}

string PhoneNumber::GetLocalNumber() const {
	return local_number_;
}

string PhoneNumber::GetInternationalNumber() const {
	return ('+' + country_code_ + '-' + city_code_ + '-' + local_number_);
}
