#include <iostream>
#include <time.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <osgViewer/CompositeViewer>
#include <osg/AnimationPath>
#include <osg/Texture>
#include <osg/Camera>
#include <osgGA/GUIEventHandler>
#include <osgText/Text>
#include <osgUtil/LineSegmentIntersector>
#include <osg/PolygonMode>
#include <osgText/Font>
#include <osgViewer/View>

//First example
#include <osgDB/ReadFile>
#include <osgUtil/TangentSpaceGenerator>
#include <osgViewer/Viewer>
#include <osg/Program>
#include <osg/Texture2D>
#include <osg/ShapeDrawable>
#include <osg/Geode>

//Shadow Mask
#include <osg/MatrixTransform>
#include <osgDB/ReadFile>
#include <osgShadow/ShadowedScene>
#include <osgShadow/ViewDependentShadowMap>
#include <osgGA/TrackballManipulator>
#include <osgViewer/ViewerEventHandlers>
#include <osgViewer/Viewer>

//Practice Include
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osgViewer/CompositeViewer>

#include <osg/PolygonMode>
#include <osg/ShapeDrawable>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/MatrixTransform>
#include <osg/LightSource>
#include <osg/Texture2D>
#include <osg/Depth>
#include <osg/Material>
#include <osg/Camera>

#include <osgGA/TrackballManipulator>
#include <osgGA/GUIEventHandler>

#include <osgUtil/LineSegmentIntersector>

//Fading in and out
#include <osg/BlendFunc>
//#include <osg/Material>
#include <osg/Node>
#include <osgAnimation/EaseMotion>
#include <osgUtil/CullVisitor>

#include <osgUtil/TangentSpaceGenerator>

//Include for map designing
#include "Sky.h"

//Include for water effect
#include <osg/TexGen>
#include <osg/ShapeDrawable>
#include <osg/Geometry>
#include <osg/ClipNode>
#include <osg/MatrixTransform>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

//Include for sonar camera
#include <osg/Camera>
#include <osg/MatrixTransform>
#include <osgDB/ReadFile>
#include <osgGA/OrbitManipulator>
#include <osgViewer/Viewer>

#include <osgViewer/ViewerEventHandlers>
#include <math.h>
#include "CameraMover.h"

#include <osg/Switch>
#include "TextureSeabed.h"
#include "FadeInOutCallback.h"

//Include for text
#include <osg/Camera>
#include <osgDB/ReadFile>
#include <osgText/Font>
#include <osgText/Text>
#include <osgViewer/Viewer>
#include "ControlMenu.h"

//Include for trait
#include "SplitScreenTrait.h"

#include <osg/Projection>
#include "Model.h"

//Include for Making your node always face the screen
#include <osg/MatrixTransform>
#include <osgDB/ReadFile>
#include <osgUtil/CullVisitor>
#include <osgViewer/Viewer>

const unsigned int MAIN_CAMERA_MASK = 0x1;
const unsigned int RADAR_CAMERA_MASK = 0x2;
#define RAND(min, max) ((min) + (float)rand()/(RAND_MAX+1) * ((max)-(min)))

osg::Camera* createHudCamera(double left, double right, double bottom, double top) 
{
	osg::ref_ptr<osg::Camera> camera = new osg::Camera;
	camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
	camera->setClearMask(GL_DEPTH_BUFFER_BIT);
	camera->setRenderOrder(osg::Camera::POST_RENDER);
	camera->setAllowEventFocus(false);
	camera->setProjectionMatrixAsOrtho2D(left, right, bottom, top);
	camera->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	return camera.release();
}

osg::Geode* createScreenSquare(float width, float height, float scale)
{
	osg::Geometry* geom = osg::createTexturedQuadGeometry(osg::Vec3(), osg::Vec3(width, 0, 0), osg::Vec3(0, height, 0),
		0, 0, width * scale, height * scale);
	osg::ref_ptr<osg::Geode> quad = new osg::Geode;
	quad->addDrawable(geom);

	int values = osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED;
	quad->getOrCreateStateSet()->setAttribute(new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK,
		osg::PolygonMode::FILL), values);
	quad->getOrCreateStateSet()->setMode(GL_LIGHTING, values);
	return quad.release();
}

