#include <maya/MFnPlugin.h>

#include "customNode.h"

MStatus initializePlugin(MObject obj) {
  MFnPlugin fnPlugin(obj, "Autodesk", "1.0", "Any");
  MStatus status = fnPlugin.registerNode(
      "CustomNode", CustomNode::typeId, CustomNode::creator,
      CustomNode::initialize, MPxNode::kDependNode);

  if (status != MS::kSuccess)
    status.perror("Could not register the poseReader node");

  return status;
}

MStatus uninitializePlugin(MObject obj) {
  MFnPlugin fnPlugin;
  fnPlugin.deregisterNode(CustomNode::typeId);

  return MS::kSuccess;
}
