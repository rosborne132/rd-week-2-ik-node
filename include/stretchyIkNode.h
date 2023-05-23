#pragma once

#include <maya/MDistance.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MFnUnitAttribute.h>
#include <maya/MMatrix.h>
#include <maya/MPxNode.h>
#include <maya/MVector.h>

class StretchyIkNode : public MPxNode {
public:
  // IK Chain info
  static MObject inRootMatrixAttr;
  static MObject inPoleVectorMatrixAttr;
  static MObject inControlMatrixAttr;
  static MObject inUpperLengthAttr;
  static MObject inLowerLengthAttr;
  static MObject inGlobalScaleAttr;

  // Features
  static MObject inSlideAttr;
  static MObject inStrectchAttr;
  static MObject inRoleVectorLockAttr;

  // Outputs
  static MObject outUpperLengthAttr;
  static MObject outLowerLengthAttr;

  static MTypeId typeId;
  static MStatus initialize();
  static void *creator() { return new StretchyIkNode(); };
  MStatus compute(const MPlug &plug, MDataBlock &dataBlock) override;
};
