#pragma once
#include <osg/AnimationPath>
#include <osg/MatrixTransform>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

class AnimatingObject
{
public:
	osg::AnimationPathCallback* createPath()
	{
		std::cout << "flying" << std::endl;
		osg::Vec3 position(0.0f, 0.0f, -4.0f);
		osg::ref_ptr<osg::AnimationPath> path = new osg::AnimationPath;
		path->setLoopMode(osg::AnimationPath::LOOP);
		/*path->insert(0.0, osg::AnimationPath::ControlPoint(position, osg::Quat()));
		path->insert(0.01, osg::AnimationPath::ControlPoint(position + osg::Vec3(0.0f, 0.02f, 0.0f), osg::Quat(osg::PI_2, osg::Z_AXIS)));
		path->insert(0.02, osg::AnimationPath::ControlPoint(position + osg::Vec3(0.0f, -0.02f, 0.0f), osg::Quat(osg::PI, osg::Z_AXIS)));*/
		float radius = 100.0f;
		float time = 6.0f;
		unsigned int numSample = 32; //This is refer to how many control point will be created
		float delta_yaw = 2 * osg::PI / ((float)numSample - 1);
		float delta_time = time / (float)numSample;
		for (int i = 0; i < numSample; i++)
		{
			float yaw = delta_yaw * (float)i;
			osg::Vec3 pos(sinf(yaw) * radius, cosf(yaw) * radius, 0.0f);
			osg::Quat rot(-yaw, osg::Z_AXIS);
			path->insert(delta_time * (float)i, osg::AnimationPath::ControlPoint(pos, rot));
		}

		osg::ref_ptr<osg::AnimationPathCallback> apcb = new osg::AnimationPathCallback;
		apcb->setAnimationPath(path);
		return apcb.release();
	}
};