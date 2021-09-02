//#include <iostream>
//#include <time.h>
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#include <osgDB/ReadFile>
//#include <osgViewer/Viewer>
//#include <osgViewer/CompositeViewer>
//#include <osgViewer/ViewerEventHandlers>
//#include <deque>
//
//#include <osg/ref_ptr>
//#include <osg/Referenced>
//#include <osg/Geode>
//#include <osg/ShapeDrawable>
//#include <osg/Geometry>
//#include <osg/MatrixTransform>
//#include <osg/PositionAttitudeTransform>
//#include <osg/Switch>
//#include <osg/LOD>
//#include <osg/PolygonMode>
//#include <osg/StateSet>
//#include <osg/Fog>
//#include <osg/LightSource>
//#include <osg/Texture2D>
//#include <osg/Program>
//#include <osg/Camera>
//#include <osg/AnimationPath>
//#include <osg/BlendFunc>
//#include <osg/Material>
//#include <osg/GraphicsContext>
//#include <osg/Billboard>
//#include <osg/Point>
//#include <osg/PointSprite>
//#include <osg/NodeVisitor>
//#include <osg/Depth>
//#include <osg/LineWidth>
//#include <osg/ComputeBoundsVisitor>
//
//#include <osgUtil/SmoothingVisitor>
//#include <osgUtil/Tessellator>
//#include <osgUtil/LineSegmentIntersector>
//
//#include <osgGA/OrbitManipulator>
//#include <osgGA/GUIEventHandler>
//#include <osgGA/TrackballManipulator>
//#include <osgGA/StateSetManipulator>
//#include <osgGA/KeySwitchMatrixManipulator>
//#include <osgGA/NodeTrackerManipulator>
//#include <osgGA/DriveManipulator>
//#include <osgGA/FirstPersonManipulator>
//#include <osgGA/FlightManipulator>
//#include <osgGA/TerrainManipulator>
//
//#include <osgAnimation/EaseMotion>
//#include <osgAnimation/BasicAnimationManager>
//#include <osgAnimation/UpdateMatrixTransform>
//#include <osgAnimation/StackedTranslateElement>
//#include <osgAnimation/StackedQuaternionElement>
//#include <osgAnimation/StackedRotateAxisElement>
//
//#include <osgText/Font>
//#include <osgText/Text>
//#include <osgText/Font3D>
//#include <osgText/Text3D>
//
//#include <osgParticle/ParticleSystem>
//#include <osgParticle/ParticleSystemUpdater>
//#include <osgParticle/ModularEmitter>
//#include <osgParticle/ModularProgram>
//#include <osgParticle/AccelOperator>
//
//#include "Model.h"
//#include "CameraHUD.h"
//#include "AnimatingObject.h"
//#include "CameraMover.h";
//#include "TextureSeabed.h";
//
//
//#define RAND(min, max) ((min) + (float)rand()/(RAND_MAX+1) *((max)-(min)))
//
////const char *vertexShaderSource = "#version 330 core\n"
////    "layout (location = 0) in vec4 position;\n"
////    "void main()\n"
////    "{\n"
////    "   gl_Position = position;\n"
////    "}\0";
////const char *vertexFragmentSource = "#version 330 core\n"
////    "layout (location = 0) out vec4 colour;\n"
////    "void main()\n"
////    "{\n"
////    "   colour = vec4(1.0, 0.0, 0.0, 1.0);\n"
////    "}\0";
//static const char* vertSource = {
//     "varying vec3 normal;\n"
//     "void main()\n"
//     "{\n"
//     " normal = normalize(gl_NormalMatrix * gl_Normal);\n"
//     " gl_Position = ftransform();\n"
//     "}\n"
//};
//static const char* fragSource = {
//     "uniform vec4 color1;\n"
//     "uniform vec4 color2;\n"
//     "uniform vec4 color3;\n"
//     "uniform vec4 color4;\n"
//     "varying vec3 normal;\n"
//     "void main()\n"
//     "{\n"
//     " float intensity = dot(vec3(gl_LightSource[0].position), normal); \n"
//     " if (intensity > 0.95) gl_FragColor = color1;\n"
//     " else if (intensity > 0.5) gl_FragColor = color2;\n"
//     " else if (intensity > 0.25) gl_FragColor = color3;\n"
//     " else gl_FragColor = color4;\n"
//     "}\n"
//};
//
//class MonitoringTarget : public osg::Referenced
//{
//public:
//    MonitoringTarget(int id) : _id(id)
//    {
//        std::cout << "Constructing target " << _id << std::endl;
//    }
//protected:
//    ~MonitoringTarget()
//    {
//        std::cout << "Destroying target " << _id << std::endl;
//    }
//    int _id;
//};
//
//MonitoringTarget* createMonitoringTarget(unsigned int id)
//{
//    osg::ref_ptr<MonitoringTarget> target = new MonitoringTarget(id);
//    return target.release();
//  
//}
//
//class InfoVisitor : public osg::NodeVisitor
//{
//public:
//    InfoVisitor() : _level{ 0 }
//    {
//        setTraversalMode(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN);
//    }
//
//    std::string space()
//    {
//        return std::string(_level * 2, ' ');
//    }
//
//    virtual void apply(osg::Node&);
//    virtual void apply(osg::Geode&);
//protected:
//    unsigned int _level;
//};
//
//void InfoVisitor::apply(osg::Node& node)
//{
//    std::cout << space() << node.libraryName() << "::" << node.className() << std::endl;
//    _level++;
//    traverse(node);
//}
//void InfoVisitor::apply(osg::Geode& geode)
//{
//    std::cout << space() << geode.libraryName() << "::" << geode.className() << std::endl;
//
//    for (int i = 0; i < geode.getNumDrawables(); i++)
//    {
//        std::cout << space() << geode.getDrawable(i)->libraryName() << "::" << geode.getDrawable(i)->className() << std::endl;
//    }
//    traverse(geode);
//    _level--;
//}
//
//osg::Node* createLightSource(unsigned int num, const osg::Vec3 &trans, const osg::Vec4 &colour)
//{
//    osg::ref_ptr<osg::Light> light = new osg::Light;
//    light->setLightNum(num);
//    light->setPosition(osg::Vec4(0.0f, 0.0f, 0.0f, 1.0f));
//    light->setDiffuse(colour);
//
//    osg::ref_ptr<osg::LightSource> lightSource = new osg::LightSource;
//    lightSource->setLight(light);
//
//    osg::ref_ptr<osg::MatrixTransform> transform = new osg::MatrixTransform();
//    transform->setMatrix(osg::Matrix::translate(trans));
//    transform->addChild(lightSource);
//
//    return transform.release();
//}
//
//osgViewer::View* createView(int x, int y, int w, int h, osg::Node* node)
//{
//    osg::ref_ptr<osgViewer::View> view = new osgViewer::View;
//    view->setSceneData(node);
//    view->setUpViewInWindow(x, y, w, h);
//    return view.release();
//}
//
//class AnimatingSwitch : public osg::Switch
//{
//public:
//    AnimatingSwitch() : osg::Switch(), _count(0) {}
//    AnimatingSwitch(const AnimatingSwitch& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY)
//        : osg::Switch(copy, copyop), _count(copy._count) {}
//    META_Node(osg, AnimatingSwitch);
//
//    virtual void traverse(osg::NodeVisitor& nv);
//
//protected:
//    unsigned int _count;
//};
//
//void AnimatingSwitch::traverse(osg::NodeVisitor& nv)
//{
//    if (!((++_count) % 60))
//    {
//        setValue(0, !getValue(0));
//        setValue(1, !getValue(1));
//    }
//    osg::Switch::traverse(nv);
//}
//
//class SwitchCallback : public osg::NodeCallback
//{
//public:
//    SwitchCallback() : id{ 0 } {};
//    virtual void operator()(osg::Node* node, osg::NodeVisitor* nv);
//protected:
//    unsigned int id;
//};
//
//void SwitchCallback::operator()(osg::Node* node, osg::NodeVisitor* nv)
//{
//    osg::ref_ptr<osg::Switch> switchNode = static_cast<osg::Switch*>(node);
//    if (!((++id) % 60) && switchNode)
//    {
//        switchNode->setValue(0, !(switchNode->getValue(0)));
//        switchNode->setValue(1, !(switchNode->getValue(1)));
//    }
//    traverse(node, nv);
//}
//
//osg::Geometry* createQuad()
//{
//    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
//    vertices->push_back(osg::Vec3(0.0f, 0.0f, 0.0f));
//    vertices->push_back(osg::Vec3(1.0f, 0.0f, 0.0f));
//    vertices->push_back(osg::Vec3(1.0f, 0.0f, 1.0f));
//    vertices->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));
//    osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array;
//    normals->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));
//    osg::ref_ptr<osg::Vec4Array> colours = new osg::Vec4Array;
//    colours->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
//    colours->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f));
//    colours->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f));
//    colours->push_back(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
//    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
//    geom->setVertexArray(vertices);
//    geom->setNormalArray(normals);
//    geom->setNormalBinding(osg::Geometry::BIND_OVERALL);
//    geom->setColorArray(colours);
//    geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
//    geom->addPrimitiveSet(new osg::DrawArrays(GL_QUADS, 0, 4));
//    return geom.release();
//}
//
//class DynamicQuadCallback : public osg::Drawable::UpdateCallback
//{
//public:
//    virtual void update(osg::NodeVisitor*, osg::Drawable* drawable);
//};
//
//void DynamicQuadCallback::update(osg::NodeVisitor* node, osg::Drawable* drawable)
//{
//    osg::Geometry* quad = static_cast<osg::Geometry*>(drawable);
//    if (!quad) return;
//
//    osg::Vec3Array* vertices = static_cast<osg::Vec3Array*>(
//        quad->getVertexArray());
//    if (!vertices) return;
//
//    osg::Quat quat(osg::PI * 0.01, osg::X_AXIS);
//    vertices->back() = quat * vertices->back();
//
//    quad->dirtyDisplayList();
//    quad->dirtyBound();
//}
//
//class AlphaFadingCallback : public osg::StateAttributeCallback
//{
//public:
//    AlphaFadingCallback()
//    {
//        _motion = new osgAnimation::InOutCubicMotion(0.0f, 1.0f);
//    }
//    virtual void operator()(osg::StateAttribute*, osg::NodeVisitor *);
//protected:
//    osg::ref_ptr<osgAnimation::InOutCubicMotion> _motion;
//};
//
//void AlphaFadingCallback::operator()(osg::StateAttribute *attribute, osg::NodeVisitor *node)
//{
//    osg::ref_ptr<osg::Material> material = static_cast<osg::Material*>(attribute);
//    if (material)
//    {
//        _motion->update(0.005);
//
//        float alpha = _motion->getValue();
//        material->setDiffuse(osg::Material::FRONT_AND_BACK, osg::Vec4(0.0f, 1.0f, 1.0f, alpha));
//    }
//}
//
//void createSamplerClass(float radius, float time, 
//    osgAnimation::Vec3KeyframeContainer* container1, osgAnimation::QuatKeyframeContainer* container2)
//{
//    unsigned int numSamples = 32;
//    float delta_yaw = 2.0f * osg::PI / ((float)numSamples - 1.0f);
//    float delta_time = time / (float)numSamples;
//    for (unsigned int i = 0; i < numSamples; ++i)
//    {
//        float yaw = delta_yaw * (float)i;
//        osg::Vec3 pos(sinf(yaw) * radius, cosf(yaw) * radius, 0.0f);
//        osg::Quat rot(-yaw, osg::Z_AXIS);
//
//        //Create Keyframe for keyframe container
//        /*osgAnimation::Vec3Keyframe *vecKeyframe = new osgAnimation::Vec3Keyframe;
//        vecKeyframe->setTime(delta_time * (float)i);
//        vecKeyframe->setValue(pos);
//        osgAnimation::QuatKeyframe *quatKeyframe = new osgAnimation::QuatKeyframe;
//        quatKeyframe->setTime(delta_time * (float)i);
//        quatKeyframe->setValue(rot);*/
//        //Assign keyframe to keyframe container
//        container1->push_back(osgAnimation::Vec3Keyframe(delta_time * (float)i, pos));
//        container2->push_back(osgAnimation::QuatKeyframe(delta_time * (float)i, rot));
//    }
//
//
//}
//
//
//class ModelController : public osgGA::GUIEventHandler
//{
//protected:
//    osg::ref_ptr<osg::MatrixTransform> _model;
//public:
//    ModelController(osg::MatrixTransform* model) : _model{ model } {}
//    virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
//};
//
//bool ModelController::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
//{
//    if (!_model) return false;
//    osg::Matrix matrix = _model->getMatrix();
//    switch (ea.getEventType())
//    {
//    case osgGA::GUIEventAdapter::KEYDOWN:
//        switch (ea.getKey())
//        {
//        case 'a': case 'A':
//            matrix *= osg::Matrix::rotate(-0.1f, osg::Z_AXIS);
//            break;
//        case 'd': case 'D':
//            matrix *= osg::Matrix::rotate(0.1f, osg::Z_AXIS);
//            break;
//        case 'w': case 'W':
//            matrix *= osg::Matrix::rotate(-0.1f, osg::X_AXIS);
//            break;
//        case 's': case 'S':
//            matrix *= osg::Matrix::rotate(0.1f, osg::X_AXIS);
//            break;
//        default:
//            break;
//        }
//        _model->setMatrix(matrix);
//        break;
//    default:
//        break;
//    }
//    return false;
//}
//
////class PickHandler : public osgGA::GUIEventHandler
////{
////protected:
////    osg::ref_ptr<osg::MatrixTransform> _selectionBox;
////public:
////    osg::Node* getOrCreateSelectionBox();
////    virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
////};
////
////osg::Node* PickHandler::getOrCreateSelectionBox()
////{
////    if (!_selectionBox)
////    {
////        osg::ref_ptr<osg::ShapeDrawable> shape = new osg::ShapeDrawable;
////        shape->setShape(new osg::Box(osg::Vec3(), 1.0));
////        //shape->setColor(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f));
////        osg::ref_ptr<osg::Geode> geod = new osg::Geode;
////        geod->addDrawable(shape);
////
////        _selectionBox = new osg::MatrixTransform;
////        _selectionBox->addChild(geod);
////        _selectionBox->setNodeMask(0x1); //What is this???
////        osg::ref_ptr<osg::StateSet> stateset = _selectionBox->getOrCreateStateSet();
////        stateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
////        stateset->setAttributeAndModes(new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE));
////    }
////    return _selectionBox.get();
////}
////
////bool PickHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
////{
////    if (ea.getEventType() != osgGA::GUIEventAdapter::RELEASE || ea.getButton() != osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON
////        || ea.getModKeyMask() & osgGA::GUIEventAdapter::MODKEY_CTRL)
////        return false;
////    osgViewer::Viewer* viewer = dynamic_cast<osgViewer::Viewer*>(&aa);
////    if (viewer)
////    {
////        osg::ref_ptr<osgUtil::LineSegmentIntersector> intersector = new osgUtil::LineSegmentIntersector(osgUtil::Intersector::WINDOW
////            , ea.getX(), ea.getY());
////        osgUtil::IntersectionVisitor iv(intersector.get());
////        iv.setTraversalMask(~0x1);
////        viewer->getCamera()->accept(iv);
////        
////        if (intersector->containsIntersections())
////        {
////            osgUtil::LineSegmentIntersector::Intersection result = *(intersector->getIntersections().begin());
////            osg::BoundingBox bb = result.drawable->getBoundingBox();
////            osg::Vec3 worldCenter = bb.center() *
////                osg::computeLocalToWorld(result.nodePath);
////            _selectionBox->setMatrix(
////                osg::Matrix::scale(bb.xMax() - bb.xMin(),
////                    bb.yMax() - bb.yMin(),
////                    bb.zMax() - bb.zMin()) *
////                osg::Matrix::translate(worldCenter));
////
////            std::cout << "Click" << std::endl;
////        }
////    }
////    return false;
////}
//
//class ObjectControlHandler : public osgGA::GUIEventHandler
//{
//protected:
//    osg::ref_ptr<osg::MatrixTransform> _model;
//public:
//    ObjectControlHandler(osg::MatrixTransform* model) : _model(model) {}
//    virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
//    {
//        if (!_model) return false;
//        osg::Matrix matrix = _model->getMatrix();
//
//        switch (ea.getKey())
//        {
//        case 'w':
//            matrix *= osg::Matrix::translate(osg::Vec3(0, -0.5, 0));
//            break;
//        case 's':
//            matrix *= osg::Matrix::translate(osg::Vec3(0, 0.5, 0));
//            break;
//        case 'a':
//            matrix *= osg::Matrix::translate(osg::Vec3(0.5, 0, 0));
//            break;
//        case 'd':
//            matrix *= osg::Matrix::translate(osg::Vec3(-0.5, 0, 0));
//            break;
//        default:
//            break;
//        }
//
//        _model->setMatrix(matrix);
//
//        return false;
//    }
//};
//
////OpenSceneGraph 3 Cookbook Section
//
//
//osg::Camera* createHUDCamera(double left, double right, double bottom, double top)
//{
//    osg::ref_ptr<osg::Camera> camera = new osg::Camera;
//    camera->setClearMask(GL_DEPTH_BUFFER_BIT);
//    camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
//    camera->setRenderOrder(osg::Camera::POST_RENDER);
//    camera->setAllowEventFocus(false);
//    camera->setProjectionMatrix(osg::Matrix::ortho2D(left, right, bottom, top));
//    osg::StateSet* ss = camera->getOrCreateStateSet();
//    ss->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
//    return camera.release();
//}
//
//osg::ref_ptr<osgText::Font> g_font = osgText::readFontFile("fonts/arial.ttf");
//osgText::Text* createText(const osg::Vec3& pos, const std::string& content, float size)
//{
//    osg::ref_ptr<osgText::Text> text = new osgText::Text;
//    text->setDataVariance(osg::Object::DYNAMIC);
//    text->setFont(g_font);
//    text->setCharacterSize(size);
//    text->setAxisAlignment(osgText::TextBase::XY_PLANE);
//    text->setPosition(pos);
//    text->setText(content);
//    return text.release();
//}
//
//class PickHandler : public osgGA::GUIEventHandler
//{
//public:
//    virtual void doUserOperations(const osgUtil::LineSegmentIntersector::Intersection& result)
//    {
//        if (result.nodePath.size() > 0)
//        {
//            osg::Geode* geode = dynamic_cast<osg::Geode*>(result.nodePath.back());
//            if (geode) geode->removeDrawable(result.drawable.get());
//        }
//    }
//
//    virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
//    {
//        if (ea.getEventType() != osgGA::GUIEventAdapter::RELEASE || ea.getButton() != osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON
//            || !(ea.getModKeyMask() & osgGA::GUIEventAdapter::MODKEY_CTRL))
//        {
//            return false;
//        }
//        osgViewer::View* view = dynamic_cast<osgViewer::View*>(&aa);
//        if (view)
//        {
//            osg::ref_ptr<osgUtil::LineSegmentIntersector> intersector = new osgUtil::LineSegmentIntersector
//                                (osgUtil::Intersector::WINDOW, ea.getX(), ea.getY());
//            osgUtil::IntersectionVisitor iv(intersector.get());
//            view->getCamera()->accept(iv);
//
//            if (intersector->containsIntersections())
//            {
//                osgUtil::LineSegmentIntersector::Intersection result = *(intersector->getIntersections().begin());
//                doUserOperations(result);
//            }
//        }
//        return false;
//    }
//};
//
//class RemoveShapeHandler : public PickHandler
//{
//    virtual void doUserOperations(osgUtil::LineSegmentIntersector::Intersection& result)
//    {
//        if (result.nodePath.size() > 0)
//        {
//            osg::Geode* geode = dynamic_cast<osg::Geode*>(result.nodePath.back());
//            if (geode) geode->removeDrawable(result.drawable.get());
//        }
//    }
//};
//
//class ObserveShapeCallback : public osg::NodeCallback
//{
//public:
//    osg::ref_ptr<osgText::Text> _text;
//    osg::observer_ptr<osg::Drawable> _drawable1;
//    osg::observer_ptr<osg::Drawable> _drawable2;
//    virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
//    {
//        std::string content;
//        if (_drawable1.valid()) content += "Drawable 1; ";
//        if (_drawable2.valid()) content += "Drawable 2; ";
//        if (_text.valid()) _text->setText(content);
//    }
//};
//
//class TempPickHandler : public osgGA::GUIEventHandler
//{
//    virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
//    {
//        if (ea.getEventType() != osgGA::GUIEventAdapter::RELEASE || ea.getButton() != osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON
//            || !(ea.getModKeyMask() & osgGA::GUIEventAdapter::MODKEY_CTRL))
//            return false;
//        osg::ref_ptr<osgViewer::View> view = dynamic_cast<osgViewer::View*>(&aa);
//        if (view)
//        {
//            osg::ref_ptr<osgUtil::LineSegmentIntersector> intersector = new osgUtil::LineSegmentIntersector
//            (osgUtil::Intersector::WINDOW, ea.getX(), ea.getY());
//            osgUtil::IntersectionVisitor iv(intersector);
//            view->getCamera()->accept(iv);
//
//            if (intersector->containsIntersections())
//            {
//                osgUtil::LineSegmentIntersector::Intersection result = *(intersector->getIntersections().begin());
//                osg::ref_ptr<osg::Geode> geod = dynamic_cast<osg::Geode*>(result.nodePath.back());
//                if (geod)
//                    geod->removeDrawable(result.drawable.get());
//            }
//        }
//        return false;
//    }
//};
//
//class ColourPicker : public osgGA::GUIEventHandler
//{
//    virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
//    {
//        if (ea.getEventType() != osgGA::GUIEventAdapter::RELEASE || ea.getButton() != osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON
//            || !(ea.getModKeyMask() & osgGA::GUIEventAdapter::MODKEY_CTRL))
//            return false;
//        osgViewer::View* view = dynamic_cast<osgViewer::View*>(&aa);
//        if (view)
//        {
//            osg::ref_ptr<osgUtil::LineSegmentIntersector> intersector = new osgUtil::LineSegmentIntersector(
//                osgUtil::LineSegmentIntersector::WINDOW, ea.getX(), ea.getY());
//            osgUtil::IntersectionVisitor iv(intersector);
//            view->getCamera()->accept(iv);
//            if (intersector->containsIntersections())
//            {
//                osgUtil::LineSegmentIntersector::Intersection result = *(intersector->getIntersections().begin());
//                osg::ShapeDrawable* shape = dynamic_cast<osg::ShapeDrawable*>(result.drawable.get());
//                if (shape)
//                {
//                    shape->setColor(osg::Vec4(
//                        1.0f, 1.0f, 1.0f, 2.0f) - shape->getColor());
//                }
//            }
//        }
//        return false;
//    }
//};
//
//osg::MatrixTransform* createWheel(osg::ShapeDrawable* shape, const osg::Matrix& matrix)
//{
//    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
//    geode->addDrawable(shape);
//    osg::ref_ptr<osg::MatrixTransform> transform = new osg::MatrixTransform;
//    transform->setMatrix(matrix);
//    transform->addChild(geode);
//    return transform.release();
//}
//
//osg::AnimationPathCallback* createAnimation(const osg::Vec3& base)
//{
//    osg::ref_ptr<osg::AnimationPath> wheelPath =
//        new osg::AnimationPath;
//    wheelPath->setLoopMode(osg::AnimationPath::LOOP);
//    wheelPath->insert(0.0, osg::AnimationPath::ControlPoint(
//        base, osg::Quat()));
//    wheelPath->insert(0.01, osg::AnimationPath::ControlPoint(
//        base + osg::Vec3(0.0f, 0.02f, 0.0f), osg::Quat(
//            osg::PI_2, osg::Z_AXIS)));
//    wheelPath->insert(0.02, osg::AnimationPath::ControlPoint(
//        base + osg::Vec3(0.0f, -0.02f, 0.0f), osg::Quat(
//            osg::PI, osg::Z_AXIS)));
//    osg::ref_ptr<osg::AnimationPathCallback> apcb =
//        new osg::AnimationPathCallback;
//    apcb->setAnimationPath(wheelPath.get());
//    return apcb.release();
//}
//
//class Compass : public osg::Camera
//{
//protected:
//    virtual ~Compass() {}
//    osg::ref_ptr<osg::MatrixTransform> _plateTransform;
//    osg::ref_ptr<osg::MatrixTransform> _needleTransform;
//    osg::observer_ptr<osg::Camera> _mainCamera;
//public:
//    Compass() {}
//    Compass(const Compass& copy, osg::CopyOp copyop = osg::CopyOp::SHALLOW_COPY) : osg::Camera(copy, copyop),
//        _plateTransform(copy._plateTransform),//_needleTransform(copy._needleTransform),
//        _mainCamera(copy._mainCamera) {}
//    META_Node(osg, Compass);
//    void setPlate(osg::MatrixTransform* plate)
//    {
//        _plateTransform = plate;
//    }
//    void setNeedle(osg::MatrixTransform* needle)
//    {
//        _needleTransform = needle;
//    }
//    void setMainCamera(osg::Camera* camera)
//    {
//        _mainCamera = camera;
//    }
//    
//    virtual void traverse(osg::NodeVisitor& nv)
//    {
//        if (_mainCamera.valid() && nv.getVisitorType() == osg::NodeVisitor::CULL_VISITOR)
//        {
//            osg::Matrix matrix = _mainCamera->getViewMatrix();
//            matrix.setTrans(osg::Vec3());
//            osg::Vec3 northVec = osg::Z_AXIS * matrix;
//            northVec.z() = 0.0f;
//            northVec.normalize();
//
//            osg::Vec3 axis = osg::Y_AXIS ^ northVec;
//            float angle = atan2(axis.length(), osg::Y_AXIS * northVec);
//            axis.normalize();
//
//            if (_plateTransform.valid())
//                _plateTransform->setMatrix(osg::Matrix::rotate(angle, axis));
//        }
//        _plateTransform->accept(nv);
//        //_needleTransform->accept(nv);
//        osg::Camera::traverse(nv);
//    }
//};
//
//osg::MatrixTransform* createCompassPlate(const std::string& image, float radius, float height)
//{
//    osg::Vec3 center(-radius, -radius, height);
//    osg::ref_ptr<osg::Drawable> quad = osg::createTexturedQuadGeometry(center, osg::Vec3(radius * 2, 0, 0), osg::Vec3(0, radius * 2, 0));
//    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
//    geode->addDrawable(quad);
//
//    osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
//    texture->setImage(osgDB::readImageFile("Images/compass_plate.png"));
//
//    osg::ref_ptr<osg::MatrixTransform> part = new osg::MatrixTransform;
//    osg::StateSet* ss = part->getOrCreateStateSet();
//    ss->setTextureAttributeAndModes(0, texture);
//    ss->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
//    part->addChild(geode);
//    return part.release();
//};
//osg::MatrixTransform* createCompassNeedle(const std::string& image, float radius, float height)
//{
//    osg::Vec3 center(-radius, -radius, height);
//    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
//    geode->addDrawable(createTexturedQuadGeometry(center, osg::Vec3(radius * 2.0f, 0.0f, 0.0f), osg::Vec3(0.0f, radius * 2.0f, 0.0f)));
//    osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
//    texture->setImage(osgDB::readImageFile("Images/compass_needle.png"));
//    osg::ref_ptr<osg::MatrixTransform> part = new osg::MatrixTransform;
//    part->getOrCreateStateSet()->setTextureAttributeAndModes(0, texture.get());
//    part->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
//    part->addChild(geode.get());
//    return part.release();
//    /*osg::Vec3 center(-radius, -radius, height);
//    osg::ref_ptr<osg::Drawable> quad = osg::createTexturedQuadGeometry(center, osg::Vec3(radius * 2, 0, 0), osg::Vec3(0, radius * 2, 0));
//    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
//    geode->addDrawable(quad);
//
//    osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
//    texture->setImage(osgDB::readImageFile(image));
//
//    osg::ref_ptr<osg::MatrixTransform> part = new osg::MatrixTransform;
//    osg::StateSet* ss = part->getOrCreateStateSet();
//    ss->setTextureAttributeAndModes(0, texture);
//    ss->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
//    part->addChild(geode);
//    return part.release();*/
//};
//
//class TestVisitor : public osg::NodeVisitor
//{
//public:
//    unsigned int _count;
//    int time = 1;
//    TestVisitor() : _count(0) { setTraversalMode(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN); }
//    std::string spaces()
//    {
//        return std::string(_count * 2, ' ');
//    }
//
//    virtual void apply(osg::Node& node)
//    {
//        std::cout << time << std::endl;
//        time++;
//        std::cout << spaces() << node.libraryName() << "::" << node.className() << std::endl;
//        _count++;
//        traverse(node);
//        _count--;
//    }
//
//    virtual void apply(osg::Geode& geode) 
//    {
//        std::cout << time << std::endl;
//        time++;
//        std::cout << spaces() << geode.libraryName() << "::" << geode.className() << std::endl;
//        _count++;
//        for (unsigned int i = 0; i < geode.getNumDrawables(); i++)
//        {
//            osg::Drawable* drawable = geode.getDrawable(i);
//            std::cout << spaces() << drawable->libraryName() << "::" << drawable->className() << std::endl;
//        }
//        traverse(geode);
//        _count--;
//    }
//};
//
//class Tracking : public osg::Camera
//{
//public:
//    osg::ref_ptr<osg::Camera> _camera;
//    osg::ref_ptr<osg::MatrixTransform> _compass;
//    Tracking() {}
//    ~Tracking() {}
//    Tracking(const Tracking& tracking, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY) : 
//        osg::Camera(tracking, copyop), _compass(tracking._compass), _camera(tracking._camera)
//    {}
//    META_Node(osg, Tracking);
//    void setCompass(osg::MatrixTransform* compass)
//    {
//        _compass = compass;
//    }
//    void setMainCamera(osg::Camera* camera)
//    {
//        _camera = camera;
//    }
//    virtual void traverse(osg::NodeVisitor& nv)
//    {
//        if (nv.getVisitorType() == osg::NodeVisitor::CULL_VISITOR)
//        {
//            osg::Matrix matrix = _camera->getViewMatrix();
//            matrix.setTrans(osg::Vec3());
//            osg::Vec3 northVec = osg::Z_AXIS * matrix;
//            northVec.z() = 0.0f;
//            northVec.normalize();
//
//            osg::Vec3 axis = osg::Y_AXIS ^ northVec;
//            float angle = atan2(axis.length(), osg::Y_AXIS * northVec);
//            axis.normalize();
//            
//            if (_compass.valid())
//                _compass->setMatrix(osg::Matrix::rotate(angle, axis));
//        }
//        _compass->accept(nv);
//        osg::Camera::traverse(nv);
//    }
//};
//
//class EarthHandle : public osgGA::GUIEventHandler
//{
//public:
//    osg::ref_ptr<osg::MatrixTransform> _node;
//    EarthHandle(osg::MatrixTransform* node) : _node(node) {}
//    virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
//    {
//        if (!_node) return false;
//        osg::Matrix matrix = _node->getMatrix();
//
//        
//        switch (ea.getKey())
//        {
//        case 'a': case 'A':
//            matrix *= osg::Matrix::rotate(-0.1f, osg::Z_AXIS);
//            break;
//        case 'd': case 'D':
//            matrix *= osg::Matrix::rotate(0.1f, osg::Z_AXIS);
//            break;
//        case 'w': case 'W':
//            matrix *= osg::Matrix::rotate(-0.1f, osg::X_AXIS);
//            break;
//        case 's': case 'S':
//            matrix *= osg::Matrix::rotate(0.1f, osg::X_AXIS);
//            break;
//        default:
//            break;
//        }
//        _node->setMatrix(matrix);
//        return false;
//    }
//};
//
//osg::Node* createNeedle(float width, float height, float depth, const osg::Vec4& color, float angle, double period)
//{
//    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
//    vertices->push_back(osg::Vec3(-0.5* height, 0, -0.1 * width));
//    vertices->push_back(osg::Vec3(0.5 * height, 0, -0.1 * width));
//    vertices->push_back(osg::Vec3(-0.5 * height, 0, 0.8 * width));
//    vertices->push_back(osg::Vec3(0.5 * height, 0, 0.8 * width));
//    vertices->push_back(osg::Vec3(0, 0, 0.9 * width));
//    osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array;
//    normals->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));
//    osg::ref_ptr<osg::Vec4Array> colours = new osg::Vec4Array;
//    colours->push_back(color);
//    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
//    geom->setVertexArray(vertices);
//    geom->setNormalArray(normals);
//    geom->setNormalBinding(osg::Geometry::BIND_OVERALL);
//    geom->setColorArray(colours);
//    geom->setColorBinding(osg::Geometry::BIND_OVERALL);
//    geom->addPrimitiveSet(new osg::DrawArrays(GL_TRIANGLE_STRIP, 0, 5));
//    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
//    geode->addDrawable(geom);
//    osg::ref_ptr<osg::MatrixTransform> needleTransform = new osg::MatrixTransform;
//    needleTransform->addChild(geode);
//    osg::ref_ptr<osg::AnimationPath> clockPath = new osg::AnimationPath;
//    clockPath->setLoopMode(osg::AnimationPath::LOOP);
//    clockPath->insert(0, osg::AnimationPath::ControlPoint(osg::Vec3(0.0f, depth, 0.0f), osg::Quat(angle, osg::Y_AXIS)));
//    clockPath->insert(period * 0.5, osg::AnimationPath::ControlPoint(osg::Vec3(0.0f, depth, 0.0f), osg::Quat(angle + osg::PI,osg::Y_AXIS)));
//    clockPath->insert(period, osg::AnimationPath::ControlPoint(osg::Vec3(0.0f, depth, 0.0f), osg::Quat(angle + osg::PI * 2.0f,osg::Y_AXIS)));
//    osg::ref_ptr<osg::AnimationPathCallback> clockPathCallback = new osg::AnimationPathCallback;
//    clockPathCallback->setAnimationPath(clockPath);
//    needleTransform->setUpdateCallback(clockPathCallback);
//    return needleTransform.release();
//}
//
//const osg::Vec4 normalColor(1.0f, 1.0f, 1.0f, 1.0f);
//const osg::Vec4 selectedColor(1.0f, 0.0f, 0.0f, 0.5f);
//osg::Geometry* createSimpleGeometry()
//{
//    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array(8);
//    (*vertices)[0].set(-0.5f, -0.5f, -0.5f);
//    (*vertices)[1].set(0.5f, -0.5f, -0.5f);
//    (*vertices)[2].set(0.5f, 0.5f, -0.5f);
//    (*vertices)[3].set(-0.5f, 0.5f, -0.5f);
//    (*vertices)[4].set(-0.5f, -0.5f, 0.5f);
//    (*vertices)[5].set(0.5f, -0.5f, 0.5f);
//    (*vertices)[6].set(0.5f, 0.5f, 0.5f);
//    (*vertices)[7].set(-0.5f, 0.5f, 0.5f);
//
//    osg::ref_ptr<osg::DrawElementsUInt> indices = new osg::DrawElementsUInt(GL_QUADS, 24);
//    (*indices)[0] = 0; (*indices)[1] = 1; (*indices)[2] = 2;
//    (*indices)[3] = 3;
//    (*indices)[4] = 4; (*indices)[5] = 5; (*indices)[6] = 6;
//    (*indices)[7] = 7;
//    (*indices)[8] = 0; (*indices)[9] = 1; (*indices)[10] = 5;
//    (*indices)[11] = 4;
//    (*indices)[12] = 1; (*indices)[13] = 2; (*indices)[14] = 6;
//    (*indices)[15] = 5;
//    (*indices)[16] = 2; (*indices)[17] = 3; (*indices)[18] = 7;
//    (*indices)[19] = 6;
//    (*indices)[20] = 3; (*indices)[21] = 0; (*indices)[22] = 4;
//    (*indices)[23] = 7;
//
//    osg::ref_ptr<osg::Vec4Array> colours = new osg::Vec4Array;
//    colours->push_back(normalColor);
//
//    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
//    geom->setVertexArray(vertices);
//    geom->setColorArray(colours);
//    geom->setColorBinding(osg::Geometry::BIND_OVERALL);
//    geom->addPrimitiveSet(indices);
//
//    geom->setDataVariance(osg::Object::DYNAMIC);
//    geom->setUseDisplayList(false);
//    geom->setUseVertexBufferObjects(true);
//    osgUtil::SmoothingVisitor::smooth(*geom);
//    return geom.release();
//}
//
//class ChangeColourHandle : public osgGA::GUIEventHandler
//{
//public:
//    osg::ref_ptr<osg::Geometry> shape;
//    ChangeColourHandle() : shape(0) {}
//    virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
//    {
//        if (ea.getEventType() != osgGA::GUIEventAdapter::RELEASE || ea.getButton() != osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON
//            || !(ea.getModKeyMask() & osgGA::GUIEventAdapter::MODKEY_CTRL))
//            return false;
//        osgViewer::View* view = dynamic_cast<osgViewer::View*>(&aa);
//        if (view)
//        {
//            osg::ref_ptr<osgUtil::LineSegmentIntersector> intersector = new osgUtil::LineSegmentIntersector
//                (osgUtil::Intersector::WINDOW, ea.getX(), ea.getY());
//            osgUtil::IntersectionVisitor iv(intersector);
//            view->getCamera()->accept(iv);
//            if (intersector->containsIntersections())
//            {
//                osgUtil::LineSegmentIntersector::Intersection result = *(intersector->getIntersections().begin());
//                shape = dynamic_cast<osg::Geometry*>(result.drawable.get());
//                osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
//                colors->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 0.5f));
//                colors->dirty();
//                shape->setColorArray(colors);
//            }
//        }
//    }
//};
//
//osgViewer::View* createView(int screenNum)
//{
//    unsigned int width = 800, height = 600;
//    osg::ref_ptr<osg::GraphicsContext::WindowingSystemInterface> wsi = osg::GraphicsContext::getWindowingSystemInterface();
//    if (wsi)
//        wsi->getScreenResolution(osg::GraphicsContext::ScreenIdentifier(screenNum), width, height);
//
//    osg::ref_ptr<osg::GraphicsContext::Traits> trait = new osg::GraphicsContext::Traits;
//    trait->x = 50;
//    trait->y = 50;
//    trait->width = width;
//    trait->height = height;
//    trait->windowDecoration = false;
//    trait->doubleBuffer = true;
//    trait->sharedContext = 0;
//
//    osg::ref_ptr<osg::GraphicsContext> gc = osg::GraphicsContext::createGraphicsContext(trait);
//    osg::Camera* camera = new osg::Camera;
//    camera->setGraphicsContext(gc);
//    camera->setViewport(0, 0, trait->width, trait->height);
//    camera->setProjectionMatrixAsPerspective(30.0f, static_cast<double>(width) / static_cast<double>(height),
//        1.0f, 10000.0f);
//    GLenum buffer = trait->doubleBuffer ? GL_BACK : GL_FRONT;
//    camera->setDrawBuffer(buffer);
//    camera->setReadBuffer(buffer);
//
//    osg::ref_ptr<osgViewer::View> view = new osgViewer::View;
//    view->setCamera(camera);
//    view->setCameraManipulator(new osgGA::TrackballManipulator);
//    return view.release();
//}
//
//osg::Camera* createSlaveCamera(int x, int y, int width, int height)
//{
//    osg::GraphicsContext::Traits* trait = new osg::GraphicsContext::Traits;
//    trait->x = x;
//    trait->y = y;
//    trait->width = width;
//    trait->height = height;
//    trait->windowDecoration = false;
//    trait->doubleBuffer = true;
//    trait->sharedContext = 0;
//    osg::ref_ptr<osg::GraphicsContext> gc = osg::GraphicsContext::createGraphicsContext(trait);
//
//    osg::ref_ptr<osg::Camera> camera = new osg::Camera;
//    camera->setGraphicsContext(gc);
//    camera->setViewport(new osg::Viewport(0, 0, width, height));
//    GLenum buffer = trait->doubleBuffer ? GL_FRONT : GL_BACK;
//    camera->setDrawBuffer(buffer);
//    camera->setReadBuffer(buffer);
//    return camera.release();
//}
//
//const double radius_earth = 6378.137;
//const double radius_sun = 695990.0;
//const double AU = 149697900.0;
//osg::Node* createScene()
//{
//    //Create Earth
//    osg::ref_ptr<osg::ShapeDrawable> earthShape = new osg::ShapeDrawable;
//    earthShape->setShape(new osg::Sphere(osg::Vec3(), radius_earth));
//    osg::ref_ptr<osg::Geode> earth = new osg::Geode;
//    earth->addDrawable(earthShape);
//    osg::ref_ptr<osg::Texture2D> earthTexture = new osg::Texture2D;
//    earthTexture->setImage(osgDB::readImageFile(("Images/land_shallow_topo_2048.jpg")));
//    earth->getOrCreateStateSet()->setTextureAttributeAndModes(0, earthTexture);
//    //Create Sun
//    osg::ref_ptr<osg::ShapeDrawable> sunShape = new osg::ShapeDrawable;
//    sunShape->setShape(new osg::Sphere(osg::Vec3(), radius_sun));
//    sunShape->setColor(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
//    osg::ref_ptr<osg::Geode> sun = new osg::Geode;
//    sun->addDrawable(sunShape);
//    osg::ref_ptr<osg::MatrixTransform> sunTransform = new osg::MatrixTransform;
//    sunTransform->addChild(sun);
//    sunTransform->setMatrix(osg::Matrix::translate(0, AU, 0));
//    
//    osg::ref_ptr<osg::Group> root = new osg::Group;
//    root->addChild(earth);
//    root->addChild(sunTransform);
//    return root.release();
//}
//
//osg::AnimationPathCallback* createAnimationPathCallback(float radius, float time)
//{
//    osg::ref_ptr<osg::AnimationPath> path =
//        new osg::AnimationPath;
//    path->setLoopMode(osg::AnimationPath::LOOP);
//    unsigned int numSamples = 32;
//    float delta_yaw = 2.0f * osg::PI / ((float)numSamples - 1.0f);
//    float delta_time = time / (float)numSamples;
//    for (unsigned int i = 0; i < numSamples; ++i)
//    {
//        float yaw = delta_yaw * (float)i;
//        osg::Vec3 pos(sinf(yaw) * radius, cosf(yaw) * radius, 0.0f);
//        osg::Quat rot(-yaw, osg::Z_AXIS);
//        path->insert(delta_time * (float)i,
//            osg::AnimationPath::ControlPoint(pos, rot));
//    }
//    osg::ref_ptr<osg::AnimationPathCallback> apcb =
//        new osg::AnimationPathCallback;
//    apcb->setAnimationPath(path.get());
//    return apcb.release();
//}
//
//const unsigned int MAIN_CAMERA_MASK = 0x1;
//const unsigned int RADAR_CAMERA_MASK = 0x2;
//
//
//osg::Node* createObject(const std::string& filename, const osg::Vec4& color)
//{
//    //Read the model from file and set up a node mask indicating it to be rendered in the main camera
//    float size = 5.0f;
//    osg::ref_ptr<osg::Node> model_node = osgDB::readNodeFile(filename);
//    if (model_node.valid()) model_node->setNodeMask(MAIN_CAMERA_MASK);
//
//    //Create a marker to replace the model itself in the radar map
//    osg::ref_ptr<osg::ShapeDrawable> mark_shape = new osg::ShapeDrawable;
//    mark_shape->setShape(new osg::Box(osg::Vec3(), size));
//    osg::ref_ptr<osg::Geode> mark_node = new osg::Geode;
//    mark_node->addDrawable(mark_shape);
//    mark_node->setNodeMask(RADAR_CAMERA_MASK);
//
//    osg::ref_ptr<osg::Group> obj_node = new osg::Group;
//    obj_node->addChild(model_node);
//    obj_node->addChild(mark_node);
//
//    osg::ref_ptr<osg::Material> material = new osg::Material;
//    material->setColorMode(osg::Material::AMBIENT);
//    material->setAmbient(osg::Material::FRONT_AND_BACK, osg::Vec4(0.8, 0.8, 0.8, 1));
//    material->setDiffuse(osg::Material::FRONT_AND_BACK, color * 0.8);
//    material->setSpecular(osg::Material::FRONT_AND_BACK, color);
//    material->setShininess(osg::Material::FRONT_AND_BACK, 1.0f);
//
//    obj_node->getOrCreateStateSet()->setAttributeAndModes(material, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
//    return obj_node.release();
//}
//
//osg::MatrixTransform* createStaticNode(const osg::Vec3& position, osg::Node* model)
//{
//    osg::ref_ptr<osg::MatrixTransform> staticNode = new osg::MatrixTransform;
//    staticNode->addChild(model);
//    staticNode->setMatrix(osg::Matrix::translate(position));
//    return staticNode.release();
//}
//
//osg::MatrixTransform* createAnimateNode(const osg::Vec3& position, float radius, float time, osg::Node* model)
//{
//    osg::ref_ptr<osg::MatrixTransform> animateNode = new osg::MatrixTransform;
//    animateNode->addUpdateCallback(createAnimationPathCallback(radius, time));
//    animateNode->addChild(model);
//    
//    osg::ref_ptr<osg::MatrixTransform> trans_node = new
//        osg::MatrixTransform;
//    trans_node->setMatrix(osg::Matrix::translate(position));
//    trans_node->addChild(animateNode.get());
//    return trans_node.release();
//}
//
//osg::Node* createModel(const std::string modelName, const osg::Vec4& color)
//{
//    osg::ref_ptr<osg::Node> _modelNode = osgDB::readNodeFile(modelName);
//    _modelNode->setNodeMask(MAIN_CAMERA_MASK);
//
//    osg::ref_ptr<osg::Geode> _markNode = new osg::Geode;
//    _markNode->addDrawable(new osg::ShapeDrawable(new osg::Box(osg::Vec3(), 10)));
//    _markNode->setNodeMask(RADAR_CAMERA_MASK);
//
//    osg::ref_ptr<osg::Material> material = new osg::Material;
//    material->setColorMode(osg::Material::AMBIENT);
//    material->setAmbient(osg::Material::FRONT_AND_BACK, osg::Vec4(0.8f, 0.8f, 0.8f, 1.0f));
//    material->setDiffuse(osg::Material::FRONT_AND_BACK, color * 0.8);
//    material->setSpecular(osg::Material::FRONT_AND_BACK, color);
//    material->setShininess(osg::Material::FRONT_AND_BACK, 1);
//    
//    _markNode->getOrCreateStateSet()->setAttributeAndModes(material, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
//
//    osg::ref_ptr<osg::Group> _groupNode = new osg::Group;
//    _groupNode->addChild(_modelNode);
//    _groupNode->addChild(_markNode);
//    
//    return _groupNode.release();
//}
//
//class BoundingBoxCallback : public osg::NodeCallback
//{
//public:
//    osg::NodePath _nodesToCompute;
//    virtual void operator()(osg::Node* node, osg::NodeVisitor& nv)
//    {
//        osg::BoundingBox bb;
//        std::cout << _nodesToCompute.size() << std::endl;
//        for (unsigned int i = 0; i < _nodesToCompute.size(); i++)
//        {
//            osg::Node* node = _nodesToCompute[i];
//            osg::ComputeBoundsVisitor cbbv;
//            node->accept(cbbv);
//
//            osg::BoundingBox localBB = cbbv.getBoundingBox();
//            osg::Matrix localToWorld = osg::computeLocalToWorld(node->getParent(0)->getParentalNodePaths()[0]);
//            for (unsigned int i = 0; i < 8; ++i)
//            {
//                bb.expandBy(localBB.corner(i) * localToWorld);
//            }
//        }
//        osg::MatrixTransform* trans = static_cast<osg::MatrixTransform*>(node);
//        trans->setMatrix(
//            osg::Matrix::scale(bb.xMax() - bb.xMin(), bb.yMax() - bb.yMin(),
//                bb.zMax() - bb.zMin()) *
//            osg::Matrix::translate(bb.center()));
//    }
//};
//
//osg::AnimationPath* createAnimationPath(float radius, float time)
//{
//    osg::ref_ptr<osg::AnimationPath> path = new osg::AnimationPath;
//    path->setLoopMode(osg::AnimationPath::LOOP);
//    unsigned int numSample = 32; //This is refer to how many control point will be created
//    float delta_yaw = 2 * osg::PI / ((float)numSample - 1);
//    float delta_time = time / (float)numSample;
//    for (int i = 0; i < numSample; i++)
//    {
//        float yaw = delta_yaw * (float)i;
//        osg::Vec3 pos(sinf(yaw) * radius, cosf(yaw) * radius, 0.0f);
//        osg::Quat rot(-yaw, osg::Z_AXIS);
//        path->insert(delta_time * (float)i, osg::AnimationPath::ControlPoint(pos, rot));
//    }
//    return path.release();
//}
//
//class FollowUpdater : public osgGA::GUIEventHandler
//{
//protected:
//    osg::observer_ptr<osg::Node> _target;
//public:
//    FollowUpdater(osg::Node* node) : _target(node) {}
//    virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
//    {
//        osgViewer::View* view = dynamic_cast<osgViewer::View*>(&aa);
//        if (!view || !_target || ea.getEventType() != osgGA::GUIEventAdapter::FRAME)
//            return false;
//        osgGA::OrbitManipulator* orbit = dynamic_cast<osgGA::OrbitManipulator*>(view->getCameraManipulator());
//        if (orbit)
//        {
//            osg::Matrix matrix;
//            if (_target->getNumParents() > 0)
//            {
//                osg::Group* parent = _target->getParent(0);
//                matrix = osg::computeLocalToWorld(parent->getParentalNodePaths()[0]);
//            }
//            osg::Vec3 targetCenter = _target->getBound().center() * matrix;
//            orbit->setCenter(targetCenter);
//        }
//        return false;
//    }
//};
//
//osg::AnimationPathCallback* FlyingCallback(float radius, float time)
//{
//    osg::ref_ptr<osg::AnimationPath> path = new osg::AnimationPath;
//    path->setLoopMode(osg::AnimationPath::LOOP);
//    unsigned int numSamples = 32;
//    float delta_yaw = 2.0f * osg::PI / ((float)numSamples - 1.0f);
//    float delta_time = time / (float)numSamples;
//    for (unsigned int i = 0; i < numSamples; ++i)
//    {
//        float yaw = delta_yaw * (float)i;
//        osg::Vec3 pos(sinf(yaw) * radius, cosf(yaw) * radius, 0.0f);
//        osg::Quat rot(-yaw, osg::Z_AXIS);
//        path->insert(delta_time * (float)i, osg::AnimationPath::ControlPoint(pos, rot));
//    }
//    osg::ref_ptr<osg::AnimationPathCallback> apcb = new osg::AnimationPathCallback;
//    apcb->setAnimationPath(path);
//    return apcb.release();
//}
//
//osg::AnimationPathCallback* mdvPathCallback(float radius, float time)
//{
//    osg::ref_ptr<osg::AnimationPath> path = new osg::AnimationPath;
//    path->setLoopMode(osg::AnimationPath::LOOP);
//    unsigned int numLoopControl = 32;
//    float delta_yaw = 2.0f * osg::PI / ((float)numLoopControl - 1.0f);
//    float delta_time = time / (float)numLoopControl;
//    for (unsigned int i = 0; i < numLoopControl; ++i)
//    {
//        float yaw = delta_yaw * (float)i;
//        osg::Vec3 pos(sinf(yaw) * radius, cosf(yaw) * radius, 0.0f);
//        osg::Quat rot(-yaw, osg::Z_AXIS);
//        path->insert(delta_time * (float)i, osg::AnimationPath::ControlPoint(pos, rot));
//    }
//    osg::ref_ptr<osg::AnimationPathCallback> pathCallback = new osg::AnimationPathCallback;
//    pathCallback->setAnimationPath(path);
//    return pathCallback.release();
//
//}
//
//class MDVFollowUpdate : public osgGA::GUIEventHandler
//{
//protected:
//    osg::Node* _target;
//public:
//    MDVFollowUpdate(osg::Node* node) : _target(node) {}
//    virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
//    {
//        osgViewer::View* view = dynamic_cast<osgViewer::View*>(&aa);
//        if (!view || !_target || ea.getEventType() != osgGA::GUIEventAdapter::FRAME)
//            return false;
//
//    }
//};
//
//osg::Node* createWall()
//{
//    osg::ref_ptr<osg::ShapeDrawable> wallLeft = new osg::ShapeDrawable();
//    wallLeft->setShape(new osg::Box(osg::Vec3(-5.5, 0, 0), 10, 0.3, 10));
//    osg::ref_ptr<osg::ShapeDrawable> wallRight = new osg::ShapeDrawable(new osg::Box(osg::Vec3(5.5, 0, 0), 10, 0.3, 10));
//    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
//    geode->addDrawable(wallLeft);
//    geode->addDrawable(wallRight);
//    return geode.release();
//}
//
//osg::MatrixTransform* createDoor()
//{
//    osg::ref_ptr<osg::ShapeDrawable> door = new osg::ShapeDrawable();
//    door->setShape(new osg::Box(osg::Vec3(2.5, 0, 0), 6, 0.2, 10));
//    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
//    geode->addDrawable(door);
//    osg::ref_ptr<osg::MatrixTransform> trans = new osg::MatrixTransform;
//    trans->addChild(geode);
//    return trans.release();
//}
//
//void generateDoorkeyFrames(osgAnimation::FloatLinearChannel* channel, bool closed)
//{
//    osg::ref_ptr<osgAnimation::FloatKeyframeContainer> container = channel->getOrCreateSampler()->getOrCreateKeyframeContainer();
//    if (closed)
//    {
//        container->push_back(osgAnimation::FloatKeyframe(0, 0));
//        container->push_back(osgAnimation::FloatKeyframe(1, osg::PI_2));
//    }
//    else
//    {
//        container->push_back(osgAnimation::FloatKeyframe(0, osg::PI_2));
//        container->push_back(osgAnimation::FloatKeyframe(1, 0));
//    }
//}
//
//class OpenDoorHandler : public osgGA::GUIEventHandler
//{
//public:
//    osg::observer_ptr<osgAnimation::BasicAnimationManager> _manager;
//    osg::observer_ptr<osgAnimation::Animation> _animation;
//    osg::observer_ptr<osg::MatrixTransform> _door;
//    bool _closed;
//
//    OpenDoorHandler() : _closed(true) {}
//    virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
//    {
//        if (ea.getEventType() != osgGA::GUIEventAdapter::RELEASE || ea.getButton() != osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON
//            || !(ea.getModKeyMask() & osgGA::GUIEventAdapter::MODKEY_CTRL))
//            return false;
//        osgViewer::View* view = dynamic_cast<osgViewer::View*>(&aa);
//        if (view)
//        {
//            osg::ref_ptr<osgUtil::LineSegmentIntersector> intersector = new osgUtil::LineSegmentIntersector
//            (osgUtil::Intersector::WINDOW, ea.getX(), ea.getY());
//            osgUtil::IntersectionVisitor iv(intersector);
//            view->getCamera()->accept(iv);
//            if (intersector->containsIntersections())
//            {
//                osgUtil::LineSegmentIntersector::Intersection result = *(intersector->getIntersections().begin());
//                osg::NodePath::iterator iter = std::find(result.nodePath.begin(), result.nodePath.end(), _door.get());
//                if (iter != result.nodePath.end())
//                {
//                    if (_manager->isPlaying(_animation.get()))
//                        return false;
//
//                    osgAnimation::FloatLinearChannel* ch = dynamic_cast<osgAnimation::FloatLinearChannel*>(_animation->getChannels().front().get());
//                    if (ch)
//                    {
//                        generateDoorkeyFrames(ch, _closed);
//                        _closed = !_closed;
//                    }
//                    _manager->playAnimation(_animation.get());
//                }
//            }
//        }
//    }
//};
//
//class Player : public osg::MatrixTransform
//{
//public:
//    enum PlayerType
//    {
//        INVALID_OBJ = 0, PLAYER_OBJ, ENEMY_OBJ,
//        PLAYER_BULLET_OBJ, ENEMY_BULLET_OBJ
//    };
//    Player() : _objType(INVALID_OBJ) {}
//    Player(float width, float height, const std::string& textfile)
//    {
//        _size.set(width, height);
//        osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
//        texture->setImage(osgDB::readImageFile(textfile));
//
//        osg::ref_ptr<osg::Drawable> quad = osg::createTexturedQuadGeometry(osg::Vec3(-width * 0.5, -height * 0.5, 0),
//            osg::Vec3(width, 0, 0), osg::Vec3(0, height, 0));
//        quad->getOrCreateStateSet()->setTextureAttributeAndModes(0, texture);
//        quad->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
//
//        osg::ref_ptr<osg::Geode> geode = new osg::Geode;
//        geode->addDrawable(quad);
//        addChild(geode);
//    }
//
//    float width() const
//    {
//        return _size[0];
//    }
//    float height() const
//    {
//        return _size[1];
//    }
//
//    void setSpeedVector(const osg::Vec3& speed)
//    {
//        _speedVec = speed;
//    }
//    osg::Vec3 getSpeedVector()
//    {
//        return _speedVec;
//    }
//
//    void setPlayerType(PlayerType T)
//    {
//        _objType = T;
//    }
//    PlayerType getPlayerType()
//    {
//        return _objType;
//    }
//    
//    bool isBullet()
//    {
//        return _objType == PLAYER_OBJ || _objType == ENEMY_BULLET_OBJ;
//    }
//
//    bool update(const osgGA::GUIEventAdapter& ea, osg::Group* root)
//    {
//        bool emitBullet = false;
//        switch (_objType)
//        {
//        case PLAYER_OBJ:
//            if (ea.getEventType() == osgGA::GUIEventAdapter::KEYDOWN)
//            {
//                switch (ea.getKey())
//                {
//                case osgGA::GUIEventAdapter::KEY_Left:
//                    _speedVec = osg::Vec3(-0.1, 0, 0);
//                    break;
//                case osgGA::GUIEventAdapter::KEY_Right:
//                    _speedVec = osg::Vec3(0.1, 0, 0);
//                    break;
//                case osgGA::GUIEventAdapter::KEY_Return:
//                    emitBullet = true;
//                    break;
//                default:
//                    break;
//                }
//            }
//            else if (ea.getEventType() == osgGA::GUIEventAdapter::KEYUP)
//                _speedVec = osg::Vec3();
//            break;
//        case ENEMY_OBJ:
//            if (RAND(0, 2000) < 1) emitBullet = true;
//            break;
//        default:
//            break;
//        }
//        osg::Vec3 pos = getMatrix().getTrans();
//        if (emitBullet)
//        {
//            //Create a bullet object
//            osg::ref_ptr<Player> bullet = new Player(0.4, 0.8, "Images/land_shallow_topo_2048.jpg");
//            if (_objType == PLAYER_OBJ)
//            {
//                bullet->setPlayerType(PLAYER_BULLET_OBJ);
//                bullet->setSpeedVector(osg::Vec3(0, 0.2, 0));
//                bullet->setMatrix(osg::Matrix::translate(pos + osg::Vec3(0, 0.9, 0)));
//            }
//            else
//            {
//                bullet->setPlayerType(ENEMY_BULLET_OBJ);
//                bullet->setSpeedVector(osg::Vec3(0, -0.2, 0));
//                bullet->setMatrix(osg::Matrix::translate(pos - osg::Vec3(0, 0.9, 0)));
//            }
//            root->addChild(bullet);
//        }
//        if (ea.getEventType() != osgGA::GUIEventAdapter::FRAME)
//            return false;
//        float halfW = width() / 2;
//        float halfH = height() / 2;
//        pos += _speedVec;
//        if (pos.x() < halfW || pos.x() > ea.getWindowWidth() - halfW)
//            return false;
//        if (pos.y() < halfH || pos.y() > ea.getWindowHeight() - halfH)
//            return false;
//        setMatrix(osg::Matrix::translate(pos));
//        return true;
//    }
//protected:
//    osg::Vec2 _size;
//    osg::Vec3 _speedVec;
//    PlayerType _objType;
//};
//
//class GameControllor : public osgGA::GUIEventHandler
//{
//protected:
//    osg::observer_ptr<osg::Group> _root;
//    float _distance;
//    float _direction;
//public:
//    GameControllor(osg::Group* root) : _root(root), _distance(0), _direction(0.1) {}
//    virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
//    {
//        _distance += fabs(_direction);
//        if (_distance > 30)
//        {
//            _direction = -_direction;
//            _distance = 0;
//        }
//
//        osg::NodePath tobeRemoved;
//        for (unsigned i = 0; i < _root->getNumChildren(); i++)
//        {
//            Player* player = static_cast<Player*>(_root->getChild(i));
//            if (!player) continue;
//
//            if (!player->update(ea, _root.get()))
//            {
//                if (player->isBullet())
//                    tobeRemoved.push_back(player);
//            }
//
//            if (player->getPlayerType() == Player::ENEMY_OBJ)
//            {
//                player->setSpeedVector(osg::Vec3(_direction, 0, 0));
//            }
//            if (!player->isBullet()) continue;
//
//            //Check for intersection
//
//        }
//        for (unsigned i = 0; i < tobeRemoved.size(); i++)
//        {
//            _root->removeChild(tobeRemoved[i]);
//        }
//        return false;
//    }
//};
//
//osg::Matrixd md;
//osg::Matrixd originalmd;
//osg::Quat qua;
//float angle = 0;
//
//osgViewer::Viewer viewer;
//osg::Vec3f eye = osg::Vec3f(0.0, -200.0, 0.0);
//osg::Vec3f centre = osg::Vec3f(0.0, 0.0, 0.0);
//osg::Vec3f up = osg::Vec3f(0.0, 0.0, 1.0);
//
//osg::Vec3f originaleye = osg::Vec3f(0.0, -200.0, 0.0);
//osg::Vec3f originalcentre = osg::Vec3f(0.0, 0.0, 0.0);
//osg::Vec3f originalup = osg::Vec3f(0.0, 0.0, 1.0);
//
//int ConstantVariation = 5;
//
//
//class PickHandlerTemp : public osgGA::GUIEventHandler {
//public:
//
//    PickHandlerTemp() {}
//
//    ~PickHandlerTemp() {}
//
//    bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
//
//
//protected:
//
//};
//
//bool PickHandlerTemp::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
//{
//    switch (ea.getEventType())
//    {
//    case(osgGA::GUIEventAdapter::PUSH):
//    {
//        osgViewer::View* view = dynamic_cast<osgViewer::View*>(&aa);
//        //if (view) pick(view,ea);
//        return false;
//    }
//    case(osgGA::GUIEventAdapter::KEYDOWN):
//    {
//        if (ea.getKey() == 'c')
//        {
//            osgViewer::View* view = dynamic_cast<osgViewer::View*>(&aa);
//            osg::ref_ptr<osgGA::GUIEventAdapter> event = new osgGA::GUIEventAdapter(ea);
//            event->setX((ea.getXmin() + ea.getXmax()) * 0.5);
//            event->setY((ea.getYmin() + ea.getYmax()) * 0.5);
//            // if (view) pick(view,*event);
//        }
//        if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Up)
//        {
//            std::cout << "Forward" << std::endl;
//
//            md = viewer.getCamera()->getViewMatrix();
//            md.getLookAt(eye, centre, up);
//
//            osg::Vec3f actuallook = centre - eye;
//
//            actuallook = actuallook / (actuallook.length());
//
//
//            eye = eye + ((actuallook) * 10);
//            centre = centre + ((actuallook) * 10);
//
//            viewer.getCamera()->setViewMatrixAsLookAt(eye, centre, osg::Z_AXIS);
//        }
//        if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Down)
//        {
//            std::cout << "BackWard" << std::endl;
//
//
//            md = viewer.getCamera()->getViewMatrix();
//            md.getLookAt(eye, centre, up);
//
//            osg::Vec3f actuallook = centre - eye;
//
//            actuallook = actuallook / (actuallook.length());
//
//
//            eye = eye - ((actuallook) * 10);
//
//            viewer.getCamera()->setViewMatrixAsLookAt(eye, centre, osg::Vec3d(up.x(), up.y(), up.z()));
//
//        }
//        if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Left)
//        {
//
//            std::cout << "LEFT Side" << std::endl;
//
//            md = viewer.getCamera()->getViewMatrix();
//            osg::Vec3d trans = md.getTrans();
//            std::cout << "translation=" << trans.x() << "," << trans.y() << "," << trans.z() << std::endl;
//
//            md.getLookAt(eye, centre, up);
//
//            trans.x() = trans.x() + 10;
//
//            md.setTrans(trans);
//
//            viewer.getCamera()->setViewMatrix(md);
//        }
//
//        if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Right)
//        {
//
//            std::cout << "Right Side" << std::endl;
//
//            md = viewer.getCamera()->getViewMatrix();
//            osg::Vec3d trans = md.getTrans();
//            std::cout << "translation=" << trans.x() << "," << trans.y() << "," << trans.z() << std::endl;
//
//            trans.x() = trans.x() - 10;
//            md.setTrans(trans);
//
//            viewer.getCamera()->setViewMatrix(md);
//
//
//        }
//        if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Page_Up)
//        {
//            std::cout << "UP" << std::endl;
//
//            md = viewer.getCamera()->getViewMatrix();
//            osg::Vec3d trans = md.getTrans();
//            std::cout << "translation=" << trans.x() << "," << trans.y() << "," << trans.z() << std::endl;
//
//            trans.y() = trans.y() - 10;
//            md.setTrans(trans);
//
//            viewer.getCamera()->setViewMatrix(md);
//
//
//        }
//
//        if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Page_Down)
//        {
//            std::cout << "Down" << std::endl;
//
//            md = viewer.getCamera()->getViewMatrix();
//            osg::Vec3d trans = md.getTrans();
//            std::cout << "translation=" << trans.x() << "," << trans.y() << "," << trans.z() << std::endl;
//
//            trans.y() = trans.y() + 10;
//            md.setTrans(trans);
//
//            viewer.getCamera()->setViewMatrix(md);
//
//
//        }
//        if (ea.getKey() == osgGA::GUIEventAdapter::KEY_7)
//        {
//            std::cout << "Rotation" << std::endl;
//            md = viewer.getCamera()->getViewMatrix();
//
//
//            angle = (3.142 / 180) * 2;
//
//            md.getLookAt(eye, centre, up);
//            std::cout << "up=" << up.x() << up.y() << up.z() << std::endl;
//
//            osg::Vec3f actuallook = centre - eye;
//            actuallook = actuallook / (actuallook.length());
//
//            osg::Quat qa(-angle, osg::Vec3f(up.x(), up.y(), up.z()));
//
//            osg::Vec3f look = (qa * actuallook);
//            look = look / (look.length());
//            centre = eye + (look * actuallook.length());
//
//            viewer.getCamera()->setViewMatrixAsLookAt(eye, centre, osg::Vec3d(up.x(), up.y(), up.z()));
//            std::cout << "up=" << up.x() << up.y() << up.z() << std::endl;
//
//            std::cout << " End Rotation" << std::endl;
//        }
//
//        if (ea.getKey() == osgGA::GUIEventAdapter::KEY_8)
//        {
//            std::cout << "Rotation" << std::endl;
//            md = viewer.getCamera()->getViewMatrix();
//
//
//            angle = (3.142 / 180) * 2;
//
//            md.getLookAt(eye, centre, up);
//            std::cout << "up=" << up.x() << up.y() << up.z() << std::endl;
//
//            osg::Vec3f actuallook = centre - eye;
//            actuallook = actuallook / (actuallook.length());
//
//            osg::Quat qa(angle, osg::Vec3f(up.x(), up.y(), up.z()));
//
//            osg::Vec3f look = (qa * actuallook);
//            look = look / (look.length());
//            centre = eye + (look * actuallook.length());
//
//            viewer.getCamera()->setViewMatrixAsLookAt(eye, centre, osg::Vec3d(up.x(), up.y(), up.z()));
//            std::cout << "up=" << up.x() << up.y() << up.z() << std::endl;
//
//            std::cout << " End Rotation" << std::endl;
//        }
//
//
//        if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Space)
//        {
//            md = originalmd;
//            viewer.getCamera()->setViewMatrix(originalmd);
//
//        }
//        return false;
//    }
//    default:
//        return false;
//    }
//}
//
//typedef std::pair<int, int> CellIndex;
//typedef std::map<CellIndex, int> CellMap;
//CellMap g_mazeMap;
//
//class MazeManipulator : public osgGA::FirstPersonManipulator
//{
//public:
//    virtual bool handle(const osgGA::GUIEventAdapter& ea,
//        osgGA::GUIActionAdapter& aa)
//    {
//        osg::Matrix lastMatrix = getMatrix();
//        bool ok = osgGA::FirstPersonManipulator::handle(ea, aa);
//        if (ea.getEventType() == osgGA::GUIEventAdapter::FRAME ||
//            ea.getEventType() == osgGA::GUIEventAdapter::SCROLL)
//        {
//            osg::Matrix matrix = getMatrix();
//            osg::Vec3 pos = matrix.getTrans();
//            if (pos[2] != 0.5f) // Fix the player height
//            {
//                pos[2] = 0.5f;
//                matrix.setTrans(pos);
//                setByMatrix(matrix);
//            }
//
//            CellIndex index(int(pos[0] + 0.5f), int(pos[1] + 0.5f));
//            CellMap::iterator itr = g_mazeMap.find(index);
//            if (itr == g_mazeMap.end()) // Outside the maze
//                setByMatrix(lastMatrix);
//            else if (itr->second != 0) // Don't intersect with walls
//                setByMatrix(lastMatrix);
//        }
//        return ok;
//    }
//};
//
//osgViewer::View* createSonarView(int x, int y, int width, int height, const osg::Vec3& lookDir, const osg::Vec3& up, osg::GraphicsContext* gc, osg::Node* model, osg::Node* scene)
//{
//    osg::ref_ptr<osgViewer::View> view = new osgViewer::View;
//    view->getCamera()->setGraphicsContext(gc);
//    view->getCamera()->setViewport(x, y, width, height);
//    view->setSceneData(scene);
//
//    osg::Vec3 center = model->getBound().center();
//    double radius = model->getBound().radius();
//
//    view->getCamera()->setViewMatrixAsLookAt(center - lookDir * (radius * 3), center, up);
//    view->getCamera()->setProjectionMatrixAsPerspective(30, width / height, 1, 1000);
//    return view.release();
//}
//
//class RotateCB : public osg::NodeCallback
//{
//protected:
//    double _angle;
//public:
//    RotateCB() : _angle(0) {}
//
//    virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
//    {
//        osg::ref_ptr<osg::MatrixTransform> mtLeft = dynamic_cast<osg::MatrixTransform*>(node);
//        osg::Matrix mR, mT;
//        mR.makeRotate(_angle, osg::Vec3(0, 0, 1));
//        mT.makeTranslate(-6, 0, 0);
//        mtLeft->setMatrix(mR*mT);
//        _angle += 0.01;
//        traverse(node, nv);
//    }
//};
//
//osg::ref_ptr<osg::Node> createTempScene()
//{
//    osg::Node* cow = osgDB::readNodeFile("cow.osg");
//    // Data variance is STATIC because we won't modify it.
//    cow->setDataVariance(osg::Object::STATIC);
//    osg::ref_ptr<osg::MatrixTransform> mtLeft = new osg::MatrixTransform;
//    mtLeft->setName("Left Cow");
//    mtLeft->setDataVariance(osg::Object::DYNAMIC);
//    mtLeft->setUpdateCallback(new RotateCB());
//    mtLeft->setMatrix(osg::Matrix::translate(-6, 0, 0));
//    mtLeft->addChild(cow);
//
//    cow->setDataVariance(osg::Object::STATIC);
//    osg::ref_ptr<osg::MatrixTransform> mtRight = new osg::MatrixTransform;
//    mtRight->setName("right Cow");
//    mtRight->setDataVariance(osg::Object::STATIC);
//    mtRight->setMatrix(osg::Matrix::translate(6, 0, 0));
//    mtRight->addChild(cow);
//
//    osg::ref_ptr<osg::Group> group = new osg::Group;
//    group->addChild(mtLeft);
//    group->addChild(mtRight);
//    return group;
//}
//
//
////Great Trash delete later
//class TwoDimManipulator : public osgGA::StandardManipulator
//{
//public:
//    osg::Vec3 _center;
//    double _distance;
//    TwoDimManipulator() : _distance(1.0) {}
//    virtual ~TwoDimManipulator() {}
//    virtual osg::Matrixd getMatrix() const
//    {
//        osg::Matrixd matrix;
//        matrix.makeTranslate(0.0f, 0.0f, _distance);
//        matrix.postMultTranslate(_center);
//        return matrix;
//    }
//    virtual osg::Matrixd getInverseMatrix() const
//    {
//        osg::Matrixd matrix;
//        matrix.makeTranslate(0.0f, 0.0f, -_distance);
//        matrix.preMultTranslate(-_center);
//        return matrix;
//    }
//    virtual void setByMatrix(const osg::Matrixd& matrix)
//    {
//        setByInverseMatrix(osg::Matrixd::inverse(matrix));
//    }
//    virtual void setByInverseMatrix(const osg::Matrixd& matrix)
//    {
//        osg::Vec3d eye, center, up;
//        matrix.getLookAt(eye, center, up);
//
//        _center = center; _center.z() = 0.0f;
//        if (_node.valid())
//            _distance = abs((_node->getBound().center() - eye).z());
//        else
//            _distance = abs((eye - center).length());
//    }
//
//    virtual void setTransformation(const osg::Vec3d&, const osg::Quat&) {}
//    virtual void setTransformation(const osg::Vec3d&, const osg::Vec3d&, const osg::Vec3d&) {}
//    virtual void getTransformation(osg::Vec3d&, osg::Quat&) const {}
//    virtual void getTransformation(osg::Vec3d&, osg::Vec3d&, osg::Vec3d&) const {}
//
//    void home(double)
//    {
//        if (_node.valid())
//        {
//            _center = _node->getBound().center();
//            _center.z() = 0.0f;
//            _distance = 2.5 * _node->getBound().radius();
//        }
//        else
//        {
//            _center.set(osg::Vec3());
//            _distance = 1.0;
//        }
//    }
//    void home(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us)
//    {
//        home(ea.getTime());
//    }
//
//    bool performMovementLeftMouseButton(const double eventTimeDelta, const double dx, const double dy)
//    {
//        _center.x() -= 100.0f * dx;
//        //_center.y() -= 100.0f * dy;
//        return false;
//    }
//    bool performMovementRightMouseButton(const double eventTimeDelta, const double dx, const double dy)
//    {
//        _distance *= (1.0 + dy);
//        if (_distance < 1.0) _distance = 1.0;
//        return false;
//    }
//};
//
//const unsigned int MDV_MAIN_CAMERA_MASK = 0x1;
//const unsigned int MDV_SONAR_CAMERA_MASK = 0x2;
//
//osg::Node* createTestObject(std::string name)
//{
//    osg::ref_ptr<osg::Node> model = osgDB::readNodeFile(name);
//    model->setNodeMask(MDV_MAIN_CAMERA_MASK);
//    
//    osg::ref_ptr<osg::ShapeDrawable> radar_node = new osg::ShapeDrawable;
//    radar_node->setShape(new osg::Box());
//    radar_node->setNodeMask(MDV_SONAR_CAMERA_MASK);
//
//    osg::ref_ptr<osg::Group> model_entity = new osg::Group;
//    model_entity->addChild(model);
//    model_entity->addChild(radar_node);
//
//    return model_entity.release();
//}
//
//osg::Camera* createTestSlaveCamera(int x, int y, int width, int
//    height)
//{
//    osg::ref_ptr<osg::GraphicsContext::Traits> traits = new
//        osg::GraphicsContext::Traits;
//    traits->screenNum = 0; // this can be changed for
//    //multi-display
//    traits->x = x;
//    traits->y = y;
//    traits->width = width;
//    traits->height = height;
//    traits->windowDecoration = false;
//    traits->doubleBuffer = true;
//    traits->sharedContext = 0;
//
//    osg::ref_ptr<osg::GraphicsContext> gc = osg::GraphicsContext::createGraphicsContext(traits.get());
//    if (!gc) return NULL;
//
//    osg::ref_ptr<osg::Camera> camera = new osg::Camera;
//    camera->setGraphicsContext(gc.get());
//    camera->setViewport(new osg::Viewport(0, 0, width, height));
//
//    GLenum buffer = traits->doubleBuffer ? GL_BACK : GL_FRONT;
//    camera->setDrawBuffer(buffer);
//    camera->setReadBuffer(buffer);
//    return camera.release();
//}
//
//int mains(int argc, char** argv)
//{
//    //MDV Demo Work
//    Model model;
//    CameraHUD cameraHud;
//    TextureSeabed textureSeabed;
//    osg::ref_ptr<osg::MatrixTransform> model1 = model.createModel("cessna.osg", osg::Vec3(0, 0, 200), osg::Vec4(1.0, 0.0, 0.0, 0));
//    osg::ref_ptr<osg::MatrixTransform> model2 = model.createModel("dumptruck.osg", osg::Vec3(0, 100, 200), osg::Vec4(1.0, 0.0, 0.0, 0));
//
//    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
//    
//    osg::ref_ptr<osg::MatrixTransform> terrain = model.createModel("lz.osg", osg::Vec3(0, 0, 0), osg::Vec4(0.0, 0.0, 0.0, 0));
//    
//    osg::ref_ptr<osg::Group> root = new osg::Group;
//    root->addChild(terrain);
//    root->addChild(model1);
//    root->addChild(model2);
//
//    osg::ref_ptr<osg::Node> obj1 = model.createTempModel("dumptruck.osg", osg::Vec4(1.0f, 0.2f, 0.2f, 1.0f));
//    osg::ref_ptr<osg::Group> scene = new osg::Group;
//    for (int i = 0; i < 10; i++)
//    {
//        osg::Vec3 center(RAND(-100, 100), RAND(-100, 100), 0);
//        scene->addChild(model.createStaticNodes(center, obj1));
//    }
//
//    osg::ref_ptr<osgGA::KeySwitchMatrixManipulator> keySwitch = new osgGA::KeySwitchMatrixManipulator;
//    keySwitch->addMatrixManipulator('1', "Trackball", new  osgGA::TrackballManipulator);
//    keySwitch->addMatrixManipulator('2', "TwoDim", new TwoDimManipulator);
//    const osg::BoundingSphere& bs = root->getBound();
//    keySwitch->setHomePosition(bs.center() + osg::Vec3(0.0f, 0.0f, bs.radius()), bs.center(), osg::Y_AXIS);
//
//    //Normal view
//    osg::ref_ptr<osgViewer::View> view1 = new osgViewer::View;
//    view1->setUpViewInWindow(50, 50, 500, 500);
//    //view1->setSceneData(root.get());
//    view1->setSceneData(scene.get());
//    view1->setCameraManipulator(keySwitch);
//    view1->getCamera()->setCullMask(0x2);
//
//    //MDV View
//    osg::ref_ptr<osgViewer::View> view2 = new osgViewer::View;
//    //osg::ref_ptr <osg::Camera> _mainCamera = cameraHud.createCamera(view1->getCamera());
//    //view1->setUpViewInWindow(50, 50, 500, 500);
//    //view1->setSceneData(root.get());
//    //view1->setCameraManipulator(keySwitch);
//
//    //New MDV View with texture mapping
//    /*osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
//    texture->setImage(osgDB::readImageFile("Images/osg256.png"));
//    osg::ref_ptr<osg::Geometry> quad = osg::createTexturedQuadGeometry(osg::Vec3(), osg::Vec3(1.0f, 0.0f, 0.0f), osg::Vec3(0.0f, 1.0f, 0.0f));
//    osg::ref_ptr<osg::Geode> textureMap = new osg::Geode;
//    textureMap->addDrawable(quad.get());
//    textureMap->getOrCreateStateSet()->setTextureAttributeAndModes(0, texture.get());*/
//    osg::ref_ptr<osg::Geode> textureMap = dynamic_cast<osg::Geode*>(textureSeabed.createTextureMap());
//
//    osg::ref_ptr<osg::Camera> camera = cameraHud.createCamera(textureMap);
//    //osg::ref_ptr<osg::Camera> camera = new osg::Camera;
//    //camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
//    //camera->setRenderOrder(osg::Camera::POST_RENDER);
//    ////camera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    ////camera->setCullMask(0x1);
//    //camera->setClearMask(0);
//    //camera->setProjectionMatrixAsOrtho2D(0.0, 1.0, 0.0, 1.0);
//    //camera->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
//    //camera->getOrCreateStateSet()->setAttributeAndModes(new osg::Depth(osg::Depth::LEQUAL, 1.0, 1.0));
//
//    //camera->addChild(textureMap.get());
//
//    osg::ref_ptr<osg::Group> sonarScene = new osg::Group;
//    sonarScene->addChild(camera.get());
//    sonarScene->addChild(scene.get());
//    //sonarScene->addChild(root);
//    //sonarScene->addChild(model2);
//
//    view2->setUpViewInWindow(50, 50, 500, 500);
//    view2->setSceneData(sonarScene.get());
//    view2->getCamera()->setCullMask(0x1);
//    view2->setCameraManipulator(keySwitch);
//
//
//    osgViewer::CompositeViewer viewer;
//    viewer.addView(view1.get());
//    viewer.addView(view2.get());
//
//    while (!viewer.done())
//    {
//        viewer.frame();
//    }
//    return 0;
//
//
//    //osg::ref_ptr<osg::Node> obj1 = createTestObject("cessna.osg");
//    //osg::ref_ptr<osg::Node> obj2 = createTestObject("dumptruck.osg");
//
//    //osg::ref_ptr<osg::Group> scene = new osg::Group;
//    //scene->addChild(obj1);
//    //scene->addChild(obj2);
//    //scene->getBound().center();
//
//    //osg::ref_ptr<osg::Camera> camera = new osg::Camera;
//    //camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
//    //camera->setClearColor(osg::Vec4(0, 0, 0, 1));
//    //camera->setRenderOrder(osg::Camera::POST_RENDER);
//    //camera->setAllowEventFocus(false);
//    //camera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    //camera->setViewport(0, 0, 200, 200);
//    //float x = 0, y = 0, z = 120;
//    //osg::Vec3 eye(x,y,z);
//    //osg::Vec3 center = scene->getBound().center();;
//    //osg::Vec3 up = osg::Y_AXIS;
//    //double left = -120.0, right = 120.0, bottom = -120, top = 120.0;
//    //camera->setViewMatrixAsLookAt(eye, osg::Vec3(), up);
//    //camera->setProjectionMatrixAsOrtho2D(left, right, bottom, top);
//    ////camera->setCullMask(MDV_SONAR_CAMERA_MASK);
//    //camera->addChild(scene.get());
//
//    //osg::ref_ptr<osg::Group> root = new osg::Group;
//    //root->addChild(camera.get());
//    //root->addChild(scene.get());
//
//    //osg::ref_ptr<osgViewer::View> view = new osgViewer::View;
//    //view->setUpViewInWindow(50, 50, 500, 500);
//    //view->setSceneData(root);
//    ////view->setCamera(camera);
//    ////view->getCamera()->setCullMask(MDV_MAIN_CAMERA_MASK);
//
//    //osgViewer::CompositeViewer viewer;
//    //viewer.addView(view.get());
//    //return viewer.run();
//
//    //1
//    //AnimatingObject anim;
//    //osg::ref_ptr<osg::MatrixTransform> model = new osg::MatrixTransform();
//    //model->addChild(osgDB::readNodeFile("cessna.osg"));
//    ////model->setUpdateCallback(anim.createPath());
//
//    //osg::ref_ptr<osg::MatrixTransform> terrain = new osg::MatrixTransform;
//    //terrain->addChild(osgDB::readNodeFile("lz.osg"));
//    //terrain->setMatrix(osg::Matrix::translate(0.0f, 0.0f, -500.0f));
//
//    //osg::ref_ptr<osg::Group> root = new osg::Group;
//    //root->addChild(terrain);
//    //root->addChild(model);
//
//    //unsigned int width = 800, height = 600;
//    //osg::ref_ptr<osg::GraphicsContext::Traits> traits = new
//    //    osg::GraphicsContext::Traits;
//    //traits->x = 0;
//    //traits->y = 0;
//    //traits->width = width;
//    //traits->height = height;
//    //traits->windowDecoration = false;
//    //traits->doubleBuffer = true;
//    //traits->sharedContext = 0;
//    //osg::ref_ptr<osg::GraphicsContext> gc = osg::GraphicsContext::createGraphicsContext(traits);
//
//    //int w_2 = width / 2, h_2 = height / 2;
//    //osg::ref_ptr<osgViewer::View> top = createSonarView( 0, h_2, w_2, h_2, -osg::Z_AXIS, osg::Y_AXIS, gc.get(), model.get(), root.get());
//
//
//    //osg::ref_ptr<osgViewer::View> main = createSonarView(w_2, 0, w_2, h_2, osg::Z_AXIS, osg::Y_AXIS, gc.get(), model.get(), root.get());
//    ////osg::ref_ptr<osgViewer::View> mainView = new osgViewer::View;
//    ////mainView->getCamera()->setGraphicsContext(gc.get());
//    ////mainView->getCamera()->setViewport(w_2, 0, w_2, h_2);
//    ////mainView->setSceneData(model.get());
//    ////main->setCameraManipulator(new osgGA::DriveManipulator);
//
//    //    //Add Tracker to Model
//    //osg::ref_ptr<osgGA::NodeTrackerManipulator> tracker = new osgGA::NodeTrackerManipulator;
//    //tracker->setHomePosition(osg::Vec3(0, -10, 0), osg::Vec3(), osg::Z_AXIS);
//    //tracker->setAutoComputeHomePosition(false);
//    //tracker->setTrackerMode(osgGA::NodeTrackerManipulator::NODE_CENTER_AND_AZIM);
//    //tracker->setRotationMode(osgGA::NodeTrackerManipulator::TRACKBALL);
//    //tracker->setTrackNode(model);
//
//    //top->addEventHandler(tracker);
//
//    //osg::ref_ptr<osgViewer::View> view = new osgViewer::View;
//    //view->setUpViewInWindow(50, 50, 360, 240);
//    //view->setSceneData(root);
//
//    //osgViewer::CompositeViewer viewer;
//    ///*viewer.addView(view.get());*/
//    //viewer.addView(top.get());
//    //viewer.addView(main.get());
//    //while (!viewer.done())
//    //{
//    //    viewer.frame();
//    //}
//    ////return viewer.run();
//    
//    //2
//    //osg::ref_ptr<osg::MatrixTransform> model = new osg::MatrixTransform;
//    //model->addChild(osgDB::readNodeFile("cessna.osg"));
//    //osgViewer::View* view = new osgViewer::View;
//    //view->setUpViewInWindow(50, 50, 500, 500);
//    //view->setSceneData(model);
//
//    //view->addEventHandler(new osgGA::StateSetManipulator(view->getCamera()->getOrCreateStateSet()));
//    ////Add some operators
//    //osg::ref_ptr<osgGA::KeySwitchMatrixManipulator> keyswitchManipulator = new osgGA::KeySwitchMatrixManipulator;
//
//    //// The first parameter is the shortcut key, the second parameter is the identification, the parameter 30 initializes the response operator
//    //keyswitchManipulator->addMatrixManipulator('1', "Trackball", new osgGA::TrackballManipulator());
//    //keyswitchManipulator->addMatrixManipulator('2', "Flight", new osgGA::FlightManipulator());
//    //keyswitchManipulator->addMatrixManipulator('3', "Drive", new osgGA::DriveManipulator());
//    //keyswitchManipulator->addMatrixManipulator('4', "Terrain", new osgGA::TerrainManipulator());
//
//    //view->setCameraManipulator(keyswitchManipulator.get());
//    //view->addEventHandler(new osgViewer::RecordCameraPathHandler);
//
//    //osgViewer::CompositeViewer viewer;
//    //viewer.addView(view);
//    //
//    //return viewer.run();
//
//    //3
//    //Create plane
//    //AnimatingObject anim;
//    //Model model;
//    //osg::ref_ptr<osg::MatrixTransform> model1 = model.createModel("cessna.osg", osg::Vec3(20, 0, 0));
//    ////Create terrain
//    //osg::ref_ptr<osg::MatrixTransform> terrain = new osg::MatrixTransform;
//    //terrain->addChild(osgDB::readNodeFile("lz.osg"));
//    //terrain->setMatrix(osg::Matrix::translate(0.0f, 0.0f, -500.0f));
//
//    //osg::ref_ptr<osg::Group> root = new osg::Group;
//    //root->addChild(terrain);
//    //root->addChild(model1);
//
//    //osg::ref_ptr<CameraMover> moveHandler = new CameraMover(model1);
//    ////model1->setUpdateCallback(anim.createPath());
//    ////model1->addEventCallback(moveHandler);
//
//    ////Add Tracker to Model
//    //osg::ref_ptr<osgGA::NodeTrackerManipulator> tracker = new osgGA::NodeTrackerManipulator;
//    //tracker->setHomePosition(osg::Vec3(0, -10, 0), osg::Vec3(), osg::Z_AXIS);
//    //tracker->setAutoComputeHomePosition(false);
//    //tracker->setTrackerMode(osgGA::NodeTrackerManipulator::NODE_CENTER_AND_AZIM);
//    //tracker->setRotationMode(osgGA::NodeTrackerManipulator::TRACKBALL);
//    //tracker->setTrackNode(model1);
//
//    ////eye: The position of your camera - this you can use to set its height.
//    ////center : The point your camera is looking at - set this to the center of the observed object.
//    ////up : The up - vector of your camera - 
//    //    //this controls how your viewport will be rotated about its center and should be equal to[0, 1, 0] in a conventional graphics coordinate system.
//    //osg::Vec3f eye = osg::Vec3f(1.0, -200.0, 20.0);
//    //osg::Vec3f centre = osg::Vec3f(0.0, 0.0, 0.0);
//    //osg::Vec3f up = osg::Vec3f(0.0, 0.0, 1.0);
//
//    //osg::ref_ptr<osgGA::DriveManipulator> driveManipulator = new osgGA::DriveManipulator();
//    //driveManipulator->setHomePosition(osg::Vec3(1, 0, 200), centre, up);
//    ////driveManipulator->setAutoComputeHomePosition(false);
//
//    //osg::ref_ptr<MazeManipulator> manipulator = new MazeManipulator;
//    //manipulator->setHomePosition(osg::Vec3(6.0f, 0.0f, 0.5f),
//    //    osg::Vec3(6.0f, 1.0f, 0.5f), osg::Z_AXIS);
//
//    //CameraHUD cameraHud;
//    //osg::ref_ptr<osg::Camera> camera = cameraHud.createCamera(model1);
//    ////camera->addChild(model1);
//
//    //osgViewer::View* planeView = new osgViewer::View;
//    //planeView->setUpViewInWindow(50, 50, 500, 500);
//    //planeView->setSceneData(root);
//    //planeView->getCamera()->setCullMask(0x2);
//    //planeView->addEventHandler(moveHandler);
//    //planeView->setCameraManipulator(driveManipulator);
//    ////planeView->addEventHandler(new osgViewer::StatsHandler);
//    ////planeView->addEventHandler(new FollowUpdater(model1));
//
//    //osgViewer::View* cameraView = new osgViewer::View;
//    //cameraView->setUpViewInWindow(50, 50, 360, 240);
//    //cameraView->setSceneData(camera);
//    //cameraView->getCamera()->setCullMask(0x2);
//    ////cameraView->setCameraManipulator(tracker);
//    ////cameraView->addEventHandler(new FollowUpdater(model1));
//
//    ////view->setCamera(camera);
//    //osgViewer::CompositeViewer viewer;
//    //viewer.addView(planeView);
//    //viewer.addView(cameraView);
//
//    //while (!viewer.done())
//    //{
//    //    viewer.frame();
//    //}
//    //return 0;
//
//}
//
//
//////DXC Sonar Camera Test
////osg::ref_ptr<osg::Node> cessna = osgDB::readNodeFile("cessna.osg");
////osg::ref_ptr<osg::MatrixTransform> mdvTrans = new osg::MatrixTransform;
////mdvTrans->addChild(cessna);
////mdvTrans->setUpdateCallback(mdvPathCallback(50, 6));
////osg::ref_ptr<osg::MatrixTransform> terrain = new osg::MatrixTransform;
////terrain->addChild(osgDB::readNodeFile("lz.osg"));
////terrain->setMatrix(osg::Matrix::translate(0, 0, -200));
////osg::ref_ptr<osg::MatrixTransform> root = new osg::MatrixTransform;
////root->addChild(mdvTrans);
////root->addChild(terrain);
////osg::ref_ptr<osgGA::NodeTrackerManipulator> nodeTracker = new osgGA::NodeTrackerManipulator;
////nodeTracker->setHomePosition(osg::Vec3(0, -10, 0), osg::Vec3(), osg::Z_AXIS);
////nodeTracker->setTrackerMode(osgGA::NodeTrackerManipulator::NODE_CENTER_AND_ROTATION);
////nodeTracker->setRotationMode(osgGA::NodeTrackerManipulator::TRACKBALL);
////nodeTracker->setTrackNode(cessna);
////osg::ref_ptr<osgGA::KeySwitchMatrixManipulator> keySwitch = new
////    osgGA::KeySwitchMatrixManipulator;
////keySwitch->addMatrixManipulator('1', "Trackball", new
////    osgGA::TrackballManipulator);
////keySwitch->addMatrixManipulator('2', "NodeTracker",
////    nodeTracker.get());
////osgViewer::View* view = new osgViewer::View;
////view->setUpViewInWindow(50, 50, 360, 240);
////view->setSceneData(root);
////view->setCameraManipulator(keySwitch);
////osgViewer::CompositeViewer viewer;
////viewer.addView(view);
////return viewer.run(); 
//
//////Camera Follow Object Test
////osg::ref_ptr<osg::Node> model = osgDB::readNodeFile("cessna.osg.0,0,90.rot");
////osg::ref_ptr<osg::MatrixTransform> trans = new osg::MatrixTransform;
////trans->setUpdateCallback(FlyingCallback(100.0f, 20.0));
////trans->addChild(model);
////osg::ref_ptr<osg::MatrixTransform> terrain = new osg::MatrixTransform;
////terrain->addChild(osgDB::readNodeFile("lz.osg"));
////terrain->setMatrix(osg::Matrix::translate(0, 0, -200));
////osg::ref_ptr<osg::Group> root = new osg::Group;
////root->addChild(trans.get());
////root->addChild(terrain.get());
////osgViewer::View* view = new osgViewer::View;
////view->setUpViewInWindow(50, 50, 360, 240);
////view->setSceneData(root);
////view->addEventHandler(new FollowUpdater(model));
////osgViewer::CompositeViewer viewer;
////viewer.addView(view);
////return viewer.run(); 
//
//////Bounding Box Test
////osg::ref_ptr<osg::MatrixTransform> cessna = new osg::MatrixTransform;
////cessna->addChild(osgDB::readNodeFile("cessna.osg"));
////osg::ref_ptr<osg::AnimationPathCallback> animationCallBack = new osg::AnimationPathCallback;
////animationCallBack->setAnimationPath(createAnimationPath(50, 6));
////cessna->setUpdateCallback(animationCallBack);
////osg::ref_ptr<osg::MatrixTransform> dumptruct = new osg::MatrixTransform;
////dumptruct->addChild(osgDB::readNodeFile("dumptruck.osgt"));
////dumptruct->setMatrix(osg::Matrix::translate(0, 0, -100));
////osg::ref_ptr<osg::MatrixTransform> models = new osg::MatrixTransform;
////models->addChild(cessna.get());
////models->addChild(dumptruct.get());
////models->setMatrix(osg::Matrix::translate(0.0f, 0.0f, 200.0f));
////osg::ref_ptr<BoundingBoxCallback> bbcb = new BoundingBoxCallback();
////bbcb->_nodesToCompute.push_back(cessna);
////bbcb->_nodesToCompute.push_back(dumptruct);
////osg::ref_ptr<osg::Geode> geode = new osg::Geode;
////geode->addDrawable(new osg::ShapeDrawable(new osg::Box));
////osg::ref_ptr<osg::MatrixTransform> boundingBoxNode = new osg::MatrixTransform;
////boundingBoxNode->addChild(geode);
////boundingBoxNode->setUpdateCallback(bbcb);
////boundingBoxNode->getOrCreateStateSet()->setAttributeAndModes(
////    new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE));
////boundingBoxNode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
////osg::ref_ptr<osg::Group> root = new osg::Group;
////root->addChild(boundingBoxNode.get());
////root->addChild(models.get());
////osgViewer::View* view = new osgViewer::View;
////view->setUpViewInWindow(50, 50, 360, 240);
////view->setSceneData(models);
////osgViewer::CompositeViewer viewer;
////viewer.addView(view);
////return viewer.run(); 
//
//////Create multiple camera angle
////osg::ref_ptr<osg::Node> scene = osgDB::readNodeFile("cessna.osg");
////unsigned int width = 800, height = 600;
////osg::ref_ptr<osg::GraphicsContext::Traits> trait = new osg::GraphicsContext::Traits;
////trait->x = 0;
////trait->y = 0;
////trait->width = width;
////trait->height = height;
//////trait->windowDecoration = false;
//////trait->doubleBuffer = true;
//////trait->sharedContext = 0;
////osg::ref_ptr<osg::GraphicsContext> gc = osg::GraphicsContext::createGraphicsContext(trait);
//////Create top view camera
////osg::ref_ptr<osg::Camera> cameraTop = new osg::Camera;
////cameraTop->setGraphicsContext(gc);
////cameraTop->setViewport(0, height / 2, width / 2, height / 2);
//////set up camera direction
////osg::Vec3 center = scene->getBound().center();
////double radius = scene->getBound().radius();
////osg::Vec3 up = osg::Y_AXIS;
////osg::Vec3 lookDir = -osg::Z_AXIS;
////cameraTop->setViewMatrixAsLookAt(center - lookDir * (radius*3), center, up);
////cameraTop->setProjectionMatrixAsPerspective(30, static_cast<double>(width) / static_cast<double>(height), 1, 10000);
//////Set up top view
////osg::ref_ptr<osgViewer::View> topView = new osgViewer::View;
////topView->setCamera(cameraTop);
////topView->setSceneData(scene);
//////Create front view camera
////osg::ref_ptr<osg::Camera> cameraFront = new osg::Camera;
////cameraFront->setGraphicsContext(gc);
////cameraFront->setViewport(width / 2, height / 2, width / 2, height / 2);
//////Set up camera Direction and  range
////osg::Vec3 center1 = scene->getBound().center();
////double radius1 = scene->getBound().radius();
////osg::Vec3 up1 = osg::Z_AXIS;
////osg::Vec3 lookDir1 = osg::Y_AXIS;
////cameraFront->setViewMatrixAsLookAt(center1 - lookDir1 * (radius1 * 3), center1, up1);
////cameraFront->setProjectionMatrixAsPerspective(30, static_cast<double>(width) / static_cast<double>(height), 1, 10000);
////osg::ref_ptr<osgViewer::View> frontView = new osgViewer::View;
////frontView->setCamera(cameraFront);
////frontView->setSceneData(scene);
////osgViewer::CompositeViewer viewer;
////viewer.addView(topView);
////viewer.addView(frontView);
////while (!viewer.done())
////{
////    viewer.frame();
////}
////return 0;
//
//////Sonar View Test
////osg::ref_ptr<osg::Group> model = dynamic_cast<osg::Group*>( createModel("cessna.osg", osg::Vec4(1.0f, 0.2f, 0.2f, 1.0f)));
////osg::ref_ptr<osg::Camera> sonar = new osg::Camera;
////sonar->setClearColor(osg::Vec4(0, 0.2, 0, 1));
//////sonar->setRenderOrder(osg::Camera::POST_RENDER);
//////sonar->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
////sonar->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
////sonar->setViewport(new osg::Viewport(0, 0, 200, 200));
////sonar->setViewMatrix(osg::Matrixd::lookAt(osg::Vec3(0, 0, 120), osg::Vec3(), osg::Y_AXIS));
////sonar->setProjectionMatrix(osg::Matrixd::ortho2D(-120.0,120.0, -120.0, 120.0));
////sonar->setCullMask(RADAR_CAMERA_MASK);
////sonar->addChild(model);
////osg::ref_ptr<osg::Group> scene = new osg::Group;
////scene->addChild(model);
////scene->addChild(sonar);
////osgViewer::View* view = new osgViewer::View;
////view->setUpViewInWindow(50, 50, 360, 240);
////view->getCamera()->setCullMask(MAIN_CAMERA_MASK);
////view->setSceneData(scene);
////osgViewer::CompositeViewer viewer;
////viewer.addView(view);
////return viewer.run();  
//
//////Slave Camera Test
////double zNear = 1.0, zMid = 1e4, zFar = 2e8;
////osg::ref_ptr<osgViewer::DepthPartitionSettings> dps = new osgViewer::DepthPartitionSettings;
////dps->_mode = osgViewer::DepthPartitionSettings::FIXED_RANGE;
////dps->_zNear = zNear;
////dps->_zMid = zMid;
////dps->_zFar = zFar;
////osgViewer::Viewer viewer;
////viewer.getCamera()->setClearColor(osg::Vec4(0.0f, 0.0f, 0.0f,
////    1.0f));
////viewer.setSceneData(createScene());
//////viewer.setUpDepthPartition(dps.get());
////viewer.setCameraManipulator(new osgGA::TrackballManipulator);
////viewer.getCameraManipulator()->setHomePosition(
////    osg::Vec3d(0.0, -12.5 * radius_earth, 0.0), osg::Vec3d(),
////    osg::Vec3d(0.0, 0.0, 1.0));
////return viewer.run();
//
//////Slave Camera Test
////osg::ref_ptr<osg::Node> scene = osgDB::readNodeFile("cessna.osg");
////osgViewer::Viewer viewer;
////int totalWidth = 1024, totalHeight = 768;
////int numColumns = 3, numRows = 3;
////int tileWidth = totalWidth / numColumns;
////int tileHeight = totalHeight / numRows;
////for (int row = 0; row < numRows; row++)
////{
////    for (int col = 0; col < numColumns; col++)
////    {
////        osg::Camera* camera = createSlaveCamera(tileWidth * col, totalHeight - tileHeight * (row + 1), tileWidth - 1, tileHeight - 1);
////        osg::Matrix projOffset = 
////            osg::Matrix::scale(numColumns, numRows, 1.0) * osg::Matrix::translate(numColumns - 1 - 2 * col,numRows - 1 - 2 * row, 0.0);
////        viewer.addSlave(camera, projOffset, osg::Matrix(), true);
////    }
////}
////viewer.setSceneData(scene);
////return viewer.run();
//
//////Change Colour Cube
////osg::ref_ptr<osg::Geode> geode = new osg::Geode;
////geode->addDrawable(createSimpleGeometry());
////geode->addDrawable(createSimpleGeometry());
////geode->getOrCreateStateSet()->setMode(
////    GL_BLEND, osg::StateAttribute::ON);
////geode->getOrCreateStateSet()->setRenderingHint(
////    osg::StateSet::TRANSPARENT_BIN);
////osg::ref_ptr<osg::Group> root = new osg::Group;
////root->addChild(geode.get());
////osgViewer::View* view = new osgViewer::View;
////view->setUpViewInWindow(50, 50, 360, 240);
////view->setSceneData(root);
////view->addEventHandler(new ChangeColourHandle());
////osgViewer::CompositeViewer viewer;
////viewer.addView(view);
////return viewer.run();  
//
//////Clock Test
////float hour_time = 10.0f, min_time = 30.0f, sec_time = 0.0f;
////osg::ref_ptr<osg::MatrixTransform> hour = dynamic_cast<osg::MatrixTransform*>(
////    createNeedle(6.0f, 1.0f, -0.02f, osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f), osg::PI * hour_time / 6.0f, 3600 * 60.0));
////osg::Node* minute = createNeedle(8.0f, 0.6f, -0.04f,
////    osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f), osg::PI * min_time /
////    30.0f, 3600.0);
////osg::Node* second = createNeedle(10.0f, 0.2f, -0.06f,
////    osg::Vec4(1.0f, 1.0f, 0.0f, 1.0f), osg::PI * sec_time /
////    30.0f, 60.0);
////osg::ref_ptr<osg::Group> root = new osg::Group;
////root->addChild(hour);
////root->addChild(minute);
////root->addChild(second);
//// osgViewer::View* view = new osgViewer::View;
//// view->setUpViewInWindow(50, 50, 360, 240);
//// view->setSceneData(root);
//// osgViewer::CompositeViewer viewer;
//// viewer.addView(view);
//// return viewer.run();
//
//// //Tesellator Test
//// osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array(8);
//// (*vertices)[0].set(0.0f, 0.0f, 0.0f);
//// (*vertices)[1].set(3, 0, 0);
//// (*vertices)[2].set(3, 0, 3);
//// (*vertices)[3].set(0, 0, 3);
//// (*vertices)[4].set(1, 0, 1);
//// (*vertices)[5].set(1, 0, 2);
//// (*vertices)[6].set(2, 0, 2);
//// (*vertices)[7].set(2, 0, 1);
//// osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array(1);
//// (*normals)[0].set(0, -1, 0);
//// osg::ref_ptr<osg::Vec4Array> colours = new osg::Vec4Array(1);
//// (*colours)[0].set(1.0f, 1.0f, 0.0f, 1.0f);
//// osg::ref_ptr<osg::Geometry> polygon = new osg::Geometry;
//// polygon->setVertexArray(vertices);
//// polygon->setNormalArray(normals);
//// polygon->setNormalBinding(osg::Geometry::BIND_OVERALL);
//// polygon->addPrimitiveSet(new osg::DrawArrays(GL_QUADS, 0, 4));
//// polygon->addPrimitiveSet(new osg::DrawArrays(GL_QUADS, 4, 4));
//// osg::ref_ptr<osgUtil::Tessellator> tessellator = new osgUtil::Tessellator;
//// tessellator->setTessellationType(osgUtil::Tessellator::TESS_TYPE_GEOMETRY);
////// tessellator->setWindingType(osgUtil::Tessellator::TESS_WINDING_ODD);
//// tessellator->retessellatePolygons(*polygon);
//// osg::ref_ptr<osg::Geometry> border = new osg::Geometry;
//// border->setVertexArray(vertices);
//// border->setColorArray(colours);
//// border->setColorBinding(osg::Geometry::BIND_OVERALL);
//// border->addPrimitiveSet(new osg::DrawArrays(GL_LINE_LOOP, 0, 4));
//// border->addPrimitiveSet(new osg::DrawArrays(GL_LINE_LOOP, 4, 4));
//// border->getOrCreateStateSet()->setAttribute(new osg::LineWidth(5));
//// osg::ref_ptr<osg::Geode> root = new osg::Geode;
//// root->addDrawable(polygon);
//// root->addDrawable(border);
//// osgViewer::View* view = new osgViewer::View;
//// view->setUpViewInWindow(50, 50, 360, 240);
//// view->setSceneData(root);
//// osgViewer::CompositeViewer viewer;
//// viewer.addView(view);
//// return viewer.run();
//
//////Sonar Track and awsd input test
////osg::ref_ptr<osgViewer::View> view = new osgViewer::View;
//////Create Earth Model
////osg::ref_ptr<osg::Geode> earth = new osg::Geode;
////earth->addDrawable(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(), osg::WGS_84_RADIUS_POLAR)));
////osg::ref_ptr<osg::Texture2D> earthTexture = new osg::Texture2D;
////earthTexture->setImage(osgDB::readImageFile("Images/land_shallow_topo_2048.jpg"));
////earth->getOrCreateStateSet()->setTextureAttributeAndModes(0, earthTexture);
////osg::ref_ptr<osg::MatrixTransform> earthNode = new osg::MatrixTransform;
////earthNode->addChild(earth);
////osg::ref_ptr<EarthHandle> earthHandle = new EarthHandle(earthNode);
//////Create Sonar Tracking
////osg::Vec3 center(-1.5f, -1.5f, -1.0f);
////osg::ref_ptr<osg::Drawable> quad = osg::createTexturedQuadGeometry(center, osg::Vec3(1.5f * 2, 0, 0), osg::Vec3(0, 1.5f * 2, 0));
////osg::ref_ptr<osg::Geode> sonar = new osg::Geode;
////sonar->addDrawable(quad);
////osg::ref_ptr<osg::Texture2D> sonarTexture = new osg::Texture2D;
////sonarTexture->setImage(osgDB::readImageFile("Images/compass_plate.png"));
////sonar->getOrCreateStateSet()->setTextureAttributeAndModes(0, sonarTexture);
////sonar->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
////osg::ref_ptr<osg::MatrixTransform> sonarTransform = new osg::MatrixTransform;
////sonarTransform->addChild(sonar);
////osg::ref_ptr<Tracking> sonarTracking = new Tracking;
////sonarTracking->setCompass(sonarTransform);
////sonarTracking->setMainCamera(view->getCamera());
////sonarTracking->setViewport(0, 0, 200, 200);
////sonarTracking->setProjectionMatrix(osg::Matrixd::ortho(-1.5, 1.5, -1.5, 1.5, -10.0, 10.0)); //What is Projection Matrix
////sonarTracking->setRenderOrder(osg::Camera::POST_RENDER);
////sonarTracking->setClearMask(GL_DEPTH_BUFFER_BIT);
////sonarTracking->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
////sonarTracking->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
////sonarTracking->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);
//////Create Root Node
////osg::ref_ptr<osg::Group> root = new osg::Group;
////root->addChild(sonarTracking);
////root->addChild(earthNode);
////view->setUpViewInWindow(50, 50, 360, 240);
////view->setSceneData(root);
////view->addEventHandler(earthHandle);
////osgViewer::CompositeViewer viewer;
////viewer.addView(view);
////return viewer.run();
//
//////Earth Compass Test
////osg::ref_ptr< osgViewer::View> view = new osgViewer::View;
////osg::ref_ptr<Compass> compass = new Compass;
////compass->setMainCamera(view->getCamera());
////compass->setViewport(0, 0, 200, 200);
////compass->setProjectionMatrix(osg::Matrixd::ortho(-1.5, 1.5, -1.5, 1.5, -10, 10));
////compass->setPlate(createCompassPlate("compass_plate.png", 1.5, -1));
//////compass->setNeedle(createCompassNeedle("compass_needle.png", 1.5, 0));
////compass->setRenderOrder(osg::Camera::POST_RENDER);
////compass->setClearMask(GL_DEPTH_BUFFER_BIT);
////compass->setAllowEventFocus(false);
////compass->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
////compass->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
////compass->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);
//////Create Earth
////osg::ref_ptr<osg::ShapeDrawable> circle = new osg::ShapeDrawable;
////circle->setShape(new osg::Sphere(osg::Vec3(), osg::WGS_84_RADIUS_POLAR));
////osg::ref_ptr<osg::Geode> earth = new osg::Geode;
////earth->addDrawable(circle);
////osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
////texture->setImage(osgDB::readImageFile("Images/land_shallow_topo_2048.jpg"));
////earth->getOrCreateStateSet()->setTextureAttributeAndModes(0, texture);
////osg::ref_ptr<osg::Group> root = new osg::Group;
////root->addChild(earth);
////root->addChild(compass);
////view->setSceneData(root);
////view->setUpViewInWindow(50, 50, 360, 240);
////osgViewer::CompositeViewer viewer;
////viewer.addView(view);
////return viewer.run();
//
//////Camera and texture test
////osg::ref_ptr<osg::Image> image = osgDB::readImageFile("Images/osg256.png");
////osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
////texture->setImage(image);
////osg::ref_ptr<osg::Drawable> quad = osg::createTexturedQuadGeometry(osg::Vec3(), osg::Vec3(1, 0, 0), osg::Vec3(0, 1, 0));
////quad->getOrCreateStateSet()->setTextureAttributeAndModes(0, texture);
////osg::ref_ptr<osg::Camera> camera = new osg::Camera;
////camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
////camera->setClearMask(0);
////camera->setProjectionMatrix(osg::Matrix::ortho2D(0.0, 1.0, 0.0, 1.0));
////camera->addChild(quad);
////camera->setRenderOrder(osg::Camera::POST_RENDER);
////camera->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
////camera->getOrCreateStateSet()->setAttributeAndModes(new osg::Depth(osg::Depth::LEQUAL, 1.0, 1.0));
////camera->setCullingActive(false);
////camera->setAllowEventFocus(false);
////osg::ref_ptr<osg::Group> root = new osg::Group;
////root->addChild(osgDB::readNodeFile("cessna.osg"));
////root->addChild(camera);
////osgViewer::View* view = new osgViewer::View;
////view->setUpViewInWindow(50, 50, 360, 240);
////view->setSceneData(root);
////osgViewer::CompositeViewer viewer;
////viewer.addView(view);
////return viewer.run();
//
//////Create animation path for wheel
//////Create Vehicle Shape
////osg::ref_ptr<osg::ShapeDrawable> mainRodShape = new osg::ShapeDrawable(new osg::Cylinder(osg::Vec3(), 0.4f, 10.0f));
////osg::ref_ptr<osg::ShapeDrawable> wheelRodShape = new osg::ShapeDrawable(new osg::Cylinder(osg::Vec3(), 0.4f, 8.0f));
////osg::ref_ptr<osg::ShapeDrawable> wheelShape = new osg::ShapeDrawable(new osg::Cylinder(osg::Vec3(), 2, 1));
////osg::ref_ptr<osg::ShapeDrawable> bodyShape = new osg::ShapeDrawable(new osg::Box(osg::Vec3(), 6.0f, 4.0f, 14.0f));
//////Setup Wheel position
////osg::ref_ptr<osg::MatrixTransform> wheel1Transform = createWheel(wheelShape, osg::Matrix::translate(0.0f, 0.0f, -4.0f));
////wheel1Transform->setUpdateCallback(createAnimation(osg::Vec3(0.0f, 0.0f, -4.0f)));
////osg::ref_ptr<osg::MatrixTransform> wheel2Transform = createWheel(wheelShape, osg::Matrix::translate(0.0f, 0.0f, 4.0f));
////wheel2Transform->setUpdateCallback(createAnimation(osg::Vec3(0.0f, 0.0f, 4.0f)));
//////Setup Wheel rod 1
////osg::ref_ptr<osg::MatrixTransform> wheelRodTransform1 = createWheel(wheelRodShape, osg::Matrix::rotate(osg::Z_AXIS, osg::X_AXIS) *
////    osg::Matrix::translate(0.0f, 0.0f, -5.0f));
////wheelRodTransform1->setMatrix(osg::Matrix::rotate(osg::Z_AXIS, osg::X_AXIS));
////wheelRodTransform1->addChild(wheel1Transform);
////wheelRodTransform1->addChild(wheel2Transform);
//////Setup Wheel rod 2
////osg::ref_ptr<osg::MatrixTransform> wheelRodTransform2 = dynamic_cast<osg::MatrixTransform*>(wheelRodTransform1->clone(osg::CopyOp::SHALLOW_COPY));
////wheelRodTransform2->setMatrix(osg::Matrix::rotate(osg::Z_AXIS,osg::X_AXIS) * osg::Matrix::translate(0.0f, 0.0f, 5.0f));
//////wheelRodTransform2->setMatrix(osg::Matrix::rotate(osg::Z_AXIS, osg::X_AXIS));
////// 
////osg::MatrixTransform* body = createWheel(bodyShape.get(), osg::Matrix::translate(0.0f, 2.2f, 0.0f));
////// 
//////Setup main Rod
////osg::MatrixTransform* mainRod = createWheel( mainRodShape.get(), osg::Matrix::identity());
////mainRod->addChild(wheelRodTransform1);
////mainRod->addChild(wheelRodTransform1);
////mainRod->addChild(body);
////osg::ref_ptr<osg::Group> root = new osg::Group;
////root->addChild(mainRod);
////osgViewer::View* view = new osgViewer::View;
////view->setUpViewInWindow(50, 50, 360, 240);
//////view->addEventHandler(new ColourPicker);
////view->setSceneData(root.get());
////osgViewer::CompositeViewer viewer;
////viewer.addView(view);
////return viewer.run();
//
//////Move Plane Test
////osg::ref_ptr<osg::Node> model = osgDB::readNodeFile("cessna.osg");
////osg::ref_ptr<osg::MatrixTransform> root = new osg::MatrixTransform;
////root->addChild(model);
////osg::ref_ptr<ObjectControlHandler> och = new ObjectControlHandler(root);
////osgViewer::Viewer viewer;
////viewer.addEventHandler(och);
////viewer.setSceneData(root);
////viewer.getCamera()->setViewMatrixAsLookAt(osg::Vec3(0.0f, -100.0f, 0.0f), osg::Vec3(), osg::X_AXIS);
////return viewer.run();
//
//////OpenScenegraph example 1
////osg::ref_ptr<osgText::Text> text = createText(osg::Vec3(50, 50, 0), "", 10);
////osg::ref_ptr<osg::Geode> textGeode = new osg::Geode;
////textGeode->addDrawable(text);
////osg::ref_ptr<osg::Camera> hudCamera = createHUDCamera(0, 800, 0, 600);
////hudCamera->addChild(textGeode);
////osg::ref_ptr<osg::Geode> geode = new osg::Geode;
////geode->addDrawable(new osg::ShapeDrawable(new osg::Box(osg::Vec3(-2, 0, 0), 1)));
////geode->addDrawable(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(2, 0, 0), 1)));
////osg::ref_ptr<osg::Group> root = new osg::Group;
////root->addChild(geode);
////root->addChild(hudCamera);
////osg::ref_ptr<ObserveShapeCallback> observerCB = new ObserveShapeCallback;
////observerCB->_text = text;
////observerCB->_drawable1 = geode->getDrawable(0);
////observerCB->_drawable2 = geode->getDrawable(1);
////root->addUpdateCallback(observerCB.get());
////osg::ref_ptr<osgViewer::View> view = new osgViewer::View;
////view->setUpViewInWindow(50, 50, 320, 240);
////view->setSceneData(root);
////view->addEventHandler(new PickHandler);
////osgViewer::CompositeViewer viewer;
////viewer.addView(view);
////return viewer.run();
//
//////Particle Test
//////Create a particle system
////osg::ref_ptr<osgParticle::ParticleSystem> particleSystem =
////    new osgParticle::ParticleSystem;
////particleSystem->getDefaultParticleTemplate().setShape(osgParticle::Particle::POINT);
//////Set rendering Attribute and mode to particle system
////osg::ref_ptr<osg::BlendFunc> blendFunc = new osg::BlendFunc;
////blendFunc->setFunction(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
////osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
////texture->setImage(osgDB::readImageFile("Images/smoke.rgb"));
////particleSystem->getOrCreateStateSet()->setAttributeAndModes(blendFunc);
////particleSystem->getOrCreateStateSet()->setTextureAttributeAndModes(0, texture);
////particleSystem->getOrCreateStateSet()->setAttribute(new osg::Point(20.0f));
////particleSystem->getOrCreateStateSet()->setTextureAttributeAndModes(0, new osg::PointSprite);
////particleSystem->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
////particleSystem->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
//////Create a RandomRateCounter class to generate random number of particle
////osg::ref_ptr<osgParticle::RandomRateCounter> randomCounter = new osgParticle::RandomRateCounter;
////randomCounter->setRateRange(500, 800);
////osg::ref_ptr<osgParticle::RadialShooter> shooter =new osgParticle::RadialShooter;
////// Theta is the angle between the velocity vector and Z axis
////shooter->setThetaRange(osg::PI_2 - 0.1f, osg::PI_2 + 0.1f);
////// Phi is the angle between X axis and the velocity vector projected
////// onto the XOY plane
////shooter->setPhiRange(-0.1f, 0.1f);
////// Set the initial speed range
////shooter->setInitialSpeedRange(5.0f, 8.0f);
//////Create a Emitter class to generate particle
////osg::ref_ptr<osgParticle::ModularEmitter> emitter = new osgParticle::ModularEmitter;
////emitter->setParticleSystem(particleSystem);
////emitter->setCounter(randomCounter);
////emitter->setShooter(shooter);
////osg::ref_ptr<osgParticle::AccelOperator> accel = new osgParticle::AccelOperator;
////accel->setToGravity();
//////Create a program to attach particle system to
////osg::ref_ptr<osgParticle::ModularProgram> program = new osgParticle::ModularProgram;
////program->setParticleSystem(particleSystem);
////program->addOperator(accel);
////osg::ref_ptr<osg::Geode> geode = new osg::Geode;
////geode->addDrawable(particleSystem);
////osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform;
////mt->setMatrix(osg::Matrix::translate(1.0f, 0.0f, 0.0f));
////mt->addChild(emitter);
////mt->addChild(program);
////mt->addChild(geode);
////osg::ref_ptr<osgParticle::ParticleSystemUpdater> updater = new osgParticle::ParticleSystemUpdater;
////updater->addParticleSystem(particleSystem);
//////osg::ref_ptr<osg::Group> root = new osg::Group;
//////root->addChild(mt.get());
////mt->addChild(updater.get());
////mt->addChild(osgDB::readNodeFile("axes.osg"));
////osg::ref_ptr<osgViewer::View> view = new osgViewer::View;
////view->setUpViewInWindow(50, 50, 320, 240);
////view->setSceneData(mt);
////osgViewer::CompositeViewer viewer;
////viewer.addView(view);
////return viewer.run();
//
//////Billboard Test
////osg::ref_ptr<osg::Geometry> quad = osg::createTexturedQuadGeometry(osg::Vec3(-0.5f, 0.0f, -0.5f), osg::Vec3(1.0f, 0.0f, 0.0f),
////    osg::Vec3(0.0f, 0.0f, 1.0f));
////osg::ref_ptr<osg::Texture2D> texture2d = new osg::Texture2D;
////osg::ref_ptr<osg::Image> image = osgDB::readImageFile("Images/tree0.rgba");
////texture2d->setImage(image);
////osg::StateSet* stateset = quad->getOrCreateStateSet();
////stateset->setTextureAttributeAndModes(0, texture2d);
////osg::ref_ptr<osg::Billboard> geode = new osg::Billboard;
////geode->setMode(osg::Billboard::POINT_ROT_WORLD);
////for (unsigned int i = 0; i < 10; i++)
////{
////    float id = (float)i;
////    geode->addDrawable(quad, osg::Vec3(-2.5f + 0.2f * id, id, 0.0f));
////    geode->addDrawable(quad, osg::Vec3(2.5f - 0.2f * id, id, 0.0f));
////}
////osg::StateSet* stateset2 = geode->getOrCreateStateSet();
////stateset2->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
////osg::ref_ptr <osg::GraphicsContext::Traits> trait = new osg::GraphicsContext::Traits;
////trait->x = 50;
////trait->y = 50;
////trait->width = 1000;
////trait->height = 1000;
////osg::ref_ptr<osg::GraphicsContext> gc = osg::GraphicsContext::createGraphicsContext(trait);
////osg::ref_ptr<osg::Camera> camera = new osg::Camera;
////camera->setGraphicsContext(gc);
////camera->setViewport(0, 0, trait->width, trait->height);
////camera->setProjectionMatrixAsPerspective(30.0f, trait->width / trait->height, 1.0, 1000.0);
////camera->setClearMask(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
////camera->setClearColor(osg::Vec4f(0.2f, 0.2f, 0.4f, 1.0f));
////osgViewer::Viewer viewer;
////viewer.setCamera(camera);
////viewer.setSceneData(geode);
////return viewer.run();
//
//////GraphicContext Test
////osg::ref_ptr<osg::GraphicsContext::Traits> trait = new osg::GraphicsContext::Traits;
////trait->x = 50;
////trait->y = 50;
////trait->width = 800;
////trait->height = 600;
////osg::ref_ptr<osg::GraphicsContext> graphicsContext = osg::GraphicsContext::createGraphicsContext(trait);
////osg::ref_ptr<osg::Camera> camera = new osg::Camera;
////camera->setGraphicsContext(graphicsContext);
////camera->setViewport(new osg::Viewport(100, 100, trait->width, trait->height));
////camera->setClearMask(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
////camera->setClearColor(osg::Vec4f(0.2f, 0.2f, 0.4f, 1.0f));
////camera->setProjectionMatrixAsPerspective(30.0f, (double)trait->width / (double)trait->height, 1.0, 1000.0);
////osg::ref_ptr<osg::Node> root = osgDB::readNodeFile("cessna.osg");
////osgViewer::Viewer viewer;
////viewer.setCamera(camera);
////viewer.setSceneData(root);
////return viewer.run();
//
//////GUIEventHandler Test
////osg::ref_ptr<osg::Node> model = osgDB::readNodeFile("cessna.osg");
////osg::ref_ptr<osg::MatrixTransform> transform = new osg::MatrixTransform;
////transform->addChild(model);
////osg::ref_ptr<ModelController> modelController = new ModelController(transform);
////osg::ref_ptr<osgViewer::View> view = new osgViewer::View;
////view->setUpViewInWindow(50, 50, 320, 240);
////view->setSceneData(transform);
////view->addEventHandler(modelController.get());
//////view->getCamera()->setViewMatrixAsLookAt(osg::Vec3(0.0f, -100.0f, 0.0f), osg::Vec3(), osg::Z_AXIS);
//////view->getCamera()->setAllowEventFocus(false);
////osgViewer::CompositeViewer viewer;
////viewer.addView(view);
////return viewer.run();
//
//////Create Animation Channel
////osg::ref_ptr<osgAnimation::Vec3LinearChannel> ch1 = new osgAnimation::Vec3LinearChannel;
////ch1->setName("position");
////ch1->setTargetName("PathCallback");
////osg::ref_ptr<osgAnimation::QuatSphericalLinearChannel> ch2 = new osgAnimation::QuatSphericalLinearChannel;
////ch2->setName("quat");
////ch2->setTargetName("PathCallback");
////createSamplerClass(50.0f, 6.0f, 
////    ch1->getOrCreateSampler()->getOrCreateKeyframeContainer(), ch2->getOrCreateSampler()->getOrCreateKeyframeContainer());
//////Setup Animation Object
////osg::ref_ptr<osgAnimation::Animation> animation = new osgAnimation::Animation;
////animation->setPlayMode(osgAnimation::Animation::LOOP);
////animation->addChannel(ch1);
////animation->addChannel(ch2);
//////Setup Node to attach animation to
////osg::ref_ptr<osgAnimation::UpdateMatrixTransform> updater = new osgAnimation::UpdateMatrixTransform("PathCallback");
////updater->getStackedTransforms().push_back(new osgAnimation::StackedTranslateElement("position"));
////updater->getStackedTransforms().push_back(new osgAnimation::StackedQuaternionElement("quat"));
////osg::ref_ptr<osg::MatrixTransform> animeRoot = new osg::MatrixTransform;
////animeRoot->addChild(osgDB::readNodeFile("cessna.osg"));
////animeRoot->setDataVariance(osg::Object::DYNAMIC);
////animeRoot->setUpdateCallback(updater);
////osg::ref_ptr<osgAnimation::BasicAnimationManager> manager = new osgAnimation::BasicAnimationManager;
////manager->registerAnimation(animation);
////osg::ref_ptr<osg::Group> root = new osg::Group;
////root->addChild(animeRoot);
////root->setUpdateCallback(manager);
////manager->playAnimation(animation);
////osg::ref_ptr<osgViewer::View> view = new osgViewer::View;
////view->setUpViewInWindow(50, 50, 320, 240);
////view->setSceneData(root);
////osgViewer::CompositeViewer viewer;
////viewer.addView(view);
////return viewer.run();
//
//////AnimationPath Test
////float radius = 50.0f, time = 6.0f;
////osg::ref_ptr<osg::Node> model = osgDB::readNodeFile("cessna.osg");
////osg::ref_ptr<osg::MatrixTransform> root = new osg::MatrixTransform;
////root->addChild(model);
////osg::ref_ptr<osg::AnimationPath> animePath = new osg::AnimationPath;
////animePath->setLoopMode(osg::AnimationPath::LOOP);
////unsigned int numSamples = 32;
////float delta_yaw = 2.0f * osg::PI / ((float)numSamples - 1.0f);
////float delta_time = time / (float)numSamples;
////for (unsigned int i = 0; i < numSamples; ++i)
////{
////    float yaw = delta_yaw * (float)i;
////    osg::Vec3 pos(sinf(yaw) * radius, cosf(yaw) * radius, 0.0f);
////    osg::Quat rot(-yaw, osg::Z_AXIS);
////    animePath->insert(delta_time * (float)i, osg::AnimationPath::ControlPoint(pos, rot));
////}
////osg::ref_ptr<osg::AnimationPathCallback> pathCallback = new osg::AnimationPathCallback;
////pathCallback->setAnimationPath(animePath);
////root->setUpdateCallback(pathCallback);
////osg::ref_ptr<osgViewer::View> view = new osgViewer::View;
////view->setUpViewInWindow(50, 50, 320, 240);
////view->setSceneData(root);
////osgViewer::CompositeViewer viewer;
////viewer.addView(view);
////return viewer.run();
//
//////osg::Drawable::UpdateCallback Test
////osg::ref_ptr<osg::Geometry> quad = createQuad();
////quad->setDataVariance(osg::Object::DYNAMIC);
////quad->setUpdateCallback(new DynamicQuadCallback);
////osg::ref_ptr<osg::Geode> root = new osg::Geode;
////root->addDrawable(quad);
////osg::ref_ptr<osgViewer::View> view = new osgViewer::View;
////view->setSceneData(root);
////view->setUpViewInWindow(50, 50, 320, 240);
////osgViewer::CompositeViewer viewer;
////viewer.addView(view);
////return viewer.run();
//
//////NodeCallback Test
////osg::ref_ptr<osg::Node> model1 = osgDB::readNodeFile("cessna.osg");
////osg::ref_ptr<osg::Node> model2 = osgDB::readNodeFile("cessnafire.osg");
////osg::ref_ptr<osg::Switch> root = new osg::Switch;
////root->addChild(model1.get(), true);
////root->addChild(model2.get(), false);
////root->setUpdateCallback(new SwitchCallback);
////osg::ref_ptr<osgViewer::View> view = new osgViewer::View;
////view->setSceneData(root);
////view->setUpViewInWindow(50, 50, 320, 240);
////osgViewer::CompositeViewer viewer;
////viewer.addView(view);
////return viewer.run();
//
//////osg::CompositeViewer Test
////osg::ref_ptr<osg::Node> model1 = osgDB::readNodeFile("lz.osg");
////osg::ref_ptr<osg::Node> model2 = osgDB::readNodeFile("cessna.osg");
////osg::ref_ptr<osg::Node> model3 = osgDB::readNodeFile("glider.osg");
////osgViewer::View* view1 = createView(50, 50, 320, 240, model1);
////osgViewer::View* view2 = createView(370, 50, 320, 240, model2);
////osgViewer::View* view3 = createView(185, 310, 320, 240, model3);
////osgViewer::CompositeViewer view;
////view.addView(view1);
////view.addView(view2);
////view.addView(view3);
////return view.run();
//
//////Camera test
////osg::ref_ptr<osg::Node> model = osgDB::readNodeFile("lz.osg");
////osg::ref_ptr<osg::Node> hud_model = osgDB::readNodeFile("glider.osg");
////osg::ref_ptr<osg::Camera> camera = new osg::Camera;
////camera->setClearMask(GL_DEPTH_BUFFER_BIT);
////camera->setRenderOrder(osg::Camera::POST_RENDER);
////camera->setReferenceFrame(osg::Camera::ABSOLUTE_RF);
////camera->setViewMatrixAsLookAt(osg::Vec3(0.0f, -5.0f, 5.0f), osg::Vec3(), osg::Vec3(0.0f, 1.0f, 1.0f));
////camera->addChild(hud_model);
////osg::ref_ptr<osg::Group> root = new osg::Group;
////root->addChild(model.get());
////root->addChild(camera.get());
////osgViewer::Viewer viewer;
////viewer.setSceneData(root.get());
////return viewer.run();
//
//////Shader Test
////osg::ref_ptr<osg::Shader> vertexShader = new osg::Shader(osg::Shader::VERTEX, vertSource);
////osg::ref_ptr<osg::Shader> fragmentShader = new osg::Shader(osg::Shader::FRAGMENT, fragSource);
////osg::ref_ptr<osg::Program> shaderProgram = new osg::Program;
////shaderProgram->addShader(vertexShader);
////shaderProgram->addShader(fragmentShader);
////osg::ref_ptr<osg::Node> model = osgDB::readNodeFile("cow.osg");
////osg::ref_ptr<osg::StateSet> stateset = new osg::StateSet;
////stateset->setAttributeAndModes(shaderProgram);
////stateset->addUniform(new osg::Uniform("color1", osg::Vec4(1.0f, 0.5f, 0.5f, 1.0f)));
////stateset->addUniform(new osg::Uniform("color2", osg::Vec4(0.5f, 0.2f, 0.2f, 1.0f)));
////stateset->addUniform(new osg::Uniform("color3", osg::Vec4(0.2f, 0.1f, 0.1f, 1.0f)));
////stateset->addUniform(new osg::Uniform("color4", osg::Vec4(0.1f, 0.05f, 0.05f, 1.0f)));
////model->setStateSet(stateset);
////osg::ref_ptr<osg::Group> root = new osg::Group;
////root->addChild(model);
////osgViewer::Viewer viewer;
////viewer.setSceneData(root);
////return viewer.run();
//
//////Texture Test
////osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
////vertices->push_back(osg::Vec3(-0.5f, 0.0f, -0.5f));
////vertices->push_back(osg::Vec3(0.5f, 0.0f, -0.5f));
////vertices->push_back(osg::Vec3(0.5f, 0.0f, 0.5f));
////vertices->push_back(osg::Vec3(-0.5f, 0.0f, 0.5f));
////osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array;
////normals->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));
////osg::ref_ptr<osg::Vec2Array> textureCoordinate = new osg::Vec2Array;
////textureCoordinate->push_back(osg::Vec2(0.0f, 0.0f));
////textureCoordinate->push_back(osg::Vec2(0.0f, 1.0f));
////textureCoordinate->push_back(osg::Vec2(1.0f, 1.0f));
////textureCoordinate->push_back(osg::Vec2(1.0f, 0.0f));
////osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
////geom->setVertexArray(vertices);
////geom->setNormalArray(normals);
////geom->setNormalBinding(osg::Geometry::BIND_OVERALL);
////geom->setTexCoordArray(0, textureCoordinate);
////geom->addPrimitiveSet(new osg::DrawArrays(GL_QUADS, 0, 4));
////osg::ref_ptr<osg::Image> image = osgDB::readImageFile("Images/lz.rgb");
////osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
////texture->setImage(image);
////osg::ref_ptr<osg::Geode> root = new osg::Geode;
////root->addDrawable(geom);
////osg::ref_ptr<osg::StateSet> stateSet = new osg::StateSet;
////stateSet->setTextureAttributeAndModes(0, texture);
////root->setStateSet(stateSet);
////osgViewer::Viewer viewer;
////viewer.setSceneData(root);
////return viewer.run();
//
//////Create light source test
////osg::ref_ptr<osg::Node> model = osgDB::readNodeFile("cessna.osg");
////osg::ref_ptr<osg::Group> root = new osg::Group;
////root->addChild(model);
////osg::ref_ptr<osg::Node> light0 = createLightSource(0, osg::Vec3(-20.0f, 0.0f, 0.0f), osg::Vec4(1.0f, 1.0f, 0.0f, 1.0f));
////osg::ref_ptr<osg::Node> light1 = createLightSource(1, osg::Vec3(0.0f, -20.0f, 0.0f), osg::Vec4(0.0f, 1.0f, 1.0f, 1.0f));
////osg::ref_ptr<osg::StateSet> stateSet1 = new osg::StateSet;
////stateSet1->setMode(GL_LIGHT0, osg::StateAttribute::ON);
////root->setStateSet(stateSet1);
////root->getOrCreateStateSet()->setMode(GL_LIGHT1, osg::StateAttribute::ON);
////root->addChild(light0);
////root->addChild(light1);
////osgViewer::Viewer viewer;
////viewer.setSceneData(root);
////return viewer.run();
//
//////Fog Test
////osg::ref_ptr<osg::Group> model = dynamic_cast<osg::Group*>( osgDB::readNodeFile("lz.osg"));
////osg::ref_ptr<osg::Fog> fog = new osg::Fog;
////fog->setMode(osg::Fog::LINEAR);
////fog->setStart(500.0f);
////fog->setEnd(2500.0f);
////fog->setColor(osg::Vec4(1.0f, 1.0f, 0.0f, 1.0f));
////osg::ref_ptr<osg::StateSet> stateset = new osg::StateSet;
////stateset->setAttributeAndModes(fog);
////model->setStateSet(stateset);
////osgViewer::Viewer viewer;
////viewer.setSceneData(model);
////return viewer.run();
//
//////GL_LIGHTING TEST
//    //osg::ref_ptr<osg::Node> model = osgDB::readNodeFile("glider.osg");
//    //osg::ref_ptr<osg::MatrixTransform> transform1 = new osg::MatrixTransform;
//    //transform1->setMatrix(osg::Matrix::translate(osg::Vec3(-0.5f, 0.0f, 0.0f)));
//    //osg::ref_ptr<osg::MatrixTransform> transform2 = new osg::MatrixTransform;
//    //transform2->setMatrix(osg::Matrix::translate(osg::Vec3(0.5f, 0.0f, 0.0f)));
//    ////Add StateSet
//    //osg::ref_ptr<osg::StateSet> transform1StateSet = new osg::StateSet;
//    //transform1StateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
//    //osg::ref_ptr<osg::StateSet> transform2StateSet = new osg::StateSet;
//    //transform2StateSet->setMode(GL_LIGHTING, osg::StateAttribute::ON|osg::StateAttribute::PROTECTED);
//    //osg::ref_ptr<osg::StateSet> rootStateSet = new osg::StateSet;
//    //transform1StateSet->setMode(GL_LIGHTING, osg::StateAttribute::ON|osg::StateAttribute::OVERRIDE);
//    //transform1->addChild(model);
//    //transform1->setStateSet(transform1StateSet);
//    //transform2->addChild(model);
//    //transform2->setStateSet(transform2StateSet);
//    //osg::ref_ptr<osg::Group> root = new osg::Group;
//    //root->addChild(transform1.get());
//    //root->addChild(transform2.get());
//    //root->setStateSet(rootStateSet);
//    //osgViewer::Viewer viewer;
//    //viewer.setSceneData(root);
//    //return viewer.run();
//
//////StateSet Example
//    //osg::ref_ptr<osg::Node> model = osgDB::readNodeFile("cessna.osg");
//    //osg::ref_ptr<osg::MatrixTransform> transform1 = new osg::MatrixTransform;
//    //transform1->setMatrix(osg::Matrix::translate(osg::Vec3(-25.0f, 0, 0)));
//    //osg::ref_ptr<osg::MatrixTransform> transform2 = new osg::MatrixTransform;
//    //transform2->setMatrix(osg::Matrix::translate(osg::Vec3(25.0f, 0, 0)));
//    //transform1->addChild(model);
//    //transform2->addChild(model);
//    //osg::ref_ptr<osg::PolygonMode> pm = new osg::PolygonMode;
//    //pm->setMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE);
//    //osg::ref_ptr<osg::StateSet> stateSet = new osg::StateSet;
//    //stateSet->setAttribute(pm.get());
//    ////transform1->getOrCreateStateSet()->setAttribute(pm.get()); //Shortcut way to set Attribute
//    //transform1->setStateSet(stateSet.get());
//    //osg::ref_ptr<osg::Group> root = new osg::Group;
//    //root->addChild(transform1.get());
//    //root->addChild(transform2.get());
//    //osgViewer::Viewer viewer;
//    //viewer.setSceneData(root);
//    //return viewer.run();
//
//////Switching Scene Test
////osg::ref_ptr<osg::Node> model1 = osgDB::readNodeFile("cessna.osg");
////osg::ref_ptr<osg::Node> model2 = osgDB::readNodeFile("cessnafire.osg");
////osg::ref_ptr<AnimatingSwitch> root = new AnimatingSwitch;
////root->addChild(model1.get(), true);
////root->addChild(model2.get(), false);
////osgViewer::Viewer viewer;
////viewer.setSceneData(root);
////return viewer.run();
//
//////Switch Test
////osg::ref_ptr<osg::Group> model1 = dynamic_cast<osg::Group*>( osgDB::readNodeFile("cessna.osg"));
////osg::ref_ptr<osg::Node> model2 = osgDB::readNodeFile("cessnafire.osg");
////osg::ref_ptr<osg::Node> model3 = dynamic_cast<osg::Node*>( model2->clone(osg::CopyOp::DEEP_COPY_ALL));
////osg::ref_ptr<osg::Switch> root = new osg::Switch;
////root->addChild(model2, false);
////root->addChild(model3, true);
//
//////Use MatrixTransform and PositionAttitudeTransform to display 2 models
////osg::ref_ptr<osg::Node> pic1 = dynamic_cast<osg::Group*>( osgDB::readNodeFile("cessna.osg"));
//////osg::ref_ptr<osg::Group> pic2 = dynamic_cast<osg::Group*>(osgDB::readNodeFile("cow.osg"));
/////*osg::ref_ptr<osg::MatrixTransform> transform1 = new osg::MatrixTransform;
////transform1->setMatrix(osg::Matrix::translate(-25.0f, 0.0f, 0.0f));
////transform1->addChild(pic1);*/
////osg::ref_ptr<osg::PositionAttitudeTransform> transform1 = new osg::PositionAttitudeTransform;
////transform1->setPosition(osg::Vec3(-25.0f, 0.0f, 0.0f));
////transform1->setScale(osg::Vec3(1.0f, 1.0f, 1.0f));
////transform1->addChild(pic1);
////osg::ref_ptr<osg::MatrixTransform> transform2 = new osg::MatrixTransform;
////transform2->setMatrix(osg::Matrix::translate(25.0f, 100.0f, 20.0f));
////transform2->setMatrix(osg::Matrix::scale(5.0f, 5.0f, 5.0f));
////transform2->addChild(pic1);
////osg::ref_ptr<osg::Group> group = new osg::Group;
//////group->addChild(pic1);
//////group->addChild(pic2);
////group->addChild(transform1);
////group->addChild(transform2);
////osgViewer::Viewer viewer;
////viewer.setSceneData(group.get());
////return viewer.run();
//
//////Drawing a polygon
//    //osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
//    //vertices->push_back(osg::Vec3(0.0f, 0.0f, 0.0f));
//    //vertices->push_back(osg::Vec3(2.0f, 0.0f, 0.0f));
//    //vertices->push_back(osg::Vec3(2.0f, 0.0f, 1.0f));
//    //vertices->push_back(osg::Vec3(1.0f, 0.0f, 1.0f));
//    //vertices->push_back(osg::Vec3(1.0f, 0.0f, 2.0f));
//    //vertices->push_back(osg::Vec3(2.0f, 0.0f, 2.0f));
//    //vertices->push_back(osg::Vec3(2.0f, 0.0f, 3.0f));
//    //vertices->push_back(osg::Vec3(0.0f, 0.0f, 3.0f));
//    //osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array;
//    //normals->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));
//    //osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
//    //geom->setVertexArray(vertices.get());
//    //geom->setNormalArray(normals.get());
//    //geom->setNormalBinding(osg::Geometry::BIND_OVERALL);
//    //geom->addPrimitiveSet(new osg::DrawArrays(GL_POLYGON, 0, 8));
//    //osgUtil::Tessellator tessellator;
//    //tessellator.retessellatePolygons(*geom);
//    //osg::ref_ptr<osg::Geode> root = new osg::Geode;
//    //root->addDrawable(geom.get());
//    //osgViewer::Viewer viewer;
//    //viewer.setSceneData(root.get());
//    //return viewer.run();
//
//////Draw a Pyramid
////osg::ref_ptr<osg::Vec3Array> pyramidVertices = new osg::Vec3Array(5);
////(*pyramidVertices)[0].set(0.0f, 0.0f, 1.0f);
////(*pyramidVertices)[1].set(-0.5f, -0.5f, 0.0f);
////(*pyramidVertices)[2].set(0.5f, -0.5f, 0.0f);
////(*pyramidVertices)[3].set(0.5f, 0.5f, 0.0f);
////(*pyramidVertices)[4].set(-0.5f, 0.5f, 0.0f);
////osg::ref_ptr<osg::DrawElementsUInt> pyramidIndices = new osg::DrawElementsUInt(GL_TRIANGLES, 12);
////(*pyramidIndices)[0] = 0; (*pyramidIndices)[1] = 1; (*pyramidIndices)[2] = 2;
////(*pyramidIndices)[3] = 0; (*pyramidIndices)[4] = 2; (*pyramidIndices)[5] = 3;
////(*pyramidIndices)[6] = 0; (*pyramidIndices)[7] = 3; (*pyramidIndices)[8] = 4;
////(*pyramidIndices)[9] = 0; (*pyramidIndices)[10] = 4; (*pyramidIndices)[11] = 1;
////osg::ref_ptr<osg::Vec4Array> pyramidColours = new osg::Vec4Array;
////pyramidColours->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
////pyramidColours->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f));
////pyramidColours->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f));
////pyramidColours->push_back(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
////osg::ref_ptr<osg::Geometry> pyramid = new osg::Geometry;
////pyramid->setVertexArray(pyramidVertices.get());
////pyramid->addPrimitiveSet(pyramidIndices.get());
////pyramid->setColorArray(pyramidColours.get());
////pyramid->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
//////Create 4 corner of the shape
//////osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array();
////osg::ref_ptr<osg::Vec3Array> rectangleVertices = new osg::Vec3Array(4);
////(*rectangleVertices)[0].set(-0.5f, -0.5f, 0.0f);
////(*rectangleVertices)[1].set(0.5f, -0.5f, 0.0f);
////(*rectangleVertices)[2].set(0.5f, 0.5f, 0.0f);
////(*rectangleVertices)[3].set(-0.5f, 0.5f, 0.0f);
////osg::ref_ptr<osg::DrawElementsUInt> rectangleIndices = new osg::DrawElementsUInt(GL_QUADS, 4);
////(*rectangleIndices)[0] = 0; (*rectangleIndices)[1] = 1; 
////(*rectangleIndices)[2] = 2; (*rectangleIndices)[3] = 3;
//////create normal vector for the shape
////osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array();
////normals->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));
//////Create color for each vertex
////osg::ref_ptr<osg::Vec4Array> rectangleColours = new osg::Vec4Array();
////rectangleColours->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
////rectangleColours->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f));
////rectangleColours->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f));
////rectangleColours->push_back(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
//////Create Geometry object to hold all information and set DrawArray
////osg::ref_ptr<osg::Geometry> quad = new osg::Geometry();
////quad->setVertexArray(rectangleVertices.get());
////quad->setNormalArray(normals.get());
////quad->setNormalBinding(osg::Geometry::BIND_OVERALL);
////quad->setColorArray(rectangleColours.get());
////quad->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
////quad->addPrimitiveSet(rectangleIndices.get());
////osg::ref_ptr<osg::Geode> root = new osg::Geode;
//////root->addDrawable(pyramid.get());
////root->addDrawable(quad.get());
////osgViewer::Viewer viewer;
////viewer.setSceneData(root.get());
////return viewer.run();
//
//
////Draw an Octahedron
////osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array(6);
/////*vertices->push_back(osg::Vec3(0,0,0));
////vertices->push_back(osg::Vec3(1, 1, 1));
////vertices->push_back(osg::Vec3(2, 2, 2));*/
////(*vertices)[0].set(0.0f, 0.0f, 1.0f);
////(*vertices)[1].set(-0.5f, -0.5f, 0.0f);
////(*vertices)[2].set(0.5f, -0.5f, 0.0f);
////(*vertices)[3].set(0.5f, 0.5f, 0.0f);
////(*vertices)[4].set(-0.5f, 0.5f, 0.0f);
////(*vertices)[5].set(0.0f, 0.0f, -1.0f);
//////24 refers to number of vertices (8 triangle * 3 vertices)
////osg::ref_ptr<osg::DrawElementsUInt> indices = new osg::DrawElementsUInt(GL_TRIANGLES, 24); 
////(*indices)[0] = 0; (*indices)[1] = 1; (*indices)[2] = 2;
////(*indices)[3] = 0; (*indices)[4] = 2; (*indices)[5] = 3;
////(*indices)[6] = 0; (*indices)[7] = 3; (*indices)[8] = 4;
////(*indices)[9] = 0; (*indices)[10] = 4; (*indices)[11] = 1;
////(*indices)[12] = 5; (*indices)[13] = 1; (*indices)[14] = 2;
////(*indices)[15] = 5; (*indices)[16] = 2; (*indices)[17] = 3;
////(*indices)[18] = 5; (*indices)[19] = 3; (*indices)[20] = 4;
////(*indices)[21] = 5; (*indices)[22] = 4; (*indices)[23] = 1;
////osg::ref_ptr<osg::Vec4Array> colours = new osg::Vec4Array();
////colours->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
////colours->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f));
////colours->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f));
////colours->push_back(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
////osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array;
////normals->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));
////osg::ref_ptr<osg::Geometry> shape = new osg::Geometry;
////shape->setVertexArray(vertices.get());
////shape->addPrimitiveSet(indices.get());
////shape->setColorArray(colours.get());
////shape->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
////shape->setNormalArray(normals.get());
////shape->setNormalBinding(osg::Geometry::BIND_OVERALL);
////osgUtil::SmoothingVisitor::smooth(*shape);
//
//////Create a Primitive Rectangle
//    ////Create 4 corner of the shape
//    //osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array();
//    //vertices->push_back(osg::Vec3(0.0f, 0.0f, 0.0f));
//    //vertices->push_back(osg::Vec3(1.0f, 0.0f, 0.0f));
//    //vertices->push_back(osg::Vec3(1.0f, 0.0f, 1.0f));
//    //vertices->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));
//    ////create normal vector for the shape
//    //osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array();
//    //normals->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));
//    ////Create color for each vertex
//    //osg::ref_ptr<osg::Vec4Array> colours = new osg::Vec4Array();
//    //colours->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
//    //colours->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f));
//    //colours->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f));
//    //colours->push_back(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
//    ////Create Geometry object to hold all information and set DrawArray
//    //osg::ref_ptr<osg::Geometry> quad = new osg::Geometry();
//    //quad->setVertexArray(vertices.get());
//    //quad->setNormalArray(normals.get());
//    //quad->setNormalBinding(osg::Geometry::BIND_OVERALL);
//    //quad->setColorArray(colours.get());
//    //quad->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
//    //quad->addPrimitiveSet(new osg::DrawArrays(GL_QUADS, 0, 4));
//    ////Create Leaf Node
//    //osg::ref_ptr<osg::Geode> root = new osg::Geode();
//    //root->addDrawable(quad.get());
//    //osgViewer::Viewer viewer;
//    //viewer.setSceneData(root.get());
//    //return viewer.run();
//
////Draw 3 Basic Shape using ShapeDrawable
////osg::ref_ptr<osg::ShapeDrawable> shape1 = new osg::ShapeDrawable();
////osg::ref_ptr<osg::ShapeDrawable> shape2 = new osg::ShapeDrawable();
////osg::ref_ptr<osg::ShapeDrawable> shape3 = new osg::ShapeDrawable();
////shape1->setShape(new osg::Box(osg::Vec3(-3.0f, 0.0f, 0.0f), 2.0f, 2.0f, 1.0f));
////shape2->setShape(new osg::Sphere(osg::Vec3(3.0f, 0.0f, 0.0f), 1.0f));
////shape2->setColor(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f));
////shape3->setShape(new osg::Cone(osg::Vec3(0.0f, 0.0f, 0.0f), 1.0f, 1.0f));
////shape3->setColor(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f));
////osg::ref_ptr<osg::Geode> root = new osg::Geode;
////root->addDrawable(shape1.get());
////root->addDrawable(shape2.get());
////root->addDrawable(shape3.get());
////osgViewer::Viewer viewer;
////viewer.setSceneData(root.get());
////return viewer.run();
//
//////Run a predefined prefab
//    ///*osgViewer::Viewer viewer;
//    //viewer.setSceneData(osgDB::readNodeFile("cow.osg"));*/
//    //osg::ref_ptr<osg::Node> root = new osg::Node;
//    //root = osgDB::readNodeFile("cessna.osg");
//    ////osg::Node *root = osgDB::readNodeFile("cessna.osg");
//    //osgViewer::Viewer viewer;
//    //viewer.setSceneData(root.get());
//    //return viewer.run();
//
//
//    //osg::ref_ptr<MonitoringTarget> target = createMonitoringTarget(1);
//    //std::cout << "Referenced count before refering: " << target->referenceCount() << std::endl;
//    //osg::ref_ptr<MonitoringTarget> anotherTarget = target;
//    //std::cout << "Referenced count after refering: " << target->referenceCount() << std::endl;
//    //for (int i = 0; i < 5; i++)
//    //{
//    //    osg::ref_ptr<MonitoringTarget> subTarget = createMonitoringTarget(i);
//    //}
//
//    
//    //OpenGL Code - Draw a Triangles
//    // 
//    //glfwInit();
//    ///* Initialize the library */
//    //if (!glfwInit())
//    //    return -1;
//    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//    //glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
//    //GLFWwindow* window;
//    ///* Create a windowed mode window and its OpenGL context */
//    //window = glfwCreateWindow(640, 480, "Triangle", NULL, NULL);
//    //if (!window)
//    //{
//    //    glfwTerminate();
//    //    return -1;
//    //}
//    ///* Make the window's context current */
//    //glfwMakeContextCurrent(window);
//    //glewInit();
//    ////Vertex data
//    //float vertices[6] =
//    //{
//    //    -0.5f, -0.5f,
//    //    0.0f, 0.5f,
//    //    0.5f, -0.5f,
//    //};
//    ////create vertex array
//    //unsigned int vao;
//    //glGenVertexArrays(1, &vao);
//    //glBindVertexArray(vao);
//    ////create vertex buffer
//    //unsigned int vbo;
//    //glGenBuffers(1, &vbo);
//    //glBindBuffer(GL_ARRAY_BUFFER, vbo);
//    //glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), vertices, GL_STATIC_DRAW);
//    ////specify vertex attribute
//    //glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
//    //glEnableVertexAttribArray(0);
//    ////vertex shader
//    //unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
//    //glShaderSource(vs, 1, &vertexShaderSource, NULL);
//    //glCompileShader(vs);
//    ////fragment shader
//    //unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
//    //glShaderSource(fs, 1, &vertexFragmentSource, NULL);
//    //glCompileShader(fs);
//    //unsigned int shaderProgram = glCreateProgram();
//    //glAttachShader(shaderProgram, vs);
//    //glAttachShader(shaderProgram, fs);
//    //glLinkProgram(shaderProgram);
//    //glDeleteShader(vs);
//    //glDeleteShader(fs);
//    //glUseProgram(shaderProgram);
//    ///* Loop until the user closes the window */
//    //while (!glfwWindowShouldClose(window))
//    //{
//    //    /* Render here */
//    //    glClear(GL_COLOR_BUFFER_BIT);
//
//    //    glDrawArrays(GL_TRIANGLES, 0, 3);
//
//    //    /* Swap front and back buffers */
//    //    glfwSwapBuffers(window);
//
//    //    /* Poll for and process events */
//    //    glfwPollEvents();
//    //}
//    //glfwTerminate();
//    //return 0;