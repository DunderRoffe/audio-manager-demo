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
import "qrc:/resources/scripts/tabs.js" as Tabs

Rectangle {
  id: fullScreen;
  width: 1024;
  height: 768;
  color: "#000000"

  Image {
    z: -1
    width: fullScreen.width;//1600//
    height: fullScreen.height;//720//900//
    fillMode: Image.Tile
    source: "qrc:/resources/pics/bg_homepage.png"
  }
  gradient: Gradient {
    GradientStop {
      position: 0.00;
      color: "#00000000";
    }
    GradientStop {
      position: 0.2;
      color: "#FF000000";
    }
    GradientStop {
      position: 0.9;
      color: "#FF000000";
    }
    GradientStop {
      position: 1;
      color: "#00000000";
    }
  }

  property int oldIndex: -1;

  function tabSelected(newIndex)
  {
    if (oldIndex != -1)
    {
      console.log("UNSELECT INDEX:", oldIndex);
      tabs.children[oldIndex].isSelected = false;
      tabs.children[oldIndex].idContainer.visible = false;
    }
    console.log("SELECT INDEX:", newIndex);

    tabs.children[newIndex].isSelected = true;
    tabs.children[newIndex].idContainer.visible = true;
    oldIndex = newIndex;
  }

  Row {
    x:0
    height: 100

    Rectangle {
        color: "#00000000"
        width: fullScreen.width * 0.08;
        height: fullScreen.width * 0.08;
    }

    Slider {
        y: 10;
        height: 32;
        width: fullScreen.width * 0.9
        id: sliderId
        objectName: "sliderVolume"
        minimum: 0
        maximum: 100
        onMaximumChanged: {
          sliderId.value = 200
        }
    }
  }

  Row {
    y: fullScreen.height * 0.1

    Column {
      id: tabs;
      //TAB BAR
      anchors.verticalCenter: parent.verticalCenter
      spacing: 20

      Tab {
        id: tab1
        iconURL: "qrc:/resources/pics/home.png"
        idContainer: tabContent1
        basecolor: "#FFFFFF";
        MouseArea {anchors.fill: parent; onClicked: { tabSelected(0); }}
      }

      Tab {
        id: tab2
        iconURL: "qrc:/resources/pics/sound.png"
        idContainer: tabContent2
        basecolor: "#FFFFFF";
        MouseArea {anchors.fill: parent; onClicked: { tabSelected(1); }}
      }
    }

    Column {
      //TAB CONTENT
      anchors.verticalCenter: parent.verticalCenter
      spacing: 20

      Rectangle {//HOME
        id: tabContent1;
        visible: false;
        color: tab1.color
        width:  fullScreen.width * 0.9;
        height: fullScreen.height * 0.8;
        radius: 10;

        HomePage {
            id: homePage
            anchors.rightMargin: -53
            anchors.bottomMargin: 204
            anchors.leftMargin: 124
            anchors.topMargin: -31
        }
      }

      Rectangle {//SOUND SETTINGS
        id: tabContent2;
        visible: false;
        color: tab2.color
        width:  fullScreen.width * 0.9;
        height: fullScreen.height * 0.8  ;
        radius: 10;

        AudioManager {
          id: audioManager
        }
      }
    }

    Component.onCompleted: {
      tabSelected(0);
    }
  }
}
