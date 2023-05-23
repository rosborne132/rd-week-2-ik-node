#include <cmath>
#include <maya/MDataHandle.h>
#include <maya/MFloatPoint.h>
#include <maya/MFnCompoundAttribute.h>
#include <maya/MFnEnumAttribute.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnNurbsCurve.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MGlobal.h>
#include <maya/MObject.h>
#include <maya/MPlug.h>
#include <maya/MTransformationMatrix.h>

#include "stretchyIkNode.h"

MTypeId StretchyIkNode::typeId(0x80004);
MObject StretchyIkNode::inRootMatrixAttr;
MObject StretchyIkNode::inPoleVectorMatrixAttr;
MObject StretchyIkNode::inControlMatrixAttr;
MObject StretchyIkNode::inUpperLengthAttr;
MObject StretchyIkNode::inLowerLengthAttr;
MObject StretchyIkNode::inGlobalScaleAttr;

MStatus StretchyIkNode::initialize() {
  MStatus status = MS::kSuccess;

  return status;
}

MStatus StretchyIkNode::compute(const MPlug &plug, MDataBlock &dataBlock) {
  return MS::kSuccess;
}
