#ifndef RCYCLOID_H
#define RCYCLOID_H

#include "baseCurve.h"

class rcycloid : public baseCurve
{
  bool initialCalculations() override;
  void startMessage() override;
  void newToothMessage() override;
  void oneToothCalculations() override;
  inline long double _a(){
    return CurrentTooth * 2.0l * M_PI / NoOfTeeth;
  }
  void toothInit();
  bool pointInMaterial(const coordinates &point);
  bool pointInside(const coordinates &point);
  bool pointOutsideMiddle(const coordinates &point);
  void basePoint(const long double &t);
  void curvePoint(const long double &t);
  void actualizeDist();
  void generateCurve(const long double &str, const long double &end);
  void generateCircle();
// rcycloid variables
  long double CirCurRadius;
  long double MatRadius;
  long double ToothRadius;
  long double TeethDist;
  long double ParamStart, ParamMiddle, ParamEnd, CurveDist, CircleDist;
  coordinates PointMiddle, Out;
  pointState CurrentPoint;  
public:
  rcycloid(int materialAddition,
          int circleDiamCurve,
          int noOfTeeth,
          int toothDiameter,
          long double pointsDist,
          const string &fileName);
  ~rcycloid() override;
};

#endif /* !RCYCLOID_H */
