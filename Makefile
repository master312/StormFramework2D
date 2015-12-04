CC = g++
CFLAGS  = -g -Wall -std=c++11 
LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer 
OBJDIR = objects/
EXNAME = a.out

default: debug

$(OBJDIR)cTestState.o: src/cTestState.cpp src/cTestState.h
	$(CC) $(CFLAGS) -c src/cTestState.cpp $(LIBS) -o $(OBJDIR)cTestState.o 
$(OBJDIR)main.o: src/main.cpp 
	$(CC) $(CFLAGS) -c src/main.cpp $(LIBS) -o $(OBJDIR)main.o 
$(OBJDIR)tinyxml2.o: src/storm/thirdparty/tinyxml2.cpp src/storm/thirdparty/tinyxml2.h
	$(CC) $(CFLAGS) -c src/storm/thirdparty/tinyxml2.cpp $(LIBS) -o $(OBJDIR)tinyxml2.o 
$(OBJDIR)cAnimation.o: src/storm/animations/cAnimation.cpp src/storm/animations/cAnimation.h
	$(CC) $(CFLAGS) -c src/storm/animations/cAnimation.cpp $(LIBS) -o $(OBJDIR)cAnimation.o 
$(OBJDIR)cAnimationManager.o: src/storm/animations/cAnimationManager.cpp src/storm/animations/cAnimationManager.h
	$(CC) $(CFLAGS) -c src/storm/animations/cAnimationManager.cpp $(LIBS) -o $(OBJDIR)cAnimationManager.o 
$(OBJDIR)animationsMain.o: src/storm/animations/animationsMain.cpp src/storm/animations/animationsMain.h
	$(CC) $(CFLAGS) -c src/storm/animations/animationsMain.cpp $(LIBS) -o $(OBJDIR)animationsMain.o 
$(OBJDIR)cMain.o: src/storm/cMain.cpp src/storm/cMain.h
	$(CC) $(CFLAGS) -c src/storm/cMain.cpp $(LIBS) -o $(OBJDIR)cMain.o 
$(OBJDIR)cTextureManager.o: src/storm/core/graphics/cTextureManager.cpp src/storm/core/graphics/cTextureManager.h
	$(CC) $(CFLAGS) -c src/storm/core/graphics/cTextureManager.cpp $(LIBS) -o $(OBJDIR)cTextureManager.o 
$(OBJDIR)cGraphicsSDL2.o: src/storm/core/graphics/SDL2/cGraphicsSDL2.cpp src/storm/core/graphics/SDL2/cGraphicsSDL2.h
	$(CC) $(CFLAGS) -c src/storm/core/graphics/SDL2/cGraphicsSDL2.cpp $(LIBS) -o $(OBJDIR)cGraphicsSDL2.o 
$(OBJDIR)cTextureSDL2.o: src/storm/core/graphics/SDL2/cTextureSDL2.cpp src/storm/core/graphics/SDL2/cTextureSDL2.h
	$(CC) $(CFLAGS) -c src/storm/core/graphics/SDL2/cTextureSDL2.cpp $(LIBS) -o $(OBJDIR)cTextureSDL2.o 
$(OBJDIR)cGraphicsManager.o: src/storm/core/graphics/cGraphicsManager.cpp src/storm/core/graphics/cGraphicsManager.h
	$(CC) $(CFLAGS) -c src/storm/core/graphics/cGraphicsManager.cpp $(LIBS) -o $(OBJDIR)cGraphicsManager.o 
$(OBJDIR)graphicsMain.o: src/storm/core/graphics/graphicsMain.cpp src/storm/core/graphics/graphicsMain.h
	$(CC) $(CFLAGS) -c src/storm/core/graphics/graphicsMain.cpp $(LIBS) -o $(OBJDIR)graphicsMain.o 
$(OBJDIR)cGraphicsBase.o: src/storm/core/graphics/cGraphicsBase.cpp src/storm/core/graphics/cGraphicsBase.h
	$(CC) $(CFLAGS) -c src/storm/core/graphics/cGraphicsBase.cpp $(LIBS) -o $(OBJDIR)cGraphicsBase.o 
$(OBJDIR)cBitmapFontManager.o: src/storm/core/graphics/cBitmapFontManager.cpp src/storm/core/graphics/cBitmapFontManager.h
	$(CC) $(CFLAGS) -c src/storm/core/graphics/cBitmapFontManager.cpp $(LIBS) -o $(OBJDIR)cBitmapFontManager.o 
$(OBJDIR)cTextureBase.o: src/storm/core/graphics/cTextureBase.cpp src/storm/core/graphics/cTextureBase.h
	$(CC) $(CFLAGS) -c src/storm/core/graphics/cTextureBase.cpp $(LIBS) -o $(OBJDIR)cTextureBase.o 
