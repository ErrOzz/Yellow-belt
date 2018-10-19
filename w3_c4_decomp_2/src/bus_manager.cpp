#include "bus_manager.h"

void BusManager::AddBus(const string& bus, const vector<string>& stops) {
  buses_to_stops[bus] = stops;
  for (const string& stop : stops) {
  stops_to_buses[stop].push_back(bus);
  }
}

BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
	  if (stops_to_buses.count(stop) != 0) {
		  return BusesForStopResponse{stops_to_buses.at(stop)};
	  }
	  return BusesForStopResponse{};
}

StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
	  StopsForBusResponse r;
	  if (buses_to_stops.count(bus) != 0) {
		  r.bus_ = bus;
		  r.stops_ = buses_to_stops.at(bus);
		  r.stop_to_buses_ = stops_to_buses;
	  }
	  return r;
}

AllBusesResponse BusManager::GetAllBuses() const {
  return AllBusesResponse{buses_to_stops};
}
