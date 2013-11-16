//
// Configuration.cpp
//
//
// Used for reading configuration parameters, use _config to access the parameters
//
// Main Developers: RageD (Dennis J. McWherter, Jr.), infernale890
//


#include "Configuration.h"
ISTANTIATE_SINGLETON(TFD::Configuration)

namespace TFD
{
	Configuration::Configuration() : _Conf(new Poco::Util::PropertyFileConfiguration)
	{
	}
	
	void Configuration::setSource(std::string Filename)
	{
		_Conf->load(Filename);
	}

	std::string Configuration::getValue(std::string key) const
	{
		return (_Conf->getString(key));
	}
}