$(OBJDIR)interruptsMain.o: src/storm/core/interrupts/interruptsMain.cpp src/storm/core/interrupts/interruptsMain.h
	$(CC) $(CFLAGS) -c src/storm/core/interrupts/interruptsMain.cpp $(LIBS) -o $(OBJDIR)interruptsMain.o 
$(OBJDIR)cInterruptManager.o: src/storm/core/interrupts/cInterruptManager.cpp src/storm/core/interrupts/cInterruptManager.h
	$(CC) $(CFLAGS) -c src/storm/core/interrupts/cInterruptManager.cpp $(LIBS) -o $(OBJDIR)cInterruptManager.o 
$(OBJDIR)cFileSystem.o: src/storm/core/framework/cFileSystem.cpp src/storm/core/framework/cFileSystem.h
	$(CC) $(CFLAGS) -c src/storm/core/framework/cFileSystem.cpp $(LIBS) -o $(OBJDIR)cFileSystem.o 
$(OBJDIR)cFileParser.o: src/storm/core/framework/cFileParser.cpp src/storm/core/framework/cFileParser.h
	$(CC) $(CFLAGS) -c src/storm/core/framework/cFileParser.cpp $(LIBS) -o $(OBJDIR)cFileParser.o 
$(OBJDIR)cBinary.o: src/storm/core/framework/cBinary.cpp src/storm/core/framework/cBinary.h
	$(CC) $(CFLAGS) -c src/storm/core/framework/cBinary.cpp $(LIBS) -o $(OBJDIR)cBinary.o 
$(OBJDIR)cString.o: src/storm/core/framework/cString.cpp src/storm/core/framework/cString.h
	$(CC) $(CFLAGS) -c src/storm/core/framework/cString.cpp $(LIBS) -o $(OBJDIR)cString.o 
$(OBJDIR)cLogger.o: src/storm/core/framework/cLogger.cpp src/storm/core/framework/cLogger.h
	$(CC) $(CFLAGS) -c src/storm/core/framework/cLogger.cpp $(LIBS) -o $(OBJDIR)cLogger.o 
$(OBJDIR)frameworkMain.o: src/storm/core/framework/frameworkMain.cpp src/storm/core/framework/frameworkMain.h
	$(CC) $(CFLAGS) -c src/storm/core/framework/frameworkMain.cpp $(LIBS) -o $(OBJDIR)frameworkMain.o 
$(OBJDIR)cVector2.o: src/storm/core/framework/cVector2.cpp src/storm/core/framework/cVector2.h
	$(CC) $(CFLAGS) -c src/storm/core/framework/cVector2.cpp $(LIBS) -o $(OBJDIR)cVector2.o 
$(OBJDIR)cBinaryFile.o: src/storm/core/framework/cBinaryFile.cpp src/storm/core/framework/cBinaryFile.h
	$(CC) $(CFLAGS) -c src/storm/core/framework/cBinaryFile.cpp $(LIBS) -o $(OBJDIR)cBinaryFile.o 
$(OBJDIR)cEventSDL2.o: src/storm/core/events/SDL2/cEventSDL2.cpp src/storm/core/events/SDL2/cEventSDL2.h
	$(CC) $(CFLAGS) -c src/storm/core/events/SDL2/cEventSDL2.cpp $(LIBS) -o $(OBJDIR)cEventSDL2.o 
$(OBJDIR)cEventManager.o: src/storm/core/events/cEventManager.cpp src/storm/core/events/cEventManager.h
	$(CC) $(CFLAGS) -c src/storm/core/events/cEventManager.cpp $(LIBS) -o $(OBJDIR)cEventManager.o 
$(OBJDIR)eventsMain.o: src/storm/core/events/eventsMain.cpp src/storm/core/events/eventsMain.h
	$(CC) $(CFLAGS) -c src/storm/core/events/eventsMain.cpp $(LIBS) -o $(OBJDIR)eventsMain.o 
$(OBJDIR)layersMain.o: src/storm/core/layers/layersMain.cpp src/storm/core/layers/layersMain.h
	$(CC) $(CFLAGS) -c src/storm/core/layers/layersMain.cpp $(LIBS) -o $(OBJDIR)layersMain.o 
$(OBJDIR)cLayerManager.o: src/storm/core/layers/cLayerManager.cpp src/storm/core/layers/cLayerManager.h
	$(CC) $(CFLAGS) -c src/storm/core/layers/cLayerManager.cpp $(LIBS) -o $(OBJDIR)cLayerManager.o 
