//
//  graphicPatternGenerator.cpp
//  Espill-ilda
//
//  Created by Eduard Frigola on 21/06/2017.
//
//

#include "graphicPatternGenerator.h"

graphicPatternGenerator::graphicPatternGenerator() : ofxOceanodeNodeModelExternalWindow("Graphic Generator"){
    setup();
}

void graphicPatternGenerator::setup(){
    parameters->add(positions.set("Positions", {ofPoint(0.25, 0.25), ofPoint(0.25, 0.75), ofPoint(0.75, 0.25), ofPoint(0.75, 0.75)}));
    parameters->add(positionReplicator.set("Position Replicator", 1, 1, 10));
//    parameters->add(scalePositions.set("Scale Pos", 1, 0, 1.1));
    lastPositionReplicator = positionReplicator;
    parameters->add(color.set("Color", ofColor::red, ofColor::white, ofColor::black));
//    parametersControl::addDropdownToParameterGroupFromParameter(parameters, "Mode Select", {"Points", "Circles", "Squares", "Lines"}, modeSelector);
    parameters->add(numVertex.set("Num Vertex", 1, 1, 100));
    parameters->add(toCenterFigure.set("To Center", false));
//    parameters->add(opacity.set("Opacity", 1, 0, 1));
//    parameters->add(size.set("Size", 0.5, 0, 1));
//    parameters->add(rotation.set("Rotation", 0, 0, 1));
//    parameters->add(jitter.set("Jitter", 0, 0, 1));
//    parameters->add(refollow.set("Refollow", false));
//    parameters->add(refollowIn.set("Refollow In", 0, 0, 1));
//    parameters->add(endFollow.set("End Follow", 1, 0, 1));
//    parameters->add(offsetFollow.set("Offset Follow", 0, 0, 1));
//    parameters->add(divisions.set("Divisions", 1, 1, 14));
//    parameters->add(divisionSpacing.set("Division Spacing", 0.5, 0, 1));
    parameters->add(scalePositions_vec.set("Scale Pos Vec", {1}, {0}, {1.1}));
    parameters->add(opacity_vec.set("Opacity Vec", {1}, {0}, {1}));
    parameters->add(size_vec.set("Size Vec", {0.5}, {0}, {1}));
    parameters->add(rotation_vec.set("Rotation Vec", {0}, {0}, {1}));
    parameters->add(jitter_vec.set("Jitter Vec", {0}, {0}, {1}));
    parameters->add(refollowIn_vec.set("Refollow In Vec", {0}, {0}, {1}));
    parameters->add(endFollow_vec.set("End Follow Vec", {1}, {0}, {1}));
    parameters->add(offsetFollow_vec.set("Offset Follow Vec", {0}, {0}, {1}));
    parameters->add(divisions_vec.set("Divisions Vec", {0}, {0}, {14}));
    parameters->add(divisionSpacing_vec.set("Division Spacing Vec", {0.5}, {0}, {1}));
    
    
    
    parameters->add(polyLinesOut.set("Output", {make_pair(ofPolyline(), ofColor())}));
    
    ofAddListener(parameters->parameterChangedE(), this, &graphicPatternGenerator::parameterChangedListener);
    positions = positions;
    
    someParameterChanged = true;
    
    pointDraggingIndex = -1;
    
    font.load("Verdana.ttf", 20);
}

