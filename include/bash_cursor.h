#ifndef BASH_CURSOR_H_
#define BASH_CURSOR_H_

class BashCursor {
public:
	//Save the cursor position
	static void save();
	//Restore the cursor position
	static void resume();
	//Move the cursor position to the (x, y) coordinates
	static void move(const int x,const int y);

private:
	BashCursor() {}
};

#endif // BASH_CURSOR_H_