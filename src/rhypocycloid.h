#ifndef RHYPOCYCLOID_H
#define RHYPOCYCLOID_H

#include "baseCurve.h"

class rhypocycloid : public baseCurve
{
  bool initialCalculations() override;
  void startMessage() override;
  void newToothMessage() override;
  void oneToothCalculations() override;
  inline long double _a(const long double &t){
    return RadiusFact * t + CurrentTooth * TeethAngle;
  }
  void sectionInit(int sectionNo);
  bool pointInMaterial(const coordinates &point);
  bool pointInside(const coordinates &point);
  bool pointOutsideMiddle(const coordinates &point);
  void basePoint(const long double &t);
  void curvePoint(const long double &t);
  void actualizeDist();
  void generateSection(const long double &str, const long double &end);
  void generateCircle();
// rhypocycloid variables
  long double CurveClosure;
  long double SectionLength;
  int NoOfSections;
  long double CirCurRadius;
  long double CirTthRadius;
  long double MatRadius;
  long double ToothRadius;
  long double RadiusSum;
  long double RadiusFact;
  long double TeethAngle;
  long double ParamStart, ParamMiddle, ParamEnd, CurveDist, CircleDist;
  coordinates PointMiddle, Out;
  pointState CurrentPoint;  
public:
  rhypocycloid(int materialAddition,
             int circleDiamCurve,
             int circleDiamTeeth,
             int noOfTeeth,
             int toothDiameter,
             long double pointsDist,
             const string &fileName);
  ~rhypocycloid() override;
};

#endif /* !RHYPOCYCLOID_H */
