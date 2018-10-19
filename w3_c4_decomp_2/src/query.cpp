#include "query.h"

#include <map>

istream& operator >> (istream& is, Query& q) {
  string str_query;
  const map<string, QueryType> query = { {"NEW_BUS", QueryType::NewBus},
  	  	  	  	  	  	  	  	   {"BUSES_FOR_STOP", QueryType::BusesForStop},
  	  	  	  	  	  	  	  	   {"STOPS_FOR_BUS", QueryType::StopsForBus},
  	  	  	  	  	  	  	  	   {"ALL_BUSES", QueryType::AllBuses} };
  is >> str_query;
  q.type = query.at(str_query);
  switch (query.at(str_query)) {
  case QueryType::NewBus: {
	  int stops_count_ = 0;
	  is >> q.bus >> stops_count_;
	  q.stops.resize(stops_count_);
	  for (auto& stop : q.stops) {
		  is >> stop;
	  }
  }
	  break;
  case QueryType::BusesForStop:
	  is >> q.stop;
	  break;
  case QueryType::StopsForBus:
	  is >> q.bus;
	  break;
  case QueryType::AllBuses:
	  break;
  }
  return is;
}
