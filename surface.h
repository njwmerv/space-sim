#ifndef SURFACE_H
#define SURFACE_H
#include "vector.h"

// Surface Texture Generator using Perlin Noise
Vector3 mapNoiseToColour(float noise);
void fillSurfaceTexture(unsigned char* noiseData, int width, int height, int seed = 1);

#endif //SURFACE_H