#ifndef CYCLOID_H
#define CYCLOID_H

#include "baseCurve.h"

class cycloid : public baseCurve
{
  bool initialCalculations() override;
  void startMessage() override;
  void newToothMessage() override;
  void oneToothCalculations() override;
  inline long double _a(){
    return CurrentTooth * TeethAngle;
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
// cycloid variables
  long double CirTthRadius;
  long double ToothRadius;
  long double TeethAngle;
  long double ParamStart, ParamMiddle, ParamEnd, CurveDist, CircleDist;
  coordinates PointMiddle, Out;
  pointState CurrentPoint;  
public:
  cycloid(int materialAddition,
          int circleDiamTeeth,
          int noOfTeeth,
          int toothDiameter,
          long double pointsDist,
          const string &fileName);
  ~cycloid() override;
};

#endif /* !CYCLOID_H */
