#pragma once
class Point
{private:
	int x, y;
public:
	Point(int x, int y);
	
		int getx();
		int gety();
		void setx(int pos);
		void sety(int pos);
	
		~Point();
	
};

