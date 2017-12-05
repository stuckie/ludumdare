/// @description Move about and scan for mice

if (mTarget == undefined) {
	// New target
	mTarget = instance_nearest(x, y, objAiNode);
}

if (undefined != mTarget) {
	var spd = mBaseSpeed;
	if (objMouse == mTarget.object_index) spd = mChaseSpeed;
	move_towards_point(mTarget.x, mTarget.y, spd);
	image_angle = point_direction(x, y, mTarget.x, mTarget.y);
	if (0 == distance_to_point(mTarget.x, mTarget.y)) {
		if (objAiNode == mTarget.object_index) {
			mTarget = mTarget.mNext;
		}
	}
}
