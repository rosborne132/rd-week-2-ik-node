#include <maya/MFnPlugin.h>

#include "ikNode.h"

MStatus initializePlugin(MObject obj) {
  MFnPlugin fnPlugin(obj, "Autodesk", "1.0", "Any");
  MStatus status =
      fnPlugin.registerNode("IkNode", IkNode::typeId, IkNode::creator,
                            IkNode::initialize, MPxNode::kDependNode);

  if (status != MS::kSuccess)
    status.perror("Could not register the poseReader node");

  return status;
}

MStatus uninitializePlugin(MObject obj) {
  MFnPlugin fnPlugin;
  fnPlugin.deregisterNode(IkNode::typeId);

  return MS::kSuccess;
}
