#include "graph.h"
#include "graphics-utils.h"
#include "easing-utils.h"

Graph::Graph(int width) {
    setSize(width, 2 * GRID_SIZE);

    showRectangle1 = false;
    showRectangle2 = false;
    showRectangle3 = false;

    rectangleWidth = 1;

    nextSampleY = 0;

    graphRefreshTime = 50;

    introLinesDuration = ofRandom(25) + 25;

    // Subtract 4 GRID_SIZE: 3 for headers and 1 for rectangle
    graphWidth = getWidth() - 4 * GRID_SIZE;

    // Add 3 anchors per grid size unit and one generator at the end
    // (with fixed position)
    int noOfPoints = getWidth() / GRID_SIZE * 4;
    pointDistance = graphWidth / noOfPoints;
    graphAmplitude = 12;

    // Populate the vector with points on the same line, separated by
    // pointDistance pixels.
    for (int index = 0; index < noOfPoints + 2; index++) {
        ofPoint newPoint = ofPoint(index * pointDistance, 0);
        graphPoints.push_back(newPoint);
    }

    initializeTexts();

    addEvent(AnimationEvent("intro", 300));
    addEvent(AnimationEvent("main"));
}

void Graph::initializeTexts() {
    AnimatedText nameText("", 5);
    nameText.setPosition(ofPoint(0, -1));
    nameText.setFlickerParameters(5, 10);
    nameText.setColor(COLOR_135);

    AnimatedText L("L", 5);
    L.setPosition(ofPoint(-1, getHeight() - 4));
    L.setFlickerParameters(5, 10);
    L.setColor(COLOR_55);

    AnimatedText M("M", 5);
    M.setPosition(ofPoint(14, getHeight() - 4));
    M.setFlickerParameters(5, 10);
    M.setColor(COLOR_55);
    
    AnimatedText H("H", 5);
    H.setPosition(ofPoint(29, getHeight() - 4));
    H.setFlickerParameters(5, 10);
    H.setColor(COLOR_55);

    texts.push_back(nameText);
    texts.push_back(L);
    texts.push_back(M);
    texts.push_back(H);
}

void Graph::update() {
      updateAnimation();

      // Retest right side rectangles at each second
      if ((int)getTime() % FRAME_RATE == 0) {
        showRectangle1 = ofRandom(0,1) > 0.5;
        showRectangle2 = ofRandom(0,1) > 0.5;
        showRectangle3 = ofRandom(0,1) > 0.5;
      }

      // Update spline
      if (currentEvent() == "main") {
          // Genereate new sample if refresh time has passed
          if ((int)getTime() % graphRefreshTime == 0) {
              // Shift all points to the left
              for (size_t index = 1; index < graphPoints.size() - 1; index++) {
                  graphPoints[index].y = graphPoints[index + 1].y;
                  graphPoints[index].x = index * pointDistance;
              }

              // Reset the X position of the last point
              graphPoints[graphPoints.size() - 1].x =
                                      (graphPoints.size() - 2) * pointDistance;

              // The Y position of the new sample;
              // The animation will slowly reach this position.
              nextSampleY = ofRandom(-1, 1) * graphAmplitude;
          }

          // Interpolate the Y position of the first and last point
          graphPoints[0].y = ofLerp(graphPoints[0].y, graphPoints[1].y,
                                    2.0 / graphRefreshTime);

          graphPoints[graphPoints.size() - 1].y =
                      ofLerp(graphPoints[graphPoints.size() - 1].y, nextSampleY,
                             2.0 / graphRefreshTime);

          // Slowly move all points to the left
          for (size_t index = 1; index < graphPoints.size() - 1; index++)
              graphPoints[index].x -= pointDistance / graphRefreshTime;
      }
}

void Graph::drawLines() {

    // The X position where lines start (drawn from right to left)
    float lineStart = getWidth() - GRID_SIZE;


    ofSetColor(COLOR_95, 100);

    if (currentEvent() == "intro") {

        // The current width of the top/bottom lines
        float currentLineWidth = easeInOut(getTime(), 0, graphWidth,
                                           introLinesDuration);

        ofSetColor(COLOR_95, 100);
        ofDrawLine(lineStart, 0.5, lineStart - currentLineWidth, 0.5);
        ofDrawLine(lineStart, getHeight() + 0.5,
                   lineStart - currentLineWidth, getHeight() + 0.5);

    } else if (currentEvent() == "main") {
        ofDrawLine(3 * GRID_SIZE, 0.5, getWidth() - GRID_SIZE, 0.5);
        ofDrawLine(3 * GRID_SIZE, getHeight() + 0.5, getWidth() - GRID_SIZE, getHeight() + 0.5);
    }
}

