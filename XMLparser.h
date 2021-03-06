#ifndef _XMLPARSER_HEADER_
#define _XMLPARSER_HEADER_

#include <vector>       // vector
#include <iostream>     // cout
#include <cstring>      // strcmp
#include <memory>       // shared_ptr, make_shared
#include <stack>        // stack
#include <cmath>        // exp
#include <sstream>      // istringstream
#include <fstream>      // file stream
#include <dirent.h>     // open a folder

#include "VReduction.h" // Split_Roulette
#include "Const.h"      // MAX
#include "pugixml.hpp"
#include "Geometry.h"
#include "Particle.h"
#include "Distribution.h"
#include "Source.h"
#include "Nuclide.h"
#include "Material.h"
#include "Reaction.h"
#include "Estimator.h"
#include "XSec.h"


// Function that returns an item from a vector of objects of type T by name provided
// the object class has a string and a method called name() allowing for it to be returned
template< typename T >
std::shared_ptr< T > findByName( const std::vector< std::shared_ptr< T > >& vec, const std::string name );


// Function that set nuclide based on library availability
// Current approximation: isotropic in C.O.M.
bool setNuclide( const std::string name, const std::string label, std::shared_ptr<Nuclide_t>& Nuc );


// XML input pasrese
void XML_input
( 
	std::string&                                             simName,
	unsigned long long&                                      nhist,          
	std::string&                                             particleType,
	double&                                                  Ecut_off,
	double&                                                  tcut_off,
	bool& 													 eigenvalue,
	int&													 ncycles,
	int&													 npassive,
	std::shared_ptr <K_Eigenvalue_Estimator>&      		     k_est,
	std::shared_ptr <Shannon_Entropy_Mesh>& 		  		 shannon_mesh,
	Source_Bank&                                             Sbank,
	std::vector < std::shared_ptr<Surface_t>   >&            Surface,     
	std::vector < std::shared_ptr<Region_t>    >&            Region,    
	std::vector < std::shared_ptr<Nuclide_t>   >&            Nuclide,   
	std::vector < std::shared_ptr<Material_t>  >&            Material, 
	std::vector < std::shared_ptr<Estimator_t> >&            Estimator,
	std::vector < std::shared_ptr<Distribution_t<double>> >& double_distributions,
  	std::vector < std::shared_ptr<Distribution_t<int>>    >& int_distributions,
  	std::vector < std::shared_ptr<Distribution_t<Point_t>>>& point_distributions,
    double&                                           transportMethod
);


#endif
