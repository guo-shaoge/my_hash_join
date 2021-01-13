DIR_SRC = ./src
DIR_BIN = ./bin

JOIN_SRC = ${DIR_SRC}/multi_thread_hash_join.cc
JOIN_MAIN = my_hash_join
COMP_NDV_MAIN = compute_ndv
GEN_DATA_MAIN = gen_data

CXXFLAGS = -pthread -std=c++11
ALL_BINS = ${DIR_BIN}/${JOIN_MAIN} ${DIR_BIN}/${COMP_NDV_MAIN} ${DIR_BIN}/${GEN_DATA_MAIN} ${DIR_BIN}/${JOIN_MAIN}_heavy_key_equal

all: ${JOIN_MAIN} ${COMP_NDV_MAIN} ${GEN_DATA_MAIN} ${JOIN_MAIN}_heavy_key_equal

${JOIN_MAIN}: ${JOIN_SRC} ${DIR_SRC}/${JOIN_MAIN}.cc 
	g++ -o ${DIR_BIN}/$@ $^ ${CXXFLAGS}
${JOIN_MAIN}_heavy_key_equal: ${JOIN_SRC} ${DIR_SRC}/${JOIN_MAIN}.cc
	g++ -o ${DIR_BIN}/$@ $^ ${CXXFLAGS} -DHEAVY_KEY_EQUAL
${GEN_DATA_MAIN}: ${DIR_SRC}/${GEN_DATA_MAIN}.cc ${JOIN_SRC}
	g++ -o ${DIR_BIN}/$@ $^ ${CXXFLAGS}
${COMP_NDV_MAIN}: ${DIR_SRC}/${COMP_NDV_MAIN}.cc ${JOIN_SRC}
	g++ -o ${DIR_BIN}/$@ $^ ${CXXFLAGS}

.PHONY: clean
clean:
	rm -rf ${ALL_BINS}
