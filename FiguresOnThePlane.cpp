//
//  main.cpp
//  FiguresOnThePlane
//
//  Created by Polya Melnik on 10.12.2023.
//

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

// Клас для представлення точки на площині
class Point {
public:
    double x, y;

    Point(double _x, double _y) : x(_x), y(_y) {}
};

// Клас для представлення прямої на площині
class Line {
public:
    double a, b, c;

    Line(double _a, double _b, double _c) : a(_a), b(_b), c(_c) {}
};

// Клас для представлення кола на площині
class Circle {
public:
    Point center;
    double radius;

    Circle(Point _center, double _radius) : center(_center), radius(_radius) {}
};

// Функція для знаходження точок перетину двох прямих
vector<Point> findIntersection(const Line& l1, const Line& l2) {
    vector<Point> intersectionPoints;

    double determinant = l1.a * l2.b - l2.a * l1.b;

    if (determinant != 0) {
        double x = (l2.c * l1.b - l1.c * l2.b) / determinant;
        double y = (l1.c * l2.a - l2.c * l1.a) / determinant;
        intersectionPoints.emplace_back(x, y);
    }

    return intersectionPoints;
}

// Функція для знаходження точок перетину прямої і кола
vector<Point> findIntersection(const Line& l, const Circle& c) {
    vector<Point> intersectionPoints;

    double a = l.a;
    double b = l.b;
    double c_line = l.c;

    double x0 = c.center.x;
    double y0 = c.center.y;
    double r = c.radius;

    double distance = abs(a * x0 + b * y0 + c_line) / sqrt(a * a + b * b);

    if (distance <= r) {
        double sign_b = (b < 0) ? -1 : 1;

        double x1 = x0 - sign_b * (distance * b) / sqrt(a * a + b * b);
        double y1 = y0 + sign_b * (distance * a) / sqrt(a * a + b * b);

        intersectionPoints.emplace_back(x1, y1);

        if (distance != r) {
            double x2 = 2 * x0 - x1;
            double y2 = 2 * y0 - y1;
            intersectionPoints.emplace_back(x2, y2);
        }
    }

    return intersectionPoints;
}

// Функція для знаходження точки симетрично відображеної відносно заданої прямої
Point reflectPoint(const Point& point, const Line& axis) {
    double a = axis.a;
    double b = axis.b;
    double c = axis.c;

    // Знаходимо відстань від точки до прямої
    double distance = (a * point.x + b * point.y + c) / sqrt(a * a + b * b);

    // Обчислюємо координати точки симетричної відображеної
    double x_reflected = point.x - 2 * a * distance / (a * a + b * b);
    double y_reflected = point.y - 2 * b * distance / (a * a + b * b);

    return Point(x_reflected, y_reflected);
}

// Функція для знаходження точки інверсії відносно заданого кола
Point invertPoint(const Point& point, const Circle& inversionCircle) {
    double x0 = inversionCircle.center.x;
    double y0 = inversionCircle.center.y;
    double r = inversionCircle.radius;

    // Знаходимо відстань від точки до центра кола
    double distanceToCenter = sqrt((point.x - x0) * (point.x - x0) + (point.y - y0) * (point.y - y0));

    // Обчислюємо координати точки інверсії
    double x_inverted = x0 + (r * r * (point.x - x0)) / (distanceToCenter * distanceToCenter);
    double y_inverted = y0 + (r * r * (point.y - y0)) / (distanceToCenter * distanceToCenter);

    return Point(x_inverted, y_inverted);
}

int main() {
    // Введення значень для першої прямої
    cout << "Введіть коефіцієнти для першої прямої (a b c): ";
    double a1, b1, c1;
    cin >> a1 >> b1 >> c1;
    Line line1(a1, b1, c1);

    // Введення значень для другої прямої
    cout << "Введіть коефіцієнти для другої прямої (a b c): ";
    double a2, b2, c2;
    cin >> a2 >> b2 >> c2;
    Line line2(a2, b2, c2);

    // Введення значень для кола
    cout << "Введіть координати центра кола (x y): ";
    double x, y;
    cin >> x >> y;
    Point center(x, y);

    cout << "Введіть радіус кола: ";
    double radius;
    cin >> radius;
    Circle circle(center, radius);

    // Задаємо пряму для симетричного відображення
    cout << "Введіть коефіцієнти для прямої симетрії (a b c): ";
    double a_symmetry, b_symmetry, c_symmetry;
    cin >> a_symmetry >> b_symmetry >> c_symmetry;
    Line symmetryAxis(a_symmetry, b_symmetry, c_symmetry);

    // Задаємо коло для інверсії
    cout << "Введіть координати центра кола для інверсії (x y): ";
    cin >> x >> y;
    Point inversionCenter(x, y);

    cout << "Введіть радіус кола для інверсії: ";
    cin >> radius;
    Circle inversionCircle(inversionCenter, radius);

    // Знаходження точок перетину
    vector<Point> intersectionPoints1 = findIntersection(line1, line2);
    vector<Point> intersectionPoints2 = findIntersection(line1, circle);

    // Виведення результатів
    cout << "Точки перетину прямих:" << endl;
    for (const Point& point : intersectionPoints1) {
        cout << "(" << point.x << ", " << point.y << ")" << endl;
    }

    cout << "\nТочки перетину прямої та кола:" << endl;
    for (const Point& point : intersectionPoints2) {
        cout << "(" << point.x << ", " << point.y << ")" << endl;
    }

    // Виведення результатів операцій симетрії та інверсії
    cout << "\nОперації симетричного відображення та інверсії:" << endl;

    // Симетричне відображення точок відносно прямої
    cout << "Точки симетрично відображеної відносно прямої:" << endl;
    for (const Point& point : intersectionPoints1) {
        Point reflected = reflectPoint(point, symmetryAxis);
        cout << "(" << reflected.x << ", " << reflected.y << ")" << endl;
    }

    // Симетричне відображення точок відносно кола
    cout << "Точки інверсії відносно кола:" << endl;
    for (const Point& point : intersectionPoints2) {
        Point inverted = invertPoint(point, inversionCircle);
        cout << "(" << inverted.x << ", " << inverted.y << ")" << endl;
    }

    return 0;
}


