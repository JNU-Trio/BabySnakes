EXECUTABLE = BabySnakes

INCLUDES = -I.. -I../Classes

SOURCES = main.cpp \
../Classes/MapAttribute.cpp\
../Classes/Snakes.cpp \
../Classes/FightScene.cpp \
../Classes/StartScene.cpp \
../Classes/GameOverScene.cpp \
../Classes/AppDelegate.cpp \
../Classes/InfoLayer.cpp

COCOS_ROOT = /home/toufu/Software/cocos2d-x-2.2.3
include $(COCOS_ROOT)/cocos2dx/proj.linux/cocos2dx.mk

SHAREDLIBS += -lcocos2d -lcocosdenshion
COCOS_LIBS = $(LIB_DIR)/libcocos2d.so $(LIB_DIR)/libcocosdenshion.so
INCLUDES += -I$(COCOS_ROOT)/CocosDenshion/include

$(TARGET): $(OBJECTS) $(STATICLIBS) $(COCOS_LIBS) $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_LINK)$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(SHAREDLIBS) $(STATICLIBS)

$(OBJ_DIR)/%.o: %.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@

$(OBJ_DIR)/%.o: ../%.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@
