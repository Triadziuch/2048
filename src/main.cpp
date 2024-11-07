//#include "Game.h"
#include <memory>
#include "controller/GameController.h"
#include "view/GameViewCMD.h"
#include "controller/ControllerHandler.h"

int main() {
	//Game game;
	//game.run();

	std::shared_ptr<ModelHandler> modelHandler(new ModelHandler());
	std::shared_ptr<ViewHandler> viewHandler(new ViewHandler());
	ControllerHandler controllerHandler(modelHandler, viewHandler);

	return 0;
}

//#include <memory>  // for allocator, __shared_ptr_access
//#include <string>  // for char_traits, operator+, string, basic_string
//
//#include "ftxui/component/captured_mouse.hpp"  // for ftxui
//#include "ftxui/component/component.hpp"       // for Input, Renderer, Vertical
//#include "ftxui/component/component_base.hpp"  // for ComponentBase
//#include "ftxui/component/component_options.hpp"  // for InputOption
//#include "ftxui/component/screen_interactive.hpp"  // for Component, ScreenInteractive
//#include "ftxui/dom/elements.hpp"  // for text, hbox, separator, Element, operator|, vbox, border
//#include "ftxui/util/ref.hpp"  // for Ref
//
//int main() {
//    using namespace ftxui;
//    auto screen = ScreenInteractive::TerminalOutput();
//
//    std::vector<std::string> entries = {
//        "entry 1",
//        "entry 2",
//        "entry 3",
//    };
//    int selected = 0;
//
//    MenuOption option;
//    option.on_enter = screen.ExitLoopClosure();
//    auto menu = Menu(&entries, &selected, option);
//
//    screen.Loop(menu);
//
//    std::cout << "Selected element = " << selected << std::endl;
//}
