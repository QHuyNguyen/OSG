#pragma once
#include <iostream>
#include <time.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osgViewer/CompositeViewer>
#include <osgViewer/ViewerEventHandlers>
#include <deque>

#include <osg/ref_ptr>
#include <osg/Referenced>
#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <osg/Geometry>
#include <osg/MatrixTransform>
#include <osg/PositionAttitudeTransform>
#include <osg/StateSet>
#include <osg/Fog>
#include <osg/LightSource>
#include <osg/Texture2D>
#include <osg/Program>
#include <osg/Camera>
#include <osg/AnimationPath>
#include <osg/BlendFunc>
#include <osg/Material>
#include <osg/GraphicsContext>
#include <osg/Billboard>
#include <osg/Depth>
#include <osg/LineWidth>

//apply a background image that represent the MDV Sonar 2D View
class TextureSeabed
{
public:
	TextureSeabed() {};

	osg::Node* createTextureMap()
	{
		osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
		texture->setImage(osgDB::readImageFile("Images/osg256.png"));
		osg::ref_ptr<osg::Geometry> quad = osg::createTexturedQuadGeometry(osg::Vec3(), osg::Vec3(1.0f, 0.0f, 0.0f), osg::Vec3(0.0f, 1.0f, 0.0f));
		osg::ref_ptr<osg::Geode> textureMap = new osg::Geode;
		textureMap->addDrawable(quad.get());
		textureMap->getOrCreateStateSet()->setTextureAttributeAndModes(0, texture.get());
		return textureMap.release();
	}

    void createTextureSeabed(osg::Geode* seabed)
    {
        osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
        vertices->push_back(osg::Vec3(-10000.0f, -10000.0f, 0.0f));
        vertices->push_back(osg::Vec3(10000.0f, -10000.0f, 0.0f));
        vertices->push_back(osg::Vec3(10000.0f, 10000.0f, 0.0f));
        vertices->push_back(osg::Vec3(-10000.0f, 10000.0f, 0.0f));
        osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array;
        normals->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));

        osg::ref_ptr<osg::Vec2Array> texcoords = new osg::Vec2Array;
        texcoords->push_back(osg::Vec2(0.0f, 0.0f));
        texcoords->push_back(osg::Vec2(0.0f, 1.0f));
        texcoords->push_back(osg::Vec2(1.0f, 1.0f));
        texcoords->push_back(osg::Vec2(1.0f, 0.0f));

        osg::ref_ptr<osg::Geometry> quad = new osg::Geometry;
        quad->setVertexArray(vertices.get());
        quad->setNormalArray(normals.get());
        quad->setNormalBinding(osg::Geometry::BIND_OVERALL);
        quad->setTexCoordArray(0, texcoords.get());
        quad->addPrimitiveSet(new osg::DrawArrays(GL_QUADS, 0, 4));

        osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
        osg::ref_ptr<osg::Image> image = osgDB::readImageFile("Images/lz.rgb");
        texture->setImage(image.get());
        osg::ref_ptr<osg::Geode> geode = new osg::Geode;
        seabed->addDrawable(quad.get());
        seabed->getOrCreateStateSet()->setTextureAttributeAndModes(0, texture.get());
    }
};