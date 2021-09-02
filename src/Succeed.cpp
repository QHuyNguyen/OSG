//5 Complete Scene with Traits and Fade In/Out effect//Create Sea Surface
//osg::ref_ptr<osg::Node> planeDude = osgDB::readNodeFile("cessna.osg");
//osg::ref_ptr<osg::Group> waterScene = new osg::Group;
//createWater(waterScene, planeDude);
//osg::ref_ptr<osg::MatrixTransform> waterTrans = new osg::MatrixTransform;
//waterTrans->addChild(waterScene);
//waterTrans->setMatrix(osg::Matrix::translate(osg::Vec3(0, 0, 300)));
//
////Create Seabed Floor
//TextureSeabed textureSeabed;
//osg::ref_ptr<osg::Geode> seabed = new osg::Geode;
//textureSeabed.createTextureSeabed(seabed);//////Model model;
//osg::ref_ptr<osg::Node> obj1 = model.createTempModel("dumptruck.osg", osg::Vec4(1.0f, 0.2f, 0.2f, 1.0f));
//osg::ref_ptr<osg::Group> carGroup = new osg::Group;
//for (int i = 0; i < 10; i++)
//{
//    int min = -100, max = 100;
//    osg::Vec3 center(RAND(min, max), RAND(min, max), 10);
//    carGroup->addChild(model.createStaticNodes(center, obj1));
//}
//
////Create Sky Box
//osg::ref_ptr<osg::Geode> sphereGeode = new osg::Geode;
//sphereGeode->addDrawable(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(), seabed->getBound().radius())));
//osg::ref_ptr<Sky> skybox = new Sky;
//skybox->getOrCreateStateSet()->setTextureAttributeAndModes(0, new osg::TexGen);
//skybox->setEnvironmentMap(0, osgDB::readImageFile("Cubemap_snow/posx.jpg"),
//    osgDB::readImageFile("Cubemap_snow/negx.jpg"),
//    osgDB::readImageFile("Cubemap_snow/posy.jpg"),
//    osgDB::readImageFile("Cubemap_snow/negy.jpg"),
//    osgDB::readImageFile("Cubemap_snow/posz.jpg"),
//    osgDB::readImageFile("Cubemap_snow/negz.jpg"));
//skybox->addChild(sphereGeode.get());
//
////Create Menu Text
//ControlMenu menu;
//osg::ref_ptr<osgText::Text> text = menu.createMenuText(20.0f, osg::Vec3(10.0f, 200.0f, 0.0f), menuText);
//osg::ref_ptr<osg::Geode> textGeode = new osg::Geode;
//textGeode->addDrawable(text.get());
//osg::Camera* camera = createSonarCamera(0, 1024, 0, 768);
//camera->addChild(textGeode.get());
//camera->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
//
////Set Up Scene Node
//osg::ref_ptr<osg::Group> scene = new  osg::Group;
//scene->addChild(carGroup);
//scene->addChild(skybox);
//scene->addChild(seabed);
//scene->addChild(camera);
//scene->addChild(waterTrans);
//
////Another test scene with switch node
////osg::ref_ptr<osg::Group> test = new osg::Group;
////test->addChild(carGroup);
////test->addChild(skybox);
////test->addChild(noseabed);
////osg::ref_ptr<SceneSwitch> root = new SceneSwitch;
////root->addChild(scene, true);
////root->addChild(test, false);
//
////Create View Trait
//unsigned int width = 800, height = 600;
//osg::GraphicsContext::WindowingSystemInterface* wsi = osg::GraphicsContext::getWindowingSystemInterface();
//if (wsi)
//wsi->getScreenResolution(osg::GraphicsContext::ScreenIdentifier(0), width, height);
//osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
//traits->x = 0;
//traits->y = 0;
//traits->width = width;
//traits->height = height;
//traits->windowDecoration = false;
//traits->doubleBuffer = true;
//traits->sharedContext = 0;
//osg::ref_ptr<osg::GraphicsContext> gc = osg::GraphicsContext::createGraphicsContext(traits.get());
//int w_2 = width / 2, h_2 = height / 2;
//
////Create the first view
//osg::ref_ptr<osgViewer::View> view1 = new osgViewer::View;
////view1->setUpViewInWindow(50, 50, 500, 500);
//view1->getCamera()->setGraphicsContext(gc.get());
//view1->getCamera()->setViewport(w_2, 0, w_2, height);
////Set Up GUIEventHandler
//CameraMover* cm = new CameraMover(view1);
//view1->addEventHandler(new osgViewer::WindowSizeHandler);
//view1->addEventHandler(cm);
//view1->setSceneData(scene.get());
//
////Set Up Camera position
//const osg::BoundingSphere& bs = carGroup->getBound();
////const osg::BoundingSphere& bs = planeDude->getBound();
//view1->getCamera()->setViewMatrixAsLookAt(bs.center() + osg::Vec3(0.0f, -(9 * bs.radius()), 100.0f), bs.center(), osg::Z_AXIS);
//cm->md = view1->getCamera()->getViewMatrix();
//
////MDV Sonar View
//osg::ref_ptr<osgViewer::View> view2 = new osgViewer::View;
////view2->setUpViewInWindow(50, 50, 500, 500);
//view2->getCamera()->setGraphicsContext(gc.get());
//view2->getCamera()->setViewport(0, 0, w_2, height);
//view2->addEventHandler(new osgViewer::WindowSizeHandler);
//view2->addEventHandler(cm);
//view2->setSceneData(scene.get());
//view2->getCamera()->setCullMask(0x1);
//view2->getCamera()->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
//view2->getCamera()->setRenderOrder(osg::Camera::POST_RENDER);
//view2->getCamera()->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//view2->getCamera()->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
//view2->getCamera()->getOrCreateStateSet()->setAttributeAndModes(new osg::Depth(osg::Depth::LEQUAL, 1.0, 1.0)); //Remove the floor
//
//osgViewer::CompositeViewer viewer;
//viewer.addView(view1.get());
//viewer.addView(view2.get());
//while (!viewer.done())
//{
//    view1->getCamera()->setViewMatrix(cm->md);
//    view2->getCamera()->setViewMatrix(cm->md);
//    viewer.frame();
//}
//return 0;//4. Complete scene with Instruction Text added//Create Seabed Floor
//TextureSeabed textureSeabed;
//osg::ref_ptr<osg::Geode> seabed = new osg::Geode;
//textureSeabed.createTextureSeabed(seabed);////Model model;
//osg::ref_ptr<osg::Node> obj1 = model.createTempModel("dumptruck.osg", osg::Vec4(1.0f, 0.2f, 0.2f, 1.0f));
//osg::ref_ptr<osg::Group> carGroup = new osg::Group;
//////Create Seabed Floor with PolygonMode added////osg::ref_ptr<osg::Geode> noseabed = new osg::Geode;
////createTextureSeabed(noseabed);////osg::ref_ptr<osg::PolygonMode> pm = new osg::PolygonMode;////pm->setMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE);////noseabed->getOrCreateStateSet()->setAttribute(pm);
//for (int i = 0; i < 10; i++)
//{
//    int min = -100, max = 100;
//    osg::Vec3 center(RAND(min, max), RAND(min, max), 10);
//    carGroup->addChild(model.createStaticNodes(center, obj1));
//}
//
//osg::ref_ptr<osg::Geode> geode = new osg::Geode;
//geode->addDrawable(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(), seabed->getBound().radius())));
//
//osg::ref_ptr<Sky> skybox = new Sky;
//skybox->getOrCreateStateSet()->setTextureAttributeAndModes(0, new osg::TexGen);
//skybox->setEnvironmentMap(0, osgDB::readImageFile("Cubemap_snow/posx.jpg"),
//    osgDB::readImageFile("Cubemap_snow/negx.jpg"),
//    osgDB::readImageFile("Cubemap_snow/posy.jpg"),
//    osgDB::readImageFile("Cubemap_snow/negy.jpg"),
//    osgDB::readImageFile("Cubemap_snow/posz.jpg"),
//    osgDB::readImageFile("Cubemap_snow/negz.jpg"));
//skybox->addChild(geode.get());
//
////Create Text
//
//ControlMenu menu;
//osg::ref_ptr<osgText::Text> text = menu.createMenuText(20.0f, osg::Vec3(10.0f, 200.0f, 0.0f), menuText);
//osg::ref_ptr<osg::Geode> textGeode = new osg::Geode;
//textGeode->addDrawable(text.get());
//
//osg::Camera* camera = createSonarCamera(0, 1024, 0, 768);
//camera->addChild(textGeode.get());
//camera->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
//
//osg::ref_ptr<osg::Group> scene = new  osg::Group;
//scene->addChild(carGroup);
//scene->addChild(skybox);
//scene->addChild(seabed);
//scene->addChild(camera);
//
////Another test scene with switch node
////osg::ref_ptr<osg::Group> test = new osg::Group;
////test->addChild(carGroup);
////test->addChild(skybox);
////test->addChild(noseabed);
//
////osg::ref_ptr<SceneSwitch> root = new SceneSwitch;
////root->addChild(scene, true);
////root->addChild(test, false);
//
////Create view Trait
//
////Create the first view
//osg::ref_ptr<osgViewer::View> view1 = new osgViewer::View;
//view1->setUpViewInWindow(50, 50, 500, 500);
//
//CameraMover* cm = new CameraMover(view1);
//view1->addEventHandler(new osgViewer::WindowSizeHandler);
//view1->addEventHandler(cm);
//
//view1->setSceneData(scene.get());
//
//const osg::BoundingSphere& bs = carGroup->getBound();
//view1->getCamera()->setViewMatrixAsLookAt(bs.center() + osg::Vec3(0.0f, -(3 * bs.radius()), 100.0f), bs.center(), osg::Z_AXIS);
//cm->md = view1->getCamera()->getViewMatrix();
//
////MDV Sonar View
//osg::ref_ptr<osgViewer::View> view2 = new osgViewer::View;
//view2->setUpViewInWindow(50, 50, 500, 500);
//view2->addEventHandler(new osgViewer::WindowSizeHandler);
//view2->addEventHandler(cm);
//view2->setSceneData(scene.get());
//view2->getCamera()->setCullMask(0x1);
//view2->getCamera()->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
//view2->getCamera()->setRenderOrder(osg::Camera::POST_RENDER);
//view2->getCamera()->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//view2->getCamera()->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
//view2->getCamera()->getOrCreateStateSet()->setAttributeAndModes(new osg::Depth(osg::Depth::LEQUAL, 1.0, 1.0));
//
//osgViewer::CompositeViewer viewer;
//viewer.addView(view1.get());
//viewer.addView(view2.get());
//while (!viewer.done())
//{
//    view1->getCamera()->setViewMatrix(cm->md);
//    view2->getCamera()->setViewMatrix(cm->md);
//    viewer.frame();
//}
//return 0;//3. Set up Complete Scene with Sonar View    //Create Seabed Floor
    //TextureSeabed textureSeabed;
    //osg::ref_ptr<osg::Geode> seabed = new osg::Geode;
    //textureSeabed.createTextureSeabed(seabed);    //    //Model model;
    //osg::ref_ptr<osg::Node> obj1 = model.createTempModel("dumptruck.osg", osg::Vec4(1.0f, 0.2f, 0.2f, 1.0f));
    //osg::ref_ptr<osg::Group> carGroup = new osg::Group;
    //    ////Create Seabed Floor with PolygonMode added    ////osg::ref_ptr<osg::Geode> noseabed = new osg::Geode;
    ////createTextureSeabed(noseabed);    ////osg::ref_ptr<osg::PolygonMode> pm = new osg::PolygonMode;    ////pm->setMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE);    ////noseabed->getOrCreateStateSet()->setAttribute(pm);
    //for (int i = 0; i < 10; i++)
    //{
    //    osg::Vec3 center(RAND(-100, 100), RAND(-100, 100), 10);
    //    carGroup->addChild(model.createStaticNodes(center, obj1));
    //}
    //
    //osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    //geode->addDrawable(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(), seabed->getBound().radius())));
    //
    //osg::ref_ptr<Sky> skybox = new Sky;
    //skybox->getOrCreateStateSet()->setTextureAttributeAndModes(0, new osg::TexGen);
    //skybox->setEnvironmentMap(0, osgDB::readImageFile("Cubemap_snow/posx.jpg"),
    //    osgDB::readImageFile("Cubemap_snow/negx.jpg"),
    //    osgDB::readImageFile("Cubemap_snow/posy.jpg"),
    //    osgDB::readImageFile("Cubemap_snow/negy.jpg"),
    //    osgDB::readImageFile("Cubemap_snow/posz.jpg"),
    //    osgDB::readImageFile("Cubemap_snow/negz.jpg"));
    //skybox->addChild(geode.get());
    //
    //osg::ref_ptr<osg::Group> scene = new  osg::Group;
    //scene->addChild(carGroup);
    //scene->addChild(skybox);
    //scene->addChild(seabed);
    //
    ////Another test scene with switch node
    ////osg::ref_ptr<osg::Group> test = new osg::Group;
    ////test->addChild(carGroup);
    ////test->addChild(skybox);
    ////test->addChild(noseabed);
    //
    ////osg::ref_ptr<SceneSwitch> root = new SceneSwitch;
    ////root->addChild(scene, true);
    ////root->addChild(test, false);
    //
    ////Create the first view
    //osg::ref_ptr<osgViewer::View> view1 = new osgViewer::View;
    //view1->setUpViewInWindow(50, 50, 500, 500);
    //
    //CameraMover* cm = new CameraMover(view1);
    //
    //view1->addEventHandler(new osgViewer::WindowSizeHandler);
    //view1->addEventHandler(cm);
    //view1->setSceneData(scene.get());
    //
    //const osg::BoundingSphere& bs = carGroup->getBound();
    //view1->getCamera()->setViewMatrixAsLookAt(bs.center() + osg::Vec3(0.0f, -(3 * bs.radius()), 100.0f), bs.center(), osg::Z_AXIS);
    //cm->md = view1->getCamera()->getViewMatrix();
    //
    ////MDV Sonar View
    //osg::ref_ptr<osgViewer::View> view2 = new osgViewer::View;
    //view2->setUpViewInWindow(50, 50, 500, 500);
    //view2->addEventHandler(new osgViewer::WindowSizeHandler);
    //view2->addEventHandler(cm);
    //view2->setSceneData(scene.get());
    //view2->getCamera()->setCullMask(0x1);
    //view2->getCamera()->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
    //view2->getCamera()->setRenderOrder(osg::Camera::POST_RENDER);
    //view2->getCamera()->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //view2->getCamera()->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
    //view2->getCamera()->getOrCreateStateSet()->setAttributeAndModes(new osg::Depth(osg::Depth::LEQUAL, 1.0, 1.0));
    //
    //osgViewer::CompositeViewer viewer;
    //viewer.addView(view1.get());
    //viewer.addView(view2.get());
    //while (!viewer.done())
    //{
    //    view1->getCamera()->setViewMatrix(cm->md);
    //    view2->getCamera()->setViewMatrix(cm->md);
    //    viewer.frame();
    //}
    //return 0;//2. Set Up complete Scene//osg::ref_ptr<osg::Geode> seabed = new osg::Geode;
