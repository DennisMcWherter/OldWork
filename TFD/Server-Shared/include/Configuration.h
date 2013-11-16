//
// Configuration.h
//
//
// Used for reading configuration parameters, use _config to access the parameters
//
// Main Developers: RageD (Dennis J. McWherter, Jr.), infernale890
//

#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__

#include "Singleton.h"
#include <string>
#include "Poco/Util/PropertyFileConfiguration.h"
#include "Poco/AutoPtr.h"

namespace TFD
{
	class Configuration
	{
	public:
		Configuration();
	
		void setSource(std::string Filename);
		std::string getValue(std::string key) const;

	private:
		Poco::AutoPtr<Poco::Util::PropertyFileConfiguration> _Conf;
	};
}
#define _config Singleton<TFD::Configuration>::Instance()
#endif