osg::Camera* createRenderToTextureCamera(osg::Camera::BufferComponent buffer, osg::Texture* tex, bool isAbsolute)
{
	osg::ref_ptr<osg::Camera> camera = new osg::Camera;
	camera->setClearColor(osg::Vec4());
	camera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	camera->setRenderTargetImplementation(osg::Camera::FRAME_BUFFER_OBJECT);
	camera->setRenderOrder(osg::Camera::PRE_RENDER);
	if (tex)
	{
		tex->setFilter(osg::Texture2D::MIN_FILTER, osg::Texture2D::LINEAR);
		tex->setFilter(osg::Texture2D::MAG_FILTER, osg::Texture2D::LINEAR);
		camera->setViewport(0, 0, tex->getTextureWidth(), tex->getTextureHeight());
		camera->attach(buffer, tex); 
	}
	if (isAbsolute)
	{
		camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
		camera->setProjectionMatrix(osg::Matrix::ortho2D(0.0, 1.0, 0.0, 1.0));
		camera->setViewMatrix(osg::Matrix::identity());
		camera->addChild(createScreenSquare(1.0f, 1.0f, 0.0f));
	}
	return camera.release();
}

osg::Texture* createTexture2DS(const std::string& fileName)
{
	osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
	texture->setImage(osgDB::readImageFile(fileName));
	texture->setWrap(osg::Texture::WRAP_S, osg::Texture::REPEAT);
	texture->setWrap(osg::Texture::WRAP_T, osg::Texture::REPEAT);
	texture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR);
	texture->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);
	return texture.release();
}

static const char* vsSource =
{
	"void main(void)\n"
	"{\n"
	"   gl_Position = ftransform();\n"
	"   gl_TexCoord[0] = gl_MultiTexCoord0;\n"
	"}\n"
};

static const char* fsSource = 
{
	"uniform sampler2D sceneTex;\n"
	"uniform sampler2D noiseTex;\n"
	"uniform float osg_FrameTime;\n"
	"void main(void)\n"
	"{\n"
	"   float factor = osg_FrameTime * 100.0;\n"
	"   vec2 uv = vec2(0.4*sin(factor), 0.4*cos(factor));\n"
	"   vec3 n = texture2D(noiseTex, (gl_TexCoord[0].st*3.5) + uv).rgb;\n"

	"   vec3 c = texture2D(sceneTex, gl_TexCoord[0].st + (n.xy*0.005)).rgb;\n"
	"   float lum = dot(vec3(0.30, 0.59, 0.11), c);\n"
	"   if (lum < 0.2) c *= 4.0;\n"

	"   vec3 finalColor = (c + (n*0.2)) * vec3(0.5, 0.5, 0.2);\n"
	"   gl_FragColor = vec4(finalColor, 1.0);\n"
	"}\n"
};

class ComputeTangentBinormalVisitor : public osg::NodeVisitor
{
public:
	void apply(osg::Node& node) { traverse(node); }

	void apply(osg::Geode& node)
	{
		for (unsigned int i = 0; i < node.getNumDrawables(); i++)
		{
			osg::Geometry* geom = dynamic_cast<osg::Geometry*>(node.getDrawable(i));
			if (geom)
			{
				osg::ref_ptr<osgUtil::TangentSpaceGenerator> tsg = new osgUtil::TangentSpaceGenerator;
				tsg->generate(geom);
				geom->setVertexAttribArray(6, tsg->getTangentArray());
				geom->setVertexAttribBinding(6, osg::Geometry::BIND_PER_VERTEX);
				geom->setVertexAttribArray(7, tsg->getBinormalArray());
				geom->setVertexAttribBinding(7, osg::Geometry::BIND_PER_VERTEX);
			}
		}
		traverse(node);
	}
};

unsigned int rcvShadowMask = 0x1;
unsigned int castShadowMask = 0x2;

osg::Geode* createScreenQuad(float width, float height, float scale)
{
	osg::Geometry* geom = osg::createTexturedQuadGeometry(
		osg::Vec3(), osg::Vec3(width, 0.0f, 0.0f), osg::Vec3(0.0f, height, 0.0f),
		0.0f, 0.0f, width * scale, height * scale);
	osg::ref_ptr<osg::Geode> quad = new osg::Geode;
	quad->addDrawable(geom);

	int values = osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED;
	quad->getOrCreateStateSet()->setAttribute(
		new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::FILL), values);
	quad->getOrCreateStateSet()->setMode(GL_LIGHTING, values);
	return quad.release();
}

