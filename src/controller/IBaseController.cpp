#include "IBaseController.h"

bool IBaseController::isGraphic = true;

void IBaseController::printDebug(const std::string& info)
{
	if (isDebug)
		std::cout << info << std::endl;
}
