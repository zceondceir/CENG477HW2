#include <vector>
#include <iomanip>
#include "Mesh.h"
#include "Instance.h"
#include "Scene.h"

Instance::Instance() {};

Instance::Instance(int instanceId, Mesh mesh, int instanceType, int numberOfTransformations,
                   std::vector<int> transformationIds,
                   std::vector<char> transformationTypes)
{
    this->instanceId = instanceId;
    this->mesh = mesh;
    this->instanceType = instanceType;
    this->numberOfTransformations = numberOfTransformations;
    this->transformationIds = transformationIds;
    this->transformationTypes = transformationTypes;
}

std::ostream &operator<<(std::ostream &os, const Instance &instance)
{
    os << "Instance #" << instance.instanceId;

    if (instance.instanceType == 0)
    {
        os << " wireframe(0) with ";
    }
    else
    {
        os << " solid(1) with ";
    }

    os << instance.numberOfTransformations << " transformations on the following mesh:" << std::endl;
    os << instance.mesh;

    return os;
}

Matrix4 Instance::getComposeTransformMatrix(
    const std::vector<Translation*>& translations,
    const std::vector<Scaling*>& scalings,
    const std::vector<Rotation*>& rotations
) const
{
    Matrix4 M = getIdentityMatrix();

    for (int i = numberOfTransformations - 1; i >= 0; i--)
    {
        char type = transformationTypes[i];
        int id = transformationIds[i];

        Matrix4 T;

        if (type == 't')
            T = translations[id - 1]->getTranslationMatrix();

        else if (type == 's')
            T = scalings[id - 1]->getScalingMatrix();

        else if (type == 'r')
            T = rotations[id - 1]->getRotationMatrix();

        M = multiplyMatrixWithMatrix(T, M);
    }

    return M;
}

