/*
 * markovChains.cpp
 *
 *  Created on: 24 окт. 2020 г.
 *      Author: Пользователь
 */

#include "markovChains.h"



markovChains::markovChains(int SIZE, std::string FILENAME, bool ADAPT, bool DINAMYC, bool UNLIMITEDBUFFERS, int BUFFERSIZE, float ADAPTVAL, bool ADAPTBUFFERSIZE, bool STATICBUFFER) {
	fileName = FILENAME;
	dinamyc = DINAMYC;
	adaptBufferSize = ADAPTBUFFERSIZE;
	staticBuffer = STATICBUFFER;
	adapt = ADAPT;
	adaptVal = ADAPTVAL;
	bufferSize = BUFFERSIZE;
	unlimitedBuffers = false;
	for(int i = 0; i < SIZE; i++) {
		for(int i = 0; i < SIZE; i++) {
				float r = (rand()%110);
				r/=100;
				exampleBuffer.push_back(0);
				example.push_back(r);
			}
		dataChains.push_back(example);
		example.clear();
		buffer.push_back(exampleBuffer);
		exampleBuffer.clear();
	}

}

markovChains::markovChains(int SIZE, std::string FILENAME) {
	fileName = FILENAME;
	dinamyc = false;
	adapt = false;
	adaptVal = 0;
	bufferSize = 0;
	unlimitedBuffers = false;
	for(int i = 0; i < SIZE; i++) {
		for(int i = 0; i < SIZE; i++) {
				float r = (rand()%110);
				r/=100;
				example.push_back(r);
				exampleBuffer.push_back(0);
			}
		buffer.push_back(exampleBuffer);
		exampleBuffer.clear();
		dataChains.push_back(example);
		example.clear();
	}

}
markovChains::markovChains(std::string FILENAME) {
	std::ifstream loader ;
	fileName = FILENAME;
	loader.open(FILENAME+".mch");
	std::string	   bufferl1;
	loader 		>> bufferl1;

	int SIZE = std::atof(bufferl1.c_str());
	for(int i = 0; i < SIZE; i++) {
		for(int o = 0; o < SIZE; o++) {
			loader 		>> bufferl1;
			float val = std::atof(bufferl1.c_str());
			example.push_back(val);
			exampleBuffer.push_back(0);
		}
		dataChains.push_back(example);
		example.clear();
		buffer.push_back(exampleBuffer);
		exampleBuffer.clear();
	}
	loader 		>> bufferl1;
	staticBuffer = std::atoi(bufferl1.c_str());
	loader 		>> bufferl1;
	adaptBufferSize = std::atoi(bufferl1.c_str());
	loader 		>> bufferl1;
	dinamyc = std::atoi(bufferl1.c_str());
	loader 		>> bufferl1;
	adapt = std::atoi(bufferl1.c_str());
	loader 		>> bufferl1;
	adaptVal = std::atoi(bufferl1.c_str());
	loader 		>> bufferl1;
	bufferSize = std::atoi(bufferl1.c_str());
	loader 		>> bufferl1;
	unlimitedBuffers = std::atoi(bufferl1.c_str());
	loader.close()		 ;




	//std::cout << "111111111" << std::endl;



	if(dinamyc) {
		std::ifstream loader;
		loader.open(fileName+".mset");
		std::string bufferl;
		loader >> bufferl;
		//std::cout << "222222222222" << std::endl;
		if(dataChains.size()==std::atoi(bufferl.c_str())) {
			loader >> bufferl;
			if("false"==bufferl) {
			for(int i = 0; i < dataChains.size(); i++) {
				loader >> bufferl;
				if(bufferl=="(") {
					loader >> bufferl;
					float all = 0;

					while(bufferl!=")") {
						buffer[i][std::atoi(bufferl.c_str())]++;
						all++;
						loader >> bufferl;
					}
				} else {
					std::cerr << "error" << std::endl;
					break;
				}
			}
		} else if("true"==bufferl) {
					for(int i = 0; i < dataChains.size(); i++) {
						loader >> bufferl;
						if(bufferl=="(") {
							loader >> bufferl;
							//std::cout << "333333333" << std::endl;
							for(int o = 0; o < dataChains.size(); o++) {
								buffer[i][o]+=1;
								//std::cout << "44444444" << std::endl;
								//std::cout << std::atoi(bufferl.c_str()) << std::endl;
								buffer[i][o]+=std::atoi(bufferl.c_str());
								//std::cout << "454545454545" << std::endl;
								loader >> bufferl;
								//std::cout << "55555555" << std::endl;
							}
							//std::cout << "666666666" << std::endl;
							//loader >> bufferl;
						} else {
							std::cerr << "error" << std::endl;
							break;
						}
					}

		}
	}
		loader.close();
	}













}
void markovChains::save() {
	std::ofstream saver;
	saver.open(fileName+".mch");
	saver << dataChains.size() << " ";
	for(int i = 0; i < dataChains.size(); i++) {
			for(int o = 0; o < dataChains.size(); o++) {
				saver << dataChains[i][o] << " ";
			}
			saver << std::endl;
		}
	saver 		<< staticBuffer << " ";
	saver 		<< adaptBufferSize << " ";
	saver 		<< dinamyc << " ";
	saver 		<< adapt << " ";
	saver 		<< adaptVal << " ";
	saver 		<< bufferSize << " ";
	saver 		<< unlimitedBuffers << " ";
	saver.flush();
	saver.close();
	if(dinamyc) {
		saver.open(fileName+".mset");
		saver << buffer.size() << " true ";
		for(int i = 0; i < buffer.size(); i++) {
			saver << "( ";
			for(int o = 0; o < buffer.size(); o++) {
				saver << buffer[i][o] << " ";
			}
			saver << ") ";
			saver << std::endl;
		}
	}
}
void markovChains::load() {
	if(!dinamyc) {
	std::ifstream loader ;
	loader.open(fileName+".mch");
	std::string	   buffer;
	loader 		>> buffer;

	int SIZE = std::atoi(buffer.c_str());
	for(int i = 0; i < SIZE; i++) {
		for(int o = 0; o < SIZE; o++) {
			loader 		>> buffer;
			float val = std::atof(buffer.c_str());
			example.push_back(val);
		}
		dataChains.push_back(example);
		example.clear();
	}
		loader 		>> buffer;
		staticBuffer = std::atoi(buffer.c_str());
		loader 		>> buffer;
		adaptBufferSize = std::atoi(buffer.c_str());
		loader 		>> buffer;
		dinamyc = std::atoi(buffer.c_str());
		loader 		>> buffer;
		adapt = std::atoi(buffer.c_str());
		loader 		>> buffer;
		adaptVal = std::atoi(buffer.c_str());
		loader 		>> buffer;
		bufferSize = std::atoi(buffer.c_str());
		loader 		>> buffer;
		unlimitedBuffers = std::atoi(buffer.c_str());
	loader.close()		 ;
	}
}
markovChains::~markovChains() {
	for(int i = 0; i < dataChains.size(); i++) {
		dataChains[i].clear();
	}
	dataChains.clear();
	// TODO Auto-generated destructor stub
}
void markovChains::run() {
	if(autoDinamycPos()) {
		if(dinamyc) {
					if(unlimitedBuffers) {
						buffer[lastPos][pos]++;
					} else {
							float all = 0;
							for(int i = 0; i < buffer[lastPos].size(); i++) {
							all+=dataChains[lastPos][i];
						}
							if(all<bufferSize) {
								buffer[lastPos][pos]++;
							} else {
								if(!staticBuffer) {
									for(int i = 0; i < buffer[lastPos].size(); i++) {
										buffer[lastPos][i]--;
									}
									buffer[lastPos][pos]++;
								}
							}
					}
				}

	for(int i = 0; i < dataChains.size(); i++) {
		float r = rand()%100;
		r/=100;
		if(r < dataChains[pos][i]) {
			IndexToPos = i;
			toPos = dataChains[pos][i];
			lastPos = pos;
			pos = i;
			break;
		}
	}
	if(dinamyc) {
	for(int i = 0; i < dataChains.size(); i++) {
		float all = 0;
		for(int o = 0; o < dataChains[i].size(); o++) {
			all +=buffer[i][o];
		}
		float oneProc = all/100;
		for(int o = 0; o < dataChains[i].size(); o++) {
			float proc = buffer[i][o]/oneProc;
			dataChains[i][o] = proc/100;
		}
	}
	}
	}
}

