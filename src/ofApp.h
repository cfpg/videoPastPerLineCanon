#pragma once

#include "ofMain.h"
#include "ofxVideoRecorder.h"

class ofApp : public ofBaseApp{

    public:

        void setup();
        void update();
        void draw();

        void keyPressed(int key);
        void keyReleased(int key);
        void mouseMoved(int x, int y);
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void mouseEntered(int x, int y);
        void mouseExited(int x, int y);
        void windowResized(int w, int h);
        void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);
    
    ofImage image;

    ofVideoGrabber vidGrabber;
    ofxVideoRecorder vidRecorder;
    
    bool bRecording;
    void recordingComplete(ofxVideoRecorderOutputFileCompleteEventArgs& args);
    
    ofPixels videoInverted;
    ofTexture videoTexture;
    
    ofPixels videoInvertedOld;
    ofTexture videoTextureOld;
    
    vector<ofPixels> frameCache;

    int camWidth;
    int camHeight;
    int pixelColorUpdateValue;
    
    string fileName;
    string fileExt;
    
    int maxFrames = 20;
};
