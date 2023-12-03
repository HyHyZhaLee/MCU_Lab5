/*
 * testCPP.h
 *
 *  Created on: Dec 1, 2023
 *      Author: Admin
 */

#ifndef INC_TESTCPP_H_
#define INC_TESTCPP_H_

#include "main.h"
class testCPP{
public:
	void test(){
		HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
	}
};


#endif /* INC_TESTCPP_H_ */
