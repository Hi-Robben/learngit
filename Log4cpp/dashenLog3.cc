#include <iostream>
#include <string>
#include <log4cpp/Category.hh>
#include <log4cpp/Appender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
using namespace log4cpp;
#define rollingFileName "rollingMylogger.log"
#define logFileName "Mylogger.log"

#ifndef __LOGSINMPLE_H__
#define __LOGSIMPLE_H__

namespace wd
{
class Mylogger
{
public:
	static Mylogger * getMylogger()
	{
		if(NULL == _pMylogger)
		{
			PatternLayout *patternLayout1=new PatternLayout();
			patternLayout1->setConversionPattern("%d [%p] %m%n");
 
			PatternLayout *patternLayout2=new PatternLayout();
			patternLayout2->setConversionPattern("%d [%p] %m%n");
			
			OstreamAppender *ostAppender=new OstreamAppender("ostAppender",&cout);
			ostAppender -> setLayout(patternLayout1);
			
			FileAppender * fileAppender = new FileAppender("fileAppender",logFileName);
			fileAppender -> setLayout(patternLayout2);
			
			_pMylogger -> _myRecord.setAppender(ostAppender);
			_pMylogger -> _myRecord.setAppender(fileAppender);
			_pMylogger -> _myRecord.setPriority(Priority::DEBUG);
		}
		return _pMylogger;
	}
	void destory()
	{
		if(_pMylogger)
		{
			delete _pMylogger;
			_pMylogger -> _myRecord.shutdown();
			//Category::shutdown();
		}
	}
	void print()
	{
		cout << "_pMylogger=" << _pMylogger << endl;
	}
	
/*	#define LogError(str1)
{   Mylogger *plog = Mylogger::getLog();\
    char str[100] = {0};\
    sprintf(str,"Error %s in %s,line %d,func %s",str1, __FILE__ ,__LINE__ , __FUNCTION__);\
    plog->error(str);\
}*/
	void LogError(const char * msg)
	{
		stringstream temp;
		temp << msg << "(" << __FILE__ << "," << __FUNCTION__ << "," << __LINE__ << ")" <<endl;
		_myRecord.error(temp.str());
		/* _myRecord.error(msg) */
	}
	void LogWarn(const char * msg)
	{
		stringstream temp;
		temp << msg << "(" << __FILE__ << "," << __FUNCTION__ << "," << __LINE__ << ")" <<endl;
		_myRecord.warn(temp.str());
		/* _myRecord.warn(msg) */
	}
	void LogInfo(const char * msg)
	{
		stringstream temp;
		temp << msg << "(" << __FILE__ << "," << __FUNCTION__ << "," << __LINE__ << ")" <<endl;
		_myRecord.info(temp.str());
		/* _myRecord.info(msg) */
	}
	void LogDebug(const char * msg)
	{
		stringstream temp;
		temp << msg << "(" << __FILE__ << "," << __FUNCTION__ << "," << __LINE__ << ")" <<endl;
		_myRecord.debug(temp.str());
		/* _myRecord.debug(msg) */
	}
private:
	Mylogger(){}
	~Mylogger(){}
	static Mylogger *_pMylogger;
	static Category &_myRecord;
	// Category& _root;
};


Mylogger *Mylogger::_pMylogger=NULL;
Category &Mylogger::_myRecord=Category::getRoot().getInstance("_myRecord");
}
#endif

using wd::Mylogger;
int main()
{
	Mylogger *mylogger1 = Mylogger::getMylogger();
	//Mylogger *mylogger2 = Mylogger::getMylogger();
	mylogger1 -> print();
	//mylogger2 -> print();
	
	for(int i = 0; i < 2; i++)
	{
		 mylogger1->LogWarn("warn .....");
		 mylogger1->LogError("error .....");
		 mylogger1->LogInfo("info .....");
		 mylogger1->LogDebug("debug .....");
	}
	mylogger1->destory();
	return 0;
}
