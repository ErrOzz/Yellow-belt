#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <memory>
#include <cmath>

using namespace std;

class Figure {
public:
  virtual ~Figure() {}

  virtual string Name() const = 0;
  virtual double Perimeter() const = 0;
  virtual double Area() const = 0;
};

class Rect : public Figure {
public:
  Rect(const int& width, const int& height) : _width(width), _height(height) {}

  string Name() const override { return "RECT"; }
  double Perimeter() const override { return (_width + _height) * 2.0; }
  double Area() const override { return _width * _height * 1.0; }

private:
  const int _width, _height;
};

class Triangle : public Figure {
public:
  Triangle(const int& a, const int& b,const int& c) : _a(a), _b(b), _c(c) {}

  string Name() const override { return "TRIANGLE"; }
  double Perimeter() const override { return (_a + _b + _c) * 1.0; }
  double Area() const override {
    const double pp = Perimeter() / 2;
    return sqrt(pp * (pp - _a) * (pp - _b) * (pp - _c));
  }

private:
  const int _a, _b, _c;
};

class Circle : public Figure {
public:
  Circle(const int& r) : _r(r) {}

  string Name() const override { return "CIRCLE"; }
  double Perimeter() const override { return _r * 2 * 3.14; }
  double Area() const override { return _r * _r * 3.14; }

private:
  const int _r;
};

shared_ptr<Figure> CreateFigure(istream& is) {
  string figure_type;
  is >> figure_type;
  if (figure_type == "RECT") {
    int w, h;
    is >> w >> h;
    return make_shared<Rect>(w, h);
  } else if (figure_type == "TRIANGLE") {
    int a, b, c;
    is >> a >> b >> c;
    return make_shared<Triangle>(a, b, c);
  } else if (figure_type == "CIRCLE") {
    int r;
    is >> r;
    return make_shared<Circle>(r);
  }
  return 0;
}

int main() {
  vector<shared_ptr<Figure>> figures;
  for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "ADD") {
      figures.push_back(CreateFigure(is));
    } else if (command == "PRINT") {
      for (const auto& current_figure : figures) {
        cout << fixed << setprecision(3)
             << current_figure->Name() << " "
             << current_figure->Perimeter() << " "
             << current_figure->Area() << endl;
      }
    }
  }
  return 0;
}
