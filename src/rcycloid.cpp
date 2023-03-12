#include "rcycloid.h"

bool rcycloid::initialCalculations(){
  CirCurRadius = CircleDiamCurve / 2.0l;
  MatRadius = CirCurRadius + MaterialAddition;
  ToothRadius = ToothDiameter / 2.0l;
  TeethDist = CirCurRadius * 2.0l * M_PI / NoOfTeeth;
  CircleDist = PointsDist / ToothRadius;
  return false;
}

void rcycloid::startMessage(){
  printData("Teeth distance: ");
  printData(to_string(TeethDist));
  printData(" Calculating reverse cycloid...\n");
}

void rcycloid::newToothMessage(){
  printData("tooth_" + to_string(CurrentTooth + 1) + "\n");
}

void rcycloid::oneToothCalculations(){
  toothInit();
  generateCurve(ParamStart, ParamMiddle);
  generateCircle();
  generateCurve(ParamMiddle, ParamEnd);
}

void rcycloid::toothInit(){
  long double a = _a();
  ParamStart = -M_PI + a;
  ParamMiddle = a;
  PointMiddle.x = CirCurRadius * cosl(ParamMiddle);
  PointMiddle.y = CirCurRadius * sinl(ParamMiddle);
  ParamEnd = M_PI + a;
  CurveDist = PointsDist / M_PI / CirCurRadius;
}

bool rcycloid::pointInMaterial(const coordinates &point){
  return point.x * point.x + point.y * point.y < MatRadius * MatRadius;
}

bool rcycloid::pointInside(const coordinates &point){
  return point.x * point.x + point.y * point.y < CirCurRadius * CirCurRadius;
}

bool rcycloid::pointOutsideMiddle(const coordinates &point){
  long double x, y;
  x = point.x - PointMiddle.x;
  y = point.y - PointMiddle.y;
  return x * x + y * y > ToothRadius * ToothRadius;
}

void rcycloid::basePoint(const long double &t){
  long double s, c, a;
  s = sinl(t);
  c = cosl(t);
  a = t - _a();
  CurrentPoint.px = CirCurRadius * (c + a * s);
  CurrentPoint.py = CirCurRadius * (s - a * c);
  CurrentPoint.vx = CirCurRadius * a * c;
  CurrentPoint.vy = CirCurRadius * a * s;
}

void rcycloid::curvePoint(const long double &t){
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

void rcycloid::actualizeDist(){
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

void rcycloid::generateCurve(const long double &str, const long double &end){
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

void rcycloid::generateCircle(){
  stringstream ss;
  long double t, tMin;
  t = ParamMiddle - M_PI / 2.0l;
  tMin = ParamMiddle - 3.0l * M_PI / 2.0l;
  while (t > tMin) {
    Out.x = PointMiddle.x + ToothRadius * cosl(t);
    Out.y = PointMiddle.y + ToothRadius * sinl(t);
    if (pointInMaterial(Out) &&
        pointInside(Out))
      ss << Out.x << ';' << Out.y << endl;
    t -= CircleDist;
  }
  printData(ss.str());
}

rcycloid::rcycloid(int materialAddition,
                 int circleDiamCurve,
                 int noOfTeeth,
                 int toothDiameter,
                 long double pointsDist,
                 const string &fileName) :
  baseCurve(materialAddition,
            circleDiamCurve,
            10,
            noOfTeeth,
            toothDiameter,
            pointsDist,
            fileName)  
{

}

rcycloid::~rcycloid()
{

}
