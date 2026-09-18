#include <iostream>
#include <string>
using namespace std;

class Ride {
protected:
    string rideID;
    double distanceKM;

public:
    static double totalCompanyRevenue;

    Ride(string rideID, double distanceKM) {
        this->rideID = rideID;
        this->distanceKM = distanceKM;
    }

    virtual ~Ride() {
        cout << "[COMPLETED] Ride " << rideID << " finished and cleared from active memory." << endl;
    }

    virtual double calculateFare() = 0;
    virtual void displayDetails() = 0;
};

double Ride::totalCompanyRevenue = 0.0;

class BikeRide : public Ride {
private:
    double helmetFee;

public:
    BikeRide(string rideID, double distanceKM, double helmetFee)
        : Ride(rideID, distanceKM), helmetFee(helmetFee) {}

    double calculateFare() override {
        return (distanceKM * 25.0) + helmetFee;
    }

    void displayDetails() override {
        cout << "\n--- [BIKE RIDE DETAILS] ---" << endl;
        cout << "Ride ID    : " << rideID << endl;
        cout << "Distance   : " << distanceKM << " KM" << endl;
        cout << "Helmet Fee : " << helmetFee << " PKR" << endl;
        cout << "Total Fare : " << calculateFare() << " PKR" << endl;
    }
};

class CarRide : public Ride {
private:
    bool isAC;

public:
    CarRide(string rideID, double distanceKM, bool isAC)
        : Ride(rideID, distanceKM), isAC(isAC) {}

    double calculateFare() override {
        double fare = distanceKM * 60.0;
        if (isAC) {
            fare += 150.0;
        }
        return fare;
    }

    void displayDetails() override {
        cout << "\n--- [CAR RIDE DETAILS] ---" << endl;
        cout << "Ride ID    : " << rideID << endl;
        cout << "Distance   : " << distanceKM << " KM" << endl;
        cout << "AC Status  : " << (isAC ? "Yes" : "No") << endl;
        cout << "Total Fare : " << calculateFare() << " PKR" << endl;
    }
};

int main() {
    Ride* activeRides[2];

    activeRides[0] = new BikeRide("B-201", 8.5, 30.0);
    activeRides[1] = new CarRide("C-909", 15.0, true);

    for (int i = 0; i < 2; i++) {
        activeRides[i]->displayDetails();
        Ride::totalCompanyRevenue += activeRides[i]->calculateFare();
    }

    cout << "\n=============================================" << endl;
    cout << "Total Company Revenue: " << Ride::totalCompanyRevenue << " PKR" << endl;
    cout << "=============================================\n" << endl;

    for (int i = 0; i < 2; i++) {
        delete activeRides[i];
        activeRides[i] = nullptr;
    }

    return 0;
}
