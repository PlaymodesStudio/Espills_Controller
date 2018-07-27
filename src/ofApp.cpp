#include "ofApp.h"
#include "graphicPatternGenerator.h"
#include "ildaController.h"
#include "positionsSaver.h"
#include "vector_op_registrator.h"
#include "oscillatorTexture.h"
#include "waveScope.h"
#include "scriptModule.h"
#include "scriptModule.h"
#include "movingheadController.h"
#include "textureReader.h"
#include "artnetSender.h"
#include "vectorPresetEaser.h"
#include "valueEaser.h"
#include "midiGateIn.h"
#include "envelopeGenerator.h"
#include "audioEngineController.h"
#include "delta.h"

#include "ofxOceanodeBPMController.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetEscapeQuitsApp(false);
    ofDisableArbTex();
    ofSetVerticalSync(false);
    ofSetFrameRate(120);
    
    auto reg = make_shared<ofxOceanodeNodeRegistry>();
    auto treg = make_shared<ofxOceanodeTypesRegistry>();
    reg->registerModel<graphicPatternGenerator>("ESPILLS");
    reg->registerModel<ildaController>("ESPILLS");
    reg->registerModel<positionSaver>("ESPILLS");
    reg->registerModel<oscillatorTexture>("Texture");
    reg->registerModel<waveScope>("Texture");
    reg->registerModel<scriptModule>("Scripting");
    reg->registerModel<movingheadController>("Controller");
    reg->registerModel<textureReader>("Texture");
    reg->registerModel<artnetSender>("ArtNet");
    reg->registerModel<vectorPresetEaser>("EASER");
    reg->registerModel<valueEaser>("EASER");
    reg->registerModel<midiGateIn>("Midi");
    reg->registerModel<envelopeGenerator>("Midi");
    reg->registerModel<audioEngineController>("OSC");
    reg->registerModel<delta>("OP");
    
    registerVectorOp(reg);
    treg->registerType<vector<pair<ofPolyline, ofColor>>>();
    treg->registerType<vector<ofPoint>>();
    treg->registerType<ofTexture*>();
    
    container = make_shared<ofxOceanodeContainer>(reg, treg);
    canvas.setContainer(container);
    canvas.setup();
    
    controls = new ofxOceanodeControls(container);
    controls->get<ofxOceanodeBPMController>()->setBPM(80);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofDrawBitmapString(ofGetFrameRate(), 20, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
