#pragma once
#include <osg/Depth>
#include <osg/TexGen>
#include <osg/TextureCubeMap>
#include <osg/ShapeDrawable>
#include <osg/Geode>
#include <osg/MatrixTransform>
#include <osgDB/ReadFile>
#include <osgUtil/CullVisitor>
#include <osgViewer/Viewer>

class Sky : public osg::Transform
{
public:
    Sky();
    Sky(const Sky& copy, osg::CopyOp copyop = osg::CopyOp::SHALLOW_COPY) : osg::Transform(copy, copyop) {}
    META_Node(osg, Sky);
    virtual ~Sky() {}

    void setEnvironmentMap(unsigned int unit, osg::Image* posX, osg::Image* negX,
        osg::Image* posY, osg::Image* negY, osg::Image* posZ, osg::Image* negZ);

    virtual bool computeLocalToWorldMatrix(osg::Matrix& matrix, osg::NodeVisitor* nv) const;
    virtual bool computeWorldToLocalMatrix(osg::Matrix& matrix, osg::NodeVisitor* nv) const;
};

Sky::Sky()
{
    setReferenceFrame(osg::Transform::ABSOLUTE_RF);
    setCullingActive(false);

    osg::StateSet* stateset = getOrCreateStateSet();
    stateset->setAttributeAndModes(new osg::Depth(osg::Depth::LEQUAL, 1, 1));
    stateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
    stateset->setMode(GL_CULL_FACE, osg::StateAttribute::OFF);
    stateset->setRenderBinDetails(5, "RenderBin");
}

void Sky::setEnvironmentMap(unsigned int unit, osg::Image* posX, osg::Image* negX,
    osg::Image* posY, osg::Image* negY, osg::Image* posZ, osg::Image* negZ)
{
    osg::ref_ptr<osg::TextureCubeMap> cubemap = new osg::TextureCubeMap;
    cubemap->setImage(osg::TextureCubeMap::POSITIVE_X, posX);
    cubemap->setImage(osg::TextureCubeMap::NEGATIVE_X, negX);
    cubemap->setImage(osg::TextureCubeMap::POSITIVE_Y, posY);
    cubemap->setImage(osg::TextureCubeMap::NEGATIVE_Y, negY);
    cubemap->setImage(osg::TextureCubeMap::POSITIVE_Z, posZ);
    cubemap->setImage(osg::TextureCubeMap::NEGATIVE_Z, negZ);

    cubemap->setWrap(osg::Texture::WRAP_S, osg::Texture::CLAMP_TO_EDGE);
    cubemap->setWrap(osg::Texture::WRAP_T, osg::Texture::CLAMP_TO_EDGE);
    cubemap->setWrap(osg::Texture::WRAP_R, osg::Texture::CLAMP_TO_EDGE);

    cubemap->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR_MIPMAP_LINEAR);
    cubemap->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);
    cubemap->setResizeNonPowerOfTwoHint(false);
    getOrCreateStateSet()->setTextureAttributeAndModes(unit, cubemap.get());
}

bool Sky::computeLocalToWorldMatrix(osg::Matrix& matrix, osg::NodeVisitor* nv) const
{
    if (nv && nv->getVisitorType() == osg::NodeVisitor::CULL_VISITOR)
    {
        osgUtil::CullVisitor* cv = static_cast<osgUtil::CullVisitor*>(nv);
        matrix.preMult(osg::Matrix::translate(cv->getEyeLocal()));
        return true;
    }
    else
        return osg::Transform::computeLocalToWorldMatrix(matrix, nv);
}

bool Sky::computeWorldToLocalMatrix(osg::Matrix& matrix, osg::NodeVisitor* nv) const
{
    if (nv && nv->getVisitorType() == osg::NodeVisitor::CULL_VISITOR)
    {
        osgUtil::CullVisitor* cv = static_cast<osgUtil::CullVisitor*>(nv);
        matrix.preMult(osg::Matrix::translate(-cv->getEyeLocal()));
        return true;
    }
    else
        return osg::Transform::computeWorldToLocalMatrix(matrix, nv);
}