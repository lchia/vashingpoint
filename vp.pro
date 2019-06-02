#-------------------------------------------------
#
# Project created by QtCreator 2019-06-01T06:25:57
#
#-------------------------------------------------
QT += core
QT -= gui

TARGET = vp
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

# OpenCV 3.1
INCLUDEPATH += /home/haha/local/opencv-3.4.0/include \
               /home/haha/local/opencv-3.4.0/include/opencv \
               /home/haha/local/opencv-3.4.0/include/opencv2

LIBS += -L/home/haha/local/opencv-3.4.0/lib
LIBS += -lopencv_core -lopencv_video -lopencv_videoio -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc -lopencv_shape -lopencv_videoio -lopencv_photo -lopencv_features2d -lopencv_objdetect -lopencv_calib3d -lopencv_ml

# NCNN
INCLUDEPATH +=/home/haha/workspaces/test/ncnn/src
INCLUDEPATH +=/home/haha/workspaces/test/ncnn/build/src

LIBS += -L/home/haha/workspaces/test/ncnn/build/src
LIBS += -lncnn -fopenmp

# CUDA
INCLUDEPATH += /usr/local/cuda/include
LIBS += -L/usr/local/cuda/lib64
LIBS += -lcudart

# armadillo
INCLUDEPATH +=/usr/include/armadillo_bits \
              /usr/include \
              /usr/include/hdf5/serial

LIBS += -L/usr/lib/x86_64-linux-gnu \
        -L/usr/lib/lapack \
        -L/usr/lib \
        -L/home/haha/anaconda3/lib \
        -L/home/haha/anaconda3/pkgs/mkl-2017.0.1-0/lib

LIBS += -larmadillo -llapack -lopenblas -lhdf5_cpp -lhdf5_hl_cpp -lhdf5 -lhdf5_hl -lmkl_rt
#CONFIG += c++14

CONFIG += c++11

SOURCES += \
        eval_vp.cpp \
        linedetect.cpp \
        lsd.c \
        main.cpp \
        undistortion.cpp

HEADERS += \
        eval_vp.h \
        linedetect.h \
        lsd.h \
        undistortion.h
