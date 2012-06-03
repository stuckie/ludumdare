#include "GrappleHook.h"

#include <cstdio>
#include <cmath>
#include "../Objects/Math.h"

GrappleHook::GrappleHook()
: source_(0)
, target_(0)
, length_(10.0F)
{
}

GrappleHook::~GrappleHook()
{
}

void GrappleHook::fire()
{
	writeVelocity().x_ += cos(deg2rad(getAngle())) * getSpeed();
	writeVelocity().y_ += sin(deg2rad(getAngle())) * getSpeed();
	
	for (Uint segment(0U); segment < segments_.size(); ++segment) {
		segments_[segment]->writePosition().x_ = readPosition().x_ - (segment * getLength());
		segments_[segment]->writePosition().y_ = readPosition().y_ - (segment * getLength());
	}
}

void GrappleHook::update(const float deltaTime)
{
	const float segmentLength(10.0F);
	std::vector<Vector2D> calculatedPositions;
	
	for (Uint segment(0U); segment < segments_.size(); ++segment) {
		if (segment == 0U) {
			if (0 != target_) {
				const Vector2D previousSegment((target_->readPosition().x_ - segments_[segment]->readPosition().x_)
											,	(target_->readPosition().y_ - segments_[segment]->readPosition().y_));
											
				float previousMagnitude(sqrt(ceil((previousSegment.x_ * previousSegment.x_) + (previousSegment.y_ * previousSegment.y_))));
				float previousExtension(previousMagnitude - segmentLength);
				
				const Vector2D nextSegment((segments_[segment+1U]->readPosition().x_ - segments_[segment]->readPosition().x_)
										,	(segments_[segment+1U]->readPosition().y_ - segments_[segment]->readPosition().y_));
										
				float nextMagnitude(sqrt(ceil((nextSegment.x_ * nextSegment.x_) + (nextSegment.y_ * nextSegment.y_))));
				float nextExtension(nextMagnitude - segmentLength);
				
				const Vector2D reactant((((previousSegment.x_ / previousMagnitude) * previousExtension) + ((nextSegment.x_ / nextMagnitude) * nextExtension))
									,	(((previousSegment.y_ / previousMagnitude) * previousExtension) + ((nextSegment.y_ / nextMagnitude) * nextExtension)));
									
				segments_[segment]->writeVelocity().x_ = (segments_[segment]->readVelocity().x_ * 0.95F) + (reactant.x_ * target_->getMass());
				segments_[segment]->writeVelocity().y_ = (segments_[segment]->readVelocity().y_ * 0.95F) + (reactant.y_ * target_->getMass());
			}
		}
		else if ((segment != 0U) && (segment != segments_.size() - 1U)) {
			const Vector2D previousSegment((segments_[segment-1U]->readPosition().x_ - segments_[segment]->readPosition().x_)
										,	(segments_[segment-1U]->readPosition().y_ - segments_[segment]->readPosition().y_));
										
			float previousMagnitude(sqrt(ceil((previousSegment.x_ * previousSegment.x_) + (previousSegment.y_ * previousSegment.y_))));
			float previousExtension(previousMagnitude - segmentLength);
			
			const Vector2D nextSegment((segments_[segment+1U]->readPosition().x_ - segments_[segment]->readPosition().x_)
									,	(segments_[segment+1U]->readPosition().y_ - segments_[segment]->readPosition().y_));
									
			float nextMagnitude(sqrt(ceil((nextSegment.x_ * nextSegment.x_) + (nextSegment.y_ * nextSegment.y_))));
			float nextExtension(nextMagnitude - segmentLength);
			
			const Vector2D reactant((((previousSegment.x_ / previousMagnitude) * previousExtension) + ((nextSegment.x_ / nextMagnitude) * nextExtension))
								,	(((previousSegment.y_ / previousMagnitude) * previousExtension) + ((nextSegment.y_ / nextMagnitude) * nextExtension)));
								
			segments_[segment]->writeVelocity().x_ = (segments_[segment]->readVelocity().x_ * 0.95F) + (reactant.x_ * segments_[segment]->getMass());
			segments_[segment]->writeVelocity().y_ = (segments_[segment]->readVelocity().y_ * 0.95F) + (reactant.y_ * segments_[segment]->getMass());
		}		
		else if (segment == segments_.size() - 1U) {
			if (0 == source_) {
				const Vector2D previousSegment((segments_[segment-1U]->readPosition().x_ - segments_[segment]->readPosition().x_)
											,	(segments_[segment-1U]->readPosition().y_ - segments_[segment]->readPosition().y_));
											
				float previousMagnitude(sqrt(ceil((previousSegment.x_ * previousSegment.x_) + (previousSegment.y_ * previousSegment.y_))));
				float previousExtension(previousMagnitude - segmentLength);
				
				const Vector2D nextSegment((readPosition().x_ - segments_[segment]->readPosition().x_)
										,	(readPosition().y_ - segments_[segment]->readPosition().y_));
										
				float nextMagnitude(sqrt(ceil((nextSegment.x_ * nextSegment.x_) + (nextSegment.y_ * nextSegment.y_))));
				float nextExtension(nextMagnitude - segmentLength);
				
				const Vector2D reactant((((previousSegment.x_ / previousMagnitude) * previousExtension) + ((nextSegment.x_ / nextMagnitude) * nextExtension))
									,	(((previousSegment.y_ / previousMagnitude) * previousExtension) + ((nextSegment.y_ / nextMagnitude) * nextExtension)));
									
				segments_[segment]->writeVelocity().x_ = (segments_[segment]->readVelocity().x_ * 0.95F) + (reactant.x_ * segments_[segment]->getMass());
				segments_[segment]->writeVelocity().y_ = (segments_[segment]->readVelocity().y_ * 0.95F) + (reactant.y_ * segments_[segment]->getMass());
			}
			else {
				const Vector2D previousSegment((segments_[segment-1U]->readPosition().x_ - segments_[segment]->readPosition().x_)
											,	(segments_[segment-1U]->readPosition().y_ - segments_[segment]->readPosition().y_));
											
				float previousMagnitude(sqrt(ceil((previousSegment.x_ * previousSegment.x_) + (previousSegment.y_ * previousSegment.y_))));
				float previousExtension(previousMagnitude - segmentLength);
				
				const Vector2D nextSegment((source_->readPosition().x_ - segments_[segment]->readPosition().x_)
										,	(source_->readPosition().y_ - segments_[segment]->readPosition().y_));
										
				float nextMagnitude(sqrt(ceil((nextSegment.x_ * nextSegment.x_) + (nextSegment.y_ * nextSegment.y_))));
				float nextExtension(nextMagnitude - segmentLength);
				
				const Vector2D reactant((((previousSegment.x_ / previousMagnitude) * previousExtension) + ((nextSegment.x_ / nextMagnitude) * nextExtension))
									,	(((previousSegment.y_ / previousMagnitude) * previousExtension) + ((nextSegment.y_ / nextMagnitude) * nextExtension)));
									
				segments_[segment]->writeVelocity().x_ = (segments_[segment]->readVelocity().x_ * 0.95F) + (reactant.x_ * source_->getMass());
				segments_[segment]->writeVelocity().y_ = (segments_[segment]->readVelocity().y_ * 0.95F) + (reactant.y_ * source_->getMass());
			}
		}
		Vector2D calculatedPosition;
		calculatedPosition.x_ = segments_[segment]->readPosition().x_ + (segments_[segment]->readVelocity().x_ * deltaTime);
		calculatedPosition.y_ = segments_[segment]->readPosition().y_ + (segments_[segment]->readVelocity().y_ * deltaTime);
		calculatedPositions.push_back(calculatedPosition);
	}
	
	for (Uint segment(0U); segment < segments_.size(); ++segment) {
		segments_[segment]->writePosition() = calculatedPositions[segment];
	}
	
	//writePosition().x_ += (readVelocity().x_ * 0.95F) * deltaTime;
	//writePosition().y_ += (readVelocity().y_ * 0.95F) * deltaTime;
}
