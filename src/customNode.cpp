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

#include "customNode.h"

MTypeId CustomNode::typeId(0x80004);
MObject CustomNode::inputVal;
MObject CustomNode::inputCurve;
MObject CustomNode::outputVal;

MStatus CustomNode::initialize() {
  MStatus status = MS::kSuccess;

  // Declaring all the needed attribute function sets
  MFnNumericAttribute numFn;
  MFnTypedAttribute typedFn;

  inputVal =
      numFn.create("inputValue", "iv", MFnNumericData::kDouble, 0, &status);

  if (status != MS::kSuccess) {
    status.perror("Failed to created inputValue");
    return MS::kFailure;
  }

  numFn.setKeyable(true);
  numFn.setStorable(true);
  numFn.setWritable(true);
  addAttribute(inputVal);

  inputCurve = typedFn.create("inputCurve", "incv", MFnData::kNurbsCurve,
                              MObject::kNullObj, &status);

  if (status != MS::kSuccess) {
    status.perror("Failed to created inputCurve");
    return MS::kFailure;
  }

  typedFn.setKeyable(true);
  typedFn.setStorable(true);
  typedFn.setWritable(true);
  addAttribute(inputCurve);

  outputVal =
      numFn.create("outputValue", "ov", MFnNumericData::kDouble, 0, &status);

  if (status != MS::kSuccess) {
    status.perror("Failed to created inputCurve");
    return MS::kFailure;
  }

  numFn.setKeyable(false);
  numFn.setStorable(false);
  numFn.setWritable(false);
  addAttribute(outputVal);

  // Defines the relationship between attributes
  attributeAffects(inputVal, outputVal);
  attributeAffects(inputCurve, outputVal);

  return status;
}

MStatus CustomNode::compute(const MPlug &plug, MDataBlock &dataBlock) {
  if (plug != outputVal)
    return MS::kSuccess;

  // Reads the input
  double inVal = dataBlock.inputValue(inputVal).asDouble();
  MObject crvVal = dataBlock.inputValue(inputCurve).asNurbsCurve();

  // Compute corresponding parameter
  MFnNurbsCurve crvFn(crvVal);
  double outVal = crvFn.findParamFromLength(inVal);

  // Set the output
  dataBlock.outputValue(outputVal).set(outVal);
  dataBlock.outputValue(outputVal).setClean();

  return MS::kSuccess;
}
