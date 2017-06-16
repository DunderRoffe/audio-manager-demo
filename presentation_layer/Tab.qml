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

  id: tab

  property bool isSelected: false;
  property string iconURL: ""
  property string basecolor: "#FFFFFF"
  property variant idContainer

  Image {
    id: name
    source: iconURL;
    smooth: true;
    anchors.horizontalCenter: parent.horizontalCenter;
    anchors.verticalCenter: parent.verticalCenter;
  }

  Rectangle {
    smooth: true;
    z:1000
    x: -12
    y: -12
    radius: 14
    width:  24;
    height: fullScreen.width * 0.08 + 10;
    color: "#000000"
  }


  Rectangle {
    id: unselected;
    x: 0
    y: +1
    width:  fullScreen.width * 0.08;
    height: fullScreen.width * 0.08;

    gradient: Gradient {
      GradientStop {
        position: 0.00;
        color: "#00000000";
      }
      GradientStop {
        position: 0.9;
        color: "#55000000";
      }
      GradientStop {
        position: 1;
        color: "#AA000000";
      }
    }
    color: "#000000"
  }

  color: tab.basecolor



  gradient: Gradient {
    GradientStop {
      id: selected;
      position: 0.00;
      color: tab.basecolor;//"#77FFFFFF";
    }
    GradientStop {
      position: 0.2;
      color: tab.basecolor;
    }
  }

 // color: "#FFCC33"
  width:  fullScreen.width * 0.08-1;
  height: fullScreen.width * 0.08;

  transform: Rotation {
    origin.x: fullScreen.width * 0.09 / 2;
    origin.y: fullScreen.width * 0.09 / 2;
    angle: -90
  }

  SequentialAnimation {
      id:animationSelect;
      PropertyAnimation {
          id: animation1;
          target: selected;
          property: "color";
          to: "#77000000";
          duration: 200
      }
  }

  SequentialAnimation {
      id:animationUnselect;
      PropertyAnimation {
          id: animation2;
          target: selected;
          property: "color";
          to: tab.basecolor;
          duration: 200
      }
  }
  onIsSelectedChanged:  {
    console.log("TAB",  isSelected);
    if (isSelected) {
      console.log("TAB selected");
      animationSelect.start();
      unselected.visible = false;
    } else {
      console.log("TAB un-selected");
      unselected.visible = true;
      animationUnselect.start();
    }
  }
}
