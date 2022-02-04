#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(255);

	this->mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

	this->number_of_base = 150;
	this->number_of_child = 5;
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->mesh.clear();
	this->circle_list.clear();

	vector<glm::vec3> location_list;
	for (int i = 0; i < this->number_of_base; i++) {

		auto base_location = glm::vec2(ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.00035), 0, 1, -350, 350), ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.00035), 0, 1, -350, 350));

		for (int k = 0; k < this->number_of_child; k++) {
		
			location_list.push_back(glm::vec3(base_location, k == 0 ? 5 : 3));
		}
	}

	for (int i = 0; i < location_list.size(); i += this->number_of_child) {

		for (int k = 1; k < this->number_of_child; k++) {

			auto gap = glm::vec2(ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, -50, 50), ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, -50, 50));
			auto noise_value = ofNoise(glm::vec4(location_list[i + k] * 0.005, ofGetFrameNum() * 0.015));
			auto param = 0.f;
			if (noise_value > 0.65) {

				param = ofMap(noise_value, 0.65, 1, 0, 3);
			}
			
			location_list[i + k] = location_list[i + k] + gap * param;
		}
	}

	for (int i = 0; i < location_list.size(); i++) {

		this->circle_list.push_back(location_list[i]);
		for (int k = 0; k < location_list.size(); k++) {

			if (i == k) { continue; }

			auto distance = glm::distance(location_list[i], location_list[k]);
			if (distance < 50) {

				this->mesh.addVertex(location_list[i]);
				this->mesh.addVertex(location_list[k]);

				this->mesh.addIndex(this->mesh.getNumVertices() - 1);
				this->mesh.addIndex(this->mesh.getNumVertices() - 2);
			}
		}

	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	ofSetLineWidth(1);
	this->mesh.drawWireframe();

	ofSetLineWidth(1.5);
	for (auto& circle : this->circle_list) {

		if (circle.z == 3) {

			ofFill();
			ofSetColor(255);
			ofDrawCircle(glm::vec2(circle.x, circle.y), circle.z);

			ofNoFill();
			ofSetColor(0);
			ofDrawCircle(glm::vec2(circle.x, circle.y), circle.z);
		}
	}

	for (auto& circle : this->circle_list) {

		if (circle.z == 5) {

			ofFill();
			ofSetColor(255);
			ofDrawCircle(glm::vec2(circle.x, circle.y), circle.z);

			ofNoFill();
			ofSetColor(0);
			ofDrawCircle(glm::vec2(circle.x, circle.y), circle.z);
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}