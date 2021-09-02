#pragma once
#include <osg/ShapeDrawable>
#include <osg/Geode>
#include <osgViewer/Viewer>

#include <osg/PolygonMode>
#include <osg/ShapeDrawable>
#include <osg/Geometry>
#include <osg/MatrixTransform>
#include <osg/Texture2D>
#include <osg/Depth>

class CameraHUD : osg::Camera
{
public:
	//CameraHUD(osgViewer::View* view) : _mainView(view) {}
	osg::Camera* createCamera(osg::Node* model)
	{
		_mainCamera = new osg::Camera;
		_mainCamera->setClearColor(osg::Vec4(0, 0.2, 0, 1));//Set Camera color
		_mainCamera->setReferenceFrame(osg::Transform::ABSOLUTE_RF); //Keep camera stand still
		_mainCamera->setRenderOrder(osg::Camera::POST_RENDER);
		_mainCamera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		_mainCamera->setViewport(0, 0, 324, 260); //Set Camera position
		//eye: The position of your camera - this you can use to set its height.
		//center : The point your camera is looking at - set this to the center of the observed object.
		//up : The up - vector of your camera - 
			//this controls how your viewport will be rotated about its center and should be equal to[0, 1, 0] in a conventional graphics coordinate system.
		osg::Vec3f eye = osg::Vec3(0, 0, 120);
		osg::Vec3f centre = osg::Vec3f(0.0, 0.0, 0.0);
		osg::Vec3f up = osg::Y_AXIS;
		_mainCamera->setViewMatrix(osg::Matrixd::lookAt(eye, centre, up)); //Set Look Direction
		_mainCamera->setProjectionMatrix(osg::Matrixd::ortho2D(-180.0, 180.0, -180.0, 180.0)); //Set Camera Range
		_mainCamera->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

		_mainCamera->addChild(model);
		_mainCamera->setCullMask(0x1);
		return _mainCamera.release();
	}

	osg::Camera* createCamera(osg::Camera* camera)
	{
		_mainCamera = camera;
		_mainCamera->setClearColor(osg::Vec4(0, 0, 0, 0));//Set Camera color
		_mainCamera->setReferenceFrame(osg::Transform::ABSOLUTE_RF); //Keep camera stand still
		_mainCamera->setRenderOrder(osg::Camera::POST_RENDER);
		_mainCamera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		_mainCamera->setCullMask(0x1);
		_mainCamera->setViewport(0, 0, 324, 260);
		return _mainCamera.release();
	}
	//osg::Node* createCamera(osg::Camera* camera)
	//{
	//	osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
	//	texture->setImage(osgDB::readImageFile("Images/osg256.png"));
	//	osg::ref_ptr<osg::Geometry> quad = osg::createTexturedQuadGeometry(osg::Vec3(), osg::Vec3(1.0f, 0.0f, 0.0f), osg::Vec3(0.0f, 1.0f, 0.0f));
	//	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	//	geode->addDrawable(quad.get());
	//	geode->getOrCreateStateSet()->setTextureAttributeAndModes(0, texture.get());

	//	osg::ref_ptr<osg::Camera> _mainCamera = camera;
	//	_mainCamera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
	//	_mainCamera->setRenderOrder(osg::Camera::POST_RENDER);
	//	//camera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//	_mainCamera->setClearMask(0);
	//	_mainCamera->setCullMask(0x1);
	//	_mainCamera->setViewport(0, 0, 324, 260);
	//	_mainCamera->setProjectionMatrixAsOrtho2D(0.0, 1.0, 0.0, 1.0);
	//	_mainCamera->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	//	_mainCamera->getOrCreateStateSet()->setAttributeAndModes(new osg::Depth(osg::Depth::LEQUAL, 1.0, 1.0));
	//	_mainCamera->addChild(geode.get());
	//	return _mainCamera.release();
	//}

	osg::Camera* createCamera(osg::Geode* textureMap)
	{
		osg::ref_ptr<osg::Camera> camera = new osg::Camera;
		camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
		camera->setRenderOrder(osg::Camera::POST_RENDER);
		//camera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//camera->setCullMask(0x1);
		camera->setClearMask(0);
		camera->setProjectionMatrixAsOrtho2D(0.0, 1.0, 0.0, 1.0);
		camera->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
		camera->getOrCreateStateSet()->setAttributeAndModes(new osg::Depth(osg::Depth::LEQUAL, 1.0, 1.0));

		camera->addChild(textureMap);
		return camera.release();
	}
protected:
	osg::ref_ptr<osg::Camera> _mainCamera;
	osg::ref_ptr<osgViewer::View> _mainView;
};