//#include <iostream>
//#include <time.h>
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#include "Model.h"
//
//#include <osgDB/ReadFile>
//#include <osgViewer/Viewer>
//#include <osgViewer/CompositeViewer>
//
//#include <osg/PolygonMode>
//#include <osg/ShapeDrawable>
//#include <osg/Geode>
//#include <osg/Geometry>
//#include <osg/MatrixTransform>
//#include <osg/LightSource>
//#include <osg/Texture2D>
//#include <osg/Depth>
//#include <osg/Material>
//#include <osg/Camera>
//
//#include <osgGA/TrackballManipulator>
//#include <osgGA/GUIEventHandler>
//
//#include <osgUtil/LineSegmentIntersector>
//
////Fading in and out
//#include <osg/BlendFunc>
////#include <osg/Material>
//#include <osg/Node>
//#include <osgAnimation/EaseMotion>
//#include <osgUtil/CullVisitor>
//
//#include <osgUtil/TangentSpaceGenerator>//////Include for map designing
//#include "Sky.h"
//
////Include for water effect
//#include <osg/TexGen>
//#include <osg/ShapeDrawable>
//#include <osg/Geometry>
//#include <osg/ClipNode>
//#include <osg/MatrixTransform>
//#include <osgDB/ReadFile>
//#include <osgViewer/Viewer>
//
////Include for sonar camera
//#include <osg/Camera>
//#include <osg/MatrixTransform>
//#include <osgDB/ReadFile>
//#include <osgGA/OrbitManipulator>
//#include <osgViewer/Viewer>
//
//#include <osgViewer/ViewerEventHandlers>
//#include <math.h>
//#include "CameraMover.h"
//
//#include <osg/Switch>
//#include "TextureSeabed.h"
//#include "FadeInOutCallback.h"
//
////Include for text
//#include <osg/Camera>
//#include <osgDB/ReadFile>
//#include <osgText/Font>
//#include <osgText/Text>
//#include <osgViewer/Viewer>
//#include "ControlMenu.h"
//
////Include for trait
//#include "SplitScreenTrait.h"
//
//#include <osg/Projection>
//
//const unsigned int MAIN_CAMERA_MASK = 0x1;
//const unsigned int RADAR_CAMERA_MASK = 0x2;
//#define RAND(min, max) ((min) + (float)rand()/(RAND_MAX+1) * ((max)-(min)))
//
//static const char* menuText = {
//    "Key Controls\n"
//    "================================\n"
//    "[Keyup]---------Move forward\n"
//    "[Keydown]-------Move backward\n"
//    "[Keyleft]-------Pan left\n"
//    "[Keyright]------Pan right\n"
//    "[w]-------------Move up\n"
//    "[s]-------------Move down\n"
//    "[a]-------------Move left\n"
//    "[d]-------------Move right\n"
//};
//
//static const char* vsSource =
//{
//    "void main(void)\n"
//    "{\n"
//    "   gl_Position = ftransform();\n"
//    "   gl_TexCoord[0] = gl_MultiTexCoord0;\n"
//    "}\n"
//};
//
//static const char* fsSource =
//{
//    "uniform sampler2D sceneTex;\n"
//    "uniform sampler2D noiseTex;\n"
//    "uniform float osg_FrameTime;\n"
//
//    "void main(void)\n"
//    "{\n"
//    "   float factor = osg_FrameTime * 100.0;\n"
//    "   vec2 uv = vec2(0.4*sin(factor), 0.4*cos(factor));\n"
//    "   vec3 n = texture2D(noiseTex, (gl_TexCoord[0].st*3.5) + uv).rgb;\n"
//
//    "   vec3 c = texture2D(sceneTex, gl_TexCoord[0].st + (n.xy*0.005)).rgb;\n"
//    "   float lum = dot(vec3(0.30, 0.59, 0.11), c);\n"
//    "   if (lum < 0.2) c *= 4.0;\n"
//
//    "   vec3 finalColor = (c + (n*0.2)) * vec3(0.1, 0.95, 0.2);\n"
//    "   gl_FragColor = vec4(finalColor, 1.0);\n"
//    "}\n"
//};
//
//static const char* vertSource = {
//    "attribute vec3 tangent;\n"
//    "attribute vec3 binormal;\n"
//    "varying vec3 lightDir;\n"
//    "void main()\n"
//    "{\n"
//    "    vec3 normal = normalize(gl_NormalMatrix * gl_Normal);\n"
//    "    mat3 rotation = mat3(tangent, binormal, normal);\n"
//    "    vec4 vertexInEye = gl_ModelViewMatrix * gl_Vertex;\n"
//    "    lightDir = vec3(gl_LightSource[0].position.xyz - vertexInEye.xyz);\n"
//    "    lightDir = normalize(rotation * normalize(lightDir));\n"
//    "    gl_Position = ftransform();\n"
//    "    gl_TexCoord[0] = gl_MultiTexCoord0;\n"
//    "}\n"
//};
//
//static const char* fragSource = {
//    "uniform sampler2D colorTex;\n"
//    "uniform sampler2D normalTex;\n"
//    "varying vec3 lightDir;\n"
//    "void main (void)\n"
//    "{\n"
//    "    vec4 base = texture2D(colorTex, gl_TexCoord[0].xy);\n"
//    "    vec3 bump = texture2D(normalTex, gl_TexCoord[0].xy).xyz;\n"
//    "    bump = normalize(bump * 2.0 - 1.0);\n"
//
//    "    float lambert = max(dot(bump, lightDir), 0.0);\n"
//    "    if (lambert > 0.0)\n"
//    "    {\n"
//    "        gl_FragColor = base * gl_LightSource[0].diffuse * lambert;\n"
//    "        gl_FragColor += gl_LightSource[0].specular * pow(lambert, 2.0);\n"
//    "    }\n"
//    "    gl_FragColor += gl_LightSource[0].ambient;\n"
//    "}\n"
//};
//
////static const char* vertSource =
////{
////    "void main(void)\n"
////    "{\n"
////    "gl_Position = ftransform();\n"
////    "gl_TexCoord[0] = gl_MultiTexCoord0;\n"
////    "}\n"
////};
//
//static const char* blurFragSource = {
//    "uniform sampler2D inputTex;\n"
//    "uniform vec2 blurDir;\n"
//    "void main(void)\n"
//    "{\n"
//    "   vec2 uv = gl_TexCoord[0].st;\n"
//    "   vec2 offset = vec2(0.004*blurDir.x, 0.003*blurDir.y);\n"
//    "   vec4 color = texture2D(inputTex, uv) * 0.3;\n"
//    "   color += texture2D(inputTex, uv - offset*3.0) * 0.05;\n"
//    "   color += texture2D(inputTex, uv - offset*2.0) * 0.1;\n"
//    "   color += texture2D(inputTex, uv - offset) * 0.2;\n"
//    "   color += texture2D(inputTex, uv + offset) * 0.2;\n"
//    "   color += texture2D(inputTex, uv + offset*2.0) * 0.1;\n"
//    "   color += texture2D(inputTex, uv + offset*3.0) * 0.05;\n"
//    "   gl_FragColor = color;\n"
//    "}\n"
//};
//
//static const char* combineFragSource = {
//    "uniform sampler2D sceneTex;\n"
//    "uniform sampler2D blurTex;\n"
//    "uniform sampler2D depthTex;\n"
//    "uniform float focalDistance;\n"
//    "uniform float focalRange;\n"
//
//    "float getBlurFromLinearDepth(vec2 uv)\n"
//    "{\n"
//    "   float z = texture2D(depthTex, uv).x;\n"
//    "   z = 2.0 * 10001.0 / (10001.0 - z * 9999.0) - 1.0;\n"  // Considering the default znear/zfar
//    "   return clamp((z - focalDistance)/focalRange, 0.0, 1.0);\n"
//    "}\n"
//
//    "void main(void)\n"
//    "{\n"
//    "   vec2 uv = gl_TexCoord[0].st;\n"
//    "   vec4 fullColor = texture2D(sceneTex, uv);\n"
//    "   vec4 blurColor = texture2D(blurTex, uv);\n"
//    "   float blurValue = getBlurFromLinearDepth(uv);\n"
//    "   gl_FragColor = fullColor + blurValue * (blurColor - fullColor);\n"
//    "}\n"
//};
//
////Relevant
//osg::Node* createTexture() {
//    osg::ref_ptr<osg::Image> image = osgDB::readImageFile("Images/lz.rgb");
//    osg::ref_ptr<osg::Texture2D> text = new osg::Texture2D;
//    text->setImage(image.get());
//
//    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
//    vertices->push_back(osg::Vec3(-0.5f, 0.0f, -0.5f));
//    vertices->push_back(osg::Vec3(0.5f, 0.0f, -0.5f));
//    vertices->push_back(osg::Vec3(0.5f, 0.0f, 0.5f));
//    vertices->push_back(osg::Vec3(-0.5f, 0.0f, 0.5f));
//    osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array;
//    normals->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));
//    osg::ref_ptr<osg::Vec2Array> texcoords = new osg::Vec2Array;
//    texcoords->push_back(osg::Vec2(0.0f, 0.0f));
//    texcoords->push_back(osg::Vec2(0.0f, 1.0f));
//    texcoords->push_back(osg::Vec2(1.0f, 1.0f));
//    texcoords->push_back(osg::Vec2(1.0f, 0.0f));
//
//    osg::ref_ptr<osg::Geometry> quad = new osg::Geometry;
//    quad->setVertexArray(vertices.get());
//    quad->setNormalArray(normals.get());
//    quad->setNormalBinding(osg::Geometry::BIND_OVERALL);
//    quad->setTexCoordArray(0, texcoords.get());
//    quad->addPrimitiveSet(new osg::DrawArrays(GL_QUADS, 0, 4));
//
//    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
//    geode->addDrawable(quad.get());
//    geode->getOrCreateStateSet()->setTextureAttributeAndModes(0, text.get());
//    return geode.release();
//}
////osg::ref_ptr<osg::Node> model = osgDB::readNodeFile("lz.osg");
////osg::ref_ptr<osg::Node> sub_model = osgDB::readNodeFile("glider.osg");
//
////int tex_width = 1024, tex_height = 1024;
////osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
////texture->setTextureSize(tex_width, tex_height);
/////*texture->setInternalFormat(GL_RGBA);
////texture->setFilter(osg::Texture2D::MIN_FILTER, osg::Texture2D::LINEAR);
////texture->setFilter(osg::Texture2D::MAG_FILTER, osg::Texture2D::LINEAR);*///////FindTextureVisitor ftv(texture.get());
////if (model.valid()) model->accept(ftv);//////osg::ref_ptr<osg::Camera> camera = new osg::Camera;
////camera->setViewport(0, 0, tex_width, tex_height);
////camera->setClearColor(osg::Vec4(1.0f, 1.0f, 1.0f, 0.0f));
////camera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);////camera->setRenderOrder(osg::Camera::PRE_RENDER);
////camera->setRenderTargetImplementation(osg::Camera::FRAME_BUFFER_OBJECT);
////camera->attach(osg::Camera::COLOR_BUFFER, texture.get());////camera->setReferenceFrame(osg::Camera::ABSOLUTE_RF);
////camera->addChild(sub_model.get());//////osg::ref_ptr<osg::Group> root = new osg::Group;
////root->addChild(model.get());
////root->addChild( camera.get() );//////osgViewer::Viewer viewer;
////viewer.setSceneData(root.get());
////viewer.setCameraManipulator(new osgGA::TrackballManipulator);//////while (!viewer.done())
////{
////    viewer.frame();
////}
////return 0;
//
////Relevant
//class FindTextureVisitor : public osg::NodeVisitor
//{
//public:
//    osg::ref_ptr<osg::Texture> _texture;
//
//    FindTextureVisitor(osg::Texture* tex) : _texture(tex)
//    {
//        setTraversalMode(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN);
//    }
//    virtual void apply(osg::Node& node)
//    {
//        //node.getOrCreateStateSet()->setTextureAttribute(0, _texture.get());
//        replaceTexture(node.getStateSet());
//        traverse(node);
//    }
//    virtual void apply(osg::Geode& geode) 
//    {
//        /*geode.getOrCreateStateSet()->setTextureAttribute(0, _texture.get());
//        for (int i = 0; i < geode.getNumDrawables(); i++)
//        {
//            geode.getDrawable(i)->getOrCreateStateSet()->setTextureAttribute(0, _texture);
//        }*/
//        replaceTexture(geode.getStateSet());
//        for (unsigned int i = 0; i < geode.getNumDrawables(); ++i)
//        {
//            replaceTexture(geode.getDrawable(i)->getStateSet());
//        }
//        traverse(geode);
//    }
//    void replaceTexture(osg::StateSet* ss)
//    {
//        if (ss)
//        {
//            osg::Texture* oldTexture = dynamic_cast<osg::Texture*>(
//                ss->getTextureAttribute(0, osg::StateAttribute::TEXTURE)
//                );
//            if (oldTexture) ss->setTextureAttribute(0, _texture.get());
//        }
//    }
//};
//
//
//osg::Camera* createAnotherHUDCamera(double left, double right, double bottom, double top)
//{
//    osg::ref_ptr<osg::Camera> camera = new osg::Camera;
//    camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
//    camera->setClearMask(GL_DEPTH_BUFFER_BIT);
//    camera->setRenderOrder(osg::Camera::POST_RENDER);
//    camera->setAllowEventFocus(false);
//    camera->setProjectionMatrix(osg::Matrix::ortho2D(left, right, bottom, top));
//    camera->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
//    return camera.release();
//}
//
//osg::Geode* createScreenQuad(float width, float height, float scale)
//{
//    osg::Geometry* geom = osg::createTexturedQuadGeometry(
//        osg::Vec3(), osg::Vec3(width, 0.0f, 0.0f), osg::Vec3(0.0f, height, 0.0f),
//        0.0f, 0.0f, width * scale, height * scale);
//    osg::ref_ptr<osg::Geode> quad = new osg::Geode;
//    quad->addDrawable(geom);
//
//    int values = osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED;
//    quad->getOrCreateStateSet()->setAttribute(
//        new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::FILL), values);
//    quad->getOrCreateStateSet()->setMode(GL_LIGHTING, values);
//    return quad.release();
//}
//
////Create a Rendering-to-texture camera
//osg::Camera* createRTTCamera(osg::Camera::BufferComponent buffer, osg::Texture* tex, bool isAbsolute)
//{
//    osg::ref_ptr<osg::Camera> camera = new osg::Camera;
//    camera->setClearColor(osg::Vec4());
//    camera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    camera->setRenderTargetImplementation(osg::Camera::FRAME_BUFFER_OBJECT);
//    camera->setRenderOrder(osg::Camera::PRE_RENDER);
//    if (tex)
//    {
//        tex->setFilter(osg::Texture2D::MIN_FILTER, osg::Texture2D::LINEAR);
//        tex->setFilter(osg::Texture2D::MAG_FILTER, osg::Texture2D::LINEAR);
//        camera->setViewport(0, 0, tex->getTextureWidth(), tex->getTextureHeight());
//        camera->attach(buffer, tex);
//    }
//
//    if (isAbsolute)
//    {
//        camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
//        camera->setProjectionMatrix(osg::Matrix::ortho2D(0.0, 1.0, 0.0, 1.0));
//        camera->setViewMatrix(osg::Matrix::identity());
//        camera->addChild(createScreenQuad(1.0f, 1.0f, 2.0f));
//    }
//    return camera.release();
//}
//
////Useless for now
//typedef std::pair<osg::Camera*, osg::Texture*> RTTPair;
//
//RTTPair createColorInput(osg::Node* scene)
//{
//    osg::ref_ptr<osg::Texture2D> texture2D = new osg::Texture2D;
//    texture2D->setTextureSize(1024, 1024);
//    texture2D->setInternalFormat(GL_RGBA);
//
//    osg::ref_ptr<osg::Camera> camera = createRTTCamera(osg::Camera::COLOR_BUFFER, texture2D.get(), true);
//    camera->addChild(scene);
//    return RTTPair(camera, texture2D);
//}
//
//RTTPair createDepthInput(osg::Node* scene)
//{
//    osg::ref_ptr<osg::Texture2D> texture2D = new osg::Texture2D;
//    texture2D->setTextureSize(1024, 1024);
//    texture2D->setInternalFormat(GL_DEPTH_COMPONENT24);
//    texture2D->setSourceFormat(GL_DEPTH_COMPONENT);
//    texture2D->setSourceType(GL_FLOAT);
//
//    osg::ref_ptr<osg::Camera> camera = createRTTCamera(osg::Camera::DEPTH_BUFFER, texture2D.get(), true);
//    camera->addChild(scene);
//    return RTTPair(camera, texture2D);
//}
//
//RTTPair createBlurPass(osg::Texture* inputTex, const osg::Vec2& dir)
//{
//    osg::ref_ptr<osg::Texture2D> tex2D = new osg::Texture2D;
//    tex2D->setTextureSize(1024, 1024);
//    tex2D->setInternalFormat(GL_RGBA);
//    osg::ref_ptr<osg::Camera> camera = createRTTCamera(
//        osg::Camera::COLOR_BUFFER, tex2D.get(), true);
//
//    osg::ref_ptr<osg::Program> blurProg = new osg::Program;
//    blurProg->addShader(new osg::Shader(osg::Shader::VERTEX, vertSource));
//    blurProg->addShader(new osg::Shader(osg::Shader::FRAGMENT, blurFragSource));
//
//    osg::StateSet* ss = camera->getOrCreateStateSet();
//    ss->setTextureAttributeAndModes(0, inputTex);
//    ss->setAttributeAndModes(blurProg.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
//    ss->addUniform(new osg::Uniform("sceneTex", 0));
//    ss->addUniform(new osg::Uniform("blurDir", dir));
//    return RTTPair(camera.release(), tex2D.get());
//}
//
//static const char* waterVert = {
//    "uniform float osg_FrameTime;\n"
//    "varying vec4 projCoords;\n"
//    "varying vec3 lightDir, eyeDir;\n"
//    "varying vec2 flowCoords, rippleCoords;\n"
//
//    "void main()\n"
//    "{\n"
//    "   vec3 T = vec3(0.0, 1.0, 0.0);\n"
//    "   vec3 N = vec3(0.0, 0.0, 1.0);\n"
//    "   vec3 B = vec3(1.0, 0.0, 0.0);\n"
//    "   T = normalize(gl_NormalMatrix * T);\n"
//    "   B = normalize(gl_NormalMatrix * B);\n"
//    "   N = normalize(gl_NormalMatrix * N);\n"
//
//    "   mat3 TBNmat;\n"
//    "   TBNmat[0][0] = T[0]; TBNmat[1][0] = T[1]; TBNmat[2][0] = T[2];\n"
//    "   TBNmat[0][1] = B[0]; TBNmat[1][1] = B[1]; TBNmat[2][1] = B[2];\n"
//    "   TBNmat[0][2] = N[0]; TBNmat[1][2] = N[1]; TBNmat[2][2] = N[2];\n"
//
//    "   vec3 vertexInEye = vec3(gl_ModelViewMatrix * gl_Vertex);\n"
//    "   lightDir =  gl_LightSource[0].position.xyz - vertexInEye;\n"
//    "   lightDir = normalize(TBNmat * lightDir);\n"
//    "   eyeDir = normalize(TBNmat * (-vertexInEye));\n"
//
//    "   vec2 t1 = vec2(osg_FrameTime*0.02, osg_FrameTime*0.02);\n"
//    "   vec2 t2 = vec2(osg_FrameTime*0.05, osg_FrameTime*0.05);\n"
//    "   flowCoords = gl_MultiTexCoord0.xy * 5.0 + t1;\n"
//    "   rippleCoords = gl_MultiTexCoord0.xy * 10.0 + t2;\n"
//
//    "   gl_TexCoord[0] = gl_MultiTexCoord0;\n"
//    "   gl_Position = ftransform();\n"
//    "   projCoords = gl_Position;\n"
//    "}\n"
//};
//
//static const char* waterFrag = {
//    "uniform sampler2D defaultTex;\n"
//    "uniform sampler2D reflection;\n"
//    "uniform sampler2D refraction;\n"
//    "uniform sampler2D normalTex;\n"
//    "varying vec4 projCoords;\n"
//    "varying vec3 lightDir, eyeDir;\n"
//    "varying vec2 flowCoords, rippleCoords;\n"
//
//    "void main()\n"
//    "{\n"
//    "   vec2 rippleEffect = 0.02 * texture2D(refraction, rippleCoords * 0.1).xy;\n"
//    "   vec4 N = texture2D(normalTex, flowCoords + rippleEffect);\n"
//    "   N = N * 2.0 - vec4(1.0);\n"
//    "   N.a = 1.0; N = normalize(N);\n"
//
//    "   vec3 refVec = normalize(reflect(-lightDir, vec3(N) * 0.6));\n"
//    "   float refAngle = clamp(dot(eyeDir, refVec), 0.0, 1.0);\n"
//    "   vec4 specular = vec4(pow(refAngle, 40.0));\n"
//
//    "   vec2 dist = texture2D(refraction, flowCoords + rippleEffect).xy;\n"
//    "   dist = (dist * 2.0 - vec2(1.0)) * 0.1;\n"
//    "   vec2 uv = projCoords.xy / projCoords.w;\n"
//    "   uv = clamp((uv + 1.0) * 0.5 + dist, 0.0, 1.0);\n"
//
//    "   vec4 base = texture2D(defaultTex, uv);\n"
//    "   vec4 refl = texture2D(reflection, uv);\n"
//    "   gl_FragColor = mix(base, refl + specular, 0.6);\n"
//    "}\n"
//};
//
//osg::Texture2D* createTexture(const std::string& filename)
//{
//    osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
//    texture->setImage(osgDB::readImageFile(filename));
//    texture->setWrap(osg::Texture2D::WRAP_S, osg::Texture2D::REPEAT);
//    texture->setWrap(osg::Texture2D::WRAP_T, osg::Texture2D::REPEAT);
//    texture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR_MIPMAP_LINEAR);
//    texture->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);
//    return texture.release();
//}
//
//const unsigned int MDV_MAIN_CAMERA_MASK = 0x1;
//const unsigned int MDV_SONAR_CAMERA_MASK = 0x2;
//
////Actual Test
//class SceneSwitch : public osg::Switch
//{
//public:
//    SceneSwitch() : osg::Switch(), _count(0) {}
//    SceneSwitch(const SceneSwitch& copy,
//        const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY)
//        : osg::Switch(copy, copyop), _count(copy._count) {}
//    META_Node(osg, SceneSwitch);
//
//    virtual void traverse(osg::NodeVisitor& nv)
//    {
//        if (!((++_count) % 60))
//        {
//            setValue(0, !getValue(0));
//            setValue(1, !getValue(1));
//        }
//        osg::Switch::traverse(nv);
//    }
//
//protected:
//    unsigned int _count;
//};
//
////Actual Use
//osg::Camera* createSonarCamera(double left, double right,
//    double bottom, double top)
//{
//    osg::ref_ptr<osg::Camera> camera = new osg::Camera;
//    camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
//    camera->setClearMask(GL_DEPTH_BUFFER_BIT);
//    camera->setRenderOrder(osg::Camera::POST_RENDER);
//    camera->setAllowEventFocus(false);
//    camera->setProjectionMatrix(
//        osg::Matrix::ortho2D(left, right, bottom, top));
//    return camera.release();
//}
//
////Actual Use
//void createWater(osg::Group* root, osg::Node* scene)
//{
//    // The reversed node
//    float z = -20.0f;
//    osg::ref_ptr<osg::MatrixTransform> reverse = new osg::MatrixTransform;
//    reverse->preMult(osg::Matrix::translate(0.0f, 0.0f, -z) *
//        osg::Matrix::scale(1.0f, 1.0f, -1.0f) *
//        osg::Matrix::translate(0.0f, 0.0f, z));
//    reverse->addChild(scene);
//
//    osg::ref_ptr<osg::ClipPlane> clipPlane = new osg::ClipPlane;
//    clipPlane->setClipPlane(0.0, 0.0, -1.0, z);
//    clipPlane->setClipPlaneNum(0);
//
//    osg::ref_ptr<osg::ClipNode> clipNode = new osg::ClipNode;
//    clipNode->addClipPlane(clipPlane.get());
//    clipNode->addChild(reverse.get());
//
//    // The RTT camera
//    osg::ref_ptr<osg::Texture2D> tex2D = new osg::Texture2D;
//    tex2D->setTextureSize(10024, 10024);
//    tex2D->setInternalFormat(GL_RGBA);
//
//    osg::ref_ptr<osg::Camera> rttCamera = createRTTCamera(osg::Camera::COLOR_BUFFER, tex2D.get(), true);
//    rttCamera->addChild(clipNode.get());
//
//    // The water plane
//    const osg::Vec3& center = scene->getBound().center();
//    float planeSize = 20.0f * scene->getBound().radius();
//    osg::Vec3 planeCorner(center.x() - 0.5f * planeSize, center.y() - 0.5f * planeSize, z);
//    osg::ref_ptr<osg::Geometry> quad = osg::createTexturedQuadGeometry(
//        planeCorner, osg::Vec3(planeSize, 0.0f, 0.0f), osg::Vec3(0.0f, planeSize, 0.0f));
//
//    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
//    geode->addDrawable(quad.get());
//
//    osg::StateSet* ss = geode->getOrCreateStateSet();
//    ss->setTextureAttributeAndModes(0, tex2D.get());
//    ss->setTextureAttributeAndModes(1, createTexture("Images/skymap.jpg"));
//    ss->setTextureAttributeAndModes(2, createTexture("water_DUDV.jpg"));
//    ss->setTextureAttributeAndModes(3, createTexture("water_NM.jpg"));
//
//    osg::ref_ptr<osg::Program> program = new osg::Program;
//    program->addShader(new osg::Shader(osg::Shader::VERTEX, waterVert));
//    program->addShader(new osg::Shader(osg::Shader::FRAGMENT, waterFrag));
//    geode->getOrCreateStateSet()->setAttributeAndModes(program.get());
//    geode->getOrCreateStateSet()->addUniform(new osg::Uniform("reflection", 0));
//    geode->getOrCreateStateSet()->addUniform(new osg::Uniform("defaultTex", 1));
//    geode->getOrCreateStateSet()->addUniform(new osg::Uniform("refraction", 2));
//    geode->getOrCreateStateSet()->addUniform(new osg::Uniform("normalTex", 3));
//    // Build the scene graph
//    root->addChild(rttCamera.get());
//    root->addChild(geode.get());
//    root->addChild(scene);
//}
//
////New
//osg::Texture* createTexture2D(const std::string& fileName)
//{
//    osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
//    texture->setImage(osgDB::readImageFile(fileName));
//    texture->setWrap(osg::Texture::WRAP_S, osg::Texture::REPEAT);
//    texture->setWrap(osg::Texture::WRAP_T, osg::Texture::REPEAT);
//    texture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR);
//    texture->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);
//    return texture.release();
//}
//
//int mains()
//{
//    //Create Sea Surface
//    osg::ref_ptr<osg::Node> planeDude = osgDB::readNodeFile("cessna.osg");
//    osg::ref_ptr<osg::Group> waterScene = new osg::Group;
//    createWater(waterScene, planeDude);
//    osg::ref_ptr<osg::MatrixTransform> waterTrans = new osg::MatrixTransform;
//    waterTrans->addChild(waterScene);
//    waterTrans->setMatrix(osg::Matrix::translate(osg::Vec3(0, 0, 300)));
//
//    //Create Seabed Floor
//    TextureSeabed textureSeabed;
//    osg::ref_ptr<osg::Geode> seabed = new osg::Geode;
//    textureSeabed.createTextureSeabed(seabed);//////    Model model;
//    osg::ref_ptr<osg::Node> obj1 = model.createTempModel("dumptruck.osg", osg::Vec4(1.0f, 0.2f, 0.2f, 1.0f));
//    osg::ref_ptr<osg::Group> carGroup = new osg::Group;
//    for (int i = 0; i < 10; i++)
//    {
//        int min = -100, max = 100;
//        osg::Vec3 center(RAND(min, max), RAND(min, max), 10);
//        carGroup->addChild(model.createStaticNodes(center, obj1));
//    }
//
//    //Create Sky Box
//    osg::ref_ptr<osg::Geode> sphereGeode = new osg::Geode;
//    sphereGeode->addDrawable(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(), seabed->getBound().radius())));
//    osg::ref_ptr<Sky> skybox = new Sky;
//    skybox->getOrCreateStateSet()->setTextureAttributeAndModes(0, new osg::TexGen);
//    skybox->setEnvironmentMap(0, osgDB::readImageFile("Cubemap_snow/posx.jpg"),
//        osgDB::readImageFile("Cubemap_snow/negx.jpg"),
//        osgDB::readImageFile("Cubemap_snow/posy.jpg"),
//        osgDB::readImageFile("Cubemap_snow/negy.jpg"),
//        osgDB::readImageFile("Cubemap_snow/posz.jpg"),
//        osgDB::readImageFile("Cubemap_snow/negz.jpg"));
//    skybox->addChild(sphereGeode.get());
//
//    //Create Menu Text
//    ControlMenu menu;
//    osg::ref_ptr<osgText::Text> text = menu.createMenuText(20.0f, osg::Vec3(10.0f, 200.0f, 0.0f), menuText);
//    osg::ref_ptr<osg::Geode> textGeode = new osg::Geode;
//    textGeode->addDrawable(text.get());
//    osg::Camera* camera = createSonarCamera(0, 1024, 0, 768);
//    camera->addChild(textGeode.get());
//    camera->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
//
//    //Set Up Scene Node
//    osg::ref_ptr<osg::Group> scene = new  osg::Group;
//    scene->addChild(carGroup);
//    scene->addChild(skybox);
//    scene->addChild(seabed);
//    scene->addChild(camera);
//    scene->addChild(waterTrans);
//
//
//
//    //Setup RTT Camera
//    //osg::ref_ptr<osg::Texture2D> tex2D = new osg::Texture2D;
//    //tex2D->setTextureSize(1024, 1024);
//    //tex2D->setInternalFormat(GL_RGBA);
//
//    //osg::ref_ptr<osg::Camera> rttCamera = createRTTCamera(osg::Camera::COLOR_BUFFER, tex2D.get(), false);
//    //rttCamera->addChild(scene);
//
//    //osg::ref_ptr<osg::Camera> hudCamera = createAnotherHUDCamera(0, 1, 0, 1);
//    //hudCamera->addChild(createScreenQuad(1, 1, 1));
//
//    //osg::ref_ptr<osg::Program> program = new osg::Program;
//    //program->addShader(new osg::Shader(osg::Shader::VERTEX, vsSource));
//    //program->addShader(new osg::Shader(osg::Shader::FRAGMENT, fsSource));
//
//    //osg::StateSet* stateset = hudCamera->getOrCreateStateSet();
//    //stateset->setTextureAttributeAndModes(0, tex2D);
//    //stateset->setTextureAttributeAndModes(1, createTexture2D("noise_tex.jpg"));
//    //stateset->setAttributeAndModes(program.get());
//    //stateset->addUniform(new osg::Uniform("sceneTex", 0));
//    //stateset->addUniform(new osg::Uniform("noiseTex", 1));
//
//    //osg::ref_ptr<osg::Group> mdvSonar = new osg::Group;
//    //mdvSonar->addChild(rttCamera.get());
//    //mdvSonar->addChild(hudCamera.get());
//    //mdvSonar->addChild(scene.get());
//    
//    //Another test scene with switch node
//    //osg::ref_ptr<osg::Group> test = new osg::Group;
//    //test->addChild(carGroup);
//    //test->addChild(skybox);
//    //test->addChild(noseabed);
//    //osg::ref_ptr<SceneSwitch> root = new SceneSwitch;
//    //root->addChild(scene, true);
//    //root->addChild(test, false);
//
//    //Create View Trait
//    unsigned int width = 800, height = 600;
//    osg::GraphicsContext::WindowingSystemInterface* wsi = osg::GraphicsContext::getWindowingSystemInterface();
//    if (wsi) 
//        wsi->getScreenResolution( osg::GraphicsContext::ScreenIdentifier(0), width, height);
//    osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
//    traits->x = 0;
//    traits->y = 0;
//    traits->width = width;
//    traits->height = height;
//    traits->windowDecoration = false;
//    traits->doubleBuffer = true;
//    traits->sharedContext = 0;
//    osg::ref_ptr<osg::GraphicsContext> gc = osg::GraphicsContext::createGraphicsContext(traits.get());
//    int w_2 = width / 2, h_2 = height / 2;
//
//    //Create the first view
//    osg::ref_ptr<osgViewer::View> view1 = new osgViewer::View;
//    //view1->setUpViewInWindow(50, 50, 500, 500);
//    view1->getCamera()->setGraphicsContext(gc.get());
//    view1->getCamera()->setViewport(w_2, 0, w_2, height);
//    //Set Up GUIEventHandler
//    CameraMover* cm = new CameraMover(view1);
//    view1->addEventHandler(new osgViewer::WindowSizeHandler);
//    view1->addEventHandler(cm);
//    view1->setSceneData(scene.get());
//
//    //Set Up Camera position
//    const osg::BoundingSphere& bs = carGroup->getBound();
//    //const osg::BoundingSphere& bs = planeDude->getBound();
//    view1->getCamera()->setViewMatrixAsLookAt(bs.center() + osg::Vec3(0.0f, -(9 * bs.radius()), 100.0f), bs.center(), osg::Z_AXIS);
//    cm->md = view1->getCamera()->getViewMatrix();
//
//
//    //MDV Sonar View
//    osg::ref_ptr<osgViewer::View> view2 = new osgViewer::View;
//    //view2->setUpViewInWindow(50, 50, 500, 500);
//    view2->getCamera()->setGraphicsContext(gc.get());
//    view2->getCamera()->setViewport(0, 0 , w_2, height);
//    view2->addEventHandler(new osgViewer::WindowSizeHandler);
//    view2->addEventHandler(cm);
//    view2->setSceneData(scene.get());
//    view2->getCamera()->setCullMask(0x1);
//    //view2->getCamera()->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
//    //view2->getCamera()->setRenderOrder(osg::Camera::POST_RENDER);
//    //view2->getCamera()->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    //view2->getCamera()->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
//    view2->getCamera()->getOrCreateStateSet()->setAttributeAndModes(new osg::Depth(osg::Depth::LEQUAL, 1.0, 1.0)); //Remove the floor
//
//    osgViewer::CompositeViewer viewer;
//    viewer.addView(view1.get());
//    viewer.addView(view2.get());
//    while (!viewer.done())
//    {
//        view1->getCamera()->setViewMatrix(cm->md);
//        view2->getCamera()->setViewMatrix(cm->md);
//        viewer.frame();
//    }
//    return 0;
//}
//
////One aspect of the view is the vantage point(i.e., the eye or camera position) from which the scene will be viewed.
////Viewing parameters also include the focus point(also called the LOOKAT POINT or the direction in which the camera is pointed) and 
////the up direction(e.g., the camera may be held sideways or upside down).