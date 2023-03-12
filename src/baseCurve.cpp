#include "baseCurve.h"
#include <algorithm>

//using namespace std;

int baseCurve::gcd(int a, int b){
  if (a == 0)
    return b;
  if (b == 0)
    return a;
  int k;
  for (k = 0; ((a | b) & 1) == 0; ++k){
    a >>= 1;
    b >>= 1;
  }
  while ((a & 1) == 0)
    a >>= 1;
  do
  {
    while ((b & 1) == 0)
      b >>= 1;
    if (a > b)
      swap(a, b);
    b = (b - a);
  }while (b != 0);

  return a << k;
}

void baseCurve::printData(const string &data){
  if (File)
    File << data;
  else
    cout << data;
}

bool baseCurve::normalizeData(){
  if (MaterialAddition < 1){
    cout << "No material addition specified." << endl;
    return true;
  }
  if (CircleDiamCurve < 1){
    cout << "No diameter of a circle with curve specified." << endl;
    return true;
  }
  if (CircleDiamTeeth < 1){
    cout << "No diameter of a circle with teeth specified." << endl;
    return true;
  }
  if (NoOfTeeth < 1){
    cout << "No number of teeth specified." << endl;
    return true;
  }
  if (ToothDiameter < 1){
    cout << "No diameter of one tooth specified." << endl;
    return true;
  }
  if (PointsDist < 0.000001){
    cout << "No distance between points specified." << endl;
    return true;
  }
  return false;
}

baseCurve::baseCurve(int materialAddition,
                     int circleDiamCurve,
                     int circleDiamTeeth,
                     int noOfTeeth,
                     int toothDiameter,
                     long double pointsDist,
                     const string &fileName) :
  MaterialAddition(materialAddition),
  CircleDiamCurve(circleDiamCurve),
  CircleDiamTeeth(circleDiamTeeth),
  NoOfTeeth(noOfTeeth),
  ToothDiameter(toothDiameter),
  PointsDist(pointsDist)
{
  if (!fileName.empty())
    File.open(fileName.c_str());
}

baseCurve::~baseCurve(){
  if (File.is_open())
    File.close();
}

void baseCurve::calculate(){
  if (normalizeData())
    return;
  if (initialCalculations())
    return;
  startMessage();
  for (CurrentTooth = 0; CurrentTooth < NoOfTeeth; ++CurrentTooth){
    newToothMessage();
    oneToothCalculations();
  }
}
