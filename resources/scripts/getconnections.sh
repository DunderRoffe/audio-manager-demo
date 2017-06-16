#!/bin/sh

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

dbus-send --session --print-reply --dest=org.genivi.audiomanager /org/genivi/audiomanager/commandinterface org.genivi.audiomanager.commandinterface.GetListMainConnections | awk '/struct/ {getline;getline;SOURCE=$2;getline;SINK=$2;getline;getline;STATUS=$2;print "Source"SOURCE"-->Sink"SINK"(Status"STATUS")";}' | sed 's/Source100/MediaPlayer/g' |  sed 's/Source101/NaviPlayer/g' | sed 's/Source102/TTSPlayer/g' | sed 's/Source103/Skype/g' | sed 's/Source104/ReverseBeep/g' | sed 's/Sink100/AlsaPrimary/g' | sed 's/Sink101/AlsaSecondary/g' | sed 's/Status1/Connecting/g' | sed 's/Status2/Connected/g' | sed 's/Status3/Disconnecting/g' | sed 's/Status4/Disconnected/g' | sed 's/Status5/Suspended/g'
