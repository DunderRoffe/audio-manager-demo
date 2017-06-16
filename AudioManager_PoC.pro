#-------------------------------------------------
#
# Project created by QtCreator 2012-03-04T09:20:56
#
#-------------------------------------------------

# SPDX license identifier: MPL-2.0
#
# Copyright (C) 2011-2014, Wind River Systems
# Copyright (C) 2014, GENIVI Alliance
#
# This file is part of GENIVI AudioManager PoC.
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License (MPL), v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
# For further information see http://www.genivi.org/.
#
# List of changes:
#
# 21.09.2014, Adrian Scarlat, First version of the code;
#                             Added Copyright and License information;
#

QT       += core
QT       += gui
QT       += dbus
QT       += qml
QT       += quick
QT       += widgets

TARGET = AudioManager_PoC
CONFIG   += console
CONFIG   -= app_bundle
CONFIG    +=qml_debug

TEMPLATE = app

SOURCES += business_logic/src/main.cpp \
           business_logic/src/qmlbuttoneventsreceiver.cpp \
           business_logic/src/volumechart.cpp \
           business_logic/src/audioManagerInterface.cpp

HEADERS += business_logic/include/qmlbuttoneventsreceiver.h \
           business_logic/include/volumechart.h \
           business_logic/include/audioManagerInterface.h

RESOURCES += AudioManager_PoC.qrc

scripts.files += resources/scripts/getconnections.sh \
                 resources/scripts/getvolumes_val.sh \
                 resources/scripts/playCarReverse.sh \
                 resources/scripts/playmusic.sh \
                 resources/scripts/playnav.sh \
                 resources/scripts/playtel.sh \
                 resources/scripts/playtts.sh \
                 resources/scripts/setvolume.sh \
                 resources/scripts/stopCarReverse.sh \
                 resources/scripts/stopmusic.sh \
                 resources/scripts/stopnav.sh \
                 resources/scripts/stoptel.sh \
                 resources/scripts/stoptts.sh \
                 resources/scripts/start_am-poc.sh
scripts.path += /opt/audiomanager-poc/scripts

audio.files += resources/audio/car_reverse.wav \
               resources/audio/navigation.wav \
               resources/audio/telephone-ring.wav \
               resources/audio/tts.wav
audio.path += /opt/audiomanager-poc/audio-files

target.path = /usr/bin
INSTALLS += target \
            scripts \
            audio
