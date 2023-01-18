#ifndef IPLATURE_EXCEPTION_H
#define IPLATURE_EXCEPTION_H

#include <iostream>
#include <string>

using namespace std;

namespace iPlature
{
	class iException
	{
	public:
		iException(void);
		iException(std::string _reason);
		iException(int _cause, std::string _reason);
		virtual ~iException(void);
		virtual const std::string name(void) const = 0;
		const std::string what(void) const;
		const std::string ToString(void) const;
		virtual const std::string GetErrorMessage(void) const = 0;
		virtual void  prepare(std::ostream&) const;
	private:		
		static const std::string m_strName;		// iException name
		std::string m_strReason;
	protected:
		int	m_nCause;
	};

	std::ostream& operator<<(std::ostream&, const iException&);
}


#endif