osg::Camera* createRTTCamera(osg::Camera::BufferComponent buffer, osg::Texture* tex, bool isAbsolute)
{
	osg::ref_ptr<osg::Camera> camera = new osg::Camera;
	camera->setClearColor(osg::Vec4());
	camera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	camera->setRenderTargetImplementation(osg::Camera::FRAME_BUFFER_OBJECT);
	camera->setRenderOrder(osg::Camera::PRE_RENDER);
	if (tex)
	{
		tex->setFilter(osg::Texture2D::MIN_FILTER, osg::Texture2D::LINEAR);
		tex->setFilter(osg::Texture2D::MAG_FILTER, osg::Texture2D::LINEAR);
		camera->setViewport(0, 0, tex->getTextureWidth(), tex->getTextureHeight());
		camera->attach(buffer, tex);
	}

	if (isAbsolute)
	{
		camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
		camera->setProjectionMatrix(osg::Matrix::ortho2D(0.0, 1.0, 0.0, 1.0));
		camera->setViewMatrix(osg::Matrix::identity());
		camera->addChild(createScreenQuad(1.0f, 1.0f, 1.0f));
	}
	return camera.release();
}

osg::Camera* createAnotherHUDCamera(double left, double right, double bottom, double top)
{
	osg::ref_ptr<osg::Camera> camera = new osg::Camera;
	camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
	camera->setClearMask(GL_DEPTH_BUFFER_BIT);
	camera->setRenderOrder(osg::Camera::POST_RENDER);
	camera->setAllowEventFocus(false);
	camera->setProjectionMatrix(osg::Matrix::ortho2D(left, right, bottom, top));
	camera->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	return camera.release();
}

//static const char* modelVSSource = {
// "varying vec3 position, range, phi;\n"
// "void main()\n"
// "{\n"
// " position = gl_ModelViewMatrix * gl_Vertex; \n"
// " range = length(position);\n"
// " phi = acos(position.x/range);\n"
// " gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;\n"
// "}\n"
//};

static const char* modelVSSource = {
 "varying vec3 lightDir, normal;\n"
 "void main()\n"
 "{\n"
 " lightDir = normalize(vec3(gl_LightSource[0].position - gl_ModelViewMatrix * gl_Vertex)); \n"
 " normal = normalize(gl_NormalMatrix * gl_Normal);\n"
 " gl_Position = ftransform();\n"
 "}\n"
};
static const char* modelFSSource = {
 "uniform vec4 color1;\n"
 "uniform vec4 color2;\n"
 "uniform vec4 color3;\n"
 "uniform vec4 color4;\n"
 "varying vec3 normal;\n"
 "void main()\n"
 "{\n"
 " float intensity = dot(vec3(gl_LightSource[0].position), normal); \n"
 " if (intensity > 0.95) gl_FragColor = color1;\n"
 " else if (intensity > 0.5) gl_FragColor = color2;\n"
 " else if (intensity > 0.25) gl_FragColor = color3;\n"
 " else gl_FragColor = color4;\n"
 "}\n"
};

class BillboardCallback : public osg::NodeCallback
{
public:
	BillboardCallback(osg::MatrixTransform* billboard) : _billboardNode(billboard) {}
	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
	{
		osgUtil::CullVisitor* cv =
			dynamic_cast<osgUtil::CullVisitor*>(nv);
		if (_billboardNode.valid() && cv)
		{
			osg::Vec3d translation, scale;
			osg::Quat rotation, so;
			cv->getModelViewMatrix()->decompose(translation, rotation,
				scale, so);
			osg::Matrixd matrix(rotation.inverse());
			_billboardNode->setMatrix(matrix);
		}
		traverse(node, nv);
	}
protected:
	osg::observer_ptr<osg::MatrixTransform> _billboardNode;
};

osg::ref_ptr<osg::Program> createProgram(const char* vertexShaderSource, const char* fragmentShaderSource)
{
	osg::ref_ptr<osg::Program> program = new osg::Program;
	program->addShader(new osg::Shader(osg::Shader::VERTEX, vertexShaderSource));
	program->addShader(new osg::Shader(osg::Shader::FRAGMENT, fragmentShaderSource));
	return program;
}

void applyStateSet(osg::StateSet* stateset, osg::Program* program)
{
	stateset->setAttributeAndModes(program);
	stateset->addUniform(new osg::Uniform("color1", osg::Vec4(1.0f, 2.5f, 0.5f, 1.0f)));
	stateset->addUniform(new osg::Uniform("color2", osg::Vec4(0.5f, 3.2f, 0.2f, 1.0f)));
	stateset->addUniform(new osg::Uniform("color3", osg::Vec4(0.2f, 4.1f, 0.1f, 1.0f)));
	stateset->addUniform(new osg::Uniform("color4", osg::Vec4(1.0,  1.0,  1.0,  1.0)));
}

