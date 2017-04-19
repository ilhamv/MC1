#include <vector>  // vector
#include <memory>  // shared_ptr

#include "Random.h"
#include "Particle.h"
#include "Reaction.h"
#include "Nuclide.h"
#include "Material.h"


// Getters
std::string Material_t::name()   { return m_name; }   // Name
// macroXsec
double Material_t::SigmaS( const double E ) 
{ 
	double sum = 0.0;
	for ( auto& n : nuclides )
	{
		sum += n.first->sigmaS( E ) * n.second;
	}	
	return sum;
}
double Material_t::SigmaC( const double E ) 
{ 
	double sum = 0.0;
	for ( auto& n : nuclides )
	{
		sum += n.first->sigmaC( E ) * n.second;
	}	
	return sum;
}
double Material_t::SigmaF( const double E ) 
{ 
	double sum = 0.0;
	for ( auto& n : nuclides )
	{
		sum += n.first->sigmaF( E ) * n.second;
	}	
	return sum;
}
double Material_t::SigmaT( const double E ) 
{ 
	double sum = 0.0;
	for ( auto& n : nuclides )
	{
		sum += n.first->sigmaT( E ) * n.second;
	}	
	return sum;
}


// Add a nuclide
// the supplied variable are the nuclide and its nuclide density
void Material_t::addNuclide( const std::shared_ptr< Nuclide_t >& Nuclide, double N ) 
{ nuclides.push_back( std::make_pair( Nuclide, N ) ); }


// Sample collision distance
double Material_t::collision_distance_sample( const double E )
{ return - std::log( Urand() ) / SigmaT( E ); }


// Sample collided nuclide
std::shared_ptr< Nuclide_t > Material_t::nuclide_sample( const double E )
{
	double u = SigmaT( E ) * Urand();
	double s = 0.0;
	for ( auto& n : nuclides ) 
	{
		// first is pointer to nuclide, second is nuclide density
		s += n.first->sigmaT( E ) * n.second;
		if ( s > u ) { return n.first; }
	}
}


// Sample entire collision (nuclide, then nuclide reaction)
// Then, process the reaction on the Particle 
void Material_t::collision_sample( Particle_t& P, std::stack<Particle_t>& Pbank ) 
{
	// First sample nuclide
	std::shared_ptr< Nuclide_t >  N = nuclide_sample( P.energy() );

	// Now get the reaction
	std::shared_ptr< Reaction_t > R = N->reaction_sample( P.energy() );
	
	// Finally process the reaction on the Particle
	R->sample( P, Pbank );
}
