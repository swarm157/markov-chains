/*
 * markovChains.h
 *
 *  Created on: 24 окт. 2020 г.
 *      Author: Пользователь
 */

#ifndef MARKOVCHAINS_H_
#define MARKOVCHAINS_H_

#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <iostream>

class markovChains {
private:
	bool dinamyc, adapt, unlimitedBuffers = true, staticBuffer = false, adaptBufferSize = false;
	int bufferSize = 100;
	float adaptVal = 0.1;
	std::string fileName;
	std::vector<int> exampleBuffer;
	std::vector<float> example;
	std::vector<std::vector<int>> buffer;
	std::vector<std::vector<float>> dataChains;
	int pos = 0, lastPos = pos;
	int IndexToPos = 0;
	float toPos = 0;
public:
	void save();
	void load();
	markovChains(int SIZE, std::string FILENAME, bool ADAPT, bool DINAMYC, bool UNLIMITEDBUFFERS, int BUFFERSIZE, float ADAPTVAL, bool ADAPTBUFFERSIZE, bool STATICBUFFER);
	markovChains(int SIZE, std::string FILENAME);
	markovChains(std::string FILENAME);
	~markovChains();
	int getPos() {
		return pos;
	}
	void setPos(int POS) {
		pos = POS;
	}
	void run();
	std::vector<std::vector<float>> getDataChains() {
		return dataChains;
	}
	void setDataChains(std::vector<std::vector<float>> DATACHAINS) {
		pos = 0;
		dataChains.clear();
		for(int i = 0; i < DATACHAINS.size(); i++) {
			dataChains.push_back(DATACHAINS[i]);
		}
	}
	void setFileName(std::string name) {
		fileName = name;
	}
	std::string getFileName() {
		return fileName;
	}
	void learn(std::string dataSet);
	float getBestResult() {
		float lastBest, now;
		lastBest = dataChains[pos][0];
		for(int i = 0; i < dataChains.size();i++) {
			now = dataChains[pos][i];
			if(now>lastBest) {
				lastBest = now;
			}
		}
		return lastBest;
	}
	float getToPos() {
		return toPos;
	}
	int getIndexToPos() {
		return IndexToPos;
	}
	float getBestResultIndex() {
			int lastBestI, nowI;
			lastBestI = 0;
			for(int i = 0; i < dataChains.size();i++) {
				nowI = i;
				if(dataChains[pos][nowI]>dataChains[pos][lastBestI]) {
					lastBestI = nowI;
				}
			}
			return lastBestI;
		}
	int getlastPos() {
		return lastPos;
	}
	void setDinamyc(bool DINAMYC) {
		dinamyc = DINAMYC;
	}
	void setAdapt(bool ADAPT) {
		adapt = ADAPT;
	}
	void setUnlimitedBuffers(bool UNLIMITEDBUFFERS) {
		unlimitedBuffers = UNLIMITEDBUFFERS;
	}
	void setAdaptVal(float ADAPTVAL) {
		adaptVal = ADAPTVAL;
	}
	void setDinamyc() {
			dinamyc = !(dinamyc);
		}
		void setAdapt() {
			adapt = !(adapt);
		}
		void setUnlimitedBuffers() {
			unlimitedBuffers = !(unlimitedBuffers);
		}
	void setBuffer(std::vector<std::vector<int>> BUFFER) {
		if(buffer.size()!=BUFFER.size()) {
			setPos(BUFFER.size()-1);
			autoDinamycPos();
		}
		buffer = BUFFER;
		for(int i = 0; i < buffer.size(); i++) {
			buffer[i] = BUFFER[i];
		}
	}

	std::vector<std::vector<int>> getBuffer() {
		return buffer;
	}

void setBufferSize(int BUFFERSIZE) {
		bufferSize = BUFFERSIZE;
	}
	bool getDinamyc() {
			return dinamyc;
		}
	bool getAdapt() {
			return adapt;
		}
	bool getUnlimitedBuffers() {
			return unlimitedBuffers;
		}
	float getAdaptVal() {
			return adaptVal;
		}
	int getBufferSize() {
			return bufferSize;
		}
	bool autoDinamycPos();
	bool getStaticBuffer() {
		return staticBuffer;
	}
	void setStaticBuffer(bool STATICBUFFER) {
		staticBuffer = STATICBUFFER;
	}
	void setStaticBuffer() {
			staticBuffer = !(staticBuffer);
		}
	bool getAdaptBufferSize() {
		return adaptBufferSize;
	}
	void setAdaptBufferSize(bool ADAPTBUFFERSIZE) {
		adaptBufferSize = ADAPTBUFFERSIZE;
	}
	void setAdaptBufferSize() {
			adaptBufferSize = !(adaptBufferSize);
		}
};

#endif /* MARKOVCHAINS_H_ */