osg::Camera* createTheRTTCamera(osg::Texture2D* sceneTex)
{
	osg::ref_ptr<osg::Camera> rttCamera = new osg::Camera;
	rttCamera->setClearColor(osg::Vec4());
	rttCamera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	rttCamera->setRenderTargetImplementation(osg::Camera::FRAME_BUFFER_OBJECT);
	rttCamera->setRenderOrder(osg::Camera::PRE_RENDER);
	rttCamera->setViewport(0, 0, sceneTex->getTextureWidth(), sceneTex->getTextureHeight());
	rttCamera->attach(osg::Camera::COLOR_BUFFER, sceneTex);
	return rttCamera.release();
}

osg::Camera* createTheHUDCamera()
{
	osg::ref_ptr<osg::Camera> hudCamera = new osg::Camera;
	hudCamera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
	hudCamera->setClearMask(GL_DEPTH_BUFFER_BIT);
	hudCamera->setRenderOrder(osg::Camera::POST_RENDER);
	hudCamera->setAllowEventFocus(false);
	hudCamera->setProjectionMatrix(osg::Matrix::ortho2D(0, 1, 0, 1));
	hudCamera->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	return hudCamera.release();
}

int main()
{
	// Create shader object for model
	osg::ref_ptr<osg::Program> modelProgram = createProgram(modelVSSource, modelFSSource);

	//Create Seabed Floor
	TextureSeabed textureSeabed;
	osg::ref_ptr<osg::Geode> seabed = new osg::Geode;
	textureSeabed.createTextureSeabed(seabed);
	//Uncomment later
	//osg::StateSet* modelStateSet = seabed->getOrCreateStateSet();
	//modelStateSet->setAttributeAndModes(modelProgram);
	//modelStateSet->addUniform(new osg::Uniform("color1", osg::Vec4(1.0f, 2.5f, 0.5f, 1.0f)));
	//modelStateSet->addUniform(new osg::Uniform("color2", osg::Vec4(0.5f, 3.2f, 0.2f, 1.0f)));
	//modelStateSet->addUniform(new osg::Uniform("color3", osg::Vec4(0.2f, 4.1f, 0.1f, 1.0f)));
	//modelStateSet->addUniform(new osg::Uniform("color4", osg::Vec4(0.1f, 5.05f, 0.05f, 1.0f)));

	//Create Model
	Model model;
	osg::ref_ptr<osg::Node> obj1 = model.createTempModel("dumptruck.osg", osg::Vec4(1.0f, 0.2f, 0.2f, 1.0f));
	osg::ref_ptr<osg::Node> obj2 = model.createTempModel("cessna.osg", osg::Vec4());

	osg::ref_ptr<osg::Group> carGroup = new osg::Group;
	for (int i = 0; i < 10; i++)
	{
		int min = -100, max = 100;
		osg::Vec3 center(RAND(min, max), RAND(min, max), 10);
		carGroup->addChild(model.createStaticNodes(center, obj1));
	}
	osg::ref_ptr<osg::Group> planeGroup = new osg::Group;
	for (int i = 0; i < 10; i++)
	{
		int min = -100, max = 100;
		osg::Vec3 center(RAND(min, max), RAND(min, max), 10);
		carGroup->addChild(model.createStaticNodes(center, obj2));
	}

	//Create another group of object for MDV Sonar
	osg::ref_ptr<osg::Group> mdvCarGroup = new osg::Group;
	mdvCarGroup->addChild(carGroup);
	mdvCarGroup->addChild(planeGroup);
	applyStateSet(mdvCarGroup->getOrCreateStateSet(), modelProgram);

	//Create Sky Box
	osg::ref_ptr<osg::Geode> sphereGeode = new osg::Geode;
	sphereGeode->addDrawable(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(), seabed->getBound().radius())));
	osg::ref_ptr<Sky> skybox = new Sky;
	skybox->getOrCreateStateSet()->setTextureAttributeAndModes(0, new osg::TexGen);
	skybox->setEnvironmentMap(0, osgDB::readImageFile("Cubemap_snow/posx.jpg"),
		osgDB::readImageFile("Cubemap_snow/negx.jpg"),
		osgDB::readImageFile("Cubemap_snow/posy.jpg"),
		osgDB::readImageFile("Cubemap_snow/negy.jpg"),
		osgDB::readImageFile("Cubemap_snow/posz.jpg"),
		osgDB::readImageFile("Cubemap_snow/negz.jpg"));
	skybox->addChild(sphereGeode.get());

	//Set Up Scene Node
	osg::ref_ptr<osg::Group> scene = new  osg::Group;
	scene->addChild(carGroup);
	scene->addChild(skybox);
	scene->addChild(seabed);

	//Setup RTT Camera
    osg::ref_ptr<osg::Texture2D> sceneTex = new osg::Texture2D;
	sceneTex->setTextureSize(1024, 1024);
	sceneTex->setInternalFormat(GL_RGBA);
	sceneTex->setFilter(osg::Texture2D::MIN_FILTER, osg::Texture2D::LINEAR);
	sceneTex->setFilter(osg::Texture2D::MAG_FILTER, osg::Texture2D::LINEAR);

	//Maybe delete later
	osg::ref_ptr<osg::Texture2D> depthBuffer = new osg::Texture2D;
	depthBuffer->setTextureSize(1024, 1024);
	depthBuffer->setInternalFormat(GL_DEPTH_COMPONENT);
	depthBuffer->setFilter(osg::Texture2D::MIN_FILTER, osg::Texture2D::LINEAR);
	depthBuffer->setFilter(osg::Texture2D::MAG_FILTER, osg::Texture2D::LINEAR);

	osg::ref_ptr<osg::Camera> rttCamera = createTheRTTCamera(sceneTex);
	rttCamera->addChild(mdvCarGroup);

	//Setup HUD Camera
	osg::ref_ptr<osg::Camera> hudCamera = createTheHUDCamera();

	float width = 1, height = 1, scale = 1;
	osg::Geometry* geom = osg::createTexturedQuadGeometry(osg::Vec3(), osg::Vec3(width, 0.0f, 0.0f), osg::Vec3(0.0f, height, 0.0f), 0.0f, 0.0f, width * scale, height * scale);
	osg::ref_ptr<osg::Geode> quad = new osg::Geode;
	quad->addDrawable(geom);

	int values = osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED;
	quad->getOrCreateStateSet()->setAttribute(
		new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::FILL), values);
	quad->getOrCreateStateSet()->setMode(GL_LIGHTING, values);
	hudCamera->addChild(quad);

	osg::ref_ptr<osg::Program> cameraProgram = createProgram(vsSource, fsSource);

	osg::ref_ptr<osg::Texture2D> noiseTex = new osg::Texture2D;
	noiseTex->setImage(osgDB::readImageFile("noise_tex.jpg"));
	noiseTex->setWrap(osg::Texture::WRAP_S, osg::Texture::REPEAT);
	noiseTex->setWrap(osg::Texture::WRAP_T, osg::Texture::REPEAT);
	noiseTex->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR);
	noiseTex->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);

	osg::StateSet* stateset = hudCamera->getOrCreateStateSet();
	stateset->setTextureAttributeAndModes(0, sceneTex);
	stateset->setTextureAttributeAndModes(1, noiseTex);
	stateset->setAttributeAndModes(cameraProgram.get());
	stateset->addUniform(new osg::Uniform("sceneTex", 0));
	stateset->addUniform(new osg::Uniform("noiseTex", 1));

    osg::ref_ptr<osg::Group> mdvSonar = new osg::Group;
    mdvSonar->addChild(rttCamera.get());
    mdvSonar->addChild(hudCamera.get());
    //mdvSonar->addChild(scene.get());

	osg::ref_ptr<osg::Group> root = new osg::Group;
	root->addChild(scene);

	osg::ref_ptr<osgViewer::View> view = new osgViewer::View;
	view->setUpViewInWindow(50, 50, 500, 500);
	//view->setSceneData(root);

	osg::ref_ptr<osgViewer::View> view2 = new osgViewer::View;
	view2->setUpViewInWindow(50, 50, 500, 500);

	CameraMover* cm = new CameraMover(view);
	view->addEventHandler(new osgViewer::WindowSizeHandler);
	view->addEventHandler(cm);
	view->setSceneData(mdvSonar);
	const osg::BoundingSphere& bs = carGroup->getBound();
	view->getCamera()->setViewMatrixAsLookAt(bs.center() + osg::Vec3(0.0f, -(9 * bs.radius()), 100.0f), bs.center(), osg::Z_AXIS);
	cm->md = view->getCamera()->getViewMatrix();

	view2->addEventHandler(new osgViewer::WindowSizeHandler);
	view2->addEventHandler(cm);
	view2->setSceneData(root);

	osgViewer::CompositeViewer viewer;
	viewer.addView(view.get());
	viewer.addView(view2.get());

	while (!viewer.done())
	{
		view->getCamera()->setViewMatrix(cm->md);
		view2->getCamera()->setViewMatrix(cm->md);
		viewer.frame();
	}
}