vector<pair<ofPolyline, ofColor>> graphicPatternGenerator::computePolylines(){
    vector<pair<ofPolyline, ofColor>> coloredPolylines;
    if(true){
        for(int i = 0 ; i < positions.get().size(); i++){
            ofPolyline unitPoly;
            ofPoint position;
            float scaleValue = getParameterValueForPosition(scalePositions_vec, i);
            position.x = ofMap(scaleValue, 0.0, 1.0, 0.5, positions.get()[i].x);
            position.y = ofMap(scaleValue, 0.0, 1.0, 0.5, positions.get()[i].y);
            ofPoint positionWithJitter = position;
            float jitterValue = getParameterValueForPosition(jitter_vec, i);
            if(jitterValue != 0){
                positionWithJitter.x = position.x + ofRandom(-jitterValue*0.05, + jitterValue*0.05);
                positionWithJitter.y = position.y + ofRandom(-jitterValue*0.05, + jitterValue*0.05);
            }
            if(numVertex == 1){
                unitPoly.addVertex(positionWithJitter - ofPoint(0, 0.0001));
                unitPoly.addVertex(positionWithJitter + ofPoint(0.0001, 0));
                unitPoly.addVertex(positionWithJitter - ofPoint(0.0001, 0));
                unitPoly.addVertex(positionWithJitter + ofPoint(0, 0.0001));
            }else{
                for(float j = 0 ; j < 1 ; j = j + (1.0/(float)numVertex)){
                    float jj = j + getParameterValueForPosition(rotation_vec, i);
                    ofPoint newVertex;
                    newVertex.x = (sin(jj*2*PI)*getParameterValueForPosition(size_vec, i)/2)+position.x;
                    newVertex.y = (cos(jj*2*PI)*getParameterValueForPosition(size_vec, i)/2)+position.y;
                    //float jitterValue = getParameterValueForPosition(jitter_vec, i);
                    if(jitterValue != 0){
                        newVertex.x = newVertex.x + ofRandom(-jitterValue*0.05, + jitterValue*0.05);
                        newVertex.y = newVertex.y + ofRandom(-jitterValue*0.05, + jitterValue*0.05);
                    }
                    unitPoly.addVertex(newVertex);
                    if(toCenterFigure){
                        unitPoly.addVertex(positionWithJitter);
                    }
                }
                unitPoly.close();
                unitPoly = unitPoly.getResampledByCount(200);
            }
            
            
            if(getParameterValueForPosition(divisions_vec, i) != 0){
                vector<glm::vec3> polyVertex = unitPoly.getVertices();
                unitPoly.clear();
                int polySize = polyVertex.size();
                for(int d = 0; d < getParameterValueForPosition(divisions_vec, i) ; d++){
                    ofPolyline tempPoly;
                    float increment = 1.0/(float)(((float)getParameterValueForPosition(divisions_vec, i)*2.0)-1);
                    float start = (d * 2 * increment) * getParameterValueForPosition(endFollow_vec, i);
                    float end = start + (increment * getParameterValueForPosition(divisionSpacing_vec, i) * 2 * getParameterValueForPosition(endFollow_vec, i));
                    for(int j = start * polySize; j < end * polySize ; j++){
                        int jj = j + ((getParameterValueForPosition(refollowIn_vec, i) + getParameterValueForPosition(offsetFollow_vec, i)) * polySize);
                        jj = jj % polySize;
                        tempPoly.addVertex(polyVertex[jj]);
                    }
                    coloredPolylines.push_back(make_pair(tempPoly, color.get() * getParameterValueForPosition(opacity_vec, i)));
                }
            }else{
                coloredPolylines.push_back(make_pair(unitPoly, color.get() * getParameterValueForPosition(opacity_vec, i)));
            }
        }
    }
    someParameterChanged = false;
    polyLinesOut = coloredPolylines;
    return coloredPolylines;
}

void graphicPatternGenerator::parameterChangedListener(ofAbstractParameter &parameter){
    someParameterChanged = true;
    if(parameter.getName() == "Positions"){
        vector<ofPoint> newPos;
        for(int i = 0 ; i < positionReplicator ; i++){
            newPos.insert(newPos.end(), positions.get().begin(), positions.get().end());
        }
        positions = newPos;
    }
    
//    if(parameter.getName() == "Opacity" || parameter.getName() == "Positions"){
//        vector<float> vecFloat;
//        vecFloat.assign(positions.get().size(), opacity.get());
//        opacity_vec = vecFloat;
//    }
//    if(parameter.getName() == "Size" || parameter.getName() == "Positions"){
//        vector<float> vecFloat;
//        vecFloat.assign(positions.get().size(), size.get());
//        size_vec = vecFloat;
//    }
//    if(parameter.getName() == "Rotation" || parameter.getName() == "Positions"){
//        vector<float> vecFloat;
//        vecFloat.assign(positions.get().size(), rotation.get());
//        rotation_vec = vecFloat;
//    }
//    if(parameter.getName() == "Jitter" || parameter.getName() == "Positions"){
//        vector<float> vecFloat;
//        vecFloat.assign(positions.get().size(), jitter.get());
//        jitter_vec = vecFloat;
//    }
//    if(parameter.getName() == "Refollow" || parameter.getName() == "Positions"){
//        vector<bool> vecFloat;
//        vecFloat.assign(positions.get().size(), refollow.get());
//        refollow_vec = vecFloat;
//    }
//    if(parameter.getName() == "Refollow In" || parameter.getName() == "Positions"){
//        vector<float> vecFloat;
//        vecFloat.assign(positions.get().size(), refollowIn.get());
//        refollowIn_vec = vecFloat;
//    }
//    if(parameter.getName() == "End Follow" || parameter.getName() == "Positions"){
//        vector<float> vecFloat;
//        vecFloat.assign(positions.get().size(), endFollow.get());
//        endFollow_vec = vecFloat;
//    }
//    if(parameter.getName() == "Offset Follow" || parameter.getName() == "Positions"){
//        vector<float> vecFloat;
//        vecFloat.assign(positions.get().size(), offsetFollow.get());
//        offsetFollow_vec = vecFloat;
//    }
//    if(parameter.getName() == "Divisions" || parameter.getName() == "Positions"){
//        vector<int> intFloat;
//        intFloat.assign(positions.get().size(), divisions.get());
//        divisions_vec = intFloat;
//    }
//    if(parameter.getName() == "Division Spacing" || parameter.getName() == "Positions"){
//        vector<float> vecFloat;
//        vecFloat.assign(positions.get().size(), divisionSpacing.get());
//        divisionSpacing_vec = vecFloat;
//    }
//    if(parameter.getName() == "Scale Pos" || parameter.getName() == "Positions"){
//        vector<float> vecFloat;
//        vecFloat.assign(positions.get().size(), 1);
//        scalePositions_vec = vecFloat;
//    }
    if(parameter.getName() == "Position Replicator"){
        int realSize = positions.get().size() / lastPositionReplicator;
        vector<ofPoint> newPos(positions.get().begin(), positions.get().begin() + realSize);
        positions = newPos;
        for(int i = 0 ; i < positionReplicator-1 ; i++){
            newPos.insert(newPos.end(), positions.get().begin(), positions.get().end());
        }
        positions = newPos;
        lastPositionReplicator = positionReplicator;
    }
}


