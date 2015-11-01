CC = g++
CFLAGS  = -g -Wall -std=c++11 
LIBS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer 
OBJDIR = objects/
EXNAME = a.out

default: debug

$(OBJDIR)main.o: src/main.cpp 
	$(CC) $(CFLAGS) -c src/main.cpp $(LIBS) -o $(OBJDIR)main.o 
$(OBJDIR)animationMain.o: src/storm/animation/animationMain.cpp src/storm/animation/animationMain.h
	$(CC) $(CFLAGS) -c src/storm/animation/animationMain.cpp $(LIBS) -o $(OBJDIR)animationMain.o 
$(OBJDIR)cAnimation.o: src/storm/animation/cAnimation.cpp src/storm/animation/cAnimation.h
	$(CC) $(CFLAGS) -c src/storm/animation/cAnimation.cpp $(LIBS) -o $(OBJDIR)cAnimation.o 
$(OBJDIR)cAnimationManager.o: src/storm/animation/cAnimationManager.cpp src/storm/animation/cAnimationManager.h
	$(CC) $(CFLAGS) -c src/storm/animation/cAnimationManager.cpp $(LIBS) -o $(OBJDIR)cAnimationManager.o 
$(OBJDIR)cAudioBase.o: src/storm/audio/cAudioBase.cpp src/storm/audio/cAudioBase.h
	$(CC) $(CFLAGS) -c src/storm/audio/cAudioBase.cpp $(LIBS) -o $(OBJDIR)cAudioBase.o 
$(OBJDIR)cAudioManager.o: src/storm/audio/cAudioManager.cpp src/storm/audio/cAudioManager.h
	$(CC) $(CFLAGS) -c src/storm/audio/cAudioManager.cpp $(LIBS) -o $(OBJDIR)cAudioManager.o 
$(OBJDIR)cMusicBase.o: src/storm/audio/cMusicBase.cpp src/storm/audio/cMusicBase.h
	$(CC) $(CFLAGS) -c src/storm/audio/cMusicBase.cpp $(LIBS) -o $(OBJDIR)cMusicBase.o 
$(OBJDIR)cSoundBase.o: src/storm/audio/cSoundBase.cpp src/storm/audio/cSoundBase.h
	$(CC) $(CFLAGS) -c src/storm/audio/cSoundBase.cpp $(LIBS) -o $(OBJDIR)cSoundBase.o 
$(OBJDIR)cTimedCallbackManager.o: src/storm/callback/cTimedCallbackManager.cpp src/storm/callback/cTimedCallbackManager.h
	$(CC) $(CFLAGS) -c src/storm/callback/cTimedCallbackManager.cpp $(LIBS) -o $(OBJDIR)cTimedCallbackManager.o 
$(OBJDIR)cMain.o: src/storm/cMain.cpp src/storm/cMain.h
	$(CC) $(CFLAGS) -c src/storm/cMain.cpp $(LIBS) -o $(OBJDIR)cMain.o 
$(OBJDIR)cEventManager.o: src/storm/core/events/cEventManager.cpp src/storm/core/events/cEventManager.h
	$(CC) $(CFLAGS) -c src/storm/core/events/cEventManager.cpp $(LIBS) -o $(OBJDIR)cEventManager.o 
$(OBJDIR)eventsMain.o: src/storm/core/events/eventsMain.cpp src/storm/core/events/eventsMain.h
	$(CC) $(CFLAGS) -c src/storm/core/events/eventsMain.cpp $(LIBS) -o $(OBJDIR)eventsMain.o 
$(OBJDIR)cEventSDL2.o: src/storm/core/events/SDL2/cEventSDL2.cpp src/storm/core/events/SDL2/cEventSDL2.h
	$(CC) $(CFLAGS) -c src/storm/core/events/SDL2/cEventSDL2.cpp $(LIBS) -o $(OBJDIR)cEventSDL2.o 
$(OBJDIR)cBinaryFile.o: src/storm/core/framework/cBinaryFile.cpp src/storm/core/framework/cBinaryFile.h
	$(CC) $(CFLAGS) -c src/storm/core/framework/cBinaryFile.cpp $(LIBS) -o $(OBJDIR)cBinaryFile.o 
