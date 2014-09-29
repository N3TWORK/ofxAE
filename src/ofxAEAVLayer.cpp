#include "ofxAEAVLayer.h"
#include "ofxAEAVLayerCap.h"
#include "ofGraphics.h"
#include "ofxAEMask.h"

#include <ofTrueTypeFont.h>

OFX_AE_NAMESPACE_BEGIN

AVLayer::AVLayer()
:Layer()
,is_3d_(false)
,is_collapse_(false)
,is_text_(false)
{
	font_ = new ofTrueTypeFont;
	font_->loadFont("avenir", 40);
}

AVLayer::~AVLayer()
{
	delete font_;
}

void AVLayer::allocate(int width, int height)
{
	size_.set(width, height);
}

void AVLayer::drawTextInLayer() {
	if(text_.size()) {
		font_->drawString(text_, -100, 0);
	}
	else if(layerName_ == "HeadlineText") {
		font_->drawString("Headline text goes here", 0, 0);
	}
	else if(layerName_ == "VerticalText") {
		font_->drawString("Vertical text goes here", 0, 0);
	}
	else if(layerName_ == "BubbleText1" || layerName_ == "BubbleText2") {
		font_->drawString("Multi-line text goes into\nthis thought bubble\nhere.", 0, 0);
	}
	else if(layerName_ == "urlText") {
		font_->drawString("http://www.n3twork.com", -400, 0);
	}
}

void AVLayer::draw(float alpha)
{
	getNode().pushMatrix();
	if(!mask_.empty()) {
		ofx_mask_.beginMask();
		if(mask_.empty()) {
			ofClear(ofColor::white);
		}
		else {
			vector<Mask*>::iterator it = mask_.begin();
			if((*it)->isSubtract()) {
				ofClear(ofColor::white);
			}
			while(it != mask_.end()) {
				(*it)->draw();
				++it;
			}
		}
		ofx_mask_.endMask();
		if(isText()) {
			ofx_mask_.draw();
			drawTextInLayer();
		}
		else if(cap_){
			ofx_mask_.begin();
			cap_->draw(alpha*opacity_);
			ofx_mask_.end();
			ofx_mask_.draw();
		}
	}
	else {
		if(cap_) {
			if(isText()) {
				drawTextInLayer();
			}
			else {
				cap_->draw(alpha*opacity_);
			}
		}
	}
	getNode().popMatrix();
}

void AVLayer::addMask(Mask *mask)
{
	if(mask_.empty()) {
		ofx_mask_.setup(getWidth(), getHeight(), ofxMask::ALPHA);
	}
	mask_.push_back(mask);
	addProperty(mask);
}


bool AVLayer::isHit(float x, float y)
{
	return isHit(ofVec3f(x,y));
}

bool AVLayer::isHit(const ofVec3f &point)
{
	ofVec3f inv = getNode().getWorldMatrixInversed()->preMult(point);
	return 0 <= inv.x && inv.x < size_.x && 0 <= inv.y && inv.y < size_.y;
}

OFX_AE_NAMESPACE_END
/* EOF */