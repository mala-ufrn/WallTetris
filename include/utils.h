#ifndef UTILS_H_
#define UTILS_H_

class Utils {
private:
	//Controller to run srand(time())on first use of randNum method
	static bool init;
public:
    //Returns a random number between 0 and x (exclusive)
    static float randNum(int x);
};
#endif // UTILS_H_