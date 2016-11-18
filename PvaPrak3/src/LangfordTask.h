/*
 * LangfordTask.h
 *
 *  Created on: 18.11.2016
 *      Author: hrehmege
 */

//#include "tbb/task.h"
#include "Langford.h"

#ifndef LANGFORDTASK_H_
#define LANGFORDTASK_H_

//using namespace tbb;

class LangfordTask /*: public task*/ {
public:
	LangfordTask();
	virtual ~LangfordTask();

	void berechneMuster(Langford &langfordSpiel, char muster);

private:
	unsigned char muster;
	int rangKindTask;
	Langford* langfordSpiel;
};

#endif /* LANGFORDTASK_H_ */
