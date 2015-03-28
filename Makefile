CC 	=	g++
SOURCE 	=	main.cpp\
		RecordAudio.cpp\
		WAVFormat.cpp\
		WAVFile.cpp\
		Process.cpp\
		ComputeFFT.cpp\
		CaptureAudio.cpp\
		FIRFilter.cpp
		
LIB 	=	-lalut\
		-lopenal\
		-lpthread\
		-lm
		
OUT	=	-o build
all:
	${CC} ${SOURCE} ${OUT} ${LIB}
clean:
	rm build fileRecord.wav