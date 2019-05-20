#include <iostream>
#include <log4cpp/Category.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/BasicLayout.hh>
#include <log4cpp/Priority.hh>
using namespace std;
using namespace log4cpp;
int main(int argc, char** argv)
{
	OstreamAppender* osAppender = new OstreamAppender("osAppender",&cout);
	osAppender -> setLayout(new BasicLayout());

	Category& root = Category::getRoot();
	root.addAppender(osAppender);
	root.setPriority(Priority::DEBUG);

	root.error("Hello log4cpp in a Error Message!");
	root.warn("Hello log4cpp in a Warning Message!");

	Category::shutdown();
	return 0;
}



