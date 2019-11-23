#include <SW/material.h>
#include <SW/object.h>
#include <SW/except.h>
#include <SW/light.h>

#include <math.h>
#include <assert.h>

SWmaterial::SWmaterial()
{}

SWmaterial::SWmaterial(float   beta,
		     bool    conductive,
		     bool    reflective,
		     SWcolor color,
		     float   refraction = 1.0f,
		     float   opaque = 1.0f)
{
  _beta = beta;
  _conductive  = conductive;
  _reflective  = reflective;
  _color       = color;
  _refraction  = refraction;
  _opaque      = opaque;

  _ns = -(float)(log(2.0) / log(cos(_beta)));
  
  float   r  = (_ns - 5.0f)/100.0f;
  if( r < 0.0f ) r = 0.0f;
  if( r > 1.0f ) r = 1.0f;

  if( _reflective )
    {
      _kd = 0.40f - (0.20f * sqrtf(r));
      _ks = 0.20f + (0.65f * sqrtf(r));
      cout << "Reflective ks = " << _ks << endl;
      cout << "Reflective kd = " << _kd << endl;
    }
  else
    {
      _kd = 0.65f - (0.3f * sqrtf(r));
      _ks = 0.05f + (0.9f * sqrtf(r));
      cout << "non-reflective ks = " << _ks << endl;
      cout << "non-reflective kd = " << _kd << endl;
    }
}

float SWmaterial::specular( const SWunitv& normal, 
			   const SWunitv& light, 
			   const SWunitv& view
			   ) const
{
  SWunitv h  = normal + light;
  float   hn = normal * h;
  return  powf(hn, _ns);
}


SWcolor SWmaterial::externalColor(const SWenv       * env,
				  const SWline      & ray,
				  const SWintersect & hit,
				  int                 depth,
				  const SWobject    * object
				  ) const
{


  // Create view vector
  SWvector viewVector    = - ray.direction();
  SWvector normalVector  = hit.inNormal();
  SWvector normalVectorP = normalVector * (viewVector * normalVector);
  SWvector stepVector    = normalVectorP - viewVector; 

  // get the light and object lists
  SWlist * lights = env->lights();

  // Get the point of intersection
  SWpoint point = ray * hit.inDistance();

  // This will be the color we return, start with ambient
  SWcolor theColor = _color * env->ambient() * _kd;

  SWcolor diffuseColor = env->intensity( point );

  SWcolor specularColor;

  // Run through the lights
  int size = lights->size();
  for( int i = 0; i < size; i ++ )
    {
      // fetch the light
      SWlight * light = (SWlight *)lights->get(i);

      SWline lightRay( point, light->location());

      // Check if this light *could* hit this point
      float lightAngle = hit.inNormal() * lightRay.direction();
      
      // If not, skip this light
      if( lightAngle < 0.0f ) continue;

      // Ask the env if this ray would hit an object while going to the light
      if( env->intersect(lightRay, object, false, NULL) != NULL )
      	continue;

      diffuseColor += (light->color() * light->power() ) * lightAngle;

      SWunitv lightUnitv = lightRay.direction();
      SWunitv viewUnitv  = viewVector;

      // Add on specular color
      specularColor += (light->color() * light->power() ) *
	specular(hit.inNormal(), lightUnitv, viewUnitv);
    }

  // If the object is metal, the specular is *= its color
  if( _conductive )
    specularColor = specularColor * _color;

  // Add on the specular color
  theColor += (specularColor * _ks);

  // Add on the diffuse color
  theColor += (_color * (diffuseColor * _kd));

  if( _reflective )
    {    
      if( depth > 0 )
	{
	  // Compute reflect vector
	  SWvector reflectVector = normalVectorP + stepVector;

	  // Create a reflect ray
	  SWline  reflectRay( point, SWunitv(reflectVector));

	  // Compute the reflect color
	  SWcolor reflectColor = env->color(reflectRay, 
					   depth -1, 
					   object);
	  // Add on the reflect color
	  theColor += (reflectColor * _ks);
	}
    }

  // Check if we are at all transparent
  if( _opaque != 1.0f )
    {
      // refract the ray
      SWline refractRay = object->enter(ray, hit);

      // Now compute the internalColor
      SWcolor iColor = internalColor( env, refractRay, 
				      depth-1, object );


      // Scale the external color and add on the internal
      theColor = ( theColor * _opaque ) + 
	( iColor * (1.0f - _opaque));

    }
	
  return theColor;
}

SWcolor SWmaterial::internalColor(const SWenv    * env,
				  const SWline   & ray,
				  int              depth,  
				  const SWobject * object 
				  ) const
{
  SWcolor exitColor;

  // Internal bounce
  SWline bounceRay;

  if( depth == 0 ) return SWcolor();
      
  try

    {
      // Get the exit ray
      SWline exitRay = object->leave(ray, depth, & bounceRay);
      
      // First, get the color of the exit ray
      exitColor = env->color( exitRay, depth-1, object);
      
    }
  catch (noLeave)
    {
      // Set exit color to black ? or maybe grey
      exitColor = SWcolor(1.0f, 1.0f, 1.0f); 
    }

  // Now compute the internalColor
  SWcolor iColor = internalColor( env, bounceRay, 
				  depth-1, object );
      
  // Scale the internalColor and add it to the exitColor
  exitColor = ( exitColor * (1.0f - _opaque ) ) + 
    iColor * _opaque;

  return exitColor;
}
  
				 
				 
  