////First success test
//// Create shader object for model
//osg::ref_ptr<osg::Program> modelProgram = new osg::Program;
//modelProgram->addShader(new osg::Shader(osg::Shader::VERTEX, modelVSSource));
//modelProgram->addShader(new osg::Shader(osg::Shader::FRAGMENT, modelFSSource));
////osg::ref_ptr<osg::Program> modelProgram = createProgram(modelVSSource, modelFSSource);
//
////Create Seabed Floor
//TextureSeabed textureSeabed;
//osg::ref_ptr<osg::Geode> seabed = new osg::Geode;
//textureSeabed.createTextureSeabed(seabed);
////Uncomment later
////osg::StateSet* modelStateSet = seabed->getOrCreateStateSet();
////modelStateSet->setAttributeAndModes(modelProgram);
////modelStateSet->addUniform(new osg::Uniform("color1", osg::Vec4(1.0f, 2.5f, 0.5f, 1.0f)));
////modelStateSet->addUniform(new osg::Uniform("color2", osg::Vec4(0.5f, 3.2f, 0.2f, 1.0f)));
////modelStateSet->addUniform(new osg::Uniform("color3", osg::Vec4(0.2f, 4.1f, 0.1f, 1.0f)));
////modelStateSet->addUniform(new osg::Uniform("color4", osg::Vec4(0.1f, 5.05f, 0.05f, 1.0f)));
//
////Create Model
//Model model;
//osg::ref_ptr<osg::Node> obj1 = model.createTempModel("dumptruck.osg", osg::Vec4(1.0f, 0.2f, 0.2f, 1.0f));
//osg::ref_ptr<osg::Node> obj2 = model.createTempModel("cessna.osg", osg::Vec4());
//
//osg::ref_ptr<osg::Group> carGroup = new osg::Group;
//for (int i = 0; i < 10; i++)
//{
//	int min = -100, max = 100;
//	osg::Vec3 center(RAND(min, max), RAND(min, max), 10);
//	carGroup->addChild(model.createStaticNodes(center, obj2));
//}
//
////Create another group of object for MDV Sonar
//osg::ref_ptr<osg::Group> mdvCarGroup = new osg::Group;
//mdvCarGroup->addChild(carGroup);
//osg::StateSet* carStateSet = mdvCarGroup->getOrCreateStateSet();
//carStateSet->setAttributeAndModes(modelProgram);
//carStateSet->addUniform(new osg::Uniform("color1", osg::Vec4(1.0f, 2.5f, 0.5f, 1.0f)));
//carStateSet->addUniform(new osg::Uniform("color2", osg::Vec4(0.5f, 3.2f, 0.2f, 1.0f)));
//carStateSet->addUniform(new osg::Uniform("color3", osg::Vec4(0.2f, 4.1f, 0.1f, 1.0f)));
//carStateSet->addUniform(new osg::Uniform("color4", osg::Vec4(0.1f, 5.05f, 0.05f, 1.0f)));
//
////Create Sky Box
//osg::ref_ptr<osg::Geode> sphereGeode = new osg::Geode;
//sphereGeode->addDrawable(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(), seabed->getBound().radius())));
//osg::ref_ptr<Sky> skybox = new Sky;
//skybox->getOrCreateStateSet()->setTextureAttributeAndModes(0, new osg::TexGen);
//skybox->setEnvironmentMap(0, osgDB::readImageFile("Cubemap_snow/posx.jpg"),
//	osgDB::readImageFile("Cubemap_snow/negx.jpg"),
//	osgDB::readImageFile("Cubemap_snow/posy.jpg"),
//	osgDB::readImageFile("Cubemap_snow/negy.jpg"),
//	osgDB::readImageFile("Cubemap_snow/posz.jpg"),
//	osgDB::readImageFile("Cubemap_snow/negz.jpg"));
//skybox->addChild(sphereGeode.get());
//
////Set Up Scene Node
//osg::ref_ptr<osg::Group> scene = new  osg::Group;
//scene->addChild(carGroup);
//scene->addChild(skybox);
//scene->addChild(seabed);
//
////Setup RTT Camera
//osg::ref_ptr<osg::Texture2D> sceneTex = new osg::Texture2D;
//sceneTex->setTextureSize(1024, 1024);
//sceneTex->setInternalFormat(GL_RGBA);
//sceneTex->setFilter(osg::Texture2D::MIN_FILTER, osg::Texture2D::LINEAR);
//sceneTex->setFilter(osg::Texture2D::MAG_FILTER, osg::Texture2D::LINEAR);
//
////Maybe delete later
//osg::ref_ptr<osg::Texture2D> depthBuffer = new osg::Texture2D;
//depthBuffer->setTextureSize(1024, 1024);
//depthBuffer->setInternalFormat(GL_DEPTH_COMPONENT);
//depthBuffer->setFilter(osg::Texture2D::MIN_FILTER, osg::Texture2D::LINEAR);
//depthBuffer->setFilter(osg::Texture2D::MAG_FILTER, osg::Texture2D::LINEAR);
//
//osg::ref_ptr<osg::Camera> rttCamera = new osg::Camera;
//rttCamera->setClearColor(osg::Vec4());
//rttCamera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//rttCamera->setRenderTargetImplementation(osg::Camera::FRAME_BUFFER_OBJECT);
//rttCamera->setRenderOrder(osg::Camera::PRE_RENDER);
//rttCamera->setViewport(0, 0, sceneTex->getTextureWidth(), sceneTex->getTextureHeight());
//rttCamera->attach(osg::Camera::COLOR_BUFFER, sceneTex);
//rttCamera->addChild(mdvCarGroup);
//
//osg::ref_ptr<osg::Camera> m_rttCamera = new osg::Camera;
////m_rttCamera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
//m_rttCamera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//m_rttCamera->setViewport(0, 0, sceneTex->getTextureWidth(), sceneTex->getTextureHeight());
//m_rttCamera->setCullingMode(osg::CullSettings::VIEW_FRUSTUM_CULLING);
//m_rttCamera->setCullingActive(true);
//m_rttCamera->setRenderTargetImplementation(osg::Camera::PIXEL_BUFFER_RTT);
//m_rttCamera->setRenderOrder(osg::Camera::PRE_RENDER);
//m_rttCamera->attach(osg::Camera::DEPTH_BUFFER, sceneTex);
////m_rttCamera->attach(osg::Camera::DEPTH_BUFFER, depthBuffer);
////m_rttCamera->setViewMatrixAsLookAt(osg::Vec3(1, 0, -1), osg::Vec3(278.1f, 981.1f, -1.0f), osg::Vec3(0, 0, 1));
////m_rttCamera->setProjectionMatrixAsPerspective(30.0f, 500 / 500,1.0, 1000.0);
////m_rttCamera->setComputeNearFarMode(osg::CullSettings::DO_NOT_COMPUTE_NEAR_FAR);
//m_rttCamera->addChild(carGroup);
//
////osg::Vec3 eye = carGroup->getBound().center() + osg::Vec3(0.0f, 50, 100.0f);
////osg::Vec3 center = carGroup->getBound().center();
////osg::Vec3 up(0.0f, 1.0f, 1.0f);
////rttCamera->setViewMatrixAsLookAt(eye, center, up);
//
////Setup HUD Camera
//osg::ref_ptr<osg::Camera> hudCamera = new osg::Camera;
//hudCamera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
//hudCamera->setClearMask(GL_DEPTH_BUFFER_BIT);
//hudCamera->setRenderOrder(osg::Camera::POST_RENDER);
//hudCamera->setAllowEventFocus(false);
//hudCamera->setProjectionMatrix(osg::Matrix::ortho2D(0, 1, 0, 1));
//hudCamera->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
//
//float width = 1, height = 1, scale = 1;
//osg::Geometry* geom = osg::createTexturedQuadGeometry(osg::Vec3(), osg::Vec3(width, 0.0f, 0.0f), osg::Vec3(0.0f, height, 0.0f), 0.0f, 0.0f, width * scale, height * scale);
//osg::ref_ptr<osg::Geode> quad = new osg::Geode;
//quad->addDrawable(geom);
//
//int values = osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED;
//quad->getOrCreateStateSet()->setAttribute(
//	new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::FILL), values);
//quad->getOrCreateStateSet()->setMode(GL_LIGHTING, values);
//hudCamera->addChild(quad);
//
//osg::ref_ptr<osg::Program> program = new osg::Program;
//program->addShader(new osg::Shader(osg::Shader::VERTEX, vsSource));
//program->addShader(new osg::Shader(osg::Shader::FRAGMENT, fsSource));
//
//osg::ref_ptr<osg::Texture2D> noiseTex = new osg::Texture2D;
//noiseTex->setImage(osgDB::readImageFile("noise_tex.jpg"));
//noiseTex->setWrap(osg::Texture::WRAP_S, osg::Texture::REPEAT);
//noiseTex->setWrap(osg::Texture::WRAP_T, osg::Texture::REPEAT);
//noiseTex->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR);
//noiseTex->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);
//
//osg::StateSet* stateset = hudCamera->getOrCreateStateSet();
//stateset->setTextureAttributeAndModes(0, sceneTex);
//stateset->setTextureAttributeAndModes(1, noiseTex);
//stateset->setAttributeAndModes(program.get());
//stateset->addUniform(new osg::Uniform("sceneTex", 0));
//stateset->addUniform(new osg::Uniform("noiseTex", 1));
//
////   osg::ref_ptr<osg::Camera> rttCamera = createRTTCamera(osg::Camera::COLOR_BUFFER, tex2D.get(), false);
//   //osg::Vec3 eye = carGroup->getBound().center() + osg::Vec3(0.0f, 50, 100.0f);
//   //osg::Vec3 center = carGroup->getBound().center();
//   //osg::Vec3 up(0.0f, 1.0f, 1.0f);
//   //rttCamera->setViewMatrixAsLookAt(eye, center, up);
////   rttCamera->addChild(scene);
//
////   osg::ref_ptr<osg::Camera> hudCamera = createAnotherHUDCamera(0, 1, 0, 1);
////   hudCamera->addChild(createScreenQuad(1, 1, 1));
//
////   osg::ref_ptr<osg::Program> program = new osg::Program;
////   program->addShader(new osg::Shader(osg::Shader::VERTEX, vsSource));
////   program->addShader(new osg::Shader(osg::Shader::FRAGMENT, fsSource));
//
////   osg::StateSet* stateset = hudCamera->getOrCreateStateSet();
////   stateset->setTextureAttributeAndModes(0, tex2D);
////   stateset->setTextureAttributeAndModes(1, createTexture2DS("noise_tex.jpg"));
////   stateset->setAttributeAndModes(program.get());
////   stateset->addUniform(new osg::Uniform("sceneTex", 0));
////   stateset->addUniform(new osg::Uniform("noiseTex", 1));
//
//osg::ref_ptr<osg::Group> mdvSonar = new osg::Group;
//mdvSonar->addChild(rttCamera.get());
//mdvSonar->addChild(hudCamera.get());
////mdvSonar->addChild(scene.get());
//
//osg::ref_ptr<osg::Group> root = new osg::Group;
//root->addChild(scene);
//
//osg::ref_ptr<osgViewer::View> view = new osgViewer::View;
//view->setUpViewInWindow(50, 50, 500, 500);
////view->setSceneData(root);
//
//osg::ref_ptr<osgViewer::View> view2 = new osgViewer::View;
//view2->setUpViewInWindow(50, 50, 500, 500);
//
//CameraMover* cm = new CameraMover(view);
//view->addEventHandler(new osgViewer::WindowSizeHandler);
//view->addEventHandler(cm);
//view->setSceneData(mdvSonar);
//
//view2->addEventHandler(new osgViewer::WindowSizeHandler);
//view2->addEventHandler(cm);
//view2->setSceneData(root);
//
//const osg::BoundingSphere& bs = carGroup->getBound();
//view->getCamera()->setViewMatrixAsLookAt(bs.center() + osg::Vec3(0.0f, -(9 * bs.radius()), 100.0f), bs.center(), osg::Z_AXIS);
//cm->md = view->getCamera()->getViewMatrix();
//
//osgViewer::CompositeViewer viewer;
//viewer.addView(view.get());
//viewer.addView(view2.get());
//while (!viewer.done())
//{
//	view->getCamera()->setViewMatrix(cm->md);
//	view2->getCamera()->setViewMatrix(cm->md);
//	viewer.frame();
//}