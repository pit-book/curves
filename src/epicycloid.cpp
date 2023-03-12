#include "epicycloid.h"

bool epicycloid::initialCalculations(){
  long double temp = 2.0 * M_PI * CircleDiamTeeth;
  int k = gcd(CircleDiamCurve, CircleDiamTeeth);
  CurveClosure = temp / k;
  SectionLength = temp / CircleDiamCurve;
  NoOfSections = CircleDiamCurve / k;
  CirCurRadius = CircleDiamCurve / 2.0;
  CirTthRadius = CircleDiamTeeth / 2.0;
  MatRadius = CirCurRadius + MaterialAddition;
  ToothRadius = ToothDiameter / 2.0;
  RadiusSum = CirCurRadius + CirTthRadius;
  RadiusFact = RadiusSum / CirTthRadius;
  TeethAngle = 2.0 * M_PI / NoOfTeeth;
  CircleDist = PointsDist / ToothRadius;
  return false;
}

void epicycloid::startMessage(){
  printData("Ratio: ");
  printData(to_string(CirCurRadius / CirTthRadius));
  printData(" Calculating epicycloid...\n");
}

void epicycloid::newToothMessage(){
  printData("tooth_" + to_string(CurrentTooth + 1) + "\n");
}

void epicycloid::oneToothCalculations(){
  for (int i = 0; i < NoOfSections; ++i){
    sectionInit(i);
    generateSection(ParamStart, ParamMiddle);
    generateCircle();
    generateSection(ParamMiddle, ParamEnd);
  }
}

void epicycloid::sectionInit(int sectionNo){
  ParamStart = (sectionNo - 0.5l) * SectionLength - CirTthRadius / CirCurRadius * _a(0.0);
  ParamMiddle = ParamStart + 0.5l * SectionLength;
  PointMiddle.x = CirCurRadius * cosl(ParamMiddle);
  PointMiddle.y = CirCurRadius * sinl(ParamMiddle);
  ParamEnd = ParamStart + SectionLength;
  CurveDist = PointsDist /(2.0l * RadiusSum);
}

bool epicycloid::pointInMaterial(const coordinates &point){
  return point.x * point.x + point.y * point.y < MatRadius * MatRadius;
}

bool epicycloid::pointInside(const coordinates &point){
  return point.x * point.x + point.y * point.y < CirCurRadius * CirCurRadius;
}

bool epicycloid::pointOutsideMiddle(const coordinates &point){
  long double x, y;
  x = point.x - PointMiddle.x;
  y = point.y - PointMiddle.y;
  return x * x + y * y > ToothRadius * ToothRadius;
}

void epicycloid::basePoint(const long double &t){
  long double s1, c1, s2, c2;  
  s1 = sinl(t);
  c1 = cosl(t);
  s2 = sinl(_a(t));
  c2 = cosl(_a(t));
  CurrentPoint.px = RadiusSum * c1 - CirTthRadius * c2;
  CurrentPoint.py = RadiusSum * s1 - CirTthRadius * s2;
  CurrentPoint.vx = -RadiusSum * (s1 - s2);
  CurrentPoint.vy = RadiusSum * (c1 - c2);
}

void epicycloid::curvePoint(const long double &t){
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

void epicycloid::actualizeDist(){
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

void epicycloid::generateSection(const long double &str, const long double &end){
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

void epicycloid::generateCircle(){
  stringstream ss;
  long double t, tMin;
  t = ParamMiddle - M_PI / 2.0;
  tMin = ParamMiddle - 3.0 * M_PI / 2.0;
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

epicycloid::epicycloid(int materialAddition,
                       int circleDiamCurve,
                       int circleDiamTeeth,
                       int noOfTeeth,
                       int toothDiameter,
                       long double pointsDist,
                       const string &fileName) :
  baseCurve(materialAddition,
            circleDiamCurve,
            circleDiamTeeth,
            noOfTeeth,
            toothDiameter,
            pointsDist,
            fileName)  
{

}

epicycloid::~epicycloid()
{

}
