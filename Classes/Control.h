#ifndef __CONTROL_H_
#define __CONTROL_H_

#include "MapAttribute.h"

// abstract class for giving the next move
class Control {
public:
	virtual Location nextMove(SnakeLocation) = 0;
};

// control by AI(writting algorithm yourself)
class AIControl : public Control {
	Location nextMove(SnakeLocation);
};

// control by player
class HumanControl : public Control {
	Location nextMove(SnakeLocation);
};

#endif // __CONTROL_H_