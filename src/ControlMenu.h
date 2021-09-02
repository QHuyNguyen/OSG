#pragma once
#include <osg/Camera>
#include <osgDB/ReadFile>
#include <osgText/Font>
#include <osgText/Text>
#include <osgViewer/Viewer>

class ControlMenu : public osgText::Text
{
public:
	osgText::Text* createMenuText(float size, osg::Vec3 pos, const std::string& content)
	{
		osg::ref_ptr<osgText::Font> font = osgText::readFontFile("fonts/arial.ttf");
		osg::ref_ptr<osgText::Text> text = new osgText::Text;
		text->setFont(font.get());
		text->setCharacterSize(size);
		text->setAxisAlignment(osgText::TextBase::XY_PLANE);
		text->setPosition(pos);
		text->setText(content);
		return text.release();
	}
};