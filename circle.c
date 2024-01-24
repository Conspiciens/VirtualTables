#include <stdlib.h>
#include <iostream> 
using namespace std; 
 
typedef double(*double_method_union)(void *); 
typedef void(*void_method_union)(void *); 

typedef union {
  double_method_union double_method; 
  void_method_union void_method;
} VirtualTableEntry;

typedef VirtualTableEntry *VTableType; 

#define PI 3.14159

struct Shape {
    VTableType Vpointer;
    string name;
};

void shape_area () {
   return;
}

void shape_circumference () {
    return;
}

VirtualTableEntry Shape_VTable [] = {
    {.void_method=(void_method_union)shape_area},
    {.void_method=(void_method_union)shape_circumference}
};

Shape* shape_shape (Shape *_this, string name) {
    _this->Vpointer = Shape_VTable;

    return _this;
};

struct Circle {
    VTableType Vpointer;
    double radius;
};

/* Circle functions */
double circle_area (Circle *_this){
    return PI * _this->radius * _this->radius;
}

double circle_circumference (Circle *_this){
    return 2.0 * PI * _this->radius;
}

VirtualTableEntry Circle_VTable [] = {
    {.double_method=(double_method_union)circle_area},
    {.double_method=(double_method_union)circle_circumference}
};

/* Constructor */
Circle* circle_circle (Circle *_this, double newRadius){
    shape_shape((Shape*)_this, "Circle");
    _this->Vpointer = Circle_VTable;
    _this->radius = newRadius;

    return _this;
};

struct Square {
    VTableType Vpointer;
    double width;
    double height;

}; 

/* Square Functions */
double square_area(Square *_this){
    return _this->width * _this->height;
}

double square_circumference(Square *_this){
    return (2  * _this->width) + (2 * _this->height);
}

VirtualTableEntry Square_VTable [] = {
    {.double_method=(double_method_union)square_area},
    {.double_method=(double_method_union)square_circumference}
};

/* Constructor */
Square* square_square (Square *_this, double width, double height){
    shape_shape((Shape*)_this, "Square");
    _this->Vpointer = Circle_VTable;
    _this->width = width;
    _this->height = height;

    return _this;
};

struct Triangle {
    VTableType Vpointer;
    double height;
    double width;

};

double triangle_area (Triangle *_this){
    return 0.5 * (_this->height * _this->width);
}

double triangle_circumference (Triangle *_this){
    double hyp = sqrt((_this->height * _this->height) + (_this->height * _this->height));
    return hyp + _this->height + _this->width;
}

VirtualTableEntry Triangle_VTable [] = {
    {.double_method=(double_method_union)triangle_area},
    {.double_method=(double_method_union)triangle_circumference}
};

/* Constructor */
Triangle* triangle_triangle (Triangle *_this, double width, double height){
    shape_shape((Shape*)_this, "Triangle");
    _this->Vpointer = Triangle_VTable;
    _this->width = width;
    _this->height = height;

    return _this;
};

int main() {
    Shape *a [] = {
        (Shape*)circle_circle((Circle*)malloc(sizeof(Circle)), 10),
        (Shape*)triangle_triangle((Triangle*)malloc(sizeof(Triangle)), 10, 20),
        (Shape*)square_square((Square*)malloc(sizeof(Square)), 10, 20),
    };

    for (int i = 0; i < (sizeof(a) / sizeof(*a)); i++){
        cout << "Area=" << (a[i]->Vpointer[0]).double_method(a[i]) << endl;
        cout << "Circumference=" << (a[i]->Vpointer[0]).double_method(a[i]) << endl;
    }
}
