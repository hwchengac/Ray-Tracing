#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "scene.h"

class Light
	: public SceneElement
{
public:
	virtual vec3f shadowAttenuation(const vec3f& P) const = 0;
	virtual double distanceAttenuation( const vec3f& P ) const = 0;
	virtual vec3f getColor() const = 0;
	virtual vec3f getDirection( const vec3f& P ) const = 0;

protected:
	Light( Scene *scene, const vec3f& col )
		: SceneElement( scene ), color( col ) {}

	vec3f 		color;
};

class DirectionalLight
	: public Light
{
public:
	DirectionalLight( Scene *scene, const vec3f& orien, const vec3f& color )
		: Light( scene, color ), orientation( orien ) {}
	virtual vec3f shadowAttenuation(const vec3f& P) const;
	virtual double distanceAttenuation( const vec3f& P ) const;
	virtual vec3f getColor() const;
	virtual vec3f getDirection( const vec3f& P ) const;

protected:
	vec3f 		orientation;
};

class PointLight
	: public Light
{
public:
	PointLight( Scene *scene, const vec3f& pos, const vec3f& color, const double constAtten = 0, const double linearAtten = 0, const double quadAtten = 0 )
		: Light( scene, color ), position( pos ), constAtten( constAtten ), linearAtten( linearAtten ), quadAtten( quadAtten ) {}
	virtual vec3f shadowAttenuation(const vec3f& P) const;
	virtual double distanceAttenuation( const vec3f& P ) const;
	virtual vec3f getColor() const;
	virtual vec3f getDirection( const vec3f& P ) const;

protected:
	vec3f position;
	double constAtten;
	double linearAtten;
	double quadAtten;
};

class AmbientLight : public Light
{
	public:
		AmbientLight(Scene* scene, const vec3f& colour) : Light(scene, colour) {}
		virtual vec3f shadowAttenuation(const vec3f& P) const;
		virtual double distanceAttenuation(const vec3f& P) const;
		virtual vec3f getColor() const;
		virtual vec3f getDirection(const vec3f& P) const { return vec3f(0, 0, 0); };
};

#endif // __LIGHT_H__
