#include "stretchyIkNode.h"
#include "utils.h"

// IK Chain info
MTypeId StretchyIkNode::typeId(0x80004);
MObject StretchyIkNode::inRootMatrixAttr;
MObject StretchyIkNode::inPoleVectorMatrixAttr;
MObject StretchyIkNode::inControlMatrixAttr;
MObject StretchyIkNode::inUpperLengthAttr;
MObject StretchyIkNode::inLowerLengthAttr;
MObject StretchyIkNode::inGlobalScaleAttr;

// Features
MObject StretchyIkNode::inSlideAttr;
MObject StretchyIkNode::inStrectchAttr;
MObject StretchyIkNode::inPoleVectorLockAttr;

// Outputs
MObject StretchyIkNode::outUpperLengthAttr;
MObject StretchyIkNode::outLowerLengthAttr;

MStatus StretchyIkNode::initialize() {
  MStatus status = MS::kSuccess;
  MFnMatrixAttribute fnMatrixAttr;
  MFnUnitAttribute fnUnitAttr;
  MFnNumericAttribute fnNumericAttr;

  // IK Chain Info
  inRootMatrixAttr = fnMatrixAttr.create("inRoot", "inRoot",
                                         MFnMatrixAttribute::kDouble, &status);
  status = addAttribute(inRootMatrixAttr);
  CHECK_MSTATUS_AND_RETURN_IT(status);

  inPoleVectorMatrixAttr = fnMatrixAttr.create(
      "inPoleVector", "inPoleVector", MFnMatrixAttribute::kDouble, &status);
  status = addAttribute(inPoleVectorMatrixAttr);
  CHECK_MSTATUS_AND_RETURN_IT(status);

  inControlMatrixAttr = fnMatrixAttr.create(
      "inControl", "inControl", MFnMatrixAttribute::kDouble, &status);
  status = addAttribute(inControlMatrixAttr);
  CHECK_MSTATUS_AND_RETURN_IT(status);

  inUpperLengthAttr =
      fnUnitAttr.create("inUpperLength", "inUpperLength",
                        MFnUnitAttribute::kDistance, 0.0, &status);
  status = fnUnitAttr.setMin(0.0);
  status = addAttribute(inUpperLengthAttr);
  CHECK_MSTATUS_AND_RETURN_IT(status);

  inLowerLengthAttr =
      fnUnitAttr.create("inLowerLength", "inLowerLength",
                        MFnUnitAttribute::kDistance, 0.0, &status);
  status = fnUnitAttr.setMin(0.0);
  status = addAttribute(inLowerLengthAttr);
  CHECK_MSTATUS_AND_RETURN_IT(status);

  inGlobalScaleAttr = fnNumericAttr.create(
      "inGlobalScale", "inGlobalScale", MFnNumericData::kDouble, 0.0, &status);
  status = fnNumericAttr.setMin(0.0);
  status = addAttribute(inGlobalScaleAttr);
  CHECK_MSTATUS_AND_RETURN_IT(status);

  // Features
  inSlideAttr = fnNumericAttr.create("inSlide", "inSlide",
                                     MFnNumericData::kDouble, 0.0, &status);
  status = fnNumericAttr.setMin(-1.0);
  status = fnNumericAttr.setMax(1.0);
  status = addAttribute(inSlideAttr);
  CHECK_MSTATUS_AND_RETURN_IT(status);

  inStrectchAttr = fnNumericAttr.create("inStrectch", "inStrectch",
                                        MFnNumericData::kDouble, 0.0, &status);
  status = fnNumericAttr.setMin(0.0);
  status = fnNumericAttr.setMax(1.0);
  status = addAttribute(inStrectchAttr);
  CHECK_MSTATUS_AND_RETURN_IT(status);

  inPoleVectorLockAttr =
      fnNumericAttr.create("inPoleVectorLock", "inPoleVectorLock",
                           MFnNumericData::kDouble, 0.0, &status);
  status = fnNumericAttr.setMin(0.0);
  status = fnNumericAttr.setMax(1.0);
  status = addAttribute(inPoleVectorLockAttr);
  CHECK_MSTATUS_AND_RETURN_IT(status);

  // Outputs
  outUpperLengthAttr =
      fnNumericAttr.create("outUpperLength", "outUpperLength",
                           MFnNumericData::kDouble, 0.0, &status);
  status = addAttribute(outUpperLengthAttr);
  CHECK_MSTATUS_AND_RETURN_IT(status);

  outLowerLengthAttr =
      fnNumericAttr.create("outLowerLength", "outLowerLength",
                           MFnNumericData::kDouble, 0.0, &status);
  status = addAttribute(outLowerLengthAttr);
  CHECK_MSTATUS_AND_RETURN_IT(status);

  // IK Chain Info
  status = attributeAffects(inRootMatrixAttr, outUpperLengthAttr);
  status = attributeAffects(inRootMatrixAttr, outLowerLengthAttr);
  status = attributeAffects(inPoleVectorMatrixAttr, outUpperLengthAttr);
  status = attributeAffects(inPoleVectorMatrixAttr, outLowerLengthAttr);
  status = attributeAffects(inControlMatrixAttr, outUpperLengthAttr);
  status = attributeAffects(inControlMatrixAttr, outLowerLengthAttr);
  status = attributeAffects(inUpperLengthAttr, outUpperLengthAttr);
  status = attributeAffects(inUpperLengthAttr, outLowerLengthAttr);
  status = attributeAffects(inLowerLengthAttr, outUpperLengthAttr);
  status = attributeAffects(inLowerLengthAttr, outLowerLengthAttr);
  status = attributeAffects(inGlobalScaleAttr, outUpperLengthAttr);
  status = attributeAffects(inGlobalScaleAttr, outLowerLengthAttr);

  // Features
  status = attributeAffects(inSlideAttr, outUpperLengthAttr);
  status = attributeAffects(inSlideAttr, outLowerLengthAttr);
  status = attributeAffects(inStrectchAttr, outUpperLengthAttr);
  status = attributeAffects(inStrectchAttr, outLowerLengthAttr);
  status = attributeAffects(inPoleVectorLockAttr, outUpperLengthAttr);
  status = attributeAffects(inPoleVectorLockAttr, outLowerLengthAttr);

  return status;
}

