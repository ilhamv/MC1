#include <vector>

#include "Const.h" // MAX
#include "Solver.h"


// Quad solver for sphere surface
// return smallest positive real root if it exists; if it does not, return very big number
// *Seems redundantly hard-coded, yet it saves up the multiplication operation with a
double sphere_quad( const double b, const double c ) 
{
  	double d = b*b - 4.0 * c;
    	
	// roots are complex, no intersection, return huge number
	// or identical roots, tangent, return huge number
  	if ( d <= 0.0 ) { return MAX; }	
  	
	else 
	{
    		double sqrtd = std::sqrt(d);

    		double r1 = 0.5 * ( -1.0 * b - sqrtd );
    		double r2 = 0.5 * ( -1.0 * b + sqrtd );

		// Negative roots return huge number
		if ( r1 < 0 ) { r1 = MAX; }
		if ( r2 < 0 ) { r2 = MAX; }

    		return std::fmin( r1, r2 );
  	}
}


// Quad solver for infinite cylinder and cone surface
// return smallest positive real root if it exists; if it does not, return very big number
double solve_quad( const double a, const double b, const double c ) 
{
  	double d = b*b - 4.0 * a * c;
    	
	// roots are complex, no intersection, return huge number
	// or identical roots, tangent, return huge number
  	if ( d <= 0.0 ) { return MAX; }
  	
	else 
	{
    		double sqrtd = std::sqrt(d);
		double ai = 0.5 / a;

    		double r1 = ai * ( -1.0 * b - sqrtd );
    		double r2 = ai * ( -1.0 * b + sqrtd );

		// Negative roots return huge number
		if ( r1 < 0 ) { r1 = MAX; }
		if ( r2 < 0 ) { r2 = MAX; }

    		return std::fmin( r1, r2 );
  	}
}


// Binary search a double location in a bin grid
int Binary_Search( const double x, const std::vector<double>& vec )
{
	int left  = 0;
	int right = vec.size() - 1;
	int mid;

	while ( left <= right )
	{
		mid = ( left +  right ) / 2;
		
		if ( vec[mid] < x ) { left  = mid + 1; }
		else                { right = mid - 1; }
	}
	
	return right; 
	// Note:
	// 	value < lowest  grid --> -1
	// 	value > highest grid --> vector.size - 1 (or number of bins)
	// 	value = grid points  --> location of bin whose upper bound is the value
	// 	                         (-1 if value = lowest grid)
}


// Scatter direction
// Return final direction dir_f after scatter initial direction dir_i with scattering polar angle mu
Point_t scatter_direction( const Point_t dir_i, const double mu0 )
{
	// Sample azimuthal direction
	const double     azi = PI2 * Urand();
	const double cos_azi = std::cos(azi);
	const double sin_azi = std::sin(azi);
	const double      Ac = std::sqrt( 1.0 - mu0 * mu0 );
	Point_t      dir_f; // Final direction

	if( dir_i.z != 1.0 )
	{
		const double       B = std::sqrt( 1.0 - dir_i.z * dir_i.z );
		const double       C = Ac / B;
		
		dir_f.x = dir_i.x * mu0 + ( dir_i.x * dir_i.z * cos_azi - dir_i.y * sin_azi ) * C;
		dir_f.y = dir_i.y * mu0 + ( dir_i.y * dir_i.z * cos_azi + dir_i.x * sin_azi ) * C;
		dir_f.z = dir_i.z * mu0 - cos_azi * Ac * B;
	}
	
	// If dir_i = k, interchange z and y in the scattering formula
	else
	{
		const double       B = std::sqrt( 1.0 - dir_i.y * dir_i.y );
		const double       C = Ac / B;
		
		Point_t            q; // to store new direction point
        
		dir_f.x = dir_i.x * mu0 + ( dir_i.x * dir_i.y * cos_azi - dir_i.z * sin_azi ) * C;
		dir_f.z = dir_i.z * mu0 + ( dir_i.z * dir_i.y * cos_azi + dir_i.x * sin_azi ) * C;
		dir_f.y = dir_i.y * mu0 - cos_azi * Ac * B;
	}
	return dir_f;
}

// Lagrenge interpolation
double Linterpolate( const double x, const double x1, const double x2, const double y1, const double y2 )
{ return ( x - x2 ) / ( x1 - x2 ) * y1 + ( x - x1 ) / ( x2 - x1 ) * y2; }