bool markovChains::autoDinamycPos() {
	int size = dataChains.size();
	if(pos-size>=0) {
		if(dinamyc) {
			for(int o = 0; o < pos-size+1; o++) {
				for(int i = 0; i < dataChains.size(); i++) {
					dataChains[i].push_back(0);
					buffer[i].push_back(0);
				}
			}
			for(int i = 0; i < pos-size+1; i++) {
				dataChains.push_back(example);
				buffer.push_back(exampleBuffer);
				for(int o = 0; o < dataChains[0].size(); o++) {
					dataChains[dataChains.size()-1].push_back(adaptVal);
					buffer[buffer.size()-1].push_back(1);
				}
			}
			if(adaptBufferSize) {
				bufferSize = dataChains.size()*100;
			}
			return true;
		} else {
			std::cerr << "error, pos out of index" << std::endl;
			return false;
		}
	}
	return true;
}

void markovChains::learn(std::string dataSet) {
	if(!dinamyc) {
	std::ifstream loader;
	loader.open(dataSet+".mset");
	std::string buffer;
	loader >> buffer;
	if(dataChains.size()==std::atoi(buffer.c_str())) {
		loader >> buffer;
		if("false"==buffer) {
		for(int i = 0; i < dataChains.size(); i++) {
			loader >> buffer;
			if(buffer=="(") {
				loader >> buffer;
				float all = 0;
				std::vector<int> count;
				for(int o = 0; o < dataChains.size(); o++) {
					count.push_back(0);
				}
				while(buffer!=")") {
					count[std::atoi(buffer.c_str())]++;
					all++;
					loader >> buffer;
				}
				float oneProc = all/100;
				for(int o = 0; o < count.size();o++) {
					float proc = count[o]/oneProc;
					dataChains[i][o] = proc/100;
					}
			} else {
				std::cerr << "error" << std::endl;
				break;
			}
		}
	} else if("true"==buffer) {
				for(int i = 0; i < dataChains.size(); i++) {
					loader >> buffer;
					if(buffer=="(") {
						loader >> buffer;
						float all = 0;
						std::vector<int> count;
						for(int o = 0; o < dataChains.size(); o++) {
							count.push_back(0);
						}
						for(int o = 0; o < dataChains.size(); o++) {
							count[o]+=std::atoi(buffer.c_str());
							all+=std::atoi(buffer.c_str());
							loader >> buffer;
						}
						loader >> buffer;
						float oneProc = all/100;
						for(int o = 0; o < count.size();o++) {
							float proc = count[o]/oneProc;
							dataChains[i][o] = proc/100;
							}
					} else {
						std::cerr << "error" << std::endl;
						break;
					}
				}

	}
}
	loader.close();
} else {
	std::cerr << "setted dinamic=true, because use learn impossible" << std::endl;
}
}