//createTextureSeabed(seabed);////Model model;
//osg::ref_ptr<osg::Node> obj1 = model.createTempModel("dumptruck.osg", osg::Vec4(1.0f, 0.2f, 0.2f, 1.0f));
//osg::ref_ptr<osg::Group> scene = new osg::Group;
//
//for (int i = 0; i < 10; i++)
//{
//    osg::Vec3 center(RAND(-100, 100), RAND(-100, 100), 10);
//    scene->addChild(model.createStaticNodes(center, obj1));
//}
//
//osg::ref_ptr<osg::Geode> geode = new osg::Geode;
//geode->addDrawable(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(), seabed->getBound().radius())));
//
//osg::ref_ptr<Sky> skybox = new Sky;
//skybox->getOrCreateStateSet()->setTextureAttributeAndModes(0, new osg::TexGen);
//skybox->setEnvironmentMap(0, osgDB::readImageFile("Cubemap_snow/posx.jpg"),
//    osgDB::readImageFile("Cubemap_snow/negx.jpg"),
//    osgDB::readImageFile("Cubemap_snow/posy.jpg"),
//    osgDB::readImageFile("Cubemap_snow/negy.jpg"),
//    osgDB::readImageFile("Cubemap_snow/posz.jpg"),
//    osgDB::readImageFile("Cubemap_snow/negz.jpg"));
//skybox->addChild(geode.get());
//
//osg::ref_ptr<osg::Camera> camera = new osg::Camera;//osg::Vec3 eye(osg::Vec3(0.0f, 1.0f, 2.0f));
//osg::Vec3 center = osg::Vec3();
//osg::Vec3 up(0.0f, 1.0f, 1.0f);
//camera->setViewMatrixAsLookAt(eye, center, up);//camera->addChild(seabed);//camera->addChild(scene);
//camera->addChild(skybox.get());
//
//osg::ref_ptr<osg::Group> root = new osg::Group;
//root->addChild(camera.get());
////root->addChild(skybox.get());
//
//osg::ref_ptr<osgViewer::View> view = new osgViewer::View;
//view->setUpViewInWindow(0, 0, 500, 500);
//view->setSceneData(root.get());
//
//osgViewer::CompositeViewer viewer;
//viewer.addView(view);
//return viewer.run();//1. Set Up the Scene InComplete    //osg::ref_ptr<osg::Geode> seabed = new osg::Geode;
    //createTextureSeabed(seabed);    //Model model;
    //osg::ref_ptr<osg::Node> obj1 = model.createTempModel("dumptruck.osg", osg::Vec4(1.0f, 0.2f, 0.2f, 1.0f));
    //osg::ref_ptr<osg::Group> scene = new osg::Group;

    //for (int i = 0; i < 10; i++)
    //{
    //    osg::Vec3 center(RAND(-100, 100), RAND(-100, 100), 10);
    //    scene->addChild(model.createStaticNodes(center, obj1));
    //}    //osg::ref_ptr<osg::Camera> camera = new osg::Camera;    //osg::Vec3 eye(osg::Vec3(0.0f, 1.0f, 2.0f));
    //osg::Vec3 center = osg::Vec3();
    //osg::Vec3 up(0.0f, 1.0f, 1.0f);
    //camera->setViewMatrixAsLookAt(eye, center, up);    //camera->addChild(seabed);    //camera->addChild(scene);    //osg::ref_ptr<osg::Group> root = new osg::Group;
    //root->addChild(camera);    //osg::ref_ptr<osgViewer::View> view = new osgViewer::View;
    //view->setUpViewInWindow(50, 50, 500, 500);
    //view->setSceneData(root);

    //osgViewer::CompositeViewer viewer;
    //viewer.addView(view.get());
    //return viewer.run();
    //osg::ref_ptr<osg::Node> obj1 = createObjects("dumptruck.osg",osg::Vec4(1.0f, 0.2f, 0.2f, 1.0f));
    //osg::ref_ptr<osg::Group> scene = new osg::Group;
    //for (int i = 0; i < 10; i++)
    //{
    //    osg::Vec3 center(RAND(-100, 100), RAND(-100, 100), 0);
    //    scene->addChild(createStaticNodes(center, obj1));
    //}

    //osg::ref_ptr<osg::Camera> radar = new osg::Camera;
    //radar->setClearColor(osg::Vec4(0.0f, 0.2f, 0.0f, 1.0f));
    //radar->setRenderOrder(osg::Camera::POST_RENDER);
    //radar->setAllowEventFocus(false);
    //radar->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //radar->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
    //radar->setViewport(0, 0, 200, 200);
    ////radar->setViewMatrix(osg::Matrixd::lookAt(osg::Vec3(0.0f, 0.0f, 120.0f), osg::Vec3(), osg::Y_AXIS));
    //radar->setProjectionMatrix(osg::Matrixd::ortho2D(-120.0, 120.0, -120.0, 120.0));
    //radar->setCullMask(RADAR_CAMERA_MASK);
    //radar->addChild(scene.get());

    //osg::ref_ptr<osg::Group> root = new osg::Group;
    //root->addChild(radar);
    //root->addChild(scene);

    //osg::ref_ptr<osgViewer::View> view = new osgViewer::View;
    //view->setUpViewInWindow(50, 50, 500, 500);
    //view->setSceneData(root.get());
    //view->getCamera()->setCullMask(MAIN_CAMERA_MASK);
    //view->setLightingMode(osg::View::SKY_LIGHT);

    //osgViewer::CompositeViewer viewer;
    //viewer.addView(view.get());
    //return viewer.run();