#ifndef IK_NODE_H
#define IK_NODE_H

#include <maya/MPxNode.h>
#include <maya/MTypeId.h>

class IkNode : public MPxNode {
public:
  virtual MStatus compute(const MPlug &plug, MDataBlock &dataBlock);

  static void *creator() { return new IkNode(); };

  static MStatus initialize();

  // The node id
  static MTypeId typeId;

  static MObject inputVal;

  static MObject inputCurve;

  // Output attribute holding the computed data
  static MObject outputVal;
};

#endif
