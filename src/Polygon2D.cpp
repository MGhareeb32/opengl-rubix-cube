#include "Polygon2D.h"

Polygon2D::Polygon2D(int vertexCount, vec2 *vertex, rgba *color, GLint mode) {
    nVertex = vertexCount;
    drawMode = mode;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(2, &vbo[0]);

    // position
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER,
                 nVertex * sizeof(vec2), vertex, GL_STATIC_DRAW);
    // set as attr 0
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    // rgba
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER,
                 nVertex * sizeof(rgba), color, GL_STATIC_DRAW);
    // set as attr 1
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

int Polygon2D::getVertexCount() {
    return nVertex;
}

void Polygon2D::render() {
    glBindVertexArray(vao);
    glDrawArrays(drawMode, 0, nVertex);
}

Polygon2D::~Polygon2D() {
    // unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    // delete buffers
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(2, &vbo[0]);
    // disable attrs
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

}

Polygon2D* new_square(rgba col) {
    vec2 vert[4] = { vec2(-.5f, +.5f), vec2(-.5f, -.5f),
                     vec2(+.5f, +.5f), vec2(+.5f, -.5f) };
    rgba cols[4] = { col, col, col, col };
    return new Polygon2D(4, vert, cols, GL_TRIANGLE_STRIP);
}

Polygon2D* new_circle(rgba col, GLint nVertex) {
    GLfloat ang = M_PI / nVertex * 2;
    vec2 vert[nVertex];
    rgba cols[nVertex];
    for (GLint i = 0; i < nVertex; ++i) {
        cols[i] = col;
        vert[i] = vec2(cos(i * ang) / 2, sin(i * ang) / 2);
    }
    return new Polygon2D(nVertex, vert, cols, GL_TRIANGLE_FAN);
}

Polygon2D* new_circle_gradient(rgba side, rgba col, GLint nVertex) {
    GLfloat ang = M_PI * 2 / (nVertex - 2);
    vec2 vert[nVertex];
    rgba cols[nVertex];
    cols[0] = col;
    vert[0] = vec2(0.0, 0.0);
    for (GLint i = 1; i < nVertex; ++i) {
        cols[i] = sin(i * ang - M_PI / 2) > 0.0 ? col : side;
        vert[i] = vec2(cos(i * ang - M_PI / 2) / 2, sin(i * ang - M_PI / 2) / 2);
    }
    return new Polygon2D(nVertex, vert, cols, GL_TRIANGLE_FAN);
}

Polygon2D* new_arrow(rgba col) {
    vec2 vert[3] = { vec2(+.0f, +.5f), vec2(-.5f, -.5f), vec2(+.5f, -.5f) };
    rgba cols[3] = { col, col, col };
    return new Polygon2D(3, vert, cols, GL_TRIANGLE_STRIP);
}