$(OBJDIR)cLayerBase.o: src/storm/core/layers/cLayerBase.cpp src/storm/core/layers/cLayerBase.h
	$(CC) $(CFLAGS) -c src/storm/core/layers/cLayerBase.cpp $(LIBS) -o $(OBJDIR)cLayerBase.o 
$(OBJDIR)storm.o: src/storm/storm.cpp src/storm/storm.h
	$(CC) $(CFLAGS) -c src/storm/storm.cpp $(LIBS) -o $(OBJDIR)storm.o 
$(OBJDIR)cSoundBase.o: src/storm/audio/cSoundBase.cpp src/storm/audio/cSoundBase.h
	$(CC) $(CFLAGS) -c src/storm/audio/cSoundBase.cpp $(LIBS) -o $(OBJDIR)cSoundBase.o 
$(OBJDIR)cMusicBase.o: src/storm/audio/cMusicBase.cpp src/storm/audio/cMusicBase.h
	$(CC) $(CFLAGS) -c src/storm/audio/cMusicBase.cpp $(LIBS) -o $(OBJDIR)cMusicBase.o 
$(OBJDIR)cAudioBase.o: src/storm/audio/cAudioBase.cpp src/storm/audio/cAudioBase.h
	$(CC) $(CFLAGS) -c src/storm/audio/cAudioBase.cpp $(LIBS) -o $(OBJDIR)cAudioBase.o 
$(OBJDIR)cAudioManager.o: src/storm/audio/cAudioManager.cpp src/storm/audio/cAudioManager.h
	$(CC) $(CFLAGS) -c src/storm/audio/cAudioManager.cpp $(LIBS) -o $(OBJDIR)cAudioManager.o 

debug: $(OBJDIR)cTestState.o $(OBJDIR)main.o $(OBJDIR)tinyxml2.o $(OBJDIR)cAnimation.o $(OBJDIR)cAnimationManager.o $(OBJDIR)animationsMain.o $(OBJDIR)cMain.o $(OBJDIR)cTextureManager.o $(OBJDIR)cGraphicsSDL2.o $(OBJDIR)cTextureSDL2.o $(OBJDIR)cGraphicsManager.o $(OBJDIR)graphicsMain.o $(OBJDIR)cGraphicsBase.o $(OBJDIR)cBitmapFontManager.o $(OBJDIR)cTextureBase.o $(OBJDIR)interruptsMain.o $(OBJDIR)cInterruptManager.o $(OBJDIR)cFileSystem.o $(OBJDIR)cFileParser.o $(OBJDIR)cBinary.o $(OBJDIR)cString.o $(OBJDIR)cLogger.o $(OBJDIR)frameworkMain.o $(OBJDIR)cVector2.o $(OBJDIR)cBinaryFile.o $(OBJDIR)cEventSDL2.o $(OBJDIR)cEventManager.o $(OBJDIR)eventsMain.o $(OBJDIR)layersMain.o $(OBJDIR)cLayerManager.o $(OBJDIR)cLayerBase.o $(OBJDIR)storm.o $(OBJDIR)cSoundBase.o $(OBJDIR)cMusicBase.o $(OBJDIR)cAudioBase.o $(OBJDIR)cAudioManager.o 
	$(CC) $(CFLAGS) $(OBJDIR)cTestState.o $(OBJDIR)main.o $(OBJDIR)tinyxml2.o $(OBJDIR)cAnimation.o $(OBJDIR)cAnimationManager.o $(OBJDIR)animationsMain.o $(OBJDIR)cMain.o $(OBJDIR)cTextureManager.o $(OBJDIR)cGraphicsSDL2.o $(OBJDIR)cTextureSDL2.o $(OBJDIR)cGraphicsManager.o $(OBJDIR)graphicsMain.o $(OBJDIR)cGraphicsBase.o $(OBJDIR)cBitmapFontManager.o $(OBJDIR)cTextureBase.o $(OBJDIR)interruptsMain.o $(OBJDIR)cInterruptManager.o $(OBJDIR)cFileSystem.o $(OBJDIR)cFileParser.o $(OBJDIR)cBinary.o $(OBJDIR)cString.o $(OBJDIR)cLogger.o $(OBJDIR)frameworkMain.o $(OBJDIR)cVector2.o $(OBJDIR)cBinaryFile.o $(OBJDIR)cEventSDL2.o $(OBJDIR)cEventManager.o $(OBJDIR)eventsMain.o $(OBJDIR)layersMain.o $(OBJDIR)cLayerManager.o $(OBJDIR)cLayerBase.o $(OBJDIR)storm.o $(OBJDIR)cSoundBase.o $(OBJDIR)cMusicBase.o $(OBJDIR)cAudioBase.o $(OBJDIR)cAudioManager.o  -o "$(EXNAME)" $(LIBS)