#ifndef WORLD_FILES_H
#define WORLD_FILES_H

#define SECTION_POSITION 1
#define SECTION_ROTATION 2
#define REGION_SIZE_BIT 5
#define REGION_SIZE (1 << (REGION_SIZE_BIT))
#define REGION_VOL ((REGION_SIZE) * (REGION_SIZE))

#include <cassert>
#include <iostream>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <unordered_map>
#include <string>

#include "files.h"
#include "camera.h"
#include "player.h"
#include "hitbox.h"
#include "chunk.h"
#include "chunks.h"

class Player;
class Chunks;

class WorldFiles {
public:
	static unsigned long totalCompressed;
	std::unordered_map<long, char**> regions;
	std::string directory;
	char* mainBufferIn;
	char* mainBufferOut;

	WorldFiles(const char* directory, size_t mainBufferCapacity);
	~WorldFiles();

	void put(const char* chunkData, int x, int y);

	bool readPlayer(Player* player);
	bool readChunk(int x, int y, char* out);
	bool getChunk(int x, int y, char* out);
	void readRegion(char* fileContent);
	unsigned int writeRegion(char* out, int x, int y, char** region);
	void writePlayer(Player* player);
	void write();

	std::string getRegionFile(int x, int y);
	std::string getPlayerFile();
};

extern void longToCoords(int& x, int& y, long key);
extern void write_world(WorldFiles* wfile, Chunks* chunks);
extern void close_world(WorldFiles* wfile, Chunks* chunks);

#endif