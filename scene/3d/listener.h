/*************************************************************************/
/*  listener.h                                                           */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2018 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2018 Godot Engine contributors (cf. AUTHORS.md)    */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#ifndef LISTENER_H
#define LISTENER_H

#include "scene/3d/spatial.h"
#include "scene/main/viewport.h"
#include "scene/3d/spatial_velocity_tracker.h"

class Listener : public Spatial {

	GDCLASS(Listener, Spatial);

public:
	enum DopplerTracking {
		DOPPLER_TRACKING_DISABLED,
		DOPPLER_TRACKING_IDLE_STEP,
		DOPPLER_TRACKING_PHYSICS_STEP
	};

	enum {
		NOTIFICATION_BECAME_CURRENT = 50,
		NOTIFICATION_LOST_CURRENT = 51
	};

private:
	bool force_change;
	bool current;

	RID scenario_id;

	virtual bool _can_gizmo_scale() const;
	virtual RES _get_gizmo_geometry() const;

	friend class Viewport;
	void _update_audio_listener_state();

	DopplerTracking doppler_tracking;
	Ref<SpatialVelocityTracker> velocity_tracker;

protected:
	void _update_listener();
	virtual void _request_listener_update();

	void _notification(int p_what);

	static void _bind_methods();

public:
	void make_current();
	void clear_current();
	bool is_current() const;
	void set_current(bool p_current);

	virtual Transform get_listener_transform() const;

	void set_doppler_tracking(DopplerTracking p_tracking);
	DopplerTracking get_doppler_tracking() const;
	Vector3 get_doppler_tracked_velocity() const;

	void set_visible_layers(uint32_t p_layers);
	uint32_t get_visible_layers() const;

	Vector<Plane> get_frustum() const;

	Listener();
	~Listener();
};

VARIANT_ENUM_CAST(Listener::DopplerTracking);

#endif
