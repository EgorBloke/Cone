#ifndef CONE_H
#define CONE_H

#include<iostream>
#include<vector>
#include<cmath>
//class Point;
//class Triangle;




class Point {		//класс для хранения координат точки

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


class Triangle		//класс треугольника. содержить указатели на вершины 
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
	Point *first;		//координаты основания
	Point *second;		
	Point *top;		//координата вершины
};


class Cone		//класс конуса. определяется радиусом, высотой, количеством сегментов
	

{
public:
	Cone(double height=1., double r=1., unsigned int segmentNumber=3) //: height(height), r(r), segmentNumber(segmentNumber)	
	{
		this->height = height > 0 ? height : -height;		//проверка корректности инициализации
		this->r = r > 0 ? r : -r;
		this->segmentNumber = segmentNumber > 2 ? segmentNumber : 3;		//если меньше 3, инициализируется 3я сегментами
		top.setValues(0, 0, height);		//инициализация координаты вершины
		for (int i = 0; i < segmentNumber; ++i)			//инициализация координат точек на окружности в основании							
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

	Triangle operator[](int i)		//перегрузка оператора доступа через [] (для удобства)
							//возвращает треугольник, образованный двумя соседними точками из контейнера circlePoints
							//и точкой вершини конуса. С целью не хранить контейнер с треугольниками
	{
		i = abs(i);		//если передано отрицательное значение
		if (i > segmentNumber - 1) {	//если передано значение больше количества сегментов
			i = i % (segmentNumber - 1);
		}		
		if (i == segmentNumber - 1) {		// крайний треугольник. чтобы обеспечить закольцовывание для корректности работы оператора << для класса Cone
			return Triangle(circlePoints[i], circlePoints[0], &top);		
		}
		else {
			return Triangle(circlePoints[i], circlePoints[i + 1], &top);		//общий случай
		}
		
	}

	int getSegmentNumber() {
		return segmentNumber;
	}
protected:
	double height;
	double r;
	int segmentNumber;		//количество сегментов
	Point top;			//координаты вершины
	std::vector<Point*> circlePoints;	//контейнер с координатами точек на окружности
};

std::ostream& operator<<(std::ostream& out,const Point& p) {
	out.precision(4);
	return out << "x = " << p.x << "; \ty = " << p.y << "; \tz = " << p.z;
}

std::ostream& operator<<(std::ostream& out, Triangle& tr) {
	out.precision(4);
	return out << "\tfirst: \t" << tr.getFirst() <<'\n'<< "\tsecond: " << tr.getSecond() << '\n' << "\ttop: \t" << tr.getTop();
}

std::ostream& operator<<(std::ostream& out, Cone& cone)			//печать всех треугольников, из которых состоит конус
{
	out.precision(4);
	for (unsigned int i = 0; i < cone.getSegmentNumber(); ++i) {
		Triangle && tr = cone[i];		//перехват временного объекта, возвращенного оператором []
		out <<"Triangle: "<< i << '\n' << tr << std::endl;
	}
	return out;
}


#endif // !CONE_H

