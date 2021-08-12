#include "Corepch.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Application/Application.h>
#include <QApplication>
#include <fstream>
#include <Graphics/GUI Components/QtGui/MainWindow/MainWindow.h>
#include "Event/EventDispatcher.h"
#include "inipp.h"
#include "CL/cl.hpp"
#define NUM_OF_STARS 49152 // 1024
//49152
#define NUM_TIME_STEPS 10000 //5000
//10000


int main(int argc, char* argv[]) {
	//{
	//inipp::Ini<char> ini;
	//std::ofstream os("./Config/test.ini");
	//ini.default_section(ini.sections["Default"]);
	//ini.sections["Default"]["SomeOption1"] = "SomeVal";
	//ini.sections["sec1"]["sec1Option1"] = "SomeVal2";
	//ini.sections["sec1"]["sec1Option2"] = "SomeVal3";
	//ini.interpolate();
	//ini.generate(os);
	//os.close();
	//}
	//inipp::Ini<char> ini;
	//std::ifstream is ("./Config/test.ini");
	//ini.parse(is);
	//ini.default_section(ini.sections["Default"]);
	//ini.interpolate();
	//std::string val;
	//inipp::get_value(ini.sections["sec1"], "SomeOption1", val);
	//std::cout << "sec1:SomeOption1 = " << val << std::endl;

	//Application::App* entry = Application::App::getInstance();
	//entry->init();
	//while ( entry->getConfig ().running );
	//entry->cleanUp();
	std::shared_ptr<Application::EventDispatcher> dispatcher;
	QApplication app(argc, argv);
	Graphics::MainWindow mainWindow(dispatcher);
	mainWindow.show();

	return app.exec();
}