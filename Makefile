EXEC 	=	openclTest
SOURCES =	openclTest.cpp

# WORKS WITH OSX
default:
	g++ -Wall -g -o ${EXEC} ${SOURCES} -framework OpenCL

clean:
	rm ${EXEC}
	rm -r ${EXEC}.dSYM



# in case of other platforms Like Linux, you need to adapt the make file, like:
# default:
#	g++ -Wall -g -o ${EXEC} ${SOURCES} -l OpenCL