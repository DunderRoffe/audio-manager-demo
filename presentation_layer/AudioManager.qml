/**
 * SPDX license identifier: MPL-2.0
 *
 * Copyright (C) 2011-2014, Wind River Systems
 * Copyright (C) 2014, GENIVI Alliance
 *
 * This file is part of GENIVI AudioManager PoC.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License (MPL), v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * For further information see http://www.genivi.org/.
 *
 * List of changes:
 *
 * 21.09.2014, Adrian Scarlat, First version of the code;
 *                             Added Copyright and License information;
 */

import QtQuick 2.2

Rectangle {

  Row{
      y: 20;
      x: 380
      Button {
        objectName: "music"
        text: "Play Music"
        width: 180
      }
  }

  Row {
    spacing: 10
    y: 100;
    x: 50
    Button {
      objectName: "parking"
      text: "Parking Signal"
      width: 200
    }
    Button {
      objectName: "nav"
      text: "Navigation Message"
      width: 250
    }
    Button {
      objectName: "tts"
      text: "Text To Speech"
      width: 200
    }
    Button {
      objectName: "phone"
      text: "Start Phone Call"
      width: 180
    }
  }

  Rectangle
  {
    color: "#000000";
    radius: 5
    width: 410
    height: 110
    x: 45
    y: 175
    Image {
      id: volChart
      source: "image://volumes/1"
      width: 400
      x:5
      y:5
      height: 100
      asynchronous: true
    }
  }

  Timer {
    property int idx: 0
    id: timerImg;
      interval: 1000
      repeat: true
      running: true
      onTriggered: {
        idx++;
        volChart.source = "image://volumes/" + idx; }
  }

  Row {
      z: 3
      x: 50
      y: 300
      spacing: 50
      //CONNECTIONS
      Column {
        x: 5
        width: 450
        z: 4
        Text {
          id: titleConnections
          z: 5
          font {
              family: "Liberation Mono"
              pointSize: 12
          }
          color: "#000000"
          text: "CONNECTIONS:"
        }


        Text {
          id: id1
          z: 5
          font {
              family: "Liberation Mono"
              pointSize: 9
          }
          color: "#000000"
          objectName: "textConnections"
          text: ""
        }
      }//end connections


      //SOURCES
      Column {
        z: 4
        width: 100
        Text {
          id: titleSources
          z: 5
          font {
              family: "Liberation Mono"
              pointSize: 12
          }
          color: "#000000"
          text: "SOURCES"
        }


        Text {
          objectName: "textSources"
          z: 5
          font {
              family: "Liberation Mono"
              pointSize: 9
          }
          color: "#000000"
          text: ""
        }
      }//end sources

      //VOLUMES
      Column {
        width: 150
        z: 4
        Text {
          id: titleVolumes
          z: 5
          font {
              family: "Liberation Mono"
              pointSize: 12
          }
          color: "#000000"
          text: "VOLUME"
        }

        Text {
          objectName: "textVolumes"
          z: 5
          font {
              family: "Liberation Mono"
              pointSize: 9
              bold: true;
          }
          color: "#000000"
          text: ""
        }
      }//end connections
  }
}