$(OBJDIR)cData.o: src/storm/core/framework/cData.cpp src/storm/core/framework/cData.h
	$(CC) $(CFLAGS) -c src/storm/core/framework/cData.cpp $(LIBS) -o $(OBJDIR)cData.o 
$(OBJDIR)cFileParser.o: src/storm/core/framework/cFileParser.cpp src/storm/core/framework/cFileParser.h
	$(CC) $(CFLAGS) -c src/storm/core/framework/cFileParser.cpp $(LIBS) -o $(OBJDIR)cFileParser.o 
$(OBJDIR)cFileSystem.o: src/storm/core/framework/cFileSystem.cpp src/storm/core/framework/cFileSystem.h
	$(CC) $(CFLAGS) -c src/storm/core/framework/cFileSystem.cpp $(LIBS) -o $(OBJDIR)cFileSystem.o 
$(OBJDIR)cLogger.o: src/storm/core/framework/cLogger.cpp src/storm/core/framework/cLogger.h
	$(CC) $(CFLAGS) -c src/storm/core/framework/cLogger.cpp $(LIBS) -o $(OBJDIR)cLogger.o 
$(OBJDIR)cString.o: src/storm/core/framework/cString.cpp src/storm/core/framework/cString.h
	$(CC) $(CFLAGS) -c src/storm/core/framework/cString.cpp $(LIBS) -o $(OBJDIR)cString.o 
$(OBJDIR)cVector2.o: src/storm/core/framework/cVector2.cpp src/storm/core/framework/cVector2.h
	$(CC) $(CFLAGS) -c src/storm/core/framework/cVector2.cpp $(LIBS) -o $(OBJDIR)cVector2.o 
$(OBJDIR)frameworkMain.o: src/storm/core/framework/frameworkMain.cpp src/storm/core/framework/frameworkMain.h
	$(CC) $(CFLAGS) -c src/storm/core/framework/frameworkMain.cpp $(LIBS) -o $(OBJDIR)frameworkMain.o 
$(OBJDIR)cGraphicsBase.o: src/storm/core/graphics/cGraphicsBase.cpp src/storm/core/graphics/cGraphicsBase.h
	$(CC) $(CFLAGS) -c src/storm/core/graphics/cGraphicsBase.cpp $(LIBS) -o $(OBJDIR)cGraphicsBase.o 
$(OBJDIR)cGraphicsManager.o: src/storm/core/graphics/cGraphicsManager.cpp src/storm/core/graphics/cGraphicsManager.h
	$(CC) $(CFLAGS) -c src/storm/core/graphics/cGraphicsManager.cpp $(LIBS) -o $(OBJDIR)cGraphicsManager.o 
$(OBJDIR)cTextureBase.o: src/storm/core/graphics/cTextureBase.cpp src/storm/core/graphics/cTextureBase.h
	$(CC) $(CFLAGS) -c src/storm/core/graphics/cTextureBase.cpp $(LIBS) -o $(OBJDIR)cTextureBase.o 
$(OBJDIR)cTextureManager.o: src/storm/core/graphics/cTextureManager.cpp src/storm/core/graphics/cTextureManager.h
	$(CC) $(CFLAGS) -c src/storm/core/graphics/cTextureManager.cpp $(LIBS) -o $(OBJDIR)cTextureManager.o 
$(OBJDIR)graphicsMain.o: src/storm/core/graphics/graphicsMain.cpp src/storm/core/graphics/graphicsMain.h
	$(CC) $(CFLAGS) -c src/storm/core/graphics/graphicsMain.cpp $(LIBS) -o $(OBJDIR)graphicsMain.o 
$(OBJDIR)cGraphicsSDL2.o: src/storm/core/graphics/SDL2/cGraphicsSDL2.cpp src/storm/core/graphics/SDL2/cGraphicsSDL2.h
	$(CC) $(CFLAGS) -c src/storm/core/graphics/SDL2/cGraphicsSDL2.cpp $(LIBS) -o $(OBJDIR)cGraphicsSDL2.o 
