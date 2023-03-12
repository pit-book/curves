#include "baseCurve.h"
#include "epicycloid.h"
#include "cycloid.h"
#include "rcycloid.h"
#include "hypocycloid.h"
#include "rhypocycloid.h"

int main(int argc, char *argv[]){
/* -v curve version
 * -a curve circle diameter
 * -b teeth circle diameter
 * -n number of teeth
 * -d tooth diameter
 * -m material addition
 * -t distance between points 
 * -f name of the file to send output
 */
  int curveVersion(0), materialAddition(0), circleDiamCurve(0), circleDiamTeeth(0), noOfTeeth(0), toothDiameter(0);
  long double pointsDist(0.0l);
  string fileName;
    for (int i = 0; i < argc - 1; ++i){
    if (argv[i][0] == '-')
      switch (argv[i][1]){
      case 'a':
        circleDiamCurve = atoi(argv[i + 1]);
        break;
      case 'b':
        circleDiamTeeth = atoi(argv[i + 1]);
        break;
      case 'd':
        toothDiameter = atoi(argv[i + 1]);
        break;
      case 'f':
        fileName = argv[i + 1];
        break;
      case 'm':
        materialAddition = atoi(argv[i + 1]);
        break;
      case 'n':
        noOfTeeth = atoi(argv[i + 1]);
        break;
      case 't':
        pointsDist = atof(argv[i + 1]);
        break;
      case 'v':
        curveVersion = atoi(argv[i + 1]);
        break;
    }
  }
  baseCurve *Curve;
  switch (curveVersion) {
    case 1:
      Curve = new epicycloid(materialAddition,
                             circleDiamCurve,
                             circleDiamTeeth,
                             noOfTeeth,
                             toothDiameter,
                             pointsDist,
                             fileName); 
      break;
    case 2:
      Curve = new cycloid(materialAddition,
                          circleDiamTeeth,
                          noOfTeeth,
                          toothDiameter,
                          pointsDist,
                          fileName); 
      break;
     case 3:
      Curve = new rcycloid(materialAddition,
                            circleDiamCurve,
                            noOfTeeth,
                            toothDiameter,
                            pointsDist,
                            fileName); 
        break;
     case 4:
      Curve = new hypocycloid(materialAddition,
                              circleDiamCurve,
                              circleDiamTeeth,
                              noOfTeeth,
                              toothDiameter,
                              pointsDist,
                              fileName); 
        break;
     case 5:
      Curve = new rhypocycloid(materialAddition,
                                circleDiamCurve,
                                circleDiamTeeth,
                                noOfTeeth,
                                toothDiameter,
                                pointsDist,
                                fileName); 
          break;
     default:
      cout << "No curve version specified" << endl;
      return 1;
  }
  Curve->calculate();
  delete Curve;
  return 0;
}

