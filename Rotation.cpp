#include <iomanip>
#include "Rotation.h"

Rotation::Rotation() {
    this->rotationId = -1;
    this->angle = 0;
    this->ux = 0;
    this->uy = 0;
    this->uz = 0;
}

Rotation::Rotation(int rotationId, double angle, double x, double y, double z)
{
    this->rotationId = rotationId;
    this->angle = angle;
    this->ux = x;
    this->uy = y;
    this->uz = z;
}

std::ostream &operator<<(std::ostream &os, const Rotation &r)
{
    os << std::fixed << std::setprecision(3) << "Rotation #" << r.rotationId << " => [angle = " << r.angle << ", " << r.ux << ", " << r.uy << ", " << r.uz << "]";
    return os;
}

Matrix4 Rotation::getRotationMatrix()
{

    //Rodrigues’ rotation formula:
    
    double rad = angle * M_PI / 180.0;

    double len = sqrt(ux*ux + uy*uy + uz*uz);
    double x = ux / len;
    double y = uy / len;
    double z = uz / len;

    double c = cos(rad);
    double s = sin(rad);
    double t = 1 - c;

    double temp[4][4] = {
        { t*x*x + c,     t*x*y - s*z,  t*x*z + s*y, 0.0 },
        { t*x*y + s*z,   t*y*y + c,    t*y*z - s*x, 0.0 },
        { t*x*z - s*y,   t*y*z + s*x,  t*z*z + c,   0.0 },
        { 0.0,           0.0,          0.0,         1.0 }
    };

    return Matrix4(temp);
}
