#include <maya/MFnPlugin.h>

#include "stretchyIkNode.h"

MStatus initializePlugin(MObject obj) {
  MStatus status;
  MFnPlugin fnPlugin(obj, "Autodesk", "1.0", "Any", &status);
  CHECK_MSTATUS_AND_RETURN_IT(status);
  CHECK_MSTATUS_AND_RETURN_IT(fnPlugin.registerNode(
      "StretchyIkNode", StretchyIkNode::typeId, StretchyIkNode::creator,
      StretchyIkNode::initialize, MPxNode::kDependNode));

  return MS::kSuccess;
}

MStatus uninitializePlugin(MObject obj) {
  MFnPlugin fnPlugin(obj);
  CHECK_MSTATUS_AND_RETURN_IT(fnPlugin.deregisterNode(StretchyIkNode::typeId));

  return MS::kSuccess;
}
