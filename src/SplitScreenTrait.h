#pragma once
#include <osg/Camera>
#include <osgDB/ReadFile>
#include <osgViewer/CompositeViewer>

class SplitScreenTrait
{
public:
    osg::GraphicsContext::Traits* createSplitScreenTrait()
	{
        unsigned int width = 800, height = 600;
        osg::GraphicsContext::WindowingSystemInterface* wsi = osg::GraphicsContext::getWindowingSystemInterface();
        if (wsi) 
            wsi->getScreenResolution( osg::GraphicsContext::ScreenIdentifier(0), width, height);
        osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
        traits->x = 0;
        traits->y = 0;
        traits->width = width;
        traits->height = height;
        traits->windowDecoration = false;
        traits->doubleBuffer = true;
        traits->sharedContext = 0;
        return traits;
	}
};