#include <iostream>
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    camWidth = 640;  // try to grab at this size.
    camHeight = 480;
    pixelColorUpdateValue = 0;
    
    //we can now get back a list of devices.
    vector<ofVideoDevice> devices = vidGrabber.listDevices();

    for(int i = 0; i < devices.size(); i++){
        if(devices[i].bAvailable){
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
        }else{
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName << " - unavailable ";
        }
    }

    vidGrabber.setDeviceID(0);
    vidGrabber.setDesiredFrameRate(60);
    vidGrabber.initGrabber(camWidth, camHeight);

    videoInverted.allocate(camWidth, camHeight, OF_PIXELS_RGB);
    videoTexture.allocate(videoInverted);
    
    videoInvertedOld.allocate(camWidth, camHeight, OF_PIXELS_RGB);
    videoTextureOld.allocate(videoInvertedOld);
    
    ofSetVerticalSync(true);
}


//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(100, 100, 100);
    vidGrabber.update();
    
    if(vidGrabber.isFrameNew()){
        ofPixels & pixels = vidGrabber.getPixels();
        
        videoInvertedOld = pixels;
        videoInvertedOld.rotate90(4);
        
        // Cache frame
        frameCache.push_back(pixels);
        
        // Clear stale cache
        if (frameCache.size() > maxFrames) {
            frameCache.erase(frameCache.begin());
        }
        
        int k = 0;
        for (int i = 0; i < pixels.size(); i++) {
            
            int newPx = frameCache.at(0)[i] - 1;
            if (newPx < 0) {
                if (frameCache.size() > (maxFrames-1) &&
                    frameCache.at((maxFrames-1)).size() > i) {
                    newPx = frameCache.at((maxFrames-1))[i];
                } else if (frameCache.size() > (maxFrames-2) &&
                           frameCache.at((maxFrames-2)).size() > i) {
                    newPx = frameCache.at((maxFrames-2))[i];
                } else if (frameCache.size() > 1 &&
                    frameCache.at(1).size() > i) {
                    newPx = frameCache.at(1)[i];
                } else {
                    newPx = videoInvertedOld[i];
                }
            }
            
            if ((i%3) == 0) {
                if (frameCache.size() > (maxFrames-3) &&
                    frameCache.at((maxFrames-3)).size() > i) {
                    newPx = frameCache.at((maxFrames-3))[i];
                } else if (frameCache.size() > (maxFrames-4) &&
                           frameCache.at((maxFrames-4)).size() > i) {
                    newPx = frameCache.at((maxFrames-4))[i];
                } else if (frameCache.size() > 1 &&
                           frameCache.at(1).size() > i) {
                    newPx = frameCache.at(1)[i];
                } else {
                    newPx = videoInvertedOld[i];
                }
            }
            
            if ((i%2) == 0) {
                if (frameCache.size() > (maxFrames-5) &&
                    frameCache.at((maxFrames-5)).size() > i) {
                    newPx = frameCache.at((maxFrames-5))[i];
                } else if (frameCache.size() > (maxFrames-6) &&
                           frameCache.at((maxFrames-6)).size() > i) {
                    newPx = frameCache.at((maxFrames-6))[i];
                } else if (frameCache.size() > 1 &&
                           frameCache.at(1).size() > i) {
                    newPx = frameCache.at(1)[i];
                } else {
                    newPx = videoInvertedOld[i];
                }
            }
            
            if (k == 0) {
                newPx = frameCache.at(0)[i];
            } else if (k == 1 && frameCache.size() > 4) {
                newPx = frameCache.at(4)[i];
            } else if (k == 2 && frameCache.size() > 8) {
                newPx = frameCache.at(8)[i];
            }
            
            videoInverted[i] = newPx;
            
            k++;
            if (k == 3) {
                k = 0;
            }
        }
        
        videoTexture.loadData(videoInverted);
        videoInverted.mirror(true, false);
        
//        videoInvertedOld.blendInto(frameCache.at(0), 0, 0);
    }
    
    ofSetHexColor(0xffffff);
    
    videoTextureOld.loadData(videoInvertedOld);
    videoTextureOld.draw(0, 0, ofGetWidth(), ofGetHeight());
    
    videoTexture.draw(50, 50, ofGetWidth() - 100, ofGetHeight() - 100);
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key=='c'){
        bRecording = false;
        vidRecorder.close();
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
}
