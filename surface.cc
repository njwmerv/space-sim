#include "surface.h"
#include <cmath>
#include <random>
#include <vector>
using namespace std;

class Perlin{
    int seed;
    std::vector<std::vector<float>> influence;

    static float influenceDotOffset(const float angle, const Vector2& vector){
        return vector.x * cos(angle) + vector.y * sin(angle);
    }

    static float lerp(const float weight, const float a1, const float a2){
        return weight * (a2 - a1) + a1;
    }

    static float smoothStep(const float x){
        return ((6 * x - 15) * x + 10) * x * x * x;
    }

public:
    explicit Perlin(int seed = 0, int width = 64, int height = 64) : seed{seed} {
        mt19937 mt(seed);
        uniform_real_distribution distrib(0.0f, 360.0f);

        // Create influence vectors
        for(int row = 0; row < height; row++){
            vector<float> newRow = vector<float>(width);
            for(int col = 0; col < width; col++){
                newRow[col] = distrib(mt);
            }
            influence.emplace_back(newRow);
        }
    }

    int getWidth() const {return influence.at(0).size() - 1;}
    int getHeight() const {return influence.size() - 1;}

    // Sample perlin noise at point (x, y)
    float perlinOctave(const float x, const float y) const {
        // Get index of point
        int ix = static_cast<int>(x);
        int iy = static_cast<int>(y);
        const float xf = x - ix;
        const float yf = y - iy;
        ix %= getWidth();
        iy %= getHeight();
        const int ixR = (ix + 1) % getWidth();
        const int iyR = (iy + 1) % getHeight();

        // Get influence vector for nearest corners
        const float tl_angle = influence.at(iy).at(ix);
        const float tr_angle = influence.at(iy).at(ixR);
        const float bl_angle = influence.at(iyR).at(ix);
        const float br_angle = influence.at(iyR).at(ixR);

        // Get offset vectors to nearest corners
        const Vector2 tl_offset{xf, yf};
        const Vector2 tr_offset{xf - 1.0f, yf};
        const Vector2 bl_offset{xf, yf - 1.0f};
        const Vector2 br_offset{xf - 1.0f, yf - 1.0f};

        // Get dot product of each corner's corresponding vectors
        const float tl_dot = influenceDotOffset(tl_angle, tl_offset);
        const float tr_dot = influenceDotOffset(tr_angle, tr_offset);
        const float bl_dot = influenceDotOffset(bl_angle, bl_offset);
        const float br_dot = influenceDotOffset(br_angle, br_offset);

        // Blend horizontally
        const float w1 = smoothStep(xf);
        const float h1 = lerp(w1, tl_dot, tr_dot);
        const float h2 = lerp(w1, bl_dot, br_dot);

        // Blend vertically
        const float w2 = smoothStep(yf);
        const float result = lerp(w2, h1, h2);

        return result;
    }

    float perlin(const float x, const float y) const{
        float noise = 0;
        float persistence = 2.0f;
        float lacunarity = 0.005f;
        constexpr int NUM_OCTAVES = 4;
        for(int octave = 0; octave < NUM_OCTAVES; octave++){
            noise += persistence * perlinOctave(x * lacunarity, y * lacunarity);
            persistence *= 0.5;
            lacunarity *= 2.0;
        }
        noise = (noise + 1.0) / 2.0; // transform from [-1, 1] -> [0, 1]
        return noise;
    }
};

Vector3 mapNoiseToColour(const float noise){
    if(noise < 0.225f){ // Deep water
        return {0, 0, 150};
    }
    else if(noise < 0.4f){ // Shallow water
        return {0, 100, 200};
    }
    else if(noise < 0.43f){ // Beach
        return {240, 220, 130};
    }
    else if(noise < 0.62f){ // Grass
        return {34, 139, 34};
    }
    else if(noise < 0.77f){ // Forest
        return {13, 105, 12};
    }
    else if(noise < 0.85){
        return {100, 100, 100};
    }
    else if(noise < 0.92f){ // Mountain
        return {151, 153, 152};
    }
    else{ // Snow
        return {255, 255, 255};
    }
}

void fillSurfaceTexture(unsigned char* noiseData, const int width, const int height, const int seed){
    const Perlin noiseGenerator{seed, width, height};
    for(int x = 0; x < width; x++){
        for(int y = 0; y < height; y++){
            const int index = (y * width + x) * 3;
            const float noise = noiseGenerator.perlin(x, y);
            const Vector3 colour = mapNoiseToColour(noise);
            noiseData[index] = static_cast<unsigned char>(colour.x);
            noiseData[index + 1] = static_cast<unsigned char>(colour.y);
            noiseData[index + 2] = static_cast<unsigned char>(colour.z);
        }
    }
}
