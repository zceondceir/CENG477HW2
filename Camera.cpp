#include <iostream>
#include <iomanip>
#include "Camera.h"






Camera::Camera() {}

Camera::Camera(int cameraId,
               int projectionType,
               Vec3 position, Vec3 gaze,
               Vec3 u, Vec3 v, Vec3 w,
               double left, double right, double bottom, double top,
               double near, double far,
               int horRes, int verRes,
               std::string outputFilename)
{

    this->cameraId = cameraId;
    this->projectionType = projectionType;
    this->position = position;
    this->gaze = gaze;
    this->u = u;
    this->v = v;
    this->w = w;
    this->left = left;
    this->right = right;
    this->bottom = bottom;
    this->top = top;
    this->near = near;
    this->far = far;
    this->horRes = horRes;
    this->verRes = verRes;
    this->outputFilename = outputFilename;
}

Camera::Camera(const Camera &other)
{
    this->cameraId = other.cameraId;
    this->projectionType = other.projectionType;
    this->position = other.position;
    this->gaze = other.gaze;
    this->u = other.u;
    this->v = other.v;
    this->w = other.w;
    this->left = other.left;
    this->right = other.right;
    this->bottom = other.bottom;
    this->top = other.top;
    this->near = other.near;
    this->far = other.far;
    this->horRes = other.horRes;
    this->verRes = other.verRes;
    this->outputFilename = other.outputFilename;
}

std::ostream &operator<<(std::ostream &os, const Camera &c)
{
    const char *camType = c.projectionType ? "perspective" : "orthographic";

    os << std::fixed << std::setprecision(6) << "Camera #" << c.cameraId << " (" << camType << ") => pos: " << c.position << " gaze: " << c.gaze << std::endl
       << "\tu: " << c.u << " v: " << c.v << " w: " << c.w << std::endl
       << std::fixed << std::setprecision(3) << "\tleft: " << c.left << " right: " << c.right << " bottom: " << c.bottom << " top: " << c.top << std::endl
       << "\tnear: " << c.near << " far: " << c.far << " resolutions: " << c.horRes << "x" << c.verRes << " fileName: " << c.outputFilename;

    return os;
}

Matrix4 Camera::getCameraMatrix()
{
    double ex = position.x;
    double ey = position.y;
    double ez = position.z;

    double data[4][4] = {
        { u.x, u.y, u.z, -(u.x*ex + u.y*ey + u.z*ez) },
        { v.x, v.y, v.z, -(v.x*ex + v.y*ey + v.z*ez) },
        { w.x, w.y, w.z, -(w.x*ex + w.y*ey + w.z*ez) },
        { 0.0, 0.0, 0.0, 1.0 }
    };

    return Matrix4(data);
}

Matrix4 Camera::getProjectionMatrix()
{
    if (projectionType == ORTOGRAPHIC_PROJECTION)
        return getOrthographicMatrix();
    else
        return getPerspectiveMatrix();
}

Matrix4 Camera::getOrthographicMatrix()
{
    double L = left, R = right;
    double B = bottom, T = top;
    double N = near,  F = far;

    double data[4][4] =
    {
        {  2.0/(R-L),      0,               0,              -(R+L)/(R-L) },
        {       0,     2.0/(T-B),           0,              -(T+B)/(T-B) },
        {       0,          0,         -2.0/(F-N),          -(F+N)/(F-N) },
        {       0,          0,              0,                       1 }
    };

    return Matrix4(data);
}


Matrix4 Camera::getPerspectiveMatrix()
{
    double L = left, R = right;
    double B = bottom, T = top;
    double N = near,  F = far;

    double data[4][4] =
    {
        { (2*N)/(R-L),       0,             (R+L)/(R-L),             0 },
        {      0,        (2*N)/(T-B),       (T+B)/(T-B),             0 },
        {      0,             0,          -(F+N)/(F-N),        -(2*F*N)/(F-N) },
        {      0,             0,               -1,                    0 }
    };

    return Matrix4(data);
}

Matrix4 Camera::getViewportMatrix()
{
    double w = horRes;
    double h = verRes;

    double data[4][4] =
    {
        { w/2.0,    0,        0,      (w-1)/2.0 },
        {   0,     -h/2.0,    0,      (h-1)/2.0 },
        {   0,        0,       1,         0      },
        {   0,        0,       0,         1      }
    };

    return Matrix4(data);
}