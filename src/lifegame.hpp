#pragma once
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <omp.h>
#include <GLFW/glfw3.h>
#include <cstdlib>



struct Vertex{
	float x, y;
	float lifeColor;
};

struct Cell {
	bool alive; 
	int lifeTime;
	std::string mutation;
	float age;
};

struct Game {
    std::vector<Vertex> vertices;
    std::vector<std::vector<Cell>> life;
    float width, height;
    int nx, ny;

    Cell empty = {false, 0, "", 0};
    Vertex v_empty = {0.0f, 0.0f, 0.0f};

    Game(int _nx, int _ny, float _width, float _height)
        : nx(_nx), ny(_ny), width(_width), height(_height),
          life(_nx, std::vector<Cell>(_ny, empty)), vertices(_ny, v_empty) {}

    void reset() {
        life.assign(nx, std::vector<Cell>(ny, empty));
        vertices.clear();
    }

	 void setUpVertices() {
	    float cellSizeX = width / nx;
	    float cellSizeY = height / ny;

	    vertices.clear();

	    int numThreads = omp_get_max_threads();
	    std::vector<std::vector<Vertex>> localBuffers(numThreads);
	    size_t estimatedPerThread = (nx * ny / numThreads) * 6;
	    for (auto &b : localBuffers) b.reserve(estimatedPerThread);

	    #pragma omp parallel for
	    for (int i = 0; i < nx; ++i) {
	        int tid = omp_get_thread_num();
	        auto& buffer = localBuffers[tid];

	        for (int j = 0; j < ny; ++j) {
	            if (!life[i][j].alive) continue;

	            float lifeColor = std::log(1.0f + life[i][j].age * 0.1f) / std::log(1.0f + 1000.0f);

	            if (!life[i][j].mutation.empty())
	                lifeColor = 0.0f;

	            Vertex v1, v2, v3, v4;
	            v1.lifeColor = v2.lifeColor = v3.lifeColor = v4.lifeColor = lifeColor;

	            float x = i * cellSizeX;
	            float y = j * cellSizeY;

	            v1.x = x - 0.5f * cellSizeX; v1.y = y - 0.5f * cellSizeY;
	            v2.x = x + 0.5f * cellSizeX; v2.y = y - 0.5f * cellSizeY;
	            v3.x = x - 0.5f * cellSizeX; v3.y = y + 0.5f * cellSizeY;
	            v4.x = x + 0.5f * cellSizeX; v4.y = y + 0.5f * cellSizeY;

	            buffer.insert(buffer.end(), {v1, v2, v3, v3, v2, v4});
	        }
	    }

	    size_t totalSize = 0;
	    for (auto& b : localBuffers) totalSize += b.size();
	    vertices.reserve(totalSize);
	    for (auto& b : localBuffers)
	        vertices.insert(vertices.end(), b.begin(), b.end());
	}
};

Game setUpGame(int nx, int ny, float width, float height);
void updateGame(Game& game, bool aléatoire);