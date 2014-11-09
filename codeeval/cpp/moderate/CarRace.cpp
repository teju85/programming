//
// Challenge name: Car Race
// Difficulty    : moderate
// Link          : https://www.codeeval.com/open_challenges/138/
// Compile       : g++ -Wall -g -o CarRace CarRace.cpp
//

#include <stdio.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

class Car {
public:
    Car(int i, float t, float ta, float td):
        id(i), topSpeed(t/3600), acc(topSpeed/ta), dec(topSpeed/td),
        angleSlope(-topSpeed/180), totalTime(0.0f) {
    }
    Car(const Car& c): id(c.id), topSpeed(c.topSpeed), acc(c.acc), dec(c.dec),
                       angleSlope(c.angleSlope), totalTime(c.totalTime) {
    }
    ~Car() {}
    void evalTotalTime(const vector<float>& sections, const vector<int>& angles) {
        float total = 0.0f;
        float vel = 0.0f;
        int size = (int)sections.size();
        for(int i=0;i<size;++i) {
            float fVel = getFinalVel(angles[i]);
            total += timeForSection(vel, sections[i], fVel);
            vel = fVel;
        }
        totalTime = total;
    }
    float totalTrackTime() const { return totalTime; }
    void printCar() const {
        printf("%d %.2f\n", id, totalTime);
    }
private:
    float timeForSection(float startVel, float sectionLen, float finalVel) const {
        float accTime = (topSpeed - startVel) / acc;
        float accLen = (startVel * accTime) + (acc * accTime * accTime / 2);
        float decTime = (topSpeed - finalVel) / dec;
        float decLen = (topSpeed * decTime) - (dec * decTime * decTime / 2);
        float secTime = (sectionLen - accLen - decLen) / topSpeed;
        return (accTime + secTime + decTime);
    }
    float getFinalVel(int angle) const {
        return (topSpeed + (angleSlope * angle));
    }
    int id;
    float topSpeed;
    float acc;
    float dec;
    float angleSlope;
    float totalTime;
};

struct CarSorter {
    bool operator()(const Car& a, const Car& b) {
        return (a.totalTrackTime() < b.totalTrackTime());
    }
};

void populateTrack(vector<float>& sections, vector<int>& angles, ifstream& ifs) {
    string ss;
    getline(ifs, ss);
    istringstream iss(ss);
    while(iss.good()) {
        float s = -0.1f;
        int a = -1;
        iss >> s >> a;
        if(a == -1) {
            continue;
        }
        sections.push_back(s);
        angles.push_back(a);
    }
}

void populateCars(vector<Car>& cars, ifstream& ifs) {
    while(ifs.good()) {
        int id;
        float top, acc, dec;
        dec = -0.1f;
        ifs >> id >> top >> acc >> dec;
        if(dec == -0.1f) {
            continue;
        }
        cars.push_back(Car(id, top, acc, dec));
    }
}

void evaluateTotalTime(vector<Car>& cars, const vector<float>& sections,
                       const vector<int>& angles) {
    for(vector<Car>::iterator itr=cars.begin();itr!=cars.end();++itr) {
        itr->evalTotalTime(sections, angles);
    }
}

void sortCars(vector<Car>& cars) {
    CarSorter sorter;
    sort(cars.begin(), cars.end(), sorter);
}

void printCars(const vector<Car>& cars) {
    for(vector<Car>::const_iterator itr=cars.begin();itr!=cars.end();++itr) {
        itr->printCar();
    }
}

int main(int argc, char** argv) {
    if(argc != 2) {
        printf("USAGE: CarRace <fileContainingTestVectors>\n");
        return 1;
    }
    ifstream ifs;
    ifs.open(argv[1], ifstream::in);
    if(!ifs.is_open()) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    vector<float> sections;
    vector<int> angles;
    populateTrack(sections, angles, ifs);
    vector<Car> cars;
    populateCars(cars, ifs);
    ifs.close();
    evaluateTotalTime(cars, sections, angles);
    sortCars(cars);
    printCars(cars);
    return 0;
}
