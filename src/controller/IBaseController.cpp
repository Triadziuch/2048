#include "IBaseController.h"

void IBaseController::printDebug(const std::string& info)
{
	if (isDebug)
		std::cout << info << std::endl;
}
