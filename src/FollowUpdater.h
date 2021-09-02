#pragma once
#include <osg/Camera>
#include <osg/MatrixTransform>
#include <osgDB/ReadFile>
#include <osgGA/OrbitManipulator>
#include <osgGA/TrackballManipulator>
#include <osgGA/NodeTrackerManipulator>
#include <osgGA/KeySwitchMatrixManipulator>

#include <osgViewer/Viewer>

class FollowUpdater : public osgGA::GUIEventHandler
{
public:
	osg::ref_ptr<osg::MatrixTransform> _target;
	FollowUpdater(osg::MatrixTransform* model) : _target(model) {};

	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
	{
		osg::ref_ptr<osgViewer::View> view = dynamic_cast<osgViewer::View*>(&aa);
		if (!view || !_target || ea.getEventType() != osgGA::GUIEventAdapter::FRAME)
			return false;
		osg::ref_ptr<osgGA::OrbitManipulator> orbitManipulator = dynamic_cast<osgGA::OrbitManipulator*>(view->getCameraManipulator());
		if (orbitManipulator)
		{
			osg::Matrix targetMatrix;
			if (_target && _target->getNumParents() > 0)
			{
				osg::Group* parent = _target->getParent(0);
				targetMatrix = osg::computeLocalToWorld(parent->getParentalNodePaths()[0]);
			}
			osg::Vec3 targetCenter = _target->getBound().center() * targetMatrix;
			orbitManipulator->setCenter(targetCenter);
		}

		//osg::ref_ptr<osgGA::NodeTrackerManipulator> tracker = dynamic_cast<osgGA::NodeTrackerManipulator*>(view->getCameraManipulator());
		//if (tracker)
		//{
		//	tracker->setHomePosition(osg::Vec3(0, -10, 0), osg::Vec3(), osg::Z_AXIS);
		//	tracker->setAutoComputeHomePosition(false);
		//	tracker->setTrackerMode(osgGA::NodeTrackerManipulator::NODE_CENTER_AND_AZIM);
		//	tracker->setRotationMode(osgGA::NodeTrackerManipulator::TRACKBALL);
		//	tracker->setTrackNode(_target);
		//	/*osg::ref_ptr<osgGA::KeySwitchMatrixManipulator> keySwitch = new
		//		osgGA::KeySwitchMatrixManipulator;
		//	keySwitch->addMatrixManipulator('1', "Trackball", new
		//		osgGA::TrackballManipulator);
		//	keySwitch->addMatrixManipulator('2', "NodeTracker",
		//		tracker.get());*/
		//}
		return false;
	}
};
