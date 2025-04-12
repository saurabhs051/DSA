// Detailed Reference at : 
// https://github.com/tssovi/grokking-the-object-oriented-design-interview/blob/master/object-oriented-design-case-studies/design-a-parking-lot.md

// Parking Lot System in C++ using Design Patterns

#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <mutex>
#include <vector>

using namespace std;

// ---------------- ENUMS ----------------
enum class VehicleType { CAR, TRUCK, ELECTRIC, VAN, MOTORBIKE };
enum class ParkingSpotType { HANDICAPPED, COMPACT, LARGE, MOTORBIKE, ELECTRIC };

// ---------------- VEHICLE ----------------
class Vehicle {
public:
    VehicleType type;
    Vehicle(VehicleType t) : type(t) {}
};

// ---------------- PARKING SPOT ----------------
class ParkingSpot {
protected:
    string number;
    bool free;
    shared_ptr<Vehicle> vehicle;
    ParkingSpotType type;
public:
    ParkingSpot(string num, ParkingSpotType t) : number(num), type(t), free(true) {}
    virtual void assignVehicle(shared_ptr<Vehicle> v) {
        vehicle = v;
        free = false;
    }
    virtual void removeVehicle() {
        vehicle.reset();
        free = true;
    }
    bool isFree() const { return free; }
    string getNumber() const { return number; }
    ParkingSpotType getType() const { return type; }
};

// Template Method pattern would apply if we had behavior to override.
class HandicappedSpot : public ParkingSpot {
public:
    HandicappedSpot(string num) : ParkingSpot(num, ParkingSpotType::HANDICAPPED) {}
};

class CompactSpot : public ParkingSpot {
public:
    CompactSpot(string num) : ParkingSpot(num, ParkingSpotType::COMPACT) {}
};

class LargeSpot : public ParkingSpot {
public:
    LargeSpot(string num) : ParkingSpot(num, ParkingSpotType::LARGE) {}
};

class MotorbikeSpot : public ParkingSpot {
public:
    MotorbikeSpot(string num) : ParkingSpot(num, ParkingSpotType::MOTORBIKE) {}
};

class ElectricSpot : public ParkingSpot {
public:
    ElectricSpot(string num) : ParkingSpot(num, ParkingSpotType::ELECTRIC) {}
};

// ---------------- FACTORY ----------------
class ParkingSpotFactory {
public:
    static shared_ptr<ParkingSpot> createSpot(ParkingSpotType type, const string& number) {
        switch(type) {
            case ParkingSpotType::HANDICAPPED: return make_shared<HandicappedSpot>(number);
            case ParkingSpotType::COMPACT: return make_shared<CompactSpot>(number);
            case ParkingSpotType::LARGE: return make_shared<LargeSpot>(number);
            case ParkingSpotType::MOTORBIKE: return make_shared<MotorbikeSpot>(number);
            case ParkingSpotType::ELECTRIC: return make_shared<ElectricSpot>(number);
        }
        return nullptr;
    }
};

// ---------------- STRATEGY ----------------
class ParkingStrategy {
public:
    virtual shared_ptr<ParkingSpot> findSpot(const vector<shared_ptr<ParkingSpot>>& spots) = 0;
};

class DefaultStrategy : public ParkingStrategy {
public:
    shared_ptr<ParkingSpot> findSpot(const vector<shared_ptr<ParkingSpot>>& spots) override {
        for (auto& spot : spots) {
            if (spot->isFree()) return spot;
        }
        return nullptr;
    }
};

// ---------------- OBSERVER ----------------
class DisplayBoard {
public:
    void update(const string& message) {
        cout << "Display: " << message << endl;
    }
};

// ---------------- SINGLETON ----------------
class ParkingLot {
private:
    static shared_ptr<ParkingLot> instance;
    static mutex mtx;
    map<string, vector<shared_ptr<ParkingSpot>>> floors;
    shared_ptr<DisplayBoard> display;

    ParkingLot() {
        display = make_shared<DisplayBoard>();
    }

public:
    static shared_ptr<ParkingLot> getInstance() {
        // Could have also used double-checked locking here
        lock_guard<mutex> lock(mtx);
        if (!instance) instance = shared_ptr<ParkingLot>(new ParkingLot());
        return instance;
    }

    void addSpot(const string& floor, shared_ptr<ParkingSpot> spot) {
        floors[floor].push_back(spot);
        display->update("Added spot: " + spot->getNumber());
    }

    void assignVehicleToSpot(VehicleType type, const string& floor, shared_ptr<Vehicle> vehicle) {
        vector<shared_ptr<ParkingSpot>>& spots = floors[floor];
        DefaultStrategy strategy;
        shared_ptr<ParkingSpot> spot = strategy.findSpot(spots);
        if (spot) {
            spot->assignVehicle(vehicle);
            display->update("Assigned to spot: " + spot->getNumber());
        } else {
            display->update("No available spot on floor: " + floor);
        }
    }
};

shared_ptr<ParkingLot> ParkingLot::instance = nullptr;
mutex ParkingLot::mtx;

// ---------------- MAIN ----------------
int main() {
    auto lot = ParkingLot::getInstance();
    lot->addSpot("G1", ParkingSpotFactory::createSpot(ParkingSpotType::COMPACT, "C1"));
    lot->addSpot("G1", ParkingSpotFactory::createSpot(ParkingSpotType::ELECTRIC, "E1"));
    
    shared_ptr<Vehicle> car = make_shared<Vehicle>(VehicleType::CAR);
    lot->assignVehicleToSpot(VehicleType::CAR, "G1", car);

    return 0;
}
