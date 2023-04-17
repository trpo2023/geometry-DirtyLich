#include <stdio.h>
#include <math.h>

struct Point {
float x;
float y;
};

struct Circle {
struct Point center;
float radius;
};

struct Triangle {
struct Point vertex1;
struct Point vertex2;
struct Point vertex3;
};

float distance(struct Point p1, struct Point p2) {
float dx = p2.x - p1.x;
float dy = p2.y - p1.y;
return sqrt(dx*dx + dy*dy);
}

float perimeter_circle(struct Circle c) {
return 2 * M_PI * c.radius;
}

float area_circle(struct Circle c) {
return M_PI * c.radius * c.radius;
}

float perimeter_triangle(struct Triangle t) {
float d1 = distance(t.vertex1, t.vertex2);
float d2 = distance(t.vertex2, t.vertex3);
float d3 = distance(t.vertex3, t.vertex1);
return d1 + d2 + d3;
}

float area_triangle(struct Triangle t) {
float a = distance(t.vertex1, t.vertex2);
float b = distance(t.vertex2, t.vertex3);
float c = distance(t.vertex3, t.vertex1);
float s = (a + b + c) / 2;
return sqrt(s*(s-a)*(s-b)*(s-c));
}

int circles_intersect(struct Circle c1, struct Circle c2) {
float dx = c1.center.x - c2.center.x;
float dy = c1.center.y - c2.center.y;
float d = sqrt(dx*dx + dy*dy);
return d < c1.radius + c2.radius;
}

int triangle_circle_intersect(struct Triangle t, struct Circle c) {
float d1 = distance(c.center, t.vertex1);
float d2 = distance(c.center, t.vertex2);
float d3 = distance(c.center, t.vertex3);
return d1 < c.radius || d2 < c.radius || d3 < c.radius;
}

int main() {
struct Point p1, p2, p3;
struct Circle c;

printf("Enter the coordinates of the first vertex of the triangle (x y): ");
scanf("%f %f", &p1.x, &p1.y);

printf("Enter the coordinates of the second vertex of the triangle (x y): ");
scanf("%f %f", &p2.x, &p2.y);

printf("Enter the coordinates of the third vertex of the triangle (x y): ");
scanf("%f %f", &p3.x, &p3.y);

printf("Enter the coordinates of the center of the circle (x y): ");
scanf("%f %f", &c.center.x, &c.center.y);

printf("Enter the radius of the circle: ");
scanf("%f", &c.radius);

struct Triangle t = {p1, p2, p3};

float tri_perimeter = perimeter_triangle(t);
float tri_area = area_triangle(t);
printf("Triangle perimeter: %.2f\n", tri_perimeter);
printf("Triangle area: %.2f\n", tri_area);

float circ_perimeter = perimeter_circle(c);
float circ_area = area_circle(c);
printf("Circle perimeter: %.2f\n", circ_perimeter);
printf("Circle area: %.2f\n", circ_area);

if (triangle_circle_intersect(t, c)) {
printf("The triangle and circle intersect.\n");
} else if(circles_intersect(c, c)) { // изменено c, c на c1, c2
printf("The circles intersect.\n");
} else {
printf("The triangle and circle do not intersect.\n");
}

// Преобразование координат окружности в WKT-формат
printf("Circle in WKT format: ");
printf("CIRCLE(%.2f %.2f, %.2f)\n", c.center.x, c.center.y, c.radius);

// Преобразование координат треугольника в WKT-формат
printf("Triangle in WKT format: ");
printf("POLYGON((%.2f %.2f, %.2f %.2f, %.2f %.2f, %.2f %.2f))\n",
p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, p1.x, p1.y);

return 0;
}