void StretchyIkNode::slideLengths(MDataBlock &dataBlock, double &lowerLength,
                                  double &upperLength,
                                  const double &chainLength) {
  double slide = dataBlock.inputValue(inSlideAttr).asDouble();

  // Clamp slide input
  if (slide < -0.999)
    slide *= -0.999;
  else if (slide > 0.999)
    slide *= 0.999;

  if (slide < 0.0) {
    // Blend the upper bone towards 0.0 length
    upperLength = lerp(upperLength, 0.0, -slide);
    lowerLength = lerp(lowerLength, chainLength, -slide);
  } else {
    // Blend the lower bone towards 0.0 length
    upperLength = lerp(upperLength, chainLength, slide);
    lowerLength = lerp(lowerLength, 0.0, slide);
  }
}

void StretchyIkNode::stretchLengths(MDataBlock &dataBlock, double &lowerLength,
                                    double &upperLength,
                                    const double &chainLength,
                                    const MVector &control,
                                    const MVector &root) {
  const MVector ikhDelta = control - root;
  const double desiredChainLength = ikhDelta.length();

  if (desiredChainLength < chainLength)
    return;

  const double stretch = dataBlock.inputValue(inStrectchAttr).asDouble();
  double scaleFactor = 1.0;
  scaleFactor = desiredChainLength / chainLength;

  // Fade stretch in and out
  scaleFactor = lerp(1.0, scaleFactor, stretch);
  upperLength *= scaleFactor;
  lowerLength *= scaleFactor;
}

void StretchyIkNode::poleVectorLockLengths(
    MDataBlock &dataBlock, double &lowerLength, double &upperLength,
    const MVector &control, const MVector &root, const MVector &pullVector) {
  const double poleVectorLock =
      dataBlock.inputValue(inPoleVectorLockAttr).asDouble();

  if (poleVectorLock < 0.0)
    return;

  double desiredUpperLength = (pullVector - root).length();
  double desiredLowerLength = (control - pullVector).length();

  // Blend lengths to the new lengths
  upperLength = lerp(upperLength, desiredUpperLength, poleVectorLock);
  lowerLength = lerp(lowerLength, desiredLowerLength, poleVectorLock);
}

MStatus StretchyIkNode::compute(const MPlug &plug, MDataBlock &dataBlock) {
  if (plug != outUpperLengthAttr && plug != outLowerLengthAttr)
    return MS::kInvalidParameter;

  double upperLength =
      dataBlock.inputValue(inUpperLengthAttr).asDistance().asCentimeters();
  double lowerLength =
      dataBlock.inputValue(inLowerLengthAttr).asDistance().asCentimeters();
  const double chainLength = upperLength + lowerLength;

  // Get the positions of the incoming matrices and get the matrix position
  const MMatrix rootMatrix = dataBlock.inputValue(inRootMatrixAttr).asMatrix();
  const MMatrix pullVectorMatrix =
      dataBlock.inputValue(inPoleVectorMatrixAttr).asMatrix();
  const MMatrix controlMatrix =
      dataBlock.inputValue(inControlMatrixAttr).asMatrix();

  // This gets the world space translation from the matrix
  MVector root(rootMatrix[3]);
  MVector pullVector(pullVectorMatrix[3]);
  MVector control(controlMatrix[3]); // ikh = Inverse Kinematic Handle

  // "pre-scale" space math
  double globalScale = dataBlock.inputValue(inGlobalScaleAttr).asDouble();

  if (globalScale < 0.00001)
    globalScale *= 0.00001;

  root /= globalScale;
  pullVector /= globalScale;
  control /= globalScale;

  StretchyIkNode::slideLengths(dataBlock, lowerLength, upperLength,
                               chainLength);

  StretchyIkNode::stretchLengths(dataBlock, lowerLength, upperLength,
                                 chainLength, control, root);

  StretchyIkNode::poleVectorLockLengths(dataBlock, lowerLength, upperLength,
                                        control, root, pullVector);

  dataBlock.outputValue(outUpperLengthAttr).setDouble(upperLength);
  dataBlock.outputValue(outLowerLengthAttr).setDouble(lowerLength);
  dataBlock.setClean(outUpperLengthAttr);
  dataBlock.setClean(outLowerLengthAttr);

  return MS::kSuccess;
}
