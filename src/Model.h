#pragma once
#include <osg/ShapeDrawable>
#include <osg/Geode>
#include <osg/MatrixTransform>
#include <osg/Material>
#include <osgViewer/Viewer>

#include <osgDB/ReadFile>

#include <iostream>

#include "FadeInOutCallback.h"

class Model : public osg::MatrixTransform
{
public:
	osg::MatrixTransform* createModel(const std::string& modelName, const osg::Vec3& pos, const osg::Vec4& color)
	{
		//Create render node
		osg::ref_ptr<osg::ShapeDrawable> markNode = new osg::ShapeDrawable();
		markNode->setShape(new osg::Box(osg::Vec3(), 3));
		markNode->setColor(color);

		osg::ref_ptr<osg::Geode> geode = new osg::Geode;
		geode->addDrawable(markNode);
		geode->setNodeMask(0x1);

		osg::ref_ptr<osg::Node> model = osgDB::readNodeFile(modelName);
		model->setNodeMask(0x2);

		osg::ref_ptr<osg::MatrixTransform> trans = new osg::MatrixTransform;
		trans->addChild(model);
		trans->addChild(geode);
		trans->setMatrix(osg::Matrix::translate(pos));

		return trans.release();
	};

	osg::Node* createTempModel(const std::string& modelName, const osg::Vec4& color)
	{
		//Create render node
		osg::ref_ptr<osg::ShapeDrawable> markNode = new osg::ShapeDrawable();
		markNode->setShape(new osg::Box(osg::Vec3(), 3));
		markNode->setColor(color);
		osg::ref_ptr<osg::Geode> geode = new osg::Geode;
		geode->addDrawable(markNode);
		geode->setNodeMask(0x1);

		osg::ref_ptr<osg::Node> model = osgDB::readNodeFile(modelName);
		model->setNodeMask(0x2);

		osg::ref_ptr<osg::Group> obj_node = new osg::Group;
		obj_node->addChild(model);
		obj_node->addChild(markNode);

		//osg::ref_ptr<osg::Material> material = new osg::Material;
		//material->setColorMode(osg::Material::AMBIENT);
		//material->setAmbient(osg::Material::FRONT_AND_BACK, osg::Vec4(0.8f, 0.8f, 0.8f, 1.0f));
		//material->setDiffuse(osg::Material::FRONT_AND_BACK, color * 0.8f);
		//material->setSpecular(osg::Material::FRONT_AND_BACK, color);
		//material->setShininess(osg::Material::FRONT_AND_BACK, 1.0f);

		//Add Fade In and Out Effect
		//obj_node->getOrCreateStateSet()->setAttributeAndModes(material.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
		//obj_node->getOrCreateStateSet()->setAttributeAndModes(new osg::BlendFunc);
		//obj_node->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
		//obj_node->addCullCallback(new FadeInOutCallback(material.get()));

		return obj_node.release();
	};

	osg::MatrixTransform* createStaticNodes(const osg::Vec3& pos, osg::Node* child)
	{
	    osg::ref_ptr<osg::MatrixTransform> trans = new osg::MatrixTransform;
	    trans->addChild(child);
	    trans->setMatrix(osg::Matrix::translate(pos));
	    return trans.release();
	}

	osg::Node* createSeabedFloor()
	{
		return 0;
	}
};