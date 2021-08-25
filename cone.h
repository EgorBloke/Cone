#ifndef CONE_H
#define CONE_H

#include<iostream>
#include<vector>
#include<cmath>
//class Point;
//class Triangle;




class Point {		//����� ��� �������� ��������� �����

public:
	Point(double x = 0., double y = 0., double z = 0.) : x(x), y(y), z(z) {}

	void setValues(double x, double y, double z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	double x;
	double y;
	double z;
};


class Triangle		//����� ������������. ��������� ��������� �� ������� 
{
public:
	Triangle(Point* first = nullptr, Point* second = nullptr, Point* top = nullptr):first(first),second(second),top(top)
	{
		
	}
	const Point& getFirst() {
		return *first;
	}
	const Point& getSecond() {
		return *second;
	}
	const Point& getTop() {
		return *top;
	}
protected:
	Point *first;		//���������� ���������
	Point *second;		
	Point *top;		//���������� �������
};


class Cone		//����� ������. ������������ ��������, �������, ����������� ���������
	

{
public:
	Cone(double height=1., double r=1., unsigned int segmentNumber=3) //: height(height), r(r), segmentNumber(segmentNumber)	
	{
		this->height = height > 0 ? height : -height;		//�������� ������������ �������������
		this->r = r > 0 ? r : -r;
		this->segmentNumber = segmentNumber > 2 ? segmentNumber : 3;		//���� ������ 3, ���������������� 3� ����������
		top.setValues(0, 0, height);		//������������� ���������� �������
		for (int i = 0; i < segmentNumber; ++i)			//������������� ��������� ����� �� ���������� � ���������							
		{
			circlePoints.push_back(new Point(r * cos(2 * 3.14159 * i / segmentNumber), r * sin(2 * 3.14159 * i / segmentNumber), 0));
		}
	}
	~Cone()
	{
		for (auto e : circlePoints) {
			delete e;
		}
	}

	Triangle operator[](int i)		//���������� ��������� ������� ����� [] (��� ��������)
							//���������� �����������, ������������ ����� ��������� ������� �� ���������� circlePoints
							//� ������ ������� ������. � ����� �� ������� ��������� � ��������������
	{
		i = abs(i);		//���� �������� ������������� ��������
		if (i > segmentNumber - 1) {	//���� �������� �������� ������ ���������� ���������
			i = i % (segmentNumber - 1);
		}		
		if (i == segmentNumber - 1) {		// ������� �����������. ����� ���������� ��������������� ��� ������������ ������ ��������� << ��� ������ Cone
			return Triangle(circlePoints[i], circlePoints[0], &top);		
		}
		else {
			return Triangle(circlePoints[i], circlePoints[i + 1], &top);		//����� ������
		}
		
	}

	int getSegmentNumber() {
		return segmentNumber;
	}
protected:
	double height;
	double r;
	int segmentNumber;		//���������� ���������
	Point top;			//���������� �������
	std::vector<Point*> circlePoints;	//��������� � ������������ ����� �� ����������
};

std::ostream& operator<<(std::ostream& out,const Point& p) {
	out.precision(4);
	return out << "x = " << p.x << "; \ty = " << p.y << "; \tz = " << p.z;
}

std::ostream& operator<<(std::ostream& out, Triangle& tr) {
	out.precision(4);
	return out << "\tfirst: \t" << tr.getFirst() <<'\n'<< "\tsecond: " << tr.getSecond() << '\n' << "\ttop: \t" << tr.getTop();
}

std::ostream& operator<<(std::ostream& out, Cone& cone)			//������ ���� �������������, �� ������� ������� �����
{
	out.precision(4);
	for (unsigned int i = 0; i < cone.getSegmentNumber(); ++i) {
		Triangle && tr = cone[i];		//�������� ���������� �������, ������������� ���������� []
		out <<"Triangle: "<< i << '\n' << tr << std::endl;
	}
	return out;
}


#endif // !CONE_H