$(OBJDIR)cTextureSDL2.o: src/storm/core/graphics/SDL2/cTextureSDL2.cpp src/storm/core/graphics/SDL2/cTextureSDL2.h
	$(CC) $(CFLAGS) -c src/storm/core/graphics/SDL2/cTextureSDL2.cpp $(LIBS) -o $(OBJDIR)cTextureSDL2.o 
$(OBJDIR)cStateBase.o: src/storm/core/states/cStateBase.cpp src/storm/core/states/cStateBase.h
	$(CC) $(CFLAGS) -c src/storm/core/states/cStateBase.cpp $(LIBS) -o $(OBJDIR)cStateBase.o 
$(OBJDIR)cStateManager.o: src/storm/core/states/cStateManager.cpp src/storm/core/states/cStateManager.h
	$(CC) $(CFLAGS) -c src/storm/core/states/cStateManager.cpp $(LIBS) -o $(OBJDIR)cStateManager.o 
$(OBJDIR)statesMain.o: src/storm/core/states/statesMain.cpp src/storm/core/states/statesMain.h
	$(CC) $(CFLAGS) -c src/storm/core/states/statesMain.cpp $(LIBS) -o $(OBJDIR)statesMain.o 
$(OBJDIR)storm.o: src/storm/storm.cpp src/storm/storm.h
	$(CC) $(CFLAGS) -c src/storm/storm.cpp $(LIBS) -o $(OBJDIR)storm.o 

debug: $(OBJDIR)main.o $(OBJDIR)animationMain.o $(OBJDIR)cAnimation.o $(OBJDIR)cAnimationManager.o $(OBJDIR)cAudioBase.o $(OBJDIR)cAudioManager.o $(OBJDIR)cMusicBase.o $(OBJDIR)cSoundBase.o $(OBJDIR)cTimedCallbackManager.o $(OBJDIR)cMain.o $(OBJDIR)cEventManager.o $(OBJDIR)eventsMain.o $(OBJDIR)cEventSDL2.o $(OBJDIR)cBinaryFile.o $(OBJDIR)cData.o $(OBJDIR)cFileParser.o $(OBJDIR)cFileSystem.o $(OBJDIR)cLogger.o $(OBJDIR)cString.o $(OBJDIR)cVector2.o $(OBJDIR)frameworkMain.o $(OBJDIR)cGraphicsBase.o $(OBJDIR)cGraphicsManager.o $(OBJDIR)cTextureBase.o $(OBJDIR)cTextureManager.o $(OBJDIR)graphicsMain.o $(OBJDIR)cGraphicsSDL2.o $(OBJDIR)cTextureSDL2.o $(OBJDIR)cStateBase.o $(OBJDIR)cStateManager.o $(OBJDIR)statesMain.o $(OBJDIR)storm.o 
	$(CC) $(CFLAGS) $(OBJDIR)main.o $(OBJDIR)animationMain.o $(OBJDIR)cAnimation.o $(OBJDIR)cAnimationManager.o $(OBJDIR)cAudioBase.o $(OBJDIR)cAudioManager.o $(OBJDIR)cMusicBase.o $(OBJDIR)cSoundBase.o $(OBJDIR)cTimedCallbackManager.o $(OBJDIR)cMain.o $(OBJDIR)cEventManager.o $(OBJDIR)eventsMain.o $(OBJDIR)cEventSDL2.o $(OBJDIR)cBinaryFile.o $(OBJDIR)cData.o $(OBJDIR)cFileParser.o $(OBJDIR)cFileSystem.o $(OBJDIR)cLogger.o $(OBJDIR)cString.o $(OBJDIR)cVector2.o $(OBJDIR)frameworkMain.o $(OBJDIR)cGraphicsBase.o $(OBJDIR)cGraphicsManager.o $(OBJDIR)cTextureBase.o $(OBJDIR)cTextureManager.o $(OBJDIR)graphicsMain.o $(OBJDIR)cGraphicsSDL2.o $(OBJDIR)cTextureSDL2.o $(OBJDIR)cStateBase.o $(OBJDIR)cStateManager.o $(OBJDIR)statesMain.o $(OBJDIR)storm.o  -o "$(EXNAME)" $(LIBS)