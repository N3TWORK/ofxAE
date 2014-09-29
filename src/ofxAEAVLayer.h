#pragma once

#include "ofxAEDef.h"
#include "ofxAELayer.h"
#include "ofxMask.h"

class ofTrueTypeFont;
OFX_AE_NAMESPACE_BEGIN

class Mask;
class Marker;

class AVLayer : public Layer {
	friend class Loader;
public:
	AVLayer();
	~AVLayer();
	void allocate(int width, int height);
	void draw(float alpha=1);
	float getWidth() { return size_.x; }
	float getHeight() { return size_.y; }
	const ofVec2f& getSize() { return size_; }
	bool is3D() { return is_3d_; }
	bool isCollapse() { return is_collapse_; }
	bool isText() {return is_text_; }
	void addMask(Mask *mask);
	ofBlendMode getBlendMode() { return blend_mode_; }
	
	bool isHit(float x, float y);
	bool isHit(const ofVec3f &point);

	void setName(const string& name) { layerName_ = name; }
	const string& getName() const { return layerName_; }
	
	void setText(const string& text) { text_ = text; }
	const string& getText() const { return text_; }
	
protected:
	bool is_3d_;
	bool is_collapse_;
	ofBlendMode blend_mode_;
	ofVec2f size_;
	vector<Mask*> mask_;
	ofxMask ofx_mask_;
	
	// Text (TODO: create a TextLayer class)
	bool is_text_;
	ofTrueTypeFont* font_;
	string layerName_;
	string text_;
	
private:
	void drawTextInLayer();
};

OFX_AE_NAMESPACE_END
/* EOF */