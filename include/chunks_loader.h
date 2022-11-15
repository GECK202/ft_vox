#ifndef VOXELS_CHUNKSLOADER_H
# define VOXELS_CHUNKSLOADER_H

# define CLOSES_C 27

# include <chrono>
# include <iostream>
# include <thread>
# include <atomic>

# include "chunk.h"
# include "chunks.h"
# include "world_generator.h"
# include "lighting.h"

class Chunk;

class ChunksLoader final {
private:
	std::thread loaderThread;
	void _thread();
	std::atomic<Chunk*> current {nullptr};
	std::atomic<Chunk**> closes {nullptr};
	std::atomic<bool> working {true};
	std::atomic<int> seed;
public:
	ChunksLoader(int seed) : loaderThread{} {
		this->seed = seed;
		loaderThread = std::thread{&ChunksLoader::_thread, this};
	}
	~ChunksLoader(){
		working = false;
		loaderThread.join();
	}

	bool isBusy(){
		return current != nullptr;
	}

	void perform(Chunk* chunk, Chunk** closes_passed);

	void stop(){
		working = false;
	}
};

#endif