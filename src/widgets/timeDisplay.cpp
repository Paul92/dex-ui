#include "timeDisplay.h"
#include "graphics-utils.h"

void TimeDisplay::initializeLines() {
    upperLine.setPosition(ofPoint(0, 0));
    midLine.setPosition(ofPoint(0, getHeight() - 30));
    lowerLine.setPosition(ofPoint(0, getHeight()));

    int unitSize = getWidth() / 16; // GRID_SIZE for width 240
    int tickMultipliers[] = {3, 4, 8, 9, 13, 14};

    for (size_t index = 0; index < sizeof(tickMultipliers) / sizeof(int); index++) {
        midLine.addTick(tickMultipliers[index] * unitSize + 0.5);
        lowerLine.addTick(tickMultipliers[index] * unitSize + 0.5);
    }
}

void TimeDisplay::initializeMainTime() {
    mainTime.setFlickerParameters(5, 20);
    mainTime.addDelay(80);
    mainTime.setColor(COLOR_175);

    float spaceSize = ofMap(getWidth(), 225, 300, 0, 1.25, true);
    mainTime.setSpaceSize(spaceSize);

    int xPosition = (getWidth() - 2 * GRID_SIZE - mainTime.getWidth()) / 2;
    mainTime.setPosition(ofPoint(xPosition + GRID_SIZE, (getHeight() - 30 - mainTime.getHeight()) / 2 ));
}

void TimeDisplay::initializeUpperTexts(int xPositions[4], std::string year) {
    std::string upperStrings[4] = {year, "UPTIME", "SYSTEM", "V"};

    int yPosition = midLine.getPosition().y + 7;

    for (int index = 0; index < 4; index++) {
        AnimatedText upperText(upperStrings[index], 7);
        upperText.setFlickerParameters(5, 20);
        upperText.setPosition(ofPoint(xPositions[index], yPosition));
        upperText.setColor(COLOR_75);
        upperText.addDelay(65);
        upperTexts.push_back(upperText);
    }
}

void TimeDisplay::initializeLowerTexts(int xPositions[4], std::string month) {
    std::string lowerStrings[4] = {month, "", "ONLINE", "0.1b"};

    int yPosition = upperTexts[0].getPosition().y + 9 + 2; 

    for (int index = 0; index < 4; index++) {
        AnimatedText lowerText(lowerStrings[index], 7);
        lowerText.setFlickerParameters(5, 20);
        lowerText.setPosition(ofPoint(xPositions[index], yPosition));
        lowerText.setColor(COLOR_135);
        lowerText.addDelay(80);
        lowerTexts.push_back(lowerText);
    }

    // Remove spaces from uptime
    lowerTexts[1].setSpaceSize(0);
}

void TimeDisplay::initializeTextArrays(int xPositions[4]) {

    std::string year = ofToString(localizedTime->tm_year + 1900);
    initializeUpperTexts(xPositions, year);


    char monthBuffer[10];
    strftime(monthBuffer, 10, "%b %d", localizedTime);
    std::string month = std::string(monthBuffer);
    std::transform(month.begin(), month.end(), month.begin(), ::toupper);
    initializeLowerTexts(xPositions, month);
}

TimeDisplay::TimeDisplay(int width) :
        upperLine(width, 40, 0, COLOR_LINE),
        midLine(width, 40, 0, COLOR_LINE),
        lowerLine(width, 40, 0, COLOR_LINE),
        mainTime("00 : 00 : 00", 35)
{
    setSize(width, 90);

    time(&currentTime);
    time(&initialTime);
    localizedTime = localtime(&currentTime);


    initializeLines();
    initializeMainTime();

    int unitSize = width / 16; // GRID_SIZE for width 240
    int xPositions[] = { 0 * unitSize + 5,
                         4 * unitSize + 5,
                         9 * unitSize + 5,
                        14 * unitSize + 5};
    initializeTextArrays(xPositions);


    addEvent(AnimationEvent("intro", 300));
    addEvent(AnimationEvent("main"));
}

std::string timeToString(int hours, int minutes, int seconds) {
    std::string hoursString = ofToString(hours);
    std::string minutesString = ofToString(minutes);
    std::string secondsString = ofToString(seconds);

    if (hours < 10)
        hoursString = "0" + hoursString;
    if (minutes < 10)
        minutesString = "0" + minutesString;
    if (seconds < 10)
        secondsString = "0" + secondsString;

    return hoursString + " : " + minutesString + " : " + secondsString;
}

void TimeDisplay::updateMainTime() {
    std::string currentTime = timeToString(localizedTime->tm_hour,
                                           localizedTime->tm_min,
                                           localizedTime->tm_sec);
    mainTime.setText(currentTime);
}

void TimeDisplay::updateUptime() {
    std::string uptime = timeToString((int)(secondsPassed / 3600) % 99,
                                      (int)(secondsPassed / 60) % 60,
                                      (int)(secondsPassed) % 60);
    lowerTexts[1].setText(uptime);
}

void TimeDisplay::update() {
    if (getTime() % 60 == 0) {
        updateClockTime();
        updateMainTime();
        updateUptime();
    }
    updateAnimation();
}

void TimeDisplay::updateClockTime() {
    // Only get real time every 10 seconds or if minute is going to change
    if (getTime() % 600 != 0 && localizedTime->tm_sec < 59) {
        localizedTime->tm_sec += 1;
        secondsPassed += 1;
    } else {
        ::time(&currentTime);
        localizedTime = localtime(&currentTime);
        secondsPassed = difftime(currentTime, initialTime);
    }
}

void TimeDisplay::draw() {
    update();
    ofPushMatrix();
    {
        ofTranslate(getPosition());
        ofSetColor(COLOR_LINE);

        upperLine.draw();
        midLine.draw();
        lowerLine.draw();

        mainTime.draw();

        for (size_t index = 0; index < upperTexts.size(); index++) {
            upperTexts[index].draw();
            lowerTexts[index].draw();
        }
    }
    ofPopMatrix();
}

