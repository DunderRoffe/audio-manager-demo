/****************************************************************************
**
** Copyright (C) 2011-2014, Wind River Systems
** Copyright (C) 2014, GENIVI Alliance
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.2

Rectangle {

   id: theRect
   property alias text: label.text;
   property alias icon: img.source;
   smooth: true;
   width: 150
   height:50
   border {
       color: "#55000000"
       width: 2
   }
   gradient: Gradient {
       GradientStop { position: 0.0; color: "#55444444" }
       GradientStop { position: 0.05; color: "#55888888" }
       GradientStop { id:gr;position: 0.8; color: "#55333333" }
       GradientStop { position: 1.0; color: "#55000000" }
   }
   radius: 10
   //anchors:
   Text {
       id: label
       y:20
       anchors.horizontalCenter: parent.horizontalCenter
       text: "-"
       //font.bold: true;
       font {
           family: "Verdana"
           pointSize: 14
      }
       style: Text.Raised;
       styleColor: "#55000000"
       color: "#55555555"
   }
   Image {
       id: img
       anchors.horizontalCenter: parent.horizontalCenter
       anchors.verticalCenter: parent.verticalCenter
       opacity: 0.4
       source: ""
   }
   transform: {
       rotation: 10
   }
   SequentialAnimation {
       id:animation;
       PropertyAnimation {
           id: animation1;
           target: gr;
           property: "color";
           to: "#55000000";
           duration: 200
       }
       PropertyAnimation {
           id: animation2;
           target: gr;
           property: "color";
           to: "#55333333";
           duration: 200
       }
   }

   MouseArea {
       anchors.fill: parent
       hoverEnabled: true;
       onEntered: {
           border.width = 2;
       }
       onExited: {
           border.width = 2;
       }
       onClicked: {
           animation.start();
           label.text = QMLButtonEventsReceiver.clicked(label.text);
       }
   }
}
