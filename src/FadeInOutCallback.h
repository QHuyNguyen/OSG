#pragma once
#include <osg/BlendFunc>
#include <osg/Material>
#include <osg/Node>
#include <osgAnimation/EaseMotion>
#include <osgDB/ReadFile>
#include <osgUtil/CullVisitor>
#include <osgViewer/Viewer>

class FadeInOutCallback : public osg::NodeCallback
{
protected:
    osg::ref_ptr<osgAnimation::InOutCubicMotion> _motion;
    osg::observer_ptr<osg::Material> _material;
    float _lastDistance;
    int _fadingState;
public:
    FadeInOutCallback(osg::Material* mat) : _material(mat), _lastDistance(1), _fadingState(0)
    {
        _motion = new osgAnimation::InOutCubicMotion;
    }

    virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
    {
        if (_fadingState != 0)
        {
            _motion->update(0.05);
            float value = _motion->getValue();
            float alpha = (_fadingState > 0 ? value : 1.0f - value);
            _material->setDiffuse(osg::Material::FRONT_AND_BACK, osg::Vec4(1.0f, 1.0f, 1.0f, alpha));
            if (value >= 1.0f) _fadingState = 0;
            traverse(node, nv);
            return;
        }

        osgUtil::CullVisitor* cv = static_cast<osgUtil::CullVisitor*>(nv);
        if (cv)
        {
            float distance = cv->getDistanceFromEyePoint(node->getBound().center(), true);
            if (_lastDistance > 0)
            {
                if (_lastDistance > 500 && distance <= 500)
                {
                    _fadingState = 1;
                    _motion->reset();
                }
                else if (_lastDistance < 500 && distance >= 500)
                {
                    _fadingState = -1;
                    _motion->reset();
                }
            }
            _lastDistance = distance;
        }
        traverse(node, nv);
    }
};