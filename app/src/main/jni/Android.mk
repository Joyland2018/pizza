LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                                      ../../Classes/AppDelegate.cpp \
                                      ../../Classes/BuyPage.cpp \
                                      ../../Classes/LogoScene.cpp \
                                      ../../Classes/GameManager.cpp \
                                      ../../Classes/HelloWorldScene.cpp \
                                      ../../Classes/pizza/AddTopping.cpp \
                                      ../../Classes/pizza/BakedPizza.cpp \
                                      ../../Classes/pizza/CutMaterial.cpp \
                                      ../../Classes/pizza/CutPizza.cpp \
                                      ../../Classes/pizza/CutTopping.cpp \
                                      ../../Classes/pizza/MakeDough.cpp \
                                      ../../Classes/pizza/MakePizza.cpp \
                                      ../../Classes/pizza/MakeSauce.cpp \
                                      ../../Classes/pizza/PizzaLineSprite.cpp \
                                      ../../Classes/pizza/PizzaManager.cpp \
                                      ../../Classes/pizza/SelectPizza.cpp \
                                      ../../Classes/pizza/SelectTopping.cpp \
                                      ../../Classes/pizza/FirstScene.cpp \


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
                    $(LOCAL_PATH)/../../Classes/pizza \


LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

APP_ALLOW_MISSING_DEPS :=true
LOCAL_ALLOW_UNDEFINED_SYMBOLS := true

include $(BUILD_SHARED_LIBRARY)

$(call import-add-path,$(LOCAL_PATH))

$(call import-module,cocos2dx)
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
$(call import-module,CocosDenshion/android)
$(call import-module,extensions)
$(call import-module,external/Box2D)
$(call import-module,external/chipmunk)
