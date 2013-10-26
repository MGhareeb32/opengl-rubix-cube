#ifndef POLYGON_H_
#define POLYGON_H_

#include "Main.h"
#include <vector>

typedef vec4 rgba;

class Polygon2D {
private:
    int nVertex;
    GLuint vao, vbo[2], drawMode;
public:
    Polygon2D(int vertexCount, vec2 *vertex, rgba *color, GLint mode);
    int getVertexCount();
    void render();
    virtual ~Polygon2D();
};

Polygon2D* new_square(rgba col);
Polygon2D* new_circle(rgba col, GLint nVertex);
Polygon2D* new_circle_gradient(rgba side, rgba col, GLint nVertex);
Polygon2D* new_arrow(rgba col);

#endif
