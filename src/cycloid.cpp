#include "cycloid.h"

bool cycloid::initialCalculations(){
  CirTthRadius = CircleDiamTeeth / 2.0;
  ToothRadius = ToothDiameter / 2.0;
  TeethAngle = 2.0 * M_PI / NoOfTeeth;
  CircleDist = PointsDist / ToothRadius;
  return false;
}

void cycloid::startMessage(){
  printData("Teeth distance: ");
  printData(to_string(TeethAngle * CirTthRadius));
  printData(" Calculating cycloid...\n");
}

void cycloid::newToothMessage(){
  printData("tooth_" + to_string(CurrentTooth + 1) + "\n");
}

void cycloid::oneToothCalculations(){
  toothInit();
  generateCurve(ParamStart, ParamMiddle);
  generateCircle();
  generateCurve(ParamMiddle, ParamEnd);
}

void cycloid::toothInit(){
  long double a = _a();
  ParamStart = -M_PI + a;
  ParamMiddle = a;
  PointMiddle.x = 0.0l;
  PointMiddle.y = CurrentTooth * CirTthRadius * TeethAngle;
  ParamEnd = M_PI + a;
  CurveDist = PointsDist / 2.0l / CirTthRadius;
}

bool cycloid::pointInMaterial(const coordinates &point){
  return point.x < MaterialAddition;
}

bool cycloid::pointInside(const coordinates &point){
  return point.x < 0.0l;
}

bool cycloid::pointOutsideMiddle(const coordinates &point){
  long double x, y;
  x = point.x - PointMiddle.x;
  y = point.y - PointMiddle.y;
  return x * x + y * y > ToothRadius * ToothRadius;
}

void cycloid::basePoint(const long double &t){
  long double s, c;
  s = sinl(t - _a());
  c = cosl(t - _a());
  CurrentPoint.px = CirTthRadius * (1.0l - c);
  CurrentPoint.py = CirTthRadius * (t - s);
  CurrentPoint.vx = CirTthRadius * s;
  CurrentPoint.vy = CirTthRadius * (1.0l - c);
}

void cycloid::curvePoint(const long double &t){
  if (CurrentPoint.vx == 0.0 && CurrentPoint.vy == 0.0){
    Out.x = 0.0l;
    Out.y = 0.0l;
  }
  else{
    long double p;
    p = sqrtl(ToothRadius * ToothRadius / (CurrentPoint.vx * CurrentPoint.vx + CurrentPoint.vy * CurrentPoint.vy));
    Out.x = -CurrentPoint.vy * p;
    Out.y = CurrentPoint.vx * p;
    if (CurrentPoint.vy < 0){
      Out.x = -Out.x;
      Out.y = -Out.y;
    }
    p = CurrentPoint.vx * Out.y - CurrentPoint.vy * Out.x;  
    if (p < 0){
      Out.x = -Out.x;
      Out.y = -Out.y;
    }
  }
  Out.x += CurrentPoint.px;
  Out.y += CurrentPoint.py;
}

void cycloid::actualizeDist(){
  long double newDist = PointsDist / sqrtl(CurrentPoint.vx * CurrentPoint.vx + CurrentPoint.vy * CurrentPoint.vy);
  long double maxlimitval, minlimitval;
  maxlimitval = CurveDist * MAXSPEEDCHANGE;
  minlimitval = CurveDist / MAXSPEEDCHANGE;
  if (newDist > maxlimitval){
    CurveDist = maxlimitval; 
  }
  else{
    if (newDist < minlimitval)
      CurveDist = minlimitval;
    else
      CurveDist = newDist;
  }
}

void cycloid::generateCurve(const long double &str, const long double &end){
  stringstream ss;
  long double t;
  t = str;
  while (t < end) {
    basePoint(t);
    curvePoint(t);
    if (pointInMaterial(Out) &&
        !pointInside(Out) &&
        pointOutsideMiddle(Out)){
      ss << Out.x << ';' << Out.y << endl;
      actualizeDist();
    }
    t +=  CurveDist;
  }
  printData(ss.str());
}

void cycloid::generateCircle(){
  stringstream ss;
  long double t, tMin;
  t = -M_PI / 2.0l;
  tMin = -3.0l * M_PI / 2.0l;
  while (t > tMin) {
    Out.x = ToothRadius * cosl(t);
    Out.y = CirTthRadius * CurrentTooth * TeethAngle + ToothRadius * sinl(t);
    if (pointInMaterial(Out) &&
        pointInside(Out))
      ss << Out.x << ';' << Out.y << endl;
    t -= CircleDist;
  }
  printData(ss.str());
}

cycloid::cycloid(int materialAddition,
                 int circleDiamTeeth,
                 int noOfTeeth,
                 int toothDiameter,
                 long double pointsDist,
                 const string &fileName) :
  baseCurve(materialAddition,
            10,
            circleDiamTeeth,
            noOfTeeth,
            toothDiameter,
            pointsDist,
            fileName)  
{

}

cycloid::~cycloid()
{

}
