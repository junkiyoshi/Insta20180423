#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofBackground(39);
	ofSetWindowTitle("Insta");

	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
	ofSetLineWidth(1.5);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	float radius = 300;
	vector<ofColor> colors = {ofColor(239, 39, 39), ofColor(39, 239, 39), ofColor(39, 39, 239)};
	for (int loop = 0; loop < 2; loop++) {

		ofRotateX(loop * 90);
		for (int i = 0; i < colors.size(); i++) {

			float sphere_deg = (360 / colors.size()) * i + ofGetFrameNum();

			ofPoint sphere_point = ofPoint(radius * cos(sphere_deg * DEG_TO_RAD), radius * sin(sphere_deg * DEG_TO_RAD));
			ofFill();
			ofSetColor(colors[i]);
			ofDrawSphere(sphere_point, 5);

			int deg_span = 5;
			for (int deg = 0; deg < 360; deg += deg_span) {

				int small_deg_span = 5;
				float small_radius = 80;
				vector<ofPoint> vertices;
				for (int small_deg = 0; small_deg < 360; small_deg += small_deg_span) {

					ofPoint point = make_point(radius, small_radius, deg, small_deg);
					float distance = sphere_point.distance(point);
					ofSetColor(colors[i], ofMap(distance, 0, 250, 255, 0));
					if (distance < 250) {

						vertices.push_back(point);

						ofPoint next_point = make_point(radius, small_radius, deg + deg_span, small_deg);
						ofDrawLine(point, next_point);
					}
				}

				ofNoFill();
				ofBeginShape();
				ofVertices(vertices);
				ofEndShape(true);
			}
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
ofPoint ofApp::make_point(float radius, float small_radius, float deg, float small_deg) {

	float x_1 = radius * cos(deg * DEG_TO_RAD);
	float y_1 = radius * sin(deg * DEG_TO_RAD);

	float x_2 = small_radius * cos(small_deg * DEG_TO_RAD) * cos(deg * DEG_TO_RAD);
	float y_2 = small_radius * cos(small_deg * DEG_TO_RAD) * sin(deg * DEG_TO_RAD);

	float x = x_1 + x_2;
	float y = y_1 + y_2;
	float z = small_radius * sin(small_deg * DEG_TO_RAD);

	return ofPoint(x, y, z);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}