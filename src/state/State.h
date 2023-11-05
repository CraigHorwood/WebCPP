#ifndef _STATE_H
#define _STATE_H

class State {
public:
	State() {}
	~State() {}
	virtual void tick() {}
	virtual void render() {}
	virtual void keyUp(int) {}
	virtual void keyDown(int) {}
	virtual void mouseDown(double, double) {}
	virtual void mouseUp(double, double) {}
	virtual void mouseMoved(double, double, double, double) {}
private:
protected:
};

#endif