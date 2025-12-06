#ifndef __INSTANCE_H__
#define __INSTANCE_H__
#define WIREFRAME_INSTANCE 0
#define SOLID_INSTANCE 1
#include "Mesh.h"


#include "Helpers.h"



class Instance
{

public:
    int instanceId;
    Mesh mesh;
    int instanceType; // type=0 for wireframe, type=1 for solid
    int numberOfTransformations;

    std::vector<int> transformationIds;
    std::vector<char> transformationTypes;

    Instance();
    Instance(int instanceId, Mesh mesh, int instanceType, int numberOfTransformations,
             std::vector<int> transformationIds,
             std::vector<char> transformationTypes);

    friend std::ostream &operator<<(std::ostream &os, const Instance &instance);

    Matrix4 getComposeTransformMatrix(
    const std::vector<Translation*>& translations,
    const std::vector<Scaling*>& scalings,
    const std::vector<Rotation*>& rotations
) const;

};

#endif