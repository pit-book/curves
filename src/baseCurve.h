#ifndef BASECURVE_H
#define BASECURVE_H

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cmath>

#define MAXSPEEDCHANGE 1.21l

using namespace std;

struct pointState{
  long double px, py, vx, vy;
};

struct coordinates {
    long double x, y;
};

class baseCurve {
  ofstream File;
protected:
  int gcd(int a, int b);
  void printData(const string &data);
  bool normalizeData();
//main variables
  int MaterialAddition;
  int CircleDiamCurve;
  int CircleDiamTeeth;
  int NoOfTeeth;
  int ToothDiameter;
  long double PointsDist;
  int CurrentTooth;
//virtual methods
  virtual bool initialCalculations() = 0;
  virtual void startMessage() = 0;
  virtual void newToothMessage() = 0;
  virtual void oneToothCalculations() = 0;
public:
  baseCurve(int materialAddition,
            int circleDiamCurve,
            int circleDiamTeeth,
            int noOfTeeth,
            int toothDiameter,
            long double pointsDist,
            const string &fileName);
  virtual ~baseCurve();
  void calculate();
};

#endif /* !BASECURVE_H */
