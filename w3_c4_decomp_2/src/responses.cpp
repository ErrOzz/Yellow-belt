#include "responses.h"

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
  if (r.buses_.empty()) {
	  os << "No stop";
	  return os;
  }
  bool first_i = true;
  for(const auto& bus : r.buses_) {
	  if (!first_i) {
		  os << " ";
	  }
	  first_i = false;
	  os << bus;
  }
  return os;
}

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
  if (r.stops_.empty()) {
	os << "No bus";
	return os;
  }
  bool first_str = true;
  for (const auto& stop : r.stops_) {
	  if (!first_str) {
		  os << endl;
	  }
	  first_str = false;
	  os << "Stop " << stop << ":";
	  if (r.stop_to_buses_.at(stop).size() == 1) {
		  os << " no interchange";
	  } else {
		  for (const auto& bus : r.stop_to_buses_.at(stop)) {
			if (bus != r.bus_) {
				os << " " << bus;
			}
		  }
	  }
  }
  return os;
}

ostream& operator << (ostream& os, const AllBusesResponse& r) {
  if (r.all_buses_.empty()) {
	os << "No buses";
	return os;
  }
  bool first_str = true;
  for (const auto& bus_stops : r.all_buses_) {
	  if (!first_str) {
		  os << endl;
	  }
	  first_str = false;
	  os << "Bus ";
	  os << bus_stops.first << ":";
	  for (const auto& stop : bus_stops.second) {
		  os << " " << stop;
	  }
  }
  return os;
}