void graphicPatternGenerator::draw(){
    ofBackground(0);
    ofSetColor(255);
    
    for(int i = 0 ; i < positions.get().size(); i++){
        auto point = positions.get()[i];
        ofSetColor(255);
        int x = point.x * ofGetWidth();
        int y = point.y * ofGetHeight();
        ofDrawCircle(x, y, 20);
        ofSetColor(255,0,0);
        string s = ofToString(i);
        ofDrawBitmapString(s, x, y);
//        float halfWidth = font.stringWidth(s)/2;
//        float halfHeight = font.stringHeight(s)/2;
//        font.drawString(s, x-halfWidth, y+halfHeight);
    }
}

void graphicPatternGenerator::mousePressed(ofMouseEventArgs &a){
    bool foundPoint = false;
    for(int i = 0; i < positions.get().size() && !foundPoint ; i++){
        auto point = positions.get()[i] * ofPoint(ofGetWidth(), ofGetHeight());
        if(ofRectangle(point.x - 20, point.y - 20, 40, 40).inside(a)){
            pointDraggingIndex = i;
            foundPoint = true;
        }
    }
    if(ofGetKeyPressed(OF_KEY_SHIFT)){
        if(foundPoint){
            vector<ofPoint> positionsCopy = positions;
            positionsCopy.erase(positionsCopy.begin() + pointDraggingIndex);
            parameters->get("Positions").cast<vector<ofPoint>>().set(positionsCopy);
            pointDraggingIndex = -1;
        }else{
            vector<ofPoint> positionsCopy = positions;
            positionsCopy.push_back(ofPoint(a.x / ofGetWidth(), a.y/ofGetHeight()));
            parameters->get("Positions").cast<vector<ofPoint>>().set(positionsCopy);
        }
    }
}

void graphicPatternGenerator::mouseReleased(ofMouseEventArgs &a){
    pointDraggingIndex = -1;
}

void graphicPatternGenerator::mouseDragged(ofMouseEventArgs &a){
    if(pointDraggingIndex != -1){
        if(ofGetKeyPressed(OF_KEY_ALT)){
            ofPoint oldPos = positions.get()[pointDraggingIndex];
            ofPoint step = oldPos - (a / ofPoint((float)ofGetWidth(), (float)ofGetHeight()));
            vector<ofPoint> positionsCopy = positions;
            positionsCopy[pointDraggingIndex] = oldPos - (step/100);
            parameters->get("Positions").cast<vector<ofPoint>>().set(positionsCopy);
        }else{
            vector<ofPoint> positionsCopy = positions;
            positionsCopy[pointDraggingIndex] = a / ofPoint(ofGetWidth(), ofGetHeight());
            parameters->get("Positions").cast<vector<ofPoint>>().set(positionsCopy);
        }
    }
}
