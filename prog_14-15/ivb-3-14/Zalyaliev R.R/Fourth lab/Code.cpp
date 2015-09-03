#include <iostream>
#include <fstream>
#include <string>

using std::ifstream;

class Point
{
public:
	int x, y;

	Point();
	Point(ifstream *stream);
};

Point::Point(){}
Point::Point(ifstream *stream)
{
	(*stream) >> x;
	(*stream) >> y;
}

class Rect
{
public:
	Point LeftTop, LeftDown, RightDown, RightTop;

	Rect(ifstream *stream);
	bool IsContact(Point p);
};

Rect::Rect(ifstream *stream)
{
	LeftTop = Point(stream);
	LeftDown = Point(stream);
	RightDown = Point(stream);
	RightTop = Point(stream);
}

bool Rect::IsContact(Point p)
{
	return (p.x >= LeftTop.x && p.x <= LeftDown.x && p.y >= LeftTop.y && p.y <= RightTop.y);
}

int main(int argc, char **argv)
{
	ifstream In = ifstream("input.txt");

	int N, Count = 0;
	In >> N;

	for (int i = 0; i < N; i++)
	{
		Point p = Point(&In);
		Rect r = Rect(&In);
		if (r.IsContact(p))
			Count++;
	}

	In.close();

	std::ofstream Out = std::ofstream("output.txt");
	Out << Count;
	Out.close();
}