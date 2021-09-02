#pragma once
#include <osg/MatrixTransform>
#include <osgDB/ReadFile>
#include <osgGA/GUIEventHandler>
#include <osgViewer/Viewer>

#include <osgViewer/ViewerEventHandlers>
#include <osg/Camera>
#include <math.h>

class CameraMover : public osgGA::GUIEventHandler
{
protected:
public:
    osg::Matrixd md;
    //osg::Matrixd originalmd;
    //osg::Quat qua;
    float angle = 0;

    //osg::Matrixd myCameraMatrix;
    //osg::Matrixd cameraRotation;

    osgViewer::Viewer viewer;
    osgViewer::View* view;

    osg::Vec3f eye = osg::Vec3f(1.0, -200.0, 2.0);
    osg::Vec3f centre = osg::Vec3f(0.0, 0.0, 0.0);
    osg::Vec3f up = osg::Vec3f(0.0, 0.0, 1.0);

    //osg::Vec3f originaleye = osg::Vec3f(0.0, -200.0, 0.0);
    //osg::Vec3f originalcentre = osg::Vec3f(0.0, 0.0, 0.0);
    //osg::Vec3f originalup = osg::Vec3f(0.0, 0.0, 1.0);

    //int ConstantVariation = 5;

    CameraMover(osgViewer::Viewer& v) : viewer(v) {}
    CameraMover(osgViewer::View* v) : view(v) 
    {
        osg::Camera* camera = view->getCamera();
        if (camera)
            std::cout << "Yo" << std::endl;
        //camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
        //camera->setClearMask(GL_DEPTH_BUFFER_BIT);
        //camera->setRenderOrder(osg::Camera::POST_RENDER);
        //camera->setAllowEventFocus(false);
        
    }

    ~CameraMover() {}

	bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
	{
        switch (ea.getEventType())
        {
            /*case osgGA::GUIEventAdapter::PUSH:
            {
                osgViewer::View* view = dynamic_cast<osgViewer::View*>(&aa);
                return false;
            }*/
        case osgGA::GUIEventAdapter::KEYDOWN:
        {
            switch (ea.getKey())
            {
            case 'w' | 'W':
            {
                md = view->getCamera()->getViewMatrix();
                osg::Vec3d trans = md.getTrans();
                trans.y() += -1;
                md.setTrans(trans);
                break;
            }
            case 's' | 'S':
            {
                md = view->getCamera()->getViewMatrix();
                osg::Vec3d trans = md.getTrans();
                trans.y() += 1;
                md.setTrans(trans);
                break;
            }
            case 'a' | 'A':
            {
                md = view->getCamera()->getViewMatrix();
                osg::Vec3d trans = md.getTrans();
                trans.x() += 1;
                md.setTrans(trans);
                break;
            }
            case 'd' | 'D':
            {
                md = view->getCamera()->getViewMatrix();
                osg::Vec3d trans = md.getTrans();
                trans.x() += -1;
                md.setTrans(trans);
                break;
            }
            case osgGA::GUIEventAdapter::KEY_Up:
            {
                std::cout << "Forward" << std::endl;
                //md = viewer.getCamera()->getViewMatrix();
                md = view->getCamera()->getViewMatrix();

                osg::Vec3d trans = md.getTrans();
                std::cout << "Translation = " << trans.x() << ", " << trans.y() << ", " << trans.z() << std::endl;

                md.getLookAt(eye, centre, up);
                trans.z() += 2;
                trans.y() -= 0.05;
                md.setTrans(trans);
                break;
            }
            case osgGA::GUIEventAdapter::KEY_Down:
            {
                std::cout << "Backward" << std::endl;
                //md = viewer.getCamera()->getViewMatrix();
                md = view->getCamera()->getViewMatrix();

                osg::Vec3d trans = md.getTrans();
                std::cout << "Translation = " << trans.x() << ", " << trans.y() << ", " << trans.z() << std::endl;

                trans.z() -= 2;
                trans.y() += 0.05;
                md.getLookAt(eye, centre, up);
                md.setTrans(trans);
                break;
            }
            case osgGA::GUIEventAdapter::KEY_Left:
            {
                std::cout << "Rotation" << std::endl;
                //md = viewer.getCamera()->getViewMatrix();
                md = view->getCamera()->getViewMatrix();
                md *= osg::Matrix::rotate(osg::Quat(-0.1f, osg::Y_AXIS));
                std::cout << " End Rotation" << std::endl;
                break;
            }
            case osgGA::GUIEventAdapter::KEY_Right:
            {
                std::cout << "Rotation" << std::endl;
                //md = viewer.getCamera()->getViewMatrix();
                md = view->getCamera()->getViewMatrix();
                md *= osg::Matrix::rotate(osg::Quat(0.1f, osg::Y_AXIS));
                std::cout << " End Rotation" << std::endl;
                break;
            }
            }
        }
        default:
            break;
        }
        return false;
	}

	//Old handle method
 
	//osg::ref_ptr<osg::MatrixTransform> _transform;
	//CameraMover(osg::MatrixTransform* node) : _transform(node) {};
	//virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
	//{
	//	osg::Matrix matrix = _transform->getMatrix();
	//	switch (ea.getKey())
	//	{
	//	case 'a':
	//		matrix *= osg::Matrix::rotate(osg::Quat(0.1, osg::Z_AXIS));
	//		break;
	//	case 'd':
	//		matrix *= osg::Matrix::rotate(osg::Quat(-0.1, osg::Z_AXIS));
	//		break;
	//	case 'w':
	//		matrix *= osg::Matrix::translate(osg::Vec3(0, 1, 0));
	//		break;
	//	case 's':
	//		matrix *= osg::Matrix::translate(osg::Vec3(0, -1, 0));
	//		break;
	//	//case 'w':
	//	//	matrix *= osg::Matrix::rotate(osg::Quat(-0.1f, osg::X_AXIS));
	//	//	break;
	//	//case 's':
	//	//	matrix *= osg::Matrix::rotate(osg::Quat(0.1f, osg::X_AXIS));
	//	//	break;
	//	default:
	//		break;
	//	}
	//	_transform->setMatrix(matrix);
	//	return false;
	//}
};