void Graph::drawRectangles() {

    // The X position where rectangles start (drawn from right to left)
    float rectangleStart = getWidth() - rectangleWidth + 0.5;

    ofSetColor(COLOR_75);

    if (currentEvent() == "intro") {

        if ((getTime() > 100 && getTime() < 170) ||
                               (getTime() > 150 && showRectangle1))
            ofDrawRectangle(rectangleStart, 0, rectangleWidth, 7);

        if ((getTime() > 105 && getTime() < 180) ||
                               (getTime() > 160 && showRectangle1))
            ofDrawRectangle(rectangleStart, 12, rectangleWidth, 7);

        if ((getTime() > 110 && getTime() < 190) ||
                               (getTime() > 170 && showRectangle1))
            ofDrawRectangle(rectangleStart, 23, rectangleWidth, 7);

    } else if (currentEvent() == "main") {

        if (showRectangle1)
            ofDrawRectangle(rectangleStart, 0, rectangleWidth, 7);

        if (showRectangle2)
            ofDrawRectangle(rectangleStart, 12, rectangleWidth, 7);

        if (showRectangle3)
            ofDrawRectangle(rectangleStart, 23, rectangleWidth, 7);

    }
}

void Graph::drawSpline() {

    if (currentEvent() == "intro") {
        // The X position where lines start (drawn from right to left)
        float lineStart = getWidth() - GRID_SIZE;

        // The current width of the spline (the line in the center)
        float currentSplineWidth = easeInOut(getTime(), 0, graphWidth,
                                             introLinesDuration * 1.5);

        ofSetColor(COLOR_135);
        ofDrawLine(lineStart, getHeight() / 2,
                   lineStart - currentSplineWidth, getHeight() / 2);

    } else if (currentEvent() == "main") {
        ofPushMatrix();
        {
            ofTranslate(3 * GRID_SIZE, GRID_SIZE);

            ofSetColor(COLOR_135);
            ofNoFill();
            ofSetPolyMode(OF_POLY_WINDING_ODD);
            ofBeginShape();
            {
                ofVertex(graphPoints[0].x, graphPoints[0].y);

                for (int index = 1; index < graphPoints.size() - 1; index++)
                    bezierVertexFromDatapoints(graphPoints[index - 1],
                                               graphPoints[index],
                                               graphPoints[index + 1]);

                ofPoint a1 = graphPoints[graphPoints.size() - 2];
                ofPoint a2 = graphPoints[graphPoints.size() - 1];
                ofBezierVertex(intermediatePoint(a1, a2, 1 / 3.0),
                               intermediatePoint(a1, a2, 2 / 3.0),
                               a2);
            }
            ofEndShape();
        }
        ofPopMatrix();
    }
}

void Graph::drawTexts() {
    for (int index = 0; index < texts.size(); index++)
        texts[index].draw();
}


void Graph::draw() {
    update();
    ofPushMatrix();
    {
        ofTranslate(getPosition());

        drawTexts();
        drawLines();
        drawSpline();
        drawRectangles();
    }
    ofPopMatrix();
}


void Graph::bezierVertexFromDatapoints(ofPoint point1, ofPoint point2,
                                                       ofPoint point3) {
    // Compute aframe1 -> aframe2, intermediates at 1/3, 2/3 (anchor1,anchor2)
    // Compute aframe2 -> aframe3, intermediate at 1/3
    // 1/2 between 2/3s intermediate of 1->2, and 1/3 of 2->3 is actual vertex pos
    ofPoint anchor1 = intermediatePoint(point1, point2, 1 / 3.0);
    ofPoint anchor2 = intermediatePoint(point1, point2, 2 / 3.0);
    ofPoint anchor3 = intermediatePoint(point2, point3, 1 / 3.0);
    ofPoint vertex = intermediatePoint(anchor2, anchor3, 1 / 2.0);
    ofBezierVertex(anchor1, anchor2, vertex);
}

ofPoint Graph::intermediatePoint(ofPoint p1, ofPoint p2, float distance) {
    return ofPoint((p2.x - p1.x) * distance + p1.x,
                   (p2.y - p1.y) * distance + p1.y);
}

void Graph::setName(std::string name) {
    texts[0].setText(name);
}

