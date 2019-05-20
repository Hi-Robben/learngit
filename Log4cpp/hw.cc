#include <iostream>
#include <iostream>
#include <log4cpp/Category.hh>
#include <log4cpp/Appender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/BasicLayout.hh>
using namespace std;
using namespace log4cpp;

int main(int argc, char ** argv)
{
	PatternLayout * pLayout1 = new PatternLayout();
	pLayout1 -> setConversionPattern("%d:%p %c %x:%m%n");
	
	PatternLayout * pLayout2 = new PatternLayout();
	pLayout2 -> setConversionPattern("%d:%p %c %x:%m%n");
	
	//Appender* fileAppender = new FileAppender("fileAppender","wxb.log");
	//fileAppender -> setLayout(pLayout1);

	OstreamAppender * osAppender = new OstreamAppender("osAppender",&cout);
	osAppender -> setLayout(pLayout1);

	RollingFileAppender* rollfileAppender = new RollingFileAppender( "rollfileAppender","hw.log",5*1024,1);
    rollfileAppender->setLayout(pLayout2);

	 Category& root = Category::getRoot().getInstance("RootName");
    root.addAppender(osAppender);
    root.addAppender(rollfileAppender);
    root.setPriority(Priority::DEBUG);

	 for (int i = 0; i < 3; i++)
    {
        string strError;
        ostringstream oss;
        oss<<i<<":Root Error Message!";
        strError = oss.str();
        root.error(strError);
    }

    Category::shutdown();
    return 0;
}
